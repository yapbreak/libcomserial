#ifndef FAKESERIAL_H_SCYTFMMV
#define FAKESERIAL_H_SCYTFMMV

#include <set>
#include <string>
#include <unistd.h>

namespace fake {
    class serial {
        public:
            serial(const std::string &in, const std::string &out);
            ~serial();

        private:
            pid_t m_pid;
            pid_t m_mypid;

        public:
            static std::set<pid_t> m_socat_pid_list;

    };
};

#endif /* end of include guard: FAKESERIAL_H_SCYTFMMV */
