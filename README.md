# ComSerial

Library that allows any C/C++ application to communicate through a serial link
on GNU/Linux (or any POSIX system with termios interface).

---

- Master branch:

[![build_status](https://gitlab.yapbreak.fr/libraries/libcomserial/badges/master/build.svg)](https://gitlab.yapbreak.fr/libraries/libcomserial/commits/master)
[![coverage report](https://gitlab.yapbreak.fr/libraries/libcomserial/badges/master/coverage.svg)](https://gitlab.yapbreak.fr/libraries/libcomserial/commits/master)

- Latest stable release:

[![build_status](https://gitlab.yapbreak.fr/libraries/libcomserial/badges/v1/build.svg)](https://gitlab.yapbreak.fr/libraries/libcomserial/commits/v1)
[![coverage report](https://gitlab.yapbreak.fr/libraries/libcomserial/badges/v1/coverage.svg)](https://gitlab.yapbreak.fr/libraries/libcomserial/commits/v1)

---

## Download

Source library are available on
https://gitlab.yapbreak.fr/libraries/libcomserial/-/jobs/artifacts/master/download?job=distribute

One can also simply clone repository to get the latest modification.

## Dependencies

ComSerial require the following libraries to work:

- termios

To have full test support, you need the aditionnal libraries and programs:

- socat
- cpputest
- gcov and lcov (to get coverage report)

To get full log support, you can install yaplog library available at
https://gitlab.yapbreak.fr/libraries/libyaplog.


## Compilation

If you clone the repository, you must run the following command before going
to next step:

```bash
./autogen.sh
```

If you download the archive directly, you can skip this step. Then, simply runs
the classical autotools build step:

```bash
./configure
make
make check # to test library
sudo make install
```

## Configuration

Additional logging facility may be enabled by settings two environment
variables:

- `CSER_LOGDESTINATION` controls where logs are stored. It could be `stderr`,
  `stdout` or any file path. Default is `stderr`.
- `CSER_LOGLEVEL` controls log verbosity from 0 (no log) to 9 (extremely
  verbose)
