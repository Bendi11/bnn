#pragma once
#include "common.hpp"
#include <Eigen/Core>
#include <cstddef>


/**
 * \brief A single layer in a neural network with input and output sizes, plus optional activation
 * function
 */
template<std::size_t IN_SZ, std::size_t OUT_SZ, ActivationFunction Activation = Sigmoid>
class Layer {
public:
    void forward(Eigen::Vector<scalar_t, IN_SZ> const& input) noexcept {
        this->m_out = input.dot(this->m_weight) + this->m_bias;
        for(auto& out : this->m_out) {
            out = Activation::activate(out);
        }
    }
private:
    Eigen::Vector<scalar_t, OUT_SZ> m_bias;
    Eigen::Matrix<scalar_t, OUT_SZ, IN_SZ> m_weight;
    Eigen::Vector<scalar_t, OUT_SZ> m_out;
};
