#pragma once
#include "common.hpp"
#include <Eigen/Core>
#include <cstddef>


/**
 * \brief A single layer in a neural network with input and output sizes, plus optional activation
 * function
 */
class Layer {
public:
    Layer(std::size_t input, std::size_t output);

    constexpr inline std::size_t in_len() const noexcept { return this->m_weight.rows(); }
    constexpr inline std::size_t out_len() const noexcept { return this->m_out.cols(); }
    inline const Eigen::Ref<const Eigen::VectorX<scalar_t>> output() const noexcept { return this->m_out; }

    void forward(Eigen::VectorX<scalar_t> const& input) noexcept;

private:
    Eigen::VectorX<scalar_t> m_bias;
    Eigen::MatrixX<scalar_t> m_weight;
    Eigen::VectorX<scalar_t> m_out;
};
