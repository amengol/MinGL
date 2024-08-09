MinGL
==========

MinGL (Minimal Graphics Library) is a tiny graphics rendering class built on top of OpenGL. Its core function is `MinGL::putPixel()`, which receives the x/y coordinates and a color to draw a single pixel on the screen.  

The idea is to serve as the most basic graphics API to try computer graphics concepts and algorithms such as line drawing, triangle rasterization, perspective projection etc, without the need to deal with complicated API states and calls. Without a graphics API, such concepts are usually tested using still images rendered to disc, but with MinGL you can see the results immediately.

Note: Since ray-tracing is very demanding, you better of writing an image to disc in such cases.

## Screenshot

![screenshot of a cube rendered with the sample program](/Example/MinGL_drawCube_Example.PNG?raw=true)

The above image was drawn using MinGL `drawLine()` function based on [Bresenham’s Line Algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)  
Bresenham’s Line Algorithm used in the [example](Example/Main.cpp)'s drawCube() function is based on https://github.com/ssloy/tinyrenderer/wiki

![screenshot of a target rendered with the ShapeSample program](/Example/MinGL_drawShapes_Example.png?raw=true)

The above image was drawn using MinGL functions `drawLine()`, `drawRectangle()`, and `drawCircle()`, the code can be found in [Example.cpp](Example/Example.cpp) drawShapes() function

`drawLine()` function is based on [Bresenham’s Line Algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm) 

`drawRectangle()` function utilises `drawLine()` function mentioned above

`drawCircle()` function is based on [Bresenham's Circle Drawing Algorithm](https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/)

Usage
=====

MinGL depends on [glad](https://glad.dav1d.de/) and [GLFW](https://www.glfw.org/) to work. Following is an example of how files could be organized:

```
.
├── Example
│   ├── Example.cpp
│   ├── Example.h
|   └── Main.cpp
├── glad
│   ├── glad.c
│   ├── glad.h
│   └── khrplatform.h
├── GLFW
│   ├── glfw3.h
│   └── glfw3native.h
├── MinGL.h
└── MinGL.cpp
```

Note:

- If you are trying to run the example, don't forget to link the glfw2 binaries: https://www.glfw.org/download. 

- Make sure to include the necessary files and link the libraries. 

    If you are using `g++` for compiling you can use the following command to compile `Main.cpp`.

    ```sh
    g++ -std=c++14 -I./ -IExample Example/Main.cpp glad/glad.c MinGL.cpp Example/Example.cpp -lglfw -o Main
    ```

    If you want to compile your own file and not include the example code, use the following
    ```sh
    g++ -std=c++14 -I./ <filename>.cpp glad/glad.c MinGL.cpp -lglfw -o <output filename>
    ```

- Use **C++ 14** or higher


## License
MinGL is licensed under [MIT License](LICENSE)
- glad is licensed under [MIT License](https://github.com/Dav1dde/glad/blob/master/LICENSE)
- GLFW is licensed [zlib license](https://github.com/glfw/glfw/blob/master/LICENSE.md)
