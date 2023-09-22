#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

void error(char* msg){
    perror(msg);
    exit(1);
}

int main(int argc,char* argv[]){
    int sockfd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_addr,client_addr;
    socklen_t clientLen;

    bzero((char*)&server_addr,sizeof(server_addr));

    int portno = atoi(argv[1]);

    //assigning values
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portno);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    //binding
    if(bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
        error("Unable to bind at server...");
    }

    //listen
    listen(sockfd,5);
    clientLen = sizeof(client_addr);

    //accept
    int newSockfd = accept(sockfd,(struct sockaddr*)&client_addr,&clientLen);

    if(newSockfd<0){
        error("Error accepting at Server Side");
    }

    int n;//dummy variable
    char buffer[255];
    bzero(buffer,255);
    n = read(newSockfd,buffer,255);
    if(n<0){
        error("Error reading msg from client side");
    }

    printf("Message from client-side is: %s\n",buffer);

    n = write(newSockfd,buffer,sizeof(buffer));

    if(n<0) error("Error writing msg to client-side");

    close(newSockfd);
    close(sockfd);
    return 0;
}
