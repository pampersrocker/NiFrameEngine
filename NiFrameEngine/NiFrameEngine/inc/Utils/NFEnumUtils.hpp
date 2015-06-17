#pragma once

#define NF_DEFINE_ENUM_OPERATORS(ENUMTYPE) \
extern "C++" { \
inline ENUMTYPE operator | (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a) | ((int)b)); } \
inline ENUMTYPE &operator |= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) |= ((int)b)); } \
inline ENUMTYPE operator & (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a) & ((int)b)); } \
inline ENUMTYPE &operator &= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) &= ((int)b)); } \
inline ENUMTYPE operator ~ (ENUMTYPE a) { return ENUMTYPE(~((int)a)); } \
inline ENUMTYPE operator ^ (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a) ^ ((int)b)); } \
inline ENUMTYPE &operator ^= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) ^= ((int)b)); } \
}
