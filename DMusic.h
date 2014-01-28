//-----------------------//
//  DirectSound�̏�����  //
//-----------------------//
HRESULT initDirectSound( HWND hWnd )
{
	HRESULT hr;         //���ʗp
	DSBUFFERDESC aDSBD; //�o�b�t�@�L�q�q
	WAVEFORMATEX aWFEX; //�g�`�I�[�f�B�I�f�[�^�̃t�H�[�}�b�g
	LPDIRECTSOUNDBUFFER	pPrimaryBuffer = NULL;	//�v���C�}���o�b�t�@���m�ۂ��邽�߂̉��̃o�b�t�@

	SAFE_RELEASE( g_pDirectSound );	//�O�̂��߂̏�����

	// �v���C�}���T�E���h�f�B�o�C�X���g���ĒT��
	if( FAILED(hr=DirectSoundCreate8(NULL, &g_pDirectSound, NULL)) )
		return hr;

	//�������x����ݒ肷��
	if( FAILED(hr=g_pDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY) ) )
		return hr;

	// �v���C�}���o�b�t�@���擾����
	ZeroMemory( &aDSBD,	sizeof(DSBUFFERDESC) );				// �\���̂̃[�����Z�b�g�i�K���s���j
    aDSBD.dwSize			= sizeof(DSBUFFERDESC);			// �K��sizeof(DSBUFFERDESC)
    aDSBD.dwFlags			= DSBCAPS_PRIMARYBUFFER;		// �v���C�}���o�b�t�@�B
    aDSBD.dwBufferBytes		= 0;							// �v���C�}���o�b�t�@�̏ꍇ�͕K��0
    aDSBD.lpwfxFormat		= NULL;							// �v���C�}���o�b�t�@�̏ꍇ�͕K��NULL
	
	// CreateSoundBuffer�̃`�F�b�N�͕K��FAILED�}�N���ōs��
	if( FAILED(hr=g_pDirectSound->CreateSoundBuffer(&aDSBD, &pPrimaryBuffer, NULL)) )
		return hr;
	ZeroMemory( &aWFEX, sizeof(WAVEFORMATEX) ); 			// �\���̂̃[�����Z�b�g�i�K���s���j
	aWFEX.wFormatTag		= (WORD) WAVE_FORMAT_PCM;		// PCM�g�`�t�H�[�}�b�g��p����
	aWFEX.nChannels			= (WORD) kPrimaryChannels;		// �`���l�����A���g���A�r�b�g���[�g�̓w�b�_���Q��
	aWFEX.nSamplesPerSec	= (DWORD) kPrimaryFreq; 
	aWFEX.wBitsPerSample	= (WORD) kPrimaryBitRate; 
	aWFEX.nBlockAlign		= (WORD) (aWFEX.wBitsPerSample / 8 * aWFEX.nChannels);	//�����̓�s�͕K����������
	aWFEX.nAvgBytesPerSec	= (DWORD) (aWFEX.nSamplesPerSec * aWFEX.nBlockAlign);
	// �v���C�}���o�b�t�@�̃t�H�[�}�b�g��ݒ�
	// SetFormat�֐��̓v���C�}���o�b�t�@�̐ݒ���s�����߂̓��ʂȊ֐��ł���
	if( FAILED(hr=pPrimaryBuffer->SetFormat(&aWFEX)) )
		return hr;
	// SetFormat�֐�������ɏI������̂ŁA��������Ȃ�
    SAFE_RELEASE( pPrimaryBuffer );

	return( S_OK );
}
//---------------------//
//  DirectMusic������  //
//---------------------//
HRESULT	initDirectMusic( HWND hWnd, LPDIRECTSOUND8 pTheDS )
{
	// COM�I�u�W�F�N�g�̏�����
	if( !g_bComInit ){
		CoInitialize(NULL);
		g_bComInit = TRUE;
	}

	HRESULT hr; // �߂�l
	IDirectSound* paDirectSound;	//DirectSound��DirectMusic�̘A���ɕK�v

	// DirectSound������������Ă��Ȃ�������A��
	if(pTheDS == NULL)
		return E_FAIL;
	else
		pTheDS->QueryInterface(IID_IDirectSound, (void**)&paDirectSound);
	// ���[�_�[�I�u�W�F�N�g�̐���
	if(FAILED(hr = CoCreateInstance(CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC, IID_IDirectMusicLoader8, (void**)&g_pDMLoader )))
		goto FAIL_RETURN;
	// �p�t�H�[�}���X�I�u�W�F�N�g�̐���
	if(FAILED(hr = CoCreateInstance(CLSID_DirectMusicPerformance, NULL, CLSCTX_INPROC, IID_IDirectMusicPerformance8, (void**)&g_pDMPerformance )))
		goto FAIL_RETURN;
	// �p�t�H�[�}���X�̏�����
	if(FAILED(hr = g_pDMPerformance->InitAudio(	NULL, &paDirectSound, hWnd, DMUS_APATH_SHARED_STEREOPLUSREVERB,
												kDirectMusicChannels, DMUS_AUDIOF_ALL, NULL )))
		goto FAIL_RETURN;
	// �f�t�H���g�I�[�f�B�I�p�X�̎擾
	g_pDMPerformance->GetDefaultAudioPath( &g_pDMAudioPath );

	return(S_OK);

// �G���[���̏o��
FAIL_RETURN:

	SAFE_RELEASE( g_pDMPerformance );
	SAFE_RELEASE( g_pDMLoader );
	return(hr);
}
//----------------------//
//�@�T�E���h�̓ǂݍ���  //
//----------------------//
HRESULT	setupSounds(void)
{
	for(int i=1; i<SOUNDFILEMAX; i++)
		if(FAILED(loadSoundsFromWaveFile(SoundFile[i], &g_SE[i], DSBCAPS_CTRLVOLUME, GUID_NULL, kNUM_OF_SE_BUFFERS)))	
			return E_FAIL;

	return S_OK;
}
//--------------------------------------//
//�@�Z�J���_���o�b�t�@��p�ӁA�ǂݍ���  //
//--------------------------------------//
HRESULT	loadSoundsFromWaveFile(char *aWaveFileName, theSounds *aSound, DWORD aCreationFlags, GUID guid3DAlgorithm, DWORD aNumOfBuffers)
{
	HRESULT hr;
	int i; //�ėp�J�E���^
	char tmpString[kSTR_LENGTH];
	LPDIRECTSOUNDBUFFER* aDSBuffers = NULL; //���o�b�t�@

	// �t�@�C������NULL��������A��
	if( aWaveFileName == NULL)
		return E_FAIL;

	// �T�E���h�o�b�t�@�ւ̃|�C���^���m��
	aDSBuffers = new LPDIRECTSOUNDBUFFER[aNumOfBuffers];
	if( aDSBuffers == NULL )
		return E_FAIL; // �������̊m�ۂɎ��s�H

	// �g�`�t�@�C���̓ǂݍ���
	if( FAILED( hr = openWaveFile( aWaveFileName , aSound ))){
		// �J�����g�Ƀt�@�C��������������Asounds�t�H���_��
		TCHAR strWavFile[MAX_PATH];
		lstrcpyn( strWavFile, kSoundsPath, MAX_PATH );
		lstrcpyn( strWavFile + kSoundsPathLength, aWaveFileName, MAX_PATH - kSoundsPathLength );

		if( FAILED( hr = openWaveFile( strWavFile , aSound ))){
			wsprintf( tmpString , "wav�t�@�C���w%s�x��������܂���ł���", strWavFile);
			goto FAIL_RETURN;
		}
	}
	// DirectSound�o�b�t�@�̍쐬
	DSBUFFERDESC	aDSBDesc;	//�o�b�t�@�L�q�q

	ZeroMemory( &aDSBDesc, sizeof(DSBUFFERDESC) );
	aDSBDesc.dwSize          = sizeof(DSBUFFERDESC);      //�����͕K��sizeof(DSBUFFERDESC)
	aDSBDesc.dwFlags         = aCreationFlags;            //�������t���O
	aDSBDesc.dwBufferBytes   = aSound->sndChunk.cksize;   //�o�b�t�@�T�C�Y�i�g�`�t�@�C���̃f�[�^�Ɠ����j
	aDSBDesc.guid3DAlgorithm = guid3DAlgorithm;           //�\�t�g�E�F�A�~�L�V���O�Ŏg���A���S���Y��
	aDSBDesc.lpwfxFormat     = &(aSound->sndWaveFormatEx);//OepnWaveFile�ŊJ����RIFF�t�@�C���ɓ����Ă���PCM�����t�H�[�}�b�g

	// PCM�ȊO�̃f�[�^���Đ��ł��邩�ǂ����Ăяo�����ɒm�点��
	if(FAILED(hr = g_pDirectSound->CreateSoundBuffer( &aDSBDesc, &aDSBuffers[0], NULL ))){
		wsprintf(tmpString , "FAIL:CreateSoundBuffer file=%s",aWaveFileName);
		goto FAIL_RETURN;
	}
	//�o�b�t�@�̕���
	for(i=0; (unsigned)i<aNumOfBuffers; i++){
		if( FAILED( hr = g_pDirectSound->DuplicateSoundBuffer( aDSBuffers[0] , &aDSBuffers[i] )) ){
			wsprintf( tmpString , "FAIL:DuplicateSoundBuffer");
			goto FAIL_RETURN;
		}
	}

	// �w�肳�ꂽ���̃o�b�t�@���쐬���Ă��̃|�C���^�������n��
	aSound->sndDSSoundBuffer = new LPDIRECTSOUNDBUFFER[aNumOfBuffers];
	if( aSound->sndDSSoundBuffer == NULL ){
		wsprintf( tmpString , "FAIL:aDSSoundBuffer");
		goto FAIL_RETURN;
	}
	//�o�b�t�@�̐���theSounds�\���̂ɋL�^����
	aSound->sndNumOfBuffers = aNumOfBuffers;
	//�o�b�t�@�̈�̃R�s�[
	for(i=0; (unsigned)i<aNumOfBuffers; i++){
		aSound->sndDSSoundBuffer[i] = aDSBuffers[i];
		// ���ʐݒ�
		aSound->sndDSSoundBuffer[i]->SetVolume(SoundVol);
	}
	//�o�b�t�@�ɉ���p�ӂ���
	fillupSoundBuffer(aSound , NULL);

	SAFE_DELETE_ARRAY(aDSBuffers);//���̃o�b�t�@��j��
	return S_OK;

	//�G���[���͂�������A��
FAIL_RETURN:

	MessageBox(NULL, tmpString, "ERROR" , MB_OK|MB_ICONHAND );
	SAFE_DELETE_ARRAY(aDSBuffers); // ���̃o�b�t�@��j��
	return E_FAIL;
}
//-----------------------------------------//
// theSound�o�b�t�@�ɔg�`�f�[�^��ǂݍ���  //
//-----------------------------------------//
HRESULT fillupSoundBuffer(theSounds *aSound , DWORD aLockBuffer)
{
	HRESULT hr; // ���ʗp
	VOID*	apLockedBuffer    = NULL; // ���b�N���ꂽDirectSound�o�b�t�@�ւ̃|�C���^
	DWORD	aLockedBufferSize = 0;    // ���b�N���ꂽDirectSound�o�b�t�@�̃T�C�Y
	DWORD	aReadedData       = 0;    // �g�`�t�@�C������ǂݏo���ꂽ�f�[�^�̃o�C�g�� 

	if( aSound->sndDSSoundBuffer[aLockBuffer] == NULL )
		return E_FAIL;
    // �o�b�t�@���m���ɑ��݂��邱�Ƃ��m���߂�B
	if( FAILED( hr = restoreDSBuffer( aSound->sndDSSoundBuffer[aLockBuffer], NULL ) ) ){
		MessageBox( NULL, "FAIL:RestoreBuffer", "ERROR", MB_OK|MB_ICONHAND );
		return( hr );
	}
	// �o�b�t�@�����b�N����
	if( FAILED( hr =  aSound->sndDSSoundBuffer[aLockBuffer]->Lock( 0, aSound->sndChunk.cksize , &apLockedBuffer , &aLockedBufferSize, NULL, NULL, 0L ) ) ){
		MessageBox( NULL, "FAIL:Lock", "ERROR", MB_OK|MB_ICONHAND );
		return hr;
	}
	// �g�`�t�@�C���̓�����������
    rewindWaveFile( aSound );

	if( FAILED( hr = readWaveToBuffer( aSound , (BYTE*)apLockedBuffer , aLockedBufferSize , &aReadedData ) ) ){
		MessageBox( NULL, "FAIL:Read", "ERROR", MB_OK|MB_ICONHAND );
		return hr;
	}

	if(aReadedData == NULL)
		// �g�`�f�[�^�����������疳���Ŗ��߂�
		FillMemory( (BYTE*) apLockedBuffer, aLockedBufferSize, (BYTE)(aSound->sndWaveFormatEx.wBitsPerSample == 8 ? 128 : 0 ) );
	else if(aReadedData < aLockedBufferSize)
		// �g�`�t�@�C�����J��Ԃ��Ȃ��Ŗ����Ŗ��߂�
		FillMemory(	(BYTE*) apLockedBuffer + aReadedData, aLockedBufferSize - aReadedData, (BYTE)(aSound->sndWaveFormatEx.wBitsPerSample == 8 ? 128 : 0 ) );
    // �K�v���Ȃ��Ȃ����̂ŁA�o�b�t�@���A�����b�N����
	aSound->sndDSSoundBuffer[aLockBuffer]->Unlock( apLockedBuffer, aLockedBufferSize, NULL, 0 );

    return S_OK;
}
//-----------------------------------------------//
// aBuffer�Ƀf�[�^�ǂݍ���aReadedData�Ƀo�C�g��  //
//-----------------------------------------------//
HRESULT readWaveToBuffer( theSounds *aSound , BYTE* aBuffer, DWORD aSizeToRead, DWORD* aReadedData )
{
	MMIOINFO mmioInfoIn; // aSound->sndHmmio�̌��݂̏�

	if(aSound->sndHmmio == NULL)
		return E_FAIL;
	if( aBuffer == NULL || aSizeToRead == NULL )
		return E_FAIL;

	*aReadedData = 0;	//���ʁi�ǂݍ��񂾃o�C�g���j��������
	// mmioGetInfo��aSound->sndHmmio�̏���mmioInfoIn�ɔ[�߂�
	if(mmioGetInfo( aSound->sndHmmio, &mmioInfoIn, 0 ) != NULL){
		MessageBox( NULL, "FAIL:mmioGetInfo", "ERROR", MB_OK|MB_ICONHAND );
		return E_FAIL;
	}

	// �ǂݍ��ރf�[�^�̃T�C�Y�𒲂ׂ�B
	UINT aNumOfReadBytes = aSizeToRead;
	if( aNumOfReadBytes > aSound->sndChunk.cksize )
		aNumOfReadBytes = aSound->sndChunk.cksize;
	// ���ۂ̓ǂݏo�����[�v
	for(int i=0; (unsigned)i<aNumOfReadBytes; i++){
		// �o�b�t�@�̐퓬���w���Ă�׃o�b�t�@�̏�ԍX�V
		if( mmioInfoIn.pchNext == mmioInfoIn.pchEndRead ){
			// �t�@�C���̏I���
			if(mmioAdvance( aSound->sndHmmio, &mmioInfoIn, MMIO_READ ) != NULL){
				MessageBox( NULL, "FAIL:mmioAdvance", "ERROR", MB_OK|MB_ICONHAND );
				return E_FAIL;
			}
			// �ǂݍ��ރf�[�^�̃T�C�Y����Ŋm�F���Ă���̂Ƀt�@�C���̏I��肪���Ă���
			if(mmioInfoIn.pchNext == mmioInfoIn.pchEndRead){
				// ���s������A��
				MessageBox( NULL, "FAIL:mmioInfoIn.pchNext", "ERROR", MB_OK|MB_ICONHAND );
				return( E_FAIL );
			}
		}
		// ���ۂ̃R�s�[
		*((BYTE*)aBuffer + i) = *((BYTE*)mmioInfoIn.pchNext);
		mmioInfoIn.pchNext++;
	}
	// mmio�擾���X�V
	if(mmioSetInfo( aSound->sndHmmio , &mmioInfoIn, 0 ) != NULL){
		MessageBox( NULL, "FAIL:mmioSetInfo", "ERROR", MB_OK|MB_ICONHAND );
		return E_FAIL;
	}

	*aReadedData = aNumOfReadBytes;	//���ʂ������n��
	return S_OK;
}
//-------------------------------------------//
//�@DirectSound�o�b�t�@�������Ă����畜��  //
//-------------------------------------------//
HRESULT	restoreDSBuffer( LPDIRECTSOUNDBUFFER aDSBuffer , BOOL* pRestoreFlag )
{
	HRESULT hr;

	// �����m�F�t���O������΁A�ŏ��Ƀ��Z�b�g
	if( pRestoreFlag != NULL )
		*pRestoreFlag = FALSE;
	// �o�b�t�@�̏�Ԃ��m�F����
	DWORD aStatus;
	if( FAILED( hr = aDSBuffer->GetStatus( &aStatus ) ) ){
		MessageBox( NULL, "FAIL:GetStatus", "ERROR", MB_OK|MB_ICONHAND );
		return( hr );
	}
	// ���X�g���Ă����畜�������݂�
	if( aStatus & DSBSTATUS_BUFFERLOST ){
		// �A�v���P�[�V�����ɐ���̈����n����҂�
		do {
			hr = aDSBuffer->Restore();
			if( hr == DSERR_BUFFERLOST )
				Sleep(10);
		}
        while( ( hr = aDSBuffer->Restore() ) == DSERR_BUFFERLOST );

		// �������������Ă�����t���O��TRUE��
		if(pRestoreFlag != NULL)
			*pRestoreFlag = TRUE;

		return S_OK;
	}
	else
		return S_FALSE;
}
//----------------------//
//�@�g�`�t�@�C�����J��  //
//----------------------//
HRESULT openWaveFile(char *aWaveFileName , theSounds *aSound)
{
	MMCKINFO		aChunkInfo;			//�`�����N�������߂�
	PCMWAVEFORMAT	aPCMWaveFormat;		//���[�h����PCM�̏����ꎞ�I�ɕۑ�����

	// �w�肳�ꂽ�t�@�C����mmioOpen�ŊJ���B
	aSound->sndHmmio = mmioOpen( aWaveFileName , NULL , MMIO_ALLOCBUF | MMIO_READ);
	// �t�@�C�����J�Ȃ�����
	if(aSound->sndHmmio == NULL){
		// �J�����g�ɂȂ��̂�sounds�t�H���_���m���߂�B
		TCHAR strWavFile[MAX_PATH];
		lstrcpyn( strWavFile, kSoundsPath, MAX_PATH );
		lstrcpyn( strWavFile + kSoundsPathLength, aWaveFileName, MAX_PATH - kSoundsPathLength );

		aSound->sndHmmio = mmioOpen( strWavFile , NULL , MMIO_ALLOCBUF | MMIO_READ);
		if( aSound->sndHmmio == NULL ){
			MessageBox( NULL, "FAIL:mmioOpen", "ERROR", MB_OK|MB_ICONHAND );
			return E_FAIL;
		}
	}

	// mmioOpen�֐��ŊJ�����g�`�t�@�C����擪����T������B
	if((MMSYSERR_NOERROR != mmioDescend( aSound->sndHmmio, &(aSound->sndChunkRiff) , NULL, 0))){
		MessageBox(NULL, "FAIL:mmioDescend", "ERROR", MB_OK|MB_ICONHAND);
		goto FAIL_RETURN;
	}

	// �L���ȃt�@�C�����m�F����
	if( (aSound->sndChunkRiff.ckid != FOURCC_RIFF) || (aSound->sndChunkRiff.fccType != mmioFOURCC('W', 'A', 'V', 'E') ) ){
		MessageBox( NULL, "FAIL:mmioFOURCC", "ERROR", MB_OK|MB_ICONHAND );
		goto FAIL_RETURN;
	}

	// �L���ȓ��̓t�@�C���ł���΁A'fmt '�`�����N��T��
	aChunkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if( MMSYSERR_NOERROR != mmioDescend( aSound->sndHmmio, &aChunkInfo, &(aSound->sndChunkRiff), MMIO_FINDCHUNK ) ){
		MessageBox( NULL, "FAIL:mmioDescend2", "ERROR", MB_OK|MB_ICONHAND );
		goto FAIL_RETURN;
	}

	// ����'fmt '�`�����N�����ʂȃp�����[�^�������������f
	if( aChunkInfo.cksize < (LONG) sizeof(PCMWAVEFORMAT)){
		MessageBox( NULL, "FAIL:PCMWAVEFORMAT", "ERROR", MB_OK|MB_ICONHAND );
		goto FAIL_RETURN;
	}
	// 'fmt '�`�����N��<PCMWAVEFORMAT>�֓ǂݏo�����B
	if( mmioRead( aSound->sndHmmio, (HPSTR) &aPCMWaveFormat, sizeof(aPCMWaveFormat)) != sizeof(aPCMWaveFormat) ){
		MessageBox( NULL, "FAIL:mmioRead", "ERROR", MB_OK|MB_ICONHAND );
		goto FAIL_RETURN;
	}
	// waveformatex��z�u����
	if( aPCMWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM ){
		// PCM�\���̂�waveformatEX�\���̂ɃR�s�[����
		aSound->sndWaveFormatEx.wFormatTag      = aPCMWaveFormat.wf.wFormatTag;
		aSound->sndWaveFormatEx.nChannels       = aPCMWaveFormat.wf.nChannels;
		aSound->sndWaveFormatEx.nSamplesPerSec  = aPCMWaveFormat.wf.nSamplesPerSec;
		aSound->sndWaveFormatEx.nAvgBytesPerSec = aPCMWaveFormat.wf.nAvgBytesPerSec;
		aSound->sndWaveFormatEx.nBlockAlign     = aPCMWaveFormat.wf.nBlockAlign;
		aSound->sndWaveFormatEx.wBitsPerSample  = aPCMWaveFormat.wBitsPerSample;

		aSound->sndWaveFormatEx.cbSize = 0;//�ǉ��t�H�[�}�b�g�ł͂Ȃ��̂�cbSize��0
	}
	else{// PCM�t�H�[�}�b�g�łȂ�������A��
		MessageBox( NULL, "FAIL:mmioRead", "ERROR", MB_OK|MB_ICONHAND );
		goto FAIL_RETURN;
	}
	// mmioDescend�̋t�B���̓t�@�C����'fmt '�`�����N���甲���o��
	if( MMSYSERR_NOERROR != mmioAscend( aSound->sndHmmio, &aChunkInfo, 0 ) ){
		MessageBox( NULL, "FAIL:mmioAscend", "ERROR", MB_OK|MB_ICONHAND );
		goto FAIL_RETURN;
	}

	// ����I�����ɂ́AaSound.paWaveFormatEx�Ɏw�肳�ꂽRIFF�t�@�C���ɓ����Ă���PCM�����t�H�[�}�b�g�����߂��Ă���
	if( FAILED(rewindWaveFile( aSound )) ){
		MessageBox( NULL, "FAIL:RewindWaveFile", "ERROR", MB_OK|MB_ICONHAND );
		goto FAIL_RETURN;
	}

	return S_OK;

FAIL_RETURN:
	closeWaveFile( aSound );
	return E_FAIL;
}
//----------------------//
//�@�g�`�t�@�C������  //
//----------------------//
HRESULT	closeWaveFile(theSounds *aSound)
{
	if(aSound->sndHmmio == NULL)
		return E_FAIL;

	//�T�E���h�����
	if(FAILED(mmioClose(aSound->sndHmmio, 0))){
		MessageBox( NULL, "FAIL:mmioClose", "ERROR", MB_OK|MB_ICONHAND );
		return( E_FAIL );
	}

	return S_OK;
}
//--------------------------------------//
//�@�g�`�t�@�C���̓ǂݏo���ʒu�����߂�  //
//--------------------------------------//
HRESULT rewindWaveFile(theSounds *aSound)
{
	// �O�̂��߂̃G���[�`�F�b�N
	if( aSound->sndHmmio == NULL)
		return E_FAIL;
	// �g�`�t�@�C���̓�����
	if(mmioSeek( aSound->sndHmmio, aSound->sndChunkRiff.dwDataOffset + sizeof(FOURCC) , SEEK_SET ) == -1){
		MessageBox( NULL, "FAIL:mmioSeek", "ERROR", MB_OK|MB_ICONHAND );
		return( E_FAIL );
	}
	// ���̓t�@�C���̃f�[�^�`�����N��T���āA���̃`�����N�̏���aSound.aChunk�Ɏ��߂�
	aSound->sndChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if( MMSYSERR_NOERROR != mmioDescend( aSound->sndHmmio, &(aSound->sndChunk), &(aSound->sndChunkRiff), MMIO_FINDCHUNK ) ){
		MessageBox( NULL, "FAIL:mmioDescend", "ERROR", MB_OK|MB_ICONHAND );
		return( E_FAIL );
	}

	return S_OK;
}
//----------------//
//�@�����Đ�����  //
//----------------//
HRESULT playASound( theSounds *aSound , DWORD aPriority ,DWORD aFlag ,BOOL aOverride)
{
	HRESULT	hr;     // ���ʕԂ��p
	BOOL aRestored;	// �o�b�t�@���������ꂽ�H
	DWORD	aFreeDSB = selectFreeBuffer( aSound , aOverride );

	if( aSound->sndDSSoundBuffer[aFreeDSB] == NULL ){
		MessageBox( NULL, "FAIL:SelectFreeBuffer", "ERROR", MB_OK|MB_ICONHAND );
		return E_FAIL;
	}
	// �o�b�t�@�������Ă��Ȃ����m�F���A�����Ă���ꍇ�͕��������݂�
	if(FAILED(hr = restoreDSBuffer( aSound->sndDSSoundBuffer[aFreeDSB] , &aRestored ))){
		MessageBox( NULL, "FAIL:RestoreDSBuffer", "ERROR", MB_OK|MB_ICONHAND );
		return E_FAIL;
	}
	// �o�b�t�@���������ꂽ�ꍇ�A�f�[�^�������Ă���\��������̂ŉ��߂ēǂݍ���
	if(aRestored){
		if(FAILED(hr = fillupSoundBuffer( aSound , aFreeDSB))){
			MessageBox( NULL, "FAIL:FillupSoundBuffer", "ERROR", MB_OK|MB_ICONHAND );
			return( E_FAIL );
		}
	}
	//                                               �\��   �D��x    ���[�v��DSBPLAY_LOOPING
	return( aSound->sndDSSoundBuffer[aFreeDSB]->Play( 0 , aPriority , aFlag ));
}
//------------------------------//
//�@�S�Ẵo�b�t�@�̉����~�߂�  //
//------------------------------//
HRESULT StopASound( theSounds *aSound )
{
	HRESULT	hr = 0;

	if(aSound->sndDSSoundBuffer == NULL)
		return E_FAIL;
	//�S�Ẵo�b�t�@�̉����~�߂�;
	for(unsigned int i=0 ; i< aSound->sndNumOfBuffers; i++)
		hr |= aSound->sndDSSoundBuffer[i]->Stop();
	
	return(hr);
}
//-------------------------------//
//�@�S�Ẵo�b�t�@�̓����������� //
//-------------------------------//
HRESULT RewindASound( theSounds *aSound )
{
	HRESULT	hr = 0;

	if(aSound->sndDSSoundBuffer == NULL)
		return E_FAIL;
	//�S�Ẵo�b�t�@�̓����������Ȃ��Ƃ������Ȏ��ɂȂ�B
	for(unsigned int i=0; i< aSound->sndNumOfBuffers; i++ )
		hr |= aSound->sndDSSoundBuffer[i]->SetCurrentPosition(NULL);

	return(hr);
}
//--------------------------------//
//�@�g�p���ł͂Ȃ��o�b�t�@��T��  //
//--------------------------------//
DWORD selectFreeBuffer(theSounds *aSound , BOOL aOverride)
{
	int i;
	// �o�b�t�@��NULL��������A��
	if(aSound->sndDSSoundBuffer[0] == NULL)
		return E_FAIL;

	// �o�b�t�@�̐������J��Ԃ�
	for(i=0; (unsigned)i< aSound->sndNumOfBuffers; i++){
		if(aSound->sndDSSoundBuffer[i] != NULL){
			DWORD aStatus;
			// �X�e�[�^�X���`�F�b�N���čĐ����łȂ����̂�T��
			aSound->sndDSSoundBuffer[i]->GetStatus( &aStatus );
			if((aStatus & DSBSTATUS_PLAYING) == 0)
				break;
		}
	}
	// ���g�p�o�b�t�@����������i0�̒l��kNumOfBuffer�ƈقȂ�̂ŁAi0��Ԃ�
	if(i == aSound->sndNumOfBuffers){
		if(aOverride){ // �����ŃI�[�o�[���C�h�t���O�������Ă�����o�b�t�@�̒����烉���_���őI��ŕԂ�
			i = rand() % (aSound->sndNumOfBuffers);
			//�I�񂾃o�b�t�@�̍Đ����~���Ċ����߂�
			aSound->sndDSSoundBuffer[i]->Stop();
			aSound->sndDSSoundBuffer[i]->SetCurrentPosition(0);
		}
		else
			i = -1;
	}

	return i;
}
//----------------//
//  MIDI�ǂݍ���  //
//----------------//
HRESULT loadSegmentFromMusicFile( char *aWaveFileName , theMusic *aMusic )
{
	HRESULT	hr;
	IUnknown* pConfig = NULL;	//�t�@�C���̑g�ݍ��݃I�[�f�B�I�p�X���擾���邽��
	CHAR strMusicPath[kSTR_LENGTH]; // �p�X�̂��߂̕�����̈�
	WCHAR wstrSearchPath[MAX_PATH+1], wstrWaveFileName[kSTR_LENGTH+1]; // DirectMusic�̓��C�h�L�������������Ȃ�

	// �V�����Z�O�����g���쐬���邽�߂ɁA�Â��Z�O�����g��j������
	SAFE_RELEASE( aMusic->pMusSegment );
	// ���[�_�[���̏��𐮗����Ȃ���
	if(g_pDMLoader)
		g_pDMLoader->CollectGarbage();
	// ���݂̃f�B���N�g�����擾
	if( GetCurrentDirectory( MAX_PATH+1 ,strMusicPath ) == 0 )
		goto FAIL_RETURN;
	// ANSI�L������UNICORD�ɕϊ�����
	// CP_ACP��MultiByteToWideChar�ɗ^���镶����ANSI������ł��邱�Ƃ�����
	MultiByteToWideChar( CP_ACP, 0, strMusicPath, -1, wstrSearchPath, MAX_PATH );
	MultiByteToWideChar( CP_ACP, 0, aWaveFileName, -1, wstrWaveFileName, kSTR_LENGTH );

	// ������NULL������ǉ����Ė�����̃G���[��h��
	wstrSearchPath[MAX_PATH] = '\0';
	wstrWaveFileName[kSTR_LENGTH] = '\0';
	// �����p�f�B���N�g���̐ݒ�
	g_pDMLoader->SetSearchDirectory( GUID_DirectMusicAllTypes, wstrSearchPath, FALSE );
	// ���y�t�@�C������Z�O�����g�����[�h����
	if( FAILED( hr = g_pDMLoader->LoadObjectFromFile(	CLSID_DirectMusicSegment,	IID_IDirectMusicSegment8,
														wstrWaveFileName,			(LPVOID*)&(aMusic->pMusSegment) ) ) ){
		// �����J�����g�f�B���N�g���Ƀt�@�C��������������Amodels�t�H���_���m���߂�B
		// �o�b�N�X���b�V��(\)����d�Ȃ��Ă���̂́A�G�X�P�[�v�V�[�P���X���L���ɂȂ��Ă��邽��
		TCHAR aStr[MAX_PATH];
		lstrcpyn( aStr, strMusicPath, MAX_PATH );
		lstrcpyn( aStr + lstrlen(strMusicPath) , kMusicPath, MAX_PATH - kMusicPathLength );

		MultiByteToWideChar( CP_ACP, 0, aStr, -1, wstrSearchPath, MAX_PATH );

		// �����p�f�B���N�g���̐ݒ�
		g_pDMLoader->SetSearchDirectory( GUID_DirectMusicAllTypes, wstrSearchPath, FALSE );

		// �J�����g�t�H���_�Ō�����Ȃ�������Amusic�t�H���_��T��
		if( FAILED( hr = g_pDMLoader->LoadObjectFromFile(	CLSID_DirectMusicSegment,	IID_IDirectMusicSegment8,
															wstrWaveFileName,			(LPVOID*)&(aMusic->pMusSegment) ) ) ){
			char cautionString[kSTR_LENGTH];
			wsprintf( cautionString , "���y�t�@�C���w%s�x�͌�����Ȃ��������A�ǂݍ��ݕs�\�ȃt�H�[�}�b�g�ł��B", aWaveFileName);
			MessageBox(NULL, cautionString, "�ǂݍ��݃G���[" , MB_OK);
			goto FAIL_RETURN;
		}
	}
	// �Z�O�����g���̂ɃI�[�f�B�I�p�X���܂܂�Ă����ꍇ�͂���𗘗p����
	if( SUCCEEDED( aMusic->pMusSegment->GetAudioPathConfig( &pConfig ) ) ){
		g_pDMPerformance->CreateAudioPath( pConfig, TRUE, &(aMusic->pMusAudioPath) );
		SAFE_RELEASE( pConfig );
	}
	else
		aMusic->pMusAudioPath = NULL;

	// �����A�w�肳�ꂽ�t�@�C����midi�t�@�C���������ꍇ�ADirectMusic�ɂ����`����
	if( strstr( aWaveFileName, ".mid" ) != NULL || strstr( aWaveFileName, ".rmi" ) != NULL )
		// �p�����[�^�̐ݒ�
		if( FAILED( hr = aMusic->pMusSegment->SetParam( GUID_StandardMIDIFile, 0xFFFFFFFF, 0, 0, NULL ) ) )
			goto FAIL_RETURN;

	// �V���Z�T�C�U�[�ɃZ�O�����g�̉����Ȃǂ��_�E�����[�h����
	if( aMusic->pMusAudioPath ){
		if( SUCCEEDED(aMusic->pMusSegment->Download( aMusic->pMusAudioPath )) )
			aMusic->bDownLoaded = TRUE;
	}
	else if( SUCCEEDED(aMusic->pMusSegment->Download( g_pDMPerformance )) )
			aMusic->bDownLoaded = TRUE;

	return S_OK;

	// �G���[���̏o��
FAIL_RETURN:

	SAFE_RELEASE(g_pDMLoader); 
	SAFE_RELEASE(g_pDMPerformance); 

	return hr;
}
//--------------------//
//  �Z�O�����g�̍Đ�  //
//--------------------//
HRESULT playAMusic(theMusic *aMusic)
{
	// �����Z�O�����g������������_�E�����[�h�Ɏ��s���Ă�����G���[
	if(( aMusic->pMusSegment == NULL )||( !aMusic->bDownLoaded ))
		return E_FAIL;
	if( isPlayingAMusic( aMusic ) != S_OK )
		stopAMusic(aMusic);

	// ���̃Z�O�����g�������ƍĐ����Â���ݒ�ɂ���
	aMusic->pMusSegment->SetRepeats( DMUS_SEG_REPEAT_INFINITE );

	IDirectMusicAudioPath8*	paAudioPath; // �I�[�f�B�I�p�X
	
	if( aMusic->pMusAudioPath )
		paAudioPath = aMusic->pMusAudioPath;
	else
		paAudioPath = g_pDMAudioPath;

    // �I�[�f�B�I�p�X�̃Z�O�����g���Đ�����
	g_pDMPerformance->PlaySegmentEx( aMusic->pMusSegment, 0, NULL, DMUS_SEGF_BEAT, 0, 0, NULL, paAudioPath );

	return S_OK;
}
//------------------------//
//�@�Z�O�����g�Đ��̒�~  //
//------------------------//
HRESULT	stopAMusic( theMusic *aMusic )
{
	if( g_pDMPerformance == NULL )
		return( E_FAIL);
	// IsPlaying�֐��́A�Đ�����Ă��Ȃ��Ƃ���S_FALSE��Ԃ����ߖ����I�Ƀ`�F�b�N����
	if( isPlayingAMusic( aMusic ) != S_OK )
		g_pDMPerformance->Stop( NULL , NULL , 0 , 0);

	return(S_OK);
}
//------------------------------//
//�@�Z�O�����g���Đ������ǂ���  //
//------------------------------//
HRESULT	isPlayingAMusic( theMusic *aMusic )
{
	if(( g_pDMPerformance == NULL )||( aMusic->pMusSegment == NULL ))
		return( E_FAIL);
	return(( g_pDMPerformance->IsPlaying( aMusic->pMusSegment , NULL) == S_OK ));
}
//--------------------------//
//�@�}�X�^�{�����[���̐ݒ�  //
//--------------------------//
HRESULT setAVolume( long aVolume )
{
	if( g_pDMPerformance == NULL )
		return( E_FAIL);
	// �{�����[���̐ݒ�
	g_pDMPerformance->SetGlobalParam( GUID_PerfMasterVolume, (void*)&aVolume, sizeof(long) );

	return( S_OK );
}
//-------------------------//
//�@DirectMusic�̊J������  //
//-------------------------//
void cleanUpDirectMusic(void)
{
	// ���[�_�[�ɃZ�O�����g�̊J����ʒm���Ă���Z�O�����g���J������
	if( g_pDMLoader ){
		for(int i=0 ; i<kNUM_OF_BGM; i++ ){
			// ���y���Đ����Ă������~����
			stopAMusic( &g_BGM[i] );
			// ���[�_�[�ɃZ�O�����g�̊J����ʒm����
			g_pDMLoader->ReleaseObjectByUnknown( g_BGM[i].pMusSegment );
			// �Z�O�����g�̊J���ƃA�����[�h
			if( g_BGM[i].bDownLoaded ){
				if( g_BGM[i].pMusAudioPath )
					g_BGM[i].pMusSegment->Unload( g_BGM[i].pMusAudioPath );
				else
					g_BGM[i].pMusSegment->Unload( g_pDMPerformance );
				g_BGM[i].bDownLoaded = FALSE;
			}
			SAFE_RELEASE( g_BGM[i].pMusSegment );
			// �I�[�f�B�I�p�X�̊J��
			SAFE_RELEASE( g_BGM[i].pMusAudioPath );
		}
	}

	SAFE_RELEASE( g_pDMLoader );		// ���[�_�[�̊J��
	SAFE_RELEASE( g_pDMAudioPath );		// �I�[�f�B�I�p�X�̊J��

	// �p�t�H�[�}���X�̊J��
	if( g_pDMPerformance ){
		g_pDMPerformance->CloseDown();
		SAFE_RELEASE( g_pDMPerformance );
	}

	// COM�I�u�W�F�N�g�̌�n��
	if( g_bComInit ){
		CoUninitialize();
		g_bComInit = FALSE;
	}
}
//---------------------//
//�@DirectSound�̏I��  //
//---------------------//
void cleanUpDirectSound(void)
{
	cleanUpTheSounds();
	SAFE_RELEASE( g_pDirectSound );	//DirectSound�I�u�W�F�N�g�̍폜
}
//------------------------//
//  themusic�\���̏�����  //
//------------------------//
void initTheMUSIC(void)
{
	for(int i=0; i<kNUM_OF_BGM; i++){
		g_BGM[i].pMusSegment = NULL;
		g_BGM[i].pMusAudioPath = NULL;
		g_BGM[i].bDownLoaded = FALSE;
	}
}
//-----------------------//
//�@theSounds�\���̊J��  //
//-----------------------//
HRESULT	cleanUpTheSounds(void)
{
	for(int i=0; i<SOUNDFILEMAX; i++){
		SAFE_DELETE_ARRAY( g_SE[i].sndDSSoundBuffer );
		SAFE_DELETE_ARRAY( g_SE[i].sndDS3DSBuffer );
		SAFE_DELETE_ARRAY( g_SE[i].sndDS3DSBufferParams );
		closeWaveFile( &g_SE[i] );
	}

	return S_OK;
}
//---------------------------//
//�@theSounds�\���̂̏�����  //
//---------------------------//
HRESULT	initTheSounds(void)
{
	for(DWORD i=0; i<SOUNDFILEMAX; i++){
		g_SE[i].sndCreationFlags = 0;
		g_SE[i].sndNumOfBuffers  = -1;
		g_SE[i].sndDSSoundBuffer = NULL;

		g_SE[i].sndDS3DSBuffer       = NULL;
		g_SE[i].sndDS3DSBufferParams = NULL;
	}

	return S_OK;
}
//---------------//
// �����ǂݍ���  //
//---------------//
void LoadMusicFile(void)
{
	// ���ʉ��\���̂̏�����
	initTheSounds();
	// ���ʉ��̓ǂݍ���
	if(FAILED( setupSounds())){
		MessageBox( NULL, "���ʉ��̓ǂݍ��݂Ɏ��s���܂����B", "ERROR", MB_OK|MB_ICONHAND );
		cleanUpDirectSound(); // DirectSound�̌�n��
		return;
	}
	// BGM�\���̂̏�����
	initTheMUSIC();
	for(int i=1; i<kNUM_OF_BGM; i++)
		loadSegmentFromMusicFile(MusicFile[i], &g_BGM[i]);
	setAVolume(MusicVol);
}