#!/bin/bash

# Var's..
PRJ="EulerUtils"
VER=1.0.0


# Get version number..
if [[ -z "$1" ]]; then
    echo "Building $PRJ version 1.0.0"
else
    if [[ $1 =~ ^[0-9]+(\.[0-9]+)*$ ]]; then
        echo "valid argument"
        VER=$1
        echo "Building $PRJ version $VER"
    else 
        echo "$1 is an invalid version number!\nAborting.."
        exit
    fi
fi
IFS='.' read -ra FULL_VER <<< "$VER"
MAJ="${FULL_VER[0]}"
#echo "major $MAJ"
#exit

# Create the static library..




# Create the static library ...
g++ -O3 -std=c++11 -c ${PRJ}.cpp -o obj/${PRJ}.o
ar rcs lib/lib${PRJ}.a obj/${PRJ}.o
rm obj/${PRJ}.o
echo "static library done.."


# Create the dynamic library...
g++ -O3 -std=c++11 -c -Wall -fPIC ${PRJ}.cpp -o obj/${PRJ}.o
g++ -shared -Wl,-soname,lib${PRJ}.so.${MAJ} -o bin/lib${PRJ}.so.${VER} obj/${PRJ}.o
rm obj/${PRJ}.o
echo "dynamic library done.."


# Copy the libraries to /usr/local/lib...
cp lib/lib${PRJ}.a /usr/local/lib/
cp bin/lib${PRJ}.so.${VER} /usr/local/lib/


# Change to /usr/local/lib/ and create the dynamic link
cd /usr/local/lib/
ln -s lib${PRJ}.so.${VER} lib${PRJ}


exit

