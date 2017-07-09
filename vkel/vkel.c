//========================================================================
// Name
//     Vulkan (Cross-Platform) Extension Loader
//
// Repository
//     https://github.com/MrVallentin/vkel
//
// Overview
//     This is a simple, dynamic and tiny cross-platform Vulkan
//     extension loader.
//
// Dependencies
//     Vulkan (library)
//     Windows (header) - needed for library loading on Windows
//     dlfcn (header) - needed for library loading on non-Windows OS'
//     Standard C Libraries (stdio, stdlib, string, assert) - needed for NULL, malloc()
//                                                 calloc(), free(), memset(), assert()
//
// Notice
//     Copyright (c) 2016 Christian Vallentin <mail@vallentinsource.com>
//
// Developers & Contributors
//     Christian Vallentin <mail@vallentinsource.com>
//
// Version History
//     Last Modified Date: May 16, 2016
//     Revision: 14
//     Version: 2.0.11
//
// Revision History
//     Revision 12, 2016/05/02
//       - Fixed "for loop initial declarations are only
//         allowed in C99 mode".
//
//     Revision 3, 2016/02/26
//       - Rewrote vkel_gen.py, now it parses and directly
//         adds vulkan.h and vk_platform.h into vkel.h,
//         along with moving the appropriate copyrights
//         to the top of vkel.h.
//       - Fixed/added better differentiation for instance
//         and device related calls.
//       - Removed the need for having the vukan.h and
//         vk_platform.h headers.
//
//     Revision 2, 2016/02/24
//       - Created a Python script for automatically generating
//         all the extensions and their functions. (Tested with
//         Python 3.5.1)
//       - Added cross-platform support, for loading libraries
//         and getting the function addresses.
//       - Fixed so platform specific functions defaults to NULL
//       - Added missing include for dlfcn (used on non-Window OS')
//
//     Revision 1, 2016/02/23
//       - Implemented the basic version supporting a few (manually
//         written) dynamically loaded functions.
//
//------------------------------------------------------------------------
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//========================================================================

/*
** Copyright (c) 2015-2017 The Khronos Group Inc.
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#include "vkel.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#include <stdio.h> /* NULL, printf() */
#include <stdlib.h> /* malloc(), calloc(), free() */
#include <string.h> /* memset() */
#include <assert.h> /* assert() */


#ifdef VK_USE_PLATFORM_WIN32_KHR

#ifndef VC_EXTRALEAN
#	define VC_EXTRALEAN
#endif

#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#endif

// STOP THAT, BAD WINDOWS!
#ifndef NOMINMAX
#	define NOMINMAX
#endif

#include <Windows.h>
#else

#include <dlfcn.h>

#endif


#ifdef VK_USE_PLATFORM_WIN32_KHR
#	define vkelPlatformOpenLibrary(name) LoadLibraryA(name)
#	define vkelPlatformCloseLibrary(handle) FreeLibrary((HMODULE) handle)
#	define vkelPlatformGetProcAddr(handle, name) GetProcAddress((HMODULE) handle, name)
// #elif defined(__APPLE__) || defined(__linux__) || defined(__ANDROID__) || defined(__unix__ )
#else
#define vkelPlatformOpenLibrary(name) dlopen(name, RTLD_LAZY | RTLD_LOCAL)
#define vkelPlatformCloseLibrary(handle) dlclose(handle)
#define vkelPlatformGetProcAddr(handle, name) dlsym(handle, name)
// #else
// #	error VKEL Unsupported Platform
#endif

static void *vkelVkLibHandle;


// Instance and device extension names
VkBool32 VKEL_AMD_draw_indirect_count;
VkBool32 VKEL_AMD_gcn_shader;
VkBool32 VKEL_AMD_gpu_shader_half_float;
VkBool32 VKEL_AMD_gpu_shader_int16;
VkBool32 VKEL_AMD_negative_viewport_height;
VkBool32 VKEL_AMD_rasterization_order;
VkBool32 VKEL_AMD_shader_ballot;
VkBool32 VKEL_AMD_shader_explicit_vertex_parameter;
VkBool32 VKEL_AMD_shader_trinary_minmax;
VkBool32 VKEL_AMD_texture_gather_bias_lod;
VkBool32 VKEL_EXT_acquire_xlib_display;
VkBool32 VKEL_EXT_blend_operation_advanced;
VkBool32 VKEL_EXT_debug_marker;
VkBool32 VKEL_EXT_debug_report;
VkBool32 VKEL_EXT_direct_mode_display;
VkBool32 VKEL_EXT_discard_rectangles;
VkBool32 VKEL_EXT_display_control;
VkBool32 VKEL_EXT_display_surface_counter;
VkBool32 VKEL_EXT_hdr_metadata;
VkBool32 VKEL_EXT_sampler_filter_minmax;
VkBool32 VKEL_EXT_shader_subgroup_ballot;
VkBool32 VKEL_EXT_shader_subgroup_vote;
VkBool32 VKEL_EXT_swapchain_colorspace;
VkBool32 VKEL_EXT_validation_flags;
VkBool32 VKEL_GOOGLE_display_timing;
VkBool32 VKEL_IMG_filter_cubic;
VkBool32 VKEL_IMG_format_pvrtc;
VkBool32 VKEL_KHR_android_surface;
VkBool32 VKEL_KHR_descriptor_update_template;
VkBool32 VKEL_KHR_display;
VkBool32 VKEL_KHR_display_swapchain;
VkBool32 VKEL_KHR_get_physical_device_properties2;
VkBool32 VKEL_KHR_get_surface_capabilities2;
VkBool32 VKEL_KHR_incremental_present;
VkBool32 VKEL_KHR_maintenance1;
VkBool32 VKEL_KHR_mir_surface;
VkBool32 VKEL_KHR_push_descriptor;
VkBool32 VKEL_KHR_sampler_mirror_clamp_to_edge;
VkBool32 VKEL_KHR_shader_draw_parameters;
VkBool32 VKEL_KHR_shared_presentable_image;
VkBool32 VKEL_KHR_surface;
VkBool32 VKEL_KHR_swapchain;
VkBool32 VKEL_KHR_wayland_surface;
VkBool32 VKEL_KHR_win32_surface;
VkBool32 VKEL_KHR_xcb_surface;
VkBool32 VKEL_KHR_xlib_surface;
VkBool32 VKEL_KHX_device_group;
VkBool32 VKEL_KHX_device_group_creation;
VkBool32 VKEL_KHX_external_memory;
VkBool32 VKEL_KHX_external_memory_capabilities;
VkBool32 VKEL_KHX_external_memory_fd;
VkBool32 VKEL_KHX_external_memory_win32;
VkBool32 VKEL_KHX_external_semaphore;
VkBool32 VKEL_KHX_external_semaphore_capabilities;
VkBool32 VKEL_KHX_external_semaphore_fd;
VkBool32 VKEL_KHX_external_semaphore_win32;
VkBool32 VKEL_KHX_multiview;
VkBool32 VKEL_KHX_win32_keyed_mutex;
VkBool32 VKEL_MVK_ios_surface;
VkBool32 VKEL_MVK_macos_surface;
VkBool32 VKEL_NN_vi_surface;
VkBool32 VKEL_NVX_device_generated_commands;
VkBool32 VKEL_NVX_multiview_per_view_attributes;
VkBool32 VKEL_NV_clip_space_w_scaling;
VkBool32 VKEL_NV_dedicated_allocation;
VkBool32 VKEL_NV_external_memory;
VkBool32 VKEL_NV_external_memory_capabilities;
VkBool32 VKEL_NV_external_memory_win32;
VkBool32 VKEL_NV_fill_rectangle;
VkBool32 VKEL_NV_fragment_coverage_to_color;
VkBool32 VKEL_NV_framebuffer_mixed_samples;
VkBool32 VKEL_NV_geometry_shader_passthrough;
VkBool32 VKEL_NV_glsl_shader;
VkBool32 VKEL_NV_sample_mask_override_coverage;
VkBool32 VKEL_NV_viewport_array2;
VkBool32 VKEL_NV_viewport_swizzle;
VkBool32 VKEL_NV_win32_keyed_mutex;

// Instance and device layer names
VkBool32 VKEL_LAYER_GOOGLE_unique_objects;
VkBool32 VKEL_LAYER_LUNARG_api_dump;
VkBool32 VKEL_LAYER_LUNARG_device_limits;
VkBool32 VKEL_LAYER_LUNARG_draw_state;
VkBool32 VKEL_LAYER_LUNARG_image;
VkBool32 VKEL_LAYER_LUNARG_mem_tracker;
VkBool32 VKEL_LAYER_LUNARG_object_tracker;
VkBool32 VKEL_LAYER_LUNARG_param_checker;
VkBool32 VKEL_LAYER_LUNARG_screenshot;
VkBool32 VKEL_LAYER_LUNARG_swapchain;
VkBool32 VKEL_LAYER_LUNARG_threading;
VkBool32 VKEL_LAYER_LUNARG_vktrace;


// Functions
PFN_vkAcquireNextImage2KHX __vkAcquireNextImage2KHX;
PFN_vkAcquireNextImageKHR __vkAcquireNextImageKHR;
PFN_vkAllocateCommandBuffers __vkAllocateCommandBuffers;
PFN_vkAllocateDescriptorSets __vkAllocateDescriptorSets;
PFN_vkAllocateMemory __vkAllocateMemory;
PFN_vkAllocationFunction __vkAllocationFunction;
PFN_vkBeginCommandBuffer __vkBeginCommandBuffer;
PFN_vkBindBufferMemory __vkBindBufferMemory;
PFN_vkBindBufferMemory2KHX __vkBindBufferMemory2KHX;
PFN_vkBindImageMemory __vkBindImageMemory;
PFN_vkBindImageMemory2KHX __vkBindImageMemory2KHX;
PFN_vkCmdBeginQuery __vkCmdBeginQuery;
PFN_vkCmdBeginRenderPass __vkCmdBeginRenderPass;
PFN_vkCmdBindDescriptorSets __vkCmdBindDescriptorSets;
PFN_vkCmdBindIndexBuffer __vkCmdBindIndexBuffer;
PFN_vkCmdBindPipeline __vkCmdBindPipeline;
PFN_vkCmdBindVertexBuffers __vkCmdBindVertexBuffers;
PFN_vkCmdBlitImage __vkCmdBlitImage;
PFN_vkCmdClearAttachments __vkCmdClearAttachments;
PFN_vkCmdClearColorImage __vkCmdClearColorImage;
PFN_vkCmdClearDepthStencilImage __vkCmdClearDepthStencilImage;
PFN_vkCmdCopyBuffer __vkCmdCopyBuffer;
PFN_vkCmdCopyBufferToImage __vkCmdCopyBufferToImage;
PFN_vkCmdCopyImage __vkCmdCopyImage;
PFN_vkCmdCopyImageToBuffer __vkCmdCopyImageToBuffer;
PFN_vkCmdCopyQueryPoolResults __vkCmdCopyQueryPoolResults;
PFN_vkCmdDebugMarkerBeginEXT __vkCmdDebugMarkerBeginEXT;
PFN_vkCmdDebugMarkerEndEXT __vkCmdDebugMarkerEndEXT;
PFN_vkCmdDebugMarkerInsertEXT __vkCmdDebugMarkerInsertEXT;
PFN_vkCmdDispatch __vkCmdDispatch;
PFN_vkCmdDispatchBaseKHX __vkCmdDispatchBaseKHX;
PFN_vkCmdDispatchIndirect __vkCmdDispatchIndirect;
PFN_vkCmdDraw __vkCmdDraw;
PFN_vkCmdDrawIndexed __vkCmdDrawIndexed;
PFN_vkCmdDrawIndexedIndirect __vkCmdDrawIndexedIndirect;
PFN_vkCmdDrawIndexedIndirectCountAMD __vkCmdDrawIndexedIndirectCountAMD;
PFN_vkCmdDrawIndirect __vkCmdDrawIndirect;
PFN_vkCmdDrawIndirectCountAMD __vkCmdDrawIndirectCountAMD;
PFN_vkCmdEndQuery __vkCmdEndQuery;
PFN_vkCmdEndRenderPass __vkCmdEndRenderPass;
PFN_vkCmdExecuteCommands __vkCmdExecuteCommands;
PFN_vkCmdFillBuffer __vkCmdFillBuffer;
PFN_vkCmdNextSubpass __vkCmdNextSubpass;
PFN_vkCmdPipelineBarrier __vkCmdPipelineBarrier;
PFN_vkCmdProcessCommandsNVX __vkCmdProcessCommandsNVX;
PFN_vkCmdPushConstants __vkCmdPushConstants;
PFN_vkCmdPushDescriptorSetKHR __vkCmdPushDescriptorSetKHR;
PFN_vkCmdPushDescriptorSetWithTemplateKHR __vkCmdPushDescriptorSetWithTemplateKHR;
PFN_vkCmdReserveSpaceForCommandsNVX __vkCmdReserveSpaceForCommandsNVX;
PFN_vkCmdResetEvent __vkCmdResetEvent;
PFN_vkCmdResetQueryPool __vkCmdResetQueryPool;
PFN_vkCmdResolveImage __vkCmdResolveImage;
PFN_vkCmdSetBlendConstants __vkCmdSetBlendConstants;
PFN_vkCmdSetDepthBias __vkCmdSetDepthBias;
PFN_vkCmdSetDepthBounds __vkCmdSetDepthBounds;
PFN_vkCmdSetDeviceMaskKHX __vkCmdSetDeviceMaskKHX;
PFN_vkCmdSetDiscardRectangleEXT __vkCmdSetDiscardRectangleEXT;
PFN_vkCmdSetEvent __vkCmdSetEvent;
PFN_vkCmdSetLineWidth __vkCmdSetLineWidth;
PFN_vkCmdSetScissor __vkCmdSetScissor;
PFN_vkCmdSetStencilCompareMask __vkCmdSetStencilCompareMask;
PFN_vkCmdSetStencilReference __vkCmdSetStencilReference;
PFN_vkCmdSetStencilWriteMask __vkCmdSetStencilWriteMask;
PFN_vkCmdSetViewport __vkCmdSetViewport;
PFN_vkCmdSetViewportWScalingNV __vkCmdSetViewportWScalingNV;
PFN_vkCmdUpdateBuffer __vkCmdUpdateBuffer;
PFN_vkCmdWaitEvents __vkCmdWaitEvents;
PFN_vkCmdWriteTimestamp __vkCmdWriteTimestamp;
PFN_vkCreateBuffer __vkCreateBuffer;
PFN_vkCreateBufferView __vkCreateBufferView;
PFN_vkCreateCommandPool __vkCreateCommandPool;
PFN_vkCreateComputePipelines __vkCreateComputePipelines;
PFN_vkCreateDebugReportCallbackEXT __vkCreateDebugReportCallbackEXT;
PFN_vkCreateDescriptorPool __vkCreateDescriptorPool;
PFN_vkCreateDescriptorSetLayout __vkCreateDescriptorSetLayout;
PFN_vkCreateDescriptorUpdateTemplateKHR __vkCreateDescriptorUpdateTemplateKHR;
PFN_vkCreateDevice __vkCreateDevice;
PFN_vkCreateDisplayModeKHR __vkCreateDisplayModeKHR;
PFN_vkCreateDisplayPlaneSurfaceKHR __vkCreateDisplayPlaneSurfaceKHR;
PFN_vkCreateEvent __vkCreateEvent;
PFN_vkCreateFence __vkCreateFence;
PFN_vkCreateFramebuffer __vkCreateFramebuffer;
PFN_vkCreateGraphicsPipelines __vkCreateGraphicsPipelines;
PFN_vkCreateImage __vkCreateImage;
PFN_vkCreateImageView __vkCreateImageView;
PFN_vkCreateIndirectCommandsLayoutNVX __vkCreateIndirectCommandsLayoutNVX;
PFN_vkCreateInstance __vkCreateInstance;
PFN_vkCreateObjectTableNVX __vkCreateObjectTableNVX;
PFN_vkCreatePipelineCache __vkCreatePipelineCache;
PFN_vkCreatePipelineLayout __vkCreatePipelineLayout;
PFN_vkCreateQueryPool __vkCreateQueryPool;
PFN_vkCreateRenderPass __vkCreateRenderPass;
PFN_vkCreateSampler __vkCreateSampler;
PFN_vkCreateSemaphore __vkCreateSemaphore;
PFN_vkCreateShaderModule __vkCreateShaderModule;
PFN_vkCreateSharedSwapchainsKHR __vkCreateSharedSwapchainsKHR;
PFN_vkCreateSwapchainKHR __vkCreateSwapchainKHR;
PFN_vkDebugMarkerSetObjectNameEXT __vkDebugMarkerSetObjectNameEXT;
PFN_vkDebugMarkerSetObjectTagEXT __vkDebugMarkerSetObjectTagEXT;
PFN_vkDebugReportCallbackEXT __vkDebugReportCallbackEXT;
PFN_vkDebugReportMessageEXT __vkDebugReportMessageEXT;
PFN_vkDestroyBuffer __vkDestroyBuffer;
PFN_vkDestroyBufferView __vkDestroyBufferView;
PFN_vkDestroyCommandPool __vkDestroyCommandPool;
PFN_vkDestroyDebugReportCallbackEXT __vkDestroyDebugReportCallbackEXT;
PFN_vkDestroyDescriptorPool __vkDestroyDescriptorPool;
PFN_vkDestroyDescriptorSetLayout __vkDestroyDescriptorSetLayout;
PFN_vkDestroyDescriptorUpdateTemplateKHR __vkDestroyDescriptorUpdateTemplateKHR;
PFN_vkDestroyDevice __vkDestroyDevice;
PFN_vkDestroyEvent __vkDestroyEvent;
PFN_vkDestroyFence __vkDestroyFence;
PFN_vkDestroyFramebuffer __vkDestroyFramebuffer;
PFN_vkDestroyImage __vkDestroyImage;
PFN_vkDestroyImageView __vkDestroyImageView;
PFN_vkDestroyIndirectCommandsLayoutNVX __vkDestroyIndirectCommandsLayoutNVX;
PFN_vkDestroyInstance __vkDestroyInstance;
PFN_vkDestroyObjectTableNVX __vkDestroyObjectTableNVX;
PFN_vkDestroyPipeline __vkDestroyPipeline;
PFN_vkDestroyPipelineCache __vkDestroyPipelineCache;
PFN_vkDestroyPipelineLayout __vkDestroyPipelineLayout;
PFN_vkDestroyQueryPool __vkDestroyQueryPool;
PFN_vkDestroyRenderPass __vkDestroyRenderPass;
PFN_vkDestroySampler __vkDestroySampler;
PFN_vkDestroySemaphore __vkDestroySemaphore;
PFN_vkDestroyShaderModule __vkDestroyShaderModule;
PFN_vkDestroySurfaceKHR __vkDestroySurfaceKHR;
PFN_vkDestroySwapchainKHR __vkDestroySwapchainKHR;
PFN_vkDeviceWaitIdle __vkDeviceWaitIdle;
PFN_vkDisplayPowerControlEXT __vkDisplayPowerControlEXT;
PFN_vkEndCommandBuffer __vkEndCommandBuffer;
PFN_vkEnumerateDeviceExtensionProperties __vkEnumerateDeviceExtensionProperties;
PFN_vkEnumerateDeviceLayerProperties __vkEnumerateDeviceLayerProperties;
PFN_vkEnumerateInstanceExtensionProperties __vkEnumerateInstanceExtensionProperties;
PFN_vkEnumerateInstanceLayerProperties __vkEnumerateInstanceLayerProperties;
PFN_vkEnumeratePhysicalDeviceGroupsKHX __vkEnumeratePhysicalDeviceGroupsKHX;
PFN_vkEnumeratePhysicalDevices __vkEnumeratePhysicalDevices;
PFN_vkFlushMappedMemoryRanges __vkFlushMappedMemoryRanges;
PFN_vkFreeCommandBuffers __vkFreeCommandBuffers;
PFN_vkFreeDescriptorSets __vkFreeDescriptorSets;
PFN_vkFreeFunction __vkFreeFunction;
PFN_vkFreeMemory __vkFreeMemory;
PFN_vkGetBufferMemoryRequirements __vkGetBufferMemoryRequirements;
PFN_vkGetDeviceGroupPeerMemoryFeaturesKHX __vkGetDeviceGroupPeerMemoryFeaturesKHX;
PFN_vkGetDeviceGroupPresentCapabilitiesKHX __vkGetDeviceGroupPresentCapabilitiesKHX;
PFN_vkGetDeviceGroupSurfacePresentModesKHX __vkGetDeviceGroupSurfacePresentModesKHX;
PFN_vkGetDeviceMemoryCommitment __vkGetDeviceMemoryCommitment;
PFN_vkGetDeviceProcAddr __vkGetDeviceProcAddr;
PFN_vkGetDeviceQueue __vkGetDeviceQueue;
PFN_vkGetDisplayModePropertiesKHR __vkGetDisplayModePropertiesKHR;
PFN_vkGetDisplayPlaneCapabilitiesKHR __vkGetDisplayPlaneCapabilitiesKHR;
PFN_vkGetDisplayPlaneSupportedDisplaysKHR __vkGetDisplayPlaneSupportedDisplaysKHR;
PFN_vkGetEventStatus __vkGetEventStatus;
PFN_vkGetFenceStatus __vkGetFenceStatus;
PFN_vkGetImageMemoryRequirements __vkGetImageMemoryRequirements;
PFN_vkGetImageSparseMemoryRequirements __vkGetImageSparseMemoryRequirements;
PFN_vkGetImageSubresourceLayout __vkGetImageSubresourceLayout;
PFN_vkGetInstanceProcAddr __vkGetInstanceProcAddr;
PFN_vkGetMemoryFdKHX __vkGetMemoryFdKHX;
PFN_vkGetMemoryFdPropertiesKHX __vkGetMemoryFdPropertiesKHX;
PFN_vkGetPastPresentationTimingGOOGLE __vkGetPastPresentationTimingGOOGLE;
PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR __vkGetPhysicalDeviceDisplayPlanePropertiesKHR;
PFN_vkGetPhysicalDeviceDisplayPropertiesKHR __vkGetPhysicalDeviceDisplayPropertiesKHR;
PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHX __vkGetPhysicalDeviceExternalBufferPropertiesKHX;
PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV __vkGetPhysicalDeviceExternalImageFormatPropertiesNV;
PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHX __vkGetPhysicalDeviceExternalSemaphorePropertiesKHX;
PFN_vkGetPhysicalDeviceFeatures __vkGetPhysicalDeviceFeatures;
PFN_vkGetPhysicalDeviceFeatures2KHR __vkGetPhysicalDeviceFeatures2KHR;
PFN_vkGetPhysicalDeviceFormatProperties __vkGetPhysicalDeviceFormatProperties;
PFN_vkGetPhysicalDeviceFormatProperties2KHR __vkGetPhysicalDeviceFormatProperties2KHR;
PFN_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX __vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX;
PFN_vkGetPhysicalDeviceImageFormatProperties __vkGetPhysicalDeviceImageFormatProperties;
PFN_vkGetPhysicalDeviceImageFormatProperties2KHR __vkGetPhysicalDeviceImageFormatProperties2KHR;
PFN_vkGetPhysicalDeviceMemoryProperties __vkGetPhysicalDeviceMemoryProperties;
PFN_vkGetPhysicalDeviceMemoryProperties2KHR __vkGetPhysicalDeviceMemoryProperties2KHR;
PFN_vkGetPhysicalDevicePresentRectanglesKHX __vkGetPhysicalDevicePresentRectanglesKHX;
PFN_vkGetPhysicalDeviceProperties __vkGetPhysicalDeviceProperties;
PFN_vkGetPhysicalDeviceProperties2KHR __vkGetPhysicalDeviceProperties2KHR;
PFN_vkGetPhysicalDeviceQueueFamilyProperties __vkGetPhysicalDeviceQueueFamilyProperties;
PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR __vkGetPhysicalDeviceQueueFamilyProperties2KHR;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties __vkGetPhysicalDeviceSparseImageFormatProperties;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR __vkGetPhysicalDeviceSparseImageFormatProperties2KHR;
PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT __vkGetPhysicalDeviceSurfaceCapabilities2EXT;
PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR __vkGetPhysicalDeviceSurfaceCapabilities2KHR;
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR __vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
PFN_vkGetPhysicalDeviceSurfaceFormats2KHR __vkGetPhysicalDeviceSurfaceFormats2KHR;
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR __vkGetPhysicalDeviceSurfaceFormatsKHR;
PFN_vkGetPhysicalDeviceSurfacePresentModesKHR __vkGetPhysicalDeviceSurfacePresentModesKHR;
PFN_vkGetPhysicalDeviceSurfaceSupportKHR __vkGetPhysicalDeviceSurfaceSupportKHR;
PFN_vkGetPipelineCacheData __vkGetPipelineCacheData;
PFN_vkGetQueryPoolResults __vkGetQueryPoolResults;
PFN_vkGetRefreshCycleDurationGOOGLE __vkGetRefreshCycleDurationGOOGLE;
PFN_vkGetRenderAreaGranularity __vkGetRenderAreaGranularity;
PFN_vkGetSemaphoreFdKHX __vkGetSemaphoreFdKHX;
PFN_vkGetSwapchainCounterEXT __vkGetSwapchainCounterEXT;
PFN_vkGetSwapchainImagesKHR __vkGetSwapchainImagesKHR;
PFN_vkGetSwapchainStatusKHR __vkGetSwapchainStatusKHR;
PFN_vkImportSemaphoreFdKHX __vkImportSemaphoreFdKHX;
PFN_vkInternalAllocationNotification __vkInternalAllocationNotification;
PFN_vkInternalFreeNotification __vkInternalFreeNotification;
PFN_vkInvalidateMappedMemoryRanges __vkInvalidateMappedMemoryRanges;
PFN_vkMapMemory __vkMapMemory;
PFN_vkMergePipelineCaches __vkMergePipelineCaches;
PFN_vkQueueBindSparse __vkQueueBindSparse;
PFN_vkQueuePresentKHR __vkQueuePresentKHR;
PFN_vkQueueSubmit __vkQueueSubmit;
PFN_vkQueueWaitIdle __vkQueueWaitIdle;
PFN_vkReallocationFunction __vkReallocationFunction;
PFN_vkRegisterDeviceEventEXT __vkRegisterDeviceEventEXT;
PFN_vkRegisterDisplayEventEXT __vkRegisterDisplayEventEXT;
PFN_vkRegisterObjectsNVX __vkRegisterObjectsNVX;
PFN_vkReleaseDisplayEXT __vkReleaseDisplayEXT;
PFN_vkResetCommandBuffer __vkResetCommandBuffer;
PFN_vkResetCommandPool __vkResetCommandPool;
PFN_vkResetDescriptorPool __vkResetDescriptorPool;
PFN_vkResetEvent __vkResetEvent;
PFN_vkResetFences __vkResetFences;
PFN_vkSetEvent __vkSetEvent;
PFN_vkSetHdrMetadataEXT __vkSetHdrMetadataEXT;
PFN_vkTrimCommandPoolKHR __vkTrimCommandPoolKHR;
PFN_vkUnmapMemory __vkUnmapMemory;
PFN_vkUnregisterObjectsNVX __vkUnregisterObjectsNVX;
PFN_vkUpdateDescriptorSetWithTemplateKHR __vkUpdateDescriptorSetWithTemplateKHR;
PFN_vkUpdateDescriptorSets __vkUpdateDescriptorSets;
PFN_vkVoidFunction __vkVoidFunction;
PFN_vkWaitForFences __vkWaitForFences;

