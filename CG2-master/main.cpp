#include <Windows.h>

//�E�B���h�E�ݒ�

//�E�B���h�E�T�C�Y

//const int WINDOW_WINDTH = 1280;//����
//const int WINDOW_HEIGHT = 720;//�c��
//
////�E�B���h�E�N���X�̐ݒ�
//
//WNDCLASSEX w{};
//w.hInstance = GetModuleHandle(nullptr);		
//w.cbSize = sizeof(WNDCLASSEX)				//�E�B���h�E�v���V�[�W����ݒ�
//w.lpfnWndProc = (WNDPROC)WindowProc;		//�E�B���h�E�N���X��
//w.lpszClassName = L"DirectXGame";			//�E�B���h�E�n���h��
//w.hCursor = LoadCursor(NULL, IDC = ARROW);	//�J�[�\���w��
//
////�E�B���h�E�N���X��OP�ɓo�^����
//RegisterClassEx(&w);
////�E�B���h�E�T�C�Y�oX���W�AY���W�A�����A�c���p
//RECT wrc = { 0,0,WINDOW_WINDTH,WINDOW_HEIGHT };
////�����ŃT�C�Y��␳����
//AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);






//�E�B���h�E�v���V�[�W��
LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
//���b�Z�[�W�ɉ����ăQ�[���̌ŗL�������s��
{
	switch (msg) 
	{
		//�E�B���h�E���j�����ꂽ
		case WM_DESTROY:
			//OS�ɑ΂��ăA�v���̏I����`����
			PostQuitMessage(0);
			return 0;
	}

	//�W���̃��b�Z�[�W�������s��
	return DefWindowProc(hwnd, msg, wparam, lparam);

}

//Windows�A�v���ł̃G���g���[�|�C���g�imain�֐��j
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//�R���\�[���ւ̕����o��
{
	//OutputDebugStringA("Hello,DrectX!!/n");
	//�E�B���h�E�T�C�Y

	const int WINDOW_WINDTH = 1280;//����
	const int WINDOW_HEIGHT = 720;//�c��

	//�E�B���h�E�N���X�̐ݒ�

	WNDCLASSEX w{};
	w.cbSize = sizeof(WNDCLASSEX);				
	w.lpfnWndProc = (WNDPROC)WindowProc;		//�E�B���h�E�v���V�[�W����ݒ�
	w.lpszClassName = L"DirectXGame";			//�E�B���h�E�N���X��
	w.hInstance = GetModuleHandle(nullptr);		//�E�B���h�E�n���h��
	w.hCursor = LoadCursor(NULL, IDC_ARROW);	//�J�[�\���w��

	//�E�B���h�E�N���X��OP�ɓo�^����
	RegisterClassEx(&w);
	//�E�B���h�E�T�C�Y�oX���W�AY���W�A�����A�c���p
	RECT wrc = { 0,0,WINDOW_WINDTH,WINDOW_HEIGHT };
	//�����ŃT�C�Y��␳����
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);


	//�E�B���h�E�I�u�W�F�N�g�̐���
	HWND hwnd = CreateWindow(w.lpszClassName,	//�N���X��
		L"DirectXGame",							//�^�C�g���o�[
		WS_OVERLAPPEDWINDOW,					//�W���I�ȃE�B���h�E�X�^�C��
		CW_USEDEFAULT,							//�\��X���W�iOS�ɔC����j
		CW_USEDEFAULT,							//�\��Y���W�iOS�ɔC����j
		wrc.right - wrc.left,					//�E�B���h�E����
		wrc.bottom - wrc.top,					//�E�B���h�E�c��
		nullprt,								//�e�E�B���h�E�n���h��
		nullptr,								//���j���[�n���h��
		w.hInstance,							//�Ăяo���A�v���P�[�V�����n���h��
		nullptr);								//�I�v�V����

	ShowWindow(hwnd, SW_SHOW);

	return 0;
}