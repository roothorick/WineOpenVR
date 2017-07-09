#include "common.h"
#include "repacked_structs.h"
#include "d3dproxy.h"

namespace fns_IVRRenderModels
{
	inline EVRRenderModelError LoadRenderModel_Async( const char *pchRenderModelName, Repacked_RenderModel_t **ppRenderModel )
	{
		// Struct packing mismatch
		// Because The API impl itself allocates the RM, things are a little complicated.
		EVRRenderModelError ret;
		RenderModel_t* linpackedRM;

		ret = VRRenderModels()->LoadRenderModel_Async(pchRenderModelName, &linpackedRM);

		// This doesn't appear to be spelled out in the API documentation, but hellovr_opengl suggests that the RM isn't
		// allocated on error (including Loading).
		if(ret == VRRenderModelError_None)
		{
			*ppRenderModel = new Repacked_RenderModel_t();
			repackRenderModel(linpackedRM, *ppRenderModel);
		}

		return ret;
	}

	inline void FreeRenderModel( Repacked_RenderModel_t *pRenderModel )
	{
		// Struct packing mismatch
		VRRenderModels()->FreeRenderModel(pRenderModel->original);
		delete pRenderModel;
	}

	inline EVRRenderModelError LoadTexture_Async( TextureID_t textureId, Repacked_RenderModel_TextureMap_t **ppTexture )
	{
		// Struct packing mismatch
		// Because The API impl itself allocates the texture, things are a little complicated.
		EVRRenderModelError ret;
		RenderModel_TextureMap_t* linpackedTex;

		ret = VRRenderModels()->LoadTexture_Async(textureId, &linpackedTex);

		// This doesn't appear to be spelled out in the API documentation, but hellovr_opengl suggests that the texture
		// isn't allocated on error (including Loading).
		if(ret == VRRenderModelError_None)
		{
			*ppTexture = new Repacked_RenderModel_TextureMap_t();
			repackRenderModelTextureMap(linpackedTex, *ppTexture);
		}

		return ret;
	}

	inline void FreeTexture( Repacked_RenderModel_TextureMap_t *pTexture )
	{
		// Struct packing mismatch
		VRRenderModels()->FreeTexture(pTexture->original);
		delete pTexture;
	}

	inline EVRRenderModelError LoadTextureD3D11_Async( TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D )
	{
		return D3DProxy()->LoadTextureD3D11_Async(textureId, pD3D11Device, ppD3D11Texture2D);
	}

	inline EVRRenderModelError LoadIntoTextureD3D11_Async( TextureID_t textureId, void *pDstTexture )
	{
		return D3DProxy()->LoadIntoTextureD3D11_Async(textureId, pDstTexture);
	}

	inline void FreeTextureD3D11( void *pD3D11Texture2D )
	{
		D3DProxy()->FreeTextureD3D11(pD3D11Texture2D);
		return;
	}

	inline uint32_t GetRenderModelName( uint32_t unRenderModelIndex, VR_OUT_STRING() char *pchRenderModelName, uint32_t unRenderModelNameLen )
	{
		return VRRenderModels()->GetRenderModelName(unRenderModelIndex, pchRenderModelName, unRenderModelNameLen);
	}

	inline uint32_t GetRenderModelCount()
	{
		return VRRenderModels()->GetRenderModelCount();
	}

	inline uint32_t GetComponentCount( const char *pchRenderModelName )
	{
		return VRRenderModels()->GetComponentCount(pchRenderModelName);
	}

	inline uint32_t GetComponentName( const char *pchRenderModelName, uint32_t unComponentIndex, VR_OUT_STRING( ) char *pchComponentName, uint32_t unComponentNameLen )
	{
		return VRRenderModels()->GetComponentName(pchRenderModelName, unComponentIndex, pchComponentName, unComponentNameLen);
	}

	inline uint64_t GetComponentButtonMask( const char *pchRenderModelName, const char *pchComponentName )
	{
		return VRRenderModels()->GetComponentButtonMask(pchRenderModelName, pchComponentName);
	}

	inline uint32_t GetComponentRenderModelName( const char *pchRenderModelName, const char *pchComponentName, VR_OUT_STRING( ) char *pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen )
	{
		return VRRenderModels()->GetComponentRenderModelName(pchRenderModelName, pchComponentName, pchComponentRenderModelName, unComponentRenderModelNameLen);
	}

	inline bool GetComponentState( const char *pchRenderModelName, const char *pchComponentName, const Repacked_VRControllerState_t *pControllerState, const RenderModel_ControllerMode_State_t *pState, RenderModel_ComponentState_t *pComponentState )
	{
		// Struct packing mismatch
		VRControllerState_t linpacked;
		repackVRControllerState(pControllerState, &linpacked);

		return VRRenderModels()->GetComponentState(pchRenderModelName, pchComponentName, &linpacked, pState, pComponentState);
	}

	inline bool RenderModelHasComponent( const char *pchRenderModelName, const char *pchComponentName )
	{
		return VRRenderModels()->RenderModelHasComponent(pchRenderModelName, pchComponentName);
	}

	inline uint32_t GetRenderModelThumbnailURL( const char *pchRenderModelName, VR_OUT_STRING() char *pchThumbnailURL, uint32_t unThumbnailURLLen, vr::EVRRenderModelError *peError )
	{
		return VRRenderModels()->GetRenderModelThumbnailURL(pchRenderModelName, pchThumbnailURL, unThumbnailURLLen, peError);
	}

	inline uint32_t GetRenderModelOriginalPath( const char *pchRenderModelName, VR_OUT_STRING() char *pchOriginalPath, uint32_t unOriginalPathLen, vr::EVRRenderModelError *peError )
	{
		return VRRenderModels()->GetRenderModelOriginalPath(pchRenderModelName, pchOriginalPath, unOriginalPathLen, peError);
	}

	inline const char *GetRenderModelErrorNameFromEnum( vr::EVRRenderModelError error )
	{
		return VRRenderModels()->GetRenderModelErrorNameFromEnum(error);
	}
}
