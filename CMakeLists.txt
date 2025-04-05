cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_CXX_STANDARD 23)
project(ACExternal VERSION 0.1.0 LANGUAGES C CXX)

find_package(imgui CONFIG REQUIRED)

add_executable(ACExternal src/main.cpp src/uihandler.cpp src/ui.cpp src/memoryhelper.cpp src/programdata.cpp src/entity.cpp src/entitymanager.cpp src/features.cpp src/utils.cpp)

target_link_libraries(ACExternal PRIVATE imgui::imgui dwmapi d3dcompiler d3d11 -static-libgcc -static-libstdc++ -static)
target_include_directories(ACExternal PRIVATE include)