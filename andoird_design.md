# Android tasks and restrictions, etc.
## NEON support
Convert the SSE2 part of the graphics-related code to NEON.
Software rendering is not essential, so it's okay to address this later.
Consider using [libsimdpp](https://github.com/p12tic/libsimdpp) or similar to abstract and reduce CPU dependency.
If you don't understand the available instructions, you may not get much speed, but there is the advantage of being able to develop on a PC and bring it over as is.
If it's okay to be reasonably fast, it might be practical.

Automatic vectorization is surprisingly powerful, and when applied, it produces speeds close to those of hand-written code.
It may be better to aim for a generally faster approach by writing code that is easily automatically vectorized.

## Sound support OpenSL
If you want to have the same level of functionality as KiriKiri, you will need to implement it with OpenSL.

## Video support
Use Java to draw to an OpenGL texture. This is the method for H.264.
If you use C++, it will be OpenMAX, but it seems to be MPEG2.
If you have your own engine, use Theora.

## Window (Activity)
Since multiple windows are not supported, create a virtual Window class in a single window.

## Startup priority
Where to read startup.tjs from.
Specify in config.cf (formerly exe name + cf, but no need to change the name, so fixed) in assets.
If not specified, read from data.xp3 in assets.
If specified by Intent, that directory is read with priority, but Intent specification should not be possible in the release version.

## Prohibit subdirectories in assets
NDK can only read files directly under assets.
Java can access subdirectories, but reading via Java is not done because of concerns about overhead.
The problem of compressing assets is avoided with a custom releaser.
If reading is still slow, it may be necessary to consider copying to SD or cache before reading.
If you want to split the download instead of putting everything in the apk, you need to add a download function.
If you are considering Google Play distribution, you need to support expansion files.

## Resource loading
Various resources of Android apps are supposed to be read by Java.
It is better to put icons, strings, and license information in resources.
For strings, you need to access them from Java using reflection, or register them all to the C side with Java at startup.
Since the icon will probably not be touched from the C side, no action is taken.

## Data storage location
Files are stored in Activity::getFilesDir().
Temporary data is stored in Activity::getCacheDir().
The app data folder on external storage is the location obtained by Environment::getExternalFilesDir().
Environment::getExternalStorageDirectory() can get the root.
Alternatively, getprop "EXTERNAL_STORAGE_MOUNT" to get the location where the SD is mounted.
If you have key-value pairs, it is desirable to save them with SharedPreference. Is this where the option settings are?
For record-like data, it is desirable to save it in SQLite using ContentResolver, and it can also be shared between apps.
User options will be in SharedPreference, and save data will be in external storage by default.

## Plugins
Only V2Link and V2Unlink are supported (adding functions and classes, etc.).
Things that interact through special interfaces such as sound decoders are not supported.
It is necessary to consider what to do with the setting data that is in the resources in the Windows version.
IStream is specific to Windows, but it is necessary to define an interface and make it usable because it is needed.

# Requirements
* Permission confirmation dialog (implemented in Java from 6.0 onwards)
Previously, there was permission confirmation at the time of installation, but from 6.0 onwards, apps can do it at any time. Therefore, it is necessary to request confirmation yourself.
For games, it's probably storage, network, and vibration.
* Save on onPause
onPause comes when deactivated, but since there are cases where it is killed without any notification after going to the background, it is better to have autosave on onPause when deactivated.
Deactivation is not something that can be prevented by being careful, such as when a phone call comes in.
* Handling of file name case
The Android file system is case-sensitive, so consider what to do. I think it's only during development, so you can search every time if you can't find it.
Case-insensitive is planned.
If you can't find it due to case differences, search from the upper path each time (that is, searching is faster if everything is in lowercase).
However, it doesn't matter much if it's xp3.
* Global variable clearing problem
There is a problem that global variables are not cleared (reused) when the app is restarted on Android. When using NativeActivity, separate the so and load the main body every time at startup to ensure clearing every time. If you use a normal Activity, you don't have to worry about it because you load the so every time from Java.
* Push notifications (if necessary)
Push notifications require a separate server to be prepared. It is not always necessary for distribution, but a server is needed to register the notification destination ID. The notification destination ID is like an email address.
It is unclear whether Google's push notifications are OK for adult content. Amazon's services may be necessary.
* DRM
DRM is different for each store, so you need to prepare each one. Implemented in Java.
If you register with Amazon, it is not necessary and the store will do it automatically.
* Character input
Since it is a software keyboard and direct input is difficult, input will be in a dialog.
* Update acquisition by RSS, etc.
If push notifications are not possible, periodically read RSS etc. at some timing to get update information. Once a day when unlocking, or a timer? It is more reliable to trigger some event than a timer.
* Touch, rotation operation
Since the Windows version has already been implemented from Z, implement the same thing on Android.

# Things not implemented or requiring consideration
* Mouse input, gamepad input
It would be better to have it, but it's okay if you don't have it if you mainly use smartphones and tablets. Future implementation item.
* Video has function restrictions
Segment loops and periods may be difficult.
* Abolish Shift-JIS, unify to UTF-8
Since we have conversion functions such as SJISToUnicodeString brought from KiriKiri 3 internally, Shift-JIS support is possible if we unify to that.
If it is not absolutely necessary, it will be easier to unify to UTF-8 later.
* wchar_t byte size problem
In Linux systems, wchar_t is 4 bytes, so problems may occur in places where 2 bytes are assumed.
It is safe to have your own string processing functions and process them with a fixed 2 bytes, but it takes a little effort.
Some functions are implemented by ourselves.
String processing also has the benefit of SIMD, so it may be a good idea to make it yourself with a view to speeding it up.
Since Bionic libc is published as a BSD license as a standard Android library, you can add it and rewrite wchar_t as tjs_char 2 bytes.
char16_t is planned to be used as the internal character code, and various string processing methods will be brought from Bionic libc.
* path delimiter
Windows uses \, but Linux systems use /, so make it so that the difference is absorbed well.
It is desirable to use / as the basis and not use \ except internally.
* Normalize the upper limit inversion of bitmap to forward order
Bitmaps used in Android are in forward order.
OpenGL/DirectX can easily invert during drawing, so it doesn't matter much either way.
There should be no problem in changing it, but there was a problem with the built-in DrawDevice, so it seems that plugins etc. will also be affected.
* Read into Intent
A function that considers the transfer of various data from other apps by Intent at startup or during startup.
In the Windows version, it is transferred via the clipboard, etc., but in Android it is Intent.
It's okay to only support startup folder specification at the beginning, but it would be better to have it in the future.
* Command line arguments are not read
* -printdatapath is invalid, it is desirable to be able to get it with ContentResolver or Intent.
* -about license information display etc. is invalid, a method to call and display it from the game is essential.

# Device-dependent problems, etc.
[GLSL device-dependent problems](http://dench.flatlib.jp/opengl/glsl)

# Tools etc.
* Android releaser
A tool that replaces only the icon, title, package name, archive, and signature.
Make it possible to release without building every time.
With normal build tools, everything in assets is compressed (apk file is a zip file), but the releaser is necessary considering that you want to specify the compression rate, no compression, etc. when placing data.xp3 etc.
I have a signature/packaging tool that I made in C# before, so it won't take much man-hours if I add to it.

# Development environment
Android Studio, which makes it easy to develop in Java, is easy to use because Java development is also necessary, but C++ is still not usable properly.
It would be nice if Visual Studio (+nVIDIA AndroidWorks) could be used for C++.
It is efficient to debug options to turn ON/OFF functions and build from the command line.
There may be requests to suppress the binary size by turning OFF unnecessary functions in the mobile environment.
It is easier to handle if the plugin is also built into the main body.

# Memo
It might be good for doujin circles to be able to insert ads and interstitials at any timing.
Banner ads narrow the screen and seem to be in the way at the bottom and are unlikely to be tapped.
If you can insert interstitials, it seems that you can effectively earn advertising revenue by inserting them at scene transitions?