#ifndef GENALG_ALGORITHM_HPP
#define GENALG_ALGORITHM_HPP

#include <cassert>
#include <cstddef>
#include <memory>
#include <random>
#include <vector>

#include "algorithm/options.hpp"
#include "algorithm/termination.hpp"
#include "operators/crossover.hpp"
#include "operators/selection.hpp"
#include "operators/mutation.hpp"
#include "population.hpp"

namespace genalg {
    /// The entry point interface to run the Genetic Algorithm (GA) flow.
    ///
    /// The Genetic Algorithm (GA) is broken down into to two main steps: (1)
    /// initialize the first population---usually performed randomly---with
    /// \ref initialize and (2) running the \ref update or \ref next functions
    /// to perform the GA for one step of a generation.
    ///
    /// @tparam I An individual
    /// @tparam F The metric used to evaluate fitness
    template<typename I, typename F>
    class GeneticAlgorithm {
    private:
        std::vector<Population<I, F>> generations_;

        const operators::SelectionOperator<I, F>* selection_;
        const operators::CrossoverOperator<I>* crossover_;
        const operators::MutationOperator<I>* mutation_;
        const algorithm::Options options_;

        const std::size_t seed_;
        std::default_random_engine rng_;

        // internal functions
        Population<I, F> generate_(const Population<I, F>& population);

    public:
        explicit GeneticAlgorithm(operators::SelectionOperator<I, F>* s,
                                  operators::CrossoverOperator<I>* c,
                                  operators::MutationOperator<I>* m,
                                  algorithm::Options o)
            : selection_{s},crossover_{c}, mutation_{m}, options_{o},
              seed_{options_.seed}, rng_{std::default_random_engine(this->seed_)} {}

        // accessors
        const std::size_t& seed() const { return this->options_.seed; }
        const std::vector<Population<I, F>>& generations() const { return this->generations_; }

        void initialize(const Population<I, F>& population);

        void run(algorithm::TerminationCondition<I, F>& termination);
        Population<I, F> update(const Population<I, F>& population);
        Population<I, F> next(void);
    };
}

namespace genalg {
    /// Initialize the GA with the first \ref Population.
    ///
    /// Provide a \ref Population of initial solutions to generate from.
    ///
    /// @param population An initial \ref Population set
    template<typename I, typename F>
    void GeneticAlgorithm<I, F>::initialize(const Population<I, F>& population) {
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
    template<typename I, typename F>
    Population<I, F> GeneticAlgorithm<I, F>::generate_(const Population<I, F>& population) {
        Population<I, F> new_population(this->options_.population_capacity);
        std::uniform_real_distribution<double> rdistr(0.0, 1.0);

        while(new_population.size() < this->options_.population_capacity) {
            // selection
            I p1 = this->selection_->select(population.solutions(), this->rng_);
            I p2 = this->selection_->select(population.solutions(), this->rng_);

            // recombination
            std::array<I, 2> offspring = this->crossover_->cross(p1, p2, this->rng_);

            // mutation
            for(int i = 0; i < offspring.size(); ++i) {
                if(rdistr(this->rng_) < this->options_.p_mutation) {
                    offspring[i] = this->mutation_->mutate(offspring[i], this->rng_);
                }
            }

            // add to population
            for(auto& x : offspring) {
                if(new_population.size() < this->options_.population_capacity) {
                    new_population.add(x);
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
    template<typename I, typename F>
    void GeneticAlgorithm<I, F>::run(algorithm::TerminationCondition<I, F>& termination) {
        while(!termination.terminate(this->next()));
    }

    /// Generate a new population based on the provided population.
    ///
    /// This interface is useful when external factors impact the fitness of
    /// individuals within the population.
    ///
    /// @param population The base population to evolve from
    /// @return A newly generated population
    template<typename I, typename F>
    Population<I, F> GeneticAlgorithm<I, F>::update(const Population<I, F>& population) {
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
    template<typename I, typename F>
    Population<I, F> GeneticAlgorithm<I, F>::next() {
        assert(this->generations_.size() > 0);

        // evolve next population
        auto new_population = this->generate_(this->generations_.back());
        this->generations_.push_back(new_population);

        return this->generations_.back();
    }
}

#endif
