#include <stdio.h> 
#include <string.h>
#include <time.h> // funções para implementação dos comandos date & time.
#include <dirent.h> // funções para implementação do comando dir.
#include <stdlib.h> // getenv, para pegar o nome do usuário.
#include <unistd.h> // getcwd, para pegar o caminho atual. gethostname, para pegar o nome do host.

int dirF(void);
int dateF(void);
int timeF(void);

int main(int argc, char const *argv[]) {
    char* user = getenv("USER");
    char path[1337];
    char host[404];
    getcwd(path, 1337);
    gethostname(host, 404);

    while (1)  {
        printf("%s@%s:%s$ ", user, host, path);
        char command[1971];
        fgets(command, 1971, stdin);
        command[strcspn(command, "\n")] = '\0';

        if (!strcmp(command, "cls")) printf("\33[H\33[2J"); // \33[H retorna o cursor para a localização incial e \33[2J limpa a tela.
        else if (!strcmp(command, "dir")) dirF();
        else if (!strcmp(command, "date")) dateF();
        else if (!strcmp(command, "time")) timeF();
        else if (!strcmp(command, "exit")) break;
        else printf("%s: command not found", command);

        printf("\n");
    }
    return 0;
}

int dirF()
{
    DIR* dir = opendir("."); // aloca o endereço do diretório passado para o parâmetro dirname 
    struct dirent* cdir; // declara a variável do ponteiro para estrutura dirent. que possuir propriedades como d_name, nome do diretório.

    // readdir, "lê" o próximo arquivo no diretório aberto, caso exista, se houver erro, como não haver próximo arquivo, retorna NULL.
    while ((cdir = readdir(dir)) != NULL)
    {
        printf("%s ", cdir->d_name);
    }
    return closedir(dir); // libera o ponteiro e o acesso ao diretório que foi aberto.
}

struct tm* get_tm() {
    // Pega o tempo do calendário atual como um valor do tipo time_t.
    time_t rawTime = time(NULL);
    // Interpreta o valor apontado por rawTime e retorna uma tm struct com os valores referentes a data e hora local.
    struct tm* tm = localtime(&rawTime);
    return tm;
}

int dateF()
{
    struct tm* tm = get_tm();
    // Exibe os valores de dia, mês e ano armazenados tm struct.
    printf("Current date: %02d/%02d/%d", tm->tm_mday, (tm->tm_mon + 1), (tm->tm_year + 1900));
    return 0;
}

int timeF()
{
    struct tm* tm = get_tm();
    // Exibe os valores de hora, minutos e segundos armazenados tm struct.
    printf("Current time: %02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
    return 0;
}
