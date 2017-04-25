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
 * @file classtemplatecommand.hpp
 * @date 2017-04-18
 *
 * @brief This file contains the declaration of class ClassTemplateCommand.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


#ifndef __CLASSTEMPLATECOMMAND_HPP__
#define __CLASSTEMPLATECOMMAND_HPP__


// std includes
#include <string>

  
/** 
 * @class ClassTemplateCommand classtemplatecommand.hpp "classtemplatecommand.hpp"
 * @brief Represents a post processing step
 */
class ClassTemplateCommand 
{      
      
   // -----------------------------------------------------------------------
   // public methods
public:
   /**
    * @brief Constructor with parameters
    * @param[in]  arName               Name of the post post processing step
    * @param[in]  arCommand            Command for the post processing step
    * @param[in]  arParams             Parameters for the command
    * @param[in]  arInfo               Info text for the command
    */
   ClassTemplateCommand(const std::string& arName,
                        const std::string& arCommand,
                        std::string& arParams,
                        std::string& arInfo )
      : mProcess(false), mName(arName), mCommand(arCommand),
        mParams(arParams), mInfo(arInfo)
   { }
      

   /**
    * @brief Destructor
    */
   ~ClassTemplateCommand() { }


   /**
    * @brief Returns the name of the post post processing step
    * @return  Name of the post post processing step
    */
   std::string getName(void) const { return mName; }


   /**
    * @brief Returns the command for the post processing step
    * @return  Command for the post processing step
    */
   std::string getCommand(void) const { return mCommand; }


   /**
    * @brief Returns the parameters for the command
    * @return  Parameters for the command
    */
   std::string getParams(void) const { return mParams; }


   /**
    * @brief Returns the info text for the command
    * @return  Info text for the command
    */
   std::string getInfoText(void) const { return mInfo; }


   // -----------------------------------------------------------------------
   // public members
public:

   bool mProcess;                ///< Process this command in post processing
        
 
   // -----------------------------------------------------------------------
   // private methods
private:

   // -----------------------------------------------------------------------
   // declared, but not defined
   
   ClassTemplateCommand(const ClassTemplateCommand&);
   ClassTemplateCommand& operator=(const ClassTemplateCommand&);

   
   // -----------------------------------------------------------------------
   // private members
private:

   std::string mName;               ///< Name of the post post processing step
   std::string mCommand;            ///< Command for the post processing step
   std::string mParams;             ///< Parameters for the command
   std::string mInfo;               ///< Info text for the command

}; // class ClassTemplateCommand


#endif //__CLASSTEMPLATECOMMAND_HPP__
