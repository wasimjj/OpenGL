#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        std::cout << "there is error";
    }
    glfwSwapInterval(1);
    std::cout << glGetString(GL_VERSION)<<std::endl;
    {
        float positions[] =
        {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f

        };
        unsigned int  indices[] =
        {
            0,1,2,
            2,3,0

        };


        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb,layout);

        IndexBuffer ib(indices, 6);


        Shader shader("res/shaders/solidcolor.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);
        unsigned int uniform = shader.GetUniformLocation("u_Color");
        
        float red = 1;
        float increment = .05;

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();
        Renderer renderer;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();
            shader.Bind();
            shader.SetUniform4f("u_Color", red, 1.0f, 0.0f, 1.0f);

            renderer.Draw(va, ib, shader);
           // CHECK_ERROR(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
            if (red > 1)
            {
                increment = -.05;
            }
            else if (red < 0)
            {
                increment = .05;
            }
            red += increment;
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}