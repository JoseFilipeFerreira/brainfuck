#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char** argv){
    int size = 30000;
    char * membeg = calloc(size, 1);
    char * mem = membeg;

    FILE *f = fopen(argv[1], "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *cod = malloc(fsize + 1);
    fread(cod, 1, fsize, f);
    fclose(f);
    cod[fsize] = 0;
    int pos = 0;
    for(long i = 0; i < fsize; i++){
        switch (cod[i]){
            case '>': mem++; pos++; break;
            case '<': mem--; pos--; break;
            case '-': (*mem)--; break;
            case '+': (*mem)++; break;
            case '.': printf("%c\n", *mem); break;
            case ',': read(0, mem, 1); break;
            case '[':
                if ((*mem) == 0){
                    int id = 1;
                    do{
                        i++;
                        if (cod[i] == '[') id++;
                        if (cod[i] == ']') id--;
                    }while(id);
                }
                break;
            case ']':
                if ((*mem) != 0){
                    int id = 1;
                    do {
                        i--;
                        if (cod[i] == '[') id--;
                        if (cod[i] == ']') id++;
                    }while(id);
                }
                break;
            default:
                break;
        }
    }

    free(membeg);
    return 0;
}
