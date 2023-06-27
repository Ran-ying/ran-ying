#define CMDER "ERROR 2\n"
#define APERR "Address or port undefined!\n"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#define CHECK_RESULT(res, msg)			\
do {									\
	if (res < 0) {						\
		perror(msg);					\
		exit(EXIT_FAILURE);				\
	}									\
} while (0)

#define MAX_MSG_LEN		10
#define BUF_SIZE 1000

time_t startTime;
int sucReq=0, errReq=0;
char * LAB2LOGFILE;
char *LAB2DEBUG;
void logerr(char * LAB2DEBUG,char *  LAB2LOGFILE,char *  msg){
    if(LAB2DEBUG && LAB2LOGFILE){
        FILE * f = fopen(LAB2LOGFILE, "a");
        char ctm[100];
        time_t t = time(0);
        strftime(ctm, 100, "%d.%m.%y %T", localtime(&t));
        fputs(ctm,f);
        fputs(" ", f);
        fputs(msg, f);
        fclose(f);
    }
}
void sig_quit(int sig)
{
    exit(0);
}
void sig_info(int sig){
    int runTime = time(0) - startTime;
    char info[1000];
    sprintf(info, "process already been run %d s\nsuccess request: %d\nerror request: %d\n", runTime, sucReq, errReq);
    fprintf(stderr, info);
    logerr(LAB2DEBUG, LAB2LOGFILE, info);
}
int main(int argc, char *argv[]){

    // signal (SIGINT,sig_quit) ;
    // signal (SIGTERM,sig_quit) ;
    // signal (SIGQUIT,sig_quit) ;
    // signal (SIGUSR1, sig_info);
    startTime = time(0);
    // Имитация работы путем приостановки обслуживающего запрос процесса/потока на N секунд. Если опция не задана, обслуживать запрос без задержки.
    char *LAB2WAIT = getenv("LAB2WAIT");
    // Работа в режиме демона.
    int DAEMON = 0;
    // Путь к лог-файлу.
    LAB2LOGFILE = getenv("LAB2LOGFILE");
    // Адрес, на котором слушает сервер и к которому подключается клиент.
    char *LAB2ADDR = getenv("LAB2ADDR");
    //Порт, на котором слушает сервер и к которому подключается клиент.
    char *LAB2PORT = getenv("LAB2PORT");
    LAB2DEBUG = getenv("LAB2DEBUG");
    for(int i = 1; i<argc;i++){
        if (!strcmp(argv[i], "-d"))
        {
            DAEMON = 1;
        }
        else if (!strcmp(argv[i], "-v"))
        {
            printf("SERVER VERSION: 0.0.1\nвариант 30");
        }
        else if(!strcmp(argv[i], "-h"))
        {
            printf("HELP SUMMARY:\n-v\tget version\n-a [address]\tconfig address\n-p [port]\tconfig port\n-d\trun in deamon mode\n-w [second]\tsleep before answer\n-l [dir]\tlog file\n");
        }
        else if (!strcmp(argv[i], "-w"))
        {
            LAB2WAIT = argv[++i];
        }
        else if(!strcmp(argv[i], "-l")){
            LAB2LOGFILE = argv[++i];
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
        logerr(LAB2DEBUG, LAB2LOGFILE, "ERROR 1\n");
        exit(0);
    }
    if(DAEMON){
        if(fork()) exit(0);
        printf("run in daemon mode!");
    }
    printf("ADDR:%s, PORT:%s\n",LAB2ADDR,LAB2PORT);
    fflush(stdout);
    //
	int serverSocket, clientSocket;
	struct sockaddr_in serverAddr = {0};
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	int res;
	
	srand(time(NULL));
	
    //AF_INT:ipv4, SOCK_STREAM:tcp协议
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	CHECK_RESULT(serverSocket, "socket");

	res = setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));
	CHECK_RESULT(res, "setsockopt");

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(LAB2PORT));
	serverAddr.sin_addr.s_addr = inet_addr(LAB2ADDR);

	res = bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	CHECK_RESULT(res, "bind");

	res = listen(serverSocket, 5);
	CHECK_RESULT(res, "listen");

    int allQueue[1000];
    int allHead = 0;
    int allRear = 0;


    while(1){
        addr_size = sizeof(serverStorage);
        clientSocket = accept(serverSocket, (struct sockaddr *)&serverStorage, &addr_size);
        CHECK_RESULT(clientSocket, "accept");

        int pid;
        if((pid = fork())==0){
            close(serverSocket);

            while(1){ 
                char input[100];
                char recvBuffer[BUF_SIZE];
                int recvRes = recv(clientSocket, recvBuffer, BUF_SIZE, 0);
                CHECK_RESULT(res, "recv");
                printf("Data received (%d bytes): [%s]\n", (int)recvRes, recvBuffer, strlen(recvBuffer));
                strncpy(input, recvBuffer, recvRes);
                input[recvRes] = '\0';
                // printf("%s", input);
                // fflush(stdout);
                char buffer[BUF_SIZE];
                char cmd[10];
                strncpy(cmd, input, 3);
                cmd[3]='\0';
                int N;
                if(!strcmp(cmd, "GET")){
                    if(allHead >= allRear){
                        //Nothing in queue
                        sprintf(buffer, "ERROR 1");
                        logerr(LAB2DEBUG, LAB2LOGFILE, "ERROR 1\n");
                        errReq++;
                    }
                    else{
                        sprintf(buffer, "%d", allQueue[allHead++]);
                        sucReq++;
                    }
                }
                else if(!strcmp(cmd, "PUT")){
                    char cN[10];
                    strncpy(cN, input+4, strlen(input)-4);
                    // printf("\n%s\n", cN);
                    // fflush(stdout);
                    N = atoi(cN);
                    allQueue[allRear++] = N;
                    sprintf(buffer, "OK");
                    sucReq++;
                }
                else {
                    //CMD ERROR
                    fprintf(stderr, CMDER);
                        logerr(LAB2DEBUG, LAB2LOGFILE, CMDER);
                    // exit(0);
                }
                        
                // char buffer[BUF_SIZE] = "Your command is: ";
                // strcat(buffer, recvBuffer);
                //res = send(clientSocket, buffer, msg_len, 0);
                if(LAB2WAIT)
                    sleep(atoi(LAB2WAIT));
                res = write(clientSocket, buffer, strlen(buffer));
                CHECK_RESULT(res, "send");
                // close(clientSocket);
                // exit(0);
                if(LAB2LOGFILE){
                    FILE * f = fopen(LAB2LOGFILE, "a");
                    char ctm[100];
                    time_t t = time(0);
                    strftime(ctm, 100, "%d.%m.%y %T", localtime(&t));
                    fputs(ctm,f);
                    fputs(" [", f);
                    fputs(input, f);
                    fputs("] ", f);
                    fputs(buffer, f);
                    fputs("\n", f);
                    fclose(f);
                }
                // sig_info(0);
            }
            close(clientSocket);
            exit(0);
        }
        else{

        }
        close(clientSocket);
    }
}