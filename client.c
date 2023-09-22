#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>

void error(char* msg){
    perror(msg);
    exit(1);
}

int main(int argc,char* argv[]){
    int sockfd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_addr;
    struct hostent* server;

    server = gethostbyname(argv[2]);

    bzero((char*) &server_addr,sizeof(server_addr));

    int portno = atoi(argv[1]);

    //assigning values to server_addr
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portno);
    bcopy((char*) server->h_addr,(char*) &server_addr.sin_addr.s_addr,server->h_length);

    if(connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0){
        error("Error establishing a connection at client-side");
    }

    char buffer[255];
    int n = 0;
    while((buffer[n++]=getchar())!='\n');

    write(sockfd,buffer,sizeof(buffer));
    bzero(buffer,sizeof(buffer));
    read(sockfd,buffer,sizeof(buffer));

    printf("Message from Server-Side: %s\n",buffer);

    close(sockfd);

    return 0;
}

