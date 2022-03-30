#ifndef GENALG_POPULATION_INDIVIDUAL_HPP
#define GENALG_POPULATION_INDIVIDUAL_HPP

namespace genalg {
    namespace population {
	template<typename T>
	class Individual {
	public:
	    Individual(T g)
		: genome{g} {}

	    T genome;
	};
    }
}

namespace genalg {
    namespace population {
	template<typename T>
        bool operator<(const Individual<T>& i1, const Individual<T>& i2) {
	    return i1.genome > i2.genome;
	}
    }
}

#endif
