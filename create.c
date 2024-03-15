#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
    int fd;

    if (argc != 2)
    {
        printf(1, "Usage: %s <filename>\n", argv[0]);
        exit();
    }

    if ((fd = open(argv[1], O_CREATE | O_WRONLY)) == -1)
    {
        printf(1, "Error creating file\n");
        exit();
    }

    close(fd);
    printf(1, "File '%s' created successfully.\n", argv[1]);

    exit();
}