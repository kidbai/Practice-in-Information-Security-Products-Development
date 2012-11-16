#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int check_port(int port, char* addr) {
  struct sockaddr_in server_addr;
  int stat = 1, ret;
  int s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    perror("socket error\n");
    return -1;
  }

  // 设置服务器地址
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(addr);
  server_addr.sin_port = htons(port);

  // 将用户输入的字符串类型的IP地址转为整型
  if (0 > (ret = connect(s, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)))) {
    stat = 0;
  }
  close(s);
  return stat;
}

int main(int argc, char *argv[])
{
  struct servent *server_pointer;
  int start_port = atoi(argv[1]);
  int end_port = atoi(argv[2]);
  int port;

  if (4 != argc) {
    perror("Invalid input.\n");
    exit(1);
  }

  for (port = start_port; port <= end_port; ++port) {
    if (check_port(port, argv[3])) {
      server_pointer = getservbyport(htons(port), NULL);
      if (server_pointer != NULL) {
        printf("\t%d\t%s\n", port, server_pointer->s_name);
      } else {
        printf("\t%d\tunknow\n", port);
      }
    }
  }

  return 0;
}