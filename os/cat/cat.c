#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int cat(int fd) {
    char buffer[4096];
    ssize_t read_cnt;

    while ((read_cnt = read(fd, buffer, sizeof(buffer))) > 0) {
        ssize_t write_offset = 0;
        while (write_offset < read_cnt) {
            ssize_t write_cnt = write(STDOUT_FILENO, buffer + write_offset, read_cnt - write_offset);
            if (write_cnt < 1) {
                return -1;
            }
            write_offset += write_cnt;
        }
    }

    if (read_cnt == 0) {
        return 0;
    }
    return -1;
}

int main(int argc, char **argv) {
    int i;
    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            int fd;
            if ((fd = open(argv[i], O_RDONLY)) == -1) {
                perror("Error while opening");
                return -1;
            } else {
                if (cat(fd) != 0) {
                    perror("Error while reading");
                    return -1;
                }

                if (close(fd) != 0) {
                    perror("Error while closing");
                    return -1;
                }
            }
        }
    } else {
        if (cat(STDIN_FILENO) != 0) {
            perror("Error while reading");
            return -1;
        }
    }
    return 0;
}
