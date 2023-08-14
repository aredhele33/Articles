# file      CMakeLists.txt
# project   Articles
# module    StackAllocator
# author    Vincent CALISTO (@aredhele33) - https://vincentcalisto.com

ADD_EXECUTABLE(Article_StackAllocator
        Sources/Main.cpp
        Sources/StackAllocatorGeneric.hpp
        Sources/StackAllocatorSpecialized.hpp)

TARGET_INCLUDE_DIRECTORIES(Article_StackAllocator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sources)
