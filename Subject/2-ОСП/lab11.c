#define UNARG "ERROR: undefined arguments\n"
#define FMTAR "ERROR: target format error\n"
#define NODIR "ERROR: undefined directory\n"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fts.h>
#include <errno.h>

void scan(char *name, char * tar){
    // printf("this is file: %s\n", name);
    FILE * file = fopen(name, "r");
    if(file == NULL){
        strerror(errno);
    }
    char c;
    char *t = tar;
    while((c = fgetc(file)) != EOF){
        while((*t!='\0')&&(*t==c)){
            // printf("%c", c);
            c = fgetc(file);
            t++;
        }
        if(*t=='\0'){
            printf("%s: %s\n", name, tar);
            break;
        }
        else t = tar;
    }
    fclose(file);
}
void dir(char *name, char* tar) {
    FTS *fts;
    char ** pdir;
    pdir = (char**)malloc(sizeof(char **));
    *pdir = name;
    if ((fts = fts_open(pdir, FTS_PHYSICAL, NULL)) == NULL)
    {
        // ERR NODIR
        fprintf(stderr, NODIR);
    };
    FTSENT *ftsfile;
    while ((ftsfile = fts_read(fts)) != NULL)
    {
        if(strlen(ftsfile->fts_name)==0) continue;
        // printf("%s\t%s\n", ftsfile->fts_name, ftsfile->fts_path);
        if(ftsfile->fts_info == FTS_F){
            // printf("|\tthis is file\n");
            scan(ftsfile->fts_path, tar);
        }
        else if(ftsfile->fts_info == FTS_D){
            // printf("|\tthis is dir\n");
        }
    }
}
int main(int argc, char *argv[])
{
    char *LAB11DEBUG = getenv("LAB11DEBUG");
    if (argc == 2)
    {
        if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "-help"))
        {
            printf("this is help\n-h  -help\t get help\n-v -version\t get version");
        }
        else if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "-version"))
        {
            printf("VERSION: 0.0.1 вариант 5");
        }
        else
        {
            // ERR undefined arg
            fprintf(stderr, UNARG);
        }
    }
    else if (argc == 3)
    {
        if(LAB11DEBUG) printf("DIR: %s\nTAR: %s\n", argv[1], argv[2]);
        
        if (strlen(argv[2]) <= 2 || argv[2][0] != '0' || !(argv[2][1] == 'x' || argv[2][1] == 'X') || (strlen(argv[2]) % 2 != 0))
        {
            // ERR target format error
            fprintf(stderr, FMTAR);
            exit(1);
        }
        for (int i = 2; i < strlen(argv[2]); i++)
        {
            if ((argv[2][i] >= '0' && argv[2][i] <= '9') || (argv[2][i] >= 'a' && argv[2][i] <= 'f') || (argv[2][i] >= 'A' && argv[2][i] <= 'F'))
            {
            }
            else
            {
                // ERR target format error
                fprintf(stderr, FMTAR);
                exit(1);
            }
        }
        char *target = (char *)malloc(sizeof(char) * (strlen(argv[2]) / 2));
        for (int i = 2; i < strlen(argv[2]); i += 2)
        {
            int temp = 0;
            if (argv[2][i] >= '0' && argv[2][i] <= '9')
            {
                temp += 16 * (argv[2][i] - '0');
            }
            else if (argv[2][i] >= 'a' && argv[2][i] <= 'f')
            {
                temp += 16 * (argv[2][i] - 'a' + 10);
            }
            else if (argv[2][i] >= 'A' && argv[2][i] <= 'F')
            {
                temp += 16 * (argv[2][i] - 'A' + 10);
            }

            if (argv[2][i + 1] >= '0' && argv[2][i + 1] <= '9')
            {
                temp += 1 * (argv[2][i + 1] - '0');
            }
            else if (argv[2][i + 1] >= 'a' && argv[2][i + 1] <= 'f')
            {
                temp += 1 * (argv[2][i + 1] - 'a' + 10);
            }
            else if (argv[2][i + 1] >= 'A' && argv[2][i + 1] <= 'F')
            {
                temp += 1 * (argv[2][i + 1] - 'A' + 10);
            }
            target[i / 2 - 1] = (char)temp;
        }
        target[strlen(argv[2])/2] = '\0';
        dir(argv[1], target);
    }
    else
    {
        // ERR undefined arg
        fprintf(stderr, UNARG);
    }
}
