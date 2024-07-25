MinGL
==========

MinGL (Minimal Graphics Library) is a tiny graphics rendering class built on top of OpenGL. Its core function is `MinGL::putPixel()`, which receives the x/y coordinates and a color to draw a single pixel on the screen.  

The idea is to serve as the most basic graphics API to try computer graphics concepts and algorithms such as line drawing, triangle rasterization, perspective projection etc, without the need to deal with complicated API states and calls. Without a graphics API, such concepts are usually tested using still images rendered to disc, but with MinGL you can see the results immediately.

Note: Since ray-tracing is very demanding, you better of writing an image to disc in such cases.

## Screenshot

![screenshot of a cube rendered with the sample program](/Example/MinGL_Example.PNG?raw=true)

The above image was drawn using MinGL within a `DrawLine()` function based on [Bresenham’s Line Algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)  
Bresenham’s Line Algorithm used in the [example](Example/Main.cpp) code was based on https://github.com/ssloy/tinyrenderer/wiki

![screenshot of a target rendered with the ShapeSample program](/Example/MinGL_ShapesExample.png?raw=true)

The above image was drawn using MinGL functions `drawLine()`, `drawRectangle()`, and `drawCircle()` functions

`drawLine()` function is based on [Bresenham’s Line Algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm) 

`drawRectangle()` function utilises `drawLine()` function mentioned above

`drawCircle()` function is based on [Bresenham's Circle Drawing Algorithm](https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/)

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

Note:

- If you are trying to run the example, don't forget to link the glfw2 binaries: https://www.glfw.org/download. 

- On Linux you can add `-lGL` and `-lglfw` flags in command-line when compiling using **g++** to link the glfw binaries. Make sure to have the header files in your include path.

- Use **C++ 17** or higher


## License
MinGL is licensed under [MIT License](LICENSE)
- glad is licensed under [MIT License](https://github.com/Dav1dde/glad/blob/master/LICENSE)
- GLFW is licensed [zlib license](https://github.com/glfw/glfw/blob/master/LICENSE.md)
