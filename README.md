Initial port to GNURadio 3.8
=============================

Dependencies:

git, cmake, swig, libitpp-dev

Install apt-file (and apt-file update): check file dependencies in Ubuntu20 after launch. (ex: liborc-0.4).

Some problem with PYTHONPATH? import ITpp_swig as ITpp?
Check: https://wiki.gnuradio.org/index.php/ModuleNotFoundError

Ex: Ubuntu20.04, check module path:
```
export PYTHONPATH="/usr/local/lib/python3/dist-packages:$PYTHONPATH"
```

Variable export to .profile also (to work in companion shell) (set all shells) (+logout).

### C++ Module Debugger

Build with:
``
cmake ../ -DCMAKE_BUILD_TYPE=Debug
``

[CLion](https://youtrack.jetbrains.com/issue/CPP-9386#focus=streamItem-27-2082580.0-0): Run Python Debugger (on a sample .py generated from a flowgraph) and "Attach to Process" (python3.8 + GDB).)

[VSCode](https://wiki.gnuradio.org/index.php/UsingVSCode)

# TODO:
C++ ITpp block initialization in class constructor + port main branch version and blocks.
