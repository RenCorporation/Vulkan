#include "Window.hpp"

GLFWwindow *s_Window = nullptr;

/*----------------------------------------------------------------------------------------------------------*/
GLFWwindow *Vulkan::Window::Create()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	s_Window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
	return s_Window;
}

/*----------------------------------------------------------------------------------------------------------*/
void Vulkan::Window::Destroy()
{
	glfwDestroyWindow(s_Window);
	glfwTerminate();
}

/*----------------------------------------------------------------------------------------------------------*/
GLFWwindow *Vulkan::Window::Get() { return s_Window; }

/*----------------------------------------------------------------------------------------------------------*/
void Vulkan::Window::MainLoop()
{
	while (!glfwWindowShouldClose(s_Window))
	{
		if (glfwGetKey(s_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{ glfwSetWindowShouldClose(s_Window, true); }
		glfwPollEvents();
	}
}

/*----------------------------------------------------------------------------------------------------------*/
