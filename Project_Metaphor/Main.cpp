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

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <chrono>


std::list<RenderParticle*> renderParticles; //list of particles to be rendered

using namespace std::chrono_literals;
constexpr std::chrono::nanoseconds timestep(16ms);



float scale = 50;
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
//initialize for mouse movement
bool firstMouse = true;
float pitch = 0.0f;
float yaw = -90.0f;

//for initial mouse movement
float lastX = 400, lastY = 400;

float height = 500;
float width = 1000;

//Initializing the object classes to be rendered
Model3D main_object({ 0, 0, 0 });
Model3D main_object2({ 0, 0, 0 });
Model3D main_object3({ 0, 0, 0 });
Model3D main_object4({ 0, 0, 0 });
//initial color


//initialize particle points
P6::P6Particle particle = P6::P6Particle(StartPos, 250, 0); //Position of Partile 1
P6::P6Particle particle2 = P6::P6Particle(StartPos, 0, 0); //Position of Partile 2
P6::P6Particle particle3 = P6::P6Particle(StartPos, -250, 0); //Position of Partile 3
P6::P6Particle Pp = P6::P6Particle(StartPos, -450, 0); //Position of Partile player

OrthoCamera orca({ 0,2,0 });
PerspectiveCamera perca({ 0,0,0 }, height, width);


//Point light variables
float brightness = 1.0f;
float dl_brightness = 2.0f;

glm::vec3 sphere_color = { 1.f,1.f,1.f };

void Destroy(Model3D& obj) //hide object
{
	obj.color=glm::vec4(0,0,0,0);
}


void Key_Callback(GLFWwindow* window, int key, int scancode, int action,int mods) 
{
    
	if (key == GLFW_KEY_SPACE)
	{
		Pp.AddForce(P6::MyVector(1000,0, 0));
	}
};

int main(void)
{
    GLFWwindow* window;

  /*  main_object.color = glm::vec4(1.f, 1.f, 1.f, 1.f);
    main_object2.color = glm::vec4(1.f, 0.f, 1.f, 1.f);
    main_object3.color = glm::vec4(0.f, 1.f, 1.f, 1.f);
    main_object4.color = glm::vec4(1.f, 1.f, 0.f, 1.f);*/

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Rameses P. Amar", NULL, NULL);
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

    //P6::MyVector scalar = x * scalar;
    //x *= y;

    //Initialize the clock and variables
	using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
	auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0); 


	P6::PhysicsWorld pWorld = P6::PhysicsWorld();

	particle.Acceleration = P6::MyVector(0.f, -900.81f, 0.f); //gravity
    //phys world for updating particles location
	pWorld.AddParticle(&particle);
	pWorld.AddParticle(&particle2);
	pWorld.AddParticle(&particle3);
	pWorld.AddParticle(&Pp);

    // adding renderparticles
    RenderParticle rpTest(&particle, &main_object, P6::MyVector(1.f, 1.f, 1.f));
	renderParticles.push_back(&rpTest);

   /* P6::DragForceGenerator drag = P6::DragForceGenerator(0.14f, 0.1f);
	pWorld.forceRegistry.Add(&particle, &drag);*/
   /* int mn = 20;
    int mx = 30;
    srand(time(0));

    P6::RSpeedGenerator rsG1 = P6::RSpeedGenerator((mn - std::rand() % (mx - mn + 1)));
	pWorld.forceRegistry.Add(&particle, &rsG1);
	P6::RSpeedGenerator rsG2 = P6::RSpeedGenerator((mn - std::rand() % (mx - mn + 1)));
	pWorld.forceRegistry.Add(&particle2, &rsG2);
	P6::RSpeedGenerator rsG3 = P6::RSpeedGenerator((mn - std::rand() % (mx - mn + 1)));

	pWorld.forceRegistry.Add(&particle3, &rsG3);*/


 //   float timeElapsed = 0.0f;

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

        //skybox
        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LEQUAL);

        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);

       
        
      
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

        else  //set the camera to perspective
        {        
            main_object.setCamera(perca.getProjection(), perca.getCameraPos(), perca.getFront(), perca.getViewMat());
        }
        //MAIN OBJECT
       //TEXTURE OF MAIN OBJECT
        mainObjShader.use();
        
        //SETCOLOR HERE
       
     /*  main_object.setTexture(&mainObjShader, &texture, "tex0");
        main_object.mainDraw(&mainObjShader, &VAO, &fullVertexData);
        
        main_object2.setTexture(&mainObjShader, &texture, "tex0");
        main_object2.mainDraw(&mainObjShader, &VAO, &fullVertexData);

        main_object3.setTexture(&mainObjShader, &texture, "tex0");
        main_object3.mainDraw(&mainObjShader, &VAO, &fullVertexData);

        main_object4.setTexture(&mainObjShader, &texture, "tex0");
        main_object4.mainDraw(&mainObjShader, &VAO, &fullVertexData);*/

     
		// testing render particles
		for (std::list<RenderParticle*>::iterator it = renderParticles.begin(); it != renderParticles.end(); ++it)
		{
			(*it)->Draw(&mainObjShader, &VAO, &fullVertexData, &texture,"tex0");
		}
		


        
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