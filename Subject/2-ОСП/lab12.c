#define UNARG "ERROR: undefined arguments\n"
#define FMTAR "ERROR: target format error\n"
#define NODIR "ERROR: undefined directory\n"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fts.h>
#include <errno.h>
#include <dlfcn.h>
#define UUIDONLY 3
#define AND 0
#define OR 1
#define NOT 2
#define UUID 4

int mode = 0;
int plugin = 0;
char *LAB1DEBUG;
int (*plugin_process_file)(char * name);
char * (*plugin_get_info)();
int scan(char *name, char * tar){
    if(LAB1DEBUG) printf("this is file: %s\n", name);
    FILE * file = fopen(name, "r");
    if(file == NULL){
        strerror(errno);
    }
    int c;
    char *t = tar;
    while((c = fgetc(file)) != EOF){
        while((*t!='\0')&&(*t==c)){
            // printf("%c", c);
            c = fgetc(file);
            t++;
        }
        if(*t=='\0'){
            // printf("%s: %s\n", name, tar);
            fclose(file);
            return 1;
            // break;
        }
        else t = tar;
    }
    fclose(file);
    return 0;
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
        if(LAB1DEBUG) printf(NODIR);
    };
    FTSENT *ftsfile;
    while ((ftsfile = fts_read(fts)) != NULL)
    {
        if(strlen(ftsfile->fts_name)==0) continue;
        if(LAB1DEBUG)  printf("%s\t%s\n", ftsfile->fts_name, ftsfile->fts_path);
        if(ftsfile->fts_info == FTS_F){
            // printf("|\tthis is file\n");
            int scanR = scan(ftsfile->fts_path, tar);
            int plugR;
            int result = 0;
            if(mode & UUID){
                plugR = plugin_process_file(ftsfile->fts_path);
                switch(mode ^ UUID){
                    case 0:
                        //AND
                        if(scanR == 1 && plugR == 1) result = 1;
                        break;
                    case 1:
                        //OR
                        if(scanR == 1 || plugR == 1) result = 1;
                        break;
                    case 2:
                        //AND NOT
                        if(scanR == 0 || plugR == 0) result = 1;
                        break;
                    case 3:
                        //OR NOT
                        if(scanR == 0 && plugR == 0) result = 1;
                        break;
                }
            }
            else {
                result = scanR;
            }
            // printf("%d", mode ^ UUID);
            if(LAB1DEBUG)  printf("mode:%d, scanR:%d, plugR:%d result: %d\n",mode, scanR, plugR,result);
            if(result) printf("%s\n", ftsfile->fts_path);
        }
        else if(ftsfile->fts_info == FTS_D){
            // printf("|\tthis is dir\n");
        }
    }
}
int isHelp;
int main(int argc, char *argv[])
{
    char * help = "this is help\n-h -help\t get help\n-v -version\t get version\n";
    LAB1DEBUG = getenv("LAB1DEBUG");
    char *pluginDir = "./";
    for(int i = 1; i<argc;i++)
    {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "-help"))
        {
            isHelp = 1;
        }
        else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "-version"))
        {
            printf("VERSION: 0.0.1\nвариант 5");
        }
        else if (!strcmp(argv[i], "-P")){
            //plugin dir:
            pluginDir = argv[++i];
        }
        else if (!strcmp(argv[i], "-A")){
            mode |= AND;
        }
        else if (!strcmp(argv[i], "-O")){
            mode |= OR;
        }
        else if (!strcmp(argv[i], "-N")){
            mode |= NOT;
        }
        else if (!strcmp(argv[i], "-uuids")){
            mode |= UUID;
        }
        else
        {
            // ERR undefined arg
            // fprintf(stderr, UNARG);
        }
    }

    //load plugin
    char pluginFile[100];
    sprintf(pluginFile, "%slibuuid.so", pluginDir);
    void * handle = dlopen(pluginFile, RTLD_LAZY);
    plugin_process_file = dlsym(handle, "plugin_process_file");
    plugin_get_info = dlsym(handle, "plugin_get_info");
    plugin = 1;
    if(isHelp){
        printf(help);
        if(plugin)
            printf("%s",plugin_get_info());
        exit(0);
    }
    if(LAB1DEBUG) printf("DIR: %s\nTAR: %s\n", argv[1], argv[2]);
    
    if (strlen(argv[2]) <= 2 || argv[2][0] != '0' || !(argv[2][1] == 'x' || argv[2][1] == 'X') || (strlen(argv[2]) % 2 != 0))
    {
        // ERR target format error
        // fprintf(stderr, FMTAR);
        //При запуске без имени каталога для поиска программа выводит справочную информацию по опциям и доступным в момент запуска плагинам.
        printf(help);
        if(plugin)
            printf("%s",plugin_get_info());
        exit(1);
    }
    // for (int i = 2; i < strlen(argv[2]); i++)
    // {
    //     if ((argv[2][i] >= '0' && argv[2][i] <= '9') || (argv[2][i] >= 'a' && argv[2][i] <= 'f') || (argv[2][i] >= 'A' && argv[2][i] <= 'F'))
    //     {
    //         printf(help);
    //         if(plugin)
    //             printf("%s",plugin_get_info());
    //     }
    //     else
    //     {
    //         // ERR target format error
    //         fprintf(stderr, FMTAR);
    //         exit(1);
    //     }
    // }

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
