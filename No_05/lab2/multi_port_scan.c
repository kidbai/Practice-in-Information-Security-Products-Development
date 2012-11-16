#include <stdlib.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <netdb.h> 
#include <unistd.h> 
#include <string.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#define THREAD_NUM 100
#define SEG_LEN 655
#define MAX_PORT 65535

typedef struct port_seg {   
  int ip;
  unsigned min_port;
  unsigned max_port;
}port_seg; 

void *scan(void *arg) {   
  struct sockaddr_in server;
  int i, sockfd, ret, opt;

  port_seg *port = (port_seg *)arg;
  memset(&server, 0, sizeof(struct sockaddr_in));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = port->ip; 

  opt = SO_REUSEADDR;
  setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

  for (i = port->min_port; i <= port->max_port; i++) {   
    server.sin_port = htons(i);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {   
      perror("can not create socket\n");
      exit(1);
    } 

    if ((ret = connect(sockfd, (struct sockaddr *)&server, sizeof(struct sockaddr))) == 0) {   
      struct servent *sp;
      sp = getservbyport(htons(i),"tcp");
      printf("%5d %-20s\n", i, (sp == NULL)?"unknown":sp->s_name);
    }
    close(sockfd);
  }
  pthread_exit(0);
}   

int main(int argc , char *argv[]) {
  int j, i;
  pthread_t *thread;
  thread = (pthread_t *)malloc(THREAD_NUM * sizeof(pthread_t));  
  for(j = 1; j < argc; j++) {   
    for(i = 0; i < THREAD_NUM; i++) {   
      port_seg *port = (port_seg *)malloc(sizeof(port_seg));
      port->ip = inet_addr(argv[j]);
      port->min_port = i * SEG_LEN + 1;
      if (i == (THREAD_NUM - 1))   
        port->max_port = MAX_PORT;
      else 
        port->max_port = port->min_port + SEG_LEN - 1;
      if (pthread_create(&thread[i], NULL, scan, (void *)port) != 0) {   
        perror("pthread_creat fail!");
        free(thread);
        exit(-2);
      }   
    }   
  }
  sleep(1);
  return 0;
}