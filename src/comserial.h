/**
* @file comserial.h
* @brief Main include file of libcomserial.
* @author Adrien Oliva
* @date 2017-10-13
*/
#ifndef SERIALCOMM_H_PSJAZOOR
#define SERIALCOMM_H_PSJAZOOR

#ifdef __cplusplus
#include <comserial/cppcomserial.h>
#endif

#include <comserial/ccomserial.h>

/**
 * @mainpage ComSerial library documentation
 *
 * @section Introduction
 *
 * Welcome to the documenation of ComSerial library.
 *
 * This library allows communication with a RS-232 serial device both from a C
 * and C++ program.
 *
 * You can see the C++ interface documentation in file cppcomserial.h, whereas
 * the C interface documentation is written in ccomserial.h.
 *
 * To use this library, you just need to include file comserial.h.
 * From a C project, you will get access to the C API only, whereas from a C++
 * project, both C and C++ API will be available.
 *
 * @section Example
 *
 * - C API is used in @example stdin_to_rs232.c file which illustrate a simple
 *   software that capture stdin and write it on the serial device given in
 *   argument.
 * - C++ API is used in @example rs232_to_stdout.cpp file which capture data on
 *   serial device, byte by byte and display it on stdout.
 */

#endif /* end of include guard: SERIALCOMM_H_PSJAZOOR */
