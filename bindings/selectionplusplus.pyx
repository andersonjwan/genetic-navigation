# distutils: language = c++

from cpp_individual cimport BinaryIndividual
from cpp_selection cimport TournamentSelection as cppTournamentSelection

cdef class TournamentSelection:
    cdef cppTournamentSelection[BinaryIndividual, double]* cpp_selection

    def __cinit__(self, tournament_size=2, p_fittest=0.5, replacement=True):
        """
        """

        self.cpp_selection = new cppTournamentSelection[BinaryIndividual, double](
            s=tournament_size,
            p=p_fittest,
            r=replacement
        )

    def __dealloc__(self):
        """
        """

        del self.cpp_selection
