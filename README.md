# BPB

This in an C++ implementation of [involutive algorithm](https://www.researchgate.net/publication/2117106_Involutive_Algorithms_for_Computing_Groebner_Bases) based on [Pommaret monomial division](https://www.researchgate.net/publication/221564293_A_pommaret_division_algorithm_for_computing_Grobner_bases_in_boolean_rings). The input of `bpb` util is the initial boolean basis in [GNV format](https://github.com/mzinin/groebner_benchmarks), the output is the corresponding boolean [Gröbner basis](https://en.wikipedia.org/wiki/Gröbner_basis).


## Getting Started

### Prerequisites

To compile this project one would need:
* C++ compiler with C++14 support (tested ones are GCC and MSVC)
* CMake >= 3.5.0

### Build

On Linux:
```
cd ./build
cmake ..
make
```
On Windows do the following:
```
cd ./build
cmake ..
```
and open `bpb.sln` with Visual Studio.


## Usage

The `bpb` utility should be run in the following way:
```
./bpb [options] <file_name.gnv>
```

The supported option are:

| Short key | Long key             | Value                      | Description                                          |
|-----------|----------------------|----------------------------|------------------------------------------------------|
| -h        | --help               |                            | print help message and exit                          |
| -v        | --version            |                            | print version and exit                               |
| -s        | --collect-statistics |                            | collect and print out statistics                     |
| -a        | --print-answer       |                            | print out constructed basis                          |
|           | --monomial-order     | lex \| deglex \| degrevlex | monomial ordering to use, supported ones are: pure lexicographic order, degree lexicographic order, degree reverse lexicographic order (default one) |


`bpb` will read the content on the GNV file and build a boolean Gröbner basis for the initial basis. If and only if the GNV file contains the correct answer, the output message `The answer is CORRECT` of `The answer is WRONG` has meaning.

### Get a boolean Gröbner basis

To get the whole answer, i.e. a boolean Gröbner basis, do not forget to add `-a` key:

```
$ ./bpb -a life4.gnv
[0] = x2*x3*x4 + x0*x3 + x1*x3 + x0*x4 + x1*x4 + x2*x4
[1] = x1*x3*x4 + x0*x3 + x2*x3 + x0*x4 + x1*x4 + x2*x4
[2] = x0*x3*x4 + x1*x3 + x2*x3 + x0*x4 + x1*x4 + x2*x4
[3] = x1*x2*x4 + x0*x1 + x0*x2 + x0*x4 + x1*x4 + x2*x4 + x4
[4] = x0*x2*x4 + x0*x1 + x1*x2 + x0*x4 + x1*x4 + x2*x4 + x4
[5] = x0*x1*x4 + x0*x2 + x1*x2 + x0*x4 + x1*x4 + x2*x4 + x4
[6] = x1*x2*x3 + x0*x1 + x0*x2 + x0*x3 + x1*x4 + x2*x4 + x3*x4
[7] = x0*x2*x3 + x0*x1 + x1*x2 + x1*x3 + x0*x4 + x2*x4 + x3*x4
[8] = x0*x1*x3 + x0*x2 + x1*x2 + x2*x3 + x0*x4 + x1*x4 + x3*x4
[9] = x0*x1*x2 + x0*x1 + x0*x2 + x1*x2 + x0*x4 + x1*x4 + x2*x4 + x4

        Memory used: 9.0 Mb
 AutoReduction time: 0.00 sec
       Running time: 0.01 sec

The answer is CORRECT
```

### Run a benchmark

That is the default behavior of the utility. Just run it with GNV file and no other options. It will print the time spent and the memory consumed for constructing boolean Gröbner basis:

```
$ ./bpb life4.gnv
        Memory used: 9.0 Mb
 AutoReduction time: 0.00 sec
       Running time: 0.00 sec

The answer is CORRECT
```

### Get a full statistics:

To get all collected statistics add `-s` key:

```
$ ./bpb -s life9.gnv
Non-Multiple Prolongations considered : 4455
Non-Zero Reductions made              : 1378 (30.93%)
Zero Reductions made                  : 3077 (69.07%)

Average Non-Multiple Prolongation length : 26.99
Average Non-Zero Reduction length        : 32.22

Memory used        : 9.0 Mb
AutoReduction time : 0.00 sec
Running time       : 0.43 sec

The answer is CORRECT
```

### Use another monomial order

Choose a different (from the default DerRevLex one) monomial order can result a different output Gröbner basis as well as increased computation time:

```
$ ./bpb -a --monomial-order=lex life4.gnv
[0] = x1*x3*x4 + x1*x3 + x2*x3*x4 + x2*x3
[1] = x1*x2*x3 + x1*x2*x4 + x1*x3 + x1*x4 + x2*x3*x4 + x2*x4 + x3*x4 + x4
[2] = x0*x3 + x0*x4 + x1*x3 + x1*x4 + x2*x3*x4 + x2*x4
[3] = x0*x2*x4 + x0*x2 + x1*x2*x4 + x1*x2
[4] = x0*x1 + x0*x2 + x0*x4 + x1*x2*x4 + x1*x4 + x2*x4 + x4

        Memory used: 9.0 Mb
 AutoReduction time: 0.00 sec
       Running time: 0.00 sec
```
