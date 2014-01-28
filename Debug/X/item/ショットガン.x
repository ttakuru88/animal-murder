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
 324;
 -0.01595;0.07283;-0.05552;,
 0.00000;0.08003;-0.05552;,
 0.00000;0.02740;-0.05552;,
 -0.01595;0.03137;-0.05552;,
 0.01595;0.07283;-0.05552;,
 0.01595;0.03137;-0.05552;,
 -0.01595;0.03137;0.02088;,
 0.00000;0.02740;0.02088;,
 0.00000;0.06097;0.02088;,
 -0.01595;0.06224;0.02088;,
 0.01595;0.03137;0.02088;,
 0.01595;0.06224;0.02088;,
 0.00000;0.08003;-0.01732;,
 0.01595;0.07283;-0.01732;,
 0.01595;0.07283;-0.05552;,
 0.00000;0.08003;-0.05552;,
 -0.01595;0.07283;-0.05552;,
 -0.01595;0.07283;-0.01732;,
 0.01595;0.07283;-0.01732;,
 0.01595;0.03137;-0.01732;,
 0.01595;0.07283;-0.05552;,
 -0.01595;0.07283;-0.01732;,
 -0.01595;0.07283;-0.05552;,
 -0.01595;0.03137;-0.01732;,
 0.00000;0.02740;-0.01732;,
 0.00000;0.02740;-0.05552;,
 0.01595;0.03137;-0.05552;,
 -0.01595;0.03137;-0.05552;,
 0.00000;0.07686;0.00178;,
 0.00000;0.06097;0.02088;,
 0.01595;0.06224;0.02088;,
 0.01595;0.07283;0.00178;,
 -0.01595;0.07283;0.00178;,
 -0.01595;0.06224;0.02088;,
 0.01595;0.07283;0.00178;,
 0.01595;0.06224;0.02088;,
 0.01595;0.03137;0.00178;,
 -0.01595;0.07283;0.00178;,
 -0.01595;0.03137;0.00178;,
 -0.01595;0.06224;0.02088;,
 0.01595;0.03137;0.00178;,
 0.01595;0.03137;0.02088;,
 0.00000;0.02740;0.02088;,
 0.00000;0.02740;0.00178;,
 -0.01595;0.03137;0.00178;,
 -0.01595;0.03137;0.02088;,
 0.00000;0.05130;-0.18343;,
 0.00870;0.05506;-0.18343;,
 0.00870;0.05506;-0.05512;,
 0.00000;0.05130;-0.05512;,
 0.01230;0.06416;-0.18343;,
 0.01230;0.06416;-0.05512;,
 0.00870;0.07326;-0.18343;,
 0.00870;0.07326;-0.05512;,
 0.00000;0.07703;-0.18343;,
 0.00000;0.07703;-0.05512;,
 -0.00870;0.07326;-0.18343;,
 -0.00870;0.07326;-0.05512;,
 -0.01230;0.06416;-0.18343;,
 -0.01230;0.06416;-0.05512;,
 -0.00870;0.05506;-0.18343;,
 -0.00870;0.05506;-0.05512;,
 0.00000;0.05130;-0.18343;,
 0.00000;0.05130;-0.05512;,
 0.00000;0.06416;-0.18343;,
 0.00000;0.06416;-0.18343;,
 0.00000;0.06416;-0.18343;,
 0.00000;0.06416;-0.18343;,
 0.00000;0.06416;-0.18343;,
 0.00000;0.06416;-0.18343;,
 0.00000;0.06416;-0.18343;,
 0.00000;0.06416;-0.18343;,
 0.00000;0.06416;-0.05512;,
 0.00000;0.06416;-0.05512;,
 0.00000;0.06416;-0.05512;,
 0.00000;0.06416;-0.05512;,
 0.00000;0.06416;-0.05512;,
 0.00000;0.06416;-0.05512;,
 0.00000;0.06416;-0.05512;,
 0.00000;0.06416;-0.05512;,
 0.00000;0.01745;-0.11868;,
 0.01446;0.02371;-0.11868;,
 0.01446;0.02371;-0.07990;,
 0.00000;0.01745;-0.07990;,
 0.02045;0.03883;-0.11868;,
 0.02045;0.03883;-0.07990;,
 0.01446;0.05395;-0.11868;,
 0.01446;0.05395;-0.07990;,
 0.00000;0.06022;-0.11868;,
 0.00000;0.06022;-0.07990;,
 -0.01446;0.05395;-0.11868;,
 -0.01446;0.05395;-0.07990;,
 -0.02045;0.03883;-0.11868;,
 -0.02045;0.03883;-0.07990;,
 -0.01446;0.02371;-0.11868;,
 -0.01446;0.02371;-0.07990;,
 0.00000;0.01745;-0.11868;,
 0.00000;0.01745;-0.07990;,
 0.00000;0.03883;-0.11868;,
 0.00000;0.03883;-0.11868;,
 0.00000;0.03883;-0.11868;,
 0.00000;0.03883;-0.11868;,
 0.00000;0.03883;-0.11868;,
 0.00000;0.03883;-0.11868;,
 0.00000;0.03883;-0.11868;,
 0.00000;0.03883;-0.11868;,
 0.00000;0.03883;-0.07990;,
 0.00000;0.03883;-0.07990;,
 0.00000;0.03883;-0.07990;,
 0.00000;0.03883;-0.07990;,
 0.00000;0.03883;-0.07990;,
 0.00000;0.03883;-0.07990;,
 0.00000;0.03883;-0.07990;,
 0.00000;0.03883;-0.07990;,
 0.00000;0.03883;-0.15021;,
 0.00511;0.03348;-0.15021;,
 0.00000;0.03127;-0.15021;,
 0.00000;0.03883;-0.15021;,
 0.00723;0.03883;-0.15021;,
 0.00000;0.03883;-0.15021;,
 0.00511;0.04418;-0.15021;,
 0.00000;0.03883;-0.15021;,
 0.00000;0.04639;-0.15021;,
 0.00000;0.03883;-0.15021;,
 -0.00511;0.04418;-0.15021;,
 0.00000;0.03883;-0.15021;,
 -0.00723;0.03883;-0.15021;,
 0.00000;0.03883;-0.15021;,
 -0.00511;0.03348;-0.15021;,
 0.00000;0.03883;-0.15021;,
 0.00000;0.03127;-0.15021;,
 0.00000;0.03883;-0.05360;,
 0.00000;0.03127;-0.05360;,
 0.00511;0.03348;-0.05360;,
 0.00000;0.03883;-0.05360;,
 0.00723;0.03883;-0.05360;,
 0.00000;0.03883;-0.05360;,
 0.00511;0.04418;-0.05360;,
 0.00000;0.03883;-0.05360;,
 0.00000;0.04639;-0.05360;,
 0.00000;0.03883;-0.05360;,
 -0.00511;0.04418;-0.05360;,
 0.00000;0.03883;-0.05360;,
 -0.00723;0.03883;-0.05360;,
 0.00000;0.03883;-0.05360;,
 -0.00511;0.03348;-0.05360;,
 0.00000;0.03883;-0.05360;,
 0.00000;0.03127;-0.05360;,
 0.00000;0.04639;-0.12606;,
 0.00511;0.04418;-0.12606;,
 -0.00511;0.04418;-0.12606;,
 0.00723;0.03883;-0.12606;,
 -0.00723;0.03883;-0.12606;,
 0.00511;0.03348;-0.12606;,
 -0.00511;0.03348;-0.12606;,
 0.00000;0.03127;-0.12606;,
 0.00000;0.03127;-0.12606;,
 0.00949;0.04875;-0.11946;,
 0.00000;0.05286;-0.11946;,
 0.00000;0.04639;-0.12002;,
 0.00511;0.04418;-0.12002;,
 0.00000;0.05286;-0.12662;,
 0.00949;0.04875;-0.12662;,
 -0.00949;0.04875;-0.12662;,
 -0.00949;0.04875;-0.11946;,
 -0.00511;0.04418;-0.12002;,
 0.01342;0.03883;-0.11946;,
 0.00723;0.03883;-0.12002;,
 0.01342;0.03883;-0.12662;,
 -0.01342;0.03883;-0.12662;,
 -0.01342;0.03883;-0.11946;,
 -0.00723;0.03883;-0.12002;,
 0.00949;0.02891;-0.11946;,
 0.00511;0.03348;-0.12002;,
 0.00949;0.02891;-0.12662;,
 -0.00949;0.02891;-0.12662;,
 -0.00949;0.02891;-0.11946;,
 -0.00511;0.03348;-0.12002;,
 0.00000;0.02480;-0.11946;,
 0.00000;0.03127;-0.12002;,
 0.00000;0.02480;-0.12662;,
 0.00000;0.02480;-0.12662;,
 0.00000;0.02480;-0.11946;,
 0.00000;0.03127;-0.12002;,
 0.01670;0.05163;0.06447;,
 0.01854;0.04528;0.10606;,
 0.01854;-0.01530;0.10606;,
 0.01670;0.00260;0.05917;,
 0.01670;0.03008;0.02046;,
 0.01581;0.06219;0.02089;,
 -0.01670;0.05163;0.06447;,
 -0.01581;0.06219;0.02089;,
 -0.01670;0.03008;0.02046;,
 -0.01670;0.00260;0.05917;,
 -0.01854;-0.01530;0.10606;,
 -0.01854;0.04528;0.10606;,
 0.00000;0.05163;0.06447;,
 -0.01670;0.05163;0.06447;,
 -0.01854;0.04528;0.10606;,
 0.00000;0.04528;0.10606;,
 0.01854;0.04528;0.10606;,
 0.01670;0.05163;0.06447;,
 0.01581;0.06219;0.02089;,
 0.00000;0.06219;0.02089;,
 -0.01581;0.06219;0.02089;,
 0.00000;0.04528;0.10606;,
 -0.01854;0.04528;0.10606;,
 0.00000;-0.01530;0.10606;,
 0.01854;0.04528;0.10606;,
 0.00000;0.06219;0.02089;,
 0.01581;0.06219;0.02089;,
 0.00000;0.03008;0.02046;,
 -0.01581;0.06219;0.02089;,
 0.00000;-0.01530;0.10606;,
 -0.01854;-0.01530;0.10606;,
 0.00000;0.00260;0.05917;,
 0.01854;-0.01530;0.10606;,
 0.00000;0.03008;0.02046;,
 0.01670;0.03008;0.02046;,
 -0.01670;0.03008;0.02046;,
 -0.00665;0.02756;0.01110;,
 0.00665;0.02756;0.01110;,
 0.00665;0.01701;0.01042;,
 -0.00665;0.01701;0.01042;,
 0.00665;0.00841;0.00687;,
 -0.00665;0.00841;0.00687;,
 0.00665;0.00568;0.00059;,
 -0.00665;0.00568;0.00059;,
 0.00665;0.00568;-0.00696;,
 -0.00665;0.00568;-0.00696;,
 0.00665;0.00824;-0.01270;,
 -0.00665;0.00824;-0.01270;,
 0.00665;0.01680;-0.01630;,
 -0.00665;0.01680;-0.01630;,
 0.00665;0.02736;-0.01642;,
 -0.00665;0.02736;-0.01642;,
 -0.00665;0.02736;-0.01642;,
 0.00665;0.02736;-0.01642;,
 0.00665;0.02736;-0.01894;,
 -0.00665;0.02736;-0.01894;,
 -0.00665;0.02736;-0.01894;,
 0.00665;0.02736;-0.01894;,
 0.00665;0.01423;-0.01837;,
 -0.00665;0.01423;-0.01837;,
 0.00665;0.00467;-0.01421;,
 -0.00665;0.00467;-0.01421;,
 0.00665;0.00120;-0.00696;,
 -0.00665;0.00120;-0.00696;,
 0.00665;0.00120;0.00059;,
 -0.00665;0.00120;0.00059;,
 0.00665;0.00450;0.00809;,
 -0.00665;0.00450;0.00809;,
 0.00665;0.01402;0.01230;,
 -0.00665;0.01402;0.01230;,
 0.00665;0.02763;0.01362;,
 -0.00665;0.02763;0.01362;,
 -0.00665;0.02763;0.01362;,
 0.00665;0.02763;0.01362;,
 0.00665;0.02756;0.01110;,
 -0.00665;0.02756;0.01110;,
 0.00665;0.02756;0.01110;,
 0.00665;0.01402;0.01230;,
 0.00665;0.01701;0.01042;,
 0.00665;0.00450;0.00809;,
 0.00665;0.00841;0.00687;,
 0.00665;0.00120;0.00059;,
 0.00665;0.00568;0.00059;,
 0.00665;0.00120;-0.00696;,
 0.00665;0.00568;-0.00696;,
 0.00665;0.00467;-0.01421;,
 0.00665;0.00824;-0.01270;,
 0.00665;0.01423;-0.01837;,
 0.00665;0.01680;-0.01630;,
 0.00665;0.02736;-0.01642;,
 -0.00665;0.02756;0.01110;,
 -0.00665;0.01701;0.01042;,
 -0.00665;0.01402;0.01230;,
 -0.00665;0.00841;0.00687;,
 -0.00665;0.00450;0.00809;,
 -0.00665;0.00568;0.00059;,
 -0.00665;0.00120;0.00059;,
 -0.00665;0.00568;-0.00696;,
 -0.00665;0.00120;-0.00696;,
 -0.00665;0.00824;-0.01270;,
 -0.00665;0.00467;-0.01421;,
 -0.00665;0.01680;-0.01630;,
 -0.00665;0.01423;-0.01837;,
 -0.00665;0.02736;-0.01642;,
 -0.00214;0.02740;-0.00194;,
 0.00214;0.02740;-0.00194;,
 0.00214;0.02740;-0.00541;,
 -0.00214;0.02740;-0.00541;,
 -0.00214;0.01763;-0.00541;,
 0.00214;0.01763;-0.00541;,
 0.00214;0.01274;-0.00656;,
 -0.00214;0.01274;-0.00656;,
 0.00214;0.00697;-0.00877;,
 -0.00214;0.00697;-0.00877;,
 -0.00214;0.00697;-0.00877;,
 0.00214;0.00697;-0.00877;,
 0.00214;0.00874;-0.00562;,
 -0.00214;0.00874;-0.00562;,
 -0.00214;0.00874;-0.00562;,
 0.00214;0.00874;-0.00562;,
 0.00214;0.01274;-0.00308;,
 -0.00214;0.01274;-0.00308;,
 0.00214;0.01763;-0.00194;,
 -0.00214;0.01763;-0.00194;,
 0.00214;0.01763;-0.00194;,
 0.00214;0.01274;-0.00308;,
 0.00214;0.01274;-0.00656;,
 0.00214;0.01763;-0.00541;,
 -0.00214;0.01274;-0.00308;,
 -0.00214;0.01274;-0.00656;,
 -0.00214;0.01763;-0.00194;,
 -0.00214;0.01763;-0.00541;,
 -0.00214;0.02740;-0.00541;,
 0.00214;0.02740;-0.00541;,
 0.00214;0.02740;-0.00194;,
 -0.00214;0.02740;-0.00194;,
 0.00214;0.02740;-0.00541;,
 0.00214;0.02740;-0.00194;,
 -0.00214;0.02740;-0.00194;,
 -0.00214;0.02740;-0.00541;;
 
 186;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;7,10,11,8;,
 4;12,13,14,15;,
 4;12,15,16,17;,
 4;18,19,5,20;,
 4;21,22,3,23;,
 4;19,24,25,26;,
 4;23,27,25,24;,
 4;28,29,30,31;,
 4;28,31,13,12;,
 4;28,12,17,32;,
 4;28,32,33,29;,
 4;34,35,10,36;,
 4;34,36,19,18;,
 4;37,21,23,38;,
 4;37,38,6,39;,
 4;40,41,42,43;,
 4;40,43,24,19;,
 4;44,23,24,43;,
 4;44,43,42,45;,
 4;46,47,48,49;,
 4;47,50,51,48;,
 4;50,52,53,51;,
 4;52,54,55,53;,
 4;54,56,57,55;,
 4;56,58,59,57;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 3;64,47,46;,
 3;65,50,47;,
 3;66,52,50;,
 3;67,54,52;,
 3;68,56,54;,
 3;69,58,56;,
 3;70,60,58;,
 3;71,62,60;,
 3;72,49,48;,
 3;73,48,51;,
 3;74,51,53;,
 3;75,53,55;,
 3;76,55,57;,
 3;77,57,59;,
 3;78,59,61;,
 3;79,61,63;,
 4;80,81,82,83;,
 4;81,84,85,82;,
 4;84,86,87,85;,
 4;86,88,89,87;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 3;98,81,80;,
 3;99,84,81;,
 3;100,86,84;,
 3;101,88,86;,
 3;102,90,88;,
 3;103,92,90;,
 3;104,94,92;,
 3;105,96,94;,
 3;106,83,82;,
 3;107,82,85;,
 3;108,85,87;,
 3;109,87,89;,
 3;110,89,91;,
 3;111,91,93;,
 3;112,93,95;,
 3;113,95,97;,
 3;114,115,116;,
 3;117,118,115;,
 3;119,120,118;,
 3;121,122,120;,
 3;123,124,122;,
 3;125,126,124;,
 3;127,128,126;,
 3;129,130,128;,
 3;131,132,133;,
 3;134,133,135;,
 3;136,135,137;,
 3;138,137,139;,
 3;140,139,141;,
 3;142,141,143;,
 3;144,143,145;,
 3;146,145,147;,
 4;148,149,120,122;,
 4;148,122,124,150;,
 4;149,151,118,120;,
 4;150,124,126,152;,
 4;151,153,115,118;,
 4;152,126,128,154;,
 4;153,155,116,115;,
 4;154,128,130,156;,
 4;157,158,159,160;,
 4;161,162,149,148;,
 4;158,157,162,161;,
 4;163,161,148,150;,
 4;158,164,165,159;,
 4;158,161,163,164;,
 4;166,157,160,167;,
 4;162,168,151,149;,
 4;157,166,168,162;,
 4;169,163,150,152;,
 4;164,170,171,165;,
 4;164,163,169,170;,
 4;172,166,167,173;,
 4;168,174,153,151;,
 4;166,172,174,168;,
 4;175,169,152,154;,
 4;170,176,177,171;,
 4;170,169,175,176;,
 4;178,172,173,179;,
 4;174,180,155,153;,
 4;172,178,180,174;,
 4;181,175,154,156;,
 4;176,182,183,177;,
 4;176,175,181,182;,
 4;160,159,139,137;,
 4;159,165,141,139;,
 4;167,160,137,135;,
 4;165,171,143,141;,
 4;173,167,135,133;,
 4;171,177,145,143;,
 4;179,173,133,132;,
 4;177,183,147,145;,
 4;184,185,186,187;,
 4;184,187,188,189;,
 4;190,191,192,193;,
 4;190,193,194,195;,
 4;196,197,198,199;,
 4;196,199,200,201;,
 4;196,201,202,203;,
 4;196,203,204,197;,
 4;205,206,194,207;,
 4;205,207,186,208;,
 4;209,210,188,211;,
 4;209,211,192,212;,
 4;213,214,193,215;,
 4;213,215,187,216;,
 4;217,218,187,215;,
 4;217,215,193,219;,
 4;220,221,222,223;,
 4;223,222,224,225;,
 4;225,224,226,227;,
 4;227,226,228,229;,
 4;229,228,230,231;,
 4;231,230,232,233;,
 4;233,232,234,235;,
 4;236,237,238,239;,
 4;240,241,242,243;,
 4;243,242,244,245;,
 4;245,244,246,247;,
 4;247,246,248,249;,
 4;249,248,250,251;,
 4;251,250,252,253;,
 4;253,252,254,255;,
 4;256,257,258,259;,
 4;260,257,261,262;,
 4;262,261,263,264;,
 4;264,263,265,266;,
 4;266,265,267,268;,
 4;268,267,269,270;,
 4;270,269,271,272;,
 4;272,271,238,273;,
 4;256,274,275,276;,
 4;276,275,277,278;,
 4;278,277,279,280;,
 4;280,279,281,282;,
 4;282,281,283,284;,
 4;284,283,285,286;,
 4;286,285,287,239;,
 4;288,289,290,291;,
 4;292,293,294,295;,
 4;295,294,296,297;,
 4;298,299,300,301;,
 4;302,303,304,305;,
 4;305,304,306,307;,
 4;308,309,310,311;,
 4;309,303,296,310;,
 4;302,312,313,297;,
 4;312,314,315,313;,
 4;316,317,293,292;,
 4;307,306,318,319;,
 4;320,321,308,311;,
 4;315,314,322,323;;
 
 MeshMaterialList {
  2;
  186;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.564800;0.426400;0.156800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.200800;0.200800;0.200800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  119;
  -0.034652;0.466126;0.884039;,
  0.000000;0.466406;0.884571;,
  0.034652;0.466126;0.884039;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.999172;0.040689;,
  0.370474;0.928074;0.037794;,
  -0.370474;0.928074;0.037794;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.940407;0.340052;,
  0.203025;0.920821;0.332970;,
  -0.203025;0.920821;0.332970;,
  0.718240;-0.695796;-0.000000;,
  1.000000;-0.000001;-0.000000;,
  0.718240;0.695795;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.718240;0.695795;0.000000;,
  -1.000000;-0.000001;-0.000000;,
  -0.718240;-0.695796;-0.000000;,
  0.000000;-0.000000;1.000000;,
  0.718240;-0.695795;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.718240;0.695796;0.000000;,
  -0.718240;0.695796;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.718240;-0.695795;0.000000;,
  0.000000;-0.000007;-1.000000;,
  0.000000;-0.000009;-1.000000;,
  -0.000003;-0.000015;-1.000000;,
  0.000000;-0.000012;-1.000000;,
  0.000003;-0.000015;-1.000000;,
  0.718241;0.695794;0.000000;,
  -0.718241;0.695794;0.000000;,
  1.000000;-0.000003;-0.000000;,
  -1.000000;-0.000003;0.000000;,
  0.718239;-0.695796;-0.000000;,
  -0.718239;-0.695796;0.000000;,
  0.000000;-0.085921;0.996302;,
  -0.063530;-0.060748;0.996129;,
  0.063530;-0.060748;0.996129;,
  -0.089834;0.000000;0.995957;,
  0.089834;0.000000;0.995957;,
  -0.063529;0.060748;0.996129;,
  0.063529;0.060748;0.996129;,
  0.000000;0.085921;0.996302;,
  0.000000;-0.085921;-0.996302;,
  -0.063530;-0.060748;-0.996129;,
  0.063530;-0.060748;-0.996129;,
  -0.089834;0.000000;-0.995957;,
  0.089834;0.000000;-0.995957;,
  -0.063529;0.060748;-0.996129;,
  0.063529;0.060748;-0.996129;,
  0.000000;0.085921;-0.996302;,
  -0.999138;0.002357;-0.041438;,
  0.999138;0.002357;-0.041438;,
  -0.999879;0.013972;-0.006838;,
  0.999879;0.013972;-0.006838;,
  0.999675;0.008166;-0.024142;,
  -0.999675;0.008166;-0.024142;,
  0.000000;0.981113;0.193435;,
  0.000000;0.988538;0.150971;,
  0.000000;0.971865;0.235539;,
  0.000000;-0.452804;-0.891610;,
  0.000000;-0.881851;-0.471528;,
  0.000000;0.064059;-0.997946;,
  0.000000;0.226058;-0.974114;,
  0.000000;0.700228;-0.713919;,
  0.000000;0.978927;-0.204211;,
  0.000000;0.977939;0.208892;,
  0.000000;0.699293;0.714835;,
  0.000000;0.203599;0.979054;,
  0.000000;0.011162;0.999938;,
  0.000000;-0.224827;-0.974399;,
  0.000000;-0.694182;-0.719800;,
  0.000000;-0.975232;-0.221185;,
  0.000000;-0.978609;0.205730;,
  0.000000;-0.707685;0.706528;,
  0.000000;-0.253706;0.967282;,
  0.000000;-0.096809;0.995303;,
  0.000000;0.114859;-0.993382;,
  0.000000;0.293481;-0.955965;,
  0.000000;0.357422;-0.933943;,
  0.000000;-0.725163;0.688577;,
  0.000000;-0.387213;0.921990;,
  0.000000;-0.114858;0.993382;,
  0.411630;0.911351;0.000000;,
  -0.411630;0.911351;0.000000;,
  0.241698;-0.970352;-0.000000;,
  0.241698;-0.970352;-0.000000;,
  -0.241698;-0.970352;0.000000;,
  -0.241698;-0.970352;0.000000;,
  0.241698;-0.970352;-0.000000;,
  -0.241698;-0.970352;0.000000;,
  0.000000;-0.000005;1.000000;,
  0.000001;-0.000006;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000001;0.000006;1.000000;,
  0.000000;0.000005;1.000000;,
  -0.000001;0.000006;1.000000;,
  -0.000001;-0.000006;1.000000;,
  0.718242;0.695793;0.000000;,
  -0.718242;0.695793;0.000000;,
  1.000000;-0.000002;-0.000000;,
  -1.000000;-0.000002;0.000000;,
  0.718241;-0.695794;-0.000000;,
  -0.718241;-0.695794;0.000000;,
  1.000000;-0.000003;-0.000000;,
  -1.000000;-0.000003;0.000000;,
  0.000000;0.981113;0.193435;,
  0.000000;0.013628;-0.999907;,
  0.000000;-0.452804;-0.891610;,
  0.000000;-0.934233;-0.356664;,
  0.000000;-0.934233;-0.356664;,
  0.000000;-0.881851;-0.471528;,
  0.000000;-0.043690;-0.999045;,
  0.000000;0.999521;-0.030955;,
  0.000000;-0.871156;0.491006;;
  186;
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,1,0;,
  4;4,4,2,1;,
  4;5,6,87,17;,
  4;5,17,88,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;89,10,10,90;,
  4;91,92,10,10;,
  4;11,1,2,12;,
  4;11,12,6,5;,
  4;11,5,7,13;,
  4;11,13,0,1;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;93,93,10,10;,
  4;93,10,10,89;,
  4;94,91,10,10;,
  4;94,10,10,94;,
  4;10,14,14,10;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,10,10,20;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;21,95,96;,
  3;21,96,97;,
  3;21,97,98;,
  3;21,98,99;,
  3;21,99,100;,
  3;21,100,97;,
  3;21,97,101;,
  3;21,101,95;,
  4;10,22,22,10;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,17,17,24;,
  4;17,25,25,17;,
  4;25,26,26,25;,
  4;26,27,27,26;,
  4;27,10,10,27;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;28,3,3;,
  3;28,29,3;,
  3;28,30,29;,
  3;28,31,30;,
  3;28,32,31;,
  3;28,29,32;,
  3;28,3,29;,
  3;28,3,3;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  4;17,33,33,17;,
  4;17,17,34,34;,
  4;33,35,35,33;,
  4;34,34,36,36;,
  4;35,37,37,35;,
  4;36,36,38,38;,
  4;37,10,10,37;,
  4;38,38,10,10;,
  4;40,39,39,40;,
  4;47,48,48,47;,
  4;17,102,102,17;,
  4;49,47,47,49;,
  4;39,41,41,39;,
  4;17,17,103,103;,
  4;42,40,40,42;,
  4;48,50,50,48;,
  4;102,104,104,102;,
  4;51,49,49,51;,
  4;41,43,43,41;,
  4;103,103,105,105;,
  4;44,42,42,44;,
  4;50,52,52,50;,
  4;104,106,106,104;,
  4;53,51,51,53;,
  4;43,45,45,43;,
  4;105,105,107,107;,
  4;46,44,44,46;,
  4;52,54,54,52;,
  4;106,10,10,106;,
  4;54,53,53,54;,
  4;45,46,46,45;,
  4;107,107,10,10;,
  4;33,17,17,33;,
  4;17,34,34,17;,
  4;108,33,33,108;,
  4;34,109,109,34;,
  4;37,108,108,37;,
  4;109,38,38,109;,
  4;10,37,37,10;,
  4;38,10,10,38;,
  4;59,56,56,59;,
  4;59,59,58,58;,
  4;60,57,57,60;,
  4;60,60,55,55;,
  4;61,110,62,62;,
  4;61,62,62,110;,
  4;61,110,63,63;,
  4;61,63,63,110;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;111,111,112,64;,
  4;111,64,112,111;,
  4;113,114,115,65;,
  4;113,65,115,114;,
  4;64,112,115,65;,
  4;64,65,115,112;,
  4;66,66,67,67;,
  4;67,67,68,68;,
  4;68,68,69,69;,
  4;69,69,70,70;,
  4;70,70,71,71;,
  4;71,71,72,72;,
  4;72,72,73,73;,
  4;17,17,17,17;,
  4;116,116,74,74;,
  4;74,74,75,75;,
  4;75,75,76,76;,
  4;76,76,77,77;,
  4;77,77,78,78;,
  4;78,78,79,79;,
  4;79,79,80,80;,
  4;117,117,117,117;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;17,17,17,17;,
  4;81,81,82,82;,
  4;82,82,83,83;,
  4;118,118,84,84;,
  4;84,84,85,85;,
  4;85,85,86,86;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;3,3,81,81;,
  4;86,86,4,4;,
  4;8,8,8,8;,
  4;9,9,9,9;;
 }
 MeshTextureCoords {
  324;
  0.000000;0.000000;
  0.500000;0.000000;
  0.500000;1.000000;
  0.000000;1.000000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.000000;0.000000;
  0.500000;0.000000;
  0.500000;1.000000;
  0.000000;1.000000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.500000;0.500000;
  1.000000;0.500000;
  1.000000;1.000000;
  0.500000;1.000000;
  0.000000;1.000000;
  0.000000;0.500000;
  0.000000;0.500000;
  1.000000;0.500000;
  0.000000;1.000000;
  1.000000;0.500000;
  1.000000;1.000000;
  0.000000;0.500000;
  0.500000;0.500000;
  0.500000;0.000000;
  1.000000;0.000000;
  0.000000;0.000000;
  0.500000;0.250000;
  0.500000;0.000000;
  1.000000;0.000000;
  1.000000;0.250000;
  0.000000;0.250000;
  0.000000;0.000000;
  0.000000;0.250000;
  0.000000;0.000000;
  1.000000;0.250000;
  1.000000;0.250000;
  0.000000;0.250000;
  1.000000;0.000000;
  1.000000;0.750000;
  1.000000;1.000000;
  0.500000;1.000000;
  0.500000;0.750000;
  0.000000;0.750000;
  0.000000;1.000000;
  0.000000;0.000000;
  0.125000;0.000000;
  0.125000;1.000000;
  0.000000;1.000000;
  0.250000;0.000000;
  0.250000;1.000000;
  0.375000;0.000000;
  0.375000;1.000000;
  0.500000;0.000000;
  0.500000;1.000000;
  0.625000;0.000000;
  0.625000;1.000000;
  0.750000;0.000000;
  0.750000;1.000000;
  0.875000;0.000000;
  0.875000;1.000000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.062500;0.000000;
  0.187500;0.000000;
  0.312500;0.000000;
  0.437500;0.000000;
  0.562500;0.000000;
  0.687500;0.000000;
  0.812500;0.000000;
  0.937500;0.000000;
  0.062500;1.000000;
  0.187500;1.000000;
  0.312500;1.000000;
  0.437500;1.000000;
  0.562500;1.000000;
  0.687500;1.000000;
  0.812500;1.000000;
  0.937500;1.000000;
  0.000000;0.000000;
  0.125000;0.000000;
  0.125000;1.000000;
  0.000000;1.000000;
  0.250000;0.000000;
  0.250000;1.000000;
  0.375000;0.000000;
  0.375000;1.000000;
  0.500000;0.000000;
  0.500000;1.000000;
  0.625000;0.000000;
  0.625000;1.000000;
  0.750000;0.000000;
  0.750000;1.000000;
  0.875000;0.000000;
  0.875000;1.000000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.062500;0.000000;
  0.187500;0.000000;
  0.312500;0.000000;
  0.437500;0.000000;
  0.562500;0.000000;
  0.687500;0.000000;
  0.812500;0.000000;
  0.937500;0.000000;
  0.062500;1.000000;
  0.187500;1.000000;
  0.312500;1.000000;
  0.437500;1.000000;
  0.562500;1.000000;
  0.687500;1.000000;
  0.812500;1.000000;
  0.937500;1.000000;
  0.062500;0.000000;
  0.125000;0.000000;
  0.000000;0.000000;
  0.187500;0.000000;
  0.250000;0.000000;
  0.312500;0.000000;
  0.375000;0.000000;
  0.437500;0.000000;
  0.500000;0.000000;
  0.562500;0.000000;
  0.625000;0.000000;
  0.687500;0.000000;
  0.750000;0.000000;
  0.812500;0.000000;
  0.875000;0.000000;
  0.937500;0.000000;
  1.000000;0.000000;
  0.062500;1.000000;
  0.000000;1.000000;
  0.125000;1.000000;
  0.187500;1.000000;
  0.250000;1.000000;
  0.312500;1.000000;
  0.375000;1.000000;
  0.437500;1.000000;
  0.500000;1.000000;
  0.562500;1.000000;
  0.625000;1.000000;
  0.687500;1.000000;
  0.750000;1.000000;
  0.812500;1.000000;
  0.875000;1.000000;
  0.937500;1.000000;
  1.000000;1.000000;
  0.500000;0.250000;
  0.375000;0.250000;
  0.625000;0.250000;
  0.250000;0.250000;
  0.750000;0.250000;
  0.125000;0.250000;
  0.875000;0.250000;
  0.000000;0.250000;
  1.000000;0.250000;
  0.375000;0.312500;
  0.500000;0.312500;
  0.500000;0.312500;
  0.375000;0.312500;
  0.500000;0.250000;
  0.375000;0.250000;
  0.625000;0.250000;
  0.625000;0.312500;
  0.625000;0.312500;
  0.250000;0.312500;
  0.250000;0.312500;
  0.250000;0.250000;
  0.750000;0.250000;
  0.750000;0.312500;
  0.750000;0.312500;
  0.125000;0.312500;
  0.125000;0.312500;
  0.125000;0.250000;
  0.875000;0.250000;
  0.875000;0.312500;
  0.875000;0.312500;
  0.000000;0.312500;
  0.000000;0.312500;
  0.000000;0.250000;
  1.000000;0.250000;
  1.000000;0.312500;
  1.000000;0.312500;
  0.000000;0.500000;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;0.500000;
  1.000000;1.000000;
  0.000000;1.000000;
  1.000000;0.500000;
  1.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.500000;
  0.000000;0.000000;
  1.000000;0.000000;
  0.500000;0.500000;
  0.000000;0.500000;
  0.000000;0.000000;
  0.500000;0.000000;
  1.000000;0.000000;
  1.000000;0.500000;
  1.000000;1.000000;
  0.500000;1.000000;
  0.000000;1.000000;
  0.500000;1.000000;
  0.000000;1.000000;
  0.500000;0.000000;
  1.000000;1.000000;
  0.500000;0.000000;
  1.000000;0.000000;
  0.500000;1.000000;
  0.000000;0.000000;
  0.500000;1.000000;
  0.000000;1.000000;
  0.500000;0.500000;
  1.000000;1.000000;
  0.500000;0.000000;
  1.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;0.142860;
  0.000000;0.142860;
  1.000000;0.285710;
  0.000000;0.285710;
  1.000000;0.428570;
  0.000000;0.428570;
  1.000000;0.571430;
  0.000000;0.571430;
  1.000000;0.714290;
  0.000000;0.714290;
  1.000000;0.857140;
  0.000000;0.857140;
  1.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;0.142860;
  0.000000;0.142860;
  1.000000;0.285710;
  0.000000;0.285710;
  1.000000;0.428570;
  0.000000;0.428570;
  1.000000;0.571430;
  0.000000;0.571430;
  1.000000;0.714290;
  0.000000;0.714290;
  1.000000;0.857140;
  0.000000;0.857140;
  1.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.000000;
  1.000000;0.142860;
  0.000000;0.142860;
  1.000000;0.285710;
  0.000000;0.285710;
  1.000000;0.428570;
  0.000000;0.428570;
  1.000000;0.571430;
  0.000000;0.571430;
  1.000000;0.714290;
  0.000000;0.714290;
  1.000000;0.857140;
  0.000000;0.857140;
  0.000000;1.000000;
  1.000000;0.000000;
  1.000000;0.142860;
  0.000000;0.142860;
  1.000000;0.285710;
  0.000000;0.285710;
  1.000000;0.428570;
  0.000000;0.428570;
  1.000000;0.571430;
  0.000000;0.571430;
  1.000000;0.714290;
  0.000000;0.714290;
  1.000000;0.857140;
  0.000000;0.857140;
  1.000000;1.000000;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.500000;
  1.000000;0.500000;
  1.000000;0.750000;
  0.000000;0.750000;
  1.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;0.250000;
  0.000000;0.250000;
  1.000000;0.500000;
  0.000000;0.500000;
  0.500000;0.000000;
  0.750000;0.000000;
  0.750000;1.000000;
  0.500000;1.000000;
  0.250000;0.000000;
  0.250000;1.000000;
  0.500000;0.000000;
  0.500000;1.000000;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;1.000000;;
 }
}
