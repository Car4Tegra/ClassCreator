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
 * @file blocktoken.hpp
 * @date 2017-04-18
 *
 * @brief This file contains the declaration of class BlockToken.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


#ifndef __BLOCKTOKEN_HPP__
#define __BLOCKTOKEN_HPP__


// std includes
#include <string>
#include <vector>

// ClassCreator includes
#include "basetoken.hpp"

  
/** 
 * @class BlockToken blocktoken.hpp "blocktoken.hpp"
 * @brief Specialized base token which can contain a string
 *
 * A typical block token is this: §§TOKEN RANDOM_STRING_CONTENT §§TOKEN.
 * In contrast to the base token the block token 
 * consists of three names (start, end and normal name). The example above would have
 * TOKEN as normal name and §§TOKEN as start and end name. 
 */
class BlockToken : public BaseToken
{
   // -----------------------------------------------------------------------
   // public methods
public:
   /**
   * @brief Standard constructor
   */
   BlockToken()
      : BaseToken(), mStartName(), mEndName()
   {}


   /**
   * @brief Overloaded constructor with a name
   *
   * @param[in] arName Name of the token.
   */
   BlockToken(const std::string& arName)
      : BaseToken(arName), mStartName(), mEndName()
   {}


   /**
   * @brief Overloaded constructor with a name
   *
   * @param[in] arName Name of the token.
   * @param[in] arStartName Char sequence indication the start of the block token.
   * @param[in] arEndName Char sequence indication the end of the block token.
   */
   BlockToken(const std::string& arName,
              const std::string& arStartName,
              const std::string& arEndName)
      : BaseToken(arName), mStartName(arStartName), mEndName(arEndName)
   {}


   /**
   * @brief Overloaded constructor with a name and a value
   *
   * @param[in] arName Name of the token.
   * @param[in] arValue Value of the token.
   */
   template <typename TValueType>
   BlockToken(const std::string& arName, const TValueType& arValue)
      : BaseToken(arName, arValue), mStartName(), mEndName()
   {}


   /**
   * @brief Overloaded constructor with name, startname, endname and a value
   *
   * @param[in] arName Name of the token.
   * @param[in] arValue Value of the token.
   * @param[in] arStartName StartName of the token, is empty if not used.
   * @param[in] arEndName EndName of the token, is empty if not used.
   */
   template <typename TValueType>
   BlockToken(const std::string& arName,
              const TValueType& arValue,
              const std::string& arStartName,
              const std::string& arEndName)
      : BaseToken(arName, arValue), mStartName(arStartName), mEndName(arEndName)
   {}


   /**
   * @brief Destructor
   */
   virtual ~BlockToken()
   {}


   /**
   * @brief Gets the start string of the token.
   *
   * @return std::string String indicating start sequence of the block token.
   */
   std::string getStartName() const
   {
      return mStartName;
   }


   /**
   * @brief Gets the end string of the token.
   *
   * @return std::string String indicating end sequence of the block token.
   */
   std::string getEndName() const
   {
      return mEndName;
   }


   /**
   * @brief Sets the start string of the token.
   *
   * @param[in] arStartName Start sequence of the block token.
   */
   void setStartName(const std::string& arStartName)
   {
      mStartName = arStartName;
   }


   /**
   * @brief Sets the end string of the token.
   *
   * @param[in] arEndName End sequence of the block token.
   */
   void setEndName(const std::string& arEndName)
   {
      mEndName = arEndName;
   }


   // -----------------------------------------------------------------------
   // private members
private:
   std::string mStartName;    ///< This is the string indicating a start of the block token.
   std::string mEndName;      ///< This is the string indicating a end of the block token.
}; // class BlockToken

#endif //__BLOCKTOKEN_HPP__
