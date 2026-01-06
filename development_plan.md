# How to proceed with development

## Repository
Even if compatibility is not maintained, a complete branch will make maintenance difficult.

*   Manage everything in the repository
*   Divide parts that have large specification differences by "class"
    Since it seems difficult to coordinate with Android with the current Window class (+drawDevice) structure, prepare a new XXWindow (provisional name) class + (Surface something class group) and implement 3D related functions there.
*   Make it possible to rearrange by specifying which classes to include at build time
    Conventional Window class system installed
    Android compatible function added version XXWindow class system added
    Android compatible function limited version XXWindow class system only, Window class is cut
