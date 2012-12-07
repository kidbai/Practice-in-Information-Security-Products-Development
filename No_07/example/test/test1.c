/*
 * =====================================================================================
 *
 *       Filename:  test1-1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月06日 13时57分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pcap.h>

int main()
{
	char *dev;
	char *net;
	char errbuf[PCAP_ERRBUF_SIZE];
	bpf_u_int32 netp;
	bpf_u_int32 maskp;
	struct in_addr addr;

	dev=NULL;
	net=NULL;
	memset(errbuf,0,PCAP_ERRBUF_SIZE);

	if(NULL==(dev=pcap_lookupdev(errbuf)))
	{
		perror("errbuf\n");
		exit(-1);
	}

	fprintf(stderr,"%s\n",dev);

	if (-1==pcap_lookupnet(dev,&netp,&maskp,errbuf))
	{
		perror("errbuf");
		exit(-1);
	}
	
	addr.s_addr=netp;
	net=inet_ntoa(addr);
	
	if (NULL!=net)
	{
		fprintf(stderr,"Net addr:%s\n",net);
	}

	addr.s_addr=maskp;
	net=inet_ntoa(addr);

	if (NULL!=net)
	{
		fprintf(stderr,"Mask:%s\n",net);
	}

	return 0;


}

