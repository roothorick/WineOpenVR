#include "common.h"
#include "repacked_structs.h"
#include "d3dproxy.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(token_) clone_IVRRenderModels_ ## token_
#define CLONECLASS_(token) CLONECLASS__(token)
#define CLONECLASS CLONECLASS_(ABITOKEN)
#define PROXYCLASS__(token_) proxy_IVRRenderModels_ ## token_
#define PROXYCLASS_(token) PROXYCLASS__(token)
#define PROXYCLASS PROXYCLASS_(ABITOKEN)
#define GETTER__(token_) getIVRRenderModelsProxy_ ## token_
#define GETTER_(token) GETTER__(token)
#define GETTER GETTER_(ABITOKEN)

class CLONECLASS
{
	WOVR_ENTRY virtual EVRRenderModelError LoadRenderModel_Async( const char *pchRenderModelName, Repacked_RenderModel_t **ppRenderModel ) = 0; // Struct packing mismatch
	WOVR_ENTRY virtual void FreeRenderModel( Repacked_RenderModel_t *pRenderModel ) = 0; // Struct packing mismatch
	WOVR_ENTRY virtual EVRRenderModelError LoadTexture_Async( TextureID_t textureId, Repacked_RenderModel_TextureMap_t **ppTexture ) = 0; // Struct packing mismatch
	WOVR_ENTRY virtual void FreeTexture( Repacked_RenderModel_TextureMap_t *pTexture ) = 0; // Struct packing mismatch
	WOVR_ENTRY virtual EVRRenderModelError LoadTextureD3D11_Async( TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D ) = 0;
	WOVR_ENTRY virtual EVRRenderModelError LoadIntoTextureD3D11_Async( TextureID_t textureId, void *pDstTexture ) = 0;
	WOVR_ENTRY virtual void FreeTextureD3D11( void *pD3D11Texture2D ) = 0;
	WOVR_ENTRY virtual uint32_t GetRenderModelName( uint32_t unRenderModelIndex, VR_OUT_STRING() char *pchRenderModelName, uint32_t unRenderModelNameLen ) = 0;
	WOVR_ENTRY virtual uint32_t GetRenderModelCount() = 0;
	WOVR_ENTRY virtual uint32_t GetComponentCount( const char *pchRenderModelName ) = 0;
	WOVR_ENTRY virtual uint32_t GetComponentName( const char *pchRenderModelName, uint32_t unComponentIndex, VR_OUT_STRING( ) char *pchComponentName, uint32_t unComponentNameLen ) = 0;
	WOVR_ENTRY virtual uint64_t GetComponentButtonMask( const char *pchRenderModelName, const char *pchComponentName ) = 0;
	WOVR_ENTRY virtual uint32_t GetComponentRenderModelName( const char *pchRenderModelName, const char *pchComponentName, VR_OUT_STRING( ) char *pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen ) = 0;
	WOVR_ENTRY virtual bool GetComponentState( const char *pchRenderModelName, const char *pchComponentName, const Repacked_VRControllerState_t *pControllerState, const RenderModel_ControllerMode_State_t *pState, RenderModel_ComponentState_t *pComponentState ) = 0; // Struct packing mismatch
	WOVR_ENTRY virtual bool RenderModelHasComponent( const char *pchRenderModelName, const char *pchComponentName ) = 0;
	WOVR_ENTRY virtual uint32_t GetRenderModelThumbnailURL( const char *pchRenderModelName, VR_OUT_STRING() char *pchThumbnailURL, uint32_t unThumbnailURLLen, vr::EVRRenderModelError *peError ) = 0;
	WOVR_ENTRY virtual uint32_t GetRenderModelOriginalPath( const char *pchRenderModelName, VR_OUT_STRING() char *pchOriginalPath, uint32_t unOriginalPathLen, vr::EVRRenderModelError *peError ) = 0;
	WOVR_ENTRY virtual const char *GetRenderModelErrorNameFromEnum( vr::EVRRenderModelError error ) = 0;
};

class PROXYCLASS : public CLONECLASS
{
    WOVR_ENTRY EVRRenderModelError LoadRenderModel_Async( const char *pchRenderModelName, Repacked_RenderModel_t **ppRenderModel )
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

	WOVR_ENTRY void FreeRenderModel( Repacked_RenderModel_t *pRenderModel )
	{
		// Struct packing mismatch
		VRRenderModels()->FreeRenderModel(pRenderModel->original);
		delete pRenderModel;
	}

	WOVR_ENTRY EVRRenderModelError LoadTexture_Async( TextureID_t textureId, Repacked_RenderModel_TextureMap_t **ppTexture )
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

