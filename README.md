Initial port to GNURadio 3.8
=============================

Dependencies:

git, cmake, swig, libitpp-dev

Install apt-file (and apt-file update): check file dependencies in Ubuntu20 after launch. (ex: liborc-0.4).

Some problem with PYTHONPATH? import ITpp_swig as ITpp?
Check: https://wiki.gnuradio.org/index.php/ModuleNotFoundError
After variable export .py script works from terminal. Flow graph don't work from companion.