#ifdef VK_USE_PLATFORM_ANDROID_KHR
PFN_vkCreateAndroidSurfaceKHR __vkCreateAndroidSurfaceKHR;
#endif /* VK_USE_PLATFORM_ANDROID_KHR */

#ifdef VK_USE_PLATFORM_IOS_MVK
PFN_vkCreateIOSSurfaceMVK __vkCreateIOSSurfaceMVK;
#endif /* VK_USE_PLATFORM_IOS_MVK */

#ifdef VK_USE_PLATFORM_MACOS_MVK
PFN_vkCreateMacOSSurfaceMVK __vkCreateMacOSSurfaceMVK;
#endif /* VK_USE_PLATFORM_MACOS_MVK */

#ifdef VK_USE_PLATFORM_MIR_KHR
PFN_vkCreateMirSurfaceKHR __vkCreateMirSurfaceKHR;
PFN_vkGetPhysicalDeviceMirPresentationSupportKHR __vkGetPhysicalDeviceMirPresentationSupportKHR;
#endif /* VK_USE_PLATFORM_MIR_KHR */

#ifdef VK_USE_PLATFORM_VI_NN
PFN_vkCreateViSurfaceNN __vkCreateViSurfaceNN;
#endif /* VK_USE_PLATFORM_VI_NN */

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
PFN_vkCreateWaylandSurfaceKHR __vkCreateWaylandSurfaceKHR;
PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR __vkGetPhysicalDeviceWaylandPresentationSupportKHR;
#endif /* VK_USE_PLATFORM_WAYLAND_KHR */

#ifdef VK_USE_PLATFORM_WIN32_KHR
PFN_vkCreateWin32SurfaceKHR __vkCreateWin32SurfaceKHR;
PFN_vkGetMemoryWin32HandleNV __vkGetMemoryWin32HandleNV;
PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR __vkGetPhysicalDeviceWin32PresentationSupportKHR;
#endif /* VK_USE_PLATFORM_WIN32_KHR */

#ifdef VK_USE_PLATFORM_WIN32_KHX
PFN_vkGetMemoryWin32HandleKHX __vkGetMemoryWin32HandleKHX;
PFN_vkGetMemoryWin32HandlePropertiesKHX __vkGetMemoryWin32HandlePropertiesKHX;
PFN_vkGetSemaphoreWin32HandleKHX __vkGetSemaphoreWin32HandleKHX;
PFN_vkImportSemaphoreWin32HandleKHX __vkImportSemaphoreWin32HandleKHX;
#endif /* VK_USE_PLATFORM_WIN32_KHX */

#ifdef VK_USE_PLATFORM_XCB_KHR
PFN_vkCreateXcbSurfaceKHR __vkCreateXcbSurfaceKHR;
PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR __vkGetPhysicalDeviceXcbPresentationSupportKHR;
#endif /* VK_USE_PLATFORM_XCB_KHR */

#ifdef VK_USE_PLATFORM_XLIB_KHR
PFN_vkCreateXlibSurfaceKHR __vkCreateXlibSurfaceKHR;
PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR __vkGetPhysicalDeviceXlibPresentationSupportKHR;
#endif /* VK_USE_PLATFORM_XLIB_KHR */

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
PFN_vkAcquireXlibDisplayEXT __vkAcquireXlibDisplayEXT;
PFN_vkGetRandROutputDisplayEXT __vkGetRandROutputDisplayEXT;
#endif /* VK_USE_PLATFORM_XLIB_XRANDR_EXT */


PFN_vkVoidFunction vkelGetProcAddr(const char *name)
{
	return (PFN_vkVoidFunction) vkelPlatformGetProcAddr(vkelVkLibHandle, name);
}

PFN_vkVoidFunction vkelGetInstanceProcAddr(VkInstance instance, const char *pName)
{
	PFN_vkVoidFunction proc = (PFN_vkVoidFunction) vkGetInstanceProcAddr(instance, pName);

	if (!proc)
		proc = (PFN_vkVoidFunction) vkelGetProcAddr(pName);

	return proc;
}

PFN_vkVoidFunction vkelGetDeviceProcAddr(VkDevice device, const char *pName)
{
	PFN_vkVoidFunction proc = (PFN_vkVoidFunction) vkGetDeviceProcAddr(device, pName);

	if (!proc)
		proc = (PFN_vkVoidFunction) vkelGetInstanceProcAddr(NULL, pName);

	return proc;
}


static int vkel_strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++, str2++;
	}

	return *(const unsigned char*) str1 - *(const unsigned char*) str2;
}

static void vkel_strpy(char *dest, char *src)
{
	while (*dest++ = *src++);
}


void vkelDeleteNames(uint32_t nameCount, char **names)
{
	// assert(names);
	if (!names)
		return;

	uint32_t nameIndex = 0;
	for (nameIndex = 0; nameIndex < nameCount; nameIndex++)
	{
		// assert(names[nameIndex]);
		if (!names[nameIndex])
			continue;

		free(names[nameIndex]);
	}

	free(names);
}


char** vkelGetInstanceExtensionNames(const char *pLayerName, uint32_t *extensionNameCount)
{
	assert(extensionNameCount);


	VkResult err;


	uint32_t extPropertyCount;
	err = vkEnumerateInstanceExtensionProperties(pLayerName, &extPropertyCount, NULL);
	assert(!err);

	(*extensionNameCount) = extPropertyCount;

	if (extPropertyCount < 1)
		return NULL;


	char **extensionNames = (char**) calloc(extPropertyCount, sizeof(char*));

	uint32_t extensionNameIndex = 0;
	for (extensionNameIndex = 0; extensionNameIndex < extPropertyCount; extensionNameIndex++)
	{
		extensionNames[extensionNameIndex] = (char*)calloc(VK_MAX_EXTENSION_NAME_SIZE, sizeof(char));
	}


	VkExtensionProperties *extProperties = (VkExtensionProperties*) calloc(extPropertyCount, sizeof(VkExtensionProperties));
	assert(extProperties);


	err = vkEnumerateInstanceExtensionProperties(pLayerName, &extPropertyCount, extProperties);
	assert(!err);

	uint32_t extPropertyIndex = 0;
	for (extPropertyIndex = 0; extPropertyIndex < extPropertyCount; extPropertyIndex++)
	{
		VkExtensionProperties extProperty = extProperties[extPropertyIndex];

		vkel_strpy(extensionNames[extPropertyIndex], extProperty.extensionName);
	}


	free(extProperties);


	return extensionNames;
}

char** vkelGetInstanceLayerNames(uint32_t *layerNameCount)
{
	assert(layerNameCount);


	VkResult err;


	uint32_t layerPropertyCount;
	err = vkEnumerateInstanceLayerProperties(&layerPropertyCount, NULL);
	assert(!err);

	(*layerNameCount) = layerPropertyCount;

	if (layerPropertyCount < 1)
		return NULL;


	char **layerNames = (char**) calloc(layerPropertyCount, sizeof(char*));

	uint32_t layerNameIndex = 0;
	for (layerNameIndex = 0; layerNameIndex < layerPropertyCount; layerNameIndex++)
	{
		layerNames[layerNameIndex] = (char*) calloc(VK_MAX_EXTENSION_NAME_SIZE, sizeof(char));
	}


	VkLayerProperties *layerProperties = (VkLayerProperties*) calloc(layerPropertyCount, sizeof(VkLayerProperties));
	assert(layerProperties);

	err = vkEnumerateInstanceLayerProperties(&layerPropertyCount, layerProperties);
	assert(!err);

	uint32_t layerPropertyIndex = 0;
	for (layerPropertyIndex = 0; layerPropertyIndex < layerPropertyCount; layerPropertyIndex++)
	{
		VkLayerProperties layerProperty = layerProperties[layerPropertyIndex];

		vkel_strpy(layerNames[layerPropertyIndex], layerProperty.layerName);
	}


	free(layerProperties);


	return layerNames;
}


char** vkelGetDeviceExtensionNames(VkPhysicalDevice physicalDevice, const char *pLayerName, uint32_t *extensionNameCount)
{
	assert(extensionNameCount);


	VkResult err;


	uint32_t extPropertyCount;
	err = vkEnumerateDeviceExtensionProperties(physicalDevice, pLayerName, &extPropertyCount, NULL);
	assert(!err);

	(*extensionNameCount) = extPropertyCount;

	if (extPropertyCount < 1)
		return NULL;


	char **extensionNames = (char**) calloc(extPropertyCount, sizeof(char*));

	uint32_t extensionNameIndex = 0;
	for (extensionNameIndex = 0; extensionNameIndex < extPropertyCount; extensionNameIndex++)
	{
		extensionNames[extensionNameIndex] = (char*) calloc(VK_MAX_EXTENSION_NAME_SIZE, sizeof(char));
	}


	VkExtensionProperties *extProperties = (VkExtensionProperties*) calloc(extPropertyCount, sizeof(VkExtensionProperties));
	assert(extProperties);


	err = vkEnumerateDeviceExtensionProperties(physicalDevice, pLayerName, &extPropertyCount, extProperties);
	assert(!err);

	uint32_t extPropertyIndex = 0;
	for (extPropertyIndex = 0; extPropertyIndex < extPropertyCount; extPropertyIndex++)
	{
		VkExtensionProperties extProperty = extProperties[extPropertyIndex];

		vkel_strpy(extensionNames[extPropertyIndex], extProperty.extensionName);
	}


	free(extProperties);


	return extensionNames;
}

char** vkelGetDeviceLayerNames(VkPhysicalDevice physicalDevice, uint32_t *layerNameCount)
{
	assert(layerNameCount);


	VkResult err;


	uint32_t layerPropertyCount;
	err = vkEnumerateDeviceLayerProperties(physicalDevice, &layerPropertyCount, NULL);
	assert(!err);

	(*layerNameCount) = layerPropertyCount;

	if (layerPropertyCount < 1)
		return NULL;


	char **layerNames = (char**) calloc(layerPropertyCount, sizeof(char*));

	uint32_t layerNameIndex = 0;
	for (layerNameIndex = 0; layerNameIndex < layerPropertyCount; layerNameIndex++)
	{
		layerNames[layerNameIndex] = (char*) calloc(VK_MAX_EXTENSION_NAME_SIZE, sizeof(char));
	}


	VkLayerProperties *layerProperties = (VkLayerProperties*) calloc(layerPropertyCount, sizeof(VkLayerProperties));
	assert(layerProperties);

	err = vkEnumerateDeviceLayerProperties(physicalDevice, &layerPropertyCount, layerProperties);
	assert(!err);

	uint32_t layerPropertyIndex = 0;
	for (layerPropertyIndex = 0; layerPropertyIndex < layerPropertyCount; layerPropertyIndex++)
	{
		VkLayerProperties layerProperty = layerProperties[layerPropertyIndex];

		vkel_strpy(layerNames[layerPropertyIndex], layerProperty.layerName);
	}


	free(layerProperties);


	return layerNames;
}


VkBool32 vkelIsInstanceLayerSupported(const char *pLayerName)
{
	uint32_t layerNameCount = 0;
	char **layerNames = vkelGetInstanceLayerNames(&layerNameCount);

	uint32_t layerNameIndex = 0;
	for (layerNameIndex = 0; layerNameIndex < layerNameCount; layerNameIndex++)
	{
		if (vkel_strcmp(layerNames[layerNameIndex], pLayerName))
		{
			vkelDeleteInstanceLayerNames(layerNameCount, layerNames);

			return VK_TRUE;
		}
	}

	vkelDeleteInstanceLayerNames(layerNameCount, layerNames);

	return VK_FALSE;
}

VkBool32 vkelIsInstanceExtensionSupported(const char *pLayerName, const char *pExtensionName)
{
	uint32_t extensionNameCount = 0;
	char **extensionNames = vkelGetInstanceExtensionNames(pLayerName, &extensionNameCount);

	uint32_t extensionNameIndex = 0;
	for (extensionNameIndex = 0; extensionNameIndex < extensionNameCount; extensionNameIndex++)
	{
		if (vkel_strcmp(extensionNames[extensionNameIndex], pExtensionName))
		{
			vkelDeleteInstanceExtensionNames(extensionNameCount, extensionNames);

			return VK_TRUE;
		}
	}

	vkelDeleteInstanceExtensionNames(extensionNameCount, extensionNames);

	return VK_FALSE;
}


VkBool32 vkelIsDeviceLayerSupported(VkPhysicalDevice physicalDevice, const char *pLayerName)
{
	uint32_t layerNameCount = 0;
	char **layerNames = vkelGetDeviceLayerNames(physicalDevice, &layerNameCount);

	uint32_t layerNameIndex = 0;
	for (layerNameIndex = 0; layerNameIndex < layerNameCount; layerNameIndex++)
	{
		if (vkel_strcmp(layerNames[layerNameIndex], pLayerName))
		{
			vkelDeleteDeviceLayerNames(layerNameCount, layerNames);

			return VK_TRUE;
		}
	}

	vkelDeleteDeviceLayerNames(layerNameCount, layerNames);

	return VK_FALSE;
}

VkBool32 vkelIsDeviceExtensionSupported(VkPhysicalDevice physicalDevice, const char *pLayerName, const char *pExtensionName)
{
	uint32_t extensionNameCount = 0;
	char **extensionNames = vkelGetDeviceExtensionNames(physicalDevice, pLayerName, &extensionNameCount);

	uint32_t extensionNameIndex = 0;
	for (extensionNameIndex = 0; extensionNameIndex < extensionNameCount; extensionNameIndex++)
	{
		if (vkel_strcmp(extensionNames[extensionNameIndex], pExtensionName))
		{
			vkelDeleteDeviceExtensionNames(extensionNameCount, extensionNames);

			return VK_TRUE;
		}
	}

	vkelDeleteDeviceExtensionNames(extensionNameCount, extensionNames);

	return VK_FALSE;
}


