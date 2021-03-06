/*
	Author: MaximusZhou
	Example:
	$gcc -Wall daytimetcpcli_1_1.c  ../lib/error.c -o  daytimetcpcli_1_1
	$./daytimetcpcli_1_1  127.0.0.1
	Wed Jul  1 15:52:07 2015
	Analyse:
*/

#include "../lib/unp.h"

int main(int argc, char **argv)
{
	int					sockfd, n;
	char				recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr;
	int count;

	if (argc != 2)
		err_quit("usage: a.out <IPaddress>");

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(13000);	/* daytime server */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
		count++;
	}
	if (n < 0)
		err_sys("read error");
	
	printf("count:%d\n",count);

	exit(0);
}
