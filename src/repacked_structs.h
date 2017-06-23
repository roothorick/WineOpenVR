#pragma once

#include "common.h"

// Some structs are packed differently on Windows vs. Linux.
// These are packed the way they are on Windows, so we can convert between them.

#pragma pack(push, 8)

/** An event posted by the server to all running applications */
struct Repacked_VREvent_t
{
	uint32_t eventType; // EVREventType enum
	TrackedDeviceIndex_t trackedDeviceIndex;
	float eventAgeSeconds;
	// event data must be the end of the struct as its size is variable
	VREvent_Data_t data;
};

// How much larger the Windows packing is than Linux. IVRSystem::PollNextEvent & IVRSystem::PollNextEventWithPose
// want the size of the struct, presumably for compatibility with older API versions that had a smaller VREvent_t.
#define VREVENT_PACKSIZE_DIFFERENCE ( sizeof(Repacked_VREvent_t) - sizeof(VREvent_t) )

inline void repackVREvent(const VREvent_t* src, Repacked_VREvent_t* dst)
{
  dst->eventType = src->eventType;
  dst->trackedDeviceIndex = src->trackedDeviceIndex;
  dst->eventAgeSeconds = src->eventAgeSeconds;
  dst->data = src->data;
}

struct Repacked_VRControllerState_t
{
	// If packet num matches that on your prior call, then the controller state hasn't been changed since
	// your last call and there is no need to process it
	uint32_t unPacketNum;

	// bit flags for each of the buttons. Use ButtonMaskFromId to turn an ID into a mask
	uint64_t ulButtonPressed;
	uint64_t ulButtonTouched;

	// Axis data for the controller's analog inputs
	VRControllerAxis_t rAxis[ k_unControllerStateAxisCount ];
};

inline void repackVRControllerState(const VRControllerState_t* src, Repacked_VRControllerState_t* dst)
{
  dst->unPacketNum = src->unPacketNum;
  dst->ulButtonPressed = src->ulButtonPressed;
  dst->ulButtonTouched = src->ulButtonTouched;

  for(int i=0; i<k_unControllerStateAxisCount; i++)
  {
    dst->rAxis[i] = src->rAxis[i];
  }
}

inline void repackVRControllerState(const Repacked_VRControllerState_t* src, VRControllerState_t* dst)
{
  dst->unPacketNum = src->unPacketNum;
  dst->ulButtonPressed = src->ulButtonPressed;
  dst->ulButtonTouched = src->ulButtonTouched;

  for(int i=0; i<k_unControllerStateAxisCount; i++)
  {
    dst->rAxis[i] = src->rAxis[i];
  }
}

struct Repacked_RenderModel_TextureMap_t
{
	uint16_t unWidth, unHeight; // width and height of the texture map in pixels
	const uint8_t *rubTextureMapData;	// Map texture data. All textures are RGBA with 8 bits per channel per pixel. Data size is width * height * 4ub

  // The API expects the application to call IVRRenderModels::FreeTexture on every RenderModel_TextureMap_t when it's
  // done with them. That means WE have to call FreeTexture ourselves on the original, then manually free our copy.
  RenderModel_TextureMap_t* original;
};

inline void repackRenderModelTextureMap(RenderModel_TextureMap_t* src, Repacked_RenderModel_TextureMap_t* dst)
{
  dst->unWidth = src->unWidth;
  dst->unHeight = src->unHeight;
  dst->rubTextureMapData = src->rubTextureMapData;
  dst->original = src;
}

struct Repacked_RenderModel_t
{
	const RenderModel_Vertex_t *rVertexData;	// Vertex data for the mesh
	uint32_t unVertexCount;						// Number of vertices in the vertex data
	const uint16_t *rIndexData;					// Indices into the vertex data for each triangle
	uint32_t unTriangleCount;					// Number of triangles in the mesh. Index count is 3 * TriangleCount
	TextureID_t diffuseTextureId;				// Session unique texture identifier. Rendermodels which share the same texture will have the same id. <0 == texture not present

  // Similarly, to RenderModel_TextureMap_t, it is the application's responsibility to call
  // IVRRenderModels::FreeRenderModel when it's done with the model.
  RenderModel_t* original;
};

inline void repackRenderModel(RenderModel_t* src, Repacked_RenderModel_t* dst)
{
  dst->rVertexData = src->rVertexData;
  dst->unVertexCount = src->unVertexCount;
  dst->rIndexData = src->rIndexData;
  dst->unTriangleCount = src->unTriangleCount;
  dst->diffuseTextureId = src->diffuseTextureId;

  dst->original = src;
}

#pragma pack(pop)
