#include "DInput.h"
#include "Setup.h"
#include "Bounding.h"
#include "D2D.h"
#include "D3D.h"
#include "OnTimer.h"
#include "BattleTimer.h"
#include "Ray.h"
#include "KeyDown.h"
#include "DMusic.h"
#include "Cpu.h"
#include "MISSILE.h"

//�K�v�ȃ��C�u�����t�@�C���̃��[�h
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dsound.lib")

//--------------------------------------//
//	�A�v���P�[�V���������̃��C���֐�	//
//--------------------------------------//
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpszCmdLine,INT nCmdShow)
{
	WNDCLASSEX wc;
	HWND hw=NULL;
	MSG msg;

	static char szAppName[] = "�ǂ��Ԃ̗�";
	wc.cbSize = sizeof(wc);
	wc.lpszClassName="�ǂ��Ԃ̗�";
	wc.lpfnWndProc=MyWindowProc;
	wc.style=CS_HREDRAW | CS_VREDRAW || CS_BYTEALIGNCLIENT;
	wc.hInstance=hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName=NULL;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon (NULL, IDI_APPLICATION) ;
	if(!RegisterClassEx(&wc))
		return FALSE;
	// �ݒ�t�@�C���ǂݍ���
	FileRead();

	int wx, wy;
	wx = (FullScreen==TRUE)?0:WINDOW_X;
	wy = (FullScreen==TRUE)?0:WINDOW_Y;
	// �E�B���h�E�쐬
	hw = CreateWindow(szAppName,szAppName, WS_VISIBLE | WS_POPUP, wx, wy, MEWIDTH, MEHEIGHT, NULL, NULL, hInstance, NULL);
	ShowWindow(hw, nCmdShow);	//�E�B���h�E�̕\��
	ValidateRect(hw, 0);		// WM_PAINT���Ă΂�Ȃ��悤�ɂ���
	UpdateWindow(hw);
	// DirectX�̏�����
	if(FAILED(InitApp(hw, hInstance)))
		return -1;
	//���C�����[�v //////////////////////////////////
	DWORD sTim,eTim;
	sTim=timeGetTime();
	ZeroMemory(&msg, sizeof(msg));
	while(msg.message != WM_QUIT){
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)){
			if(!GetMessage(&msg, NULL, 0, 0))
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if(DrawingMode == BATTLEWINDOW || DrawingMode == MENUWINDOW || DrawingMode == RESULTWINDOW)
			Render(); // 3D�`��

		eTim = timeGetTime();
		if(eTim-sTim > TIMERINTERVAL_MOV){
			sTim = eTim;
			//�W���C�X�e�B�b�N�̏�Ԏ擾
			for(int i=1; i<=((DrawingMode==BATTLEWINDOW)?gNinzu:JoyCount); i++){
				if(Ch[i].cpu==TRUE && DrawingMode==BATTLEWINDOW) // CPU����
					cpuInput(i);
				else if(KeyMode==FALSE)
					if(DInput.GetJoyState2(&Joy[i].LX, &Joy[i].LY, &Joy[i].RX, &Joy[i].RY, &Joy[i].But, i)==FALSE)
						Joy[i].LX = Joy[i].LY = Joy[i].RX = Joy[i].RY = Joy[i].But = 0;
			}
		}
	}

	FreeDx(); // �F�X���������
	return 0;
}

