#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

template<
    class T,
    class Allocator = std::allocator<T>
> 
using TYVector = std::vector<T, Allocator>;


#define HASHFUNC std::hash<Key>
#define HASHEQUAL  std::equal_to<Key>

template<
    class Key,
    class T,
    class Hash = HASHFUNC,
    class KeyEqual = HASHEQUAL,
    class Allocator = std::allocator< std::pair<const Key, T> >
>
using TYHashMap = std::unordered_map<Key, T, Hash, KeyEqual, Allocator>;


template<
    class Key,
    class Hash = HASHFUNC,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator<Key>
>
using HYHashSet = std::unordered_set<Key, Hash, KeyEqual, Allocator>;
