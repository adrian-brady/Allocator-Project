# Allocator Project

This project requires an understanding of C, memory, and allocation strategies.

## C

You should know the following C topics:
- Type casting
- Pointer Arithmetic
- Bit manipulation

Reading: K&R up to chapter 6.

## Memory

This project requires at least a rudimentary understanding of memory, and how memory is laid out in a computer.

Reading: Computing Systems A Programmers Perspective 9.1, 9.2, 9.9.1-9.9.6

## Allocation

You should have a basic understanding of how allocation works, and the techniques used.

Reading: Computing Systems A Programmers Perspective 9.9.7 - 9.9.14

# Usage

There is a collection of tests available in the `./tests/` directory. They test 3 separate functions of the allocator: allocation, freeing, and coalescing. All tests should pass.

The tests have been created with MacBooks in mind, as they have a larger page size than Linux machines. The page size can be modified in the heap.h header file. You'll then have to change the values used in some of the tests, as some use values that are associated with the page size of the MacBook.

Tests can be run using the command `make test`, and individual test suites can be run using their respective commands.

```sh
make test
make test_alloc
make test_free
make test_coal
```

Project files can be built using `make build`, and cleaned using `make clean`. Look at the Makefile for more info, ChatGPT is pretty good with simple Makefiles.

The project builds a shared library in to the `./target` directory, and then the tests are built using it.

All tests are emitted to the `./target/tests` directory.

LLDB can be used on MacBooks to step through and debug the processes.

# Objective

You will build a dynamic memory allocator using the *best-fit* placement policy, and use immediate coalescing.
