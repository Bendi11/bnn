#pragma once
#include <Eigen/Dense>
#include <bits/utility.h>
#include <layer.hpp>
#include <tuple>
#include <utility>

namespace _impl {

template<std::size_t F, std::size_t S> struct term_pair {
    static constexpr const std::size_t FIRST = F;
    static constexpr const std::size_t SECOND = S;
};

template<typename T, std::size_t FIRST, std::size_t SECOND>
struct TermPairCons { typedef term_pair<FIRST, SECOND> value; typedef T next; };

template<typename Layers, std::size_t i1, std::size_t i2, std::size_t... rest>
struct PairConsBuilder : PairConsBuilder<TermPairCons<Layers, i1, i2>, i2, rest...> {};

template<typename Layers, std::size_t i1, std::size_t i2>
struct PairConsBuilder<Layers, i1, i2> { typedef TermPairCons<Layers, i1, i2> List; };

template<typename T, typename... Final>
struct TupleBuilder : TupleBuilder<typename T::next, Layer<T::value::FIRST, T::value::SECOND>, Final...> {};

template<typename... Final>
struct TupleBuilder<std::nullptr_t, Final...> {
    typedef std::tuple<Final...> type;
};

}

template<std::size_t... TOPOLOGY>
class Network {
private:
    template<std::size_t FIRST, std::size_t...>
    static constexpr auto firstval = FIRST;
public:
    static_assert(sizeof...(TOPOLOGY) > 1);

    using Layers = typename _impl::TupleBuilder<
        typename _impl::PairConsBuilder<std::nullptr_t, TOPOLOGY...>::List
    >::type;

    static constexpr const std::size_t INPUT_SIZE = firstval<TOPOLOGY...>;
    static constexpr const std::size_t LAYERS = sizeof...(TOPOLOGY);
    
    /**
     * \brief Feed the given input data through the network, updating the output layer's values
     */
    void forward(Eigen::Vector<scalar_t, INPUT_SIZE> const& input) {
        this->layer<0>().forward(input);
        for(std::size_t i = 0; i < LAYERS; ++i) {
            this->layer<i>().forward(input); 
        }
    }
private:
    template<std::size_t I>
    auto& layer() noexcept {
        return std::get<I>(this->m_layers);
    }

    Layers m_layers;
};
