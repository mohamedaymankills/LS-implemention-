# MYLS - A Custom Directory Listing Tool

## Overview
MYLS is a custom implementation of the Unix ls command, designed to provide various options for listing directory contents. This project demonstrates proficiency in C programming, file system interactions, and command-line interface design. MYLS supports several listing formats and sorting options, allowing users to customize the output to their needs.

## Features
File Listing: Display files and directories with various formatting options.
Sorting: Sort files by name, modification time, access time, and creation time.
Formatting: List files in long format, single column, or unsorted.
Hidden Files: Option to include or exclude hidden files.
Color Output: Supports colorized output for easier file type differentiation.

## Table of Contents
Installation
Usage
Options
Source Files
Functionality
License
Acknowledgments

## Installation
To build MYLS, follow these steps:

Clone the Repository:

```bash
git clone https://github.com/mohamedaymankills/LS-implemention-.git
```
Navigate to the Project Directory:

```bash
cd myls
```
Compile the Code: Use make to build the project. Ensure you have gcc and make installed.

```bash
make
```
This will generate the myls executable.
## Usage
Run the myls command with various options to customize the output:

```bash
./myls [options] [path]
```
If no path is provided, myls defaults to the current directory.

## Options
`-a`: Include hidden files (those starting with a dot).\
`-d`: List directories themselves, not their contents.<br/>
`-i`: Print the index number (inode) of each file.
`-l`: Use a long listing format, which includes detailed file information.
`-1`: List one file per line.
`-t`: Sort files by modification time.
`-u`: Sort files by last access time.
`-c`: Sort files by creation time (if supported).
`-f`: Do not sort; list entries as they appear.
`-h`: Show the help message and exit.

## Source Files
The MYLS project consists of several source files:

MYLS.c: The main program file that handles command-line arguments and executes appropriate listing functions.
list.c: Contains functions to list files in different formats.
list_all.c: Lists all files in the directory.
list_inode.c: Lists files with their inode numbers.
list_long.c: Lists files in long format.
list_single_column.c: Lists files in a single column.
list_time.c: Lists files sorted by modification time.
list_unsorted.c: Lists files in the order they appear.
sorting.c: Implements sorting functions, including case-insensitive comparison for directory entries.
utils.c: Contains utility functions such as converting strings to lowercase and comparing entries.

## Functionality

## Listing Formats

     Long Format (-l): Provides detailed information about each file, including permissions, number of links, owner, group, size, and modification time.
     Single Column (-1): Displays one file per line, making it easier to read long lists of files.
     Unsorted (-f): Displays files in the order they appear in the directory, without sorting.

## Sorting Options

    By Name: Default sorting by file name, case-insensitive.
    By Modification Time (-t): Sorts files by their last modification time, with the most recently modified files appearing first.
    By Access Time (-u): Sorts files by their last access time.
    By Creation Time (-c): Sorts files by their creation time (if supported by the file system).

## Color Output
     The MYLS implementation supports colorized output to differentiate between file types. Colors are enabled by default when outputting to a terminal. The color settings are 
     managed in color.c, which includes functions to determine the appropriate color based on file type and print file names in color.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.

## Acknowledgments
Special thanks to the open-source community for providing valuable resources and tools.
Thanks to the contributors and maintainers of the ls command and related Unix utilities, which served as the foundation for this project.
