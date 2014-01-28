//--------------------//
//  コンピュータ入力  //
//--------------------//
int cpuInput(int lp)
{
	// 前進
	if(Ch[lp].collision == -1)
		Joy[lp].LY = -120;
	else{ // 衝突
		if(Ch[lp].collision == RAY_MAE){
			Joy[lp].LY = 120;
			Joy[lp].LX = 120*((rand()%2)?1:-1);
		}
		else if(Ch[lp].collision == RAY_MIGI)
			Joy[lp].LX = -120;
		else if(Ch[lp].collision == RAY_HIDARI)
			Joy[lp].LX = 120;
		if(!(rand()%3))
			ON_R1(lp);
		else
			OFF_R1(lp);
	}
	// ダッシュ
	if(Ch[lp].st > Ch[lp].maxst/2+20)
		ON_L1(lp);
	else if(Ch[lp].st < Ch[lp].maxst/2)
		OFF_L1(lp);
	
	// ターゲット決定
	int target, oltarget;
	float x, z, y, teki, zibun, xz, MinDist;
	target=0;
	MinDist=0;
	for(int i=1; i<=gNinzu; i++){
		if(i==lp || Ch[i].alive==FALSE || Ch[i].Team==Ch[lp].Team) continue;
		GetMinDist(lp, &target, &MinDist, &Ch[i].obj[Ch[i].NowX], i);
	}
	if(!target)
		target = 1;
	oltarget = target;
	
	if(MinDist > CPUCENSER){
		if(Ch[lp].item[1].num == NULL)// 武器取りに行く場合
			CpuGetItem(lp, WEPON, &target, oltarget, &x, &y, &z, &teki, &zibun);
		else if(Ch[lp].item[2].num == NULL || Ch[lp].item[3].num == NULL) // アイテム取りに行く
			CpuGetItem(lp, SUBITEM, &target, oltarget, &x, &y, &z, &teki, &zibun);
	}
	// XZ方向転換
	if(target != GETITEM) // キャラクタへ
		VecAlterAngle(&x, &y, &z, lp, &Ch[target].obj[Ch[target].NowX], &teki, &zibun);

	if(teki>=0 && zibun>=0 || teki<=0 && zibun<=0){
		if(teki >= zibun)
			CpuMoveYaw(lp, LOOKLEFT, teki, zibun, MinDist);
		else
			CpuMoveYaw(lp, LOOKRIGHT, teki, zibun, MinDist);
	}
	else if(teki >= 0 && zibun <= 0){
		if(teki-zibun >= 1)
			CpuMoveYaw(lp, LOOKRIGHT, teki, zibun, MinDist);
		else
			CpuMoveYaw(lp, LOOKLEFT, teki, zibun, MinDist);
	}
	else if(teki <= 0 && zibun >= 0){
		if(teki-zibun < -1)
			CpuMoveYaw(lp, LOOKLEFT, teki, zibun, MinDist);
		else
			CpuMoveYaw(lp, LOOKRIGHT, teki, zibun, MinDist);
	}
	else
		Joy[lp].RX = -1;
	// Y座標カメラ移動
	xz = sqrtf(x*x+z*z);
	teki = y/sqrtf(xz*xz+y*y);
	zibun = sinf(Ch[lp].Camera.Pitch)/(float)(PI/2);
	if(teki < zibun)
		Joy[lp].RY = -MoveCalc(teki, zibun); // 左
	else if(teki > zibun)
		Joy[lp].RY = MoveCalc(teki, zibun);  // 右
	else
		Joy[lp].RY = -1;
	// ジャンプ
	if(Ch[lp].Stop)
		ON_R1(lp);
	else
		OFF_R1(lp);
	// 攻撃種類選択
	CpuSelAtackType(lp, x, y, z, target);
	// アイテム使用
	CpuUseItem(lp);
	//Joy[lp].LY=Joy[lp].LX=-1;
	return 0;
}
//----------------//
//  攻撃種類選択  //
//----------------//
void CpuSelAtackType(int lp, float x, float y, float z, int target)
{
	if(target != GETITEM){
		// 打つ
		ON_R2(lp);
		// 打撃
		y = Ch[lp].obj[Ch[lp].NowX].vecPosition.y - Ch[target].obj[Ch[target].NowX].vecPosition.y;
		if(sqrt(x*x+y*y)<0.5f && sqrt(z*z+y*y)<0.5f && sqrt(x*x+z*z)<0.5f)
			ON_L2(lp);
		else
			OFF_L2(lp);
	}
	else
		OFF_R2(lp);
}
//---------------------//
//  CPUのアイテム使用  //
//---------------------//
void CpuUseItem(int lp)
{
	int hit, use;
	use = hit = FALSE;
	for(int i=1; i<ITEMMAX; i++){
		if(Ch[lp].item[i].num){
			hit = i;
			if(i==1)// 武器
				use = TRUE;
			else if(i>1){ // アイテム
				switch(Ch[lp].item[i].num){
					case NIKU: // ダメージ受けてたら使用
						if(Ch[lp].maxhp > Ch[lp].hp)
							use = TRUE;
						break;
					case RORABUREDO:
					case TESTITEM1:
					case TESTITEM2:
					case TESTITEM3: // 使用済みならカーソル戻す
						if(Ch[lp].item[i].Timer<=0)
							use = TRUE;
						break;
				}
			}
			if(use == TRUE)
				break;
		}
	}
	if(!hit || use==FALSE){ // カーソル戻し
		OFF_RD(lp);
		OFF_RL(lp);
		OFF_RR(lp);
		ON_RU(lp);
	}
	else if(use==TRUE){
		OFF_RU(lp);
		if(hit == 1)
			ON_RR(lp);
		if(hit == 2)
			ON_RD(lp);
		else if(hit == 3)
			ON_RL(lp);
	}
}
//----------------------//
//  アイテム取りに行く  //
//----------------------//
void CpuGetItem(int lp, int Itype, int *target, int oltarget, float *x, float *y, float *z, float *teki, float *zibun)
{
	float MinDist = 0;
	*target = -1;

	for(int i=0; i<StageItemMax; i++)
		if(ItemDat[StageDat.item[i].num].type==Itype && StageDat.item[i].obj.Visible == TRUE)
			GetMinDist(lp, target, &MinDist, &StageDat.item[i].obj, i);
	if(*target == -1)
		*target = oltarget;
	else{
		VecAlterAngle(x, y, z, lp, &StageDat.item[*target].obj, teki, zibun);
		*target = GETITEM;
	}
}
//----------------//
//  近い物体探す  //
//----------------//
void GetMinDist(int lp, int *target, float *MinDist, THING *Target, int i)
{
	float x, z, y, xz;

	x = Ch[lp].obj[Ch[lp].NowX].vecPosition.x - Target->vecPosition.x;
	z = Ch[lp].obj[Ch[lp].NowX].vecPosition.z - Target->vecPosition.z;
	y = Ch[lp].obj[Ch[lp].NowX].vecPosition.y - Target->vecPosition.y;
	xz = sqrtf(x*x+z*z);
	y = sqrtf(y*y+xz*xz);
	if(!(*MinDist) || *MinDist>y){
		*MinDist = y;
		*target = i;
	}
}
//--------------//
//  CpuYaw移動  //
//--------------//
void CpuMoveYaw(int lp, int VEC, float Ateki, float Azibun, float dist)
{
	Joy[lp].RX = VEC * MoveCalc(Ateki, Azibun); // 左
	if(Ch[lp].collision == -1){
		Joy[lp].LX = -Joy[lp].RX;
		if(fabs(Ateki-Azibun) > 0.5f || dist > 2.0f)
			Joy[lp].LY = abs(Joy[lp].LX)-120;
		else if(abs(Joy[lp].LX) <= 30)
			Joy[lp].LY = -120;
		else{
			Joy[lp].LY = 0;
			Joy[lp].LX = 0;
		}
	}
}
//--------------------------//
//  ベクトルから角度を出す  //
//--------------------------//
void VecAlterAngle(float *x, float *y, float *z, int lp, THING* Target, float *teki, float *zibun)
{
	*x = Ch[lp].obj[Ch[lp].NowX].vecPosition.x - Target->vecPosition.x;
	*z = Ch[lp].obj[Ch[lp].NowX].vecPosition.z - Target->vecPosition.z;
	*y = (Ch[lp].obj[Ch[lp].NowX].vecPosition.y+2.5f) - Target->vecPosition.y;
	*teki = acosf((*z)/sqrtf((*x)*(*x)+(*z)*(*z))) / (float)PI;
	if(*x > 0)
		*teki = *teki*-1;
	*zibun = -Ch[lp].obj[Ch[lp].NowX].fYaw/(float)PI;
}
//------------------//
//  動きの早さ計算  //
//------------------//
int MoveCalc(float pit, float yaw)
{
	float sa;
	sa = fabsf(pit-yaw);

	if(sa>0.2f)
		return 120;
	else if(sa > 0.1f)
		return 80;
	else if(sa > 0.01f)
		return 60;
	else if(sa > 0.005)
		return 30;
	else if(sa > 0.001f)
		return 10;
	else if(sa > 0.0001f)
		return 1;
	else 
		return 0;
}
//--------------------//
//  アイコンチェンジ  //
//--------------------//
int CpuIconChange(int lp, int inum)
{
	if(Ch[lp].cpuIcon[inum] == FALSE)
		Ch[lp].IconFlg = FALSE;

	for(int i=0; i<4; i++){
		if(i==inum)
			Ch[lp].cpuIcon[i] = TRUE;
		else
			Ch[lp].cpuIcon[i] = FALSE;
	}

	return 0;
}