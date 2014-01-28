#ifndef _SETUP_H
#define _SETUP_H
// インクルード
#include <time.h>
#include <dsound.h>
#include <dmusicc.h>
#include <dmusici.h>
#include <windows.h>
#include <d3dx9.h>
#include <stdlib.h>

// でばぐ
#include <stdio.h>
///////////////////////////////////////////////////////////////////////
// 定数定義
/*--- 単なる数値マクロと列挙 ---*/
#define PI 3.14159265358979323846264 // 円周率

enum{
	MOVETIMER=101,// 移動タイマＩＤ
	STMINTIMER,   // スタミナタイマＩＤ
	ITEMTIMER,    // アイテムタイマ
	TRAPTIMER,    // トラップタイマ
	BLASTTIMER    // 爆風タイマＩＤ
};
enum{
	FREEALL,    // メモリ全部開放
	FREETHING,  // 障害物メモリ開放
	FREERELEASE // リリース以外開放
};
#define SELRETURN 0x0000 // 戻る
#define SELENTER  0xffff // 決定

#define ATACK_HIT 3  // ジャンプフラグ攻撃後
#define RAKKA 2      // ジャンプフラグ落下中
#define JEND 4       // ジャンプ終了
#define JFLOAT 5
#define JSTOP 4      // ジャンプ後の停止時間
// オブジェクト種類
enum{
	TYPE_FIELD,
	TYPE_CHAR,
	TYPE_SYOUGAI,
	TYPE_TRAP,
	TYPE_DAGEKI,
	TYPE_ITEM,
	TYPE_TAMA,
	TYPE_ICON,
	TYPE_DOKU,
	TYPE_BLAST,
	TYPE_SITE,
	TYPE_BETA,
	TYPE_IN,
	TYPE_OUT,
	TYPE_JUMP,
	TYPE_MOUNT
};
// ダメージタイプ
enum{
	DAGEDMG=1,
	JUMPDMG,
	WANADMG,
	SHOTDMG,
	DOKUDMG,
	BLASTDMG,
};
// ゲーム画面
enum{
	STARTWINDOW,
	CHARASELECTWINDOW,
	STAGESELECTWINDOW,
	BATTLEWINDOW,
	MENUWINDOW,
	RESULTWINDOW,
	GOMOKUWINDOW
};
// アイテム種類
#define WEPON 1
#define SUBITEM 2
// アイテムID
enum{
	PATINKO=1,
	BAZUKA,
	RORABUREDO,
	NORMALSHOT,
	NIKU,
	GETA,
	KARASI,
	SHOTGUN,
	ENKEI,
	SYURYUDAN,
	BAKURETSU,
	ZIRAI,
	KANTSU,
	TESTITEM1,
	TESTITEM2,
	TESTITEM3,
	ZIKANSA,
	BOM,
	KOUSEN,
	SUNAIPA,
	MISSILE,
	MIRA,
	KAN,
	INBIZI,
	MOUNT_TAMA,
	BEAMSODE
};
// アイテム効果
#define BAKURETSU_2    100

#define LOOKRIGHT    1
#define LOOKLEFT    -1
#define PITCHUP   -1
#define PITCHDOWN  1

// soundアイディー
#define BGM_m 1
#define BGM_M 2
enum{
	SD_SHOT1=1,
	SD_SHOT2,
	SD_SHOT3,
	SD_SHOT4,
	SD_SHOT5,
	SD_SHOT6,
	SD_SHOT7,
	SD_SHOT8,
	SD_SHOT9,
	SD_SHOT10,
	SD_SHOT11,
	SD_SHOT12,
	SD_SHOT13,
	SD_SHOT14,
	SD_SHOT15,
	SD_ATACK1,
	SD_ATACK2,
	SD_ATACK3,
	SD_ATACK4,
	SD_ATACK5,
	SD_CLICK1,
	SD_CLICK2,
	SD_DEATH,
	SD_DOG,
	SD_HIT1,
	SD_HIT2,
	SD_HIT3,
	SD_JUMP,
	SD_RL,
	SD_ICON,
	SD_START,
	SD_WATER,
	SD_ITEMUSE,
	SD_ITEMGET,
	SD_MENU,
	SD_MOVE,
	SD_DMG,
	SD_ENTER,
	SD_RETURN,
	SD_SHOT16,
	SD_SHOT17,
	SD_SHOT18,
	SD_EXPLOSION1,
	SD_EXPLOSION2,
	SD_EXPLOSION3,
	SD_SHOT19,
	SD_SHOT20,
	SD_SHOT21,
	SD_JUMP2,
	SD_WARP
};

