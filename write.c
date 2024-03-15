#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUF_SIZE 512

int main(int argc, char *argv[])
{
    char buf[BUF_SIZE];
    int fd, n;

    if (argc != 2)
    {
        printf(2, "Usage: editor <filename>\n");
        exit();
    }

    // Open the file for reading and writing, create if it doesn't exist
    if ((fd = open(argv[1], O_CREATE | O_RDWR)) < 0)
    {
        printf(2, "editor: cannot open %s\n", argv[1]);
        exit();
    }

    // Print usage instructions
    printf(1, "Welcome to xv6 Text Editor\n");
    printf(1, "Press Ctrl+C and ENTER to save and exit\n");

    // Read file content, if any, and print to console
    while ((n = read(fd, buf, sizeof(buf))) > 0)
    {
        write(1, buf, n); // Print file content to console
    }

    // Prompt user for input
    printf(1, "\n");

    // Read user input and write to file
    while ((n = read(0, buf, sizeof(buf))) > 0)
    {
        // Check if the input is Ctrl+C (ASCII value 3)
        if (buf[0] == 3)
        {
            printf(1, "\nSaving changes and exiting...\n");
            close(fd);
            exit();
        }

        // Write user input to file
        if (write(fd, buf, n) != n)
        {
            printf(2, "editor: error writing to file\n");
            break;
        }
    }

    // Close file
    close(fd);

    exit();
}
