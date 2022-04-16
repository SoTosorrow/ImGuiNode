cmake_minimum_required(VERSION 3.0)
project(Node)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)

add_subdirectory(extern/imgui)
#add_subdirectory(extern/benchmark)


set(MAIN
    main.cpp 
    )

set(current ${CMAKE_CURRENT_SOURCE_DIR})

set(GLFW_INC "${current}/extern/glfw")
set(GLFW_DLL "${current}/extern/lib/glfw3.dll")

set(IMGUI_INC "${current}/extern/imgui")
set(IMGUI_LIB "${current}/extern/imgui/build/libimgui.a")

# set(GLM_INC "${current}/extern/glm")

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenMP REQUIRED)

include_directories(
    ${GLFW_INC}
    ${IMGUI_INC}
    # ${BENCH_INC}
    # ${GLM_INC}
)

add_executable(a ${MAIN})
add_definitions(-w)

target_link_libraries(a ${GLFW_DLL})
target_link_libraries(a ${IMGUI_LIB})
target_link_libraries(a OpenMP::OpenMP_CXX)
target_link_libraries(a opengl32)
target_link_libraries(a pthread)
# target_compile_options(a PUBLIC -ffast-math -march=native)