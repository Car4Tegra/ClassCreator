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
 * @file configurationmanager.cpp
 * @date 2017-04-18
 *
 * @brief This file contains the definition of class ConfigurationManager.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


// std includes
#include <exception>
#include <stdexcept>

// Qt includes
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDomDocument>
#include <QTextStream>
#include <QStandardPaths>
#include <QCoreApplication>
#include <qglobal.h>

// ClassCreator includes
#include "configurationmanager.hpp"


void ConfigurationManager::getTemplateList(std::vector<std::string>& arTemplateList)
{
   std::string lTemplatePath = getTemplateDir();

   QDir lFolder(lTemplatePath.c_str());

   // check if folder exists
   if(!lFolder.exists())
   {
      lFolder.mkpath(lTemplatePath.c_str());
      throw std::runtime_error("Template directory doesn't exist!\nCreated an empty one at: " + lTemplatePath);
   }

   // get file list
   QFileInfoList files = lFolder.entryInfoList(QDir::Files, QDir::Name);

   if(files.size() == 0)
      throw std::runtime_error("No templates found in directory:\n" + lTemplatePath);

   for(int i = 0; i < files.size(); i++)
   {
      if(files[i].suffix() == "xml")
      {
         arTemplateList.push_back(files[i].absoluteFilePath().toStdString());
      }
   }

   if(arTemplateList.size() == 0)
      throw std::runtime_error("No templates found in directory:\n" + lTemplatePath);
}


// -----------------------------------------------------------------------
// ----------


void ConfigurationManager::getUserSettings(std::shared_ptr<UserSettingsData>& arSettings)
{
   // get file path / name
   std::string lFilePath = getConfigDir();
   std::string lFileName = USER_SETTINGS_FILE;

   // variables for read access
   QFile lFile(QString((lFilePath + "//" + lFileName).c_str()));

   // if file exists
   if(!lFile.exists())
   {
      // if not exists => create file with default values
      arSettings = std::shared_ptr<UserSettingsData>(new UserSettingsData());
      setUserSettings(arSettings);
      return;
   }

   // open settings file
   if(!lFile.open(QIODevice::ReadOnly))
   {
      throw std::runtime_error("User settings file couldn't be loaded.\nPath: " + lFilePath);
   }

   QDomDocument lQDomDoc;
   QString errMsg;      // error message
   int lErrLine = 0;     // line of error
   int lErrCol  = 0;     // column of error

   // read settings file
   if(!lQDomDoc.setContent(&lFile, false, &errMsg, &lErrLine, &lErrCol))
   {
      throw std::runtime_error("Error while reading user settings file:\nmsg=" + errMsg.toStdString() +
                               "\n(line=" + std::to_string(lErrLine) +
                               " / column=" + std::to_string(lErrCol) + ")");
   }

   // get root element
   QDomElement lDocElem = lQDomDoc.documentElement();

   // get list of all parameter parent nodes
   QDomNodeList lPropertyList = lDocElem.elementsByTagName("settings");

   // loop through all found settings nodes
   for(int i = 0;  i < lPropertyList.length(); i++)
   {
      // is valid element?
      if(lPropertyList.at(i).isElement())
      {
         QDomElement lParamElement = lPropertyList.at(i).toElement();

         // get values for property
         std::string lSetName = lParamElement.attributeNode("name").value().toStdString();
         std::string lSetValue = lParamElement.attributeNode("value").value().toStdString();

         // add element
         if(lSetName == "author")
            arSettings->mAuthor = lSetValue;
         else if(lSetName == "dateformat")
            arSettings->mDateFormat = lSetValue;
         else if(lSetName == "headerEx")
            arSettings->mHeaderExtension = lSetValue;
         else if(lSetName == "sourceEx")
            arSettings->mSourceExtension = lSetValue;
         else if(lSetName == "indent")
            arSettings->mIndentSpace = lSetValue;
         else if(lSetName == "outpath")
            arSettings->mOutputPath = lSetValue;
         else
            throw std::runtime_error("Error while reading user settings file:\nInvalid Attribute: \"" +
                                     lSetName + "\"");
      }
   }
}


// -----------------------------------------------------------------------
// ----------


void ConfigurationManager::setUserSettings(const std::shared_ptr<UserSettingsData>& arSettings)
{
   // create document
   QDomDocument lQDomDoc;

   // create root element
   QDomElement lQDomRoot = lQDomDoc.createElement("usersettings");
   lQDomDoc.appendChild(lQDomRoot);

   QDomElement lQDomElem;

   // add element author
   lQDomElem = lQDomDoc.createElement("settings");
   lQDomElem.setAttribute("name", "author");
   lQDomElem.setAttribute("value", arSettings->mAuthor.c_str());
   lQDomRoot.appendChild(lQDomElem);

   // add element dateformat
   lQDomElem = lQDomDoc.createElement("settings");
   lQDomElem.setAttribute("name", "dateformat");
   lQDomElem.setAttribute("value", arSettings->mDateFormat.c_str());
   lQDomRoot.appendChild(lQDomElem);

   // add element headerEx
   lQDomElem = lQDomDoc.createElement("settings");
   lQDomElem.setAttribute("name", "headerEx");
   lQDomElem.setAttribute("value", arSettings->mHeaderExtension.c_str());
   lQDomRoot.appendChild(lQDomElem);

   // add element sourceEx
   lQDomElem = lQDomDoc.createElement("settings");
   lQDomElem.setAttribute("name", "sourceEx");
   lQDomElem.setAttribute("value", arSettings->mSourceExtension.c_str());
   lQDomRoot.appendChild(lQDomElem);

   // add element indent
   lQDomElem = lQDomDoc.createElement("settings");
   lQDomElem.setAttribute("name", "indent");
   lQDomElem.setAttribute("value", arSettings->mIndentSpace.c_str());
   lQDomRoot.appendChild(lQDomElem);

   // add element outpath
   lQDomElem = lQDomDoc.createElement("settings");
   lQDomElem.setAttribute("name", "outpath");
   lQDomElem.setAttribute("value", arSettings->mOutputPath.c_str());
   lQDomRoot.appendChild(lQDomElem);


   // get file path / name
   std::string lFilePath = getConfigDir();
   std::string lFileName = USER_SETTINGS_FILE;

   // check if folder exists
   QDir lFolder(lFilePath.c_str());
   if(!lFolder.exists())
      lFolder.mkpath(lFilePath.c_str());

   // create file
   QFile lFile((lFilePath + "/" + lFileName).c_str());
   if( !lFile.open( QIODevice::WriteOnly ) )
      throw std::runtime_error("Could not create user settings file:\n" +
                               lFilePath + "/" + lFileName);

   // write data to file
   QTextStream lTs( &lFile );
   lTs << lQDomDoc.toString();

   // close file
   lFile.close();
}


// -----------------------------------------------------------------------
// ----------


std::string ConfigurationManager::getConfigDir()
{
   return QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation).toStdString();
}


// -----------------------------------------------------------------------
// ----------


std::string ConfigurationManager::getTemplateDir()
{
   return TEMPLATE_PATH;
}
