set -x DYLD_LIBRARY_PATH (pwd)
set -x DYLD_INSERT_LIBRARIES (pwd)"/libft_malloc.dylib"
set -x DYLD_FORCE_FLAT_NAMESPACE 1

echo 'ft_malloc:'
eval $argv

set -x DYLD_INSERT_LIBRARIES ''

echo 'malloc_machine:'
eval $argv
