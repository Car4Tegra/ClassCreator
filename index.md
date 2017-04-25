<img src="/images/Screenshot.png" alt="Screenshot" align="middle">

# Table of Contents
- 
{:toc}

# Building ClassCreator
To automatically copy the **template** directory to the build directory an additional building step has to be added in Qt Creator:

1. Open **Build Settings** (**Projects** tab on the left side)
2. Select the wanted **Build-Configuration**: `Debug` / `Release`
3. Select **Add Build Step** -> **Make**
4. Add for the **Make arguments**: `install`

# Creating Templates for ClassCreator
In this documentation the template creation for Car4Tegra ClassCreator will be explained.
  
## Overview

A ClassCreator template can consist of these four files:

* **XML Configuration**

* **Header Template** *(optional)*

* **Source Template** *(optional)*

* **CMake Template** *(optional)*

In the following sections the XML Configuration file and the available tokens for the template files will be described in detail.

## XML Configuration File

The XML configuration file contains all information about the template. The parent node ist shown below:

```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<template name="" headerfile="" sourcefile="" cmakefile="" classNameProperty="" sysPathVar=""> 

   <!-- Insert nodes here -->
   
</template>
```

Some of the attributes of the parent node are optional and could be omitted if not neccessary:

* **name**

  Contains the name of the template, which is shown in the selection combo box (e.g. "Example Class").

* **headerfile** *(optional)*

  Contains the file name of the header template file (e.g. `example_header.template`).

* **sourcefile** *(optional)*

  Contains the file name of the source template file (e.g. `example_source.template`).

* **cmakefile** *(optional)*

  Contains the file name of the CMake template file (e.g. `example_cmake.template`).

* **classNameProperty**

  Contains the identifier of the property which contains the name of the class (e.g. `CLASS_NAME`).

* **sysPathVar** *(optional)*

  Contains the name of the environment variable which should be used for auto detection of the output path (e.g. `CVHAB_FILE_DIR`).

There are five different node types:

### Node filepath

There has to be a `filepath` node for each template file used (header / source / CMake). The nodes for unused template files could be omitted.

```xml
<filepath file="header" path="\header" />
<filepath file="source" path="\source" />
<filepath file="cmake"  path="\cmake" />
```

* **file**

  Refers to the corresponding template file **type** (not the template file name itself!).

* **path**

  Contains the template for the output path for this file relative to the main output path. It could be written directly as shown above or by using tokens as shown below.

```xml
<filepath file="header" path="$HEADER_PATH$$@USE_SUB_DIR$\$SUB_DIRECTORY$$USE_SUB_DIR@$" />
```

### Node directory

The `directory` node allows to create directories, also if there is no file inside.

```xml
<directory path="/templates" />
<directory path="/modules/$MODULE_NAME_L$/source" />
```

* **path**

  Contains the template for the directory path relative to the main output path. It could be written directly or by using tokens.

### Node property

The `property` nodes represent the settings for this template. From this nodes the tokens for template parsing are created (see token section below). There are three types of `property` nodes:

```xml
<property name="" identifier="" type="bool"       default=""           info="" group="" />
<property name="" identifier="" type="string"     default="" format="" info="" group="" />
<property name="" identifier="" type="stringlist" default="" values="" info="" group="" />
```

* **name**

  Name of the property for visualization (e.g. "Class Name")

* **identifier**

  Identifier of the property for token generation (e.g. `CLASS_NAME`)

* **type**

  Type of the property 
  
  * `bool` for block token
  * `string` for text edit
  * `stringlist` for selection box

* **default**

  Default value for the property. Valid values depends on the property type:
  
  * bool: `TRUE` or `FALSE`
  * string: any string
  * stringlist: 0 based index

* **format** *(only string type)*

  Regular expression for this string type to limit input possibilities (e.g. `[A-Z].[a-zA-Z0-9_]*`)

* **values** *(only stringlist type)*

  Values for selection in combo box, separated by `,` (e.g. `Value 1,Value 2,Value 3`)

* **info**

  Help text which is shown at mouse over.

