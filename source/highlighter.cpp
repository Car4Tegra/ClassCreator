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
 * @file highlighter.cpp
 * @date 2017-04-18
 *
 * @brief This file contains the definition of class Highlighter.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


// Qt includes
#include <QtGui>
#include <QColor>

// ClassCreator includes
#include "highlighter.hpp"


Highlighter::Highlighter(const languageType& arLangType, QTextDocument *apParent)
     : QSyntaxHighlighter(apParent), mLangType(arLangType)
{
   if(mLangType == LANG_TYPE_CPP)
      initCppRules();
   else
      initCmakeRules();
}


// -----------------------------------------------------------------------
// ----------


Highlighter::~Highlighter()
{
   mHighlightingRules.clear();
}


// -----------------------------------------------------------------------
// ----------


void Highlighter::initCppRules(void)
{
   HighlightingRule lRule;
   QTextCharFormat lFormat;

   // set rule for c++ keywords
   lFormat.setForeground(Qt::blue);
   lFormat.setFontWeight(QFont::Normal);
   QStringList keywordPatterns;
   keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                   << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                   << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                   << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                   << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                   << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                   << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                   << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                   << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                   << "\\#include\\b" << "\\#ifndef\\b" << "\\#define\\b"
                   << "\\#endif\\b" << "\\busing\\b" << "\\bQ_OBJECT\\b"
                   << "\\bbool\\b" << "\\bvoid\\b" << "\\bvolatile\\b"
                   << "\\#pragma\\b" << "\\bonce\\b";
   foreach (const QString &pattern, keywordPatterns) {
       lRule.pattern = QRegExp(pattern);
       lRule.format = lFormat;
       mHighlightingRules.append(lRule);
   }
   
   // create rules for comments
   lFormat.setForeground(Qt::darkGreen);
   lRule.pattern = QRegExp("//[^\n]*");
   lRule.format = lFormat;
   mHighlightingRules.append(lRule);

   // create rule for quotations
   lFormat.setForeground(Qt::darkRed);
   lRule.pattern = QRegExp("\".*\"");
   lRule.format = lFormat;
   mHighlightingRules.append(lRule);

   // create rule for brackets
   lFormat.setForeground(Qt::darkRed);
   lRule.pattern = QRegExp(" <.*>");
   lRule.format = lFormat;
   mHighlightingRules.append(lRule);

   // create rule for class names
   /*lFormat.setFontWeight(QFont::Normal);
   lFormat.setForeground(Qt::black);
   lRule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
   lRule.format = classFormat;
   mHighlightingRules.append(lRule);*/

   // create ruke for function names
   /*lFormat.setForeground(Qt::black);
   lRule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
   lRule.format = lFormat;
   mHighlightingRules.append(lRule);*/

   // set format for multiline comments (processed separately)
   mCommentStartExpression = QRegExp("/\\*");
   mCommentEndExpression = QRegExp("\\*/");
   mMultiLineCommentFormat.setForeground(Qt::darkGreen);
}


// -----------------------------------------------------------------------
// ----------


