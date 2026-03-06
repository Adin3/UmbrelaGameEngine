#include "App.h"
#include "../engine/gfx/Model.h"
#include "../engine/shader/shader.h"
#include "gfx/MeshPrimitives.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void App::onCreate()
{
    scene = std::make_shared<Scene>("Main");

    rp3d::PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 20;
    settings.isSleepingEnabled = false;
    settings.gravity = rp3d::Vector3(0, -9.81, 0);

    world = physicsCommon.createPhysicsWorld(settings);

    /*SceneObject sponza;
    sponza.name = "sponza";
    sponza.model = std::make_shared<Model>(MODEL("teapot/scene.gltf"));
    sponza.shader = std::make_shared<Shader>(
        SHADER("vshader.vs"), 
        SHADER("fshader.fs"));
    sponza.scale = glm::vec3(0.5f);

    scene->AddObject(sponza);*/

    auto& cube = std::make_shared<Object>();
    cube->SetName("cube");
    cube->SetModel(std::make_shared<Model>(std::vector<Mesh>{ MeshPrimitives::CreateCube() }));
    cube->SetShader(std::make_shared<Shader>(
        SHADER("lightvshader.vs"),
        SHADER("lightfshader.fs")));

    cube->SetPosition(glm::vec3(0.0, 10.0, 0.0));
    cube->SetScale(glm::vec3(1.0, 1.0, 1.0));
    cube->createRigidBody(world, physicsCommon, rp3d::BodyType::DYNAMIC);

    scene->AddObject(cube);

    auto& plane = std::make_shared<Object>();
    plane->SetName("plane");
    plane->SetModel(std::make_shared<Model>(std::vector<Mesh>{ MeshPrimitives::CreatePlane() }));
    plane->SetShader(std::make_shared<Shader>(
        SHADER("lightvshader.vs"),
        SHADER("lightfshader.fs")));

    plane->SetPosition(glm::vec3(0.0, 1.0, 0.0));
    plane->SetScale(glm::vec3(5.0, 0.01f, 5.0));
    plane->createRigidBody(world, physicsCommon, rp3d::BodyType::STATIC);

    scene->AddObject(plane);

    /*Light sun;
    sun.position = glm::vec3(0.25f, 4.75f, -0.30f);
    scene->AddLight(sun);*/

    scene->camera = Camera();

    GLFWwindow* win = GetWindow().GetWindowContext();
    glfwSetWindowUserPointer(win, this);
    glfwSetCursorPosCallback(win, mouse_callback);

    m_Context->SetWindow(win);
}

void App::onUpdate(float dt)
{
    m_Context->Draw(dt, *scene, nullptr);

    scene->camera.processKeyboard(dt);

    // imgui specific to this app
    ImGui::Begin("My App");
    ImGui::Text("FPS: %d", (int)(1.0f / dt));
    ImGui::End();

    physicsAccumulator += dt;
    const float physicsStep = 1.0f / 60.0f;
    while (physicsAccumulator >= physicsStep)
    {
        world->update(physicsStep);
        physicsAccumulator -= physicsStep;
    }

    glm::vec3 pos = scene->objects[0]->GetWorldPosition();
    std::cout << pos.y << std::endl;

    if (Input::KeyboardInput(GLFW_KEY_M, GLFW_PRESS)) {
        scene->objects[0]->SetPosition(glm::vec3(0.0, 10.0, 0.0));
    }
}

void App::onDestroy()
{
    scene.reset();
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    if (!app || !app->scene) return;

	static bool firstMouse = true;
	static float lastX = 400.0f, lastY = 300.0f;

	if (Input::KeyboardInput(GLFW_KEY_LEFT_ALT, GLFW_REPEAT)) return;

	if (firstMouse) {
		lastX = xpos; lastY = ypos;
		firstMouse = false;
	}

	float xoffset = (xpos - lastX);
	float yoffset = -(ypos - lastY); // inverted Y
	lastX = xpos;
	lastY = ypos;

	app->scene->camera.processMouse(xoffset, yoffset);
}