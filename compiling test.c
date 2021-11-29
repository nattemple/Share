rm -f *.o *~ core *.x *.pdf
gcc -O3 -I/home/nathant/blis/include/blis -m64 -mavx2 -std=c99 -march=native -fopenmp -D_POSIX_C_SOURCE=200809L -g  -c -o test.o test.c
gcc -O3 -I/home/nathant/blis/include/blis -m64 -mavx2 -std=c99 -march=native -fopenmp -D_POSIX_C_SOURCE=200809L -g  -c -o RandomMatrix.o RandomMatrix.c
gcc test.o RandomMatrix.o -o test.x -lpthread -m64 -lm -fopenmp -g
rm output.txt
./test.x > output.txt

