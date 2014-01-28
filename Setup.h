#ifndef _SETUP_H
#define _SETUP_H
// �C���N���[�h
#include <time.h>
#include <dsound.h>
#include <dmusicc.h>
#include <dmusici.h>
#include <windows.h>
#include <d3dx9.h>
#include <stdlib.h>

// �ł΂�
#include <stdio.h>
///////////////////////////////////////////////////////////////////////
// �萔��`
/*--- �P�Ȃ鐔�l�}�N���Ɨ� ---*/
#define PI 3.14159265358979323846264 // �~����

enum{
	MOVETIMER=101,// �ړ��^�C�}�h�c
	STMINTIMER,   // �X�^�~�i�^�C�}�h�c
	ITEMTIMER,    // �A�C�e���^�C�}
	TRAPTIMER,    // �g���b�v�^�C�}
	BLASTTIMER    // �����^�C�}�h�c
};
enum{
	FREEALL,    // �������S���J��
	FREETHING,  // ��Q���������J��
	FREERELEASE // �����[�X�ȊO�J��
};
#define SELRETURN 0x0000 // �߂�
#define SELENTER  0xffff // ����

#define ATACK_HIT 3  // �W�����v�t���O�U����
#define RAKKA 2      // �W�����v�t���O������
#define JEND 4       // �W�����v�I��
#define JFLOAT 5
#define JSTOP 4      // �W�����v��̒�~����
// �I�u�W�F�N�g���
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
// �_���[�W�^�C�v
enum{
	DAGEDMG=1,
	JUMPDMG,
	WANADMG,
	SHOTDMG,
	DOKUDMG,
	BLASTDMG,
};
// �Q�[�����
enum{
	STARTWINDOW,
	CHARASELECTWINDOW,
	STAGESELECTWINDOW,
	BATTLEWINDOW,
	MENUWINDOW,
	RESULTWINDOW,
	GOMOKUWINDOW
};
// �A�C�e�����
#define WEPON 1
#define SUBITEM 2
// �A�C�e��ID
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
// �A�C�e������
#define BAKURETSU_2    100

#define LOOKRIGHT    1
#define LOOKLEFT    -1
#define PITCHUP   -1
#define PITCHDOWN  1

// sound�A�C�f�B�[
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
// DirectSound�֘A�萔
#define	kPrimaryChannels 2     // �X�e���I�ɂ������̂�2�`���l��
#define	kPrimaryFreq     44100 // ���g���iHz�P�ʁj
#define	kPrimaryBitRate  16    // 16bit

#define	kNUM_OF_SE_BUFFERS	4

#define RRBTN 1
#define RDBTN 2
#define RLBTN 3
#define RUBTN 4
// �Q�[�����[�h
#define ROYALE_MODE 1
#define TEAM_MODE 2
#define GOMOKU_MODE 3
// ���C����
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
/*--- �Q�[���o�����X�Ɋւ���ݒ� ---*/
#define TIMERINTERVAL_MOV 40 // �ړ��^�C�}�Ԋu
#define TIMERINTERVAL_ST  50 // �X�^�~�i�^�C�}�Ԋu
#define TIMERINTERVAL_ITM 40 // �A�C�e�����ʊԊu
#define TIMERINTERVAL_TRP 100// �g���b�v�^�C�}�Ԋu
#define TIMERINTERVAL_BLS 60 // �����^�C�}�Ԋu

#define DUSHST 3    // �_�b�V���ŏ����X�^�~�i
#define JUMPST 30   // �W�����v�ŏ����X�^�~�i
#define DAGEST 40   // �Ō��U���ŏ����X�^�~�i

#define DSTOP 4     // �Ō��U����̒�~����
#define WANASTOP 20 // 㩂ɂ������Ē�~���鎞��

#define HIT_DIST 1.5    // �����蔻�苗��
#define BLUR_DIST 15.0  // �����鋗��

#define NIKUKAIFUKU 50  // ���ŉ񕜂����

#define FIRST_A 0.2f  // �����x
#define FIRST_G 0.02f // �d��
#define MAX_G   0.48f  // �ő嗎�����x
// �L�����ړ��ƃJ�����ړ����x
#define CHAR_MOVE 1500.0
#define CAMERA_MOVE 2000.0
#define CHAR_KAITEN 2000.0
// �A�C�e������
#define UP_SPD    1.0f // ���[���u���[�h�ŏオ��ړ����x
#define UP_TURN   0.5f // ���[���u���[�h�ŏオ����񑬓x
#define DOWN_SPD  0.5f // �Q�^�ŉ�����ړ����x
#define DOWN_TURN 0.5f // �Q�^�ŉ�������񑬓x
#define UP_JUMP   0.5f // �A�C�e���ł�����W�����v��
#define UP_ATK    100  // �A�C�e���ł�����U����
#define UP_DEF    100  // �A�C�e���ł�����h���

