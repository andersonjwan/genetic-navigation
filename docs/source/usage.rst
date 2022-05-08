Installation
============

This project utilizes both C++ and Python.

Dependencies
------------

To build and run the project, the set of dependencies required include:

C++ Dependencies:
 * `CMake <https://cmake.org/>`_
 * Any compatible C++ compiler (e.g., `GCC <https://gcc.gnu.org/>`_ ,
   `Clang <https://clang.llvm.org/>`_, etc.)

Python Dependencies:
 * numpy
 * random
 * matplotlib
 * kaleido
 * pandas
 * plotly
 * typing
 * multiprocessing

Downloading
-----------

To download the *Genetic Navigation*:

.. code-block:: console

   $ git clone https://github.com/andersonjwan/genetic-navigation.git

Building
--------
With the C++ dependencies installed, to build the project, run the following commands
in the project's root directory:

.. code-block:: console

   $ cmake -B build
   $ cmake --build build

To install the dependencies for the project, run:

.. code-block:: console

   $ pip install .

To run the project, use:

.. code-block:: console

   $ python3 src/simulator/main.py
