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
#if ABIVER < 4
	WOVR_ENTRY virtual bool LoadRenderModel( const char *pchRenderModelName, Repacked_RenderModel_t **ppRenderModel ) = 0; // Struct packing mismatch
#else // >= 4
	WOVR_ENTRY virtual EVRRenderModelError LoadRenderModel_Async( const char *pchRenderModelName, Repacked_RenderModel_t **ppRenderModel ) = 0; // Struct packing mismatch
#endif
	WOVR_ENTRY virtual void FreeRenderModel( Repacked_RenderModel_t *pRenderModel ) = 0; // Struct packing mismatch
#if ABIVER < 4
	WOVR_ENTRY virtual bool LoadTexture( TextureID_t textureId, Repacked_RenderModel_TextureMap_t **ppTexture ) = 0; // Struct packing mismatch
#else // >= 4
	WOVR_ENTRY virtual EVRRenderModelError LoadTexture_Async( TextureID_t textureId, Repacked_RenderModel_TextureMap_t **ppTexture ) = 0; // Struct packing mismatch
#endif
	WOVR_ENTRY virtual void FreeTexture( Repacked_RenderModel_TextureMap_t *pTexture ) = 0; // Struct packing mismatch
#if ABIVER >= 4
	WOVR_ENTRY virtual EVRRenderModelError LoadTextureD3D11_Async( TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D ) = 0;
#if ABIVER >= 5
	WOVR_ENTRY virtual EVRRenderModelError LoadIntoTextureD3D11_Async( TextureID_t textureId, void *pDstTexture ) = 0;
#endif
	WOVR_ENTRY virtual void FreeTextureD3D11( void *pD3D11Texture2D ) = 0;
#endif
	WOVR_ENTRY virtual uint32_t GetRenderModelName( uint32_t unRenderModelIndex, VR_OUT_STRING() char *pchRenderModelName, uint32_t unRenderModelNameLen ) = 0;
	WOVR_ENTRY virtual uint32_t GetRenderModelCount() = 0;
	WOVR_ENTRY virtual uint32_t GetComponentCount( const char *pchRenderModelName ) = 0;
	WOVR_ENTRY virtual uint32_t GetComponentName( const char *pchRenderModelName, uint32_t unComponentIndex, VR_OUT_STRING( ) char *pchComponentName, uint32_t unComponentNameLen ) = 0;
	WOVR_ENTRY virtual uint64_t GetComponentButtonMask( const char *pchRenderModelName, const char *pchComponentName ) = 0;
	WOVR_ENTRY virtual uint32_t GetComponentRenderModelName( const char *pchRenderModelName, const char *pchComponentName, VR_OUT_STRING( ) char *pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen ) = 0;
#if ABIVER < 4
	WOVR_ENTRY virtual bool GetComponentState( const char *pchRenderModelName, const char *pchComponentName, const Repacked_VRControllerState_t *pControllerState, RenderModel_ComponentState_t *pComponentState ) = 0; // Struct packing mismatch
#else // >= 4
	WOVR_ENTRY virtual bool GetComponentState( const char *pchRenderModelName, const char *pchComponentName, const Repacked_VRControllerState_t *pControllerState, const RenderModel_ControllerMode_State_t *pState, RenderModel_ComponentState_t *pComponentState ) = 0; // Struct packing mismatch
#endif
	WOVR_ENTRY virtual bool RenderModelHasComponent( const char *pchRenderModelName, const char *pchComponentName ) = 0;
	WOVR_ENTRY virtual uint32_t GetRenderModelThumbnailURL( const char *pchRenderModelName, VR_OUT_STRING() char *pchThumbnailURL, uint32_t unThumbnailURLLen, vr::EVRRenderModelError *peError ) = 0;
	WOVR_ENTRY virtual uint32_t GetRenderModelOriginalPath( const char *pchRenderModelName, VR_OUT_STRING() char *pchOriginalPath, uint32_t unOriginalPathLen, vr::EVRRenderModelError *peError ) = 0;
	WOVR_ENTRY virtual const char *GetRenderModelErrorNameFromEnum( vr::EVRRenderModelError error ) = 0;
};

