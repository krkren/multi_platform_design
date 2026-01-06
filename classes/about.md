# KirikiriZ Multiplatform Edition API Reference
This is the KirikiriZ Multiplatform Edition API Reference.

# About the Multiplatform Edition
This version is designed to run on Android in addition to Windows.
GPU rendering is the main focus to achieve drawing speed even in less powerful environments.
Currently, it is partially incompatible with older versions.

# Environment-Dependent Features
Not all methods and properties in the multiplatform edition can be used in all environments.
Some features are environment-specific.
Environment-specific methods, etc., are marked with [Windows] or [Android] at the beginning of the description summary.
Methods, etc., marked in this way can only be used in that environment.
Some may do nothing when called, while others may throw exceptions.
For details, please refer to the following end symbols:

* [Windows+] Usable only in Windows; prohibited in other environments due to exceptions or undefined behavior.
* [Windows*] Usable in Windows; does nothing in other environments.
* [Windows] Usable in Windows; behavior undefined in other environments.
* [Android+] Usable only in Android; prohibited in other environments due to exceptions or undefined behavior.
* [Android*] Usable in Android; does nothing in other environments.
* [Android] Usable in Android; behavior undefined in other environments.

You can dynamically determine which environment you are in by using the System.isWindows and System.isAndroid properties.
To determine statically, use the preprocessor.
"windows" is set to 1 on Windows, and "android" is set to 1 on Android.
When determining statically, be aware that the bytecode output depends on the environment.
Bytecode for the compiled environment is output.
To avoid this, change the value of the preprocessor in advance before calling the compile function to make it suitable for each environment before converting it to bytecode.
