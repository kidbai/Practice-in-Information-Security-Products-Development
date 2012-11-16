#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 8900
#define SIZE 2048

int main()
{
	int mysocket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char send_buf[SIZE];
	char recv_buf[SIZE];
	int length;

	mysocket=-1;
	memset(&server,0, sizeof(server));
	memset(&client,0,sizeof(client));
	memset(send_buf,0,SIZE);
	memset(recv_buf,0,SIZE);
	length=0;


	if (0>(mysocket=socket(AF_INET,SOCK_DGRAM,0)))
	{
		perror("can not create socket\n");
		exit(-1);
	
	}


	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");



	if (0<connect(mysocket,(struct sockaddr*)&server,sizeof(server)))
	{
		perror("connect error\n");
		close(mysocket);
		exit(-1);
	
	}
	
	fgets(send_buf,sizeof(send_buf),stdin);

	if(0> (length=send(mysocket,send_buf,strlen(send_buf),0)))
	{
		perror("send data error\n");
		close(mysocket);
		exit(-1);
	
	}

	if (0>(length=recv(mysocket,recv_buf,sizeof(recv_buf),0)))
	{
		perror("can not recv data\n");
		close(mysocket);
		exit(-1);
	
	}

	fprintf(stderr,"the data receive from server is %s\n",recv_buf);

	close(recv_buf);
	exit(-1);
}
