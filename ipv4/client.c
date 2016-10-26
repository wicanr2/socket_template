#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
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

int main(int argc, char *argv[])
{
    int sockfd = 0;
    int num = 0, r = 0;
    struct sockaddr_in6 dest;
    char message[128];
    char buffer[128];
    char destIP[128] = "::1";
    memset(message, 0, sizeof(message));
    strcpy(message, argv[1]);

    /* create socket */
    sockfd = socket(AF_INET6, SOCK_STREAM, 0);

    /* initialize value in dest */
    bzero(&dest, sizeof(dest));
    dest.sin6_flowinfo = 0;
    dest.sin6_family = AF_INET6;
    dest.sin6_port = htons(8889);
    inet_pton(AF_INET6, destIP, &dest.sin6_addr);

    while(1) {
        r=connect(sockfd, (struct sockaddr*)&dest, sizeof(dest));
        if ( r == 0 ) break;
        //printf("errono : %d\n", errno);
        if ( errno == ENETUNREACH ) {
            printf("destination %s is unreachable\n", destIP);
            exit(1);
        }
        if ( errno == ECONNREFUSED ) {
            printf("no one listening on the remote address %s\n", destIP);
            exit(1);
        }
    }
    do {
        r= send(sockfd, message, strlen(message), 0);
        printf("send message %s[%d] to server\n", message, r);
        bzero(buffer, 128);
        num = readable_timeout_millisec(sockfd, 1000);
        if ( num == 0 ) continue;
        r = recv(sockfd, buffer, sizeof(buffer), 0);
        printf("recv message [%d] %s to server\n", r, buffer);
        if ( r > 0 ) break;
    } while (1);
    close(sockfd);
    printf("close socket\n");
    
	return 0;
}
