#!/bin/bash

time ./dyn_test
export DYLD_LIBRARY_PATH=`pwd`
export DYLD_INSERT_LIBRARIES=libft_malloc.dylib
export DYLD_FORCE_FLAT_NAMESPACE=1
time ./dyn_test
