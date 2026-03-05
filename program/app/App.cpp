#include "App.h"
#include "../engine/gfx/Model.h"
#include "../engine/shader/shader.h"
#include "gfx/MeshPrimitives.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void App::onCreate()
{
    scene = std::make_shared<Scene>("Main");

    /*SceneObject sponza;
    sponza.name = "sponza";
    sponza.model = std::make_shared<Model>(MODEL("teapot/scene.gltf"));
    sponza.shader = std::make_shared<Shader>(
        SHADER("vshader.vs"), 
        SHADER("fshader.fs"));
    sponza.scale = glm::vec3(0.5f);

    scene->AddObject(sponza);*/

    SceneObject cube;
    cube.name = "cube";
    cube.model = std::make_shared<Model>(std::vector<Mesh>{ MeshPrimitives::CreateCube(0.5f) });
    cube.shader = std::make_shared<Shader>(
        SHADER("lightvshader.vs"),
        SHADER("lightfshader.fs"));

    cube.position = glm::vec3(0.0, 1.0, 0.0);

    scene->AddObject(cube);

    SceneObject plane;
    plane.name = "plane";
    plane.model = std::make_shared<Model>(std::vector<Mesh>{ MeshPrimitives::CreatePlane(5.f) });
    plane.shader = std::make_shared<Shader>(
        SHADER("lightvshader.vs"),
        SHADER("lightfshader.fs"));

    //plane.position = glm::vec3(1.0, 1.0, 1.0);
    scene->AddObject(plane);

    /*Light sun;
    sun.position = glm::vec3(0.25f, 4.75f, -0.30f);
    scene->AddLight(sun);*/

    scene->camera = Camera();

    GLFWwindow* win = GetWindow().GetWindowContext();
    glfwSetWindowUserPointer(win, this);
    glfwSetCursorPosCallback(win, mouse_callback);

    m_Context->SetWindow(win);

    rp3d::PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 20;
    settings.isSleepingEnabled = false;
    settings.gravity = rp3d::Vector3(0, -9.81, 0);

    world = physicsCommon.createPhysicsWorld(settings);

    cubeBody = world->createRigidBody(
        rp3d::Transform(rp3d::Vector3(0, 5, 0), rp3d::Quaternion::identity()));
    cubeBody->setType(rp3d::BodyType::DYNAMIC);
    rp3d::BoxShape* cubeShape = physicsCommon.createBoxShape(rp3d::Vector3(0.5f, 0.5f, 0.5f));
    cubeBody->addCollider(cubeShape, rp3d::Transform::identity());

    planeBody = world->createRigidBody(
        rp3d::Transform(rp3d::Vector3(0, 0, 0), rp3d::Quaternion::identity()));
    planeBody->setType(rp3d::BodyType::STATIC);
    rp3d::BoxShape* planeShape = physicsCommon.createBoxShape(rp3d::Vector3(5.0f, 0.1f, 5.0f));
    planeBody->addCollider(planeShape, rp3d::Transform::identity());
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

    rp3d::Transform t = cubeBody->getTransform();
    rp3d::Vector3 pos = t.getPosition();
    rp3d::Quaternion rot = t.getOrientation();

    scene->objects[0].position = glm::vec3(pos.x, pos.y, pos.z);
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