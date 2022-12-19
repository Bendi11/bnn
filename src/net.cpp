#include "common.hpp"
#include <net.hpp>
#include <iostream>


void Network::forward(Eigen::Ref<const Eigen::VectorX<scalar_t>> input) {
    for(Layer& layer : this->m_layers) {
        layer.forward(input);
        new (&input) Eigen::Ref<const Eigen::VectorX<scalar_t>>(layer.output());
    }
}

scalar_t Network::cost(TrainingInput const& input) {
    this->forward(input.input);
    scalar_t cost = 0;

    assert(input.expected.size() == this->output().out_len());
    for(std::size_t i = 0; i < input.expected.size(); ++i) {
        scalar_t error = this->output().output()[i] - input.expected[i];
        cost += error * error;
    }

    return cost;
}

scalar_t Network::cost_avg(const std::vector<TrainingInput> &inputs) {
    scalar_t cost;
    for(TrainingInput const& input : inputs) {
        cost += this->cost(input);
    }

    return cost / inputs.size();
}

void Network::train(const std::vector<TrainingInput> &inputs, scalar_t lr) {
        
}
