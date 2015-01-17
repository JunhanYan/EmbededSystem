#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFLEN 30

int main(int argc, char **argv)
{
    int sockfd, newfd;
    struct sockaddr_in s_addr, c_addr;
    char buf[BUFLEN];
    socklen_t len;
    unsigned int port, listnum;
    
    /*建立socket*/
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(errno);
    }else
        printf("socket create success!\n");
    /*设置服务器端口*/    
    if(argv[2])
        port = atoi(argv[2]);
    else
        port = 4567;
    /*设置侦听队列长度*/
    if(argv[3])
        listnum = atoi(argv[3]);
    else
        listnum = 3;
    /*设置服务器ip*/
    bzero(&s_addr, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    if(argv[1])
        s_addr.sin_addr.s_addr = inet_addr(argv[1]);
    else
        s_addr.sin_addr.s_addr = INADDR_ANY;
    /*把地址和端口帮定到套接字上*/
    if((bind(sockfd, (struct sockaddr*) &s_addr,sizeof(struct sockaddr))) == -1){
        perror("bind");
        exit(errno);
    }else
        printf("bind success!\n");
    /*侦听本地端口*/
    if(listen(sockfd,listnum) == -1){
        perror("listen");
        exit(errno);    
    }else
        printf("the server is listening!\n");
    while(1){
        printf("*****************Start Server***************\n");
        len = sizeof(struct sockaddr);
        if((newfd = accept(sockfd,(struct sockaddr*) &c_addr, &len)) == -1){
            perror("accept");        
            exit(errno);
        }else
            printf("The connecting client is %s: %d\n",inet_ntoa(c_addr.sin_addr),ntohs(c_addr.sin_port));
        while(1){
        
            /******接收消息*******/
            bzero(buf,BUFLEN);
            len = recv(newfd,buf,BUFLEN,0);
			char tempstr[30];
			bzero(tempstr,30);
            if(len > 0){
                printf("message from client：%s,total length: %d\n",buf,len);
				if(strstr(buf,"ADD")){
					int a = atoi(strtok(buf,","));
					int b = atoi(strtok(NULL,","));
					sprintf(tempstr,"%d + %d = %d",a,b,a+b);
				}				
				if(strstr(buf,"SUB")){
					int a = atoi(strtok(buf,","));
					int b = atoi(strtok(NULL,","));
					sprintf(tempstr,"%d - %d = %d",a,b,a-b);
				}				
				if(strstr(buf,"MUL")){
					int a = atoi(strtok(buf,","));
					int b = atoi(strtok(NULL,","));
					sprintf(tempstr,"%d x %d = %d",a,b,a*b);
				}				
				if(strstr(buf,"DIV")){
					int a = atoi(strtok(buf,","));
					int b = atoi(strtok(NULL,","));
					sprintf(tempstr,"%d / %d = %d",a,b,a/b);
				}				

				send(newfd,tempstr,strlen(tempstr),0);
			}

            else{
                if(len < 0 )
                    printf("recieve failure！\n");
                else
                    printf("client is closed\n");
                break;        
            }
	
        }
        /*关闭聊天的套接字*/
        close(newfd);
        /*是否退出服务器*/
        printf("quit the program?：y->yes；n->no? ");
        bzero(buf, BUFLEN);
        fgets(buf,BUFLEN, stdin);
        if(!strncasecmp(buf,"y",1)){
            printf("server closed\n");
            break;
        }
    }
    /*关闭服务器的套接字*/
    close(sockfd);
    return 0;
}
