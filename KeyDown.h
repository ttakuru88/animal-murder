//------------------//
//  文字キーダウン  //
//------------------//
int KeyChara(WPARAM key)
{
	if(DrawingMode != BATTLEWINDOW)
		return -1;

	switch(key){
		// キャラ全回復
		case '1': case '2': case '3': case '4':
			int lp;
			lp = key-'0';
			if(GameMode==TEAM_MODE && Ch[lp].alive == FALSE){
				char fname[256];
				wsprintf(fname, "./X/icon/teamC%d.x", Ch[lp].Team);		
				InitThing(&Ch[lp].Iconobj, fname, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), FALSE, TYPE_ICON);
				Ch[lp].IconFlg = TRUE;
			}
			Ch[lp].alive = TRUE;
			Ch[lp].hp = Ch[lp].maxhp;
			Ch[lp].st = Ch[lp].maxst;
			
			break;
		// ステージチェンジ
		case '5': case '6': case '7': case '8': case '9':
			if(KeyMode == FALSE)
				ChangeStage(key-4-'0');
			break;
		case 't':
			if(KeyMode == FALSE)
				ChangeStage(6);
			break;
		case 'y':
			if(KeyMode == FALSE)
				ChangeStage(7);
			break;
		case 'u':
			if(KeyMode == FALSE)
				ChangeStage(8);
			break;
		case 'i':
			if(KeyMode == FALSE)
				ChangeStage(9);
			break;
		case 'o':
			if(KeyMode == FALSE)
				ChangeStage(10);
			break;
		// フィルモード
		case '0': pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);     break;
		case '-': pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); break;
		// BGM変更
		case 'q': playAMusic(&g_BGM[1]); break;
		case 'w': playAMusic(&g_BGM[2]); break;
		case 'e': playAMusic(&g_BGM[3]); break;
		case 'r': playAMusic(&g_BGM[4]); break;
		case 'a': ChangeCharaByKey(1);   break;
		case 's': ChangeCharaByKey(2);   break;
		case 'd': ChangeCharaByKey(3);   break;
		case 'f': ChangeCharaByKey(4);   break;
		case 'g': ChangeCharaByKey(5);   break;
		case 'h': ChangeCharaByKey(6);   break;
		case 'j': ChangeCharaByKey(7);   break;
		case 'k': ChangeCharaByKey(8);   break;
	}
	
	return 0;
}
//--------------//
//  キーダウン  //
//--------------//
int KeyDown(WPARAM key)
{
	if(KeyMode == FALSE)
		return -1;

	switch(key){
		case VK_LEFT: Joy[KeyChar].LX=-120; break;
		case VK_RIGHT:Joy[KeyChar].LX=120;  break;
		case VK_UP:   Joy[KeyChar].LY=-120; break;
		case VK_DOWN: Joy[KeyChar].LY=120;  break;
		case VK_SPACE: ON_START(KeyChar);   break;
		case VK_RETURN:
		case VK_F2: ON_RR(KeyChar); break;
		case VK_F1: ON_RU(KeyChar); break;
		case VK_F3: ON_RD(KeyChar); break;
		case VK_F4: ON_RL(KeyChar); break;
		case VK_F7:  KeyChar=1; break;
		case VK_F8: KeyChar=2; break;
		case VK_F9: KeyChar=3; break;
		case VK_F11: KeyChar=4; break;
		case VK_NUMPAD1: ON_L1(KeyChar); break;
		case VK_NUMPAD3: ON_R1(KeyChar); break;
		case VK_NUMPAD7: ON_L2(KeyChar); break;
		case VK_NUMPAD9: ON_R2(KeyChar); break;
		case VK_NUMPAD2: Joy[KeyChar].RY=80; break;
		case VK_NUMPAD4: Joy[KeyChar].RX=-80;break;
		case VK_NUMPAD6: Joy[KeyChar].RX=80; break;
		case VK_NUMPAD8: Joy[KeyChar].RY=-80;break;
		case VK_F5: ON_L3(KeyChar); break;
		case VK_F6: ON_R3(KeyChar); break;
	}
	
	return 0;
}
//--------------//
//  キーアップ  //
//--------------//
int KeyUp(WPARAM key)
{
	if(KeyMode == FALSE)
		return -1;

	switch(key){
		case VK_LEFT: Joy[KeyChar].LX=-1;  break;
		case VK_RIGHT:Joy[KeyChar].LX=-1;  break;
		case VK_UP:   Joy[KeyChar].LY=-1;  break;
		case VK_DOWN: Joy[KeyChar].LY=-1;  break;
		case VK_SPACE: OFF_START(KeyChar);break;
		case VK_RETURN:
		case VK_F2: OFF_RR(KeyChar); break;
		case VK_F1: OFF_RU(KeyChar); break;
		case VK_F3: OFF_RD(KeyChar); break;
		case VK_F4: OFF_RL(KeyChar); break;
		case VK_NUMPAD1: OFF_L1(KeyChar); break;
		case VK_NUMPAD3: OFF_R1(KeyChar); break;
		case VK_NUMPAD7: OFF_L2(KeyChar); break;
		case VK_NUMPAD9: OFF_R2(KeyChar); break;
		case VK_NUMPAD2: Joy[KeyChar].RY=-1;break;
		case VK_NUMPAD4: Joy[KeyChar].RX=-1;break;
		case VK_NUMPAD6: Joy[KeyChar].RX=-1;break;
		case VK_NUMPAD8: Joy[KeyChar].RY=-1;break;
		case VK_F5: OFF_L3(KeyChar); break;
		case VK_F6: OFF_R3(KeyChar); break;
	}
	
	return 0;
}
//------------------//
//  キャラチェンジ  //
//------------------//
void ChangeCharaByKey(int i)
{
	for(int j=0; j<Ch[1].Xcnt; j++)
		if(SubX[Ch[1].num][j][0] != '\0')
			if(Ch[1].obj[j].Mesh.dwNumMaterials)
				ReleaseObject(&Ch[1].obj[j]);
	Ch[1].Xcnt = 0;
	Ch[1].num = i;
	for(int j=0; j<SUBXCNT; j++){
		if(SubX[i][j][0] != '\0'){
			char buf[256];
			wsprintf(buf, "%s%s", CharXDir, SubX[i][j]);
			InitThing(&Ch[1].obj[Ch[1].Xcnt++], buf, &D3DXVECTOR3(10.0f, 0.0f, 0.0f), TRUE, TYPE_CHAR);
		}
	}
	if(Ch[1].Dageki.Mesh.dwNumMaterials)
		ReleaseObject(&Ch[1].Dageki);
	InitThing(&Ch[1].Dageki, ChDat[i].dAtack, &D3DXVECTOR3(10.0f, 0.0f, 0.0f), FALSE, TYPE_CHAR);

	if(Ch[1].SelItem==1)
		ChangeCharaMesh(1, Ch[1].item[1].num);
}