#define	kSTR_LENGTH 512
#define MAX_PATH 260
#define	kDirectMusicChannels 64
// DirectSound関連定数
#define	kPrimaryChannels 2     // ステレオにしたいので2チャネル
#define	kPrimaryFreq     44100 // 周波数（Hz単位）
#define	kPrimaryBitRate  16    // 16bit

#define	kNUM_OF_SE_BUFFERS	4

#define RRBTN 1
#define RDBTN 2
#define RLBTN 3
#define RUBTN 4
// ゲームモード
#define ROYALE_MODE 1
#define TEAM_MODE 2
#define GOMOKU_MODE 3
// レイ方向
enum{
	RAY_MAE,
	RAY_USIRO,
	RAY_UE,
	RAY_SITA,
	RAY_HIDARI,
	RAY_MIGI
};

#define FULLSCREENMODE 2
#define WINDOWMODE 3

#define GOTOP 0
#define GOBOTTOM 1

#define SETTIMER 1
#define KILLTIMER 2

enum{
	ICON_BIKKURI,
	ICON_SIGUMA,
	ICON_NICONICO,
	ICON_IKARI
};

#define GETITEM 100

///////////////////////////////////////////////////////////////////////
/*--- ゲームバランスに関する設定 ---*/
#define TIMERINTERVAL_MOV 40 // 移動タイマ間隔
#define TIMERINTERVAL_ST  50 // スタミナタイマ間隔
#define TIMERINTERVAL_ITM 40 // アイテム効果間隔
#define TIMERINTERVAL_TRP 100// トラップタイマ間隔
#define TIMERINTERVAL_BLS 60 // 爆風タイマ間隔

#define DUSHST 3    // ダッシュで消費するスタミナ
#define JUMPST 30   // ジャンプで消費するスタミナ
#define DAGEST 40   // 打撃攻撃で消費するスタミナ

#define DSTOP 4     // 打撃攻撃後の停止時間
#define WANASTOP 20 // 罠にかかって停止する時間

#define HIT_DIST 1.5    // 当たり判定距離
#define BLUR_DIST 15.0  // 見える距離

#define NIKUKAIFUKU 50  // 肉で回復する量

#define FIRST_A 0.2f  // 初速度
#define FIRST_G 0.02f // 重力
#define MAX_G   0.48f  // 最大落下速度
// キャラ移動とカメラ移動速度
#define CHAR_MOVE 1500.0
#define CAMERA_MOVE 2000.0
#define CHAR_KAITEN 2000.0
// アイテム効果
#define UP_SPD    1.0f // ローラブレードで上がる移動速度
#define UP_TURN   0.5f // ローラブレードで上がる旋回速度
#define DOWN_SPD  0.5f // ゲタで下がる移動速度
#define DOWN_TURN 0.5f // ゲタで下がる旋回速度
#define UP_JUMP   0.5f // アイテムであがるジャンプ力
#define UP_ATK    100  // アイテムであがる攻撃力
#define UP_DEF    100  // アイテムであがる防御力

#define STAGEMOVEDIST 15 // ステージ選択アイコン移動速度
#define DMGBARLOST 3     // ダメージバー減少量
#define VIBTIMEMAX 30    // 振動最大継続時間

#define MAXSPEED 3.0f // 最大速度