//------------------------------//
//	���b�Z�[�W���[�v���ł̏���	//
//------------------------------//
LRESULT CALLBACK MyWindowProc(HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	switch(iMsg){
		case WM_CREATE:
			for(int i=1; i<=4; i++){ // �|�C���^�����ʒu
				Joy[i].x = MEWIDTH/2;
				Joy[i].y = MEHEIGHT/2;
			}
			// �L�����ő�\�͎擾
			for(int c=1; c<=8; c++){
				if(ChDat[c].maxhp  > maxN[0]) maxN[0] = (float)ChDat[c].maxhp;
				if(ChDat[c].nStmin > maxN[1]) maxN[1] = (float)ChDat[c].nStmin;
				if(ChDat[c].nAtack > maxN[2]) maxN[2] = (float)ChDat[c].nAtack;
				if(ChDat[c].nGard  > maxN[3]) maxN[3] = (float)ChDat[c].nGard;
				if(ChDat[c].nSpeed > maxN[4]) maxN[4] = ChDat[c].nSpeed;
				if(ChDat[c].nDash  > maxN[5]) maxN[5] = ChDat[c].nDash;
				if(ChDat[c].nJump  > maxN[6]) maxN[6] = ChDat[c].nJump;
				if(ChDat[c].nTurn  > maxN[7]) maxN[7] = ChDat[c].nTurn;
			}
			// �e���x�ő�擾
			MaxtSpd = 0;
			for(int i=1; i<=ITEMCOUNT; i++)
				if(MaxtSpd < ItemDat[i].tSpd && ItemDat[i].type == WEPON)
					MaxtSpd = ItemDat[i].tSpd;
			MaxtSpd += 0.1f;

			srand((unsigned)time(NULL));
			break;
		case WM_DESTROY:
			// �^�C�}�[�j��
			KillTimer(hWnd, MOVETIMER);
			KillTimer(hWnd, STMINTIMER);
			KillTimer(hWnd, TRAPTIMER);
			KillTimer(hWnd, ITEMTIMER);
			KillTimer(hWnd, BLASTTIMER);
			DestroyWindow(hWnd);
			PostQuitMessage(0);
			break;
		case WM_TIMER:
			switch(wParam){
				case MOVETIMER:
					if(bEnd) // �I��
						SendMessage(hWnd, WM_DESTROY, 0, 0);
					if(TimerFlg == SETTIMER){
						SetTimer(hWnd, STMINTIMER,TIMERINTERVAL_ST,  NULL);
						SetTimer(hWnd, ITEMTIMER, TIMERINTERVAL_ITM, NULL);
						SetTimer(hWnd, TRAPTIMER, TIMERINTERVAL_TRP, NULL);
						SetTimer(hWnd, BLASTTIMER,TIMERINTERVAL_BLS, NULL);
						TimerFlg = NULL;
					}
					else if(TimerFlg == KILLTIMER){
						KillTimer(hWnd, STMINTIMER);
						KillTimer(hWnd, ITEMTIMER);
						KillTimer(hWnd, TRAPTIMER);
						KillTimer(hWnd, BLASTTIMER);
						TimerFlg = NULL;
					}
					// �I�����
					if(DrawingMode == STARTWINDOW || DrawingMode == CHARASELECTWINDOW || DrawingMode == STAGESELECTWINDOW || DrawingMode == GOMOKUWINDOW){
						SendView(D2D_SEL, 0, MEWIDTH, 0, MEHEIGHT, 0, hWnd);
						pDevice->Present( NULL, NULL, NULL, NULL );
					}
					// �퓬���
					else if(DrawingMode == BATTLEWINDOW || DrawingMode == MENUWINDOW || DrawingMode == RESULTWINDOW)
						BattleTimer(hWnd);
					break;
				case STMINTIMER:
					StminTimer();
					break;
				case ITEMTIMER:
					ItemTimer();
					break;
				case TRAPTIMER:
					TrapTimer();
					break;
				case BLASTTIMER:
					BlastTimer();
					break;
				default:
					return(DefWindowProc(hWnd, iMsg, wParam, lParam));
			}
			break;
		case WM_SIZE:
			width = (float)(lParam & 0xffff);
			height = (float)((lParam >> 16) & 0xffff);
			g_aspect = width / height;
			break;
		case WM_ACTIVATE:
			for(int i=0; i<JoyCount; i++)
				DInput.AcquireJoy(wParam==WA_INACTIVE, i);
			break;
		case WM_KEYDOWN:
			if(wParam == VK_ESCAPE)
				SendMessage(hWnd, WM_DESTROY, wParam, lParam);
			KeyDown(wParam);
			break;
		case WM_KEYUP:
			KeyUp(wParam);
			break;
		case WM_CHAR:
			KeyChara(wParam);
			break;
		case WM_SETCURSOR:
			SetCursor(NULL);
			break;
		default:
			return DefWindowProc(hWnd, iMsg, wParam, lParam);
	}
	return NULL;
}

