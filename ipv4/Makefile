
all:
	gcc client.c -o ipv4_client 
	gcc server_thread.c -o ipv4_server -lpthread -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast

clean:
	rm ipv4_client ipv4_server
