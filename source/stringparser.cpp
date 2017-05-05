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
 * @file stringparser.cpp
 * @date 2017-04-18
 *
 * @brief This file contains the definition of class StringParser.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


// std includes
#include <exception>
#include <stdexcept>

// ClassCreator includes
#include "stringparser.hpp"
#include "stringutil.hpp"


std::vector<std::shared_ptr<BaseToken> > StringParser::findTokens(const std::string& arStr,
                                                                  const std::string& arTokenStart,
                                                                  const std::string& arTokenEnd)
{
   // create token vector for output
   std::vector<std::shared_ptr<BaseToken> > lTokens;
   std::vector<std::shared_ptr<BaseToken> >::iterator lTokenIt;
   
   // check if the input is valid ...
   if(arTokenStart.empty() || arTokenEnd.empty() || arStr.empty())
     // if not return empty token vector.
     return lTokens;
     
   // token anchors
   size_t lStart, lEnd;

   // search for first start position
   lStart = arStr.find(arTokenStart);

   // if there is no start value, return empty token vector
   if(lStart == arStr.npos)
      return lTokens;

   // search all tokens
   while(lStart != arStr.npos)
   {
      // find end of start token
      lEnd = arStr.find(arTokenEnd, lStart + arTokenStart.size());

      // check if the end of the start token could be found
      if(lEnd == arStr.npos)
      {         
         // if the end of the token could not be found, return error and empty map
         throw std::runtime_error("Could not found end of Token " + arTokenEnd);
      }

      // get whole token length (with start and end length)
      size_t lTokenLength = lEnd + arTokenEnd.size() - lStart;

      // extract complete token with start and end condition
      std::string lTokenName = arStr.substr(lStart, lTokenLength);

      lTokenIt = lTokens.begin();
      // check if the element was already found ...
      while(lTokenIt != lTokens.end() && (*lTokenIt)->getName() != lTokenName)
         lTokenIt++;
      
      // if the element was not found, push it into the vector
      if(lTokenIt == lTokens.end())
         lTokens.push_back(std::make_shared<BaseToken>(lTokenName));

      // search next token after previous token occurrence
      lStart = arStr.find(arTokenStart, lEnd + arTokenEnd.size());
   }

   // finished
   return lTokens;
}

// -----------------------------------------------------------------------
// ----------

std::vector<std::shared_ptr<BlockToken> > StringParser::findBlockTokens(const std::string& arStr,
                                                                        const std::string& arTokenStart,
                                                                        const std::string& arTokenEnd,
                                                                        const std::string& arTokenNameEnd)
{
   // create output vector
   std::vector<std::shared_ptr<BlockToken> > lTokens;

   // check if the input is valid ...
   if(arTokenStart.empty() || arTokenEnd.empty() || arStr.empty())
     // if not return empty token vector.
     return lTokens;

   // extract the tokens by extracting the start tokens ...
   std::vector<std::shared_ptr<BaseToken> > lStartTokens;

   // with the configured findTokens method ...
   lStartTokens = StringParser::findTokens(arStr,arTokenStart,arTokenNameEnd);
   for(size_t i = 0; i < lStartTokens.size(); ++i)
   {
      // extract the name without start addition ...
      std::string lTokName = lStartTokens[i]->getName().substr(arTokenStart.size(),
                                                               lStartTokens[i]->getName().size() - 1 - arTokenStart.size());

      // and create a block token for each start token ...
      std::shared_ptr<BlockToken> lpTok(new BlockToken(lTokName,
                                                       arTokenStart + lTokName + arTokenNameEnd,
                                                       arTokenNameEnd + lTokName + arTokenEnd));

      // and push them into the BlockToken vector
      lTokens.push_back(lpTok);
   }

   // do some error checking (must have same amount of start and end tokens)
   for(size_t i = 0; i < lTokens.size(); ++i)
   {
      if (StringUtil::countOccurences(arStr, lTokens[i]->getStartName()) != StringUtil::countOccurences(arStr, lTokens[i]->getEndName()))
      {
         throw std::runtime_error("Amount of Start Tokens "
                                  + std::to_string(StringUtil::countOccurences(arStr,lTokens[i]->getStartName()))
                                  + " of Token " + lTokens[i]->getName()
                                  + " do not match amount of End Tokens "
                                  + std::to_string(StringUtil::countOccurences(arStr,lTokens[i]->getEndName()))
                                  + "!");
      }
   }
   
   // finished
   return lTokens;
}

// -----------------------------------------------------------------------
// ----------

std::string StringParser::replaceToken(const std::string& arInStr, const BaseToken& arInToken)
{
   // replace input string and return processed output
   return StringUtil::replaceSubString(arInStr, arInToken.getName(), arInToken.getValue());
}

