#ifndef GENALG_POPULATION_INDIVIDUAL_HPP
#define GENALG_POPULATION_INDIVIDUAL_HPP

#include <cstddef>

namespace genalg {
    namespace population {
	template<typename T, typename F>
	class Individual {
	private:
	    T m_genome;
	    std::size_t m_age;

	public:
	    Individual(T g)
		: m_genome{g} {}

	    // accessors
	    T genome(void);
	    std::size_t age(void);

	    // mutators
	    void genome(T g);
	    void age(std::size_t a);

	    virtual F fitness() = 0;
	};
    }
}

namespace genalg {
    namespace population {
	template<typename T, typename F>
	T Individual<T, F>::genome(void) { return this->m_genome; }

	template<typename T, typename F>
	std::size_t Individual<T, F>::age(void) { return this->m_age; }

	template<typename T, typename F>
	void Individual<T, F>::genome(T g) { this->m_genome = g; }

	template<typename T, typename F>
	void Individual<T, F>::age(std::size_t a) { this->m_age = a; }

	template<typename T, typename F>
        bool operator<(const Individual<T, F>& i1, const Individual<T, F>& i2) {
	    return i1.genome > i2.genome;
	}
    }
}

#endif
