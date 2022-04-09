#ifndef GENALG_ALGORITHM_HPP
#define GENALG_ALGORITHM_HPP

#include <cstddef>
#include <memory>
#include <random>
#include <vector>

#include "operators/crossover.hpp"
#include "operators/selection.hpp"
#include "operators/mutation.hpp"
#include "algorithm/options.hpp"
#include "population.hpp"

namespace genalg {
    template<typename I, typename F>
    class GeneticAlgorithm {
    public:
        std::vector<Population<I, F>> generations;

        const operators::SelectionOperator<I, F>* selection;
        const operators::CrossoverOperator<I>* crossover;
        const operators::MutationOperator<I>* mutation;

        const algorithm::Options options;

        std::size_t seed;
        std::default_random_engine rng;

        Population<I, F> generate(const Population<I, F>& population);

    public:
        explicit GeneticAlgorithm(operators::SelectionOperator<I, F>* s,
                                  operators::CrossoverOperator<I>* c,
                                  operators::MutationOperator<I>* m,
                                  algorithm::Options o)
            : selection{s}, crossover{c}, mutation{m}, options{o},
              seed{options.seed}, rng{std::default_random_engine(seed)} {}

        void initialize(const Population<I, F>& population);

        Population<I, F> update(const Population<I, F>& population);
        Population<I, F> next(void);
    };
}

namespace genalg {
    /// Initialize the GA with the first generation.
    ///
    /// Provide a population of initial solutions to generate from.
    ///
    /// @param population The initial Population set
    template<typename I, typename F>
    void GeneticAlgorithm<I, F>::initialize(const Population<I, F>& population) {
        assert(population.size() == this->options.population_size);
        this->generations.push_back(population);
    }

    /// Perform the GA algorithm steps to generate a new population.
    ///
    /// Execute the series of GA steps to produce a new population: (1) selection,
    /// (2) recombination, and (3) mutation. Note: This is an internal function.
    /// Therefore, you should use the publicly exposed interfaces: update or next.
    ///
    /// @param population The base population to generate from
    /// @return The newly generated population
    template<typename I, typename F>
    Population<I, F> GeneticAlgorithm<I, F>::generate(const Population<I, F>& population) {
        Population<I, F> new_population(options.population_size);
        std::uniform_real_distribution<double> rdistr(0.0, 1.0);

        while(new_population.size() < this->options.population_size) {
            // selection
            I p1 = this->selection->select(population.solutions(), this->rng);
            I p2 = this->selection->select(population.solutions(), this->rng);

            // recombination
            std::array<I, 2> offspring = this->crossover->cross(p1, p2, this->rng);

            // mutation
            for(int i = 0; i < offspring.size(); ++i) {
                if(rdistr(this->rng) < this->options.mutation_chance) {
                    offspring[i] = this->mutation->mutate(offspring[i]);
                }
            }

            // add to population
            for(auto& x : offspring) {
                if(new_population.size() < this->options.population_size) {
                    new_population.add(x);
                }
            }
        }

        return new_population;
    }

    /// Generate a new population based on the provided population.
    ///
    /// This interface is useful when external factors impact the fitness of
    /// individuals within the population.
    ///
    /// @param population The base population to evolve from
    /// @return The newly generated population
    template<typename I, typename F>
    Population<I, F> GeneticAlgorithm<I, F>::update(const Population<I, F>& population) {
        this->generations.push_back(this->generate(population));
        return this->generations.back();
    }

    /// Generate a new population based on the previous population.
    ///
    /// This interface is useful when internal factors impact the fitness of
    /// individuals within the population (e.g., an objective function)
    ///
    /// @return The newly generated population
    template<typename I, typename F>
    Population<I, F> GeneticAlgorithm<I, F>::next(void) {
        this->generations.push_back(this->generate(this->generations.back()));
        return this->generations.back();
    }
}

#endif
