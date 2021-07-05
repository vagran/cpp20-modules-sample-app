#!/bin/bash

set -ev

CXX_FLAGS="-std=c++20 -fmodules -fimplicit-modules -stdlib=libc++"
CXXM_FLAGS="$CXX_FLAGS --precompile -x c++-module"

/opt/clang-12/bin/clang++ -c $CXXM_FLAGS ../src/impl/std.core.cppm -o std.core.pcm \
    -Xclang -emit-module-interface
    
/opt/clang-12/bin/clang++ -c $CXXM_FLAGS -fmodule-file=std.core.pcm \
    ../src/impl/std.io.cppm -o std.io.pcm \
    -Xclang -emit-module-interface

/opt/clang-12/bin/clang++ -c $CXXM_FLAGS ../src/impl/tmp.cppm -o tmp.pcm \
    -Xclang -emit-module-interface
    
/opt/clang-12/bin/clang++ -c $CXX_FLAGS \
    -fmodule-file=tmp.pcm -fmodule-file=std.io.pcm \
    ../src/impl/tmp_impl.cpp -o tmp_impl.o
    
/opt/clang-12/bin/clang++ -c $CXX_FLAGS \
    -fmodule-file=tmp.pcm \
    ../src/impl/tmp_impl2.cpp -o tmp_impl2.o
    
/opt/clang-12/bin/clang++ -c $CXX_FLAGS \
    -fmodule-file=tmp.pcm \
    ../src/impl/main.cpp -o main.o

/opt/clang-12/bin/clang++ $CXX_FLAGS \
    tmp.pcm tmp_impl.o tmp_impl2.o main.o -o test
