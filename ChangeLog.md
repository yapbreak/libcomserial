# ChangeLog


## 1.0.1

Logging release

2018-07-23	Adrien Oliva <olivaa+gitlab@yapbreak.fr>

	* build(release): Prepare release 1.0.1
	* feat(logger): Use latest yaplog version (2.0.0)

2018-07-18	Adrien Oliva <olivaa+gitlab@yapbreak.fr>

	* Merge branch '4-integrate-libyaplog' into 'master'
	* GTLAB #4 feat(libyaplog): Integrate libyaplog

2018-07-11	Adrien Oliva <olivaa+gitlab@yapbreak.fr>

	* Merge branch '3-add-logs' into 'master'
	* Add configurable log capability

2018-07-03	Adrien Oliva <olivaa+gitlab@yapbreak.fr>

	* Add support of lcov_cobertura


## 1.0.0

Release version 1.0.0

2017-10-19	Adrien Oliva <olivaa+gitlab@yapbreak.fr>

	* Prepare version 1.0.0 release

2017-10-17	Adrien Oliva <olivaa+gitlab@yapbreak.fr>

	* Fix all documentation warning and restore warn as error in Doxyfile.

2017-10-16	Adrien Oliva <olivaa+gitlab@yapbreak.fr>

	* Fix automatic doc generation
	* Merge branch '2-package-config' into 'master'
	* Fix libraries/libcomserial#2
	* Fix example files according to CppCheck warnings.

2017-10-13	Adrien Oliva <olivaa+gitlab@yapbreak.fr>

	* Merge branch '1-write-docuentation' into 'master'
	* Add main page to documentation
	* Add all documentation of every function/class/macro/type…

2017-10-10	Adrien Oliva <olivaa+gitlab@yapbreak.fr>

	* Continue to add documentation
	* libraries/libcomserial#1

## 0.99.0

Release version 0.99.0

2017-10-10	Adrien Oliva <olivaa+gitlab@yapbreak.fr>

	* Update information files to prepare v0.99.0

2017-10-09	Adrien Oliva <olivaa+gitlab@yapbreak.fr>

	* Add const correctness in exception management
	* Add I/O function in C interface
	* Add I/O function in C++ interface
	* Add GCC specific warning flags

2017-09-28	Adrien Oliva <adrien.oliva@yapbreak.fr>

	* Add ability to set and retrieve read/write timeout from C interface.

2017-09-27	Adrien Oliva <adrien.oliva@yapbreak.fr>

	* Add ability to set read/write timeout (only from C++ interface)

2017-09-26	Adrien Oliva <olivaa+gitlab@yapbreak.fr>

	* Update download link in README
	* Add device check and set default configuration
	* Add ability to set and retrieve parity from C interface.
	* Add ability to set and retrieve stop size from C interface.
	* Add ability to set parity (only from C++ interface)
	* Add ability to set stop size (only from C++ interface)
	* Add ability to set and retrieve data size from C interface.
	* Add ability to set data size (only from C++ interface)
	* Introduce termios configuration set.
	* Add coverage support in Gitlab-CI

2017-09-25	Adrien Oliva <olivaa+gitlab@yapbreak.fr>

	* Add ability to set and retrieve speed from C interface.
	* Create device with C-interface

2017-09-04	Adrien Oliva <adrien.oliva@yapbreak.fr>

	* Fix cppcheck issue
	* Add ability to set and get speed of serial device (Only in C++ interface)
	* Add logger capabilities

2017-09-01	Adrien Oliva <olivaa+gitlab@yapbreak.fr>

	* Really open device and fail with exception if not available.
	* Add logging capabilities
	* Improve coverage
	* Create C++ interface
	* Add cppcheck ability
	* Add destroy function
	* Better handling of coverage report given to jenkins.

2017-08-31	Adrien Oliva <adrien.oliva@yapbreak.fr>

	* Add build badge on README page
	* Remove Electric Fence option since it is not simply compatible with C++ code
	* Fix typo to enable electric fence through configure script.

2017-08-31	Adrien Oliva <olivaa+gitlab@yapbreak.fr>

	* Start implementation of C interface of library with its unittests
	* Create main code structure using Autotools
	* Add README

