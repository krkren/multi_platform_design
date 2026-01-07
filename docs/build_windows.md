---
layout: default
title: How to build on Windows
---

Currently, there are no changes from the previous method (there is a possibility of switching to generating vcxproj/sln files from CMake in the future).  
Simply open tvpwin32.sln in the vcproj folder and build with tvpwin32 selected in the Solution Explorer.  
However, since a normal build does not generate ANGLE DLLs, you need to build each DLL with ANGLE/libEGL and ANGLE/libGLESv2 selected.  
Basically, rebuilding the ANGLE DLLs is not necessary.  
Please use the distributed DLLs as they are.