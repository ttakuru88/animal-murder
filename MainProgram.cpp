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

//必要なライブラリファイルのロード
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dsound.lib")

//--------------------------------------//
//	アプリケーション生成のメイン関数	//
//--------------------------------------//
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpszCmdLine,INT nCmdShow)
{
	WNDCLASSEX wc;
	HWND hw=NULL;
	MSG msg;

	static char szAppName[] = "どうぶつの里";
	wc.cbSize = sizeof(wc);
	wc.lpszClassName="どうぶつの里";
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
	// 設定ファイル読み込み
	FileRead();

	int wx, wy;
	wx = (FullScreen==TRUE)?0:WINDOW_X;
	wy = (FullScreen==TRUE)?0:WINDOW_Y;
	// ウィンドウ作成
	hw = CreateWindow(szAppName,szAppName, WS_VISIBLE | WS_POPUP, wx, wy, MEWIDTH, MEHEIGHT, NULL, NULL, hInstance, NULL);
	ShowWindow(hw, nCmdShow);	//ウィンドウの表示
	ValidateRect(hw, 0);		// WM_PAINTが呼ばれないようにする
	UpdateWindow(hw);
	// DirectXの初期化
	if(FAILED(InitApp(hw, hInstance)))
		return -1;
	//メインループ //////////////////////////////////
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
			Render(); // 3D描画

		eTim = timeGetTime();
		if(eTim-sTim > TIMERINTERVAL_MOV){
			sTim = eTim;
			//ジョイスティックの状態取得
			for(int i=1; i<=((DrawingMode==BATTLEWINDOW)?gNinzu:JoyCount); i++){
				if(Ch[i].cpu==TRUE && DrawingMode==BATTLEWINDOW) // CPU入力
					cpuInput(i);
				else if(KeyMode==FALSE)
					if(DInput.GetJoyState2(&Joy[i].LX, &Joy[i].LY, &Joy[i].RX, &Joy[i].RY, &Joy[i].But, i)==FALSE)
						Joy[i].LX = Joy[i].LY = Joy[i].RX = Joy[i].RY = Joy[i].But = 0;
			}
		}
	}

	FreeDx(); // 色々メモリ解放
	return 0;
}

