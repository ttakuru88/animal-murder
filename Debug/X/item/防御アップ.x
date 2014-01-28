xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 215;
 0.00278;0.19676;0.00058;,
 0.05278;0.16747;-0.04942;,
 0.00278;0.16747;-0.07013;,
 0.00278;0.19676;0.00058;,
 0.07349;0.16747;0.00058;,
 0.00278;0.19676;0.00058;,
 0.05278;0.16747;0.05058;,
 0.00278;0.19676;0.00058;,
 0.00278;0.16747;0.07129;,
 0.00278;0.19676;0.00058;,
 -0.04722;0.16747;0.05058;,
 0.00278;0.19676;0.00058;,
 -0.06793;0.16747;0.00058;,
 0.00278;0.19676;0.00058;,
 -0.04722;0.16747;-0.04942;,
 0.00278;0.19676;0.00058;,
 0.00278;0.16747;-0.07013;,
 0.07349;0.09676;-0.07013;,
 0.00278;0.09676;-0.09942;,
 0.10278;0.09676;0.00058;,
 0.07349;0.09676;0.07129;,
 0.00278;0.09676;0.10058;,
 -0.06793;0.09676;0.07129;,
 -0.09722;0.09676;0.00058;,
 -0.06793;0.09676;-0.07013;,
 0.00278;0.09676;-0.09942;,
 0.05278;0.02605;-0.04942;,
 0.00278;0.02605;-0.07013;,
 0.07349;0.02605;0.00058;,
 0.05278;0.02605;0.05058;,
 0.00278;0.02605;0.07129;,
 -0.04722;0.02605;0.05058;,
 -0.06793;0.02605;0.00058;,
 -0.04722;0.02605;-0.04942;,
 0.00278;0.02605;-0.07013;,
 0.00278;-0.00324;0.00058;,
 0.00278;-0.00324;0.00058;,
 0.00278;-0.00324;0.00058;,
 0.00278;-0.00324;0.00058;,
 0.00278;-0.00324;0.00058;,
 0.00278;-0.00324;0.00058;,
 0.00278;-0.00324;0.00058;,
 0.00278;-0.00324;0.00058;,
 0.00278;0.20242;-0.13410;,
 0.02358;0.19023;-0.15490;,
 0.00278;0.19023;-0.16352;,
 0.00278;0.20242;-0.13410;,
 0.03220;0.19023;-0.13410;,
 0.00278;0.20242;-0.13410;,
 0.02358;0.19023;-0.11330;,
 0.00278;0.20242;-0.13410;,
 0.00278;0.19023;-0.10469;,
 0.00278;0.20242;-0.13410;,
 -0.01802;0.19023;-0.11330;,
 0.00278;0.20242;-0.13410;,
 -0.02663;0.19023;-0.13410;,
 0.00278;0.20242;-0.13410;,
 -0.01802;0.19023;-0.15490;,
 0.00278;0.20242;-0.13410;,
 0.00278;0.19023;-0.16352;,
 0.03220;0.16082;-0.16352;,
 0.00278;0.16082;-0.17570;,
 0.04438;0.16082;-0.13410;,
 0.03220;0.16082;-0.10469;,
 0.00278;0.16082;-0.09250;,
 -0.02663;0.16082;-0.10469;,
 -0.03882;0.16082;-0.13410;,
 -0.02663;0.16082;-0.16352;,
 0.00278;0.16082;-0.17570;,
 0.02358;0.13140;-0.15490;,
 0.00278;0.13140;-0.16352;,
 0.03220;0.13140;-0.13410;,
 0.02358;0.13140;-0.11330;,
 0.00278;0.13140;-0.10469;,
 -0.01802;0.13140;-0.11330;,
 -0.02663;0.13140;-0.13410;,
 -0.01802;0.13140;-0.15490;,
 0.00278;0.13140;-0.16352;,
 0.00278;0.11922;-0.13410;,
 0.00278;0.11922;-0.13410;,
 0.00278;0.11922;-0.13410;,
 0.00278;0.11922;-0.13410;,
 0.00278;0.11922;-0.13410;,
 0.00278;0.11922;-0.13410;,
 0.00278;0.11922;-0.13410;,
 0.00278;0.11922;-0.13410;,
 0.00278;0.20242;0.13362;,
 0.02358;0.19023;0.11282;,
 0.00278;0.19023;0.10420;,
 0.00278;0.20242;0.13362;,
 0.03220;0.19023;0.13362;,
 0.00278;0.20242;0.13362;,
 0.02358;0.19023;0.15442;,
 0.00278;0.20242;0.13362;,
 0.00278;0.19023;0.16303;,
 0.00278;0.20242;0.13362;,
 -0.01802;0.19023;0.15442;,
 0.00278;0.20242;0.13362;,
 -0.02663;0.19023;0.13362;,
 0.00278;0.20242;0.13362;,
 -0.01802;0.19023;0.11282;,
 0.00278;0.20242;0.13362;,
 0.00278;0.19023;0.10420;,
 0.03220;0.16082;0.10420;,
 0.00278;0.16082;0.09202;,
 0.04438;0.16082;0.13362;,
 0.03220;0.16082;0.16303;,
 0.00278;0.16082;0.17522;,
 -0.02663;0.16082;0.16303;,
 -0.03882;0.16082;0.13362;,
 -0.02663;0.16082;0.10420;,
 0.00278;0.16082;0.09202;,
 0.02358;0.13140;0.11282;,
 0.00278;0.13140;0.10420;,
 0.03220;0.13140;0.13362;,
 0.02358;0.13140;0.15442;,
 0.00278;0.13140;0.16303;,
 -0.01802;0.13140;0.15442;,
 -0.02663;0.13140;0.13362;,
 -0.01802;0.13140;0.11282;,
 0.00278;0.13140;0.10420;,
 0.00278;0.11922;0.13362;,
 0.00278;0.11922;0.13362;,
 0.00278;0.11922;0.13362;,
 0.00278;0.11922;0.13362;,
 0.00278;0.11922;0.13362;,
 0.00278;0.11922;0.13362;,
 0.00278;0.11922;0.13362;,
 0.00278;0.11922;0.13362;,
 0.12596;0.20242;-0.00285;,
 0.14676;0.19023;-0.02365;,
 0.12596;0.19023;-0.03227;,
 0.12596;0.20242;-0.00285;,
 0.15537;0.19023;-0.00285;,
 0.12596;0.20242;-0.00285;,
 0.14676;0.19023;0.01795;,
 0.12596;0.20242;-0.00285;,
 0.12596;0.19023;0.02656;,
 0.12596;0.20242;-0.00285;,
 0.10516;0.19023;0.01795;,
 0.12596;0.20242;-0.00285;,
 0.09654;0.19023;-0.00285;,
 0.12596;0.20242;-0.00285;,
 0.10516;0.19023;-0.02365;,
 0.12596;0.20242;-0.00285;,
 0.12596;0.19023;-0.03227;,
 0.15537;0.16082;-0.03227;,
 0.12596;0.16082;-0.04445;,
 0.16756;0.16082;-0.00285;,
 0.15537;0.16082;0.02656;,
 0.12596;0.16082;0.03875;,
 0.09654;0.16082;0.02656;,
 0.08436;0.16082;-0.00285;,
 0.09654;0.16082;-0.03227;,
 0.12596;0.16082;-0.04445;,
 0.14676;0.13140;-0.02365;,
 0.12596;0.13140;-0.03227;,
 0.15537;0.13140;-0.00285;,
 0.14676;0.13140;0.01795;,
 0.12596;0.13140;0.02656;,
 0.10516;0.13140;0.01795;,
 0.09654;0.13140;-0.00285;,
 0.10516;0.13140;-0.02365;,
 0.12596;0.13140;-0.03227;,
 0.12596;0.11922;-0.00285;,
 0.12596;0.11922;-0.00285;,
 0.12596;0.11922;-0.00285;,
 0.12596;0.11922;-0.00285;,
 0.12596;0.11922;-0.00285;,
 0.12596;0.11922;-0.00285;,
 0.12596;0.11922;-0.00285;,
 0.12596;0.11922;-0.00285;,
 -0.11892;0.20242;-0.00285;,
 -0.09812;0.19023;-0.02365;,
 -0.11892;0.19023;-0.03227;,
 -0.11892;0.20242;-0.00285;,
 -0.08951;0.19023;-0.00285;,
 -0.11892;0.20242;-0.00285;,
 -0.09812;0.19023;0.01795;,
 -0.11892;0.20242;-0.00285;,
 -0.11892;0.19023;0.02656;,
 -0.11892;0.20242;-0.00285;,
 -0.13972;0.19023;0.01795;,
 -0.11892;0.20242;-0.00285;,
 -0.14834;0.19023;-0.00285;,
 -0.11892;0.20242;-0.00285;,
 -0.13972;0.19023;-0.02365;,
 -0.11892;0.20242;-0.00285;,
 -0.11892;0.19023;-0.03227;,
 -0.08951;0.16082;-0.03227;,
 -0.11892;0.16082;-0.04445;,
 -0.07732;0.16082;-0.00285;,
 -0.08951;0.16082;0.02656;,
 -0.11892;0.16082;0.03875;,
 -0.14834;0.16082;0.02656;,
 -0.16052;0.16082;-0.00285;,
 -0.14834;0.16082;-0.03227;,
 -0.11892;0.16082;-0.04445;,
 -0.09812;0.13140;-0.02365;,
 -0.11892;0.13140;-0.03227;,
 -0.08951;0.13140;-0.00285;,
 -0.09812;0.13140;0.01795;,
 -0.11892;0.13140;0.02656;,
 -0.13972;0.13140;0.01795;,
 -0.14834;0.13140;-0.00285;,
 -0.13972;0.13140;-0.02365;,
 -0.11892;0.13140;-0.03227;,
 -0.11892;0.11922;-0.00285;,
 -0.11892;0.11922;-0.00285;,
 -0.11892;0.11922;-0.00285;,
 -0.11892;0.11922;-0.00285;,
 -0.11892;0.11922;-0.00285;,
 -0.11892;0.11922;-0.00285;,
 -0.11892;0.11922;-0.00285;,
 -0.11892;0.11922;-0.00285;;
 
 160;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 3;27,26,35;,
 3;26,28,36;,
 3;28,29,37;,
 3;29,30,38;,
 3;30,31,39;,
 3;31,32,40;,
 3;32,33,41;,
 3;33,34,42;,
 3;43,44,45;,
 3;46,47,44;,
 3;48,49,47;,
 3;50,51,49;,
 3;52,53,51;,
 3;54,55,53;,
 3;56,57,55;,
 3;58,59,57;,
 4;45,44,60,61;,
 4;44,47,62,60;,
 4;47,49,63,62;,
 4;49,51,64,63;,
 4;51,53,65,64;,
 4;53,55,66,65;,
 4;55,57,67,66;,
 4;57,59,68,67;,
 4;61,60,69,70;,
 4;60,62,71,69;,
 4;62,63,72,71;,
 4;63,64,73,72;,
 4;64,65,74,73;,
 4;65,66,75,74;,
 4;66,67,76,75;,
 4;67,68,77,76;,
 3;70,69,78;,
 3;69,71,79;,
 3;71,72,80;,
 3;72,73,81;,
 3;73,74,82;,
 3;74,75,83;,
 3;75,76,84;,
 3;76,77,85;,
 3;86,87,88;,
 3;89,90,87;,
 3;91,92,90;,
 3;93,94,92;,
 3;95,96,94;,
 3;97,98,96;,
 3;99,100,98;,
 3;101,102,100;,
 4;88,87,103,104;,
 4;87,90,105,103;,
 4;90,92,106,105;,
 4;92,94,107,106;,
 4;94,96,108,107;,
 4;96,98,109,108;,
 4;98,100,110,109;,
 4;100,102,111,110;,
 4;104,103,112,113;,
 4;103,105,114,112;,
 4;105,106,115,114;,
 4;106,107,116,115;,
 4;107,108,117,116;,
 4;108,109,118,117;,
 4;109,110,119,118;,
 4;110,111,120,119;,
 3;113,112,121;,
 3;112,114,122;,
 3;114,115,123;,
 3;115,116,124;,
 3;116,117,125;,
 3;117,118,126;,
 3;118,119,127;,
 3;119,120,128;,
 3;129,130,131;,
 3;132,133,130;,
 3;134,135,133;,
 3;136,137,135;,
 3;138,139,137;,
 3;140,141,139;,
 3;142,143,141;,
 3;144,145,143;,
 4;131,130,146,147;,
 4;130,133,148,146;,
 4;133,135,149,148;,
 4;135,137,150,149;,
 4;137,139,151,150;,
 4;139,141,152,151;,
 4;141,143,153,152;,
 4;143,145,154,153;,
 4;147,146,155,156;,
 4;146,148,157,155;,
 4;148,149,158,157;,
 4;149,150,159,158;,
 4;150,151,160,159;,
 4;151,152,161,160;,
 4;152,153,162,161;,
 4;153,154,163,162;,
 3;156,155,164;,
 3;155,157,165;,
 3;157,158,166;,
 3;158,159,167;,
 3;159,160,168;,
 3;160,161,169;,
 3;161,162,170;,
 3;162,163,171;,
 3;172,173,174;,
 3;175,176,173;,
 3;177,178,176;,
 3;179,180,178;,
 3;181,182,180;,
 3;183,184,182;,
 3;185,186,184;,
 3;187,188,186;,
 4;174,173,189,190;,
 4;173,176,191,189;,
 4;176,178,192,191;,
 4;178,180,193,192;,
 4;180,182,194,193;,
 4;182,184,195,194;,
 4;184,186,196,195;,
 4;186,188,197,196;,
 4;190,189,198,199;,
 4;189,191,200,198;,
 4;191,192,201,200;,
 4;192,193,202,201;,
 4;193,194,203,202;,
 4;194,195,204,203;,
 4;195,196,205,204;,
 4;196,197,206,205;,
 3;199,198,207;,
 3;198,200,208;,
 3;200,201,209;,
 3;201,202,210;,
 3;202,203,211;,
 3;203,204,212;,
 3;204,205,213;,
 3;205,206,214;;
 
 MeshMaterialList {
  1;
  160;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  130;
  0.000000;1.000000;0.000000;,
  0.000000;0.715247;-0.698872;,
  0.494177;0.715247;-0.494177;,
  0.698872;0.715247;0.000000;,
  0.494177;0.715247;0.494177;,
  -0.000000;0.715247;0.698872;,
  -0.494177;0.715247;0.494177;,
  -0.698872;0.715247;0.000000;,
  -0.494177;0.715247;-0.494177;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000000;0.000000;1.000000;,
  -0.707107;-0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-0.715247;-0.698872;,
  0.494177;-0.715247;-0.494177;,
  0.698872;-0.715247;0.000000;,
  0.494177;-0.715247;0.494177;,
  -0.000000;-0.715247;0.698872;,
  -0.494177;-0.715247;0.494177;,
  -0.698872;-0.715247;0.000000;,
  -0.494177;-0.715247;-0.494177;,
  0.000000;-1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  0.000000;0.715248;-0.698871;,
  0.494177;0.715247;-0.494176;,
  0.698872;0.715247;0.000000;,
  0.494177;0.715247;0.494177;,
  0.000000;0.715247;0.698872;,
  -0.494177;0.715248;0.494176;,
  -0.698871;0.715247;0.000000;,
  -0.494177;0.715248;-0.494176;,
  0.000000;-0.000001;-1.000000;,
  0.707107;-0.000001;-0.707106;,
  1.000000;-0.000001;0.000000;,
  0.707107;-0.000001;0.707107;,
  0.000000;-0.000001;1.000000;,
  -0.707107;-0.000001;0.707107;,
  -1.000000;-0.000001;0.000000;,
  -0.707107;-0.000001;-0.707106;,
  0.000000;-0.715247;-0.698872;,
  0.494178;-0.715247;-0.494177;,
  0.698872;-0.715246;0.000000;,
  0.494177;-0.715246;0.494177;,
  0.000000;-0.715246;0.698872;,
  -0.494177;-0.715247;0.494177;,
  -0.698872;-0.715247;0.000000;,
  -0.494178;-0.715247;-0.494176;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.715247;-0.698872;,
  0.494177;0.715247;-0.494177;,
  0.698872;0.715247;-0.000000;,
  0.494177;0.715247;0.494176;,
  0.000000;0.715248;0.698871;,
  -0.494177;0.715248;0.494176;,
  -0.698871;0.715247;-0.000000;,
  -0.494177;0.715248;-0.494176;,
  0.000000;-0.000001;-1.000000;,
  0.707107;-0.000001;-0.707107;,
  1.000000;-0.000001;-0.000000;,
  0.707107;-0.000001;0.707106;,
  0.000000;-0.000001;1.000000;,
  -0.707107;-0.000001;0.707106;,
  -1.000000;-0.000001;-0.000000;,
  -0.707107;-0.000001;-0.707107;,
  0.000000;-0.715246;-0.698872;,
  0.494177;-0.715247;-0.494177;,
  0.698872;-0.715246;-0.000000;,
  0.494178;-0.715247;0.494177;,
  0.000000;-0.715247;0.698872;,
  -0.494178;-0.715247;0.494176;,
  -0.698872;-0.715247;-0.000000;,
  -0.494177;-0.715247;-0.494177;,
  -0.000000;-1.000000;-0.000000;,
  -0.000000;1.000000;0.000000;,
  -0.000000;0.715247;-0.698871;,
  0.494177;0.715247;-0.494177;,
  0.698871;0.715248;0.000000;,
  0.494176;0.715247;0.494177;,
  -0.000000;0.715247;0.698872;,
  -0.494177;0.715247;0.494177;,
  -0.698872;0.715247;0.000000;,
  -0.494177;0.715247;-0.494176;,
  -0.000000;-0.000001;-1.000000;,
  0.707107;-0.000001;-0.707107;,
  1.000000;-0.000001;0.000000;,
  0.707106;-0.000001;0.707107;,
  -0.000000;-0.000001;1.000000;,
  -0.707107;-0.000001;0.707107;,
  -1.000000;-0.000001;0.000000;,
  -0.707107;-0.000001;-0.707106;,
  -0.000000;-0.715247;-0.698872;,
  0.494177;-0.715247;-0.494177;,
  0.698872;-0.715247;0.000000;,
  0.494177;-0.715247;0.494178;,
  -0.000000;-0.715246;0.698872;,
  -0.494177;-0.715246;0.494177;,
  -0.698872;-0.715246;0.000000;,
  -0.494178;-0.715247;-0.494177;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  -0.000000;0.715247;-0.698871;,
  0.494177;0.715247;-0.494177;,
  0.698871;0.715248;0.000000;,
  0.494176;0.715247;0.494177;,
  -0.000000;0.715247;0.698872;,
  -0.494177;0.715247;0.494177;,
  -0.698872;0.715247;0.000000;,
  -0.494177;0.715247;-0.494176;,
  -0.000000;-0.000001;-1.000000;,
  0.707107;-0.000001;-0.707107;,
  1.000000;-0.000001;0.000000;,
  0.707106;-0.000001;0.707107;,
  -0.000000;-0.000001;1.000000;,
  -0.707107;-0.000001;0.707107;,
  -1.000000;-0.000001;0.000000;,
  -0.707107;-0.000001;-0.707106;,
  -0.000000;-0.715247;-0.698872;,
  0.494177;-0.715247;-0.494177;,
  0.698872;-0.715247;0.000000;,
  0.494177;-0.715247;0.494178;,
  -0.000000;-0.715246;0.698872;,
  -0.494177;-0.715246;0.494177;,
  -0.698872;-0.715246;0.000000;,
  -0.494178;-0.715247;-0.494177;,
  -0.000000;-1.000000;0.000000;;
  160;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  3;17,18,25;,
  3;18,19,25;,
  3;19,20,25;,
  3;20,21,25;,
  3;21,22,25;,
  3;22,23,25;,
  3;23,24,25;,
  3;24,17,25;,
  3;26,28,27;,
  3;26,29,28;,
  3;26,30,29;,
  3;26,31,30;,
  3;26,32,31;,
  3;26,33,32;,
  3;26,34,33;,
  3;26,27,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,27,35,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;42,35,43,50;,
  3;43,44,51;,
  3;44,45,51;,
  3;45,46,51;,
  3;46,47,51;,
  3;47,48,51;,
  3;48,49,51;,
  3;49,50,51;,
  3;50,43,51;,
  3;52,54,53;,
  3;52,55,54;,
  3;52,56,55;,
  3;52,57,56;,
  3;52,58,57;,
  3;52,59,58;,
  3;52,60,59;,
  3;52,53,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,57,65,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,53,61,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,65,73,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,61,69,76;,
  3;69,70,77;,
  3;70,71,77;,
  3;71,72,77;,
  3;72,73,77;,
  3;73,74,77;,
  3;74,75,77;,
  3;75,76,77;,
  3;76,69,77;,
  3;78,80,79;,
  3;78,81,80;,
  3;78,82,81;,
  3;78,83,82;,
  3;78,84,83;,
  3;78,85,84;,
  3;78,86,85;,
  3;78,79,86;,
  4;79,80,88,87;,
  4;80,81,89,88;,
  4;81,82,90,89;,
  4;82,83,91,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,79,87,94;,
  4;87,88,96,95;,
  4;88,89,97,96;,
  4;89,90,98,97;,
  4;90,91,99,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,87,95,102;,
  3;95,96,103;,
  3;96,97,103;,
  3;97,98,103;,
  3;98,99,103;,
  3;99,100,103;,
  3;100,101,103;,
  3;101,102,103;,
  3;102,95,103;,
  3;104,106,105;,
  3;104,107,106;,
  3;104,108,107;,
  3;104,109,108;,
  3;104,110,109;,
  3;104,111,110;,
  3;104,112,111;,
  3;104,105,112;,
  4;105,106,114,113;,
  4;106,107,115,114;,
  4;107,108,116,115;,
  4;108,109,117,116;,
  4;109,110,118,117;,
  4;110,111,119,118;,
  4;111,112,120,119;,
  4;112,105,113,120;,
  4;113,114,122,121;,
  4;114,115,123,122;,
  4;115,116,124,123;,
  4;116,117,125,124;,
  4;117,118,126,125;,
  4;118,119,127,126;,
  4;119,120,128,127;,
  4;120,113,121,128;,
  3;121,122,129;,
  3;122,123,129;,
  3;123,124,129;,
  3;124,125,129;,
  3;125,126,129;,
  3;126,127,129;,
  3;127,128,129;,
  3;128,121,129;;
 }
 MeshTextureCoords {
  215;
  0.062500;0.000000;
  0.125000;0.250000;
  0.000000;0.250000;
  0.187500;0.000000;
  0.250000;0.250000;
  0.312500;0.000000;
  0.375000;0.250000;
  0.437500;0.000000;
  0.500000;0.250000;
  0.562500;0.000000;
  0.625000;0.250000;
  0.687500;0.000000;
  0.750000;0.250000;
  0.812500;0.000000;
  0.875000;0.250000;
  0.937500;0.000000;
  1.000000;0.250000;
  0.125000;0.500000;
  0.000000;0.500000;
  0.250000;0.500000;
  0.375000;0.500000;
  0.500000;0.500000;
  0.625000;0.500000;
  0.750000;0.500000;
  0.875000;0.500000;
  1.000000;0.500000;
  0.125000;0.750000;
  0.000000;0.750000;
  0.250000;0.750000;
  0.375000;0.750000;
  0.500000;0.750000;
  0.625000;0.750000;
  0.750000;0.750000;
  0.875000;0.750000;
  1.000000;0.750000;
  0.062500;1.000000;
  0.187500;1.000000;
  0.312500;1.000000;
  0.437500;1.000000;
  0.562500;1.000000;
  0.687500;1.000000;
  0.812500;1.000000;
  0.937500;1.000000;
  0.062500;0.000000;
  0.125000;0.250000;
  0.000000;0.250000;
  0.187500;0.000000;
  0.250000;0.250000;
  0.312500;0.000000;
  0.375000;0.250000;
  0.437500;0.000000;
  0.500000;0.250000;
  0.562500;0.000000;
  0.625000;0.250000;
  0.687500;0.000000;
  0.750000;0.250000;
  0.812500;0.000000;
  0.875000;0.250000;
  0.937500;0.000000;
  1.000000;0.250000;
  0.125000;0.500000;
  0.000000;0.500000;
  0.250000;0.500000;
  0.375000;0.500000;
  0.500000;0.500000;
  0.625000;0.500000;
  0.750000;0.500000;
  0.875000;0.500000;
  1.000000;0.500000;
  0.125000;0.750000;
  0.000000;0.750000;
  0.250000;0.750000;
  0.375000;0.750000;
  0.500000;0.750000;
  0.625000;0.750000;
  0.750000;0.750000;
  0.875000;0.750000;
  1.000000;0.750000;
  0.062500;1.000000;
  0.187500;1.000000;
  0.312500;1.000000;
  0.437500;1.000000;
  0.562500;1.000000;
  0.687500;1.000000;
  0.812500;1.000000;
  0.937500;1.000000;
  0.062500;0.000000;
  0.125000;0.250000;
  0.000000;0.250000;
  0.187500;0.000000;
  0.250000;0.250000;
  0.312500;0.000000;
  0.375000;0.250000;
  0.437500;0.000000;
  0.500000;0.250000;
  0.562500;0.000000;
  0.625000;0.250000;
  0.687500;0.000000;
  0.750000;0.250000;
  0.812500;0.000000;
  0.875000;0.250000;
  0.937500;0.000000;
  1.000000;0.250000;
  0.125000;0.500000;
  0.000000;0.500000;
  0.250000;0.500000;
  0.375000;0.500000;
  0.500000;0.500000;
  0.625000;0.500000;
  0.750000;0.500000;
  0.875000;0.500000;
  1.000000;0.500000;
  0.125000;0.750000;
  0.000000;0.750000;
  0.250000;0.750000;
  0.375000;0.750000;
  0.500000;0.750000;
  0.625000;0.750000;
  0.750000;0.750000;
  0.875000;0.750000;
  1.000000;0.750000;
  0.062500;1.000000;
  0.187500;1.000000;
  0.312500;1.000000;
  0.437500;1.000000;
  0.562500;1.000000;
  0.687500;1.000000;
  0.812500;1.000000;
  0.937500;1.000000;
  0.062500;0.000000;
  0.125000;0.250000;
  0.000000;0.250000;
  0.187500;0.000000;
  0.250000;0.250000;
  0.312500;0.000000;
  0.375000;0.250000;
  0.437500;0.000000;
  0.500000;0.250000;
  0.562500;0.000000;
  0.625000;0.250000;
  0.687500;0.000000;
  0.750000;0.250000;
  0.812500;0.000000;
  0.875000;0.250000;
  0.937500;0.000000;
  1.000000;0.250000;
  0.125000;0.500000;
  0.000000;0.500000;
  0.250000;0.500000;
  0.375000;0.500000;
  0.500000;0.500000;
  0.625000;0.500000;
  0.750000;0.500000;
  0.875000;0.500000;
  1.000000;0.500000;
  0.125000;0.750000;
  0.000000;0.750000;
  0.250000;0.750000;
  0.375000;0.750000;
  0.500000;0.750000;
  0.625000;0.750000;
  0.750000;0.750000;
  0.875000;0.750000;
  1.000000;0.750000;
  0.062500;1.000000;
  0.187500;1.000000;
  0.312500;1.000000;
  0.437500;1.000000;
  0.562500;1.000000;
  0.687500;1.000000;
  0.812500;1.000000;
  0.937500;1.000000;
  0.062500;0.000000;
  0.125000;0.250000;
  0.000000;0.250000;
  0.187500;0.000000;
  0.250000;0.250000;
  0.312500;0.000000;
  0.375000;0.250000;
  0.437500;0.000000;
  0.500000;0.250000;
  0.562500;0.000000;
  0.625000;0.250000;
  0.687500;0.000000;
  0.750000;0.250000;
  0.812500;0.000000;
  0.875000;0.250000;
  0.937500;0.000000;
  1.000000;0.250000;
  0.125000;0.500000;
  0.000000;0.500000;
  0.250000;0.500000;
  0.375000;0.500000;
  0.500000;0.500000;
  0.625000;0.500000;
  0.750000;0.500000;
  0.875000;0.500000;
  1.000000;0.500000;
  0.125000;0.750000;
  0.000000;0.750000;
  0.250000;0.750000;
  0.375000;0.750000;
  0.500000;0.750000;
  0.625000;0.750000;
  0.750000;0.750000;
  0.875000;0.750000;
  1.000000;0.750000;
  0.062500;1.000000;
  0.187500;1.000000;
  0.312500;1.000000;
  0.437500;1.000000;
  0.562500;1.000000;
  0.687500;1.000000;
  0.812500;1.000000;
  0.937500;1.000000;;
 }
}
