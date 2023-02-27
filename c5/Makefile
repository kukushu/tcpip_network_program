all: echo_client echo_server
echo_client: echo_client.c
	gcc -o echo_client echo_client.c
echo_server: echo_server.c
	gcc -o echo_server echo_server.c
server:
	./echo_server 8899
client:
	./echo_client 127.0.0.1 8899

