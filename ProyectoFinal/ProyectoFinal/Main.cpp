// Std. Includes
#include <string>
#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

#include "SOIL2/SOIL2.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );



// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;


GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;
bool anim = false;
bool anim2 = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

float tiempo;

glm::vec3 pointLightPositions[] = {
    glm::vec3(0.0f,0.0f, 0.0f),
    glm::vec3(0.0f,0.0f, 0.0f),
    glm::vec3(0.0f,0.0f,  0.0f),
    glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
glm::vec3 Light1 = glm::vec3(0);


int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Adaptacion,carga de modelos y camara sintetica", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shaders/modelLoading.vs", "Shaders/modelLoading.frag" );
    
    //Carga modelos/  Load models 
   
//Carga del parque-escenario / Load of the park-stage
    Model parque((char*)"Models/escenario/parqueFinal.obj");

//Carga de puertas-ventanas / Load of doors-windows
    Model puerta((char*)"Models/escenario/puerta.obj");
    Model puertaEntrada1((char*)"Models/escenario/puertaEntrada1.obj");
    Model puertaEntrada2((char*)"Models/escenario/puertaEntrada2.obj");
    Model puertaVidrio2((char*)"Models/escenario/puertavidrio2.obj");
    Model puertaVidrio3((char*)"Models/escenario/puertavidrio3.obj");
    Model puertaVidrio4((char*)"Models/escenario/puertavidrio4.obj");
    Model puertaVidrio5((char*)"Models/escenario/puertavidrio5.obj");
    Model puertaVidrio6((char*)"Models/escenario/puertavidrio6.obj");
    Model puertaVidrio7((char*)"Models/escenario/puertavidrio7.obj");
    Model puertaVidrio8((char*)"Models/escenario/puertavidrio8.obj");
    Model puertaVidrio9((char*)"Models/escenario/puertavidrio9.obj");

//Carga de modelos sin animación / Load of models without animation
    Model mesa((char*)"Models/table/table.obj");
    Model materialLab((char*)"Models/lab/materialab.obj");
    Model estante((char*)"Models/lab/shelf.obj");
    Model tubo((char*)"Models/lab/tubo.obj");
    Model tubo2((char*)"Models/lab/tubo2.obj");
    Model tubo3((char*)"Models/lab/tubo3.obj");
    Model tubo4((char*)"Models/lab/tubo4.obj");
    Model tubo5((char*)"Models/lab/tubo5.obj");
    Model tubo6((char*)"Models/lab/tubo6.obj");
    Model tubo7((char*)"Models/lab/tubo7.obj");
    Model tubo8((char*)"Models/lab/tubo8.obj");
    Model tubo9((char*)"Models/lab/tubo9.obj");
    Model tubo10((char*)"Models/lab/tubo10.obj");
  
    Model dispensador((char*)"Models/dispenser/dispenser1.obj");

//Carga de modelos con animación / Load of models with animation
    Model dispensadorAbajo((char*)"Models/dispenser/dispensadorAbajo.obj"); //Esto no tiene animación /This has no animation
    Model dispensadorArriba((char*)"Models/dispenser/dispensadorArriba.obj"); //Esto tiene animación /This has animation
    Model dinoCola((char*)"Models/dino/dinoCola.obj"); //Esto tiene animación /This has animation
    Model dinoCuerpo((char*)"Models/dino/dinoCuerpo.obj"); //Esto no tiene animación /This has no animation
    Model mezclador((char*)"Models/lab/mezclador.obj");
    Model persona1Cabeza((char*)"Models/person/person1Cabeza.obj"); 
    Model persona1Cuerpo((char*)"Models/person/person1Cabeza.obj");

    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
  

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        glm::mat4 model(1);
       
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

      //Dibuja modelos /Draw models
      //Dibuja  parque-escenario / Draw park-stage
        parque.Draw(shader);

     ////Dibuja puertas-ventanas / Draw doors-windows
     //   puerta.Draw(shader);
     //   puertaEntrada1.Draw(shader);
     //   puertaEntrada2.Draw(shader);
     //   puertaVidrio2.Draw(shader);
     //   puertaVidrio3.Draw(shader);
     //   puertaVidrio4.Draw(shader);
     //   puertaVidrio5.Draw(shader);
     //   puertaVidrio6.Draw(shader);
     //   puertaVidrio7.Draw(shader);
     //   puertaVidrio8.Draw(shader);
     //   puertaVidrio9.Draw(shader);

     ////Dibuja modelos sin animación / Draw models without animation
     //   mesa.Draw(shader);
     //   materialLab.Draw(shader);
     //   estante.Draw(shader);
     //   tubo.Draw(shader);
     //   tubo2.Draw(shader);
     //   tubo3.Draw(shader);
     //   tubo4.Draw(shader);
     //   tubo5.Draw(shader);
     //   tubo6.Draw(shader);
     //   tubo7.Draw(shader);
     //   tubo8.Draw(shader);
     //   tubo9.Draw(shader);
     //   tubo10.Draw(shader);
     //   medicina.Draw(shader);
     //   medicina2.Draw(shader);
     //   medicina3.Draw(shader);
     //   dispensador.Draw(shader);

     ////Dibuja modelos con animación / Draw models with animation
        dispensadorAbajo.Draw(shader);
        dispensadorArriba.Draw(shader);
      //  dinoCola.Draw(shader);
     //   dinoCuerpo.Draw(shader);





        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }
    if (anim)
    {
       
            rot += 0.08f;

   
    }
   
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }

    if (keys[GLFW_KEY_O]) {
        anim = true;
    }

 
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

