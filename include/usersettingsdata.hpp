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
 * @file usersettingsdata.hpp
 * @date 2017-04-18
 *
 * @brief This file contains the declaration of class ClassTemplateParameter.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


#ifndef __USERSETTINGSDATA_HPP__
#define __USERSETTINGSDATA_HPP__


// std includes
#include <string>


// define default values
#define AUTHOR       "John Doe"
#define DATEFORMAT   "yyyy-MM-dd" 
#define HEADEREX     "hpp"
#define SOURCEEX     "cpp"
#define IDENTSPACE   "3"
#define OUTPATH      ""

#define TOKEN_START   "$"
#define TOKEN_END     "$"

#define BLOCK_TOKEN_POS_START_START    "$@"
#define BLOCK_TOKEN_POS_START_END      "$"
#define BLOCK_TOKEN_POS_END_START      "$"
#define BLOCK_TOKEN_POS_END_END        "@$"

#define BLOCK_TOKEN_NEG_START_START    "$@!"
#define BLOCK_TOKEN_NEG_START_END      "$"
#define BLOCK_TOKEN_NEG_END_START      "$!"
#define BLOCK_TOKEN_NEG_END_END        "@$"


  
/** 
 * @class UserSettingsData usersettingsdata.hpp "usersettingsdata.hpp"
 * @brief Represents an user settings data object
 */
class UserSettingsData 
{
   // -----------------------------------------------------------------------
   // public methods
public:
   /**
    * @brief Default Constructor (set members to default values);
    */
   UserSettingsData()
      : mAuthor(AUTHOR),
        mDateFormat(DATEFORMAT),
        mHeaderExtension(HEADEREX),
        mSourceExtension(SOURCEEX),
        mIndentSpace(IDENTSPACE),
        mOutputPath(OUTPATH),
        mTokenStart(TOKEN_START),
        mTokenEnd(TOKEN_END),
        mBlockTockenPosStartStart(BLOCK_TOKEN_POS_START_START),
        mBlockTockenPosStartEnd(BLOCK_TOKEN_POS_START_END),
        mBlockTockenPosEndStart(BLOCK_TOKEN_POS_END_START),
        mBlockTockenPosEndEnd(BLOCK_TOKEN_POS_END_END),
        mBlockTockenNegStartStart(BLOCK_TOKEN_NEG_START_START),
        mBlockTockenNegStartEnd(BLOCK_TOKEN_NEG_START_END),
        mBlockTockenNegEndStart(BLOCK_TOKEN_NEG_END_START),
        mBlockTockenNegEndEnd(BLOCK_TOKEN_NEG_END_END)
      { }
      
   /**
    * @brief Destructor
    */
   ~UserSettingsData() { }


   // -----------------------------------------------------------------------
   // public members
public:

   std::string mAuthor;                   ///< Author of class
   std::string mDateFormat;               ///< Format for date elements in source files
   std::string mHeaderExtension;          ///< File extension for header files
   std::string mSourceExtension;          ///< File extension for source files
   std::string mIndentSpace;              ///< Number of space characters for an indent
   std::string mOutputPath;               ///< Last used output path
   std::string mTokenStart;               ///< Identifier for Start of a Token
   std::string mTokenEnd;                 ///< Identifier for End of a Token
   std::string mBlockTockenPosStartStart; ///< Begin identifier for a Start-Block-Token
   std::string mBlockTockenPosStartEnd;   ///< End identifier for a Start-Block-Token
   std::string mBlockTockenPosEndStart;   ///< Begin identifier for a End-Block-Token
   std::string mBlockTockenPosEndEnd;     ///< End identifier for a End-Block-Token
   std::string mBlockTockenNegStartStart; ///< Begin identifier for a negated Start-Block-Token
   std::string mBlockTockenNegStartEnd;   ///< End identifier for a negated Start-Block-Token
   std::string mBlockTockenNegEndStart;   ///< Begin identifier for a negated End-Block-Token
   std::string mBlockTockenNegEndEnd;     ///< End identifier for a negated End-Block-Token
 
   // -----------------------------------------------------------------------
   // private methods
private:

   // -----------------------------------------------------------------------
   // declared, but not defined
   
   UserSettingsData(const UserSettingsData&);
   UserSettingsData& operator=(const UserSettingsData&);                

}; // class UserSettingsData

#endif //__USERSETTINGSDATA_HPP__
