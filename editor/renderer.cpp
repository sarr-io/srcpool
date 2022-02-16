
// srcpool renderer

#include <renderer.h>

using namespace Renderer;

// List all objects in the queue.
void Queue::listObjects() {
    for (auto name : names) {
        std::cout << name << std::endl;
    }
}

// Returns true or false if the object is found.
bool Queue::findObject(std::string objName) {
    auto index = std::find(names.begin(), names.end(), objName);
    if (index != names.end()) {
        return true;
    } else {
        return false;
    }
}

// Returns the object id.
GLuint Queue::getObject(std::string objName) {
    auto index = std::find(names.begin(), names.end(), objName);
    if (findObject(objName)) {
        return index - names.begin();
    } else {
        return -1;
    }
}

// Renders all objects linked to the current queue.
void Queue::Render() {
    for (int i = 0; i < names.size(); i++) {
        glUseProgram(shaderProgramIDs[i]);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices[i].size(), GL_UNSIGNED_INT, 0);
    }
}

std::string Shader::readFile(const char* _path) {
    std::string content;
    std::ifstream fileStream(_path, std::ios::in);

    if (!fileStream.is_open()) {
        std::cerr << "Could not read file " << _path << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

bool Shader::checkShader(GLuint &_shader) {
    GLint success;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        GLint maxLength = 0;
        glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(_shader, maxLength, &maxLength, &errorLog[0]);

        std::cout << "Shader compilation failed: " << std::endl;
        std::cout << &errorLog[0] << std::endl;
        return false;
    }
    return true;
}

bool Shader::checkProgram(GLuint &_program) {
    GLint success;
    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if(!success) {
        GLint maxLength = 0;
        glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(_program, maxLength, &maxLength, &errorLog[0]);

        std::cout << "Program linking failed: " << std::endl;
        std::cout << &errorLog[0] << std::endl;
        return false;
    }
    return true;
}

void Shader::Update(
    const char* _vertexPath, 
    const char* _fragmentPath
){
    GLuint vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    vertexPath = _vertexPath;
    fragmentPath = _fragmentPath;

    std::string vertexString = readFile(_vertexPath);
    std::string fragmentString = readFile(_fragmentPath);

    const char *vertexSource = vertexString.c_str();
    const char *fragmentSource = fragmentString.c_str();

    glShaderSource(vertex, 1, &vertexSource, NULL);
    glCompileShader(vertex);
    checkShader(vertex);

    glShaderSource(fragment, 1, &fragmentSource, NULL);
    glCompileShader(fragment);
    checkShader(fragment);

    this->id = glCreateProgram();
    glAttachShader(this->id, vertex);
    glAttachShader(this->id, fragment);
    glLinkProgram(this->id);
    checkProgram(this->id);
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Object::Attach(Queue &queue) {
    queue.names.push_back(this->name);
    GLuint id = queue.getObject(this->name);
    queue.shaderProgramIDs.insert(queue.shaderProgramIDs.begin()+id, this->shaderProgramID);
    queue.vertices.insert(queue.vertices.begin()+id, this->vertices);
    queue.indices.insert(queue.indices.begin()+id, this->indices);
    queue.vertexAttribs.insert(queue.vertexAttribs.begin()+id, this->vertexAttribSizes);

    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glGenVertexArrays(1, &queue.VAO);
    glBindVertexArray(queue.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * this->indices.size(), this->indices.data(), GL_STATIC_DRAW);

    int stride = 3;
    for (int i = 0; i < this->vertexAttribSizes.size(); i++) {
        stride+=this->vertexAttribSizes[i];
    }

    // Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Other attributes
    int totalSize = 3;
    for (int i = 0; i < this->vertexAttribSizes.size(); i++) {
        glVertexAttribPointer(i+1, this->vertexAttribSizes[i], GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(totalSize * sizeof(float)));
        glEnableVertexAttribArray(i+1);
        totalSize+=this->vertexAttribSizes[i];
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Object::Detach(Queue &queue) {
    GLuint id = queue.getObject(this->name);
    queue.names.erase(std::remove(queue.names.begin(), queue.names.end(), this->name), queue.names.end());
    queue.vertices.erase(queue.vertices.begin()+id, queue.vertices.begin()+id+this->vertices.size());
    queue.indices.erase(queue.indices.begin()+id, queue.indices.begin()+id+this->indices.size());
    queue.vertexAttribs.erase(queue.vertexAttribs.begin()+id, queue.vertexAttribs.begin()+id+this->vertexAttribSizes.size());

    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}

void Object::Update(
    std::vector<GLfloat> _vertices, 
    std::vector<GLuint> _indices, 
    int _shaderProgramID, 
    std::string _name,
    std::vector<int> _vertexAttribSizes
){
    // TODO: Clear all vectors, also detach and reattach automatically.

    for (int i = 0; i < _vertices.size(); i++) {
        vertices.push_back(_vertices[i]);
    }
    for (int i = 0; i < _indices.size(); i++) {
        indices.push_back(_indices[i]);
    }
    for (int i = 0; i < _vertexAttribSizes.size(); i++) {
        vertexAttribSizes.push_back(_vertexAttribSizes[i]);
    }

    shaderProgramID = _shaderProgramID;
    name = _name;
}