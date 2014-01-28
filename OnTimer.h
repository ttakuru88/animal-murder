//----------------//
// スタミナタイマ //
//----------------//
int StminTimer(void)
{
	for(int lp=1; lp<=gNinzu; lp++){
		// スタミナ回復
		if(Ch[lp].JpFlg >= RAKKA || !Ch[lp].JpFlg)
			Ch[lp].st += 1;
		if(Ch[lp].st > Ch[lp].maxst)
			Ch[lp].st = Ch[lp].maxst;
		// ダメージバー０へ収束
		if(Ch[lp].dmg > 0){
			Ch[lp].dmg -= DMGBARLOST;
			if(Ch[lp].dmg < 0)
				Ch[lp].dmg = 0;
		}
		else if(Ch[lp].dmg < 0){
			Ch[lp].dmg += DMGBARLOST;
			if(Ch[lp].dmg > 0)
				Ch[lp].dmg = 0;
		}
	}
	// ステージアイテム再出現タイマ
	for(int i=0; i<STAGEITEMMAX; i++){
		if(StageDat.item[i].num){
			if(StageDat.item[i].AppTimer){
				StageDat.item[i].AppTimer -= 1;
				if(StageDat.item[i].AppTimer == 0)
					StageDat.item[i].obj.Visible = TRUE;
			}
		}
	}
				

	return 0;
}
//----------------//
//  アイテム使用  //
//----------------//
int UseItem(int iNum, int lp, int useNum)
{
	if(Ch[lp].item[useNum].Timer || Ch[lp].item[useNum].rlTimer)
		return -1;

	switch(iNum){
		case NORMALSHOT: // 通常ショット
		case PATINKO:    // ぱちんこ
		case BAZUKA:     // バズーカ
		case KARASI:
		case SYURYUDAN:// テスト武器（手榴弾的軌道
		case BAKURETSU:// テスト武器（発射後破裂
		case ZIRAI:    // テスト武器（地雷
		case KANTSU:   // テスト武器（貫通
		case ZIKANSA:  // テスト武器（しばらく待機
		case BOM:      // 爆弾
		case KOUSEN:   // 光線銃
		case MISSILE:
		case SUNAIPA:  // スナイパーライフル
		case BEAMSODE:
			UseWepon(lp, useNum, iNum, 1);
			break;
		case SHOTGUN: // テスト武器（拡散
			UseWepon(lp, useNum, iNum, 15);
			break;
		case ENKEI: // テスト武器（横に１回転
			UseWepon(lp, useNum, iNum, 36);
			break;
		case RORABUREDO: // ローラブレード
			playASound(&g_SE[SD_ITEMUSE], 0, 0L ,TRUE);
			Ch[lp].item[useNum].Timer = ItemDat[iNum].shTime;
			Ch[lp].SpdUp  += UP_SPD;
			Ch[lp].TurnUp += UP_TURN;
			break;
		case NIKU:// お肉
			int ohp;
			// サウンド
			playASound(&g_SE[SD_ITEMUSE], 0, 0L ,TRUE);

			ohp = Ch[lp].hp;
			Ch[lp].hp += NIKUKAIFUKU;
			if(Ch[lp].maxhp < Ch[lp].hp)
				Ch[lp].hp = Ch[lp].maxhp;
			Ch[lp].dmg -= Ch[lp].hp - ohp; // 青ゲージ
			Ch[lp].item[useNum].num = 0;
			StageDat.item[Ch[lp].item[useNum].Ptnum].AppTimer = ItemDat[NIKU].AppTime;
			break;
		case GETA:// 下駄
			playASound(&g_SE[SD_ITEMUSE], 0, 0L ,TRUE);
			Ch[lp].item[useNum].Timer = ItemDat[iNum].shTime;
			Ch[lp].SpdUp  -= DOWN_SPD;
			Ch[lp].TurnUp -= DOWN_TURN;
			break;
		case TESTITEM1: // ジャンプアップ
			playASound(&g_SE[SD_ITEMUSE], 0, 0L ,TRUE);
			Ch[lp].item[useNum].Timer = ItemDat[iNum].shTime;
			Ch[lp].JumpUp += UP_JUMP;
			break;
		case TESTITEM2: // 攻撃アップ
			playASound(&g_SE[SD_ITEMUSE], 0, 0L ,TRUE);
			Ch[lp].item[useNum].Timer = ItemDat[iNum].shTime;
			Ch[lp].AtkUp += UP_ATK;
			break;
		case TESTITEM3: // 防御アップ
			playASound(&g_SE[SD_ITEMUSE], 0, 0L ,TRUE);
			Ch[lp].item[useNum].Timer = ItemDat[iNum].shTime;
			Ch[lp].DefUp += UP_DEF;
			break;
		case MIRA: // 反射
			playASound(&g_SE[SD_ITEMUSE], 0, 0L, TRUE);
			Ch[lp].item[useNum].Timer = ItemDat[iNum].shTime;
			break;
		case KAN:
			playASound(&g_SE[SD_ITEMUSE], 0, 0L, TRUE);
			Ch[lp].item[useNum].Timer = ItemDat[iNum].shTime;
			Ch[lp].JpFlg = JFLOAT;
			break;
		case INBIZI:
			playASound(&g_SE[SD_ITEMUSE], 0, 0L, TRUE);
			Ch[lp].item[useNum].Timer = ItemDat[iNum].shTime;
			Ch[lp].Visible = FALSE;
			break;
	}
	return 0;
}
//--------------//
//  弾発射処理  //
//--------------//
int UseWepon(int lp, int useNum, int iNum, int shotMax)
{
	int shotCnt = 0; // 発射回数

	if(lp) // 伽羅攻撃サウンド
		playASound(&g_SE[ItemDat[iNum].shSnd],0 , 0L ,TRUE);

	for(int i=0; i<=BULLETMAX; i++){
		if(Bullet[lp][i].num == NULL){ // 弾格納配列に空きあり。

			int hit=0;
			if(lp){ // キャラの弾発射
				ObjectPositionCopy(&Bullet[lp][i].obj, &Ch[lp].obj[Ch[lp].NowX]);
				Bullet[lp][i].obj.BBox.fLengthZ = BulletObj[iNum].BBox.fLengthZ/2;
				Ch[lp].item[useNum].Timer = ItemDat[iNum].shTime; // 発射間隔

				if(iNum != ZIRAI){
						// キャラの中心ぐらいから発射
					Bullet[lp][i].obj.vecPosition.y += Ch[lp].obj[Ch[lp].NowX].BBox.vecMax.y/2.3f;
					// レイ判定による目標への縦角度計算
					// ステージと
					if (RayShoot(&Ch[lp], &StageDat.obj, &fDistance, &vIntersect))
						CalcBulletPitch(lp, i, &hit, &vIntersect);
					// キャラと
					for(int j=1; j<=gNinzu; j++){
						if(j==lp || Ch[lp].item[1].num != MISSILE || Ch[lp].SelItem != 1) continue;
						if(RayShoot(&Ch[lp], &Ch[j].obj[Ch[j].NowX], &fDistance, &vIntersect))
							CalcBulletPitch(lp, i, &hit, &vIntersect);
					}
					// 横角度
					Bullet[lp][i].obj.fYaw = Ch[lp].obj[Ch[lp].NowX].fYaw;
					// レイが当たらなかった場合
					if(!hit)
						Bullet[lp][i].obj.fPitch = Ch[lp].Camera.Pitch-0.5f;
				}
			}
			if(!lp){ // 火山
				ObjectPositionCopy(&Bullet[lp][i].obj, &StageDat.trap[useNum]);
				Bullet[lp][i].obj.vecPosition.y += 1.0f;
				Bullet[lp][i].obj.fYaw = (rand()%314)/100.0f * ((rand()%2)?-1:1);
				Bullet[lp][i].obj.fPitch = -(float)(PI/2.0f);
				Bullet[lp][i].obj.ftag = (rand()%5) / 10.0f + 0.1f;
			}

			Bullet[lp][i].cnt = 0;
			Bullet[lp][i].mflg = FALSE;
			Bullet[lp][i].num = iNum;
			
			shotCnt++;
			// 特殊武器の効果
			switch(iNum){
				case SHOTGUN: // 拡散効果			
					Bullet[lp][i].obj.fPitch += ((rand()%10) / 100.0f) * ((rand()%2)?-1:1);
					Bullet[lp][i].obj.fYaw += ((rand()%10) / 100.0f) * ((rand()%2)?-1:1);
					break;
				case ENKEI: // 横に１回転
					Bullet[lp][i].obj.fYaw = (float)((shotCnt-1.0f)/(shotMax-1.0f) * PI*2);
					if(Bullet[lp][i].obj.fYaw > PI)
						Bullet[lp][i].obj.fYaw -= (float)(PI*2);
					break;
				case SYURYUDAN:case BOM:case MOUNT_TAMA: // 手榴弾的軌道の武器
					Bullet[lp][i].obj.fPitch -= 0.2f;
					Bullet[lp][i].gs = 0;
					Bullet[lp][i].g = (float)ItemDat[iNum].gSpeed;
					Bullet[lp][i].a = -Bullet[lp][i].obj.fPitch/2;
					break;
				case ZIRAI:
					Bullet[lp][i].gs = 0;
					Bullet[lp][i].g = (float)ItemDat[iNum].gSpeed;
					Bullet[lp][i].a = -Bullet[lp][i].obj.fPitch/2;
					break;
				case ZIKANSA: // 一時待機
					Bullet[lp][i].obj.tag = 40;
					break;
				case MISSILE: // ミサイル
					if(Ch[lp].LockOnNum)
						Bullet[lp][i].Target = Ch[lp].LockOnNum;
					break;
				case BEAMSODE:
					Bullet[lp][i].obj.vecPosition.x = Ch[lp].obj[Ch[lp].NowX].vecPosition.x - ChDat[Ch[lp].num].dX * sinf(Ch[lp].obj[Ch[lp].NowX].fYaw);
					Bullet[lp][i].obj.vecPosition.z = Ch[lp].obj[Ch[lp].NowX].vecPosition.z - ChDat[Ch[lp].num].dX * cosf(Ch[lp].obj[Ch[lp].NowX].fYaw);
					Bullet[lp][i].obj.vecPosition.y = Ch[lp].obj[Ch[lp].NowX].vecPosition.y + ChDat[Ch[lp].num].dY;
					Bullet[lp][i].obj.fYaw = Ch[lp].obj[Ch[lp].NowX].fYaw;
					Bullet[lp][i].obj.tag = 40;
					Ch[lp].Stop = DSTOP+2;
					Ch[lp].DageTime = DSTOP;
					break;
			}
			if(shotCnt>=shotMax)
				break;
		}
	}
	// 弾消費
	if(lp)
		DecBullet(lp, useNum, iNum);

	return 0;
}
//----------//
//  弾消費  //
//----------//
void DecBullet(int lp, int useNum, int iNum)
{
	Ch[lp].item[useNum].tama--;
	if(Ch[lp].item[useNum].tama == 0){ // リロード
		if(Ch[lp].item[useNum].rlCnt == 0 && useNum!=0){ // 弾尽きた
			Ch[lp].item[useNum].num = 0;
			Ch[lp].item[useNum].Timer = 0;
			// ズーム戻す
			Ch[lp].zoom = 1;
			StageDat.item[Ch[lp].item[useNum].Ptnum].AppTimer = ItemDat[iNum].AppTime;
			ChangeCharaMesh(lp, NORMALSHOT);
		}
		else{
			Ch[lp].item[useNum].rlCnt--;
			Ch[lp].item[useNum].rlTimer = ItemDat[iNum].rlTime;
		}
	}
}
//------------------//
//  弾のＹ角度計算  //
//------------------//
int CalcBulletPitch(int lp, int i, int *hit, D3DXVECTOR3 *Intersect)
{
	float a, b, xz;
	a = Ch[lp].obj[Ch[lp].NowX].vecPosition.x-Intersect->x;
	b = Ch[lp].obj[Ch[lp].NowX].vecPosition.z-Intersect->z;
	xz = sqrtf(a*a+b*b);
	b = Ch[lp].obj[Ch[lp].NowX].vecPosition.y-Intersect->y;
	Bullet[lp][i].obj.fPitch = b/xz;

	*hit = 1;

	return 0;
}
//------------------//
//  アイテムタイマ  //
//------------------//
int ItemTimer(void)
{
	int lp, i;
	
	for(i=0; i<STAGEITEMMAX; i++)
		if(StageDat.item[i].num)
			StageDat.item[i].obj.fYaw += 0.1f;

	for(lp=0; lp<=gNinzu; lp++){
		// 弾移動 ///////////////////////////////////
		for(int t=0; t<BULLETMAX; t++){
			if(Bullet[lp][t].num == NULL) continue;
			// 待機式の場合
			if(Bullet[lp][t].num == ZIKANSA){
				if(Bullet[lp][t].obj.tag > 0){
					Bullet[lp][t].obj.tag--;
					continue;
				}
			}
			if(Bullet[lp][t].num == BEAMSODE){
				if(Bullet[lp][t].obj.tag > 0){
					Bullet[lp][t].obj.tag--;
					continue;
				}
				Bullet[lp][t].num = Bullet[lp][t].obj.tag = 0;
			}
			Bullet[lp][t].cnt++;

			// 飛距離の限界に到達
			if(Bullet[lp][t].num == ZIRAI){ // 地雷式なら
				if(Bullet[lp][t].cnt > ItemDat[Bullet[lp][t].num].Range)
					Bullet[lp][t].num = Bullet[lp][t].tag = 0;
			}
			else if(Bullet[lp][t].cnt*ItemDat[Bullet[lp][t].num].tSpd >= ItemDat[Bullet[lp][t].num].Range * ((Bullet[lp][t].tag==BAKURETSU_2)?2:1)){
				// 分散処理 内部if文
				WeponEffect_Bunretsu(lp, t, BAKURETSUMAX, BAKURETSU, BAKURETSU_2);

				Bullet[lp][t].num = 0;
				Bullet[lp][t].tag = 0;
				continue;
			}
			// 障害物とのあたり判定
			else if(Bullet[lp][t].num != KANTSU){
				if(BulletStageRayInter(lp, t, RAY_MAE))
					continue;
				// 重力有りならレイ下にも
				if(ItemDat[Bullet[lp][t].num].gSpeed > 0){
					if(BulletStageRayInter(lp, t, RAY_SITA))
						continue;
				}
			}

			if (Bullet[lp][t].num){
				if(Bullet[lp][t].num == MOUNT_TAMA) // 火山弾
					ItemDat[Bullet[lp][t].num].tSpd = Bullet[lp][t].obj.ftag;

				Bullet[lp][t].obj.vecPosition.x -= ItemDat[Bullet[lp][t].num].tSpd * sinf(Bullet[lp][t].obj.fYaw);
				Bullet[lp][t].obj.vecPosition.z -= ItemDat[Bullet[lp][t].num].tSpd * cosf(Bullet[lp][t].obj.fYaw);
				// 爆裂後の乱数移動
				if(Bullet[lp][t].tag == BAKURETSU_2){
					Bullet[lp][t].obj.vecPosition.x -= Bullet[lp][t].obj.ftag;
					Bullet[lp][t].obj.vecPosition.z -= Bullet[lp][t].obj.ftag;
				}
				// 落下速度が設定されていれば
				if(ItemDat[Bullet[lp][t].num].gSpeed > 0){
					if(Bullet[lp][t].num != ZIRAI || Bullet[lp][t].num == ZIRAI && Bullet[lp][t].tag == FALSE){
						Bullet[lp][t].gs += Bullet[lp][t].g;
						Bullet[lp][t].a -= Bullet[lp][t].gs;
						LimitsMaxMin(Bullet[lp][t].a, -MAX_G, MAX_G);
						Bullet[lp][t].obj.vecPosition.y += Bullet[lp][t].a;
					}
					// 地雷なら地面まで落下
					if(Bullet[lp][t].num == ZIRAI){
						if(RayIntersect(&Bullet[lp][t].obj, &StageDat.obj, &fDistance, &vIntersect, &Ray[RAY_UE])){
							if(fDistance <= MAX_G){
								Bullet[lp][t].obj.vecPosition.y = vIntersect.y;
								Bullet[lp][t].tag = TRUE;
							}
						}
					}
				}
				else{ // その他y座標移動
					if(Bullet[lp][t].num == MISSILE)
						Bullet[lp][t].obj.vecPosition.y -= ItemDat[Bullet[lp][t].num].tSpd * tanf(-Bullet[lp][t].obj.fPitch);
					else
						Bullet[lp][t].obj.vecPosition.y -= ItemDat[Bullet[lp][t].num].tSpd * tanf(Bullet[lp][t].obj.fPitch);
				}
				if(Bullet[lp][t].num == MISSILE && Bullet[lp][t].cnt*ItemDat[Bullet[lp][t].num].tSpd < ItemDat[Bullet[lp][t].num].Range / 2) // ミサイルなら追尾
					MissileMove(lp,t,Bullet[lp][t].Target);
			}
		}
		// アイテム効果 ///////////////////////////////////
		for(i=0; i<ITEMMAX; i++){
			int iNum;
			iNum = Ch[lp].item[i].num;
			if(ItemDat[Ch[lp].item[i].num].type == SUBITEM){ // アイテムの場合
				if(!Ch[lp].item[i].Timer)
					continue;
				Ch[lp].item[i].Timer--;
				if(Ch[lp].item[i].Timer > 0)
					continue;
				// 効果終了
				StageDat.item[Ch[lp].item[i].Ptnum].AppTimer = ItemDat[Ch[lp].item[i].num].AppTime;
				Ch[lp].item[i].num = 0;
			}

			switch(iNum){
				case NORMALSHOT: case PATINKO:
				case BAZUKA:     case KARASI:
				case SHOTGUN:    case ENKEI:
				case SYURYUDAN:  case BAKURETSU:
				case ZIRAI:      case ZIKANSA:
				case KANTSU:     case BOM:
				case KOUSEN:     case SUNAIPA:
				case MISSILE:    case BEAMSODE:
					if(Ch[lp].item[i].Timer)
						Ch[lp].item[i].Timer--;
					if(Ch[lp].item[i].rlTimer && Ch[lp].SelItem == i){ // リロード
						Ch[lp].item[i].rlTimer--;
						if(Ch[lp].item[i].rlTimer == 0){// 完了
							// サウンド
							playASound(&g_SE[SD_RL],0 , 0L ,TRUE);
					
							Ch[lp].item[i].tama = Ch[lp].item[i].maxtama;
						}
					}
					break;
				case RORABUREDO: // ローラブレード
					Ch[lp].SpdUp  -= UP_SPD;
					Ch[lp].TurnUp -= UP_TURN;
					break;
				case GETA:// 下駄
					Ch[lp].SpdUp  += DOWN_SPD;
					Ch[lp].TurnUp += DOWN_TURN;
					break;
				case TESTITEM1: // ジャンプアップ
					Ch[lp].JumpUp -= UP_JUMP;
					break;
				case TESTITEM2: // 攻撃アップ
					Ch[lp].AtkUp -= UP_ATK;
					break;
				case TESTITEM3: // 防御アップ
					Ch[lp].DefUp -= UP_DEF;
					break;
				case KAN: // 浮遊
					if(!(Ch[lp].item[2].num == KAN && Ch[lp].item[2].Timer || Ch[lp].item[3].num == KAN && Ch[lp].item[3].Timer)){
						Ch[lp].JpFlg = RAKKA;
						Ch[lp].Mfloat = 0;
						Ch[lp].Ffloat = 0;
					}
					break;
				case INBIZI: // 透明
					Ch[lp].Visible = TRUE;
				default:
					break;
			}
		}
	}

	return 0;
}
//------------------------//
//  弾と障害物のレイ発射  //
//------------------------//
int BulletStageRayInter(int lp, int t, int RayVec)
{
	if(RayIntersect(&Bullet[lp][t].obj, &StageDat.obj, &fDistance, &vIntersect, &Ray[RayVec])){
		if(fDistance <= ItemDat[Bullet[lp][t].num].tSpd+Bullet[lp][t].obj.BBox.fLengthZ){
			BulletHitObstacle(lp, t);
			return 1;
		}
	}

	return 0;	
}
//------------------------//
//  弾が障害物に当たった  //
//------------------------//
void BulletHitObstacle(int lp, int t)
{
	int rt;
	rt = WeponEffect_Bunretsu(lp, t, 100, BAKURETSU, BAKURETSU_2);
	// 爆風が設定されてたら
	if(ItemDat[Bullet[lp][t].num].bMax > 0)
		SetBlast(lp, t);
	else if(rt == -1)
		playASound(&g_SE[SD_HIT3],0 , 0L ,TRUE);
	// 弾終了
	Bullet[lp][t].num = 0;
	Bullet[lp][t].tag = 0;
}
//------------//
//  爆風作る  //
//------------//
void SetBlast(int lp, int t)
{
	for(int b=0; b<BLASTMAX; b++){
		if(Blast[lp][b].num == NULL){
			playASound(&g_SE[SD_EXPLOSION3],0 , 0L ,TRUE);
			ObjectPositionCopy(&Blast[lp][b].obj, &Bullet[lp][t].obj);
			Blast[lp][b].obj.Sphere.fRadius = BlastObj.Sphere.fRadius;
			Blast[lp][b].num = Bullet[lp][t].num;
			Blast[lp][b].obj.fScale = 0.1f;
			break;
		}
	}
}
//--------------//
//  弾分裂処理  //
//--------------//
int WeponEffect_Bunretsu(int lp, int t, int shotMax, int wnum, int wtag)
{
	if(Bullet[lp][t].num == wnum && !Bullet[lp][t].tag){
		playASound(&g_SE[SD_SHOT14],0 , 0L ,TRUE);
		int shotCnt=0;
		for(int b=0; b<=BULLETMAX; b++){
			if(Bullet[lp][b].num == NULL){ // 弾格納配列に空きあり。
				ObjectPositionCopy(&Bullet[lp][b].obj, &Bullet[lp][t].obj);
				shotCnt++;
				// 横角度
				Bullet[lp][b].obj.fYaw = (rand()%314)/100.0f * ((rand()%2)?-1:1);
				Bullet[lp][b].obj.fPitch = ((rand()%200)+114)/100.0f * -1;
				Bullet[lp][b].cnt = 0;
				Bullet[lp][b].num = wnum;
				Bullet[lp][b].tag = wtag;
				Bullet[lp][b].obj.ftag = ((rand()%2)?-1:1)*(rand()%10)/100.0f * sinf(Bullet[lp][t].obj.fYaw);
				
				if(shotCnt>=shotMax)
					return 1;
			}
		}
	}
	else
		return -1;

	return 0;
}
//------------------//
//  爆風タイマ      //
//------------------//
int BlastTimer(void)
{
	int lp;
	for(lp=0; lp<=gNinzu ; lp++){
		for(int t=0 ; t<BLASTMAX;t++){
			if(Blast[lp][t].num == NULL)continue;
			if(Blast[lp][t].obj.fScale >= ItemDat[Blast[lp][t].num].bMax*2){
				// 爆風終了
				Blast[lp][t].num = 0;
				Blast[lp][t].obj.fScale=0;
				Blast[lp][t].ScaleUp=1;
				return 0;
			}
			Blast[lp][t].obj.fScale +=Blast[lp][t].ScaleUp;
			Blast[lp][t].ScaleUp /= 2.4f;
			Blast[lp][t].ScaleUp += 0.04f;
		}
	}
	return 0;
}
//------------------//
//  トラップタイマ  //
//------------------//
int TrapTimer(void)
{
	for(int i=0; i<Syougaisu; i++){
		if(StageDat.trap[i].type == TYPE_DOKU){ // 毒移動
			if(StageDat.trap[i].tag == GOTOP){
				StageDat.trap[i].vecPosition.y += 0.05f;
				if(StageDat.trap[i].vecPosition.y > -16.5f)
					StageDat.trap[i].tag = GOBOTTOM;
			}
			else{
				StageDat.trap[i].vecPosition.y -= 0.05f;
				if(StageDat.trap[i].vecPosition.y < -25.0f)
					StageDat.trap[i].tag = GOTOP;
			}
			// 毒との当たり判定
			for(int lp=1; lp<=gNinzu; lp++){
				if(Ch[lp].obj[Ch[lp].NowX].vecPosition.y < StageDat.trap[i].vecPosition.y+20.0f){
					Calcdmg(i, lp, DOKUDMG, NULL);
					if(Ch[lp].JpFlg==FALSE)
						Ch[lp].g = FIRST_G/2;
				}
				else
					Ch[lp].g = FIRST_G;
			}

		}
		else if(StageDat.trap[i].type == TYPE_BETA){// エレベーター
			if(StageDat.trap[i].tag == GOTOP){
				StageDat.trap[i].vecPosition.y += 0.06f;
				if(StageDat.trap[i].vecPosition.y > 18.0f)
					StageDat.trap[i].tag = GOBOTTOM;
			}
			else{
				StageDat.trap[i].vecPosition.y -= 0.06f;
				if(StageDat.trap[i].vecPosition.y < -6.0f)
					StageDat.trap[i].tag = GOTOP;
			}
		}
		else if(StageDat.trap[i].type == TYPE_MOUNT){ // 火山
			StageDat.trap[i].tag++;
			if(StageDat.trap[i].tag > MOUNT_INTER){
				playASound(&g_SE[SD_SHOT4], 0, 0L, TRUE);
				UseWepon(0, i, MOUNT_TAMA, 1);
				StageDat.trap[i].tag = 0;
			}
		}
	}

	return 0;
}
//--------------------//
//  攻撃ダメージ処理  //
//--------------------//
VOID Calcdmg(int c, int cc, int type, int t)
{
	if(Ch[cc].alive == FALSE)
		return;

	int dmg;
	int vx, vy, vt=0, st;
	switch(type){
		case JUMPDMG: // ジャンプ攻撃
			dmg = 30;
			if(Ch[cc].hp <= 0){
				Ch[cc].hp = 0;
				Ch[cc].alive = FALSE;
			}
			Ch[c].JpFlg = ATACK_HIT;
			vy = 10000;
			st = 2;
			vt = 10;
			break;
		case DAGEDMG: // 打撃攻撃
				dmg = (ChDat[Ch[c].num].nAtack + Ch[c].AtkUp) - (ChDat[Ch[cc].num].nGard + Ch[cc].DefUp);
				if(dmg <= 0)
					dmg = 10;
				vx = 10000;
				st = 2;
				vt = 10;
			break;
		case WANADMG: // 罠にはまった
			dmg = 20;
			vt = st = WANASTOP;
			StageDat.trap[c].Visible = FALSE;
			vx = 3000;
			vy = -3000;
			break;
		case SHOTDMG: // 弾に当たった。ccが
			dmg = ItemDat[Bullet[c][t].num].atk - ChDat[Ch[cc].num].nGard;
			if(dmg <= 0)
				dmg = 10;
			vx = 10000;
			st = 3;
			vt = 15;

			Bullet[c][t].num = 0;
			Bullet[c][t].obj.Visible = FALSE;
			break;
		case DOKUDMG: // 毒沼落ちた
			dmg = 2;
			st = 0;
			break;
		case BLASTDMG: //爆風に当たった
			dmg = 5;
			vt = 1;
			vx = 4000;
			vy = -4000;
			st = 0;
			break;
	}
	Ch[cc].hp -= dmg;
	Ch[cc].dmg += dmg;
	if(Ch[cc].hp <= 0) // 死んだ
		CharaDied(cc, vx, vy, vt);
	else if(type != DOKUDMG && type != BLASTDMG)
		playASound(&g_SE[SD_DMG], 0, 0L ,TRUE);
	Joy[cc].VibTime += vt;
	if(Joy[cc].VibTime > VIBTIMEMAX)
		Joy[cc].VibTime = VIBTIMEMAX;
	Joy[cc].VibX += vx;
	Joy[cc].VibY += vy;
	Ch[cc].Stop += st;
	if(Ch[cc].Stop > STOPMAX)
		Ch[cc].Stop = STOPMAX;
}
//------------------//
//  死んだ時の処理  //
//------------------//
void CharaDied(int cc, int vx, int vy, int vt)
{
	// サウンド
	playASound(&g_SE[SD_DEATH],0 , 0L ,TRUE);

	Ch[cc].hp = 0;
	Ch[cc].alive = FALSE;
	Ch[cc].Dageki.Visible = FALSE;
	Ch[Ch[cc].LockOnFlg].LockOnNum = 0;
	Ch[cc].LockOnFlg = 0;
	
	vx *= 2;
	vy *= 2;
	vt *= 2;

	// 弾消す
	for(int i=0; i<BULLETMAX; i++){
		if(Bullet[cc][i].num){
			Bullet[cc][i].num = 0;
			Bullet[cc][i].obj.Visible = FALSE;
		}
	}
	// アイコン出てたら消す
	if(Ch[cc].IconFlg == TRUE){
		Ch[cc].IconFlg = FALSE;
		ReleaseObject(&Ch[cc].Iconobj);
	}

	// 勝敗決定
	AliveCnt--;
	if(GameMode == ROYALE_MODE){
		Ch[cc].rank = AliveCnt+1;
		if(AliveCnt == 1){
			for(int i=1; i<=gNinzu; i++) // 1位決定
				if(Ch[i].alive == TRUE)
					Ch[i].rank = 1;
			ChangeDrawingMode(RESULTWINDOW, gNinzu, NULL);
		}
	}
	else{ // チーム戦
		// 順位決定
		TeamNowCnt[Ch[cc].Team]--;
		if(!TeamNowCnt[Ch[cc].Team]){
			for(int t=1; t<=gNinzu; t++){
				if(Ch[t].Team == Ch[cc].Team)
					Ch[t].rank = TeamKazu;
			}
			TeamKazu--;
		}
		if(TeamKazu==1){
			for(int t=1; t<=gNinzu; t++){
				if(Ch[t].alive == TRUE){
					WinTeam = Ch[t].Team;
					break;
				}
			}
			for(int t=1; t<=gNinzu; t++)
				if(Ch[t].Team == WinTeam)
					Ch[t].rank = 1;
			ChangeDrawingMode(RESULTWINDOW, gNinzu, NULL);
		}
	}
}
//-------------//
//  枠読み込み //
//-------------//
int ReadFrame(int n)
{
	// 枠読み込み
	char fname[128];
	wsprintf(fname, "./pic/bar%d.png", n);
	TextureFromFile(fname, &pBar);

	return 0;
}