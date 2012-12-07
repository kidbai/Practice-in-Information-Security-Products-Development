/*
 * =====================================================================================
 *
 *       Filename:  test4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月06日 22时19分09秒
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
#include <pcap.h>
#include <arpa/inet.h>

int main()
{
	char * dev;
	char * net;
	struct pcap_pkthdr packet;
	pcap_t *device;
	bpf_u_int32 netp;
	bpf_u_int32 maskp;
	char errbuf[PCAP_ERRBUF_SIZE];
	char* upacket;
	struct in_addr addr;


	if (NULL==(dev=pcap_lookupdev(errbuf)))
	{
		perror("errbuf\n");
		exit(-1);
	}

	fprintf(stderr,"device name:%s\n",dev);

	if (-1==pcap_lookupnet(dev,&netp,&maskp,errbuf))
	{
		perror("errbuf\n");
		exit(-1);
	}
	
	addr.s_addr=netp;
	net=inet_ntoa(addr);

	if (NULL!=net)
	{
		fprintf(stderr,"network addr:%s\n",net);
		
	}

	addr.s_addr=maskp;
	net=inet_ntoa(addr);

	
	if (NULL!=net)
	{
		fprintf(stderr,"network addr:%s\n",net);
		
	}
	
	device=pcap_open_live(dev,1518,1,0,errbuf);

	if (NULL==device)
	{
		perror("errbuf\n");
		exit(-1);
	}

	upacket=pcap_next(device,&packet);
	
	if (NULL==upacket)
	{
		fprintf(stderr,"can not get packet\n");
		exit(-1);
	}

	fprintf(stderr,"packet caplen:%d\n",packet.caplen);
	fprintf(stderr,"packet len:%d\n",packet.len);
	fprintf(stderr,"capture time:%s\n",ctime((const time_t*)&packet.ts.tv_sec));

	pcap_close(device);
	
	return 0;
	

}
