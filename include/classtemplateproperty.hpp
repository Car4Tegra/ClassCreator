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
 * @file classtemplateproperty.hpp
 * @date 2017-04-18
 *
 * @brief This file contains the declaration of class ClassTemplateParameter
 *
 * @version 1.0 - 2017-04-18 - File created
 */


#ifndef __CLASSTEMPLATEPROPERTY_HPP__
#define __CLASSTEMPLATEPROPERTY_HPP__


// std includes
#include <string>
#include <vector>

  
/** 
 * @class ClassTemplateProperty classtemplateproperty.hpp "classtemplateproperty.hpp"
 * @brief Represents a template property
 */
class ClassTemplateProperty 
{            
   // -----------------------------------------------------------------------
   // public types and enumerations
public:
      
   /**
    * @brief Parameter type
    */
   enum PropertyType {
      PROP_TYPE_STRING,
      PROP_TYPE_STRINGLIST,
      PROP_TYPE_BOOL
   };

   // -----------------------------------------------------------------------
   // public methods
public:   
   /**
    * @brief Constructor with parameters
    * @param[in]  arName               Name of the property
    * @param[in]  arIdentifier         Identifier of the property for template parsing
    * @param[in]  aType                Type of the property
    * @param[in]  arDefault            Default value of the property
    * @param[in]  arInfo               Help text for this property
    * @param[in]  arGroup              Property group
    * @param[in]  arRegExpression      Regular expression for string types
    */
   ClassTemplateProperty(const std::string& arName,
                         const std::string& arIdentifier,
                         PropertyType aType,
                         const std::string& arDefault,
                         const std::string& arInfo,
                         const std::string& arGroup,
                         const std::string& arRegExpression)
      : mValue(arDefault.c_str()), mName(arName.c_str()), mIdentifier(arIdentifier.c_str()),
        mType(aType), mDefault(arDefault.c_str()), mInfo(arInfo.c_str()), mGroup(arGroup),
        mRegExpression(arRegExpression)
   { }


   /**
    * @brief Constructor with parameters for string list types
    * @param[in]  arName               Name of the property
    * @param[in]  arIdentifier         Identifier of the property for template parsing
    * @param[in]  aType                Type of the property
    * @param[in]  arDefault            Default value of the property
    * @param[in]  arInfo               Help text for this property
    * @param[in]  arGroup              Property group
    * @param[in]  arList               Value list for string list types
    */
   ClassTemplateProperty(const std::string& arName,
                         const std::string& arIdentifier,
                         PropertyType aType,
                         const std::string& arDefault,
                         const std::string& arInfo,
                         const std::string& arGroup,
                         const std::vector<std::string> arList)
      : mValue(arDefault.c_str()), mName(arName.c_str()), mIdentifier(arIdentifier.c_str()),
        mType(aType), mDefault(arDefault.c_str()), mInfo(arInfo.c_str()), mList(arList),
        mGroup(arGroup), mRegExpression("")
   { }

      
   /**
    * @brief Destructor
    */
   ~ClassTemplateProperty()
   {  mList.clear(); }


   /**
    * @brief Returns the name of the property
    * @return  Name of the property
    */
   std::string getName(void) const { return mName; }


   /**
    * @brief Returns the identifier of the property for template parsing
    * @return  Identifier of the property for template parsing
    */
   std::string getIdentifier(void) const { return mIdentifier; }


   /**
    * @brief Returns the type of the property
    * @return  Type of the property
    */
   PropertyType getType(void) const { return mType; }


   /**
    * @brief Returns the default value of the property
    * @return  Default value of the property
    */
   std::string getDefaultValue(void) const { return mDefault; }


   /**
    * @brief Returns the info text for this property
    * @return  Info text for this property
    */
   std::string getInfoText(void) const { return mInfo; }


   /**
    * @brief Returns the value List for string list types for this property
    * @return  Value List for string list types
    */
   std::vector<std::string> getStringList(void) const { return mList; }


   /**
    * @brief Returns the property group for this property
    * @return  Property group for this property (empty if no group exists)
    */
   std::string getGroup(void) const { return mGroup; }


   /**
    * @brief Returns the regular expression for this property (only for string types)
    * @return  Regular expression for this property (empty means no limitations)
    */
   std::string getRegExpression(void) const { return mRegExpression; }


   // -----------------------------------------------------------------------
   // public members
public:
   std::string mValue;              ///< Value of the property

   // -----------------------------------------------------------------------
   // private members
private:

   std::string mName;               ///< Name of the property
   std::string mIdentifier;         ///< Identifier of the property for template parsing
   PropertyType mType;              ///< Type of the property
   std::string mDefault;            ///< Default value of the property
   std::string mInfo;               ///< Help text for this property
   std::vector<std::string> mList;  ///< Value List for string list types
   std::string mGroup;              ///< Property group
   std::string mRegExpression;      ///< Regular expression (only for string properties)

}; // class ClassTemplateProperty

#endif //__CLASSTEMPLATEPROPERTY_HPP__
