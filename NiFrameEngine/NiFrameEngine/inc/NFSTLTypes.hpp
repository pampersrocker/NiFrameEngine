#pragma once
#include <deque>
#include <map>
#include <vector>
#include <list>
#ifndef NiFrameVector_h__
#define NiFrameVector_h__

namespace nfe
{

    template < typename T >
    using vector = std::vector < T >;

    template < typename Key, typename Value >
    using map = std::map < Key, Value >;

    template < typename T >
    using list = std::list < T >;

    template < typename T >
    using deque = std::deque < T >;
}

#endif // NiFrameVector_h__