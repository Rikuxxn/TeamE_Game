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
 136;
 -46.91044;5.64256;15.07319;,
 -46.91044;5.64256;-14.70919;,
 -42.58069;5.64256;-14.70919;,
 -42.58069;5.64256;15.07319;,
 -60.02714;19.88884;-14.70919;,
 -46.91044;5.64256;-14.70919;,
 -46.91044;5.64256;15.07319;,
 -60.02714;19.89761;15.07319;,
 -42.58069;19.69516;-14.70919;,
 -46.91044;5.64256;-14.70919;,
 -60.02714;19.88884;-14.70919;,
 -42.58069;19.70385;15.07319;,
 -42.58069;5.64256;15.07319;,
 -42.58069;5.64256;-14.70919;,
 -42.58069;19.69516;-14.70919;,
 -60.02714;19.89761;15.07319;,
 -46.91044;5.64256;15.07319;,
 -42.58069;19.70385;15.07319;,
 -60.02714;32.88260;-14.70919;,
 -60.02714;39.18443;-14.70919;,
 -42.58069;39.18443;-14.70919;,
 -42.58069;32.80676;-14.70919;,
 -42.58069;32.80900;15.07319;,
 -42.58069;39.18443;15.07319;,
 -60.02714;39.18443;15.07319;,
 -60.02714;32.88484;15.07319;,
 -42.58069;24.83550;-14.70919;,
 -60.02714;25.18164;-14.70919;,
 -60.02714;25.19164;15.07319;,
 -42.58069;24.84545;15.07319;,
 -42.58069;39.18443;5.15466;,
 -60.02714;39.18443;5.34211;,
 -60.02714;39.18443;15.07319;,
 -60.02714;39.18443;5.34211;,
 -60.02714;32.88407;5.34211;,
 -60.02714;32.88484;15.07319;,
 -60.02714;39.18443;15.07319;,
 -42.58069;39.18443;5.15466;,
 -42.58069;39.18443;15.07319;,
 -42.58069;32.80900;15.07319;,
 -42.58069;32.80823;5.15466;,
 -60.02714;19.89469;5.34218;,
 -60.02714;25.19164;15.07319;,
 -60.02714;25.18831;5.34218;,
 -42.58069;19.70097;5.15472;,
 -42.58069;24.84210;5.15472;,
 -42.58069;24.84545;15.07319;,
 -42.58069;39.18443;-4.14208;,
 -60.02714;39.18443;-14.70919;,
 -60.02714;39.18443;-3.63913;,
 -60.02714;39.18443;-3.63913;,
 -60.02714;39.18443;-14.70919;,
 -60.02714;32.88260;-14.70919;,
 -60.02714;32.88344;-3.63918;,
 -42.58069;32.80759;-4.14214;,
 -42.58069;32.80676;-14.70919;,
 -42.58069;39.18443;-14.70919;,
 -42.58069;39.18443;-4.14208;,
 -60.02714;25.18531;-3.63925;,
 -60.02714;25.18164;-14.70919;,
 -60.02714;19.89211;-3.63929;,
 -42.58069;19.69819;-4.14226;,
 -42.58069;24.83550;-14.70919;,
 -42.58069;24.83896;-4.14226;,
 -51.49323;25.18531;-3.63925;,
 -51.49323;32.88344;-3.63918;,
 -51.49323;25.18831;5.34218;,
 -51.49323;32.88407;5.34211;,
 46.86124;5.64256;-14.13432;,
 46.86124;5.64256;15.64806;,
 42.53153;5.64256;15.64810;,
 42.53153;5.64256;-14.13432;,
 59.97794;19.88884;15.64806;,
 46.86124;5.64256;15.64806;,
 46.86124;5.64256;-14.13432;,
 59.97794;19.89761;-14.13432;,
 42.53153;19.69516;15.64810;,
 46.86124;5.64256;15.64806;,
 59.97794;19.88884;15.64806;,
 42.53153;19.70385;-14.13432;,
 42.53153;5.64256;-14.13432;,
 42.53153;5.64256;15.64810;,
 42.53153;19.69516;15.64810;,
 59.97794;19.89761;-14.13432;,
 46.86124;5.64256;-14.13432;,
 42.53153;19.70385;-14.13432;,
 59.97794;32.88260;15.64806;,
 59.97794;39.18443;15.64806;,
 42.53153;39.18443;15.64810;,
 42.53153;32.80676;15.64810;,
 42.53153;32.80900;-14.13427;,
 42.53153;39.18443;-14.13432;,
 59.97794;39.18443;-14.13432;,
 59.97794;32.88484;-14.13432;,
 42.53153;24.83550;15.64810;,
 59.97794;25.18164;15.64806;,
 59.97794;25.19164;-14.13432;,
 42.53153;24.84545;-14.13427;,
 42.53153;39.18443;-4.21581;,
 59.97794;39.18443;-4.40325;,
 59.97794;39.18443;-14.13432;,
 59.97794;39.18443;-4.40325;,
 59.97794;32.88407;-4.40325;,
 59.97794;32.88484;-14.13432;,
 59.97794;39.18443;-14.13432;,
 42.53153;39.18443;-4.21581;,
 42.53153;39.18443;-14.13432;,
 42.53153;32.80900;-14.13427;,
 42.53153;32.80823;-4.21581;,
 59.97794;19.89469;-4.40331;,
 59.97794;25.19164;-14.13432;,
 59.97794;25.18831;-4.40331;,
 42.53153;19.70097;-4.21586;,
 42.53153;24.84210;-4.21586;,
 42.53153;24.84545;-14.13427;,
 42.53153;39.18443;5.08095;,
 59.97794;39.18443;15.64806;,
 59.97794;39.18443;4.57799;,
 59.97794;39.18443;4.57799;,
 59.97794;39.18443;15.64806;,
 59.97794;32.88260;15.64806;,
 59.97794;32.88344;4.57805;,
 42.53153;32.80759;5.08106;,
 42.53153;32.80676;15.64810;,
 42.53153;39.18443;15.64810;,
 42.53153;39.18443;5.08095;,
 59.97794;25.18531;4.57811;,
 59.97794;25.18164;15.64806;,
 59.97794;19.89211;4.57817;,
 42.53153;19.69819;5.08113;,
 42.53153;24.83550;15.64810;,
 42.53153;24.83896;5.08113;,
 51.44397;25.18531;4.57811;,
 51.44397;32.88344;4.57805;,
 51.44397;25.18831;-4.40331;,
 51.44397;32.88407;-4.40325;;
 
 72;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,2,9,10;,
 4;11,12,13,14;,
 4;15,16,3,17;,
 4;18,19,20,21;,
 4;22,23,24,25;,
 4;26,8,10,27;,
 4;26,27,18,21;,
 4;28,15,17,29;,
 4;28,29,22,25;,
 4;30,31,32,23;,
 4;33,34,35,36;,
 4;37,38,39,40;,
 4;41,7,42,43;,
 4;43,42,35,34;,
 4;44,45,46,11;,
 4;45,40,39,46;,
 4;47,20,48,49;,
 4;47,49,31,30;,
 4;50,51,52,53;,
 4;50,53,34,33;,
 4;54,55,56,57;,
 4;54,57,37,40;,
 4;58,59,4,60;,
 4;58,60,41,43;,
 4;53,52,59,58;,
 4;61,14,62,63;,
 4;61,63,45,44;,
 4;63,62,55,54;,
 4;63,54,40,45;,
 4;64,65,53,58;,
 4;66,64,58,43;,
 4;67,66,43,34;,
 4;65,67,34,53;,
 4;65,64,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,70,77,78;,
 4;79,80,81,82;,
 4;83,84,71,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;94,76,78,95;,
 4;94,95,86,89;,
 4;96,83,85,97;,
 4;96,97,90,93;,
 4;98,99,100,91;,
 4;101,102,103,104;,
 4;105,106,107,108;,
 4;109,75,110,111;,
 4;111,110,103,102;,
 4;112,113,114,79;,
 4;113,108,107,114;,
 4;115,88,116,117;,
 4;115,117,99,98;,
 4;118,119,120,121;,
 4;118,121,102,101;,
 4;122,123,124,125;,
 4;122,125,105,108;,
 4;126,127,72,128;,
 4;126,128,109,111;,
 4;121,120,127,126;,
 4;129,82,130,131;,
 4;129,131,113,112;,
 4;131,130,123,122;,
 4;131,122,108,113;,
 4;132,133,121,126;,
 4;134,132,126,111;,
 4;135,134,111,102;,
 4;133,135,102,121;,
 4;133,132,134,135;;
 
 MeshMaterialList {
  4;
  72;
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
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
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
  3,
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
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
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
  3;;
  Material {
   0.000000;0.564800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.690400;0.680800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\SL00_Button.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  31;
  0.000000;0.000000;1.000000;,
  -0.401729;-0.915758;0.000054;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.931605;-0.363473;0.000054;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.000009;-1.000000;,
  0.000000;1.000000;-0.000334;,
  0.000000;-0.000009;1.000000;,
  0.000000;-1.000000;0.000070;,
  -0.000001;-0.000004;-1.000000;,
  0.401729;-0.915758;-0.000054;,
  0.000002;0.000000;1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.931605;-0.363473;-0.000054;,
  0.000004;-0.000002;1.000000;,
  -1.000000;0.000000;0.000000;,
  -0.000002;-0.000002;-1.000000;,
  0.000002;0.000000;1.000000;,
  -0.000002;0.000002;-1.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-0.000008;1.000000;,
  0.000000;1.000000;0.000334;,
  0.000000;-0.000008;-1.000000;,
  0.000006;-0.000004;1.000000;,
  -0.000001;0.000002;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000070;;
  72;
  4;1,1,3,3;,
  4;4,1,1,4;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;5,5,5,5;,
  4;7,4,7,7;,
  4;7,7,7,7;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;7,7,4,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;10,10,10,10;,
  4;9,9,9,9;,
  4;8,8,8,8;,
  4;11,11,11,11;,
  4;7,7,7,7;,
  4;13,13,15,15;,
  4;16,13,13,16;,
  4;17,27,27,17;,
  4;18,18,18,18;,
  4;28,29,29,28;,
  4;20,14,14,20;,
  4;19,12,12,19;,
  4;20,17,17,20;,
  4;20,20,20,20;,
  4;21,28,28,21;,
  4;21,21,19,19;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;18,18,18,18;,
  4;23,16,23,23;,
  4;23,23,23,23;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;23,23,23,23;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;23,23,16,23;,
  4;23,23,23,23;,
  4;23,23,23,23;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;26,26,26,26;,
  4;25,25,25,25;,
  4;24,24,24,24;,
  4;30,30,30,30;,
  4;23,23,23,23;;
 }
 MeshTextureCoords {
  136;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.575270;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.575010;,
  1.000000;0.581040;,
  0.000000;1.000000;,
  0.000000;0.575270;,
  1.000000;0.580780;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.581040;,
  1.000000;0.575010;,
  1.000000;1.000000;,
  0.000000;0.580780;,
  0.000000;0.187880;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.190140;,
  0.000000;0.190070;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.187810;,
  1.000000;0.427790;,
  0.000000;0.417470;,
  1.000000;0.417170;,
  0.000000;0.427490;,
  0.333030;0.000000;,
  0.326740;1.000000;,
  0.000000;1.000000;,
  0.326740;0.000000;,
  0.326740;0.187830;,
  0.000000;0.187810;,
  0.000000;0.000000;,
  0.666970;0.000000;,
  1.000000;0.000000;,
  1.000000;0.190070;,
  0.666970;0.190100;,
  0.326740;0.575090;,
  0.000000;0.417170;,
  0.326740;0.417270;,
  0.666970;0.580870;,
  0.666970;0.427590;,
  1.000000;0.427490;,
  0.645190;0.000000;,
  1.000000;1.000000;,
  0.628300;1.000000;,
  0.628300;0.000000;,
  1.000000;0.000000;,
  1.000000;0.187880;,
  0.628300;0.187850;,
  0.354810;0.190120;,
  0.000000;0.190140;,
  0.000000;0.000000;,
  0.354810;0.000000;,
  0.628300;0.417360;,
  1.000000;0.417470;,
  0.628310;0.575170;,
  0.354800;0.580950;,
  0.000000;0.427790;,
  0.354810;0.427690;,
  0.628300;0.417360;,
  0.628300;0.187850;,
  0.326740;0.417270;,
  0.326740;0.187830;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.575270;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.575010;,
  1.000000;0.581040;,
  0.000000;1.000000;,
  0.000000;0.575270;,
  1.000000;0.580780;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.581040;,
  1.000000;0.575010;,
  1.000000;1.000000;,
  0.000000;0.580780;,
  0.000000;0.187880;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.190140;,
  0.000000;0.190070;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.187810;,
  1.000000;0.427790;,
  0.000000;0.417470;,
  1.000000;0.417170;,
  0.000000;0.427490;,
  0.333030;0.000000;,
  0.326740;1.000000;,
  0.000000;1.000000;,
  0.326740;0.000000;,
  0.326740;0.187830;,
  0.000000;0.187810;,
  0.000000;0.000000;,
  0.666970;0.000000;,
  1.000000;0.000000;,
  1.000000;0.190070;,
  0.666970;0.190100;,
  0.326740;0.575090;,
  0.000000;0.417170;,
  0.326740;0.417270;,
  0.666970;0.580870;,
  0.666970;0.427590;,
  1.000000;0.427490;,
  0.645190;0.000000;,
  1.000000;1.000000;,
  0.628300;1.000000;,
  0.628300;0.000000;,
  1.000000;0.000000;,
  1.000000;0.187880;,
  0.628300;0.187850;,
  0.354810;0.190120;,
  0.000000;0.190140;,
  0.000000;0.000000;,
  0.354810;0.000000;,
  0.628300;0.417360;,
  1.000000;0.417470;,
  0.628310;0.575170;,
  0.354800;0.580950;,
  0.000000;0.427790;,
  0.354810;0.427690;,
  0.628300;0.417360;,
  0.628300;0.187850;,
  0.326740;0.417270;,
  0.326740;0.187830;;
 }
}
