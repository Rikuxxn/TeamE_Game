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
 79;
 2.50958;2.50315;0.84500;,
 3.19419;2.31057;0.16039;,
 2.50958;2.31057;-0.12319;,
 2.50958;2.50315;0.84500;,
 3.47777;2.31057;0.84500;,
 2.50958;2.50315;0.84500;,
 3.19419;2.31057;1.52961;,
 2.50958;2.50315;0.84500;,
 2.50958;2.31057;1.81319;,
 2.50958;2.50315;0.84500;,
 1.82496;2.31057;1.52961;,
 2.50958;2.50315;0.84500;,
 1.54139;2.31057;0.84500;,
 2.50958;2.50315;0.84500;,
 1.82496;2.31057;0.16039;,
 2.50958;2.50315;0.84500;,
 2.50958;2.31057;-0.12319;,
 3.77458;1.76213;-0.42000;,
 2.50958;1.76213;-0.94398;,
 4.29856;1.76213;0.84500;,
 3.77458;1.76213;2.11000;,
 2.50958;1.76213;2.63398;,
 1.24458;1.76213;2.11000;,
 0.72060;1.76213;0.84500;,
 1.24458;1.76213;-0.42000;,
 2.50958;1.76213;-0.94398;,
 4.16238;0.94134;-0.80780;,
 2.50958;0.94134;-1.49242;,
 4.84699;0.94134;0.84500;,
 4.16238;0.94134;2.49780;,
 2.50958;0.94134;3.18242;,
 0.85678;0.94134;2.49780;,
 0.17216;0.94134;0.84500;,
 0.85678;0.94134;-0.80780;,
 2.50958;0.94134;-1.49242;,
 4.29856;-0.02685;-0.94398;,
 2.50958;-0.02685;-1.68500;,
 5.03958;-0.02685;0.84500;,
 4.29856;-0.02685;2.63398;,
 2.50958;-0.02685;3.37500;,
 0.72060;-0.02685;2.63398;,
 -0.02042;-0.02685;0.84500;,
 0.72060;-0.02685;-0.94398;,
 2.50958;-0.02685;-1.68500;,
 4.16238;-0.99504;-0.80780;,
 2.50958;-0.99504;-1.49242;,
 4.84699;-0.99504;0.84500;,
 4.16238;-0.99504;2.49780;,
 2.50958;-0.99504;3.18242;,
 0.85678;-0.99504;2.49780;,
 0.17216;-0.99504;0.84500;,
 0.85678;-0.99504;-0.80780;,
 2.50958;-0.99504;-1.49242;,
 3.77458;-1.81582;-0.42000;,
 2.50958;-1.81582;-0.94398;,
 4.29856;-1.81582;0.84500;,
 3.77458;-1.81582;2.11000;,
 2.50958;-1.81582;2.63398;,
 1.24458;-1.81582;2.11000;,
 0.72060;-1.81582;0.84500;,
 1.24458;-1.81582;-0.42000;,
 2.50958;-1.81582;-0.94398;,
 3.19419;-2.36426;0.16039;,
 2.50958;-2.36426;-0.12319;,
 3.47777;-2.36426;0.84500;,
 3.19419;-2.36426;1.52961;,
 2.50958;-2.36426;1.81319;,
 1.82496;-2.36426;1.52961;,
 1.54139;-2.36426;0.84500;,
 1.82496;-2.36426;0.16039;,
 2.50958;-2.36426;-0.12319;,
 2.50958;-2.55685;0.84500;,
 2.50958;-2.55685;0.84500;,
 2.50958;-2.55685;0.84500;,
 2.50958;-2.55685;0.84500;,
 2.50958;-2.55685;0.84500;,
 2.50958;-2.55685;0.84500;,
 2.50958;-2.55685;0.84500;,
 2.50958;-2.55685;0.84500;;
 
 64;
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
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 3;63,62,71;,
 3;62,64,72;,
 3;64,65,73;,
 3;65,66,74;,
 3;66,67,75;,
 3;67,68,76;,
 3;68,69,77;,
 3;69,70,78;;
 
 MeshMaterialList {
  1;
  64;
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
   0.800000;0.571200;0.445600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  58;
  0.000001;1.000000;-0.000000;,
  0.000001;0.924736;-0.380610;,
  0.269133;0.924735;-0.269133;,
  0.380610;0.924736;-0.000000;,
  0.269133;0.924735;0.269133;,
  0.000001;0.924735;0.380611;,
  -0.269133;0.924735;0.269133;,
  -0.380611;0.924735;-0.000000;,
  -0.269133;0.924735;-0.269133;,
  0.000001;0.709229;-0.704978;,
  0.498496;0.709228;-0.498495;,
  0.704979;0.709228;0.000000;,
  0.498496;0.709228;0.498495;,
  0.000001;0.709229;0.704978;,
  -0.498496;0.709228;0.498496;,
  -0.704979;0.709228;-0.000000;,
  -0.498496;0.709228;-0.498496;,
  0.000001;0.384552;-0.923103;,
  0.652734;0.384552;-0.652732;,
  0.923103;0.384552;0.000000;,
  0.652734;0.384552;0.652732;,
  0.000001;0.384552;0.923103;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;0.000000;,
  -0.652733;0.384551;-0.652733;,
  0.000001;0.000001;-1.000000;,
  0.707107;0.000001;-0.707106;,
  1.000000;0.000001;-0.000000;,
  0.707107;0.000001;0.707106;,
  0.000001;0.000001;1.000000;,
  -0.707107;0.000001;0.707106;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707106;,
  0.000001;-0.384555;-0.923102;,
  0.652733;-0.384554;-0.652731;,
  0.923102;-0.384555;-0.000000;,
  0.652733;-0.384555;0.652731;,
  0.000001;-0.384555;0.923102;,
  -0.652732;-0.384554;0.652732;,
  -0.923102;-0.384554;-0.000000;,
  -0.652732;-0.384554;-0.652732;,
  0.000001;-0.709231;-0.704976;,
  0.498494;-0.709230;-0.498493;,
  0.704977;-0.709230;-0.000000;,
  0.498494;-0.709230;0.498494;,
  0.000001;-0.709231;0.704976;,
  -0.498494;-0.709230;0.498494;,
  -0.704977;-0.709230;-0.000000;,
  -0.498494;-0.709230;-0.498494;,
  0.000001;-0.924733;-0.380616;,
  0.269137;-0.924733;-0.269137;,
  0.380616;-0.924733;-0.000000;,
  0.269137;-0.924733;0.269137;,
  0.000001;-0.924733;0.380616;,
  -0.269137;-0.924733;0.269137;,
  -0.380617;-0.924733;-0.000000;,
  -0.269137;-0.924733;-0.269137;,
  0.000001;-1.000000;-0.000000;;
  64;
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
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;;
 }
 MeshTextureCoords {
  79;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