#define CAMERAPITCHMAX 1.7f // カメラ上下動きの上限

#define STOPMAX 20

#define BAKURETSUMAX 50

#define CPUCENSER 10.0f  // CPUがキャラ見つける距離

#define MAXVECY 100 // 最大落下y座標

#define FLOATMAX 0.08f // 浮遊中の動き最大
#define FLOATVALUECHANGE 0.03f
#define FLOATMOVEMIN 0.001f

#define MOUNT_INTER 10 // 火山頻度
///////////////////////////////////////////////////////////////////////
/*--- 開発により数値が変わる定義 ---*/
#define SYOUGAISUU 15      // 障害物設置数

#define ITEMMAX 4       // 所持アイテム最大数
#define STAGEITEMMAX 50 // ステージ設置可能アイテム最大数
#define BULLETMAX 100   // 移動中の弾の最大数

#define ITEMCOUNT   26 // データ登録アイテム数
#define TAMAFILEMAX 12 // 弾のＸファイル数+1

#define STAGECNT 10  // ステージ数

#define SOUNDFILEMAX (50+1) // 効果音数+1
#define kNUM_OF_BGM  (4+1) // BGM数+1

#define SUBXCNT 8 // 代わり身の術

#define BLASTMAX 100 // 爆風の最大数
///////////////////////////////////////////////////////////////////////
/*--- 関数的マクロ ---*/
// オブジェクトpのメモリ開放
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = NULL; } } 

// ジョイスティックのボタンが押されているか
// プレイヤー n 番のボタンが押されていればTRUE
#define BTN_RL(n) (0x8000&Joy[n].But)
#define BTN_RU(n) (0x4000&Joy[n].But)
#define BTN_RD(n) (0x2000&Joy[n].But)
#define BTN_RR(n) (0x1000&Joy[n].But)
#define BTN_L1(n) (0x0800&Joy[n].But)
#define BTN_R1(n) (0x0400&Joy[n].But)
#define BTN_L2(n) (0x0200&Joy[n].But)
#define BTN_R2(n) (0x0100&Joy[n].But)
#define BTN_L3(n) (0x0080&Joy[n].But)
#define BTN_R3(n) (0x0040&Joy[n].But)
#define BTN_SELECT(n) (0x0020&Joy[n].But)
#define BTN_START(n) (0x0010&Joy[n].But)
// ジョイスティックを押してることにする。
#define ON_RL(n) Joy[n].But|=0x8000
#define ON_RU(n) Joy[n].But|=0x4000
#define ON_RD(n) Joy[n].But|=0x2000
#define ON_RR(n) Joy[n].But|=0x1000
#define ON_L1(n) Joy[n].But|=0x0800
#define ON_R1(n) Joy[n].But|=0x0400
#define ON_L2(n) Joy[n].But|=0x0200
#define ON_R2(n) Joy[n].But|=0x0100
#define ON_L3(n) Joy[n].But|=0x0080
#define ON_R3(n) Joy[n].But|=0x0040
#define ON_SELECT(n) Joy[n].But|=0x0020
#define ON_START(n)  Joy[n].But|=0x0010
// ジョイスティックを押してない
#define OFF_RL(n) Joy[n].But&=0x7fff
#define OFF_RU(n) Joy[n].But&=0xbfff
#define OFF_RD(n) Joy[n].But&=0xdfff
#define OFF_RR(n) Joy[n].But&=0xefff
#define OFF_L1(n) Joy[n].But&=0xf7ff
#define OFF_R1(n) Joy[n].But&=0xfbff
#define OFF_L2(n) Joy[n].But&=0xfdff
#define OFF_R2(n) Joy[n].But&=0xfeff
#define OFF_L3(n) Joy[n].But&=0xff7f
#define OFF_R3(n) Joy[n].But&=0xffbf
#define OFF_SELECT(n) Joy[n].But&=0xffdf
#define OFF_START(n)  Joy[n].But&=0xffef

