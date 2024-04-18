# Surevyor 

Surveyor is a C dependency manager designed to make C packages more like npm for node. The goal is to be able to configure, install, and build a projects depedencies from either source, or even predefined packages stored in a repository. One of the core issues with C development compared to other languages like PHP, Perl, or JavaScript is the lack of package management. C developers tend to build solutions that already exists due to the desire to keep their projects simple or because including an external library can be difficult and introduce changes to the existing build tools.

## Bulid Types
> Note: Surveyor curriently only supports a monolithic build type out of the box as of version 0.2.0.

### Monolithic

Monolithic builds are the simplest and work best with most common clibs style imports. This build type takes all of the sources files in the project and creates a survey.c file which includes all of them. The first caveat is that all dependencies should be in a deps directory at the root of the project with the directory name being the dependency name. The second caveat is that the entire deps folder should be included in the compiler flags (ie. -Ideps for GCC). 

Example: 
For clibs/buffer the file structure would be 
(project directory)
----deps
-------buffer
-----------buffer.c

### Modular [Implementing in 0.4.0]

Modular builds take a more library-esque style approach. All dependencies are built into individual comilations which are then linked with the main project compilation at build time. This allows for the future watch feature to be implemented. Modular builds also allow users to reduce compilation time by reducing the amount of comilation per build. The main caveat is that building modules which can operate independently isn't possible out of the box if there are shared depedencies. 

## Surveys

Surveys come in two forms one is survey.json and the second is survey.c (root directory). The first is survey.json, this file is responsible for laying out the dependencies,their version, and even location. The second is survey.c, this file is responsible for mapping includes for the project. The survey.json and survey.c file should be built in such a ways as to allow the user to include survey.c in their main source file and have no depedencies (using the monotlithic build style).

### Legacy Surveys (clib.json)
There are two legacy "survey" types that Surveyor supports, clib.json and package.json. These are only for clib based projects and limit what additional features can be used. 

Basic clibs.json example.
```json
{
  "name": "",
  "version": "",
  "repo": "",
  "install": "",
  "makefile": "",
  "license": "",
  "src": [],
  "keywords": [],
  "dependencies": {},
  "development": {
    
  }
}
```

[clib.json]


### Survey.json (v1.0) [Implementing in 0.3.0]
Survey.json allows users to specify which version of survey.json they are using as well as dependency type and location.
```json
{
  "surveyVersion": "1.0",
  "name": "",
  "version": "",
  "repo": "",
  "install": "",
  "makefile": "",
  "license": "",
  "src": [],
  "keywords": [],
  "dependencies": {
    "<some/Dependency>": 
        {
          "name": "",
          "version": "",
          "type": "[clib:surveyor]",
          "location": "[url if surveyor package]"
        } 
  },
  "development": {
    
  }
}
```

[//]:

[clib.json]: <https://github.com/clibs/clib/wiki/Explanation-of-clib.json>
