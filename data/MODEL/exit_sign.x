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
 72;
 37.65179;28.88983;1.30691;,
 39.02430;28.88983;1.30691;,
 39.02430;28.88983;-1.30691;,
 37.50500;28.88983;-1.30691;,
 37.50663;-0.32819;-1.30691;,
 39.02430;-0.32819;-1.30691;,
 39.02430;-0.32819;1.30691;,
 37.65346;-0.32819;1.30691;,
 -37.66302;28.88983;-1.30691;,
 -39.02430;28.88983;-1.30691;,
 -39.02430;28.88983;1.30691;,
 -37.89000;28.88983;1.30691;,
 -37.89165;-0.32819;1.30691;,
 -39.02430;-0.32819;1.30691;,
 -39.02430;-0.32819;-1.30691;,
 -37.66473;-0.32819;-1.30691;,
 39.02430;26.53121;1.30691;,
 39.02430;26.47255;-1.30691;,
 39.02430;28.88983;-1.30691;,
 -39.02430;26.53699;-1.30691;,
 -39.02430;26.59565;1.30691;,
 -39.02430;28.88983;-1.30691;,
 39.02430;26.47255;-1.30691;,
 37.50512;26.47380;-1.30691;,
 37.50500;28.88983;-1.30691;,
 39.02430;28.88983;-1.30691;,
 37.65191;26.53234;1.30691;,
 39.02430;26.53121;1.30691;,
 39.02430;28.88983;1.30691;,
 37.65179;28.88983;1.30691;,
 -39.02430;26.53699;-1.30691;,
 -39.02430;28.88983;-1.30691;,
 -37.66302;28.88983;-1.30691;,
 -37.66315;26.53586;-1.30691;,
 -39.02430;26.59565;1.30691;,
 -37.89010;26.59471;1.30691;,
 -37.89000;28.88983;1.30691;,
 -39.02430;28.88983;1.30691;,
 39.02430;2.37049;1.30691;,
 39.02430;-0.32819;-1.30691;,
 39.02430;2.43163;-1.30691;,
 -39.02430;2.36446;-1.30691;,
 -39.02430;-0.32819;-1.30691;,
 -39.02430;2.30331;1.30691;,
 39.02430;2.43163;-1.30691;,
 39.02430;-0.32819;-1.30691;,
 37.50663;-0.32819;-1.30691;,
 37.50650;2.43032;-1.30691;,
 37.65333;2.36931;1.30691;,
 37.65346;-0.32819;1.30691;,
 39.02430;-0.32819;1.30691;,
 39.02430;2.37049;1.30691;,
 -37.66457;2.36563;-1.30691;,
 -37.66473;-0.32819;-1.30691;,
 -39.02430;-0.32819;-1.30691;,
 -39.02430;2.36446;-1.30691;,
 -39.02430;2.30331;1.30691;,
 -39.02430;-0.32819;1.30691;,
 -37.89165;-0.32819;1.30691;,
 -37.89148;2.30429;1.30691;,
 -37.66457;2.36563;-0.24324;,
 37.50650;2.43032;-0.24324;,
 -37.66315;26.53586;-0.24324;,
 37.50512;26.47380;-0.24324;,
 37.50650;2.43032;-0.24324;,
 -37.66457;2.36563;-0.24324;,
 -37.66315;26.53586;-0.24324;,
 37.50512;26.47380;-0.24324;,
 37.65333;2.36931;0.44268;,
 -37.89148;2.30429;0.44268;,
 37.65191;26.53234;0.44268;,
 -37.89010;26.59471;0.44268;;
 
 38;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,11,0,3;,
 4;12,13,14,15;,
 4;12,15,4,7;,
 4;16,17,18,1;,
 4;19,20,10,21;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;33,32,24,23;,
 4;34,35,36,37;,
 4;35,26,29,36;,
 4;38,6,39,40;,
 4;38,40,17,16;,
 4;41,42,13,43;,
 4;41,43,20,19;,
 4;44,45,46,47;,
 4;44,47,23,22;,
 4;48,49,50,51;,
 4;48,51,27,26;,
 4;52,53,54,55;,
 4;52,55,30,33;,
 4;47,46,53,52;,
 4;56,57,58,59;,
 4;56,59,35,34;,
 4;59,58,49,48;,
 4;60,61,47,52;,
 4;62,60,52,33;,
 4;63,62,33,23;,
 4;61,63,23,47;,
 4;64,65,66,67;,
 4;68,69,59,48;,
 4;70,68,48,26;,
 4;71,70,26,35;,
 4;69,71,35,59;,
 4;69,68,70,71;;
 
 MeshMaterialList {
  3;
  38;
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
  2,
  1,
  1,
  1,
  1,
  0;;
  Material {
   0.000000;0.178360;0.109200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.610540;0.373800;;
  }
  Material {
   0.392000;0.392000;0.392000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.520000;0.520000;0.520000;;
   TextureFilename {
    "data\\TEXTURE\\EX00_Sign.png";
   }
  }
 }
 MeshNormals {
  14;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000826;-1.000000;0.000000;,
  1.000000;-0.000059;-0.000000;,
  -0.000861;1.000000;0.000000;,
  -1.000000;-0.000059;0.000000;,
  -0.000826;-1.000000;0.000000;,
  -0.000861;1.000000;0.000000;,
  -1.000000;-0.000057;0.000000;,
  1.000000;-0.000057;-0.000000;;
  38;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;8,8,8,8;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;12,12,12,12;,
  4;4,4,4,4;,
  4;11,11,11,11;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;13,13,13,13;,
  4;5,5,5,5;;
 }
 MeshTextureCoords {
  72;
  0.982410;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.980530;1.000000;,
  0.980550;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.982440;1.000000;,
  0.017440;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.014530;0.000000;,
  0.014510;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.017420;0.000000;,
  1.000000;0.080720;,
  0.000000;0.082730;,
  0.000000;0.000000;,
  1.000000;0.080530;,
  0.000000;0.078520;,
  1.000000;0.000000;,
  1.000000;0.082730;,
  0.980540;0.082690;,
  0.980530;0.000000;,
  1.000000;0.000000;,
  0.017580;0.080690;,
  0.000000;0.080720;,
  0.000000;0.000000;,
  0.017590;0.000000;,
  0.000000;0.080530;,
  0.000000;0.000000;,
  0.017440;0.000000;,
  0.017440;0.080570;,
  1.000000;0.078520;,
  0.985470;0.078550;,
  0.985470;0.000000;,
  1.000000;0.000000;,
  1.000000;0.907640;,
  0.000000;1.000000;,
  0.000000;0.905540;,
  1.000000;0.907840;,
  1.000000;1.000000;,
  0.000000;0.909940;,
  1.000000;0.905540;,
  1.000000;1.000000;,
  0.980550;1.000000;,
  0.980550;0.905590;,
  0.017570;0.907680;,
  0.017560;1.000000;,
  0.000000;1.000000;,
  0.000000;0.907640;,
  0.017420;0.907800;,
  0.017420;1.000000;,
  0.000000;1.000000;,
  0.000000;0.907840;,
  1.000000;0.909940;,
  1.000000;1.000000;,
  0.985490;1.000000;,
  0.985490;0.909900;,
  0.017420;0.907800;,
  0.980550;0.905590;,
  0.017440;0.080570;,
  0.980540;0.082690;,
  1.000000;0.997322;,
  -0.000001;0.999999;,
  0.000018;-0.000003;,
  0.999982;0.002565;,
  0.017570;0.907680;,
  0.985490;0.909900;,
  0.017580;0.080690;,
  0.985470;0.078550;;
 }
}
