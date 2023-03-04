project(DPPHandlerTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt REQUIRED)

add_executable(DPPHandlerTest src/main.cpp src/commands/TestCommandGroup.cpp src/commands/TestCommandGroup.h src/EnvReader.cpp src/EnvReader.h)
target_link_libraries(DPPHandlerTest PRIVATE DPPHandler dpp fmt)