#define STAGEMOVEDIST 15 // �X�e�[�W�I���A�C�R���ړ����x
#define DMGBARLOST 3     // �_���[�W�o�[������
#define VIBTIMEMAX 30    // �U���ő�p������

#define MAXSPEED 3.0f // �ő呬�x

#define CAMERAPITCHMAX 1.7f // �J�����㉺�����̏��

#define STOPMAX 20

#define BAKURETSUMAX 50

#define CPUCENSER 10.0f  // CPU���L���������鋗��

#define MAXVECY 100 // �ő嗎��y���W

#define FLOATMAX 0.08f // ���V���̓����ő�
#define FLOATVALUECHANGE 0.03f
#define FLOATMOVEMIN 0.001f

#define MOUNT_INTER 10 // �ΎR�p�x
///////////////////////////////////////////////////////////////////////
/*--- �J���ɂ�萔�l���ς���` ---*/
#define SYOUGAISUU 15      // ��Q���ݒu��

#define ITEMMAX 4       // �����A�C�e���ő吔
#define STAGEITEMMAX 50 // �X�e�[�W�ݒu�\�A�C�e���ő吔
#define BULLETMAX 100   // �ړ����̒e�̍ő吔

#define ITEMCOUNT   26 // �f�[�^�o�^�A�C�e����
#define TAMAFILEMAX 12 // �e�̂w�t�@�C����+1

#define STAGECNT 10  // �X�e�[�W��

#define SOUNDFILEMAX (50+1) // ���ʉ���+1
#define kNUM_OF_BGM  (4+1) // BGM��+1

#define SUBXCNT 8 // ����g�̏p

#define BLASTMAX 100 // �����̍ő吔
///////////////////////////////////////////////////////////////////////
/*--- �֐��I�}�N�� ---*/
// �I�u�W�F�N�gp�̃������J��
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = NULL; } } 

