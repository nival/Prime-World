
#include <ws2tcpip.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
  struct hostent *h;

  if (argc != 2)
    exit(1);

  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData))
    exit(1);

  if ((h=gethostbyname(argv[1])) == NULL)
    exit(1);

  printf("%s", inet_ntoa(*((struct in_addr *)h->h_addr)));

  return 0;
}
