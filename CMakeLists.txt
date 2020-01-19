cmake_minimum_required(VERSION 3.15)
project(AlgorithmicProgramming2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(AlgorithmicProgramming2 main.cpp server_side.h MySerialServer.cpp MySerialServer.h ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h CacheManager.h FileCacheManager.cpp FileCacheManager.h Solver.h StringReverser.cpp StringReverser.h State.cpp State.h Server.h Main.h Point.cpp Point.h Matrix.cpp Matrix.h SearchableMatrix.cpp SearchableMatrix.h Searchable.h Searcher.h MyParallelServer.cpp MyParallelServer.h SearcheableBuilder.cpp SearcheableBuilder.h MatrixShortestPaths.cpp MatrixShortestPaths.h Cloneable.h MyClientHandler.cpp MyClientHandler.h  BestFirstSearch.cpp BestFirstSearch.h HashPriorityQueue.cpp HashPriorityQueue.h)