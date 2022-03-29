#ifndef GENALG_OPERATORS_MUTATION_HPP
#define GENALG_OPERATORS_MUTATION_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <random>
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

namespace genalg {
    namespace operators {
	template<typename T, typename G>
	T GeneReplacement<T, G>::mutate(const T& genome) {
	    T new_genome(genome);

	    std::random_device rd;
	    std::mt19937 gen(rd());

	    std::vector<std::size_t> indices(genome.size());
	    std::iota(indices.begin(), indices.end(), 0);

	    std::shuffle(indices.begin(), indices.end(), gen);

	    std::vector<std::size_t> mutations(this->n_mutations);
	    for(int i = 0; i < this->n_mutations; ++i) {
		mutations[i] = indices[i];
	    }

	    std::uniform_int_distribution<int> distr(0, this->genes.size());
	    for(auto& x : mutations) {
		G gene;

		do {
		    gene = this->genes[distr(gen)];
		} while(gene == new_genome[x]);

		new_genome[x] = gene;
	    }

	    return new_genome;
	}
    }
}

#endif