// -----------------------------------------------------------------------
// ----------

std::string StringParser::replaceTokens(const std::string& arInStr,
                                        const std::vector<std::shared_ptr<BaseToken> >& arInTokens)
{
   // copy input string
   std::string arOutString = arInStr;

   // replace all tokens
   for(size_t i = 0; i < arInTokens.size(); ++i)
   {
      arOutString = StringUtil::replaceSubString(arOutString, arInTokens[i]->getName(), arInTokens[i]->getValue());
   }

   // return processed output
   return arOutString;
}

// -----------------------------------------------------------------------
// ----------

std::string StringParser::replaceBlockTokens(const std::string& arInStr,
                                             const std::vector<std::shared_ptr<BlockToken> >& arInTokens,
                                             const size_t aIndent)
{
   // copy input string
   std::string arOutString = arInStr;

   // replace all tokens
   for (size_t i = 0; i < arInTokens.size(); ++i)
   {
      // error check
      if (StringUtil::countOccurences(arOutString, arInTokens[i]->getStartName()) != StringUtil::countOccurences(arOutString, arInTokens[i]->getEndName()))
      {
         throw std::runtime_error("Amount of Start Tokens "
            + std::to_string(StringUtil::countOccurences(arOutString, arInTokens[i]->getStartName()))
            + " of Token "
            + arInTokens[i]->getName()
            + " do not match amount of End Tokens "
            + std::to_string(StringUtil::countOccurences(arOutString, arInTokens[i]->getEndName()))
            + "!");
      }

      // if the value is true and there is no indent, replace only the token
      if (StringUtil::checkTrue(arInTokens[i]->getValue()) && aIndent == 0)
      {
         // delete start tokens
         arOutString = StringUtil::replaceSubString(arOutString, arInTokens[i]->getStartName(), "");
         // delete end tokens
         arOutString = StringUtil::replaceSubString(arOutString, arInTokens[i]->getEndName(), "");
      }
      // if we also want to apply an indent
      else if (StringUtil::checkTrue(arInTokens[i]->getValue()))
      {
         std::string lIndent = "\n";
         // generate indent string
         for (size_t j = 0; j < aIndent; ++j)
         {
            lIndent.append(" ");
         }

         size_t lEndPos = 0, lStartPos = 0;

         lEndPos = arOutString.find(arInTokens[i]->getEndName());
         while (lEndPos != arOutString.npos)
         {
            // find next left start to the end 
            lStartPos = arOutString.substr(0, lEndPos).rfind(arInTokens[i]->getStartName(), lEndPos);
            if (lStartPos == arOutString.npos)
            {
               throw std::runtime_error("Found end string " + arInTokens[i]->getEndName()
                                        + " before start string " + arInTokens[i]->getStartName()
                                        + " for token " + arInTokens[i]->getName());
            }

            size_t lEndPosInternal = 0;
            size_t lStartPosInternal = lStartPos + arInTokens[i]->getStartName().size();

            // find \n's
            lEndPosInternal = lEndPos;
            lStartPosInternal = arOutString.find("\n", lStartPosInternal);
            while (lStartPosInternal < lEndPosInternal)
            {
               // replace "\n" with "\n    "
               arOutString = arOutString.replace(lStartPosInternal, 1, lIndent);
               lEndPosInternal += aIndent;
               lStartPosInternal = arOutString.find("\n", lStartPosInternal += aIndent);
            }

            // delete the token, first end, then start (if the start is deleted first, the end will move)
            arOutString = arOutString.replace(lEndPosInternal, arInTokens[i]->getEndName().size(), "");
            arOutString = arOutString.replace(lStartPos, arInTokens[i]->getStartName().size(), "");

            // find next end
            lEndPos = arOutString.find(arInTokens[i]->getEndName());
         }
      }
      // otherwise replace the complete token with enclosed text block
      else
      {
         size_t lEndPos = 0, lStartPos = 0;

         lEndPos = arOutString.find(arInTokens[i]->getEndName());
         while (lEndPos != arOutString.npos)
         {
            // find next left start to the end 
            lStartPos = arOutString.substr(0, lEndPos).rfind(arInTokens[i]->getStartName(), lEndPos);
            if (lStartPos == arOutString.npos)
            {
               throw std::runtime_error("Found end string " + arInTokens[i]->getEndName()
                                        + " before start string " + arInTokens[i]->getStartName()
                                        + " for token " + arInTokens[i]->getName());
            }

            // delete content
            arOutString = arOutString.replace(lStartPos, lEndPos + arInTokens[i]->getEndName().size() - lStartPos, "");

            // find next end
            lEndPos = arOutString.find(arInTokens[i]->getEndName());
         }
      }
   }

   // return output string
   return arOutString;
}

