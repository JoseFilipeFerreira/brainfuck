#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char** argv){
    char a;
    int size = 1000;
    char * membeg = calloc(size, 1);
    char * mem = membeg;
    mem += size / 2;

    int fd = open(argv[1], O_RDONLY);
    while(read(fd, &a, 1)){
        switch (a){
            case '>': mem++; break;
            case '<': mem--; break;
            case '-': (*mem)--; break;
            case '+': (*mem)++; break;
            case '.': printf("%c\n", *mem); break;
            case ',': read(0, mem, 1); break;
            case '[':
                if (!(*mem)){
                    do{
                        read(fd, &a, 1);
                    }while(a != ']');
                }
                break;
            case ']':
                if (!(*mem)){
                    do{
                        lseek(fd,-1,SEEK_CUR);
                        read(fd, &a, 1);
                    }while(a != '[');
                }
                break;
            default:
                break;
        }
    }

    close(fd);
    free(membeg);
    return 0;
}
