# Surveyor
A depedency file builder for C. 

Surveyor reads clibs.json of the root file, goes through the dependencies and grabs all the *.c files. 

It then builds a survey.c file to be included in your root compilation. 

# Use
```bash
./surveyor
```
Then include the survey.c file in your main C file.
```C
#include "survey.c"
```

# Building
```bash
make
```
