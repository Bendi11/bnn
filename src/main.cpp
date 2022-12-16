#include <net.hpp>
#include <iostream>
#include <cxxabi.h>

int main(int argc, const char *argv[]) {
    std::cout << abi::__cxa_demangle(typeid(Network<2, 5, 3>::Layers).name(), NULL, NULL, NULL) << std::endl; 
}
