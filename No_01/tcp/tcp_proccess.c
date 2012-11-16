// tcp_proccess.c

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

// 服务器对客户端的处理
void process_conn_server(int s) {
  ssize_t size = 0;
  char buffer[1024];

  for (;;) {
    size = read(s, buffer, 1024);
    if (size == 0) {
      return;
    }

    // 构建响应字符，为接收客户端字节的数量
    sprintf(buffer, "%d bytes altogether\n", size);
    write(s, buffer, strlen(buffer)+1);
  }
}

// 客户端的处理过程
void process_conn_client(int s) {
  ssize_t size = 0;
  char buffer[1024];

  for (;;) {
    // 从标准输入中读取数据到缓冲区buffer中
    size = read(0, buffer, 1024);
    if (size > 0) {
      write(s, buffer, size);
      size = read(s, buffer, 1024);
      write(1, buffer, size);
    }
  }
}

void sig_proccess(int signo) {
  printf("Catch a exit signal\n");
  exit(0);
}

void sig_pipe(int sign) {
  printf("Catch a SIGPIPE signal\n");
  // 释放资源
}