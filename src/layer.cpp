#include <layer.hpp>
#include <iostream>

Layer::Layer(std::size_t input, std::size_t output) :
    m_bias{output},
    m_out{output},
    m_weight{input, output}
{
    this->m_weight.setRandom();
    this->m_bias.setRandom();
}

void Layer::forward(const Eigen::VectorX<scalar_t> &input) noexcept {
    this->m_out = input.transpose() * this->m_weight;
    for(auto& out : this->m_out) {
        out = Sigmoid::activate(out);
    }
}
