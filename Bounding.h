//------------------//
//  バウンディング  //
//------------------//
HRESULT InitBBox(THING* pThing)
{
	HRESULT hr = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
    VOID* pVertices = NULL;
	D3DXVECTOR3 vecMax,vecMin;

	//メッシュの頂点バッファーをロックする
	if(FAILED(pThing->Mesh.pMesh->GetVertexBuffer(&pVB)))
		return E_FAIL;
	if(FAILED(pVB->Lock(0, 0, &pVertices, 0))){
        SAFE_RELEASE(pVB);
        return E_FAIL;
    }
	// メッシュ内頂点位置の最大と最小を検索する
	hr=D3DXComputeBoundingBox( (D3DXVECTOR3*)pVertices, pThing->Mesh.pMesh->GetNumVertices(), 
                                    D3DXGetFVFVertexSize(pThing->Mesh.pMesh->GetFVF()), &vecMin,&vecMax );
	pVB->Unlock();
    SAFE_RELEASE(pVB);

	if(FAILED(hr))
        return hr;
	pThing->BBox.vecMax=vecMax;
	pThing->BBox.vecMin=vecMin;
	//軸ベクトルと軸の長さ（この場合ボックスの辺の長さ）を初期化する
	pThing->BBox.fLengthX=(vecMax.x-vecMin.x) / 2;
	pThing->BBox.fLengthY=(vecMax.y-vecMin.y) / 2;
	pThing->BBox.fLengthZ=(vecMax.z-vecMin.z) / 2;

	return S_OK;
}