VkBool32 vkelInit(void)
{
	vkelUninit();

#ifdef VK_USE_PLATFORM_WIN32_KHR
	const char *name = "vulkan-1.dll";
#else
	const char *name = "libvulkan.so.1";
#endif

	vkelVkLibHandle = vkelPlatformOpenLibrary(name);

	if (!vkelVkLibHandle)
		return VK_FALSE;


	__vkAcquireNextImage2KHX = (PFN_vkAcquireNextImage2KHX) vkelGetProcAddr("vkAcquireNextImage2KHX");
	__vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR) vkelGetProcAddr("vkAcquireNextImageKHR");
	__vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers) vkelGetProcAddr("vkAllocateCommandBuffers");
	__vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets) vkelGetProcAddr("vkAllocateDescriptorSets");
	__vkAllocateMemory = (PFN_vkAllocateMemory) vkelGetProcAddr("vkAllocateMemory");
	__vkAllocationFunction = (PFN_vkAllocationFunction) vkelGetProcAddr("vkAllocationFunction");
	__vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer) vkelGetProcAddr("vkBeginCommandBuffer");
	__vkBindBufferMemory = (PFN_vkBindBufferMemory) vkelGetProcAddr("vkBindBufferMemory");
	__vkBindBufferMemory2KHX = (PFN_vkBindBufferMemory2KHX) vkelGetProcAddr("vkBindBufferMemory2KHX");
	__vkBindImageMemory = (PFN_vkBindImageMemory) vkelGetProcAddr("vkBindImageMemory");
	__vkBindImageMemory2KHX = (PFN_vkBindImageMemory2KHX) vkelGetProcAddr("vkBindImageMemory2KHX");
	__vkCmdBeginQuery = (PFN_vkCmdBeginQuery) vkelGetProcAddr("vkCmdBeginQuery");
	__vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass) vkelGetProcAddr("vkCmdBeginRenderPass");
	__vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets) vkelGetProcAddr("vkCmdBindDescriptorSets");
	__vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer) vkelGetProcAddr("vkCmdBindIndexBuffer");
	__vkCmdBindPipeline = (PFN_vkCmdBindPipeline) vkelGetProcAddr("vkCmdBindPipeline");
	__vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers) vkelGetProcAddr("vkCmdBindVertexBuffers");
	__vkCmdBlitImage = (PFN_vkCmdBlitImage) vkelGetProcAddr("vkCmdBlitImage");
	__vkCmdClearAttachments = (PFN_vkCmdClearAttachments) vkelGetProcAddr("vkCmdClearAttachments");
	__vkCmdClearColorImage = (PFN_vkCmdClearColorImage) vkelGetProcAddr("vkCmdClearColorImage");
	__vkCmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage) vkelGetProcAddr("vkCmdClearDepthStencilImage");
	__vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer) vkelGetProcAddr("vkCmdCopyBuffer");
	__vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage) vkelGetProcAddr("vkCmdCopyBufferToImage");
	__vkCmdCopyImage = (PFN_vkCmdCopyImage) vkelGetProcAddr("vkCmdCopyImage");
	__vkCmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer) vkelGetProcAddr("vkCmdCopyImageToBuffer");
	__vkCmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults) vkelGetProcAddr("vkCmdCopyQueryPoolResults");
	__vkCmdDebugMarkerBeginEXT = (PFN_vkCmdDebugMarkerBeginEXT) vkelGetProcAddr("vkCmdDebugMarkerBeginEXT");
	__vkCmdDebugMarkerEndEXT = (PFN_vkCmdDebugMarkerEndEXT) vkelGetProcAddr("vkCmdDebugMarkerEndEXT");
	__vkCmdDebugMarkerInsertEXT = (PFN_vkCmdDebugMarkerInsertEXT) vkelGetProcAddr("vkCmdDebugMarkerInsertEXT");
	__vkCmdDispatch = (PFN_vkCmdDispatch) vkelGetProcAddr("vkCmdDispatch");
	__vkCmdDispatchBaseKHX = (PFN_vkCmdDispatchBaseKHX) vkelGetProcAddr("vkCmdDispatchBaseKHX");
	__vkCmdDispatchIndirect = (PFN_vkCmdDispatchIndirect) vkelGetProcAddr("vkCmdDispatchIndirect");
	__vkCmdDraw = (PFN_vkCmdDraw) vkelGetProcAddr("vkCmdDraw");
	__vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed) vkelGetProcAddr("vkCmdDrawIndexed");
	__vkCmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect) vkelGetProcAddr("vkCmdDrawIndexedIndirect");
	__vkCmdDrawIndexedIndirectCountAMD = (PFN_vkCmdDrawIndexedIndirectCountAMD) vkelGetProcAddr("vkCmdDrawIndexedIndirectCountAMD");
	__vkCmdDrawIndirect = (PFN_vkCmdDrawIndirect) vkelGetProcAddr("vkCmdDrawIndirect");
	__vkCmdDrawIndirectCountAMD = (PFN_vkCmdDrawIndirectCountAMD) vkelGetProcAddr("vkCmdDrawIndirectCountAMD");
	__vkCmdEndQuery = (PFN_vkCmdEndQuery) vkelGetProcAddr("vkCmdEndQuery");
	__vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass) vkelGetProcAddr("vkCmdEndRenderPass");
	__vkCmdExecuteCommands = (PFN_vkCmdExecuteCommands) vkelGetProcAddr("vkCmdExecuteCommands");
	__vkCmdFillBuffer = (PFN_vkCmdFillBuffer) vkelGetProcAddr("vkCmdFillBuffer");
	__vkCmdNextSubpass = (PFN_vkCmdNextSubpass) vkelGetProcAddr("vkCmdNextSubpass");
	__vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier) vkelGetProcAddr("vkCmdPipelineBarrier");
	__vkCmdProcessCommandsNVX = (PFN_vkCmdProcessCommandsNVX) vkelGetProcAddr("vkCmdProcessCommandsNVX");
	__vkCmdPushConstants = (PFN_vkCmdPushConstants) vkelGetProcAddr("vkCmdPushConstants");
	__vkCmdPushDescriptorSetKHR = (PFN_vkCmdPushDescriptorSetKHR) vkelGetProcAddr("vkCmdPushDescriptorSetKHR");
	__vkCmdPushDescriptorSetWithTemplateKHR = (PFN_vkCmdPushDescriptorSetWithTemplateKHR) vkelGetProcAddr("vkCmdPushDescriptorSetWithTemplateKHR");
	__vkCmdReserveSpaceForCommandsNVX = (PFN_vkCmdReserveSpaceForCommandsNVX) vkelGetProcAddr("vkCmdReserveSpaceForCommandsNVX");
	__vkCmdResetEvent = (PFN_vkCmdResetEvent) vkelGetProcAddr("vkCmdResetEvent");
	__vkCmdResetQueryPool = (PFN_vkCmdResetQueryPool) vkelGetProcAddr("vkCmdResetQueryPool");
	__vkCmdResolveImage = (PFN_vkCmdResolveImage) vkelGetProcAddr("vkCmdResolveImage");
	__vkCmdSetBlendConstants = (PFN_vkCmdSetBlendConstants) vkelGetProcAddr("vkCmdSetBlendConstants");
	__vkCmdSetDepthBias = (PFN_vkCmdSetDepthBias) vkelGetProcAddr("vkCmdSetDepthBias");
	__vkCmdSetDepthBounds = (PFN_vkCmdSetDepthBounds) vkelGetProcAddr("vkCmdSetDepthBounds");
	__vkCmdSetDeviceMaskKHX = (PFN_vkCmdSetDeviceMaskKHX) vkelGetProcAddr("vkCmdSetDeviceMaskKHX");
	__vkCmdSetDiscardRectangleEXT = (PFN_vkCmdSetDiscardRectangleEXT) vkelGetProcAddr("vkCmdSetDiscardRectangleEXT");
	__vkCmdSetEvent = (PFN_vkCmdSetEvent) vkelGetProcAddr("vkCmdSetEvent");
	__vkCmdSetLineWidth = (PFN_vkCmdSetLineWidth) vkelGetProcAddr("vkCmdSetLineWidth");
	__vkCmdSetScissor = (PFN_vkCmdSetScissor) vkelGetProcAddr("vkCmdSetScissor");
	__vkCmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask) vkelGetProcAddr("vkCmdSetStencilCompareMask");
	__vkCmdSetStencilReference = (PFN_vkCmdSetStencilReference) vkelGetProcAddr("vkCmdSetStencilReference");
	__vkCmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask) vkelGetProcAddr("vkCmdSetStencilWriteMask");
	__vkCmdSetViewport = (PFN_vkCmdSetViewport) vkelGetProcAddr("vkCmdSetViewport");
	__vkCmdSetViewportWScalingNV = (PFN_vkCmdSetViewportWScalingNV) vkelGetProcAddr("vkCmdSetViewportWScalingNV");
	__vkCmdUpdateBuffer = (PFN_vkCmdUpdateBuffer) vkelGetProcAddr("vkCmdUpdateBuffer");
	__vkCmdWaitEvents = (PFN_vkCmdWaitEvents) vkelGetProcAddr("vkCmdWaitEvents");
	__vkCmdWriteTimestamp = (PFN_vkCmdWriteTimestamp) vkelGetProcAddr("vkCmdWriteTimestamp");
	__vkCreateBuffer = (PFN_vkCreateBuffer) vkelGetProcAddr("vkCreateBuffer");
	__vkCreateBufferView = (PFN_vkCreateBufferView) vkelGetProcAddr("vkCreateBufferView");
	__vkCreateCommandPool = (PFN_vkCreateCommandPool) vkelGetProcAddr("vkCreateCommandPool");
	__vkCreateComputePipelines = (PFN_vkCreateComputePipelines) vkelGetProcAddr("vkCreateComputePipelines");
	__vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT) vkelGetProcAddr("vkCreateDebugReportCallbackEXT");
	__vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool) vkelGetProcAddr("vkCreateDescriptorPool");
	__vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout) vkelGetProcAddr("vkCreateDescriptorSetLayout");
	__vkCreateDescriptorUpdateTemplateKHR = (PFN_vkCreateDescriptorUpdateTemplateKHR) vkelGetProcAddr("vkCreateDescriptorUpdateTemplateKHR");
	__vkCreateDevice = (PFN_vkCreateDevice) vkelGetProcAddr("vkCreateDevice");
	__vkCreateDisplayModeKHR = (PFN_vkCreateDisplayModeKHR) vkelGetProcAddr("vkCreateDisplayModeKHR");
	__vkCreateDisplayPlaneSurfaceKHR = (PFN_vkCreateDisplayPlaneSurfaceKHR) vkelGetProcAddr("vkCreateDisplayPlaneSurfaceKHR");
	__vkCreateEvent = (PFN_vkCreateEvent) vkelGetProcAddr("vkCreateEvent");
	__vkCreateFence = (PFN_vkCreateFence) vkelGetProcAddr("vkCreateFence");
	__vkCreateFramebuffer = (PFN_vkCreateFramebuffer) vkelGetProcAddr("vkCreateFramebuffer");
	__vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines) vkelGetProcAddr("vkCreateGraphicsPipelines");
	__vkCreateImage = (PFN_vkCreateImage) vkelGetProcAddr("vkCreateImage");
	__vkCreateImageView = (PFN_vkCreateImageView) vkelGetProcAddr("vkCreateImageView");
	__vkCreateIndirectCommandsLayoutNVX = (PFN_vkCreateIndirectCommandsLayoutNVX) vkelGetProcAddr("vkCreateIndirectCommandsLayoutNVX");
	__vkCreateInstance = (PFN_vkCreateInstance) vkelGetProcAddr("vkCreateInstance");
	__vkCreateObjectTableNVX = (PFN_vkCreateObjectTableNVX) vkelGetProcAddr("vkCreateObjectTableNVX");
	__vkCreatePipelineCache = (PFN_vkCreatePipelineCache) vkelGetProcAddr("vkCreatePipelineCache");
	__vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout) vkelGetProcAddr("vkCreatePipelineLayout");
	__vkCreateQueryPool = (PFN_vkCreateQueryPool) vkelGetProcAddr("vkCreateQueryPool");
	__vkCreateRenderPass = (PFN_vkCreateRenderPass) vkelGetProcAddr("vkCreateRenderPass");
	__vkCreateSampler = (PFN_vkCreateSampler) vkelGetProcAddr("vkCreateSampler");
	__vkCreateSemaphore = (PFN_vkCreateSemaphore) vkelGetProcAddr("vkCreateSemaphore");
	__vkCreateShaderModule = (PFN_vkCreateShaderModule) vkelGetProcAddr("vkCreateShaderModule");
	__vkCreateSharedSwapchainsKHR = (PFN_vkCreateSharedSwapchainsKHR) vkelGetProcAddr("vkCreateSharedSwapchainsKHR");
	__vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR) vkelGetProcAddr("vkCreateSwapchainKHR");
	__vkDebugMarkerSetObjectNameEXT = (PFN_vkDebugMarkerSetObjectNameEXT) vkelGetProcAddr("vkDebugMarkerSetObjectNameEXT");
	__vkDebugMarkerSetObjectTagEXT = (PFN_vkDebugMarkerSetObjectTagEXT) vkelGetProcAddr("vkDebugMarkerSetObjectTagEXT");
	__vkDebugReportCallbackEXT = (PFN_vkDebugReportCallbackEXT) vkelGetProcAddr("vkDebugReportCallbackEXT");
	__vkDebugReportMessageEXT = (PFN_vkDebugReportMessageEXT) vkelGetProcAddr("vkDebugReportMessageEXT");
	__vkDestroyBuffer = (PFN_vkDestroyBuffer) vkelGetProcAddr("vkDestroyBuffer");
	__vkDestroyBufferView = (PFN_vkDestroyBufferView) vkelGetProcAddr("vkDestroyBufferView");
	__vkDestroyCommandPool = (PFN_vkDestroyCommandPool) vkelGetProcAddr("vkDestroyCommandPool");
	__vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT) vkelGetProcAddr("vkDestroyDebugReportCallbackEXT");
	__vkDestroyDescriptorPool = (PFN_vkDestroyDescriptorPool) vkelGetProcAddr("vkDestroyDescriptorPool");
	__vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout) vkelGetProcAddr("vkDestroyDescriptorSetLayout");
	__vkDestroyDescriptorUpdateTemplateKHR = (PFN_vkDestroyDescriptorUpdateTemplateKHR) vkelGetProcAddr("vkDestroyDescriptorUpdateTemplateKHR");
	__vkDestroyDevice = (PFN_vkDestroyDevice) vkelGetProcAddr("vkDestroyDevice");
	__vkDestroyEvent = (PFN_vkDestroyEvent) vkelGetProcAddr("vkDestroyEvent");
	__vkDestroyFence = (PFN_vkDestroyFence) vkelGetProcAddr("vkDestroyFence");
	__vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer) vkelGetProcAddr("vkDestroyFramebuffer");
	__vkDestroyImage = (PFN_vkDestroyImage) vkelGetProcAddr("vkDestroyImage");
	__vkDestroyImageView = (PFN_vkDestroyImageView) vkelGetProcAddr("vkDestroyImageView");
	__vkDestroyIndirectCommandsLayoutNVX = (PFN_vkDestroyIndirectCommandsLayoutNVX) vkelGetProcAddr("vkDestroyIndirectCommandsLayoutNVX");
	__vkDestroyInstance = (PFN_vkDestroyInstance) vkelGetProcAddr("vkDestroyInstance");
	__vkDestroyObjectTableNVX = (PFN_vkDestroyObjectTableNVX) vkelGetProcAddr("vkDestroyObjectTableNVX");
	__vkDestroyPipeline = (PFN_vkDestroyPipeline) vkelGetProcAddr("vkDestroyPipeline");
	__vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache) vkelGetProcAddr("vkDestroyPipelineCache");
	__vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout) vkelGetProcAddr("vkDestroyPipelineLayout");
	__vkDestroyQueryPool = (PFN_vkDestroyQueryPool) vkelGetProcAddr("vkDestroyQueryPool");
	__vkDestroyRenderPass = (PFN_vkDestroyRenderPass) vkelGetProcAddr("vkDestroyRenderPass");
	__vkDestroySampler = (PFN_vkDestroySampler) vkelGetProcAddr("vkDestroySampler");
	__vkDestroySemaphore = (PFN_vkDestroySemaphore) vkelGetProcAddr("vkDestroySemaphore");
	__vkDestroyShaderModule = (PFN_vkDestroyShaderModule) vkelGetProcAddr("vkDestroyShaderModule");
	__vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR) vkelGetProcAddr("vkDestroySurfaceKHR");
	__vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR) vkelGetProcAddr("vkDestroySwapchainKHR");
	__vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle) vkelGetProcAddr("vkDeviceWaitIdle");
	__vkDisplayPowerControlEXT = (PFN_vkDisplayPowerControlEXT) vkelGetProcAddr("vkDisplayPowerControlEXT");
	__vkEndCommandBuffer = (PFN_vkEndCommandBuffer) vkelGetProcAddr("vkEndCommandBuffer");
	__vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties) vkelGetProcAddr("vkEnumerateDeviceExtensionProperties");
	__vkEnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties) vkelGetProcAddr("vkEnumerateDeviceLayerProperties");
	__vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties) vkelGetProcAddr("vkEnumerateInstanceExtensionProperties");
	__vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties) vkelGetProcAddr("vkEnumerateInstanceLayerProperties");
	__vkEnumeratePhysicalDeviceGroupsKHX = (PFN_vkEnumeratePhysicalDeviceGroupsKHX) vkelGetProcAddr("vkEnumeratePhysicalDeviceGroupsKHX");
	__vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices) vkelGetProcAddr("vkEnumeratePhysicalDevices");
	__vkFlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges) vkelGetProcAddr("vkFlushMappedMemoryRanges");
	__vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers) vkelGetProcAddr("vkFreeCommandBuffers");
	__vkFreeDescriptorSets = (PFN_vkFreeDescriptorSets) vkelGetProcAddr("vkFreeDescriptorSets");
	__vkFreeFunction = (PFN_vkFreeFunction) vkelGetProcAddr("vkFreeFunction");
	__vkFreeMemory = (PFN_vkFreeMemory) vkelGetProcAddr("vkFreeMemory");
	__vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements) vkelGetProcAddr("vkGetBufferMemoryRequirements");
	__vkGetDeviceGroupPeerMemoryFeaturesKHX = (PFN_vkGetDeviceGroupPeerMemoryFeaturesKHX) vkelGetProcAddr("vkGetDeviceGroupPeerMemoryFeaturesKHX");
	__vkGetDeviceGroupPresentCapabilitiesKHX = (PFN_vkGetDeviceGroupPresentCapabilitiesKHX) vkelGetProcAddr("vkGetDeviceGroupPresentCapabilitiesKHX");
	__vkGetDeviceGroupSurfacePresentModesKHX = (PFN_vkGetDeviceGroupSurfacePresentModesKHX) vkelGetProcAddr("vkGetDeviceGroupSurfacePresentModesKHX");
	__vkGetDeviceMemoryCommitment = (PFN_vkGetDeviceMemoryCommitment) vkelGetProcAddr("vkGetDeviceMemoryCommitment");
	__vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr) vkelGetProcAddr("vkGetDeviceProcAddr");
	__vkGetDeviceQueue = (PFN_vkGetDeviceQueue) vkelGetProcAddr("vkGetDeviceQueue");
	__vkGetDisplayModePropertiesKHR = (PFN_vkGetDisplayModePropertiesKHR) vkelGetProcAddr("vkGetDisplayModePropertiesKHR");
	__vkGetDisplayPlaneCapabilitiesKHR = (PFN_vkGetDisplayPlaneCapabilitiesKHR) vkelGetProcAddr("vkGetDisplayPlaneCapabilitiesKHR");
	__vkGetDisplayPlaneSupportedDisplaysKHR = (PFN_vkGetDisplayPlaneSupportedDisplaysKHR) vkelGetProcAddr("vkGetDisplayPlaneSupportedDisplaysKHR");
	__vkGetEventStatus = (PFN_vkGetEventStatus) vkelGetProcAddr("vkGetEventStatus");
	__vkGetFenceStatus = (PFN_vkGetFenceStatus) vkelGetProcAddr("vkGetFenceStatus");
	__vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements) vkelGetProcAddr("vkGetImageMemoryRequirements");
	__vkGetImageSparseMemoryRequirements = (PFN_vkGetImageSparseMemoryRequirements) vkelGetProcAddr("vkGetImageSparseMemoryRequirements");
	__vkGetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout) vkelGetProcAddr("vkGetImageSubresourceLayout");
	__vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) vkelGetProcAddr("vkGetInstanceProcAddr");
	__vkGetMemoryFdKHX = (PFN_vkGetMemoryFdKHX) vkelGetProcAddr("vkGetMemoryFdKHX");
	__vkGetMemoryFdPropertiesKHX = (PFN_vkGetMemoryFdPropertiesKHX) vkelGetProcAddr("vkGetMemoryFdPropertiesKHX");
	__vkGetPastPresentationTimingGOOGLE = (PFN_vkGetPastPresentationTimingGOOGLE) vkelGetProcAddr("vkGetPastPresentationTimingGOOGLE");
	__vkGetPhysicalDeviceDisplayPlanePropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR) vkelGetProcAddr("vkGetPhysicalDeviceDisplayPlanePropertiesKHR");
	__vkGetPhysicalDeviceDisplayPropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPropertiesKHR) vkelGetProcAddr("vkGetPhysicalDeviceDisplayPropertiesKHR");
	__vkGetPhysicalDeviceExternalBufferPropertiesKHX = (PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHX) vkelGetProcAddr("vkGetPhysicalDeviceExternalBufferPropertiesKHX");
	__vkGetPhysicalDeviceExternalImageFormatPropertiesNV = (PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV) vkelGetProcAddr("vkGetPhysicalDeviceExternalImageFormatPropertiesNV");
	__vkGetPhysicalDeviceExternalSemaphorePropertiesKHX = (PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHX) vkelGetProcAddr("vkGetPhysicalDeviceExternalSemaphorePropertiesKHX");
	__vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures) vkelGetProcAddr("vkGetPhysicalDeviceFeatures");
	__vkGetPhysicalDeviceFeatures2KHR = (PFN_vkGetPhysicalDeviceFeatures2KHR) vkelGetProcAddr("vkGetPhysicalDeviceFeatures2KHR");
	__vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties) vkelGetProcAddr("vkGetPhysicalDeviceFormatProperties");
	__vkGetPhysicalDeviceFormatProperties2KHR = (PFN_vkGetPhysicalDeviceFormatProperties2KHR) vkelGetProcAddr("vkGetPhysicalDeviceFormatProperties2KHR");
	__vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX = (PFN_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX) vkelGetProcAddr("vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX");
	__vkGetPhysicalDeviceImageFormatProperties = (PFN_vkGetPhysicalDeviceImageFormatProperties) vkelGetProcAddr("vkGetPhysicalDeviceImageFormatProperties");
	__vkGetPhysicalDeviceImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceImageFormatProperties2KHR) vkelGetProcAddr("vkGetPhysicalDeviceImageFormatProperties2KHR");
	__vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties) vkelGetProcAddr("vkGetPhysicalDeviceMemoryProperties");
	__vkGetPhysicalDeviceMemoryProperties2KHR = (PFN_vkGetPhysicalDeviceMemoryProperties2KHR) vkelGetProcAddr("vkGetPhysicalDeviceMemoryProperties2KHR");
	__vkGetPhysicalDevicePresentRectanglesKHX = (PFN_vkGetPhysicalDevicePresentRectanglesKHX) vkelGetProcAddr("vkGetPhysicalDevicePresentRectanglesKHX");
	__vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties) vkelGetProcAddr("vkGetPhysicalDeviceProperties");
	__vkGetPhysicalDeviceProperties2KHR = (PFN_vkGetPhysicalDeviceProperties2KHR) vkelGetProcAddr("vkGetPhysicalDeviceProperties2KHR");
	__vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties) vkelGetProcAddr("vkGetPhysicalDeviceQueueFamilyProperties");
	__vkGetPhysicalDeviceQueueFamilyProperties2KHR = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR) vkelGetProcAddr("vkGetPhysicalDeviceQueueFamilyProperties2KHR");
	__vkGetPhysicalDeviceSparseImageFormatProperties = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties) vkelGetProcAddr("vkGetPhysicalDeviceSparseImageFormatProperties");
	__vkGetPhysicalDeviceSparseImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR) vkelGetProcAddr("vkGetPhysicalDeviceSparseImageFormatProperties2KHR");
	__vkGetPhysicalDeviceSurfaceCapabilities2EXT = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT) vkelGetProcAddr("vkGetPhysicalDeviceSurfaceCapabilities2EXT");
	__vkGetPhysicalDeviceSurfaceCapabilities2KHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR) vkelGetProcAddr("vkGetPhysicalDeviceSurfaceCapabilities2KHR");
	__vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR) vkelGetProcAddr("vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
	__vkGetPhysicalDeviceSurfaceFormats2KHR = (PFN_vkGetPhysicalDeviceSurfaceFormats2KHR) vkelGetProcAddr("vkGetPhysicalDeviceSurfaceFormats2KHR");
	__vkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR) vkelGetProcAddr("vkGetPhysicalDeviceSurfaceFormatsKHR");
	__vkGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR) vkelGetProcAddr("vkGetPhysicalDeviceSurfacePresentModesKHR");
	__vkGetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR) vkelGetProcAddr("vkGetPhysicalDeviceSurfaceSupportKHR");
	__vkGetPipelineCacheData = (PFN_vkGetPipelineCacheData) vkelGetProcAddr("vkGetPipelineCacheData");
	__vkGetQueryPoolResults = (PFN_vkGetQueryPoolResults) vkelGetProcAddr("vkGetQueryPoolResults");
	__vkGetRefreshCycleDurationGOOGLE = (PFN_vkGetRefreshCycleDurationGOOGLE) vkelGetProcAddr("vkGetRefreshCycleDurationGOOGLE");
	__vkGetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity) vkelGetProcAddr("vkGetRenderAreaGranularity");
	__vkGetSemaphoreFdKHX = (PFN_vkGetSemaphoreFdKHX) vkelGetProcAddr("vkGetSemaphoreFdKHX");
	__vkGetSwapchainCounterEXT = (PFN_vkGetSwapchainCounterEXT) vkelGetProcAddr("vkGetSwapchainCounterEXT");
	__vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR) vkelGetProcAddr("vkGetSwapchainImagesKHR");
	__vkGetSwapchainStatusKHR = (PFN_vkGetSwapchainStatusKHR) vkelGetProcAddr("vkGetSwapchainStatusKHR");
	__vkImportSemaphoreFdKHX = (PFN_vkImportSemaphoreFdKHX) vkelGetProcAddr("vkImportSemaphoreFdKHX");
	__vkInternalAllocationNotification = (PFN_vkInternalAllocationNotification) vkelGetProcAddr("vkInternalAllocationNotification");
	__vkInternalFreeNotification = (PFN_vkInternalFreeNotification) vkelGetProcAddr("vkInternalFreeNotification");
	__vkInvalidateMappedMemoryRanges = (PFN_vkInvalidateMappedMemoryRanges) vkelGetProcAddr("vkInvalidateMappedMemoryRanges");
	__vkMapMemory = (PFN_vkMapMemory) vkelGetProcAddr("vkMapMemory");
	__vkMergePipelineCaches = (PFN_vkMergePipelineCaches) vkelGetProcAddr("vkMergePipelineCaches");
	__vkQueueBindSparse = (PFN_vkQueueBindSparse) vkelGetProcAddr("vkQueueBindSparse");
	__vkQueuePresentKHR = (PFN_vkQueuePresentKHR) vkelGetProcAddr("vkQueuePresentKHR");
	__vkQueueSubmit = (PFN_vkQueueSubmit) vkelGetProcAddr("vkQueueSubmit");
	__vkQueueWaitIdle = (PFN_vkQueueWaitIdle) vkelGetProcAddr("vkQueueWaitIdle");
	__vkReallocationFunction = (PFN_vkReallocationFunction) vkelGetProcAddr("vkReallocationFunction");
	__vkRegisterDeviceEventEXT = (PFN_vkRegisterDeviceEventEXT) vkelGetProcAddr("vkRegisterDeviceEventEXT");
	__vkRegisterDisplayEventEXT = (PFN_vkRegisterDisplayEventEXT) vkelGetProcAddr("vkRegisterDisplayEventEXT");
	__vkRegisterObjectsNVX = (PFN_vkRegisterObjectsNVX) vkelGetProcAddr("vkRegisterObjectsNVX");
	__vkReleaseDisplayEXT = (PFN_vkReleaseDisplayEXT) vkelGetProcAddr("vkReleaseDisplayEXT");
	__vkResetCommandBuffer = (PFN_vkResetCommandBuffer) vkelGetProcAddr("vkResetCommandBuffer");
	__vkResetCommandPool = (PFN_vkResetCommandPool) vkelGetProcAddr("vkResetCommandPool");
	__vkResetDescriptorPool = (PFN_vkResetDescriptorPool) vkelGetProcAddr("vkResetDescriptorPool");
	__vkResetEvent = (PFN_vkResetEvent) vkelGetProcAddr("vkResetEvent");
	__vkResetFences = (PFN_vkResetFences) vkelGetProcAddr("vkResetFences");
	__vkSetEvent = (PFN_vkSetEvent) vkelGetProcAddr("vkSetEvent");
	__vkSetHdrMetadataEXT = (PFN_vkSetHdrMetadataEXT) vkelGetProcAddr("vkSetHdrMetadataEXT");
	__vkTrimCommandPoolKHR = (PFN_vkTrimCommandPoolKHR) vkelGetProcAddr("vkTrimCommandPoolKHR");
	__vkUnmapMemory = (PFN_vkUnmapMemory) vkelGetProcAddr("vkUnmapMemory");
	__vkUnregisterObjectsNVX = (PFN_vkUnregisterObjectsNVX) vkelGetProcAddr("vkUnregisterObjectsNVX");
	__vkUpdateDescriptorSetWithTemplateKHR = (PFN_vkUpdateDescriptorSetWithTemplateKHR) vkelGetProcAddr("vkUpdateDescriptorSetWithTemplateKHR");
	__vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets) vkelGetProcAddr("vkUpdateDescriptorSets");
	__vkVoidFunction = (PFN_vkVoidFunction) vkelGetProcAddr("vkVoidFunction");
	__vkWaitForFences = (PFN_vkWaitForFences) vkelGetProcAddr("vkWaitForFences");

