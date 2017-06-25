#include "common.h"
#include "repacked_structs.h"

class clone_IVRRenderModels
{
	THISCALL virtual EVRRenderModelError LoadRenderModel_Async( const char *pchRenderModelName, Repacked_RenderModel_t **ppRenderModel ) = 0; // Struct packing mismatch
	THISCALL virtual void FreeRenderModel( Repacked_RenderModel_t *pRenderModel ) = 0; // Struct packing mismatch
	THISCALL virtual EVRRenderModelError LoadTexture_Async( TextureID_t textureId, Repacked_RenderModel_TextureMap_t **ppTexture ) = 0; // Struct packing mismatch
	THISCALL virtual void FreeTexture( Repacked_RenderModel_TextureMap_t *pTexture ) = 0; // Struct packing mismatch
	THISCALL virtual EVRRenderModelError LoadTextureD3D11_Async( TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D ) = 0;
	THISCALL virtual EVRRenderModelError LoadIntoTextureD3D11_Async( TextureID_t textureId, void *pDstTexture ) = 0;
	THISCALL virtual void FreeTextureD3D11( void *pD3D11Texture2D ) = 0;
	THISCALL virtual uint32_t GetRenderModelName( uint32_t unRenderModelIndex, VR_OUT_STRING() char *pchRenderModelName, uint32_t unRenderModelNameLen ) = 0;
	THISCALL virtual uint32_t GetRenderModelCount() = 0;
	THISCALL virtual uint32_t GetComponentCount( const char *pchRenderModelName ) = 0;
	THISCALL virtual uint32_t GetComponentName( const char *pchRenderModelName, uint32_t unComponentIndex, VR_OUT_STRING( ) char *pchComponentName, uint32_t unComponentNameLen ) = 0;
	THISCALL virtual uint64_t GetComponentButtonMask( const char *pchRenderModelName, const char *pchComponentName ) = 0;
	THISCALL virtual uint32_t GetComponentRenderModelName( const char *pchRenderModelName, const char *pchComponentName, VR_OUT_STRING( ) char *pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen ) = 0;
	THISCALL virtual bool GetComponentState( const char *pchRenderModelName, const char *pchComponentName, const Repacked_VRControllerState_t *pControllerState, const RenderModel_ControllerMode_State_t *pState, RenderModel_ComponentState_t *pComponentState ) = 0; // Struct packing mismatch
	THISCALL virtual bool RenderModelHasComponent( const char *pchRenderModelName, const char *pchComponentName ) = 0;
	THISCALL virtual uint32_t GetRenderModelThumbnailURL( const char *pchRenderModelName, VR_OUT_STRING() char *pchThumbnailURL, uint32_t unThumbnailURLLen, vr::EVRRenderModelError *peError ) = 0;
	THISCALL virtual uint32_t GetRenderModelOriginalPath( const char *pchRenderModelName, VR_OUT_STRING() char *pchOriginalPath, uint32_t unOriginalPathLen, vr::EVRRenderModelError *peError ) = 0;
	THISCALL virtual const char *GetRenderModelErrorNameFromEnum( vr::EVRRenderModelError error ) = 0;
};

class proxy_IVRRenderModels : public clone_IVRRenderModels
{
public:
	proxy_IVRRenderModels(IVRRenderModels* real) { realImpl = real; }

	THISCALL EVRRenderModelError LoadRenderModel_Async( const char *pchRenderModelName, Repacked_RenderModel_t **ppRenderModel )
	{
		// Struct packing mismatch
		// Because The API impl itself allocates the RM, things are a little complicated.
		EVRRenderModelError ret;
		RenderModel_t* linpackedRM;

		ret = realImpl->LoadRenderModel_Async(pchRenderModelName, &linpackedRM);

		// This doesn't appear to be spelled out in the API documentation, but hellovr_opengl suggests that the RM isn't
		// allocated on error (including Loading).
		if(ret == VRRenderModelError_None)
		{
			*ppRenderModel = new Repacked_RenderModel_t();
			repackRenderModel(linpackedRM, *ppRenderModel);
		}

		return ret;
	}

	THISCALL void FreeRenderModel( Repacked_RenderModel_t *pRenderModel )
	{
		// Struct packing mismatch
		realImpl->FreeRenderModel(pRenderModel->original);
		delete pRenderModel;
	}

