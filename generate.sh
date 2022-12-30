rm -rf build
compiler="/bin/clang++"
echo -e "\nGenerating Unit Test build system:"
cmake -DCMAKE_CXX_COMPILER=$compiler -DUNIT_TEST=true  -B build/unit    -G "Ninja" -DCMAKE_BUILD_TYPE=Debug   . 
echo -e "\nGenerating Debug build system:"
cmake -DCMAKE_CXX_COMPILER=$compiler -B build/debug   -G "Ninja" -DCMAKE_BUILD_TYPE=Debug   . 
echo -e "\nGenerating Release build system:"
cmake -DCMAKE_CXX_COMPILER=$compiler -B build/release -G "Ninja" -DCMAKE_BUILD_TYPE=Release . 
