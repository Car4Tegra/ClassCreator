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
 * @file classcreator.cpp
 * @date 2017-04-18
 *
 * @brief This file contains the definition of class ClassCreator.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


// std includes
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <exception>
#include <stdexcept>

// Qt includes
#include <QString>
#include <QFile>
#include <QTextStream>

// ClassCreator includes
#include "classcreator.hpp"
#include "stringparser.hpp"
#include "stringutil.hpp"


bool ClassCreator::parseTemplateFile(const std::string& arFileName,
                                     std::string& arParsedContent,
                                     const std::vector<std::shared_ptr<ClassTemplateProperty> >& arProperties)
{
   std::string lTemplate;
   std::vector<std::shared_ptr<BaseToken> > lTokens;
   std::vector<std::shared_ptr<BlockToken> > lBlockTokens;

   // read template file
   readFile(arFileName, lTemplate);

   // convert properties to token
   convertToTokens(arProperties, lTokens, lBlockTokens);

   // replace tokens
   lTemplate = StringParser::replaceTokens(lTemplate, lTokens);
   arParsedContent = StringParser::replaceBlockTokens(lTemplate, lBlockTokens);      
   
   return true;
}


// -----------------------------------------------------------------------
// ----------


bool ClassCreator::parseTemplate(const std::string& arTemplate,
                                 std::string& arParsedContent,
                                 const std::vector<std::shared_ptr<ClassTemplateProperty> >& arProperties)
{
   std::string lTemplate;
   std::vector<std::shared_ptr<BaseToken> > lTokens;
   std::vector<std::shared_ptr<BlockToken> > lBlockTokens;
   
   // convert properties to token
   convertToTokens(arProperties, lTokens, lBlockTokens);

   // replace tokens
   lTemplate = StringParser::replaceTokens(arTemplate, lTokens);
   arParsedContent = StringParser::replaceBlockTokens(lTemplate, lBlockTokens);      
   
   return true;
}


// -----------------------------------------------------------------------
// ----------


bool ClassCreator::readFile(const std::string& arFileName, std::string& arOutFileContent)
{
   QFile file(QString(arFileName.c_str()));

   if(!file.open(QIODevice::ReadOnly))
   {
      throw std::runtime_error("XML Configuration file could not be loaded.\nPath: " + arFileName);
   }

   QTextStream lStream(&file);

   arOutFileContent = lStream.readAll().toStdString();

   // finished
   return true;
}

void ClassCreator::convertToTokens(const std::vector<std::shared_ptr<ClassTemplateProperty> >& arProperties,
                                   std::vector<std::shared_ptr<BaseToken> >& arTokens,
                                   std::vector<std::shared_ptr<BlockToken> >& arBlockTokens)
{
   arTokens.clear();
   arBlockTokens.clear();

   for(size_t i = 0; i < arProperties.size(); i++)
   {
      if(arProperties[i]->getType() == ClassTemplateProperty::PROP_TYPE_BOOL)
      {
         bool lRet;
         const std::string lTemp = arProperties[i]->mValue;
         if ("true" == StringUtil::toLower(lTemp))
            lRet = true;
         else
            lRet = false;

         // add block token
         arBlockTokens.push_back(std::make_shared<BlockToken>(arProperties[i]->getIdentifier()));
         arBlockTokens[arBlockTokens.size() - 1]->setStartName("$@" + arProperties[i]->getIdentifier() + "$");
         arBlockTokens[arBlockTokens.size() - 1]->setEndName("$" + arProperties[i]->getIdentifier() + "@$");
         arBlockTokens[arBlockTokens.size() - 1]->setValue<bool>(lRet);

         // add NOT block token
         arBlockTokens.push_back(std::make_shared<BlockToken>("!" + arProperties[i]->getIdentifier()));
         arBlockTokens[arBlockTokens.size() - 1]->setStartName("$@!" + arProperties[i]->getIdentifier() + "$");
         arBlockTokens[arBlockTokens.size() - 1]->setEndName("$!" + arProperties[i]->getIdentifier() + "@$");
         arBlockTokens[arBlockTokens.size() - 1]->setValue<bool>(!lRet);
      }
      else
      {
         // create indent
         if(arProperties[i]->getIdentifier() == "INDENT")
         {
            std::shared_ptr<BaseToken> lIndent(new BaseToken("$INDT$"));
            lIndent->setValue<std::string>("");
            std::shared_ptr<BaseToken> lSubIndent(new BaseToken("$SUB_INDT$"));
            lSubIndent->setValue<std::string>("");
            
            // create indent
            for(size_t j = 0; j < arProperties.size(); ++j)
            {
               bool lRet;
               const std::string lTemp = arProperties[j]->mValue;
               if ("true" == StringUtil::toLower(lTemp))
                  lRet = true;
               else
                  lRet = false;

               if(arProperties[j]->getIdentifier()== "HAS_NAMESPACE")
               {
                  if (lRet)
                  {
                     lIndent->setValue<std::string>(arProperties[i]->mValue);
                     if(lSubIndent->getValue() == "")
                        lSubIndent->setValue<std::string>(arProperties[i]->mValue);
                  }
               }
               else if(arProperties[j]->getIdentifier() == "HAS_SUBNAMESPACE")
               {
                  if (lRet)
                     lSubIndent->setValue<std::string>(arProperties[i]->mValue + arProperties[i]->mValue);
                  else
                     lSubIndent->setValue<std::string>(lIndent->getValue());
               }
            }

            arTokens.push_back(lIndent);
            arTokens.push_back(lSubIndent);
         }
         else
         {

            // add token
            arTokens.push_back(std::make_shared<BaseToken>("$" + arProperties[i]->getIdentifier() + "$"));

            std::string lTemp;

            if(arProperties[i]->getType() == ClassTemplateProperty::PROP_TYPE_STRINGLIST)
            {
               // get string value for selected string list index
               std::vector<std::string> lList = arProperties[i]->getStringList();
               int lIndex = std::atoi(arProperties[i]->mValue.c_str());

               lTemp = lList[static_cast<size_t>(lIndex)];
            }
            else
               lTemp = arProperties[i]->mValue;

            // add normal, lower and upper case token
            arTokens[arTokens.size() - 1]->setValue<std::string>(lTemp);
            arTokens.push_back(std::make_shared<BaseToken>("$" + arProperties[i]->getIdentifier() + "_U$"));
            StringUtil::toUpper(lTemp);
            arTokens[arTokens.size() - 1]->setValue<std::string>(lTemp);
            arTokens.push_back(std::make_shared<BaseToken>("$" + arProperties[i]->getIdentifier() + "_L$"));
            StringUtil::toUpper(lTemp);
            arTokens[arTokens.size() - 1]->setValue<std::string>(lTemp);
         }
      }
   }
}
   
