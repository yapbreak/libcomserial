#include "fakeserial.h"

#include <sstream>
#include <iostream>

#include <signal.h>
#include <errno.h>
#include <cstring>
#include <sys/wait.h>

std::set<pid_t> fake::serial::m_socat_pid_list;

#if HAVE_SOCAT == 1
static void crash_handler(int signum)
{
    switch (signum) {
        case SIGSEGV:
        case SIGABRT:
            for (auto &it: fake::serial::m_socat_pid_list) {
                kill(it, SIGINT);
                waitpid(it, NULL, 0);
            }

            signal(signum, SIG_DFL);
            kill(getpid(), signum);
            break;
    }
}
#endif

fake::serial::serial(const std::string &in, const std::string &out)
    : m_pid(0)
    , m_mypid(getpid())
{
#if HAVE_SOCAT == 1
    // Create fake serial using socat
    m_pid = fork();
    if (m_pid == 0) {
        // We are in child process
        std::stringstream arg1;
        std::stringstream arg2;

        arg1 << "pty,link=" << in << ",rawer";
        arg2 << "pty,link=" << out << ",rawer";

        int ret = execl("socat", "socat",
                        arg1.str().c_str(),
                        arg2.str().c_str(),
                        (char *) NULL);
        if (ret == -1) {
            int errsys = errno;
            std::cerr << "Fail to start socat: "
                      << strerror(errsys)
                      << std::endl;
            kill(m_mypid, SIGINT);
            throw std::exception();
        }
    } else if (m_pid == -1) {
        throw std::exception();
    } else {
        // Store child in set and register crash handler that will clean
        // all socat instances on SIGNAL
        m_socat_pid_list.insert(m_pid);
        signal(SIGSEGV, crash_handler);
        signal(SIGABRT, crash_handler);

        bool all_ok = false;
        while (!all_ok) {
            all_ok =    (access(in.c_str(), F_OK) == 0)
                    &&  (access(out.c_str(), F_OK) == 0);
            usleep(1);
        }
    }
#else
    (void) in;
    (void) out;
#endif
}

fake::serial::~serial()
{
#if HAVE_SOCAT == 1
    kill(m_pid, SIGINT);
    m_socat_pid_list.erase(m_pid);
    waitpid(m_pid, NULL, 0);
#endif
}

