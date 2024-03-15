#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUF_SIZE 512

int main(int argc, char *argv[])
{
    int fd_src, fd_dest;
    char buf[BUF_SIZE];
    int read_bytes;

    if (argc != 3)
    {
        printf(1, "Usage: %s <source> <destination>\n", argv[0]);
        exit();
    }

    if ((fd_src = open(argv[1], O_RDONLY)) == -1)
    {
        printf(1, "Error opening source file\n");
        exit();
    }

    if ((fd_dest = open(argv[2], O_CREATE | O_WRONLY)) == -1)
    {
        printf(1, "Error opening destination file\n");
        close(fd_src);
        exit();
    }

    while((read_bytes = read(fd_src, buf, sizeof(buf))) > 0)
    {
        write(fd_dest, buf, read_bytes);
    }

    close(fd_src);
    close(fd_dest);

    if(unlink(argv[1]) < 0)
    {
        printf(1, "Error deleting source file\n");
        exit();
    }

    printf(1, "File moved successfully.\n");

    exit();
}