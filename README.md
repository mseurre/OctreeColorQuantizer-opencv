# OctreeColorQuantizer-opencv
Color quantization of images using octrees (implemented in C++ with OpenCV)

### Implementation details
This implementation:
- relies on morton codes to compute indexes of colors inside the tree (bit manipulation involved),
- is based on recursivity for inserting and getting colors inside the tree,
- does not modify the tree when creating the quantized palette (its size can be changed without having to re-compute the tree),
- can quantize an image that was not used to generate the tree (ex : a similar image)
