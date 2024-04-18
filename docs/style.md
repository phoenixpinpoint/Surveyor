# Surveyor Style Guide
Date: April 10 2024
Version: 1.0

## File Header Template
```c
/** @file filename
 * 
 * @brief A description of the file/module’s purpose. 
 *
 * Copyright (C) 2024 Diamond Grade Labs.
 * This file is part of the Surveyor C package manager software. 
 * This software is part of the GNU GPL 3.0 License. 
 */ 
```

## Header Template
```c
<file header template redacted>
#ifndef FILENAME_H
#define FILENAME_H

//Build Path Header Includes
//ie #include <stdlib.h>

//Local Headers
//ie #include "somefile.h"

//Variables and Data Structures

//Function Prototypes

#endif
```

## Comments
```c
//Single or double line comments
//

/** 3+ Line Comments
* Use the multiline comment format
* Like this.
*/
```

## Variables, Structs, and Functions
```c
//local scope variables
int someInteger = 0;

//global/static variables
static int sSomeGlobalInteger = 0;

//structs
struct SomeStructure;

//Typedef Structs
typedef struct SomeStructure {
    //Some Struct Members
} SomeStructure_t

//General Functions
void some_general_function()
{
    // Some Function Text
}

//Internal Only Functions
void prv_some_internal_function()
{
    //Some internal only function. 
}
```
