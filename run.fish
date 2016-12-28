function timed
  echo "--------------------"
  echo "    "$argv[1]
  time -l $argv[1]
end

# timed ./stt_temoin
# timed ./stt_test
timed ./dyn_temoin
# timed ./dyn_test

set -x DYLD_LIBRARY_PATH (pwd)
set -x DYLD_INSERT_LIBRARIES libft_malloc.dylib
set -x DYLD_FORCE_FLAT_NAMESPACE 1

# timed ./stt_temoin
# timed ./stt_test
timed ./dyn_temoin
# timed ./dyn_test
