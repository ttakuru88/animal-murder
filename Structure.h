// �\����
struct BBOX{
	D3DXVECTOR3 vecMax;
	D3DXVECTOR3 vecMin;
	D3DXVECTOR3 vecAxisX;
	D3DXVECTOR3 vecAxisY;
	D3DXVECTOR3 vecAxisZ;
	FLOAT fLengthX;
	FLOAT fLengthY;
	FLOAT fLengthZ;
	BBOX()
	{
		ZeroMemory(this,sizeof(BBOX));
		vecAxisX=D3DXVECTOR3(1,0,0);
		vecAxisY=D3DXVECTOR3(0,1,0);
		vecAxisZ=D3DXVECTOR3(0,0,1);
	}
};
// �o�E���f�B���O�X�t�B�A
struct SPHERE{
	D3DXVECTOR3 vecCenter;
	FLOAT fRadius;
};
//�I�u�W�F�N�g�̗l�X�ȗv�f��錾����\����
typedef struct{
	LPD3DXMESH pMesh;             //���b�V��
	D3DMATERIAL9* Materials;      //���b�V���̃}�e���A��
	LPDIRECT3DTEXTURE9* Textures; //�e�N�X�`��
	DWORD dwNumMaterials;				//���i�̐�
}MESHSTRUCT;
struct THING{
	MESHSTRUCT Mesh;
	int tag;
	float ftag;
	BOOL Visible;
	int type;
	
	BBOX BBox;
	SPHERE Sphere;
	D3DXMATRIX matYaw;
	D3DXMATRIX matPitch;
	D3DXMATRIX matRotation;				//�I�u�W�F�N�g�̌���
	D3DXMATRIX matPosition;
	D3DXVECTOR3 vecPosition;			//�I�u�W�F�N�g�̈ʒu
	FLOAT fYaw;
	FLOAT fPitch;
	FLOAT fScale;
	THING()
	{
		ZeroMemory(this,sizeof(THING));//������
		D3DXMatrixIdentity(&matRotation);
		fScale=1;
	}
};

