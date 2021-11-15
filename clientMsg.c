#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc , char *argv[])
{
	int socket_desc,new_socket,c;
	struct sockaddr_in server; 
        char *message;
	char clientMsg[20000],buff[20000];
	void sigTSTP_handler(int tstp);//SIGNAL handler to exit the message program
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
		
	server.sin_addr.s_addr = inet_addr("192.168.56.103"); //Please enter the ip address of your Server VM
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );//Using port 8888 to send the message

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}
	
	puts("Connected \n");

	//Message with SERVER
	printf("******Welcome to application chat with SERVER*******\n\n");
	for(;;)
	{
	printf("!!! Press CTRL + Z if you want to exit the application !!!\n\n");
	printf("CLIENT :");
	fgets(clientMsg,2000,stdin);
	send(socket_desc,clientMsg,2000,0);
	
	printf("*****Waiting for SERVER message******\n\n");
	recv(socket_desc,buff,2000,0);
	printf("SERVER :%s\n ",buff);
	
	//SIGNAL Handler
	if (signal(SIGTSTP, sigTSTP_handler) == SIG_ERR){
	perror("signal");
	exit(1);
  	}

	}

	if( send(socket_desc , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");

        //If fail to receive reply from SERVER
	if( recv(socket_desc, buff, 2000 , 0) < 0)
	{
		puts("recv failed");
	}
	close(socket_desc);
	return 0;
}

void sigTSTP_handler(int tstp)
{
  printf("Ending Message with Server \n\n");
  printf("******Thank for using our application********\n\n");
  exit(0);
}





