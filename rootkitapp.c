#include <fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
    int ret = open("/dev/my_misc_device", O_RDONLY);
    if (ret== -1)
    {
        perror("open error");
    }
    system("sh");
}

