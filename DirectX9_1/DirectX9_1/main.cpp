#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>

IDirect3D9* direct3d9;
IDirect3DDevice9* device9;
IDirect3DVertexBuffer9* vertexBuffer;
ID3DXFont* font;

//int white = 255;
//bool isBlack = true;

struct CUSTOM_VERTEX
{
	FLOAT x, y, z, w;
	DWORD color;
};

///���b�Z�[�W�ɔ���
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//int color;
	switch (msg)
	{
	case WM_CLOSE:
		//�E�B���h�E����
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			//ESC������
			PostQuitMessage(0);
		}
		break;
	case WM_PAINT:
		//color = isBlack ? 0 : white;
		device9->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 0), 1, 0);

		RECT rect;
		SetRect(&rect, 0, 0, 50, 50);
		font->DrawTextW(NULL, L"����", -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));
		if (SUCCEEDED(device9->BeginScene()))
		{
			//���\�[�X�����Ă��邩����ݒ�
			device9->SetStreamSource(0, vertexBuffer, 0, sizeof(CUSTOM_VERTEX));
			device9->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
			device9->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 18);
			device9->EndScene();
		}

		//isBlack = !isBlack;
		//�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@��؂�ւ�(�X���b�v)
		device9->Present(NULL, NULL, NULL, NULL);
		break;
	case WM_SIZE:
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	default:
		//�������Ȃ��ꍇ�͂��̊֐���Ԃ�
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}



INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),
		NULL,
		WindowProc,
		0,
		0,
		hInst,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		NULL,
		NULL,
		L"Window1",
		NULL
	};

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	HWND hwnd = CreateWindow(
		L"Window1",
		L"hoge",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1280,
		960,
		NULL,
		NULL,
		hInst,
		NULL
	);

	//D3D_SDK_VERSION�̓C���X�g�[������Ă���ŐV��Ԃ�
	//GPU�ƂȂ���
	direct3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d9 == NULL)
	{
		return 1;
	}

	//�X���b�v�`�F�[���̐ݒ�
	D3DPRESENT_PARAMETERS param = {
		1280,
		980,
		D3DFMT_UNKNOWN,		//D3DFMT_XXX �͐F�t�H�[�}�b�g�ݒ�
		1,		//2�p�ӂ��ď���
		D3DMULTISAMPLE_8_SAMPLES,
		0,
		D3DSWAPEFFECT_DISCARD,
		hwnd,
		TRUE,		//�E�B���h�E��?
		FALSE,
		D3DFMT_D16,
		0,
		D3DPRESENT_RATE_DEFAULT,
		D3DPRESENT_INTERVAL_DEFAULT
	};

	//GPU�ɐڑ������f�o�C�X
	if (FAILED(direct3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &param, &device9)))
	{
		return 1;
	}

	if (FAILED(D3DXCreateFont(device9, 24, 0, FW_HEAVY, 1, FALSE, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, L"�l�r �S�V�b�N", &font)))
	{
		return 1;
	}

	CUSTOM_VERTEX vertexArray[] =
	{
		{ 200.0f,  50.0f, 0.5f, 1.0f, 0xffffffff, }, // x, y, z, rhw, color
		{ 200.0f, 100.0f, 0.5f, 1.0f, 0xffffffff, },
		{ 150.0f, 100.0f, 0.5f, 1.0f, 0xffffffff, },

		{ 200.0f,  50.0f, 0.5f, 1.0f, 0xff111111, }, // x, y, z, rhw, color
		{ 250.0f,  100.0f, 0.5f, 1.0f, 0xff111111, },
		{ 200.0f, 100.0f, 0.5f, 1.0f, 0xff111111, },

		//2�i��
		{ 100.0f,  150.0f, 0.5f, 1.0f, 0xffffffff, }, // x, y, z, rhw, color
		{ 150.0f, 100.0f, 0.5f, 1.0f, 0xffffffff, },
		{ 150.0f, 150.0f, 0.5f, 1.0f, 0xffffffff, },

		{ 150.0f,  100.0f, 0.5f, 1.0f, 0xff111111, }, // x, y, z, rhw, color
		{ 200.0f, 100.0f, 0.5f, 1.0f, 0xff111111, },
		{ 150.0f, 150.0f, 0.5f, 1.0f, 0xff111111, },

		{ 200.0f,  100.0f, 0.5f, 1.0f, 0xff111111, }, // x, y, z, rhw, color
		{ 200.0f, 150.0f, 0.5f, 1.0f, 0xff111111, },
		{ 150.0f, 150.0f, 0.5f, 1.0f, 0xff111111, },


		{ 200.0f,  100.0f, 0.5f, 1.0f, 0xffffffff, }, // x, y, z, rhw, color
		{ 250.0f, 100.0f, 0.5f, 1.0f, 0xffffffff, },
		{ 200.0f, 150.0f, 0.5f, 1.0f, 0xffffffff, },

		{ 250.0f,  100.0f, 0.5f, 1.0f, 0xffffffff, }, // x, y, z, rhw, color
		{ 250.0f, 150.0f, 0.5f, 1.0f, 0xffffffff, },
		{ 200.0f, 150.0f, 0.5f, 1.0f, 0xffffffff, },

		{ 250.0f,  100.0f, 0.5f, 1.0f, 0xff111111, }, // x, y, z, rhw, color
		{ 300.0f, 150.0f, 0.5f, 1.0f, 0xff111111, },
		{ 250.0f, 150.0f, 0.5f, 1.0f, 0xff111111, },

		//3�i��

		{ 50,  200, 0.5f, 1.0f, 0xffffffff, }, // x, y, z, rhw, color
		{ 100, 150, 0.5f, 1.0f, 0xffffffff, },
		{ 100, 200, 0.5f, 1.0f, 0xffffffff, },

		{ 100,  150, 0.5f, 1.0f, 0xff111111, }, // x, y, z, rhw, color
		{ 150, 150, 0.5f, 1.0f, 0xff111111, },
		{ 100, 200, 0.5f, 1.0f, 0xff111111, },

		{ 150,  150, 0.5f, 1.0f, 0xff111111, }, // x, y, z, rhw, color
		{ 150, 200, 0.5f, 1.0f, 0xff111111, },
		{ 100, 200, 0.5f, 1.0f, 0xff111111, },

		{ 150.0f,  150, 0.5f, 1.0f, 0xffffffff, }, // x, y, z, rhw, color
		{ 200.0f, 150, 0.5f, 1.0f, 0xffffffff, },
		{ 150.0f, 200, 0.5f, 1.0f, 0xffffffff, },

		{ 200.0f,  150, 0.5f, 1.0f, 0xffffffff, }, // x, y, z, rhw, color
		{ 200.0f, 200, 0.5f, 1.0f, 0xffffffff, },
		{ 150.0f, 200, 0.5f, 1.0f, 0xffffffff, },


		{ 200.0f,  150, 0.5f, 1.0f, 0xff111111, }, // x, y, z, rhw, color
		{ 250.0f, 150, 0.5f, 1.0f, 0xff111111, },
		{ 200.0f, 200, 0.5f, 1.0f, 0xff111111, },

		{ 250.0f,  150, 0.5f, 1.0f, 0xff111111, }, // x, y, z, rhw, color
		{ 250.0f, 200, 0.5f, 1.0f, 0xff111111, },
		{ 200.0f, 200, 0.5f, 1.0f, 0xff111111, },

		{ 250,  150, 0.5f, 1.0f, 0xffffffff, }, // x, y, z, rhw, color
		{ 300, 150, 0.5f, 1.0f, 0xffffffff, },
		{ 250, 200, 0.5f, 1.0f, 0xffffffff, },

		{ 300,  150, 0.5f, 1.0f, 0xffffffff, }, // x, y, z, rhw, color
		{ 300, 200, 0.5f, 1.0f, 0xffffffff, },
		{ 250, 200, 0.5f, 1.0f, 0xffffffff, },

		{ 300,  200, 0.5f, 1.0f, 0xff111111, }, // x, y, z, rhw, color
		{ 300, 150, 0.5f, 1.0f, 0xff111111, },
		{ 350, 200, 0.5f, 1.0f, 0xff111111, },
	};


	//���_�o�b�t�@�̍쐬
	if (FAILED(device9->CreateVertexBuffer(6 * sizeof(CUSTOM_VERTEX), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &vertexBuffer, NULL)))
	{
		return 1;
	}

	VOID* pVertices = NULL;
	if (FAILED(vertexBuffer->Lock(0, sizeof(vertexArray), (void**)&pVertices, 0)))
	{
		return 1;
	}

	memcpy(pVertices, vertexArray, sizeof(vertexArray));

	CUSTOM_VERTEX* hoge = reinterpret_cast<CUSTOM_VERTEX*>(pVertices);

	vertexBuffer->Unlock();

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	MSG msg;
	//���2�͗~���������i���
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//TranslateMessage(&msg);
		//WindowProc�֐����Ă΂��
		DispatchMessageW(&msg);
	}

	font->Release();

	vertexBuffer->Release();

	device9->Release();

	direct3d9->Release();

	UnregisterClass(
		L"Window1",
		hInst);
}

