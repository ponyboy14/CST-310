# CST-310

This is an OpenGL project done by Lucas Lasecla and Sammie Vaicius

To run this program you must have:
    g++
    glut
    glew
    glu
    GL

Once those libraries are installed, in the terminal you will compile the program with the following command:
    g++ scene.cpp Mesh.cpp shader.cpp Texture.cpp stb_image.c -o scene -lGL -lglfw -lGLEW -lSOIL -lglut -lGLU

After the program is compiled, you can run it with the following command:
    ./scene

Once the program is running, you will traverse the scene with the following methods:
    UP ARROW : Move forward in the direction you are looking
    DOWN ARROW : Move backward in the direction you are looking
    LEFT CLICK + DRAG: Look around on the x - axis

To end the program, simply close the window