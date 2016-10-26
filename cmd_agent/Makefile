
all:
	mkdir -p out
	gcc client.c -o out/cmd_agent_c
	gcc server_thread.c -o out/cmd_agent_s -lpthread -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast

clean:
	rm -rf out
