// Some statistics on how these constants are used you can find here:

// ==================================================================================
// Global system samplers
// ==================================================================================

// PS samplers
#define WARFOGSAMPLERINDEX           s10
#define GLOBALENVIROMENTSAMPLERINDEX s12
#define DISTORTIONBUFFERSAMPLERINDEX s13
#define DISTORTIONNOISESAMPLERINDEX  s14

// Terrain: 4 consecutive samplers
#define TERRAIN_DIFFUSESAMPLER0      s0
#define TERRAIN_DIFFUSESAMPLER1      s1
#define TERRAIN_DIFFUSESAMPLER2      s2
#define TERRAIN_DIFFUSESAMPLER3      s3

// ==================================================================================
// Material specific samplers
// ==================================================================================

/*
* Dif = Diffuse
* Spc = Specular
* Nrm = Normal map
* Drk = Dark map
* WGr = Water gradient

| s0| BWeather:Dif | OldTerr:Dif | Basic:Dif | Terr:Dif0 |
| s1| BWeather:Dif | OldTerr:Dif | Basic:Nrm | Terr:Dif1 |
| s2| BWeather:Dif | OldTerr:Dif | Basic:Drk | Terr:Dif2 |
| s3| BWeather:Nrm | OldTerr:Nrm | Basic:Spc | Terr:Dif3 |
| s4| BWeather:Nrm | OldTerr:Nrm | 
| s5| BWeather:Nrm | OldTerr:Nrm | Basic:WGr |
| s6| BWeather:Spc | OldTerr:Spc |
| s7| BWeather:Spc | OldTerr:Spc |
| s8| BWeather:Spc | OldTerr:Spc |
| s9| BWeather:Drk | OldTerr:Drk |

|s10| Water Reflection |
|s11| Shadow Map |
|s12| Global Environment |
|s13| Old Terrain holes |
|s14|  |
|s15| Old Terrain type sampler index |

*/

// ==================================================================================
// Global constants
// ==================================================================================

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Vertex Shader

// Per object locals (common semantic)
#define WORLD            c0   // 4 regs

// Per frame zone (ApplySceneConstants...)
#define VIEW             c4   // 4 regs
#define VIEWPROJECTION   c8   // 4 regs
#define PROJECTION       c12  // 4 regs
#define EYEPOSITION      c16
#define CAMERADIRECTION  c17
#define RENDERTIME       c18
#define WARFOGMAPPING    c19  // !!! set only once and forever on VisibilityMapClient::OnCreate !!!

// Custom vertex shader locals (!!! contiguous constant range)
#define VSHADER_LOCALCONST0   c20
#define VSHADER_LOCALCONST1   c21
#define VSHADER_LOCALCONST2   c22
#define VSHADER_LOCALCONST3   c23
#define VSHADER_LOCALCONST4   c24
#define VSHADER_LOCALCONST5   c25
#define VSHADER_LOCALCONST6   c26
#define VSHADER_LOCALCONST7   c27
#define VSHADER_LOCALCONST8   c28
#define VSHADER_LOCALCONST9   c29
#define VSHADER_LOCALCONST10  c30
#define VSHADER_LOCALCONST11  c31

// SkeletalMesh local bones array
#define BONES  c24    // this value can't be much higher (say, c27), due to problems with Wine
#define MAX_BONES 70

//
#define VSHADER_NIGHT_PARAMS  c234
#define PSHADER_NIGHT_PARAMS  c220

// Instancing material
#define INSTANCE_DATA            c20
#define INSTANCING_AMBIENTCOLOR  c0
#define INSTANCING_DIFFUSE_COEFF c1
#define INSTANCING_COLOR_MIN     c2
#define INSTANCING_COLOR_MAX     c3
#define MAX_INSTANCES_COUNT      19


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ParticleFX
#define PFX_MAX_INSTANCES  47


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pixel Shader

// Per frame zone
#define AMBIENTCOLOR        c0
#define LIGHT1DIRECTION     c1
#define LIGHT1DIFFUSECOLOR  c2
#define LIGHT2DIRECTION     c3
#define LIGHT2DIFFUSECOLOR  c4
#define WARFOGCOLOR         c5

