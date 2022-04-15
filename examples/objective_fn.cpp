#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <string>

#include "algorithm.hpp"
#include "algorithm/options.hpp"
#include "algorithm/termination.hpp"

#include "operators/crossover.hpp"
#include "operators/mutation.hpp"
#include "operators/selection.hpp"

#include "population.hpp"
#include "population/individual.hpp"

using genalg::algorithm::Options;
using genalg::algorithm::BestLimit;

using genalg::operators::MultiPointCrossover;
using genalg::operators::TournamentSelection;
using genalg::operators::InversionMutation;

using genalg::Population;
using genalg::population::Individual;

using Genome = std::vector<bool>;
using Fitness = double;

// DEFINE for plotting functionality
// Note: Ensure you set -DMATPLOTPLUSPLUS=ON to CMake

// #define PLOT

#ifdef PLOT
#include <matplot/matplot.h>
#endif

#define POPULATION_SIZE 10
#define K_GENERATIONS 500
#define P_MUTATION 0.4

class Solution : public Individual<Genome, Fitness> {
public:
    static int capacity;
    static int bounds;

    explicit Solution(const Genome& g)
        : Individual<Genome, Fitness>(g) {}

    double decimal() const {
        bool sign = this->genome_[0];
        double value = 0;

        // right to left
        for(int i = this->genome_.size() - 1; i > 0; --i) {
            value += std::pow(2, (this->genome_.size() - 1) - i) * this->genome_[i];
        }

        // maximum
        double max = 0;
        for(std::size_t i = 0; i < this->genome_.size(); ++i) {
            max += std::pow(2, i);
        }

        // normalize
        value = (value / max) * this->bounds;

        if(sign) {
            return -value;
        } else {
            return value;
        }
    }

    Fitness fitness() const override {
        double x = this->decimal();
        return std::sin(x) - 0.2 * std::abs(x);
    }
};

int Solution::capacity = 10;
int Solution::bounds = 10;

int
main(int argc, char** argv) {
    std::unique_ptr<Options> options;

    if(argc == 2) {
        // seed provided
        options = std::make_unique<Options>
            (POPULATION_SIZE, P_MUTATION, std::stoul(argv[1]));
    } else {
        options = std::make_unique<Options>
            (POPULATION_SIZE, P_MUTATION);
    }

    // GA operations
    TournamentSelection<Solution, Fitness> selection(2, 0.85);
    MultiPointCrossover<Solution> crossover(2);
    InversionMutation<Solution> mutation;

    BestLimit<Solution, Fitness> termination(100);

    genalg::GeneticAlgorithm<Solution, Fitness>
        ga(&selection, &crossover, &mutation, *options);

    // create a random initial population
    std::default_random_engine engine(options->seed);
    std::uniform_int_distribution<int> idistr(0, 1);
    Population<Solution, Fitness> population(options->population_capacity);

    for(std::size_t i = 0; i < options->population_capacity; ++i) {
        std::vector<bool> genome;

        for(int j = 0; j < Solution::capacity; ++j) {
            genome.push_back(idistr(engine));
        }

        population.add(Solution(genome));
    }

    ga.initialize(population);
    ga.run(termination);

    int i = 0;
    for(const auto& p : ga.generations()) {
        std::cout << "GENERATION " << std::setw(3) << std::setfill('0') << i + 1
                  << " BEST: "
                  << "{" << p.best().first.decimal() << ", "
                  << p.best().second << "}\n";
        ++i;
    }

    #ifdef PLOT
    auto results = ga.generations();

    std::vector<double> index;
    std::vector<double> best;
    std::vector<double> worst;
    std::vector<double> average;

    for(int i = 0; i < results.size(); ++i) {
        index.push_back(i);

        best.push_back(results[i].best().second);
        worst.push_back(results[i].worst().second);
        average.push_back(results[i].average());
    }

    matplot::title("Best, Worst, and Average Fitness per Generation");
    matplot::xlabel("Generation");
    matplot::ylabel("Fitness");

    matplot::hold(matplot::on);
    matplot::plot(index, best);
    matplot::plot(index, worst);
    matplot::plot(index, average);

    auto l = matplot::legend({"best", "worst", "avg"});
    l->location(matplot::legend::general_alignment::bottomright);

    matplot::show();
    #endif
}
