#ifndef GAMEAPP_H
#define GAMEAPP_H

#include <d3dcompiler.h>
#include <directxmath.h>
#include <DirectXColors.h>
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>
#include "d3dApp.h"
#include "LightHelper.h"
#include "Geometry.h"

class GameApp : public D3DApp
{
public:
	struct VertexPosNormalTex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 tex;
		static const D3D11_INPUT_ELEMENT_DESC inputLayout[3];
	};

	

	struct VSConstantBuffer
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX proj;
		DirectX::XMMATRIX worldInvTranspose;
		
	};

	struct PSConstantBuffer
	{
		DirectionalLight dirLight[10];
		PointLight pointLight[10];
		SpotLight spotLight[10];
		Material material;
		int numDirLight;
		int numPointLight;
		int numSpotLight;
		float pad;		// �����֤16�ֽڶ���
		DirectX::XMFLOAT4 eyePos;
	};

	enum class ShowMode { WoodCrate, FireAnim };

public:
	GameApp(HINSTANCE hInstance);
	~GameApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();

	// ��.fx/.hlsl�ļ��б�����ɫ��
	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

private:
	bool InitEffect();
	bool InitResource();
	bool ResetMesh(const Geometry::MeshData& meshData);


private:
	
	ComPtr<ID2D1SolidColorBrush> mColorBrush;				// ��ɫ��ˢ
	ComPtr<IDWriteFont> mFont;								// ����
	ComPtr<IDWriteTextFormat> mTextFormat;					// �ı���ʽ

	ComPtr<ID3D11InputLayout> mVertexLayout2D;				// ����2D�Ķ������벼��
	ComPtr<ID3D11InputLayout> mVertexLayout3D;				// ����3D�Ķ������벼��
	ComPtr<ID3D11Buffer> mVertexBuffer;						// ���㻺����
	ComPtr<ID3D11Buffer> mIndexBuffer;						// ����������
	ComPtr<ID3D11Buffer> mConstantBuffers[2];				// ����������
	int mIndexCount;										// ������������������С
	int mCurrFrame;											// ��ǰ���涯�����ŵ��ڼ�֡
	ShowMode mCurrMode;										// ��ǰ��ʾ��ģʽ

	ComPtr<ID3D11ShaderResourceView> mWoodCrate;			// ľ������
	std::vector<ComPtr<ID3D11ShaderResourceView>> mFireAnim;// ����������
	ComPtr<ID3D11SamplerState> mSamplerState;				// ������״̬

	ComPtr<ID3D11VertexShader> mVertexShader3D;				// ����3D�Ķ�����ɫ��
	ComPtr<ID3D11PixelShader> mPixelShader3D;				// ����3D��������ɫ��
	ComPtr<ID3D11VertexShader> mVertexShader2D;				// ����2D�Ķ�����ɫ��
	ComPtr<ID3D11PixelShader> mPixelShader2D;				// ����2D��������ɫ��

	VSConstantBuffer mVSConstantBuffer;						// �����޸�����VS��GPU�����������ı���
	PSConstantBuffer mPSConstantBuffer;						// �����޸�����PS��GPU�����������ı���
};


#endif