#define SAFE_DELETE_ARRAY(me) {if(me){delete[] (me); ( me )=NULL;}}
// 2次元描画用ファイル読み込み
#define TextureFromFile(fname,padd) D3DXCreateTextureFromFileEx(pDevice,fname,0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_DEFAULT,0xff000000,NULL,NULL,padd)
// 最大、最小内に収める
#define LimitsMaxMin(a,min,max) a=(max<a)?max:(min>a)?min:a
///////////////////////////////////////////////////////////////////////
/*--- デザイン関連 ---*/
// 人数選択ボックス
#define NINZU_X 550
#define NINZU_Y 300
#define NINZU_K 75  // ボックス間隔
#define NINZU_W 150 // ボックス横幅
#define NINZU_H 50  // ボックス高さ
// キュラ選択画面
#define CHAR_X  125
#define CHAR_K  140
#define CHAR_Y1 360 // 1段目
#define CHAR_Y2 480 // 2段目
#define CHAR_H  100
#define CHAR_W  100
// 選択済みキャラクタ表示位置
#define SELCHAR_X 20
#define SELCHAR_K 200
#define SELCHAR_Y 20.0f
#define SELCHAR_W 80
#define SELCHAR_H 80
// 能力バー
#define SELCHARBAR_X (SELCHAR_X+30)
#define SELCHARBAR_K 25 // Y座標
#define SELCHARBAR_Y (SELCHAR_X+SELCHAR_H+10)
#define NBAR_H 10
#define NBAR_W 100
// 能力ヘッダー
#define NHEADBAR_X 20
#define NHEADBAR_Y (SELCHARBAR_Y-6)
// ステージ選択画面
#define STAGE_X 50
#define STAGE_K 150
#define STAGE_Y 300
#define STAGE_W 100
#define STAGE_H 100
#define STAGERAND_Y 450.0f
#define STAGERAND_X 290.0f
// 戻るボタン
#define RETURN_X 670.0f
#define RETURN_Y 500.0f
#define RETURN_W 100
#define RETURN_H 50
// 決定ボタン
#define ENTER_X 670.0f
#define ENTER_Y 425.0f
#define ENTER_W 100
#define ENTER_H 50
// メニューウィンドウ
#define MENU_X 100
#define MENU_Y 200
#define MENU_K 50
#define MENU_H 250
#define MENU_W 200
// 選択済みステージ画像表示位置
#define SELSTAGE_X 75
#define SELSTAGE_Y 50
// 照準位置
// 照準画像サイズ
#define PINTWIDTH 39
#define PINTHEIGHT 39
#define PITX_2   400  // 2プレイX
#define PITY_1_1 300  // 1プレイ1コンY
#define PITY_2_1 150  // 2プレイ1コンY
#define PITY_2_2 450  // 2プレイ2コンY
#define PITX_34_13 200 // 3,4プレイ1,3コンX
#define PITX_34_24 600 // 3,4プレイ2,4コンX
#define PITY_34_12 150 // 3,4プレイ1,2コンY
#define PITY_34_34 450 // 3,4プレイ3,4コンY
// HPバー
#define HPBARX_2     40.0f  // 2プレイX
#define HPBARY_2_1   16.0f  // 2プレイ1コンY
#define HPBARY_2_2   316.0f // 2プレイ2コンY
#define HPBARX_34_13 40.0f  // 3,4プレイ1,3コンX
#define HPBARX_34_24 640.0f // 3,4プレイ2,4コンX
#define HPBARY_34_12 16.0f  // 3,4プレイ1,2コンY
#define HPBARY_34_34 316.0f // 3,4プレイ3,4コンY
// MPバー
#define MPBARX_2     40.0f  // 2プレイX
#define MPBARY_2_1   38.0f  // 2プレイ1コンY
#define MPBARY_2_2   338.0f // 2プレイ2コンY
#define MPBARX_34_13 40.0f  // 3,4プレイ1,3コンX
#define MPBARX_34_24 640.0f // 3,4プレイ2,4コンX
#define MPBARY_34_12 38.0f  // 3,4プレイ1,2コンY
#define MPBARY_34_34 338.0f // 3,4プレイ3,4コンY
// MPバー
#define RLBARX_2     40.0f  // 2プレイX
#define RLBARY_2_1   81.0f  // 2プレイ1コンY
#define RLBARY_2_2   381.0f // 2プレイ2コンY
#define RLBARX_34_13 40.0f  // 3,4プレイ1,3コンX
#define RLBARX_34_24 640.0f // 3,4プレイ2,4コンX
#define RLBARY_34_12 81.0f  // 3,4プレイ1,2コンY
#define RLBARY_34_34 381.0f // 3,4プレイ3,4コンY
// バーサイズ
#define BARHEIGHT 10    // バー高さ
#define HSDBARWIDTH 150 // HP,ST,dmgバー横幅
#define RLBARWIDTH 100  // リロードバー横幅
// 死亡ロゴ
#define SIBOUX_2 300.0f
#define SIBOUY_2_1 110.0f
#define SIBOUY_2_2 450.0f
#define SIBOUX_34_13 100.0f
#define SIBOUX_34_24 500.0f
#define SIBOUY_34_12 100.0f
#define SIBOUY_34_34 400.0f
#define SIBOUW 200
#define SIBOUH 100
// 矢印画像
#define LEFT_X 200
#define LEFT_Y 450
#define RIGHT_X 400
#define RIGHT_Y 450
#define LEFTRIGHT_W 80
#define LEFTRIGHT_H 100
// アイテムボックス
#define ITEMBOXW 39
#define ITEMBOXH 39
// ゲームモード
#define MODE_W 50
#define MODE_H 50
#define MODE_K 100
// チーム色
#define TCOL_X 45
#define TCOL_K 60
#define TCOL_H 40
#define TCOL_W 40
// ウィンドウサイズ
#define MEWIDTH 800     // 初期画面横幅
#define MEHEIGHT 600    // 初期画面高さ
// スクリーン位置取得
#define WINDOW_X ((GetSystemMetrics( SM_CXSCREEN ) - MEWIDTH ) / 2)
#define WINDOW_Y ((GetSystemMetrics( SM_CYSCREEN ) - MEHEIGHT ) / 2)

