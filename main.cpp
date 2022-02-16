#include <loader.h>
using namespace srcpool;

int close(SDL_Window* window, SDL_GLContext glContext) {
    IMG_Quit();
    
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(glContext);
    SDL_Quit();

    return 0;
}

// Simple debugger callback, will most likely modify in the future.
static void APIENTRY openglCallbackFunction(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam
){
    (void)source; (void)type; (void)id; 
    (void)severity; (void)length; (void)userParam;
    fprintf(stderr, "%s\n", message);
    if (severity==GL_DEBUG_SEVERITY_HIGH) {
        fprintf(stderr, "Aborting...\n");
        abort();
    }
}

std::vector<GLfloat> vertices {
    // positions         // colors
    -1.0f, 1.0f, 0.0f,  0.071f, 0.071f, 0.071f,  // top left
    1.0f,  1.0f, 0.0f,  0.071f, 0.071f, 0.071f,   // top right
    -1.0f, 0.95f, 0.0f,  0.071f, 0.071f, 0.071f,  // bottom left
    1.0f, 0.95f, 0.0f,  0.071f, 0.071f, 0.071f  // bottom right
};

std::vector<GLuint> indices {
    0, 1, 2,
    2, 1, 3
};

std::vector<int> vertexAttribSizes {
    3
};

int main(int argc, char* argv[]) {

    // Variables
    bool quit = false;

    // Initializations
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    setGLAttributes();

    // Creating the window
    SDL_Window* window = SDL_CreateWindow("srcpool", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winW, winH, flags);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glContext);

    SDL_Surface* icon = IMG_Load("images/icon.png");
    setIcon(window, icon);

    // Setting up OpenGL
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    glViewport(0, 0, winW, winH);

    // Enable the debug callback
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(openglCallbackFunction, nullptr);
    glDebugMessageControl
    (
        GL_DONT_CARE, 
        GL_DONT_CARE, 
        GL_DONT_CARE, 
        0, NULL, true
    );

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Renderer::Queue DefaultUI;
    Renderer::Shader defaultShader;
    Renderer::Object topBar;

    defaultShader.Update("..\\editor\\shaders\\default\\default.vertex", "..\\editor\\shaders\\default\\default.fragment");
    topBar.Update(vertices, indices, defaultShader.id, "triangle", vertexAttribSizes);
    topBar.Attach(DefaultUI);

    while(!quit) {
        SDL_Event event;
        mouseX = event.motion.x;
        mouseY = event.motion.y;
        
        while (SDL_PollEvent(&event) != 0) {
            inputCollection(event, quit);
        }

        SDL_SetWindowHitTest(window, hitCallback, 0);
        
        glClearColor(0.078f, 0.078f, 0.078f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        DefaultUI.Render();

        SDL_GL_SwapWindow(window);
    }

    // Closes all processes
    topBar.Detach(DefaultUI);
    defaultShader.Delete();
    close(window, glContext);

    return 0;
}