# Multithreaded Mandelbrot written in C++

## TODO:

- [x] Take out bmp class and replace with arrays
- [ ] Add zooming and panning functionality to mandelbrot math
- [x] Update mandelbrot math and data structures so they can be used in parallel
- [ ] Add parallel functionality to mandelbrot class
- [ ] Generate AVX2 instructions for mandelbrot class
- [ ] Add testing to see speed ups

**Optional:**

- [ ] Add SFML window to see mandelbrot in real time
- [ ] Generate partial images first to see where we need to perform calcs
- [ ] Test some kind of caching system
- [ ] Pipeline Mandelbrot generation for smoother/higher frame rates

## Pipelining ideas

Introduce a pipeline and cache for zooming in and out.

Previous frame (cached) > Current frame (next to be cached) > Interpolated frame > Next Frame