// レーダーアイコンサイズ
#define RDCHARWIDTH 11
#define RDCHARHEIGHT 16
// レーダーアイテム場所サイズ
#define ITEMPTWIDTH 10
#define ITEMPTHEIGHT 10
// レーダー弾場所サイズ
#define BULLETPTWIDTH 5
#define BULLETPTHEIGHT 5
///////////////////////////////////////////////////////////////////////
#include "Structure.h"
//関数プロトタイプ/////////////////////////////////////
// MainProgram.cpp
LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL InitApp(HWND hwnd, HINSTANCE hInst);	//アプリケーションの初期化処理
VOID RenderString(LPSTR ,INT,INT);
VOID FreeDx(void);     // オブジェクトの開放
int FileRead(void);
// D3D.h
HRESULT InitD3d(HWND);
VOID Render(); //描画するのに使う
VOID RenderThingBlur(THING* pThing, int lp, int show, MESHSTRUCT *lpMesh);
VOID SendView(VIEW4 vw, int player, int w1, int w2, int h1, int h2, HWND hWnd); // ビュー行列
HRESULT ChangeViewport(DWORD dwX,DWORD dwY,DWORD dwWidth,DWORD dwHeight);
HRESULT InitThing(THING *,LPSTR,D3DXVECTOR3*, BOOL, int);
void ChangeStage(int Stage);
int ReleaseObject(THING *pObject);
void SetViewMatrix(int vi, PLAYERCHARASTATE *aCh);
int ItemPut(int StgPt, int inum, float x, float y, float z);
// D2D.h
int DrawD2DSelect(HWND hWnd);
int DrawD2DSelectSt(HWND hWnd);
int StageDec(int *hit, int i);
void OpSelNinzu(void);
void IpSelNinzu(int lp, HWND hWnd);
void OpSelChara(void);
void IpSelChara(int lp);
void OpSelStage(void);
void IpSelStage(int lp, HWND hWnd, int *r1flg, int *l1flg);
void OpGomoku(void);
void IpGomoku(int lp);
int ReleaseStartWindow(void);
int ReleaseCharaSelectWindow(void);
int ReleaseStageSelectWindow(void);
int ReleaseGomokuWindow(void);
int SelectChara(int lp, int cnum, int btn);
int GameStart(HWND hWnd);
int ChangeDrawingMode(int mode, int Nin, HWND hWnd);
int SelectResultNinzu(int nin);
void MovePointer(int lopmax);
int ReleaseResultWindow(void);
int DrawD2DBattle(void);
int SelectCharaPos(int lp, int btn);
int LoadTexture(HWND hWnd);
void Setvec3Position(D3DXVECTOR3 *Pos, int nin, float x1, float y1, float x2, float y2);
int SelectTeam(int lp, int tnum, int btn);
void Calcdmg(int c, int cc, int type, int t);
void DrawD2D(float x, float y, LPDIRECT3DTEXTURE9 pP);
void GomokuSyouhai(int lp, int x, int y);
// BattleTimer.h
int BattleTimer(HWND hWnd);
void BattleVib(int lp, float *Pitup, float *Yawup);
void BattleStartButton(int lp, int *stflg);
void BattleJump(int lp);
void CharaJump(int lp, float fuka, int usest);
void BattleCharaMove(int lp, float *yxmove, float *yzmove, float *xxmove, float *xzmove);
void BattleCharaCollisionToStage(int lp, float yxmove, float yzmove, float xxmove, float xzmove);
void BattleCharaCollisionToChara(int lp);
void BattleCharaCollisionToBeta(int lp);
void BattleCharaCollisionToDageki(int lp);
void BattleCharaCollisionToTrap(int lp);
void BattleCharaCollisionToBullet(int lp);
void BattleCharaCollisionToItem(int lp);
void BattleCharaCollisionToBlast(int lp);
void BattleCameraMove(int lp, float Pitup, float Yawup);
void BattleCharaIcon(int lp);
void BattleLockOn(int lp);
void BattleDageki(int lp);
void BattleItemUse(int lp);
void BattleZoom(int lp);
int BringIcon(int inum, int lp, D3DXVECTOR3 vecPt);
// OnTimer.h
int StminTimer(void);
int ItemTimer(void);
int TrapTimer(void);
int BlastTimer(void);
int UseItem(int iNum, int lp, int useNum);
int ReadFrame(int n);
int ObjectPositionCopy(THING *p1, THING *p2);
int ChangeCharaMesh(int lp, int inum);
int UseWepon(int lp, int useNum, int iNum, int shotMax);
int WeponEffect_Bunretsu(int lp, int t, int shotMax, int wnum, int wtag);
int CalcBulletPitch(int lp, int i, int *hit, D3DXVECTOR3 *Intersect);
void HansyaSuruyo(int lp, int cc, int t, int inum);
void CharaDied(int cc, int vx, int vy, int vt);
void SetBlast(int lp, int t);
void BulletHitObstacle(int lp, int t);
void DecBullet(int lp, int useNum, int iNum);
int CompDist(THING *Aobj, THING *Bobj, float limDist);
int BulletStageRayInter(int lp, int t, int RayVec);
// Bounding.h
BOOL CompareLength(BBOX* ,BBOX* ,D3DXVECTOR3* ,D3DXVECTOR3* );
HRESULT InitBBox(THING* );
BOOL OBBCollisionDetection(THING* ,THING* );
HRESULT InitSphere(THING* );
BOOL SphereCollision(THING* ,THING* );
// Ray.h
BOOL RayIntersect(THING*  ,THING* ,FLOAT*,D3DXVECTOR3* ,D3DXVECTOR3*);
BOOL RayShoot(PLAYERCHARASTATE* ,THING* ,FLOAT*,D3DXVECTOR3*);
HRESULT FindVerticesOnPoly(LPD3DXMESH ,DWORD ,D3DXVECTOR3* );
int RayFooter(THING *pThing, FLOAT *pfDistance, D3DXVECTOR3 *pvIntersect, D3DXVECTOR3 *vecStart, D3DXVECTOR3 *vecEnd);
// DMusic.h
HRESULT	initDirectMusic( HWND hWnd, LPDIRECTSOUND8 pTheDS );
HRESULT loadSegmentFromMusicFile( char *aWaveFileName , theMusic *aMusic );
HRESULT playAMusic(theMusic *aMusic);
HRESULT	stopAMusic(theMusic *aMusic);
HRESULT	isPlayingAMusic(theMusic *aMusic);
HRESULT setAVolume(long aVolume);
void cleanUpDirectMusic(void);
void cleanUpDirectSound(void);
void initTheMUSIC(void);
void LoadMusicFile(void);
HRESULT	cleanUpTheSounds(void);
HRESULT	initTheSounds(void);
HRESULT	setupSounds(void);
HRESULT	loadSoundsFromWaveFile(char *aWaveFileName, theSounds *aSound, DWORD aCreationFlags, GUID guid3DAlgorithm, DWORD aNumOfBuffers);
HRESULT fillupSoundBuffer( theSounds *aSound, DWORD aLockBuffer );
HRESULT readWaveToBuffer( theSounds *aSound , BYTE* aBuffer, DWORD aSizeToRead, DWORD* aReadedData );
HRESULT	restoreDSBuffer( LPDIRECTSOUNDBUFFER aDSBuffer , BOOL* pRestoreFlag );
HRESULT openWaveFile( char	*aWaveFileName , theSounds *aSound );
HRESULT	closeWaveFile( theSounds *aSound );
HRESULT rewindWaveFile(theSounds *aSound);
HRESULT playASound( theSounds *aSound , DWORD aPriority ,DWORD aFlag ,BOOL aOverride);
HRESULT StopASound( theSounds *aSound );
HRESULT RewindASound( theSounds *aSound );
DWORD selectFreeBuffer(theSounds *aSound , BOOL aOverride);
// Cpu.h
int MoveCalc(float pit, float yaw);
int cpuInput(int lp);
void VecAlterAngle(float *x, float *y, float *z, int lp, THING *Target, float *teki, float *zibun);
void CpuMoveYaw(int lp, int VEC, float Ateki, float Azibun, float dist);
int CpuIconChange(int lp, int inum);
void GetMinDist(int lp, int *target, float *MinDist, THING *Target, int i);
void CpuGetItem(int lp, int Itype, int *target, int oltarget, float *x, float *y, float *z, float *teki, float *zibun);
void CpuUseItem(int lp);
void CpuSelAtackType(int lp, float x, float y, float z, int target);
//missile.h
int MissileMove(int lp,int t,int target);
int VecAlterAngle(float *x, float *y, float *z, int lp,int t, int target, float *teki, float *zibun);
float Movebalc(float pit, float yaw);
// KeyDown.h
int KeyChara(WPARAM key);
int KeyDown(WPARAM key);
int KeyUp(WPARAM key);
void ChangeCharaByKey(int i);
// グローバル変数宣言 ///////////////////////////////
// Direct3D
LPDIRECT3D9 pD3d;
LPDIRECT3DDEVICE9 pDevice; // Direct3Dデバイス
D3DVIEWPORT9 g_VP;         // ビューポート
// DirectInput
CDInput DInput;		    // DirectInput制御クラス
DWORD g_dwFFBAxisAmt = 2; // スティックのぐりぐりの数
LPDIRECTINPUTEFFECT g_pEffect[4] = {NULL,NULL,NULL,NULL}; // FFBで使用
// DirectMusic
IDirectMusicAudioPath8*   g_pDMAudioPath = NULL;
IDirectMusicLoader8*      g_pDMLoader = NULL;
IDirectMusicPerformance8* g_pDMPerformance = NULL;
LPDIRECTSOUND8 g_pDirectSound = NULL; // DirectSoundオブジェクト
bool g_bComInit = FALSE;
const TCHAR* kMusicPath = TEXT("./sound/");   //musicフォルダ
const TCHAR* kSoundsPath = TEXT("./sound/"); //soundsフォルダ
const int kSoundsPathLength	= lstrlen(kSoundsPath);
const int kMusicPathLength	= lstrlen(kMusicPath);

