// tcp_proccess.c

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 2048

int execute(char* command,char* buf) {
  FILE * fp;
  int count;

  if (NULL==(fp = popen(command,"r"))) {
    perror("creating pipe error\n");
    exit(1);
  }
  
  count = 0 ;

  while(((buf[count] = fgetc(fp))!=EOF)&&count<2047)
  count++;
  buf[count]='\0';

  pclose(fp);
  return count;
}

// 服务器对客户端的处理
int process_conn_server(int s) {
  char cmd[BUF_SIZE];
  char send_buf[BUF_SIZE];
  char recv_buf[BUF_SIZE];

  ssize_t size = 0;

  for (;;) {
    size = read(s, recv_buf, BUF_SIZE);

    if (size == 0) {
      return;
    }
    // PATH
    strcpy(cmd, "/bin/");
    strcat(cmd, recv_buf);
    execute(cmd, send_buf);

    if ('\0' == *send_buf) {
      memset(cmd, 0, sizeof(cmd));
      strcpy(cmd, "/sbin/");
      strcat(cmd, recv_buf);
      execute(cmd, send_buf);
      
      if ('\0' == *send_buf) { 
        memset(cmd, 0, sizeof(cmd));
        strcpy(cmd, "/usr/bin/");
        strcat(cmd, recv_buf);
        execute(cmd, send_buf);
      }
      
      if ('\0' == *send_buf) { 
        memset(cmd, 0, sizeof(cmd));
        strcpy(cmd, "/usr/sbin/");
        strcat(cmd, recv_buf);
        execute(cmd, send_buf);
      }
    }
    if ('\0'==*send_buf)
      sprintf(send_buf,"command is not vaild,check it please\n");

    printf("Client: %s\n%s", recv_buf, send_buf);
    write(s, send_buf, strlen(send_buf)+1);
    bzero(recv_buf,sizeof(send_buf));
  }
  return 0;
}

// 客户端的处理过程
int process_conn_client(int s) {
  char cmd[BUF_SIZE];
  char send_buf[BUF_SIZE];
  char recv_buf[BUF_SIZE];

  ssize_t size = 0;

  for (;;) {
    write(1, "\nTCP>", 6);
    // 从标准输入中读取数据到缓冲区send_buf中
    size = read(0, send_buf, BUF_SIZE);
    if (size > 0) {
      write(s, send_buf, size);
      size = read(s, recv_buf, BUF_SIZE);
      write(1, recv_buf, size);
    }
    // 判断是否退出
    if (strcmp(send_buf, "quit\n") == 0) {
      printf("Bye-bye\n");
      break;
    }
  }
  return 0;
}
