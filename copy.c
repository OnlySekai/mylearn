#include<stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>

int main(int agrc, char **argv){
    int fcome=open(argv[1],O_RDONLY);
    if (fcome==-1) {
        perror("open 1");
        return -1;
    }

    int flags=O_CREAT|O_WRONLY|O_TRUNC;
    int mode=S_IRUSR|S_IWUSR|S_IRGRP;
    int fout=open(argv[2],flags,mode);
    if(fout==-1) {
        perror("open 2");
        return -1;
    }
    
    char *buf;
    int readc=read(fcome,buf,1024);
    while(readc>0){
        if (write(fout,buf,1024)!=readc){
            perror("copy:");
            return -1;
        }
        readc=read(fcome,buf,1024);
    }
    if (readc==-1){
        perror("read");
        return -1;
    }
    if (close(fcome)==-1) {
        perror("close 1");
        return -1;
    }
    if (close(fout)==-1) {
        perror("close 1");
        return -1;
    }
}
