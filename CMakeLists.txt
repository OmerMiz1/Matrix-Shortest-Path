cmake_minimum_required(VERSION 3.15)
project(AlgorithmicProgramming2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
include_directories(/Library/Developer/CommandLineTools/usr/include)

add_executable(AlgorithmicProgramming2 main.cpp server_side.h MySerialServer.cpp MySerialServer.h ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h CacheManager.h FileCacheManager.cpp FileCacheManager.h Solver.h StringReverser.cpp StringReverser.h State.cpp State.h Server.h Main.h Point.cpp Point.h Matrix.cpp Matrix.h SearchableMatrix.cpp SearchableMatrix.h Searchable.h Searcher.h MyParallelServer.cpp MyParallelServer.h SearchableBuilder.cpp SearchableBuilder.h SearchSolver.cpp SearchSolver.h Cloneable.h MyClientHandler.cpp MyClientHandler.h BestFS.cpp BestFS.h HashPriorityQueueBestFirstSearch.cpp HashPriorityQueueBestFirstSearch.h BFS.cpp BFS.h DFS.cpp DFS.h AStar.cpp AStar.h HashPriorityQueueAStar.cpp HashPriorityQueueAStar.h Stringable.h)