int DrawingMode=NULL;
int Ninzu, cpuNinzu, gNinzu;    // プレイ人数
int Stage;    // 現在使用中のステージ
int chselcnt; // キャラ決定人数
int GameMode=ROYALE_MODE;
int bEnd=FALSE;
int TeamCnt[5],TeamNowCnt[5],TeamKazu; // チーム人数
int FullScreen=FALSE, VibMode=TRUE;

float g_aspect = MEWIDTH/MEHEIGHT;    // サイズ比率
float width=MEWIDTH, height=MEHEIGHT; // 現在の画面サイズ

int StageMove=0; // ステージ選択アイコン移動数
float maxN[8];   // 最大能力
int StageItemMax;
int Syougaisu, TimerFlg;
int SoundVol, MusicVol; // 音量
int AliveCnt, WinTeam;
float MaxtSpd;

int Goban[19][19], putTurn, putCnt, goWin;

LPD3DXFONT pFont = NULL;     // 文字フォント
LPDIRECT3DTEXTURE9 pBar;     // 2D描画する画面枠
LPDIRECT3DTEXTURE9 pChar[5]; // マップキャラ
LPDIRECT3DTEXTURE9 pItemBoxW, pItemBoxI, pItemBoxYellow, pResultBox; // アイテムボックス
LPDIRECT3DTEXTURE9 pItemIcon[ITEMCOUNT+1];  // アイテムアイコン
LPDIRECT3DTEXTURE9 pPint;    // 照準
LPDIRECT3DTEXTURE9 pLeft, pRight; // 矢印
LPDIRECT3DTEXTURE9 pHpBar, pHpBarDmg, pHpBarRec, pStBar, pRlBar, pnBar;
LPDIRECT3DTEXTURE9 pSelnin[5], pSelchar[9], pSelstage[STAGECNT], pSelcharX[9], pTeamCol[5], pTeamWaku[5];
LPDIRECT3DTEXTURE9 pReturn, pEnter, pStartBox, pSibou, pnHead, pCpu, pStageR;
LPDIRECT3DTEXTURE9 pBackimg, pGolog, pBackStage, pItemPt1, pItemPt2, pBulletPt;
LPDIRECT3DTEXTURE9 pPointer[5], pIsi[6]; // ポインタ
LPD3DXSPRITE pSprite;           // 2D描画のキャンパス

//Ray.h
FLOAT fDistance=0;
D3DXVECTOR3 vIntersect;
D3DXVECTOR3 Ray[]={ D3DXVECTOR3(0,0,-1),
					D3DXVECTOR3(0,0,1),
					D3DXVECTOR3(0,1,0),
					D3DXVECTOR3(0,-1,0),
					D3DXVECTOR3(1,0,0),
					D3DXVECTOR3(-1,0,0),
					D3DXVECTOR3(1,0,-1),
					D3DXVECTOR3(-1,0,1),
					D3DXVECTOR3(-1,0,-1),
					D3DXVECTOR3(1,0,1)};
// デバグ
char debug1[512];
char debug2[512];
char debug3[512];
int battleFlg, KeyChar=1;
int KeyMode;    // キーボードモード

#endif