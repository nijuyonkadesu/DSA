#include <cstdlib>
#include<iostream>
#include<GLFW/glfw3.h>
#include<adder.h>

int main(){
    std::cout<<"This is makecake";
    std::cout<<add(8.8f, 0.7f);
    
    GLFWwindow *window;

    if(!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    
    window = glfwCreateWindow(300, 300, "Gears", NULL, NULL);
    if(!window){
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // main loop
    while(!glfwWindowShouldClose(window)){
        // swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
