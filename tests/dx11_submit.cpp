// DirectX11 submit test.
// Submits solid magenta color fills in the form of D3D11 textures.
#include <openvr.h>

#include <cassert>

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>

ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;

uint32_t texWidth = 0;
uint32_t texHeight = 0;

void MakeEyeTexture( ID3D11Texture2D** tex, ID3D11RenderTargetView** rtv );
void ClearAndSubmit( ID3D11Texture2D* tex, ID3D11RenderTargetView* rtv, vr::EVREye eye );

int main()
{
	ID3D11Texture2D* pLeftEyeTex = NULL;
	ID3D11RenderTargetView* pLeftEyeRTV = NULL;
	ID3D11Texture2D* pRightEyeTex = NULL;
	ID3D11RenderTargetView* pRightEyeRTV = NULL;

	HRESULT hr;
	
	{
		vr::EVRInitError err = vr::VRInitError_None;
		vr::VR_Init( &err, vr::VRApplication_Scene );   assert( err != vr::VRInitError_None );
	}
	
	{
		int32_t pAdapterIdx = -1;
		IDXGIFactory* pFactory = NULL;
		IDXGIAdapter* pAdapter = NULL;
		
		vr::VRSystem()->GetDXGIOutputInfo( &pAdapterIdx );   assert( pAdapterIdx != -1 );
		hr = CreateDXGIFactory( __uuidof(IDXGIFactory), (void**) &pFactory );   assert( !FAILED(hr) );
		
		hr = pFactory->EnumAdapters( pAdapterIdx, &pAdapter );   assert( !FAILED(hr) );
		pFactory->Release();
		
		hr = D3D11CreateDevice(
				pAdapter, // pAdapter
				D3D_DRIVER_TYPE_HARDWARE, // DriverType
				NULL, // Software
				0, // Flags
				NULL, // pFeatureLevels
				0, // FeatureLevels
				D3D11_SDK_VERSION, // SDKVersion
				&pDevice, // ppDevice
				NULL, // pFeatureLevel
				&pContext // ppImmediateContext
		);   assert( !FAILED(hr) );
		pAdapter->Release();
	}
	
	vr::VRSystem()->GetRecommendedRenderTargetSize( &texWidth, &texHeight );
	
	MakeEyeTexture( &pLeftEyeTex, &pLeftEyeRTV );
	MakeEyeTexture( &pRightEyeTex, &pRightEyeRTV );
	
	//
	// ==== Loop ====
	//
	
	bool run = true;
	while(run)
	{
		vr::EVRCompositorError err = vr::VRCompositorError_None;
		err = vr::VRCompositor()->WaitGetPoses( NULL, 0, NULL, 0 );   assert( err == vr::VRCompositorError_None );
		
		ClearAndSubmit( pLeftEyeTex, pLeftEyeRTV, vr::Eye_Left );
		ClearAndSubmit( pRightEyeTex, pRightEyeRTV, vr::Eye_Right );
		
		vr::VREvent_t ev;
		while( vr::VRSystem()->PollNextEvent( &ev, sizeof(ev) ) )
		{
			if(ev.eventType == vr::VREvent_Quit)
			{
				vr::VRSystem()->AcknowledgeQuit_Exiting();
				run = false;
				break;
			}
		}
	}
	
	//
	// ==== Shutdown ====
	//
	
	vr::VR_Shutdown();
	
	pRightEyeRTV->Release();
	pRightEyeTex->Release();
	pLeftEyeRTV->Release();
	pLeftEyeTex->Release();
	pContext->Release();
	pDevice->Release();
}

void MakeEyeTexture( ID3D11Texture2D** tex, ID3D11RenderTargetView** rtv )
{
	HRESULT hr;
	
	{
		D3D11_TEXTURE2D_DESC dsc = {};
		dsc.Width = texWidth;
		dsc.Height = texHeight;
		dsc.MipLevels = 1;
		dsc.ArraySize = 1;
		dsc.Format = DXGI_FORMAT_R8G8B8A8_UINT;
		dsc.BindFlags = D3D11_BIND_RENDER_TARGET;
		
		hr = pDevice->CreateTexture2D( &dsc, NULL, tex );   assert( !FAILED(hr) );
	}
	
	{
		D3D11_RENDER_TARGET_VIEW_DESC dsc = {};
		dsc.Format = DXGI_FORMAT_R8G8B8A8_UINT;
		dsc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		
		hr = pDevice->CreateRenderTargetView( *tex, &dsc, rtv );   assert( !FAILED(hr) );
	}
}

void ClearAndSubmit( ID3D11Texture2D* tex, ID3D11RenderTargetView* rtv, vr::EVREye eye )
{
	{
		float color[4] = { 1.0f, 0.0f, 1.0f, 1.0f };
		pContext->ClearRenderTargetView( rtv, color );
	}

	{
		vr::EVRCompositorError err = vr::VRCompositorError_None;
		
		vr::Texture_t vrTex = {};
		vrTex.handle = (void*) tex;
		vrTex.eType = vr::TextureType_DirectX;
		err = vr::VRCompositor()->Submit( eye, &vrTex );   assert( err == vr::VRCompositorError_None );
	}
}
