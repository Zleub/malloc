set -l malloc_count (grep malloc log | wc -l)
set -l CACHE_count (grep CACHE log | wc -l)
set -l ERROR_count (grep ERROR log | wc -l)
set -l new_map_count (grep new_map log | wc -l)

echo 'malloc call: '$malloc_count
echo 'cache call:  '$CACHE_count
echo 'error call:  '$ERROR_count
echo 'newmap call:  '$new_map_count

echo 'newmap call / malloc call: '(echo 'scale=4; '$new_map_count' / '$malloc_count | bc -l)
echo 'cache call / malloc call: '(echo 'scale=4; '$CACHE_count' / '$malloc_count | bc -l)
echo 'error call / malloc call: '(echo 'scale=4; '$ERROR_count' / '$malloc_count | bc -l)

