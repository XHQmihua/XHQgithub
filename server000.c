#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define PORT 8000
int main()
{
	int server_sockfd, client_sockfd;
	int server_len, client_len ,buflen;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	pid_t childpid;  //子进程号
	char buf[256];

	unlink("server_socket");
/*
 *server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
 */
 	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*server_address.sun_family = AF_UNIX;
 *strcpy(server_address.sun_path, "server_socket");
 *server_len = sizeof(server_address);
 *bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
 */
 	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(server_sockfd, (struct  sockaddr*)&server_address, 
	sizeof(server_address));
    listen(server_sockfd, 5);

    signal(SIGCHLD, SIG_IGN);

while(1)
{
	//char ch;

	printf("server waiting\n");

	client_len = sizeof(client_address);
	client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);

	if(( childpid = fork() ) == 0)
		{
			close(server_sockfd);   //server关闭与其链接，交给子进程处理
		for(;;)
		{
	    buflen = recv(client_sockfd, buf, sizeof(buf), 0);


		if(buflen== 0)
			break;
		printf("Received line:%s  from IP: %s\n",buf ,inet_ntoa(client_address.sin_addr));
		//sleep(1);
		send(client_sockfd, buf,buflen, 0);
	     }
	    //close(client_sockfd);
	    exit(EXIT_SUCCESS);
	    }

	    else if(childpid < 0)
	    {
	    	printf("fork error...\n");
	    	close(client_sockfd);
	    	exit(EXIT_FAILURE);
	    }
	    close(client_sockfd);
    }
	return 0;



/*****************************************************
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
*/
}