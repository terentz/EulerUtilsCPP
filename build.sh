#!/bin/bash

# Var's..
P_NAME="EulerUtils"
P_VER=1.0.0
P_BIN=`pwd`

# Get version number..
if [[ -z "$1" ]]; then
    echo "Building $P_NAME version 1.0.0"
else
    if [[ $1 =~ ^[0-9]+(\.[0-9]+)*$ ]]; then
        echo "valid argument"
        P_VER=$1
        echo "Building $P_NAME version $P_VER"
    else 
        echo "$1 is an invalid version number!\nAborting.."
        exit
    fi
fi
IFS='.' read -ra FULL_VER <<< "$P_VER"
P_MAJ="${FULL_VER[0]}"
#echo "major $MAJ"
#exit


# Create the static library ...
g++ -O3 -std=c++11 -c ${P_NAME}.cpp -o obj/${P_NAME}.o
ar rcs lib/lib${P_NAME}.a obj/${P_NAME}.o
rm obj/${P_NAME}.o
echo "static library built.."


# Create the dynamic library...
g++ -O3 -std=c++11 -c -Wall -fPIC ${P_NAME}.cpp -o obj/${P_NAME}.o
g++ -shared -Wl,-soname,lib${P_NAME}.so.${P_MAJ} -o bin/lib${P_NAME}.so.${P_VER} obj/${P_NAME}.o
rm obj/${P_NAME}.o
echo "dynamic library built.."


# Copy the libraries to /usr/local/lib...
echo "copying static library to /usr/local/lib/ .."
cp lib/lib${P_NAME}.a /usr/local/lib/
echo "copying dynamic library to /usr/local/lib/ .."
cp bin/lib${P_NAME}.so.${P_VER} /usr/local/lib/


# Change to /usr/local/lib/ and create the dynamic link
cd /usr/local/lib/
ln -s lib${P_NAME}.so.${P_VER} lib${P_NAME}


exit

