#!/bin/bash

set -ev

/opt/clang-12/bin/clang++ -c -std=c++20 -fmodules -stdlib=libc++ -fbuiltin-module-map \
    -fimplicit-module-maps ../src/impl/tmp.cpp -o tmp.pcm \
    -Xclang -emit-module-interface
    
/opt/clang-12/bin/clang++ -c -std=c++20 -fmodules -stdlib=libc++ -fbuiltin-module-map \
    -fimplicit-module-maps -fmodule-file=tmp=tmp.pcm \
    ../src/impl/tmp_impl.cpp -o tmp_impl.o
    
/opt/clang-12/bin/clang++ -c -std=c++20 -fmodules -stdlib=libc++ -fbuiltin-module-map \
    -fimplicit-module-maps -fno-implicit-modules -fmodule-file=tmp=tmp.pcm \
    ../src/impl/main.cpp -o main.o

/opt/clang-12/bin/clang++ -std=c++20 -fmodules -stdlib=libc++ tmp.pcm tmp_impl.o main.o -o test