// Per object locals (BasicMaterial, BasicFXMaterial, ParticleFXMaterial)
#define OPACITY_AND_OTHERS  c6
#define BASICMAT_AMBIENT    c7
#define BASICMAT_DIFFUSE1   c8
#define BASICMAT_DIFFUSE2   c9
#define SCREEN_TO_TEXTURE   c10
#define DISTORTION_PARAMS1  c11

// Sampler modifiers (Sampler::Bind() for NDb::SamplerEx)
#define SAMPLER_CONSTANTS_BEGIN c20
#define SAMPLER0_MUL  c20
#define SAMPLER0_ADD  c21
#define SAMPLER1_MUL  c22
#define SAMPLER1_ADD  c23
#define SAMPLER2_MUL  c24
#define SAMPLER2_ADD  c25
#define SAMPLER3_MUL  c26
#define SAMPLER3_ADD  c27
#define SAMPLER4_MUL  c28
#define SAMPLER4_ADD  c29

// Custom pixel shader locals (!!! contiguous constant range)
#define PSHADER_LOCALCONST0   c20
#define PSHADER_LOCALCONST1   c21
#define PSHADER_LOCALCONST2   c22
#define PSHADER_LOCALCONST3   c23
#define PSHADER_LOCALCONST4   c24
#define PSHADER_LOCALCONST5   c25
#define PSHADER_LOCALCONST6   c26
#define PSHADER_LOCALCONST7   c27
#define PSHADER_LOCALCONST8   c28
#define PSHADER_LOCALCONST9   c29

#define PSHADER_SHCONSTS      c12

// Terrain global
#define TERRAIN_AMBIENT      c10
#define TERRAIN_DIFFUSE1     c11
#define TERRAIN_DIFFUSE2     c12

// Water global (10 regs)
#define WATER_PARAMS0        c10
#define WATER_VIEWINV_Z      c11
#define WATER_REFLECTION_MTX c12  // 4 regs
#define WATER_REFRACTION_MTX c16  // 4 regs

// Lighting (BasicMaterial)
#define POINTLIGHTSCOUNT 4
#define POINTLIGHTSDATA      c10  // 2*POINTLIGHTSCOUNT regs
#define POINTLIGHTFACTOR     c18  // (POINTLIGHTSDATA + 2 * POINTLIGHTSCOUNT)

// Bloom constant (BasicMaterial, BasicFXMaterial)
#define BLOOM_ENCODING_THRESHOLD 0.75f

// Post-processing constants

#define NATURE_TYPES_COUNT 3

// enum PivotParams {
#define PP_IN_MIN  0
#define PP_IN_MAX  1
#define PP_OUT_MIN 2
#define PP_OUT_MAX 3
#define PP_GAMMA   4
#define PP_COLOR   5
#define PP_PIVOT_PARAMS_COUNT 6
//};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constants for C++

#ifndef HLSL
#pragma once

static const unsigned int s0 = 257;

static const unsigned int s7 = 7;
static const unsigned int s8 = 8;
static const unsigned int s9 = 9;
static const unsigned int s10 = 10;
static const unsigned int s11 = 11;
static const unsigned int s12 = 12;
static const unsigned int s13 = 13;
static const unsigned int s14 = 14;
static const unsigned int s15 = 15;

