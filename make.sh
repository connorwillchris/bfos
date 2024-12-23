#!/usr/bin/sh
build_dir="build"

if [ ! -e $build_dir ];
then
    echo "== Making build directory =="
    mkdir -p $build_dir
fi

# build the bfcompiler
echo "== Making the compiler =="
gcc -o bfcompiler/bfcompiler \
    bfcompiler/bfcompiler.c \
    bfcompiler/ast.c

# then compile each file in the kernel directory
echo "== Compiling kernel =="
for i in test game;
do
    echo "Compiling file: kernel/$i.b"
    ./bfcompiler/bfcompiler "kernel/$i.b" > "build/$i.s"
done

#cat build/game.s
