// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// Client side C/C++ program to demonstrate Socket programming
// https://www.geeksforgeeks.org/socket-programming-cc/ idea sacada de aca
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define PORT 8080
#define BUFF_SIZE 1024
void cleanBuffer(char *buffer);

int main(int argc, char const *argv[])
{
	char ESC[] = {27, 0};
	int sock = 0;
	struct sockaddr_in serv_addr;
	int still_in_game = 1;
	char buffer[BUFF_SIZE] = {0};

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		perror("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("\nConnection Failed \n");
		return -1;
	}

	printf("Conexion exitosa\n");
	printf("Para terminar la conexión envíe un ESC\n");

	while (still_in_game)
	{
		scanf("%1023s", buffer);
		if (strcmp(ESC, buffer) == 0)
		{
			still_in_game = 0;
		}
		else
		{
			strcat(buffer, "\n");
			send(sock, buffer, strlen(buffer), 0);
			cleanBuffer(buffer);
		}
	}

	if( close(sock) < 0 )
	{
		perror("error in fd close");
        exit(1);
	}

	return 0;
}

void cleanBuffer(char *buffer)
{
	int i;
	for (i = 0; i < strlen(buffer) || buffer[i] == 0; i++)
	{
		buffer[i] = 0;
	}
}
