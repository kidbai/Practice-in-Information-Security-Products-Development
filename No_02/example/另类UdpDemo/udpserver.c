#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 8900
#define SIZE 2048



int main()
{
	/*definition*/
	int mysocket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char send_buf[SIZE];
	char recv_buf[SIZE];
	int length;
	int len;


   /*initialize*/
	mysocket=-1;
	memset(&server,0,sizeof(server));
	memset(&client,0,sizeof(client));
	memset(send_buf,0,SIZE);
	memset(recv_buf,0,SIZE);
	length=0;
	len=0;

	
	/*get socket*/

	if (0>(mysocket=socket(AF_INET,SOCK_DGRAM,0)))
	{
		perror("create socket error\n");
		exit(-1);
	
	}

	/*bind*/
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	

	if (0>bind(mysocket,(struct sockadrr *)&server,sizeof(server)))
	{
		perror("bind error\n");
		close(mysocket);
		exit(-1);
	
	}

	len=sizeof(client);
	while(1)
	{
	   memset(send_buf,0,SIZE);
	   memset(recv_buf,0,SIZE);

	   if (0>(length=recvfrom(mysocket,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&client,&len)))
	   {
			perror("read data error\n");
			close(mysocket);
			exit(-1);
	   
	   }
	   send_buf[length]='\0';
	   
	   fprintf(stderr,"the client message is %s\n",recv_buf);

	
	   snprintf(send_buf,SIZE,"hello, server welcome you");
	   
	   if (0>(length=sendto(mysocket,send_buf,strlen(send_buf),0,(struct sockaddr*)&client,len)))
	   {
			perror("send data error\n");
			close(mysocket);
			exit(-1);
	   }
	
	}
	close(mysocket);
	return 0;


}
