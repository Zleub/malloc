set -x DYLD_LIBRARY_PATH (pwd)
set -x DYLD_INSERT_LIBRARIES (pwd)"/libft_malloc.dylib"
set -x DYLD_FORCE_FLAT_NAMESPACE 1

eval $argv # > /tmp/mine
set -x TMP $status
echo '-> '$TMP

set -x DYLD_INSERT_LIBRARIES ''
set -x DYLD_LIBRARY_PATH ''

if test $TMP = '0'
	eval $argv # > /tmp/system
end
# echo $status

# diff -y /tmp/mine /tmp/system
