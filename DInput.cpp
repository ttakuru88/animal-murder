#include <math.h>
#include "DInput.h"
LPDIRECTINPUTDEVICE8 pJoyDev[JOYPADMAX];
int JoyCount;
//--------------------------------//
//  ジョイスティックデバイス列挙  //
//--------------------------------//
static BOOL CALLBACK InitJoystickInput(LPCDIDEVICEINSTANCE pdInst,LPVOID pvRef)
{
	LPDIRECTINPUT8 pdi=(LPDIRECTINPUT8)pvRef;

	if(JoyCount >= 4)
		return 1;

	//デバイスの作成
	if(pdi->CreateDevice(pdInst->guidInstance,&pJoyDev[JoyCount],NULL)!=DI_OK)
		return DIENUM_CONTINUE;
	//データフォーマット設定
	if(pJoyDev[JoyCount]->SetDataFormat(&c_dfDIJoystick)!=DI_OK){
		pJoyDev[JoyCount]->Release();
		pJoyDev[JoyCount]=NULL;
		return DIENUM_CONTINUE;
	}
	JoyCount++;

	return DIENUM_CONTINUE;
}
//------------------//
//  コンストラクタ  //
//------------------//
CDInput::CDInput()
{
	lpDInput=NULL;
	lpDIJoyDev[0]=lpDIJoyDev[1]=lpDIJoyDev[2]=lpDIJoyDev[3]=NULL;
}
//----------------//
//  デストラクタ  //
//----------------//
CDInput::~CDInput()
{
	for(int i=0; i<JoyCount; i++){
		if(lpDIJoyDev[i]!=NULL){
	        lpDIJoyDev[i]->Unacquire();
	        lpDIJoyDev[i]->Release();
	        lpDIJoyDev[i]=NULL;
		}
	}
	if(lpDInput!=NULL){
		lpDInput->Release();
		lpDInput=NULL;
	}
}
//-----------------------//
//  DirectInputの初期化  //
//-----------------------//
BOOL CDInput::Init(HINSTANCE hinst,HWND hwnd)
{
	HRESULT ret;
	ret=DirectInput8Create(hinst, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&lpDInput,NULL);
	if(ret != DI_OK)
		return FALSE;
	return TRUE;
}
//--------------------------------//
//  ジョイスティックデバイス設定  //
//--------------------------------//
BOOL CDInput::InitJoystick(HINSTANCE hinst,HWND hwnd)
{
	HRESULT ret;

	if(lpDInput==NULL){
		if(Init(hinst,hwnd)==FALSE) return FALSE;
	}
	//ジョイスティックのデバイス列挙
	lpDInput->EnumDevices(DI8DEVTYPE_JOYSTICK,InitJoystickInput,lpDInput,DIEDFL_ATTACHEDONLY);
	if(!JoyCount)
		return FALSE;

	//ジョイスティックの移動範囲設定(-127～+127の範囲）
	DIPROPRANGE di;
	di.diph.dwSize = sizeof(DIPROPRANGE);
	di.diph.dwHeaderSize = sizeof(di.diph);
	di.diph.dwHow = DIPH_BYOFFSET; 
	di.lMin = -127; 
	di.lMax = +127;
	// オートセンター無効
	DIPROPDWORD DIPropAutoCenter;
	DIPropAutoCenter.diph.dwSize       = sizeof(DIPropAutoCenter);
	DIPropAutoCenter.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	DIPropAutoCenter.diph.dwObj        = 0;
	DIPropAutoCenter.diph.dwHow        = DIPH_DEVICE;
	DIPropAutoCenter.dwData            = DIPROPAUTOCENTER_OFF;
	//エフェクト（反力のオブジェクト）を作成
	DIEFFECT eff;	
	//スティックの場合、軸は2つ以上なのでパラメーターは要素数2の配列にする
	DWORD rgdwAxes[2]={DIJOFS_X, DIJOFS_Y};
	LONG rglDirection[2]={0,0};
	DICONSTANTFORCE cf={0};
	ZeroMemory( &eff, sizeof(eff) );
	eff.dwSize                  = sizeof(DIEFFECT);
	eff.dwFlags                 = DIEFF_POLAR | DIEFF_OBJECTOFFSETS;
	eff.dwDuration              = INFINITE;
	eff.dwSamplePeriod          = 0;
	eff.dwGain                  = DI_FFNOMINALMAX;
	eff.dwTriggerButton         = DIEB_NOTRIGGER;
	eff.dwTriggerRepeatInterval = 0;
	eff.cAxes                   = g_dwFFBAxisAmt;
	eff.rgdwAxes                = rgdwAxes;
	eff.rglDirection            = rglDirection;
	eff.lpEnvelope              = 0;
	eff.cbTypeSpecificParams    = sizeof(DICONSTANTFORCE);
	eff.lpvTypeSpecificParams   = &cf;
	eff.dwStartDelay            = 0;
	for(int i=0; i<JoyCount; i++){
		lpDIJoyDev[i]=pJoyDev[i];
		if(lpDIJoyDev[i] == NULL)
			return FALSE;

		ret = lpDIJoyDev[i]->SetCooperativeLevel(hwnd,DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		if(ret != DI_OK){
			lpDIJoyDev[i]->Release();
			lpDIJoyDev[i] = NULL;
			return FALSE;
		}
		// 有効範囲設定
		di.diph.dwObj = DIJOFS_X; 
		lpDIJoyDev[i]->SetProperty(DIPROP_RANGE,&di.diph);
		di.diph.dwObj = DIJOFS_Y; 
		lpDIJoyDev[i]->SetProperty(DIPROP_RANGE,&di.diph);
		di.diph.dwObj = DIJOFS_Z; 
		lpDIJoyDev[i]->SetProperty(DIPROP_RANGE,&di.diph);
		di.diph.dwObj = DIJOFS_RZ; 
		lpDIJoyDev[i]->SetProperty(DIPROP_RANGE,&di.diph);
		// FFB　//////////////////////////////////////
		// FFBなので場合協調レベルはEXCLUSIVEとする
		pJoyDev[i]->SetCooperativeLevel(hwnd,DISCL_EXCLUSIVE | DISCL_FOREGROUND);
		// タイプをジョイスティック（ホイールコントローラーも含む）にする
		pJoyDev[i]->SetDataFormat(&c_dfDIJoystick);
		// オート・センター機能は無効にする（FFB効果の邪魔になるので）
		pJoyDev[i]->SetProperty(DIPROP_AUTOCENTER,&DIPropAutoCenter.diph);
		// エフェクトオブジェクト作成
		if(VibMode == TRUE){
			if( FAILED(pJoyDev[i]->CreateEffect( GUID_ConstantForce,&eff, &g_pEffect[i], NULL ) ) ){
				MessageBox(hwnd, "エフェクト・オブジェクトの作成に失敗しました\r\n振動機能無しでのプレイになります。", "error", MB_OK);
				VibMode = FALSE;
			}
		}
	}
	return TRUE;
}
//----------------------------//
//  ジョイスティック状態取得  //
//----------------------------//
BOOL CDInput::GetJoyState2(int *rxL,int *ryL, int *rxR, int *ryR, WORD *rBut, int joynum)
{
	DIJOYSTATE js;
	HRESULT ret;
	WORD But,ww;

	if(lpDIJoyDev[joynum-1]==NULL)
		return FALSE;

	//ジョイスティックの状態取得
	ret=lpDIJoyDev[joynum-1]->GetDeviceState(sizeof(DIJOYSTATE),&js);
	if(ret==DIERR_INPUTLOST){
		lpDIJoyDev[joynum-1]->Acquire();
		return FALSE;
	}
	if(ret != DI_OK)
		return FALSE;

	*rxL = js.lX;
	if(*rxL != -1){
		if(*rxL < 0 && *rxL > -30)
			*rxL = -30;
		else if(*rxL > 0 && *rxL < 30)
			*rxL = 30;
	}
	*ryL = js.lY;
	if(*ryL != -1){
		if(*ryL < 0 && *ryL > -30)
			*ryL = -30;
		else if(*ryL > 0 && *ryL < 30)
			*ryL = 30;
	}
	*rxR = js.lZ;
	*ryR = js.lRz;
	But=0;
	ww=0x8000;
	for(int i=0;i<16;i++){
		if(js.rgbButtons[i] & 0x80)
			But |= ww;
		ww>>=1;
	}
	*rBut = But;

	return TRUE;
}
//----------------------//
//  ジョイデバイス認識  //
//----------------------//
void CDInput::AcquireJoy(BOOL Flag, int joynum)
{
	if(lpDIJoyDev[joynum]==NULL)
		return;

	if(Flag==TRUE)
		lpDIJoyDev[joynum]->Unacquire();
	else
		lpDIJoyDev[joynum]->Acquire();
}
//-------------//
//  FFBを更新  //
//-------------//
HRESULT UpdateEffect(LONG iXForce, LONG iYForce, int joynum)
{
	//デバイスを有効にする。
	pJoyDev[joynum]->Acquire();
    //エフェクトのパラメーターを設定する。
	LONG rglDirection[2]={iXForce ,iYForce};
    DICONSTANTFORCE cf;
	
    cf.lMagnitude = (LONG)sqrt((double)iXForce*iXForce + (double)iYForce*iYForce);

    DIEFFECT eff;
    ZeroMemory( &eff, sizeof(eff) );
    eff.dwSize                = sizeof(DIEFFECT);
    eff.dwFlags               = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
    eff.cAxes                 = g_dwFFBAxisAmt;
    eff.rglDirection          = rglDirection; 
    eff.cbTypeSpecificParams  = sizeof(DICONSTANTFORCE);
    eff.lpvTypeSpecificParams = &cf;

    if(FAILED(g_pEffect[joynum]->SetParameters( &eff, DIEP_DIRECTION | DIEP_TYPESPECIFICPARAMS | DIEP_START )))
		return E_FAIL;

	return S_OK;
}