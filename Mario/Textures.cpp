#include "Textures.h"
#include <Windows.h>
#include <d3d9.h>
#include "Utils.h"
Textures* Textures::__instance = NULL;

Textures::Textures() {

}

Textures* Textures::GetInstance()
{
	if (__instance == NULL) __instance = new Textures();
	return __instance;
}

void Textures::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DTEXTURE9 texture;

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}

	textures[id] = texture;

	DebugOut(L"[INFO] Texture loaded Ok: id=%d, %s\n", id, filePath);
}


LPDIRECT3DTEXTURE9 Textures::Get(unsigned int i) {
	return textures[i];
}

void Textures::LoadResources() {

	ifstream File;
	File.open(L"resource\\texture.txt");
	int rgb1, rgb2, rgb3, id;
	string path;
	while (!File.eof())
	{
		File >> id >> path >> rgb1 >> rgb2 >> rgb3;
		std::wstring stemp = std::wstring(path.begin(), path.end());		//change string to LPSWSTR
		LPCWSTR sw = stemp.c_str();
		Add(id, sw, D3DCOLOR_XRGB(rgb1, rgb2, rgb3));
		DebugOut(L"[INFO] Texture loaded Ok: id=%d, %s \n", id, stemp);
	}
	File.close();
}

void Textures::Clear()
{
	for (auto x : textures)
	{
		LPDIRECT3DTEXTURE9 tex = x.second;
		if (tex != NULL) tex->Release();
	}

	textures.clear();
}