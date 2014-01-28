//-------------------//
//  選択画面２D描画  //
//-------------------//
int DrawD2DSelect(HWND hWnd)
{
	D3DXVECTOR3 vec3Center(0,0,0);
	D3DXVECTOR3 vec3Position(0,0,0);
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	int lopmax, r1flg, l1flg;
	r1flg = l1flg = FALSE;

	lopmax = (DrawingMode==STARTWINDOW || DrawingMode != GOMOKUWINDOW && KeyMode==TRUE)?1:(!cpuNinzu)?Ninzu:JoyCount;
	// 人数選択画面
	if(DrawingMode == STARTWINDOW)
		OpSelNinzu();
	// キャラクタ選択画面
	else if(DrawingMode == CHARASELECTWINDOW)
		OpSelChara();
	// ステージ選択画面
	else if(DrawingMode == STAGESELECTWINDOW)
		OpSelStage();
	else if(DrawingMode == GOMOKUWINDOW)
		OpGomoku();

	// ポインタ移動
	MovePointer(lopmax);
	// 決定処理 /////////////////////////////////////////////////////
	for(int lp=1; lp<=lopmax; lp++){
		// 人数選択
		if(DrawingMode == STARTWINDOW && lp==1) // 1Pのみ
			IpSelNinzu(lp, hWnd);
		// キャラクター選択
		else if(DrawingMode == CHARASELECTWINDOW)
			IpSelChara(lp);
		// ステージ選択
		else if(DrawingMode == STAGESELECTWINDOW)
			IpSelStage(lp, hWnd, &r1flg, &l1flg);
		else if(DrawingMode == GOMOKUWINDOW)
			IpGomoku(lp);
	}
	pSprite->End();

	return 0;
}
//--------------------//
//  人数選択画面描画  //
//--------------------//
void OpSelNinzu(void)
{
	// 背景
	DrawD2D(0,0,pBackimg);
	// ゲームモード
	for(int i=0; i<4; i++)
		if(GameMode == ROYALE_MODE || GameMode==GOMOKU_MODE && JoyCount>i+1 || i==3)
			DrawD2D(NINZU_X, (float)(NINZU_Y + i*NINZU_K), pSelnin[i]);

	if(GameMode == GOMOKU_MODE)
		DrawD2D(205, 320, pGolog);
}
//--------------------------//
//  人数選択画面の決定処理  //
//--------------------------//
void IpSelNinzu(int lp, HWND hWnd)
{
	// クイックスタート（開発用）
	if(BTN_R3(lp)){
		Ninzu=2;
		cpuNinzu=0;
		gNinzu = Ninzu + cpuNinzu;
		Stage=1;
		Ch[1].Team = 1;
		Ch[1].num=2;
		Ch[2].Team = 2;
		Ch[2].num=4;
		GameStart(hWnd);
	}
	// モードチェンジ
	if(BTN_L3(lp) && Joy[lp].l3Flg == FALSE){
		Joy[lp].l3Flg = TRUE;
		GameMode = (GameMode == ROYALE_MODE)?GOMOKU_MODE:ROYALE_MODE;
	}
	else if(!BTN_L3(lp))
		Joy[lp].l3Flg = FALSE;

	// 通常選択
	int hit;
	hit = 0;
	if(BTN_RR(lp) && Joy[lp].rrFlg == FALSE){
		Joy[lp].rrFlg = TRUE;
		hit = -1;
		if(Joy[lp].x >= NINZU_X && Joy[lp].x <= NINZU_X+NINZU_W){
			for(int i=0; i<3; i++){
				if(Joy[lp].y>=NINZU_Y+NINZU_K*i && Joy[lp].y<=NINZU_Y+NINZU_K*i+NINZU_H && (GameMode==ROYALE_MODE || GameMode==GOMOKU_MODE && JoyCount>i+1)){
					hit = 1;
					SelectResultNinzu(i+2);
				}
			}
			if(Joy[lp].y>=NINZU_Y+NINZU_K*3 && Joy[lp].y<=NINZU_Y+NINZU_K*3+NINZU_H){
				SendMessage(hWnd, WM_DESTROY, 0, 0);
				hit = 1;
			}
		}
	}
	else if(!BTN_RR(lp))
			Joy[lp].rrFlg = FALSE;
	// サウンド
	if(hit == 1)
		playASound(&g_SE[SD_ENTER], 0, 0L ,TRUE);
	else if(hit == -1)
		playASound(&g_SE[SD_CLICK1], 0, 0L, TRUE);
}
//------------------------//
//  どうぶつ選択画面描画  //
//------------------------//
void OpSelChara(void)
{
	DrawD2D(0, 0, pBackimg);
	for(int i=0; i<8; i++) // キャラアイコン
		DrawD2D((float)(CHAR_X + (i%4)*CHAR_K),(float)((i>3)?CHAR_Y2:CHAR_Y1), pSelchar[i]);
	for(int i=1; i<=4; i++) // チーム色
		DrawD2D(TCOL_X, (float)(CHAR_Y1 + (i-1)*TCOL_K), pTeamCol[i]);
	// 選択キャラを上部に表示
	for(int i=1; i<=Ninzu+cpuNinzu; i++){
		if(Ch[i].num){
			float chN[8] = {
				(float)ChDat[Ch[i].num].maxhp,
				(float)ChDat[Ch[i].num].nStmin,
				(float)ChDat[Ch[i].num].nAtack,
				(float)ChDat[Ch[i].num].nGard,
				ChDat[Ch[i].num].nSpeed,
				ChDat[Ch[i].num].nDash,
				ChDat[Ch[i].num].nJump,
				ChDat[Ch[i].num].nTurn
			};
			DrawD2D((float)(SELCHAR_X + (i-1)*SELCHAR_K), SELCHAR_Y, pSelcharX[Ch[i].num]);
			// 能力バー
			DrawD2D((float)(NHEADBAR_X + (i-1)*SELCHAR_K), NHEADBAR_Y, pnHead);
			for(int j=0; j<8; j++){
				D3DXVECTOR3 vec3Center(0,0,0);
				D3DXVECTOR3 vec3Position(0,0,0);
				RECT rc={0,0,0,NBAR_H};
				rc.right = (LONG)(chN[j]/maxN[j] * NBAR_W);
				
				vec3Position.x = (float)(SELCHARBAR_X + (i-1)*SELCHAR_K);
				vec3Position.y = (float)(SELCHARBAR_Y + j*SELCHARBAR_K);
				pSprite->Draw(pnBar, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255,255,255,255));
			}
			
		}
		else //　未選択
			DrawD2D((float)(SELCHAR_X + (i-1)*SELCHAR_K), SELCHAR_Y, pSelcharX[0]);
		
		if(Ch[i].cpu == TRUE || i>Ninzu) // CPUマーク
			DrawD2D((float)(SELCHAR_X + (i-1)*SELCHAR_K) + 15 , SELCHAR_Y + 25, pCpu);
		// チーム枠
		DrawD2D((float)(SELCHAR_X + (i-1)*SELCHAR_K) , SELCHAR_Y, pTeamWaku[Ch[i].Team]);
	}
	// 戻る
	DrawD2D(RETURN_X , RETURN_Y, pReturn);
	// 全員が選択終わったら進む
	if(chselcnt == Ninzu+cpuNinzu)
		DrawD2D(ENTER_X , ENTER_Y, pEnter);
}
//------------------------//
//  どうぶつ選択決定処理  //
//------------------------//
void IpSelChara(int lp)
{
	int hit = -1;

	if(BTN_RR(lp) && Joy[lp].rrFlg==FALSE){
		Joy[lp].rrFlg = TRUE;
		hit = SelectCharaPos(lp, RRBTN);

		// 戻る
		if(Joy[lp].x>=RETURN_X && Joy[lp].x<=RETURN_X+RETURN_W && Joy[lp].y>=RETURN_Y && Joy[lp].y<=RETURN_Y+RETURN_H)
			hit = SelectChara(SELRETURN, SELRETURN, SELRETURN) + 1;
		// 進む
		if(Joy[lp].x>=ENTER_X && Joy[lp].x<=ENTER_X+ENTER_W && Joy[lp].y>=ENTER_Y && Joy[lp].y<=ENTER_Y+ENTER_H && chselcnt==Ninzu+cpuNinzu)
			hit = SelectChara(SELENTER, SELENTER, SELENTER) + 2;
	}
	else if(!BTN_RR(lp))
		Joy[lp].rrFlg = FALSE;
	// １Pのみコンピュータキャラ選択
	if(lp == 1){ 
		// 2P
		if(BTN_RD(lp) && Joy[lp].rdFlg==FALSE){
		Joy[lp].rdFlg = TRUE;
			hit = SelectCharaPos(lp, RDBTN);
		}
		else if(!BTN_RD(lp))
			Joy[lp].rdFlg = FALSE;
		// 3P
		if(BTN_RL(lp) && Joy[lp].rlFlg==FALSE){
			Joy[lp].rlFlg = TRUE;
			hit = SelectCharaPos(lp, RLBTN);
		}
		else if(!BTN_RL(lp))
			Joy[lp].rlFlg = FALSE;
		// 4P
		if(BTN_RU(lp) && Joy[lp].ruFlg==FALSE){
			Joy[lp].ruFlg = TRUE;
			hit = SelectCharaPos(lp, RUBTN);
		}
		else if(!BTN_RU(lp))
			Joy[lp].ruFlg = FALSE;
	}
	// 進む
	if(BTN_START(lp) && chselcnt==Ninzu+cpuNinzu){
		SelectChara(SELENTER, SELENTER, SELENTER);
		playASound(&g_SE[SD_ENTER], 0, 0L ,TRUE);
	}
	else{
		// サウンド
		if(hit == 1)
			playASound(&g_SE[SD_CLICK2], 0, 0L ,TRUE);
		else if(hit == 2)
			playASound(&g_SE[SD_RETURN], 0 , 0L ,TRUE);
		else if(hit == 3)
			playASound(&g_SE[SD_ENTER], 0 , 0L ,TRUE);
		else if(hit == 0)
			playASound(&g_SE[SD_CLICK1], 0, 0L, TRUE);
	}
}
//------------------------//
//  ステージ選択画面描画  //
//------------------------//
void OpSelStage(void)
{
	D3DXVECTOR3 vec3Center(0,0,0);
	D3DXVECTOR3 vec3Position(0,0,0);
	// ステージ選択済みなら
	if(Stage){
		DrawD2D(SELSTAGE_X, SELSTAGE_Y, pBackStage); // 選択済みステージ表示
		DrawD2D(ENTER_X, ENTER_Y, pEnter); // 決定ボタン
	}
	// ステージアイコン
	for(int i=0; i<STAGECNT; i++){
		float xpt;
		xpt = (float)(STAGE_X + i*STAGE_K + StageMove);
		if(xpt+STAGE_W < 0 || xpt>width)
			continue;
		DrawD2D(xpt, STAGE_Y, pSelstage[i]);
	}
	
	DrawD2D(STAGERAND_X, STAGERAND_Y, pStageR);// ランダム選択
	DrawD2D(RETURN_X, RETURN_Y, pReturn);// 戻る
	// 矢印
	DrawD2D(LEFT_X, LEFT_Y, pLeft);
	DrawD2D(RIGHT_X, RIGHT_Y, pRight);
}
//--------------------//
//  ステージ選択処理  //
//--------------------//
void IpSelStage(int lp, HWND hWnd, int *r1flg, int *l1flg)
{
	// 矢印
	if((Joy[lp].y>=LEFT_Y && Joy[lp].y<=LEFT_Y+LEFTRIGHT_H && Joy[lp].x >= LEFT_X && Joy[lp].x <= LEFT_X+LEFTRIGHT_W && BTN_RR(lp) || BTN_L1(lp) && !(*l1flg)) && StageMove < 0){
		playASound(&g_SE[SD_MOVE], 0, 0L ,TRUE);
		*l1flg = TRUE;
		StageMove += STAGEMOVEDIST;
	}
	else if((Joy[lp].y>=RIGHT_Y && Joy[lp].y<=RIGHT_Y+LEFTRIGHT_H && Joy[lp].x >= RIGHT_X && Joy[lp].x <= RIGHT_X+LEFTRIGHT_W && BTN_RR(lp) || BTN_R1(lp)&&!(*r1flg)) && -StageMove<STAGE_K*(STAGECNT-5)){
		playASound(&g_SE[SD_MOVE], 0, 0L ,TRUE);
		*r1flg = TRUE;
		StageMove -= STAGEMOVEDIST;
	}
	if(BTN_RR(lp) && Joy[lp].rrFlg==FALSE){
		int hit=0;
		Joy[lp].rrFlg = TRUE;
		// ステージクリック
		if(Joy[lp].y>=STAGE_Y && Joy[lp].y<=STAGE_Y+STAGE_H)
			for(int i=0; i<STAGECNT; i++)
				if(Joy[lp].x>=STAGE_X+STAGE_K*i+StageMove && Joy[lp].x<=STAGE_X+STAGE_K*i+STAGE_W+StageMove&&Stage!=i+1)
					StageDec(&hit, i);
		if(Joy[lp].y>=STAGERAND_Y && Joy[lp].y<=STAGERAND_Y+STAGE_H && Joy[lp].x>=STAGERAND_X && Joy[lp].x<=STAGERAND_X+STAGE_W)
				StageDec(&hit, rand()%STAGECNT);
		// 戻る
		if(Joy[lp].x>=RETURN_X&&Joy[lp].x<=RETURN_X+RETURN_W && Joy[lp].y>=RETURN_Y&&Joy[lp].y<=RETURN_Y+RETURN_H){
			hit = 2;
			if(Stage)
				SAFE_RELEASE(pBackStage);
			ChangeDrawingMode(CHARASELECTWINDOW, Ninzu, NULL);
		}
		// 進む
		if(Joy[lp].x>=ENTER_X && Joy[lp].x<=ENTER_X+ENTER_W && Joy[lp].y>=ENTER_Y && Joy[lp].y<=ENTER_Y+ENTER_H && Stage){
			if(Stage)
				SAFE_RELEASE(pBackStage);
			GameStart(hWnd);
		}
		// サウンド
		if(hit==1)
			playASound(&g_SE[SD_CLICK2], 0, 0L ,TRUE);
		else if(hit == 2)
			playASound(&g_SE[SD_RETURN], 0 , 0L ,TRUE);
		else if(hit == 0)
			playASound(&g_SE[SD_CLICK1], 0, 0L, TRUE);
	}
	else if(!BTN_RR(lp))
		Joy[lp].rrFlg = FALSE;
	// 進む
	if(BTN_START(lp) && Stage)
		GameStart(hWnd);
}
//--------------------//
//  ステージ一時選択  //
//--------------------//
int StageDec(int *hit, int i)
{
	if(Stage)
		SAFE_RELEASE(pBackStage);
	TextureFromFile(StageFile[i].img, &pBackStage);
	Stage = i+1;
	*hit = 1;
	
	return 1;
}
//----------------//
//  五目画面描画  //
//----------------//
void OpGomoku(void)
{
	DrawD2D(0, 0, pBackimg);
	DrawD2D(627, 69, pIsi[putTurn]);

	for(int i=0; i<19; i++)
		for(int j=0; j<19; j++)
			if(Goban[i][j])
				DrawD2D((float)(j*26+14), (float)(i*26+14), pIsi[Goban[i][j]]);
	// 勝者
	if(goWin)
		DrawD2D(627, 154, pIsi[goWin]);
}
//----------------//
//  五目選択処理  //
//----------------//
void IpGomoku(int lp)
{
	D3DXVECTOR3 vec3Center(0,0,0);
	D3DXVECTOR3 vec3Position(0,0,0);

	if(Joy[lp].y >= 525 && Joy[lp].y < 585 && Joy[lp].x >= 650 && Joy[lp].x < 790 && BTN_RR(lp) && (goWin || !goWin && putTurn == lp)) // 戻る
		ChangeDrawingMode(STARTWINDOW, Ninzu, NULL);

	if(Joy[lp].y > 505 || Joy[lp].x > 505 || goWin || putTurn != lp)
		return;

	vec3Position.x = (float)(((Joy[lp].x-14)/26+1)*26-12);
	vec3Position.y = (float)(((Joy[lp].y-14)/26+1)*26-12);
	pSprite->Draw(pIsi[lp], NULL, &vec3Center, &vec3Position, D3DCOLOR_ARGB(64,255,255,255)); // 石半透明

	if(BTN_RR(lp) && Joy[lp].rrFlg == FALSE){
		Joy[lp].rrFlg = TRUE;
		int x = (Joy[lp].x-14)/26;
		int y = (Joy[lp].y-14)/26;
		if(!Goban[y][x]){ // 未入力
			playASound(&g_SE[SD_CLICK1], 0, 0L, TRUE);

			Goban[y][x] = lp;
			putTurn++;
			if(putTurn > Ninzu)
				putTurn = 1;
			// 連珠判定
			for(x=0; x<19; x++)
				for(y=0; y<19; y++)
					if(Goban[y][x] == lp)
						GomokuSyouhai(lp, x, y);
			if(!goWin){ // 引き分け判定
				putCnt++;
				if(putCnt >= 19*19)
					goWin = 5;
			}
			if(goWin) // 勝利音
				playASound(&g_SE[SD_DEATH], 0, 0L, TRUE);
		}
	}
	else if(!BTN_RR(lp))
		Joy[lp].rrFlg = FALSE;
}
//----------------//
//  五目連珠判定  //
//----------------//
void GomokuSyouhai(int lp, int x, int y)
{
	if(y >= 4){ // 左上　上　右上
		// 上
		if(Goban[y-1][x] == lp)
			if(Goban[y-2][x] == lp)
				if(Goban[y-3][x] == lp)
					if(Goban[y-4][x] == lp)
						goWin = lp;
		if(x >= 4) // 左上
			if(Goban[y-1][x-1] == lp)
				if(Goban[y-2][x-2] == lp)
					if(Goban[y-3][x-3] == lp)
						if(Goban[y-4][x-4] == lp)
							goWin = lp;
		if(x < 15) // 右上
			if(Goban[y-1][x+1] == lp)
				if(Goban[y-2][x+2] == lp)
					if(Goban[y-3][x+3] == lp)
						if(Goban[y-4][x+4] == lp)
							goWin = lp;
	}
	if(x >= 4) // 左
		if(Goban[y][x-1] == lp)
			if(Goban[y][x-2] == lp)
				if(Goban[y][x-3] == lp)
					if(Goban[y][x-4] == lp)
						goWin = lp;
	if(x < 15) // 右
		if(Goban[y][x+1] == lp)
			if(Goban[y][x+2] == lp)
				if(Goban[y][x+3] == lp)
					if(Goban[y][x+4] == lp)
						goWin = lp;
	if(y < 15){ // 右下　下　左下
		// 下
		if(Goban[y+1][x] == lp)
			if(Goban[y+2][x] == lp)
				if(Goban[y+3][x] == lp)
					if(Goban[y+4][x] == lp)
						goWin = lp;
		if(x < 15) // 右下
			if(Goban[y+1][x+1] == lp)
				if(Goban[y+2][x+2] == lp)
					if(Goban[y+3][x+3] == lp)
						if(Goban[y+4][x+4] == lp)
							goWin = lp;
		if(x >= 4) // 左下
			if(Goban[y+1][x-1] == lp)
				if(Goban[y+2][x-2] == lp)
					if(Goban[y+3][x-3] == lp)
						if(Goban[y+4][x-4] == lp)
							goWin = lp;
	}
}
//----------------//
//  キャラ位置で  //
//----------------//
int SelectCharaPos(int lp, int btn)
{
	if(Joy[lp].y>=CHAR_Y1 && Joy[lp].y<=CHAR_Y1+CHAR_H){
		if(Joy[lp].x>=CHAR_X && Joy[lp].x<=CHAR_X+CHAR_W)
			return SelectChara(lp, 1, btn);
		else if(Joy[lp].x>=CHAR_X+CHAR_K && Joy[lp].x<=CHAR_X+CHAR_K+CHAR_W)
			return SelectChara(lp, 2, btn);
		else if(Joy[lp].x>=CHAR_X+CHAR_K*2 && Joy[lp].x<=CHAR_X+CHAR_K*2+CHAR_W)
			return SelectChara(lp, 3, btn);
		else if(Joy[lp].x>=CHAR_X+CHAR_K*3 && Joy[lp].x<=CHAR_X+CHAR_K*3+CHAR_W)
			return SelectChara(lp, 4, btn);
	}
	else if(Joy[lp].y>=CHAR_Y2 && Joy[lp].y<=CHAR_Y2+CHAR_H){
		if(Joy[lp].x>=CHAR_X && Joy[lp].x<=CHAR_X+CHAR_W)
			return SelectChara(lp, 5, btn);
		else if(Joy[lp].x>=CHAR_X+CHAR_K && Joy[lp].x<=CHAR_X+CHAR_K+CHAR_W)
			return SelectChara(lp, 6, btn);
		else if(Joy[lp].x>=CHAR_X+CHAR_K*2 && Joy[lp].x<=CHAR_X+CHAR_K*2+CHAR_W)
			return SelectChara(lp, 7, btn);
		else if(Joy[lp].x>=CHAR_X+CHAR_K*3 && Joy[lp].x<=CHAR_X+CHAR_K*3+CHAR_W)
			return SelectChara(lp, 8, btn);
	}
	// チーム色決定
	if(Joy[lp].x>=TCOL_X && Joy[lp].x<=TCOL_X+TCOL_W)
		for(int i=0; i<4; i++)
			if(Joy[lp].y>=CHAR_Y1+i*TCOL_K && Joy[lp].y<=CHAR_Y1+i*TCOL_K+TCOL_H)
				return SelectTeam(lp, i+1, btn);
	
	return 0;
}
//------------------//
//  使用キャラ選択  //
//------------------//
int SelectChara(int lp, int cnum, int btn)
{
	// 戻る処理
	if(lp==SELRETURN && cnum==SELRETURN)
		return ChangeDrawingMode(STARTWINDOW, Ninzu+cpuNinzu, NULL);
	// 進む処理
	else if(lp==SELENTER && cnum==SELENTER)
		return ChangeDrawingMode(STAGESELECTWINDOW, Ninzu+cpuNinzu, NULL);
	// 人数より多いCPUの選択
	if(btn > Ninzu+cpuNinzu)
		return FALSE;

	// 未選択の場合
	if(!Ch[(lp==1)?btn:lp].num)
		chselcnt++;

	if(btn != RRBTN) // CPU
		Ch[btn].cpu = TRUE;
	else
		Ch[lp].cpu = FALSE;
	Ch[(lp==1)?btn:lp].num = cnum;

	return 1;
}
//------------------//
//  チーム(班)選択  //
//------------------//
int SelectTeam(int lp, int tnum, int btn)
{
	// 人数より多いCPUの選択 || 全員同一チーム禁止
	if(btn > Ninzu+cpuNinzu || TeamCnt[tnum]+1 == cpuNinzu+Ninzu)
		return FALSE;
	if(btn != RRBTN){ // CPU
		TeamCnt[Ch[btn].Team]--;
		Ch[btn].Team = tnum;
	}
	else{
		TeamCnt[Ch[lp].Team]--;
		Ch[lp].Team = tnum;
	}
	TeamCnt[tnum]++;

	return 1;
}
//----------------//
//  ポインタ移動  //
//----------------//
void MovePointer(int lopmax)
{
	D3DXVECTOR3 vec3Center(0,0,0);
	D3DXVECTOR3 vec3Position(0,0,0);

	for(int i=1; i<=lopmax; i++){
		Joy[i].x += Joy[i].LX / ((DrawingMode==MENUWINDOW)?15:8);
		Joy[i].y += Joy[i].LY / ((DrawingMode==MENUWINDOW)?15:8);
		if(Joy[i].x < 0)
			Joy[i].x = 0;
		else if(Joy[i].x > width-2)
			Joy[i].x = int(width-2);
		if(Joy[i].y < 0)
			Joy[i].y = 0;
		else if(Joy[i].y > height-4)
			Joy[i].y = (int)(height-4);

		vec3Position.x = (float)Joy[i].x;
		vec3Position.y = (float)Joy[i].y;
		pSprite->Draw(pPointer[i], NULL, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255,255,255,255));
	}
}
//----------------------------//
//  スタートボタンウィンドウ  //
//----------------------------//
int DrawD2DSelectSt(HWND hWnd)
{
	D3DXVECTOR3 vec3Center(0,0,0);
	D3DXVECTOR3 vec3Position(0,0,0);
	// 表示 ////////////////////////
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	vec3Position.x = MENU_X;
	vec3Position.y = MENU_Y;
	if(DrawingMode == MENUWINDOW) // セレクトメニュ
		pSprite->Draw(pStartBox, NULL, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255,255,255,255));
	else{ // リザルトメニュ
		pSprite->Draw(pResultBox, NULL, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255,255,255,255));
		// 順位表示
		if(GameMode == ROYALE_MODE){ // 個人戦
			for(int rank=1; rank<=gNinzu; rank++){
				char buf[256];
				wsprintf(buf, "第 %d 位", rank);
				RenderString(buf, 350, 150+(rank-1)*100);
				for(int c=1; c<=gNinzu; c++){ // 画像表示
					if(Ch[c].rank == rank){
						DrawD2D(450.0f, 120.0f+(rank-1)*100.0f, pSelcharX[Ch[c].num]);
						DrawD2D(450.0f, 120.0f+(rank-1)*100.0f, pTeamWaku[Ch[c].Team]);
					}
				}
			}
		}
		else if(GameMode == TEAM_MODE){ // チーム戦闘
			int rNin=0, resNin;
			for(int rank=1; rank<=gNinzu; rank++){
				char buf[256];
				wsprintf(buf, "第 %d 位", rank);
				RenderString(buf, 350, 150+(rank-1)*100);
				
				resNin = 0;
				for(int c=1; c<=gNinzu; c++){ // 画像表示
					if(Ch[c].rank == rank){
						DrawD2D(450.0f+resNin*100, 120.0f+(rank-1)*100.0f, pSelcharX[Ch[c].num]);
						DrawD2D(450.0f+resNin*100, 120.0f+(rank-1)*100.0f, pTeamWaku[Ch[c].Team]);
						resNin++;
					}
				}
				rNin += resNin;
				if(rNin >= gNinzu)
					break;
			}
		}
	}
	MovePointer(Ninzu);
	pSprite->End();
	// 決定判定 ///////////////
	for(int lp=1; lp<=Ninzu; lp++){
		int hit = 0;
		if(BTN_RR(lp) && Joy[lp].rrFlg == FALSE){
			Joy[lp].rrFlg = TRUE;
			if(Joy[lp].x>=MENU_X && Joy[lp].x<=MENU_X+MENU_W){
				if(Joy[lp].y>=MENU_Y && Joy[lp].y<MENU_Y+MENU_K){
					if(DrawingMode == MENUWINDOW)
						hit = ChangeDrawingMode(BATTLEWINDOW, Ninzu+cpuNinzu, hWnd);
					else if(DrawingMode == RESULTWINDOW)
						GameStart(hWnd);
				}
				else if(Joy[lp].y>=MENU_Y+MENU_K && Joy[lp].y<MENU_Y+MENU_K*2)
					hit = ChangeDrawingMode(STARTWINDOW, Ninzu+cpuNinzu, hWnd);
				else if(Joy[lp].y>=MENU_Y+MENU_K*2 && Joy[lp].y<MENU_Y+MENU_K*3)
					hit = ChangeDrawingMode(CHARASELECTWINDOW, Ninzu+cpuNinzu, hWnd);
				else if(Joy[lp].y>=MENU_Y+MENU_K*3 && Joy[lp].y<MENU_Y+MENU_K*4)
					hit = ChangeDrawingMode(STAGESELECTWINDOW, Ninzu+cpuNinzu, hWnd);
				else if(Joy[lp].y>=MENU_Y+MENU_K*4 && Joy[lp].y<MENU_Y+MENU_K*5){
					hit = 2;
					bEnd = TRUE;
				}
			}
			// サウンド
			if(hit==1)
				playASound(&g_SE[SD_CLICK2], 0, 0L ,TRUE);
			else if(hit==2)
				playASound(&g_SE[SD_RETURN], 0, 0L ,TRUE);
			else
				playASound(&g_SE[SD_CLICK1], 0, 0L, TRUE);
		}
		else if(!BTN_RR(lp))
			Joy[lp].rrFlg = FALSE;
	}
	return 0;
}
//------------------//
//  ゲームスタート  //
//------------------//
int GameStart(HWND hWnd)
{
	// サウンド
	playASound(&g_SE[SD_START], 0, 0L ,TRUE);
	
	// チーム戦闘かどうか
	GameMode = ROYALE_MODE;
	for(int i=1; i<=4; i++) // チーム人数コピー
		TeamNowCnt[i] = TeamCnt[i];
	TeamKazu = 0;
	for(int i=1; i<=4; i++){
		if(TeamNowCnt[i]) // チーム数取得
			TeamKazu++;
		if(TeamNowCnt[i] > 1) // チームモード決定
			GameMode = TEAM_MODE;
	}
	// キャラクタステータス読み込み
	for(int i=1; i<=Ninzu+cpuNinzu; i++){
		for(int j=0; j<Ch[i].Xcnt; j++)
			if(Ch[i].obj[j].Mesh.dwNumMaterials)
				ReleaseObject(&Ch[i].obj[j]);
		if(Ch[i].Dageki.Mesh.dwNumMaterials)
			ReleaseObject(&Ch[i].Dageki);
		// キャラメッシュ読み込み
		Ch[i].Xcnt = 0;
		for(int j=0; j<SUBXCNT; j++){
			if(SubX[Ch[i].num][j][0] != '\0'){
				char buf[256];
				wsprintf(buf, "%s%s", CharXDir, SubX[Ch[i].num][j]);
				InitThing(&Ch[i].obj[Ch[i].Xcnt++], buf, &StartPt[Stage-1][i-1], TRUE, TYPE_CHAR);
			}
		}
		// 打撃メッシュ
		InitThing(&Ch[i].Dageki, ChDat[Ch[i].num].dAtack, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), FALSE, TYPE_DAGEKI);	
		// チームアイコンメッシュ
		if(Ch[i].Iconobj.Mesh.dwNumMaterials)
			ReleaseObject(&Ch[i].Iconobj);
		
		if(GameMode==TEAM_MODE){
			char fname[256];
			wsprintf(fname, "./X/icon/teamC%d.x", Ch[i].Team);		
			InitThing(&Ch[i].Iconobj, fname, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), FALSE, TYPE_ICON);
			Ch[i].IconFlg=TRUE;
		}
		else
			Ch[i].IconFlg = FALSE;

		Ch[i].SelItem = 0;
		Ch[i].alive = TRUE;
		Ch[i].hp = Ch[i].maxhp = ChDat[Ch[i].num].maxhp;
		Ch[i].st = Ch[i].maxst = ChDat[Ch[i].num].nStmin;
		Ch[i].a = FIRST_A * ChDat[Ch[i].num].nJump;
		Ch[i].g = FIRST_G;
		Ch[i].gs = 0;
		Ch[i].dmg = 0;
		Ch[i].Stop = 0;
		Ch[i].Visible = TRUE;
		Ch[i].item[0].num = NORMALSHOT;
		Ch[i].item[1].num = Ch[i].item[2].num = Ch[i].item[3].num = NULL;
		for(int j=0; j<ITEMMAX; j++){
			Ch[i].item[j].rlTimer = 0;
			Ch[i].item[j].Timer = 0;
			Ch[i].cpuIcon[j] = 0;
		}
		Ch[i].item[0].tama = Ch[i].item[0].maxtama = ItemDat[NORMALSHOT].tama;
		Ch[i].item[0].rlCnt = ItemDat[NORMALSHOT].rlCount;
		Ch[i].AtkUp	= 0;
		Ch[i].DefUp = 0;
		Ch[i].JumpUp = 0;
		Ch[i].JpFlg = JEND;
		Ch[i].SpdUp = 0;
		Ch[i].TurnUp = 0;
		Ch[i].NowX = 0;
		Ch[i].Mfloat = 0;
		Ch[i].rank = 0;
		Ch[i].Ffloat = 0;
		Ch[i].Mfloat = 0;
		Ch[i].zoom = 1;
		Ch[i].Camera.Pitch = 0.5f;
		Ch[i].IconNum = -1;
		Ch[i].LockOnFlg = 0;
		Ch[i].LockOnNum = 0;
		Ch[i].LockOnObj.type = TYPE_SITE;
		Joy[i].VibFlg = FALSE;
		Joy[i].VibTime = 0;
		if(Ch[i].cpu==TRUE){
			Joy[i].But = 0x0000;
			Joy[i].RX = -1;
			Joy[i].RY = -1;
			Joy[i].LX = -1;
			Joy[i].LY = -1;
		}
		// 弾初期化
		for(int j=0; j<BULLETMAX; j++)
			Bullet[i][j].num = 0;
		// 爆風初期化
		for(int j=0; j<BLASTMAX; j++){
			Blast[i][j].obj.Sphere.fRadius = NULL;
			Blast[i][j].num = 0;
		}
	}
	wsprintf(debug1, "");
	wsprintf(debug2, "");
	wsprintf(debug3, "");
	// プレイヤ人数決定
	int hit=0;
	gNinzu = Ninzu+cpuNinzu;
	for(int i=1; i<=gNinzu; i++){
		if(Ch[i].cpu == FALSE){ // プレイヤなら
			hit++;
			Chpt[hit] = &Ch[i];
		}
	}
	Ninzu = hit;
	cpuNinzu = gNinzu - Ninzu;

	AliveCnt = gNinzu;
	// ステージ読み込み
	ChangeStage(Stage);
	g_aspect = (Ninzu==2)? width/(height/2) : width/height;
	// 枠読み込み
	if(DrawingMode != RESULTWINDOW)
		ReadFrame(Ninzu);

	ChangeDrawingMode(BATTLEWINDOW, Ninzu, hWnd);

	return 0;
}
//----------------//
//  対戦人数決定  //
//----------------//
int SelectResultNinzu(int nin)
{
	if(JoyCount < nin && GameMode == ROYALE_MODE){
		cpuNinzu = nin - ((KeyMode==TRUE)?1:JoyCount); // コンピュータ数
		Ninzu = nin - cpuNinzu;    // プレイヤー数
	}
	else{
		Ninzu = nin;
		cpuNinzu = 0;
	}

	if(GameMode == ROYALE_MODE)
		ChangeDrawingMode(CHARASELECTWINDOW, Ninzu, NULL);
	else
		ChangeDrawingMode(GOMOKUWINDOW, Ninzu, NULL);

	return 0;
}
//----------------//
//  描画画面変更  //
//----------------//
int ChangeDrawingMode(int mode, int Nin, HWND hWnd)
{
	int i;
	char fname[256];
	
	if((DrawingMode == MENUWINDOW || DrawingMode == RESULTWINDOW) && mode != BATTLEWINDOW)
		SAFE_RELEASE(pBar);

	switch(mode){
		case STARTWINDOW:
			// ２次元解放
			ReleaseGomokuWindow();
			ReleaseCharaSelectWindow();
			if(DrawingMode == RESULTWINDOW)
				ReleaseResultWindow();
			if(DrawingMode == MENUWINDOW || DrawingMode == RESULTWINDOW)
				SAFE_RELEASE(pBar);
			if(!DrawingMode)
				SetTimer(hWnd, MOVETIMER, TIMERINTERVAL_MOV, NULL);
			// ２次元読み込み
			TextureFromFile("./pic/bgimage.png", &pBackimg);  // トップロゴ
			TextureFromFile("./pic/2play.png", &pSelnin[0]);
			TextureFromFile("./pic/3play.png", &pSelnin[1]);
			TextureFromFile("./pic/4play.png", &pSelnin[2]);
			TextureFromFile("./pic/end.png",   &pSelnin[3]);

			for(i=1; i<=Nin; i++)
				Ch[i].num = 0;
			Ninzu = 0;
			chselcnt=0;
			// BGMの再生開始
			playAMusic(&g_BGM[1]);
			break;
		case CHARASELECTWINDOW:
			// ２次元解放
			ReleaseStageSelectWindow();
			if(DrawingMode == RESULTWINDOW)
				ReleaseResultWindow();
			if(DrawingMode == MENUWINDOW || DrawingMode == RESULTWINDOW)
				SAFE_RELEASE(pBar);
			ReleaseStartWindow();
			// ２次元読み込み
			TextureFromFile("./pic/bgimage2.png", &pBackimg);
			// キャラ画像
			for(i=0; i<9; i++){
				if(i<8){
					wsprintf(fname, "./pic/selchar%d.png", i+1);
					TextureFromFile(fname, &pSelchar[i]);
				}
				wsprintf(fname, "./pic/selch%d.png", i);
				TextureFromFile(fname, &pSelcharX[i]);
			}
			// チーム色と枠
			for(i=1; i<=4; i++){
				wsprintf(fname, "./pic/teamC%d.png", i);
				TextureFromFile(fname, &pTeamCol[i]);
				wsprintf(fname, "./pic/teamwakuC%d.png", i);
				TextureFromFile(fname, &pTeamWaku[i]);
				// チーム色振り分け
				if(DrawingMode == STARTWINDOW){
					if(i > Ninzu + cpuNinzu)
						TeamCnt[i] = 0;
					else{
						Ch[i].Team = i;
						TeamCnt[i] = 1;
					}
				}
			}
			// BGM再生
			playAMusic(&g_BGM[3]);
			Stage = 0;
			break;
		case STAGESELECTWINDOW:
			// ２次元解放
			ReleaseCharaSelectWindow();
			if(DrawingMode == RESULTWINDOW)
				ReleaseResultWindow();
			if(DrawingMode == MENUWINDOW || DrawingMode == RESULTWINDOW)
				SAFE_RELEASE(pBar);
			Stage=0;
			// ステージ選択アイコン読み込み
			for(i=0; i<STAGECNT; i++){
				wsprintf(fname, "./pic/selstage%d.png", i+1);
				TextureFromFile(fname, &pSelstage[i]);
			}
			TextureFromFile("./pic/selstageR.png",&pStageR);   // ランダム選択
			TextureFromFile("./pic/left.png",     &pLeft);     // 左矢印
			TextureFromFile("./pic/right.png",    &pRight);    // 右矢印
			// BGM再生
			playAMusic(&g_BGM[4]);
			break;
		case BATTLEWINDOW:
			ReleaseStartWindow();
			if(DrawingMode == RESULTWINDOW)
				ReleaseResultWindow();
			// ２次元開放
			ReleaseStageSelectWindow();
			
			TimerFlg = SETTIMER;
			if(isPlayingAMusic( &g_BGM[2] ) == S_OK)
				playAMusic(&g_BGM[2]);
			break;
		case MENUWINDOW:
		case RESULTWINDOW:
			playASound(&g_SE[SD_MENU], 0, 0L ,TRUE);
			
			TimerFlg = KILLTIMER;
			for(i=1; i<=Nin; i++){
				Joy[i].x = 100;
				Joy[i].y = 100;
			}
			// 結果画面なら
			if(mode == RESULTWINDOW){ // キャラ画像
				for(i=1; i<=8; i++){
					wsprintf(fname, "./pic/selch%d.png", i);
					TextureFromFile(fname, &pSelcharX[i]);
				}
				// チーム枠
				for(i=1; i<=4; i++){
					wsprintf(fname, "./pic/teamwakuC%d.png", i);
					TextureFromFile(fname, &pTeamWaku[i]);
				}
			}
			break;
		case GOMOKUWINDOW:
			ReleaseStartWindow();
			TextureFromFile("./pic/goban.png", &pBackimg);
			for(int i=1; i<=5; i++){
				wsprintf(fname, "./pic/isi%d.png", i);
				TextureFromFile(fname, &pIsi[i]);
			}
			for(int i=0; i<19; i++)
				for(int j=0; j<19; j++)
					Goban[i][j] = 0;
			putTurn = 1;
			putCnt = 0;
			goWin = 0;
			break;
	}
	DrawingMode = mode;

	return 1;
}
//--------------------//
//  起動画面２Ｄ解放  //
//--------------------//
int ReleaseStartWindow(void)
{
	if(DrawingMode == STARTWINDOW){
		SAFE_RELEASE(pBackimg);
		for(int i=0; i<4; i++)
			SAFE_RELEASE(pSelnin[i]);
	}

	return 0;
}
//---------------------------//
//  キャラ選択画面の２D解放  //
//---------------------------//
int ReleaseCharaSelectWindow(void)
{
	int i;

	if(DrawingMode == CHARASELECTWINDOW){
		SAFE_RELEASE(pBackimg);
		for(i=0; i<9; i++){
			if(pSelchar[i] && i<8)
				SAFE_RELEASE(pSelchar[i]);
			if(pSelcharX[i])
				SAFE_RELEASE(pSelcharX[i]);
		}
		// チーム枠
		for(i=1; i<=4; i++){
			SAFE_RELEASE(pTeamCol[i]);
			SAFE_RELEASE(pTeamWaku[i]);
		}
	}
	return 0;
}
//---------------------------//
//  ステジ選択画面の２D解放  //
//---------------------------//
int ReleaseStageSelectWindow(void)
{
	if(DrawingMode == STAGESELECTWINDOW){
		SAFE_RELEASE(pLeft);
		SAFE_RELEASE(pRight);
		for(int i=0; i<STAGECNT; i++)
			SAFE_RELEASE(pSelstage[i]);
		SAFE_RELEASE(pStageR);
	}

	return 0;
}
//-------------------//
//  結果画面２D解放  //
//-------------------//
int ReleaseResultWindow(void)
{
	int i;
	for(i=1; i<=8; i++)
		SAFE_RELEASE(pSelcharX[i]);
	// チーム枠
	for(i=1; i<=4; i++)
		SAFE_RELEASE(pTeamWaku[i]);

	return 0;
}
//--------------------//
//  五目並べ２Ｄ解放  //
//--------------------//
int ReleaseGomokuWindow(void)
{
	if(DrawingMode == GOMOKUWINDOW){
		SAFE_RELEASE(pBackimg);
		for(int i=1; i<=5; i++)
			SAFE_RELEASE(pIsi[i]);
	}

	return 0;
}
//-------------------//
//  戦闘画面２D描画  //
//-------------------//
int DrawD2DBattle(void)
{
	D3DXMATRIX matWorld, matRotation, matTranslation;
	D3DXVECTOR3 vec3Center(0,0,0);
	D3DXVECTOR3 vec3Position(0,0,0);
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	
	// 枠表示
	if(Ninzu == 1)
		DrawD2D(503, 355, pBar);
	else if(Ninzu == 2)
		DrawD2D(0, 205, pBar);
	else
		DrawD2D(0, 0, pBar);

	for(int i=1; i<=Ninzu; i++){
		// HP,stとか表示
		char buf[64];
		wsprintf(buf, "HP\nST\nBL  %d/%d\nRL", Chpt[i]->item[Chpt[i]->SelItem].tama, Chpt[i]->item[Chpt[i]->SelItem].rlCnt);
		RenderString(buf, (Ninzu==2&&i==2)?10:10+((!(i%2))?600:0), (Ninzu==2&&i==2)?310:10+((i>=3)?300:0));
		
RenderString(debug1, 10, 100);
RenderString(debug2,210, 100);
RenderString(debug3,410, 100);

		if(Chpt[i]->alive == FALSE){// 死亡してる場合、ロゴ表示
			RECT rc={0,0,SIBOUW,SIBOUH};
			Setvec3Position(&vec3Position, Ninzu, SIBOUX_2, (i==1)?SIBOUY_2_1:SIBOUY_2_2, (i%2) ? SIBOUX_34_13 : SIBOUX_34_24, (i<3) ? SIBOUY_34_12 : SIBOUY_34_34);
			pSprite->Draw(pSibou, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
		}	
		// アイテムボックス表示
		for(int j=0; j<ITEMMAX; j++){
			RECT rc={0,0,ITEMBOXW,ITEMBOXH};
			if(Ninzu == 2){
				vec3Position.x = float(250 + (!(j%2)?35:0) + ((j==1)?70:0));
				vec3Position.y = float(((i==1)?10:310) + ((j%2)?35:0) + ((j==2)?70:0));
			}
			else{
				vec3Position.x = float((!(i%2) ? 410 : 270) + (!(j%2)?35:0) + ((j==1)?70:0));
				vec3Position.y = float(((i>2) ? 475 : 10) + ((j%2)?35:0) + ((j==2)?70:0));
			}
			// アイテム効果時間
			if(Chpt[i]->item[j].Timer)
				rc.bottom = (int)((float)Chpt[i]->item[j].Timer/ItemDat[Chpt[i]->item[j].num].shTime * 39);
			if(Chpt[i]->item[j].num != NULL)
				pSprite->Draw(pItemIcon[Chpt[i]->item[j].num], &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255,255,255,255));
			else if(j==1) // 武器ボックス空
				pSprite->Draw(pItemBoxW, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
			else          // アイテムボックス空
				pSprite->Draw(pItemBoxI, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
			if(j == Chpt[i]->SelItem)// 黄色ボックス
				pSprite->Draw(pItemBoxYellow, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(254, 255, 255, 255));
		}
		// HPバー表示
		RECT rc={0,0,0,BARHEIGHT};
		Setvec3Position(&vec3Position, Ninzu, HPBARX_2, (i==1)?HPBARY_2_1:HPBARY_2_2, (i%2) ? HPBARX_34_13 : HPBARX_34_24, (i<3) ? HPBARY_34_12 : HPBARY_34_34);
		rc.right = (int)((float)Chpt[i]->hp/Chpt[i]->maxhp * HSDBARWIDTH);
		pSprite->Draw(pHpBar, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
		// ダメージバー表示
		if(Chpt[i]->dmg > 0){
			rc.left = rc.right;
			Setvec3Position(&vec3Position, Ninzu, HPBARX_2 + rc.left, (i==1)?HPBARY_2_1:HPBARY_2_2, ((i%2) ? HPBARX_34_13 : HPBARX_34_24) + rc.left, (i<3) ? HPBARY_34_12 : HPBARY_34_34);
			rc.right = (int)((float)Chpt[i]->dmg/Chpt[i]->maxhp * HSDBARWIDTH)+rc.left;
			pSprite->Draw(pHpBarDmg, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 回復バー表示
		else if(Chpt[i]->dmg < 0){
			rc.left = (int)((float)(Chpt[i]->hp+Chpt[i]->dmg)/Chpt[i]->maxhp * HSDBARWIDTH)+rc.left;
			Setvec3Position(&vec3Position, Ninzu, HPBARX_2 + rc.left, (i==1)?HPBARY_2_1:HPBARY_2_2, ((i%2) ? HPBARX_34_13 : HPBARX_34_24) + rc.left, (i<3) ? HPBARY_34_12 : HPBARY_34_34);
			pSprite->Draw(pHpBarRec, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// STバー表示
		Setvec3Position(&vec3Position, Ninzu, MPBARX_2, (i==1)?MPBARY_2_1:MPBARY_2_2, (i%2) ? MPBARX_34_13 : MPBARX_34_24, (i<3) ? MPBARY_34_12 : MPBARY_34_34);
		rc.right = (int)((float)Chpt[i]->st/Chpt[i]->maxst * HSDBARWIDTH);
		rc.left = 0;
		pSprite->Draw(pStBar, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
		// リロードバー表示
		if(Chpt[i]->item[Chpt[i]->SelItem].rlTimer > 0){
			Setvec3Position(&vec3Position, Ninzu, RLBARX_2, (i==1)?RLBARY_2_1:RLBARY_2_2, (i%2) ? RLBARX_34_13 : RLBARX_34_24, (i<3) ? RLBARY_34_12 : RLBARY_34_34);
			rc.right = (int)((float)Chpt[i]->item[Chpt[i]->SelItem].rlTimer/ItemDat[Chpt[i]->item[Chpt[i]->SelItem].num].rlTime * RLBARWIDTH);
			rc.left = 0;
			pSprite->Draw(pRlBar, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// 照準表示
		if(Chpt[i]->SelItem < 2 && Chpt[i]->alive == TRUE){
			Setvec3Position(&vec3Position, Ninzu, float(PITX_2 - PINTWIDTH/2), float(((i==1&&Ninzu==1)?PITY_1_1:(i==1&&Ninzu==2)?PITY_2_1:PITY_2_2) - PINTHEIGHT/2), float(((i%2) ? PITX_34_13 : PITX_34_24) - PINTWIDTH/2), float(((i<3) ? PITY_34_12 : PITY_34_34) - PINTHEIGHT/2));
			pSprite->Draw(pPint, NULL, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
	// レーダーアイテム位置表示
	float xpt = 395.0f + ((Ninzu==3||Ninzu==1)?200.0f:(Ninzu==2)?300.0f:0);
	float ypt = 295.0f + ((Ninzu==3||Ninzu==1)?150.0f:0);
	for(int i=0; i<StageItemMax; i++){
		if(StageDat.item[i].obj.Visible == FALSE) continue;
		DrawD2D(xpt+StageDat.item[i].obj.vecPosition.x*7, ypt-StageDat.item[i].obj.vecPosition.z*7, (ItemDat[StageDat.item[i].num].type == SUBITEM)?pItemPt1:pItemPt2);
	}
	// レーダー弾位置表示
	for(int i=0; i<=gNinzu; i++){
		for(int j=0; j<BULLETMAX; j++){
			if(Bullet[i][j].num == NULL || Bullet[i][j].num == ZIRAI) continue;
			DrawD2D(xpt+Bullet[i][j].obj.vecPosition.x*7+RDCHARWIDTH/2, ypt-Bullet[i][j].obj.vecPosition.z*7+RDCHARHEIGHT/2, pBulletPt);
		}
	}
	// レーダーキャラ位置表示
	for(int i=1; i<=gNinzu; i++){
		if(Ch[i].alive == FALSE || Ch[i].Visible == FALSE) continue;

		vec3Position.x = xpt + Ch[i].obj[Ch[i].NowX].vecPosition.x * 7 + RDCHARWIDTH/2;
		vec3Position.y = ypt - Ch[i].obj[Ch[i].NowX].vecPosition.z * 7 + RDCHARHEIGHT/2;

		vec3Center.x = vec3Position.x + RDCHARWIDTH/2;
		vec3Center.y = vec3Position.y + RDCHARHEIGHT/2;
		// 回転
		D3DXMatrixRotationZ(&matRotation, Ch[i].obj[Ch[i].NowX].fYaw);
		D3DXMatrixTranslation(&matTranslation, vec3Position.x, vec3Position.y, 0);
		matWorld = matRotation * matTranslation;
		pSprite->SetTransform(&matWorld);

		pSprite->Draw(pChar[i], NULL, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255,255,255,255));
	}
	// 回転戻す
	D3DXMatrixRotationZ(&matRotation, 0.0f);
	D3DXMatrixTranslation(&matTranslation, 0, 0, 0);
	matWorld = matRotation * matTranslation;
	pSprite->SetTransform(&matWorld);

	pSprite->End();

	return 0;
}
//--------------------//
//  画像表示位置設定  //
//--------------------//
void Setvec3Position(D3DXVECTOR3 *Pos, int nin, float x1, float y1, float x2, float y2)
{
	if(nin<3){
		Pos->x = x1;
		Pos->y = y1;
	}
	else{
		Pos->x = x2;
		Pos->y = y2;
	}
}
//----------------------//
//  2D画像読み込み関数  //
//----------------------//
int LoadTexture(HWND hWnd)
{
	char fname[256];
	int i;
	// レダ表示
	for(i=1; i<=4; i++){
		wsprintf(fname, "./pic/char%d.png", i);
		TextureFromFile(fname, &pChar[i]);
	}
	// ポインタ
	for(i=1; i<=4; i++){
		wsprintf(fname, "./pic/pointer%d.png", i);
		TextureFromFile(fname, &pPointer[i]);
	}
	// アイテムアイコン
	for(i=1; i<=ITEMCOUNT; i++){
		wsprintf(fname, "./pic/item%d.png", i);
		TextureFromFile(fname, &pItemIcon[i]);
	}
	// アイテムボックス
	TextureFromFile("./pic/itemboxW.png", &pItemBoxW);
	TextureFromFile("./pic/itemboxI.png", &pItemBoxI);
	TextureFromFile("./pic/itemboxy.png", &pItemBoxYellow);

	TextureFromFile("./pic/pint.png",     &pPint);     // 照準
	TextureFromFile("./pic/hpBar.png",    &pHpBar);    // HPバー
	TextureFromFile("./pic/hpBarDmg.png", &pHpBarDmg);
	TextureFromFile("./pic/hpBarRec.png", &pHpBarRec);
	TextureFromFile("./pic/rlBar.png",    &pRlBar);    // リロードバー
	TextureFromFile("./pic/stBar.png",    &pStBar);    // STバー
	TextureFromFile("./pic/nBar.png",     &pnBar);     // 能力バー
	TextureFromFile("./pic/nHead.png",    &pnHead);    // 能力ヘッダー
	TextureFromFile("./pic/return.png",   &pReturn);   // 戻る
	TextureFromFile("./pic/enter.png",    &pEnter);    // 決定
	TextureFromFile("./pic/startbox.png", &pStartBox); // スタートボタンボックス
	TextureFromFile("./pic/resultBox.png",&pResultBox);// 結果ボックス
	TextureFromFile("./pic/sibou.png",    &pSibou);    // 死亡ロゴ
	TextureFromFile("./pic/cpu.png",      &pCpu);      // CPUマーク
	TextureFromFile("./pic/itempt1.png",  &pItemPt1);    // アイテム位置
	TextureFromFile("./pic/itempt2.png",  &pItemPt2);    // アイテム位置
	TextureFromFile("./pic/bulletpt.png", &pBulletPt);    // 弾位置
	TextureFromFile("./pic/gomoku_log.png",&pGolog);


	D3DXCreateSprite(pDevice, &pSprite);

	return 0;
}
//------------//
//  ２Ｄ描画  //
//------------//
void DrawD2D(float x, float y, LPDIRECT3DTEXTURE9 pP)
{
	D3DXVECTOR3 vec3Center(0,0,0);
	D3DXVECTOR3 vec3Position(0,0,0);

	vec3Position.x = x;
	vec3Position.y = y;
	pSprite->Draw(pP, NULL, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255,255,255,255));
}