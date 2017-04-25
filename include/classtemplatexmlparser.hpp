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
 * @file classtemplatexmlparser.hpp
 * @date 2017-04-18
 *
 * @brief This file contains the declaration of class ClassTemplateXMLParser.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


#ifndef __CLASSTEMPLATEXMLPARSER_HPP__
#define __CLASSTEMPLATEXMLPARSER_HPP__


// std includes
#include <string>
#include <vector>
#include <memory>

// Qt includes
#include <QDomDocument>

// ClassCreator includes
#include "classtemplatedata.hpp"
#include "classtemplateproperty.hpp"
#include "classtemplatecommand.hpp"

  
/** 
 * @class ClassTemplateXMLParser classtemplatexmlparser.hpp "classtemplatexmlparser.hpp"
 * @brief XML parser for class template properties files
 */
class ClassTemplateXMLParser 
{
   // -----------------------------------------------------------------------
   // public static methods
public:
   /**
    * @brief Parses a class template properties file
    * @param[in]  arFilePath           Path of the class template properties file
    * @param[out] arTplData            Global class template information
    * @param[out] arTplProps           Vector with all properties of this template
    * @param[out] arFileProps          Vector with all file path properties of this template
    * @param[out] arTplCmd             Vector with all commands of this template
    *
    * @return  parsing of file completed successfully
    */
   static bool loadTemplateParameters(const std::string& arFilePath,
                                      std::shared_ptr<ClassTemplateData>& arTplData,
                                      std::vector<std::shared_ptr<ClassTemplateProperty> >& arTplProps,
                                      std::vector<std::shared_ptr<ClassTemplateProperty> >& arFileProps,
                                      std::vector<std::shared_ptr<ClassTemplateCommand> >& arTplCmd);


   /**
    * @brief Parses a class template properties file
    * @param[in]  arFilePath           Path of the class template properties file
    * @param[out] arTplData            Global class template information
    *
    * @return  parsing of file completed successfully
    */
   static bool loadTemplateParameters(const std::string& arFilePath,
                                      std::shared_ptr<ClassTemplateData>& arTplData);


   // -----------------------------------------------------------------------
   // private static methods
private:
   /**
    * @brief Opens template properties file for parsing
    * @param[in]  arFilePath           Path of the class template properties file
    * @param[out] arQDomDoc            Content of the XML configuration file
    
    * @return  file opened successfully
    */
   static bool openTemplateFile(const std::string& arFilePath, QDomDocument& arQDomDoc);


   /**
    * @brief Parses the global information for the template
    * @param[in]  arQDomDoc            Content of the XML configuration file
    * @param[out] arTplData            Template information file
    *
    * @return  parsing of file completed successfully
    */
   static bool parseTemplInfos(const QDomDocument& arQDomDoc,
                               std::shared_ptr<ClassTemplateData>& arTplData);


   /**
    * @brief Parses the file path templates
    * @param[in]  arQDomDoc            Content of the XML configuration file
    * @param[out] arHeaderPath         Path template for header file
    * @param[out] arSourcePath         Path template for source file
    * @param[out] arCmakePath          Path template for CMake file
    *
    * @return  parsing of file completed successfully
    */
   static bool parseFilePaths(const QDomDocument& arQDomDoc,
                              std::string& arHeaderPath,
                              std::string& arSourcePath,
                              std::string& arCmakePath);


   /**
    * @brief Parses the directory templates
    * @param[in]  arQDomDoc            Content of the XML configuration file
    * @param[out] arDir                Directory templates which should be created
    *
    * @return  parsing of file completed successfully
    */
   static bool parseDirectories(const QDomDocument& arQDomDoc, std::vector<std::string>& arDir);


   /**
    * @brief Parses the content of a class template file for properties
    * @param[in]  arQDomDoc            Content of the XML configuration file
    * @param[out] arTplProps           Properties of the template
    *
    * @return  parsing of file completed successfully
    */
   static bool parseProperties(const QDomDocument& arQDomDoc,
                               std::vector<std::shared_ptr<ClassTemplateProperty> >& arTplProps);


   /**
    * @brief Parses the content of a class template file for properties
    * @param[in]  arQDomDoc            Content of the XML configuration file
    * @param[out] arTplProps           Properties of the template
    *
    * @return  parsing of file completed successfully
    */
   static bool parsePostProcessing(const QDomDocument& arQDomDoc,
                                   std::vector<std::shared_ptr<ClassTemplateCommand> >& arTplCmd);


   /**
    * @brief Parses the content of a class template file for file path properties
    * @param[in]  arQDomDoc            Content of the XML configuration file
    * @param[out] arTplProps           File path properties of the template
    *
    * @return  parsing of file completed successfully
    */
   static bool parseFileProperties(const QDomDocument& arQDomDoc,
                                   std::vector<std::shared_ptr<ClassTemplateProperty> >& arTplFileProps);
              
 
   // -----------------------------------------------------------------------
   // private methods
private:
   /**
    * @brief Standard constructor
    */
   ClassTemplateXMLParser() { }


   /**
    * @brief Destructor
    */
   ~ClassTemplateXMLParser() { }


   // -----------------------------------------------------------------------
   // declared, but not defined
   
   ClassTemplateXMLParser(const ClassTemplateXMLParser&);
   ClassTemplateXMLParser& operator=(const ClassTemplateXMLParser&);

}; // class ClassTemplateXMLParser

#endif //__CLASSTEMPLATEXMLPARSER_HPP__
