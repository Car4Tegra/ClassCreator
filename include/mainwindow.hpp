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
 * @file mainwindow.hpp
 * @date 2017-04-18
 *
 * @brief This file contains the declaration of class MainWindow.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


#ifndef __MAINWINDOW_HPP__
#define __MAINWINDOW_HPP__


// std includes
#include <memory>
#include <exception>
#include <stdexcept>

// Qt includes
#include <QMainWindow>
#include <QtTreePropertyBrowser>
#include <QtVariantPropertyManager>
#include <QtVariantProperty>
#include <QtVariantEditorFactory>
#include "ui_MainWindowView.h"

// ClassCreator includes
#include "preview.hpp"
#include "usersettingsdialog.hpp"
#include "configurationmanager.hpp"
#include "usersettingsdata.hpp"
#include "classtemplatecommand.hpp"


/** 
 * @class MainWindow mainwindow.hpp "mainwindow.hpp"
 * @brief Shows the main window of the ClassCreator
 */
class MainWindow : public QMainWindow
{
   // QT compiler macro
   Q_OBJECT


   // -----------------------------------------------------------------------
   // public methods
public:
   /**
    * Creates a new class creator main window view
    * @param aParent          Pointer to parent widget.
    * @param aFlags           Window flags.
    */
   MainWindow(QWidget* apParent = 0, Qt::WindowFlags aFlags = 0);


   //! Destroys the dialog.
   ~MainWindow();


   // -----------------------------------------------------------------------
   // protected methods
protected:
   //! Overwritten QT close event function
   void closeEvent( QCloseEvent *evt );


   // -----------------------------------------------------------------------
   // private methods
private:
   /**
    * Get parsed header / source file content
    * @param[out] arHppContent         Parsed content of Hpp header file
    * @param[out] arCppContent         Parsed content of Cpp source file
    *
    * @return  parsing of files completed successfully
    */
   bool parseFiles(std::string& arHppContent, std::string& arCppContent);


   /**
    * Get parsed CMake file content
    * @param[out] arCmakeContent       Parsed content of CMake file
    *
    * @return  parsing of files completed successfully
    */
   bool parseCmakeFile(std::string& arCmakeContent);


   /**
    * Get parsed header / source file path templates
    * @param[out] arHppPath            Parsed Hpp header file path
    * @param[out] arCppPath            Parsed Cpp source file path
    * @param[out] arCmakePath          Parsed CMake file path
    *
    * @return  parsing of file paths completed successfully
    */
   bool parseFilePaths(std::string& arHppPath,
                       std::string& arCppPath,
                       std::string& arCmakePath);


   /**
    * Create tokens from properties
    * @param[out] arParsProps          Tokens
    */
   void getTokens(std::vector<std::shared_ptr<ClassTemplateProperty> >& arParsProps);


   //! Update code in preview dialog
   void updatePreview(void);


   //! Update property view widget
   void updatePropertyView(void);


   //! release or block generate button
   void setGenerateState(void);


   /**
    * Shows an error dialog
    * @param[in] arErrorText     Error text shown in dialog
    */
   void showError(const std::string& arErrorText);


   //! run selected post processing commands
   void runPostProcessing(void);


   //! read property and command values from tree view
   void readTreeViewValues(void);


   //! show current file paths
   void updatFilePaths(void);


   // -----------------------------------------------------------------------
   // private slots
private slots:

   //! Preview button clicked
   void btPreviewClicked(void);


   //! User settings button clicked
   void btSettingsClicked(void);


   //! User settings button clicked
   void btSaveClicked(void);


   /**
    * User settings dialog closing
    * @param[in] arSettings      Changed user settings
    */
   void mSetClosing(const std::shared_ptr<UserSettingsData>& arSettings);


   /**
    * User settings dialog closing
    * @param[in] aIndex          Selected template index
    */
   void cbIndexChanged(int aIndex);


   /**
    * Output path browse button clicked
    */
   void btBrowseClicked(void);


   /**
    * Generate button clicked
    */
   void btGenerateClicked(void);


   /**
    * Auto detect checkbox clicked
    * @param[in] aChecked        Checkbox is checked
    */
   void cbAutoDetectClicked(bool aChecked);


   /**
    * Output path line edit text changed
    * @param[in] arText          New line edit text
    */
   void lePathTextChanged(const QString& arText);


   /**
    * Property browser tree item has changed
    * @param[in] apItem          Changed tree item
    */
   void treeItemChanged(QtBrowserItem* apItem);


   /**
    * property view element changed
    */
   void valueChanged(QtProperty* apProperty, const QVariant& arVal);


   // -----------------------------------------------------------------------
   // private members
private:
   Ui::MainWindowView ui;                                               ///< User interface builded by Qt Designer.

   Preview* mPv;                                                        ///< Preview dialog instance
   UserSettingsDialog* mSet;                                            ///< User settings dialog instance

   std::vector<std::string> mTemplateFiles;                             ///< List of found template files
   std::shared_ptr<UserSettingsData> mSettings;                         ///< Current user settings

   std::shared_ptr<ClassTemplateData> mTplData;                         ///< Global template data of current selected template
   std::vector<std::shared_ptr<ClassTemplateProperty> > mTplProps;      ///< Property data of current selected template
   std::vector<std::shared_ptr<ClassTemplateProperty> > mTplFileProps;  ///< File path property data of current selected template
   std::vector<std::shared_ptr<ClassTemplateCommand> > mTplCmd;         ///< Post processing commands of the selected template

   std::vector<std::shared_ptr<QtVariantProperty> > mPropViewElem;      ///< Properties in property browser tree view
   QtVariantPropertyManager* mpVariantManager;                          ///< VariantManager for property elements
   QtVariantEditorFactory* mpVariantFactory;                            ///< VariantFactory for mpVariantManager

   std::vector<std::shared_ptr<QtVariantProperty> > mFileViewElem;      ///< Properties in property browser tree view
   QtVariantPropertyManager* mpVariantManagerFile;                      ///< VariantManager for property elements
   QtVariantEditorFactory* mpVariantFactoryFile;                        ///< VariantFactory for mpVariantManager

   std::vector<std::shared_ptr<QtVariantProperty> > mCmdViewElem;       ///< Command in property browser tree view
   QtVariantPropertyManager* mpVariantManagerCmd;                       ///< VariantManager for command elements
   QtVariantEditorFactory* mpVariantFactoryCmd;                         ///< VariantFactory for mpVariantManagerCmd

   int mClassNameIndex;                                                 ///< Index of the class name property
   
};

#endif //__MAINWINDOW_HPP__
