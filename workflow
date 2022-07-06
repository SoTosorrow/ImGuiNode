git submodule add -b docking https://github.com/ocornut/imgui extern/imgui

mv doc/CMakeLists.txt extern/imgui
mv extern/imgui/backends/{gl3,glfw} extern/imgui
cmake .. -G "MinGW Makefiles"
make
mv extern/lib/glfw3.dll build