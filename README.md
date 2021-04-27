MinGL
==========

MinGL (Minimal Graphics Library) is a tiny graphics rendering class built on top of OpenGL. Its core function is `MinGL::putPixel()`, which receives the x/y coordinates and a color to draw a single pixel on the screen.  

The idea is to serve as the most basic graphics API to test Computer Graphics concepts and algorithms such as line drawing, triangle rasterization, perspective projection etc. Normally those things are tested using still images rendered to disc, but with MinGL you can see the results immediately.

Note: Since ray-tracing is very demanding, you better of writing an image to disc in such cases.

## Screenshot

![screenshot of a cube rendered with the sample program](/Example/MinGL_Example.PNG?raw=true)

The above image was drawn using MinGL within a `DrawLine()` function based on [Bresenham’s Line Algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)  
Bresenham’s Line Algorithm used in the [example](Example/Main.cpp) code was based on https://github.com/ssloy/tinyrenderer/wiki

Usage
=====

MinGL depends on [glad](https://glad.dav1d.de/) and [GLFW](https://www.glfw.org/) to work. Following is an example of how files could be organized:
```
Main.cpp
MinGL.h
MinGL.cpp
glad/khrplatform.h
glad/glad.h
glad/glad.c
GLFW/glfw3.h
GLFW/glfw3native.h
```

## License
MinGL is licensed under [MIT License](LICENSE)
- glad is licensed under [MIT License](https://github.com/Dav1dde/glad/blob/master/LICENSE)
- GLFW is licensed [zlib license](https://github.com/glfw/glfw/blob/master/LICENSE.md)
