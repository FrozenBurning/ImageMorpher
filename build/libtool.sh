#!/bin/sh

exe="ImageMorpher" 
des="/home/royubuntu/numerical_analysis/ImageMorpher/3rdparty"

deplist=$(ldd $exe | awk  '{if (match($3,"/")){ printf("%s "),$3 } }')
cp $deplist $des






