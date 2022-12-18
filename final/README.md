# CST-310

This is an OpenGL project done by Lucas Lasecla and Sammie Vaicius

This project is to show our understanding of openGL texture mapping.

To run this program you must have:
    g++
    glfw
    GL
    assimp

If the above libraries are missing, you can download them with:
    g++:
        sudo apt install g++

    glfw:
        sudo apt-get install libglfw3
        sudo apt-get install libglfw3-dev

    GL:
        sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev

    assimp:
        sudo apt-get install libassimp-dev

Once those libraries are installed, in the terminal you will compile the program with the following command:
    g++ main.cpp glad.c khrplatform.h stb_image.h -o run -lGL -lglfw -lassimp -lGLU -lglut

After the program is compiled, you can run it with the following command:
    ./run

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