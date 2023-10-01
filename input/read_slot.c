
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h> 
#include <linux/input.h>

int main(int argc, char ** argv) {

    int fd = -1;
    struct input_event in_ev;
    struct input_absinfo info;
    int ret = -1;
    char name[100];

    if(argc != 2) {
        fprintf(stderr, "usage:%s <input-dev> \n", argv[0]);
        exit(-1);
    }

    fd = open(argv[1], O_RDONLY );
    if(fd < 0) {
        perror ("open error");
        exit(-1);
    }

    ret = ioctl(fd, EVIOCGABS(ABS_MT_SLOT), &info);
    if(ret < 0) {
        perror("ioctl error");
        close(fd);
        exit(EXIT_FAILURE);
    }

    int max_slots = info.maximum + 1 - info.minimum;
    printf("max_slots: %d\n", max_slots); 

    ret = ioctl(fd, EVIOCGNAME(sizeof(name)), &name);
    if(ret < 0) {
        perror("ioctl error");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("name: %s\n", name); 

    /* 关闭、退出 */ 
    close(fd); 
    exit(EXIT_SUCCESS);
}