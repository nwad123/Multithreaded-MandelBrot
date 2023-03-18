# Multithreaded Mandelbrot written in C++

## TODO:

- [x] Take out bmp class and replace with arrays
- [ ] Add zooming and panning functionality to mandelbrot math
- [x] Update mandelbrot math and data structures so they can be used in parallel
- [x] Add parallel functionality to mandelbrot class
- [ ] Generate AVX2 instructions for mandelbrot class
- [ ] Add testing to see speed ups, maybe use `std::chrono::high_resolution_clock` as suggested [here](https://stackoverflow.com/questions/21856025/getting-an-accurate-execution-time-in-c-micro-seconds)

**Optional:**

- [ ] Add SFML window to see mandelbrot in real time
- [ ] Generate partial images first to see where we need to perform calcs
- [ ] Test some kind of caching system
- [ ] Pipeline Mandelbrot generation for smoother/higher frame rates

## Pipelining ideas

Introduce a pipeline and cache for zooming in and out.

Previous frame (cached) > Current frame (next to be cached) > Interpolated frame > Next Frame

## Multithreading ideas

An initial run through Vtune suggests that some cores are getting more heavily used than others. This makes sense as some sections of the mandelbrot require all 1000 iterations while other sections require only a few iterations.

Ideas to fix this:

1. Build a thread pool with a checkout system where each thread executes a row, then returns, then checks out another row, executes, returns, etc. This way each thread may be used more effectively.
2. Assigne each thread to the only doubles of their original position. E.g. thread 0 executes rows 0, 12, 24, 36, 48, etc. This way the rows would be more evenly spread between threads, so they should execute at normal times. This would only provide a speed up for some zoom levels of the mandelbrot.
