//------------------------//
//  ダイレクト3Dの初期化  //
//------------------------//
HRESULT InitD3d(HWND hWnd)
{
	// 「Direct3D」オブジェクトの作成
	if(NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION))){
		MessageBox(0, "Direct3Dの作成に失敗しました", "", MB_OK);
        return E_FAIL;
	}

	// 「DIRECT3Dデバイス」オブジェクトの作成
	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );   
	d3dpp.BackBufferCount=1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.BackBufferFormat =D3DFMT_UNKNOWN;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	 if( FAILED( pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDevice ) ) ){	
		if( FAILED( pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pDevice ) ) ){
			MessageBox(0,"DIRECT3Dデバイスの作成に失敗しました",NULL,MB_OK);
			 return E_FAIL;
		}
    }
//////////////////////////////////////////////////////////////////////////////
	//文字列レンダリングの初期化
	if(FAILED(D3DXCreateFont(pDevice,0,10,FW_REGULAR,	NULL,	FALSE,SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,PROOF_QUALITY,FIXED_PITCH | FF_MODERN, "tahoma", &pFont))) return E_FAIL;
	//////////////////////////////////////////////////////////////////////////////
    pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );      // Zバッファー処理を有効にする
	pDevice->SetRenderState( D3DRS_AMBIENT, 0x00111111 );// アンビエントライト（環境光）を設定する
	pDevice->SetRenderState(D3DRS_SPECULARENABLE,TRUE);  // スペキュラ（鏡面反射）を有効にする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);// カリングする
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // アルファ・ブレンディングを行う
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); // 透過処理を行う

	// ライトをあてる 白色で鏡面反射ありに設定	
	D3DXVECTOR3 vecDirection(1, -1, 1);
	D3DLIGHT9 light;
	ZeroMemory( &light, sizeof(D3DLIGHT9) );
	light.Type       = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.a  = light.Diffuse.r  = light.Diffuse.g  = light.Diffuse.b  = 1.0f;
	light.Specular.a = light.Specular.r = light.Specular.g = light.Specular.b = 1.0f;
	light.Ambient.a = light.Ambient.r = light.Ambient.g = light.Ambient.b= 1.0f;
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDirection );
	light.Range = 100.0f;
	pDevice->SetLight(0, &light);
	pDevice->LightEnable(0, TRUE); 
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);     // ライトを有効にする
	
	//FSAAで多少でもぼかす
	pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);

	pDevice->GetViewport(&g_VP);// ビュー初期化

	LoadTexture(hWnd); // ２D読み込み

	return S_OK;
}
//---------------------//
//  Xファイル読み込み  //
//---------------------//
HRESULT InitThing(THING *pThing,LPSTR szXFileName,D3DXVECTOR3* pvecPosition, BOOL VisibleT, int typeT)
{
	// メッシュの初期位置
	memcpy(&pThing->vecPosition,pvecPosition,sizeof(D3DXVECTOR3));
	// Xファイルからメッシュをロードする	
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
	// 可視か
	pThing->Visible = VisibleT;
	pThing->type = typeT;

	if( FAILED( D3DXLoadMeshFromX( szXFileName, D3DXMESH_SYSTEMMEM, 
		pDevice, NULL, &pD3DXMtrlBuffer, NULL, &pThing->Mesh.dwNumMaterials, &pThing->Mesh.pMesh ) ) ){
			
		char buf[512];
		wsprintf(buf, "| %s | Xファイルの読み込みに失敗しました", szXFileName);
		MessageBox(NULL, buf,szXFileName, MB_OK);
		return E_FAIL;   
    }
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	pThing->Mesh.Materials = new D3DMATERIAL9[pThing->Mesh.dwNumMaterials];
    pThing->Mesh.Textures  = new LPDIRECT3DTEXTURE9[pThing->Mesh.dwNumMaterials];

	for( DWORD i=0; i<pThing->Mesh.dwNumMaterials; i++ ){
		pThing->Mesh.Materials[i] = d3dxMaterials[i].MatD3D;	
		pThing->Mesh.Materials[i].Ambient = pThing->Mesh.Materials[i].Diffuse;
		pThing->Mesh.Textures[i] = NULL;
		if( d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlen(d3dxMaterials[i].pTextureFilename) > 0 ){
			if( FAILED( D3DXCreateTextureFromFile( pDevice, d3dxMaterials[i].pTextureFilename, &pThing->Mesh.Textures[i]))){
				char buf[512];
				wsprintf(buf, "|%s|のテクスチャの読み込みに失敗しました。", szXFileName);
				MessageBox(NULL, buf, NULL, MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();

	InitBBox(pThing);
	InitSphere(pThing);

	return S_OK;
}
//------------------//
//  メッシュの描画  //
//------------------//
VOID RenderThingBlur(THING* pThing, int lp, int show, MESHSTRUCT *lpMesh)
{
	UINT i;	
	D3DXMATRIXA16 matProj;

	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/(4*Chpt[lp]->zoom), g_aspect, 0.1f, 1000.0f );
	pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	// レンダリング
	D3DXVECTOR3 Pos = pThing->vecPosition;
	D3DXMATRIX matPos = pThing->matPosition;
	D3DXMATRIX matRot = pThing->matRotation;
	D3DXMATRIX matYaw = pThing->matYaw;
	D3DXMATRIX matPitch = pThing->matPitch;
	FLOAT Yaw = pThing->fYaw;
	FLOAT Pitch = -pThing->fPitch;
	FLOAT Scale = pThing->fScale;
	D3DXMATRIX matScale;
	D3DXMatrixIdentity(&matScale); // 単位行列に初期化
	if(show == TYPE_BLAST)
		D3DXMatrixScaling(&matScale, Scale, Scale, Scale);
	if(pThing->type == TYPE_SITE)
		Pos.y += 0.3f;
	//ワールドトランスフォーム（絶対座標変換）
	matRot *= matScale;
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationX(&matPitch, Pitch);
	D3DXMatrixRotationY(&matYaw, Yaw);
	matRot *= matPitch * matYaw;
	D3DXMatrixTranslation(&matPos, Pos.x, Pos.y, Pos.z);
	D3DXMatrixMultiply(&matWorld, &matRot, &matPos);
	pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	for(i=0; i<lpMesh->dwNumMaterials; i++){
		D3DMATERIAL9 Mat = lpMesh->Materials[i];
		// マテリアル設定
		if(pThing->type == TYPE_CHAR){
			if(Ch[show].Visible == FALSE) // キャラ透明になってる
				Mat.Diffuse.a = 0.3f;
			if(GameMode == TEAM_MODE){ // チームカラーに配色
				switch(Ch[show].Team){
					case 1: Mat.Emissive.r = 0.2f; break;
					case 2: Mat.Emissive.r = Mat.Emissive.g = 0.2f; break;
					case 3: Mat.Emissive.b = 0.2f; break;
					case 4: Mat.Emissive.r = Mat.Emissive.g = Mat.Emissive.b = 0.2f;
				}
			}
		}
		pDevice->SetMaterial(&Mat);
		pDevice->SetTexture(0, lpMesh->Textures[i]);
		lpMesh->pMesh->DrawSubset(i);
	}
}
//------------//
//  画面分割  //
//------------//
void SetViewMatrix(int vi, PLAYERCHARASTATE *aCh)
{
	// ビュートランスフォーム（ワールド座標→カメラ座標への変換）
	if(vi != D2D_DRAW && vi != D2D_SEL){ // 3D描画のみ
		D3DXMATRIXA16 matView;
		D3DXMatrixIdentity(&matView);
		aCh->Camera.vecLookatPt.x = aCh->obj[aCh->NowX].vecPosition.x;
		aCh->Camera.vecLookatPt.z = aCh->obj[aCh->NowX].vecPosition.z;
		aCh->Camera.vecLookatPt.y = aCh->obj[aCh->NowX].vecPosition.y + 0.7f;

		aCh->Camera.vecEyePt.x = aCh->obj[aCh->NowX].vecPosition.x + 2 * sinf(aCh->Camera.Yaw);
		aCh->Camera.vecEyePt.z = aCh->obj[aCh->NowX].vecPosition.z + 2 * cosf(aCh->Camera.Yaw);
		aCh->Camera.vecEyePt.y = aCh->obj[aCh->NowX].vecPosition.y + 2 * sinf(aCh->Camera.Pitch);
		
		if (RayFooter(&StageDat.obj, &fDistance, &vIntersect, &aCh->Camera.vecLookatPt, &aCh->Camera.vecEyePt))
			if(fDistance<=0.7f)
				aCh->Camera.vecEyePt=vIntersect;

		D3DXMatrixLookAtLH( &matView, &aCh->Camera.vecEyePt, &aCh->Camera.vecLookatPt, &aCh->Camera.vecUp );
		pDevice->SetTransform( D3DTS_VIEW, &matView );
	}

}
//--------------//
//  ビュー行列  //
//--------------//
VOID SendView(VIEW4 vw, int player, int w1, int w2, int h1, int h2, HWND hWnd)
{
	SetViewMatrix(vw, Chpt[(vw==LEFT_DOWN && Ninzu==2)?2:vw]);
	switch(player){
		case 0:
		case 11:
		case 21:
		case 41: ChangeViewport(0, 0, w1, h1); break;
		case 42: ChangeViewport(w1, 0, w2, h1); break;
		case 22:
		case 43: ChangeViewport(0, h1, w1, h2); break;
		case 44: ChangeViewport(w1, h1, w2, h2); break;
	}
	if(vw != D2D_DRAW)
		pDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(10,10,200), 1.0f, 0 );
	if( SUCCEEDED( pDevice->BeginScene() ) ){
		if(vw < D2D_DRAW){
			int lp;
			lp = player - player/10*10;
			//フィールド
			RenderThingBlur(&StageDat.obj, lp, TRUE, &StageDat.obj.Mesh);
			// キャラクタ
			for(int i=1; i<=gNinzu; i++){
				if(Ch[i].alive == TRUE && Ch[i].Visible==TRUE || Ch[i].alive == TRUE && lp == i){ // 生きてるキャラ
					Ch[i].obj[Ch[i].NowX].vecPosition.y += Ch[i].Mfloat;
					RenderThingBlur(&Ch[i].obj[Ch[i].NowX], lp, i, &Ch[i].obj[Ch[i].NowX].Mesh);
					Ch[i].obj[Ch[i].NowX].vecPosition.y -= Ch[i].Mfloat;
				}
			}
			// 打撃
			for(int i=1; i<=gNinzu; i++)
				if(Ch[i].Dageki.Visible == TRUE)
					RenderThingBlur(&Ch[i].Dageki, lp, FALSE, &Ch[i].Dageki.Mesh);
			// アイテム
			for(int i=0; i<StageItemMax; i++)
				if(StageDat.item[i].num)
					if(StageDat.item[i].obj.Visible == TRUE)
						RenderThingBlur(&StageDat.item[i].obj, lp, FALSE, &StageDat.item[i].obj.Mesh);
			// 弾
			for(int c=0; c<=gNinzu; c++)
				for(int i=0; i<BULLETMAX; i++)
					if(Bullet[c][i].num)
						RenderThingBlur(&Bullet[c][i].obj, lp, TYPE_TAMA, &BulletObj[ItemDat[Bullet[c][i].num].tnum].Mesh);
			// 爆風
			for(int c=0; c<=gNinzu; c++)
				for(int i=0; i<BLASTMAX;i++)
					if(Blast[c][i].num)
						RenderThingBlur(&Blast[c][i].obj, lp, TYPE_BLAST, &BlastObj.Mesh);
			// アイコン
			for(int c=1; c<=gNinzu; c++){
				if(Ch[c].IconFlg == TRUE){
					if(GameMode == ROYALE_MODE)
						RenderThingBlur(&Ch[c].Iconobj, lp, FALSE, &IconObj[Ch[c].IconNum].Mesh);
					else
						RenderThingBlur(&Ch[c].Iconobj, lp, FALSE, &Ch[c].Iconobj.Mesh);
				}
			}
			//ロックオンサイト
			for(int c=1; c<=gNinzu; c++)
				if(Ch[c].LockOnFlg && Chpt[lp]->LockOnNum)
					RenderThingBlur(&Ch[c].LockOnObj, lp, FALSE, &LockOnObj.Mesh);
			// 障害物
			for(int i=0; i<Syougaisu; i++)
				if(StageDat.trap[i].Visible == TRUE)
					RenderThingBlur(&StageDat.trap[i], lp, TRUE, &StageDat.trap[i].Mesh);

		}
		else if(vw == D2D_DRAW){
			if(DrawingMode == BATTLEWINDOW)
				DrawD2DBattle();
			else
				DrawD2DSelectSt(hWnd);
		}
		else if(vw == D2D_SEL)
			DrawD2DSelect(hWnd);
		else
			DrawD2DSelectSt(hWnd);

		pDevice->EndScene();
	}
}
//--------//
//  描画  //
//--------//
VOID Render()
{
	if(DrawingMode==BATTLEWINDOW || DrawingMode==MENUWINDOW || DrawingMode==RESULTWINDOW){
		if(Ninzu==1) // １プレイ
			SendView(LEFT_UP, 11, g_VP.Width, 0, g_VP.Height, 0, NULL);
		else if(Ninzu==2){ // ２人プレイ
			SendView(LEFT_UP, 21, g_VP.Width, 0, g_VP.Height/2, 0, NULL);// １プレイヤ
			SendView(LEFT_DOWN, 22, g_VP.Width, 0, g_VP.Height/2, g_VP.Height/2, NULL);// ２プレイヤ
		}
		else{
			///// ４、３人プレイ
			SendView(LEFT_UP, 41, g_VP.Width/2, 0, g_VP.Height/2, 0, NULL);// １プレイヤ
			SendView(RIGHT_UP, 42, g_VP.Width/2, g_VP.Width/2, g_VP.Height/2, 0, NULL);// ２プレイヤ
			SendView(LEFT_DOWN, 43, g_VP.Width/2, 0, g_VP.Height/2, g_VP.Height/2, NULL);// ３プレイヤ
			if(Ninzu==4)
				SendView(RIGHT_DOWN, 44, g_VP.Width/2, g_VP.Width/2, g_VP.Height/2, g_VP.Height/2, NULL);// ４プレイヤ
		}
		// CPUのカメラ移動
		for(int i=1; i<=gNinzu; i++)
			if(Ch[i].cpu==TRUE)
				SetViewMatrix(i, &Ch[i]);
	}
	// 2次元描画
	SendView(D2D_DRAW, 0, g_VP.Width, 0, g_VP.Height, 0, NULL);

	pDevice->Present( NULL, NULL, NULL, NULL );
}
//------------------------//
//  ビューポート切り替え  //
//------------------------//
HRESULT ChangeViewport(DWORD dwX,DWORD dwY,DWORD dwWidth,DWORD dwHeight)
{
	D3DVIEWPORT9 vp;

	vp.X=dwX;
	vp.Y=dwY;
	vp.Width=dwWidth;
	vp.Height=dwHeight;
	vp.MinZ=0;
	vp.MaxZ=1;	

	 if(FAILED(pDevice->SetViewport(&vp))){
		 MessageBox(0,"ビューポート切り替え失敗","エラー",MB_OK);
		 return E_FAIL;
	 }
	return S_OK;
}
//--------------//
//  障害物設置  //
//--------------//
void ChangeStage(int Stage)
{
	if(StageDat.obj.Mesh.dwNumMaterials){
		ReleaseObject(&StageDat.obj);
		for(int i=0; i<Syougaisu; i++) // 障害物
			ReleaseObject(&StageDat.trap[i]);
		for(int i=0; i<StageItemMax; i++) // アイテム、スフィア
			ReleaseObject(&StageDat.item[i].obj);
	}
	// ステージ読み込み
	InitThing(&StageDat.obj,StageFile[Stage-1].X,&D3DXVECTOR3(0, 0, 0), TRUE, TYPE_FIELD);

	// 罠やアイテムの設置
	switch(Stage){
		case 1: // 岩
		case 2: // 森
		case 3: // 海
		case 4: // 空
		case 5: // 屋敷
		case 6: // ?
		case 9:
			Syougaisu = 5;
			for(int i=0; i<Syougaisu; i++)
				InitThing(&StageDat.trap[i], "./X/trap/罠.x",&D3DXVECTOR3(float(rand()%3*((rand()%2)?1:-1)), 0.0f, float(rand()%3*((rand()%2)?1:-1))), TRUE, TYPE_TRAP);

			ItemPut( 0, PATINKO,  -1.0f, 0.0f, 3.0f);
			ItemPut( 1, ENKEI,     0.0f, 0.0f, 3.0f);
			ItemPut( 2, BAZUKA,    1.0f, 0.0f, 3.0f);
			ItemPut( 3, SYURYUDAN, 2.0f, 0.0f, 3.0f);
			ItemPut( 4, RORABUREDO,4.0f, 0.0f, 3.0f);
			ItemPut( 5, NIKU,      5.0f, 0.0f, 3.0f);
			ItemPut( 6, SHOTGUN,   6.0f, 0.0f, 3.0f);
			ItemPut( 7, GETA,      7.0f, 0.0f, 3.0f);
			ItemPut( 8, KARASI,    8.0f, 0.0f, 3.0f);
			ItemPut( 9, BAKURETSU, 9.0f, 0.0f, 3.0f);
			ItemPut(10, ZIRAI,    -2.0f, 0.0f, 3.0f);
			ItemPut(11, ZIKANSA,  -3.0f, 0.0f, 3.0f);
			ItemPut(12, TESTITEM1,-4.0f, 0.0f, 3.0f);
			ItemPut(13, TESTITEM2,-5.0f, 0.0f, 3.0f);
			ItemPut(14, TESTITEM3,-6.0f, 0.0f, 3.0f);
			ItemPut(15, KANTSU,   -7.0f, 0.0f, 3.0f);
			ItemPut(16, BOM,      -8.0f, 0.0f, 3.0f);
			ItemPut(17, KOUSEN,   -9.0f, 0.0f, 3.0f);
			ItemPut(18, SUNAIPA,   3.0f, 0.0f, 3.0f);
			ItemPut(19, MISSILE, -10.0f, 0.0f, 3.0f);
			ItemPut(20, MIRA,     10.0f, 0.0f, 3.0f);
			ItemPut(21, KAN,     -10.0f, 0.0f, 2.0f);
			ItemPut(22, INBIZI,   -9.0f, 0.0f, 2.0f);
			ItemPut(23, BEAMSODE,  9.0f, 0.0f, 2.0f);
			StageItemMax = 24;
			break;
		case 7: // 五角
			StageDat.trap[1].tag = GOTOP;
			InitThing(&StageDat.trap[1], "./X/trap/毒.x",&D3DXVECTOR3(0.0f, -22.0f, 0.0f), TRUE, TYPE_DOKU);
			InitThing(&StageDat.trap[0], "./X/trap/火山.x",&D3DXVECTOR3(-0.0f, 3.95f,  -0.0f), TRUE, TYPE_MOUNT);
			Syougaisu = 2;

			ItemPut(0, NIKU,      -1.83f, 0.54f, -14.31f);
			ItemPut(1, RORABUREDO,-0.02f, 0.54f,  -5.07f);
			ItemPut(2, PATINKO,    7.89f, 0.54f,  -0.52f);
			ItemPut(3, BAZUKA,     0.85f, 0.54f,  10.30f);
			ItemPut(4, KARASI,    -12.5f, 0.54f,   1.38f);
			ItemPut(5, GETA,      -0.20f, 3.95f,  -0.21f);
			StageItemMax = 6;
			break;
		case 8: // 多数へｙは
			StageDat.trap[0].tag = 1;
			InitThing(&StageDat.trap[0], "./X/trap/IN.x",&D3DXVECTOR3(11.5f, 2.5f, -0.1f), TRUE, TYPE_IN);
			InitThing(&StageDat.trap[1], "./X/trap/OUT.x",&D3DXVECTOR3(-11.5f, 5.0f, -0.1f), TRUE, TYPE_OUT);
			StageDat.trap[3].tag = 2;
			InitThing(&StageDat.trap[2], "./X/trap/OUT.x",&D3DXVECTOR3(10.0f, 2.5f, -0.1f), TRUE, TYPE_OUT);
			InitThing(&StageDat.trap[3], "./X/trap/IN.x",&D3DXVECTOR3(-10.0f, 5.0f, -0.1f), TRUE, TYPE_IN);
			Syougaisu = 4;

			ItemPut( 0, PATINKO,  -1.0f, 0.0f, 0.4f);
			ItemPut( 1, ENKEI,     0.0f, 0.0f, 0.4f);
			ItemPut( 2, BAZUKA,    1.0f, 0.0f, 0.4f);
			ItemPut( 3, SYURYUDAN, 2.0f, 0.0f, 0.4f);
			ItemPut( 4, RORABUREDO,4.0f, 0.0f, 0.4f);
			ItemPut( 5, NIKU,      5.0f, 0.0f, 0.4f);
			ItemPut( 6, SHOTGUN,   6.0f, 0.0f, 0.4f);
			ItemPut( 7, GETA,      7.0f, 0.0f, 0.4f);
			ItemPut( 8, KARASI,    8.0f, 0.0f, 0.4f);
			ItemPut( 9, BAKURETSU, 9.0f, 0.0f, 0.4f);
			ItemPut(10, ZIRAI,    -2.0f, 0.0f, 0.4f);
			ItemPut(11, ZIKANSA,  -3.0f, 0.0f, 0.4f);
			ItemPut(12, TESTITEM1,-4.0f, 0.0f, 0.4f);
			ItemPut(13, TESTITEM2,-5.0f, 0.0f, 0.4f);
			ItemPut(14, TESTITEM3,-6.0f, 0.0f, 0.4f);
			ItemPut(15, KANTSU,   -7.0f, 0.0f, 0.4f);
			ItemPut(16, BOM,      -8.0f, 0.0f, 0.4f);
			ItemPut(17, KOUSEN,   -9.0f, 0.0f, 0.4f);
			ItemPut(18, SUNAIPA,   3.0f, 0.0f, 0.4f);
			ItemPut(19, PATINKO,  -1.0f, 0.0f, -0.4f);
			ItemPut(20, ENKEI,     0.0f, 0.0f, -0.4f);
			ItemPut(21, BAZUKA,    1.0f, 0.0f, -0.4f);
			ItemPut(22, SYURYUDAN, 2.0f, 0.0f, -0.4f);
			ItemPut(23, RORABUREDO,4.0f, 0.0f, -0.4f);
			ItemPut(24, NIKU,      5.0f, 0.0f, -0.4f);
			ItemPut(25, SHOTGUN,   6.0f, 0.0f, -0.4f);
			ItemPut(26, GETA,      7.0f, 0.0f, -0.4f);
			ItemPut(27, KARASI,    8.0f, 0.0f, -0.4f);
			ItemPut(28, BAKURETSU, 9.0f, 0.0f, -0.4f);
			ItemPut(39, ZIRAI,    -2.0f, 0.0f, -0.4f);
			ItemPut(30, ZIKANSA,  -3.0f, 0.0f, -0.4f);
			ItemPut(31, TESTITEM1,-4.0f, 0.0f, -0.4f);
			ItemPut(32, TESTITEM2,-5.0f, 0.0f, -0.4f);
			ItemPut(33, TESTITEM3,-6.0f, 0.0f, -0.4f);
			ItemPut(34, KANTSU,   -7.0f, 0.0f, -0.4f);
			ItemPut(35, BOM,      -8.0f, 0.0f, -0.4f);
			ItemPut(36, KOUSEN,   -9.0f, 0.0f, -0.4f);
			ItemPut(37, SUNAIPA,   3.0f, 0.0f, -0.4f);
			StageItemMax = 38;
			break;
		case 10: // 球体
			StageDat.trap[0].tag = GOTOP;
			StageDat.trap[1].tag = GOTOP;
			StageDat.trap[2].tag = GOTOP;
			StageDat.trap[3].tag = GOTOP;
			InitThing(&StageDat.trap[0], "./X/trap/ベータ.x",&D3DXVECTOR3(11.0f, -6.0f, 11.0f), TRUE, TYPE_BETA);
			InitThing(&StageDat.trap[1], "./X/trap/ベータ.x",&D3DXVECTOR3(11.0f, -1.0f, -11.0f), TRUE, TYPE_BETA);
			InitThing(&StageDat.trap[2], "./X/trap/ベータ.x",&D3DXVECTOR3(-11.0f, 4.0f, 11.0f), TRUE, TYPE_BETA);
			InitThing(&StageDat.trap[3], "./X/trap/ベータ.x",&D3DXVECTOR3(-11.0f, 9.0f, -11.0f), TRUE, TYPE_BETA);
			// ワープ
			StageDat.trap[4].tag = 5;
			InitThing(&StageDat.trap[4], "./X/trap/IN.x",&D3DXVECTOR3(0, -6.0f, 0), TRUE, TYPE_IN);
			InitThing(&StageDat.trap[5], "./X/trap/OUT.x",&D3DXVECTOR3(0, 9.3f, 0), TRUE, TYPE_OUT);
			// ジャンプ
			InitThing(&StageDat.trap[6], "./X/trap/Poyo.x",&D3DXVECTOR3(10.0f, -6.0f, 0), TRUE, TYPE_JUMP);
			InitThing(&StageDat.trap[7], "./X/trap/Poyo.x",&D3DXVECTOR3(0, -6.0f, 10.0f), TRUE, TYPE_JUMP);
			InitThing(&StageDat.trap[8], "./X/trap/Poyo.x",&D3DXVECTOR3(-10.0f, -6.0f, 0), TRUE, TYPE_JUMP);
			InitThing(&StageDat.trap[9], "./X/trap/Poyo.x",&D3DXVECTOR3(0, -6.0f, -10.0f), TRUE, TYPE_JUMP);
			Syougaisu = 10;


			ItemPut( 0, NIKU,      0.0f, 6.2f, 0.0f);
			ItemPut( 1, SUNAIPA,   3.0f, 6.2f, 0.0f);
			ItemPut( 2, BAZUKA,   -3.0f, 6.2f, 0.0f);
			ItemPut( 3, BOM,       0.0f, 6.2f, 3.0f);
			ItemPut( 4, RORABUREDO,3.0f, 6.2f, 3.0f);
			ItemPut( 5, ENKEI,    -3.0f, 6.2f, 3.0f);
			ItemPut( 6, MISSILE,   0.0f, 6.2f, -3.0f);
			ItemPut( 7, GETA,      3.0f, 6.2f, -3.0f);
			ItemPut( 8, BAKURETSU,-3.0f, 6.2f, -3.0f);
			ItemPut( 9, KAN,      -2.0f, 3.6f,  2.0f);
			ItemPut(10, KAN,      -2.0f, 3.6f, -2.0f);
			ItemPut(11, KAN,       2.0f, 3.6f,  2.0f);
			ItemPut(12, KAN,       2.0f, 3.6f, -2.0f);
			StageItemMax = 13;
			break;
	}
}
//--------------------//
//  オブジェクト開放  //
//--------------------//
int ReleaseObject(THING *pObject)
{
	for(DWORD k=0; k<pObject->Mesh.dwNumMaterials; k++)
		SAFE_RELEASE(pObject->Mesh.Textures[k]);
	SAFE_RELEASE( pObject->Mesh.pMesh );

	return 0;
}
//----------------//
//  アイテム設置  //
//----------------//
int ItemPut(int StgPt, int inum, float x, float y, float z)
{
	char fname[256];

	wsprintf(fname, "%s%s", ItemXDir, ItemDat[inum].fname);
	StageDat.item[StgPt].num=inum;
	InitThing(&StageDat.item[StgPt].obj,fname,&D3DXVECTOR3(x,y,z),TRUE,TYPE_ITEM);

	return 0;
}