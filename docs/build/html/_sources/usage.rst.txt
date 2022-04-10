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
 * matplotlib

Downloading
-----------

This project uses `Matplot++ <https://github.com/alandefreitas/matplotplusplus>`_
to visualize the demos. This is an optional dependency and is not required to
use the Genetic Algorithm. Below are the two commands to download this project
with/without dependencies.

To download the *Genetic Navigation*:

.. code-block:: console

   $ git clone https://github.com/andersonjwan/genetic-navigation.git

If the plotting functionality through Matplot++ is preferred,
add :code:`--recurse-submodules` to the command above:

.. code-block:: console

   $ git clone https://github.com/andersonjwan/genetic-navigation.git --recurse-submodules


Building
--------
With the dependencies installed, to build the project, run the following commands
in the project's root directory:

.. code-block:: console

   $ cmake -B build
   $ cmake --build build

If you opted-in to use the optional Matplot++ dependency for plotting functionality,
add the following option to the first command for CMake: :code:`-DMATPLOTPLUSPLUS=ON`.

To run the project, use:

.. code-block:: console

   $ python main.py
