#ifndef GENALG_POPULATION_INDIVIDUAL_HPP
#define GENALG_POPULATION_INDIVIDUAL_HPP

#include <cstddef>

namespace genalg {
    namespace population {
	template<typename T, typename F>
	class Individual {
	protected:
	    T m_genome;
	    std::size_t m_age;

	public:
	    Individual(T g)
		: m_genome{g} {}

	    virtual F fitness() = 0;
	};
    }
}

namespace genalg {
    namespace population {
	template<typename T, typename F>
        bool operator<(const Individual<T, F>& i1, const Individual<T, F>& i2) {
	    return i1.genome > i2.genome;
	}
    }
}

#endif
