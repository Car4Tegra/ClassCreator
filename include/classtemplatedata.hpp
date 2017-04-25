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
 * @file classtemplatedata.hpp
 * @date 2017-04-18
 *
 * @brief This file contains the declaration of class ClassTemplateData
 *
 * @version 1.0 - 2017-04-18 - File created
 */


#ifndef __CLASSTEMPLATEDATA_HPP__
#define __CLASSTEMPLATEDATA_HPP__


// std includes
#include <string>
#include <vector>

  
/** 
 * @class ClassTemplateData classtemplatedata.hpp "classtemplatedata.hpp"
 * @brief Represents the global data for a template
 */
class ClassTemplateData 
{      
      
   // -----------------------------------------------------------------------
   // public methods
public:
   /**
    * @brief Constructor with parameters
    * @param[in]  arName               Name of the class template
    * @param[in]  arHeaderFile         Name of the corresponding template header file
    * @param[in]  arSourceFile         Name of the corresponding template source file
    * @param[in]  arCmakeFile          Name of the corresponding template CMake file
    * @param[in]  aHasHeader           Class has a header file
    * @param[in]  aHasHeader           Class has a source file
    * @param[in]  aHasCmake            Class has a CMake file
    * @param[in]  arClassNameProperty  Property representing class name
    * @param[in]  arHeaderPath         Path template for header file
    * @param[in]  arSourcePath         Path template for source file
    * @param[in]  arCmakePath          Path template for CMake file
    * @param[in]  arDir                Path templates for directories which should be created
    * @param[in]  arUseSystemPath      Use system path variable for output path
    * @param[in]  arSystemPathVar      System variable with output path
    */
   ClassTemplateData(const std::string& arName,
                     const std::string& arHeaderFile,
                     const std::string& arSourceFile,
                     const std::string& arCmakeFile,
                     bool aHasHeader,
                     bool aHasSource,
                     bool aHasCmake,
                     std::string& arClassNameProperty,
                     const std::string& arHeaderPath,
                     const std::string& arSourcePath,
                     const std::string& arCmakePath,
                     const std::vector<std::string>& arDir,
                     bool arUseSystemPath,
                     const std::string& arSystemPathVar)
      : mName(arName.c_str()), mHeaderFile(arHeaderFile.c_str()), mSourceFile(arSourceFile.c_str()),
        mCmakeFile(arCmakeFile.c_str()), mHasHeader(aHasHeader), mHasSource(aHasSource),
        mHasCmake(aHasCmake), mClassNameProperty(arClassNameProperty), mHeaderPath(arHeaderPath),
        mSourcePath(arSourcePath), mCmakePath(arCmakePath), mDir(arDir),mUseSystemPath(arUseSystemPath),
        mSystemPathVar(arSystemPathVar)
   { }

      
   /**
    * @brief Destructor
    */
   ~ClassTemplateData() { }


   /**
    * @brief Returns the name of the class template
    * @return  Name of the class template
    */
   std::string getName(void) const { return mName; }


   /**
    * @brief Returns the file name of the corresponding template header file
    * @return  File name of the corresponding template header file
    */
   std::string getHeaderFileName(void) const { return mHeaderFile; }


   /**
    * @brief Returns the file name of the corresponding template source file
    * @return  File name of the corresponding template source file
    */
   std::string getSourceFileName(void) const { return mSourceFile; }


   /**
    * @brief Returns the file name of the corresponding template CMake file
    * @return  File name of the corresponding template CMake file
    */
   std::string getCmakeFileName(void) const { return mCmakeFile; }


   /**
    * @brief Returns if the class has a header file
    * @return  True if class has a header file
    */
   bool getHasHeader(void) const { return mHasHeader; }


   /**
    * @brief Returns if the class has a header file
    * @return  True if class has a header file
    */
   bool getHasSource(void) const { return mHasSource; }


   /**
    * @brief Returns if the class has a CMake file
    * @return  True if class has a CMake file
    */
   bool getHasCmake(void) const { return mHasCmake; }


   /**
    * @brief Returns identifier of the property representing the class name
    * @return  Identifier of the property representing the class name
    */
   std::string getClasNameProperty(void) const { return mClassNameProperty; }


   /**
    * @brief Returns the path template for header file
    * @return  Path template for the header file
    */
   std::string getHeaderPath(void) const { return mHeaderPath; }


   /**
    * @brief Returns the path template for source file
    * @return  Path template for the source file
    */
   std::string getSourcePath(void) const { return mSourcePath; }


   /**
    * @brief Returns the path template for CMake file
    * @return  Path template for the CMake file
    */
   std::string getCmakePath(void) const { return mCmakePath; }


   /**
    * @brief Returns the path templates for directories which should be created
    * @return  Path templates for directories which should be created
    */
   std::vector<std::string> getDirectories(void) const { return mDir; }


   /**
    * @brief Returns if the system variable should be used
    * @return  True if system path variable should be used
    */
   bool getUseSystemPath(void) const { return mUseSystemPath; }


   /**
    * @brief Returns the system variable with output path
    * @return  System variable with output path
    */
   std::string getSystemPath(void) const { return mSystemPathVar; }
        
 
   // -----------------------------------------------------------------------
   // private methods
private:

   // -----------------------------------------------------------------------
   // declared, but not defined
   
   ClassTemplateData(const ClassTemplateData&);
   ClassTemplateData& operator=(const ClassTemplateData&);

   
   // -----------------------------------------------------------------------
   // private members
private:

   std::string mName;               ///< Name of the class template
   std::string mHeaderFile;         ///< Name of the corresponding template header file
   std::string mSourceFile;         ///< Name of the corresponding template source file
   std::string mCmakeFile;          ///< Name of the corresponding template CMake file
   bool mHasHeader;                 ///< Class has a header file
   bool mHasSource;                 ///< Class has a source file
   bool mHasCmake;                  ///< Class has a CMake file
   std::string mClassNameProperty;  ///< Property with class name
   std::string mHeaderPath;         ///< Path template for header file
   std::string mSourcePath;         ///< Path template for source file
   std::string mCmakePath;          ///< Path template for CMake file
   std::vector<std::string> mDir;   ///< Path templates for directories which should be created
   bool mUseSystemPath;             ///< Use system path variable for output path
   std::string mSystemPathVar;      ///< System variable with output path

}; // class ClassTemplateData


#endif //__CLASSTEMPLATEDATA_HPP__
