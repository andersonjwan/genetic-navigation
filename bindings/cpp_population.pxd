cdef extern from "population.hpp" namespace "genalg":
    cdef cppclass Population[I, F]:
        Population(size_t s)
