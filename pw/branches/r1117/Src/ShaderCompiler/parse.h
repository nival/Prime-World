#pragma once

class CommandLine
{
public:
  CommandLine()  : isV20(false), isClean(false), isOutDir(false), isShader(false), isNoShare(false) {}
  
  void Print();
  void Parse(int argc, char *argv[ ]);
  
  int GetVersion() const;
  int GetCleanState() const;
  const char* GetOutDir() const;
  const char* GetShaderName() const;

  bool IsNoShare() const { return isNoShare; }

private:
  bool isV20;
  bool isClean;

  string outDir;
  bool isOutDir;

  string shader;
  bool isShader;

  bool isNoShare;
};

