make ; and for var in 4 1024 4096
# 4 50 64 100 128 416 496 512 1000 1024 2000 2048 3000 3072 4000 4096
	rm -rf /tmp/time /tmp/sys_time

	# time -l ./dyn_void # 174
	time -l ./test.out $var > /tmp/time 2> /tmp/sys_time
	# time -l ./dyn_void $var > /tmp/void_time 2> /tmp/sys_void_time

	set -l real_sys (grep -Eo '([0-9.])+ real' /tmp/sys_time)
	set -l reclaim_sys (grep -Eo '([0-9])+  page reclaims' /tmp/sys_time | grep -Eow "[0-9]+")
	# set -l reclaim_sys_void (grep -Eo '([0-9])+  page reclaims' /tmp/sys_void_time | grep -Eow "[0-9]+")

	rm -rf /tmp/time /tmp/time$var

	set -x DYLD_LIBRARY_PATH (pwd)
	set -x DYLD_INSERT_LIBRARIES (pwd)"/libft_malloc.dylib"
	set -x DYLD_FORCE_FLAT_NAMESPACE 1

	time -l ./test.out $var 2> /tmp/time$var
	# time -l ./dyn_void $var > /tmp/void_time 2> /tmp/void_time$var

	set -x DYLD_INSERT_LIBRARIES ''
	set -l real_nono (grep -Eo '([0-9.])+ real' /tmp/time$var)

	set -l reclaim_nono (grep -Eo '([0-9])+  page reclaims' /tmp/time$var | grep -Eow "[0-9]+")
	# set -l reclaim_nono_void (grep -Eo '([0-9])+  page reclaims' /tmp/void_time$var | grep -Eow "[0-9]+")

	# set -l malloc_count (grep MALLOC log | wc -l)
	# set -l cache_count (grep CACHE log | wc -l)
	# set -l error_count (grep ERROR log | wc -l)
	# set -l new_map_count (grep MAP log | wc -l)

	# cp log log_$var

	if math $reclaim_nono' < '$reclaim_sys > /tmp/res
		echo -e '---- \033[32m '$var'\033[0m ----'
	else
		echo -e '---- \033[31m '$var'\033[0m ----'
	end

	if math $malloc_count' > 0' > /tmp/res

		# head -n 3 log_$var
		grep "~" log_$var
		echo ''
		grep 'Command terminated abnormally.' /tmp/time$var
		echo 'malloc call: '$malloc_count
		echo 'cache call:  '$cache_count
		echo 'error call:  '$error_count
		echo 'newmap call: '$new_map_count
		echo ''
		echo 'newmap call / malloc call: '(echo 'scale=4; '$new_map_count' / '$malloc_count | bc -l)
		echo 'cache call / malloc call:  '(echo 'scale=4; '$cache_count' / '$malloc_count | bc -l)
		echo 'error call / malloc call:  '(echo 'scale=4; '$error_count' / '$malloc_count | bc -l)
		echo ''
		# echo 'reclaim_nono - 175:                '(echo 'scale=4; ('$reclaim_nono' - 175)' | bc -l)
		echo 'reclaim_nono - reclaim_sys: '(echo 'scale=4; ('$reclaim_nono' - '$reclaim_sys')' | bc -l)
		# echo 'reclaim_nono - reclaim_nono_void:  '(echo 'scale=4; ('$reclaim_nono' - '$reclaim_nono_void')' | bc -l)
		# echo 'reclaim_sys - reclaim_sys_void:    '(echo 'scale=4; ('$reclaim_sys' - '$reclaim_sys_void')' | bc -l)
	end

	echo 'reclaim_sys: '$reclaim_sys' vs nonito: '$reclaim_nono

	echo 'real_sys: '$real_sys' vs nonito: '$real_nono
end

# 4096 / 4
# 1024
# 1024 / 4
# 256
#
# 4096 / 32
# 128
# 1024 / 32
# 32
#
# (4096 * 4) / 32
# 512
# (1024 * 4) / 32
# 128
#
# (4096 * 8) / 32
# 1024
# (1024 * 8) / 32
# 256
#
# (4096 * 8) / 4 / 32
# 256
# (4096 * 8) / 4 / 4 / 32
# 64
