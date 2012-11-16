// tcp_server.c

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <linux/in.h>
#include <sys/wait.h>
#include <pthread.h>

#define PORT 8887
#define BACKLOG 2

void * thread_info(void* sc) {
  while (1) {
    process_conn_server(sc);

  }
  close(sc);
  pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
  int ss, sc, opt, closeSignal = 0;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  int err;
  pthread_t thread;

  // 端口重用
  opt = SO_REUSEADDR;
  setsockopt(ss,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

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

  while (1) {
    int addrlen = sizeof(struct sockaddr);
    sc = accept(ss, (struct sockaddr*)&client_addr, &addrlen);
    thread=pthread_create(&thread,NULL,(void*)thread_info, (void*)sc);
  }
  return 0;
}