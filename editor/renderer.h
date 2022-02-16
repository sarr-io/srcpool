// Includes
#include <glad/glad.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <fstream>
#include <cstring>
#include <sstream>
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h> // (https://github.com/nothings/stb/blob/master/stb_truetype.h)
#define VERTEXT_IMPLEMENTATION
#include "vertext.h" // (thanks to Kevin Chin) if this didn't exsist I would probably cry

// Renderer
namespace Renderer {

    class Shader {

        private:

            // Read the shader's source code.
            std::string readFile(const char* _path);

            // Check the shader.
            bool checkShader(GLuint &_shader);

            // Check the program.
            bool checkProgram(GLuint &_program);

        public:

            const char* vertexPath;
            const char* fragmentPath;
            GLuint id;

            void Update(const char* _vertexPath, const char* _fragmentPath); // Update the shader's parameters.

            void Use() {  glUseProgram(id); } // Use the shader.

            void Delete() { glDeleteProgram(id); } // Delete the shader.

    };

    class Queue {

        public:

            GLuint VAO;

            void listObjects(); // List all objects in the queue (BY NAME, INDEX IS THE ID FOR ALL VALUES/PARAMETERS)
            GLuint getObject(std::string objName); // Grab an object from the queue (BY NAME, INDEX IS THE ID FOR ALL VALUES/PARAMETERS) [Returns the id of the object]
            bool findObject(std::string objName); // Returns true or false if the object is found.


            void Render(); // Render all objects in the queue. (Sets VAOs)

            std::vector<std::vector<GLfloat>> vertices;
            std::vector<std::vector<int>> indices;
            std::vector<std::vector<int>> vertexAttribs;

            std::vector<int> shaderProgramIDs;
            std::vector<std::string> names;

    };

    class Object {

        public:

            GLuint VBO, EBO;

            std::vector<GLfloat> vertices;
            std::vector<int> indices;
            std::vector<int> vertexAttribSizes; // This is the sizes of the vertex attributes, not the values.

            GLuint shaderProgramID;
            std::string name;

            // Set the object's parameters.
            void Update(
                std::vector<GLfloat> _vertices, 
                std::vector<GLuint> _indices, 
                int _shaderProgramID, 
                std::string _name,
                std::vector<int> _vertexAttribSizes
            );

            void Attach(Queue &queue);
            void Detach(Queue &queue);

    };
    
};