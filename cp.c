#include "types.h" // Include necessary header files
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUF_SIZE 512 // Define the buffer size

// Function to copy contents from source file to destination file
void cp(char *src, char *dest)
{
    int fd_src, fd_dest, n; // Declare file descriptors and a counter
    char buf[BUF_SIZE];     // Declare a buffer

    // Open the source file for reading
    if ((fd_src = open(src, O_RDONLY)) < 0)
    {
        printf(2, "cp: cannot open %s for reading\n", src); // Print error message if source file cannot be opened
        return;
    }

    // Open the destination file for writing
    if ((fd_dest = open(dest, O_CREATE | O_WRONLY)) < 0)
    {
        printf(2, "cp: cannot open %s for writing\n", dest); // Print error message if destination file cannot be opened
        close(fd_src);                                       // Close the source file
        return;
    }

    // Read from source file and write to destination file
    while ((n = read(fd_src, buf, sizeof(buf))) > 0)
    {
        if (write(fd_dest, buf, n) != n)
        {
            printf(2, "cp: error writing to %s\n", dest); // Print error message if there is an error writing to the destination file
            close(fd_src);                                // Close the source file
            close(fd_dest);                               // Close the destination file
            return;
        }
    }

    // Check for errors in reading from the source file
    if (n < 0)
    {
        printf(2, "cp: error reading from %s\n", src); // Print error message if there is an error reading from the source file
    }

    close(fd_src);  // Close the source file
    close(fd_dest); // Close the destination file
}

// Main function
int main(int argc, char *argv[])
{
    // Check if the correct number of arguments are provided
    if (argc != 3)
    {
        printf(2, "Usage: cp <source> <destination>\n"); // Print usage message if incorrect number of arguments are provided
        exit();
    }

    cp(argv[1], argv[2]); // Call the cp function with the source and destination file paths provided as arguments

    exit(); // Exit the program
}