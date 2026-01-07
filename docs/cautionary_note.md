---
layout: default
title: KiriKiri Z Multi-platform Version Development/Porting Notes
---

Describes parts of the functions changed or added from the conventional KiriKiri Z that require attention.

## File Name Case Sensitivity
Previously, there was no need to pay special attention to uppercase and lowercase in file names, but since the Android file system is case-sensitive, it is affected depending on where the files are placed.
Files archived in XP3 remain case-insensitive as before.
Others are case-sensitive.
Plugin files, save data file names, and video file names (currently specified to be placed in Assets) require special attention.
When checking operation by specifying a folder on Android without archiving, all files are affected by this.
To avoid problems such as storage locations in operation, it is safer to use all lowercase file names.
If you only execute XP3 archived files on Android, no special attention is required except for the three types of files mentioned above.

## On Android, only one Window is allowed and full screen is assumed
Only one Window can be created on Android.
Also, it is assumed to be full screen.
Modal windows cannot be used either.

## When adding a menu
Windows traditionally has a menu at the top, but on Android, when displaying by swiping in, the left side is the only option because other sides are used by the system.

## Drawing using hardware
### Draw within Window.onDraw
Since hardware-based drawing involves pre-drawing settings and post-drawing flips (swaps), drawing Canvas methods can only be called within onDraw. Note that calling them elsewhere will result in unintended consequences.
In conventional systems like KAG3, drawing was performed immediately when a tag was called, but in hardware-based drawing, only state changes should be made, and the actual drawing must be performed within onDraw.

### Internally inverted vertical coordinate system
Since it is implemented in OpenGL ES 2.0/3.0, it is internally vertically inverted (origin at the bottom left).
The default shader uses the vertex shader's ortho matrix to convert to the top-left origin.
Note that textures drawn using the Offscreen class will be flipped if a vertically inverted vertex shader is used.

### Device-dependent issues
In the Windows version, compatibility is considered quite high (only presence of support) because the shader compiler (HLSL) is made by MS via ANGLE. However, on Android, the shader compiler (GLSL) is a driver implementation, so behavior may differ for each GPU (each driver), requiring caution.
Also, on Android, driver fixes may not be applied unless the OS version is updated, and since some devices are not updated, there are devices where bugs remain.
Regarding GLSL, thorough testing on Android is necessary.
The [GLSL Device Dependency Issues](http://dench.flatlib.jp/opengl/glsl) page should be read first and checked occasionally.

## Deprecation of DrawDevice
DrawDevice has been deprecated in the Android version, so if you were creating your own DrawDevice, changes will be required.
It is recommended to rewrite to a drawing system using hardware.
If you prioritize compatibility only with the Windows version and do not use the newly added drawing system, it is possible to continue using DrawDevice.
However, since there is a high possibility of future deprecation, early migration is recommended.