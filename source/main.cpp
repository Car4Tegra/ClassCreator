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
 * @file main.cpp
 * @date 2017-04-18
 *
 * @brief This file contains the main function of the application
 *
 * @version 1.0 - 2017-04-18 - File created
 */


// Qt includes
#include <QApplication>

// ClassCreator includes
#include "mainwindow.hpp"


/**
 * @brief Main function
 *
 * @param[in]  aArgc    Number of arguments
 * @param[in]  apArgv   Value of arguments
 *
 * @return `0` if application works fine, `non zero` otherwise
 */
int main(int aArgc, char *apArgv[])
{
   // show main window
   QApplication lApp(aArgc, apArgv);
   MainWindow lWindow;
   lWindow.show();
   
   return lApp.exec();
}
