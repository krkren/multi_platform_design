---
layout: default
title: Release of KiriKiriZ Android Version
---

The Android version is split into development and packaging versions.
The development version is for Android 5.0 and later; it allows you to select a folder at startup and run the startup.tjs located there.
In contrast, the packaging version runs from startup.tjs or data.xp3 within the Assets.
Besides Assets, it can also be launched via Google Play Expansion Files or by downloading data (xp3) via HTTP from a specified server (planned).
Instead of downloading everything, it is also possible to keep data that rarely changes, such as font data, in Assets while downloading other data (planned).
Switching between development and packaging versions is done using the Product Flavor feature in Android Studio.
The official release is fine for development, but if you need to add plugins, you must build the APK yourself.
The packaging version is used when releasing the game.
The development version is named "develop" and the packaging version is named "product".

## Changing the Application (Game) Name
Change the app_name element in the following two XML files.
By default, it contains "GameName", so change it to the name of the game you are releasing.
krkrz/android/app/src/product/res/values/strings.xml (English)
krkrz/android/app/src/product/res/values-ja/strings.xml (Japanese)

## Changing the Icon
Place a file named ic_launcher.png in the mipmap-xxx directories under krkrz/android/app/src/product/res/.
Place the icons with the following sizes:
* mipmap-mdpi : 48x48
* mipmap-hdpi : 72x72
* mipmap-xhdpi : 96x96
* mipmap-xxhdpi : 144x144
* mipmap-xxxhdpi : 192x192

## Version Number
Two values are required: a human-readable version name and an automatically processed version code.
The version code is incremented by 1 for each release and is used by Android devices to detect updates and perform automatic updates (or update notifications).
Release with 1 initially.
The version name is text.
Release as 1.0.0, etc.
How you increment it is optional.
The version name corresponds to the versionName field, and the version code corresponds to the versionCode field.
Update android { productFlavors { product { versionCode/versionName } } } in krkrz/android/app/build.gradle.
By default, they are set to 1 and '1.0.0' respectively.
It is fine to leave them as is for the initial release.

## Package Name
You must provide a package name for the APK that is unique within Google Play.
The same applies to other stores.
Following Java package naming conventions, it is generally formatted as the domain name reversed followed by the app name, separated by dots.
Use a domain name you own to avoid duplicates.
Update android { productFlavors { product { applicationId } } } in krkrz/android/app/build.gradle.
By default, it is 'com.domain.productname', so change it to your domain name + app name.

## Placement of data.xp3
Place it in the krkrz/android/app/src/product/assets folder.
Placing it here will include it in the APK.

## Adding Plugins
Refer to [Using Plugins in the Android Version](https://krkrz.github.io/android_plugins/).
Do not place them inside the xp3 file; their location is fixed so they are included in the APK.