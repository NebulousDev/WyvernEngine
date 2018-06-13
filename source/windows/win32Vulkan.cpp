#include <vulkan/vulkan.h>

#include <core/common.h>
#include <core/platform/platform.h>

#include <vector>

RESULT Win32VulkanCreateInstance(ApplicationInfo appInfo, VkInstance* instance)
{
	VkApplicationInfo applicationInfo = {};
	applicationInfo.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.pApplicationName	= appInfo.appName;
	applicationInfo.engineVersion		= 1;
	applicationInfo.apiVersion			= VK_API_VERSION_1_1;

	VkInstanceCreateInfo instanceInfo = {};
	instanceInfo.sType					= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pApplicationInfo		= &applicationInfo;

	VkResult result = vkCreateInstance(&instanceInfo, NULL, instance);
	if (result != VK_SUCCESS)
	{
		//TODO: Error
		return WYVERN_ERROR;
	}

	return WYVERN_SUCCESS;
}

void Win32VulkanDestroyInstance(VkInstance* instance)
{
	vkDestroyInstance(*instance, NULL);
	instance = NULL;
}

RESULT Win32VulkanEnumerateDevices(VkInstance instance, uint32* deviceCount)
{
	VkResult result = vkEnumeratePhysicalDevices(instance, deviceCount, NULL);

	if (result != VK_SUCCESS)
	{
		//TODO: Error
		return WYVERN_ERROR;
	}

	if (*deviceCount == 0)
	{
		//TODO: Error
		return WYVERN_ERROR;
	}

	//TODO: replace std:vector with custom vector
	std::vector<VkPhysicalDevice> devices(*deviceCount);
	result = vkEnumeratePhysicalDevices(instance, deviceCount, &devices[0]);

	if (result != VK_SUCCESS)
	{
		//TODO: Error
		return WYVERN_ERROR;
	}

	return WYVERN_SUCCESS;
}