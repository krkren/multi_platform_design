# ハードウェア描画用のクラス関係

// Class relationships for hardware drawing

* 3D機能対応用.tjs
// For 3D functionality support.
// The class design has been slightly modified due to implementation issues, etc., as requested.
// For things specified by texture id, etc., they are class-ified to enable runtime error detection, etc.
* Canvas.tjs
// In the request, drawing methods were to be added directly to the Window class, but this has been separated due to problems such as increased size.
* Matrix44.tjs
// Class-ified to make passing easier.
* Mesh2D.tjs
// The name Mesh class might conflict when supporting 3D, so 2D is added to the name.
// Since this class is for efficiency, we will proceed with considering the detailed information this class holds while implementing it.
* Offscreen.tjs
// In the request, it was screen id, but Screen class is a bit confusing and the name might conflict, so the name is Offscreen.
* Texture.tjs
// Class-ify the texture. Load directly or load from Bitmap class.
* Window.tjs
// Window class with methods greatly reduced and some added.

## Layerを描画する方法
// How to draw a Layer
// Added clearDirtyRect method, dirtyRect/isUpdated properties to BitmapLayerTreeOwner class.
// Generate Layer class with BitmapLayerTreeOwner class as owner.
// If BitmapLayerTreeOwner.isUpdated is true at drawing time, the image has been updated from before, so transfer the image to the texture.
// The updated area is obtained with dirtyRect.
// The texture size should match the primary layer size (BitmapLayerTreeOwner.bitmap).
// When written in virtual code, the update rectangle can be transferred to the texture by writing as follows.
```javascript
BitmapLayerTreeOwner lto;
Texture texture = new Texture( width, height );
texture.copyRect( lto.dirtyRect.left, lto.dirtyRect.top, lto.bitmap, lto.dirtyRect );
lto.clearDirtyRect();
```
// The Offscreen class also has a similar copy method, so it can be done in the same way, but it includes FBO etc. so that it can be set as a render target, so there is memory overhead.
// If you are not using it as a render target, it is better to use the Texture class.
// It seems that there is no need to use the Offscreen class for the purpose of drawing with Layer.


## 互換性に関して
// Regarding compatibility
// There is a request for a function to draw Layer Tree on Offscreen, and it is possible to copy only the updated area, so the Offscreen class should implement the Layer Tree Owner interface.
// If the Offscreen has the LTO interface, almost compatible operation can be realized with the conventional one.
// The current LTO interface of the Window class is almost provided by DrawDevice, but when the newly established hardware drawing is used instead of DrawDevice, when a Layer is generated specifying Window, the Offscreen class is generated internally and registered as the default Offscreen in Canvas, and from the notification of Layer update, an OnDraw event is generated, and the default Offscreen is drawn before starting drawing in Canvas, or it is drawn after calling OnDraw, so that Layer can be used in the same way as before.
// However, since DrawDevice will be gone, compatibility will be lost for parts that depend on DrawDevice or use a unique DrawDevice.

## TextureLayerTreeOwner
// This time, it is not necessary to create TextureLayerTreeOwner because partial updates can be handled by adding members to the BitmapLayerTreeOwner described above.
// TextureLayerTreeOwner is necessary to improve compatibility, so I want to create it in the future with an efficient implementation of asynchronous updates using PBO.
// In that case, it will be dedicated to OpenGL ES3.0 or later, but that is not a big problem.

// If it is OpenGL ES3.0 or later, PBO can be used, and the transfer from PBO to Texture is DMA processed, so the CPU load is light.
// Automatically transfer from PBO copy to Texture when Layer is updated.
// Call the OnDraw event accordingly to reflect the drawing on the screen, resulting in the same operation as before.
// If you update every frame, you can eliminate transfer waiting by creating two PBO/Textures and double buffering.

## 間接的に実現できる機能
// Functions that can be realized indirectly
### クロスフェード
// Cross fade
```javascript
var crossfadeShader = new ShaderProgram( default.vert, crossfade.frag );
crossfadeShader.s_opacity = 0.0;
Canvas.drawTexture( prevTexture, nextTexture, crossfadeShader );
```
// Can be realized with a script like.
// Gradually fade by changing the opacity of the shader.
// It is efficient to create only one shader such as crossfadeShader and keep holding it.

### ユニバーサルトランジション
// Universal transition
```javascript
var universalShader = new ShaderProgram( default.vert, universal.frag );
universalShader.s_vague = 64.0/255.0;
universalShader.s_phase = 0.0;
Canvas.drawTexture( prevTexture, nextTexture, ruleTexture, crossfadeShader );
```
// Can be realized with a script like.
// Gradually fade by changing the phase of the shader.
// It is efficient to create only one shader such as universalShader and keep holding it.

### アルファクリッピング
// Alpha clipping
```javascript
var alphaclipShader = new ShaderProgram( default.vert, alphaclip.frag );
Canvas.drawTexture( texture, clipAlpha, alphaclipShader );
```
// Can be realized with a script like.
// It is efficient to create only one shader such as alphaclipShader and keep holding it.