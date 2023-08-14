/// \file    Main.cpp
/// \project Articles
/// \module  StringIdentifier
/// \author  Vincent CALISTO (@aredhele33) - https://vincentcalisto.com

#include <string>
#include <iostream>

#include <StringIdentifier.hpp>

int main()
{
    // Compile time hash
    constexpr uint32_t identifierCompileTime = SSID("MyIdentifier");

    // Runtime hash
    std::string foo("MyIdentifier");
    const uint32_t identifierRuntime = DSID(foo.c_str());

    std::cout << "Compile time hash of 'MyIdentifier' : " << identifierCompileTime << std::endl;
    std::cout << "Runtime hash of 'MyIdentifier'      : " << identifierRuntime << std::endl;

    return 0;
}
