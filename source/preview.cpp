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
 * @file preview.cpp
 * @date 2017-04-18
 *
 * @brief This file contains the definition of class Preview.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


// Qt includes
#include <QDialog>

// ClassCreator includes
#include "preview.hpp"


Preview::Preview(QWidget* apParent, Qt::WindowFlags aFlags)
   : QDialog(apParent, aFlags | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint)
{
   ui.setupUi(this);   

   // create highlighter for both file views
   mpHighlighterHpp = new Highlighter(Highlighter::LANG_TYPE_CPP, ui.textEditHpp->document());
   mpHighlighterCpp = new Highlighter(Highlighter::LANG_TYPE_CPP, ui.textEditCpp->document());
   mpHighlighterCmake = new Highlighter(Highlighter::LANG_TYPE_CMAKE, ui.textEditCMake->document());
}


// -----------------------------------------------------------------------
// ----------


Preview::~Preview()
{
   delete mpHighlighterHpp;
   delete mpHighlighterCpp;
   delete mpHighlighterCmake;
}


// -----------------------------------------------------------------------
// ----------


void Preview::updateHpp(const std::string& arContent)
{
   // set new text to view (highlighter is apply automatically)
   ui.textEditHpp->setText(arContent.c_str());
}


// -----------------------------------------------------------------------
// ----------


void Preview::updateCpp(const std::string& arContent)
{
   // set new text to view (highlighter is apply automatically)
   ui.textEditCpp->setText(arContent.c_str());
}

// -----------------------------------------------------------------------
// ----------

void Preview::updateCmake(const std::string& arContent)
{
   ui.textEditCMake->setText(arContent.c_str());
}

// -----------------------------------------------------------------------
// ----------

void Preview::setFiles(bool aHasHeader, bool aHasSource, bool aHasCmake)
{
   ui.tabMainWidget->setTabEnabled(0, aHasHeader);
   ui.tabMainWidget->setTabEnabled(1, aHasSource);
   ui.tabMainWidget->setTabEnabled(2, aHasCmake);
}


// -----------------------------------------------------------------------
// ----------


void Preview::updateFileNames(const std::string& arClassName,
                              const std::string& arHeaderExt,
                              const std::string& arSourceExt)
{
   ui.tabMainWidget->setTabText(0, std::string(arClassName + "." + arHeaderExt).c_str());
   ui.tabMainWidget->setTabText(1, std::string(arClassName + "." + arSourceExt).c_str());
}
