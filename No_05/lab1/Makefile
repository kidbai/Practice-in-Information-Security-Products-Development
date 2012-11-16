all:client server

client:tcp_proccess.c tcp_client.c
	gcc -o client tcp_proccess.c tcp_client.c
server:tcp_proccess.c tcp_server.c
	gcc -o server tcp_proccess.c tcp_server.c -lpthread
clean:
	rm -f client server
