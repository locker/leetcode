Solutions of LeetCode problems
==============================

Solving problems just for fun.

Repository structure
--------------------

Each directory except `template` contains a solution of the eponymous LeetCode problem.
The `template` directory is a skeleton to create a new solution directory.
Inside a solution directory there are the following files:

 - `link.txt` contains a link to the problem description at LeetCode.

 - `problem.txt` contains the problem description.

 - `solution.cpp` contains the problem solution.

 - `Makefile` is a makefile to build the problem solution.

The solution executable built by the makefile is named `solution`.

Prerequisites
-------------

GNU Make and a decent C++ compiler supporting at least C++11 are required to build solutions.

Building and running
--------------------

To build all solutions, run `make all` or simply `make` in the repository root directory.
To clean up, run `make clean`.

To build a particular solution, run `make <problem-name>` or enter the problem directory
and run `make`.

To execute a solution, run `<problem-name>/solution`.

Licensing
---------

The source code is free to use and redistribute under the terms of the FreeBSD License.
See [COPYING](https://github.com/locker/leetcode/blob/master/COPYING) for the full license text.
