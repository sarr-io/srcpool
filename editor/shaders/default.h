#include "glad/glad.h"
#include <iostream>

namespace defaultShader {

    // Variables
    unsigned int vertexShader;
    unsigned int fragmentShader;

    int success;
    char infoLog[512];

    // Functions
    void loadVertex(unsigned int& shaderProgram) {

        const GLchar* vertexSource = R"glsl(
            #version 150 core
            in vec2 position;
            void main()
            {
                gl_Position = vec4(position, 0.0, 1.0);
            }
        )glsl";

        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        glAttachShader(shaderProgram, vertexShader);
    }

    void loadFragment(unsigned int& shaderProgram) {

        const GLchar* fragmentSource = R"glsl(
            #version 150 core
            out vec4 outColor;
            void main()
            {
                outColor = vec4(1.0, 1.0, 1.0, 1.0);
            }
        )glsl";

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        glAttachShader(shaderProgram, fragmentShader);
    }

    void cleanup() {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

}