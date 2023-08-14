# file      CMakeLists.txt
# project   Articles
# module    StringIdentifier
# author    Vincent CALISTO (@aredhele33) - https://vincentcalisto.com

ADD_EXECUTABLE(Article_StringIdentifier
        Sources/Main.cpp
        Sources/StringIdentifier.hpp)

TARGET_INCLUDE_DIRECTORIES(Article_StringIdentifier PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sources)
