all:server client

server:udp_server.c
	gcc -o server udp_server.c
client:udp_client.c
	gcc -o client udp_client.c
clean:
	rm -f server client