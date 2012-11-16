// tcp_client.c

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <linux/in.h>

static int s;

#define PORT 8887

int main(int argc, char const *argv[])
{
  struct sockaddr_in server_addr;
  int err;

  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    printf("socket error\n");
    return -1;
  }

  // 设置服务器地址
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);

  inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
  // 将用户输入的字符串类型的IP地址转为整型
  connect(s, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));
  process_conn_client(s);
  close(s);

  return 0;
}