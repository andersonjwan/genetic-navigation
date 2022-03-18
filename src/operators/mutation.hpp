#ifndef GENALG_OPERATORS_MUTATION_HPP
#define GENALG_OPERATORS_MUTATION_HPP

#include <cassert>
#include <cstddef>
#include <vector>

namespace genalg {
    namespace operators {
	template<typename T>
	class MutationOperator {
	public:
	    virtual T mutate(const T& genome) = 0;
	};

	template<typename T, typename G>
	class GeneReplacement : public MutationOperator<T> {
	private:
	    std::vector<G> genes;
	    std::size_t n_mutations;
	    double p = 0.5;

	public:
	    GeneReplacement<T, G>(std::vector<G> gene_pool, std::size_t n)
		: genes {gene_pool}, n_mutations {n} { assert(n_mutations > 0); }

	    GeneReplacement<T, G>(std::vector<G> gene_pool, std::size_t n, double prob)
		: genes {gene_pool}, n_mutations {n}, p {prob} { assert(n_mutations > 0); }

	    virtual T mutate(const T& genome) override;
	};
    }
}

#include "operators/mutation.tpp"
#endif
