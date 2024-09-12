// simpletcptest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int __cdecl run_client(int argc, char **argv);
int __cdecl run_server(int argc, char **argv);


int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    printf("incorrect parameters\n");
    return -1;
  }

  if (strcmp(argv[1], "client") == 0)
  {
    return run_client(argc, argv);
  }
  else
  if (strcmp(argv[1], "server") == 0)
  {
    return run_server(argc, argv);
  }

  return 0;
}

