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
 * @file usersettingsdialog.cpp
 * @date 2017-04-18
 *
 * @brief This file contains the definition of class UserSettingsDialog.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


// Qt includes
#include <QWidget>

// ClassCreator includes
#include "usersettingsdialog.hpp"


UserSettingsDialog::UserSettingsDialog(QWidget* apParent, Qt::WindowFlags aFlags)
   : QWidget(apParent, aFlags)
{
   ui.setupUi(this);

   // connect button signal
   QObject::connect(ui.settingsSave, SIGNAL(clicked()), this, SLOT(settingsSaveCLicked()));

   // create regular expression
   mpLatinSmallValidator = new QRegExpValidator(QRegExp("[a-z]*"),this);
	mpNumberValidator = new QRegExpValidator(QRegExp("[0-9]*"),this);
   mpUserSettingsExtensionValidator = new QRegExpValidator(QRegExp("[a-z]{1,3}"),this);

   // set regular expressions to GUI elements
   ui.settingsSourceExEdit->setValidator(mpUserSettingsExtensionValidator);
   ui.settingsHeaderExEdit->setValidator(mpUserSettingsExtensionValidator);
   ui.settingsIndentEdit->setValidator(mpNumberValidator);

}


// -----------------------------------------------------------------------
// ----------


void UserSettingsDialog::updateSettingsView(const std::shared_ptr<UserSettingsData>& arSettings)
{
   // set current values
   ui.settingsAuthorEdit->setText(arSettings->mAuthor.c_str());
   ui.settingsDateEdit->setText(arSettings->mDateFormat.c_str());
   ui.settingsSourceExEdit->setText(arSettings->mSourceExtension.c_str());
   ui.settingsHeaderExEdit->setText(arSettings->mHeaderExtension.c_str());
   ui.settingsIndentEdit->setText(arSettings->mIndentSpace.c_str());

}


// -----------------------------------------------------------------------
// ----------


void UserSettingsDialog::settingsSaveCLicked(void)
{
   std::shared_ptr<UserSettingsData> lSettings = std::shared_ptr<UserSettingsData>(new UserSettingsData());

   // save new values
   lSettings->mAuthor = ui.settingsAuthorEdit->text().toStdString();
   lSettings->mDateFormat = ui.settingsDateEdit->text().toStdString();
   lSettings->mHeaderExtension = ui.settingsHeaderExEdit->text().toStdString();
   lSettings->mSourceExtension = ui.settingsSourceExEdit->text().toStdString();
   lSettings->mIndentSpace = ui.settingsIndentEdit->text().toStdString();
   
   // emit closing signal
   emit dialogClosing(lSettings);

   // close dialog
   close();
}
