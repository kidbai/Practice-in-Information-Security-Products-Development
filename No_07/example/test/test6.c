/*
 * =====================================================================================
 *
 *       Filename:  test6.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月06日 22时49分05秒
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

void getpacket(u_char*,struct pcap_pkthdr*, const u_char*);


int main()
{
	char *dev;
	char *net;
	bpf_u_int32 netp;
	bpf_u_int32 maskp;
	pcap_t * device;
	struct pcap_pkthdr;
	struct in_addr addr;
	int id;
	char errbuf[PCAP_ERRBUF_SIZE];


	dev=pcap_lookupdev(errbuf);
	if (NULL==dev)
	{
		fprintf(stderr,"can not open device\n");
		exit(-1);
	
	}

	fprintf(stderr,"device name:%s\n",dev);

	if (-1==pcap_lookupnet(dev,&netp,&maskp,errbuf))
	{
		fprintf(stderr,"can not get the interface%s\n",errbuf);
		exit(-1);
	
	}

	addr.s_addr=netp;
	net=inet_ntoa(addr);
	if(NULL!=net)
	{
		fprintf(stderr,"network addr:%s\n",net);
	
	}

	addr.s_addr=maskp;
	net=inet_ntoa(addr);
	if(NULL!=net)
	{
		fprintf(stderr,"network mask:%s\n",net);
	
	}

	device=pcap_open_live(dev,65535,1,0,errbuf);
	if(NULL==device)
	{
		fprintf(stderr,"can not open the device\n");
		exit(-1);
	
	}

	id=0;
	pcap_loop(device,-1,getpacket,(const u_char*)&id);
	
	pcap_close(device);


}

void getpacket(u_char* user, struct pcap_pkthdr* pkthdr,const u_char* udata)
{
	
	int* id;
	int count;
	int j;

	id=(int*)user;

	fprintf(stderr,"%d\n",++(*id));
	fprintf(stderr,"capture length:%d\n",pkthdr->caplen);
	fprintf(stderr,"packet length:%d\n",pkthdr->len);
	fprintf(stderr,"capture time:%s\n",ctime((const time_t*)&pkthdr->ts.tv_sec));

	for (count=0;count<pkthdr->caplen;count++)
	{
		
		fprintf(stderr,"%2x ",udata[count]);
		if (0==((count+1)%16))
		{
			fprintf(stderr,"| ");
			for(j=15;j>=0;j--)
				fprintf(stderr,"%2c",udata[count-j]);
			fprintf(stderr,"\n");
		}
	
	}

	fprintf(stderr,"\n\n");
}
