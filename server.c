// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// Server side C/C++ program to demonstrate Socket programming
// https://www.geeksforgeeks.org/socket-programming-cc/ idea sacada de aca
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define MAX_DESAFIOS 12
#define BUFF_SIZE 512
#define FIRST_ASCII 33
#define LAST_ASCII 127
#define CANT_NORMAL 1000
#define PORT 8080
#define PI 3.141592
char *pistas[MAX_DESAFIOS] = {"Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\nEn este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\nAdemás tendrán que investigar otras preguntas para responder durante la defensa.\nEl desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\nAdemás, deberán implementar otro programa para comunicarse conmigo.\nDeberán estar atentos a los easter eggs.\nPara verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra 'entendido\n'\n",
                              "The Wire S1E5 5295 888 6288\n",
                              "https://ibb.co/tc0Hb6w\n",
                              "EBADF… write: Bad File Descriptor\n",
                              " respuesta = strings:70\n",
                              ".debug_line .debug_str .debug_macro ? .shstrtab .symtab .strtab\n",
                              "Filter error\n",
                              "¿?\n",
                              " Latexme\nSi\n\\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\frac{u'}{u})\nentonces\ny =\n",
                              "quine\n",
                              " b gdb_me y encontrá el valor mágico\n",
                              "Me conoces \n"};
char *rtas[MAX_DESAFIOS] = {"entendido\n", "itba\n", "M4GFKZ289aku\n", "fk3wfLCm3QvS\n", "too_easy\n", ".RUN_ME\n", "K5n2UFfpFMUN\n", "BUmyYq5XxXGt\n", "u^v\n", "chin_chu_lan_cha\n", "gdb_rules\n", "normal\n"};



// https://rosettacode.org/wiki/Random_numbers#C

double drand() /* uniform distribution, (0..1] */
{
    return (rand() + 1.0) / (RAND_MAX + 1.0);
}

double normal() /* normal distribution, centered on 0, std dev 1 */
{
    return sqrt(-2 * log(drand())) * cos(2 * PI * drand());
}

void dist_normal()
{
    double valores[CANT_NORMAL];
    int i;
    for (i = 0; i < CANT_NORMAL; i++)
    {
        valores[i] = 1.0 + 0.5 * normal();
        printf("%g ", valores[i]);
    }
}

void gdb_me()
{
    if (getpid() == 0x12345678)
    {
        printf("La respuesta es: gdb_rules\n\n");
    }
    else
    {
        printf("Oprima ok para reintentar.\n");
    }
}

void filter_error()
{
    char *rta = "K5n2UFfpFMUN";
    int i = 0;
    while (rta[i] != 0)
    {
        int randomfd = (rand() % 5) + 1;

        if (randomfd == STDOUT_FILENO)
        {
            write(STDOUT_FILENO, rta + i++, 1);
        }

        else
        {
            char c = (char)(rand() % (FIRST_ASCII - LAST_ASCII) + FIRST_ASCII);
            write(STDERR_FILENO, &c, 1);
        }
    }
}

void check_quine()
{
    int flag = system("gcc quine.c -o quine");

    if (flag != 0)
    {
        printf("gcc: error: quine.c: No such file or directory\ngcc: fatal error: no input files\ncompilation terminated. oprima ok para reintentar\n");
    }
    else
    {
        printf("¡Genial!, ya lograron meter un programa en quine.c, veamos si hace lo que corresponde.\n");
        int isValid = system("./quine | diff - quine.c");
        if (isValid == 0)
        {
            printf("La respuesta es chin_chu_lan_cha\n");
        }
        else
        {
            printf("diff encontró diferencias.\n");
        }
    }
}
void cleanBuffer(char *buffer)
{
    int i;
    for (i = 0; i < BUFF_SIZE || buffer[i] == 0; i++)
    {
        buffer[i] = 0;
    }
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char bufferClient[BUFF_SIZE] = {0};
    int desafioNro = 0;


    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)))
    {
        printf("%s", pistas[desafioNro]);
        while (desafioNro < MAX_DESAFIOS && (valread = read(new_socket, bufferClient, BUFF_SIZE)) > 0)
        {

            if (strcmp(bufferClient, rtas[desafioNro]) == 0)
            {
                desafioNro++;
                if(desafioNro == MAX_DESAFIOS)
                    break;
            }
            else
            {
                printf("Respuesta incorrecta: %s", bufferClient);
            }
            cleanBuffer(bufferClient);
            sleep(1);
            system("clear");
            printf("-------DESAFIO NRO %d --------\n", desafioNro + 1);
            printf("%s", pistas[desafioNro]);

            switch (desafioNro)
            {
            case 3:
                if (write(73, ".......................La respuesta es fk3wfLCm3QvS\n", 53) == -1)
                    perror("write");
                break;
            case 6:
                filter_error();
                break;
            case 7:
                printf("\033[30;40mLa respuesta es BUmyYq5XxXGt\033[0m\n\n");
                break;
            case 9:
                check_quine();
                break;
            case 10:
                gdb_me();
                break;
            case 11:
                dist_normal();
                break;
            default:
                break;
            }
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
    if(close(server_fd) < 0) 
    {
        perror("error in fd close");
        exit(EXIT_FAILURE);
    }

    return 0;
}