//-----------------------//
//  DirectSoundの初期化  //
//-----------------------//
HRESULT initDirectSound( HWND hWnd )
{
	HRESULT hr;         //結果用
	DSBUFFERDESC aDSBD; //バッファ記述子
	WAVEFORMATEX aWFEX; //波形オーディオデータのフォーマット
	LPDIRECTSOUNDBUFFER	pPrimaryBuffer = NULL;	//プライマリバッファを確保するための仮のバッファ

	SAFE_RELEASE( g_pDirectSound );	//念のための初期化

	// プライマリサウンドディバイスを使って探す
	if( FAILED(hr=DirectSoundCreate8(NULL, &g_pDirectSound, NULL)) )
		return hr;

	//協調レベルを設定する
	if( FAILED(hr=g_pDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY) ) )
		return hr;

	// プライマリバッファを取得する
	ZeroMemory( &aDSBD,	sizeof(DSBUFFERDESC) );				// 構造体のゼロリセット（必ず行う）
    aDSBD.dwSize			= sizeof(DSBUFFERDESC);			// 必ずsizeof(DSBUFFERDESC)
    aDSBD.dwFlags			= DSBCAPS_PRIMARYBUFFER;		// プライマリバッファ。
    aDSBD.dwBufferBytes		= 0;							// プライマリバッファの場合は必ず0
    aDSBD.lpwfxFormat		= NULL;							// プライマリバッファの場合は必ずNULL
	
	// CreateSoundBufferのチェックは必ずFAILEDマクロで行う
	if( FAILED(hr=g_pDirectSound->CreateSoundBuffer(&aDSBD, &pPrimaryBuffer, NULL)) )
		return hr;
	ZeroMemory( &aWFEX, sizeof(WAVEFORMATEX) ); 			// 構造体のゼロリセット（必ず行う）
	aWFEX.wFormatTag		= (WORD) WAVE_FORMAT_PCM;		// PCM波形フォーマットを用いる
	aWFEX.nChannels			= (WORD) kPrimaryChannels;		// チャネル数、周波数、ビットレートはヘッダを参照
	aWFEX.nSamplesPerSec	= (DWORD) kPrimaryFreq; 
	aWFEX.wBitsPerSample	= (WORD) kPrimaryBitRate; 
	aWFEX.nBlockAlign		= (WORD) (aWFEX.wBitsPerSample / 8 * aWFEX.nChannels);	//ここの二行は必ずこうする
	aWFEX.nAvgBytesPerSec	= (DWORD) (aWFEX.nSamplesPerSec * aWFEX.nBlockAlign);
	// プライマリバッファのフォーマットを設定
	// SetFormat関数はプライマリバッファの設定を行うための特別な関数である
	if( FAILED(hr=pPrimaryBuffer->SetFormat(&aWFEX)) )
		return hr;
	// SetFormat関数が正常に終わったので、もういらない
    SAFE_RELEASE( pPrimaryBuffer );

	return( S_OK );
}
//---------------------//
//  DirectMusic初期化  //
//---------------------//
HRESULT	initDirectMusic( HWND hWnd, LPDIRECTSOUND8 pTheDS )
{
	// COMオブジェクトの初期化
	if( !g_bComInit ){
		CoInitialize(NULL);
		g_bComInit = TRUE;
	}

	HRESULT hr; // 戻り値
	IDirectSound* paDirectSound;	//DirectSoundとDirectMusicの連動に必要

	// DirectSoundが初期化されていなかったら帰る
	if(pTheDS == NULL)
		return E_FAIL;
	else
		pTheDS->QueryInterface(IID_IDirectSound, (void**)&paDirectSound);
	// ローダーオブジェクトの生成
	if(FAILED(hr = CoCreateInstance(CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC, IID_IDirectMusicLoader8, (void**)&g_pDMLoader )))
		goto FAIL_RETURN;
	// パフォーマンスオブジェクトの生成
	if(FAILED(hr = CoCreateInstance(CLSID_DirectMusicPerformance, NULL, CLSCTX_INPROC, IID_IDirectMusicPerformance8, (void**)&g_pDMPerformance )))
		goto FAIL_RETURN;
	// パフォーマンスの初期化
	if(FAILED(hr = g_pDMPerformance->InitAudio(	NULL, &paDirectSound, hWnd, DMUS_APATH_SHARED_STEREOPLUSREVERB,
												kDirectMusicChannels, DMUS_AUDIOF_ALL, NULL )))
		goto FAIL_RETURN;
	// デフォルトオーディオパスの取得
	g_pDMPerformance->GetDefaultAudioPath( &g_pDMAudioPath );

	return(S_OK);

// エラー時の出口
FAIL_RETURN:

	SAFE_RELEASE( g_pDMPerformance );
	SAFE_RELEASE( g_pDMLoader );
	return(hr);
}
//----------------------//
//　サウンドの読み込み  //
//----------------------//
HRESULT	setupSounds(void)
{
	for(int i=1; i<SOUNDFILEMAX; i++)
		if(FAILED(loadSoundsFromWaveFile(SoundFile[i], &g_SE[i], DSBCAPS_CTRLVOLUME, GUID_NULL, kNUM_OF_SE_BUFFERS)))	
			return E_FAIL;

	return S_OK;
}
//--------------------------------------//
//　セカンダリバッファを用意、読み込み  //
//--------------------------------------//
HRESULT	loadSoundsFromWaveFile(char *aWaveFileName, theSounds *aSound, DWORD aCreationFlags, GUID guid3DAlgorithm, DWORD aNumOfBuffers)
{
	HRESULT hr;
	int i; //汎用カウンタ
	char tmpString[kSTR_LENGTH];
	LPDIRECTSOUNDBUFFER* aDSBuffers = NULL; //仮バッファ

	// ファイル名がNULLだったら帰る
	if( aWaveFileName == NULL)
		return E_FAIL;

	// サウンドバッファへのポインタを確保
	aDSBuffers = new LPDIRECTSOUNDBUFFER[aNumOfBuffers];
	if( aDSBuffers == NULL )
		return E_FAIL; // メモリの確保に失敗？

	// 波形ファイルの読み込み
	if( FAILED( hr = openWaveFile( aWaveFileName , aSound ))){
		// カレントにファイルが無かったら、soundsフォルダへ
		TCHAR strWavFile[MAX_PATH];
		lstrcpyn( strWavFile, kSoundsPath, MAX_PATH );
		lstrcpyn( strWavFile + kSoundsPathLength, aWaveFileName, MAX_PATH - kSoundsPathLength );

		if( FAILED( hr = openWaveFile( strWavFile , aSound ))){
			wsprintf( tmpString , "wavファイル『%s』が見つかりませんでした", strWavFile);
			goto FAIL_RETURN;
		}
	}
	// DirectSoundバッファの作成
	DSBUFFERDESC	aDSBDesc;	//バッファ記述子

	ZeroMemory( &aDSBDesc, sizeof(DSBUFFERDESC) );
	aDSBDesc.dwSize          = sizeof(DSBUFFERDESC);      //ここは必ずsizeof(DSBUFFERDESC)
	aDSBDesc.dwFlags         = aCreationFlags;            //生成時フラグ
	aDSBDesc.dwBufferBytes   = aSound->sndChunk.cksize;   //バッファサイズ（波形ファイルのデータと同じ）
	aDSBDesc.guid3DAlgorithm = guid3DAlgorithm;           //ソフトウェアミキシングで使うアルゴリズム
	aDSBDesc.lpwfxFormat     = &(aSound->sndWaveFormatEx);//OepnWaveFileで開いたRIFFファイルに入っているPCM音声フォーマット

	// PCM以外のデータを再生できるかどうか呼び出し元に知らせる
	if(FAILED(hr = g_pDirectSound->CreateSoundBuffer( &aDSBDesc, &aDSBuffers[0], NULL ))){
		wsprintf(tmpString , "FAIL:CreateSoundBuffer file=%s",aWaveFileName);
		goto FAIL_RETURN;
	}
	//バッファの複製
	for(i=0; (unsigned)i<aNumOfBuffers; i++){
		if( FAILED( hr = g_pDirectSound->DuplicateSoundBuffer( aDSBuffers[0] , &aDSBuffers[i] )) ){
			wsprintf( tmpString , "FAIL:DuplicateSoundBuffer");
			goto FAIL_RETURN;
		}
	}

	// 指定された数のバッファを作成してそのポインタを引き渡す
	aSound->sndDSSoundBuffer = new LPDIRECTSOUNDBUFFER[aNumOfBuffers];
	if( aSound->sndDSSoundBuffer == NULL ){
		wsprintf( tmpString , "FAIL:aDSSoundBuffer");
		goto FAIL_RETURN;
	}
	//バッファの数をtheSounds構造体に記録する
	aSound->sndNumOfBuffers = aNumOfBuffers;
	//バッファ領域のコピー
	for(i=0; (unsigned)i<aNumOfBuffers; i++){
		aSound->sndDSSoundBuffer[i] = aDSBuffers[i];
		// 音量設定
		aSound->sndDSSoundBuffer[i]->SetVolume(SoundVol);
	}
	//バッファに音を用意する
	fillupSoundBuffer(aSound , NULL);

	SAFE_DELETE_ARRAY(aDSBuffers);//仮のバッファを破棄
	return S_OK;

	//エラー時はここから帰る
FAIL_RETURN:

	MessageBox(NULL, tmpString, "ERROR" , MB_OK|MB_ICONHAND );
	SAFE_DELETE_ARRAY(aDSBuffers); // 仮のバッファを破棄
	return E_FAIL;
}
//-----------------------------------------//
// theSoundバッファに波形データを読み込む  //
//-----------------------------------------//
HRESULT fillupSoundBuffer(theSounds *aSound , DWORD aLockBuffer)
{
	HRESULT hr; // 結果用
	VOID*	apLockedBuffer    = NULL; // ロックされたDirectSoundバッファへのポインタ
	DWORD	aLockedBufferSize = 0;    // ロックされたDirectSoundバッファのサイズ
	DWORD	aReadedData       = 0;    // 波形ファイルから読み出されたデータのバイト数 

	if( aSound->sndDSSoundBuffer[aLockBuffer] == NULL )
		return E_FAIL;
    // バッファが確実に存在することを確かめる。
	if( FAILED( hr = restoreDSBuffer( aSound->sndDSSoundBuffer[aLockBuffer], NULL ) ) ){
		MessageBox( NULL, "FAIL:RestoreBuffer", "ERROR", MB_OK|MB_ICONHAND );
		return( hr );
	}
	// バッファをロックする
	if( FAILED( hr =  aSound->sndDSSoundBuffer[aLockBuffer]->Lock( 0, aSound->sndChunk.cksize , &apLockedBuffer , &aLockedBufferSize, NULL, NULL, 0L ) ) ){
		MessageBox( NULL, "FAIL:Lock", "ERROR", MB_OK|MB_ICONHAND );
		return hr;
	}
	// 波形ファイルの頭だしをする
    rewindWaveFile( aSound );

	if( FAILED( hr = readWaveToBuffer( aSound , (BYTE*)apLockedBuffer , aLockedBufferSize , &aReadedData ) ) ){
		MessageBox( NULL, "FAIL:Read", "ERROR", MB_OK|MB_ICONHAND );
		return hr;
	}

	if(aReadedData == NULL)
		// 波形データが無かったら無音で埋める
		FillMemory( (BYTE*) apLockedBuffer, aLockedBufferSize, (BYTE)(aSound->sndWaveFormatEx.wBitsPerSample == 8 ? 128 : 0 ) );
	else if(aReadedData < aLockedBufferSize)
		// 波形ファイルを繰り返さないで無音で埋める
		FillMemory(	(BYTE*) apLockedBuffer + aReadedData, aLockedBufferSize - aReadedData, (BYTE)(aSound->sndWaveFormatEx.wBitsPerSample == 8 ? 128 : 0 ) );
    // 必要がなくなったので、バッファをアンロックする
	aSound->sndDSSoundBuffer[aLockBuffer]->Unlock( apLockedBuffer, aLockedBufferSize, NULL, 0 );

    return S_OK;
}
//-----------------------------------------------//
// aBufferにデータ読み込みaReadedDataにバイト数  //
//-----------------------------------------------//
HRESULT readWaveToBuffer( theSounds *aSound , BYTE* aBuffer, DWORD aSizeToRead, DWORD* aReadedData )
{
	MMIOINFO mmioInfoIn; // aSound->sndHmmioの現在の状況

	if(aSound->sndHmmio == NULL)
		return E_FAIL;
	if( aBuffer == NULL || aSizeToRead == NULL )
		return E_FAIL;

	*aReadedData = 0;	//結果（読み込んだバイト数）を初期化
	// mmioGetInfoでaSound->sndHmmioの情報をmmioInfoInに納める
	if(mmioGetInfo( aSound->sndHmmio, &mmioInfoIn, 0 ) != NULL){
		MessageBox( NULL, "FAIL:mmioGetInfo", "ERROR", MB_OK|MB_ICONHAND );
		return E_FAIL;
	}

	// 読み込むデータのサイズを調べる。
	UINT aNumOfReadBytes = aSizeToRead;
	if( aNumOfReadBytes > aSound->sndChunk.cksize )
		aNumOfReadBytes = aSound->sndChunk.cksize;
	// 実際の読み出しループ
	for(int i=0; (unsigned)i<aNumOfReadBytes; i++){
		// バッファの戦闘を指してる為バッファの状態更新
		if( mmioInfoIn.pchNext == mmioInfoIn.pchEndRead ){
			// ファイルの終わり
			if(mmioAdvance( aSound->sndHmmio, &mmioInfoIn, MMIO_READ ) != NULL){
				MessageBox( NULL, "FAIL:mmioAdvance", "ERROR", MB_OK|MB_ICONHAND );
				return E_FAIL;
			}
			// 読み込むデータのサイズを上で確認しているのにファイルの終わりがきている
			if(mmioInfoIn.pchNext == mmioInfoIn.pchEndRead){
				// 失敗したら帰る
				MessageBox( NULL, "FAIL:mmioInfoIn.pchNext", "ERROR", MB_OK|MB_ICONHAND );
				return( E_FAIL );
			}
		}
		// 実際のコピー
		*((BYTE*)aBuffer + i) = *((BYTE*)mmioInfoIn.pchNext);
		mmioInfoIn.pchNext++;
	}
	// mmio取得情報更新
	if(mmioSetInfo( aSound->sndHmmio , &mmioInfoIn, 0 ) != NULL){
		MessageBox( NULL, "FAIL:mmioSetInfo", "ERROR", MB_OK|MB_ICONHAND );
		return E_FAIL;
	}

	*aReadedData = aNumOfReadBytes;	//結果を引き渡し
	return S_OK;
}
//-------------------------------------------//
//　DirectSoundバッファが失われていたら復旧  //
//-------------------------------------------//
HRESULT	restoreDSBuffer( LPDIRECTSOUNDBUFFER aDSBuffer , BOOL* pRestoreFlag )
{
	HRESULT hr;

	// 復旧確認フラグがあれば、最初にリセット
	if( pRestoreFlag != NULL )
		*pRestoreFlag = FALSE;
	// バッファの状態を確認する
	DWORD aStatus;
	if( FAILED( hr = aDSBuffer->GetStatus( &aStatus ) ) ){
		MessageBox( NULL, "FAIL:GetStatus", "ERROR", MB_OK|MB_ICONHAND );
		return( hr );
	}
	// ロストしていたら復旧を試みる
	if( aStatus & DSBSTATUS_BUFFERLOST ){
		// アプリケーションに制御の引き渡しを待つ
		do {
			hr = aDSBuffer->Restore();
			if( hr == DSERR_BUFFERLOST )
				Sleep(10);
		}
        while( ( hr = aDSBuffer->Restore() ) == DSERR_BUFFERLOST );

		// 復旧が成功していたらフラグをTRUEに
		if(pRestoreFlag != NULL)
			*pRestoreFlag = TRUE;

		return S_OK;
	}
	else
		return S_FALSE;
}
//----------------------//
//　波形ファイルを開く  //
//----------------------//
HRESULT openWaveFile(char *aWaveFileName , theSounds *aSound)
{
	MMCKINFO		aChunkInfo;			//チャンク情報を収める
	PCMWAVEFORMAT	aPCMWaveFormat;		//ロードするPCMの情報を一時的に保存する

	// 指定されたファイルをmmioOpenで開く。
	aSound->sndHmmio = mmioOpen( aWaveFileName , NULL , MMIO_ALLOCBUF | MMIO_READ);
	// ファイルが開なかった
	if(aSound->sndHmmio == NULL){
		// カレントにないのでsoundsフォルダを確かめる。
		TCHAR strWavFile[MAX_PATH];
		lstrcpyn( strWavFile, kSoundsPath, MAX_PATH );
		lstrcpyn( strWavFile + kSoundsPathLength, aWaveFileName, MAX_PATH - kSoundsPathLength );

		aSound->sndHmmio = mmioOpen( strWavFile , NULL , MMIO_ALLOCBUF | MMIO_READ);
		if( aSound->sndHmmio == NULL ){
			MessageBox( NULL, "FAIL:mmioOpen", "ERROR", MB_OK|MB_ICONHAND );
			return E_FAIL;
		}
	}

	// mmioOpen関数で開いた波形ファイルを先頭から探索する。
	if((MMSYSERR_NOERROR != mmioDescend( aSound->sndHmmio, &(aSound->sndChunkRiff) , NULL, 0))){
		MessageBox(NULL, "FAIL:mmioDescend", "ERROR", MB_OK|MB_ICONHAND);
		goto FAIL_RETURN;
	}

	// 有効なファイルか確認する
	if( (aSound->sndChunkRiff.ckid != FOURCC_RIFF) || (aSound->sndChunkRiff.fccType != mmioFOURCC('W', 'A', 'V', 'E') ) ){
		MessageBox( NULL, "FAIL:mmioFOURCC", "ERROR", MB_OK|MB_ICONHAND );
		goto FAIL_RETURN;
	}

	// 有効な入力ファイルであれば、'fmt 'チャンクを探す
	aChunkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if( MMSYSERR_NOERROR != mmioDescend( aSound->sndHmmio, &aChunkInfo, &(aSound->sndChunkRiff), MMIO_FINDCHUNK ) ){
		MessageBox( NULL, "FAIL:mmioDescend2", "ERROR", MB_OK|MB_ICONHAND );
		goto FAIL_RETURN;
	}

	// もし'fmt 'チャンクが特別なパラメータを持つ時処理中断
	if( aChunkInfo.cksize < (LONG) sizeof(PCMWAVEFORMAT)){
		MessageBox( NULL, "FAIL:PCMWAVEFORMAT", "ERROR", MB_OK|MB_ICONHAND );
		goto FAIL_RETURN;
	}
	// 'fmt 'チャンクを<PCMWAVEFORMAT>へ読み出しす。
	if( mmioRead( aSound->sndHmmio, (HPSTR) &aPCMWaveFormat, sizeof(aPCMWaveFormat)) != sizeof(aPCMWaveFormat) ){
		MessageBox( NULL, "FAIL:mmioRead", "ERROR", MB_OK|MB_ICONHAND );
		goto FAIL_RETURN;
	}
	// waveformatexを配置する
	if( aPCMWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM ){
		// PCM構造体をwaveformatEX構造体にコピーする
		aSound->sndWaveFormatEx.wFormatTag      = aPCMWaveFormat.wf.wFormatTag;
		aSound->sndWaveFormatEx.nChannels       = aPCMWaveFormat.wf.nChannels;
		aSound->sndWaveFormatEx.nSamplesPerSec  = aPCMWaveFormat.wf.nSamplesPerSec;
		aSound->sndWaveFormatEx.nAvgBytesPerSec = aPCMWaveFormat.wf.nAvgBytesPerSec;
		aSound->sndWaveFormatEx.nBlockAlign     = aPCMWaveFormat.wf.nBlockAlign;
		aSound->sndWaveFormatEx.wBitsPerSample  = aPCMWaveFormat.wBitsPerSample;

		aSound->sndWaveFormatEx.cbSize = 0;//追加フォーマットではないのでcbSizeは0
	}
	else{// PCMフォーマットでなかったら帰る
		MessageBox( NULL, "FAIL:mmioRead", "ERROR", MB_OK|MB_ICONHAND );
		goto FAIL_RETURN;
	}
	// mmioDescendの逆。入力ファイルの'fmt 'チャンクから抜け出す
	if( MMSYSERR_NOERROR != mmioAscend( aSound->sndHmmio, &aChunkInfo, 0 ) ){
		MessageBox( NULL, "FAIL:mmioAscend", "ERROR", MB_OK|MB_ICONHAND );
		goto FAIL_RETURN;
	}

	// 正常終了時には、aSound.paWaveFormatExに指定されたRIFFファイルに入っていたPCM音声フォーマットが収められている
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
//　波形ファイル閉じる  //
//----------------------//
HRESULT	closeWaveFile(theSounds *aSound)
{
	if(aSound->sndHmmio == NULL)
		return E_FAIL;

	//サウンドを閉じる
	if(FAILED(mmioClose(aSound->sndHmmio, 0))){
		MessageBox( NULL, "FAIL:mmioClose", "ERROR", MB_OK|MB_ICONHAND );
		return( E_FAIL );
	}

	return S_OK;
}
//--------------------------------------//
//　波形ファイルの読み出し位置巻き戻し  //
//--------------------------------------//
HRESULT rewindWaveFile(theSounds *aSound)
{
	// 念のためのエラーチェック
	if( aSound->sndHmmio == NULL)
		return E_FAIL;
	// 波形ファイルの頭だし
	if(mmioSeek( aSound->sndHmmio, aSound->sndChunkRiff.dwDataOffset + sizeof(FOURCC) , SEEK_SET ) == -1){
		MessageBox( NULL, "FAIL:mmioSeek", "ERROR", MB_OK|MB_ICONHAND );
		return( E_FAIL );
	}
	// 入力ファイルのデータチャンクを探して、そのチャンクの情報をaSound.aChunkに収める
	aSound->sndChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if( MMSYSERR_NOERROR != mmioDescend( aSound->sndHmmio, &(aSound->sndChunk), &(aSound->sndChunkRiff), MMIO_FINDCHUNK ) ){
		MessageBox( NULL, "FAIL:mmioDescend", "ERROR", MB_OK|MB_ICONHAND );
		return( E_FAIL );
	}

	return S_OK;
}
//----------------//
//　音を再生する  //
//----------------//
HRESULT playASound( theSounds *aSound , DWORD aPriority ,DWORD aFlag ,BOOL aOverride)
{
	HRESULT	hr;     // 結果返し用
	BOOL aRestored;	// バッファが復旧された？
	DWORD	aFreeDSB = selectFreeBuffer( aSound , aOverride );

	if( aSound->sndDSSoundBuffer[aFreeDSB] == NULL ){
		MessageBox( NULL, "FAIL:SelectFreeBuffer", "ERROR", MB_OK|MB_ICONHAND );
		return E_FAIL;
	}
	// バッファが失われていないか確認し、失われている場合は復旧を試みる
	if(FAILED(hr = restoreDSBuffer( aSound->sndDSSoundBuffer[aFreeDSB] , &aRestored ))){
		MessageBox( NULL, "FAIL:RestoreDSBuffer", "ERROR", MB_OK|MB_ICONHAND );
		return E_FAIL;
	}
	// バッファが復旧された場合、データが失われている可能性があるので改めて読み込む
	if(aRestored){
		if(FAILED(hr = fillupSoundBuffer( aSound , aFreeDSB))){
			MessageBox( NULL, "FAIL:FillupSoundBuffer", "ERROR", MB_OK|MB_ICONHAND );
			return( E_FAIL );
		}
	}
	//                                               予約   優先度    ループ→DSBPLAY_LOOPING
	return( aSound->sndDSSoundBuffer[aFreeDSB]->Play( 0 , aPriority , aFlag ));
}
//------------------------------//
//　全てのバッファの音を止める  //
//------------------------------//
HRESULT StopASound( theSounds *aSound )
{
	HRESULT	hr = 0;

	if(aSound->sndDSSoundBuffer == NULL)
		return E_FAIL;
	//全てのバッファの音を止める;
	for(unsigned int i=0 ; i< aSound->sndNumOfBuffers; i++)
		hr |= aSound->sndDSSoundBuffer[i]->Stop();
	
	return(hr);
}
//-------------------------------//
//　全てのバッファの頭だしをする //
//-------------------------------//
HRESULT RewindASound( theSounds *aSound )
{
	HRESULT	hr = 0;

	if(aSound->sndDSSoundBuffer == NULL)
		return E_FAIL;
	//全てのバッファの頭だしをしないとおかしな事になる。
	for(unsigned int i=0; i< aSound->sndNumOfBuffers; i++ )
		hr |= aSound->sndDSSoundBuffer[i]->SetCurrentPosition(NULL);

	return(hr);
}
//--------------------------------//
//　使用中ではないバッファを探す  //
//--------------------------------//
DWORD selectFreeBuffer(theSounds *aSound , BOOL aOverride)
{
	int i;
	// バッファがNULLだったら帰る
	if(aSound->sndDSSoundBuffer[0] == NULL)
		return E_FAIL;

	// バッファの数だけ繰り返し
	for(i=0; (unsigned)i< aSound->sndNumOfBuffers; i++){
		if(aSound->sndDSSoundBuffer[i] != NULL){
			DWORD aStatus;
			// ステータスをチェックして再生中でないものを探す
			aSound->sndDSSoundBuffer[i]->GetStatus( &aStatus );
			if((aStatus & DSBSTATUS_PLAYING) == 0)
				break;
		}
	}
	// 未使用バッファがあったらi0の値はkNumOfBufferと異なるので、i0を返す
	if(i == aSound->sndNumOfBuffers){
		if(aOverride){ // 同じでオーバーライドフラグが立っていたらバッファの中からランダムで選んで返す
			i = rand() % (aSound->sndNumOfBuffers);
			//選んだバッファの再生を停止して巻き戻す
			aSound->sndDSSoundBuffer[i]->Stop();
			aSound->sndDSSoundBuffer[i]->SetCurrentPosition(0);
		}
		else
			i = -1;
	}

	return i;
}
//----------------//
//  MIDI読み込み  //
//----------------//
HRESULT loadSegmentFromMusicFile( char *aWaveFileName , theMusic *aMusic )
{
	HRESULT	hr;
	IUnknown* pConfig = NULL;	//ファイルの組み込みオーディオパスを取得するため
	CHAR strMusicPath[kSTR_LENGTH]; // パスのための文字列領域
	WCHAR wstrSearchPath[MAX_PATH+1], wstrWaveFileName[kSTR_LENGTH+1]; // DirectMusicはワイドキャラしか扱えない

	// 新しいセグメントを作成するために、古いセグメントを破棄する
	SAFE_RELEASE( aMusic->pMusSegment );
	// ローダー内の情報を整理しなおす
	if(g_pDMLoader)
		g_pDMLoader->CollectGarbage();
	// 現在のディレクトリを取得
	if( GetCurrentDirectory( MAX_PATH+1 ,strMusicPath ) == 0 )
		goto FAIL_RETURN;
	// ANSIキャラをUNICORDに変換する
	// CP_ACPはMultiByteToWideCharに与える文字列がANSI文字列であることを示す
	MultiByteToWideChar( CP_ACP, 0, strMusicPath, -1, wstrSearchPath, MAX_PATH );
	MultiByteToWideChar( CP_ACP, 0, aWaveFileName, -1, wstrWaveFileName, kSTR_LENGTH );

	// 末尾にNULL文字を追加して万が一のエラーを防ぐ
	wstrSearchPath[MAX_PATH] = '\0';
	wstrWaveFileName[kSTR_LENGTH] = '\0';
	// 検索用ディレクトリの設定
	g_pDMLoader->SetSearchDirectory( GUID_DirectMusicAllTypes, wstrSearchPath, FALSE );
	// 音楽ファイルからセグメントをロードする
	if( FAILED( hr = g_pDMLoader->LoadObjectFromFile(	CLSID_DirectMusicSegment,	IID_IDirectMusicSegment8,
														wstrWaveFileName,			(LPVOID*)&(aMusic->pMusSegment) ) ) ){
		// もしカレントディレクトリにファイルが無かったら、modelsフォルダを確かめる。
		// バックスラッシュ(\)が二つ重なっているのは、エスケープシーケンスが有効になっているため
		TCHAR aStr[MAX_PATH];
		lstrcpyn( aStr, strMusicPath, MAX_PATH );
		lstrcpyn( aStr + lstrlen(strMusicPath) , kMusicPath, MAX_PATH - kMusicPathLength );

		MultiByteToWideChar( CP_ACP, 0, aStr, -1, wstrSearchPath, MAX_PATH );

		// 検索用ディレクトリの設定
		g_pDMLoader->SetSearchDirectory( GUID_DirectMusicAllTypes, wstrSearchPath, FALSE );

		// カレントフォルダで見つからなかったら、musicフォルダを探す
		if( FAILED( hr = g_pDMLoader->LoadObjectFromFile(	CLSID_DirectMusicSegment,	IID_IDirectMusicSegment8,
															wstrWaveFileName,			(LPVOID*)&(aMusic->pMusSegment) ) ) ){
			char cautionString[kSTR_LENGTH];
			wsprintf( cautionString , "音楽ファイル『%s』は見つからなかったか、読み込み不能なフォーマットです。", aWaveFileName);
			MessageBox(NULL, cautionString, "読み込みエラー" , MB_OK);
			goto FAIL_RETURN;
		}
	}
	// セグメント自体にオーディオパスが含まれていた場合はそれを利用する
	if( SUCCEEDED( aMusic->pMusSegment->GetAudioPathConfig( &pConfig ) ) ){
		g_pDMPerformance->CreateAudioPath( pConfig, TRUE, &(aMusic->pMusAudioPath) );
		SAFE_RELEASE( pConfig );
	}
	else
		aMusic->pMusAudioPath = NULL;

	// もし、指定されたファイルがmidiファイルだった場合、DirectMusicにそれを伝える
	if( strstr( aWaveFileName, ".mid" ) != NULL || strstr( aWaveFileName, ".rmi" ) != NULL )
		// パラメータの設定
		if( FAILED( hr = aMusic->pMusSegment->SetParam( GUID_StandardMIDIFile, 0xFFFFFFFF, 0, 0, NULL ) ) )
			goto FAIL_RETURN;

	// シンセサイザーにセグメントの音源などをダウンロードする
	if( aMusic->pMusAudioPath ){
		if( SUCCEEDED(aMusic->pMusSegment->Download( aMusic->pMusAudioPath )) )
			aMusic->bDownLoaded = TRUE;
	}
	else if( SUCCEEDED(aMusic->pMusSegment->Download( g_pDMPerformance )) )
			aMusic->bDownLoaded = TRUE;

	return S_OK;

	// エラー時の出口
FAIL_RETURN:

	SAFE_RELEASE(g_pDMLoader); 
	SAFE_RELEASE(g_pDMPerformance); 

	return hr;
}
//--------------------//
//  セグメントの再生  //
//--------------------//
HRESULT playAMusic(theMusic *aMusic)
{
	// もしセグメントが無かったりダウンロードに失敗していたらエラー
	if(( aMusic->pMusSegment == NULL )||( !aMusic->bDownLoaded ))
		return E_FAIL;
	if( isPlayingAMusic( aMusic ) != S_OK )
		stopAMusic(aMusic);

	// このセグメントをずっと再生しつづける設定にする
	aMusic->pMusSegment->SetRepeats( DMUS_SEG_REPEAT_INFINITE );

	IDirectMusicAudioPath8*	paAudioPath; // オーディオパス
	
	if( aMusic->pMusAudioPath )
		paAudioPath = aMusic->pMusAudioPath;
	else
		paAudioPath = g_pDMAudioPath;

    // オーディオパスのセグメントを再生する
	g_pDMPerformance->PlaySegmentEx( aMusic->pMusSegment, 0, NULL, DMUS_SEGF_BEAT, 0, 0, NULL, paAudioPath );

	return S_OK;
}
//------------------------//
//　セグメント再生の停止  //
//------------------------//
HRESULT	stopAMusic( theMusic *aMusic )
{
	if( g_pDMPerformance == NULL )
		return( E_FAIL);
	// IsPlaying関数は、再生されていないときはS_FALSEを返すため明示的にチェックする
	if( isPlayingAMusic( aMusic ) != S_OK )
		g_pDMPerformance->Stop( NULL , NULL , 0 , 0);

	return(S_OK);
}
//------------------------------//
//　セグメントが再生中かどうか  //
//------------------------------//
HRESULT	isPlayingAMusic( theMusic *aMusic )
{
	if(( g_pDMPerformance == NULL )||( aMusic->pMusSegment == NULL ))
		return( E_FAIL);
	return(( g_pDMPerformance->IsPlaying( aMusic->pMusSegment , NULL) == S_OK ));
}
//--------------------------//
//　マスタボリュームの設定  //
//--------------------------//
HRESULT setAVolume( long aVolume )
{
	if( g_pDMPerformance == NULL )
		return( E_FAIL);
	// ボリュームの設定
	g_pDMPerformance->SetGlobalParam( GUID_PerfMasterVolume, (void*)&aVolume, sizeof(long) );

	return( S_OK );
}
//-------------------------//
//　DirectMusicの開放処理  //
//-------------------------//
void cleanUpDirectMusic(void)
{
	// ローダーにセグメントの開放を通知してからセグメントを開放する
	if( g_pDMLoader ){
		for(int i=0 ; i<kNUM_OF_BGM; i++ ){
			// 音楽を再生していたら停止する
			stopAMusic( &g_BGM[i] );
			// ローダーにセグメントの開放を通知する
			g_pDMLoader->ReleaseObjectByUnknown( g_BGM[i].pMusSegment );
			// セグメントの開放とアンロード
			if( g_BGM[i].bDownLoaded ){
				if( g_BGM[i].pMusAudioPath )
					g_BGM[i].pMusSegment->Unload( g_BGM[i].pMusAudioPath );
				else
					g_BGM[i].pMusSegment->Unload( g_pDMPerformance );
				g_BGM[i].bDownLoaded = FALSE;
			}
			SAFE_RELEASE( g_BGM[i].pMusSegment );
			// オーディオパスの開放
			SAFE_RELEASE( g_BGM[i].pMusAudioPath );
		}
	}

	SAFE_RELEASE( g_pDMLoader );		// ローダーの開放
	SAFE_RELEASE( g_pDMAudioPath );		// オーディオパスの開放

	// パフォーマンスの開放
	if( g_pDMPerformance ){
		g_pDMPerformance->CloseDown();
		SAFE_RELEASE( g_pDMPerformance );
	}

	// COMオブジェクトの後始末
	if( g_bComInit ){
		CoUninitialize();
		g_bComInit = FALSE;
	}
}
//---------------------//
//　DirectSoundの終了  //
//---------------------//
void cleanUpDirectSound(void)
{
	cleanUpTheSounds();
	SAFE_RELEASE( g_pDirectSound );	//DirectSoundオブジェクトの削除
}
//------------------------//
//  themusic構造体初期化  //
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
//　theSounds構造体開放  //
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
//　theSounds構造体の初期化  //
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
// 音源読み込み  //
//---------------//
void LoadMusicFile(void)
{
	// 効果音構造体の初期化
	initTheSounds();
	// 効果音の読み込み
	if(FAILED( setupSounds())){
		MessageBox( NULL, "効果音の読み込みに失敗しました。", "ERROR", MB_OK|MB_ICONHAND );
		cleanUpDirectSound(); // DirectSoundの後始末
		return;
	}
	// BGM構造体の初期化
	initTheMUSIC();
	for(int i=1; i<kNUM_OF_BGM; i++)
		loadSegmentFromMusicFile(MusicFile[i], &g_BGM[i]);
	setAVolume(MusicVol);
}