#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* check readable inline function */
__inline int readable_timeout( int fd, int sec,int usec) {
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

int join_multicast_group(int fd,char* group_addr)
{
    struct ip_mreq mreq;
    int ret = 0;
    memset( &mreq, 0, sizeof(mreq));
    mreq.imr_multiaddr.s_addr = inet_addr(group_addr);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    ret = setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    if ( ret < 0 ) {
		fprintf(stdout,"setsockopt(IP_ADD_MEMBERSHIP) failed\n" );
        return -1;
    }
    return 0;
}

int main(int argc, char* argv) 
{
    struct sockaddr_in addr;
    struct ip_mreq mreq;
    int mcast_fd = 0;
    int r = 0, n = 0, addrlen = 0;
    char buf[1024];
    mcast_fd = socket(AF_INET, SOCK_DGRAM,0);
    if ( mcast_fd < 0 ) {
        fprintf(stderr,"error in socket creation\n");
        exit(1);
    }
    fprintf(stdout,"set socket reusable\n");
    set_socket_reusable( mcast_fd );

    fprintf(stdout,"bind socket\n");
    memset( &addr, 0 , sizeof(addr));
    addr.sin_family = AF_INET; 
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8888);
    r = bind( mcast_fd, (struct sockaddr*) &addr, sizeof(addr));
    if ( r < 0 ) {
        fprintf(stderr,"error in socket binding\n");
        exit(1);
    }
    fprintf(stdout,"join multicast group 225.0.0.10\n");
    join_multicast_group(mcast_fd, "225.0.0.10");
    
    fprintf(stdout,"enter loop\n");
    while(1) {
        r = readable_timeout_millisec( mcast_fd, 1000 );
        if ( r > 0 ) {
            memset( buf, 0, 1024);
            n = recvfrom( mcast_fd, buf, 1024, 0, (struct sockaddr*) &addr, &addrlen ); 
            if ( n < 0 ) {
                fprintf(stderr,"receive zero packet in socket binding\n");
                continue;
            }
            fprintf(stdout,"[%d.%d.%d.%d] send [%s]\n",
                    (int)(addr.sin_addr.s_addr&0xFF),
                    (int)((addr.sin_addr.s_addr&0xFF00)>>8),
                    (int)((addr.sin_addr.s_addr&0xFF0000)>>16),
                    (int)((addr.sin_addr.s_addr&0xFF000000)>>24),
                    buf );


        }
    }
}
