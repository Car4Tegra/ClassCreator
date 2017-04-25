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
 * @file basetoken.hpp
 * @date 2017-04-18
 *
 * @brief This file contains the declaration of class BaseToken.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


#ifndef __BASETOKEN_HPP__
#define __BASETOKEN_HPP__


// std includes
#include <string>
#include <vector>
#include <sstream>

  
/** 
 * @class BaseToken basetoken.hpp "basetoken.hpp"
 * @brief Represents a token.
 *
 * A BaseToken consists of a name and a value.
 */
class BaseToken
{      
   // -----------------------------------------------------------------------
   // public methods
public:
   /**
   * @brief Standard constructor
   */
   BaseToken()
      : mName(), mValue()
   {}


   /**
   * @brief Overloaded constructor with a name
   *
   * @param[in] arName Name of the token.
   */
   BaseToken(const std::string& arName)
      : mName(arName), mValue()
   {}


   /**
   * @brief Overloaded constructor with a name and a value
   *
   * @param[in] arName Name of the token.
   * @param[in] arValue Value of the token.
   */
   template <typename TValueType>
   BaseToken(const std::string& arName, const TValueType& arValue)
      : mName(arName), mValue(std::to_string(arValue))
   {}


   /**
   * @brief Destructor
   */
   virtual ~BaseToken()
   {}


   /**
   * @brief Gets the name of the token.
   *
   * @return std::string Name of the token.
   */
   std::string getName() const
   {
      return mName;
   }


   /**
   * @brief Gets the value of the token
   *
   * @return std::string Value of the token as string.
   */
   std::string getValue() const
   {
      return mValue;
   }


   /**
   * @brief Sets the name of the token.
   *
   * The setName function sets the name, if the token
   * has not already a name. If it has, the old name is
   * NOT overwritten.
   * @param[in] arName Name of the token.
   * @return bool Is true, if the token name could be set.
   */
   bool setName(const std::string& arName)
   {
      // if the name is not set already, set it
      if (mName.size() != 0)
         return false;

      mName = arName;
      return true;
   }


   /**
   * @brief Sets the value of the token
   *
   * The value is saved as a string
   * @param[in] arValue Value to be saved in the token.
   */
   template <typename TValueType>
   void setValue(const TValueType& arValue)
   {
      std::stringstream lStream;
      lStream << arValue;
      mValue = lStream.str();
   }


   /**
   * @brief Resets the token value.
   */
   virtual void reset()
   {
      // reset the value
      mValue.clear();
   }

   // -----------------------------------------------------------------------
   // private members
protected:
   std::string mName;      ///< This is the name of the token.
   std::string mValue;     ///< This is the value of the token.
}; // class BaseToken


#endif //__BASETOKEN_HPP__
