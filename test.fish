for var in 4 50 64 100 128 416 496 1000 1024 2000 2048 3000 3072 4000 4096
	set -l sys (time -l ./a.out $var > /tmp/time ^| grep -Eo '([0-9])+  page reclaims' | grep -Eow "[0-9]+")

	set -x DYLD_LIBRARY_PATH (pwd)
	set -x DYLD_INSERT_LIBRARIES (pwd)"/libft_malloc.dylib"
	set -x DYLD_FORCE_FLAT_NAMESPACE 1

	time -l ./a.out $var > /tmp/time 2> /tmp/time$var

	set -x DYLD_INSERT_LIBRARIES ''

	set -l nono (grep -Eo '([0-9])+  page reclaims' /tmp/time$var | grep -Eow "[0-9]+")
	set -l malloc_count (grep malloc log | wc -l)
	set -l CACHE_count (grep CACHE log | wc -l)
	set -l ERROR_count (grep ERROR log | wc -l)
	set -l new_map_count (grep new_map log | wc -l)

	cp log log_$var

	if math $nono' < '$sys > /tmp/res
		echo -e '---- \033[32m '$var'\033[0m ----'
	else
		echo -e '---- \033[31m '$var'\033[0m ----'
	end
	echo 'malloc call: '$malloc_count
	echo 'cache call:  '$CACHE_count
	echo 'error call:  '$ERROR_count
	echo 'newmap call: '$new_map_count
	echo ''
	echo 'newmap call / malloc call: '(echo 'scale=4; '$new_map_count' / '$malloc_count | bc -l)
	echo 'cache call / malloc call:  '(echo 'scale=4; '$CACHE_count' / '$malloc_count | bc -l)
	echo 'error call / malloc call:  '(echo 'scale=4; '$ERROR_count' / '$malloc_count | bc -l)
	echo ''
	echo $sys' vs '$nono
end
