/*
	Author: MaximusZhou
	Example:
	$gcc -Wall daytimetcpcli_1_1.c  ../lib/error.c -o  daytimetcpcli_1_1
	$./daytimetcpcli_1_1  127.0.0.1
	Wed Jul  1 15:52:07 2015
	Analyse:
*/

#include "../lib/unp.h"
#include	<time.h>

int main(int argc, char **argv)
{
	int					listenfd, connfd;
	struct sockaddr_in	servaddr;
	char				buff[MAXLINE];
	time_t				ticks;
	char *temp;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(13000);	/* daytime server */

	bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	listen(listenfd, LISTENQ);

	for ( ; ; )
	{
		connfd = accept(listenfd, (SA *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		// write(connfd, buff, strlen(buff));
		for(temp = buff; *temp != '\0'; temp++)
        	write(connfd, temp, 1);

		close(connfd);
	}
}
