#include "MinGL.h"
#include "Example.h"

void drawCube(const MinGL& minGL){
    // Draw a green cube
    const MinGLColor green{ 0.0f, 1.0f, 0.0f, 1.0f };
    int c0X = 300;
    int c0Y = 250;
    int c1X = c0X;
    int c1Y = c0Y + 100;
    minGL.drawLine(c0X, c0Y, c1X, c1Y, green);
    int c2X = c0X + 100;
    int c2Y = c0Y + 100;
    minGL.drawLine(c1X, c1Y, c2X, c2Y, green);
    int c3X = c0X + 100;
    int c3Y = c0Y;
    minGL.drawLine(c2X, c2Y, c3X, c3Y, green);
    minGL.drawLine(c3X, c3Y, c0X, c0Y, green);
    int c4X = c1X + 50;
    int c4Y = c1Y + 50;
    minGL.drawLine(c1X, c1Y, c4X, c4Y, green);
    int c5X = c4X + 100;
    int c5Y = c4Y;
    minGL.drawLine(c4X, c4Y, c5X, c5Y, green);
    minGL.drawLine(c2X, c2Y, c5X, c5Y, green);
    int c6X = c3X + 50;
    int c6Y = c3Y + 50;
    minGL.drawLine(c3X, c3Y, c6X, c6Y, green);
    minGL.drawLine(c5X, c5Y, c6X, c6Y, green);
}

void drawShapes(const MinGL& minGL){

    // declare color variable
    const MinGLColor green{ 0.0f, 1.0f, 0.0f, 1.0f };

    // draw a circle
    // takes the center of circle and radius as parameters
    // if (x, y) is then center of circle and rad is the radius->
    // drawCircle(x, y, rad, color)
    minGL.drawCircle(400, 300, 100, green);

    // draw a rectangle
    // takes two endpoints of a diagonal of rectangle and color as parameters
    // if(x1,y1) and (x2,y2) are endpoints of one of the diagonals->
    // drawRectangle(x1, y1, x2, y2, color)
    minGL.drawRectangle(300, 200, 500, 400, green);

    // draw lines
    // takes the endpoints of line as parameters
    // if (x1, y1) and (x2, y2) are the endpoints of the line->
    // drawline(x1, y1, x2, y2, color)
    minGL.drawLine(400, 150, 400, 450, green);
    minGL.drawLine(250, 300, 550, 300, green); 
}
