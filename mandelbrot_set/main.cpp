#include <iostream>
#include "lib/glad/glad.h"
#include <OpenGL/glu.h>
#include "lib/glfw/include/GLFW/glfw3.h"
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

double cx = -0.58, cy = 0.0, zoom = 0.35;
int itr = 100, fps = 0, exponent = 2;
bool keys[1024] = {0};
int w = 800, h = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
static void cursor_callback(GLFWwindow* window, double xpos, double ypos) {}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    double xr = 2.0 * (xpos / (double)w - 0.5);
    double yr = 2.0 * (ypos / (double)h - 0.5);

    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        cx += (xr - cx) / zoom / 2.0;
        cy -= (yr - cy) / zoom / 2.0;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    zoom += yoffset * 0.1 * zoom;
    if(zoom < 0.1) {
        zoom = 0.1;
    }
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    const double d = 0.1 / zoom;

    if(action == GLFW_PRESS) {
        keys[key] = true;
    } else if(action == GLFW_RELEASE) {
        keys[key] = false;
    }

    if(keys[GLFW_KEY_ESCAPE]) {
        glfwSetWindowShouldClose(window, 1);
    } else if(keys[GLFW_KEY_A]) {
        cx -= d;
    } else if(keys[GLFW_KEY_D]) {
        cx += d;
    } else if(keys[GLFW_KEY_W]) {
        cy -= d;
    } else if(keys[GLFW_KEY_S]) {
        cy += d;
    } else if (keys[GLFW_KEY_2]) {
        exponent = 2;
    } else if (keys[GLFW_KEY_3]) {
        exponent = 3;
    } else if (keys[GLFW_KEY_4]) {
        exponent = 4;
    } else if (keys[GLFW_KEY_5]) {
        exponent = 5;
    } else if (keys[GLFW_KEY_6]) {
        exponent = 6;
    } else if (keys[GLFW_KEY_7]) {
        exponent = 7;
    } else if (keys[GLFW_KEY_8]) {
        exponent = 8;
    } else if(keys[GLFW_KEY_MINUS]) {
        itr += 10;
    } else if(keys[GLFW_KEY_EQUAL]) {
        itr -= 10;
        if(itr <= 0) {
            itr = 0;
        }
    }
}
static void update_window_title(GLFWwindow *window) {
    std::ostringstream ss;
    ss << "William Trimmer | Mandelbrot";
    ss << ", Iterations: " << itr;
    ss << ", Zoom: " << zoom;
    ss << ", Exponent: " << exponent;
    glfwSetWindowTitle(window, ss.str().c_str());
}


GLFWwindow* initialize(unsigned int screenWidth, unsigned int screenHeight) {
    // glfw: initialize and configure
    if(!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        glfwTerminate();
    }
    // ------------------------------
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Mandelbrot", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }
    return window;
}

int main() {
    GLFWwindow *window = initialize(w, h);
    // create mandelbrot shader
    Shader mandelbrotShader("../mandelbrotVertex.vs", "../mandelbrotFragment.fs");
    // create name shader
    Shader nameShader("../nameVertex.vs", "../nameFragment.fs");

    float nameVertices[] = {
            // position         // color        // texture coordinate
            0.4f,  0.4f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,// top right
            0.4f, -0.4f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,// bottom right
            -0.4f, -0.4f, 0.f, 1.0f, 1.0f, 1.0f, 0.f, 0.0f,// bottom left
            -0.4f, 0.4f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f// top left
    };

    float mandelbrotVertices[] = {
            -1.0f,  1.0f,  0.0f,
            -1.0f,  -1.0f,  0.0f,
            1.0f,  -1.0f,  0.0f,

            -1.0f,  1.0f,  0.0f,
            1.0f,  -1.0f,  0.0f,
            1.0f,  1.0f,  0.0f,
    };

    unsigned int nameIndices[] = {
            0, 1, 3, // first triangle
            1, 2, 3
    };

    GLuint vao_mandelbrot, vbo_mandelbrot, vao_name, vbo_name, ebo_name;
    // mandelbrot
    glGenBuffers (1, &vbo_mandelbrot);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_mandelbrot);
    glBufferData (GL_ARRAY_BUFFER, 2 * 9 * sizeof (float), mandelbrotVertices, GL_STATIC_DRAW);

    glGenVertexArrays (1, &vao_mandelbrot);
    glBindVertexArray (vao_mandelbrot);
    glEnableVertexAttribArray (0);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // name
    glGenVertexArrays(1, &vao_name);
    glGenBuffers(1, &vbo_name);
    glGenBuffers(1, &ebo_name);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vao_name);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_name);
    glBufferData(GL_ARRAY_BUFFER, sizeof(nameVertices), nameVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_name);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(nameIndices), nameIndices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("../name_texture.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    int iterator = 0;
    while(!glfwWindowShouldClose(window)) {
        update_window_title(window);

        glfwGetWindowSize(window, &w, &h);

        mandelbrotShader.use();
        glBindBuffer(GL_ARRAY_BUFFER, vbo_mandelbrot);
        glBindVertexArray(vao_mandelbrot);
        if(iterator > 1) {

            glUniform2d(glGetUniformLocation(mandelbrotShader.ID, "screen_size"), (double) w, (double) h);
            glUniform1d(glGetUniformLocation(mandelbrotShader.ID, "screen_ratio"), (double) w / (double) h);
            glUniform2d(glGetUniformLocation(mandelbrotShader.ID, "center"), cx, cy);
            glUniform1d(glGetUniformLocation(mandelbrotShader.ID, "zoom"), zoom);
            glUniform1i(glGetUniformLocation(mandelbrotShader.ID, "itr"), itr);
            glUniform1i(glGetUniformLocation(mandelbrotShader.ID, "exponent"), exponent);
        }
        iterator++;
        glDrawArrays(GL_TRIANGLES, 0, 6);


        glBindVertexArray(vao_name);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_name);
        nameShader.use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &vao_mandelbrot);
    glDeleteVertexArrays(1, &vao_name);
    glDeleteBuffers(1, &vbo_mandelbrot);
    glDeleteBuffers(1, &vbo_name);
    glDeleteBuffers(1, &ebo_name);

    glfwTerminate();
    return 0;
}