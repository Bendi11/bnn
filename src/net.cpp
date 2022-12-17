#include <net.hpp>
#include <iostream>


void Network::forward(Eigen::Ref<const Eigen::VectorX<scalar_t>> input) {
    for(Layer& layer : this->m_layers) {
        layer.forward(input);
        new (&input) Eigen::Ref<const Eigen::VectorX<scalar_t>>(layer.output());
    }
}