class PROXYCLASS : public CLONECLASS
{
#if ABIVER < 4
	WOVR_ENTRY bool LoadRenderModel( const char *pchRenderModelName, Repacked_RenderModel_t **ppRenderModel )
#else // >= 4
	WOVR_ENTRY EVRRenderModelError LoadRenderModel_Async( const char *pchRenderModelName, Repacked_RenderModel_t **ppRenderModel )
#endif
	{
		TRACE("");
		// Struct packing mismatch
		// Because The API impl itself allocates the RM, things are a little complicated.
		EVRRenderModelError ret = VRRenderModelError_Loading;
		RenderModel_t* linpackedRM;

#if ABIVER < 4
		while(ret == VRRenderModelError_Loading)
#endif
			ret = VRRenderModels()->LoadRenderModel_Async(pchRenderModelName, &linpackedRM);

		// This doesn't appear to be spelled out in the API documentation, but hellovr_opengl suggests that the RM isn't
		// allocated on error (including Loading).
		if(ret == VRRenderModelError_None)
		{
			*ppRenderModel = new Repacked_RenderModel_t();
			repackRenderModel(linpackedRM, *ppRenderModel);
		}
#if ABIVER < 4
		return ret == VRRenderModelError_None;
#else
		return ret;
#endif
	}

	WOVR_ENTRY void FreeRenderModel( Repacked_RenderModel_t *pRenderModel )
	{
		TRACE("");
		// Struct packing mismatch
		VRRenderModels()->FreeRenderModel(pRenderModel->original);
		delete pRenderModel;
	}

#if ABIVER < 4
	WOVR_ENTRY bool LoadTexture( TextureID_t textureId, Repacked_RenderModel_TextureMap_t **ppTexture )
#else
	WOVR_ENTRY EVRRenderModelError LoadTexture_Async( TextureID_t textureId, Repacked_RenderModel_TextureMap_t **ppTexture )
#endif
	{
		TRACE("");
		// Struct packing mismatch
		// Because The API impl itself allocates the texture, things are a little complicated.
		EVRRenderModelError ret = VRRenderModelError_Loading;
		RenderModel_TextureMap_t* linpackedTex;

#if ABIVER < 4
		while(ret == VRRenderModelError_Loading)
#endif
			ret = VRRenderModels()->LoadTexture_Async(textureId, &linpackedTex);

		// This doesn't appear to be spelled out in the API documentation, but hellovr_opengl suggests that the texture
		// isn't allocated on error (including Loading).
		if(ret == VRRenderModelError_None)
		{
			*ppTexture = new Repacked_RenderModel_TextureMap_t();
			repackRenderModelTextureMap(linpackedTex, *ppTexture);
		}

#if ABIVER < 4
		return ret == VRRenderModelError_None;
#else
		return ret;
#endif
	}

	WOVR_ENTRY void FreeTexture( Repacked_RenderModel_TextureMap_t *pTexture )
	{
		TRACE("");
		// Struct packing mismatch
		VRRenderModels()->FreeTexture(pTexture->original);
		delete pTexture;
	}

#if ABIVER >= 4
	WOVR_ENTRY EVRRenderModelError LoadTextureD3D11_Async( TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D )
	{
		TRACE("");
		return D3DProxy()->LoadTextureD3D11_Async(textureId, pD3D11Device, ppD3D11Texture2D);
	}

#if ABIVER >= 5
	WOVR_ENTRY EVRRenderModelError LoadIntoTextureD3D11_Async( TextureID_t textureId, void *pDstTexture )
	{
		TRACE("");
		return D3DProxy()->LoadIntoTextureD3D11_Async(textureId, pDstTexture);
	}
#endif

	WOVR_ENTRY void FreeTextureD3D11( void *pD3D11Texture2D )
	{
		TRACE("");
		D3DProxy()->FreeTextureD3D11(pD3D11Texture2D);
		return;
	}
#endif

