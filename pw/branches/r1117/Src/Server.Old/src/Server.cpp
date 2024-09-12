//============================================================================
// Name        : Server.cpp
// Author      : Vladik
// Version     :
// Copyright   : Driver-Intet
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "sysapi.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "common.h"
#include "ServerApp.h"
#include "CommandFactory.h"

int main(int argc, char **argv)
{
  ServerApp::Init(argc, argv);
  ServerApp::Get()->Run();
  ServerApp::Term();
  return 0;
}