// �W���C�X�e�B�b�N�̃{�^����������Ă��邩
// �v���C���[ n �Ԃ̃{�^����������Ă����TRUE
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
// �W���C�X�e�B�b�N�������Ă邱�Ƃɂ���B
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
// �W���C�X�e�B�b�N�������ĂȂ�
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
// 2�����`��p�t�@�C���ǂݍ���
#define TextureFromFile(fname,padd) D3DXCreateTextureFromFileEx(pDevice,fname,0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_DEFAULT,0xff000000,NULL,NULL,padd)
// �ő�A�ŏ����Ɏ��߂�
#define LimitsMaxMin(a,min,max) a=(max<a)?max:(min>a)?min:a
///////////////////////////////////////////////////////////////////////
/*--- �f�U�C���֘A ---*/
// �l���I���{�b�N�X
#define NINZU_X 550
#define NINZU_Y 300
#define NINZU_K 75  // �{�b�N�X�Ԋu
#define NINZU_W 150 // �{�b�N�X����
#define NINZU_H 50  // �{�b�N�X����
// �L�����I�����
#define CHAR_X  125
#define CHAR_K  140
#define CHAR_Y1 360 // 1�i��
#define CHAR_Y2 480 // 2�i��
#define CHAR_H  100
#define CHAR_W  100
// �I���ς݃L�����N�^�\���ʒu
#define SELCHAR_X 20
#define SELCHAR_K 200
#define SELCHAR_Y 20.0f
#define SELCHAR_W 80
#define SELCHAR_H 80
// �\�̓o�[
#define SELCHARBAR_X (SELCHAR_X+30)
#define SELCHARBAR_K 25 // Y���W
#define SELCHARBAR_Y (SELCHAR_X+SELCHAR_H+10)
#define NBAR_H 10
#define NBAR_W 100
// �\�̓w�b�_�[
#define NHEADBAR_X 20
#define NHEADBAR_Y (SELCHARBAR_Y-6)
// �X�e�[�W�I�����
#define STAGE_X 50
#define STAGE_K 150
#define STAGE_Y 300
#define STAGE_W 100
#define STAGE_H 100
#define STAGERAND_Y 450.0f
#define STAGERAND_X 290.0f
// �߂�{�^��
#define RETURN_X 670.0f
#define RETURN_Y 500.0f
#define RETURN_W 100
#define RETURN_H 50
// ����{�^��
#define ENTER_X 670.0f
#define ENTER_Y 425.0f
#define ENTER_W 100
#define ENTER_H 50
// ���j���[�E�B���h�E
#define MENU_X 100
#define MENU_Y 200
#define MENU_K 50
#define MENU_H 250
#define MENU_W 200
// �I���ς݃X�e�[�W�摜�\���ʒu
#define SELSTAGE_X 75
#define SELSTAGE_Y 50
// �Ə��ʒu
// �Ə��摜�T�C�Y
#define PINTWIDTH 39
#define PINTHEIGHT 39
#define PITX_2   400  // 2�v���CX
#define PITY_1_1 300  // 1�v���C1�R��Y
#define PITY_2_1 150  // 2�v���C1�R��Y
#define PITY_2_2 450  // 2�v���C2�R��Y
#define PITX_34_13 200 // 3,4�v���C1,3�R��X
#define PITX_34_24 600 // 3,4�v���C2,4�R��X
#define PITY_34_12 150 // 3,4�v���C1,2�R��Y
#define PITY_34_34 450 // 3,4�v���C3,4�R��Y
// HP�o�[
#define HPBARX_2     40.0f  // 2�v���CX
#define HPBARY_2_1   16.0f  // 2�v���C1�R��Y
#define HPBARY_2_2   316.0f // 2�v���C2�R��Y
#define HPBARX_34_13 40.0f  // 3,4�v���C1,3�R��X
#define HPBARX_34_24 640.0f // 3,4�v���C2,4�R��X
#define HPBARY_34_12 16.0f  // 3,4�v���C1,2�R��Y
#define HPBARY_34_34 316.0f // 3,4�v���C3,4�R��Y
// MP�o�[
#define MPBARX_2     40.0f  // 2�v���CX
#define MPBARY_2_1   38.0f  // 2�v���C1�R��Y
#define MPBARY_2_2   338.0f // 2�v���C2�R��Y
#define MPBARX_34_13 40.0f  // 3,4�v���C1,3�R��X
#define MPBARX_34_24 640.0f // 3,4�v���C2,4�R��X
#define MPBARY_34_12 38.0f  // 3,4�v���C1,2�R��Y
#define MPBARY_34_34 338.0f // 3,4�v���C3,4�R��Y
// MP�o�[
#define RLBARX_2     40.0f  // 2�v���CX
#define RLBARY_2_1   81.0f  // 2�v���C1�R��Y
#define RLBARY_2_2   381.0f // 2�v���C2�R��Y
#define RLBARX_34_13 40.0f  // 3,4�v���C1,3�R��X
#define RLBARX_34_24 640.0f // 3,4�v���C2,4�R��X
#define RLBARY_34_12 81.0f  // 3,4�v���C1,2�R��Y
#define RLBARY_34_34 381.0f // 3,4�v���C3,4�R��Y
// �o�[�T�C�Y
#define BARHEIGHT 10    // �o�[����
#define HSDBARWIDTH 150 // HP,ST,dmg�o�[����
#define RLBARWIDTH 100  // �����[�h�o�[����
// ���S���S
#define SIBOUX_2 300.0f
#define SIBOUY_2_1 110.0f
#define SIBOUY_2_2 450.0f
#define SIBOUX_34_13 100.0f
#define SIBOUX_34_24 500.0f
#define SIBOUY_34_12 100.0f
#define SIBOUY_34_34 400.0f
#define SIBOUW 200
#define SIBOUH 100
// ���摜
#define LEFT_X 200
#define LEFT_Y 450
#define RIGHT_X 400
#define RIGHT_Y 450
#define LEFTRIGHT_W 80
#define LEFTRIGHT_H 100
// �A�C�e���{�b�N�X
#define ITEMBOXW 39
#define ITEMBOXH 39
// �Q�[�����[�h
#define MODE_W 50
#define MODE_H 50
#define MODE_K 100
// �`�[���F
#define TCOL_X 45
#define TCOL_K 60
#define TCOL_H 40
#define TCOL_W 40
// �E�B���h�E�T�C�Y
#define MEWIDTH 800     // ������ʉ���
#define MEHEIGHT 600    // ������ʍ���
// �X�N���[���ʒu�擾
#define WINDOW_X ((GetSystemMetrics( SM_CXSCREEN ) - MEWIDTH ) / 2)
#define WINDOW_Y ((GetSystemMetrics( SM_CYSCREEN ) - MEHEIGHT ) / 2)

