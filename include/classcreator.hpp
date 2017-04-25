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
 * @file classcreator.hpp
 * @date 2017-04-18
 *
 * @brief This file contains the declaration of class ClassCreator
 *
 * @version 1.0 - 2017-04-18 - File created
 */


#ifndef __CLASSCREATOR_HPP__
#define __CLASSCREATOR_HPP__


// std includes
#include <string>
#include <vector>
#include <memory>

// ClassCreator includes
#include "classtemplateproperty.hpp"
#include "basetoken.hpp"
#include "blocktoken.hpp"

  
/** 
 * @class ClassCreator classcreator.hpp "classcreator.hpp"
 * @brief Static class for parsing of template files to generate header and source files content
 */
class ClassCreator 
{
   // -----------------------------------------------------------------------
   // public methods
public:
   /**
    * Create file content from template file and properties
    * @param[in]  arFileName           Path to template file
    * @param[out] arParsedContent      Content of the generated file
    * @param[in]  arProperties         Properties for parsing
    *
    * @return  File content created successfully
    */
   static bool parseTemplateFile(const std::string& arFileName,
                                 std::string& arParsedContent,
                                 const std::vector<std::shared_ptr<ClassTemplateProperty> >& arProperties);


   /**
    * Create file content from template file and properties
    * @param[in]  arTemplate           Template data
    * @param[out] arParsedContent      Content of the generated file
    * @param[in]  arProperties         Properties for parsing
    *
    * @return  File content created successfully
    */
   static bool parseTemplate(const std::string& arTemplate,
                             std::string& arParsedContent,
                             const std::vector<std::shared_ptr<ClassTemplateProperty> >& arProperties);
   

   // -----------------------------------------------------------------------
   // private methods
private:
   // -----------------------------------------------------------------------
   // declared, but not defined
   ClassCreator();
   ~ClassCreator();
   ClassCreator(const ClassCreator&);
   ClassCreator& operator=(const ClassCreator&);


   // -----------------------------------------------------------------------
   // helper methods

   /**
    * Get content of template file
    * @param[in]  arFileName           Path to template file
    * @param[out] arOutFileContent     Content of the template file
    *
    * @return  File reading completed successfully
    */
   static bool readFile(const std::string& arFileName, std::string& arOutFileContent);


   /**
    * Convert properties to tokens
    * @param[in]  arProperties         Path to template file
    * @param[out] arTokens             Vector with all tokens
    * @param[out] arBlockTokens        Vector with all block tokens
    *
    * @return  Conversion completed successfully
    */
   static void convertToTokens(const std::vector<std::shared_ptr<ClassTemplateProperty> >& arProperties,
                               std::vector<std::shared_ptr<BaseToken> >& arTokens,
                               std::vector<std::shared_ptr<BlockToken> >& arBlockTokens);
     
}; // class ClassCreator


#endif //__CLASSCREATOR_HPP__
