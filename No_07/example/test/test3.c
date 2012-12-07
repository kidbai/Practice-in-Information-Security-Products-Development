/*
 * =====================================================================================
 *
 *       Filename:  test3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月06日 14时56分55秒
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

int main()  
{  
    //find device  
    pcap_if_t *alldevs;
	pcap_if_t *pdev;
	char buf[PCAP_ERRBUF_SIZE];
    pcap_findalldevs(&alldevs, buf);  
      
    int i=0;  
    for (pdev = alldevs; pdev; pdev=pdev->next)  
        printf("#%d: %s %s\n", ++i, pdev->name, pdev->description? pdev->description:"");  
          
    pcap_freealldevs(alldevs);  
    return 0;  
}  
