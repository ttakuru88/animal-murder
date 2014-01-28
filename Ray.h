//-------------------------------..
// ���̃|���S���̒��_��������  //
//-------------------------------//
HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh,DWORD dwPolyIndex,D3DXVECTOR3* pvecVertices )
{
	DWORD dwStride=pMesh->GetNumBytesPerVertex();
	DWORD dwVertexAmt=pMesh->GetNumVertices();
	DWORD dwPolyAmt=pMesh->GetNumFaces();
	WORD* pwPoly=NULL;
	pMesh->LockIndexBuffer(D3DLOCK_READONLY,(VOID**)&pwPoly);	

	BYTE *pbVertices=NULL;
	FLOAT* pfVetices=NULL;
	LPDIRECT3DVERTEXBUFFER9 VB=NULL;
	pMesh->GetVertexBuffer(&VB);
	if(SUCCEEDED(VB->Lock(0,0,(VOID**)&pbVertices,0)))
	{
		pfVetices=(FLOAT*)&pbVertices[dwStride*pwPoly[ dwPolyIndex* 3] ];
		pvecVertices[0].x=pfVetices[0];
		pvecVertices[0].y=pfVetices[1];
		pvecVertices[0].z=pfVetices[2];

		pfVetices=(FLOAT*)&pbVertices[dwStride*pwPoly[ dwPolyIndex * 3+1] ];
		pvecVertices[1].x=pfVetices[0];
		pvecVertices[1].y=pfVetices[1];
		pvecVertices[1].z=pfVetices[2];

		pfVetices=(FLOAT*)&pbVertices[dwStride*pwPoly[ dwPolyIndex * 3+2] ];
		pvecVertices[2].x=pfVetices[0];
		pvecVertices[2].y=pfVetices[1];
		pvecVertices[2].z=pfVetices[2];

		pMesh->UnlockIndexBuffer();
		VB->Unlock();
	}
	return S_OK;
}
//---------------------//
// ���C�ɂ��Փ˔���  //
//---------------------//
BOOL RayIntersect(THING* pThingA ,THING* pThingB,FLOAT* pfDistance,D3DXVECTOR3* pvIntersect,D3DXVECTOR3* Muki)
{
	D3DXVECTOR3 vecStart, vecEnd;
	D3DXVECTOR3 vecPosA = pThingA->vecPosition;
	D3DXMATRIX matRotA = pThingA->matRotation;
	D3DXMATRIX matYaw = pThingA->matYaw;
	D3DXMATRIX matPitch = pThingA->matPitch;
	//���C���o�����b�V���̈ʒu�E��]�����C�ɓK�p
	vecStart=vecPosA;
	vecStart.y=vecPosA.y+pThingA->BBox.vecMax.y;
	vecEnd = *Muki;
	D3DXMatrixRotationX(&matPitch, -pThingA->fPitch);
	D3DXMatrixRotationY(&matYaw, pThingA->fYaw);
	matRotA *= matPitch * matYaw;
	D3DXVec3TransformCoord(&vecEnd,&vecEnd,&matRotA);
	vecEnd+=vecStart;

	return RayFooter(pThingB, pfDistance, pvIntersect, &vecStart, &vecEnd);
}
//----------------//
//  �J�����̃��C  //
//----------------//
BOOL RayShoot(PLAYERCHARASTATE* Ch ,THING* pThing,FLOAT* pfDistance,D3DXVECTOR3* pvIntersect)
{
	D3DXVECTOR3 vecStart,vecEnd;
	//���C���o�����b�V���̈ʒu�E��]�����C�ɓK�p
	vecStart=Ch->Camera.vecEyePt;
	vecStart.y += 0.045f;
	vecEnd=Ch->Camera.vecLookatPt;

	return RayFooter(pThing, pfDistance, pvIntersect, &vecStart, &vecEnd);
}
//------------------//
//  ���C����㏈��  //
//------------------//
int RayFooter(THING *pThing, FLOAT *pfDistance, D3DXVECTOR3 *pvIntersect, D3DXVECTOR3 *vecStart, D3DXVECTOR3 *vecEnd)
{
	BOOL boHit=FALSE;
	D3DXMATRIX matWorld,matWorldB,matRotA,matYaw,matPitch;
	D3DXMATRIX matRot = pThing->matRotation;
	D3DXMATRIX matPos = pThing->matPosition;
	D3DXVECTOR3 vecPos = pThing->vecPosition;
	D3DXVECTOR3 vecDirection;
	// ���C�𓖂Ă郁�b�V���������Ă������]���Ă���ꍇ�ł��Ώۂ̃��[���h�s��̋t�s���p����ΐ��������C��������
	D3DXMatrixTranslation(&matWorld,vecPos.x,vecPos.y,vecPos.z);
	D3DXMatrixInverse(&matWorld,NULL,&matWorld);
	D3DXVec3TransformCoord(vecStart, vecStart,&matWorld);
	D3DXVec3TransformCoord(vecEnd, vecEnd,&matWorld);
	
	D3DXMatrixRotationY(&matRot,pThing->fYaw);
	D3DXMatrixTranslation(&matPos,vecPos.x,vecPos.y,vecPos.z);
	D3DXMatrixMultiply(&matWorldB,&matPos,&matRot);
	DWORD dwIndex=0;
	D3DXVECTOR3 vVertex[3];
	FLOAT U=0,V=0;
	vecDirection = *vecEnd - *vecStart;
	D3DXIntersect(pThing->Mesh.pMesh, vecStart,&vecDirection,&boHit,&dwIndex,&U,&V, pfDistance,NULL,NULL);
	if(boHit){
		FindVerticesOnPoly(pThing->Mesh.pMesh,dwIndex,vVertex);
		//�d�S���W�����_���Z�o�@ ���[�J����_p�́@v0+U*(v1-v0)+V*(v2-v0)
		*pvIntersect=vVertex[0]+U*(vVertex[1]-vVertex[0])+V*(vVertex[2]-vVertex[0]);
		//���[�J����_�����[���h�n�Ɋ��Z
		D3DXVec3TransformCoord(pvIntersect,pvIntersect,&matWorldB);
		return TRUE;
	}
	return FALSE;
}