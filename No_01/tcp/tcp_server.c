// tcp_server.c

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <linux/in.h>
#include <signal.h>

extern void sig_proccess(int signo);

#define PORT 8880
#define BACKLOG 2

int main(int argc, char const *argv[])
{
  int ss, sc;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  int err;
  pid_t pid;

  signal(SIGINT, sig_proccess);
  signal(SIGPIPE, sig_proccess);

  // 建立一个流式套接字
  ss = socket(AF_INET, SOCK_STREAM, 0);
  if (ss < 0) {
    printf("socket error\n");
    return -1;
  }

  // 设置服务器地址
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);

  // 绑定地址结构到套接字描述符
  err = bind(ss, (struct sockaddtr*)&server_addr, sizeof(server_addr));
  if (err < 0) {
    printf("bind error\n");
    return -1;
  }

  // 设置侦听
  err = listen(ss, BACKLOG);
  if (err < 0) {
    printf("listen error\n");
    return -1;
  } else {
    printf("This server is listening on port: %d.\n", PORT);
  }

  // 主循环过程
  for (;;) {
    int addrlen = sizeof(struct sockaddr);

    sc = accept(ss, (struct sockaddr*)&client_addr, &addrlen);
    // 接收客户端连接
    if (sc <0) {
      continue;
    }

    // 建立一个新的进程处理到来的连接
    pid = fork();
    if (pid == 0) {
      close(ss);
      process_conn_server(sc);
    } else {
      close(sc);
    }
  }

  return 0;
}



















