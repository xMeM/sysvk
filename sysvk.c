#include <hardware/hardware.h>
#include <hardware/hwvulkan.h>

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL
vk_icdGetInstanceProcAddr(VkInstance instance, const char *pName) {
  hw_module_t *module;
  int ret =
      hw_get_module(HWVULKAN_HARDWARE_MODULE_ID, (const hw_module_t **)&module);
  if (ret) {
    return NULL;
  }
  hwvulkan_device_t *sysvk = NULL;
  module->methods->open(module, HWVULKAN_DEVICE_0, (hw_device_t **)&sysvk);
  if (!sysvk) {
    return NULL;
  }
  return sysvk->GetInstanceProcAddr(instance, pName);
}

PFN_vkVoidFunction vk_icdGetPhysicalDeviceProcAddr(VkInstance _instance,
                                                   const char *pName) {
  return NULL;
}

VKAPI_ATTR VkResult VKAPI_CALL
vk_icdNegotiateLoaderICDInterfaceVersion(uint32_t *pSupportedVersion) {
#define MIN(i, j) (((i) < (j)) ? (i) : (j))
  *pSupportedVersion = MIN(*pSupportedVersion, 5u);
  return VK_SUCCESS;
}
