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
 * @file configurationmanager.hpp
 * @date 2017-04-18
 *
 * @brief This file contains the declaration of class ConfigurationManager.
 *
 * @version 1.0 - 2017-04-18 - File created
 */


#ifndef __CONFIGURATIONMANAGER_HPP__
#define __CONFIGURATIONMANAGER_HPP__


// std includes
#include <string>
#include <vector>
#include <utility>
#include <memory>

// ClassCreator includes
#include "classtemplatedata.hpp"
#include "classtemplateproperty.hpp"
#include "usersettingsdata.hpp"


//define files & folders
#define TEMPLATE_PATH         "templates"                // Relative path to folder with template files
#define USER_SETTINGS_FILE    "usersettings.xml"         // File name of user settings xml


/** 
 * @class ConfigurationManager configurationmanager.hpp "configurationmanager.hpp"
 * @brief Finds configuration files and parses them.
 */
class ConfigurationManager 
{   

   // -----------------------------------------------------------------------
   // public methods
public:

   /**
    * @brief List all template files in a directory
    * @param[out] arTemplateList       List with found templates
    */
   static void getTemplateList(std::vector<std::string>& arTemplateList);


   /**
    * @brief Returns user settings
    * @param[out] arSettings           List of settings
    */
   static void getUserSettings(std::shared_ptr<UserSettingsData>& arSettings);


   /**
    * @brief Writes user settings
    * @param[in]  arSettings           List of settings
    */
   static void setUserSettings(const std::shared_ptr<UserSettingsData>& arSettings);

   
   // -----------------------------------------------------------------------
   // private methods
private:
   // -----------------------------------------------------------------------
   // declared, but not defined
   ConfigurationManager();
   ~ConfigurationManager();
   ConfigurationManager(const ConfigurationManager&);
   ConfigurationManager& operator=(const ConfigurationManager&);


   /**
    * @brief Config directory
    *
    * @return Returns the default config directory depending on the OS (Selected at compile time!)
    */
   static std::string getConfigDir();


   /**
    * @brief Template directory
    *
    * @return Returns the directory with the template files
    */
   static std::string getTemplateDir();
   
}; // class ConfigurationManager


#endif //__CONFIGURATIONMANAGER_HPP__
