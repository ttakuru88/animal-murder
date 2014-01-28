//----------------//
//  ミサイル移動  //
//----------------//
int MissileMove(int lp,int t,int target)
{
	float x, z, y, teki, zibun;
	VecAlterAngle(&x, &y, &z, lp,t, target, &teki, &zibun);

	// 横移動 ///

	if(teki>=0 && zibun>=0 || teki<=0 && zibun<=0){
		if(teki >= zibun)
			Bullet[lp][t].obj.fYaw += LOOKLEFT * Movebalc(teki,zibun);// 左
		else
			Bullet[lp][t].obj.fYaw += LOOKRIGHT * Movebalc(teki,zibun);// 右
	}
	else if(teki >= 0 && zibun <= 0){
		if(teki-zibun >= 1)
			Bullet[lp][t].obj.fYaw += LOOKRIGHT * Movebalc(teki,zibun);// 右
		else
			Bullet[lp][t].obj.fYaw += LOOKLEFT * Movebalc(teki,zibun);// 左
	}
	else if(teki <= 0 && zibun >= 0){
		if(teki-zibun < -1)
			Bullet[lp][t].obj.fYaw += LOOKLEFT * Movebalc(teki,zibun);// 左
		else
			Bullet[lp][t].obj.fYaw += LOOKRIGHT * Movebalc(teki,zibun);// 右
	}
	else
		Bullet[lp][t].obj.fYaw += -1;

	if(Bullet[lp][t].obj.fYaw > PI)
		Bullet[lp][t].obj.fYaw -= (float)(2*PI);
	if(Ch[lp].obj[Ch[lp].NowX].fYaw < -PI)
		Ch[lp].obj[Ch[lp].NowX].fYaw += (float)(2*PI);

	// 縦移動  /////
	y = Bullet[lp][t].obj.vecPosition.y - (Ch[target].obj[Ch[target].NowX].vecPosition.y+Ch[target].obj[Ch[target].NowX].BBox.fLengthY/2);
	teki = y/sqrtf(x*x+y*y);
	teki = teki/(float)PI;
	zibun = sinf(Bullet[lp][t].obj.fPitch);
	if(teki>=0 && zibun>=0 || teki<=0 && zibun<=0){
		if(teki > zibun)
			Bullet[lp][t].obj.fPitch += PITCHDOWN * Movebalc(teki,zibun); // 
		else 
			Bullet[lp][t].obj.fPitch += PITCHUP * Movebalc(teki,zibun);  // 右
	}
	else if(teki >= 0 && zibun <= 0){
		if(teki-zibun >= 1)
			Bullet[lp][t].obj.fPitch += PITCHUP * Movebalc(teki,zibun); // 左
		else
			Bullet[lp][t].obj.fPitch += PITCHDOWN * Movebalc(teki,zibun);  // 右
	}
	else if(teki <= 0 && zibun >= 0){
		if(teki-zibun < -1)
			Bullet[lp][t].obj.fPitch += PITCHDOWN * Movebalc(teki,zibun); // 左
		else
			Bullet[lp][t].obj.fPitch += PITCHUP * Movebalc(teki,zibun);  // 右
	}
	if (Bullet[lp][t].obj.fPitch > PI/2 )
		Bullet[lp][t].obj.fPitch = (float)(PI/2);
	if(Bullet[lp][t].obj.fPitch < -PI/2 )
		Bullet[lp][t].obj.fPitch = -(float)(PI/2);

	Bullet[lp][t].obj.fPitch = -1*Bullet[lp][t].obj.fPitch;
	return 0;
}
//--------------------//
//  ミサイル角度計算  //
//--------------------//
int VecAlterAngle(float *x, float *y, float *z, int lp,int t, int target, float *teki, float *zibun)
{
	*x = Bullet[lp][t].obj.vecPosition.x - Ch[target].obj[Ch[target].NowX].vecPosition.x;
	*z = Bullet[lp][t].obj.vecPosition.z - Ch[target].obj[Ch[target].NowX].vecPosition.z;
	*y = Bullet[lp][t].obj.vecPosition.y - Ch[target].obj[Ch[target].NowX].vecPosition.y;
	*teki = acosf((*z)/sqrtf((*x)*(*x)+(*z)*(*z)));
	*teki = *teki/(float)PI;
	if(*x > 0)
		*teki = *teki*-1;
	*zibun = -Bullet[lp][t].obj.fYaw/(float)PI;

	return 0;
}
//----------------------//
//  距離により角度変更  //
//----------------------//
float Movebalc(float pit, float yaw)
{
	float sa;
	sa = fabsf(pit-yaw);

	if(sa>0.2f)
		return 0.3f;
	else if(sa > 0.1f)
		return 0.1f;
	else if(sa > 0.05f)
		return 0.06f;
	else if(sa > 0.01f)
		return 0.04f;
	else if(sa > 0.005f)
		return 0.02f;
	else if(sa > 0.001f)
		return 0.01f;
	else 
		return 0;
}