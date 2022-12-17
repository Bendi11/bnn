#pragma once
#include <cmath>
#include <concepts>

typedef double scalar_t;

/**
 * \brief Concept that must be fulfilled by all classes that represent a neural network's activation
 * function, requires two static methods for the function and the function's derivative
 */
template<typename T>
concept ActivationFunction = requires(scalar_t scalar) {
    { T::activate(scalar) } -> std::same_as<scalar_t>;
    { T::derivative(scalar) } -> std::same_as<scalar_t>;
};

/**
 * \brief Sigmoid activation function structure
 * \implements ActivationFunction
 */
struct Sigmoid {
    static inline constexpr scalar_t activate(scalar_t v) noexcept {
        return 1. / ( 1. + std::exp(-v) );
    }

    static inline constexpr scalar_t derivative(scalar_t v) noexcept {
        return v * (1. - v);
    }
};

static_assert(ActivationFunction<Sigmoid>);
