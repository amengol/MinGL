

MinGL
==========

MinGL (Minimal Graphics Library) es una pequeña clase de renderizado gráfico construida sobre OpenGL. Su función principal es `MinGL::putPixel()`, que recibe las coordenadas x/y y un color para dibujar un solo píxel en la pantalla.  

La idea es servir como la API gráfica más básica para probar conceptos y algoritmos de gráficos por computadora, como dibujo de líneas, rasterización de triángulos, proyección en perspectiva, etc., sin necesidad de lidiar con estados y llamadas de API complicados. Sin una API gráfica, estos conceptos suelen probarse utilizando imágenes estáticas renderizadas en disco, pero con MinGL puedes ver los resultados de inmediato.

Nota: Dado que el ray-tracing es muy demandante, es mejor escribir una imagen en disco en esos casos.

## Captura de pantalla

![captura de pantalla de un cubo renderizado con el programa de ejemplo](/Example/MinGL_drawCube_Example.PNG?raw=true)

La imagen anterior se dibujó utilizando la función `drawLine()` de MinGL basada en el [Algoritmo de línea de Bresenham](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)  
El algoritmo de línea de Bresenham utilizado en la función drawCube() del [ejemplo](Example/Main.cpp) se basa en https://github.com/ssloy/tinyrenderer/wiki

![captura de pantalla de un objetivo renderizado con el programa ShapeSample](/Example/MinGL_drawShapes_Example.png?raw=true)

La imagen anterior se dibujó utilizando las funciones `drawLine()`, `drawRectangle()` y `drawCircle()` de MinGL, el código se puede encontrar en la función drawShapes() de [Example.cpp](Example/Example.cpp)

La función `drawLine()` se basa en el [Algoritmo de línea de Bresenham](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm) 

La función `drawRectangle()` utiliza la función `drawLine()` mencionada anteriormente

La función `drawCircle()` se basa en el [Algoritmo de dibujo de círculos de Bresenham](https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/)

Uso
=====

MinGL depende de [glad](https://glad.dav1d.de/) y [GLFW](https://www.glfw.org/) para funcionar. A continuación se muestra un ejemplo de cómo podrían organizarse los archivos:

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

Nota:

- Si intentas ejecutar el ejemplo, no olvides enlazar los binarios de glfw2: https://www.glfw.org/download. 

- Asegúrate de incluir los archivos necesarios y enlazar las bibliotecas. 

    Si estás usando `g++` para compilar, puedes usar el siguiente comando para compilar `Main.cpp`.

    ```sh
    g++ -std=c++14 -I./ -IExample Example/Main.cpp glad/glad.c MinGL.cpp Example/Example.cpp -lglfw -o Main
    ```

    Si deseas compilar tu propio archivo y no incluir el código de ejemplo, usa lo siguiente
    ```sh
    g++ -std=c++14 -I./ <filename>.cpp glad/glad.c MinGL.cpp -lglfw -o <output filename>
    ```

- Usa **C++ 14** o superior


## Licencia
MinGL está licenciado bajo [Licencia MIT](LICENSE)
- glad está licenciado bajo [Licencia MIT](https://github.com/Dav1dde/glad/blob/master/LICENSE)
- GLFW está licenciado bajo [licencia zlib](https://github.com/glfw/glfw/blob/master/LICENSE.md)
