#include <iostream>
#include <fstream>
#include <glad/glad.h>

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <simulation/sun.h>
#include <simulation/shell.h>

using namespace std; 

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void write_data(shell* shells) {
    ofstream fout;
    fout.open("data/data.csv");

    // write the headers
    if (fout.is_open()) {
        fout << "radius,xi,mass,luminosity,pressure,temperature,density,theta,y\n";
        for (int i = 0; i <= NUM_SHELLS - 1; i++) {
            fout << shells[i].radius << "," << shells[i].xi << "," << shells[i].mass << "," << shells[i].luminosity << "," << shells[i].pressure << "," << shells[i].temperature << "," << shells[i].density << "," << shells[i].theta << "," << shells[i].y << "\n";    
        }
        cout << "Data written to data/data.csv" << endl;
        fout.close();
    } else {
        cout << "Failed to open file for writing" << endl;
    }
}

int main()
{
    sun Sun = sun();
    Sun.simulate_eddington();

    shell* shells = Sun.get_shells();

    write_data(shells);

    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Solar Thermodynamics Simulation", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to open GLFW window" << endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();

    return 0;
}