//----------------------------------//
//	�A�v���P�[�V�����̏���������	//
//----------------------------------//
BOOL InitApp(HWND hwnd,HINSTANCE hInst)
{
	
	if(FAILED(InitD3d(hwnd)))
		return FALSE; // Direct3D�̏�����
	if(FAILED(initDirectSound(hwnd)))
		return -1; // DirectSound�̏�����
	if(FAILED(initDirectMusic(hwnd, g_pDirectSound )))
		return -1; // DirectMusic�̏�����
	LoadMusicFile();
	// Directinput�̏�����
	if(DInput.Init(hInst,hwnd)==FALSE)
		MessageBox(hwnd,"DirectInput���g�p�ł��܂���B","Error",MB_OK);
	if(DInput.InitJoystick(hInst,hwnd) == FALSE){
		MessageBox(hwnd,"�W���C�X�e�B�b�N���g�p�ł��܂���B\n�L�[�{�[�h�ő��삵�Ă�������","Error",MB_OK);
		KeyMode = TRUE;
	}
	else
		KeyMode = FALSE;
	if(VibMode == TRUE)
		CoInitialize(NULL);//FFB���g�p���邽�߁ACOM��������
	for(int i=0; i<JoyCount; i++)
		DInput.AcquireJoy(FALSE, i);

	// �e���b�V���ǂݍ���
	for(int i=1; i<TAMAFILEMAX; i++){
		char fname[64];
		wsprintf(fname, "%s%s", ItemXDir, BulletFile[i]);
		InitThing(&BulletObj[i], fname, &D3DXVECTOR3(0, 0, 0), FALSE, TYPE_TAMA);
	}
	//�������b�V���ǂݍ���
	InitThing(&BlastObj,BlastFile,&D3DXVECTOR3(0, 0, 0),FALSE, TYPE_BLAST);
	// �A�C�R�����b�V���ǂݍ���
	for(int i=0; i<4; i++)
		InitThing(&IconObj[i], IconFile[i], &D3DXVECTOR3(0, 0, 0), FALSE, TYPE_ICON);
	InitThing(&LockOnObj,LockOnFile, &D3DXVECTOR3(0, 0, 0), FALSE, TYPE_SITE);

	// �`�惂�[�h�ؑ�
	ChangeDrawingMode(STARTWINDOW, JoyCount, hwnd);

	return TRUE;
}
//--------------//
//  ������o��  //
//--------------//
VOID RenderString(LPSTR szStr,INT iX,INT iY)
{
	RECT rect={iX,iY,0,0};
	//������̃T�C�Y���v�Z
	pFont->DrawText(NULL,szStr,-1,&rect,DT_CALCRECT,NULL);
	// ���̃T�C�Y�Ń����_�����O
	pFont->DrawText(NULL,szStr,-1,&rect,DT_LEFT | DT_BOTTOM,0xff00ff00);
}
//----------------------------//
//  �I�u�W�F�N�g�̃������J��  //
//----------------------------//
VOID FreeDx(void)
{
	// �t�B�[���h
	ReleaseObject(&StageDat.obj);
	for(int i=0; i<Syougaisu; i++) // ��Q��
		ReleaseObject(&StageDat.trap[i]);
	for(int i=0; i<StageItemMax; i++) // �A�C�e��
		ReleaseObject(&StageDat.item[i].obj);
	// �L�����N�^
	for(int i=1; i<=JoyCount; i++){
		for(int j=0; j<Ch[i].Xcnt; j++)
			if(SubX[Ch[i].num][j][0] != '\0')
				if(Ch[i].obj[j].Mesh.dwNumMaterials)
					ReleaseObject(&Ch[i].obj[j]);
		// �Ō�
		if(Ch[i].Dageki.Mesh.dwNumMaterials)
			ReleaseObject(&Ch[i].Dageki);
	}
	
	cleanUpDirectSound(); // DirectSound�̌�n��
	cleanUpDirectMusic(); // DirectMusic�̌�n��
	SAFE_RELEASE( pDevice );
	SAFE_RELEASE( pD3d );
	CoUninitialize();
}
//--------------------//
//  �t�@�C���ǂݍ���  //
//--------------------//
int FileRead(void)
{
	DEVMODE devmode;
	HANDLE fp;
	DWORD Fsz;
	char fdate[64];
	fp = CreateFile("Setup.ini", GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	SetFilePointer(fp, 0, 0, FILE_BEGIN);
	ReadFile(fp, fdate, 64, &Fsz, NULL);
	CloseHandle(fp);
	// ��ʃ��[�h
	if(fdate[0] == '1'){
		for(int i=0; EnumDisplaySettings(NULL, i, &devmode); i++){
			if(devmode.dmPelsWidth == 800 && devmode.dmPelsHeight == 600 && devmode.dmBitsPerPel == 16){
				FullScreen = TRUE;
				break;
			}
		}
		if(FullScreen == FALSE)
			MessageBox(NULL, "�Ή�����f�B�X�v���C���[�h��������܂���", "�G���[", MB_OK);
		else{ // �X�N���[���`�F���W
			switch(ChangeDisplaySettings(&devmode, CDS_FULLSCREEN)){
				case DISP_CHANGE_SUCCESSFUL:   // ����
					break;
				case DISP_CHANGE_RESTART: // �ċN�����K�v
					MessageBox(NULL, "�ݒ�̕ύX��L���ɂ���ɂ͍ċN�����K�v�ł�", "�G���[", MB_OK);
					break;
				default: // ���s
					MessageBox(NULL, "�ݒ�̕ύX�Ɏ��s���܂���", "�G���[", MB_OK);
					break;
			}
		}
	}
	// ���ʉ���
	if(fdate[4] == '1')
		SoundVol = -10000;
	else if(fdate[2] >= '0' && fdate[2] <= '9')
		SoundVol = ((fdate[2]-'0') - 9) * 400;
	// BGM����
	if(fdate[8] == '1')
		MusicVol = -10000;
	else if(fdate[6] >= '0' && fdate[6] <= '9')
		MusicVol = ((fdate[6]-'0') - 9) * 400;
	// �U��OnOff
	if(fdate[10] == '1')
		VibMode = TRUE;
	else
		VibMode = FALSE;

	return 0;
}