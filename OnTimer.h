//----------------//
// �X�^�~�i�^�C�} //
//----------------//
int StminTimer(void)
{
	for(int lp=1; lp<=gNinzu; lp++){
		// �X�^�~�i��
		if(Ch[lp].JpFlg >= RAKKA || !Ch[lp].JpFlg)
			Ch[lp].st += 1;
		if(Ch[lp].st > Ch[lp].maxst)
			Ch[lp].st = Ch[lp].maxst;
		// �_���[�W�o�[�O�֎���
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
	// �X�e�[�W�A�C�e���ďo���^�C�}
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
//  �A�C�e���g�p  //
//----------------//
int UseItem(int iNum, int lp, int useNum)
{
	if(Ch[lp].item[useNum].Timer || Ch[lp].item[useNum].rlTimer)
		return -1;

	switch(iNum){
		case NORMALSHOT: // �ʏ�V���b�g
		case PATINKO:    // �ς���
		case BAZUKA:     // �o�Y�[�J
		case KARASI:
		case SYURYUDAN:// �e�X�g����i��֒e�I�O��
		case BAKURETSU:// �e�X�g����i���ˌ�j��
		case ZIRAI:    // �e�X�g����i�n��
		case KANTSU:   // �e�X�g����i�ђ�
		case ZIKANSA:  // �e�X�g����i���΂炭�ҋ@
		case BOM:      // ���e
		case KOUSEN:   // �����e
		case MISSILE:
		case SUNAIPA:  // �X�i�C�p�[���C�t��
		case BEAMSODE:
			UseWepon(lp, useNum, iNum, 1);
			break;
		case SHOTGUN: // �e�X�g����i�g�U
			UseWepon(lp, useNum, iNum, 15);
			break;
		case ENKEI: // �e�X�g����i���ɂP��]
			UseWepon(lp, useNum, iNum, 36);
			break;
		case RORABUREDO: // ���[���u���[�h
			playASound(&g_SE[SD_ITEMUSE], 0, 0L ,TRUE);
			Ch[lp].item[useNum].Timer = ItemDat[iNum].shTime;
			Ch[lp].SpdUp  += UP_SPD;
			Ch[lp].TurnUp += UP_TURN;
			break;
		case NIKU:// ����
			int ohp;
			// �T�E���h
			playASound(&g_SE[SD_ITEMUSE], 0, 0L ,TRUE);

			ohp = Ch[lp].hp;
			Ch[lp].hp += NIKUKAIFUKU;
			if(Ch[lp].maxhp < Ch[lp].hp)
				Ch[lp].hp = Ch[lp].maxhp;
			Ch[lp].dmg -= Ch[lp].hp - ohp; // �Q�[�W
			Ch[lp].item[useNum].num = 0;
			StageDat.item[Ch[lp].item[useNum].Ptnum].AppTimer = ItemDat[NIKU].AppTime;
			break;
		case GETA:// ����
			playASound(&g_SE[SD_ITEMUSE], 0, 0L ,TRUE);
			Ch[lp].item[useNum].Timer = ItemDat[iNum].shTime;
			Ch[lp].SpdUp  -= DOWN_SPD;
			Ch[lp].TurnUp -= DOWN_TURN;
			break;
		case TESTITEM1: // �W�����v�A�b�v
			playASound(&g_SE[SD_ITEMUSE], 0, 0L ,TRUE);
			Ch[lp].item[useNum].Timer = ItemDat[iNum].shTime;
			Ch[lp].JumpUp += UP_JUMP;
			break;
		case TESTITEM2: // �U���A�b�v
			playASound(&g_SE[SD_ITEMUSE], 0, 0L ,TRUE);
			Ch[lp].item[useNum].Timer = ItemDat[iNum].shTime;
			Ch[lp].AtkUp += UP_ATK;
			break;
		case TESTITEM3: // �h��A�b�v
			playASound(&g_SE[SD_ITEMUSE], 0, 0L ,TRUE);
			Ch[lp].item[useNum].Timer = ItemDat[iNum].shTime;
			Ch[lp].DefUp += UP_DEF;
			break;
		case MIRA: // ����
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
//  �e���ˏ���  //
//--------------//
int UseWepon(int lp, int useNum, int iNum, int shotMax)
{
	int shotCnt = 0; // ���ˉ�

	if(lp) // �����U���T�E���h
		playASound(&g_SE[ItemDat[iNum].shSnd],0 , 0L ,TRUE);

	for(int i=0; i<=BULLETMAX; i++){
		if(Bullet[lp][i].num == NULL){ // �e�i�[�z��ɋ󂫂���B

			int hit=0;
			if(lp){ // �L�����̒e����
				ObjectPositionCopy(&Bullet[lp][i].obj, &Ch[lp].obj[Ch[lp].NowX]);
				Bullet[lp][i].obj.BBox.fLengthZ = BulletObj[iNum].BBox.fLengthZ/2;
				Ch[lp].item[useNum].Timer = ItemDat[iNum].shTime; // ���ˊԊu

				if(iNum != ZIRAI){
						// �L�����̒��S���炢���甭��
					Bullet[lp][i].obj.vecPosition.y += Ch[lp].obj[Ch[lp].NowX].BBox.vecMax.y/2.3f;
					// ���C����ɂ��ڕW�ւ̏c�p�x�v�Z
					// �X�e�[�W��
					if (RayShoot(&Ch[lp], &StageDat.obj, &fDistance, &vIntersect))
						CalcBulletPitch(lp, i, &hit, &vIntersect);
					// �L������
					for(int j=1; j<=gNinzu; j++){
						if(j==lp || Ch[lp].item[1].num != MISSILE || Ch[lp].SelItem != 1) continue;
						if(RayShoot(&Ch[lp], &Ch[j].obj[Ch[j].NowX], &fDistance, &vIntersect))
							CalcBulletPitch(lp, i, &hit, &vIntersect);
					}
					// ���p�x
					Bullet[lp][i].obj.fYaw = Ch[lp].obj[Ch[lp].NowX].fYaw;
					// ���C��������Ȃ������ꍇ
					if(!hit)
						Bullet[lp][i].obj.fPitch = Ch[lp].Camera.Pitch-0.5f;
				}
			}
			if(!lp){ // �ΎR
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
			// ���ꕐ��̌���
			switch(iNum){
				case SHOTGUN: // �g�U����			
					Bullet[lp][i].obj.fPitch += ((rand()%10) / 100.0f) * ((rand()%2)?-1:1);
					Bullet[lp][i].obj.fYaw += ((rand()%10) / 100.0f) * ((rand()%2)?-1:1);
					break;
				case ENKEI: // ���ɂP��]
					Bullet[lp][i].obj.fYaw = (float)((shotCnt-1.0f)/(shotMax-1.0f) * PI*2);
					if(Bullet[lp][i].obj.fYaw > PI)
						Bullet[lp][i].obj.fYaw -= (float)(PI*2);
					break;
				case SYURYUDAN:case BOM:case MOUNT_TAMA: // ��֒e�I�O���̕���
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
				case ZIKANSA: // �ꎞ�ҋ@
					Bullet[lp][i].obj.tag = 40;
					break;
				case MISSILE: // �~�T�C��
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
	// �e����
	if(lp)
		DecBullet(lp, useNum, iNum);

	return 0;
}
//----------//
//  �e����  //
//----------//
void DecBullet(int lp, int useNum, int iNum)
{
	Ch[lp].item[useNum].tama--;
	if(Ch[lp].item[useNum].tama == 0){ // �����[�h
		if(Ch[lp].item[useNum].rlCnt == 0 && useNum!=0){ // �e�s����
			Ch[lp].item[useNum].num = 0;
			Ch[lp].item[useNum].Timer = 0;
			// �Y�[���߂�
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
//  �e�̂x�p�x�v�Z  //
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
//  �A�C�e���^�C�}  //
//------------------//
int ItemTimer(void)
{
	int lp, i;
	
	for(i=0; i<STAGEITEMMAX; i++)
		if(StageDat.item[i].num)
			StageDat.item[i].obj.fYaw += 0.1f;

	for(lp=0; lp<=gNinzu; lp++){
		// �e�ړ� ///////////////////////////////////
		for(int t=0; t<BULLETMAX; t++){
			if(Bullet[lp][t].num == NULL) continue;
			// �ҋ@���̏ꍇ
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

			// �򋗗��̌��E�ɓ��B
			if(Bullet[lp][t].num == ZIRAI){ // �n�����Ȃ�
				if(Bullet[lp][t].cnt > ItemDat[Bullet[lp][t].num].Range)
					Bullet[lp][t].num = Bullet[lp][t].tag = 0;
			}
			else if(Bullet[lp][t].cnt*ItemDat[Bullet[lp][t].num].tSpd >= ItemDat[Bullet[lp][t].num].Range * ((Bullet[lp][t].tag==BAKURETSU_2)?2:1)){
				// ���U���� ����if��
				WeponEffect_Bunretsu(lp, t, BAKURETSUMAX, BAKURETSU, BAKURETSU_2);

				Bullet[lp][t].num = 0;
				Bullet[lp][t].tag = 0;
				continue;
			}
			// ��Q���Ƃ̂����蔻��
			else if(Bullet[lp][t].num != KANTSU){
				if(BulletStageRayInter(lp, t, RAY_MAE))
					continue;
				// �d�͗L��Ȃ烌�C���ɂ�
				if(ItemDat[Bullet[lp][t].num].gSpeed > 0){
					if(BulletStageRayInter(lp, t, RAY_SITA))
						continue;
				}
			}

			if (Bullet[lp][t].num){
				if(Bullet[lp][t].num == MOUNT_TAMA) // �ΎR�e
					ItemDat[Bullet[lp][t].num].tSpd = Bullet[lp][t].obj.ftag;

				Bullet[lp][t].obj.vecPosition.x -= ItemDat[Bullet[lp][t].num].tSpd * sinf(Bullet[lp][t].obj.fYaw);
				Bullet[lp][t].obj.vecPosition.z -= ItemDat[Bullet[lp][t].num].tSpd * cosf(Bullet[lp][t].obj.fYaw);
				// �����̗����ړ�
				if(Bullet[lp][t].tag == BAKURETSU_2){
					Bullet[lp][t].obj.vecPosition.x -= Bullet[lp][t].obj.ftag;
					Bullet[lp][t].obj.vecPosition.z -= Bullet[lp][t].obj.ftag;
				}
				// �������x���ݒ肳��Ă����
				if(ItemDat[Bullet[lp][t].num].gSpeed > 0){
					if(Bullet[lp][t].num != ZIRAI || Bullet[lp][t].num == ZIRAI && Bullet[lp][t].tag == FALSE){
						Bullet[lp][t].gs += Bullet[lp][t].g;
						Bullet[lp][t].a -= Bullet[lp][t].gs;
						LimitsMaxMin(Bullet[lp][t].a, -MAX_G, MAX_G);
						Bullet[lp][t].obj.vecPosition.y += Bullet[lp][t].a;
					}
					// �n���Ȃ�n�ʂ܂ŗ���
					if(Bullet[lp][t].num == ZIRAI){
						if(RayIntersect(&Bullet[lp][t].obj, &StageDat.obj, &fDistance, &vIntersect, &Ray[RAY_UE])){
							if(fDistance <= MAX_G){
								Bullet[lp][t].obj.vecPosition.y = vIntersect.y;
								Bullet[lp][t].tag = TRUE;
							}
						}
					}
				}
				else{ // ���̑�y���W�ړ�
					if(Bullet[lp][t].num == MISSILE)
						Bullet[lp][t].obj.vecPosition.y -= ItemDat[Bullet[lp][t].num].tSpd * tanf(-Bullet[lp][t].obj.fPitch);
					else
						Bullet[lp][t].obj.vecPosition.y -= ItemDat[Bullet[lp][t].num].tSpd * tanf(Bullet[lp][t].obj.fPitch);
				}
				if(Bullet[lp][t].num == MISSILE && Bullet[lp][t].cnt*ItemDat[Bullet[lp][t].num].tSpd < ItemDat[Bullet[lp][t].num].Range / 2) // �~�T�C���Ȃ�ǔ�
					MissileMove(lp,t,Bullet[lp][t].Target);
			}
		}
		// �A�C�e������ ///////////////////////////////////
		for(i=0; i<ITEMMAX; i++){
			int iNum;
			iNum = Ch[lp].item[i].num;
			if(ItemDat[Ch[lp].item[i].num].type == SUBITEM){ // �A�C�e���̏ꍇ
				if(!Ch[lp].item[i].Timer)
					continue;
				Ch[lp].item[i].Timer--;
				if(Ch[lp].item[i].Timer > 0)
					continue;
				// ���ʏI��
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
					if(Ch[lp].item[i].rlTimer && Ch[lp].SelItem == i){ // �����[�h
						Ch[lp].item[i].rlTimer--;
						if(Ch[lp].item[i].rlTimer == 0){// ����
							// �T�E���h
							playASound(&g_SE[SD_RL],0 , 0L ,TRUE);
					
							Ch[lp].item[i].tama = Ch[lp].item[i].maxtama;
						}
					}
					break;
				case RORABUREDO: // ���[���u���[�h
					Ch[lp].SpdUp  -= UP_SPD;
					Ch[lp].TurnUp -= UP_TURN;
					break;
				case GETA:// ����
					Ch[lp].SpdUp  += DOWN_SPD;
					Ch[lp].TurnUp += DOWN_TURN;
					break;
				case TESTITEM1: // �W�����v�A�b�v
					Ch[lp].JumpUp -= UP_JUMP;
					break;
				case TESTITEM2: // �U���A�b�v
					Ch[lp].AtkUp -= UP_ATK;
					break;
				case TESTITEM3: // �h��A�b�v
					Ch[lp].DefUp -= UP_DEF;
					break;
				case KAN: // ���V
					if(!(Ch[lp].item[2].num == KAN && Ch[lp].item[2].Timer || Ch[lp].item[3].num == KAN && Ch[lp].item[3].Timer)){
						Ch[lp].JpFlg = RAKKA;
						Ch[lp].Mfloat = 0;
						Ch[lp].Ffloat = 0;
					}
					break;
				case INBIZI: // ����
					Ch[lp].Visible = TRUE;
				default:
					break;
			}
		}
	}

	return 0;
}
//------------------------//
//  �e�Ə�Q���̃��C����  //
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
//  �e����Q���ɓ�������  //
//------------------------//
void BulletHitObstacle(int lp, int t)
{
	int rt;
	rt = WeponEffect_Bunretsu(lp, t, 100, BAKURETSU, BAKURETSU_2);
	// �������ݒ肳��Ă���
	if(ItemDat[Bullet[lp][t].num].bMax > 0)
		SetBlast(lp, t);
	else if(rt == -1)
		playASound(&g_SE[SD_HIT3],0 , 0L ,TRUE);
	// �e�I��
	Bullet[lp][t].num = 0;
	Bullet[lp][t].tag = 0;
}
//------------//
//  �������  //
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
//  �e���􏈗�  //
//--------------//
int WeponEffect_Bunretsu(int lp, int t, int shotMax, int wnum, int wtag)
{
	if(Bullet[lp][t].num == wnum && !Bullet[lp][t].tag){
		playASound(&g_SE[SD_SHOT14],0 , 0L ,TRUE);
		int shotCnt=0;
		for(int b=0; b<=BULLETMAX; b++){
			if(Bullet[lp][b].num == NULL){ // �e�i�[�z��ɋ󂫂���B
				ObjectPositionCopy(&Bullet[lp][b].obj, &Bullet[lp][t].obj);
				shotCnt++;
				// ���p�x
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
//  �����^�C�}      //
//------------------//
int BlastTimer(void)
{
	int lp;
	for(lp=0; lp<=gNinzu ; lp++){
		for(int t=0 ; t<BLASTMAX;t++){
			if(Blast[lp][t].num == NULL)continue;
			if(Blast[lp][t].obj.fScale >= ItemDat[Blast[lp][t].num].bMax*2){
				// �����I��
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
//  �g���b�v�^�C�}  //
//------------------//
int TrapTimer(void)
{
	for(int i=0; i<Syougaisu; i++){
		if(StageDat.trap[i].type == TYPE_DOKU){ // �ňړ�
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
			// �łƂ̓����蔻��
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
		else if(StageDat.trap[i].type == TYPE_BETA){// �G���x�[�^�[
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
		else if(StageDat.trap[i].type == TYPE_MOUNT){ // �ΎR
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
//  �U���_���[�W����  //
//--------------------//
VOID Calcdmg(int c, int cc, int type, int t)
{
	if(Ch[cc].alive == FALSE)
		return;

	int dmg;
	int vx, vy, vt=0, st;
	switch(type){
		case JUMPDMG: // �W�����v�U��
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
		case DAGEDMG: // �Ō��U��
				dmg = (ChDat[Ch[c].num].nAtack + Ch[c].AtkUp) - (ChDat[Ch[cc].num].nGard + Ch[cc].DefUp);
				if(dmg <= 0)
					dmg = 10;
				vx = 10000;
				st = 2;
				vt = 10;
			break;
		case WANADMG: // 㩂ɂ͂܂���
			dmg = 20;
			vt = st = WANASTOP;
			StageDat.trap[c].Visible = FALSE;
			vx = 3000;
			vy = -3000;
			break;
		case SHOTDMG: // �e�ɓ��������Bcc��
			dmg = ItemDat[Bullet[c][t].num].atk - ChDat[Ch[cc].num].nGard;
			if(dmg <= 0)
				dmg = 10;
			vx = 10000;
			st = 3;
			vt = 15;

			Bullet[c][t].num = 0;
			Bullet[c][t].obj.Visible = FALSE;
			break;
		case DOKUDMG: // �ŏ�������
			dmg = 2;
			st = 0;
			break;
		case BLASTDMG: //�����ɓ�������
			dmg = 5;
			vt = 1;
			vx = 4000;
			vy = -4000;
			st = 0;
			break;
	}
	Ch[cc].hp -= dmg;
	Ch[cc].dmg += dmg;
	if(Ch[cc].hp <= 0) // ����
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
//  ���񂾎��̏���  //
//------------------//
void CharaDied(int cc, int vx, int vy, int vt)
{
	// �T�E���h
	playASound(&g_SE[SD_DEATH],0 , 0L ,TRUE);

	Ch[cc].hp = 0;
	Ch[cc].alive = FALSE;
	Ch[cc].Dageki.Visible = FALSE;
	Ch[Ch[cc].LockOnFlg].LockOnNum = 0;
	Ch[cc].LockOnFlg = 0;
	
	vx *= 2;
	vy *= 2;
	vt *= 2;

	// �e����
	for(int i=0; i<BULLETMAX; i++){
		if(Bullet[cc][i].num){
			Bullet[cc][i].num = 0;
			Bullet[cc][i].obj.Visible = FALSE;
		}
	}
	// �A�C�R���o�Ă������
	if(Ch[cc].IconFlg == TRUE){
		Ch[cc].IconFlg = FALSE;
		ReleaseObject(&Ch[cc].Iconobj);
	}

	// ���s����
	AliveCnt--;
	if(GameMode == ROYALE_MODE){
		Ch[cc].rank = AliveCnt+1;
		if(AliveCnt == 1){
			for(int i=1; i<=gNinzu; i++) // 1�ʌ���
				if(Ch[i].alive == TRUE)
					Ch[i].rank = 1;
			ChangeDrawingMode(RESULTWINDOW, gNinzu, NULL);
		}
	}
	else{ // �`�[����
		// ���ʌ���
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
//  �g�ǂݍ��� //
//-------------//
int ReadFrame(int n)
{
	// �g�ǂݍ���
	char fname[128];
	wsprintf(fname, "./pic/bar%d.png", n);
	TextureFromFile(fname, &pBar);

	return 0;
}