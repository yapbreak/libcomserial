/**
* @file stdin_to_rs232.c
* @brief Sample program that write word from stdin to serial device.
* @author Adrien Oliva
* @version 
* @date 2017-10-13
*
* This program shows how to use C API.
*
* Compile this program with:
* gcc stdin_to_rs232.c -o write.x -lcomserial
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <comserial.h>

/**
* @brief Main function of sample software.
*
* @param argc Number of arguments
* @param argv[] Array of arguments
*
* @return 0 on success.
*/
int main(int argc, const char *argv[])
{
    int quit = 0;
    comserial_t serial;

    if (argc != 2) {
        printf("Usage: %s /path/to/tty\n", argv[0]);
        return EXIT_FAILURE;
    }

    serial = comserial_create_device(argv[1]);
    if (serial == NULL) {
        printf("Fail to create serial device\n");
        return EXIT_FAILURE;
    }

    printf("Type /quit to quit\n");
    while (!quit) {
        char buffer[1024] = {};
        printf("> ");
        scanf("%1023s", buffer);
        if (strcmp(buffer, "/quit") == 0) {
            quit = 1;
        } else {
            size_t size = strlen(buffer);
            ssize_t len = comserial_write_buffer(serial, buffer, size);
            if (len == -COMSER_IOERROR) {
                printf("Communication error\n");
            } else if (len < 0) {
                printf("Timeout reached (%ld bytes written befor timeout)\n",
                       -len);
            } else if (len != size) {
                printf("Unknown error\n");
            } else {
                printf("%s successfully written\n", buffer);
            }
        }
    }

    comserial_destroy_device(&serial);

    return EXIT_SUCCESS;
}