	THISCALL EVRRenderModelError LoadTexture_Async( TextureID_t textureId, Repacked_RenderModel_TextureMap_t **ppTexture )
	{
		// Struct packing mismatch
		// Because The API impl itself allocates the texture, things are a little complicated.
		EVRRenderModelError ret;
		RenderModel_TextureMap_t* linpackedTex;

		ret = realImpl->LoadTexture_Async(textureId, &linpackedTex);

		// This doesn't appear to be spelled out in the API documentation, but hellovr_opengl suggests that the texture
		// isn't allocated on error (including Loading).
		if(ret == VRRenderModelError_None)
		{
			*ppTexture = new Repacked_RenderModel_TextureMap_t();
			repackRenderModelTextureMap(linpackedTex, *ppTexture);
		}

		return ret;
	}

	THISCALL void FreeTexture( Repacked_RenderModel_TextureMap_t *pTexture )
	{
		// Struct packing mismatch
		realImpl->FreeTexture(pTexture->original);
		delete pTexture;
	}

	THISCALL EVRRenderModelError LoadTextureD3D11_Async( TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D )
	{
		printf("WOVR fixme: LoadTextureD3D11_Async stub!\n");
		return VRRenderModelError_NotSupported;
	}

	THISCALL EVRRenderModelError LoadIntoTextureD3D11_Async( TextureID_t textureId, void *pDstTexture )
	{
		printf("WOVR fixme: LoadIntoTextureD3D11_Async stub!\n");
		return VRRenderModelError_NotSupported;

	}

	THISCALL void FreeTextureD3D11( void *pD3D11Texture2D )
	{
		printf("WOVR fixme: FreeTextureD3D11 stub!\n");
		return;
	}

	THISCALL uint32_t GetRenderModelName( uint32_t unRenderModelIndex, VR_OUT_STRING() char *pchRenderModelName, uint32_t unRenderModelNameLen )
	{
		return realImpl->GetRenderModelName(unRenderModelIndex, pchRenderModelName, unRenderModelNameLen);
	}

	THISCALL uint32_t GetRenderModelCount()
	{
		return realImpl->GetRenderModelCount();
	}

	THISCALL uint32_t GetComponentCount( const char *pchRenderModelName )
	{
		return realImpl->GetComponentCount(pchRenderModelName);
	}

	THISCALL uint32_t GetComponentName( const char *pchRenderModelName, uint32_t unComponentIndex, VR_OUT_STRING( ) char *pchComponentName, uint32_t unComponentNameLen )
	{
		return realImpl->GetComponentName(pchRenderModelName, unComponentIndex, pchComponentName, unComponentNameLen);
	}

	THISCALL uint64_t GetComponentButtonMask( const char *pchRenderModelName, const char *pchComponentName )
	{
		return realImpl->GetComponentButtonMask(pchRenderModelName, pchComponentName);
	}

	THISCALL uint32_t GetComponentRenderModelName( const char *pchRenderModelName, const char *pchComponentName, VR_OUT_STRING( ) char *pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen )
	{
		return realImpl->GetComponentRenderModelName(pchRenderModelName, pchComponentName, pchComponentRenderModelName, unComponentRenderModelNameLen);
	}

	THISCALL bool GetComponentState( const char *pchRenderModelName, const char *pchComponentName, const Repacked_VRControllerState_t *pControllerState, const RenderModel_ControllerMode_State_t *pState, RenderModel_ComponentState_t *pComponentState )
	{
		// Struct packing mismatch
		VRControllerState_t linpacked;
		repackVRControllerState(pControllerState, &linpacked);

		return realImpl->GetComponentState(pchRenderModelName, pchComponentName, &linpacked, pState, pComponentState);
	}

	THISCALL bool RenderModelHasComponent( const char *pchRenderModelName, const char *pchComponentName )
	{
		return realImpl->RenderModelHasComponent(pchRenderModelName, pchComponentName);
	}

	THISCALL uint32_t GetRenderModelThumbnailURL( const char *pchRenderModelName, VR_OUT_STRING() char *pchThumbnailURL, uint32_t unThumbnailURLLen, vr::EVRRenderModelError *peError )
	{
		return realImpl->GetRenderModelThumbnailURL(pchRenderModelName, pchThumbnailURL, unThumbnailURLLen, peError);
	}

	THISCALL uint32_t GetRenderModelOriginalPath( const char *pchRenderModelName, VR_OUT_STRING() char *pchOriginalPath, uint32_t unOriginalPathLen, vr::EVRRenderModelError *peError )
	{
		return realImpl->GetRenderModelOriginalPath(pchRenderModelName, pchOriginalPath, unOriginalPathLen, peError);
	}

	THISCALL const char *GetRenderModelErrorNameFromEnum( vr::EVRRenderModelError error )
	{
		return realImpl->GetRenderModelErrorNameFromEnum(error);
	}

private:
	IVRRenderModels* realImpl;
};

vr::IVRRenderModels* getIVRRenderModelsProxy (IVRRenderModels* real)
{
	return (IVRRenderModels*) new proxy_IVRRenderModels(real);
}
