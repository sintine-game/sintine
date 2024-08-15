#!/usr/bin/env bash

cmake --build build
cd build/sintine || exit
./sintine
