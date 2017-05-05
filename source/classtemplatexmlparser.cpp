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
 * @file classtemplatexmlparser.cpp
 * @date 2017-04-18
 *
 * @brief This file contains the definition of class ClassTemplateXMLParser.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


// std includes
#include <exception>
#include <stdexcept>
#include <string>
#include <memory>
#include <vector>

// Qt includes
#include <QFile>

// ClassCreator includes
#include "classtemplatexmlparser.hpp"
#include "stringutil.hpp"


void ClassTemplateXMLParser::loadTemplateParameters(const std::string& arFilePath,
                                                    std::shared_ptr<ClassTemplateData>& arTplData,
                                                    std::vector<std::shared_ptr<ClassTemplateProperty> >& arTplProps,
                                                    std::vector<std::shared_ptr<ClassTemplateProperty> >& arFileProps,
                                                    std::vector<std::shared_ptr<ClassTemplateCommand> >& arTplCmd)
{
   QDomDocument lQDomDoc;

   // Load file
   openTemplateFile(arFilePath, lQDomDoc);

   // Parse template infos
   parseTemplInfos(lQDomDoc, arTplData);

   // Parse for properties
   parseProperties(lQDomDoc, arTplProps);

   // Parse for file properties
   parseFileProperties(lQDomDoc, arFileProps);

   // Parse for post processing commands
   parsePostProcessing(lQDomDoc, arTplCmd);
}


// -----------------------------------------------------------------------
// ----------

void ClassTemplateXMLParser::loadTemplateParameters(const std::string& arFilePath,
                                                    std::shared_ptr<ClassTemplateData>& arTplData)
{
   QDomDocument lQDomDoc;

   // Load file
   openTemplateFile(arFilePath, lQDomDoc);
   // Parse template infos
   parseTemplInfos(lQDomDoc, arTplData);
}


// -----------------------------------------------------------------------
// ----------


void ClassTemplateXMLParser::openTemplateFile(const std::string& arFilePath, QDomDocument& arQDomDoc)
{
   QFile file(QString(arFilePath.c_str()));
   QString errMsg;      // error message
   int errLine = 0;     // line of error
   int errCol  = 0;     // column of error

   if(!file.open(QIODevice::ReadOnly))
   {
      throw std::runtime_error("XML Configuration file could not be loaded. Path: " + arFilePath);
   }

   if(!arQDomDoc.setContent(&file, false, &errMsg, &errLine, &errCol))
   {
      throw std::runtime_error("Error while parsing file:  msg=" + errMsg.toStdString() + 
         " file=" + arFilePath + " line" + std::to_string(errLine) + " column=" + std::to_string(errCol));
   }
}


// -----------------------------------------------------------------------
// ----------


void ClassTemplateXMLParser::parseTemplInfos(const QDomDocument& arQDomDoc, std::shared_ptr<ClassTemplateData>& arTplData)
{
   // get root element
   QDomElement lDocElem = arQDomDoc.documentElement();

   // read infos from node
   std::string tmplName = lDocElem.attributeNode("name").value().toStdString();

   // read file names
   bool tmplHasHeader = false;
   bool tmplHasSource = false;
   bool tmplHasCmake = false;
   std::string tmplFileHeader = "";
   std::string tmplFileSource = "";
   std::string tmplFileCmake = "";

   if(lDocElem.hasAttribute("headerfile"))
   {
      tmplFileHeader = lDocElem.attributeNode("headerfile").value().toStdString();
      if(tmplFileHeader != "") tmplHasHeader = true;
   }
   if(lDocElem.hasAttribute("sourcefile"))
   {
      tmplFileSource = lDocElem.attributeNode("sourcefile").value().toStdString();
      if(tmplFileSource != "") tmplHasSource = true;
   }
   if(lDocElem.hasAttribute("cmakefile"))
   {
      tmplFileCmake = lDocElem.attributeNode("cmakefile").value().toStdString();
      if(tmplFileCmake != "") tmplHasCmake = true;
   }

   // read system variable
   bool tmplUseSystemPath = false;
   std::string tmplSystemVar = "";

   if(lDocElem.hasAttribute("sysPathVar"))
   {
      tmplSystemVar = lDocElem.attributeNode("sysPathVar").value().toStdString();
      if(tmplSystemVar != "") tmplUseSystemPath = true;
   }

   // read class name property
   std::string tmplClProp = lDocElem.attributeNode("classNameProperty").value().toStdString();
   

   // Parse file path templates
   std::string lHeaderPath, lSourcePath, lCmakePath;
   parseFilePaths(arQDomDoc, lHeaderPath, lSourcePath, lCmakePath);

   // Parse directories
   std::vector<std::string> lDir;
   parseDirectories(arQDomDoc, lDir);

   // create data item
   arTplData = std::make_shared<ClassTemplateData>(tmplName,
                                                   tmplFileHeader,
                                                   tmplFileSource,
                                                   tmplFileCmake,
                                                   tmplHasHeader,
                                                   tmplHasSource,
                                                   tmplHasCmake,
                                                   tmplClProp,
                                                   lHeaderPath,
                                                   lSourcePath,
                                                   lCmakePath,
                                                   lDir,
                                                   tmplUseSystemPath,
                                                   tmplSystemVar);
}


