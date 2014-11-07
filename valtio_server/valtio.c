#include <stdio.h>
#include <stdlib.h>

#include "blktrace.h"

int main()
{
	printf("실행됩미다.");
	return 0;
}

void asdfasdf() {
	
	int listenfd; /* listening socket */
	//int connfd; /* connection socket */
	int portno; /* port to listen on */
	int clientlen; /* byte size of client's address */
	struct sockaddr_in serveraddr; /* server's addr */
	struct sockaddr_in clientaddr; /* client addr */
	struct hostent *hostp; /* client host info */
	char *hostaddrp; /* dotted decimal host addr string */
	int optval; /* flag value for setsockopt */

	/* check command line args */
	/*  if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(1);
	}*/
	portno = net_port;

	/* socket: create a socket */
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0) 
		error("ERROR opening socket");

	/* setsockopt: Handy debugging trick that lets 
	* us rerun the server immediately after we kill it; 
	* otherwise we have to wait about 20 secs. 
	* Eliminates "ERROR on binding: Address already in use" error. 
	*/
	optval = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, 
	(const void *)&optval , sizeof(int));

	/* build the server's internet address */
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET; /* we are using the Internet */
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); /* accept reqs to any IP addr */
	serveraddr.sin_port = htons((unsigned short)portno); /* port to listen on */

	/* bind: associate the listening socket with a port */
	if (bind(listenfd, (struct sockaddr *) &serveraddr, 
	sizeof(serveraddr)) < 0) 
		error("ERROR on binding");

	/* listen: make it a listening socket ready to accept connection requests */
	if (listen(listenfd, 5) < 0) /* allow 5 requests to queue up */ 
		error("ERROR on listen");

	/* main loop: wait for a connection request, echo input line, 
	then close connection. */
	clientlen = sizeof(clientaddr);
	while (1) {

		/* accept: wait for a connection request */
		connfd = accept(listenfd, (struct sockaddr *) &clientaddr, (socklen_t *)&clientlen);
		if (connfd < 0) 
			error("ERROR on accept");
    
		/* gethostbyaddr: determine who sent the message */
		hostaddrp = inet_ntoa(clientaddr.sin_addr);
		printf("client addr: %s\n",hostaddrp);
		hostp = gethostbyname(hostaddrp);//, clientlen, AF_INET);
		if (hostp == NULL)
			error("ERROR on gethostbyaddr");
		if (hostaddrp == NULL)
			error("ERROR on inet_ntoa\n");
		printf("server established connection with %s (%s)\n", 
		hostp->h_name, hostaddrp);
    

		/* read: read input string from the client */
		/*   bzero(buf, BUFSIZE);
		n = read(connfd, buf, BUFSIZE);
		if (n < 0) 
		error("ERROR reading from socket");
		printf("server received %d bytes: %s", n, buf);
		*/    
		/* write: echo the input string back to the client */
		/*   n = write(connfd, buf, strlen(buf));
		if (n < 0) 
		error("ERROR writing to socket");
		*/



		//    close(connfd);
  

		//original code from here on.



		

	}

	close(connfd);
}