#include <cstdlib>
#include <net.hpp>
#include <iostream>
#include <cxxabi.h>

int main(int argc, const char *argv[]) {
    srand(time(NULL));
    auto network = Network{2, 5, 1};

    Eigen::VectorX<scalar_t> input{2};
    input.setRandom();
    network.forward(input);
    std::cout << network.output().output() << std::endl;
}