	WOVR_ENTRY uint32_t GetRenderModelName( uint32_t unRenderModelIndex, VR_OUT_STRING() char *pchRenderModelName, uint32_t unRenderModelNameLen )
	{
		TRACE("");
		return VRRenderModels()->GetRenderModelName(unRenderModelIndex, pchRenderModelName, unRenderModelNameLen);
	}

	WOVR_ENTRY uint32_t GetRenderModelCount()
	{
		TRACE("");
		return VRRenderModels()->GetRenderModelCount();
	}

	WOVR_ENTRY uint32_t GetComponentCount( const char *pchRenderModelName )
	{
		TRACE("");
		return VRRenderModels()->GetComponentCount(pchRenderModelName);
	}

	WOVR_ENTRY uint32_t GetComponentName( const char *pchRenderModelName, uint32_t unComponentIndex, VR_OUT_STRING( ) char *pchComponentName, uint32_t unComponentNameLen )
	{
		TRACE("");
		return VRRenderModels()->GetComponentName(pchRenderModelName, unComponentIndex, pchComponentName, unComponentNameLen);
	}

	WOVR_ENTRY uint64_t GetComponentButtonMask( const char *pchRenderModelName, const char *pchComponentName )
	{
		TRACE("");
		return VRRenderModels()->GetComponentButtonMask(pchRenderModelName, pchComponentName);
	}

	WOVR_ENTRY uint32_t GetComponentRenderModelName( const char *pchRenderModelName, const char *pchComponentName, VR_OUT_STRING( ) char *pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen )
	{
		TRACE("");
		return VRRenderModels()->GetComponentRenderModelName(pchRenderModelName, pchComponentName, pchComponentRenderModelName, unComponentRenderModelNameLen);
	}

#if ABIVER < 4
	WOVR_ENTRY bool GetComponentState( const char *pchRenderModelName, const char *pchComponentName, const Repacked_VRControllerState_t *pControllerState, RenderModel_ComponentState_t *pComponentState )
#else
	WOVR_ENTRY bool GetComponentState( const char *pchRenderModelName, const char *pchComponentName, const Repacked_VRControllerState_t *pControllerState, const RenderModel_ControllerMode_State_t *pState, RenderModel_ComponentState_t *pComponentState )
#endif
	{
		TRACE("");
		// Struct packing mismatch
		VRControllerState_t linpacked;
		repackVRControllerState(pControllerState, &linpacked);

#if ABIVER < 4
		WARN("Passing NULL for controller mode state\n");
		return VRRenderModels()->GetComponentState(pchRenderModelName, pchComponentName, &linpacked, NULL, pComponentState);
#else
		return VRRenderModels()->GetComponentState(pchRenderModelName, pchComponentName, &linpacked, pState, pComponentState);
#endif
	}

	WOVR_ENTRY bool RenderModelHasComponent( const char *pchRenderModelName, const char *pchComponentName )
	{
		TRACE("");
		return VRRenderModels()->RenderModelHasComponent(pchRenderModelName, pchComponentName);
	}

	WOVR_ENTRY uint32_t GetRenderModelThumbnailURL( const char *pchRenderModelName, VR_OUT_STRING() char *pchThumbnailURL, uint32_t unThumbnailURLLen, vr::EVRRenderModelError *peError )
	{
		TRACE("");
		return VRRenderModels()->GetRenderModelThumbnailURL(pchRenderModelName, pchThumbnailURL, unThumbnailURLLen, peError);
	}

	WOVR_ENTRY uint32_t GetRenderModelOriginalPath( const char *pchRenderModelName, VR_OUT_STRING() char *pchOriginalPath, uint32_t unOriginalPathLen, vr::EVRRenderModelError *peError )
	{
		TRACE("");
		return VRRenderModels()->GetRenderModelOriginalPath(pchRenderModelName, pchOriginalPath, unOriginalPathLen, peError);
	}

	WOVR_ENTRY const char *GetRenderModelErrorNameFromEnum( vr::EVRRenderModelError error )
	{
		TRACE("");
		return VRRenderModels()->GetRenderModelErrorNameFromEnum(error);
	}
};

vr::IVRRenderModels* GETTER ()
{
	return (IVRRenderModels*) new PROXYCLASS ();
}
