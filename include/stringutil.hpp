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
 * @file stringutil.hpp
 * @date 2017-04-18
 *
 * @brief This file contains the declaration of class StringUtil.
 *
 * @version 1.0 - 2017-04-18 - File created
 */

#ifndef __STRINGUTIL_HPP__
#define __STRINGUTIL_HPP__


// std includes
#include <string>
#include <vector>


/**
* @class StringUtil stringutil.hpp "stringutil.hpp"
* @brief Implementation for StringUtil class
*/
class StringUtil
{
   //--------------------------------------------------------------------
   // public types
public:

   /// Flag for the split behavior of a string.
   typedef enum ESplitBehavior
   {
      SPLIT_KEEP_EMTY_PART = 0,  // Keep empty parts during string split.
      SPLIT_SKIP_EMTY_PART = 1   // Skip empty parts during string split.
   }TSplitBehavior;


   // -----------------------------------------------------------------------
   // public methods
public:
   /**
   * @brief Converts each character to lower case.
   * @param[in] arString String which should be converted.
   * @return Converted string.
   */
   static std::string toLower(const std::string& arString);


   /**
   * @brief Converts each character to lower case.
   * @param[in,out] arString String which should be converted.
   */
   static void toLower(std::string& arString);


   /**
   * @brief Converts each character to upper case.
   * @param[in] arString String which should be converted.
   * @return Converted string.
   */
   static std::string toUpper(const std::string& arString);


   /**
   * @brief Converts each character to lower case.
   * @param[in,out] arString String which should be converted.
   */
   static void toUpper(std::string& arString);


   /**
   * @brief Splits a string into several parts.
   *
   * @param[in] arToSplit String to split.
   * @param[in] arSeparator String with separator.
   * @param[in] aBehavior Specifies how the function should behave with respect to empty strings.
   *
   * @return List with separated strings.
   */
   static std::vector<std::string> split(const std::string& arToSplit,
                                         const std::string& arSeparator,
                                         StringUtil::TSplitBehavior aBehavior = StringUtil::SPLIT_SKIP_EMTY_PART);


   /**
   * @brief Splits a string into several parts.
   *
   * @param[in] arToSplit String to split.
   * @param[in] arSeparator Char with separator.
   * @param[in] aBehavior Specifies how the function should behave with respect to empty strings.
   *
   * @return List with separated strings
   */
   static std::vector<std::string> split(const std::string& arToSplit,
                                         char aSeparator,
                                         StringUtil::TSplitBehavior aBehavior = StringUtil::SPLIT_SKIP_EMTY_PART);


   /**
   * @brief Replaces a substring from a string with another string, wherever it occurs.
   *
   * This method replaces all substrings equal to a specific input with a defined replacement.
   * @param[in] arInString Input string.
   * @param[in] arSubString String to be replaced. Occurs 0 to n times in the input string.
   * @param[in] arReplacement Replacement string, replaces all occurrences of arSubString.
   *
   * @return std::string Input string with replacements.
   */
   static std::string replaceSubString(const std::string& arInString,
                                       const std::string& arSubString,
                                       const std::string& arReplacement = std::string());


   /**
   * @brief Counts number of occurrences of a substring in a string.
   *
   * @param[in] arInString Input string.
   * @param[in] arSubString String to be counted. Occurs 0 to n times in the input string.
   *
   * @return size_t Number of occurrences.
   */
   static size_t countOccurences(const std::string& arInString, const std::string& arSubString);


   /**
   * @brief Unifies the delimiters in a input path to /
   *
   * @param[in] arInString Input string.
   *
   * @return std::string path with unified delimiter /.
   */
   static std::string unifyPathDelimiter(const std::string& arInString);


   /**
   * @brief Checks if the input string is a boolean true
   *
   * @param[in] arInString Input string.
   *
   * @return True if input string is "true" or "1", false otherwise.
   */
   static bool checkTrue(const std::string& arInString);


   // -----------------------------------------------------------------------
   // private methods
private:
   // -----------------------------------------------------------------------
   // declared, but not defined
   StringUtil();
   ~StringUtil();
   StringUtil(const StringUtil&);
   StringUtil& operator=(const StringUtil&);

}; // class StringUtil

#endif //__STRINGUTIL_HPP__
