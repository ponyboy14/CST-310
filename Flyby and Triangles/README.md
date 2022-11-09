# CST-310

This is an OpenGL project done by Lucas Lasecla and Sammie Vaicius

To run these programs you must have:
    g++
    glut
    glu

Once those libraries are installed, in the terminal you will compile the checkered triangle program with the following command:
    g++ CheckeredTriangles.cpp -o tri -lGL -lGLU -lglut

After the checkered triangles program is compiled, you can run it with the following command:
    ./tri

While the code is running, you can press the following buttons to perform various actions:
    'p' : Stop spinning
    'c' : Start spinning
    'u' : Move objects up
    'd' : Move objects down
    'l' : Move objects left
    'r' : Move object right
    '+' : Zoom in
    '-' : Zoom out

To end the program, simply close the window

To compile the Cube Fly By program, use the following command:
    g++ ColorCubeFlyby.cpp -o cube -lGL -lGLU -lglut

After the Cube Fly By program is compiled, you can run it with the following command:
    ./cube

While the code is running, you can press the following buttons to perform various actions:
    's' : Stop spinning
    'c' : Start spinning
    'u' : Move objects up
    'd' : Move objects down
    'r' : Rotates the image
    '+' : Zoom in
    '-' : Zoom out

    *NOTE*: Zoom in and zoom out only work when the image is not spinning. The other functions only work when the image is spinning.

To end the program, simply close the window