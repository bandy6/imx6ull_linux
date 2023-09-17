#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <linux/input.h>

int main(int argc, char **argv) {
    struct input_event in_ev =
    {
        0
    };
    int fd = -1;

    if (2 != argv) {
        fprintf(stderr, "usage:%s <input-dev>\n", argv[0]);
        exit(-1);
    }
    
    if(0> (fd = open(argv[1], O_RDONLY))) {
        peror("open error");
        exit(-1);
    }

    while(1) {
        if(sizeof(struct input_event) != read(fd, &in_ev, sizeof(struct input_event))) {
            perror("read error");
            exit(-1);
        }
        printf("type:%d code:%d value:%d \n", in_ev.type, in_ev.code, in_ev.value);
    }
}

//编译后，通过cat /proc/bus/input/devices  查看该文件可以获取到系统中注册的所有输入设备相关的信息

//printf == fprintf(stdout, "")
//perror == fprintf(stderr, "")