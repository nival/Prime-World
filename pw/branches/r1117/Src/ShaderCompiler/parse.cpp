#include "stdafx.h"

#include "parse.h"

namespace
{
  const string noshare = "--noshare";
  const string version = "--sm20";
  const string clean   = "--clean";
  const string outputDirPrefix   = "--out";
  const string shaderNamePrefix  = "--name";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandLine::Print()
{
  printf("Wrong format. Use: <config filename> [%s] [%s] [%s] [%s<out path>] [%s<single build shader name>]\n", 
    noshare.c_str(), version.c_str(), clean.c_str(), outputDirPrefix.c_str(), shaderNamePrefix.c_str());
}


void CommandLine::Parse(int argc, char *argv[ ])
{
  // parse noshare mode
  for (int i = 2; i < argc; ++i)
  {
    if (0 == strcmp(argv[i], noshare.c_str()))
    {
      isNoShare = true;
      break;
    }
  }

  // parse version
  for (int i = 2; i < argc; ++i)
  {
    if (0 == strcmp(argv[i], version.c_str()))
    {
      isV20 = true;
      break;
    }
  }

  // parse clean build
  for (int i = 2; i < argc; ++i)
  {
    if (0 == strcmp(argv[i], clean.c_str()))
    {
      isClean = true;
      break;
    }
  }

  // parse output dir
  for (int i = 2; i < argc; ++i)
  {
    char *dir;
    
    dir = strstr(argv[i], outputDirPrefix.c_str());
    if (0 != dir)
    {
      isOutDir = true;
      outDir = dir + outputDirPrefix.length();
      break;
    }
  }

  // parse shader name
  for (int i = 2; i < argc; ++i)
  {
    char *name;

    name = strstr(argv[i], shaderNamePrefix.c_str());
    if (0 != name)
    {
      isShader = true;
      shader = name + shaderNamePrefix.length();
      break;
    }
  }
}

int CommandLine::GetVersion() const
{
  if (isV20)
    return 1;

  return 0;
}

int CommandLine::GetCleanState() const
{
  if (isClean)
    return 1;

  return 0;
}

const char* CommandLine::GetOutDir() const
{
  if (isOutDir)
    return outDir.c_str();

  return 0;
}

const char* CommandLine::GetShaderName() const
{
  if (isShader)
    return shader.c_str();

  return 0;
}