* **group** *(optional)*

  Name of the group the property is corresponding to (e.g. "Example Group")

### Node filepathproperty

The `filepathproperty` node is the same as the `property` node above but it is highlighted in green in the property browser of the GUI. It should be used for properties which only have an impact on `filepath` templates but not on the content of the template files.

```xml
<filepathproperty name="" identifier="" type="bool"       default=""           info="" group="" />
<filepathproperty name="" identifier="" type="string"     default="" format="" info="" group="" />
<filepathproperty name="" identifier="" type="stringlist" default="" values="" info="" group="" />
```

### Node postprocessing

> **The `postprocessing` node is not tested yet!!!**<br>
> The `postprocessing` node allows to run commands after file generation. They are selectable in the property browser of the GUI (highlighted in red).

```xml
<postprocessing name="Auto CMake" command="cmake" params="param1 param2 param3" info="Runs cmake for project after generate." />
```

* **name**
  
  Name of the post processing command, visible in the GUI (e.g. "Run Command")

* **command**

  Command which should be processed (e.g. `cmd`)

* **params**

  Additional parameters for the command, separated by space (e.g. `param1 param2 param3`)

* **info**

  Help text which is shown at mouse over.

## Tokens

There are two different tokens: Text tokens (string / stringlist properties) and block tokens (bool properties):

### Text Tokens


Text tokens (for string / stringlist type properties) are represented by `$IDENTIFIER$` as shown below:

```cpp
class $CLASS_NAME$
{
   // Constructor
   $CLASS_NAME$();
   
   // Destructor
   ~$CLASS_NAME$();
}
```

There is also generated automatically an `$IDENTIFIER_U$` for upper case and an `$IDENTIFIER_L$` for lower case for each text token.

### Block Tokens

A block token (for bool type properties) starts with an `$\@IDENTIFIER$` token and ends with an `$IDENTIFIER\@$` token. The code between this two tokens will be removed if `IDENTIFIER` is `FALSE`.

```cpp
class $CLASS_NAME$
{
   // Constructor
   $CLASS_NAME$();
      
   $@HAS_DESTRUCTOR$
   // Destructor
   ~$CLASS_NAME$();
   $HAS_DESTRUCTOR@$
}
```

There is also generated automatically a negated pair of tokens `$\@!IDENTIFIER$` and `$!IDENTIFIER\@$` (note the `!` sign).

### Global Tokens

Beside the tokens generated by the properties specified in the XML configuration file, there are a few other `global` tokens which are influenced by the user settings:

* **$AUTHOR$**

  Name of the author as specified in the user settings

* **$HEADER_FILE_NAME$**

  Name of the output header file (including file extension)

* **$SOURCE_FILE_NAME$**

  Name of the output source file (including file extension)

* **$CMAKE_FILE_NAME$**

  Name of the output CMake file (including file extension)

* **$IFNDEF_MACRO$**

  Include macro for header file (e.g. `__NAMESPACE_SUBNAMESPACE_FILENAME_HPP__`)

* **$DATE$**

  Current date formated as specified in the user settings

* **$INDT$**

  Indent spacing is empty if there is no `HAS_NAMESPACE` property or `HAS_NAMESPACE` is false otherwise it has the ident spaces as specified in the user settings

* **$SUB_INDT$**

  Indent spacing has the same value as `$INDT$` if there is no `HAS_SUBNAMESPACE` property or `HAS_SUBNAMESPACE` is false otherwise it has twice the ident spaces as specified in the user settings

> **Note:**<br>
> The `$IFNDEF_MACRO$` / `$INDT$` / `$SUB_INDT$` tokens are searching for `HAS_NAMESPACE` / `HAS_SUBNAMESPACE` / `NAMESPACE` / `SUB_NAMESPACE` identifiers during parsing. To use these tokens, you have to add properties with these identifiers to your configuration XML. For the `$IFNDEF_MACRO$` token, the `HAS_NAMESPACE` / `HAS_SUBNAMESPACE` identifiers are optional. 

## License
The program and all of its files are under [**MIT license**](licenseinfo.md)!
