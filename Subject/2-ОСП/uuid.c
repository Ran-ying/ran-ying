#include <stdio.h>
#include <stdlib.h>
int isUUID(char *);
char * plugin_get_info(){
    return "this is uuid plugin help summary:\n-uuids\tenable search uuid\n-A\tAND\n-O\tOR\n-N\tNOT\n";
}
int plugin_process_file(char * name){
    // 8-4-4-4-12,
    // printf("this is file: %s\n", name);
    FILE * file = fopen(name, "r");
    char c;

    fpos_t fpos; //当前位置
    fgetpos(file, &fpos); //获取当前位置
    fseek(file, 0, SEEK_END);
    long n = ftell(file);
    fsetpos(file,&fpos); //恢复之前的位置
    char * content = (char *)malloc(sizeof(char) * n);
    int s = 0;
    while((c = fgetc(file)) != EOF){
        content[s++] = c;
    }
    fclose(file);
    for(int i = 0; i < n-8; i++){
        if(isUUID(&content[i]))
        return 1;
    }
        
    return 0;
}
int isUUID(char * str){
    int uuidFormat[] = 
    {1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1};
    // 1 0-F 
    // 0 -
    for(int i = 0; i < 36; i++){
        if (uuidFormat[i] == 1 && 
                ((str[i] >= '0' && str[i] <= '9') || 
                (str[i] >= 'a' && str[i] <= 'f') || 
                (str[i] >= 'A' && str[i] <= 'F'))){
        }
        else if(uuidFormat[i] == 0 && str[i] == '-'){

        }
        else {
            return 0;
        }
    }
    return 1;
}