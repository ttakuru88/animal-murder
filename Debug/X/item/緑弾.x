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
 52;
 0.00000;0.04360;0.00000;,
 0.01812;0.03527;-0.01812;,
 0.00000;0.03527;-0.02563;,
 0.00000;0.04360;0.00000;,
 0.02563;0.03527;0.00000;,
 0.00000;0.04360;0.00000;,
 0.01812;0.03527;0.01812;,
 0.00000;0.04360;0.00000;,
 0.00000;0.03527;0.02563;,
 0.00000;0.04360;0.00000;,
 -0.01812;0.03527;0.01812;,
 0.00000;0.04360;0.00000;,
 -0.02563;0.03527;0.00000;,
 0.00000;0.04360;0.00000;,
 -0.01812;0.03527;-0.01812;,
 0.00000;0.04360;0.00000;,
 0.00000;0.03527;-0.02563;,
 0.02932;0.01347;-0.02932;,
 0.00000;0.01347;-0.04147;,
 0.04147;0.01347;0.00000;,
 0.02932;0.01347;0.02932;,
 0.00000;0.01347;0.04147;,
 -0.02932;0.01347;0.02932;,
 -0.04147;0.01347;0.00000;,
 -0.02932;0.01347;-0.02932;,
 0.00000;0.01347;-0.04147;,
 0.02932;-0.01347;-0.02932;,
 0.00000;-0.01347;-0.04147;,
 0.04147;-0.01347;0.00000;,
 0.02932;-0.01347;0.02932;,
 -0.00000;-0.01347;0.04147;,
 -0.02932;-0.01347;0.02932;,
 -0.04147;-0.01347;0.00000;,
 -0.02932;-0.01347;-0.02932;,
 0.00000;-0.01347;-0.04147;,
 0.01812;-0.03527;-0.01812;,
 0.00000;-0.03527;-0.02563;,
 0.02563;-0.03527;0.00000;,
 0.01812;-0.03527;0.01812;,
 -0.00000;-0.03527;0.02563;,
 -0.01812;-0.03527;0.01812;,
 -0.02563;-0.03527;0.00000;,
 -0.01812;-0.03527;-0.01812;,
 0.00000;-0.03527;-0.02563;,
 0.00000;-0.04360;-0.00000;,
 0.00000;-0.04360;-0.00000;,
 0.00000;-0.04360;-0.00000;,
 0.00000;-0.04360;-0.00000;,
 0.00000;-0.04360;-0.00000;,
 0.00000;-0.04360;-0.00000;,
 0.00000;-0.04360;-0.00000;,
 0.00000;-0.04360;-0.00000;;
 
 40;
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
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 3;36,35,44;,
 3;35,37,45;,
 3;37,38,46;,
 3;38,39,47;,
 3;39,40,48;,
 3;40,41,49;,
 3;41,42,50;,
 3;42,43,51;;
 
 MeshMaterialList {
  1;
  40;
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
   0.031000;1.000000;0.000000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshTextureCoords {
  52;
  0.062500;0.000000;
  0.125000;0.200000;
  0.000000;0.200000;
  0.187500;0.000000;
  0.250000;0.200000;
  0.312500;0.000000;
  0.375000;0.200000;
  0.437500;0.000000;
  0.500000;0.200000;
  0.562500;0.000000;
  0.625000;0.200000;
  0.687500;0.000000;
  0.750000;0.200000;
  0.812500;0.000000;
  0.875000;0.200000;
  0.937500;0.000000;
  1.000000;0.200000;
  0.125000;0.400000;
  0.000000;0.400000;
  0.250000;0.400000;
  0.375000;0.400000;
  0.500000;0.400000;
  0.625000;0.400000;
  0.750000;0.400000;
  0.875000;0.400000;
  1.000000;0.400000;
  0.125000;0.600000;
  0.000000;0.600000;
  0.250000;0.600000;
  0.375000;0.600000;
  0.500000;0.600000;
  0.625000;0.600000;
  0.750000;0.600000;
  0.875000;0.600000;
  1.000000;0.600000;
  0.125000;0.800000;
  0.000000;0.800000;
  0.250000;0.800000;
  0.375000;0.800000;
  0.500000;0.800000;
  0.625000;0.800000;
  0.750000;0.800000;
  0.875000;0.800000;
  1.000000;0.800000;
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
