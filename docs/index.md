---
layout: default
title: KiriKiri Z Ver.2
---

## About KiriKiri Z Ver.2

KiriKiri Z Ver.2 (Multi-platform version) is a version of KiriKiri Z that runs on Windows and Android.  
Currently, compatibility with the conventional Ver 1.X series of KiriKiri Z is somewhat low, but we plan to improve compatibility in the future so that migration can be done as-is, with some exceptions.  
In addition to conventional software rendering (Layer), hardware rendering (OpenGL ES 2.0/3.0) capabilities have been added.  
On Windows, brute-force processing is possible to some extent due to powerful CPUs, but performance issues are expected in underpowered Android environments.  
On Android, rewriting code to use hardware (GPU) as much as possible will ensure a smoother, stress-free play experience.  
Naturally, since the hardware (GPU) will also be used on Windows, it becomes possible to achieve more complex and diverse effects with lower CPU load than before.  
While it is not yet possible to migrate conventional scripts as they are, we recommend migrating to GPU rendering because rewriting for GPU-based drawing ensures comfortable operation on both Android and Windows.

## Download

* [Releases](https://github.com/krkrz/multi_platform_design/releases)

## Multi-platform Version API Reference

* [API Reference](./apiref/)

## Supported Platforms

### Windows
* Windows 7 or later
* DirectX 11 required

### Android
* Android 4.4 or later
* OpenGL ES 3.0 or later recommended (2.0 required)

## Repository

* [Main body is in the dev_multi_platform branch](https://github.com/krkrz/krkrz/tree/dev_multi_platform)
* [KAG Sigma (Sample implementation of new drawing API)](https://github.com/krkren/KAGSigma)

## Various Explanations Regarding the Multi-platform Version

* [How to release (build) the Android version](./develop_android.html)
* [How to build the Windows version](./build_windows.html)
* [Video playback function](./video_overlay.html)
* [How to create/use plugins](https://krkren.github.io/android_plugins/)
* [Sound](./audio.html)
* [How to use shaders](./shader_program.html)
* [Notes on porting](./cautionary_note.html)