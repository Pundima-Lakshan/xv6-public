#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {
    // Check if the user provided the file name as an argument
    if (argc < 2) {
        printf(2, "Usage: touch <filename1> [<filename2> ...]\n");
        exit();
    }

    // Iterate over each filename provided by the user
    for (int i = 1; i < argc; i++) {
        // Attempt to open the file with the provided filename
        int fd = open(argv[i], O_CREATE | O_RDWR);
        if (fd < 0) {
            printf(2, "Failed to create file or update timestamp: %s\n", argv[i]);
            continue;
        }

        // Close the file descriptor
        close(fd);
    }

    exit();
}
