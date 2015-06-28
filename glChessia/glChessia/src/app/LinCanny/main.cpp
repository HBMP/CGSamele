#include <iostream>

#include <common/Utility.hpp>
#include <common/Marco.h>
#include <common/Assert.hpp>

#include <app/LinCanny/Scene.h>
#include <glbinding/Binding.h>

namespace detail
{
	template<class T>
	using UniquePtr = std::unique_ptr < T > ;

	static void ErrorCallback(int error, const char* description)
	{
		printf("Error : %d, Desc : %s", error, description);
	}
}

int main(int, char *[])
{
	using namespace detail;

	using namespace gl;
	using namespace glbinding;

	if (glfwInit() == 0)
	{
		ExitProcess(-1);		
	} 

	glfwSetErrorCallback(ErrorCallback);

	ON_SCOPE_EXIT([&]{ glfwTerminate(); });

	auto window = glfwCreateWindow(800, 600, "Simple", nullptr, nullptr);	

	ENSURE_FATAL(ENSURE(window != nullptr), "window create failure");

	ON_SCOPE_EXIT([&]{ glfwDestroyWindow(window); });

	glfwSetKeyCallback(window, Scene::KeyDown);
	glfwSetFramebufferSizeCallback(window, Scene::ReSizeFrameBuffer);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	Binding::initialize();

	auto scene_ptr(std::make_unique<Scene>());

	while (!glfwWindowShouldClose(window))
	{
		scene_ptr->SceneRender(0.0f);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}