---
layout: default
title: ShaderProgram Class
---

In the multi-platform version, the ShaderProgram class has been added.
On Android, rendering is performed using OpenGL ES 2.0/3.0. On Windows, it is performed using OpenGL ES 3.0 via ANGLE with a DirectX 11 backend.
Because of this, shaders are unified using GLSL.

In the multi-platform version's hardware-based rendering functionality, the number of internal shaders is kept to a minimum for development efficiency and extensibility. Similar to TJS2 scripts, shader scripts are loaded externally to allow for more diverse rendering.

The default blend modes provided are only those that can be implemented with built-in functions. Many of the blending methods available in KiriKiri 2/Z Layers must be implemented via shaders.
Since these shaders are provided as separate scripts, they can be used via drawing commands that take a texture and a shader as arguments.
Transitions can also be implemented in the same way.
Specifically, a crossfade can be achieved using two textures and a shader.
By specifying a render target, the drawing destination can be set to a texture, and this texture can then be used to implement the crossfade.
Universal transitions can be achieved using three textures and a shader.
Furthermore, while built-in scaling interpolation only supports Nearest Neighbor and Bilinear, Lanczos or Bicubic can be implemented via scripts using shaders.

## Internal Details
The ShaderProgram class stores compiled and linked Vertex/Fragment shaders.
Compilation and linking are executed in the constructor. If an error occurs, an exception is thrown, so check the log for corrections.
Parameters used for shader input are added as members by leveraging the dynamic language characteristics of TJS2, allowing values to be set via these members (Uniforms only).
Variable names described in the shader program are retrieved using reflection.
Specifications for things like Texture must be made using predefined reserved words.
Attribute values, which serve as vertex information, cannot be set via members; they must be set using reserved words or via a separate Mesh2D class (planned).
Member functions and properties that originally exist in the ShaderProgram class cannot be used as input variable names within the shader (for this reason, only a minimum number of members are currently added).

When values are set to properties added as input names defined in the shader, those values are applied during rendering.
Added properties are write-only; they cannot be read (this is a limitation due to implementation man-hours and may be relaxed in the future).
Values are retained, so when using the same shader, you must change the values to the desired ones before drawing.
Property types are retrieved from the shader script.
Types like vec4 are passed to the Array class as an array of real types.
While structures and arrays can be used in shaders, they are currently not supported (this is a limitation due to implementation man-hours and may be relaxed in the future).

Reserved words are automatically set internally during drawing execution, so there is no need to set them explicitly.
ex. The first texture id is passed to s_tex0.
The values set automatically depend on the drawing command (manuals will be prepared sequentially).

## Usefulness
If shaders can be specified from scripts and swapped freely, it is predicted that new visual effects can be added using only TJS2 scripts faster than traditional CPU processing, without having to write plugins to extend Layer functionality.
While Layer-equivalent functionality does not exist currently, if the peripheral functions necessary to implement Layer/Sprite etc. in TJS2 scripts are enhanced, those parts can be written in scripts, reducing the need for native (C++) plugins compared to before.
On Android, where binaries must be prepared for multiple CPUs, the ability to extend functionality via scripts also helps reduce APK size.
It is also advantageous for multi-platform development.
By distributing a set consisting of a shader and a TJS2 script that handles things like Sprites using that shader, visual effects can be enhanced.