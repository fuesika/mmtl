#!/usr/bin/env bash

## configure ###################################################################
#get CMAKE_INSTALL_PREFIX
ROOTDIR="${PWD}"
#set CMAKE_INSTALL_PREFIX
INST_PRFX=''

NCORES=$(grep -ic ^processor /proc/cpuinfo)

## Build MMTL_BEM from scratch #################################################
#clean, create and cd to build-directory
echo "== Configure MMTL-BEM ================================================="
echo "Delete old build-dir and binaries..";
cd "${ROOTDIR}"
[ -d "${ROOTDIR}/build" ] && rm -rIf "${ROOTDIR}/build"
rm -rIf "${ROOTDIR}/bin"     &> /dev/null
mkdir build
cd build
echo "[done]";

#start cmake
echo "Run cmake..";
#cmake ../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$INST_PRFX
cmake ../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$INST_PRFX

## make MMTL-BEM ###############################################################
echo "== Build MMTL-BEM ====================================================="
#echo -n "Build MMTL-BEM now? ([Y]/N)"
#read CONFIRM
#case $CONFIRM in
#  n|N|NO|no|No) echo 'Not building MMTL-BEM. Please cd to build-directory and run "make" and possibly "make install" for manual handling.'
#    ;;
#  *) cd $ROOTDIR/build
    make -j $NCORES
#    ;;
#esac

#install mmtl_bem to binary-directory
make DESTDIR="$ROOTDIR" install