struct CAMERA{
	FLOAT X;
	FLOAT Y;
	FLOAT Z;
	FLOAT Yaw;
	FLOAT Pitch;
	FLOAT Roll;
	D3DXVECTOR3 vecEyePt; //�J�����i���_�j�ʒu
	D3DXVECTOR3 vecUp; // �J�����������
	D3DXVECTOR3 vecLookatPt;
	int left;
	int right;
	CAMERA()
	{
		ZeroMemory(this,sizeof(CAMERA));//������
		vecUp = D3DXVECTOR3(0,1,0);
	}
};
// �L�����N�^�[�\�� ////////////////////
typedef struct{
	char dAtack[64];
	int sdAtack;
	int maxhp;
	int nStmin;
	int nAtack;
	int nGard;
	float nJump;
	float nSpeed;
	float nDash;
	float nTurn;
	float dY;
	float dX;
}CHARA_STATE;
//                                                         HP �X�^ �U�� �h��  ����  �ړ�  �v��  ����   dY      dX
CHARA_STATE ChDat[]={{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
                     { "./X/atack/�F�p.x",     SD_ATACK1, 420,150,  80 ,  20, 0.9f, 0.9f, 1.5f, 0.8f, 0.05f, 0.25f}, // ����
                     { "./X/atack/�Ō�.x",     SD_ATACK2, 380,230,  40 ,  10, 1.0f, 1.4f, 2.4f, 1.5f, 0.05f, 0.3f},  // �˂���
					 { "./X/atack/��ڍU��.x", SD_ATACK3, 390,180,  90 ,  30, 1.2f, 0.8f, 2.6f, 1.3f, 0.1f , 0.25f}, // ���
					 { "./X/atack/��.x",       SD_ATACK4, 240,200,  60 ,  17, 1.1f, 1.1f, 1.6f, 1.0f, 0.1f , 0.2f},  // ����
					 { "./X/atack/�����΂�.x", SD_ATACK5, 410,150,  60 ,  20, 1.1f, 0.9f, 1.7f, 3.0f, 0.25f, 0.15f}, // �؂񂬂�
					 { "./X/atack/���.x",   SD_ATACK1, 500,250, 100 ,  40, 0.8f, 0.9f, 1.3f, 0.4f, 0.2f , 0.5f},  // ����
					 { "./X/atack/��.x",       SD_ATACK1, 400,220,  60 ,  20, 1.2f, 1.2f, 2.0f, 0.8f, 0.05f, 0.5f},  // ��イ
                     { "./X/atack/��.x",       SD_ATACK1, 200,150,  50 ,  20, 1.2f, 1.3f, 2.0f, 2.0f, 0.02f, 0.4f}}; // ���T�p��
char CharXDir[32]="./X/chara/";
char SubX[][SUBXCNT][124]={{"\0"},
//                           0           1                2               3              4           5             6               7
                           {"�F.x", "�F_�o�Y�[�J.x", "�F_�����e.x", "�F_�T�[�x��.x", "�F_���e.x", "�F_�n��.x", "�F_���].x", "�F_���ԍ�.x"},
                           {"�l.x", "�l_�o�Y�[�J.x", "�l_�����e.x", "�l_�T�[�x��.x", "�l_���e.x", "�l_�n��.x", "�l_���].x", "�l_���ԍ�.x"},
                           {"�@.x", "�@_�o�Y�[�J.x", "�@_�����e.x", "�@_�T�[�x��.x", "�@_���e.x", "�@_�n��.x", "�@_���].x", "�@_���ԍ�.x"},
                           {"��.x", "��_�o�Y�[�J.x", "��_�����e.x", "��_�T�[�x��.x", "��_���e.x", "��_�n��.x", "��_���].x", "��_���ԍ�.x"},
                           {"��.x", "��_�o�Y�[�J.x", "��_�����e.x", "��_�T�[�x��.x", "��_���e.x", "��_�n��.x", "��_���].x", "��_���ԍ�.x"},
                           {"��.x", "��_�o�Y�[�J.x", "��_�����e.x", "��_�T�[�x��.x", "��_���e.x", "��_�n��.x", "��.x",        "��.x"},
                           {"��.x", "��.x",          "��.x",        "��_�T�[�x��.x", "��_���e.x", "��_�n��.x", "��.x",        "��.x"},
                           {"�K.x", "�K.x",          "�K.x",        "�K_�T�[�x��.x", "�K_���e.x", "�K_�n��.x", "�K.x",        "�K.x"}};
typedef struct{
	int num;
	int maxhp, hp;
	int maxst, st;
	BOOL alive;
	THING obj[SUBXCNT];    // �L�����I�u�W�F�N�g�i�[
	THING Dageki; // �Ō��f�[�^�i�[
	CAMERA Camera;// �J������� Structure.h
	int DageTime; // �Ō��ێ��J�E���^
	int Stop;     // �����~�J�E���^
	int JpFlg;    // �W�����v����̃t���O
	float SpdUp, TurnUp, JumpUp;
	int AtkUp, DefUp;
	float a;      // ���ݑ��x
	float g, gs;  // �d��
	float zoom;
	float Mfloat;
	int Ffloat, Visible;
	int dmg;      // �H����Ă�_���[�W
	int SelItem;  // �I�𒆃A�C�e��
	int IconFlg, IconNum;
	int cpuIcon[4];
	int cpu;
	int NowX;     // ���݂�X�B����0
	int Xcnt;     // Xfile��
	int LockOnFlg, LockOnNum;
	int Target;
	int Team, rank;
	int collision;
	THING Iconobj;
	THING LockOnObj;
	struct {
		int num;
		int Ptnum;
		int Timer;
		int rlTimer;
		int maxtama, tama;
		int rlCnt;
	}item[ITEMMAX];
}PLAYERCHARASTATE;
PLAYERCHARASTATE Ch[5];
PLAYERCHARASTATE *Chpt[5];
// �W���C�X�e�B�b�N�\����
typedef struct{
	int LX;   // ���X�e�B�b�N�w���W
	int LY;   // ���X�e�B�b�N�x���W
	int RX;   // �E�X�e�B�b�N�w���W
	int RY;   // �E�X�e�B�b�N�x���W
	WORD But; // �W���C�X�e�B�b�N�{�^�����
	// �{�^���t���O
	int r1Flg, r2Flg, r3Flg;
	int l1Flg, l2Flg, l3Flg;
	int startFlg, selectFlg;
	int rrFlg, ruFlg, rlFlg, rdFlg;
	// �U���f�[�^
	int VibTime;
	int VibFlg;
	int VibX, VibY;
	int x, y;
}JOYSTATES;
JOYSTATES Joy[5];
// �A�C�e�����\����
typedef struct{
	int type;
	char fname[64];
	int tnum;
	int atk;      // �U����
	int tama;     // �e��
	int rlCount;  // �����[�h��
	float tSpd;   // �e��
	int shTime;   // ���ˊԊu
	int rlTime;   // �����[�h����
	int Range;    // �˒�
	int shSnd;    // �V���b�g��
	int AppTime;  // �ďo������
	float gSpeed; // �������x
	float bMax;   // �����͈�
	float zoom;   // �g��@�\
	int ChX;
}ITEMDAT;
char ItemXDir[32]="./X/item/";
//                   type     fname               tnum atc tama rlC tSpd   shT  rlT Range sound   App  gSpd bMax zoom
ITEMDAT ItemDat[]={{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
              /*1*/{ WEPON,   "�ς���.x",         2,  50,   3,  3, 0.5f,  10, 60,  8, SD_SHOT3, 100, 0,      0,    0,   0},
                   { WEPON,   "�o�Y�[�J.x",         3, 130,   2,  2, 0.4f, 100,200, 15, SD_SHOT4, 200, 0,      1.0f, 2.5f,1},
                   { SUBITEM, "���[���[�u���[�h.x", 0,   0,   0,  0, 0.0f, 400,  0,  0, 0,        100, 0,      0,    1,   0},
                   { WEPON,   "\0"                , 1,  50, 995,999, 0.3f,  10,120, 12, SD_SHOT5,   0, 0,      0,    1,   0},
              /*5*/{ SUBITEM, "��.x"              , 0,   0,   0,  0, 0.0f,   0,  0,  0, 0,        300, 0,      0,    1,   0},
				   { SUBITEM, "����.x"            , 0,   0,   0,  0, 0.0f, 200,  0,  0, 0,         50, 0,      0,    1,   0},
                   { WEPON,   "�J���V�j�R�t.x",     1, 120,  20,  2, 0.6f,   8, 80, 40, SD_SHOT6, 150, 0,      0,    1,   0},
                   { WEPON,   "�V���b�g�K��.x",     4,  50,   1,  3, 0.4f,   0, 50, 33, SD_SHOT7, 120, 0,      0,    1,   0},
                   { WEPON,   "���].x",           4,  60,   2,  3, 0.2f,  25, 50, 35, SD_SHOT8, 120, 0,      0,    1,   6},
             /*10*/{ WEPON,   "��֒e.x",           4, 200,   2,  2, 0.3f,  35,200, 15, SD_SHOT9, 120, 0.002f, 1.2f, 1,   0},
                   { WEPON,   "����.x",             4, 100,   1,  0, 0.1f,   0,250,  5, SD_SHOT10,420, 0,      0.5f, 1,   0},
                   { WEPON,   "�n��.x",             5, 130,   3,  2, 0.0f,  30, 60,999, SD_SHOT11,120, 0.01f,  0,    1,   5},
                   { WEPON,   "�ђ�.x",             6,  90,  12,  3, 0.2f,   5, 70, 10, SD_SHOT12,120, 0,      0,    1,   0},
                   { SUBITEM, "�W�����v�A�b�v.x",   0,   0,   0,  0, 0.0f, 400,  0,  0, 0        ,100, 0,      0,    1,   0},
             /*15*/{ SUBITEM, "�U���A�b�v.x",       0,   0,   0,  0, 0.0f, 400,  0,  0, 0        ,100, 0,      0,    1,   0},
                   { SUBITEM, "�h��A�b�v.x",       0,   0,   0,  0, 0.0f, 400,  0,  0, 0        ,100, 0,      0,    1,   0},
                   { WEPON,   "���ԍ�.x",           7,  80,  10,  3, 0.2f,  10, 70, 15, SD_SHOT13,120, 0,      0,    1,   7},
				   { WEPON,   "���e.x",             9,  60,   1,  3, 0.4f,  36,180, 40, SD_SHOT6, 150, 0.001f, 1.5f, 1,   4},
				   { WEPON,   "�����e.x",           8,  30,  25,  3, 1.2f,   3,100,  8, SD_SHOT6, 150, 0,      0,    1,   2},
			 /*20*/{ WEPON,   "�X�i.x",             8, 200,   5,  1, 2.9f,  80,150, 50, SD_SHOT14,159, 0,      0,    8.0f,0},
				   { WEPON,   "�~�T�C�������`��.x",10,  90,   5,  2, 0.2f,  30, 40, 11, SD_SHOT6, 180, 0,      1.1f, 2.0f,0},
                   { SUBITEM, "�~���[.x",           0,   0,   0,  0, 0.0f,1000,  0,  0, 0        ,120, 0,      0,    1,   0},
                   { SUBITEM, "��.x",               0,   0,   0,  0, 0.0f, 500,  0,  0, 0        ,180, 0,      0,    1,   0},
                   { SUBITEM, "�C���r�W.x",         0,   0,   0,  0, 0.0f, 500,  0,  0, 0        ,180, 0,      0,    1,   0},
		     /*25*/{ WEPON,   "���e.x",             9,  60,   1,  3, MAX_G, 36,180, 40, SD_SHOT6 ,150, 0.02f,  1.4f, 1,   0},
				   { WEPON, "�r�[���T�[�x��.x",    11, 100,   1,  3, 0.0f,  10,100,  1, SD_SHOT6 ,180, 0,      0,    1,   3}};
// �e�t�@�C��                   1        2              3              4          5       6          7         8           9          10           11
char BulletFile[][64]={"\0", "�e.x", "�p�`���R��.x", "�o�Y�[�J��.x", "���e.x", "�n��.x", "�Βe.x", "���e.x","�����e�e.x","���e.x","�~�T�C��.x","���̋O��.x"};
THING BulletObj[TAMAFILEMAX];
// ���ʉ��t�@�C����
char SoundFile[][64]={"\0",        "shot1.wav", "shot2.wav", "shot3.wav", "shot4.wav", "shot5.wav", "shot6.wav", "shot7.wav", "shot8.wav", "shot9.wav",
                      "shot10.wav","shot11.wav","shot12.wav","shot13.wav","shot14.wav","shot15.wav","atack1.wav","atack2.wav","atack3.wav","atack4.wav",
					  "atack5.wav","click1.wav","click2.wav","death.wav", "dog.wav",   "hit1.wav",  "hit2.wav",  "hit3.wav",  "jump.wav",  "rl.wav",
					  "icon.wav", "start.wav", "water.wav", "itemuse.wav","itemget.wav","menu.wav","move.wav",  "dmg.wav",   "enter.wav", "return.wav",
					  "shot16.wav","shot17.wav","shot18.wav","Explosion1.wav","Explosion2.wav","Explosion3.wav", "shot19.wav","shot20.wav", "shot21.wav",
                      "jump2.wav", "warp.wav"};
// BGM�t�@�C����
char MusicFile[][64]={"\0", "op.mid", "op2.mid","op3.mid","dasaku.mid"};
// �X�e�[�W���
typedef struct{
	THING obj;
	THING trap[SYOUGAISUU]; // 㩃I�u�W�F�N�g�i�[
	// �A�C�e��
	struct ITEM{
		int num;
		int AppTimer;
		THING obj;
	}item[STAGEITEMMAX];
}STAGEDAT;
STAGEDAT StageDat;
// �ړ����̒e���
typedef struct{
	int num;
	int cnt;
	int tag;
	float a,g,gs; // ��������
	int Target;
	int mflg;
	THING obj;
}MOVINGBULLET;
MOVINGBULLET Bullet[5][BULLETMAX];
//�������i�ʒu�A�傫�����܂�
struct EXTENSIONBLAST{
	int num;
	FLOAT ScaleUp;
	THING obj;
	EXTENSIONBLAST(){
		ScaleUp = 1;
	}
};
EXTENSIONBLAST Blast[5][BLASTMAX];
//�����p�ϐ�
char BlastFile[64]={"./X/bom/����.x"};
THING BlastObj;

// �I���X�e�[�W���
typedef struct{
	char X[256];
	char img[256];
}STAGEFILE;
STAGEFILE StageFile[STAGECNT]={{"./X/field/�����.x", "./pic/Scr1.jpg"},
                               {"./X/field/����.x",   "./pic/Scr2.jpg"},
                               {"./X/field/�C.x",     "./pic/Scr3.jpg"},
                               {"./X/field/����.x",   "./pic/Scr4.jpg"},
                               {"./X/field/���~.x",   "./pic/Scr5.jpg"},
                               {"./X/field/�H�H�H.x", "./pic/Scr6.jpg"},
                               {"./X/field/�܊p.x",   "./pic/Scr7.jpg"},
                               {"./X/field/���[�v.x", "./pic/Scr8.jpg"},
                               {"./X/field/�Ȃɂ�.x", "./pic/Scr9.jpg"},
                               {"./X/field/����.x",   "./pic/Scr10.jpg"}};

D3DXVECTOR3 StartPt[STAGECNT][4] = 	{{D3DXVECTOR3(-7.6f, 1.0f, -6.5f), D3DXVECTOR3(-7.6f, 1.0f, -6.5f)/*D3DXVECTOR3(9.2f, 1.0f, -4.7f)*/,  D3DXVECTOR3(6.0f, 1.0f, 8.5f),  D3DXVECTOR3(-7.7f, 1.0f, 8.0f)},
	                                 {D3DXVECTOR3(7.2f, 1.0f, -7.2f),  D3DXVECTOR3(-7.2f, 1.0f, -7.2f), D3DXVECTOR3(-7.2f, 1.0f, 7.2f), D3DXVECTOR3(7.2f, 1.0f, 7.2f)},
	                                 {D3DXVECTOR3(4.0f, 0.5f, -3.7f),  D3DXVECTOR3(-6.4f, 0.5f, -6.4f), D3DXVECTOR3(-3.2f, 0.5f, 2.8f), D3DXVECTOR3(-0.2f, 0.5f, 6.3f)},
	                                 {D3DXVECTOR3(-5.0f, 2.5f, -5.0f), D3DXVECTOR3(-5.5f, 3.0f, 5.8f),  D3DXVECTOR3(9.3f, 3.0f, 3.1f),  D3DXVECTOR3(3.6f, 5.0f, -7.2f)},
	                                 {D3DXVECTOR3(-3.0f, 1.0f, 0.0f),  D3DXVECTOR3(-3.0f, 1.0f, -7.3f), D3DXVECTOR3(-4.4f, 1.0f, 7.2f), D3DXVECTOR3(7.2f, 0, 0)},
	                            /*5*/{D3DXVECTOR3(9.0f, 3.0f, 6.0f),   D3DXVECTOR3(-5.5f, 5.0f, 11.5f), D3DXVECTOR3(-4.8f, 7.03f, 2.3f),D3DXVECTOR3(1.0f, 4.3f, -2.2f)},
	                                 {D3DXVECTOR3(18.3f, 1.0f, -18.3f),D3DXVECTOR3(-18.3f, 1.0f,-18.3f),D3DXVECTOR3(18.3f, 1.0f, 18.3f),D3DXVECTOR3(-18.3f, 1.0f, -18.3f)},
	                                 {D3DXVECTOR3(1.3f, 1.0f, -1.3f),  D3DXVECTOR3(-8.3f, 1.0f,-8.3f),  D3DXVECTOR3(8.3f, 1.0f, 1.3f),  D3DXVECTOR3(-8.3f, 1.0f, -1.3f)},
	                                 {D3DXVECTOR3(1.3f, 1.0f, -1.3f),  D3DXVECTOR3(-8.3f, 1.0f,-8.3f),  D3DXVECTOR3(8.3f, 1.0f, 1.3f),  D3DXVECTOR3(-8.3f, 1.0f, -1.3f)},
	                                 {D3DXVECTOR3(7.3f, 9.0f, 7.3f), D3DXVECTOR3(-7.3f, 9.0f,-7.3f),  D3DXVECTOR3(7.3f, 9.0f, -7.3f),  D3DXVECTOR3(-7.3f, 9.0f, 7.3f)}};
// �S�����񋓌^
enum VIEW4{
	LEFT_UP=1,  // 1P
	RIGHT_UP,   // 2P
	LEFT_DOWN,  // 3P
	RIGHT_DOWN, // 4P
	D2D_DRAW,   // 2D�`��
	D2D_SEL,    // �I�����
};
// BGM�f�[�^
typedef struct{
	IDirectMusicSegment8*	pMusSegment;		// �Z�O�����g
	IDirectMusicAudioPath8*	pMusAudioPath;		// �I�[�f�B�I�p�X
	BOOL bDownLoaded; // �_�E�����[�h�ς݂��ǂ���
}theMusic;
theMusic g_BGM[kNUM_OF_BGM]; // BGM�̐�����

// ���ʉ��f�[�^
typedef struct{
	WAVEFORMATEX sndWaveFormatEx;	// �g�`�f�[�^���
	HMMIO    sndHmmio;        // �g�`�f�[�^��mmio�ւ̃n���h��
	MMCKINFO sndChunk;        // data�`�����N�̏��
	MMCKINFO sndChunkRiff;    // �g�`�t�@�C�����J���Ƃ��Ɏg��
	DWORD    sndCreationFlags;// �����t���O
	DWORD    sndNumOfBuffers; // �o�b�t�@�̐�

	LPDIRECTSOUND3DBUFFER* sndDS3DSBuffer; // 3D�o�b�t�@�ւ̃|�C���^�ƃp�����[�^
	DS3DBUFFER*            sndDS3DSBufferParams;

	LPDIRECTSOUNDBUFFER*   sndDSSoundBuffer; // �o�b�t�@�ւ̃|�C���^
}theSounds;
theSounds g_SE[SOUNDFILEMAX];

// �A�C�R��
char IconFile[][64]={{"./X/icon/�т�����1.x"},
                     {"./X/icon/�т�����2.x"},
                     {"./X/icon/���.x"},
				     {"./X/icon/�{��.x"}};
THING IconObj[4];
char LockOnFile[64]={"./X/Site/���b�N�I��.x"};
THING LockOnObj;