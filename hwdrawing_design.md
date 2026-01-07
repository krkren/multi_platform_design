# Hardware Drawing Design
## XXWindow
* Provides the base screen
* Transition functionality between front/back buffers
* Touch and mouse interfaces are managed entirely here.
  From the layer level onwards, it only needs an interface to determine if an object exists at specified coordinates (event propagation is not required).
* Screen capture at any position of overlapping Surface rendering

## XXSurface
### Base class for 3D components
* Plane specification for transitions (Front/Back/Both)
* Display ON/OFF
* Order specification
* Should render texture related processing go here?
  Color processing after capture/render, blend mode specification, opacity specification

## XXMeth extends XXSurface
If preparing 3D mesh rendering, handle it at this layer?

## XXNanoVGLayer extends XXSurface
If viewed as a rendering layer equivalent to a 2D layer, is it this layer?

## XXLayer extends XXSurface
### Mechanism providing basic 2D rendering processing
* Drawing clipping functionality
* Affine transformation for the entire drawing - This is a crucial element for ADV projects and UI production effects.
* Holds and manages resources required by child XXLayerObjects

## XXLayerObject
### Base class for 2D rendering elements that can be simply placed on XXLayer
* Display order and placement offset on XXLayer can be specified commonly
* Image transformation (scale/rotate), blend mode, opacity, etc.
* Note: Whether these are actually supported depends on the object.
  In E-mote, blend modes change for each drawing part.

## XXPicture extends XXLayerObject
* Image display
* Crop and display an arbitrary area from a specified image
* Ideally, KiriKiri LTO can be rendered directly here

## XXNanoVGPicture extens XXLayerObject
* If 2D drawing is considered a type of image, this hierarchy is appropriate

## XXTextRender extends XXLayerObject
* For text rendering processing

## XXEmote extends XXLayerObject
* Displays E-mote data

# Overall Structure
Structurally: Window > Surface
              Layer(Surface) > LayerObj

This assumes a 3-layer structure.
While making Layer a "Surface that can be a parent of a Surface" and making LayerObj equivalent to Surface would allow for flexible nesting and higher versatility, in practice, this 3-layer structure is easier to understand and should not cause any particular issues.