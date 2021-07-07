#!/bin/bash

set -ev

CXX="/opt/clang-12/bin/clang++"
CXX_FLAGS="-std=c++20 -fmodules -fimplicit-modules -stdlib=libc++"
CXXM_FLAGS="$CXX_FLAGS --precompile -x c++-module"

$CXX -c $CXXM_FLAGS ../src/modules/adk/src/adk/std/core.cppm -o std.core.pcm \
    -Xclang -emit-module-interface
    
$CXX -c $CXXM_FLAGS -fmodule-file=std.core.pcm \
    ../src/modules/adk/src/adk/std/io.cppm -o std.io.pcm \
    -Xclang -emit-module-interface

$CXX -c $CXXM_FLAGS ../src/valve_controller/tmp/tmp.cppm -o tmp.pcm \
    -Xclang -emit-module-interface
    
$CXX -c $CXX_FLAGS \
    -fmodule-file=tmp.pcm -fmodule-file=std.io.pcm \
    ../src/valve_controller/tmp/tmp_impl.cpp -o tmp_impl.o
    
$CXX -c $CXX_FLAGS \
    -fmodule-file=tmp.pcm \
    ../src/valve_controller/tmp/tmp_impl2.cpp -o tmp_impl2.o
    
$CXX -c $CXX_FLAGS \
    -fmodule-file=tmp.pcm \
    ../src/valve_controller/main.cpp -o main.o

$CXX $CXX_FLAGS \
    tmp.pcm tmp_impl.o tmp_impl2.o main.o -o valve_controller
