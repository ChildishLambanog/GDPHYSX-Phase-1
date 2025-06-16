#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model3D.h"
#include "Shader.h"
#include "Light.h"
#include "DirectionLight.h"
#include "PointLight.h"
#include "Camera.h"
#include "OrthoCamera.h"
#include "PerspectiveCamera.h"
#include "P6/MyVector.h"
#include "P6/P6Particle.h"
#include "P6/PhysicsWorld.h"
#include "P6/DragForceGenerator.h"

#include "P6/RSpeedGenerator.h"

// testing renderparticle

#include "RenderParticle.h"

#include"FountainDemo.h"

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <chrono>


std::list<RenderParticle*> renderParticles; //list of particles to be rendered

using namespace std::chrono_literals;
constexpr std::chrono::nanoseconds timestep(16ms);

float scale = 3;
float StartPos = -800; // start of particles

/*
Timerstuff

float timerecord[4] = {}; /// all times from the balls
bool isRecords[4] = { false, false, false, false }; // if the record is set or not
std::vector<float> order;
std::vector<std::string> nOrder; // name order
//false = main, true = sphere
*/

bool stateControl = false;
bool stateCam = true;

int Presseds = 0; //amount of spaces pressed or hold

//initialize camera vars
glm::vec3 cameraPos = glm::vec3(0, 0, 2.f);
glm::vec3 WorldUp = glm::vec3(0, 1.0f, 0);
glm::vec3 Front = glm::vec3(0, 0.0f, -1);
const float cameraRotateSpeed = 1.5f; // degrees per key press/frame

//initialize for mouse movement
bool firstMouse = true;
float pitch = 0.0f;
float yaw = -90.0f;

//for initial mouse movement
float lastX = 400, lastY = 400;

float height = 800;
float width = 800;

//Initializing the object classes to be rendered
Model3D main_object({ 0, 0, 0 });
Model3D main_object2({ 0, 0, 0 });
Model3D main_object3({ 0, 0, 0 });
Model3D main_object4({ 0, 0, 0 });
OrthoCamera orca({ 0,2,0 });
PerspectiveCamera perca({ 0,0,0 }, height, width);
 
//initial color
P6::PhysicsWorld pWorld = P6::PhysicsWorld();

//initialize particle points
P6::P6Particle particle = P6::P6Particle(StartPos, 250, 0); //Position of Particle 1
P6::P6Particle particle2 = P6::P6Particle(StartPos, 0, 0); //Position of Particle 2
P6::P6Particle particle3 = P6::P6Particle(StartPos, -250, 0); //Position of Particle 3
P6::P6Particle Pp = P6::P6Particle(StartPos, -450, 0); //Position of Particle player

//Fountain Variables
FountainDemo* fountain = nullptr;

//Point light variables
float brightness = 1.0f;
float dl_brightness = 2.0f;

glm::vec3 sphere_color = { 1.f,1.f,1.f };

void Destroy(Model3D& obj) //hide object
{
    obj.color = glm::vec4(0, 0, 0, 0);
}

