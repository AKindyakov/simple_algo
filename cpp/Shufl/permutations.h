#pragma once

template<typename TContainer>
class Gen {
public:
    TContainer next();
};

template<typename TCont>
typename TCont::iterator
FindMinGreaterThen(
    typename TCont::iterator begin
    , typename TCont::iterator end
    , const typename TCont::value_type& pivot
);

template<typename TCont>
bool Next(TCont& cont);

#include "next_impl.h"
