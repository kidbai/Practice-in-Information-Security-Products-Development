 // udp_client.c

#include <sys/types.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <strings.h>
#define PORT_SERV 8881
#define BUFF_LEN  256

static void updclie_echo(int s, struct sockaddr *to) {
  char buff[BUFF_LEN];
  struct sockaddr_in from;
  int len = sizeof(*to);

  gets(buff);
  printf("Message:%s\n", buff);
  sendto(s, buff, BUFF_LEN, 0, to, len);
  recvfrom(s, buff, BUFF_LEN, 0, (struct sockaddr*)&from, &len);
}

int main(int argc, char const *argv[])
{
  int s;
  struct sockaddr_in addr_serv, addr_clie;

  s = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&addr_serv, 0, sizeof(addr_serv));
  addr_serv.sin_family = AF_INET;
  addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
  addr_serv.sin_port = htons(PORT_SERV);

  updclie_echo(s, (struct sockaddr*)&addr_serv);

  close(s);
  return 0;
}