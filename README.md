# 2D Image Convolution
A simple software implementation to demonstrate image convolution in C.

## Desc
The convolve_base() function uses a sliding window buffer to insure each pixel is read once to reduce overhead. The kernel buffer (i.e. window buffer) stores the pixels to be multiplied & summed with the kernel. The line buffer has two pixel queues that feed the kernel buffer. The result of the operation is shifted and clipped depending on the kernel.
