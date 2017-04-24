cd tests.d

for varname in *.c
	clang -O0 -L.. -lft_malloc -D FT_MALLOC $varname -I../inc -o $varname.nonito
	clang -O0 $varname -I../inc -o $varname.system

	rm -rf /tmp/time /tmp/sys_time
	time -l ./$varname.system > /tmp/time 2> /tmp/sys_time

	set -l real_sys (grep -Eo '([0-9.])+ real' /tmp/sys_time)
	set -l reclaim_sys (grep -Eo '([0-9])+  page reclaims' /tmp/sys_time | grep -Eow "[0-9]+")

	set -x DYLD_LIBRARY_PATH (pwd)'/..'
	set -x DYLD_INSERT_LIBRARIES (pwd)'/..'"/libft_malloc.dylib"
	set -x DYLD_FORCE_FLAT_NAMESPACE 1

	rm -rf /tmp/time /tmp/time$varname
	time -l ./$varname.nonito > /tmp/time 2> /tmp/time$varname
	set -x nonito_status $status

	set -x DYLD_INSERT_LIBRARIES ''

	set -l real_nono (grep -Eo '([0-9.])+ real' /tmp/time$varname)

	set -l reclaim_nono (grep -Eo '([0-9])+  page reclaims' /tmp/time$varname | grep -Eow "[0-9]+")
	set -l malloc_count (grep malloc ../log | wc -l)
	set -l CACHE_count (grep CACHE ../log | wc -l)
	set -l ERROR_count (grep ERROR ../log | wc -l)
	set -l new_map_count (grep new_map ../log | wc -l)

	if math $reclaim_nono' < '$reclaim_sys > /tmp/res
		echo -e '---- \033[32m '$varname'\033[0m ----'
	else
		echo -e '---- \033[31m '$varname'\033[0m ----'
	end

	echo $nonito_status

	cp ../log $varname.log

	if math $malloc_count' > 0' > /tmp/res
		head ../log
		echo ''
		grep 'Command terminated abnormally.' /tmp/time$varname
		echo 'malloc call: '$malloc_count
		echo 'cache call:  '$CACHE_count
		echo 'error call:  '$ERROR_count
		echo 'newmap call: '$new_map_count
		echo ''
		echo 'newmap call / malloc call: '(echo 'scale=4; '$new_map_count' / '$malloc_count | bc -l)
		echo 'cache call / malloc call:  '(echo 'scale=4; '$CACHE_count' / '$malloc_count | bc -l)
		echo 'error call / malloc call:  '(echo 'scale=4; '$ERROR_count' / '$malloc_count | bc -l)
		echo ''
	end

	echo 'reclaim_sys: '$reclaim_sys' vs nonito: '$reclaim_nono
	echo 'real_sys: '$real_sys' vs nonito: '$real_nono
end
