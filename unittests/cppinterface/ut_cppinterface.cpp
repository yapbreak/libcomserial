#include "ut_cppmodule.h"
#include "ut_exceptions.h"

#include <CppUTest/CommandLineTestRunner.h>

int main(int argc, char *argv[])
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
