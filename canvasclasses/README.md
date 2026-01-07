# Class relationships for hardware drawing

* 3D機能対応用.tjs
// For 3D functionality support.
// The class design has been slightly modified from the request due to implementation issues, etc.
// Things specified by texture IDs, etc., are class-ified to enable runtime error detection.
* Canvas.tjs
// In the request, drawing methods were to be added directly to the Window class, but this has been separated due to issues such as increased size.
* Matrix44.tjs
// Class-ified to make passing easier.
* Mesh2D.tjs
// The name Mesh class might conflict when supporting 3D, so 2D is added to the name.
// Since this class is for efficiency, the detailed information it holds will be considered during implementation.
* Offscreen.tjs
// In the request, it was screen ID, but Screen class is a bit confusing and the name might conflict, so the name is Offscreen.
* Texture.tjs
// Class-ify the texture. Load directly or from the Bitmap class.
* Window.tjs
// Window class with methods greatly reduced and some added.

## How to draw a Layer
// Added clearDirtyRect method and dirtyRect/isUpdated properties to the BitmapLayerTreeOwner class.
// Create a Layer class with BitmapLayerTreeOwner as the owner.
// If BitmapLayerTreeOwner.isUpdated is true at drawing time, the image has been updated, so transfer the image to the texture.
// The updated area is obtained with dirtyRect.
// The texture size should match the primary layer size (BitmapLayerTreeOwner.bitmap).
// In virtual code, the update rectangle can be transferred to the texture as follows:
```javascript
BitmapLayerTreeOwner lto;
Texture texture = new Texture( width, height );
texture.copyRect( lto.dirtyRect.left, lto.dirtyRect.top, lto.bitmap, lto.dirtyRect );
lto.clearDirtyRect();
```
// The Offscreen class also has a similar copy method, so it can be done in the same way, but it includes FBO etc. so that it can be set as a render target, resulting in memory overhead.
// If not using it as a render target, it is better to use the Texture class.
// For the purpose of drawing with Layers, there seems to be no need to use the Offscreen class.


## Regarding compatibility
// There is a request for a function to draw the Layer Tree on an Offscreen. Since it is possible to copy only the updated area, the Offscreen class should implement the Layer Tree Owner interface.
// If the Offscreen has the LTO interface, operation nearly compatible with the conventional one can be realized.
// The current LTO interface of the Window class is mostly provided by DrawDevice. When using the new hardware drawing instead of DrawDevice, if a Layer is created specifying a Window, an Offscreen class is generated internally and registered as the default Offscreen in Canvas. An OnDraw event is triggered by the Layer update notification, and the default Offscreen is drawn before Canvas drawing starts or after the OnDraw call, allowing Layers to be used as before.
// However, since DrawDevice will be removed, compatibility will be lost for parts that depend on DrawDevice or use a custom DrawDevice.

## TextureLayerTreeOwner
// This time, it is not necessary to create TextureLayerTreeOwner because partial updates can be handled by adding members to the BitmapLayerTreeOwner described above.
// TextureLayerTreeOwner is necessary to improve compatibility, so I want to create it in the future with an efficient implementation of asynchronous updates using PBO.
// In that case, it will be dedicated to OpenGL ES 3.0 or later, but that is not a big problem.

// If it is OpenGL ES 3.0 or later, PBO can be used, and the transfer from PBO to Texture is DMA processed, so the CPU load is light.
// Automatically transfer from PBO copy to Texture when the Layer is updated.
// Call the OnDraw event accordingly to reflect the drawing on the screen, resulting in the same operation as before.
// If updating every frame, transfer wait times can be eliminated by creating two PBO/Textures and using double buffering.

## Functions that can be realized indirectly
### Crossfade
```javascript
var crossfadeShader = new ShaderProgram( default.vert, crossfade.frag );
crossfadeShader.s_opacity = 0.0;
Canvas.drawTexture( prevTexture, nextTexture, crossfadeShader );
```
// Can be realized with a script like the one above.
// Gradually fade by changing the opacity of the shader.
// It is efficient to create only one shader, such as crossfadeShader, and keep holding it.

### Universal Transition
```javascript
var universalShader = new ShaderProgram( default.vert, universal.frag );
universalShader.s_vague = 64.0/255.0;
universalShader.s_phase = 0.0;
Canvas.drawTexture( prevTexture, nextTexture, ruleTexture, crossfadeShader );
```
// Can be realized with a script like the one above.
// Gradually fade by changing the phase of the shader.
// It is efficient to create only one shader, such as universalShader, and keep holding it.

### Alpha Clipping
```javascript
var alphaclipShader = new ShaderProgram( default.vert, alphaclip.frag );
Canvas.drawTexture( texture, clipAlpha, alphaclipShader );
```
// Can be realized with a script like the one above.
// It is efficient to create only one shader, such as alphaclipShader, and keep holding it.