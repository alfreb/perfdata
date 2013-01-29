perfdata
========

Collect performance data, while impacting the system as little as possible

Effectively, the program will output most of /proc/stat and all of /proc/meminfo


Installation:
------------
System requirements:
- Linux-like system with linux-like /proc/stat and /proc/meminfo
- g++ (gcc for C++) and make

NOTE: A shared library will be compiled to the program folder, so as to be able to compile without sudo. This requires an environment variable to be set, see last step.

1. Compile with make
```
$ make
```

2. Update the search path for libraries
```
$ . set_libpath.sh
```



Usage:
------------
Print performance data with column names
```
./perfdata -T
```

print performance data without column names
```
./perfdata
```

Example:
--------------
```
./perfdata -T > testdump.txt
./perfdata >> testdump.txt
./perfdata >> testdump.txt
./perfdata >> testdump.txt
```
This will add column headers and 4 (four) lines of performance data to testdump.txt


Future features:
--------------
- Run as daemon
- Collect KVM-data from kvm_stat

Distant future features:
--------------
- Servec-client mode, enabling the system to emit performance data over the network using googles protobuf
