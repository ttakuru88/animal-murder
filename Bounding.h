//------------------//
//  �o�E���f�B���O  //
//------------------//
HRESULT InitBBox(THING* pThing)
{
	HRESULT hr = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
    VOID* pVertices = NULL;
	D3DXVECTOR3 vecMax,vecMin;

	//���b�V���̒��_�o�b�t�@�[�����b�N����
	if(FAILED(pThing->Mesh.pMesh->GetVertexBuffer(&pVB)))
		return E_FAIL;
	if(FAILED(pVB->Lock(0, 0, &pVertices, 0))){
        SAFE_RELEASE(pVB);
        return E_FAIL;
    }
	// ���b�V�������_�ʒu�̍ő�ƍŏ�����������
	hr=D3DXComputeBoundingBox( (D3DXVECTOR3*)pVertices, pThing->Mesh.pMesh->GetNumVertices(), 
                                    D3DXGetFVFVertexSize(pThing->Mesh.pMesh->GetFVF()), &vecMin,&vecMax );
	pVB->Unlock();
    SAFE_RELEASE(pVB);

	if(FAILED(hr))
        return hr;
	pThing->BBox.vecMax=vecMax;
	pThing->BBox.vecMin=vecMin;
	//���x�N�g���Ǝ��̒����i���̏ꍇ�{�b�N�X�̕ӂ̒����j������������
	pThing->BBox.fLengthX=(vecMax.x-vecMin.x) / 2;
	pThing->BBox.fLengthY=(vecMax.y-vecMin.y) / 2;
	pThing->BBox.fLengthZ=(vecMax.z-vecMin.z) / 2;

	return S_OK;
}

//---------------------//
//  OBB�ɂ��Փ˔���  //
//---------------------//
BOOL OBBCollisionDetection(THING* pThingA,THING* pThingB)
{
	if(fabs(pThingA->vecPosition.x - pThingB->vecPosition.x) > HIT_DIST || fabs(pThingA->vecPosition.y - pThingB->vecPosition.y) > HIT_DIST || fabs(pThingA->vecPosition.z - pThingB->vecPosition.z) > HIT_DIST)
		return 0;

	//�{�b�N�X�̋����x�N�g���i���S�ƒ��S�����񂾃x�N�g���j
	D3DXVECTOR3 vecDistance = pThingB->vecPosition - pThingA->vecPosition;
	//������
	D3DXVECTOR3 vecSeparate;
	//���ꂼ��̃��[�J����ꎲ�x�N�g���ɁA���ꂼ��̉�]�𔽉f������
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
	//�{�b�N�XA�̃��[�J����ꎲ����ɂ����A�h�e�h�̎Z�o�i3�p�^�[���j
	//X���𕪗����Ƃ����ꍇ
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&pThingA->BBox.vecAxisX,&vecDistance)) return FALSE;
	//Y���𕪗����Ƃ����ꍇ
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&pThingA->BBox.vecAxisY,&vecDistance)) return FALSE;
	//Z���𕪗����Ƃ����ꍇ
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&pThingA->BBox.vecAxisZ,&vecDistance)) return FALSE;
	
	//�{�b�N�XB�̃��[�J����ꎲ����ɂ����A�h�e�h�̎Z�o�i3�p�^�[���j
	//X���𕪗����Ƃ����ꍇ
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&pThingB->BBox.vecAxisX,&vecDistance)) return FALSE;
	//Y���𕪗����Ƃ����ꍇ
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&pThingB->BBox.vecAxisY,&vecDistance)) return FALSE;
	//Z���𕪗����Ƃ����ꍇ
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&pThingB->BBox.vecAxisZ,&vecDistance)) return FALSE;
	
	//���݂��̊�ꎲ���m�̊O�σx�N�g������ɂ����A�h�e�h�̎Z�o�i9�p�^�[���j
	//�{�b�N�XA��X��
	//�Ɓ@�{�b�N�XB��X���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisX,&pThingB->BBox.vecAxisX);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;
	//�Ɓ@�{�b�N�XB��Y���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisX,&pThingB->BBox.vecAxisY);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;
	//�Ɓ@�{�b�N�XB��Z���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisX,&pThingB->BBox.vecAxisZ);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;
	
	//�{�b�N�XA��Y��
	//�Ɓ@�{�b�N�XB��X���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisY,&pThingB->BBox.vecAxisX);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;
	//�Ɓ@�{�b�N�XB��Y���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisY,&pThingB->BBox.vecAxisY);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;
	//�Ɓ@�{�b�N�XB��Z���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisY,&pThingB->BBox.vecAxisZ);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;
	
	//�{�b�N�XA��Z��
	//�Ɓ@�{�b�N�XB��X���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisZ,&pThingB->BBox.vecAxisX);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;
	//�Ɓ@�{�b�N�XB��Y���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisZ,&pThingB->BBox.vecAxisY);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;
	//�Ɓ@�{�b�N�XB��Z���Ƃ̊O�σx�N�g���𕪗����Ƃ����ꍇ
	D3DXVec3Cross( &vecSeparate, &pThingA->BBox.vecAxisZ,&pThingB->BBox.vecAxisZ);
	if(!CompareLength(&pThingA->BBox,&pThingB->BBox,&vecSeparate,&vecDistance)) return FALSE;

	return TRUE;
}
//------------//
//  �Փ˔���  //
//------------//
BOOL CompareLength(BBOX* pboxA,BBOX* pboxB,D3DXVECTOR3* pvecSeparate,D3DXVECTOR3* pvecDistance)
{
	//�h��������ł́h�{�b�N�X�`�̒��S����{�b�N�X�a�̒��S�܂ł̋���
	FLOAT fDistance=fabsf( D3DXVec3Dot( pvecDistance, pvecSeparate) );
	//��������Ń{�b�N�XA�̒��S����ł������{�b�N�XA�̒��_�܂ł̋���
	FLOAT fShadowA=0;
	//��������Ń{�b�N�XB�̒��S����ł������{�b�N�XB�̒��_�܂ł̋���
	FLOAT fShadowB=0;		
	//���ꂼ��̃{�b�N�X�́h�e�h���Z�o
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
//  �o�E���f�B���O�X�t�B�A�쐬  //
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
	// ���b�V���̊O�ډ~�̒��S�Ɣ��a���v�Z����
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
//  �o�E���f�B���O�X�t�B�A�̏Փ˔���  //
//------------------------------------//
BOOL SphereCollision(THING* pThingA,THING* pThingB)
{
	//�Q�̕��̂̒��S�Ԃ̋��������߂�
	D3DXVECTOR3 vecLength=pThingB->vecPosition-pThingA->vecPosition;
	FLOAT fLength=D3DXVec3Length(&vecLength);
	// ���̋������A2���̂̔��a�𑫂������̂�菬�����Ƃ������Ƃ́A
	//���E�����m���d�Ȃ��Ă���i�Փ˂��Ă���j�Ƃ�������
	if(fLength <= (pThingA->Sphere.fRadius*pThingA->fScale)+(pThingB->Sphere.fRadius*pThingB->fScale)-0.5f)
		return TRUE;

	return FALSE;
}