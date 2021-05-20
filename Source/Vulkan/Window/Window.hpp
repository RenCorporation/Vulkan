#pragma once

#include <GLFW/glfw3.h>

namespace Vulkan::Window {
	GLFWwindow *Create();

	void Destroy();

	GLFWwindow *Get();

	void MainLoop();
}
