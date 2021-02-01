for count in $(seq 1 100)
do
	echo $count
	./console >> results.dat
done
