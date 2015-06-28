#ifndef _SCENE_H_
#define _SCENE_H_

#include <glfw3.h>
#include <glbinding/gl/gl.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace obj
{
	class Cube
	{
	public:
		Cube();
		~Cube();

	private:
		gl::GLuint vertex_array_object_;
		gl::GLuint vertex_buffer_object_;
		gl::GLuint indice_buffer_object_;
	};
}

class Scene
{
public:
	Scene();
	~Scene();

	void SceneInit();
	void SceneRender(const gl::GLfloat delta);
	void SceneClear();

	static void ReSizeFrameBuffer(GLFWwindow*  window, int width, int height);
	static void KeyDown(GLFWwindow* window, int key, int scan_code, int action, int mods);
};

#endif
