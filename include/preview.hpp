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
 * @file preview.hpp
 * @date 2017-04-18
 *
 * @brief This file contains the declaration of class Preview.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


#ifndef __PREVIEW_HPP__
#define __PREVIEW_HPP__


// Qt includes
#include <QDialog>

// ClassCreator includes
#include "ui_PreviewView.h"
#include "highlighter.hpp"


/** 
 * @class Preview preview.hpp "preview.hpp"
 * @brief Shows a C++ code preview dialog
 */
class Preview : public QDialog
{
   // QT compiler macro
   Q_OBJECT

   // -----------------------------------------------------------------------
   // public methods
public:
   /**
    * Creates a new class creater preview dialog
    * @param aParent         Pointer to parent widget.
    * @param aFlags          Window flags.
    */
   Preview(QWidget* apParent = 0, Qt::WindowFlags aFlags = 0);


   //! Destroys the dialog.
   ~Preview();


   /**
    * Update view of hpp file
    * @param[in] arContent      Hpp header file content
    */
   void updateHpp(const std::string& arContent);


   /**
    * Update view of cpp file
    * @param[in] arContent      Cpp source file content
    */
   void updateCpp(const std::string& arContent);


   /**
    * Update view of CMake file
    * @param[in] arContent      CMake file content
    */
   void updateCmake(const std::string& arContent);


   /**
    * Select which files should be shown
    * @param[in] aHasHeader     Show header file
    * @param[in] aHasSource     Show source file
    * @param[in] aHasCMake      Show CMake file
    */
   void setFiles(bool aHasHeader, bool aHasSource, bool aHasCmake);


   /**
    * Update tab titles
    * @param[in] arClassName    Name of the class
    * @param[in] arHeaderExt    File extension of the header file
    * @param[in] arSourceExt    File extension of the source file
    */
   void updateFileNames(const std::string& arClassName,
                        const std::string& arHeaderExt,
                        const std::string& arSourceExt);


   // -----------------------------------------------------------------------
   // private members
private:
   Ui::PreviewView ui;                 ///< User interface builded by Qt Designer.

   Highlighter *mpHighlighterHpp;      ///< Highlighter for hpp file
   Highlighter *mpHighlighterCpp;      ///< Highlighter for cpp file
   Highlighter *mpHighlighterCmake;    ///< Highlighter for CMake file
};

#endif //__PREVIEW_HPP__
