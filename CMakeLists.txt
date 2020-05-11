cmake_minimum_required(VERSION 3.10)
project(CAL_FP05)

set(CMAKE_CXX_STANDARD 11)
# The line below is necessary if you are under Windows only
# Comment the line below if you are under Linux or Mac OS
link_libraries(ws2_32 wsock32)

include_directories(GraphViewerLib)
include_directories(src)
include_directories(maps)

set(PROJECT_HEADERS
        src/Cliente.h
        src/EatExpress.h
        src/Estafeta.h
        src/Graph.h
        src/MeioTransporte.h
        src/Menus.h
        src/MutablePriorityQueue.h
        src/Pedido.h
        src/Restaurante.h
        src/utils.h
        GraphViewerLib/connection.h
        GraphViewerLib/edgetype.h
        GraphViewerLib/graphviewer.h
        )
set(PROJECT_SOURCES
        src/main.cpp
        src/Cliente.cpp
        src/EatExpress.cpp
        src/Estafeta.cpp
        src/MeioTransporte.cpp
        src/Menus.cpp
        src/Pedido.cpp
        src/Restaurante.cpp
        GraphViewerLib/connection.cpp
        GraphViewerLib/graphviewer.cpp
        src/Algoritmos.h)

add_executable(CAL_FP05 ${PROJECT_SOURCES} ${PROJECT_HEADERS})