// -----------------------------------------------------------------------
// ----------


void ClassTemplateXMLParser::parseFilePaths(const QDomDocument& arQDomDoc,
                                            std::string& arHeaderPath,
                                            std::string& arSourcePath,
                                            std::string& arCmakePath)
{
   // get root element
   QDomElement lDocElem = arQDomDoc.documentElement();

   // get list of all post processing parent nodes
   QDomNodeList fileList = lDocElem.elementsByTagName("filepath");

   // set default values
   arHeaderPath = "";
   arSourcePath = "";
   arCmakePath  = "";

   // loop through all found property nodes
   for(size_t i=0; static_cast<int>(i)<fileList.length(); i++)
   {
      // is valid element?
      if(fileList.at(static_cast<int>(i)).isElement())
      {
         QDomElement paramElement = fileList.at(static_cast<int>(i)).toElement();

         std::string lFile = paramElement.attributeNode("file").value().toStdString();
         std::string lPath = paramElement.attributeNode("path").value().toStdString();

         if(lFile == "header")
            arHeaderPath = lPath;
         else if(lFile == "source")
            arSourcePath = lPath;
         else if(lFile == "cmake")
            arCmakePath = lPath;

      }
   }
}


// -----------------------------------------------------------------------
// ----------


void ClassTemplateXMLParser::parseDirectories(const QDomDocument& arQDomDoc, std::vector<std::string>& arDir)
{
   // get root element
   QDomElement lDocElem = arQDomDoc.documentElement();

   // get list of all post processing parent nodes
   QDomNodeList lDirList = lDocElem.elementsByTagName("directory");
   
   // loop through all found property nodes
   for(size_t i=0; static_cast<int>(i)<lDirList.length(); i++)
   {
      // is valid element?
      if (lDirList.at(static_cast<int>(i)).isElement())
      {
         QDomElement paramElement = lDirList.at(static_cast<int>(i)).toElement();

         std::string lPath = paramElement.attributeNode("path").value().toStdString();

         arDir.push_back(lPath);
      }
   }
}


// -----------------------------------------------------------------------
// ----------


void ClassTemplateXMLParser::parseProperties(const QDomDocument& arQDomDoc,
                                             std::vector<std::shared_ptr<ClassTemplateProperty> >& arTplProps)
{
   // get root element
   QDomElement lDocElem = arQDomDoc.documentElement();

   // get list of all parameter parent nodes
   QDomNodeList propertyList = lDocElem.elementsByTagName("property");

   // loop through all found property nodes
   for(size_t i=0; static_cast<int>(i)<propertyList.length(); i++)
   {
      // is valid element?
      if (propertyList.at(static_cast<int>(i)).isElement())
      {
         QDomElement paramElement = propertyList.at(static_cast<int>(i)).toElement();

         // get values for property
         std::string propName = paramElement.attributeNode("name").value().toStdString();
         std::string propIdentifier = paramElement.attributeNode("identifier").value().toStdString();
         std::string propType = paramElement.attributeNode("type").value().toStdString();
         std::string propDefault = paramElement.attributeNode("default").value().toStdString();
         std::string propInfo = paramElement.attributeNode("info").value().toStdString();
         std::string propGroup = "";

         if(paramElement.attributeNode("group").isAttr())
            propGroup = paramElement.attributeNode("group").value().toStdString();

         // create vector entry
         if(propType == "string")
         {
            std::string propGenExp = "";
            if(paramElement.attributeNode("format").isAttr())
               propGenExp = paramElement.attributeNode("format").value().toStdString();

            arTplProps.push_back(std::make_shared<ClassTemplateProperty>(propName,
                                                                         propIdentifier,
                                                                         ClassTemplateProperty::PROP_TYPE_STRING,
                                                                         propDefault,
                                                                         propInfo,
                                                                         propGroup,
                                                                         propGenExp));
         }
         else if(propType == "stringlist")
         {            
            std::string propList = paramElement.attributeNode("values").value().toStdString();
            std::vector<std::string> lListValues = StringUtil::split(propList, ",", StringUtil::SPLIT_SKIP_EMTY_PART);

            arTplProps.push_back(std::make_shared<ClassTemplateProperty>(propName,
                                                                         propIdentifier,
                                                                         ClassTemplateProperty::PROP_TYPE_STRINGLIST,
                                                                         propDefault,
                                                                         propInfo,
                                                                         propGroup,
                                                                         lListValues));
         }
         else if(propType == "bool")
         {
            arTplProps.push_back(std::make_shared<ClassTemplateProperty>(propName,
                                                                         propIdentifier,
                                                                         ClassTemplateProperty::PROP_TYPE_BOOL,
                                                                         propDefault,
                                                                         propInfo,
                                                                         propGroup,
                                                                         ""));
         }
         else
         {
            // undefined property type
            throw std::runtime_error("Invalid property type: " + propType);
         }
      }
   }
}


