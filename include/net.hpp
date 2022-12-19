#pragma once
#include "common.hpp"
#include <Eigen/Dense>
#include <layer.hpp>
#include <iostream>

class Network {
public:
    inline constexpr Layer const& output() const noexcept { return this->m_layers.back(); }

    template<std::convertible_to<std::size_t>... Topology>
    Network(std::size_t input, Topology... topology) {
        static_assert(sizeof...(topology) > 0, "Must have at least two layers when constructing a network");
        this->m_layers.reserve(sizeof...(topology));
        for(std::size_t size : { (std::size_t)topology... }) {
            this->m_layers.push_back(Layer{ input, size });
            input = size;
        }
    }

    /**
     * \brief Feed the given input data through the network, updating the output layer's values
     */
    void forward(Eigen::Ref<const Eigen::VectorX<scalar_t>> input);
    
    scalar_t cost(TrainingInput const& input);
    
    scalar_t cost_avg(std::vector<TrainingInput> const& inputs);

    void train(std::vector<TrainingInput> const& inputs, scalar_t lr);
private:
    std::vector<Layer> m_layers{};
};
