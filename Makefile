
all:
	make -C ipv6
	make -C ipv4
	make -C udp_multicast

clean:
	make clean -C ipv6 
	make clean -C ipv4
	make clean -C udp_multicast
