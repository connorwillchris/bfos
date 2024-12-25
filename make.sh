#!/usr/bin/sh
build_dir="build"

if [ ! -e $build_dir ];
then
    echo "== Making build directory =="
    mkdir -p $build_dir
fi

# build the bfcompiler
# ...

# then compile each file in the kernel directory
echo "== Compiling kernel =="
for i in test game;
do
    echo "Compiling file: kernel/$i.b"
    ./bfcompiler/bfcompiler "kernel/$i.b" > "build/$i.s"
done
