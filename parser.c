#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include <sys/stat.h>

int main(int argc, char** argv){
    int size = 30000;
    char * membeg = calloc(size, 1);
    char * mem = membeg;

    int f = open(argv[1], O_RDONLY);
    struct stat st;
    fstat(f, &st);
    long fsize = st.st_size;
    char *cod = malloc(fsize + 1);
    read(f, cod, fsize);
    close(f);

    for(long i = 0; i < fsize; i++){
        switch (cod[i]){
            case '>': mem++; break;
            case '<': mem--; break;
            case '-': (*mem)--; break;
            case '+': (*mem)++; break;
            case '.': write(1, mem, 1); break;
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
