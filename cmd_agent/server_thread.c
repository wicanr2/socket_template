#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *connection_handler(void *);

/* check readable inline function */
int readable_timeout( int fd, int sec,int usec) {
	fd_set rset;
	struct timeval tv;
	FD_ZERO(&rset);	
	FD_SET(fd, &rset);
	tv.tv_sec = sec;
	tv.tv_usec = usec;
	return ( select(fd+1, &rset, NULL, NULL, &tv) );
}

/* check readable when timeout in mircoseconds usec */
int readable_timeout_usec( int fd, int usec) {
	return readable_timeout( fd, 0, usec );
}

/* check readable when timeout in mircoseconds usec */
int readable_timeout_millisec( int fd, int millisec) {
	return readable_timeout( fd, 0, millisec * 1000 );
}

/* check readable when timeout in seconds usec */
int readable_timeout_sec( int fd, int sec) {
	return readable_timeout( fd, sec, 0 );
}
/*
    set socket option reusable 
*/
int set_socket_reusable(int fd)
{
	int addr_reuse_flag = 1;
	int ret = 0;
	ret = setsockopt( fd , SOL_SOCKET, SO_REUSEADDR, 
		              (char*)&addr_reuse_flag, sizeof(addr_reuse_flag));
	if ( ret < 0 ) {
		fprintf(stdout,"setsockopt(SO_REUSEADDR) failed\n" );
		return -1;
	}
	return 0;
}

int main()
{
    int sockfd;
    //server sockaddr_in saddr;
    struct sockaddr_in saddr;
    //
    char client_addr_ip[100];
    char interface_ip[64] = "127.0.0.1";

    fprintf(stdout,"Server Start");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    set_socket_reusable(sockfd);

    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(17290);
    //saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_pton(AF_INET, interface_ip, &saddr.sin_addr);

    bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));

    listen(sockfd, 20);

    while(1)
    {
        //int clientfd;
        struct sockaddr_in client_addr;
        int addrlen = sizeof(client_addr);
        int clientfd = accept(sockfd, (struct sockaddr *) &client_addr, &addrlen);
        pthread_t tid;
        inet_ntop(AF_INET, &(client_addr.sin_addr), client_addr_ip, 100);
        fprintf(stdout,"Incoming connection from client having IPv6 address: %s\n", client_addr_ip);

        if( pthread_create( &tid , NULL ,  connection_handler , (void*) clientfd) < 0)
        {
            fprintf(stderr,"could not create thread");
            return 1;
        }

    }

    close(sockfd);
    return 0;
}

void *connection_handler(void *clientfd) {
    int client = (int)clientfd;
    char buffer[1024];
    int num = 0, r = 0;

    fprintf(stdout,"sockFd: %d\n",client);

    bzero(buffer, 1024);
    do {
        num = readable_timeout_millisec( client, 1000 );
        if ( num == 0 ) continue;
        r = recv(client, buffer, sizeof(buffer), 0);
        printf("recv data[%d] %s\n", r, buffer);
        if ( r > 0 ) break;
    } while (1);

    fprintf(stdout,"execute cmd %s\n", buffer);
    system(buffer);
    send(client, "OK", 2, 0);
    close(client);
    fprintf(stdout,"close sockFd: %d\n",client);
    pthread_exit(0);
    return 0;
}