//---------------------//
//  OBBによる衝突判定  //
//---------------------//
BOOL OBBCollisionDetection(THING* pThingA,THING* pThingB)
{
	if(fabs(pThingA->vecPosition.x - pThingB->vecPosition.x) > HIT_DIST || fabs(pThingA->vecPosition.y - pThingB->vecPosition.y) > HIT_DIST || fabs(pThingA->vecPosition.z - pThingB->vecPosition.z) > HIT_DIST)
		return 0;

	//ボックスの距離ベクトル（中心と中心を結んだベクトル）
	D3DXVECTOR3 vecDistance = pThingB->vecPosition - pThingA->vecPosition;
	//分離軸
	D3DXVECTOR3 vecSeparate;
	//それぞれのローカル基底軸ベクトルに、それぞれの回転を反映させる
	pThingA->BBox.vecAxisX=D3DXVECTOR3(1,0,0);
	pThingA->BBox.vecAxisY=D3DXVECTOR3(0,1,0);
	pThingA->BBox.vecAxisZ=D3DXVECTOR3(0,0,1);

	pThingB->BBox.vecAxisX=D3DXVECTOR3(1,0,0);
	pThingB->BBox.vecAxisY=D3DXVECTOR3(0,1,0);
	pThingB->BBox.vecAxisZ=D3DXVECTOR3(0,0,1);

	D3DXVec3TransformCoord(&pThingA->BBox.vecAxisX,&pThingA->BBox.vecAxisX,&pThingA->matRotation);
	D3DXVec3TransformCoord(&pThingA->BBox.vecAxisY,&pThingA->BBox.vecAxisY,&pThingA->matRotation);
	D3DXVec3TransformCoord(&pThingA->BBox.vecAxisZ,&pThingA->BBox.vecAxisZ,&pThingA->matRotation);

	D3DXVec3TransformCoord(&pThingB->BBox.vecAxisX,&pThingB->BBox.vecAxisX,&pThingB->matRotation);
	D3DXVec3TransformCoord(&pThingB->BBox.vecAxisY,&pThingB->BBox.vecAxisY,&pThingB->matRotation);
	D3DXVec3TransformCoord(&pThingB->BBox.vecAxisZ,&pThingB->BBox.vecAxisZ,&pThingB->matRotation);
	//ボックスAのローカル基底軸を基準にした、”影”の算出（3パターン）
	//X軸を分離軸とした場合
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&pThingA->BBox.vecAxisX,&vecDistance)) return FALSE;
	//Y軸を分離軸とした場合
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&pThingA->BBox.vecAxisY,&vecDistance)) return FALSE;
	//Z軸を分離軸とした場合
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&pThingA->BBox.vecAxisZ,&vecDistance)) return FALSE;
	
	//ボックスBのローカル基底軸を基準にした、”影”の算出（3パターン）
	//X軸を分離軸とした場合
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&pThingB->BBox.vecAxisX,&vecDistance)) return FALSE;
	//Y軸を分離軸とした場合
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&pThingB->BBox.vecAxisY,&vecDistance)) return FALSE;
	//Z軸を分離軸とした場合
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&pThingB->BBox.vecAxisZ,&vecDistance)) return FALSE;
	
	//お互いの基底軸同士の外積ベクトルを基準にした、”影”の算出（9パターン）
	//ボックスAのX軸
	//と　ボックスBのX軸との外積ベクトルを分離軸とした場合
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisX,&pThingB->BBox.vecAxisX);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;
	//と　ボックスBのY軸との外積ベクトルを分離軸とした場合
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisX,&pThingB->BBox.vecAxisY);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;
	//と　ボックスBのZ軸との外積ベクトルを分離軸とした場合
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisX,&pThingB->BBox.vecAxisZ);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;
	
	//ボックスAのY軸
	//と　ボックスBのX軸との外積ベクトルを分離軸とした場合
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisY,&pThingB->BBox.vecAxisX);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;
	//と　ボックスBのY軸との外積ベクトルを分離軸とした場合
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisY,&pThingB->BBox.vecAxisY);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;
	//と　ボックスBのZ軸との外積ベクトルを分離軸とした場合
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisY,&pThingB->BBox.vecAxisZ);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;
	
	//ボックスAのZ軸
	//と　ボックスBのX軸との外積ベクトルを分離軸とした場合
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisZ,&pThingB->BBox.vecAxisX);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;
	//と　ボックスBのY軸との外積ベクトルを分離軸とした場合
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisZ,&pThingB->BBox.vecAxisY);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;
	//と　ボックスBのZ軸との外積ベクトルを分離軸とした場合
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisZ,&pThingB->BBox.vecAxisZ);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;

	return TRUE;
}
//------------//
//  衝突判定  //
//------------//
BOOL CompareLength(BBOX* pboxA,BBOX* pboxB,D3DXVECTOR3* pvecSeparate,D3DXVECTOR3* pvecDistance)
{
	//”分離軸上での”ボックスＡの中心からボックスＢの中心までの距離
	FLOAT fDistance=fabsf( D3DXVec3Dot( pvecDistance, pvecSeparate) );
	//分離軸上でボックスAの中心から最も遠いボックスAの頂点までの距離
	FLOAT fShadowA=0;
	//分離軸上でボックスBの中心から最も遠いボックスBの頂点までの距離
	FLOAT fShadowB=0;		
	//それぞれのボックスの”影”を算出
	fShadowA = fabsf( D3DXVec3Dot( &pboxA->vecAxisX, pvecSeparate ) * pboxA->fLengthX)+
		fabsf( D3DXVec3Dot( &pboxA->vecAxisY, pvecSeparate ) * pboxA->fLengthY)+
		fabsf( D3DXVec3Dot( &pboxA->vecAxisZ, pvecSeparate ) * pboxA->fLengthZ);

	fShadowB = fabsf( D3DXVec3Dot( &pboxB->vecAxisX, pvecSeparate ) * pboxB->fLengthX)+
		fabsf( D3DXVec3Dot( &pboxB->vecAxisY, pvecSeparate ) * pboxB->fLengthY)+
		fabsf( D3DXVec3Dot( &pboxB->vecAxisZ, pvecSeparate ) * pboxB->fLengthZ);
	if(fDistance > fShadowA + fShadowB)
		return FALSE;

	return TRUE;
}
//------------------------------//
//  バウンディングスフィア作成  //
//------------------------------//
HRESULT InitSphere(THING* pThing)
{
	HRESULT hr = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
    VOID* pVertices = NULL;
	D3DXVECTOR3 vecCenter;
	FLOAT fRadius;

	if(FAILED(pThing->Mesh.pMesh->GetVertexBuffer(&pVB)))
		return E_FAIL;
	if(FAILED(pVB->Lock(0, 0, &pVertices, 0))){
        SAFE_RELEASE(pVB);
        return E_FAIL;
    }
	// メッシュの外接円の中心と半径を計算する
	hr=D3DXComputeBoundingSphere( (D3DXVECTOR3*)pVertices, pThing->Mesh.pMesh->GetNumVertices(), 
                                    D3DXGetFVFVertexSize(pThing->Mesh.pMesh->GetFVF()), &vecCenter, 
                                    &fRadius );
	pVB->Unlock();
    SAFE_RELEASE( pVB );

	if(FAILED( hr ))
        return hr;

	pThing->Sphere.vecCenter=vecCenter;
	pThing->Sphere.fRadius=fRadius;

	return S_OK;
}
//------------------------------------//
//  バウンディングスフィアの衝突判定  //
//------------------------------------//
BOOL SphereCollision(THING* pThingA,THING* pThingB)
{
	//２つの物体の中心間の距離を求める
	D3DXVECTOR3 vecLength=pThingB->vecPosition-pThingA->vecPosition;
	FLOAT fLength=D3DXVec3Length(&vecLength);
	// その距離が、2物体の半径を足したものより小さいということは、
	//境界球同士が重なっている（衝突している）ということ
	if(fLength <= (pThingA->Sphere.fRadius*pThingA->fScale)+(pThingB->Sphere.fRadius*pThingB->fScale)-0.5f)
		return TRUE;

	return FALSE;
}