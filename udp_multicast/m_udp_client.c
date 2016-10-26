#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


int main(int argc, char* argv[] )
{
    char m_group[64];
    char message[255];
    int m_port = 0, i =0;
    int mcast_fd = 0, r = 0;
    struct sockaddr_in addr;
    if ( argc < 4 ) {
        fprintf(stdout,"%s [multicast_group] [port] [message]\n", argv[0]);
        exit(1);
    }

    memset( m_group, 0, 64); strncpy( m_group, argv[1], 64 );
    m_port = atoi(argv[2]);
    memset( message, 0, 255); strncpy( message, argv[3], 255 );
    
    mcast_fd = socket( AF_INET, SOCK_DGRAM,0 ) ;
    if ( mcast_fd < 0 ) {
        fprintf(stderr,"error in socket creation\n");
        exit(1);
    }

    memset( &addr, 0 , sizeof(addr));
    addr.sin_family = AF_INET; 
    addr.sin_addr.s_addr = inet_addr(m_group);
    addr.sin_port = htons(m_port);

    for( i = 0; i < 10 ; i++ ) {
        r = sendto( mcast_fd, message, strlen(message), 0, (struct sockaddr *)&addr, sizeof(addr));
        if ( r < 0 ) {
            fprintf(stderr,"send message [%s] to %s error\n", message, m_group);
            exit(1);
        }
        usleep(200000); //sleep 200ms
    }
    sleep(1);
    memset(message, 0, sizeof(message)); strcpy(message,"good bye");
    r = sendto( mcast_fd, message, strlen(message), 0, (struct sockaddr *)&addr, sizeof(addr));
    if ( r < 0 ) {
        fprintf(stderr,"send message [%s] to %s error\n", message, m_group);
        exit(1);
    }
    close( mcast_fd );

    return 0;
}
