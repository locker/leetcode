Solutions of LeetCode problems
==============================

Solving problems just for fun.

Repository structure
--------------------

Problem solutions are located in the `solutions` directory. Each subdirectory
except `template` contains a solution of the eponymous LeetCode problem.
The `template` directory is a skeleton to create a new solution directory.
Inside a solution directory there are the following files:

 - `link.txt` contains a link to the problem description at LeetCode.

 - `problem.txt` contains the problem description.

 - `solution.cpp` contains the problem solution.

 - `Makefile` is a makefile to build the problem solution.

The solution executable built by the makefile is named `solution`.

The `by-difficulty` and `by-tag` directories contain symlinks to solution
directories grouped by difficulty (easy, medium, hard) and tag, respectively.

`add-solution.sh` is a shell script that given a problem name, difficulty,
and a comma-separated list of tags creates the corresponding solution directory
from the template and makes symlinks to it in the `by-difficulty` and `by-tag`
directories.

Prerequisites
-------------

GNU Make and a decent C++ compiler supporting at least C++17 are required to build solutions.

Building and running
--------------------

To build all solutions, run `make all` or simply `make` in the `solutions` directory.
To clean up, run `make clean`.

To build a particular solution, run `make <problem-name>` or enter the problem directory
and run `make`.

To execute a solution, run `<problem-name>/solution`.

Licensing
---------

The source code is free to use and redistribute under the terms of the FreeBSD License.
See [COPYING](https://github.com/locker/leetcode/blob/master/COPYING) for the full license text.
