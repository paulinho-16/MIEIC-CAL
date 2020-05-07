cmake_minimum_required(VERSION 3.10)
project(CAL_FP05)

set(CMAKE_CXX_STANDARD 11)
# The line below is necessary if you are under Windows only
# Comment the line below if you are under Linux or Mac OS
link_libraries(ws2_32 wsock32)

include_directories(GraphViewerLib)
include_directories(src)
include_directories(maps)
add_executable(CAL_FP05 src/main.cpp src/Graph.h src/MutablePriorityQueue.h src/Menus.cpp src/Menus.h src/utils.cpp src/utils.h GraphViewerLib/connection.cpp GraphViewerLib/graphviewer.cpp)
