# cython: language_level = 3
# distutils: language = c++

cdef extern from "algorithm/fitness.hpp" namespace "genalg::algorithm":
    cdef cppclass FitnessFunction[G, F]:
        pass

    cdef cppclass ZeroFitnessFunction[G, F]:
        pass
