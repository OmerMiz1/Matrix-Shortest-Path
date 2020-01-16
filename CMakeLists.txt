cmake_minimum_required(VERSION 3.15)
project(AlgorithmicProgramming2)

set(CMAKE_CXX_STANDARD 14)

add_executable(AlgorithmicProgramming2 main.cpp Server.h MySerialServer.cpp MySerialServer.h ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h CacheManager.h FileCacheManager.cpp FileCacheManager.h Solver.cpp Solver.h)