# C-- Compiler

## About

This project is a reduced c compiler.
## Usage

To compile the compiler
```shell
mkdir build
cd build
cmake ..
make
```

To compile a program
```shell
./compiler program.cmm program
```

To compile the msm
```shell
cd msm
make
```

To compile the tester (dependancies: `OpenMP` `pThreads`):
```shell
# If openmp is not installed
sudo apt-get install libomp-dev
```
```shell
mkdir test/build
cd test/build
cmake ..
make
```

To launch premade tests :
```shell
./test/build/tester -m msm/msm -c build/compiler -t test/tests/
```
