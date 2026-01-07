---
layout: default
title: Video Functions
---

On Android, video-related functions are currently significantly fewer compared to the Windows version.
First, the VideoOverlay object is limited to only one and is always displayed in the foreground.
For usable video formats, please refer to the [ExoPlayer page](https://google.github.io/ExoPlayer/supported-formats.html).
Since it depends on the device and version, H.264 is likely to be stable, but please be aware of licensing issues.
It is best to think of it as having functionality similar to early KiriKiri 2.

Regarding error notifications, they are reported via onStatusChanged as either a load error or a player error.

The currently supported methods and other items are as follows.

## Methods
* close
* open
* play
* stop
* pause
* rewind

## Properties
* audioVolume
* totalTime
* position

## Events
* onStatusChanged( stop/ready/play )