void Highlighter::initCmakeRules(void)
{
   HighlightingRule lRule;
   QTextCharFormat lFormat;
   QTextCharFormat lFormat2;

   // set rule for blue keywords
   lFormat.setForeground(Qt::blue);
   lFormat.setFontWeight(QFont::Bold);
   QStringList keywordPatterns;
   keywordPatterns << "add_custom_command" << "add_custom_target" << "add_definitions" 
      << "add_dependencies" << "add_executable" << "add_library" << "add_subdirectory" 
      << "add_test" << "aux_source_directory" << "uild_command" << "uild_name" 
      << "cmake_minimum_required" << "configure_file" << "create_test_sourcelist" 
      << "else" << "elseif" << "enable_language" << "enable_testing" 
      << "endforeach" << "endif" << "endmacro" << "endwhile" << "exec_program"
      << "execute_process" << "export_library_dependencies" << "file" << "find_file" 
      << "find_library" << "find_package" << "find_path" << "find_program" 
      << "fltk_wrap_ui" << "foreach" << "get_cmake_property" << "get_directory_property" 
      << "get_filename_component" << "get_source_file_property" << "get_target_property" 
      << "get_test_property" << "if" << "include" << "include_directories" 
      << "include_external_msproject" << "include_regular_expression" << "install" 
      << "install_files" << "install_programs" << "install_targets" << "link_directories" 
      << "link_libraries" << "list" << "load_cache" << "load_command" << "macro" 
      << "make_directory" << "mark_as_advanced" << "math" << "message" << "option" 
      << "output_required_files" << "project" << "qt_wrap_cpp" << "qt_wrap_ui" 
      << "remove" << "remove_definitions" << "separate_arguments" << "set" 
      << "set_directory_properties" << "set_source_files_properties" << "set_target_properties" 
      << "set_tests_properties" << "site_name" << "source_group" << "string" 
      << "subdir_depends" << "subdirs" << "target_link_libraries" << "try_compile" 
      << "try_run" << "use_mangled_mesa" << "utility_source" << "variable_requires" 
      << "vtk_make_instantiator" << "vtk_wrap_java" << "vtk_wrap_python" << "vtk_wrap_tcl" 
      << "while" << "write_file" << "libraryModule";
   foreach (const QString &pattern, keywordPatterns) {
       lRule.pattern = QRegExp(pattern);
       lRule.format = lFormat;
       mHighlightingRules.append(lRule);
   }

   // set rule for dark blue keywords
   lFormat2.setForeground(Qt::darkBlue);
   lFormat2.setFontWeight(QFont::Normal);
   QStringList keywordPatterns2;
   keywordPatterns2 << "\\ABSOLUTE\\b" << "\\ABSTRACT\\b" << "\\ADDITIONAL_MAKE_CLEAN_FILES\\b" 
                    << "\\ALL\\b" << "\\AND\\b" << "\\APPEND\\b" << "\\ARGS\\b" << "\\ASCII\\b"
                    << "\\BEFORE\\b" << "\\CACHE\\b" << "\\CACHE_VARIABLES\\b" << "\\CLEAR\\b" 
                    << "\\COMMAND\\b" << "\\COMMANDS\\b" << "\\COMMAND_NAME\\b" << "\\COMMENT\\b" 
                    << "\\COMPARE\\b" << "\\COMPILE_FLAGS\\b" << "\\COPYONLY\\b" << "\\DEFINED\\b" 
                    << "\\DEFINE_SYMBOL\\b" << "\\DEPENDS\\b" << "\\DOC\\b" << "\\EQUAL\\b" 
                    << "\\ESCAPE_QUOTES\\b" << "\\EXCLUDE\\b" << "\\EXCLUDE_FROM_ALL\\b" 
                    << "\\EXISTS\\b" << "\\EXPORT_MACRO\\b" << "\\EXT\\b" << "\\EXTRA_INCLUDE\\b" 
                    << "\\FATAL_ERROR\\b" << "\\FILE\\b" << "\\FILES\\b" << "\\FORCE\\b" 
                    << "\\FUNCTION\\b" << "\\GENERATED\\b" << "\\GLOB\\b" << "\\GLOB_RECURSE\\b" 
                    << "\\GREATER\\b" << "\\GROUP_SIZE\\b" << "\\HEADER_FILE_ONLY\\b" << "\\HEADER_LOCATION\\b" 
                    << "\\IMMEDIATE\\b" << "\\INCLUDES\\b" << "\\INCLUDE_DIRECTORIES\\b" << "\\INCLUDE_INTERNALS\\b" 
                    << "\\INCLUDE_REGULAR_EXPRESSION\\b" << "\\LESS\\b" << "\\LINK_DIRECTORIES\\b" 
                    << "\\LINK_FLAGS\\b" << "\\LOCATION\\b" << "\\MACOSX_BUNDLE\\b" << "\\MACROS\\b" 
                    << "\\MAIN_DEPENDENCY\\b" << "\\MAKE_DIRECTORY\\b" << "\\MATCH\\b" << "\\MATCHALL\\b" 
                    << "\\MATCHES\\b" << "\\MODULE\\b" << "\\bNAME\\b" << "\\NAME_WE\\b" << "\\NOT\\b" 
                    << "\\NOTEQUAL\\b" << "\\NO_SYSTEM_PATH\\b" << "\\OBJECT_DEPENDS\\b" << "\\OPTIONAL\\b" 
                    << "\\OR\\b" << "\\OUTPUT\\b" << "\\OUTPUT_VARIABLE\\b" << "\\PATH\\b" << "\\PATHS\\b" 
                    << "\\POST_BUILD\\b" << "\\POST_INSTALL_SCRIPT\\b" << "\\PREFIX\\b" << "\\PREORDER\\b" 
                    << "\\PRE_BUILD\\b" << "\\PRE_INSTALL_SCRIPT\\b" << "\\PRE_LINK\\b" << "\\PROGRAM\\b" 
                    << "\\PROGRAM_ARGS\\b" << "\\PROPERTIES\\b" << "\\QUIET\\b" << "\\RANGE\\b" << "\\READ\\b" 
                    << "\\REGEX\\b" << "\\REGULAR_EXPRESSION\\b" << "\\REPLACE\\b" << "\\REQUIRED\\b" 
                    << "\\RETURN_VALUE\\b" << "\\RUNTIME_DIRECTORY\\b" << "\\SEND_ERROR\\b" << "\\SHARED\\b" 
                    << "\\SOURCES\\b" << "\\STATIC\\b" << "\\STATUS\\b" << "\\STREQUAL\\b" << "\\STRGREATER\\b" 
                    << "\\STRLESS\\b" << "\\SUFFIX\\b" << "\\TARGET\\b" << "\\TOLOWER\\b" << "\\TOUPPER\\b" 
                    << "\\VAR\\b" << "\\VARIABLES\\b" << "\\VERSION\\b" << "\\WIN32\\b" << "\\WRAP_EXCLUDE\\b" 
                    << "\\WRITE\\b" << "\\APPLE\\b" << "\\MINGW\\b" << "\\MSYS\\b" << "\\CYGWIN\\b" 
                    << "\\BORLAND\\b" << "\\WATCOM\\b" << "\\MSVC\\b" << "\\MSVC_IDE\\b" << "\\MSVC60\\b" 
                    << "\\MSVC70\\b" << "\\MSVC71\\b" << "\\MSVC80\\b" << "\\CMAKE_COMPILER_2005\\b" << "\\OFF\\b" 
                    << "\\ON\\b";
   foreach (const QString &pattern, keywordPatterns2) {
       lRule.pattern = QRegExp(pattern);
       lRule.format = lFormat2;
       mHighlightingRules.append(lRule);
   }

   lFormat.setFontWeight(QFont::Normal);

   // create rule for quotations
   lFormat.setForeground(QColor::fromRgb(255, 127, 39));
   lRule.pattern = QRegExp("[$][{][a-zA-Z0-9_]*[}]");
   lRule.format = lFormat;
   mHighlightingRules.append(lRule);

   // create rule for quotations
   lFormat.setForeground(Qt::gray);
   //lRule.pattern = QRegExp("\".*\"");
   lRule.pattern = QRegExp("\"[a-zA-Z0-9_${}]*\"");
   lRule.format = lFormat;
   mHighlightingRules.append(lRule);

   // create rules for comments
   lFormat.setForeground(Qt::darkGreen);
   lRule.pattern = QRegExp("#[^\n]*");
   lRule.format = lFormat;
   mHighlightingRules.append(lRule);
}


// -----------------------------------------------------------------------
// ----------


void Highlighter::highlightBlock(const QString &text)
{
   // apply all rules
   foreach (const HighlightingRule &rule, mHighlightingRules)
   {
      QRegExp expression(rule.pattern);
      int index = expression.indexIn(text);
      while (index >= 0)
      {
         int length = expression.matchedLength();
         setFormat(index, length, rule.format);
         index = expression.indexIn(text, index + length);
      }
   }

   setCurrentBlockState(0);
   int startIndex = 0;

   if(mLangType == LANG_TYPE_CPP)
   {
      // format multiline comments
      if (previousBlockState() != 1)
         startIndex = mCommentStartExpression.indexIn(text);

      while (startIndex >= 0)
      {
         int endIndex = mCommentEndExpression.indexIn(text, startIndex);
         int commentLength;

         if (endIndex == -1)
         {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
         } else {
            commentLength = endIndex - startIndex + mCommentEndExpression.matchedLength();
         }

         setFormat(startIndex, commentLength, mMultiLineCommentFormat);
         startIndex = mCommentStartExpression.indexIn(text, startIndex + commentLength);
      }
   }
}
