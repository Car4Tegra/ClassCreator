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
 * @file highlighter.hpp
 * @date 2017-04-18
 *
 * @brief This file contains the declaration of class Highlighter.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


#ifndef __HIGHLIGHTER_HPP__
#define __HIGHLIGHTER_HPP__


// Qt includes
#include <QSyntaxHighlighter>
#include <QHash>
#include <QTextCharFormat>

// class declarations
class QTextDocument;


/** 
 * @class Highlighter highlighter.hpp "highlighter.hpp"
 * @brief C++ code highlighting for QTextEdit
 */
class Highlighter : public QSyntaxHighlighter
{
   // QT compiler macro
   Q_OBJECT

   // -----------------------------------------------------------------------
   // public types
public:
   //! Language type
   enum languageType {
      LANG_TYPE_CPP,
      LANG_TYPE_CMAKE
   };


   // -----------------------------------------------------------------------
   // public methods
public:
   //! Creates a new Highlighter instance
   //! @param[in] arLangType      Language type for this highlighter instance
   //! @param     apParent        Pointer to parent TextDocument   
   Highlighter(const languageType& arLangType, QTextDocument *apParent = 0);


   //! Destroys the Highlighter
   ~Highlighter();


   // -----------------------------------------------------------------------
   // protected methods
protected:
   //! Method which is called automatically by QSyntaxHighlighter
   //! @param text      Text for highlighting
   void highlightBlock(const QString &text);


   // -----------------------------------------------------------------------
   // private types
private:
   //! Struct for highlighting rule representation
   struct HighlightingRule
   {
      QRegExp pattern;              ///< Pattern expression
      QTextCharFormat format;       ///< Highlighing format
   };
   

   // -----------------------------------------------------------------------
   // private methods
private:
   
   //! Init highlight rules for C++ language 
   void initCppRules(void);


   //! Init highlight rules for CMake language
   void initCmakeRules(void);


   // -----------------------------------------------------------------------
   // private members
private:

   languageType mLangType;                             ///< Language type for this highlighter instance

   QVector<HighlightingRule> mHighlightingRules;       ///< All rules for highlighting
   
   QRegExp mCommentStartExpression;                    ///< Start expression for multiline comments
   QRegExp mCommentEndExpression;                      ///< End expression for multiline comments
   QTextCharFormat mMultiLineCommentFormat;            ///< Format for multiline comments
};


#endif //__HIGHLIGHTER_HPP__
