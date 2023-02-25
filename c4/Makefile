all: hello_client hello_server
hello_client: hello_client.c
	gcc -o hello_client hello_client.c
hello_server: hello_server.c
	gcc -o hello_server hello_server.c
server:
	./hello_server 8899
client:
	./hello_client 127.0.0.1 8899

