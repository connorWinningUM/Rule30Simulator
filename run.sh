cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON . -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/Rule30