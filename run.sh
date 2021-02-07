make clean
make console
for count in $(seq 1 100)
do
	./console >> results.dat
done
