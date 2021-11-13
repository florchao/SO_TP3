// Server side C/C++ program to demonstrate Socket programming
// https://www.geeksforgeeks.org/socket-programming-cc/ idea sacada de aca

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define MAX_DESAFIOS 13
#define CANT_RESPUESTAS 12
char *rtas[CANT_RESPUESTAS] = {"entendido\n", "itba\n", "M4GFKZ289aku\n", "fk3wfLCm3QvS\n", "too_easy\n", ".RUN_ME\n", "K5n2UFfpFMUN\n", "BUmyYq5XxXGt\n", "u^v", "chin_chu_lan_cha\n", "gdb_rules\n", "normal\n"};

#define PORT 8080

void cleanBuffer(char * buffer){
    int i;
    for(i=0; i< strlen(buffer) || buffer[i]==0; i++){
        buffer[i] = 0;
    }
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
	char bufferClient[124] = {0};
    int desafioNro;
    //////////////////////////// CREACION DEL SERVER ////////////////////////
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    ///////////////////////////////////////////////////////////////

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)))
    {
        desafioNro = 1;
        //habria que llamar al primer desafio
		//(*desafios[desafioNro])();  --> Para mi no va aca
        while(desafioNro < MAX_DESAFIOS && (valread = read(new_socket, bufferClient, (size_t) bufferClient))>0){
            //(*desafios[desafioNro])(); --> para mi esto no va 
            if(strcmp(bufferClient, rtas[desafioNro]) == 0){
                desafioNro++;
                if(desafioNro<MAX_DESAFIOS){
                    //(*desafios[desafioNro])(); --> aca si
                }
            }
            else{
                printf("Respuesta incorrecta: %s", bufferClient);
            }
            cleanBuffer(bufferClient);
        }
        if (new_socket < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        if (valread < 0)
        {
            perror("error in fd reading");
            exit(EXIT_FAILURE);
        }
        
    }
    printf("Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto\n");
    close(server_fd);
    return 0;
}