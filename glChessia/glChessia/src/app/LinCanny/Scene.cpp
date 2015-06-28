#include <app/LinCanny/Scene.h>

namespace obj
{
	Cube::Cube()
		: vertex_array_object_(0), vertex_buffer_object_(0), indice_buffer_object_(0)
	{
		using namespace gl;

		glGenVertexArrays(1, &vertex_array_object_);

		GLuint buffer[2];
		glGenBuffers(2, buffer);

		vertex_buffer_object_ = buffer[0];
		indice_buffer_object_ = buffer[1];
	}

	Cube::~Cube()
	{
		using namespace gl;

		glDeleteVertexArrays(1, &vertex_array_object_);

		GLuint buffer[2] = { vertex_buffer_object_, indice_buffer_object_ };
		glDeleteBuffers(2, buffer);
	}
}


Scene::Scene()
{
	SceneInit();
}

Scene::~Scene()
{
	SceneClear();
}

void Scene::SceneInit()
{
	using namespace gl;

	glClearColor(0.3f, 0.2f, 0.4f, 1.0f);
}

void Scene::SceneRender( const gl::GLfloat delta )
{
	using namespace gl;

	glClear(GL_COLOR_BUFFER_BIT);
}

void Scene::SceneClear()
{

}

void Scene::ReSizeFrameBuffer(GLFWwindow* window, int width, int height)
{
	using namespace gl;
	using namespace glm;

	auto ratio = 1.0f;

	if (height > 0)
	{
		ratio = static_cast<float>(width) / static_cast<float>(height);
	}

	glViewport(0, 0, width, height);
	perspective(60.0f, ratio, 1.0f, 1024.0f);
}

void Scene::KeyDown(GLFWwindow* window, int key, int scan_code, int action, int mods)
{
	using namespace gl;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, static_cast<int>(GL_TRUE));
	}
}