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

    for(long i = 0; i < fsize; i++){
        for(int i = 0; i< 10; i++)
            printf("%c", mem + i);
        printf("\n");
        switch (cod[i]){
            case '>': mem++; break;
            case '<': mem--; break;
            case '-': (*mem)--; break;
            case '+': (*mem)++; break;
            case '.': printf("%c\n", *mem); break;
            case ',': read(0, mem, 1); break;
            case '[':
                if ((*mem) == 0){
                    // while(cod[i] != ']') i++;
                    int id = 1;
                    do{
                        printf("%c", cod[i]);
                        i++;
                        if (cod[i] == '[') id++;
                        if (cod[i] == ']') id--;
                    }while(cod[i] != ']' && id != 0);
                }
                break;
            case ']':
                if ((*mem) != 0){
                    // for(cod[i] != '[') i--;
                    int id = 1;
                    do {
                        i--;
                        if (cod[i] == '[') id--;
                        if (cod[i] == ']') id++;
                    }while(cod[i] != '[' && id != 0);
                }
                break;
            default:
                break;
        }
    }

    free(membeg);
    return 0;
}
