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

## Expected results
Listed below are the objective values computed by the mutex watershed algorithm and the measured runtime for selected benchmark instances:

|dataset|instance|objective|runtime[s]|
|---|---|---|---|
|image-seg|3096|-638.2|0.0026|
|image-seg|175032|-4102.2|0.0022|
|knott3D|gm-knott-3d-032|-5486.0|0.0051|
|knott3D|gm-knott-3d-096|-87519.3|0.0123|
|CREMI-SP|large-problem-L0|-146315.5|694.5|
|CREMI-SP|large-problem-L4|-150854.5|41.9|