	WOVR_ENTRY void FreeTexture( Repacked_RenderModel_TextureMap_t *pTexture )
	{
		// Struct packing mismatch
		VRRenderModels()->FreeTexture(pTexture->original);
		delete pTexture;
	}

	WOVR_ENTRY EVRRenderModelError LoadTextureD3D11_Async( TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D )
	{
		return D3DProxy()->LoadTextureD3D11_Async(textureId, pD3D11Device, ppD3D11Texture2D);
	}

	WOVR_ENTRY EVRRenderModelError LoadIntoTextureD3D11_Async( TextureID_t textureId, void *pDstTexture )
	{
		return D3DProxy()->LoadIntoTextureD3D11_Async(textureId, pDstTexture);
	}

	WOVR_ENTRY void FreeTextureD3D11( void *pD3D11Texture2D )
	{
		D3DProxy()->FreeTextureD3D11(pD3D11Texture2D);
		return;
	}

	WOVR_ENTRY uint32_t GetRenderModelName( uint32_t unRenderModelIndex, VR_OUT_STRING() char *pchRenderModelName, uint32_t unRenderModelNameLen )
	{
		return VRRenderModels()->GetRenderModelName(unRenderModelIndex, pchRenderModelName, unRenderModelNameLen);
	}

	WOVR_ENTRY uint32_t GetRenderModelCount()
	{
		return VRRenderModels()->GetRenderModelCount();
	}

	WOVR_ENTRY uint32_t GetComponentCount( const char *pchRenderModelName )
	{
		return VRRenderModels()->GetComponentCount(pchRenderModelName);
	}

	WOVR_ENTRY uint32_t GetComponentName( const char *pchRenderModelName, uint32_t unComponentIndex, VR_OUT_STRING( ) char *pchComponentName, uint32_t unComponentNameLen )
	{
		return VRRenderModels()->GetComponentName(pchRenderModelName, unComponentIndex, pchComponentName, unComponentNameLen);
	}

	WOVR_ENTRY uint64_t GetComponentButtonMask( const char *pchRenderModelName, const char *pchComponentName )
	{
		return VRRenderModels()->GetComponentButtonMask(pchRenderModelName, pchComponentName);
	}

	WOVR_ENTRY uint32_t GetComponentRenderModelName( const char *pchRenderModelName, const char *pchComponentName, VR_OUT_STRING( ) char *pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen )
	{
		return VRRenderModels()->GetComponentRenderModelName(pchRenderModelName, pchComponentName, pchComponentRenderModelName, unComponentRenderModelNameLen);
	}

	WOVR_ENTRY bool GetComponentState( const char *pchRenderModelName, const char *pchComponentName, const Repacked_VRControllerState_t *pControllerState, const RenderModel_ControllerMode_State_t *pState, RenderModel_ComponentState_t *pComponentState )
	{
		// Struct packing mismatch
		VRControllerState_t linpacked;
		repackVRControllerState(pControllerState, &linpacked);

		return VRRenderModels()->GetComponentState(pchRenderModelName, pchComponentName, &linpacked, pState, pComponentState);
	}

	WOVR_ENTRY bool RenderModelHasComponent( const char *pchRenderModelName, const char *pchComponentName )
	{
		return VRRenderModels()->RenderModelHasComponent(pchRenderModelName, pchComponentName);
	}

	WOVR_ENTRY uint32_t GetRenderModelThumbnailURL( const char *pchRenderModelName, VR_OUT_STRING() char *pchThumbnailURL, uint32_t unThumbnailURLLen, vr::EVRRenderModelError *peError )
	{
		return VRRenderModels()->GetRenderModelThumbnailURL(pchRenderModelName, pchThumbnailURL, unThumbnailURLLen, peError);
	}

	WOVR_ENTRY uint32_t GetRenderModelOriginalPath( const char *pchRenderModelName, VR_OUT_STRING() char *pchOriginalPath, uint32_t unOriginalPathLen, vr::EVRRenderModelError *peError )
	{
		return VRRenderModels()->GetRenderModelOriginalPath(pchRenderModelName, pchOriginalPath, unOriginalPathLen, peError);
	}

	WOVR_ENTRY const char *GetRenderModelErrorNameFromEnum( vr::EVRRenderModelError error )
	{
		return VRRenderModels()->GetRenderModelErrorNameFromEnum(error);
	}
};

vr::IVRRenderModels* GETTER ()
{
	return (IVRRenderModels*) new PROXYCLASS ();
}
