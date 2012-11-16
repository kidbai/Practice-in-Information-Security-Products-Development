// udp_server.c

#include <sys/types.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <strings.h>
#define PORT_SERV 8881
#define BUFF_LEN  256

static void udpserv_echo(int s, struct sockaddr *client) {
  int n, len;
  char buff[BUFF_LEN];
  
  for (;;) {
    printf("This server is listening on port: %d.\n", PORT_SERV);
    len = sizeof(*client);
    n = recvfrom(s, buff, BUFF_LEN, 0, client, &len);

    printf("The message form client:%s\n", buff);
    sprintf(buff,"Hello, client.\n");

    sendto(s, buff, n, 0, client, len);
  }
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

  bind(s, (struct sockaddr*)&addr_serv, sizeof(addr_serv));

  udpserv_echo(s, (struct sockaddr*)&addr_clie);

  return 0;
}