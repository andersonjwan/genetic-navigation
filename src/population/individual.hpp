#ifndef GENALG_POPULATION_INDIVIDUAL_HPP
#define GENALG_POPULATION_INDIVIDUAL_HPP

#include <cstddef>

namespace genalg {
    namespace population {
	template<typename G, typename F>
	class Individual {
	protected:
	    G genome;
	    std::size_t age = 0;

	public:
	    Individual(G g)
		: genome{g} {}

	    G get_genome(void) const;
	    virtual F fitness(void) const = 0;
	};
    }
}

namespace genalg {
    namespace population {
	template<typename G, typename F>
	G Individual<G, F>::get_genome(void) const { return this->genome; }
    }
}

#endif
