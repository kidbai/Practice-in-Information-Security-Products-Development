
#include <stdio.h>
#include <pcap.h>

  int main (int argc, char* argv[])
  {
          /*the printer running when packet have captured*/
          void printer()
          {
                  printf("A packet is captured!\n");
                  return;
          }

          /*the error code buf of libpcap*/
          char ebuf[PCAP_ERRBUF_SIZE];
          /*create capture handler of libpcap*/
          pcap_t *pd = pcap_open_live ("eth0", 68, 0, 1000, ebuf);

          /*start the loop of capture, loop 5 times, enter printer when capted*/
          pcap_loop (pd, 5, printer, NULL);

          pcap_close (pd);
          return 0;
  }

