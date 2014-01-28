//--------------------------//
//  キャラ移動、アクション  //
//--------------------------//
int BattleTimer(HWND hWnd)
{
	int stflg = FALSE; // スタートボタン重複防止
	battleFlg = TRUE;

	for(int lp=1; lp<=gNinzu; lp++){ // ４キャラ分ループ
		Joy[lp].LX = (!Joy[lp].LX)?-1:Joy[lp].LX;
		Joy[lp].LY = (!Joy[lp].LY)?-1:Joy[lp].LY;
		Joy[lp].RX = (!Joy[lp].RX)?-1:Joy[lp].RX;
		Joy[lp].RY = (!Joy[lp].RY)?-1:Joy[lp].RY;
		// 振動パック
		FLOAT Pitup=0, Yawup=0;
		BattleVib(lp, &Pitup, &Yawup);
		// スタートボタンで停止
		BattleStartButton(lp, &stflg);
		// メニューが出てたら
		if(Ch[lp].alive == FALSE || DrawingMode==MENUWINDOW || DrawingMode==RESULTWINDOW)
			continue;
		// 以下、生きてるキャラのみ ///////////////////////////
		BattleJump(lp); // ジャンプ
		// キャラ移動
		float yxmove, yzmove, xxmove, xzmove;
		BattleCharaMove(lp, &yxmove, &yzmove, &xxmove, &xzmove);
		// 衝突判定 //////////////////////////////////
		BattleCharaCollisionToStage(lp, yxmove, yzmove, xxmove, xzmove);
		BattleCharaCollisionToBeta(lp);
		BattleCharaCollisionToChara(lp);  // ジャンプ攻撃
		BattleCharaCollisionToDageki(lp); // 打撃攻撃
		BattleCharaCollisionToTrap(lp);   // 罠
		BattleCharaCollisionToBullet(lp); // 弾
		BattleCharaCollisionToItem(lp);   // アイテム
		BattleCharaCollisionToBlast(lp);  // 爆風
		// カメラ移動
		BattleCameraMove(lp, Pitup, Yawup);
		// キャラアイコン
		BattleCharaIcon(lp);
		//ロックオンサイト
		BattleLockOn(lp);
		// 打撃攻撃
		BattleDageki(lp);
		// アイテム使用
		BattleItemUse(lp);
		// ズーム
		BattleZoom(lp);
	}
	// 座標表示
	if(gNinzu == 1)
		sprintf(debug1, "x=%f\ny=%f\nz=%f\nfYaw=%f\nPitch=%f\nselitem=%d",Ch[1].obj[Ch[1].NowX].vecPosition.x,Ch[1].obj[Ch[1].NowX].vecPosition.y,Ch[1].obj[Ch[1].NowX].vecPosition.z,Ch[1].obj[Ch[1].NowX].fYaw,Ch[1].Camera.Pitch,Ch[1].SelItem);

	return 0;
}
//------------//
//  振動処理  //
//------------//
void BattleVib(int lp, float *Pitup, float *Yawup)
{
	if(Joy[lp].VibTime > 0 && KeyMode==FALSE && Ch[lp].cpu == FALSE){
		if(Joy[lp].VibFlg == FALSE){
			Joy[lp].VibFlg = TRUE;
			if(VibMode == TRUE)
				UpdateEffect(Joy[lp].VibX, Joy[lp].VibY, lp-1);
		}
		Joy[lp].VibTime--;
		*Pitup = float(0.1 * ((Joy[lp].VibTime%2)?-1:1));
		*Yawup = float(0.1 * ((Joy[lp].VibTime%2)?1:-1));
		if(Joy[lp].VibTime<=0){
			Joy[lp].VibX = Joy[lp].VibY = 0;
			Joy[lp].VibFlg = FALSE;
			Joy[lp].VibTime=0;
			if(VibMode == TRUE)
				UpdateEffect(0, 0, lp-1);
		}
	}
	// コンピュータ
	if(GameMode == ROYALE_MODE){
		if(Ch[lp].cpu == TRUE && Joy[lp].VibTime>0){
			CpuIconChange(lp, ICON_BIKKURI);
			Joy[lp].VibTime--;
		}
		else if((float)Ch[lp].hp/Ch[lp].maxhp < 0.3f)
			CpuIconChange(lp, ICON_IKARI);
		else
			CpuIconChange(lp, ICON_NICONICO);
	}
}
//----------------------//
//  スタートボタン処理  //
//----------------------//
void BattleStartButton(int lp, int *stflg)
{
	if(BTN_START(lp) && Joy[lp].startFlg==FALSE && *stflg==FALSE){
		Joy[lp].startFlg = TRUE;
		*stflg = TRUE;
		
		if(DrawingMode == BATTLEWINDOW) // ウィンドウ開く
			ChangeDrawingMode(MENUWINDOW, gNinzu, NULL);
		else if(DrawingMode == MENUWINDOW) // ウィンドウ閉じる
			ChangeDrawingMode(BATTLEWINDOW, gNinzu, NULL);
	}
	else if(!BTN_START(lp))
		Joy[lp].startFlg = FALSE;
}
//----------------------//
//  ジャンプと落下処理  //
//----------------------//
void BattleJump(int lp)
{
	if(Ch[lp].JpFlg == JFLOAT){
		if(BTN_R1(lp))
			Ch[lp].obj[Ch[lp].NowX].vecPosition.y += 0.1f;
		if(BTN_L1(lp))
			Ch[lp].obj[Ch[lp].NowX].vecPosition.y -= 0.1f;
		if(Ch[lp].Ffloat == GOTOP){ // 上揺れ
			float ans = (FLOATMAX - fabsf(Ch[lp].Mfloat))/10;
			Ch[lp].Mfloat += (ans<FLOATMOVEMIN)?FLOATMOVEMIN:ans;
			if(Ch[lp].Mfloat >= FLOATMAX)
				Ch[lp].Ffloat = GOBOTTOM;
		}
		else if(Ch[lp].Ffloat == GOBOTTOM){ // 下揺れ
			float ans = (FLOATMAX + -fabsf(Ch[lp].Mfloat))/10;
			Ch[lp].Mfloat -= (ans<FLOATMOVEMIN)?FLOATMOVEMIN:ans;
			if(Ch[lp].Mfloat <= -FLOATMAX)
				Ch[lp].Ffloat = GOTOP;
		}
	}
	else{
		if(BTN_R1(lp) && Joy[lp].r1Flg==FALSE && Ch[lp].st >= JUMPST && Ch[lp].JpFlg==FALSE && !Ch[lp].gs)
			CharaJump(lp, NULL, JUMPST);
		else if(!BTN_R1(lp))
			Joy[lp].r1Flg = FALSE;
		// 落下
		Ch[lp].gs -= Ch[lp].g;
		if(Ch[lp].gs<=-MAX_G)
			Ch[lp].gs=-MAX_G;
		// 落下中かどうか
		if(Ch[lp].JpFlg == TRUE && Ch[lp].gs < 0)
			Ch[lp].JpFlg = RAKKA;
	
		Ch[lp].obj[Ch[lp].NowX].vecPosition.y += Ch[lp].gs;
		if(Ch[lp].obj[Ch[lp].NowX].vecPosition.y < -MAXVECY)
			Ch[lp].obj[Ch[lp].NowX].vecPosition.y = MAXVECY;
	}
}
//----------------//
//  ジャンプ行為  //
//----------------//
void CharaJump(int lp, float fuka, int usest)
{
	if(fuka >= 1.0)
		playASound(&g_SE[SD_JUMP2], 0, 0L, TRUE);
	else
		playASound(&g_SE[SD_JUMP],0 , 0L ,TRUE);

	Joy[lp].r1Flg = TRUE;
	Ch[lp].gs += Ch[lp].a * (ChDat[Ch[lp].num].nJump + Ch[lp].JumpUp + fuka);
	Ch[lp].JpFlg = TRUE;
	Ch[lp].st -= usest;
}
//------------------//
//  キャラ移動処理  //
//------------------//
void BattleCharaMove(int lp, float *yxmove, float *yzmove, float *xxmove, float *xzmove)
{
	// キャラ停止
	float move_q;
	if(Ch[lp].Stop > 0){
		move_q = 0;
		Ch[lp].Stop--;
	}
	else if(BTN_L1(lp) && Ch[lp].JpFlg != JFLOAT){ // ダッシュ使用
		if(Joy[lp].LY+1!=0 || Joy[lp].LX+1!=0) // ダッシュ中
			Ch[lp].st -= DUSHST + Ch[lp].JpFlg;
		if(Ch[lp].st > 0)
			move_q = ChDat[Ch[lp].num].nDash + Ch[lp].SpdUp;
		else{
			Ch[lp].st = 0;
			move_q = ChDat[Ch[lp].num].nSpeed/2.0f + Ch[lp].SpdUp;
		}
	}
	else
		move_q = ChDat[Ch[lp].num].nSpeed + Ch[lp].SpdUp;
	
	// 移動
	if(move_q > MAXSPEED)
		move_q = MAXSPEED;
	*yxmove = (float)((Joy[lp].LY+1)/CHAR_MOVE) * sinf(Ch[lp].obj[Ch[lp].NowX].fYaw) * move_q;
	*yzmove = (float)((Joy[lp].LY+1)/CHAR_MOVE) * cosf(Ch[lp].obj[Ch[lp].NowX].fYaw) * move_q;
	*xxmove = (float)((Joy[lp].LX+1)/CHAR_MOVE) * cosf(Ch[lp].obj[Ch[lp].NowX].fYaw) * move_q;
	*xzmove = (float)((Joy[lp].LX+1)/CHAR_MOVE) * sinf(Ch[lp].obj[Ch[lp].NowX].fYaw) * move_q;
	if (Joy[lp].LY+1 != 0){
		Ch[lp].obj[Ch[lp].NowX].vecPosition.x += *yxmove;
		Ch[lp].obj[Ch[lp].NowX].vecPosition.z += *yzmove;
	}
	if (Joy[lp].LX+1 != 0){
		Ch[lp].obj[Ch[lp].NowX].vecPosition.x -= *xxmove;
		Ch[lp].obj[Ch[lp].NowX].vecPosition.z += *xzmove;
	}
}
//--------------------------------//
//  キャラとステージの当たり判定  //
//--------------------------------//
void BattleCharaCollisionToStage(int lp, float yxmove, float yzmove, float xxmove, float xzmove)
{
	int coll=-1;

	for (int k=0;k<10;k++){
		if(RayIntersect(&Ch[lp].obj[Ch[lp].NowX], &StageDat.obj, &fDistance, &vIntersect, &Ray[k]) ){
			if(k==RAY_UE && fDistance <=0.15f + Ch[lp].obj[Ch[lp].NowX].BBox.fLengthY){ // 頭上に衝突
				Ch[lp].gs = -Ch[lp].gs + 0.3f;
				if(Ch[lp].gs>0)
					Ch[lp].gs = 0;
				if(Ch[lp].JpFlg != JFLOAT)
					Ch[lp].JpFlg = RAKKA;
				else
					Ch[lp].obj[Ch[lp].NowX].vecPosition.y -= 0.1f;
			}
			if(k==RAY_SITA && fDistance <= Ch[lp].obj[Ch[lp].NowX].BBox.vecMax.y || k==RAY_UE && fDistance <= Ch[lp].obj[Ch[lp].NowX].BBox.fLengthY/2){ // 地面にいる
				Ch[lp].gs = (float)0.0f;
				if(Ch[lp].JpFlg != JFLOAT)
					Ch[lp].JpFlg = FALSE;
				Ch[lp].obj[Ch[lp].NowX].vecPosition.y = vIntersect.y;
			}
			else if (fDistance <= 0.12){ // 衝突
				if (Joy[lp].LY+1 != 0){
					Ch[lp].obj[Ch[lp].NowX].vecPosition.x -= yxmove;
					Ch[lp].obj[Ch[lp].NowX].vecPosition.z -= yzmove;
				}
				if (Joy[lp].LX+1 != 0){
					Ch[lp].obj[Ch[lp].NowX].vecPosition.x += xxmove;
					Ch[lp].obj[Ch[lp].NowX].vecPosition.z -= xzmove;
				}
			}
			else if(fDistance <= 0.5)
				// cpu用
				if(Ch[lp].cpu == TRUE)
					if(coll == -1 && (k == RAY_MAE || k == RAY_MIGI || k == RAY_HIDARI))
						coll = k;
		}
	}
	Ch[lp].collision = coll;
}
//--------------------------//
//  ベーターとのあたり判定  //
//--------------------------//
void BattleCharaCollisionToBeta(int lp)
{
	for(int i=0; i<Syougaisu; i++){
		if(!CompDist(&Ch[lp].obj[Ch[lp].NowX], &StageDat.trap[i], 5.0f) || StageDat.trap[i].type != TYPE_BETA && StageDat.trap[i].type != TYPE_MOUNT || Ch[lp].JpFlg == JFLOAT) continue;
		if(RayIntersect(&Ch[lp].obj[Ch[lp].NowX], &StageDat.trap[i], &fDistance, &vIntersect, &Ray[RAY_SITA])){
			if(fDistance <= Ch[lp].obj[Ch[lp].NowX].BBox.vecMax.y){
				Ch[lp].gs = (float)0.0f;
				Ch[lp].JpFlg = FALSE;
				Ch[lp].obj[Ch[lp].NowX].vecPosition.y = vIntersect.y;
			}
		}
	}
}
//----------------------------//
//  ジャンプ攻撃の当たり判定  //
//----------------------------//
void BattleCharaCollisionToChara(int lp)
{
	for(int cc=lp+1; cc<=gNinzu; cc++){
		if(Ch[cc].alive==FALSE || lp==gNinzu || Ch[lp].Team==Ch[cc].Team || !CompDist(&Ch[cc].obj[Ch[cc].NowX], &Ch[lp].obj[Ch[lp].NowX], 2.0f)) continue;
		if(OBBCollisionDetection(&Ch[lp].obj[Ch[lp].NowX], &Ch[cc].obj[Ch[cc].NowX])){
			if(Ch[lp].JpFlg==RAKKA) Calcdmg(lp, cc, JUMPDMG, NULL);
			if(Ch[cc].JpFlg==RAKKA) Calcdmg(cc, lp, JUMPDMG, NULL);
		}
	}
}
//--------------------//
//  距離が遠ければ偽  //
//--------------------//
int CompDist(THING *Aobj, THING *Bobj, float limDist)
{
	float x = Aobj->vecPosition.x - Bobj->vecPosition.x;
	float z = Aobj->vecPosition.z - Bobj->vecPosition.z;

	if(sqrt(x*x+z*z) <= limDist)
		return 1;
	else
		return 0;
}
//------------------------//
//  打撃攻撃の当たり判定  //
//------------------------//
void BattleCharaCollisionToDageki(int lp)
{
	for(int cc=1; cc<=gNinzu; cc++){
		if(Ch[cc].Dageki.Visible==FALSE || lp==cc || Ch[lp].Team==Ch[cc].Team || !CompDist(&Ch[cc].obj[Ch[cc].NowX], &Ch[lp].obj[Ch[lp].NowX], 2.0f)) continue;
		if(OBBCollisionDetection(&Ch[lp].obj[Ch[lp].NowX], &Ch[cc].Dageki)){
			Calcdmg(cc, lp, DAGEDMG, NULL);
			Ch[cc].Dageki.Visible = FALSE;
		}
	}
}
//--------------------//
//  罠とのあたり判定  //
//--------------------//
void BattleCharaCollisionToTrap(int lp)
{
	for(int cc=0; cc<Syougaisu; cc++){
		if(StageDat.trap[cc].Visible==FALSE || !CompDist(&StageDat.trap[cc], &Ch[lp].obj[Ch[lp].NowX], 2.0f)) continue;
		if(OBBCollisionDetection(&StageDat.trap[cc], &Ch[lp].obj[Ch[lp].NowX])){
			if(StageDat.trap[cc].type == TYPE_IN){
				playASound(&g_SE[SD_WARP], 0, 0L, TRUE);
				Ch[lp].obj[Ch[lp].NowX].vecPosition = StageDat.trap[StageDat.trap[cc].tag].vecPosition;
			}
			else if(StageDat.trap[cc].type == TYPE_TRAP)
				Calcdmg(cc, lp, WANADMG, NULL);
			else if(StageDat.trap[cc].type == TYPE_JUMP && Ch[lp].JpFlg != JFLOAT)
				CharaJump(lp, 1.0f, NULL);
		}
	}
}
//--------------------//
//  弾との当たり判定  //
//--------------------//
void BattleCharaCollisionToBullet(int lp)
{
	for(int cc=1; cc<=gNinzu; cc++){
		if(Ch[lp].Team==Ch[cc].Team && lp!=cc) continue;
		for(int t=0; t<BULLETMAX; t++){
			if(lp==cc&&Bullet[cc][t].mflg==FALSE || Bullet[cc][t].num==NULL || !CompDist(&Bullet[cc][t].obj, &Ch[lp].obj[Ch[lp].NowX], MaxtSpd)) continue;
			if(Bullet[cc][t].num != ZIRAI && Bullet[cc][t].num != BEAMSODE){
				if(RayIntersect(&Bullet[cc][t].obj, &Ch[lp].obj[Ch[lp].NowX], &fDistance, &vIntersect, &Ray[RAY_MAE])){
					if(fDistance <= ItemDat[Bullet[cc][t].num].tSpd+Bullet[cc][t].obj.BBox.fLengthZ){
						if(Ch[lp].item[2].num == MIRA && Ch[lp].item[2].Timer) // 反射
							HansyaSuruyo(lp, cc, t, 2);
						else if(Ch[lp].item[3].num == MIRA && Ch[lp].item[3].Timer) // 反射
							HansyaSuruyo(lp, cc, t, 3);
						else // 通常
							Calcdmg(cc, lp, SHOTDMG, t);
					}
				}
			}
			// 地雷はBBox
			else if(Bullet[cc][t].num == ZIRAI){
				if(OBBCollisionDetection(&Bullet[cc][t].obj, &Ch[lp].obj[Ch[lp].NowX]))
					Calcdmg(cc, lp, SHOTDMG, t);
			}
			// ビームソードの当たり判定
			else if(Bullet[cc][t].num == BEAMSODE){
				Bullet[cc][t].obj.BBox = BulletObj[ItemDat[BEAMSODE].tnum].BBox;
				for(int t2=0;t2<BULLETMAX;t2++){
					if(OBBCollisionDetection(&Bullet[cc][t].obj,&Bullet[lp][t2].obj)){
						Bullet[lp][t2].mflg = TRUE;
						Bullet[lp][t2].obj.fPitch = -Bullet[lp][t2].obj.fPitch;
						Bullet[lp][t2].obj.fYaw   = ((rand()%2)?-1:1) * (rand()%314)/100.0f;
					}
				}
				if(OBBCollisionDetection(&Bullet[cc][t].obj,&Ch[lp].obj[Ch[lp].NowX])){
					Calcdmg(cc, lp, SHOTDMG, t);
				}
			}
		}
	}
}
//------------//
//  反射処理  //
//------------//
void HansyaSuruyo(int lp, int cc, int t, int inum)
{
	playASound(&g_SE[SD_HIT3],0 , 0L ,TRUE);
	Bullet[cc][t].mflg = TRUE;
	Bullet[cc][t].obj.fPitch = -Bullet[cc][t].obj.fPitch;
	Bullet[cc][t].obj.fYaw   = ((rand()%2)?-1:1) * (rand()%314)/100.0f;
	Ch[lp].item[inum].Timer -= ItemDat[Bullet[cc][t].num].atk;
	
	// ミサイルなら
	if(Bullet[cc][t].num == MISSILE)
		Bullet[cc][t].Target = cc;

	if(Ch[lp].item[inum].Timer <= 0){ // 効果終了
		StageDat.item[Ch[lp].item[inum].Ptnum].AppTimer = ItemDat[Ch[lp].item[inum].num].AppTime;
		Ch[lp].item[inum].Timer = 0;
		Ch[lp].item[inum].num = 0;
	}
	else if(ItemDat[Bullet[cc][t].num].type == WEPON){
		
	}
}
//--------------------------//
//  アイテムとの当たり判定  //
//--------------------------//
void BattleCharaCollisionToItem(int lp)
{
	for(int i=0; i<StageItemMax; i++){
		if(StageDat.item[i].obj.Visible==FALSE || !StageDat.item[i].num || !CompDist(&StageDat.item[i].obj, &Ch[lp].obj[Ch[lp].NowX], 1.0f)) continue;
		if(OBBCollisionDetection(&StageDat.item[i].obj, &Ch[lp].obj[Ch[lp].NowX])){
			for(int j=1; j<ITEMMAX; j++){
				if(Ch[lp].item[j].num==NULL && (ItemDat[StageDat.item[i].num].type==WEPON&&j==1 || ItemDat[StageDat.item[i].num].type==SUBITEM&&j>1)){
					Ch[lp].item[j].num = StageDat.item[i].num;
					StageDat.item[i].obj.Visible = FALSE;
					Ch[lp].item[j].Ptnum = i;
					// 武器なら
					if(ItemDat[StageDat.item[i].num].type == WEPON){
						Ch[lp].item[j].tama = Ch[lp].item[j].maxtama = ItemDat[StageDat.item[i].num].tama;
						Ch[lp].item[j].rlCnt = ItemDat[StageDat.item[i].num].rlCount;
						if(Ch[lp].SelItem == 1) // 武器にカーソルがあればキャラチェンジ
							ChangeCharaMesh(lp, Ch[lp].item[1].num);
					}
					// アイテムゲタなら即効使用
					if(Ch[lp].item[j].num==GETA)
						UseItem(GETA, lp, j);
					else
						playASound(&g_SE[SD_ITEMGET], 0, 0L ,TRUE);
					break;
				}
			}
		}
	}
}
//----------------------//
//  爆風との当たり判定  //
//----------------------//
void BattleCharaCollisionToBlast(int lp)
{
	for(int cc=0; cc<=gNinzu; cc++){
		for(int t=0;t<=BLASTMAX;t++){
			if(Blast[cc][t].num == NULL) continue;
			if(SphereCollision(&Ch[lp].obj[Ch[lp].NowX],&Blast[cc][t].obj ))
				Calcdmg(cc, lp, BLASTDMG, NULL);
		}
	}
}
//--------------//
//  カメラ移動  //
//--------------//
void BattleCameraMove(int lp, float Pitup, float Yawup)
{
	float turn_q = ChDat[Ch[lp].num].nTurn + Ch[lp].TurnUp;
	if(!Ch[lp].DageTime){
		Ch[lp].Camera.Pitch += (float)((Joy[lp].RY+1)/Ch[lp].zoom/CAMERA_MOVE * turn_q + Pitup);
		if (Ch[lp].Camera.Pitch > PI/2 )
			Ch[lp].Camera.Pitch = (float)(PI/2);
		if(Ch[lp].Camera.Pitch < -PI/2 )
			Ch[lp].Camera.Pitch = -(float)(PI/2);
		Ch[lp].Camera.Yaw = Ch[lp].obj[Ch[lp].NowX].fYaw + Yawup;
		// キャラ回転
		if(Joy[lp].RX+1 > 0){
			Ch[lp].obj[Ch[lp].NowX].fYaw += (float)((Joy[lp].RX+1)/Ch[lp].zoom/CHAR_KAITEN * turn_q);
			if(Ch[lp].obj[Ch[lp].NowX].fYaw > PI)
				Ch[lp].obj[Ch[lp].NowX].fYaw -= (float)(2*PI);
		}
		else if(Joy[lp].RX+1 < 0){
			Ch[lp].obj[Ch[lp].NowX].fYaw += (float)((Joy[lp].RX+1)/Ch[lp].zoom/CHAR_KAITEN * turn_q);
			if(Ch[lp].obj[Ch[lp].NowX].fYaw < -PI)
				Ch[lp].obj[Ch[lp].NowX].fYaw += (float)(2*PI);
		}
	}
}
//--------------------------------//
//  キャラアイコン位置決定、表示  //
//--------------------------------//
void BattleCharaIcon(int lp)
{
	if(Ch[lp].IconFlg==TRUE){
		D3DXVECTOR3 vecPt;
		vecPt = Ch[lp].obj[Ch[lp].NowX].vecPosition;
		vecPt.y += Ch[lp].obj[Ch[lp].NowX].BBox.vecMax.y;
		Ch[lp].Iconobj.vecPosition = vecPt;
		Ch[lp].Iconobj.fYaw = Ch[lp].obj[Ch[lp].NowX].fYaw;
	}
	if(GameMode != TEAM_MODE){ // チーム戦以外
		int hit1=0;

		if(BTN_L3(lp) || Ch[lp].cpu == TRUE){
			D3DXVECTOR3 vecPt;
			vecPt = Ch[lp].obj[Ch[lp].NowX].vecPosition;
			vecPt.y += Ch[lp].obj[Ch[lp].NowX].BBox.vecMax.y-0.1f;
			if(BTN_RU(lp) && Ch[lp].cpu==FALSE || Ch[lp].cpu == TRUE && Ch[lp].cpuIcon[ICON_NICONICO] == TRUE)
				hit1 = BringIcon(ICON_NICONICO, lp, vecPt);
			else if(BTN_RD(lp) && Ch[lp].cpu==FALSE || Ch[lp].cpu == TRUE && Ch[lp].cpuIcon[ICON_IKARI] == TRUE)
				hit1 = BringIcon(ICON_IKARI, lp, vecPt);
			else if(BTN_RL(lp) && Ch[lp].cpu==FALSE || Ch[lp].cpu == TRUE && Ch[lp].cpuIcon[ICON_SIGUMA] == TRUE)
				hit1 = BringIcon(ICON_SIGUMA, lp, vecPt);
			else if(BTN_RR(lp) && Ch[lp].cpu==FALSE || Ch[lp].cpu == TRUE && Ch[lp].cpuIcon[ICON_BIKKURI] == TRUE)
				hit1 = BringIcon(ICON_BIKKURI, lp, vecPt);
		}
		if(!hit1 && Ch[lp].IconFlg == TRUE){
			Ch[lp].IconNum = -1;
			Ch[lp].IconFlg = FALSE;
		}
	}
}
//--------------//
//  ロックオン  //
//--------------//
void BattleLockOn(int lp)
{
	if(Ch[lp].item[1].num == MISSILE && Ch[lp].SelItem == 1){
		for(int j=1; j<=gNinzu; j++){
			if(j==lp || j==Ch[lp].LockOnFlg || Ch[j].alive == FALSE) continue;
			if(RayShoot(&Ch[lp], &Ch[j].obj[Ch[j].NowX], &fDistance, &vIntersect)){
				if(Ch[lp].LockOnNum)
					Ch[Ch[lp].LockOnNum].LockOnFlg = FALSE;
				Ch[j].LockOnFlg = lp; // ロックオンされたやつにしたやつの番号
				Ch[lp].LockOnNum = j; // ロックオンしたやつにされたやつの番号
				break;
			}
		}
	}
	else if(Ch[lp].LockOnNum) // ロックオンの武器でなかったら
		Ch[Ch[lp].LockOnNum].LockOnFlg = 0;

	if(Ch[lp].LockOnFlg) // ロックオンされてたら
		Ch[lp].LockOnObj.vecPosition = Ch[lp].obj->vecPosition;
}
//----------------//
//  アイコン表示  //
//----------------//
int BringIcon(int inum, int lp, D3DXVECTOR3 vecPt)
{
	if(Ch[lp].IconFlg == FALSE){
		if(Ch[lp].cpu == FALSE)
			playASound(&g_SE[SD_ICON], 0, 0L ,TRUE);

		Ch[lp].IconNum = inum;
		ObjectPositionCopy(&Ch[lp].Iconobj, &Ch[lp].obj[Ch[lp].NowX]);
		Ch[lp].Iconobj.vecPosition.y += Ch[lp].obj[Ch[lp].NowX].BBox.vecMax.y/2;
		Ch[lp].IconFlg = TRUE;
	}
	return 1;
}
//------------//
//  打撃攻撃  //
//------------//
void BattleDageki(int lp)
{
	if(Ch[lp].DageTime){ // 打撃中
		Ch[lp].DageTime--;
		Ch[lp].Dageki.vecPosition.y = Ch[lp].obj[Ch[lp].NowX].vecPosition.y + ChDat[Ch[lp].num].dY;
		if(!Ch[lp].DageTime) // 打撃終了
			Ch[lp].Dageki.Visible = FALSE;
	}
	else if(BTN_L2(lp) && Joy[lp].l2Flg==FALSE && DAGEST <= Ch[lp].st && !Ch[lp].Stop){
		// サウンド
		playASound(&g_SE[ChDat[Ch[lp].num].sdAtack],0 , 0L ,TRUE);

		Joy[lp].l2Flg = TRUE; // 打撃開始
		Ch[lp].Dageki.Visible = TRUE;
		Ch[lp].Dageki.vecPosition.x = Ch[lp].obj[Ch[lp].NowX].vecPosition.x - ChDat[Ch[lp].num].dX * sinf(Ch[lp].obj[Ch[lp].NowX].fYaw);
		Ch[lp].Dageki.vecPosition.z = Ch[lp].obj[Ch[lp].NowX].vecPosition.z - ChDat[Ch[lp].num].dX * cosf(Ch[lp].obj[Ch[lp].NowX].fYaw);
		Ch[lp].Dageki.vecPosition.y = Ch[lp].obj[Ch[lp].NowX].vecPosition.y + ChDat[Ch[lp].num].dY;
		Ch[lp].Dageki.fYaw = Ch[lp].obj[Ch[lp].NowX].fYaw;
		Ch[lp].Stop = DSTOP+2;
		Ch[lp].DageTime = DSTOP;
		Ch[lp].st -= DAGEST;
	}
	else if(!BTN_L2(lp))
		Joy[lp].l2Flg = FALSE;
}
//--------------------------------//
//  アイテム使用ボタン押したかな  //
//--------------------------------//
void BattleItemUse(int lp)
{
	if(!Ch[lp].DageTime && !Ch[lp].Stop && !BTN_L3(lp)){
		// 三角
		if(BTN_RU(lp) && Joy[lp].ruFlg==FALSE){
			Joy[lp].ruFlg = TRUE;
			Ch[lp].SelItem = 0;

			ChangeCharaMesh(lp, NORMALSHOT);
		}
		else if(!BTN_RU(lp))
			Joy[lp].ruFlg = FALSE;
		// 丸
		if(BTN_RR(lp) && Joy[lp].rrFlg==FALSE){
			Joy[lp].rrFlg = TRUE;
			Ch[lp].SelItem = 1;
			ChangeCharaMesh(lp, Ch[lp].item[1].num);
		}
		else if(!BTN_RR(lp))
			Joy[lp].rrFlg = FALSE;
		// バツ
		if(BTN_RD(lp) && Joy[lp].rdFlg==FALSE){
			Joy[lp].rdFlg = TRUE;
			Ch[lp].SelItem = 2;
		}
		else if(!BTN_RD(lp))
			Joy[lp].rdFlg = FALSE;
		// 四角
		if(BTN_RL(lp) && Joy[lp].rlFlg==FALSE){
			Joy[lp].rlFlg = TRUE;
			Ch[lp].SelItem = 3;
		}
		else if(!BTN_RL(lp))
			Joy[lp].rlFlg = FALSE;
		if(BTN_R2(lp))
			UseItem(Ch[lp].item[Ch[lp].SelItem].num, lp, Ch[lp].SelItem);
	}
}
//--------------//
//  ズーム処理  //
//--------------//
void BattleZoom(int lp)
{
	if(Ch[lp].SelItem != 1){
		Ch[lp].zoom = 1;
		return;
	}
	if(BTN_R3(lp) && Joy[lp].r3Flg == FALSE){
		Joy[lp].r3Flg = TRUE;
		if(Ch[lp].zoom == 1.0f && Ch[lp].item[1].num)
			Ch[lp].zoom = ItemDat[Ch[lp].item[1].num].zoom;
		else
			Ch[lp].zoom = 1;
	}
	else if(!BTN_R3(lp))
		Joy[lp].r3Flg = FALSE;
}
//--------------------//
//  キャラ位置コピー  //
//--------------------//
int ObjectPositionCopy(THING *p1, THING *p2)
{
	p1->fPitch   = p2->fPitch;
	p1->fYaw     = p2->fYaw;
	p1->matPitch = p2->matPitch;
	p1->matYaw   = p2->matYaw;
	p1->matPosition = p2->matPosition;
	p1->matRotation = p2->matRotation;
	p1->vecPosition = p2->vecPosition;

	return 0;
}
//--------------//
//  キャラ変更  //
//--------------//
int ChangeCharaMesh(int lp, int inum)
{
	if(SubX[Ch[lp].num][ItemDat[inum].ChX][0] == '\0' || ItemDat[inum].ChX == NULL && inum!=NORMALSHOT)
		return -1;
	ObjectPositionCopy(&Ch[lp].obj[ItemDat[inum].ChX], &Ch[lp].obj[Ch[lp].NowX]);
	Ch[lp].NowX = ItemDat[inum].ChX;

	return 0;
}