all: op_client op_server
op_client: echo_client.c
	gcc -o op_client op_client.c
op_server: echo_server.c
	gcc -o op_server op_server.c
server:
	./op_server 8899
client:
	./op_client 127.0.0.1 8899
clean:
	rm -f op_client op_server

