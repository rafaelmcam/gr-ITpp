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