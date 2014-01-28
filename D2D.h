//-------------------//
//  �I����ʂQD�`��  //
//-------------------//
int DrawD2DSelect(HWND hWnd)
{
	D3DXVECTOR3 vec3Center(0,0,0);
	D3DXVECTOR3 vec3Position(0,0,0);
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	int lopmax, r1flg, l1flg;
	r1flg = l1flg = FALSE;

	lopmax = (DrawingMode==STARTWINDOW || DrawingMode != GOMOKUWINDOW && KeyMode==TRUE)?1:(!cpuNinzu)?Ninzu:JoyCount;
	// �l���I�����
	if(DrawingMode == STARTWINDOW)
		OpSelNinzu();
	// �L�����N�^�I�����
	else if(DrawingMode == CHARASELECTWINDOW)
		OpSelChara();
	// �X�e�[�W�I�����
	else if(DrawingMode == STAGESELECTWINDOW)
		OpSelStage();
	else if(DrawingMode == GOMOKUWINDOW)
		OpGomoku();

	// �|�C���^�ړ�
	MovePointer(lopmax);
	// ���菈�� /////////////////////////////////////////////////////
	for(int lp=1; lp<=lopmax; lp++){
		// �l���I��
		if(DrawingMode == STARTWINDOW && lp==1) // 1P�̂�
			IpSelNinzu(lp, hWnd);
		// �L�����N�^�[�I��
		else if(DrawingMode == CHARASELECTWINDOW)
			IpSelChara(lp);
		// �X�e�[�W�I��
		else if(DrawingMode == STAGESELECTWINDOW)
			IpSelStage(lp, hWnd, &r1flg, &l1flg);
		else if(DrawingMode == GOMOKUWINDOW)
			IpGomoku(lp);
	}
	pSprite->End();

	return 0;
}
//--------------------//
//  �l���I����ʕ`��  //
//--------------------//
void OpSelNinzu(void)
{
	// �w�i
	DrawD2D(0,0,pBackimg);
	// �Q�[�����[�h
	for(int i=0; i<4; i++)
		if(GameMode == ROYALE_MODE || GameMode==GOMOKU_MODE && JoyCount>i+1 || i==3)
			DrawD2D(NINZU_X, (float)(NINZU_Y + i*NINZU_K), pSelnin[i]);

	if(GameMode == GOMOKU_MODE)
		DrawD2D(205, 320, pGolog);
}
//--------------------------//
//  �l���I����ʂ̌��菈��  //
//--------------------------//
void IpSelNinzu(int lp, HWND hWnd)
{
	// �N�C�b�N�X�^�[�g�i�J���p�j
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
	// ���[�h�`�F���W
	if(BTN_L3(lp) && Joy[lp].l3Flg == FALSE){
		Joy[lp].l3Flg = TRUE;
		GameMode = (GameMode == ROYALE_MODE)?GOMOKU_MODE:ROYALE_MODE;
	}
	else if(!BTN_L3(lp))
		Joy[lp].l3Flg = FALSE;

	// �ʏ�I��
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
	// �T�E���h
	if(hit == 1)
		playASound(&g_SE[SD_ENTER], 0, 0L ,TRUE);
	else if(hit == -1)
		playASound(&g_SE[SD_CLICK1], 0, 0L, TRUE);
}
//------------------------//
//  �ǂ��ԂI����ʕ`��  //
//------------------------//
void OpSelChara(void)
{
	DrawD2D(0, 0, pBackimg);
	for(int i=0; i<8; i++) // �L�����A�C�R��
		DrawD2D((float)(CHAR_X + (i%4)*CHAR_K),(float)((i>3)?CHAR_Y2:CHAR_Y1), pSelchar[i]);
	for(int i=1; i<=4; i++) // �`�[���F
		DrawD2D(TCOL_X, (float)(CHAR_Y1 + (i-1)*TCOL_K), pTeamCol[i]);
	// �I���L�������㕔�ɕ\��
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
			// �\�̓o�[
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
		else //�@���I��
			DrawD2D((float)(SELCHAR_X + (i-1)*SELCHAR_K), SELCHAR_Y, pSelcharX[0]);
		
		if(Ch[i].cpu == TRUE || i>Ninzu) // CPU�}�[�N
			DrawD2D((float)(SELCHAR_X + (i-1)*SELCHAR_K) + 15 , SELCHAR_Y + 25, pCpu);
		// �`�[���g
		DrawD2D((float)(SELCHAR_X + (i-1)*SELCHAR_K) , SELCHAR_Y, pTeamWaku[Ch[i].Team]);
	}
	// �߂�
	DrawD2D(RETURN_X , RETURN_Y, pReturn);
	// �S�����I���I�������i��
	if(chselcnt == Ninzu+cpuNinzu)
		DrawD2D(ENTER_X , ENTER_Y, pEnter);
}
//------------------------//
//  �ǂ��ԂI�����菈��  //
//------------------------//
void IpSelChara(int lp)
{
	int hit = -1;

	if(BTN_RR(lp) && Joy[lp].rrFlg==FALSE){
		Joy[lp].rrFlg = TRUE;
		hit = SelectCharaPos(lp, RRBTN);

		// �߂�
		if(Joy[lp].x>=RETURN_X && Joy[lp].x<=RETURN_X+RETURN_W && Joy[lp].y>=RETURN_Y && Joy[lp].y<=RETURN_Y+RETURN_H)
			hit = SelectChara(SELRETURN, SELRETURN, SELRETURN) + 1;
		// �i��
		if(Joy[lp].x>=ENTER_X && Joy[lp].x<=ENTER_X+ENTER_W && Joy[lp].y>=ENTER_Y && Joy[lp].y<=ENTER_Y+ENTER_H && chselcnt==Ninzu+cpuNinzu)
			hit = SelectChara(SELENTER, SELENTER, SELENTER) + 2;
	}
	else if(!BTN_RR(lp))
		Joy[lp].rrFlg = FALSE;
	// �PP�̂݃R���s���[�^�L�����I��
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
	// �i��
	if(BTN_START(lp) && chselcnt==Ninzu+cpuNinzu){
		SelectChara(SELENTER, SELENTER, SELENTER);
		playASound(&g_SE[SD_ENTER], 0, 0L ,TRUE);
	}
	else{
		// �T�E���h
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
//  �X�e�[�W�I����ʕ`��  //
//------------------------//
void OpSelStage(void)
{
	D3DXVECTOR3 vec3Center(0,0,0);
	D3DXVECTOR3 vec3Position(0,0,0);
	// �X�e�[�W�I���ς݂Ȃ�
	if(Stage){
		DrawD2D(SELSTAGE_X, SELSTAGE_Y, pBackStage); // �I���ς݃X�e�[�W�\��
		DrawD2D(ENTER_X, ENTER_Y, pEnter); // ����{�^��
	}
	// �X�e�[�W�A�C�R��
	for(int i=0; i<STAGECNT; i++){
		float xpt;
		xpt = (float)(STAGE_X + i*STAGE_K + StageMove);
		if(xpt+STAGE_W < 0 || xpt>width)
			continue;
		DrawD2D(xpt, STAGE_Y, pSelstage[i]);
	}
	
	DrawD2D(STAGERAND_X, STAGERAND_Y, pStageR);// �����_���I��
	DrawD2D(RETURN_X, RETURN_Y, pReturn);// �߂�
	// ���
	DrawD2D(LEFT_X, LEFT_Y, pLeft);
	DrawD2D(RIGHT_X, RIGHT_Y, pRight);
}
//--------------------//
//  �X�e�[�W�I������  //
//--------------------//
void IpSelStage(int lp, HWND hWnd, int *r1flg, int *l1flg)
{
	// ���
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
		// �X�e�[�W�N���b�N
		if(Joy[lp].y>=STAGE_Y && Joy[lp].y<=STAGE_Y+STAGE_H)
			for(int i=0; i<STAGECNT; i++)
				if(Joy[lp].x>=STAGE_X+STAGE_K*i+StageMove && Joy[lp].x<=STAGE_X+STAGE_K*i+STAGE_W+StageMove&&Stage!=i+1)
					StageDec(&hit, i);
		if(Joy[lp].y>=STAGERAND_Y && Joy[lp].y<=STAGERAND_Y+STAGE_H && Joy[lp].x>=STAGERAND_X && Joy[lp].x<=STAGERAND_X+STAGE_W)
				StageDec(&hit, rand()%STAGECNT);
		// �߂�
		if(Joy[lp].x>=RETURN_X&&Joy[lp].x<=RETURN_X+RETURN_W && Joy[lp].y>=RETURN_Y&&Joy[lp].y<=RETURN_Y+RETURN_H){
			hit = 2;
			if(Stage)
				SAFE_RELEASE(pBackStage);
			ChangeDrawingMode(CHARASELECTWINDOW, Ninzu, NULL);
		}
		// �i��
		if(Joy[lp].x>=ENTER_X && Joy[lp].x<=ENTER_X+ENTER_W && Joy[lp].y>=ENTER_Y && Joy[lp].y<=ENTER_Y+ENTER_H && Stage){
			if(Stage)
				SAFE_RELEASE(pBackStage);
			GameStart(hWnd);
		}
		// �T�E���h
		if(hit==1)
			playASound(&g_SE[SD_CLICK2], 0, 0L ,TRUE);
		else if(hit == 2)
			playASound(&g_SE[SD_RETURN], 0 , 0L ,TRUE);
		else if(hit == 0)
			playASound(&g_SE[SD_CLICK1], 0, 0L, TRUE);
	}
	else if(!BTN_RR(lp))
		Joy[lp].rrFlg = FALSE;
	// �i��
	if(BTN_START(lp) && Stage)
		GameStart(hWnd);
}
//--------------------//
//  �X�e�[�W�ꎞ�I��  //
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
//  �ܖډ�ʕ`��  //
//----------------//
void OpGomoku(void)
{
	DrawD2D(0, 0, pBackimg);
	DrawD2D(627, 69, pIsi[putTurn]);

	for(int i=0; i<19; i++)
		for(int j=0; j<19; j++)
			if(Goban[i][j])
				DrawD2D((float)(j*26+14), (float)(i*26+14), pIsi[Goban[i][j]]);
	// ����
	if(goWin)
		DrawD2D(627, 154, pIsi[goWin]);
}
//----------------//
//  �ܖڑI������  //
//----------------//
void IpGomoku(int lp)
{
	D3DXVECTOR3 vec3Center(0,0,0);
	D3DXVECTOR3 vec3Position(0,0,0);

	if(Joy[lp].y >= 525 && Joy[lp].y < 585 && Joy[lp].x >= 650 && Joy[lp].x < 790 && BTN_RR(lp) && (goWin || !goWin && putTurn == lp)) // �߂�
		ChangeDrawingMode(STARTWINDOW, Ninzu, NULL);

	if(Joy[lp].y > 505 || Joy[lp].x > 505 || goWin || putTurn != lp)
		return;

	vec3Position.x = (float)(((Joy[lp].x-14)/26+1)*26-12);
	vec3Position.y = (float)(((Joy[lp].y-14)/26+1)*26-12);
	pSprite->Draw(pIsi[lp], NULL, &vec3Center, &vec3Position, D3DCOLOR_ARGB(64,255,255,255)); // �Δ�����

	if(BTN_RR(lp) && Joy[lp].rrFlg == FALSE){
		Joy[lp].rrFlg = TRUE;
		int x = (Joy[lp].x-14)/26;
		int y = (Joy[lp].y-14)/26;
		if(!Goban[y][x]){ // ������
			playASound(&g_SE[SD_CLICK1], 0, 0L, TRUE);

			Goban[y][x] = lp;
			putTurn++;
			if(putTurn > Ninzu)
				putTurn = 1;
			// �A�씻��
			for(x=0; x<19; x++)
				for(y=0; y<19; y++)
					if(Goban[y][x] == lp)
						GomokuSyouhai(lp, x, y);
			if(!goWin){ // ������������
				putCnt++;
				if(putCnt >= 19*19)
					goWin = 5;
			}
			if(goWin) // ������
				playASound(&g_SE[SD_DEATH], 0, 0L, TRUE);
		}
	}
	else if(!BTN_RR(lp))
		Joy[lp].rrFlg = FALSE;
}
//----------------//
//  �ܖژA�씻��  //
//----------------//
void GomokuSyouhai(int lp, int x, int y)
{
	if(y >= 4){ // ����@��@�E��
		// ��
		if(Goban[y-1][x] == lp)
			if(Goban[y-2][x] == lp)
				if(Goban[y-3][x] == lp)
					if(Goban[y-4][x] == lp)
						goWin = lp;
		if(x >= 4) // ����
			if(Goban[y-1][x-1] == lp)
				if(Goban[y-2][x-2] == lp)
					if(Goban[y-3][x-3] == lp)
						if(Goban[y-4][x-4] == lp)
							goWin = lp;
		if(x < 15) // �E��
			if(Goban[y-1][x+1] == lp)
				if(Goban[y-2][x+2] == lp)
					if(Goban[y-3][x+3] == lp)
						if(Goban[y-4][x+4] == lp)
							goWin = lp;
	}
	if(x >= 4) // ��
		if(Goban[y][x-1] == lp)
			if(Goban[y][x-2] == lp)
				if(Goban[y][x-3] == lp)
					if(Goban[y][x-4] == lp)
						goWin = lp;
	if(x < 15) // �E
		if(Goban[y][x+1] == lp)
			if(Goban[y][x+2] == lp)
				if(Goban[y][x+3] == lp)
					if(Goban[y][x+4] == lp)
						goWin = lp;
	if(y < 15){ // �E���@���@����
		// ��
		if(Goban[y+1][x] == lp)
			if(Goban[y+2][x] == lp)
				if(Goban[y+3][x] == lp)
					if(Goban[y+4][x] == lp)
						goWin = lp;
		if(x < 15) // �E��
			if(Goban[y+1][x+1] == lp)
				if(Goban[y+2][x+2] == lp)
					if(Goban[y+3][x+3] == lp)
						if(Goban[y+4][x+4] == lp)
							goWin = lp;
		if(x >= 4) // ����
			if(Goban[y+1][x-1] == lp)
				if(Goban[y+2][x-2] == lp)
					if(Goban[y+3][x-3] == lp)
						if(Goban[y+4][x-4] == lp)
							goWin = lp;
	}
}
//----------------//
//  �L�����ʒu��  //
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
	// �`�[���F����
	if(Joy[lp].x>=TCOL_X && Joy[lp].x<=TCOL_X+TCOL_W)
		for(int i=0; i<4; i++)
			if(Joy[lp].y>=CHAR_Y1+i*TCOL_K && Joy[lp].y<=CHAR_Y1+i*TCOL_K+TCOL_H)
				return SelectTeam(lp, i+1, btn);
	
	return 0;
}
//------------------//
//  �g�p�L�����I��  //
//------------------//
int SelectChara(int lp, int cnum, int btn)
{
	// �߂鏈��
	if(lp==SELRETURN && cnum==SELRETURN)
		return ChangeDrawingMode(STARTWINDOW, Ninzu+cpuNinzu, NULL);
	// �i�ޏ���
	else if(lp==SELENTER && cnum==SELENTER)
		return ChangeDrawingMode(STAGESELECTWINDOW, Ninzu+cpuNinzu, NULL);
	// �l����葽��CPU�̑I��
	if(btn > Ninzu+cpuNinzu)
		return FALSE;

	// ���I���̏ꍇ
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
//  �`�[��(��)�I��  //
//------------------//
int SelectTeam(int lp, int tnum, int btn)
{
	// �l����葽��CPU�̑I�� || �S������`�[���֎~
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
//  �|�C���^�ړ�  //
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
//  �X�^�[�g�{�^���E�B���h�E  //
//----------------------------//
int DrawD2DSelectSt(HWND hWnd)
{
	D3DXVECTOR3 vec3Center(0,0,0);
	D3DXVECTOR3 vec3Position(0,0,0);
	// �\�� ////////////////////////
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	vec3Position.x = MENU_X;
	vec3Position.y = MENU_Y;
	if(DrawingMode == MENUWINDOW) // �Z���N�g���j��
		pSprite->Draw(pStartBox, NULL, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255,255,255,255));
	else{ // ���U���g���j��
		pSprite->Draw(pResultBox, NULL, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255,255,255,255));
		// ���ʕ\��
		if(GameMode == ROYALE_MODE){ // �l��
			for(int rank=1; rank<=gNinzu; rank++){
				char buf[256];
				wsprintf(buf, "�� %d ��", rank);
				RenderString(buf, 350, 150+(rank-1)*100);
				for(int c=1; c<=gNinzu; c++){ // �摜�\��
					if(Ch[c].rank == rank){
						DrawD2D(450.0f, 120.0f+(rank-1)*100.0f, pSelcharX[Ch[c].num]);
						DrawD2D(450.0f, 120.0f+(rank-1)*100.0f, pTeamWaku[Ch[c].Team]);
					}
				}
			}
		}
		else if(GameMode == TEAM_MODE){ // �`�[���퓬
			int rNin=0, resNin;
			for(int rank=1; rank<=gNinzu; rank++){
				char buf[256];
				wsprintf(buf, "�� %d ��", rank);
				RenderString(buf, 350, 150+(rank-1)*100);
				
				resNin = 0;
				for(int c=1; c<=gNinzu; c++){ // �摜�\��
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
	// ���蔻�� ///////////////
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
			// �T�E���h
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
//  �Q�[���X�^�[�g  //
//------------------//
int GameStart(HWND hWnd)
{
	// �T�E���h
	playASound(&g_SE[SD_START], 0, 0L ,TRUE);
	
	// �`�[���퓬���ǂ���
	GameMode = ROYALE_MODE;
	for(int i=1; i<=4; i++) // �`�[���l���R�s�[
		TeamNowCnt[i] = TeamCnt[i];
	TeamKazu = 0;
	for(int i=1; i<=4; i++){
		if(TeamNowCnt[i]) // �`�[�����擾
			TeamKazu++;
		if(TeamNowCnt[i] > 1) // �`�[�����[�h����
			GameMode = TEAM_MODE;
	}
	// �L�����N�^�X�e�[�^�X�ǂݍ���
	for(int i=1; i<=Ninzu+cpuNinzu; i++){
		for(int j=0; j<Ch[i].Xcnt; j++)
			if(Ch[i].obj[j].Mesh.dwNumMaterials)
				ReleaseObject(&Ch[i].obj[j]);
		if(Ch[i].Dageki.Mesh.dwNumMaterials)
			ReleaseObject(&Ch[i].Dageki);
		// �L�������b�V���ǂݍ���
		Ch[i].Xcnt = 0;
		for(int j=0; j<SUBXCNT; j++){
			if(SubX[Ch[i].num][j][0] != '\0'){
				char buf[256];
				wsprintf(buf, "%s%s", CharXDir, SubX[Ch[i].num][j]);
				InitThing(&Ch[i].obj[Ch[i].Xcnt++], buf, &StartPt[Stage-1][i-1], TRUE, TYPE_CHAR);
			}
		}
		// �Ō����b�V��
		InitThing(&Ch[i].Dageki, ChDat[Ch[i].num].dAtack, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), FALSE, TYPE_DAGEKI);	
		// �`�[���A�C�R�����b�V��
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
		// �e������
		for(int j=0; j<BULLETMAX; j++)
			Bullet[i][j].num = 0;
		// ����������
		for(int j=0; j<BLASTMAX; j++){
			Blast[i][j].obj.Sphere.fRadius = NULL;
			Blast[i][j].num = 0;
		}
	}
	wsprintf(debug1, "");
	wsprintf(debug2, "");
	wsprintf(debug3, "");
	// �v���C���l������
	int hit=0;
	gNinzu = Ninzu+cpuNinzu;
	for(int i=1; i<=gNinzu; i++){
		if(Ch[i].cpu == FALSE){ // �v���C���Ȃ�
			hit++;
			Chpt[hit] = &Ch[i];
		}
	}
	Ninzu = hit;
	cpuNinzu = gNinzu - Ninzu;

	AliveCnt = gNinzu;
	// �X�e�[�W�ǂݍ���
	ChangeStage(Stage);
	g_aspect = (Ninzu==2)? width/(height/2) : width/height;
	// �g�ǂݍ���
	if(DrawingMode != RESULTWINDOW)
		ReadFrame(Ninzu);

	ChangeDrawingMode(BATTLEWINDOW, Ninzu, hWnd);

	return 0;
}
//----------------//
//  �ΐ�l������  //
//----------------//
int SelectResultNinzu(int nin)
{
	if(JoyCount < nin && GameMode == ROYALE_MODE){
		cpuNinzu = nin - ((KeyMode==TRUE)?1:JoyCount); // �R���s���[�^��
		Ninzu = nin - cpuNinzu;    // �v���C���[��
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
//  �`���ʕύX  //
//----------------//
int ChangeDrawingMode(int mode, int Nin, HWND hWnd)
{
	int i;
	char fname[256];
	
	if((DrawingMode == MENUWINDOW || DrawingMode == RESULTWINDOW) && mode != BATTLEWINDOW)
		SAFE_RELEASE(pBar);

	switch(mode){
		case STARTWINDOW:
			// �Q�������
			ReleaseGomokuWindow();
			ReleaseCharaSelectWindow();
			if(DrawingMode == RESULTWINDOW)
				ReleaseResultWindow();
			if(DrawingMode == MENUWINDOW || DrawingMode == RESULTWINDOW)
				SAFE_RELEASE(pBar);
			if(!DrawingMode)
				SetTimer(hWnd, MOVETIMER, TIMERINTERVAL_MOV, NULL);
			// �Q�����ǂݍ���
			TextureFromFile("./pic/bgimage.png", &pBackimg);  // �g�b�v���S
			TextureFromFile("./pic/2play.png", &pSelnin[0]);
			TextureFromFile("./pic/3play.png", &pSelnin[1]);
			TextureFromFile("./pic/4play.png", &pSelnin[2]);
			TextureFromFile("./pic/end.png",   &pSelnin[3]);

			for(i=1; i<=Nin; i++)
				Ch[i].num = 0;
			Ninzu = 0;
			chselcnt=0;
			// BGM�̍Đ��J�n
			playAMusic(&g_BGM[1]);
			break;
		case CHARASELECTWINDOW:
			// �Q�������
			ReleaseStageSelectWindow();
			if(DrawingMode == RESULTWINDOW)
				ReleaseResultWindow();
			if(DrawingMode == MENUWINDOW || DrawingMode == RESULTWINDOW)
				SAFE_RELEASE(pBar);
			ReleaseStartWindow();
			// �Q�����ǂݍ���
			TextureFromFile("./pic/bgimage2.png", &pBackimg);
			// �L�����摜
			for(i=0; i<9; i++){
				if(i<8){
					wsprintf(fname, "./pic/selchar%d.png", i+1);
					TextureFromFile(fname, &pSelchar[i]);
				}
				wsprintf(fname, "./pic/selch%d.png", i);
				TextureFromFile(fname, &pSelcharX[i]);
			}
			// �`�[���F�Ƙg
			for(i=1; i<=4; i++){
				wsprintf(fname, "./pic/teamC%d.png", i);
				TextureFromFile(fname, &pTeamCol[i]);
				wsprintf(fname, "./pic/teamwakuC%d.png", i);
				TextureFromFile(fname, &pTeamWaku[i]);
				// �`�[���F�U�蕪��
				if(DrawingMode == STARTWINDOW){
					if(i > Ninzu + cpuNinzu)
						TeamCnt[i] = 0;
					else{
						Ch[i].Team = i;
						TeamCnt[i] = 1;
					}
				}
			}
			// BGM�Đ�
			playAMusic(&g_BGM[3]);
			Stage = 0;
			break;
		case STAGESELECTWINDOW:
			// �Q�������
			ReleaseCharaSelectWindow();
			if(DrawingMode == RESULTWINDOW)
				ReleaseResultWindow();
			if(DrawingMode == MENUWINDOW || DrawingMode == RESULTWINDOW)
				SAFE_RELEASE(pBar);
			Stage=0;
			// �X�e�[�W�I���A�C�R���ǂݍ���
			for(i=0; i<STAGECNT; i++){
				wsprintf(fname, "./pic/selstage%d.png", i+1);
				TextureFromFile(fname, &pSelstage[i]);
			}
			TextureFromFile("./pic/selstageR.png",&pStageR);   // �����_���I��
			TextureFromFile("./pic/left.png",     &pLeft);     // �����
			TextureFromFile("./pic/right.png",    &pRight);    // �E���
			// BGM�Đ�
			playAMusic(&g_BGM[4]);
			break;
		case BATTLEWINDOW:
			ReleaseStartWindow();
			if(DrawingMode == RESULTWINDOW)
				ReleaseResultWindow();
			// �Q�����J��
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
			// ���ʉ�ʂȂ�
			if(mode == RESULTWINDOW){ // �L�����摜
				for(i=1; i<=8; i++){
					wsprintf(fname, "./pic/selch%d.png", i);
					TextureFromFile(fname, &pSelcharX[i]);
				}
				// �`�[���g
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
//  �N����ʂQ�c���  //
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
//  �L�����I����ʂ̂QD���  //
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
		// �`�[���g
		for(i=1; i<=4; i++){
			SAFE_RELEASE(pTeamCol[i]);
			SAFE_RELEASE(pTeamWaku[i]);
		}
	}
	return 0;
}
//---------------------------//
//  �X�e�W�I����ʂ̂QD���  //
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
//  ���ʉ�ʂQD���  //
//-------------------//
int ReleaseResultWindow(void)
{
	int i;
	for(i=1; i<=8; i++)
		SAFE_RELEASE(pSelcharX[i]);
	// �`�[���g
	for(i=1; i<=4; i++)
		SAFE_RELEASE(pTeamWaku[i]);

	return 0;
}
//--------------------//
//  �ܖڕ��ׂQ�c���  //
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
//  �퓬��ʂQD�`��  //
//-------------------//
int DrawD2DBattle(void)
{
	D3DXMATRIX matWorld, matRotation, matTranslation;
	D3DXVECTOR3 vec3Center(0,0,0);
	D3DXVECTOR3 vec3Position(0,0,0);
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	
	// �g�\��
	if(Ninzu == 1)
		DrawD2D(503, 355, pBar);
	else if(Ninzu == 2)
		DrawD2D(0, 205, pBar);
	else
		DrawD2D(0, 0, pBar);

	for(int i=1; i<=Ninzu; i++){
		// HP,st�Ƃ��\��
		char buf[64];
		wsprintf(buf, "HP\nST\nBL  %d/%d\nRL", Chpt[i]->item[Chpt[i]->SelItem].tama, Chpt[i]->item[Chpt[i]->SelItem].rlCnt);
		RenderString(buf, (Ninzu==2&&i==2)?10:10+((!(i%2))?600:0), (Ninzu==2&&i==2)?310:10+((i>=3)?300:0));
		
RenderString(debug1, 10, 100);
RenderString(debug2,210, 100);
RenderString(debug3,410, 100);

		if(Chpt[i]->alive == FALSE){// ���S���Ă�ꍇ�A���S�\��
			RECT rc={0,0,SIBOUW,SIBOUH};
			Setvec3Position(&vec3Position, Ninzu, SIBOUX_2, (i==1)?SIBOUY_2_1:SIBOUY_2_2, (i%2) ? SIBOUX_34_13 : SIBOUX_34_24, (i<3) ? SIBOUY_34_12 : SIBOUY_34_34);
			pSprite->Draw(pSibou, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
		}	
		// �A�C�e���{�b�N�X�\��
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
			// �A�C�e�����ʎ���
			if(Chpt[i]->item[j].Timer)
				rc.bottom = (int)((float)Chpt[i]->item[j].Timer/ItemDat[Chpt[i]->item[j].num].shTime * 39);
			if(Chpt[i]->item[j].num != NULL)
				pSprite->Draw(pItemIcon[Chpt[i]->item[j].num], &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255,255,255,255));
			else if(j==1) // ����{�b�N�X��
				pSprite->Draw(pItemBoxW, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
			else          // �A�C�e���{�b�N�X��
				pSprite->Draw(pItemBoxI, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
			if(j == Chpt[i]->SelItem)// ���F�{�b�N�X
				pSprite->Draw(pItemBoxYellow, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(254, 255, 255, 255));
		}
		// HP�o�[�\��
		RECT rc={0,0,0,BARHEIGHT};
		Setvec3Position(&vec3Position, Ninzu, HPBARX_2, (i==1)?HPBARY_2_1:HPBARY_2_2, (i%2) ? HPBARX_34_13 : HPBARX_34_24, (i<3) ? HPBARY_34_12 : HPBARY_34_34);
		rc.right = (int)((float)Chpt[i]->hp/Chpt[i]->maxhp * HSDBARWIDTH);
		pSprite->Draw(pHpBar, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
		// �_���[�W�o�[�\��
		if(Chpt[i]->dmg > 0){
			rc.left = rc.right;
			Setvec3Position(&vec3Position, Ninzu, HPBARX_2 + rc.left, (i==1)?HPBARY_2_1:HPBARY_2_2, ((i%2) ? HPBARX_34_13 : HPBARX_34_24) + rc.left, (i<3) ? HPBARY_34_12 : HPBARY_34_34);
			rc.right = (int)((float)Chpt[i]->dmg/Chpt[i]->maxhp * HSDBARWIDTH)+rc.left;
			pSprite->Draw(pHpBarDmg, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// �񕜃o�[�\��
		else if(Chpt[i]->dmg < 0){
			rc.left = (int)((float)(Chpt[i]->hp+Chpt[i]->dmg)/Chpt[i]->maxhp * HSDBARWIDTH)+rc.left;
			Setvec3Position(&vec3Position, Ninzu, HPBARX_2 + rc.left, (i==1)?HPBARY_2_1:HPBARY_2_2, ((i%2) ? HPBARX_34_13 : HPBARX_34_24) + rc.left, (i<3) ? HPBARY_34_12 : HPBARY_34_34);
			pSprite->Draw(pHpBarRec, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// ST�o�[�\��
		Setvec3Position(&vec3Position, Ninzu, MPBARX_2, (i==1)?MPBARY_2_1:MPBARY_2_2, (i%2) ? MPBARX_34_13 : MPBARX_34_24, (i<3) ? MPBARY_34_12 : MPBARY_34_34);
		rc.right = (int)((float)Chpt[i]->st/Chpt[i]->maxst * HSDBARWIDTH);
		rc.left = 0;
		pSprite->Draw(pStBar, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
		// �����[�h�o�[�\��
		if(Chpt[i]->item[Chpt[i]->SelItem].rlTimer > 0){
			Setvec3Position(&vec3Position, Ninzu, RLBARX_2, (i==1)?RLBARY_2_1:RLBARY_2_2, (i%2) ? RLBARX_34_13 : RLBARX_34_24, (i<3) ? RLBARY_34_12 : RLBARY_34_34);
			rc.right = (int)((float)Chpt[i]->item[Chpt[i]->SelItem].rlTimer/ItemDat[Chpt[i]->item[Chpt[i]->SelItem].num].rlTime * RLBARWIDTH);
			rc.left = 0;
			pSprite->Draw(pRlBar, &rc, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// �Ə��\��
		if(Chpt[i]->SelItem < 2 && Chpt[i]->alive == TRUE){
			Setvec3Position(&vec3Position, Ninzu, float(PITX_2 - PINTWIDTH/2), float(((i==1&&Ninzu==1)?PITY_1_1:(i==1&&Ninzu==2)?PITY_2_1:PITY_2_2) - PINTHEIGHT/2), float(((i%2) ? PITX_34_13 : PITX_34_24) - PINTWIDTH/2), float(((i<3) ? PITY_34_12 : PITY_34_34) - PINTHEIGHT/2));
			pSprite->Draw(pPint, NULL, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
	// ���[�_�[�A�C�e���ʒu�\��
	float xpt = 395.0f + ((Ninzu==3||Ninzu==1)?200.0f:(Ninzu==2)?300.0f:0);
	float ypt = 295.0f + ((Ninzu==3||Ninzu==1)?150.0f:0);
	for(int i=0; i<StageItemMax; i++){
		if(StageDat.item[i].obj.Visible == FALSE) continue;
		DrawD2D(xpt+StageDat.item[i].obj.vecPosition.x*7, ypt-StageDat.item[i].obj.vecPosition.z*7, (ItemDat[StageDat.item[i].num].type == SUBITEM)?pItemPt1:pItemPt2);
	}
	// ���[�_�[�e�ʒu�\��
	for(int i=0; i<=gNinzu; i++){
		for(int j=0; j<BULLETMAX; j++){
			if(Bullet[i][j].num == NULL || Bullet[i][j].num == ZIRAI) continue;
			DrawD2D(xpt+Bullet[i][j].obj.vecPosition.x*7+RDCHARWIDTH/2, ypt-Bullet[i][j].obj.vecPosition.z*7+RDCHARHEIGHT/2, pBulletPt);
		}
	}
	// ���[�_�[�L�����ʒu�\��
	for(int i=1; i<=gNinzu; i++){
		if(Ch[i].alive == FALSE || Ch[i].Visible == FALSE) continue;

		vec3Position.x = xpt + Ch[i].obj[Ch[i].NowX].vecPosition.x * 7 + RDCHARWIDTH/2;
		vec3Position.y = ypt - Ch[i].obj[Ch[i].NowX].vecPosition.z * 7 + RDCHARHEIGHT/2;

		vec3Center.x = vec3Position.x + RDCHARWIDTH/2;
		vec3Center.y = vec3Position.y + RDCHARHEIGHT/2;
		// ��]
		D3DXMatrixRotationZ(&matRotation, Ch[i].obj[Ch[i].NowX].fYaw);
		D3DXMatrixTranslation(&matTranslation, vec3Position.x, vec3Position.y, 0);
		matWorld = matRotation * matTranslation;
		pSprite->SetTransform(&matWorld);

		pSprite->Draw(pChar[i], NULL, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255,255,255,255));
	}
	// ��]�߂�
	D3DXMatrixRotationZ(&matRotation, 0.0f);
	D3DXMatrixTranslation(&matTranslation, 0, 0, 0);
	matWorld = matRotation * matTranslation;
	pSprite->SetTransform(&matWorld);

	pSprite->End();

	return 0;
}
//--------------------//
//  �摜�\���ʒu�ݒ�  //
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
//  2D�摜�ǂݍ��݊֐�  //
//----------------------//
int LoadTexture(HWND hWnd)
{
	char fname[256];
	int i;
	// ���_�\��
	for(i=1; i<=4; i++){
		wsprintf(fname, "./pic/char%d.png", i);
		TextureFromFile(fname, &pChar[i]);
	}
	// �|�C���^
	for(i=1; i<=4; i++){
		wsprintf(fname, "./pic/pointer%d.png", i);
		TextureFromFile(fname, &pPointer[i]);
	}
	// �A�C�e���A�C�R��
	for(i=1; i<=ITEMCOUNT; i++){
		wsprintf(fname, "./pic/item%d.png", i);
		TextureFromFile(fname, &pItemIcon[i]);
	}
	// �A�C�e���{�b�N�X
	TextureFromFile("./pic/itemboxW.png", &pItemBoxW);
	TextureFromFile("./pic/itemboxI.png", &pItemBoxI);
	TextureFromFile("./pic/itemboxy.png", &pItemBoxYellow);

	TextureFromFile("./pic/pint.png",     &pPint);     // �Ə�
	TextureFromFile("./pic/hpBar.png",    &pHpBar);    // HP�o�[
	TextureFromFile("./pic/hpBarDmg.png", &pHpBarDmg);
	TextureFromFile("./pic/hpBarRec.png", &pHpBarRec);
	TextureFromFile("./pic/rlBar.png",    &pRlBar);    // �����[�h�o�[
	TextureFromFile("./pic/stBar.png",    &pStBar);    // ST�o�[
	TextureFromFile("./pic/nBar.png",     &pnBar);     // �\�̓o�[
	TextureFromFile("./pic/nHead.png",    &pnHead);    // �\�̓w�b�_�[
	TextureFromFile("./pic/return.png",   &pReturn);   // �߂�
	TextureFromFile("./pic/enter.png",    &pEnter);    // ����
	TextureFromFile("./pic/startbox.png", &pStartBox); // �X�^�[�g�{�^���{�b�N�X
	TextureFromFile("./pic/resultBox.png",&pResultBox);// ���ʃ{�b�N�X
	TextureFromFile("./pic/sibou.png",    &pSibou);    // ���S���S
	TextureFromFile("./pic/cpu.png",      &pCpu);      // CPU�}�[�N
	TextureFromFile("./pic/itempt1.png",  &pItemPt1);    // �A�C�e���ʒu
	TextureFromFile("./pic/itempt2.png",  &pItemPt2);    // �A�C�e���ʒu
	TextureFromFile("./pic/bulletpt.png", &pBulletPt);    // �e�ʒu
	TextureFromFile("./pic/gomoku_log.png",&pGolog);


	D3DXCreateSprite(pDevice, &pSprite);

	return 0;
}
//------------//
//  �Q�c�`��  //
//------------//
void DrawD2D(float x, float y, LPDIRECT3DTEXTURE9 pP)
{
	D3DXVECTOR3 vec3Center(0,0,0);
	D3DXVECTOR3 vec3Position(0,0,0);

	vec3Position.x = x;
	vec3Position.y = y;
	pSprite->Draw(pP, NULL, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255,255,255,255));
}