// -----------------------------------------------------------------------
// ----------


void ClassTemplateXMLParser::parsePostProcessing(const QDomDocument& arQDomDoc,
                                                 std::vector<std::shared_ptr<ClassTemplateCommand> >& arTplCmd)
{
   // get root element
   QDomElement lDocElem = arQDomDoc.documentElement();

   // get list of all post processing parent nodes
   QDomNodeList cmdList = lDocElem.elementsByTagName("postprocessing");

   // loop through all found property nodes
   for(size_t i=0; static_cast<int>(i)<cmdList.length(); i++)
   {
      // is valid element?
      if(cmdList.at(static_cast<int>(i)).isElement())
      {
         QDomElement paramElement = cmdList.at(static_cast<int>(i)).toElement();

         std::string cmdName = paramElement.attributeNode("name").value().toStdString();
         std::string cmdCommand = paramElement.attributeNode("command").value().toStdString();
         std::string cmdParams = paramElement.attributeNode("params").value().toStdString();
         std::string cmdInfo = paramElement.attributeNode("info").value().toStdString();

         arTplCmd.push_back(std::make_shared<ClassTemplateCommand>(cmdName, cmdCommand, cmdParams, cmdInfo));
      }
   }
}


// -----------------------------------------------------------------------
// ----------


void ClassTemplateXMLParser::parseFileProperties(const QDomDocument& arQDomDoc,
                                                 std::vector<std::shared_ptr<ClassTemplateProperty> >& arTplFileProps)
{
   // get root element
   QDomElement lDocElem = arQDomDoc.documentElement();

   // get list of all parameter parent nodes
   QDomNodeList propertyList = lDocElem.elementsByTagName("filepathproperty");

   // loop through all found property nodes
   for(size_t i=0; static_cast<int>(i)<propertyList.length(); i++)
   {
      // is valid element?
      if (propertyList.at(static_cast<int>(i)).isElement())
      {
         QDomElement paramElement = propertyList.at(static_cast<int>(i)).toElement();

         // get values for property
         std::string propName = paramElement.attributeNode("name").value().toStdString();
         std::string propIdentifier = paramElement.attributeNode("identifier").value().toStdString();
         std::string propType = paramElement.attributeNode("type").value().toStdString();
         std::string propDefault = paramElement.attributeNode("default").value().toStdString();
         std::string propInfo = paramElement.attributeNode("info").value().toStdString();
         std::string propGroup = "";

         if(paramElement.attributeNode("group").isAttr())
            propGroup = paramElement.attributeNode("group").value().toStdString();

         // create vector entry
         if(propType == "string")
         {
            std::string propGenExp = "";
            if(paramElement.attributeNode("format").isAttr())
               propGenExp = paramElement.attributeNode("format").value().toStdString();

            arTplFileProps.push_back(std::make_shared<ClassTemplateProperty>(propName,
                                                                             propIdentifier,
                                                                             ClassTemplateProperty::PROP_TYPE_STRING,
                                                                             propDefault,
                                                                             propInfo,
                                                                             propGroup,
                                                                             propGenExp));
         }
         else if(propType == "stringlist")
         {            
            std::string propList = paramElement.attributeNode("values").value().toStdString();
            std::vector<std::string> lListValues = StringUtil::split(propList, ",", StringUtil::SPLIT_SKIP_EMTY_PART);

            arTplFileProps.push_back(std::make_shared<ClassTemplateProperty>(propName,
                                                                             propIdentifier,
                                                                             ClassTemplateProperty::PROP_TYPE_STRINGLIST,
                                                                             propDefault,
                                                                             propInfo,
                                                                             propGroup,
                                                                             lListValues));
         }
         else if(propType == "bool")
         {
            arTplFileProps.push_back(std::make_shared<ClassTemplateProperty>(propName,
                                                                             propIdentifier,
                                                                             ClassTemplateProperty::PROP_TYPE_BOOL,
                                                                             propDefault,
                                                                             propInfo,
                                                                             propGroup,
                                                                             ""));
         }
         else
         {
            // undefined property type
            throw std::runtime_error("Invalid property type: " + propType);
         }
      }
   }
}
