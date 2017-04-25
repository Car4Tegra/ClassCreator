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
 * @file stringparser.hpp
 * @date 2017-04-18
 *
 * @brief This file contains the declaration of class StringParser.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


#ifndef __STRINGPARSER_HPP__
#define __STRINGPARSER_HPP__


// std includes
#include <string>
#include <vector>
#include <map>
#include <memory>

// ClassCreator includes
#include "basetoken.hpp"
#include "blocktoken.hpp"


/** 
 * @class StringParser stringparser.hpp "stringparser.hpp"
 * @brief Class to parse strings.
 */
class StringParser
{

   // -----------------------------------------------------------------------
   // public methods
public:
   // -----------------------------------------------------------------------
   // methods to find and replace tokens

   /**
    * @brief Finds and return all Tokens located in a string.
    *
    * The tokens are identified by a start and an end condition.
    * for example %THIS_IS_A_RANDOM_TOKEN$.
    *
    * @param[in] arStr String to parse.
    * @param[in] arTokenStart Start condition for a token, has to be something useful, not "".
    * @param[in] arTokenEnd End condition for a token, has to be something useful, not "".
    *
    * @return std::vector<RefPtr<BaseToken> > Vector of pointers to the found tokens.
    */
   static std::vector<std::shared_ptr<BaseToken> > findTokens(const std::string& arStr,
                                                              const std::string& arTokenStart,
                                                              const std::string& arTokenEnd);


   /**
    * @brief Finds and return all BlockTokens located in a string.
    *
    * The tokens are identified by a start and an end condition,
    * for example %START%TOKEN$ ... RANDOM_STRING ... $TOKEN%END%.
    *
    * @param[in] arStr String to parse.
    * @param[in] arTokenStart Start condition for a token, in the example "%START%".
    * @param[in] arTokenEnd End condition for a token, in the example "%END%".
    * @param[in] arTokenNameEnd End condition for a token name, in the example "$".
    *
    * @return std::vector<RefPtr<BlockToken> > Vector of pointers to the found tokens.
    */
   static std::vector<std::shared_ptr<BlockToken> > findBlockTokens(const std::string& arStr,
                                                                    const std::string& arTokenStart,
                                                                    const std::string& arTokenEnd,
                                                                    const std::string& arTokenNameEnd);


   /**
    * @brief Replaces all Tokens equal to the input token by its value.
    *
    * @param[in] arInStr String to be (partly) replaced with the token value.
    * @param[in] arInToken Token, that will replace parts of the string.
    *
    * @return std::string Processed output string.
    */
   static std::string replaceToken(const std::string& arInStr, const BaseToken& arInToken);


   /**
    * @brief Replaces all Tokens located in a string by their value.
    *
    * @param[in] arOutStr String to be (partly) replaced with the token values.
    * @param[in] arInTokens Vector of (pointers to) tokens - the tokens will replace parts of the string.
    */
   static std::string replaceTokens(const std::string& arInStr,
                                    const std::vector<std::shared_ptr<BaseToken> >& arInTokens);


   /**
    * @brief Replaces all BlockTokens located in a string.
    *
    * If the value of the BlockToken to be replaced is false,
    * the text block surrounded by the BlockToken is deleted, e.g.:
    * "%START%TOKEN ... RANDOM_STRING ... TOKEN%END%" -> ""
    * Otherwise only the BlockToken strings are deleted and the
    * text block is left unprocessed, e.g.:
    * "%START%TOKEN ... RANDOM_STRING ... TOKEN%END%" -> " ... RANDOM_STRING ... "
    *
    * It is also possible to set an (internal) indent for the text block surrounded by the BlockToken.
    * Then all lines within the BlockToken will get an additional indent, if the token is not deleted.
    * A block surrounded by TOKEN with the indent 3
    *
    * #######
    * %START%TOKEN
    * RANDOM_LINE1
    *    RANDOM_LINE2
    * RANDOM_LINE3
    * TOKEN%END%
    * #######
    *
    * will look like this, after TOKEN is replaced:
    *
    * #######
    *
    *    RANDOM_LINE1
    *       RANDOM_LINE2
    *    RANDOM_LINE3
    *
    * #######
    *
    * @param[in] arOutStr String to be (partly) replaced with the token values.
    * @param[in] arInTokens Vector of (pointers to) tokens - the tokens will replace parts of the string.
    * @param[in] aIndent Indent applied on each surrounded block, if the token is not deleted.
    *
    * @return std::string Processed string
    */
   static std::string replaceBlockTokens(const std::string& arInStr,
                                         const std::vector<std::shared_ptr<BlockToken> >& arInTokens,
                                         const size_t aIndent = 0);


   // -----------------------------------------------------------------------
   // private methods
private:
   // -----------------------------------------------------------------------
   // declared, but not defined
   StringParser();
   ~StringParser();
   StringParser(const StringParser&);
   StringParser& operator=(const StringParser&);

}; // class StringParser

#endif //__STRINGPARSER_HPP__
