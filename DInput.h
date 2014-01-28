#ifndef _DINPUT_H
#define _DINPUT_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#define JOYPADMAX 4

class CDInput
{
	LPDIRECTINPUT8 lpDInput;					//DirectInput Object
	LPDIRECTINPUTDEVICE8 lpDIJoyDev[JOYPADMAX];	//DirectInputDevice(Joystick)

public:
	CDInput();
	~CDInput();

	//DirectInputの初期化
	BOOL Init(HINSTANCE hinst,HWND hwnd);
	BOOL InitJoystick(HINSTANCE hinst,HWND hwnd);
	//ジョイスティック状態の取得
	BOOL GetJoyState2(int *rxL,int *ryL, int *rxR, int *ryR, WORD *rBut, int joynum);
	
	//ジョイスティックデバイスの認識
	void AcquireJoy(BOOL Flag=TRUE, int joynum=0);
};

extern LPDIRECTINPUTEFFECT g_pEffect[];
extern DWORD g_dwFFBAxisAmt;
extern HRESULT UpdateEffect(LONG iXForce, LONG iYForce, int joynum);

extern LPDIRECTINPUTDEVICE8 pJoyDev[];
extern int JoyCount;
extern int VibMode;

#endif
