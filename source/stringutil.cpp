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
 * @file stringutil.cpp
 * @date 2017-04-18
 *
 * @brief This file contains the definition of class StringUtil.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


// std includes
#include <algorithm>
#include <sstream>
#include <vector>

// ClassCreator includes
#include "stringutil.hpp"


std::string StringUtil::toLower(const std::string& arString)
{
   std::string lRetVal(arString);
   std::transform(arString.begin(), arString.end(), lRetVal.begin(), ::tolower);
   return lRetVal;
}

// -----------------------------------------------------------------------
// ----------

void StringUtil::toLower(std::string& arString)
{
   std::transform(arString.begin(), arString.end(), arString.begin(), ::tolower);
}

// -----------------------------------------------------------------------
// ----------

std::string StringUtil::toUpper(const std::string& arString)
{
   std::string lRetVal(arString);
   std::transform(arString.begin(), arString.end(), lRetVal.begin(), ::toupper);
   return lRetVal;
}

// -----------------------------------------------------------------------
// ----------

void StringUtil::toUpper(std::string& arString)
{
   std::transform(arString.begin(), arString.end(), arString.begin(), ::toupper);
}

// -----------------------------------------------------------------------
// ----------

std::vector<std::string> StringUtil::split(const std::string& arToSplit,
                                           const std::string& arSeparator,
                                           StringUtil::TSplitBehavior aBehavior)
{
   if (arSeparator.empty())
   {
      //CVHAB_WARNING("Splitting a string with an empty separator is not reasonable. The resultant string list contains the input string!");
      return std::vector < std::string > {arToSplit};
   }

   std::string::const_iterator lStartSubString = arToSplit.begin();
   std::string::const_iterator lFoundSeparator = arToSplit.begin();
   std::string::const_iterator lEnd = arToSplit.end();
   std::vector<std::string> lRetVal;

   while (lFoundSeparator != lEnd)
   {
      // search for sequence
      lFoundSeparator = std::search(lStartSubString, arToSplit.end(), arSeparator.begin(), arSeparator.end());
      // create string
      std::string lStringVal(lStartSubString, lFoundSeparator);

      // check if empty values should be skipped or not
      if ((aBehavior == StringUtil::SPLIT_KEEP_EMTY_PART) ||
         ((aBehavior == StringUtil::SPLIT_SKIP_EMTY_PART) && !lStringVal.empty()))
      {
         lRetVal.push_back(lStringVal);
      }

      // only update start of search if iterator does not reach end of string
      if (lFoundSeparator != lEnd)
      {
         lStartSubString = lFoundSeparator + arSeparator.size();
      }
   }

   return lRetVal;
}

// -----------------------------------------------------------------------
// ----------

std::vector<std::string> StringUtil::split(const std::string& arToSplit,
                                           char aSeparator,
                                           StringUtil::TSplitBehavior aBehavior)
{
   std::stringstream lStrStream(arToSplit);
   std::vector<std::string>  lRetVal;
   std::string lStringVal;

   // get part of string till end of string is reached
   while (std::getline(lStrStream, lStringVal, aSeparator))
   {
      // check if empty values should be skipped or not
      if ((aBehavior == StringUtil::SPLIT_KEEP_EMTY_PART) ||
         ((aBehavior == StringUtil::SPLIT_SKIP_EMTY_PART) && !lStringVal.empty()))
      {
         lRetVal.push_back(lStringVal);
      }
   }

   return lRetVal;
}

// -----------------------------------------------------------------------
// ----------

std::string StringUtil::replaceSubString(const std::string& arInString,
                                         const std::string& arSubString,
                                         const std::string& arReplacement)
{
   // create string for output
   std::string lOutString = arInString;

   // check if the whole string is shorter than the string to be replaced or the string to be replaced is equal to the replacement...
   if ((arInString.size() < arSubString.size()) || (arReplacement == arSubString))
      // .. and if yes, return the input string without replacement
      return lOutString;

   // search for all substrings in the string ...
   for (size_t lPosition = lOutString.find(arSubString); lPosition != std::string::npos; lPosition = lOutString.find(arSubString))
   {
      // and replace them
      lOutString.replace(lPosition, arSubString.length(), arReplacement);
   }

   // return replaced string
   return lOutString;
}

// -----------------------------------------------------------------------
// ----------

size_t StringUtil::countOccurences(const std::string& arInString,
                                   const std::string& arSubString)
{
   // error check
   if (arSubString.empty() || arInString.empty() || arInString.size() < arSubString.size())
      return 0;

   size_t lOccurences = 0, lPos = 0;

   // find and count substring
   while (lPos != arInString.npos)
   {
      lPos = arInString.find(arSubString, lPos);
      if (lPos != arInString.npos)
      {
         lPos += arSubString.size();
         lOccurences++;
      }
   }

   return lOccurences;
}

// -----------------------------------------------------------------------
// ----------

std::string StringUtil::unifyPathDelimiter(const std::string& arInString)
{
   // unify delimiters
   std::string lPath = replaceSubString(arInString, "\\\\", "/");
   lPath = replaceSubString(lPath, "\\/", "/");
   lPath = replaceSubString(lPath, "\\", "/");
   lPath = replaceSubString(lPath, "//", "/");
   lPath = replaceSubString(lPath, "/\\", "/");
   return lPath;
}

// -----------------------------------------------------------------------
// ----------

bool StringUtil::checkTrue(const std::string& arInString)
{
   std::string lLower = StringUtil::toLower(arInString);

   if (lLower == "true" || lLower == "1")
      return true;   

   return false;
}
