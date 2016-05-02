#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main()
{
int server_sockfd, client_sockfd;
int server_len, client_len;
struct sockaddr_un server_address;
struct sockaddr_un client_address;

unlink("server_socket");
server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

server_address.sun_family = AF_UNIX;
strcpy(server_address.sun_path, "server_socket");
server_len = sizeof(server_address);
bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

listen(server_sockfd, 5);
while(1)
{
char ch;

printf("server waiting\n");

client_len = sizeof(client_address);
client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);


struct hostent *hostinfo;
char **addrs;
if(hostinfo -> h_addrtype != AF_INET) 
{
fprintf(stderr, "not an IP host!\n");
exit(1);
}
addrs = hostinfo -> h_addr_list;
while(*addrs) 
{
printf(" %s", inet_ntoa(*(struct in_addr *)*addrs));
addrs++;
}
printf("\n");
exit(0);


read(client_sockfd, &ch, 1);
ch++;
write(client_sockfd, &ch, 1);
close(client_sockfd);
}
}
