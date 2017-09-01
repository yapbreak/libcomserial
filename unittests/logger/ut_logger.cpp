#include "ut_dumper.h"
#include "ut_log_location.h"
#include "ut_internallog.h"

#include <CppUTest/CommandLineTestRunner.h>

int main(int argc, char *argv[])
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
