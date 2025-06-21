// Email: sone0149@gmail.com

# CPP_EX4_25

This project implements a generic C++ container (`MyContainer`) that allows storing elements of various types and provides several different ways to iterate through its contents beside the standard insertion order.

## Files

*   `MyContainer.hpp`
*   `Demo.cpp`
*   `test_mycontainer.cpp`
*   `Makefile`
*   `doctest.h`

## Features

The `MyContainer` class supports:

*   Adding elements (`add`).
*   Removing all instances of a specific element (`remove`).
*   Getting the current number of elements (`size`).
*   Printing the container contents to an output stream (`operator<<`).
*   Multiple distinct iteration orders:
    *   **Normal/Insertion Order**: Iterates through elements in the order they were added.
    *   **Ascending Order**: Iterates through elements in sorted ascending order.
    *   **Descending Order**: Iterates through elements in sorted descending order.
    *   **Side Cross Order**: Alternates between the smallest and largest remaining elements (based on sorted order).
    *   **Reverse Order**: Iterates through elements in reverse of insertion order.
    *   **Middle Out Order**: Iterates starting from the middle element and alternates outwards.

## Building and Running

The project uses a `Makefile` for easy compilation and execution. Navigate to the project directory in your terminal.

*   **To build and run the demo:**
    ```bash
    make Main
    ```
*   **To build and run the unit tests:**
    ```bash
    make test
    ```
*   **To check for memory leaks using Valgrind:**
    ```bash
    make valgrind
    ```
    (Requires Valgrind to be installed)

*   **To clean up compiled files:**
    ```bash
    make clean
    ```


