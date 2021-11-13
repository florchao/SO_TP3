// Client side C/C++ program to demonstrate Socket programming
// https://www.geeksforgeeks.org/socket-programming-cc/ idea sacada de aca
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

void cleanBuffer(char * buffer);

int main(int argc, char const *argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
    int still_in_game =1;
	char buffer[1024] = {0};

    ////////// CONEXION AL SERVIDOR   ///////////
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		perror("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("\nConnection Failed \n");
		return -1;
	}

    printf("Felicitaciones. Lograste una conexion exitosa\n");
    //////////////////////////////////////////////////
    
    while(still_in_game){ //ahora esta como en un while 1. Hay que ver como hacemos que corte cuando termina

		// habria que hacer los chequeos de conexion al server 
		
        scanf("%s", buffer);
        strcat(buffer, "\n");
        send(sock,buffer, strlen(buffer), 0 ); //mandas la respuesta
        cleanBuffer(buffer);  
    
    }

    close(sock);

	return 0;
}

void cleanBuffer(char * buffer){
    int i;
    for(i=0; i< strlen(buffer) || buffer[i]==0; i++){
        buffer[i] = 0;
    }
}
