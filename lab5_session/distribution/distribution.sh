#! /bin/sh

n_elems=10000000
n_bits=22
runs=3
freq=3794132


LANG=C
tformat='%U %S'
filename="results.txt"
nombre="distribution.2"


# Para las distribuciones 0 i 1
for d in `seq 0 1 1`; do
	rm -f $n_elems-$d-$filename

	# Para diferentes tamaños de bits
	for b in `seq 1 1 $n_bits`; do

		# Ejecutamos
		printf "$b " >> $n_elems-$d-$filename

		# Ejecutamos run veces y hacemos el cálculo:
		#  Ciclos por elemento: (tiempo*FREQUENCIA/n_elems)/runs
		for i in `seq 1 $runs`; do
			/usr/bin/time -f "$tformat" ./$nombre $n_elems $b $d 2>&1 >/dev/null
		done | awk '/^[0-9]/{user+=$1;sys+=$2;i++} 
			END{printf "%.2f\n",((user+sys)*'$freq'/('$n_elems'*i))}' >> $n_elems-$d-$filename

	done

done

