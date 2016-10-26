
all:
	mkdir -p out
	gcc client6.c -o out/ipv6_client 
	gcc server6thread.c -o out/ipv6_server -lpthread -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast

clean:
	rm -rf out 
