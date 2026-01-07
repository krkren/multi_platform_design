# Multi-platform Support

## Requirements
* Must be releasable on Windows and Android using a common system.
Excluding unavoidable specifications due to OS differences.
* Prioritize reducing man-hours over maintaining perfect compatibility.
Compatibility with legacy versions will be improved in the future.
* Focus on hardware-based rendering.
Focus on 2D rendering using 3D; legacy software-based rendering is not mandatory.
Ideally, both should be usable together in the future.
* Vector Rendering
Add vector rendering features to achieve resolution-independent UI, etc.
Assuming [NanoVG](https://github.com/memononen/nanovg)

### Windows
* Windows 7 or later only
* DirectX 11 required

### Android
* Android 4.4 or later only
* OpenGL ES 3.0 or later recommended (2.0 required; may be reconsidered)

See [Android Work Items and Limitations](andoird_design.md) for others.

### Hardware Rendering Design
See [Hardware Rendering Design](hwdrawing_design.md).

### Development Environment
Ideally, development would be completed within Visual Studio, but this is currently seen as difficult.
Build with Android Studio.

### Development Process
[Development Process](development_plan.md)

### Multi-platform Version Support
[KiriKiri Z Multi-platform Version Development/Porting Notes](https://krkrz.github.io/multi_platform_design/cautionary_note.html)

### Other Multi-platform Considerations
By creating stubs for platform-dependent parts and implementing (replacing) them with various libraries, development can proceed efficiently as it can be done to some extent on PC.
If the graphics part can be developed on PC using OpenGL (ES2), Android development efficiency will be significantly different, but the man-hours required to achieve this must be considered.
Stub creation is intended to make multi-platform deployment easier by implementing the contents, while implementation with various libraries is to ensure that dependent parts are properly separated. Additionally, since Android/MacOSX/Linux (other than Windows) have similar API systems, it is beneficial to implement them together.
The Windows version with replaced lower-level parts should also be usable as a feature-restricted development version limited to Android-equivalent features, while the current version that directly calls Win32 APIs will remain in use.

#### Considering the following libraries:

* POCO: Threads, environment info, etc. -> Threads will use C++11 features + pthread.
* PortAudio: Sound. Android OpenSL is not supported, so a separate implementation is required -> Implement per environment.
* GLFW: OS GUI. This part will be unique for Android, but OpenGL is common -> Implement per environment.
* Movies will be implemented natively.

Regarding Windows, only one can be created on Android; consider future alternatives using the Layer Tree Owner for hardware layer implementation of dialogs.