#ifdef VK_USE_PLATFORM_ANDROID_KHR
	__vkCreateAndroidSurfaceKHR = (PFN_vkCreateAndroidSurfaceKHR) vkelGetProcAddr("vkCreateAndroidSurfaceKHR");
#endif /* VK_USE_PLATFORM_ANDROID_KHR */

#ifdef VK_USE_PLATFORM_IOS_MVK
	__vkCreateIOSSurfaceMVK = (PFN_vkCreateIOSSurfaceMVK) vkelGetProcAddr("vkCreateIOSSurfaceMVK");
#endif /* VK_USE_PLATFORM_IOS_MVK */

#ifdef VK_USE_PLATFORM_MACOS_MVK
	__vkCreateMacOSSurfaceMVK = (PFN_vkCreateMacOSSurfaceMVK) vkelGetProcAddr("vkCreateMacOSSurfaceMVK");
#endif /* VK_USE_PLATFORM_MACOS_MVK */

#ifdef VK_USE_PLATFORM_MIR_KHR
	__vkCreateMirSurfaceKHR = (PFN_vkCreateMirSurfaceKHR) vkelGetProcAddr("vkCreateMirSurfaceKHR");
	__vkGetPhysicalDeviceMirPresentationSupportKHR = (PFN_vkGetPhysicalDeviceMirPresentationSupportKHR) vkelGetProcAddr("vkGetPhysicalDeviceMirPresentationSupportKHR");
#endif /* VK_USE_PLATFORM_MIR_KHR */

#ifdef VK_USE_PLATFORM_VI_NN
	__vkCreateViSurfaceNN = (PFN_vkCreateViSurfaceNN) vkelGetProcAddr("vkCreateViSurfaceNN");
#endif /* VK_USE_PLATFORM_VI_NN */

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
	__vkCreateWaylandSurfaceKHR = (PFN_vkCreateWaylandSurfaceKHR) vkelGetProcAddr("vkCreateWaylandSurfaceKHR");
	__vkGetPhysicalDeviceWaylandPresentationSupportKHR = (PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR) vkelGetProcAddr("vkGetPhysicalDeviceWaylandPresentationSupportKHR");
#endif /* VK_USE_PLATFORM_WAYLAND_KHR */

#ifdef VK_USE_PLATFORM_WIN32_KHR
	__vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR) vkelGetProcAddr("vkCreateWin32SurfaceKHR");
	__vkGetMemoryWin32HandleNV = (PFN_vkGetMemoryWin32HandleNV) vkelGetProcAddr("vkGetMemoryWin32HandleNV");
	__vkGetPhysicalDeviceWin32PresentationSupportKHR = (PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR) vkelGetProcAddr("vkGetPhysicalDeviceWin32PresentationSupportKHR");
#endif /* VK_USE_PLATFORM_WIN32_KHR */

#ifdef VK_USE_PLATFORM_WIN32_KHX
	__vkGetMemoryWin32HandleKHX = (PFN_vkGetMemoryWin32HandleKHX) vkelGetProcAddr("vkGetMemoryWin32HandleKHX");
	__vkGetMemoryWin32HandlePropertiesKHX = (PFN_vkGetMemoryWin32HandlePropertiesKHX) vkelGetProcAddr("vkGetMemoryWin32HandlePropertiesKHX");
	__vkGetSemaphoreWin32HandleKHX = (PFN_vkGetSemaphoreWin32HandleKHX) vkelGetProcAddr("vkGetSemaphoreWin32HandleKHX");
	__vkImportSemaphoreWin32HandleKHX = (PFN_vkImportSemaphoreWin32HandleKHX) vkelGetProcAddr("vkImportSemaphoreWin32HandleKHX");
#endif /* VK_USE_PLATFORM_WIN32_KHX */

#ifdef VK_USE_PLATFORM_XCB_KHR
	__vkCreateXcbSurfaceKHR = (PFN_vkCreateXcbSurfaceKHR) vkelGetProcAddr("vkCreateXcbSurfaceKHR");
	__vkGetPhysicalDeviceXcbPresentationSupportKHR = (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR) vkelGetProcAddr("vkGetPhysicalDeviceXcbPresentationSupportKHR");
#endif /* VK_USE_PLATFORM_XCB_KHR */

#ifdef VK_USE_PLATFORM_XLIB_KHR
	__vkCreateXlibSurfaceKHR = (PFN_vkCreateXlibSurfaceKHR) vkelGetProcAddr("vkCreateXlibSurfaceKHR");
	__vkGetPhysicalDeviceXlibPresentationSupportKHR = (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR) vkelGetProcAddr("vkGetPhysicalDeviceXlibPresentationSupportKHR");
#endif /* VK_USE_PLATFORM_XLIB_KHR */

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
	__vkAcquireXlibDisplayEXT = (PFN_vkAcquireXlibDisplayEXT) vkelGetProcAddr("vkAcquireXlibDisplayEXT");
	__vkGetRandROutputDisplayEXT = (PFN_vkGetRandROutputDisplayEXT) vkelGetProcAddr("vkGetRandROutputDisplayEXT");
#endif /* VK_USE_PLATFORM_XLIB_XRANDR_EXT */


	// Instance and device extension names
	VKEL_AMD_draw_indirect_count = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_draw_indirect_count");
	VKEL_AMD_gcn_shader = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_gcn_shader");
	VKEL_AMD_gpu_shader_half_float = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_gpu_shader_half_float");
	VKEL_AMD_gpu_shader_int16 = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_gpu_shader_int16");
	VKEL_AMD_negative_viewport_height = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_negative_viewport_height");
	VKEL_AMD_rasterization_order = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_rasterization_order");
	VKEL_AMD_shader_ballot = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_shader_ballot");
	VKEL_AMD_shader_explicit_vertex_parameter = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_shader_explicit_vertex_parameter");
	VKEL_AMD_shader_trinary_minmax = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_shader_trinary_minmax");
	VKEL_AMD_texture_gather_bias_lod = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_texture_gather_bias_lod");
	VKEL_EXT_acquire_xlib_display = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_acquire_xlib_display");
	VKEL_EXT_blend_operation_advanced = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_blend_operation_advanced");
	VKEL_EXT_debug_marker = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_debug_marker");
	VKEL_EXT_debug_report = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_debug_report");
	VKEL_EXT_direct_mode_display = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_direct_mode_display");
	VKEL_EXT_discard_rectangles = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_discard_rectangles");
	VKEL_EXT_display_control = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_display_control");
	VKEL_EXT_display_surface_counter = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_display_surface_counter");
	VKEL_EXT_hdr_metadata = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_hdr_metadata");
	VKEL_EXT_sampler_filter_minmax = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_sampler_filter_minmax");
	VKEL_EXT_shader_subgroup_ballot = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_shader_subgroup_ballot");
	VKEL_EXT_shader_subgroup_vote = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_shader_subgroup_vote");
	VKEL_EXT_swapchain_colorspace = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_swapchain_colorspace");
	VKEL_EXT_validation_flags = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_validation_flags");
	VKEL_GOOGLE_display_timing = vkelIsInstanceExtensionSupported(NULL, "VK_GOOGLE_display_timing");
	VKEL_IMG_filter_cubic = vkelIsInstanceExtensionSupported(NULL, "VK_IMG_filter_cubic");
	VKEL_IMG_format_pvrtc = vkelIsInstanceExtensionSupported(NULL, "VK_IMG_format_pvrtc");
	VKEL_KHR_android_surface = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_android_surface");
	VKEL_KHR_descriptor_update_template = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_descriptor_update_template");
	VKEL_KHR_display = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_display");
	VKEL_KHR_display_swapchain = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_display_swapchain");
	VKEL_KHR_get_physical_device_properties2 = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_get_physical_device_properties2");
	VKEL_KHR_get_surface_capabilities2 = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_get_surface_capabilities2");
	VKEL_KHR_incremental_present = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_incremental_present");
	VKEL_KHR_maintenance1 = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_maintenance1");
	VKEL_KHR_mir_surface = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_mir_surface");
	VKEL_KHR_push_descriptor = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_push_descriptor");
	VKEL_KHR_sampler_mirror_clamp_to_edge = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_sampler_mirror_clamp_to_edge");
	VKEL_KHR_shader_draw_parameters = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_shader_draw_parameters");
	VKEL_KHR_shared_presentable_image = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_shared_presentable_image");
	VKEL_KHR_surface = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_surface");
	VKEL_KHR_swapchain = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_swapchain");
	VKEL_KHR_wayland_surface = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_wayland_surface");
	VKEL_KHR_win32_surface = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_win32_surface");
	VKEL_KHR_xcb_surface = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_xcb_surface");
	VKEL_KHR_xlib_surface = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_xlib_surface");
	VKEL_KHX_device_group = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_device_group");
	VKEL_KHX_device_group_creation = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_device_group_creation");
	VKEL_KHX_external_memory = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_external_memory");
	VKEL_KHX_external_memory_capabilities = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_external_memory_capabilities");
	VKEL_KHX_external_memory_fd = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_external_memory_fd");
	VKEL_KHX_external_memory_win32 = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_external_memory_win32");
	VKEL_KHX_external_semaphore = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_external_semaphore");
	VKEL_KHX_external_semaphore_capabilities = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_external_semaphore_capabilities");
	VKEL_KHX_external_semaphore_fd = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_external_semaphore_fd");
	VKEL_KHX_external_semaphore_win32 = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_external_semaphore_win32");
	VKEL_KHX_multiview = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_multiview");
	VKEL_KHX_win32_keyed_mutex = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_win32_keyed_mutex");
	VKEL_MVK_ios_surface = vkelIsInstanceExtensionSupported(NULL, "VK_MVK_ios_surface");
	VKEL_MVK_macos_surface = vkelIsInstanceExtensionSupported(NULL, "VK_MVK_macos_surface");
	VKEL_NN_vi_surface = vkelIsInstanceExtensionSupported(NULL, "VK_NN_vi_surface");
	VKEL_NVX_device_generated_commands = vkelIsInstanceExtensionSupported(NULL, "VK_NVX_device_generated_commands");
	VKEL_NVX_multiview_per_view_attributes = vkelIsInstanceExtensionSupported(NULL, "VK_NVX_multiview_per_view_attributes");
	VKEL_NV_clip_space_w_scaling = vkelIsInstanceExtensionSupported(NULL, "VK_NV_clip_space_w_scaling");
	VKEL_NV_dedicated_allocation = vkelIsInstanceExtensionSupported(NULL, "VK_NV_dedicated_allocation");
	VKEL_NV_external_memory = vkelIsInstanceExtensionSupported(NULL, "VK_NV_external_memory");
	VKEL_NV_external_memory_capabilities = vkelIsInstanceExtensionSupported(NULL, "VK_NV_external_memory_capabilities");
	VKEL_NV_external_memory_win32 = vkelIsInstanceExtensionSupported(NULL, "VK_NV_external_memory_win32");
	VKEL_NV_fill_rectangle = vkelIsInstanceExtensionSupported(NULL, "VK_NV_fill_rectangle");
	VKEL_NV_fragment_coverage_to_color = vkelIsInstanceExtensionSupported(NULL, "VK_NV_fragment_coverage_to_color");
	VKEL_NV_framebuffer_mixed_samples = vkelIsInstanceExtensionSupported(NULL, "VK_NV_framebuffer_mixed_samples");
	VKEL_NV_geometry_shader_passthrough = vkelIsInstanceExtensionSupported(NULL, "VK_NV_geometry_shader_passthrough");
	VKEL_NV_glsl_shader = vkelIsInstanceExtensionSupported(NULL, "VK_NV_glsl_shader");
	VKEL_NV_sample_mask_override_coverage = vkelIsInstanceExtensionSupported(NULL, "VK_NV_sample_mask_override_coverage");
	VKEL_NV_viewport_array2 = vkelIsInstanceExtensionSupported(NULL, "VK_NV_viewport_array2");
	VKEL_NV_viewport_swizzle = vkelIsInstanceExtensionSupported(NULL, "VK_NV_viewport_swizzle");
	VKEL_NV_win32_keyed_mutex = vkelIsInstanceExtensionSupported(NULL, "VK_NV_win32_keyed_mutex");

	// Instance and device layer names
	VKEL_LAYER_GOOGLE_unique_objects = vkelIsInstanceLayerSupported("VK_LAYER_GOOGLE_unique_objects");
	VKEL_LAYER_LUNARG_api_dump = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_api_dump");
	VKEL_LAYER_LUNARG_device_limits = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_device_limits");
	VKEL_LAYER_LUNARG_draw_state = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_draw_state");
	VKEL_LAYER_LUNARG_image = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_image");
	VKEL_LAYER_LUNARG_mem_tracker = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_mem_tracker");
	VKEL_LAYER_LUNARG_object_tracker = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_object_tracker");
	VKEL_LAYER_LUNARG_param_checker = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_param_checker");
	VKEL_LAYER_LUNARG_screenshot = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_screenshot");
	VKEL_LAYER_LUNARG_swapchain = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_swapchain");
	VKEL_LAYER_LUNARG_threading = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_threading");
	VKEL_LAYER_LUNARG_vktrace = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_vktrace");


	return VK_TRUE;
}

