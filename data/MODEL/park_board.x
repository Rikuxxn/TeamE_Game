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
 44;
 61.19918;20.56445;-3.71618;,
 61.19918;20.56445;3.71618;,
 61.19918;-5.55044;3.71618;,
 61.19918;-5.55044;-3.71618;,
 -71.59790;20.56445;3.71618;,
 -71.59790;20.56445;-3.71618;,
 -71.59790;-5.55044;-3.71618;,
 -71.59790;-5.55044;3.71618;,
 -37.80313;5.17430;-3.71618;,
 -71.59790;-5.55044;-3.71618;,
 -71.59790;20.56445;-3.71618;,
 -37.80313;33.63885;-3.71618;,
 -5.19713;39.82314;-3.71618;,
 -5.19713;11.35859;-3.71618;,
 -37.80313;5.17430;-3.71618;,
 -5.19713;11.35859;-3.71618;,
 -5.19713;11.35859;3.71618;,
 -37.80313;5.17430;3.71618;,
 -71.59790;-5.55044;-3.71618;,
 -37.80313;33.63885;-3.71618;,
 -71.59790;20.56445;-3.71618;,
 -37.80313;33.63885;3.71618;,
 -5.19713;39.82314;3.71618;,
 -5.19713;39.82314;-3.71618;,
 -37.80313;5.17430;3.71618;,
 -5.19713;11.35859;3.71618;,
 -5.19713;39.82314;3.71618;,
 -37.80313;33.63885;3.71618;,
 -71.59790;20.56445;3.71618;,
 -71.59790;-5.55044;3.71618;,
 28.77323;5.17430;-3.71618;,
 28.77323;33.63885;-3.71618;,
 61.19918;20.56445;-3.71618;,
 61.19918;-5.55044;-3.71618;,
 28.77323;5.17430;-3.71618;,
 61.19918;-5.55044;-3.71618;,
 28.77323;5.17430;3.71618;,
 28.77323;33.63885;-3.71618;,
 28.77323;33.63885;3.71618;,
 61.19918;20.56445;-3.71618;,
 28.77323;5.17430;3.71618;,
 61.19918;-5.55044;3.71618;,
 61.19918;20.56445;3.71618;,
 28.77323;33.63885;3.71618;;
 
 18;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,11,12,13;,
 4;14,15,16,17;,
 4;14,17,7,18;,
 4;19,20,4,21;,
 4;19,21,22,23;,
 4;24,25,26,27;,
 4;24,27,28,29;,
 4;30,13,12,31;,
 4;30,31,32,33;,
 4;34,35,2,36;,
 4;34,36,16,15;,
 4;37,23,22,38;,
 4;37,38,1,39;,
 4;40,41,42,43;,
 4;40,43,26,25;;
 
 MeshMaterialList {
  2;
  18;
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
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
    "data\\TEXTURE\\park_board.png";
   }
  }
 }
 MeshNormals {
  14;
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.003682;-0.999993;-0.000000;,
  -0.003682;0.999993;0.000000;,
  0.244853;-0.969560;-0.000000;,
  -0.274713;0.961526;0.000000;,
  -0.247160;-0.968975;0.000000;,
  0.277963;0.960592;0.000000;,
  0.302483;-0.953155;-0.000000;,
  -0.360815;0.932637;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.314016;-0.949418;0.000000;,
  0.373954;0.927447;0.000000;;
  18;
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;5,3,3,5;,
  4;5,5,9,9;,
  4;6,10,10,6;,
  4;6,6,4,4;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;7,12,12,7;,
  4;7,7,3,3;,
  4;8,4,4,8;,
  4;8,8,13,13;,
  4;11,11,11,11;,
  4;11,11,11,11;;
 }
 MeshTextureCoords {
  44;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.238869;0.902897;,
  -0.022042;1.194315;,
  -0.022042;0.484709;,
  0.238869;0.129445;,
  0.490601;-0.038597;,
  0.490601;0.734855;,
  0.254484;0.000000;,
  0.500017;0.000000;,
  0.500017;1.000000;,
  0.254484;1.000000;,
  0.000000;0.000000;,
  0.254484;1.000000;,
  0.000000;1.000000;,
  0.254484;0.000000;,
  0.500017;0.000000;,
  0.500017;1.000000;,
  0.745516;1.000000;,
  0.499983;1.000000;,
  0.499983;0.000000;,
  0.745516;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.752867;0.902897;,
  0.752867;0.129445;,
  1.003210;0.484709;,
  1.003210;1.194315;,
  0.755823;0.000000;,
  1.000000;0.000000;,
  0.755823;1.000000;,
  0.755823;1.000000;,
  0.755823;0.000000;,
  1.000000;1.000000;,
  0.244177;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.244177;0.000000;;
 }
}
