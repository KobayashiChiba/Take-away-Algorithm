# Take-away-Algorithm
外卖调度算法 by group 6.

To build on MSVC, use ```build.bat```

To build on CMake+GCC, use following: (we havn't tested on CMake+GCC, so compile error might happen)

```bash
mkdir build
cd build
cmake ..
make
```

To use ```plot.py```, use output of compiled ```exec/gen_map.cpp```, then copy the output to corresponding numpy arrays (```data1``` and ```data2```).