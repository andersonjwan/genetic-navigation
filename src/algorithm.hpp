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

        operators::SelectionOperator<I, F>* selection;
        operators::CrossoverOperator<I>* crossover;
        operators::MutationOperator<I>* mutation;

        const algorithm::Options options;

        std::size_t seed;
        std::default_random_engine rng;

        // Population<I, F> generate(const Population<I, F>& population);
        // std::array<I, 2> select_breeders(const Population<I, F>& population);
        // std::array<I, 2> breed(const I& p1, const I& p2);

    public:
        explicit GeneticAlgorithm(operators::SelectionOperator<I, F>* s,
                                  operators::CrossoverOperator<I>* c,
                                  operators::MutationOperator<I>* m,
                                  algorithm::Options o)
            : selection{s}, crossover{c}, mutation{m}, options{o},
              seed{options.seed}, rng{std::default_random_engine(seed)} {}

        // Population<I, F> update(const Population<I, F>& population);
        // Population<I, F> next(void);
    };
}

namespace genalg {
    /// Select two breeders from the population.
    ///
    /// The set selection method is used to select two individuals from the
    /// provided population.
    ///
    /// @param population The population to select breeders from
    /// @return Two breeders
    // template<typename I, typename F>
    // std::array<I, 2> GeneticAlgorithm<I, F>::select_breeders(const Population<I, F>& population) {
    //     return std::array<I, 2>(select(population), select(population));
    // }

    /// Breed (recombine) two selected individuals.
    ///
    /// @param p1 The first selected breeder
    /// @param p2 The second selected breeder
    /// @return Two new individuals
    // template<typename I, typename F>
    // std::array<I, 2> GeneticAlgorithm<I, F>::breed(const I& p1, const I& p2) {
    //     return crossover(p1, p2);
    // }

    /// Perform the GA algorithm steps to generate a new population.
    ///
    /// Execute the series of GA steps to produce a new population: (1) selection,
    /// (2) recombination, and (3) mutation.
    ///
    /// @param population The base population to generate from
    /// @return The newly generated population
    // template<typename I, typename F>
    // Population<I, F> GeneticAlgorithm<I, F>::generate(const Population<I, F>& population) {
    //     // selection
    //     std::array<I, 2> breeders = select_breeders(population);

    //     // recombination
    //     std::array<I, 2> offspring = breed<I, F>(breeders[0], breeders[1]);

    //     // mutation
    // }

    /// Generate a new population based on the provided population.
    ///
    /// This interface is useful when external factors impact the fitness of
    /// individuals within the population.
    ///
    /// @param population The base population to evolve from
    /// @return The newly generated population
    // template<typename I, typename F>
    // Population<I, F> GeneticAlgorithm<I, F>::update(const Population<I, F>& population) {
    //     return generate(population);
    // }

    /// Generate a new population based on the previous population.
    ///
    /// This interface is useful when internal factors impact the fitness of
    /// individuals within the population (e.g., an objective function)
    ///
    /// @return The newly generated population
    // template<typename I, typename F>
    // Population<I, F> GeneticAlgorithm<I, F>::next(void) {
    //     return generate(generations.back());
    // }
}

#endif
