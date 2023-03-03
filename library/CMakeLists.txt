project(DPPHandler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

find_package(DPP REQUIRED)

add_library(DPPHandler STATIC source/CommandBase.cpp source/Handler.cpp header/dpp_handler/CommandBase.h header/dpp_handler/Handler.h source/util/ButtonCollector.cpp)
target_include_directories(DPPHandler PUBLIC header)

target_link_libraries(DPPHandler PUBLIC dpp)