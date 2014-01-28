// 構造体
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
// バウンディングスフィア
struct SPHERE{
	D3DXVECTOR3 vecCenter;
	FLOAT fRadius;
};
//オブジェクトの様々な要素を宣言する構造体
typedef struct{
	LPD3DXMESH pMesh;             //メッシュ
	D3DMATERIAL9* Materials;      //メッシュのマテリアル
	LPDIRECT3DTEXTURE9* Textures; //テクスチャ
	DWORD dwNumMaterials;				//部品の数
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
	D3DXMATRIX matRotation;				//オブジェクトの向き
	D3DXMATRIX matPosition;
	D3DXVECTOR3 vecPosition;			//オブジェクトの位置
	FLOAT fYaw;
	FLOAT fPitch;
	FLOAT fScale;
	THING()
	{
		ZeroMemory(this,sizeof(THING));//初期化
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
	D3DXVECTOR3 vecEyePt; //カメラ（視点）位置
	D3DXVECTOR3 vecUp; // カメラ上方向き
	D3DXVECTOR3 vecLookatPt;
	int left;
	int right;
	CAMERA()
	{
		ZeroMemory(this,sizeof(CAMERA));//初期化
		vecUp = D3DXVECTOR3(0,1,0);
	}
};
// キャラクター能力 ////////////////////
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
//                                                         HP スタ 攻撃 防御  跳躍  移動  迅速  旋回   dY      dX
CHARA_STATE ChDat[]={{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
                     { "./X/atack/熊用.x",     SD_ATACK1, 420,150,  80 ,  20, 0.9f, 0.9f, 1.5f, 0.8f, 0.05f, 0.25f}, // くま
                     { "./X/atack/打撃.x",     SD_ATACK2, 380,230,  40 ,  10, 1.0f, 1.4f, 2.4f, 1.5f, 0.05f, 0.3f},  // ねずみ
					 { "./X/atack/ろぼ攻撃.x", SD_ATACK3, 390,180,  90 ,  30, 1.2f, 0.8f, 2.6f, 1.3f, 0.1f , 0.25f}, // ろぼ
					 { "./X/atack/牙.x",       SD_ATACK4, 240,200,  60 ,  17, 1.1f, 1.1f, 1.6f, 1.0f, 0.1f , 0.2f},  // いぬ
					 { "./X/atack/くちばし.x", SD_ATACK5, 410,150,  60 ,  20, 1.1f, 0.9f, 1.7f, 3.0f, 0.25f, 0.15f}, // ぺんぎん
					 { "./X/atack/りんご.x",   SD_ATACK1, 500,250, 100 ,  40, 0.8f, 0.9f, 1.3f, 0.4f, 0.2f , 0.5f},  // ぞう
					 { "./X/atack/炎.x",       SD_ATACK1, 400,220,  60 ,  20, 1.2f, 1.2f, 2.0f, 0.8f, 0.05f, 0.5f},  // りゅう
                     { "./X/atack/牙.x",       SD_ATACK1, 200,150,  50 ,  20, 1.2f, 1.3f, 2.0f, 2.0f, 0.02f, 0.4f}}; // レサパン
char CharXDir[32]="./X/chara/";
char SubX[][SUBXCNT][124]={{"\0"},
//                           0           1                2               3              4           5             6               7
                           {"熊.x", "熊_バズーカ.x", "熊_光線銃.x", "熊_サーベル.x", "熊_爆弾.x", "熊_地雷.x", "熊_一回転.x", "熊_時間差.x"},
                           {"鼠.x", "鼠_バズーカ.x", "鼠_光線銃.x", "鼠_サーベル.x", "鼠_爆弾.x", "鼠_地雷.x", "鼠_一回転.x", "鼠_時間差.x"},
                           {"機.x", "機_バズーカ.x", "機_光線銃.x", "機_サーベル.x", "機_爆弾.x", "機_地雷.x", "機_一回転.x", "機_時間差.x"},
                           {"犬.x", "犬_バズーカ.x", "犬_光線銃.x", "犬_サーベル.x", "犬_爆弾.x", "犬_地雷.x", "犬_一回転.x", "犬_時間差.x"},
                           {"鳥.x", "鳥_バズーカ.x", "鳥_光線銃.x", "鳥_サーベル.x", "鳥_爆弾.x", "鳥_地雷.x", "鳥_一回転.x", "鳥_時間差.x"},
                           {"象.x", "象_バズーカ.x", "象_光線銃.x", "象_サーベル.x", "象_爆弾.x", "象_地雷.x", "像.x",        "像.x"},
                           {"竜.x", "竜.x",          "竜.x",        "竜_サーベル.x", "竜_爆弾.x", "竜_地雷.x", "竜.x",        "竜.x"},
                           {"狸.x", "狸.x",          "狸.x",        "狸_サーベル.x", "狸_爆弾.x", "狸_地雷.x", "狸.x",        "狸.x"}};
typedef struct{
	int num;
	int maxhp, hp;
	int maxst, st;
	BOOL alive;
	THING obj[SUBXCNT];    // キャラオブジェクト格納
	THING Dageki; // 打撃データ格納
	CAMERA Camera;// カメラ情報 Structure.h
	int DageTime; // 打撃保持カウンタ
	int Stop;     // 動作停止カウンタ
	int JpFlg;    // ジャンプ判定のフラグ
	float SpdUp, TurnUp, JumpUp;
	int AtkUp, DefUp;
	float a;      // 現在速度
	float g, gs;  // 重力
	float zoom;
	float Mfloat;
	int Ffloat, Visible;
	int dmg;      // 食らってるダメージ
	int SelItem;  // 選択中アイテム
	int IconFlg, IconNum;
	int cpuIcon[4];
	int cpu;
	int NowX;     // 現在のX。初期0
	int Xcnt;     // Xfile数
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
// ジョイスティック構造体
typedef struct{
	int LX;   // 左スティックＸ座標
	int LY;   // 左スティックＹ座標
	int RX;   // 右スティックＸ座標
	int RY;   // 右スティックＹ座標
	WORD But; // ジョイスティックボタン情報
	// ボタンフラグ
	int r1Flg, r2Flg, r3Flg;
	int l1Flg, l2Flg, l3Flg;
	int startFlg, selectFlg;
	int rrFlg, ruFlg, rlFlg, rdFlg;
	// 振動データ
	int VibTime;
	int VibFlg;
	int VibX, VibY;
	int x, y;
}JOYSTATES;
JOYSTATES Joy[5];
// アイテム情報構造体
typedef struct{
	int type;
	char fname[64];
	int tnum;
	int atk;      // 攻撃力
	int tama;     // 弾数
	int rlCount;  // リロード数
	float tSpd;   // 弾速
	int shTime;   // 発射間隔
	int rlTime;   // リロード時間
	int Range;    // 射程
	int shSnd;    // ショット音
	int AppTime;  // 再出現時間
	float gSpeed; // 落下速度
	float bMax;   // 爆風範囲
	float zoom;   // 拡大機能
	int ChX;
}ITEMDAT;
char ItemXDir[32]="./X/item/";
//                   type     fname               tnum atc tama rlC tSpd   shT  rlT Range sound   App  gSpd bMax zoom
ITEMDAT ItemDat[]={{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
              /*1*/{ WEPON,   "ぱちんこ.x",         2,  50,   3,  3, 0.5f,  10, 60,  8, SD_SHOT3, 100, 0,      0,    0,   0},
                   { WEPON,   "バズーカ.x",         3, 130,   2,  2, 0.4f, 100,200, 15, SD_SHOT4, 200, 0,      1.0f, 2.5f,1},
                   { SUBITEM, "ローラーブレード.x", 0,   0,   0,  0, 0.0f, 400,  0,  0, 0,        100, 0,      0,    1,   0},
                   { WEPON,   "\0"                , 1,  50, 995,999, 0.3f,  10,120, 12, SD_SHOT5,   0, 0,      0,    1,   0},
              /*5*/{ SUBITEM, "肉.x"              , 0,   0,   0,  0, 0.0f,   0,  0,  0, 0,        300, 0,      0,    1,   0},
				   { SUBITEM, "下駄.x"            , 0,   0,   0,  0, 0.0f, 200,  0,  0, 0,         50, 0,      0,    1,   0},
                   { WEPON,   "カラシニコフ.x",     1, 120,  20,  2, 0.6f,   8, 80, 40, SD_SHOT6, 150, 0,      0,    1,   0},
                   { WEPON,   "ショットガン.x",     4,  50,   1,  3, 0.4f,   0, 50, 33, SD_SHOT7, 120, 0,      0,    1,   0},
                   { WEPON,   "一回転.x",           4,  60,   2,  3, 0.2f,  25, 50, 35, SD_SHOT8, 120, 0,      0,    1,   6},
             /*10*/{ WEPON,   "手榴弾.x",           4, 200,   2,  2, 0.3f,  35,200, 15, SD_SHOT9, 120, 0.002f, 1.2f, 1,   0},
                   { WEPON,   "爆裂.x",             4, 100,   1,  0, 0.1f,   0,250,  5, SD_SHOT10,420, 0,      0.5f, 1,   0},
                   { WEPON,   "地雷.x",             5, 130,   3,  2, 0.0f,  30, 60,999, SD_SHOT11,120, 0.01f,  0,    1,   5},
                   { WEPON,   "貫通.x",             6,  90,  12,  3, 0.2f,   5, 70, 10, SD_SHOT12,120, 0,      0,    1,   0},
                   { SUBITEM, "ジャンプアップ.x",   0,   0,   0,  0, 0.0f, 400,  0,  0, 0        ,100, 0,      0,    1,   0},
             /*15*/{ SUBITEM, "攻撃アップ.x",       0,   0,   0,  0, 0.0f, 400,  0,  0, 0        ,100, 0,      0,    1,   0},
                   { SUBITEM, "防御アップ.x",       0,   0,   0,  0, 0.0f, 400,  0,  0, 0        ,100, 0,      0,    1,   0},
                   { WEPON,   "時間差.x",           7,  80,  10,  3, 0.2f,  10, 70, 15, SD_SHOT13,120, 0,      0,    1,   7},
				   { WEPON,   "爆弾.x",             9,  60,   1,  3, 0.4f,  36,180, 40, SD_SHOT6, 150, 0.001f, 1.5f, 1,   4},
				   { WEPON,   "光線銃.x",           8,  30,  25,  3, 1.2f,   3,100,  8, SD_SHOT6, 150, 0,      0,    1,   2},
			 /*20*/{ WEPON,   "スナ.x",             8, 200,   5,  1, 2.9f,  80,150, 50, SD_SHOT14,159, 0,      0,    8.0f,0},
				   { WEPON,   "ミサイルランチャ.x",10,  90,   5,  2, 0.2f,  30, 40, 11, SD_SHOT6, 180, 0,      1.1f, 2.0f,0},
                   { SUBITEM, "ミラー.x",           0,   0,   0,  0, 0.0f,1000,  0,  0, 0        ,120, 0,      0,    1,   0},
                   { SUBITEM, "缶.x",               0,   0,   0,  0, 0.0f, 500,  0,  0, 0        ,180, 0,      0,    1,   0},
                   { SUBITEM, "インビジ.x",         0,   0,   0,  0, 0.0f, 500,  0,  0, 0        ,180, 0,      0,    1,   0},
		     /*25*/{ WEPON,   "爆弾.x",             9,  60,   1,  3, MAX_G, 36,180, 40, SD_SHOT6 ,150, 0.02f,  1.4f, 1,   0},
				   { WEPON, "ビームサーベル.x",    11, 100,   1,  3, 0.0f,  10,100,  1, SD_SHOT6 ,180, 0,      0,    1,   3}};
// 弾ファイル                   1        2              3              4          5       6          7         8           9          10           11
char BulletFile[][64]={"\0", "弾.x", "パチンコ玉.x", "バズーカ玉.x", "小弾.x", "地雷.x", "緑弾.x", "水弾.x","光線銃弾.x","爆弾.x","ミサイル.x","剣の軌跡.x"};
THING BulletObj[TAMAFILEMAX];
// 効果音ファイル名
char SoundFile[][64]={"\0",        "shot1.wav", "shot2.wav", "shot3.wav", "shot4.wav", "shot5.wav", "shot6.wav", "shot7.wav", "shot8.wav", "shot9.wav",
                      "shot10.wav","shot11.wav","shot12.wav","shot13.wav","shot14.wav","shot15.wav","atack1.wav","atack2.wav","atack3.wav","atack4.wav",
					  "atack5.wav","click1.wav","click2.wav","death.wav", "dog.wav",   "hit1.wav",  "hit2.wav",  "hit3.wav",  "jump.wav",  "rl.wav",
					  "icon.wav", "start.wav", "water.wav", "itemuse.wav","itemget.wav","menu.wav","move.wav",  "dmg.wav",   "enter.wav", "return.wav",
					  "shot16.wav","shot17.wav","shot18.wav","Explosion1.wav","Explosion2.wav","Explosion3.wav", "shot19.wav","shot20.wav", "shot21.wav",
                      "jump2.wav", "warp.wav"};
// BGMファイル名
char MusicFile[][64]={"\0", "op.mid", "op2.mid","op3.mid","dasaku.mid"};
// ステージ情報
typedef struct{
	THING obj;
	THING trap[SYOUGAISUU]; // 罠オブジェクト格納
	// アイテム
	struct ITEM{
		int num;
		int AppTimer;
		THING obj;
	}item[STAGEITEMMAX];
}STAGEDAT;
STAGEDAT StageDat;
// 移動中の弾情報
typedef struct{
	int num;
	int cnt;
	int tag;
	float a,g,gs; // 落下処理
	int Target;
	int mflg;
	THING obj;
}MOVINGBULLET;
MOVINGBULLET Bullet[5][BULLETMAX];
//爆風情報（位置、大きさを含む
struct EXTENSIONBLAST{
	int num;
	FLOAT ScaleUp;
	THING obj;
	EXTENSIONBLAST(){
		ScaleUp = 1;
	}
};
EXTENSIONBLAST Blast[5][BLASTMAX];
//爆風用変数
char BlastFile[64]={"./X/bom/爆発.x"};
THING BlastObj;

// 選択ステージ情報
typedef struct{
	char X[256];
	char img[256];
}STAGEFILE;
STAGEFILE StageFile[STAGECNT]={{"./X/field/じゃり.x", "./pic/Scr1.jpg"},
                               {"./X/field/もり.x",   "./pic/Scr2.jpg"},
                               {"./X/field/海.x",     "./pic/Scr3.jpg"},
                               {"./X/field/そら.x",   "./pic/Scr4.jpg"},
                               {"./X/field/屋敷.x",   "./pic/Scr5.jpg"},
                               {"./X/field/？？？.x", "./pic/Scr6.jpg"},
                               {"./X/field/五角.x",   "./pic/Scr7.jpg"},
                               {"./X/field/ワープ.x", "./pic/Scr8.jpg"},
                               {"./X/field/なにか.x", "./pic/Scr9.jpg"},
                               {"./X/field/球体.x",   "./pic/Scr10.jpg"}};

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
// ４分割列挙型
enum VIEW4{
	LEFT_UP=1,  // 1P
	RIGHT_UP,   // 2P
	LEFT_DOWN,  // 3P
	RIGHT_DOWN, // 4P
	D2D_DRAW,   // 2D描画
	D2D_SEL,    // 選択画面
};
// BGMデータ
typedef struct{
	IDirectMusicSegment8*	pMusSegment;		// セグメント
	IDirectMusicAudioPath8*	pMusAudioPath;		// オーディオパス
	BOOL bDownLoaded; // ダウンロード済みかどうか
}theMusic;
theMusic g_BGM[kNUM_OF_BGM]; // BGMの数だけ

// 効果音データ
typedef struct{
	WAVEFORMATEX sndWaveFormatEx;	// 波形データ情報
	HMMIO    sndHmmio;        // 波形データのmmioへのハンドル
	MMCKINFO sndChunk;        // dataチャンクの情報
	MMCKINFO sndChunkRiff;    // 波形ファイルを開くときに使う
	DWORD    sndCreationFlags;// 生成フラグ
	DWORD    sndNumOfBuffers; // バッファの数

	LPDIRECTSOUND3DBUFFER* sndDS3DSBuffer; // 3Dバッファへのポインタとパラメータ
	DS3DBUFFER*            sndDS3DSBufferParams;

	LPDIRECTSOUNDBUFFER*   sndDSSoundBuffer; // バッファへのポインタ
}theSounds;
theSounds g_SE[SOUNDFILEMAX];

// アイコン
char IconFile[][64]={{"./X/icon/びっくり1.x"},
                     {"./X/icon/びっくり2.x"},
                     {"./X/icon/喜び.x"},
				     {"./X/icon/怒り.x"}};
THING IconObj[4];
char LockOnFile[64]={"./X/Site/ロックオン.x"};
THING LockOnObj;