#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>

int main(int argc,char *argv[]) {
int sd,cd;
struct sockaddr_in servaddr,cliaddr; socklen_t servlen,clilen;
char buff[1000],buff1[1000];
pid_t cpid; bzero(&servaddr,sizeof(servaddr)); servaddr.sin_family=AF_INET; servaddr.sin_addr.s_addr=inet_addr(argv[1]); servaddr.sin_port=htons(5500);
/*Creating a socket, assigning IP address and port number for that socket*/
sd=socket(AF_INET,SOCK_STREAM,0);
/*Connect establishes connection with the server using server IP address*/
cd=connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
/*Fork is used to create a new process*/
cpid=fork(); if(cpid==0) {
    while(1) {
bzero(&buff,sizeof(buff)); printf("%s\n","Enter the input data:");
/*This function is used to read from server*/
fgets(buff,10000,stdin);
/*Send the message to server*/
send(sd,buff,strlen(buff)+1,0);
printf("%s\n","Data sent..."); }
}

else {

    while(1) {
        bzero(&buff1,sizeof(buff1));
/*Receive the message from server*/
recv(sd,buff1,sizeof(buff1),0);
printf("Received message from the server:%s\n",buff1);
    }}
    return 0;
}
