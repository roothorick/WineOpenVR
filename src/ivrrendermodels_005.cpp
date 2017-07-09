#include "ivrrendermodels.h"

class clone_IVRRenderModels_005
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

class proxy_IVRRenderModels_005 : public clone_IVRRenderModels_005
{
	WOVR_ENTRY EVRRenderModelError LoadRenderModel_Async( const char *pchRenderModelName, Repacked_RenderModel_t **ppRenderModel )
	{
		return fns_IVRRenderModels::LoadRenderModel_Async(pchRenderModelName, ppRenderModel);
	}

	WOVR_ENTRY void FreeRenderModel( Repacked_RenderModel_t *pRenderModel )
	{
		fns_IVRRenderModels::FreeRenderModel(pRenderModel);
	}

	WOVR_ENTRY EVRRenderModelError LoadTexture_Async( TextureID_t textureId, Repacked_RenderModel_TextureMap_t **ppTexture )
	{
		return fns_IVRRenderModels::LoadTexture_Async(textureId, ppTexture);
	}

	WOVR_ENTRY void FreeTexture( Repacked_RenderModel_TextureMap_t *pTexture )
	{
		fns_IVRRenderModels::FreeTexture(pTexture);
	}

	WOVR_ENTRY EVRRenderModelError LoadTextureD3D11_Async( TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D )
	{
		return fns_IVRRenderModels::LoadTextureD3D11_Async(textureId, pD3D11Device, ppD3D11Texture2D);
	}

	WOVR_ENTRY EVRRenderModelError LoadIntoTextureD3D11_Async( TextureID_t textureId, void *pDstTexture )
	{
		return fns_IVRRenderModels::LoadIntoTextureD3D11_Async(textureId, pDstTexture);
	}

	WOVR_ENTRY void FreeTextureD3D11( void *pD3D11Texture2D )
	{
		fns_IVRRenderModels::FreeTextureD3D11(pD3D11Texture2D);
		return;
	}

	WOVR_ENTRY uint32_t GetRenderModelName( uint32_t unRenderModelIndex, VR_OUT_STRING() char *pchRenderModelName, uint32_t unRenderModelNameLen )
	{
		return fns_IVRRenderModels::GetRenderModelName(unRenderModelIndex, pchRenderModelName, unRenderModelNameLen);
	}

	WOVR_ENTRY uint32_t GetRenderModelCount()
	{
		return fns_IVRRenderModels::GetRenderModelCount();
	}

	WOVR_ENTRY uint32_t GetComponentCount( const char *pchRenderModelName )
	{
		return fns_IVRRenderModels::GetComponentCount(pchRenderModelName);
	}

	WOVR_ENTRY uint32_t GetComponentName( const char *pchRenderModelName, uint32_t unComponentIndex, VR_OUT_STRING( ) char *pchComponentName, uint32_t unComponentNameLen )
	{
		return fns_IVRRenderModels::GetComponentName(pchRenderModelName, unComponentIndex, pchComponentName, unComponentNameLen);
	}

	WOVR_ENTRY uint64_t GetComponentButtonMask( const char *pchRenderModelName, const char *pchComponentName )
	{
		return fns_IVRRenderModels::GetComponentButtonMask(pchRenderModelName, pchComponentName);
	}

	WOVR_ENTRY uint32_t GetComponentRenderModelName( const char *pchRenderModelName, const char *pchComponentName, VR_OUT_STRING( ) char *pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen )
	{
		return fns_IVRRenderModels::GetComponentRenderModelName(pchRenderModelName, pchComponentName, pchComponentRenderModelName, unComponentRenderModelNameLen);
	}

	WOVR_ENTRY bool GetComponentState( const char *pchRenderModelName, const char *pchComponentName, const Repacked_VRControllerState_t *pControllerState, const RenderModel_ControllerMode_State_t *pState, RenderModel_ComponentState_t *pComponentState )
	{
		return fns_IVRRenderModels::GetComponentState(pchRenderModelName, pchComponentName, pControllerState, pState, pComponentState);
	}

	WOVR_ENTRY bool RenderModelHasComponent( const char *pchRenderModelName, const char *pchComponentName )
	{
		return fns_IVRRenderModels::RenderModelHasComponent(pchRenderModelName, pchComponentName);
	}

	WOVR_ENTRY uint32_t GetRenderModelThumbnailURL( const char *pchRenderModelName, VR_OUT_STRING() char *pchThumbnailURL, uint32_t unThumbnailURLLen, vr::EVRRenderModelError *peError )
	{
		return fns_IVRRenderModels::GetRenderModelThumbnailURL(pchRenderModelName, pchThumbnailURL, unThumbnailURLLen, peError);
	}

	WOVR_ENTRY uint32_t GetRenderModelOriginalPath( const char *pchRenderModelName, VR_OUT_STRING() char *pchOriginalPath, uint32_t unOriginalPathLen, vr::EVRRenderModelError *peError )
	{
		return fns_IVRRenderModels::GetRenderModelOriginalPath(pchRenderModelName, pchOriginalPath, unOriginalPathLen, peError);
	}

	WOVR_ENTRY const char *GetRenderModelErrorNameFromEnum( vr::EVRRenderModelError error )
	{
		return fns_IVRRenderModels::GetRenderModelErrorNameFromEnum(error);
	}
};

vr::IVRRenderModels* getIVRRenderModelsProxy_005()
{
	return (IVRRenderModels*) new proxy_IVRRenderModels_005();
}