// ���[�_�[�A�C�R���T�C�Y
#define RDCHARWIDTH 11
#define RDCHARHEIGHT 16
// ���[�_�[�A�C�e���ꏊ�T�C�Y
#define ITEMPTWIDTH 10
#define ITEMPTHEIGHT 10
// ���[�_�[�e�ꏊ�T�C�Y
#define BULLETPTWIDTH 5
#define BULLETPTHEIGHT 5
///////////////////////////////////////////////////////////////////////
#include "Structure.h"
//�֐��v���g�^�C�v/////////////////////////////////////
// MainProgram.cpp
LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL InitApp(HWND hwnd, HINSTANCE hInst);	//�A�v���P�[�V�����̏���������
VOID RenderString(LPSTR ,INT,INT);
VOID FreeDx(void);     // �I�u�W�F�N�g�̊J��
int FileRead(void);
// D3D.h
HRESULT InitD3d(HWND);
VOID Render(); //�`�悷��̂Ɏg��
VOID RenderThingBlur(THING* pThing, int lp, int show, MESHSTRUCT *lpMesh);
VOID SendView(VIEW4 vw, int player, int w1, int w2, int h1, int h2, HWND hWnd); // �r���[�s��
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
// �O���[�o���ϐ��錾 ///////////////////////////////
// Direct3D
LPDIRECT3D9 pD3d;
LPDIRECT3DDEVICE9 pDevice; // Direct3D�f�o�C�X
D3DVIEWPORT9 g_VP;         // �r���[�|�[�g
// DirectInput
CDInput DInput;		    // DirectInput����N���X
DWORD g_dwFFBAxisAmt = 2; // �X�e�B�b�N�̂��肮��̐�
LPDIRECTINPUTEFFECT g_pEffect[4] = {NULL,NULL,NULL,NULL}; // FFB�Ŏg�p
// DirectMusic
IDirectMusicAudioPath8*   g_pDMAudioPath = NULL;
IDirectMusicLoader8*      g_pDMLoader = NULL;
IDirectMusicPerformance8* g_pDMPerformance = NULL;
LPDIRECTSOUND8 g_pDirectSound = NULL; // DirectSound�I�u�W�F�N�g
bool g_bComInit = FALSE;
const TCHAR* kMusicPath = TEXT("./sound/");   //music�t�H���_
const TCHAR* kSoundsPath = TEXT("./sound/"); //sounds�t�H���_
const int kSoundsPathLength	= lstrlen(kSoundsPath);
const int kMusicPathLength	= lstrlen(kMusicPath);

int DrawingMode=NULL;
int Ninzu, cpuNinzu, gNinzu;    // �v���C�l��
int Stage;    // ���ݎg�p���̃X�e�[�W
int chselcnt; // �L��������l��
int GameMode=ROYALE_MODE;
int bEnd=FALSE;
int TeamCnt[5],TeamNowCnt[5],TeamKazu; // �`�[���l��
int FullScreen=FALSE, VibMode=TRUE;

float g_aspect = MEWIDTH/MEHEIGHT;    // �T�C�Y�䗦
float width=MEWIDTH, height=MEHEIGHT; // ���݂̉�ʃT�C�Y

int StageMove=0; // �X�e�[�W�I���A�C�R���ړ���
float maxN[8];   // �ő�\��
int StageItemMax;
int Syougaisu, TimerFlg;
int SoundVol, MusicVol; // ����
int AliveCnt, WinTeam;
float MaxtSpd;

int Goban[19][19], putTurn, putCnt, goWin;

LPD3DXFONT pFont = NULL;     // �����t�H���g
LPDIRECT3DTEXTURE9 pBar;     // 2D�`�悷���ʘg
LPDIRECT3DTEXTURE9 pChar[5]; // �}�b�v�L����
LPDIRECT3DTEXTURE9 pItemBoxW, pItemBoxI, pItemBoxYellow, pResultBox; // �A�C�e���{�b�N�X
LPDIRECT3DTEXTURE9 pItemIcon[ITEMCOUNT+1];  // �A�C�e���A�C�R��
LPDIRECT3DTEXTURE9 pPint;    // �Ə�
LPDIRECT3DTEXTURE9 pLeft, pRight; // ���
LPDIRECT3DTEXTURE9 pHpBar, pHpBarDmg, pHpBarRec, pStBar, pRlBar, pnBar;
LPDIRECT3DTEXTURE9 pSelnin[5], pSelchar[9], pSelstage[STAGECNT], pSelcharX[9], pTeamCol[5], pTeamWaku[5];
LPDIRECT3DTEXTURE9 pReturn, pEnter, pStartBox, pSibou, pnHead, pCpu, pStageR;
LPDIRECT3DTEXTURE9 pBackimg, pGolog, pBackStage, pItemPt1, pItemPt2, pBulletPt;
LPDIRECT3DTEXTURE9 pPointer[5], pIsi[6]; // �|�C���^
LPD3DXSPRITE pSprite;           // 2D�`��̃L�����p�X

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
// �f�o�O
char debug1[512];
char debug2[512];
char debug3[512];
int battleFlg, KeyChar=1;
int KeyMode;    // �L�[�{�[�h���[�h

#endif