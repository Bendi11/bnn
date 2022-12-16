#pragma once
#include <bits/utility.h>
#include <layer.hpp>
#include <tuple>
#include <utility>

namespace _impl {

template<std::size_t f, std::size_t s> struct term_pair {
    static constexpr const std::size_t FIRST = f;
    static constexpr const std::size_t SECOND = s;
};

template<std::size_t... Is>
consteval std::size_t nth(std::size_t i) { return ((std::size_t[]){Is...}); }

template<typename T, std::size_t f, std::size_t s>
struct TermPairCons { typedef term_pair<f, s> value; typedef T next; };

template<typename Layers, std::size_t i1, std::size_t i2, std::size_t... rest>
struct PairConsBuilder : PairConsBuilder<TermPairCons<Layers, i1, i2>, i2, rest...> {};

template<typename Layers, std::size_t i1, std::size_t i2>
struct PairConsBuilder<Layers, i1, i2> { typedef TermPairCons<Layers, i1, i2> List; };

template<typename T>
struct LayerConstructor {
    using type = std::pair<typename LayerConstructor<typename T::next>::type, Layer<T::value::FIRST, T::value::SECOND>>;
};

template<>
struct LayerConstructor<std::nullptr_t> {
    using type = std::nullptr_t;
};

template<typename... Final>
struct LayerDeconstructor;

template<typename First, typename Next, typename... Final>
struct LayerDeconstructor<std::pair<First, Next>, Final...> : LayerDeconstructor<First, Next, Final...> {}; 

template<typename... Final>
struct LayerDeconstructor<std::nullptr_t, Final...> { typedef std::tuple<Final...> type; };

}

template<std::size_t... TOPOLOGY>
class Network {
public:
    using Layers = typename _impl::LayerDeconstructor<
        typename _impl::LayerConstructor<
            typename _impl::PairConsBuilder<std::nullptr_t, TOPOLOGY...>::List    
        >::type
    >::type;
private:
    Layers m_layers;
};
