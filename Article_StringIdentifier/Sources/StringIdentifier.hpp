/// \file    StringIdentifier.hpp
/// \project Articles
/// \module  StringIdentifier
/// \author  Vincent CALISTO (@aredhele33) - https://vincentcalisto.com

#pragma once

#include <cstdint> //< uint32_t, uint64_t

/// \namespace  impl
namespace impl
{

/// Computes a 32 bits hash from a c-string at compile time.
///
/// \param  str A pointer on the c-string to hash.
/// \param  seed The seed of the hash. Modify it only if you know what you're doing.
/// \return A 32 bits hash of the c-string.
/// \note   This function is tail recursive in C++11.
///         If you only want the compile time version, you can use the consteval keyword
///         from C++20 that can be tested with __cpp_consteval.
constexpr uint32_t HashFunction(const char* str, uint64_t seed = 5381)
{
#if __cplusplus >= 201402L
    // C++14 relaxed a bit the constraints over constexpr
    while(*str)
    {
        seed = (seed << 5U) + seed + *str;
        str++;
    }
    return static_cast<uint32_t>(seed);
#else
    // Else, we have to stick to a recursive constexpr function
    return static_cast<uint32>((!str[0]) ? seed : HashFunction(str + 1, (seed << 5L) + seed + *str));
#endif
}

/// Binds the constexpr hash function to a template parameter
/// to force the compiler to hash the string compile time (only for C++11).
///
/// \tparam the hash as a template parameter.
/// \return see hash_function.
template <uint32_t hash>
inline constexpr uint32_t CompileTimeHash()
{
    return hash;
}

} // !namespace

/// \example DSID
///
/// DSID is the dymanic or runtime version of SSID.
/// It takes in parameter a const char *
/// Example : U32 goID_1 = DSID(go.c_str());
///           U32 goID_2 = DSID("BossDoor");
///           U32 goID_3 = DSID(szP)
#define DSID(string) impl::HashFunction(string)

/// \example SSID
///
/// To pre-hash all strings and get back a 32 bits unsigned int
/// at compile time, you have to call the SSID macro.
/// It takes in parameter a literal const char *
/// Example : uint32_t identifier = SSID("MyLiteralIdentifier");
#define SSID(string) impl::CompileTimeHash<impl::HashFunction(string)>()
