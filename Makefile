
all:
	gcc client6.c -o ipv6_client 
	gcc server6thread.c -o ipv6_server -lpthread -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast
	make -C udp_multicast

clean:
	rm ipv6_client ipv6_server
	make clean -C udp_multicast
