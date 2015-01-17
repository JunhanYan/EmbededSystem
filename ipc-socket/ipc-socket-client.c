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
    int sockfd;
    struct sockaddr_in s_addr;
    socklen_t len;
    unsigned int port;
    char buf[BUFLEN];    
    
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
    /*设置服务器ip*/
    bzero(&s_addr, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    if (inet_aton(argv[1], (struct in_addr *)&s_addr.sin_addr.s_addr) == 0) {
        perror(argv[1]);
        exit(errno);
    }
    /*开始连接服务器*/    
    if(connect(sockfd,(struct sockaddr*)&s_addr,sizeof(struct sockaddr)) == -1){
        perror("connect");
        exit(errno);
    }else
        printf("conncet success!\n");
    
    while(1){
	   
        /******发送消息*******/    
        bzero(buf,BUFLEN);
        printf("Send message to server：\n");
        printf("select option：\n");
        printf("1: ADD\n");
        printf("2: SUB\n");
        printf("3: MUL\n");
        printf("4: DIV\n");
        printf("5: QUIT CLIENT\n");
		int a=0, b=0, op=0;
		char *option;
		scanf("%d",&op);
		switch(op)
		{
			case 1:{
				   option = "ADD";
				   break;
				   }
			case 2:{
				   option = "SUB";
				   break;
				   }
			case 3:{
				   option = "MUL";
				   break;
				   }
			case 4:{
				   option = "DIV";
				   break;
				   }
			case 5:{
				   printf("client closed\n");
				   break;
				   }
		}
		if(op == 5){
			break;
		}
		printf("Input the first integer operand: ");
		scanf("%d",&a);

		printf("Input the second integer operand: ");
		scanf("%d",&b);
	
		while (op==4&&b==0){
			printf("Can't divide by 0, please input the second operand again: ");
	
			scanf("%d",&b);
		}
		sprintf(buf,"%d,%d,%s",a,b,option);
	
      
        /*如果buf中含有'\n'，那么要用strlen(buf)-1，去掉'\n'*/    
        if(strchr(buf,'\n'))
            len = send(sockfd,buf,strlen(buf)-1,0);
        /*如果buf中没有'\n'，则用buf的真正长度strlen(buf)*/    
        else
            len = send(sockfd,buf,strlen(buf),0);
        if(len > 0)
            printf("Send %s successfully，total length：%d\n",buf,len);            
        else{
            printf("send failure\n");
            break;            
        }
        /******接收消息*******/
        bzero(buf,BUFLEN);
        len = recv(sockfd,buf,BUFLEN,0);
        if(len > 0)
            printf("message recieved from server is：%s,total length: %d\n",buf,len);
        else{
            if(len < 0 )
                printf("recieve failure！\n");
            else
                printf("server is closed\n");
            break;    
        }
   
    }
    /*关闭连接*/
    close(sockfd);

    return 0;
}
