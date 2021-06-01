#pragma once

#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>

#include "../Queue/Queue.hpp"
#include "../Framebuffers/Framebuffers.hpp"
#include "../GraphicsPipeline/GraphicsPipeline.hpp"

namespace Vulkan::Command
{
	void CreatePool();

    void DestroyPool();
    
    void CreateBuffers();
}
