[![Build](https://img.shields.io/badge/build-passing-green)](https://github.com/akhalid-dev/sparse-solver)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/nlohmann/json.svg?logo=lgtm&logoWidth=18)](https://github.com/akhalid-dev/sparse-solver)

## Installation
Run the following commands on the terminal:
```bash
git clone https://github.com/akhalid-dev/sparse-solver
```
```bash
make clean
```

Sparse solver requires that the correct build directory be places in the Makefile.
Run pwd on linux or Mac to find out the current repository:
```bash
$ pwd
```
Place the working path (pwd result) in the <strong>Makefile<strong> for <strong>SRCDIR</strong>

<strong>Add matrices:</strong>
The matrices torso1 and TSOPF_RS_b678_c2 can be downloaded from:
torso1: https://sparse.tamu.edu/Norris/torso1
TSOPF_RS_b678_c2: https://sparse.tamu.edu/TSOPF/TSOPF_RS_b678_c2

The downloaded files should be added in the matrices folder and the path set in the main.cpp file. Currently it is set to a dummy matrix used to testing purposes.






