/**
 * @copyright
 * MIT License
 *
 * Copyright (c) 2017 Car4Tegra
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @file mainwindow.cpp
 * @date 2017-04-18
 *
 * @brief This file contains the definition of class MainWindow.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


// std includes
#include <string>
#include <algorithm>
#include <vector>

// qt includes
#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QFont>
#include <QMessageBox>
#include <QRegExp>
#include <QProcess>
#include <QStringList>
#include <QString>
#include <QDate>

// ClassCreator includes
#include "mainwindow.hpp"
#include "preview.hpp"
#include "classtemplatexmlparser.hpp"
#include "classcreator.hpp"
#include "stringutil.hpp"


MainWindow::MainWindow(QWidget* apParent, Qt::WindowFlags aFlags)
   : QMainWindow(apParent, aFlags), mSettings(std::make_shared<UserSettingsData>())
{
   ui.setupUi(this);
   ui.treeWidget->setPropertiesWithoutValueMarked(true);

   // read settings
   try
   {
      // try to find xml template files
      ConfigurationManager::getTemplateList(mTemplateFiles);

      //load user settings
      ConfigurationManager::getUserSettings(mSettings);
   }
   catch (std::runtime_error e)
   {
      this->showError(e.what());
   }

   // create dialogs
   mPv = new Preview();
   mSet = new UserSettingsDialog();
   
   // connect signals
   QObject::connect(ui.btPreview, SIGNAL(clicked()), this, SLOT(btPreviewClicked()));
   QObject::connect(ui.btSettings, SIGNAL(clicked()), this, SLOT(btSettingsClicked()));
   QObject::connect(ui.btSave, SIGNAL(clicked()), this, SLOT(btSaveClicked()));
   QWidget::connect(mSet,
                    SIGNAL(dialogClosing(const std::shared_ptr<UserSettingsData>&)),
                    this,
                    SLOT(mSetClosing(const std::shared_ptr<UserSettingsData>&)));
   QObject::connect(ui.cbClassTemplates, SIGNAL(currentIndexChanged(int)), this, SLOT(cbIndexChanged(int)));
   QObject::connect(ui.btBrowse, SIGNAL(clicked()), this, SLOT(btBrowseClicked()));
   QObject::connect(ui.btGenerate, SIGNAL(clicked()), this, SLOT(btGenerateClicked()));
   QObject::connect(ui.cbAutoDetect, SIGNAL(clicked(bool)), this, SLOT(cbAutoDetectClicked(bool)));
   //QObject::connect(ui.treeWidget, SIGNAL(currentItemChanged(QtBrowserItem*)), this, SLOT(treeItemChanged(QtBrowserItem*)));
   
   // set last output path and connect changed signal
   ui.lePath->setText(mSettings->mOutputPath.c_str());
   QObject::connect(ui.lePath, SIGNAL(textChanged(const QString&)), this, SLOT(lePathTextChanged(const QString&)));

   // set variables for property browser
   mpVariantManager = new QtVariantPropertyManager();
   mpVariantFactory = new QtVariantEditorFactory();
   ui.treeWidget->setFactoryForManager(mpVariantManager, mpVariantFactory);
   mpVariantManagerFile = new QtVariantPropertyManager();
   mpVariantFactoryFile = new QtVariantEditorFactory();
   ui.treeWidget->setFactoryForManager(mpVariantManagerFile, mpVariantFactoryFile);
   mpVariantManagerCmd = new QtVariantPropertyManager();
   mpVariantFactoryCmd = new QtVariantEditorFactory();
   ui.treeWidget->setFactoryForManager(mpVariantManagerCmd, mpVariantFactoryCmd);

   // create Template dropdown list
   for(size_t i = 0; i < mTemplateFiles.size(); i++)
   {
      std::shared_ptr<ClassTemplateData> lTplData;

      try
      {
         ClassTemplateXMLParser::loadTemplateParameters(mTemplateFiles[i], lTplData);
      }
      catch(std::runtime_error e)
      {
         this->showError(e.what());
      }

      ui.cbClassTemplates->addItem(lTplData->getName().c_str());
   }
}


// -----------------------------------------------------------------------
// ----------


MainWindow::~MainWindow()
{
   delete mPv;
   delete mSet;
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::closeEvent( QCloseEvent *evt )
{
   // close all open dialogs
   mPv->close();
   mSet->close();

   // clear template data
   mTplData.reset();
   mTplProps.clear();
   mTplFileProps.clear();
   mTplCmd.clear();

   // disconnect signals
   //QObject::disconnect(ui.treeWidget,
   //                    SIGNAL(currentItemChanged(QtBrowserItem*)),
   //                    this,
   //                    SLOT(treeItemChanged(QtBrowserItem*)));
   QObject::disconnect(mpVariantManager,
                       SIGNAL(valueChanged(QtProperty*, QVariant)),
                       this,
                       SLOT(valueChanged(QtProperty*, QVariant)));
   QObject::disconnect(mpVariantManagerFile,
                       SIGNAL(valueChanged(QtProperty*, QVariant)),
                       this,
                       SLOT(valueChanged(QtProperty*, QVariant)));
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::btPreviewClicked(void)
{   
   updatePreview();   
	mPv->show();
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::btSettingsClicked(void)
{   
   mSet->updateSettingsView(mSettings);
	mSet->show();
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::mSetClosing(const std::shared_ptr<UserSettingsData>& arSettings)
{
   // update changed settings
   mSettings = arSettings;
   
   try
   {
      // write changed settings to User-XML
      ConfigurationManager::setUserSettings(mSettings);
   }
   catch(std::runtime_error e)
   {
      this->showError(e.what());
   }

   // Update changed settings in Preview
   if(mPv->isVisible())
      updatePreview();

   // update paths
   updatFilePaths();
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::cbIndexChanged(int aIndex)
{
   // clear current template data
   mTplData.reset();
   mTplProps.clear();
   mTplFileProps.clear();
   mTplCmd.clear();

   try
   {
      // parse selected template XML
      ClassTemplateXMLParser::loadTemplateParameters(mTemplateFiles[static_cast<size_t>(aIndex)],
                                                     mTplData,
                                                     mTplProps,
                                                     mTplFileProps,
                                                     mTplCmd);
   }
   catch(std::runtime_error e)
   {
      this->showError(e.what());
   }

   // get property index of class name
   for(size_t i = 0; i < mTplProps.size();i++)
   {
      if(mTplProps[i]->getIdentifier() == mTplData->getClasNameProperty())
      {
         mClassNameIndex = static_cast<int>(i);
         break;
      }
   }
   
   // update tree view
   updatePropertyView();

   // release or block generate button
   setGenerateState();

   // if preview window is visible => show code
   if(mPv->isVisible())
      updatePreview();

   // check if auto detect
   if(mTplData->getUseSystemPath())
   {
      QByteArray pPath;
      pPath = qgetenv (mTplData->getSystemPath().c_str());

      if(pPath != nullptr)
      {
         ui.cbAutoDetect->setEnabled(true);
         ui.cbAutoDetect->setChecked(true);
         ui.lePath->setEnabled(false);
         ui.btBrowse->setEnabled(false);
         ui.lePath->setText(pPath);
      }
      else
      {
         ui.cbAutoDetect->setChecked(false);
         ui.cbAutoDetect->setEnabled(false);
         ui.lePath->setEnabled(true);
         ui.btBrowse->setEnabled(true);
         ui.lePath->setText(mSettings->mOutputPath.c_str());
      }
   }
   else
   {
      ui.cbAutoDetect->setChecked(false);
      ui.cbAutoDetect->setEnabled(false);
      ui.lePath->setEnabled(true);
      ui.btBrowse->setEnabled(true);
      ui.lePath->setText(mSettings->mOutputPath.c_str());
   }

   // update paths
   updatFilePaths();
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::btBrowseClicked(void)
{
   const QString lPath = ui.lePath->text();
   QString lDir = QFileDialog::getExistingDirectory(this,
                                                    tr("Select output directory"),
                                                    lPath,
                                                    QFileDialog::ShowDirsOnly);
   if(!lDir.isEmpty())
   {
      ui.lePath->setText(lDir);

      // update paths
      updatFilePaths();
   }
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::btSaveClicked(void)
{
   
}


// -----------------------------------------------------------------------
// ----------


bool MainWindow::parseFiles(std::string& arHppContent, std::string& arCppContent)
{
   // get path to template file
   QFileInfo lFileInfo;
   lFileInfo.setFile(mTemplateFiles[static_cast<size_t>(ui.cbClassTemplates->currentIndex())].c_str());
   std::string lTemplateHeaderFile = lFileInfo.absoluteDir().absolutePath().toStdString() +
                                     "/" + mTplData->getHeaderFileName();
   std::string lTemplateSourceFile = lFileInfo.absoluteDir().absolutePath().toStdString() +
                                     "/" + mTplData->getSourceFileName();

   // get tokens
   std::vector<std::shared_ptr<ClassTemplateProperty> > lParsProps;
   getTokens(lParsProps);

   // parse template file
   try
   {
      if(mTplData->getHasHeader())
         ClassCreator::parseTemplateFile(lTemplateHeaderFile, arHppContent, lParsProps);
      if(mTplData->getHasSource())
         ClassCreator::parseTemplateFile(lTemplateSourceFile, arCppContent, lParsProps);
   }
   catch(std::runtime_error e)
   {
      this->showError(e.what());
   }

   return true;
}


// -----------------------------------------------------------------------
// ----------


bool MainWindow::parseCmakeFile(std::string& arCmakeContent)
{
   // get path to template file
   QFileInfo lFileInfo;
   lFileInfo.setFile(mTemplateFiles[static_cast<size_t>(ui.cbClassTemplates->currentIndex())].c_str());
   std::string lTemplateCmakeFile = lFileInfo.absoluteDir().absolutePath().toStdString() +
                                    "/" + mTplData->getCmakeFileName();

   // get tokens
   std::vector<std::shared_ptr<ClassTemplateProperty> > lParsProps;
   getTokens(lParsProps);

   // parse template file
   if(mTplData->getHasCmake())
   {
      try
      {
         ClassCreator::parseTemplateFile(lTemplateCmakeFile, arCmakeContent, lParsProps);
      }
      catch(std::runtime_error e)
      {
         this->showError(e.what());
      }
   }

   return true;
}


// -----------------------------------------------------------------------
// ----------


bool MainWindow::parseFilePaths(std::string& arHppPath, std::string& arCppPath, std::string& arCmakePath)
{
   // get tokens
   std::vector<std::shared_ptr<ClassTemplateProperty> > lParsProps;
   getTokens(lParsProps);

   // parse file path templates
   try
   {
      ClassCreator::parseTemplate(mTplData->getHeaderPath(), arHppPath, lParsProps);
      ClassCreator::parseTemplate(mTplData->getSourcePath(), arCppPath, lParsProps);
      ClassCreator::parseTemplate(mTplData->getCmakePath(), arCmakePath, lParsProps);
   }
   catch(std::runtime_error e)
   {
      this->showError(e.what());
   }

   return true;
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::getTokens(std::vector<std::shared_ptr<ClassTemplateProperty> >& arParsProps)
{
   // create class name for files
   const std::string lFileName = mTplProps[static_cast<size_t>(mClassNameIndex)]->mValue;
   const std::string lHeaderExt = mSettings->mHeaderExtension;
      
   //create filename
   std::string lHeaderFileName = StringUtil::toLower(lFileName) + "." + mSettings->mHeaderExtension;
   std::string lSourceFileName = StringUtil::toLower(lFileName) + "." + mSettings->mSourceExtension;
   std::string lCmakeFileName = "CMakeLists.txt";
	   
   // create indent string
   std::string lIdentString = "";
   for(int i = 0; i < std::atoi(mSettings->mIndentSpace.c_str()); i++)
   {
      lIdentString += " ";
   }

   // copy properties and add user properties
   for(size_t i = 0; i < mTplProps.size(); i++)
   {
      arParsProps.push_back(std::make_shared<ClassTemplateProperty>(*mTplProps[i]));
   }

   // copy file path properties and add user properties
   for(size_t i = 0; i < mTplFileProps.size(); i++)
   {
      arParsProps.push_back(std::make_shared<ClassTemplateProperty>(*mTplFileProps[i]));
   }

	// create macro filename
   std::string lNdefMacro = "__";
   
	// has namespace and subnamespace?
   bool lHasNam = false;
   bool lHasSubNam = false;
	bool lNamTok = false;
   bool lSubNamTok = false;
   std::string lNam;
   std::string lSubName;
   
   for(size_t j = 0; j < arParsProps.size(); ++j)
   {
      if(arParsProps[j]->getIdentifier()== "HAS_NAMESPACE")
		{
         const std::string lTemp = arParsProps[j]->mValue;
         if ("true" == StringUtil::toLower(lTemp))
            lHasNam = true;
         else
            lHasNam = false;
			lNamTok = true;
		}
      else if(arParsProps[j]->getIdentifier() == "HAS_SUBNAMESPACE")
		{
         const std::string lTemp = arParsProps[j]->mValue;
         if ("true" == StringUtil::toLower(lTemp))
            lHasSubNam = true;
         else
            lHasSubNam = false;
			lSubNamTok = true;
		}
		else if(arParsProps[j]->getIdentifier() == "NAMESPACE")
			lNam = arParsProps[j]->mValue;
		else if(arParsProps[j]->getIdentifier() == "SUB_NAMESPACE")
			lSubName = arParsProps[j]->mValue;
   }
	
   StringUtil::toUpper(lNam);
   StringUtil::toUpper(lSubName);

   if((lNamTok && lHasNam) || (!lNamTok && (lNam != "")))
		lNdefMacro = lNdefMacro + lNam + "_";
		
   if((lSubNamTok && lHasSubNam) || (!lSubNamTok && (lSubName != "")))
		lNdefMacro = lNdefMacro + lSubName + "_";
   
   lNdefMacro = lNdefMacro + StringUtil::toUpper(lFileName) + "_" + StringUtil::toUpper(lHeaderExt) + "__";

   // add user properties
   arParsProps.push_back(std::make_shared<ClassTemplateProperty>("ath",
                                                                 "AUTHOR",
                                                                 ClassTemplateProperty::PROP_TYPE_STRING,
                                                                 mSettings->mAuthor,
                                                                 "", "", ""));
   arParsProps.push_back(std::make_shared<ClassTemplateProperty>("fnh",
                                                                 "HEADER_FILE_NAME",
                                                                 ClassTemplateProperty::PROP_TYPE_STRING,
                                                                 lHeaderFileName,
                                                                 "", "", ""));
   arParsProps.push_back(std::make_shared<ClassTemplateProperty>("fns",
                                                                 "SOURCE_FILE_NAME",
                                                                 ClassTemplateProperty::PROP_TYPE_STRING,
                                                                 lSourceFileName,
                                                                 "", "", ""));
   arParsProps.push_back(std::make_shared<ClassTemplateProperty>("fnc",
                                                                 "CMAKE_FILE_NAME",
                                                                 ClassTemplateProperty::PROP_TYPE_STRING,
                                                                 lCmakeFileName,
                                                                 "", "", ""));
   arParsProps.push_back(std::make_shared<ClassTemplateProperty>("def",
                                                                 "IFNDEF_MACRO",
                                                                 ClassTemplateProperty::PROP_TYPE_STRING,
                                                                 lNdefMacro,
                                                                 "", "", ""));
   arParsProps.push_back(std::make_shared<ClassTemplateProperty>("date",
                                                                 "DATE",
                                                                 ClassTemplateProperty::PROP_TYPE_STRING,
                                                                 QDate::currentDate().toString(mSettings->mDateFormat.c_str()).toStdString(),
                                                                 "", "", ""));
   arParsProps.push_back(std::make_shared<ClassTemplateProperty>("indent",
                                                                 "INDENT",
                                                                 ClassTemplateProperty::PROP_TYPE_STRING,
                                                                 lIdentString,
                                                                 "", "", ""));
   
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::updatePreview(void)
{
   std::string lHppContent;
   std::string lCppContent;
   std::string lCmakeContent;

   // create class name for files
   std::string lFileName = mTplProps[static_cast<size_t>(mClassNameIndex)]->mValue;
   StringUtil::toLower(lFileName);

   mPv->setFiles(mTplData->getHasHeader(), mTplData->getHasSource(), mTplData->getHasCmake());

   // update view
   mPv->updateFileNames(lFileName, mSettings->mHeaderExtension, mSettings->mSourceExtension);

   // try to parse template
   if (parseFiles(lHppContent, lCppContent))
   {
      // update preview
      if (mTplData->getHasHeader())
         mPv->updateHpp(lHppContent);
      if (mTplData->getHasSource())
         mPv->updateCpp(lCppContent);
   }
   else
      showError("Error while parsing template!");

   // try to parse template
   if(parseCmakeFile(lCmakeContent))
   {
      // update preview
      if(mTplData->getHasCmake())
         mPv->updateCmake(lCmakeContent);
   }
   else
      showError("Error while parsing template!");
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::updatePropertyView(void)
{
   // disconnect changed signal
   //QObject::disconnect(ui.treeWidget,
   //                    SIGNAL(currentItemChanged(QtBrowserItem*)),
   //                    this,
   //                    SLOT(treeItemChanged(QtBrowserItem*)));
   QObject::disconnect(mpVariantManager,
                       SIGNAL(valueChanged(QtProperty*, QVariant)),
                       this,
                       SLOT(valueChanged(QtProperty*, QVariant)));
   QObject::disconnect(mpVariantManagerFile,
                       SIGNAL(valueChanged(QtProperty*, QVariant)),
                       this,
                       SLOT(valueChanged(QtProperty*, QVariant)));
   

   // Clear current view
   ui.treeWidget->clear();
   mPropViewElem.clear();
   mpVariantManager->clear();   
   mCmdViewElem.clear();
   mpVariantManagerCmd->clear();   


   //####################################
   // create property items
   //####################################

   std::string lLastGroup = "";
   QtVariantProperty* lGroup = nullptr;

   // create new property items
   for(size_t i=0; i < mTplProps.size(); i++)
   {
      int lPropertyType;

      // select property type
      if(mTplProps[i]->getType() == ClassTemplateProperty::PROP_TYPE_BOOL)
         lPropertyType = QVariant::Bool;
      else if(mTplProps[i]->getType() == ClassTemplateProperty::PROP_TYPE_STRING)
         lPropertyType = QVariant::String;
      else if(mTplProps[i]->getType() == ClassTemplateProperty::PROP_TYPE_STRINGLIST)
         lPropertyType = QtVariantPropertyManager::enumTypeId();
      else
         lPropertyType = QVariant::String;
      
      // add property
      mPropViewElem.push_back(std::shared_ptr<QtVariantProperty>(mpVariantManager->addProperty(lPropertyType,
                                                                                               mTplProps[i]->getName().c_str())));

      // create list values
      if(mTplProps[i]->getType() == ClassTemplateProperty::PROP_TYPE_STRINGLIST)
      {
         QStringList lValues;
         std::vector<std::string> lValueList = mTplProps[i]->getStringList();

         for(size_t j=0; j<lValueList.size();j++)
         {
            lValues << lValueList[j].c_str();
         }

         mPropViewElem[mPropViewElem.size()-1]->setAttribute("enumNames", lValues);
      }
      else if(mTplProps[i]->getType() == ClassTemplateProperty::PROP_TYPE_STRING)
      {
         mPropViewElem[mPropViewElem.size()-1]->setAttribute("regExp",
                                                             QRegExp(mTplProps[i]->getRegExpression().c_str()));
      }
            
      // set default values
      mPropViewElem[mPropViewElem.size()-1]->setValue(mTplProps[i]->getDefaultValue().c_str());
      mPropViewElem[mPropViewElem.size()-1]->setToolTip(mTplProps[i]->getInfoText().c_str());

      // create group
      if(mTplProps[i]->getGroup() == "")
      {
         // no group => add property to view
         ui.treeWidget->addProperty(&(*mPropViewElem[mPropViewElem.size()-1]));
         lLastGroup = "";
      }
      else
      {
         if(lLastGroup != mTplProps[i]->getGroup())
         {
            // create new group
            lGroup = mpVariantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
                                                   mTplProps[i]->getGroup().c_str());
            lLastGroup = mTplProps[i]->getGroup();

            // add group to view
            ui.treeWidget->addProperty(lGroup);
            ui.treeWidget->setBackgroundColor(ui.treeWidget->items(lGroup)[0],QColor::fromRgb(180,180,180));            
         }

         if(lGroup != nullptr)
         {
            // add to group
            lGroup->addSubProperty(&(*mPropViewElem[mPropViewElem.size()-1]));
            ui.treeWidget->setBackgroundColor(ui.treeWidget->items(&(*mPropViewElem[mPropViewElem.size()-1]))[0],
                  QColor::fromRgb(255,255,255));
         }
      } 
      
   }

   //####################################
   // create file path property items
   //####################################

   if(mTplFileProps.size() > 0)
   {
      lLastGroup = "";

      // create new property items
      for(size_t i=0; i < mTplFileProps.size(); i++)
      {
         int lPropertyType;

         // select property type
         if(mTplFileProps[i]->getType() == ClassTemplateProperty::PROP_TYPE_BOOL)
            lPropertyType = QVariant::Bool;
         else if(mTplFileProps[i]->getType() == ClassTemplateProperty::PROP_TYPE_STRING)
            lPropertyType = QVariant::String;
         else if(mTplFileProps[i]->getType() == ClassTemplateProperty::PROP_TYPE_STRINGLIST)
            lPropertyType = QtVariantPropertyManager::enumTypeId();
         else
            lPropertyType = QVariant::String;
      
         // add property
         mFileViewElem.push_back(std::shared_ptr<QtVariantProperty>(mpVariantManagerFile->addProperty(lPropertyType,
                                                                                                      mTplFileProps[i]->getName().c_str())));

         // create list values
         if(mTplFileProps[i]->getType() == ClassTemplateProperty::PROP_TYPE_STRINGLIST)
         {
            QStringList lValues;
            std::vector<std::string> lValueList = mTplFileProps[i]->getStringList();

            for(size_t j=0; j<lValueList.size();j++)
            {
               lValues << lValueList[j].c_str();
            }

            mFileViewElem[mFileViewElem.size()-1]->setAttribute("enumNames", lValues);
         }
         else if(mTplFileProps[i]->getType() == ClassTemplateProperty::PROP_TYPE_STRING)
         {
            mFileViewElem[mFileViewElem.size()-1]->setAttribute("regExp",
                                                                QRegExp(mTplFileProps[i]->getRegExpression().c_str()));
         }
            
         // set default values
         mFileViewElem[mFileViewElem.size()-1]->setValue(mTplFileProps[i]->getDefaultValue().c_str());
         mFileViewElem[mFileViewElem.size()-1]->setToolTip(mTplFileProps[i]->getInfoText().c_str());

         // create group
         if(mTplFileProps[i]->getGroup() == "")
         {
            // no group => add property to view
            ui.treeWidget->addProperty(&(*mFileViewElem[mFileViewElem.size()-1]));
            lLastGroup = "";
         }
         else
         {
            if(lLastGroup != mTplFileProps[i]->getGroup())
            {
               // create new group
               lGroup = mpVariantManagerFile->addProperty(QtVariantPropertyManager::groupTypeId(),
                                                          mTplFileProps[i]->getGroup().c_str());
               lLastGroup = mTplFileProps[i]->getGroup();

               // add group to view
               ui.treeWidget->addProperty(lGroup);
               ui.treeWidget->setBackgroundColor(ui.treeWidget->items(lGroup)[0],QColor::fromRgb(180,255,180));            
            }

            // add to group
            lGroup->addSubProperty(&(*mFileViewElem[mFileViewElem.size()-1]));
            ui.treeWidget->setBackgroundColor(ui.treeWidget->items(&(*mFileViewElem[mFileViewElem.size()-1]))[0],
                  QColor::fromRgb(200,255,200));
         } 
      
      }
   }


   //####################################
   // create command items
   //####################################

   if(mTplCmd.size() > 0)
   {
      // create new command group
      QtVariantProperty* lCmdGroup = mpVariantManagerCmd->addProperty(QtVariantPropertyManager::groupTypeId(), "Post Processing Commands");
   
      // add group to view
      ui.treeWidget->addProperty(lCmdGroup);
      ui.treeWidget->setBackgroundColor(ui.treeWidget->items(lCmdGroup)[0],QColor::fromRgb(255,128,128));

      // add elements
      for(size_t i = 0; i < mTplCmd.size(); i++)
      {
         // create new element
         mCmdViewElem.push_back(std::shared_ptr<QtVariantProperty>(mpVariantManagerCmd->addProperty(QVariant::Bool,
                                                                                                    mTplCmd[i]->getName().c_str())));
         mCmdViewElem[mCmdViewElem.size()-1]->setValue(false);
         mCmdViewElem[mCmdViewElem.size()-1]->setToolTip(mTplCmd[i]->getInfoText().c_str());

         // show element
         lCmdGroup->addSubProperty(&(*mCmdViewElem[mCmdViewElem.size()-1]));
         ui.treeWidget->setBackgroundColor(ui.treeWidget->items(&(*mCmdViewElem[mCmdViewElem.size()-1]))[0],
               QColor::fromRgb(255,200,200));
      }
   }

   // connect changed signal
   //QObject::connect(ui.treeWidget,
   //                 SIGNAL(currentItemChanged(QtBrowserItem*)),
   //                 this,
   //                 SLOT(treeItemChanged(QtBrowserItem*)));
   QObject::connect(mpVariantManager,
                    SIGNAL(valueChanged(QtProperty*, QVariant)),
                    this,
                    SLOT(valueChanged(QtProperty*, QVariant)));
   QObject::connect(mpVariantManagerFile,
                    SIGNAL(valueChanged(QtProperty*, QVariant)),
                    this,
                    SLOT(valueChanged(QtProperty*, QVariant)));
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::treeItemChanged(QtBrowserItem* apItem)
{
   // read changed values from view
   readTreeViewValues();

   // release or block generate button
   setGenerateState();

   // if preview window is visible => show code
   if(mPv->isVisible())
      updatePreview();

   // update paths
   updatFilePaths();
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::valueChanged(QtProperty* apProperty, const QVariant& arVal)
{
   // read changed values from view
   readTreeViewValues();

   // release or block generate button
   setGenerateState();

   // if preview window is visible => show code
   if(mPv->isVisible())
      updatePreview();

   // update paths
   updatFilePaths();
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::readTreeViewValues(void)
{
   // save new property values
   for(size_t i=0; i < mTplProps.size(); i++)
      mTplProps[i]->mValue = mPropViewElem[i]->value().toString().toStdString();

   // save new property values
   for(size_t i=0; i < mTplFileProps.size(); i++)
      mTplFileProps[i]->mValue = mFileViewElem[i]->value().toString().toStdString();

   // save new command values
   for(size_t i=0; i < mTplCmd.size(); i++)
      mTplCmd[i]->mProcess = mCmdViewElem[i]->value().toBool();
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::btGenerateClicked(void)
{
   // check if an output path is selected
   if(ui.lePath->text().toStdString() == "")
   {
      showError("No output path selected!");
      return;
   }

   // read changed values from view
   readTreeViewValues();

   // create path variables
   std::string lHeaderPath;
   std::string lSourcePath;
   std::string lCmakePath;
   std::string lOutputPath;

   // get output path
   if(ui.cbAutoDetect->isChecked())
      lOutputPath = ui.lePath->text().toStdString();
   else
      lOutputPath = mSettings->mOutputPath;

   // parse file paths
   parseFilePaths(lHeaderPath, lSourcePath, lCmakePath);   

   // add main path
   lHeaderPath = lOutputPath + "/" + lHeaderPath;
   lSourcePath  = lOutputPath + "/" + lSourcePath;
   lCmakePath  = lOutputPath + "/" + lCmakePath;

   lHeaderPath = StringUtil::unifyPathDelimiter(lHeaderPath);
   lSourcePath = StringUtil::unifyPathDelimiter(lSourcePath);
   lCmakePath = StringUtil::unifyPathDelimiter(lCmakePath);

   // create class name for files
   std::string lFileName = mTplProps[static_cast<size_t>(mClassNameIndex)]->mValue;
   StringUtil::toLower(lFileName);

   //create filename
   std::string lHeaderFileName = lHeaderPath + "/" + lFileName + "." + mSettings->mHeaderExtension;
   std::string lSourceFileName = lSourcePath + "/" + lFileName + "." + mSettings->mSourceExtension;
   std::string lCmakeFileName = lCmakePath + "/CMakeLists.txt";

   lHeaderFileName = StringUtil::unifyPathDelimiter(lHeaderFileName);
   lSourceFileName = StringUtil::unifyPathDelimiter(lSourceFileName);
   lCmakeFileName = StringUtil::unifyPathDelimiter(lCmakeFileName);


   // generate content for files
   std::string lHeaderContent = "";
   std::string lSourceContent = "";   
   std::string lCmakeContent = "";   
   parseFiles(lHeaderContent, lSourceContent);
   parseCmakeFile(lCmakeContent);


   // generate directories
   std::vector<std::string> lDir = mTplData->getDirectories();
   QDir lFolder;
   if(lDir.size() > 0)
   {
      // get tokens
      std::vector<std::shared_ptr<ClassTemplateProperty> > lParsProps;
      getTokens(lParsProps);

      for(size_t i = 0; i < lDir.size(); i++)
      {
         // parse file path template
         try
         {
            ClassCreator::parseTemplate(lDir[i], lDir[i], lParsProps);
         }
         catch(std::runtime_error e)
         {
            this->showError(e.what());
         }
         lDir[i] = lOutputPath + lDir[i];
         // create path
         lFolder.setPath(lDir[i].c_str());
         if(!lFolder.exists())
            lFolder.mkpath(lDir[i].c_str());
      }
   }
   

   
   // check if include subfolder exists else create it
   if(mTplData->getHasHeader())
   {   
      lFolder.setPath(lHeaderPath.c_str());
      if(!lFolder.exists())
         lFolder.mkpath(lHeaderPath.c_str());
   }

   // check if source subfolder exists else create it
   if(mTplData->getHasSource())
   {
      lFolder.setPath(lSourcePath.c_str());
      if(!lFolder.exists())
         lFolder.mkpath(lSourcePath.c_str());
   }

   // check if CMake subfolder exists else create it
   if(mTplData->getHasCmake())
   {
      lFolder.setPath(lCmakePath.c_str());
      if(!lFolder.exists())
         lFolder.mkpath(lCmakePath.c_str());
   }
   


   // create and open header file
   if(mTplData->getHasHeader())
   { 
      QFile lHeaderFile(lHeaderFileName.c_str());   
      if(lHeaderFile.exists())
      {
         if(!lHeaderFile.remove())
         {
            showError("Header file with the same name in output path couldn't be removed!");
         }
      }
      if( !lHeaderFile.open( QIODevice::WriteOnly ) )
      {
         showError("Couldn't create / open header file!");
      }

      // write content to header file
      QTextStream lTsHeader( &lHeaderFile );
      lTsHeader << lHeaderContent.c_str();
      lHeaderFile.close();
   }



   // create and open source file
   if(mTplData->getHasSource())
   {
      QFile lSourceFile(lSourceFileName.c_str());   
      if(lSourceFile.exists())
      {
         if(!lSourceFile.remove())
         {
            showError("Source file with the same name in output path couldn't be removed!");
         }
      }
      if( !lSourceFile.open( QIODevice::WriteOnly ) )
      {
         showError("Couldn't create / open source file!");
      }

      // write content to source file
      QTextStream lTsSource( &lSourceFile );
      lTsSource << lSourceContent.c_str();
      lSourceFile.close();
   }

   // create and open CMake file
   if(mTplData->getHasCmake())
   {
      QFile lCmakeFile(lCmakeFileName.c_str());   
      if(lCmakeFile.exists())
      {
         if(!lCmakeFile.remove())
         {
            showError("Source file with the same name in output path couldn't be removed!");
         }
      }
      if( !lCmakeFile.open( QIODevice::WriteOnly ) )
      {
         showError("Couldn't create / open source file!");
      }

      // write content to source file
      QTextStream lTsCmake( &lCmakeFile );
      lTsCmake << lCmakeContent.c_str();
      lCmakeFile.close();
   }

   // run post processing
   runPostProcessing();

   QMessageBox msgBox("ClassCreator",
                      "Files successfully generated!",
                      QMessageBox::Icon::Information,
                      QMessageBox::Button::Ok,
                      QMessageBox::Button::NoButton,
                      QMessageBox::Button::NoButton);
   msgBox.exec();
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::cbAutoDetectClicked(bool aChecked)
{
   ui.lePath->setEnabled(!aChecked);
   ui.btBrowse->setEnabled(!aChecked);

   // check if auto detect
   if(aChecked)
   {
      if(mTplData->getUseSystemPath())
      {
         QByteArray pPath;
         pPath = qgetenv (mTplData->getSystemPath().c_str());

         if(pPath != nullptr)
         {
            ui.cbAutoDetect->setEnabled(true);
            ui.cbAutoDetect->setChecked(true);
            ui.lePath->setEnabled(false);
            ui.btBrowse->setEnabled(false);
            ui.lePath->setText(pPath);
         }
         else
         {
            ui.cbAutoDetect->setChecked(false);
            ui.cbAutoDetect->setEnabled(false);
            ui.lePath->setEnabled(true);
            ui.btBrowse->setEnabled(true);
            ui.lePath->setText(mSettings->mOutputPath.c_str());
         }
      }
      else
      {
         ui.cbAutoDetect->setChecked(false);
         ui.cbAutoDetect->setEnabled(false);
         ui.lePath->setEnabled(true);
         ui.btBrowse->setEnabled(true);
         ui.lePath->setText(mSettings->mOutputPath.c_str());
      }

      // update paths
      updatFilePaths();
   }

   
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::runPostProcessing(void)
{
   // loop through all commands
   for(size_t i = 0; i < mTplCmd.size(); i++)
   {
      // should the command be executed?
      if(mTplCmd[i]->mProcess)
      {
         // execute command
         QStringList largs = static_cast<QString>(mTplCmd[i]->getParams().c_str()).split(" ");
         QProcess* lProc = new QProcess(this);
         lProc->start(mTplCmd[i]->getCommand().c_str(), largs);
      }
   }
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::lePathTextChanged(const QString& arText)
{
   // only save if not auto detect   
   if(!ui.cbAutoDetect->isChecked())
   {   
      // save changed path
      mSettings->mOutputPath = arText.toStdString();

      try
      {
         // write changed settings to User-XML
         ConfigurationManager::setUserSettings(mSettings);
      }
      catch(std::runtime_error e)
      {
         this->showError(e.what());
      }
   }

   updatFilePaths();
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::setGenerateState(void)
{
   // initialize allowed value
   bool lGenAllowed = true;

   // check all string properties for valid values (bool and string list are always valid)
   for(size_t i = 0; i < mTplProps.size(); i++)
   {
      if(mTplProps[i]->getType() == ClassTemplateProperty::PROP_TYPE_STRING)
      {
         if(mTplProps[i]->mValue == "" && mTplProps[i]->getRegExpression() != "")
         {
            lGenAllowed = false;
            break;
         }
      }
   }


   // set button enable state
   ui.btGenerate->setEnabled(lGenAllowed);
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::updatFilePaths(void)
{
   // create path variables
   std::string lHeaderPath;
   std::string lSourcePath;
   std::string lCmakePath;
   std::string lOutputPath;

   // get output path
   if(ui.cbAutoDetect->isChecked())
      lOutputPath = ui.lePath->text().toStdString();
   else
      lOutputPath = mSettings->mOutputPath;
   
   // parse file paths
   parseFilePaths(lHeaderPath, lSourcePath, lCmakePath);   

   // add main path
   lHeaderPath = lOutputPath + "/" + lHeaderPath;
   lSourcePath  = lOutputPath + "/" + lSourcePath;
   lCmakePath  = lOutputPath + "/" + lCmakePath;

   // create class name for files
   std::string lFileName = mTplProps[static_cast<size_t>(mClassNameIndex)]->mValue;
   StringUtil::toLower(lFileName);

   lHeaderPath = lHeaderPath + "/" + lFileName + "." + mSettings->mHeaderExtension;
   lSourcePath = lSourcePath + "/" + lFileName + "." + mSettings->mSourceExtension;
   lCmakePath = lCmakePath + "/CMakeLists.txt";

   lHeaderPath = StringUtil::unifyPathDelimiter(lHeaderPath);
   lSourcePath = StringUtil::unifyPathDelimiter(lSourcePath);
   lCmakePath = StringUtil::unifyPathDelimiter(lCmakePath);

   //create filename
   if(mTplData->getHasHeader())
   {
      ui.leHeaderPath->setEnabled(true);
      ui.lHeaderPath->setEnabled(true);
      ui.leHeaderPath->setText(StringUtil::replaceSubString(lHeaderPath, "/", "\\").c_str());
   }
   else
   {
      ui.leHeaderPath->setText("No Header File!");
      ui.leHeaderPath->setEnabled(false);
      ui.lHeaderPath->setEnabled(false);
   }

   if(mTplData->getHasSource())
   {
      ui.leSourcePath->setEnabled(true);
      ui.lSourcePath->setEnabled(true);
      ui.leSourcePath->setText(StringUtil::replaceSubString(lSourcePath, "/", "\\").c_str());
   }
   else
   {
      ui.leSourcePath->setText("No Source File!");
      ui.leSourcePath->setEnabled(false);
      ui.lSourcePath->setEnabled(false);
   }

   if(mTplData->getHasCmake())
   {
      ui.leCmakePath->setEnabled(true);
      ui.lCmakePath->setEnabled(true);
      ui.leCmakePath->setText(StringUtil::replaceSubString(lCmakePath, "/", "\\").c_str());
   }
   else
   {
      ui.leCmakePath->setText("No CMake File!");
      ui.leCmakePath->setEnabled(false);
      ui.lCmakePath->setEnabled(false);
   }
}


// -----------------------------------------------------------------------
// ----------


void MainWindow::showError(const std::string& arErrorText)
{
   // show QT error (GUI)
   QMessageBox msgBox("ClassCreator Error",
                      arErrorText.c_str(),
                      QMessageBox::Icon::Warning,
                      QMessageBox::Button::Ok,
                      QMessageBox::Button::NoButton,
                      QMessageBox::Button::NoButton);
   msgBox.exec();
}