//------------------------------//
//	メッセージループ内での処理	//
//------------------------------//
LRESULT CALLBACK MyWindowProc(HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	switch(iMsg){
		case WM_CREATE:
			for(int i=1; i<=4; i++){ // ポインタ初期位置
				Joy[i].x = MEWIDTH/2;
				Joy[i].y = MEHEIGHT/2;
			}
			// キャラ最大能力取得
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
			// 弾速度最大取得
			MaxtSpd = 0;
			for(int i=1; i<=ITEMCOUNT; i++)
				if(MaxtSpd < ItemDat[i].tSpd && ItemDat[i].type == WEPON)
					MaxtSpd = ItemDat[i].tSpd;
			MaxtSpd += 0.1f;

			srand((unsigned)time(NULL));
			break;
		case WM_DESTROY:
			// タイマー破棄
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
					if(bEnd) // 終了
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
					// 選択画面
					if(DrawingMode == STARTWINDOW || DrawingMode == CHARASELECTWINDOW || DrawingMode == STAGESELECTWINDOW || DrawingMode == GOMOKUWINDOW){
						SendView(D2D_SEL, 0, MEWIDTH, 0, MEHEIGHT, 0, hWnd);
						pDevice->Present( NULL, NULL, NULL, NULL );
					}
					// 戦闘画面
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
//	アプリケーションの初期化処理	//
//----------------------------------//
BOOL InitApp(HWND hwnd,HINSTANCE hInst)
{
	
	if(FAILED(InitD3d(hwnd)))
		return FALSE; // Direct3Dの初期化
	if(FAILED(initDirectSound(hwnd)))
		return -1; // DirectSoundの初期化
	if(FAILED(initDirectMusic(hwnd, g_pDirectSound )))
		return -1; // DirectMusicの初期化
	LoadMusicFile();
	// Directinputの初期化
	if(DInput.Init(hInst,hwnd)==FALSE)
		MessageBox(hwnd,"DirectInputが使用できません。","Error",MB_OK);
	if(DInput.InitJoystick(hInst,hwnd) == FALSE){
		MessageBox(hwnd,"ジョイスティックが使用できません。\nキーボードで操作してください","Error",MB_OK);
		KeyMode = TRUE;
	}
	else
		KeyMode = FALSE;
	if(VibMode == TRUE)
		CoInitialize(NULL);//FFBを使用するため、COMを初期化
	for(int i=0; i<JoyCount; i++)
		DInput.AcquireJoy(FALSE, i);

	// 弾メッシュ読み込み
	for(int i=1; i<TAMAFILEMAX; i++){
		char fname[64];
		wsprintf(fname, "%s%s", ItemXDir, BulletFile[i]);
		InitThing(&BulletObj[i], fname, &D3DXVECTOR3(0, 0, 0), FALSE, TYPE_TAMA);
	}
	//爆風メッシュ読み込み
	InitThing(&BlastObj,BlastFile,&D3DXVECTOR3(0, 0, 0),FALSE, TYPE_BLAST);
	// アイコンメッシュ読み込み
	for(int i=0; i<4; i++)
		InitThing(&IconObj[i], IconFile[i], &D3DXVECTOR3(0, 0, 0), FALSE, TYPE_ICON);
	InitThing(&LockOnObj,LockOnFile, &D3DXVECTOR3(0, 0, 0), FALSE, TYPE_SITE);

	// 描画モード切替
	ChangeDrawingMode(STARTWINDOW, JoyCount, hwnd);

	return TRUE;
}
//--------------//
//  文字列出力  //
//--------------//
VOID RenderString(LPSTR szStr,INT iX,INT iY)
{
	RECT rect={iX,iY,0,0};
	//文字列のサイズを計算
	pFont->DrawText(NULL,szStr,-1,&rect,DT_CALCRECT,NULL);
	// そのサイズでレンダリング
	pFont->DrawText(NULL,szStr,-1,&rect,DT_LEFT | DT_BOTTOM,0xff00ff00);
}
//----------------------------//
//  オブジェクトのメモリ開放  //
//----------------------------//
VOID FreeDx(void)
{
	// フィールド
	ReleaseObject(&StageDat.obj);
	for(int i=0; i<Syougaisu; i++) // 障害物
		ReleaseObject(&StageDat.trap[i]);
	for(int i=0; i<StageItemMax; i++) // アイテム
		ReleaseObject(&StageDat.item[i].obj);
	// キャラクタ
	for(int i=1; i<=JoyCount; i++){
		for(int j=0; j<Ch[i].Xcnt; j++)
			if(SubX[Ch[i].num][j][0] != '\0')
				if(Ch[i].obj[j].Mesh.dwNumMaterials)
					ReleaseObject(&Ch[i].obj[j]);
		// 打撃
		if(Ch[i].Dageki.Mesh.dwNumMaterials)
			ReleaseObject(&Ch[i].Dageki);
	}
	
	cleanUpDirectSound(); // DirectSoundの後始末
	cleanUpDirectMusic(); // DirectMusicの後始末
	SAFE_RELEASE( pDevice );
	SAFE_RELEASE( pD3d );
	CoUninitialize();
}
//--------------------//
//  ファイル読み込み  //
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
	// 画面モード
	if(fdate[0] == '1'){
		for(int i=0; EnumDisplaySettings(NULL, i, &devmode); i++){
			if(devmode.dmPelsWidth == 800 && devmode.dmPelsHeight == 600 && devmode.dmBitsPerPel == 16){
				FullScreen = TRUE;
				break;
			}
		}
		if(FullScreen == FALSE)
			MessageBox(NULL, "対応するディスプレイモードが見つかりません", "エラー", MB_OK);
		else{ // スクリーンチェンジ
			switch(ChangeDisplaySettings(&devmode, CDS_FULLSCREEN)){
				case DISP_CHANGE_SUCCESSFUL:   // 成功
					break;
				case DISP_CHANGE_RESTART: // 再起動が必要
					MessageBox(NULL, "設定の変更を有効にするには再起動が必要です", "エラー", MB_OK);
					break;
				default: // 失敗
					MessageBox(NULL, "設定の変更に失敗しました", "エラー", MB_OK);
					break;
			}
		}
	}
	// 効果音量
	if(fdate[4] == '1')
		SoundVol = -10000;
	else if(fdate[2] >= '0' && fdate[2] <= '9')
		SoundVol = ((fdate[2]-'0') - 9) * 400;
	// BGM音量
	if(fdate[8] == '1')
		MusicVol = -10000;
	else if(fdate[6] >= '0' && fdate[6] <= '9')
		MusicVol = ((fdate[6]-'0') - 9) * 400;
	// 振動OnOff
	if(fdate[10] == '1')
		VibMode = TRUE;
	else
		VibMode = FALSE;

	return 0;
}