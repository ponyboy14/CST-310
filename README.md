# CST-310

This is an OpenGL project done by Lucas Lasecla and Sammie Vaicius

This project is to show our understanding of openGL shaders and translations.

To run this program you must have:
    g++
    glut
    glu
    GL

Once those libraries are installed, in the terminal you will compile the program with the following command:
    g++ AShaders.cpp -o shaders -lGL -lGLU -lglut

After the program is compiled, you can run it with the following command:
    ./shaders

Once the program is running, you will move the camera with the following method:
    Right Arrow:			Slide camera 1 unit in the positive X direction 

    Left Arrow: 			Slide camera 1 unit in the negative X direction 

    Up Arrow:			    Slide camera 1 unit in the positive Y direction 

    Down Arrow:			    Slide camera 1 unit in the negative Y direction 

    Shift Up Arrow:		    Slide camera 1 unit in the positive Z ("in") direction 

    Shift Down Arrow:		Slide camera 1 unit in the negative Z ("out") direction 

    Control Down Arrow:		Change camera pitch by 2 degrees 

    Control Up Arrow:		Change camera pitch by -2 degrees 

    Control Right Arrow:	Change camera yaw by 2 degrees 

    Control Left Arrow:		Change camera yaw by -2 degrees 

    <:				        Change camera roll by 2 degrees 

    >:				        Change camera roll by -2 degrees 

    r:				        Reset to the default position and orientation 

To end the program, simply close the window