static const unsigned int c0 = 0;
static const unsigned int c1 = 1;
static const unsigned int c2 = 2;
static const unsigned int c3 = 3;
static const unsigned int c4 = 4;
static const unsigned int c5 = 5;
static const unsigned int c6 = 6;
static const unsigned int c7 = 7;
static const unsigned int c8 = 8;
static const unsigned int c9 = 9;
static const unsigned int c10 = 10;
static const unsigned int c11 = 11;
static const unsigned int c12 = 12;
static const unsigned int c13 = 13;
static const unsigned int c14 = 14;
static const unsigned int c15 = 15;
static const unsigned int c16 = 16;
static const unsigned int c17 = 17;
static const unsigned int c18 = 18;
static const unsigned int c19 = 19;
static const unsigned int c20 = 20;
static const unsigned int c21 = 21;
static const unsigned int c22 = 22;
static const unsigned int c23 = 23;
static const unsigned int c24 = 24;
static const unsigned int c25 = 25;
static const unsigned int c26 = 26;
static const unsigned int c27 = 27;
static const unsigned int c28 = 28;
static const unsigned int c29 = 29;
static const unsigned int c30 = 30;
static const unsigned int c31 = 31;
static const unsigned int c32 = 32;
static const unsigned int c33 = 33;
static const unsigned int c34 = 34;
static const unsigned int c35 = 35;
static const unsigned int c36 = 36;
static const unsigned int c37 = 37;
static const unsigned int c38 = 38;
static const unsigned int c39 = 39;
static const unsigned int c40 = 40;
static const unsigned int c41 = 41;
static const unsigned int c42 = 42;
static const unsigned int c43 = 43;
static const unsigned int c44 = 44;
static const unsigned int c45 = 45;
static const unsigned int c46 = 46;
static const unsigned int c47 = 47;
static const unsigned int c48 = 48;
static const unsigned int c49 = 49;
static const unsigned int c50 = 50;
static const unsigned int c51 = 51;
static const unsigned int c52 = 52;
static const unsigned int c53 = 53;
static const unsigned int c54 = 54;
static const unsigned int c55 = 55;
static const unsigned int c56 = 56;
static const unsigned int c57 = 57;
static const unsigned int c58 = 58;
static const unsigned int c59 = 59;
static const unsigned int c60 = 60;
static const unsigned int c61 = 61;
static const unsigned int c62 = 62;
static const unsigned int c63 = 63;
static const unsigned int c64 = 64;
static const unsigned int c65 = 65;
static const unsigned int c66 = 66;
static const unsigned int c67 = 67;
static const unsigned int c68 = 68;
static const unsigned int c69 = 69;
static const unsigned int c70 = 70;
static const unsigned int c71 = 71;
static const unsigned int c72 = 72;
static const unsigned int c73 = 73;
static const unsigned int c74 = 74;
static const unsigned int c75 = 75;
static const unsigned int c76 = 76;
static const unsigned int c77 = 77;
static const unsigned int c78 = 78;
static const unsigned int c79 = 79;
static const unsigned int c80 = 80;
static const unsigned int c81 = 81;
static const unsigned int c82 = 82;
static const unsigned int c83 = 83;
static const unsigned int c84 = 84;
static const unsigned int c85 = 85;
static const unsigned int c86 = 86;
static const unsigned int c87 = 87;
static const unsigned int c88 = 88;
static const unsigned int c89 = 89;
static const unsigned int c90 = 90;
static const unsigned int c91 = 91;
static const unsigned int c92 = 92;
static const unsigned int c93 = 93;
static const unsigned int c94 = 94;
static const unsigned int c95 = 95;
static const unsigned int c96 = 96;
static const unsigned int c97 = 97;
static const unsigned int c98 = 98;
static const unsigned int c99 = 99;
static const unsigned int c100 = 100;
static const unsigned int c101 = 101;
static const unsigned int c102 = 102;
static const unsigned int c103 = 103;
static const unsigned int c104 = 104;
static const unsigned int c105 = 105;
static const unsigned int c106 = 106;
static const unsigned int c107 = 107;
static const unsigned int c108 = 108;
static const unsigned int c109 = 109;
static const unsigned int c110 = 110;
static const unsigned int c111 = 111;
static const unsigned int c112 = 112;
static const unsigned int c113 = 113;
static const unsigned int c114 = 114;
static const unsigned int c115 = 115;
static const unsigned int c116 = 116;
static const unsigned int c117 = 117;
static const unsigned int c118 = 118;
static const unsigned int c119 = 119;
static const unsigned int c120 = 120;
static const unsigned int c121 = 121;
static const unsigned int c122 = 122;
static const unsigned int c123 = 123;
static const unsigned int c124 = 124;
static const unsigned int c125 = 125;
static const unsigned int c126 = 126;
static const unsigned int c127 = 127;
static const unsigned int c128 = 128;
static const unsigned int c129 = 129;
static const unsigned int c130 = 130;
static const unsigned int c131 = 131;
static const unsigned int c132 = 132;
static const unsigned int c133 = 133;
static const unsigned int c134 = 134;
static const unsigned int c135 = 135;
static const unsigned int c136 = 136;
static const unsigned int c137 = 137;
static const unsigned int c138 = 138;
static const unsigned int c139 = 139;
static const unsigned int c140 = 140;
static const unsigned int c141 = 141;
static const unsigned int c142 = 142;
static const unsigned int c143 = 143;
static const unsigned int c144 = 144;
static const unsigned int c145 = 145;
static const unsigned int c146 = 146;
static const unsigned int c147 = 147;
static const unsigned int c148 = 148;
static const unsigned int c149 = 149;
static const unsigned int c150 = 150;
static const unsigned int c151 = 151;
static const unsigned int c152 = 152;
static const unsigned int c153 = 153;
static const unsigned int c154 = 154;
static const unsigned int c155 = 155;
static const unsigned int c156 = 156;
static const unsigned int c157 = 157;
static const unsigned int c158 = 158;
static const unsigned int c159 = 159;
static const unsigned int c160 = 160;
static const unsigned int c161 = 161;
static const unsigned int c162 = 162;
static const unsigned int c163 = 163;
static const unsigned int c164 = 164;
static const unsigned int c165 = 165;
static const unsigned int c166 = 166;
static const unsigned int c167 = 167;
static const unsigned int c168 = 168;
static const unsigned int c169 = 169;
static const unsigned int c170 = 170;
static const unsigned int c171 = 171;
static const unsigned int c172 = 172;
static const unsigned int c173 = 173;
static const unsigned int c174 = 174;
static const unsigned int c175 = 175;
static const unsigned int c176 = 176;
static const unsigned int c177 = 177;
static const unsigned int c178 = 178;
static const unsigned int c179 = 179;
static const unsigned int c180 = 180;
static const unsigned int c181 = 181;
static const unsigned int c182 = 182;
static const unsigned int c183 = 183;
static const unsigned int c184 = 184;
static const unsigned int c185 = 185;
static const unsigned int c186 = 186;
static const unsigned int c187 = 187;
static const unsigned int c188 = 188;
static const unsigned int c189 = 189;
static const unsigned int c190 = 190;
static const unsigned int c191 = 191;
static const unsigned int c192 = 192;
static const unsigned int c193 = 193;
static const unsigned int c194 = 194;
static const unsigned int c195 = 195;
static const unsigned int c196 = 196;
static const unsigned int c197 = 197;
static const unsigned int c198 = 198;
static const unsigned int c199 = 199;
static const unsigned int c200 = 200;
static const unsigned int c201 = 201;
static const unsigned int c202 = 202;
static const unsigned int c203 = 203;
static const unsigned int c204 = 204;
static const unsigned int c205 = 205;
static const unsigned int c206 = 206;
static const unsigned int c207 = 207;
static const unsigned int c208 = 208;
static const unsigned int c209 = 209;
static const unsigned int c210 = 210;
static const unsigned int c211 = 211;
static const unsigned int c212 = 212;
static const unsigned int c213 = 213;
static const unsigned int c214 = 214;
static const unsigned int c215 = 215;
static const unsigned int c216 = 216;
static const unsigned int c217 = 217;
static const unsigned int c218 = 218;
static const unsigned int c219 = 219;
static const unsigned int c220 = 220;
static const unsigned int c221 = 221;
static const unsigned int c222 = 222;
static const unsigned int c223 = 223;
static const unsigned int c224 = 224;
static const unsigned int c225 = 225;
static const unsigned int c226 = 226;
static const unsigned int c227 = 227;
static const unsigned int c228 = 228;
static const unsigned int c229 = 229;
static const unsigned int c230 = 230;
static const unsigned int c231 = 231;
static const unsigned int c232 = 232;
static const unsigned int c233 = 233;
static const unsigned int c234 = 234;
static const unsigned int c235 = 235;
static const unsigned int c236 = 236;
static const unsigned int c237 = 237;
static const unsigned int c238 = 238;
static const unsigned int c239 = 239;
static const unsigned int c240 = 240;
static const unsigned int c241 = 241;
static const unsigned int c242 = 242;
static const unsigned int c243 = 243;
static const unsigned int c244 = 244;
static const unsigned int c245 = 245;
static const unsigned int c246 = 246;
static const unsigned int c247 = 247;
static const unsigned int c248 = 248;
static const unsigned int c249 = 249;
static const unsigned int c250 = 250;
static const unsigned int c251 = 251;
static const unsigned int c252 = 252;
static const unsigned int c253 = 253;
static const unsigned int c254 = 254;
static const unsigned int c255 = 255;
#endif