VkBool32 vkelInstanceInit(VkInstance instance)
{
	if (!vkelVkLibHandle && !vkelInit())
		return VK_FALSE;


	__vkAcquireNextImage2KHX = (PFN_vkAcquireNextImage2KHX) vkelGetInstanceProcAddr(instance, "vkAcquireNextImage2KHX");
	__vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR) vkelGetInstanceProcAddr(instance, "vkAcquireNextImageKHR");
	__vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers) vkelGetInstanceProcAddr(instance, "vkAllocateCommandBuffers");
	__vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets) vkelGetInstanceProcAddr(instance, "vkAllocateDescriptorSets");
	__vkAllocateMemory = (PFN_vkAllocateMemory) vkelGetInstanceProcAddr(instance, "vkAllocateMemory");
	__vkAllocationFunction = (PFN_vkAllocationFunction) vkelGetInstanceProcAddr(instance, "vkAllocationFunction");
	__vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer) vkelGetInstanceProcAddr(instance, "vkBeginCommandBuffer");
	__vkBindBufferMemory = (PFN_vkBindBufferMemory) vkelGetInstanceProcAddr(instance, "vkBindBufferMemory");
	__vkBindBufferMemory2KHX = (PFN_vkBindBufferMemory2KHX) vkelGetInstanceProcAddr(instance, "vkBindBufferMemory2KHX");
	__vkBindImageMemory = (PFN_vkBindImageMemory) vkelGetInstanceProcAddr(instance, "vkBindImageMemory");
	__vkBindImageMemory2KHX = (PFN_vkBindImageMemory2KHX) vkelGetInstanceProcAddr(instance, "vkBindImageMemory2KHX");
	__vkCmdBeginQuery = (PFN_vkCmdBeginQuery) vkelGetInstanceProcAddr(instance, "vkCmdBeginQuery");
	__vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass) vkelGetInstanceProcAddr(instance, "vkCmdBeginRenderPass");
	__vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets) vkelGetInstanceProcAddr(instance, "vkCmdBindDescriptorSets");
	__vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer) vkelGetInstanceProcAddr(instance, "vkCmdBindIndexBuffer");
	__vkCmdBindPipeline = (PFN_vkCmdBindPipeline) vkelGetInstanceProcAddr(instance, "vkCmdBindPipeline");
	__vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers) vkelGetInstanceProcAddr(instance, "vkCmdBindVertexBuffers");
	__vkCmdBlitImage = (PFN_vkCmdBlitImage) vkelGetInstanceProcAddr(instance, "vkCmdBlitImage");
	__vkCmdClearAttachments = (PFN_vkCmdClearAttachments) vkelGetInstanceProcAddr(instance, "vkCmdClearAttachments");
	__vkCmdClearColorImage = (PFN_vkCmdClearColorImage) vkelGetInstanceProcAddr(instance, "vkCmdClearColorImage");
	__vkCmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage) vkelGetInstanceProcAddr(instance, "vkCmdClearDepthStencilImage");
	__vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer) vkelGetInstanceProcAddr(instance, "vkCmdCopyBuffer");
	__vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage) vkelGetInstanceProcAddr(instance, "vkCmdCopyBufferToImage");
	__vkCmdCopyImage = (PFN_vkCmdCopyImage) vkelGetInstanceProcAddr(instance, "vkCmdCopyImage");
	__vkCmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer) vkelGetInstanceProcAddr(instance, "vkCmdCopyImageToBuffer");
	__vkCmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults) vkelGetInstanceProcAddr(instance, "vkCmdCopyQueryPoolResults");
	__vkCmdDebugMarkerBeginEXT = (PFN_vkCmdDebugMarkerBeginEXT) vkelGetInstanceProcAddr(instance, "vkCmdDebugMarkerBeginEXT");
	__vkCmdDebugMarkerEndEXT = (PFN_vkCmdDebugMarkerEndEXT) vkelGetInstanceProcAddr(instance, "vkCmdDebugMarkerEndEXT");
	__vkCmdDebugMarkerInsertEXT = (PFN_vkCmdDebugMarkerInsertEXT) vkelGetInstanceProcAddr(instance, "vkCmdDebugMarkerInsertEXT");
	__vkCmdDispatch = (PFN_vkCmdDispatch) vkelGetInstanceProcAddr(instance, "vkCmdDispatch");
	__vkCmdDispatchBaseKHX = (PFN_vkCmdDispatchBaseKHX) vkelGetInstanceProcAddr(instance, "vkCmdDispatchBaseKHX");
	__vkCmdDispatchIndirect = (PFN_vkCmdDispatchIndirect) vkelGetInstanceProcAddr(instance, "vkCmdDispatchIndirect");
	__vkCmdDraw = (PFN_vkCmdDraw) vkelGetInstanceProcAddr(instance, "vkCmdDraw");
	__vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed) vkelGetInstanceProcAddr(instance, "vkCmdDrawIndexed");
	__vkCmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect) vkelGetInstanceProcAddr(instance, "vkCmdDrawIndexedIndirect");
	__vkCmdDrawIndexedIndirectCountAMD = (PFN_vkCmdDrawIndexedIndirectCountAMD) vkelGetInstanceProcAddr(instance, "vkCmdDrawIndexedIndirectCountAMD");
	__vkCmdDrawIndirect = (PFN_vkCmdDrawIndirect) vkelGetInstanceProcAddr(instance, "vkCmdDrawIndirect");
	__vkCmdDrawIndirectCountAMD = (PFN_vkCmdDrawIndirectCountAMD) vkelGetInstanceProcAddr(instance, "vkCmdDrawIndirectCountAMD");
	__vkCmdEndQuery = (PFN_vkCmdEndQuery) vkelGetInstanceProcAddr(instance, "vkCmdEndQuery");
	__vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass) vkelGetInstanceProcAddr(instance, "vkCmdEndRenderPass");
	__vkCmdExecuteCommands = (PFN_vkCmdExecuteCommands) vkelGetInstanceProcAddr(instance, "vkCmdExecuteCommands");
	__vkCmdFillBuffer = (PFN_vkCmdFillBuffer) vkelGetInstanceProcAddr(instance, "vkCmdFillBuffer");
	__vkCmdNextSubpass = (PFN_vkCmdNextSubpass) vkelGetInstanceProcAddr(instance, "vkCmdNextSubpass");
	__vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier) vkelGetInstanceProcAddr(instance, "vkCmdPipelineBarrier");
	__vkCmdProcessCommandsNVX = (PFN_vkCmdProcessCommandsNVX) vkelGetInstanceProcAddr(instance, "vkCmdProcessCommandsNVX");
	__vkCmdPushConstants = (PFN_vkCmdPushConstants) vkelGetInstanceProcAddr(instance, "vkCmdPushConstants");
	__vkCmdPushDescriptorSetKHR = (PFN_vkCmdPushDescriptorSetKHR) vkelGetInstanceProcAddr(instance, "vkCmdPushDescriptorSetKHR");
	__vkCmdPushDescriptorSetWithTemplateKHR = (PFN_vkCmdPushDescriptorSetWithTemplateKHR) vkelGetInstanceProcAddr(instance, "vkCmdPushDescriptorSetWithTemplateKHR");
	__vkCmdReserveSpaceForCommandsNVX = (PFN_vkCmdReserveSpaceForCommandsNVX) vkelGetInstanceProcAddr(instance, "vkCmdReserveSpaceForCommandsNVX");
	__vkCmdResetEvent = (PFN_vkCmdResetEvent) vkelGetInstanceProcAddr(instance, "vkCmdResetEvent");
	__vkCmdResetQueryPool = (PFN_vkCmdResetQueryPool) vkelGetInstanceProcAddr(instance, "vkCmdResetQueryPool");
	__vkCmdResolveImage = (PFN_vkCmdResolveImage) vkelGetInstanceProcAddr(instance, "vkCmdResolveImage");
	__vkCmdSetBlendConstants = (PFN_vkCmdSetBlendConstants) vkelGetInstanceProcAddr(instance, "vkCmdSetBlendConstants");
	__vkCmdSetDepthBias = (PFN_vkCmdSetDepthBias) vkelGetInstanceProcAddr(instance, "vkCmdSetDepthBias");
	__vkCmdSetDepthBounds = (PFN_vkCmdSetDepthBounds) vkelGetInstanceProcAddr(instance, "vkCmdSetDepthBounds");
	__vkCmdSetDeviceMaskKHX = (PFN_vkCmdSetDeviceMaskKHX) vkelGetInstanceProcAddr(instance, "vkCmdSetDeviceMaskKHX");
	__vkCmdSetDiscardRectangleEXT = (PFN_vkCmdSetDiscardRectangleEXT) vkelGetInstanceProcAddr(instance, "vkCmdSetDiscardRectangleEXT");
	__vkCmdSetEvent = (PFN_vkCmdSetEvent) vkelGetInstanceProcAddr(instance, "vkCmdSetEvent");
	__vkCmdSetLineWidth = (PFN_vkCmdSetLineWidth) vkelGetInstanceProcAddr(instance, "vkCmdSetLineWidth");
	__vkCmdSetScissor = (PFN_vkCmdSetScissor) vkelGetInstanceProcAddr(instance, "vkCmdSetScissor");
	__vkCmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask) vkelGetInstanceProcAddr(instance, "vkCmdSetStencilCompareMask");
	__vkCmdSetStencilReference = (PFN_vkCmdSetStencilReference) vkelGetInstanceProcAddr(instance, "vkCmdSetStencilReference");
	__vkCmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask) vkelGetInstanceProcAddr(instance, "vkCmdSetStencilWriteMask");
	__vkCmdSetViewport = (PFN_vkCmdSetViewport) vkelGetInstanceProcAddr(instance, "vkCmdSetViewport");
	__vkCmdSetViewportWScalingNV = (PFN_vkCmdSetViewportWScalingNV) vkelGetInstanceProcAddr(instance, "vkCmdSetViewportWScalingNV");
	__vkCmdUpdateBuffer = (PFN_vkCmdUpdateBuffer) vkelGetInstanceProcAddr(instance, "vkCmdUpdateBuffer");
	__vkCmdWaitEvents = (PFN_vkCmdWaitEvents) vkelGetInstanceProcAddr(instance, "vkCmdWaitEvents");
	__vkCmdWriteTimestamp = (PFN_vkCmdWriteTimestamp) vkelGetInstanceProcAddr(instance, "vkCmdWriteTimestamp");
	__vkCreateBuffer = (PFN_vkCreateBuffer) vkelGetInstanceProcAddr(instance, "vkCreateBuffer");
	__vkCreateBufferView = (PFN_vkCreateBufferView) vkelGetInstanceProcAddr(instance, "vkCreateBufferView");
	__vkCreateCommandPool = (PFN_vkCreateCommandPool) vkelGetInstanceProcAddr(instance, "vkCreateCommandPool");
	__vkCreateComputePipelines = (PFN_vkCreateComputePipelines) vkelGetInstanceProcAddr(instance, "vkCreateComputePipelines");
	__vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT) vkelGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	__vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool) vkelGetInstanceProcAddr(instance, "vkCreateDescriptorPool");
	__vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout) vkelGetInstanceProcAddr(instance, "vkCreateDescriptorSetLayout");
	__vkCreateDescriptorUpdateTemplateKHR = (PFN_vkCreateDescriptorUpdateTemplateKHR) vkelGetInstanceProcAddr(instance, "vkCreateDescriptorUpdateTemplateKHR");
	__vkCreateDevice = (PFN_vkCreateDevice) vkelGetInstanceProcAddr(instance, "vkCreateDevice");
	__vkCreateDisplayModeKHR = (PFN_vkCreateDisplayModeKHR) vkelGetInstanceProcAddr(instance, "vkCreateDisplayModeKHR");
	__vkCreateDisplayPlaneSurfaceKHR = (PFN_vkCreateDisplayPlaneSurfaceKHR) vkelGetInstanceProcAddr(instance, "vkCreateDisplayPlaneSurfaceKHR");
	__vkCreateEvent = (PFN_vkCreateEvent) vkelGetInstanceProcAddr(instance, "vkCreateEvent");
	__vkCreateFence = (PFN_vkCreateFence) vkelGetInstanceProcAddr(instance, "vkCreateFence");
	__vkCreateFramebuffer = (PFN_vkCreateFramebuffer) vkelGetInstanceProcAddr(instance, "vkCreateFramebuffer");
	__vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines) vkelGetInstanceProcAddr(instance, "vkCreateGraphicsPipelines");
	__vkCreateImage = (PFN_vkCreateImage) vkelGetInstanceProcAddr(instance, "vkCreateImage");
	__vkCreateImageView = (PFN_vkCreateImageView) vkelGetInstanceProcAddr(instance, "vkCreateImageView");
	__vkCreateIndirectCommandsLayoutNVX = (PFN_vkCreateIndirectCommandsLayoutNVX) vkelGetInstanceProcAddr(instance, "vkCreateIndirectCommandsLayoutNVX");
	__vkCreateInstance = (PFN_vkCreateInstance) vkelGetInstanceProcAddr(instance, "vkCreateInstance");
	__vkCreateObjectTableNVX = (PFN_vkCreateObjectTableNVX) vkelGetInstanceProcAddr(instance, "vkCreateObjectTableNVX");
	__vkCreatePipelineCache = (PFN_vkCreatePipelineCache) vkelGetInstanceProcAddr(instance, "vkCreatePipelineCache");
	__vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout) vkelGetInstanceProcAddr(instance, "vkCreatePipelineLayout");
	__vkCreateQueryPool = (PFN_vkCreateQueryPool) vkelGetInstanceProcAddr(instance, "vkCreateQueryPool");
	__vkCreateRenderPass = (PFN_vkCreateRenderPass) vkelGetInstanceProcAddr(instance, "vkCreateRenderPass");
	__vkCreateSampler = (PFN_vkCreateSampler) vkelGetInstanceProcAddr(instance, "vkCreateSampler");
	__vkCreateSemaphore = (PFN_vkCreateSemaphore) vkelGetInstanceProcAddr(instance, "vkCreateSemaphore");
	__vkCreateShaderModule = (PFN_vkCreateShaderModule) vkelGetInstanceProcAddr(instance, "vkCreateShaderModule");
	__vkCreateSharedSwapchainsKHR = (PFN_vkCreateSharedSwapchainsKHR) vkelGetInstanceProcAddr(instance, "vkCreateSharedSwapchainsKHR");
	__vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR) vkelGetInstanceProcAddr(instance, "vkCreateSwapchainKHR");
	__vkDebugMarkerSetObjectNameEXT = (PFN_vkDebugMarkerSetObjectNameEXT) vkelGetInstanceProcAddr(instance, "vkDebugMarkerSetObjectNameEXT");
	__vkDebugMarkerSetObjectTagEXT = (PFN_vkDebugMarkerSetObjectTagEXT) vkelGetInstanceProcAddr(instance, "vkDebugMarkerSetObjectTagEXT");
	__vkDebugReportCallbackEXT = (PFN_vkDebugReportCallbackEXT) vkelGetInstanceProcAddr(instance, "vkDebugReportCallbackEXT");
	__vkDebugReportMessageEXT = (PFN_vkDebugReportMessageEXT) vkelGetInstanceProcAddr(instance, "vkDebugReportMessageEXT");
	__vkDestroyBuffer = (PFN_vkDestroyBuffer) vkelGetInstanceProcAddr(instance, "vkDestroyBuffer");
	__vkDestroyBufferView = (PFN_vkDestroyBufferView) vkelGetInstanceProcAddr(instance, "vkDestroyBufferView");
	__vkDestroyCommandPool = (PFN_vkDestroyCommandPool) vkelGetInstanceProcAddr(instance, "vkDestroyCommandPool");
	__vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT) vkelGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	__vkDestroyDescriptorPool = (PFN_vkDestroyDescriptorPool) vkelGetInstanceProcAddr(instance, "vkDestroyDescriptorPool");
	__vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout) vkelGetInstanceProcAddr(instance, "vkDestroyDescriptorSetLayout");
	__vkDestroyDescriptorUpdateTemplateKHR = (PFN_vkDestroyDescriptorUpdateTemplateKHR) vkelGetInstanceProcAddr(instance, "vkDestroyDescriptorUpdateTemplateKHR");
	__vkDestroyDevice = (PFN_vkDestroyDevice) vkelGetInstanceProcAddr(instance, "vkDestroyDevice");
	__vkDestroyEvent = (PFN_vkDestroyEvent) vkelGetInstanceProcAddr(instance, "vkDestroyEvent");
	__vkDestroyFence = (PFN_vkDestroyFence) vkelGetInstanceProcAddr(instance, "vkDestroyFence");
	__vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer) vkelGetInstanceProcAddr(instance, "vkDestroyFramebuffer");
	__vkDestroyImage = (PFN_vkDestroyImage) vkelGetInstanceProcAddr(instance, "vkDestroyImage");
	__vkDestroyImageView = (PFN_vkDestroyImageView) vkelGetInstanceProcAddr(instance, "vkDestroyImageView");
	__vkDestroyIndirectCommandsLayoutNVX = (PFN_vkDestroyIndirectCommandsLayoutNVX) vkelGetInstanceProcAddr(instance, "vkDestroyIndirectCommandsLayoutNVX");
	__vkDestroyInstance = (PFN_vkDestroyInstance) vkelGetInstanceProcAddr(instance, "vkDestroyInstance");
	__vkDestroyObjectTableNVX = (PFN_vkDestroyObjectTableNVX) vkelGetInstanceProcAddr(instance, "vkDestroyObjectTableNVX");
	__vkDestroyPipeline = (PFN_vkDestroyPipeline) vkelGetInstanceProcAddr(instance, "vkDestroyPipeline");
	__vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache) vkelGetInstanceProcAddr(instance, "vkDestroyPipelineCache");
	__vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout) vkelGetInstanceProcAddr(instance, "vkDestroyPipelineLayout");
	__vkDestroyQueryPool = (PFN_vkDestroyQueryPool) vkelGetInstanceProcAddr(instance, "vkDestroyQueryPool");
	__vkDestroyRenderPass = (PFN_vkDestroyRenderPass) vkelGetInstanceProcAddr(instance, "vkDestroyRenderPass");
	__vkDestroySampler = (PFN_vkDestroySampler) vkelGetInstanceProcAddr(instance, "vkDestroySampler");
	__vkDestroySemaphore = (PFN_vkDestroySemaphore) vkelGetInstanceProcAddr(instance, "vkDestroySemaphore");
	__vkDestroyShaderModule = (PFN_vkDestroyShaderModule) vkelGetInstanceProcAddr(instance, "vkDestroyShaderModule");
	__vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR) vkelGetInstanceProcAddr(instance, "vkDestroySurfaceKHR");
	__vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR) vkelGetInstanceProcAddr(instance, "vkDestroySwapchainKHR");
	__vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle) vkelGetInstanceProcAddr(instance, "vkDeviceWaitIdle");
	__vkDisplayPowerControlEXT = (PFN_vkDisplayPowerControlEXT) vkelGetInstanceProcAddr(instance, "vkDisplayPowerControlEXT");
	__vkEndCommandBuffer = (PFN_vkEndCommandBuffer) vkelGetInstanceProcAddr(instance, "vkEndCommandBuffer");
	__vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties) vkelGetInstanceProcAddr(instance, "vkEnumerateDeviceExtensionProperties");
	__vkEnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties) vkelGetInstanceProcAddr(instance, "vkEnumerateDeviceLayerProperties");
	__vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties) vkelGetInstanceProcAddr(instance, "vkEnumerateInstanceExtensionProperties");
	__vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties) vkelGetInstanceProcAddr(instance, "vkEnumerateInstanceLayerProperties");
	__vkEnumeratePhysicalDeviceGroupsKHX = (PFN_vkEnumeratePhysicalDeviceGroupsKHX) vkelGetInstanceProcAddr(instance, "vkEnumeratePhysicalDeviceGroupsKHX");
	__vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices) vkelGetInstanceProcAddr(instance, "vkEnumeratePhysicalDevices");
	__vkFlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges) vkelGetInstanceProcAddr(instance, "vkFlushMappedMemoryRanges");
	__vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers) vkelGetInstanceProcAddr(instance, "vkFreeCommandBuffers");
	__vkFreeDescriptorSets = (PFN_vkFreeDescriptorSets) vkelGetInstanceProcAddr(instance, "vkFreeDescriptorSets");
	__vkFreeFunction = (PFN_vkFreeFunction) vkelGetInstanceProcAddr(instance, "vkFreeFunction");
	__vkFreeMemory = (PFN_vkFreeMemory) vkelGetInstanceProcAddr(instance, "vkFreeMemory");
	__vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements) vkelGetInstanceProcAddr(instance, "vkGetBufferMemoryRequirements");
	__vkGetDeviceGroupPeerMemoryFeaturesKHX = (PFN_vkGetDeviceGroupPeerMemoryFeaturesKHX) vkelGetInstanceProcAddr(instance, "vkGetDeviceGroupPeerMemoryFeaturesKHX");
	__vkGetDeviceGroupPresentCapabilitiesKHX = (PFN_vkGetDeviceGroupPresentCapabilitiesKHX) vkelGetInstanceProcAddr(instance, "vkGetDeviceGroupPresentCapabilitiesKHX");
	__vkGetDeviceGroupSurfacePresentModesKHX = (PFN_vkGetDeviceGroupSurfacePresentModesKHX) vkelGetInstanceProcAddr(instance, "vkGetDeviceGroupSurfacePresentModesKHX");
	__vkGetDeviceMemoryCommitment = (PFN_vkGetDeviceMemoryCommitment) vkelGetInstanceProcAddr(instance, "vkGetDeviceMemoryCommitment");
	__vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr) vkelGetInstanceProcAddr(instance, "vkGetDeviceProcAddr");
	__vkGetDeviceQueue = (PFN_vkGetDeviceQueue) vkelGetInstanceProcAddr(instance, "vkGetDeviceQueue");
	__vkGetDisplayModePropertiesKHR = (PFN_vkGetDisplayModePropertiesKHR) vkelGetInstanceProcAddr(instance, "vkGetDisplayModePropertiesKHR");
	__vkGetDisplayPlaneCapabilitiesKHR = (PFN_vkGetDisplayPlaneCapabilitiesKHR) vkelGetInstanceProcAddr(instance, "vkGetDisplayPlaneCapabilitiesKHR");
	__vkGetDisplayPlaneSupportedDisplaysKHR = (PFN_vkGetDisplayPlaneSupportedDisplaysKHR) vkelGetInstanceProcAddr(instance, "vkGetDisplayPlaneSupportedDisplaysKHR");
	__vkGetEventStatus = (PFN_vkGetEventStatus) vkelGetInstanceProcAddr(instance, "vkGetEventStatus");
	__vkGetFenceStatus = (PFN_vkGetFenceStatus) vkelGetInstanceProcAddr(instance, "vkGetFenceStatus");
	__vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements) vkelGetInstanceProcAddr(instance, "vkGetImageMemoryRequirements");
	__vkGetImageSparseMemoryRequirements = (PFN_vkGetImageSparseMemoryRequirements) vkelGetInstanceProcAddr(instance, "vkGetImageSparseMemoryRequirements");
	__vkGetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout) vkelGetInstanceProcAddr(instance, "vkGetImageSubresourceLayout");
	__vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) vkelGetInstanceProcAddr(instance, "vkGetInstanceProcAddr");
	__vkGetMemoryFdKHX = (PFN_vkGetMemoryFdKHX) vkelGetInstanceProcAddr(instance, "vkGetMemoryFdKHX");
	__vkGetMemoryFdPropertiesKHX = (PFN_vkGetMemoryFdPropertiesKHX) vkelGetInstanceProcAddr(instance, "vkGetMemoryFdPropertiesKHX");
	__vkGetPastPresentationTimingGOOGLE = (PFN_vkGetPastPresentationTimingGOOGLE) vkelGetInstanceProcAddr(instance, "vkGetPastPresentationTimingGOOGLE");
	__vkGetPhysicalDeviceDisplayPlanePropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR");
	__vkGetPhysicalDeviceDisplayPropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPropertiesKHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceDisplayPropertiesKHR");
	__vkGetPhysicalDeviceExternalBufferPropertiesKHX = (PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHX) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalBufferPropertiesKHX");
	__vkGetPhysicalDeviceExternalImageFormatPropertiesNV = (PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalImageFormatPropertiesNV");
	__vkGetPhysicalDeviceExternalSemaphorePropertiesKHX = (PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHX) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceExternalSemaphorePropertiesKHX");
	__vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFeatures");
	__vkGetPhysicalDeviceFeatures2KHR = (PFN_vkGetPhysicalDeviceFeatures2KHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFeatures2KHR");
	__vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFormatProperties");
	__vkGetPhysicalDeviceFormatProperties2KHR = (PFN_vkGetPhysicalDeviceFormatProperties2KHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceFormatProperties2KHR");
	__vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX = (PFN_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX");
	__vkGetPhysicalDeviceImageFormatProperties = (PFN_vkGetPhysicalDeviceImageFormatProperties) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceImageFormatProperties");
	__vkGetPhysicalDeviceImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceImageFormatProperties2KHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceImageFormatProperties2KHR");
	__vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceMemoryProperties");
	__vkGetPhysicalDeviceMemoryProperties2KHR = (PFN_vkGetPhysicalDeviceMemoryProperties2KHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceMemoryProperties2KHR");
	__vkGetPhysicalDevicePresentRectanglesKHX = (PFN_vkGetPhysicalDevicePresentRectanglesKHX) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDevicePresentRectanglesKHX");
	__vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceProperties");
	__vkGetPhysicalDeviceProperties2KHR = (PFN_vkGetPhysicalDeviceProperties2KHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceProperties2KHR");
	__vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties");
	__vkGetPhysicalDeviceQueueFamilyProperties2KHR = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties2KHR");
	__vkGetPhysicalDeviceSparseImageFormatProperties = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSparseImageFormatProperties");
	__vkGetPhysicalDeviceSparseImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSparseImageFormatProperties2KHR");
	__vkGetPhysicalDeviceSurfaceCapabilities2EXT = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceCapabilities2EXT");
	__vkGetPhysicalDeviceSurfaceCapabilities2KHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceCapabilities2KHR");
	__vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
	__vkGetPhysicalDeviceSurfaceFormats2KHR = (PFN_vkGetPhysicalDeviceSurfaceFormats2KHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceFormats2KHR");
	__vkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceFormatsKHR");
	__vkGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfacePresentModesKHR");
	__vkGetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceSupportKHR");
	__vkGetPipelineCacheData = (PFN_vkGetPipelineCacheData) vkelGetInstanceProcAddr(instance, "vkGetPipelineCacheData");
	__vkGetQueryPoolResults = (PFN_vkGetQueryPoolResults) vkelGetInstanceProcAddr(instance, "vkGetQueryPoolResults");
	__vkGetRefreshCycleDurationGOOGLE = (PFN_vkGetRefreshCycleDurationGOOGLE) vkelGetInstanceProcAddr(instance, "vkGetRefreshCycleDurationGOOGLE");
	__vkGetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity) vkelGetInstanceProcAddr(instance, "vkGetRenderAreaGranularity");
	__vkGetSemaphoreFdKHX = (PFN_vkGetSemaphoreFdKHX) vkelGetInstanceProcAddr(instance, "vkGetSemaphoreFdKHX");
	__vkGetSwapchainCounterEXT = (PFN_vkGetSwapchainCounterEXT) vkelGetInstanceProcAddr(instance, "vkGetSwapchainCounterEXT");
	__vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR) vkelGetInstanceProcAddr(instance, "vkGetSwapchainImagesKHR");
	__vkGetSwapchainStatusKHR = (PFN_vkGetSwapchainStatusKHR) vkelGetInstanceProcAddr(instance, "vkGetSwapchainStatusKHR");
	__vkImportSemaphoreFdKHX = (PFN_vkImportSemaphoreFdKHX) vkelGetInstanceProcAddr(instance, "vkImportSemaphoreFdKHX");
	__vkInternalAllocationNotification = (PFN_vkInternalAllocationNotification) vkelGetInstanceProcAddr(instance, "vkInternalAllocationNotification");
	__vkInternalFreeNotification = (PFN_vkInternalFreeNotification) vkelGetInstanceProcAddr(instance, "vkInternalFreeNotification");
	__vkInvalidateMappedMemoryRanges = (PFN_vkInvalidateMappedMemoryRanges) vkelGetInstanceProcAddr(instance, "vkInvalidateMappedMemoryRanges");
	__vkMapMemory = (PFN_vkMapMemory) vkelGetInstanceProcAddr(instance, "vkMapMemory");
	__vkMergePipelineCaches = (PFN_vkMergePipelineCaches) vkelGetInstanceProcAddr(instance, "vkMergePipelineCaches");
	__vkQueueBindSparse = (PFN_vkQueueBindSparse) vkelGetInstanceProcAddr(instance, "vkQueueBindSparse");
	__vkQueuePresentKHR = (PFN_vkQueuePresentKHR) vkelGetInstanceProcAddr(instance, "vkQueuePresentKHR");
	__vkQueueSubmit = (PFN_vkQueueSubmit) vkelGetInstanceProcAddr(instance, "vkQueueSubmit");
	__vkQueueWaitIdle = (PFN_vkQueueWaitIdle) vkelGetInstanceProcAddr(instance, "vkQueueWaitIdle");
	__vkReallocationFunction = (PFN_vkReallocationFunction) vkelGetInstanceProcAddr(instance, "vkReallocationFunction");
	__vkRegisterDeviceEventEXT = (PFN_vkRegisterDeviceEventEXT) vkelGetInstanceProcAddr(instance, "vkRegisterDeviceEventEXT");
	__vkRegisterDisplayEventEXT = (PFN_vkRegisterDisplayEventEXT) vkelGetInstanceProcAddr(instance, "vkRegisterDisplayEventEXT");
	__vkRegisterObjectsNVX = (PFN_vkRegisterObjectsNVX) vkelGetInstanceProcAddr(instance, "vkRegisterObjectsNVX");
	__vkReleaseDisplayEXT = (PFN_vkReleaseDisplayEXT) vkelGetInstanceProcAddr(instance, "vkReleaseDisplayEXT");
	__vkResetCommandBuffer = (PFN_vkResetCommandBuffer) vkelGetInstanceProcAddr(instance, "vkResetCommandBuffer");
	__vkResetCommandPool = (PFN_vkResetCommandPool) vkelGetInstanceProcAddr(instance, "vkResetCommandPool");
	__vkResetDescriptorPool = (PFN_vkResetDescriptorPool) vkelGetInstanceProcAddr(instance, "vkResetDescriptorPool");
	__vkResetEvent = (PFN_vkResetEvent) vkelGetInstanceProcAddr(instance, "vkResetEvent");
	__vkResetFences = (PFN_vkResetFences) vkelGetInstanceProcAddr(instance, "vkResetFences");
	__vkSetEvent = (PFN_vkSetEvent) vkelGetInstanceProcAddr(instance, "vkSetEvent");
	__vkSetHdrMetadataEXT = (PFN_vkSetHdrMetadataEXT) vkelGetInstanceProcAddr(instance, "vkSetHdrMetadataEXT");
	__vkTrimCommandPoolKHR = (PFN_vkTrimCommandPoolKHR) vkelGetInstanceProcAddr(instance, "vkTrimCommandPoolKHR");
	__vkUnmapMemory = (PFN_vkUnmapMemory) vkelGetInstanceProcAddr(instance, "vkUnmapMemory");
	__vkUnregisterObjectsNVX = (PFN_vkUnregisterObjectsNVX) vkelGetInstanceProcAddr(instance, "vkUnregisterObjectsNVX");
	__vkUpdateDescriptorSetWithTemplateKHR = (PFN_vkUpdateDescriptorSetWithTemplateKHR) vkelGetInstanceProcAddr(instance, "vkUpdateDescriptorSetWithTemplateKHR");
	__vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets) vkelGetInstanceProcAddr(instance, "vkUpdateDescriptorSets");
	__vkVoidFunction = (PFN_vkVoidFunction) vkelGetInstanceProcAddr(instance, "vkVoidFunction");
	__vkWaitForFences = (PFN_vkWaitForFences) vkelGetInstanceProcAddr(instance, "vkWaitForFences");

#ifdef VK_USE_PLATFORM_ANDROID_KHR
	__vkCreateAndroidSurfaceKHR = (PFN_vkCreateAndroidSurfaceKHR) vkelGetInstanceProcAddr(instance, "vkCreateAndroidSurfaceKHR");
#endif /* VK_USE_PLATFORM_ANDROID_KHR */

#ifdef VK_USE_PLATFORM_IOS_MVK
	__vkCreateIOSSurfaceMVK = (PFN_vkCreateIOSSurfaceMVK) vkelGetInstanceProcAddr(instance, "vkCreateIOSSurfaceMVK");
#endif /* VK_USE_PLATFORM_IOS_MVK */

#ifdef VK_USE_PLATFORM_MACOS_MVK
	__vkCreateMacOSSurfaceMVK = (PFN_vkCreateMacOSSurfaceMVK) vkelGetInstanceProcAddr(instance, "vkCreateMacOSSurfaceMVK");
#endif /* VK_USE_PLATFORM_MACOS_MVK */

#ifdef VK_USE_PLATFORM_MIR_KHR
	__vkCreateMirSurfaceKHR = (PFN_vkCreateMirSurfaceKHR) vkelGetInstanceProcAddr(instance, "vkCreateMirSurfaceKHR");
	__vkGetPhysicalDeviceMirPresentationSupportKHR = (PFN_vkGetPhysicalDeviceMirPresentationSupportKHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceMirPresentationSupportKHR");
#endif /* VK_USE_PLATFORM_MIR_KHR */

#ifdef VK_USE_PLATFORM_VI_NN
	__vkCreateViSurfaceNN = (PFN_vkCreateViSurfaceNN) vkelGetInstanceProcAddr(instance, "vkCreateViSurfaceNN");
#endif /* VK_USE_PLATFORM_VI_NN */

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
	__vkCreateWaylandSurfaceKHR = (PFN_vkCreateWaylandSurfaceKHR) vkelGetInstanceProcAddr(instance, "vkCreateWaylandSurfaceKHR");
	__vkGetPhysicalDeviceWaylandPresentationSupportKHR = (PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceWaylandPresentationSupportKHR");
#endif /* VK_USE_PLATFORM_WAYLAND_KHR */

#ifdef VK_USE_PLATFORM_WIN32_KHR
	__vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR) vkelGetInstanceProcAddr(instance, "vkCreateWin32SurfaceKHR");
	__vkGetMemoryWin32HandleNV = (PFN_vkGetMemoryWin32HandleNV) vkelGetInstanceProcAddr(instance, "vkGetMemoryWin32HandleNV");
	__vkGetPhysicalDeviceWin32PresentationSupportKHR = (PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceWin32PresentationSupportKHR");
#endif /* VK_USE_PLATFORM_WIN32_KHR */

#ifdef VK_USE_PLATFORM_WIN32_KHX
	__vkGetMemoryWin32HandleKHX = (PFN_vkGetMemoryWin32HandleKHX) vkelGetInstanceProcAddr(instance, "vkGetMemoryWin32HandleKHX");
	__vkGetMemoryWin32HandlePropertiesKHX = (PFN_vkGetMemoryWin32HandlePropertiesKHX) vkelGetInstanceProcAddr(instance, "vkGetMemoryWin32HandlePropertiesKHX");
	__vkGetSemaphoreWin32HandleKHX = (PFN_vkGetSemaphoreWin32HandleKHX) vkelGetInstanceProcAddr(instance, "vkGetSemaphoreWin32HandleKHX");
	__vkImportSemaphoreWin32HandleKHX = (PFN_vkImportSemaphoreWin32HandleKHX) vkelGetInstanceProcAddr(instance, "vkImportSemaphoreWin32HandleKHX");
#endif /* VK_USE_PLATFORM_WIN32_KHX */

#ifdef VK_USE_PLATFORM_XCB_KHR
	__vkCreateXcbSurfaceKHR = (PFN_vkCreateXcbSurfaceKHR) vkelGetInstanceProcAddr(instance, "vkCreateXcbSurfaceKHR");
	__vkGetPhysicalDeviceXcbPresentationSupportKHR = (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceXcbPresentationSupportKHR");
#endif /* VK_USE_PLATFORM_XCB_KHR */

#ifdef VK_USE_PLATFORM_XLIB_KHR
	__vkCreateXlibSurfaceKHR = (PFN_vkCreateXlibSurfaceKHR) vkelGetInstanceProcAddr(instance, "vkCreateXlibSurfaceKHR");
	__vkGetPhysicalDeviceXlibPresentationSupportKHR = (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR) vkelGetInstanceProcAddr(instance, "vkGetPhysicalDeviceXlibPresentationSupportKHR");
#endif /* VK_USE_PLATFORM_XLIB_KHR */

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
	__vkAcquireXlibDisplayEXT = (PFN_vkAcquireXlibDisplayEXT) vkelGetInstanceProcAddr(instance, "vkAcquireXlibDisplayEXT");
	__vkGetRandROutputDisplayEXT = (PFN_vkGetRandROutputDisplayEXT) vkelGetInstanceProcAddr(instance, "vkGetRandROutputDisplayEXT");
#endif /* VK_USE_PLATFORM_XLIB_XRANDR_EXT */


	// Instance and device extension names
	VKEL_AMD_draw_indirect_count = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_draw_indirect_count");
	VKEL_AMD_gcn_shader = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_gcn_shader");
	VKEL_AMD_gpu_shader_half_float = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_gpu_shader_half_float");
	VKEL_AMD_gpu_shader_int16 = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_gpu_shader_int16");
	VKEL_AMD_negative_viewport_height = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_negative_viewport_height");
	VKEL_AMD_rasterization_order = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_rasterization_order");
	VKEL_AMD_shader_ballot = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_shader_ballot");
	VKEL_AMD_shader_explicit_vertex_parameter = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_shader_explicit_vertex_parameter");
	VKEL_AMD_shader_trinary_minmax = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_shader_trinary_minmax");
	VKEL_AMD_texture_gather_bias_lod = vkelIsInstanceExtensionSupported(NULL, "VK_AMD_texture_gather_bias_lod");
	VKEL_EXT_acquire_xlib_display = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_acquire_xlib_display");
	VKEL_EXT_blend_operation_advanced = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_blend_operation_advanced");
	VKEL_EXT_debug_marker = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_debug_marker");
	VKEL_EXT_debug_report = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_debug_report");
	VKEL_EXT_direct_mode_display = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_direct_mode_display");
	VKEL_EXT_discard_rectangles = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_discard_rectangles");
	VKEL_EXT_display_control = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_display_control");
	VKEL_EXT_display_surface_counter = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_display_surface_counter");
	VKEL_EXT_hdr_metadata = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_hdr_metadata");
	VKEL_EXT_sampler_filter_minmax = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_sampler_filter_minmax");
	VKEL_EXT_shader_subgroup_ballot = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_shader_subgroup_ballot");
	VKEL_EXT_shader_subgroup_vote = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_shader_subgroup_vote");
	VKEL_EXT_swapchain_colorspace = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_swapchain_colorspace");
	VKEL_EXT_validation_flags = vkelIsInstanceExtensionSupported(NULL, "VK_EXT_validation_flags");
	VKEL_GOOGLE_display_timing = vkelIsInstanceExtensionSupported(NULL, "VK_GOOGLE_display_timing");
	VKEL_IMG_filter_cubic = vkelIsInstanceExtensionSupported(NULL, "VK_IMG_filter_cubic");
	VKEL_IMG_format_pvrtc = vkelIsInstanceExtensionSupported(NULL, "VK_IMG_format_pvrtc");
	VKEL_KHR_android_surface = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_android_surface");
	VKEL_KHR_descriptor_update_template = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_descriptor_update_template");
	VKEL_KHR_display = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_display");
	VKEL_KHR_display_swapchain = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_display_swapchain");
	VKEL_KHR_get_physical_device_properties2 = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_get_physical_device_properties2");
	VKEL_KHR_get_surface_capabilities2 = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_get_surface_capabilities2");
	VKEL_KHR_incremental_present = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_incremental_present");
	VKEL_KHR_maintenance1 = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_maintenance1");
	VKEL_KHR_mir_surface = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_mir_surface");
	VKEL_KHR_push_descriptor = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_push_descriptor");
	VKEL_KHR_sampler_mirror_clamp_to_edge = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_sampler_mirror_clamp_to_edge");
	VKEL_KHR_shader_draw_parameters = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_shader_draw_parameters");
	VKEL_KHR_shared_presentable_image = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_shared_presentable_image");
	VKEL_KHR_surface = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_surface");
	VKEL_KHR_swapchain = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_swapchain");
	VKEL_KHR_wayland_surface = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_wayland_surface");
	VKEL_KHR_win32_surface = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_win32_surface");
	VKEL_KHR_xcb_surface = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_xcb_surface");
	VKEL_KHR_xlib_surface = vkelIsInstanceExtensionSupported(NULL, "VK_KHR_xlib_surface");
	VKEL_KHX_device_group = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_device_group");
	VKEL_KHX_device_group_creation = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_device_group_creation");
	VKEL_KHX_external_memory = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_external_memory");
	VKEL_KHX_external_memory_capabilities = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_external_memory_capabilities");
	VKEL_KHX_external_memory_fd = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_external_memory_fd");
	VKEL_KHX_external_memory_win32 = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_external_memory_win32");
	VKEL_KHX_external_semaphore = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_external_semaphore");
	VKEL_KHX_external_semaphore_capabilities = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_external_semaphore_capabilities");
	VKEL_KHX_external_semaphore_fd = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_external_semaphore_fd");
	VKEL_KHX_external_semaphore_win32 = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_external_semaphore_win32");
	VKEL_KHX_multiview = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_multiview");
	VKEL_KHX_win32_keyed_mutex = vkelIsInstanceExtensionSupported(NULL, "VK_KHX_win32_keyed_mutex");
	VKEL_MVK_ios_surface = vkelIsInstanceExtensionSupported(NULL, "VK_MVK_ios_surface");
	VKEL_MVK_macos_surface = vkelIsInstanceExtensionSupported(NULL, "VK_MVK_macos_surface");
	VKEL_NN_vi_surface = vkelIsInstanceExtensionSupported(NULL, "VK_NN_vi_surface");
	VKEL_NVX_device_generated_commands = vkelIsInstanceExtensionSupported(NULL, "VK_NVX_device_generated_commands");
	VKEL_NVX_multiview_per_view_attributes = vkelIsInstanceExtensionSupported(NULL, "VK_NVX_multiview_per_view_attributes");
	VKEL_NV_clip_space_w_scaling = vkelIsInstanceExtensionSupported(NULL, "VK_NV_clip_space_w_scaling");
	VKEL_NV_dedicated_allocation = vkelIsInstanceExtensionSupported(NULL, "VK_NV_dedicated_allocation");
	VKEL_NV_external_memory = vkelIsInstanceExtensionSupported(NULL, "VK_NV_external_memory");
	VKEL_NV_external_memory_capabilities = vkelIsInstanceExtensionSupported(NULL, "VK_NV_external_memory_capabilities");
	VKEL_NV_external_memory_win32 = vkelIsInstanceExtensionSupported(NULL, "VK_NV_external_memory_win32");
	VKEL_NV_fill_rectangle = vkelIsInstanceExtensionSupported(NULL, "VK_NV_fill_rectangle");
	VKEL_NV_fragment_coverage_to_color = vkelIsInstanceExtensionSupported(NULL, "VK_NV_fragment_coverage_to_color");
	VKEL_NV_framebuffer_mixed_samples = vkelIsInstanceExtensionSupported(NULL, "VK_NV_framebuffer_mixed_samples");
	VKEL_NV_geometry_shader_passthrough = vkelIsInstanceExtensionSupported(NULL, "VK_NV_geometry_shader_passthrough");
	VKEL_NV_glsl_shader = vkelIsInstanceExtensionSupported(NULL, "VK_NV_glsl_shader");
	VKEL_NV_sample_mask_override_coverage = vkelIsInstanceExtensionSupported(NULL, "VK_NV_sample_mask_override_coverage");
	VKEL_NV_viewport_array2 = vkelIsInstanceExtensionSupported(NULL, "VK_NV_viewport_array2");
	VKEL_NV_viewport_swizzle = vkelIsInstanceExtensionSupported(NULL, "VK_NV_viewport_swizzle");
	VKEL_NV_win32_keyed_mutex = vkelIsInstanceExtensionSupported(NULL, "VK_NV_win32_keyed_mutex");

	// Instance and device layer names
	VKEL_LAYER_GOOGLE_unique_objects = vkelIsInstanceLayerSupported("VK_LAYER_GOOGLE_unique_objects");
	VKEL_LAYER_LUNARG_api_dump = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_api_dump");
	VKEL_LAYER_LUNARG_device_limits = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_device_limits");
	VKEL_LAYER_LUNARG_draw_state = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_draw_state");
	VKEL_LAYER_LUNARG_image = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_image");
	VKEL_LAYER_LUNARG_mem_tracker = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_mem_tracker");
	VKEL_LAYER_LUNARG_object_tracker = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_object_tracker");
	VKEL_LAYER_LUNARG_param_checker = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_param_checker");
	VKEL_LAYER_LUNARG_screenshot = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_screenshot");
	VKEL_LAYER_LUNARG_swapchain = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_swapchain");
	VKEL_LAYER_LUNARG_threading = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_threading");
	VKEL_LAYER_LUNARG_vktrace = vkelIsInstanceLayerSupported("VK_LAYER_LUNARG_vktrace");


	return VK_TRUE;
}

VkBool32 vkelDeviceInit(VkPhysicalDevice physicalDevice, VkDevice device)
{
	if (!vkelVkLibHandle && !vkelInit())
		return VK_FALSE;


	__vkAcquireNextImage2KHX = (PFN_vkAcquireNextImage2KHX) vkelGetDeviceProcAddr(device, "vkAcquireNextImage2KHX");
	__vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR) vkelGetDeviceProcAddr(device, "vkAcquireNextImageKHR");
	__vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers) vkelGetDeviceProcAddr(device, "vkAllocateCommandBuffers");
	__vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets) vkelGetDeviceProcAddr(device, "vkAllocateDescriptorSets");
	__vkAllocateMemory = (PFN_vkAllocateMemory) vkelGetDeviceProcAddr(device, "vkAllocateMemory");
	__vkAllocationFunction = (PFN_vkAllocationFunction) vkelGetDeviceProcAddr(device, "vkAllocationFunction");
	__vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer) vkelGetDeviceProcAddr(device, "vkBeginCommandBuffer");
	__vkBindBufferMemory = (PFN_vkBindBufferMemory) vkelGetDeviceProcAddr(device, "vkBindBufferMemory");
	__vkBindBufferMemory2KHX = (PFN_vkBindBufferMemory2KHX) vkelGetDeviceProcAddr(device, "vkBindBufferMemory2KHX");
	__vkBindImageMemory = (PFN_vkBindImageMemory) vkelGetDeviceProcAddr(device, "vkBindImageMemory");
	__vkBindImageMemory2KHX = (PFN_vkBindImageMemory2KHX) vkelGetDeviceProcAddr(device, "vkBindImageMemory2KHX");
	__vkCmdBeginQuery = (PFN_vkCmdBeginQuery) vkelGetDeviceProcAddr(device, "vkCmdBeginQuery");
	__vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass) vkelGetDeviceProcAddr(device, "vkCmdBeginRenderPass");
	__vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets) vkelGetDeviceProcAddr(device, "vkCmdBindDescriptorSets");
	__vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer) vkelGetDeviceProcAddr(device, "vkCmdBindIndexBuffer");
	__vkCmdBindPipeline = (PFN_vkCmdBindPipeline) vkelGetDeviceProcAddr(device, "vkCmdBindPipeline");
	__vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers) vkelGetDeviceProcAddr(device, "vkCmdBindVertexBuffers");
	__vkCmdBlitImage = (PFN_vkCmdBlitImage) vkelGetDeviceProcAddr(device, "vkCmdBlitImage");
	__vkCmdClearAttachments = (PFN_vkCmdClearAttachments) vkelGetDeviceProcAddr(device, "vkCmdClearAttachments");
	__vkCmdClearColorImage = (PFN_vkCmdClearColorImage) vkelGetDeviceProcAddr(device, "vkCmdClearColorImage");
	__vkCmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage) vkelGetDeviceProcAddr(device, "vkCmdClearDepthStencilImage");
	__vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer) vkelGetDeviceProcAddr(device, "vkCmdCopyBuffer");
	__vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage) vkelGetDeviceProcAddr(device, "vkCmdCopyBufferToImage");
	__vkCmdCopyImage = (PFN_vkCmdCopyImage) vkelGetDeviceProcAddr(device, "vkCmdCopyImage");
	__vkCmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer) vkelGetDeviceProcAddr(device, "vkCmdCopyImageToBuffer");
	__vkCmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults) vkelGetDeviceProcAddr(device, "vkCmdCopyQueryPoolResults");
	__vkCmdDebugMarkerBeginEXT = (PFN_vkCmdDebugMarkerBeginEXT) vkelGetDeviceProcAddr(device, "vkCmdDebugMarkerBeginEXT");
	__vkCmdDebugMarkerEndEXT = (PFN_vkCmdDebugMarkerEndEXT) vkelGetDeviceProcAddr(device, "vkCmdDebugMarkerEndEXT");
	__vkCmdDebugMarkerInsertEXT = (PFN_vkCmdDebugMarkerInsertEXT) vkelGetDeviceProcAddr(device, "vkCmdDebugMarkerInsertEXT");
	__vkCmdDispatch = (PFN_vkCmdDispatch) vkelGetDeviceProcAddr(device, "vkCmdDispatch");
	__vkCmdDispatchBaseKHX = (PFN_vkCmdDispatchBaseKHX) vkelGetDeviceProcAddr(device, "vkCmdDispatchBaseKHX");
	__vkCmdDispatchIndirect = (PFN_vkCmdDispatchIndirect) vkelGetDeviceProcAddr(device, "vkCmdDispatchIndirect");
	__vkCmdDraw = (PFN_vkCmdDraw) vkelGetDeviceProcAddr(device, "vkCmdDraw");
	__vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed) vkelGetDeviceProcAddr(device, "vkCmdDrawIndexed");
	__vkCmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect) vkelGetDeviceProcAddr(device, "vkCmdDrawIndexedIndirect");
	__vkCmdDrawIndexedIndirectCountAMD = (PFN_vkCmdDrawIndexedIndirectCountAMD) vkelGetDeviceProcAddr(device, "vkCmdDrawIndexedIndirectCountAMD");
	__vkCmdDrawIndirect = (PFN_vkCmdDrawIndirect) vkelGetDeviceProcAddr(device, "vkCmdDrawIndirect");
	__vkCmdDrawIndirectCountAMD = (PFN_vkCmdDrawIndirectCountAMD) vkelGetDeviceProcAddr(device, "vkCmdDrawIndirectCountAMD");
	__vkCmdEndQuery = (PFN_vkCmdEndQuery) vkelGetDeviceProcAddr(device, "vkCmdEndQuery");
	__vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass) vkelGetDeviceProcAddr(device, "vkCmdEndRenderPass");
	__vkCmdExecuteCommands = (PFN_vkCmdExecuteCommands) vkelGetDeviceProcAddr(device, "vkCmdExecuteCommands");
	__vkCmdFillBuffer = (PFN_vkCmdFillBuffer) vkelGetDeviceProcAddr(device, "vkCmdFillBuffer");
	__vkCmdNextSubpass = (PFN_vkCmdNextSubpass) vkelGetDeviceProcAddr(device, "vkCmdNextSubpass");
	__vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier) vkelGetDeviceProcAddr(device, "vkCmdPipelineBarrier");
	__vkCmdProcessCommandsNVX = (PFN_vkCmdProcessCommandsNVX) vkelGetDeviceProcAddr(device, "vkCmdProcessCommandsNVX");
	__vkCmdPushConstants = (PFN_vkCmdPushConstants) vkelGetDeviceProcAddr(device, "vkCmdPushConstants");
	__vkCmdPushDescriptorSetKHR = (PFN_vkCmdPushDescriptorSetKHR) vkelGetDeviceProcAddr(device, "vkCmdPushDescriptorSetKHR");
	__vkCmdPushDescriptorSetWithTemplateKHR = (PFN_vkCmdPushDescriptorSetWithTemplateKHR) vkelGetDeviceProcAddr(device, "vkCmdPushDescriptorSetWithTemplateKHR");
	__vkCmdReserveSpaceForCommandsNVX = (PFN_vkCmdReserveSpaceForCommandsNVX) vkelGetDeviceProcAddr(device, "vkCmdReserveSpaceForCommandsNVX");
	__vkCmdResetEvent = (PFN_vkCmdResetEvent) vkelGetDeviceProcAddr(device, "vkCmdResetEvent");
	__vkCmdResetQueryPool = (PFN_vkCmdResetQueryPool) vkelGetDeviceProcAddr(device, "vkCmdResetQueryPool");
	__vkCmdResolveImage = (PFN_vkCmdResolveImage) vkelGetDeviceProcAddr(device, "vkCmdResolveImage");
	__vkCmdSetBlendConstants = (PFN_vkCmdSetBlendConstants) vkelGetDeviceProcAddr(device, "vkCmdSetBlendConstants");
	__vkCmdSetDepthBias = (PFN_vkCmdSetDepthBias) vkelGetDeviceProcAddr(device, "vkCmdSetDepthBias");
	__vkCmdSetDepthBounds = (PFN_vkCmdSetDepthBounds) vkelGetDeviceProcAddr(device, "vkCmdSetDepthBounds");
	__vkCmdSetDeviceMaskKHX = (PFN_vkCmdSetDeviceMaskKHX) vkelGetDeviceProcAddr(device, "vkCmdSetDeviceMaskKHX");
	__vkCmdSetDiscardRectangleEXT = (PFN_vkCmdSetDiscardRectangleEXT) vkelGetDeviceProcAddr(device, "vkCmdSetDiscardRectangleEXT");
	__vkCmdSetEvent = (PFN_vkCmdSetEvent) vkelGetDeviceProcAddr(device, "vkCmdSetEvent");
	__vkCmdSetLineWidth = (PFN_vkCmdSetLineWidth) vkelGetDeviceProcAddr(device, "vkCmdSetLineWidth");
	__vkCmdSetScissor = (PFN_vkCmdSetScissor) vkelGetDeviceProcAddr(device, "vkCmdSetScissor");
	__vkCmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask) vkelGetDeviceProcAddr(device, "vkCmdSetStencilCompareMask");
	__vkCmdSetStencilReference = (PFN_vkCmdSetStencilReference) vkelGetDeviceProcAddr(device, "vkCmdSetStencilReference");
	__vkCmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask) vkelGetDeviceProcAddr(device, "vkCmdSetStencilWriteMask");
	__vkCmdSetViewport = (PFN_vkCmdSetViewport) vkelGetDeviceProcAddr(device, "vkCmdSetViewport");
	__vkCmdSetViewportWScalingNV = (PFN_vkCmdSetViewportWScalingNV) vkelGetDeviceProcAddr(device, "vkCmdSetViewportWScalingNV");
	__vkCmdUpdateBuffer = (PFN_vkCmdUpdateBuffer) vkelGetDeviceProcAddr(device, "vkCmdUpdateBuffer");
	__vkCmdWaitEvents = (PFN_vkCmdWaitEvents) vkelGetDeviceProcAddr(device, "vkCmdWaitEvents");
	__vkCmdWriteTimestamp = (PFN_vkCmdWriteTimestamp) vkelGetDeviceProcAddr(device, "vkCmdWriteTimestamp");
	__vkCreateBuffer = (PFN_vkCreateBuffer) vkelGetDeviceProcAddr(device, "vkCreateBuffer");
	__vkCreateBufferView = (PFN_vkCreateBufferView) vkelGetDeviceProcAddr(device, "vkCreateBufferView");
	__vkCreateCommandPool = (PFN_vkCreateCommandPool) vkelGetDeviceProcAddr(device, "vkCreateCommandPool");
	__vkCreateComputePipelines = (PFN_vkCreateComputePipelines) vkelGetDeviceProcAddr(device, "vkCreateComputePipelines");
	__vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT) vkelGetDeviceProcAddr(device, "vkCreateDebugReportCallbackEXT");
	__vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool) vkelGetDeviceProcAddr(device, "vkCreateDescriptorPool");
	__vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout) vkelGetDeviceProcAddr(device, "vkCreateDescriptorSetLayout");
	__vkCreateDescriptorUpdateTemplateKHR = (PFN_vkCreateDescriptorUpdateTemplateKHR) vkelGetDeviceProcAddr(device, "vkCreateDescriptorUpdateTemplateKHR");
	__vkCreateDevice = (PFN_vkCreateDevice) vkelGetDeviceProcAddr(device, "vkCreateDevice");
	__vkCreateDisplayModeKHR = (PFN_vkCreateDisplayModeKHR) vkelGetDeviceProcAddr(device, "vkCreateDisplayModeKHR");
	__vkCreateDisplayPlaneSurfaceKHR = (PFN_vkCreateDisplayPlaneSurfaceKHR) vkelGetDeviceProcAddr(device, "vkCreateDisplayPlaneSurfaceKHR");
	__vkCreateEvent = (PFN_vkCreateEvent) vkelGetDeviceProcAddr(device, "vkCreateEvent");
	__vkCreateFence = (PFN_vkCreateFence) vkelGetDeviceProcAddr(device, "vkCreateFence");
	__vkCreateFramebuffer = (PFN_vkCreateFramebuffer) vkelGetDeviceProcAddr(device, "vkCreateFramebuffer");
	__vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines) vkelGetDeviceProcAddr(device, "vkCreateGraphicsPipelines");
	__vkCreateImage = (PFN_vkCreateImage) vkelGetDeviceProcAddr(device, "vkCreateImage");
	__vkCreateImageView = (PFN_vkCreateImageView) vkelGetDeviceProcAddr(device, "vkCreateImageView");
	__vkCreateIndirectCommandsLayoutNVX = (PFN_vkCreateIndirectCommandsLayoutNVX) vkelGetDeviceProcAddr(device, "vkCreateIndirectCommandsLayoutNVX");
	__vkCreateInstance = (PFN_vkCreateInstance) vkelGetDeviceProcAddr(device, "vkCreateInstance");
	__vkCreateObjectTableNVX = (PFN_vkCreateObjectTableNVX) vkelGetDeviceProcAddr(device, "vkCreateObjectTableNVX");
	__vkCreatePipelineCache = (PFN_vkCreatePipelineCache) vkelGetDeviceProcAddr(device, "vkCreatePipelineCache");
	__vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout) vkelGetDeviceProcAddr(device, "vkCreatePipelineLayout");
	__vkCreateQueryPool = (PFN_vkCreateQueryPool) vkelGetDeviceProcAddr(device, "vkCreateQueryPool");
	__vkCreateRenderPass = (PFN_vkCreateRenderPass) vkelGetDeviceProcAddr(device, "vkCreateRenderPass");
	__vkCreateSampler = (PFN_vkCreateSampler) vkelGetDeviceProcAddr(device, "vkCreateSampler");
	__vkCreateSemaphore = (PFN_vkCreateSemaphore) vkelGetDeviceProcAddr(device, "vkCreateSemaphore");
	__vkCreateShaderModule = (PFN_vkCreateShaderModule) vkelGetDeviceProcAddr(device, "vkCreateShaderModule");
	__vkCreateSharedSwapchainsKHR = (PFN_vkCreateSharedSwapchainsKHR) vkelGetDeviceProcAddr(device, "vkCreateSharedSwapchainsKHR");
	__vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR) vkelGetDeviceProcAddr(device, "vkCreateSwapchainKHR");
	__vkDebugMarkerSetObjectNameEXT = (PFN_vkDebugMarkerSetObjectNameEXT) vkelGetDeviceProcAddr(device, "vkDebugMarkerSetObjectNameEXT");
	__vkDebugMarkerSetObjectTagEXT = (PFN_vkDebugMarkerSetObjectTagEXT) vkelGetDeviceProcAddr(device, "vkDebugMarkerSetObjectTagEXT");
	__vkDebugReportCallbackEXT = (PFN_vkDebugReportCallbackEXT) vkelGetDeviceProcAddr(device, "vkDebugReportCallbackEXT");
	__vkDebugReportMessageEXT = (PFN_vkDebugReportMessageEXT) vkelGetDeviceProcAddr(device, "vkDebugReportMessageEXT");
	__vkDestroyBuffer = (PFN_vkDestroyBuffer) vkelGetDeviceProcAddr(device, "vkDestroyBuffer");
	__vkDestroyBufferView = (PFN_vkDestroyBufferView) vkelGetDeviceProcAddr(device, "vkDestroyBufferView");
	__vkDestroyCommandPool = (PFN_vkDestroyCommandPool) vkelGetDeviceProcAddr(device, "vkDestroyCommandPool");
	__vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT) vkelGetDeviceProcAddr(device, "vkDestroyDebugReportCallbackEXT");
	__vkDestroyDescriptorPool = (PFN_vkDestroyDescriptorPool) vkelGetDeviceProcAddr(device, "vkDestroyDescriptorPool");
	__vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout) vkelGetDeviceProcAddr(device, "vkDestroyDescriptorSetLayout");
	__vkDestroyDescriptorUpdateTemplateKHR = (PFN_vkDestroyDescriptorUpdateTemplateKHR) vkelGetDeviceProcAddr(device, "vkDestroyDescriptorUpdateTemplateKHR");
	__vkDestroyDevice = (PFN_vkDestroyDevice) vkelGetDeviceProcAddr(device, "vkDestroyDevice");
	__vkDestroyEvent = (PFN_vkDestroyEvent) vkelGetDeviceProcAddr(device, "vkDestroyEvent");
	__vkDestroyFence = (PFN_vkDestroyFence) vkelGetDeviceProcAddr(device, "vkDestroyFence");
	__vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer) vkelGetDeviceProcAddr(device, "vkDestroyFramebuffer");
	__vkDestroyImage = (PFN_vkDestroyImage) vkelGetDeviceProcAddr(device, "vkDestroyImage");
	__vkDestroyImageView = (PFN_vkDestroyImageView) vkelGetDeviceProcAddr(device, "vkDestroyImageView");
	__vkDestroyIndirectCommandsLayoutNVX = (PFN_vkDestroyIndirectCommandsLayoutNVX) vkelGetDeviceProcAddr(device, "vkDestroyIndirectCommandsLayoutNVX");
	__vkDestroyInstance = (PFN_vkDestroyInstance) vkelGetDeviceProcAddr(device, "vkDestroyInstance");
	__vkDestroyObjectTableNVX = (PFN_vkDestroyObjectTableNVX) vkelGetDeviceProcAddr(device, "vkDestroyObjectTableNVX");
	__vkDestroyPipeline = (PFN_vkDestroyPipeline) vkelGetDeviceProcAddr(device, "vkDestroyPipeline");
	__vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache) vkelGetDeviceProcAddr(device, "vkDestroyPipelineCache");
	__vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout) vkelGetDeviceProcAddr(device, "vkDestroyPipelineLayout");
	__vkDestroyQueryPool = (PFN_vkDestroyQueryPool) vkelGetDeviceProcAddr(device, "vkDestroyQueryPool");
	__vkDestroyRenderPass = (PFN_vkDestroyRenderPass) vkelGetDeviceProcAddr(device, "vkDestroyRenderPass");
	__vkDestroySampler = (PFN_vkDestroySampler) vkelGetDeviceProcAddr(device, "vkDestroySampler");
	__vkDestroySemaphore = (PFN_vkDestroySemaphore) vkelGetDeviceProcAddr(device, "vkDestroySemaphore");
	__vkDestroyShaderModule = (PFN_vkDestroyShaderModule) vkelGetDeviceProcAddr(device, "vkDestroyShaderModule");
	__vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR) vkelGetDeviceProcAddr(device, "vkDestroySurfaceKHR");
	__vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR) vkelGetDeviceProcAddr(device, "vkDestroySwapchainKHR");
	__vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle) vkelGetDeviceProcAddr(device, "vkDeviceWaitIdle");
	__vkDisplayPowerControlEXT = (PFN_vkDisplayPowerControlEXT) vkelGetDeviceProcAddr(device, "vkDisplayPowerControlEXT");
	__vkEndCommandBuffer = (PFN_vkEndCommandBuffer) vkelGetDeviceProcAddr(device, "vkEndCommandBuffer");
	__vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties) vkelGetDeviceProcAddr(device, "vkEnumerateDeviceExtensionProperties");
	__vkEnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties) vkelGetDeviceProcAddr(device, "vkEnumerateDeviceLayerProperties");
	__vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties) vkelGetDeviceProcAddr(device, "vkEnumerateInstanceExtensionProperties");
	__vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties) vkelGetDeviceProcAddr(device, "vkEnumerateInstanceLayerProperties");
	__vkEnumeratePhysicalDeviceGroupsKHX = (PFN_vkEnumeratePhysicalDeviceGroupsKHX) vkelGetDeviceProcAddr(device, "vkEnumeratePhysicalDeviceGroupsKHX");
	__vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices) vkelGetDeviceProcAddr(device, "vkEnumeratePhysicalDevices");
	__vkFlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges) vkelGetDeviceProcAddr(device, "vkFlushMappedMemoryRanges");
	__vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers) vkelGetDeviceProcAddr(device, "vkFreeCommandBuffers");
	__vkFreeDescriptorSets = (PFN_vkFreeDescriptorSets) vkelGetDeviceProcAddr(device, "vkFreeDescriptorSets");
	__vkFreeFunction = (PFN_vkFreeFunction) vkelGetDeviceProcAddr(device, "vkFreeFunction");
	__vkFreeMemory = (PFN_vkFreeMemory) vkelGetDeviceProcAddr(device, "vkFreeMemory");
	__vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements) vkelGetDeviceProcAddr(device, "vkGetBufferMemoryRequirements");
	__vkGetDeviceGroupPeerMemoryFeaturesKHX = (PFN_vkGetDeviceGroupPeerMemoryFeaturesKHX) vkelGetDeviceProcAddr(device, "vkGetDeviceGroupPeerMemoryFeaturesKHX");
	__vkGetDeviceGroupPresentCapabilitiesKHX = (PFN_vkGetDeviceGroupPresentCapabilitiesKHX) vkelGetDeviceProcAddr(device, "vkGetDeviceGroupPresentCapabilitiesKHX");
	__vkGetDeviceGroupSurfacePresentModesKHX = (PFN_vkGetDeviceGroupSurfacePresentModesKHX) vkelGetDeviceProcAddr(device, "vkGetDeviceGroupSurfacePresentModesKHX");
	__vkGetDeviceMemoryCommitment = (PFN_vkGetDeviceMemoryCommitment) vkelGetDeviceProcAddr(device, "vkGetDeviceMemoryCommitment");
	__vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr) vkelGetDeviceProcAddr(device, "vkGetDeviceProcAddr");
	__vkGetDeviceQueue = (PFN_vkGetDeviceQueue) vkelGetDeviceProcAddr(device, "vkGetDeviceQueue");
	__vkGetDisplayModePropertiesKHR = (PFN_vkGetDisplayModePropertiesKHR) vkelGetDeviceProcAddr(device, "vkGetDisplayModePropertiesKHR");
	__vkGetDisplayPlaneCapabilitiesKHR = (PFN_vkGetDisplayPlaneCapabilitiesKHR) vkelGetDeviceProcAddr(device, "vkGetDisplayPlaneCapabilitiesKHR");
	__vkGetDisplayPlaneSupportedDisplaysKHR = (PFN_vkGetDisplayPlaneSupportedDisplaysKHR) vkelGetDeviceProcAddr(device, "vkGetDisplayPlaneSupportedDisplaysKHR");
	__vkGetEventStatus = (PFN_vkGetEventStatus) vkelGetDeviceProcAddr(device, "vkGetEventStatus");
	__vkGetFenceStatus = (PFN_vkGetFenceStatus) vkelGetDeviceProcAddr(device, "vkGetFenceStatus");
	__vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements) vkelGetDeviceProcAddr(device, "vkGetImageMemoryRequirements");
	__vkGetImageSparseMemoryRequirements = (PFN_vkGetImageSparseMemoryRequirements) vkelGetDeviceProcAddr(device, "vkGetImageSparseMemoryRequirements");
	__vkGetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout) vkelGetDeviceProcAddr(device, "vkGetImageSubresourceLayout");
	__vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) vkelGetDeviceProcAddr(device, "vkGetInstanceProcAddr");
	__vkGetMemoryFdKHX = (PFN_vkGetMemoryFdKHX) vkelGetDeviceProcAddr(device, "vkGetMemoryFdKHX");
	__vkGetMemoryFdPropertiesKHX = (PFN_vkGetMemoryFdPropertiesKHX) vkelGetDeviceProcAddr(device, "vkGetMemoryFdPropertiesKHX");
	__vkGetPastPresentationTimingGOOGLE = (PFN_vkGetPastPresentationTimingGOOGLE) vkelGetDeviceProcAddr(device, "vkGetPastPresentationTimingGOOGLE");
	__vkGetPhysicalDeviceDisplayPlanePropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR");
	__vkGetPhysicalDeviceDisplayPropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPropertiesKHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceDisplayPropertiesKHR");
	__vkGetPhysicalDeviceExternalBufferPropertiesKHX = (PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHX) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceExternalBufferPropertiesKHX");
	__vkGetPhysicalDeviceExternalImageFormatPropertiesNV = (PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceExternalImageFormatPropertiesNV");
	__vkGetPhysicalDeviceExternalSemaphorePropertiesKHX = (PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHX) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceExternalSemaphorePropertiesKHX");
	__vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceFeatures");
	__vkGetPhysicalDeviceFeatures2KHR = (PFN_vkGetPhysicalDeviceFeatures2KHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceFeatures2KHR");
	__vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceFormatProperties");
	__vkGetPhysicalDeviceFormatProperties2KHR = (PFN_vkGetPhysicalDeviceFormatProperties2KHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceFormatProperties2KHR");
	__vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX = (PFN_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX");
	__vkGetPhysicalDeviceImageFormatProperties = (PFN_vkGetPhysicalDeviceImageFormatProperties) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceImageFormatProperties");
	__vkGetPhysicalDeviceImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceImageFormatProperties2KHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceImageFormatProperties2KHR");
	__vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceMemoryProperties");
	__vkGetPhysicalDeviceMemoryProperties2KHR = (PFN_vkGetPhysicalDeviceMemoryProperties2KHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceMemoryProperties2KHR");
	__vkGetPhysicalDevicePresentRectanglesKHX = (PFN_vkGetPhysicalDevicePresentRectanglesKHX) vkelGetDeviceProcAddr(device, "vkGetPhysicalDevicePresentRectanglesKHX");
	__vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceProperties");
	__vkGetPhysicalDeviceProperties2KHR = (PFN_vkGetPhysicalDeviceProperties2KHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceProperties2KHR");
	__vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceQueueFamilyProperties");
	__vkGetPhysicalDeviceQueueFamilyProperties2KHR = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceQueueFamilyProperties2KHR");
	__vkGetPhysicalDeviceSparseImageFormatProperties = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceSparseImageFormatProperties");
	__vkGetPhysicalDeviceSparseImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceSparseImageFormatProperties2KHR");
	__vkGetPhysicalDeviceSurfaceCapabilities2EXT = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceSurfaceCapabilities2EXT");
	__vkGetPhysicalDeviceSurfaceCapabilities2KHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceSurfaceCapabilities2KHR");
	__vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
	__vkGetPhysicalDeviceSurfaceFormats2KHR = (PFN_vkGetPhysicalDeviceSurfaceFormats2KHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceSurfaceFormats2KHR");
	__vkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceSurfaceFormatsKHR");
	__vkGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceSurfacePresentModesKHR");
	__vkGetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceSurfaceSupportKHR");
	__vkGetPipelineCacheData = (PFN_vkGetPipelineCacheData) vkelGetDeviceProcAddr(device, "vkGetPipelineCacheData");
	__vkGetQueryPoolResults = (PFN_vkGetQueryPoolResults) vkelGetDeviceProcAddr(device, "vkGetQueryPoolResults");
	__vkGetRefreshCycleDurationGOOGLE = (PFN_vkGetRefreshCycleDurationGOOGLE) vkelGetDeviceProcAddr(device, "vkGetRefreshCycleDurationGOOGLE");
	__vkGetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity) vkelGetDeviceProcAddr(device, "vkGetRenderAreaGranularity");
	__vkGetSemaphoreFdKHX = (PFN_vkGetSemaphoreFdKHX) vkelGetDeviceProcAddr(device, "vkGetSemaphoreFdKHX");
	__vkGetSwapchainCounterEXT = (PFN_vkGetSwapchainCounterEXT) vkelGetDeviceProcAddr(device, "vkGetSwapchainCounterEXT");
	__vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR) vkelGetDeviceProcAddr(device, "vkGetSwapchainImagesKHR");
	__vkGetSwapchainStatusKHR = (PFN_vkGetSwapchainStatusKHR) vkelGetDeviceProcAddr(device, "vkGetSwapchainStatusKHR");
	__vkImportSemaphoreFdKHX = (PFN_vkImportSemaphoreFdKHX) vkelGetDeviceProcAddr(device, "vkImportSemaphoreFdKHX");
	__vkInternalAllocationNotification = (PFN_vkInternalAllocationNotification) vkelGetDeviceProcAddr(device, "vkInternalAllocationNotification");
	__vkInternalFreeNotification = (PFN_vkInternalFreeNotification) vkelGetDeviceProcAddr(device, "vkInternalFreeNotification");
	__vkInvalidateMappedMemoryRanges = (PFN_vkInvalidateMappedMemoryRanges) vkelGetDeviceProcAddr(device, "vkInvalidateMappedMemoryRanges");
	__vkMapMemory = (PFN_vkMapMemory) vkelGetDeviceProcAddr(device, "vkMapMemory");
	__vkMergePipelineCaches = (PFN_vkMergePipelineCaches) vkelGetDeviceProcAddr(device, "vkMergePipelineCaches");
	__vkQueueBindSparse = (PFN_vkQueueBindSparse) vkelGetDeviceProcAddr(device, "vkQueueBindSparse");
	__vkQueuePresentKHR = (PFN_vkQueuePresentKHR) vkelGetDeviceProcAddr(device, "vkQueuePresentKHR");
	__vkQueueSubmit = (PFN_vkQueueSubmit) vkelGetDeviceProcAddr(device, "vkQueueSubmit");
	__vkQueueWaitIdle = (PFN_vkQueueWaitIdle) vkelGetDeviceProcAddr(device, "vkQueueWaitIdle");
	__vkReallocationFunction = (PFN_vkReallocationFunction) vkelGetDeviceProcAddr(device, "vkReallocationFunction");
	__vkRegisterDeviceEventEXT = (PFN_vkRegisterDeviceEventEXT) vkelGetDeviceProcAddr(device, "vkRegisterDeviceEventEXT");
	__vkRegisterDisplayEventEXT = (PFN_vkRegisterDisplayEventEXT) vkelGetDeviceProcAddr(device, "vkRegisterDisplayEventEXT");
	__vkRegisterObjectsNVX = (PFN_vkRegisterObjectsNVX) vkelGetDeviceProcAddr(device, "vkRegisterObjectsNVX");
	__vkReleaseDisplayEXT = (PFN_vkReleaseDisplayEXT) vkelGetDeviceProcAddr(device, "vkReleaseDisplayEXT");
	__vkResetCommandBuffer = (PFN_vkResetCommandBuffer) vkelGetDeviceProcAddr(device, "vkResetCommandBuffer");
	__vkResetCommandPool = (PFN_vkResetCommandPool) vkelGetDeviceProcAddr(device, "vkResetCommandPool");
	__vkResetDescriptorPool = (PFN_vkResetDescriptorPool) vkelGetDeviceProcAddr(device, "vkResetDescriptorPool");
	__vkResetEvent = (PFN_vkResetEvent) vkelGetDeviceProcAddr(device, "vkResetEvent");
	__vkResetFences = (PFN_vkResetFences) vkelGetDeviceProcAddr(device, "vkResetFences");
	__vkSetEvent = (PFN_vkSetEvent) vkelGetDeviceProcAddr(device, "vkSetEvent");
	__vkSetHdrMetadataEXT = (PFN_vkSetHdrMetadataEXT) vkelGetDeviceProcAddr(device, "vkSetHdrMetadataEXT");
	__vkTrimCommandPoolKHR = (PFN_vkTrimCommandPoolKHR) vkelGetDeviceProcAddr(device, "vkTrimCommandPoolKHR");
	__vkUnmapMemory = (PFN_vkUnmapMemory) vkelGetDeviceProcAddr(device, "vkUnmapMemory");
	__vkUnregisterObjectsNVX = (PFN_vkUnregisterObjectsNVX) vkelGetDeviceProcAddr(device, "vkUnregisterObjectsNVX");
	__vkUpdateDescriptorSetWithTemplateKHR = (PFN_vkUpdateDescriptorSetWithTemplateKHR) vkelGetDeviceProcAddr(device, "vkUpdateDescriptorSetWithTemplateKHR");
	__vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets) vkelGetDeviceProcAddr(device, "vkUpdateDescriptorSets");
	__vkVoidFunction = (PFN_vkVoidFunction) vkelGetDeviceProcAddr(device, "vkVoidFunction");
	__vkWaitForFences = (PFN_vkWaitForFences) vkelGetDeviceProcAddr(device, "vkWaitForFences");

#ifdef VK_USE_PLATFORM_ANDROID_KHR
	__vkCreateAndroidSurfaceKHR = (PFN_vkCreateAndroidSurfaceKHR) vkelGetDeviceProcAddr(device, "vkCreateAndroidSurfaceKHR");
#endif /* VK_USE_PLATFORM_ANDROID_KHR */

#ifdef VK_USE_PLATFORM_IOS_MVK
	__vkCreateIOSSurfaceMVK = (PFN_vkCreateIOSSurfaceMVK) vkelGetDeviceProcAddr(device, "vkCreateIOSSurfaceMVK");
#endif /* VK_USE_PLATFORM_IOS_MVK */

#ifdef VK_USE_PLATFORM_MACOS_MVK
	__vkCreateMacOSSurfaceMVK = (PFN_vkCreateMacOSSurfaceMVK) vkelGetDeviceProcAddr(device, "vkCreateMacOSSurfaceMVK");
#endif /* VK_USE_PLATFORM_MACOS_MVK */

#ifdef VK_USE_PLATFORM_MIR_KHR
	__vkCreateMirSurfaceKHR = (PFN_vkCreateMirSurfaceKHR) vkelGetDeviceProcAddr(device, "vkCreateMirSurfaceKHR");
	__vkGetPhysicalDeviceMirPresentationSupportKHR = (PFN_vkGetPhysicalDeviceMirPresentationSupportKHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceMirPresentationSupportKHR");
#endif /* VK_USE_PLATFORM_MIR_KHR */

#ifdef VK_USE_PLATFORM_VI_NN
	__vkCreateViSurfaceNN = (PFN_vkCreateViSurfaceNN) vkelGetDeviceProcAddr(device, "vkCreateViSurfaceNN");
#endif /* VK_USE_PLATFORM_VI_NN */

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
	__vkCreateWaylandSurfaceKHR = (PFN_vkCreateWaylandSurfaceKHR) vkelGetDeviceProcAddr(device, "vkCreateWaylandSurfaceKHR");
	__vkGetPhysicalDeviceWaylandPresentationSupportKHR = (PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceWaylandPresentationSupportKHR");
#endif /* VK_USE_PLATFORM_WAYLAND_KHR */

#ifdef VK_USE_PLATFORM_WIN32_KHR
	__vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR) vkelGetDeviceProcAddr(device, "vkCreateWin32SurfaceKHR");
	__vkGetMemoryWin32HandleNV = (PFN_vkGetMemoryWin32HandleNV) vkelGetDeviceProcAddr(device, "vkGetMemoryWin32HandleNV");
	__vkGetPhysicalDeviceWin32PresentationSupportKHR = (PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceWin32PresentationSupportKHR");
#endif /* VK_USE_PLATFORM_WIN32_KHR */

#ifdef VK_USE_PLATFORM_WIN32_KHX
	__vkGetMemoryWin32HandleKHX = (PFN_vkGetMemoryWin32HandleKHX) vkelGetDeviceProcAddr(device, "vkGetMemoryWin32HandleKHX");
	__vkGetMemoryWin32HandlePropertiesKHX = (PFN_vkGetMemoryWin32HandlePropertiesKHX) vkelGetDeviceProcAddr(device, "vkGetMemoryWin32HandlePropertiesKHX");
	__vkGetSemaphoreWin32HandleKHX = (PFN_vkGetSemaphoreWin32HandleKHX) vkelGetDeviceProcAddr(device, "vkGetSemaphoreWin32HandleKHX");
	__vkImportSemaphoreWin32HandleKHX = (PFN_vkImportSemaphoreWin32HandleKHX) vkelGetDeviceProcAddr(device, "vkImportSemaphoreWin32HandleKHX");
#endif /* VK_USE_PLATFORM_WIN32_KHX */

#ifdef VK_USE_PLATFORM_XCB_KHR
	__vkCreateXcbSurfaceKHR = (PFN_vkCreateXcbSurfaceKHR) vkelGetDeviceProcAddr(device, "vkCreateXcbSurfaceKHR");
	__vkGetPhysicalDeviceXcbPresentationSupportKHR = (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceXcbPresentationSupportKHR");
#endif /* VK_USE_PLATFORM_XCB_KHR */

#ifdef VK_USE_PLATFORM_XLIB_KHR
	__vkCreateXlibSurfaceKHR = (PFN_vkCreateXlibSurfaceKHR) vkelGetDeviceProcAddr(device, "vkCreateXlibSurfaceKHR");
	__vkGetPhysicalDeviceXlibPresentationSupportKHR = (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR) vkelGetDeviceProcAddr(device, "vkGetPhysicalDeviceXlibPresentationSupportKHR");
#endif /* VK_USE_PLATFORM_XLIB_KHR */

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
	__vkAcquireXlibDisplayEXT = (PFN_vkAcquireXlibDisplayEXT) vkelGetDeviceProcAddr(device, "vkAcquireXlibDisplayEXT");
	__vkGetRandROutputDisplayEXT = (PFN_vkGetRandROutputDisplayEXT) vkelGetDeviceProcAddr(device, "vkGetRandROutputDisplayEXT");
#endif /* VK_USE_PLATFORM_XLIB_XRANDR_EXT */


	// Instance and device extension names
	VKEL_AMD_draw_indirect_count = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_AMD_draw_indirect_count");
	VKEL_AMD_gcn_shader = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_AMD_gcn_shader");
	VKEL_AMD_gpu_shader_half_float = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_AMD_gpu_shader_half_float");
	VKEL_AMD_gpu_shader_int16 = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_AMD_gpu_shader_int16");
	VKEL_AMD_negative_viewport_height = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_AMD_negative_viewport_height");
	VKEL_AMD_rasterization_order = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_AMD_rasterization_order");
	VKEL_AMD_shader_ballot = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_AMD_shader_ballot");
	VKEL_AMD_shader_explicit_vertex_parameter = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_AMD_shader_explicit_vertex_parameter");
	VKEL_AMD_shader_trinary_minmax = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_AMD_shader_trinary_minmax");
	VKEL_AMD_texture_gather_bias_lod = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_AMD_texture_gather_bias_lod");
	VKEL_EXT_acquire_xlib_display = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_EXT_acquire_xlib_display");
	VKEL_EXT_blend_operation_advanced = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_EXT_blend_operation_advanced");
	VKEL_EXT_debug_marker = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_EXT_debug_marker");
	VKEL_EXT_debug_report = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_EXT_debug_report");
	VKEL_EXT_direct_mode_display = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_EXT_direct_mode_display");
	VKEL_EXT_discard_rectangles = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_EXT_discard_rectangles");
	VKEL_EXT_display_control = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_EXT_display_control");
	VKEL_EXT_display_surface_counter = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_EXT_display_surface_counter");
	VKEL_EXT_hdr_metadata = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_EXT_hdr_metadata");
	VKEL_EXT_sampler_filter_minmax = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_EXT_sampler_filter_minmax");
	VKEL_EXT_shader_subgroup_ballot = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_EXT_shader_subgroup_ballot");
	VKEL_EXT_shader_subgroup_vote = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_EXT_shader_subgroup_vote");
	VKEL_EXT_swapchain_colorspace = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_EXT_swapchain_colorspace");
	VKEL_EXT_validation_flags = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_EXT_validation_flags");
	VKEL_GOOGLE_display_timing = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_GOOGLE_display_timing");
	VKEL_IMG_filter_cubic = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_IMG_filter_cubic");
	VKEL_IMG_format_pvrtc = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_IMG_format_pvrtc");
	VKEL_KHR_android_surface = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_android_surface");
	VKEL_KHR_descriptor_update_template = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_descriptor_update_template");
	VKEL_KHR_display = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_display");
	VKEL_KHR_display_swapchain = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_display_swapchain");
	VKEL_KHR_get_physical_device_properties2 = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_get_physical_device_properties2");
	VKEL_KHR_get_surface_capabilities2 = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_get_surface_capabilities2");
	VKEL_KHR_incremental_present = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_incremental_present");
	VKEL_KHR_maintenance1 = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_maintenance1");
	VKEL_KHR_mir_surface = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_mir_surface");
	VKEL_KHR_push_descriptor = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_push_descriptor");
	VKEL_KHR_sampler_mirror_clamp_to_edge = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_sampler_mirror_clamp_to_edge");
	VKEL_KHR_shader_draw_parameters = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_shader_draw_parameters");
	VKEL_KHR_shared_presentable_image = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_shared_presentable_image");
	VKEL_KHR_surface = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_surface");
	VKEL_KHR_swapchain = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_swapchain");
	VKEL_KHR_wayland_surface = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_wayland_surface");
	VKEL_KHR_win32_surface = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_win32_surface");
	VKEL_KHR_xcb_surface = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_xcb_surface");
	VKEL_KHR_xlib_surface = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHR_xlib_surface");
	VKEL_KHX_device_group = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHX_device_group");
	VKEL_KHX_device_group_creation = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHX_device_group_creation");
	VKEL_KHX_external_memory = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHX_external_memory");
	VKEL_KHX_external_memory_capabilities = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHX_external_memory_capabilities");
	VKEL_KHX_external_memory_fd = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHX_external_memory_fd");
	VKEL_KHX_external_memory_win32 = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHX_external_memory_win32");
	VKEL_KHX_external_semaphore = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHX_external_semaphore");
	VKEL_KHX_external_semaphore_capabilities = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHX_external_semaphore_capabilities");
	VKEL_KHX_external_semaphore_fd = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHX_external_semaphore_fd");
	VKEL_KHX_external_semaphore_win32 = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHX_external_semaphore_win32");
	VKEL_KHX_multiview = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHX_multiview");
	VKEL_KHX_win32_keyed_mutex = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_KHX_win32_keyed_mutex");
	VKEL_MVK_ios_surface = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_MVK_ios_surface");
	VKEL_MVK_macos_surface = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_MVK_macos_surface");
	VKEL_NN_vi_surface = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NN_vi_surface");
	VKEL_NVX_device_generated_commands = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NVX_device_generated_commands");
	VKEL_NVX_multiview_per_view_attributes = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NVX_multiview_per_view_attributes");
	VKEL_NV_clip_space_w_scaling = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NV_clip_space_w_scaling");
	VKEL_NV_dedicated_allocation = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NV_dedicated_allocation");
	VKEL_NV_external_memory = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NV_external_memory");
	VKEL_NV_external_memory_capabilities = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NV_external_memory_capabilities");
	VKEL_NV_external_memory_win32 = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NV_external_memory_win32");
	VKEL_NV_fill_rectangle = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NV_fill_rectangle");
	VKEL_NV_fragment_coverage_to_color = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NV_fragment_coverage_to_color");
	VKEL_NV_framebuffer_mixed_samples = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NV_framebuffer_mixed_samples");
	VKEL_NV_geometry_shader_passthrough = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NV_geometry_shader_passthrough");
	VKEL_NV_glsl_shader = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NV_glsl_shader");
	VKEL_NV_sample_mask_override_coverage = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NV_sample_mask_override_coverage");
	VKEL_NV_viewport_array2 = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NV_viewport_array2");
	VKEL_NV_viewport_swizzle = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NV_viewport_swizzle");
	VKEL_NV_win32_keyed_mutex = vkelIsDeviceExtensionSupported(physicalDevice, NULL, "VK_NV_win32_keyed_mutex");

	// Instance and device layer names
	VKEL_LAYER_GOOGLE_unique_objects = vkelIsDeviceLayerSupported(physicalDevice, "VK_LAYER_GOOGLE_unique_objects");
	VKEL_LAYER_LUNARG_api_dump = vkelIsDeviceLayerSupported(physicalDevice, "VK_LAYER_LUNARG_api_dump");
	VKEL_LAYER_LUNARG_device_limits = vkelIsDeviceLayerSupported(physicalDevice, "VK_LAYER_LUNARG_device_limits");
	VKEL_LAYER_LUNARG_draw_state = vkelIsDeviceLayerSupported(physicalDevice, "VK_LAYER_LUNARG_draw_state");
	VKEL_LAYER_LUNARG_image = vkelIsDeviceLayerSupported(physicalDevice, "VK_LAYER_LUNARG_image");
	VKEL_LAYER_LUNARG_mem_tracker = vkelIsDeviceLayerSupported(physicalDevice, "VK_LAYER_LUNARG_mem_tracker");
	VKEL_LAYER_LUNARG_object_tracker = vkelIsDeviceLayerSupported(physicalDevice, "VK_LAYER_LUNARG_object_tracker");
	VKEL_LAYER_LUNARG_param_checker = vkelIsDeviceLayerSupported(physicalDevice, "VK_LAYER_LUNARG_param_checker");
	VKEL_LAYER_LUNARG_screenshot = vkelIsDeviceLayerSupported(physicalDevice, "VK_LAYER_LUNARG_screenshot");
	VKEL_LAYER_LUNARG_swapchain = vkelIsDeviceLayerSupported(physicalDevice, "VK_LAYER_LUNARG_swapchain");
	VKEL_LAYER_LUNARG_threading = vkelIsDeviceLayerSupported(physicalDevice, "VK_LAYER_LUNARG_threading");
	VKEL_LAYER_LUNARG_vktrace = vkelIsDeviceLayerSupported(physicalDevice, "VK_LAYER_LUNARG_vktrace");


	return VK_TRUE;
}

void vkelUninit(void)
{
	if (vkelVkLibHandle)
	{
		vkelPlatformCloseLibrary(vkelVkLibHandle);
		vkelVkLibHandle = NULL;
	}
}


#ifdef __cplusplus
}
#endif /* __cplusplus */
