cd tests.d

for varname in *.c
	clang -O0 -D FT_MALLOC $varname -I../inc -L.. -lft_malloc -L../libft -lft -o $varname.nonito
	clang -O0 $varname -I../inc -L../libft -lft -o $varname.system

	echo $varname
	echo "nonito --------"
	time -l ./$varname.nonito
	echo "system --------"
	time -l ./$varname.system
end
