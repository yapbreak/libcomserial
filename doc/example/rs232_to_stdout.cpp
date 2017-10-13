/**
* @file rs232_to_stdout.cpp
* @brief Sample program that read serial device and print result in stdout.
* @author Adrien Oliva
* @date 2017-10-13
*
* @example C++ API
*
* This program show how to use C++ API.
*
* This program will open a serial device, set read timeout to 1 second and read
* byte by byte data from serial device.
*
* Timeout and generic error will be printed on standard error output.
*
* Compile this program with:
* g++ rs232_to_stdout.cpp -o read.x -lcomserial
*/
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <comserial.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " /path/to/tty" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Will read byte by byte serial device" << std::endl;
    std::cout << "With 1 seconds of timeout" << std::endl;
    std::cout << "Cancel with Ctrl-C" << std::endl;

    // Create device
    com::serial device(argv[1]);

    // Set read timeout to 1s
    device.set_read_timeout(1000);
    while (true) {
        unsigned char byte = 0;

        try {
            size_t len = device.read_buffer(&byte, 1);
            if (len == 1)
                std::cout << static_cast<char>(byte);
            else
                std::cerr << "Unexpected error" << std::endl;
        } catch (com::exception::invalid_input) {
            std::cerr << "Very very unlikely!" << std::endl;
        } catch (const com::exception::runtime_error &e) {
            std::cerr << e.what() << std::endl;
        } catch (const com::exception::timeout &e) {
            std::cerr << e.what() << std::endl;
            if (e.get_bytes() != 0)
                std::cout << byte;
        }
    }

    return EXIT_SUCCESS;
}
