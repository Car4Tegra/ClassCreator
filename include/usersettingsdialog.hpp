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
 * @file usersettingsdialog.hpp
 * @date 2017-04-18
 *
 * @brief This file contains the declaration of class UserSettingsDialog.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


#ifndef __USERSETTINGSDIALOG_HPP__
#define __USERSETTINGSDIALOG_HPP__


// std includes
#include <memory>

// Qt includes
#include <QWidget>
#include <QRegExp>

// ClassCreator includes
#include "ui_UserSettingsDialogView.h"
#include "configurationmanager.hpp"
#include "usersettingsdata.hpp"


/** 
 * @class UserSettingsDialog usersettingsdialog.hpp "usersettingsdialog.hpp"
 * @brief Shows an user settings dialog
 */
class UserSettingsDialog : public QWidget
{
   // QT compiler macro
   Q_OBJECT

   // -----------------------------------------------------------------------
   // public methods
public:
   /**
    * Creates a new class creator user settings dialog view
    * @param aParent         Pointer to parent widget.
    * @param aFlags          Window flags.
    */
   UserSettingsDialog(QWidget* apParent = 0, Qt::WindowFlags aFlags = 0);


   //! Destroys the dialog.
   ~UserSettingsDialog() { }


   /**
    * Update the viewed user settings
    * @param[in] arSettings     User settings for visualization
    */
   void updateSettingsView(const std::shared_ptr<UserSettingsData>& arSettings);


   // -----------------------------------------------------------------------
   // public signals
signals:
   /**
    * Signal for closing event of the dialog
    * @param[in] arSettings     Changed user settings
    */
   void dialogClosing(const std::shared_ptr<UserSettingsData>& arSettings);


   // -----------------------------------------------------------------------
   // private slots
private slots:
   //! Slot for save button clicked
   void settingsSaveCLicked(void);


   // -----------------------------------------------------------------------
   // private members
private:
   Ui::UserSettingsDialogView ui;      ///< User interface builded by Qt Designer.   

   // regular expressions
   QRegExpValidator* mpNumberValidator;                  ///< Number validator for GUI elements
   QRegExpValidator* mpLatinSmallValidator;              ///< String 1 validator for GUI elements
   QRegExpValidator* mpUserSettingsExtensionValidator;   ///< String 2 validator for GUI elements
};


#endif //__USERSETTINGSDIALOG_HPP__