void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    //if (key == GLFW_KEY_SPACE)
    //{
    //	Pp.AddForce(P6::MyVector(1000,0, 0)); PLEASE REMOVE BEFORE SUBMISSION
    //}

    if (glfwGetKey(window, GLFW_KEY_1))
    {
        stateCam = true; //changes the camera into ortho mode
        std::cout << "Camera changed to Ortographic" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_2))
    {
        stateCam = false; //changes the camera into perspective mode
        std::cout << "Camera changed to Perspective" << std::endl;
    }

    // Only rotate camera in perspective mode
    if (!stateCam)
    {
        bool updated = false;

        // Rotate right (D)
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            yaw -= cameraRotateSpeed;
            updated = true;
        }

        // Rotate left (A)
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            yaw += cameraRotateSpeed;
            updated = true;
        }

        // Rotate up (W)
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            pitch += cameraRotateSpeed;
            updated = true;
        }

        // Rotate down (S)
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            pitch -= cameraRotateSpeed;
            updated = true;
        }

        //Clamp the pitch to avoid flipping
        if (pitch > 89.0f)
        {
            pitch = 89.0f;
        }

        if (pitch < -89.0f)
        {
            pitch = -89.0f;
        }

        //If any key was pressed, update camera position and front //new addition 

        if (updated)
        {
            glm::vec3 fountainCenter = main_object.getPosition(); // Or use your fountain's actual center

            float radius = 500.0f; //Camera distance from the fountain, adjust as needed 12.0f/120/240
            float heightOffset = 250.0f; //Height above the fountain center, adjust as needed 80.0f/200/

            glm::vec3 offset;
            offset.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch)) * radius;
            offset.y = sin(glm::radians(pitch)) * radius + heightOffset;
            offset.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch)) * radius;

            glm::vec3 camPos = fountainCenter + offset;
            perca.setCameraPos(camPos);

            //Look at the fountain center
            perca.setFront(glm::normalize(fountainCenter - camPos));
        }
    }
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Amar, Dacanay, Villanueva Phase 1", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();


    //Texture
    int img_width, img_height, colorChannels;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* tex_bytes = stbi_load(
        "3D/jelly.jpg",
        &img_width,
        &img_height,
        &colorChannels,
        0
    );

    GLuint texture;

    glGenTextures(1, &texture);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D,
        0,
        GL_RGB,
        img_width,
        img_height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        tex_bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes);
    

    glEnable(GL_DEPTH_TEST);


    glfwSetKeyCallback(window, Key_Callback);

    //Shaders
    Shader mainObjShader("Shaders/mainObj.vert", "Shaders/mainObj.frag");

    //compile shader vertex
    std::fstream vertSrc("Shaders/directionLight.vert");
    std::stringstream vertBuff;

    vertBuff << vertSrc.rdbuf();

    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    //compile shader fragment
    std::fstream fragSrc("Shaders/directionLight.frag");
    std::stringstream fragBuff;

    fragBuff << fragSrc.rdbuf();

    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    //MAIN OBJECT
    //create vertex shader(used for movements)
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &v, NULL);

    glCompileShader(vertexShader);

    //create frag shader (our objects are turned into pixels/fragments which we will use to color in an object)
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragShader, 1, &f, NULL);

    glCompileShader(fragShader);

    //create shader program that'll just run both frag and vert together as one.
    GLuint shaderProg = glCreateProgram();
    glAttachShader(shaderProg, vertexShader);
    glAttachShader(shaderProg, fragShader);

    glLinkProgram(shaderProg);//compile to make sure computer remembers

    std::string path = "3D/sphere.obj"; //provided from class
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;

    tinyobj::attrib_t attributes;

    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str()
    );  

    GLfloat UV[]{
        0.f, 1.f,
        0.f, 0.f,
        1.f, 1.f,
        1.f, 0.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 1.f,
        0.f, 0.f
    };
   
    //array of Mesh for the main object
    std::vector<GLfloat> fullVertexData;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData = shapes[0].mesh.indices[i];

        //vertex
        fullVertexData.push_back(
            attributes.vertices[(vData.vertex_index * 3)]
        );

        fullVertexData.push_back(
            attributes.vertices[(vData.vertex_index * 3) + 1]
        );

        fullVertexData.push_back(
            attributes.vertices[(vData.vertex_index * 3) + 2]
        );

        //normal
        fullVertexData.push_back(
            attributes.normals[(vData.normal_index * 3)]
        );

        fullVertexData.push_back(
            attributes.normals[(vData.normal_index * 3) + 1]
        );

        fullVertexData.push_back(
            attributes.normals[(vData.normal_index * 3) + 2]
        );

        //texcoord
        fullVertexData.push_back(
            attributes.texcoords[(vData.texcoord_index * 2)]
        );

        fullVertexData.push_back(
            attributes.texcoords[(vData.texcoord_index * 2) + 1]
        );

    }

    //main object
    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * fullVertexData.size(),
        fullVertexData.data(),
        GL_DYNAMIC_DRAW
    );

    
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,

        8 * sizeof(float),
        (void*)0

    );

    glEnableVertexAttribArray(0);

    GLintptr litPtr = 3 * sizeof(float);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,

        8 * sizeof(float),
        (void*)litPtr

    );

    glEnableVertexAttribArray(1);

    GLintptr uvPtr = 6 * sizeof(float);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,

        8 * sizeof(float),
        (void*)uvPtr

    );

    glEnableVertexAttribArray(2);

    //SET BINDINGS TO NULL
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glm::mat4 identity_matrix = glm::mat4(1.0f);


    //Camera Variables
    glm::mat4 projection = glm::perspective(
        glm::radians(60.f),     //FOV
        height / width,         //aspect ratio
        0.1f,                   //znear > 0
        1000.f                  //zfar
    );

    //Light Variables
    glm::vec3 lightPos = glm::vec3(-10, 10, 0);

    glm::vec3 lightColor = glm::vec3(1,1,1);

    float ambientStr = 0.2f;

    glm::vec3 ambientColor = lightColor;

    float specStr = 0.5f;

    float specPhong = 8;

    //Light Classes
    glm::vec3 lightDirection = { 4,-5,0 };
    DirectionLight directionLight(lightPos, lightColor, ambientStr, ambientColor, specStr, specPhong, lightDirection, dl_brightness);

    P6::MyVector sample(0.0f, 0.0f, 0.0f);
    //sample.x = 0;
 

    //Scale Setting of objects
    main_object.setScale(glm::vec3(scale, scale, scale));
	main_object2.setScale(glm::vec3(scale, scale, scale));
	main_object3.setScale(glm::vec3(scale, scale, scale));
	main_object4.setScale(glm::vec3(scale, scale, scale));

    //Initialize the clock and variables
	using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
	auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0); 

	particle.Acceleration = P6::MyVector(0.f, -900.81f, 0.f); //gravity
    //phys world for updating particles location
	pWorld.AddParticle(&particle);
	pWorld.AddParticle(&particle2);
	pWorld.AddParticle(&particle3);
	pWorld.AddParticle(&Pp);

    // adding renderparticles
    RenderParticle rpTest(&particle, &main_object, P6::MyVector(1.f, 1.f, 1.f));
	renderParticles.push_back(&rpTest);

    //Fountain
    fountain = new FountainDemo(&pWorld, &main_object, 1000);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
		curr_time = clock::now();
		auto dur = std::chrono::duration_cast<std::chrono::nanoseconds> (curr_time - prev_time);
        prev_time = curr_time;

        curr_ns += dur;

        if (curr_ns >= timestep)
        {
			auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);
           // std::cout << "MS: " << (float)ms.count() << "\n";

            curr_ns -= timestep;
        
			pWorld.Update((float)ms.count() / 10000);
            fountain->Update((float)ms.count() / 1000); // deltaTime in seconds
 
        }

       // std::cout << "Normal Update\n";

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 viewMatrix;


        //setposition of particle to object

      //  main_object.setPosition(glm::vec3(particle.Position.x, particle.Position.y, particle.Position.z));
		main_object2.setPosition(glm::vec3(particle2.Position.x, particle2.Position.y, particle2.Position.z));
        main_object3.setPosition(glm::vec3(particle3.Position.x, particle3.Position.y, particle3.Position.z));

        main_object4.setPosition(glm::vec3(Pp.Position.x, Pp.Position.y, Pp.Position.z));

        
        //set camera to be MOVEABLE i.e. can be influenced
        if (stateCam) 
        {
            //set the camera to ortho
            viewMatrix = glm::lookAt(orca.getCameraPos(), orca.getCameraPos() + orca.getFront(), orca.getWorldUp());
        }

        else 
        {
            //set the camera to perspective
            viewMatrix = glm::lookAt(perca.getCameraPos(), perca.getCameraPos() + perca.getFront(), perca.getWorldUp());
        }

        ////skybox
        //glDepthMask(GL_FALSE);
        //glDepthFunc(GL_LEQUAL);

        //glDepthMask(GL_TRUE);
        //glDepthFunc(GL_LESS);

        //Drawing Main Object
        directionLight.setBrightness(dl_brightness);

        //attaches the same values for direction and point light
        directionLight.attachFundamentals(&mainObjShader);

        //attaches the specific values of each light
        directionLight.attachSpecifics(&mainObjShader);

        if (stateCam) //set the camera to ortho
        {
            main_object.setCamera(orca.getProjection(), orca.getCameraPos(), orca.getFront(), orca.getViewMat());
            main_object2.setCamera(orca.getProjection(), orca.getCameraPos(), orca.getFront(), orca.getViewMat());
            main_object3.setCamera(orca.getProjection(), orca.getCameraPos(), orca.getFront(), orca.getViewMat());
            main_object4.setCamera(orca.getProjection(), orca.getCameraPos(), orca.getFront(), orca.getViewMat());

        }

        else  //set the camera to perspective //MAYBE NEEDS TO CHANGE
        {        
            main_object.setCamera(perca.getProjection(), perca.getCameraPos(), perca.getFront(), perca.getViewMat());
        }

        //MAIN OBJECT
        //TEXTURE OF MAIN OBJECT
        mainObjShader.use();

		// testing render particles
		for (std::list<RenderParticle*>::iterator it = renderParticles.begin(); it != renderParticles.end(); ++it)
		{
			(*it)->Draw(&mainObjShader, &VAO, &fullVertexData, &texture,"tex0");
		}
		

        fountain->Render(&mainObjShader, &VAO, &fullVertexData, &texture, "spark");
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
    std::cin.get();

}