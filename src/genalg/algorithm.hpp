#ifndef GENALG_ALGORITHM_HPP
#define GENALG_ALGORITHM_HPP

#include <cassert>
#include <cstddef>
#include <random>
#include <vector>

#include "algorithm/fitness.hpp"
#include "algorithm/options.hpp"
#include "algorithm/termination.hpp"

#include "operators/crossover.hpp"
#include "operators/selection.hpp"
#include "operators/mutation.hpp"

#include "population.hpp"

namespace genalg {
    /// The entry point interface to run the Genetic Algorithm.
    ///
    /// The Genetic Algorithm (GA) is broken down into to two main steps: (1)
    /// initialize the first population---usually performed randomly---with
    /// \ref initialize and (2) running the \ref update or \ref next functions
    /// to perform the GA for one step of a generation. Otherwise, \ref run can
    /// be used with a provided \ref TerminationCondition.
    ///
    /// @tparam I An individual
    template<typename I, typename G, typename F>
    class GeneticAlgorithm {
    private:
        std::vector<Population<I>> generations_;

        const operators::SelectionOperator<I>* selection_;
        const operators::CrossoverOperator<G>* crossover_;
        const operators::MutationOperator<G>* mutation_;

        const algorithm::FitnessFunction<G, F>* fitness_;
        const algorithm::Options options_;

        const std::size_t seed_;
        std::default_random_engine rng_;

        // internal functions
        Population<I> generate_(const Population<I>& population);

    public:
        explicit GeneticAlgorithm(operators::SelectionOperator<I>* s,
                                  operators::CrossoverOperator<G>* c,
                                  operators::MutationOperator<G>* m,
                                  algorithm::FitnessFunction<G, F>* f,
                                  algorithm::Options o)
            : selection_{s}, crossover_{c}, mutation_{m}, fitness_{f}, options_{o},
              seed_{options_.seed}, rng_{std::default_random_engine(this->seed_)} {}

        // accessors
        std::size_t seed() const { return this->options_.seed; }
        const std::vector<Population<I>>& generations() const { return this->generations_; }

        void initialize(const Population<I>& population);

        void run(algorithm::TerminationCondition<I>& termination);
        Population<I> update(const Population<I>& population);
        Population<I> next();
    };
}

namespace genalg {
    /// Initialize the GA with the first \ref Population.
    ///
    /// Provide a \ref Population of initial solutions to generate from.
    ///
    /// @param population An initial \ref Population set
    template<typename I, typename G, typename F>
    void GeneticAlgorithm<I, G, F>::initialize(const Population<I>& population) {
        assert(population.size() == this->options_.population_capacity);
        this->generations_.push_back(population);
    }

    /// Perform the GA algorithm steps to generate a new \ref Population.
    ///
    /// Execute the series of GA steps to produce a new \ref Population: (1) selection,
    /// (2) recombination, and (3) mutation. Note: This is an internal function.
    /// Therefore, you should use the publicly exposed interfaces:
    /// \ref update or \ref next.
    ///
    /// @param population The base \ref Population to generate from
    /// @return A newly generated \ref Population
    template<typename I, typename G, typename F>
    Population<I> GeneticAlgorithm<I, G, F>::generate_(const Population<I>& population) {
        Population<I> new_population(this->options_.population_capacity);

        while(new_population.size() < this->options_.population_capacity) {
            // selection
            I p1 = this->selection_->select(population, this->rng_);
            I p2 = this->selection_->select(population, this->rng_);

            // recombination
            auto genomes = this->crossover_->cross(p1.genome(), p2.genome(),
                                                   this->rng_);

            std::array<I, 2> offspring = {
                I(genomes[0], this->fitness_->evaluate(genomes[0])),
                I(genomes[1], this->fitness_->evaluate(genomes[1]))
            };

            // mutation
            std::uniform_real_distribution<double> rdistr(0.0, 1.0);

            for(int i = 0; i < offspring.size(); ++i) {
                if(rdistr(this->rng_) < this->options_.p_mutation) {
                    G mutated = this->mutation_->mutate
                        (offspring[i].genome(), this->rng_);

                    offspring[i] = I(mutated, this->fitness_->evaluate(mutated));
                }
            }

            // add to population
            for(auto& x : offspring) {
                if(new_population.size() < this->options_.population_capacity) {
                    new_population.append(x);
                }
            }
        }

        return new_population;
    }

    /// Find the optimal solution using the Genetic Algorithm.
    ///
    /// This will execute the GA until the terminating condition is reached
    /// as defined through the \ref TerminationCondition interface.
    ///
    /// @param termination The \ref TerminationCondition
    template<typename I, typename G, typename F>
    void GeneticAlgorithm<I, G, F>::run(algorithm::TerminationCondition<I>& termination) {
        while(!termination.terminate(this->next()));
    }

    /// Generate a new population based on the provided population.
    ///
    /// This interface is useful when external factors impact the fitness of
    /// individuals within the population.
    ///
    /// @param population The base population to evolve from
    /// @return A newly generated population
    template<typename I, typename G, typename F>
    Population<I> GeneticAlgorithm<I, G, F>::update(const Population<I>& population) {
        assert(population.size() == this->options_.population_capacity);

        // evolve next population
        auto new_population = this->generate_(population);
        this->generations_.push_back(new_population);

        return this->generations_.back();
    }

    /// Generate a new \ref Population based on the previous \ref Population.
    ///
    /// This interface is useful when internal factors impact the fitness of
    /// individuals within the \ref Population (e.g., an objective function)
    ///
    /// @return A newly generated \ref Population
    template<typename I, typename G, typename F>
    Population<I> GeneticAlgorithm<I, G, F>::next() {
        assert(this->generations_.size() > 0);

        // evolve next population
        auto new_population = this->generate_(this->generations_.back());
        this->generations_.push_back(new_population);

        return this->generations_.back();
    }
}

#endif
