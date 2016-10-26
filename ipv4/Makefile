
all:
	mkdir -p out
	gcc client.c -o out/ipv4_client 
	gcc server_thread.c -o out/ipv4_server -lpthread -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast

clean:
	rm -rf out
