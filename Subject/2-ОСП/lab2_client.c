#define CMDER "Command format error\n"
#define APERR "Address or port undefined!\n"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define CHECK_RESULT(res, msg)			\
do {									\
	if (res < 0) {						\
		perror(msg);					\
		exit(EXIT_FAILURE);				\
	}									\
} while (0)
#define BUF_SIZE 1000

int main(int argc, char *argv[])
{
    // Адрес, на котором слушает сервер и к которому подключается клиент.
    char *LAB2ADDR = getenv("LAB2ADDR");
    //Порт, на котором слушает сервер и к которому подключается клиент.
    char *LAB2PORT = getenv("LAB2PORT");
    char *LAB2DEBUG = getenv("LAB2DEBUG");
    for(int i = 1; i<argc;i++){
        if (!strcmp(argv[i], "-v"))
        {
            printf("CLIENT VERSION: 0.0.1\nвариант 30");
        }
        else if(!strcmp(argv[i], "-h"))
        {
            printf("HELP SUMMARY:\n-v\tget version\n-a [address]\tconfig address\n-p [port]\tconfig port\n");
        }
        else if (!strcmp(argv[i], "-a"))
        {
            LAB2ADDR = argv[++i];
        }
        else if (!strcmp(argv[i], "-p"))
        {
            LAB2PORT = argv[++i];
        }
    }
    if(!LAB2ADDR || !LAB2PORT){
        fprintf(stderr, APERR);
        exit(0);
    }
    printf("ADDR:%s, PORT:%s\n",LAB2ADDR,LAB2PORT);
    fflush(stdout);

	int clientSocket;
	struct sockaddr_in serverAddr = {0};
	socklen_t addr_size;

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	CHECK_RESULT(clientSocket, "socket");
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(LAB2PORT));
	serverAddr.sin_addr.s_addr = inet_addr(LAB2ADDR);

	int res = connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	CHECK_RESULT(res, "connect");

    while(1){
        char input[100];
        scanf("%s", input);
        int N;
        if(!strcmp(input, "GET")){
        }
        else if(!strcmp(input, "PUT")){
            scanf("%d", &N);
            input[3] = ' ';
            input[4] = '\0';
            char cN[10];
            sprintf(cN, "%d", N);
            strcat(input, cN);
        }
        else {
            //CMD ERROR
            fprintf(stderr, CMDER);
            continue;
        }
        // printf("Your command is %d: %s\n", strlen(input), input);
        //send to server
        // strcat(input, '\0');

        write(clientSocket, input, strlen(input));

        char buffer[BUF_SIZE];
        res = recv(clientSocket, buffer, BUF_SIZE, 0);
        //res = read(clientSocket, buffer, BUF_SIZE);
        CHECK_RESULT(res, "recv");
        buffer[res] = '\0';
        printf("Data received (%d bytes): [%s]\n", (int)res, buffer);   
    }
	close(clientSocket);
}
