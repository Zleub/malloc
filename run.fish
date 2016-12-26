echo "./stt_temoin" ; and time -l ./stt_temoin
echo "./stt_test" ; and time -l ./stt_test
# echo "./dyn_temoin" ; and time -l ./dyn_temoin
# echo "./dyn_test" ; and time -l ./dyn_test

set -x DYLD_LIBRARY_PATH (pwd)
set -x DYLD_INSERT_LIBRARIES libft_malloc.dylib
set -x DYLD_FORCE_FLAT_NAMESPACE 1

echo "./stt_temoin" ; and time -l ./stt_temoin
echo "./stt_test" ; and time -l ./stt_test
# echo "./dyn_temoin" ; and time -l ./dyn_temoin
# echo "./dyn_test" ; and time -l ./dyn_test

ls -la
