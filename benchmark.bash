#!/bin/bash

./benchmark/a.out

export DYLD_LIBRARY_PATH=`pwd`
export DYLD_INSERT_LIBRARIES=`pwd`"/libft_malloc.dylib"
export DYLD_FORCE_FLAT_NAMESPACE=1

./benchmark/a.out
