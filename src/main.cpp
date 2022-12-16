#include <net.hpp>
#include <iostream>
#include <cxxabi.h>

int main(int argc, const char *argv[]) {
    auto network = Network<2, 5, 1>{};
    network.forward({0, 1});
}
