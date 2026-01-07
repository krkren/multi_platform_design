---
layout: default
title: Audio Constraints for Android Version
---

Describes constraints arising from Android's OpenSL ES specifications that differ from the current KiriKiriZ Windows version constraints.  
While it is possible to eliminate (apparent) constraints by pre-converting via software, there are currently no plans to do so.

Specific constraints are as follows.

* 8-bit unsigned or 16-bit signed
(Playback of floating-point data is supported in Android 5.0 and later. There are no plans to implement this in the initial Android version.)

* Mono or Stereo
(The Windows version supports more channels, but the Android version does not.)

* Sample Rate
8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000Hz
(48000Hz is recommended. The recommended value depends on the device, but 48kHz seems common. Documentation states this helps reduce latency.)

* Simultaneous Playback Count: 32
(The documentation uses the term "object," so the actual limit might be slightly lower. Since it is shared with OpenMAX AL, videos are also included in this count. If mixing is done manually, this limit would not apply, but since it is not a very strict limit, the current plan is to keep it as is.)

Information regarding low latency can be found at [Audio output latency](https://googlesamples.github.io/android-audio-high-performance/guides/audio-output-latency.html).  
This involves using the device's optimal sampling rate and buffer size while constantly outputting silence to stay ready, but we will not go that far.