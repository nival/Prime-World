#pragma once
#include <d3dx9shader.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IXmlSaver;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct UberShaderPin
{
  string pinName;   // Pin name
  int maxPinValue;  // Assume pins are numbered from 0
  int pinMultiplier;

	int operator&( IXmlSaver &saver );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct UberShaderDesc
{
  unsigned int GetTotalCount() const;

  string shaderName;          // Name of material == name of user shader on disk. Ex: "BasicMaterial"
	vector<UberShaderPin> pins; // Vector of pins for the shader

	int operator&( IXmlSaver &saver );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UberShaderFileInfo
{
public:
  UberShaderFileInfo(UberShaderDesc& _shader) : shader(_shader), needWrite(true), similar(0) {}
  void Reset();
  void Read( int isV20 = 0 );
  void Build( LPD3DXBUFFER *matrix );
  void Write( int isV20 = 0 );
  void SetDir(string &dir) {directory = dir;}
  int GetIdx (int code) { return codes[code].idx; }
  int GetCRC (int code) { return codes[code].CRC; }

private:
  UberShaderDesc& shader;
  UberShaderFileInfo &operator=(UberShaderFileInfo const &);

private:
  struct CodeInfo
  {
    int idx;
    unsigned int CRC;
  };

  int similar;
  bool needWrite;
  string directory;
  vector<CodeInfo> codes;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LoadShadersCollection( const string& fileName, vector<UberShaderDesc>* pShaders );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////