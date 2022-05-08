for run in {0..3}
do 
	echo "Run #${run}."
	echo "Bulding with optimaztion level: ${run}"
	gcc -O${run} matMult.c -o matMult
	echo "Running performance test for optimization level"
	perf stat -o "Data/o${run}lu0.csv" -x , ./matMult 0
	echo "Done running performance test"
	echo "Run tests for loop unrolling at optimization level ${run}"
	for unrol in {1..3}
	do
		lu=$((2**unrol))
		echo "running performance test with loop unrolling set to ${lu}"
		perf stat -o "Data/o${run}lu${lu}.csv" -x , ./matMult $lu
		echo "Done running performance test"
	done
done
