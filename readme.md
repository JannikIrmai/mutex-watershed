# Mutex watershed implementation in C++

## Build
To build the project with cmake, execute the following commands starting from the project root directory
```
mkdir build
cd build
cmake ..
make
```

## Run

To run the mutex algorithm, execute
```
./main path/to/instance.txt
```
where `instance.txt` is a text file specifying the edge costs of a multicut instance. 
Download links for benchmark instances can be found in [Swoboda et al. (2023)](https://arxiv.org/abs/2202.03574).