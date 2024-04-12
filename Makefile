surveyor:
	gcc -Ideps -Ideps/cwalk main.c -o surveyor

local: 
	clib install;
	gcc -Ideps -Ideps/cwalk main.c -o surveyor;
	mv ./surveyor /usr/local/bin;

leak:
	make clean;
	make;
	valgrind --leak-check=yes ./surveyor
	
test:
	make clean;
	cd ./tests; gcc -I../deps -I../deps/cwalk -I../modules tests.c -o all_tests.o -pthread -lcheck -lsubunit -lrt -lm; ./all_tests.o
	rm -rf ./tests/getfilestest

clean:
	rm -rf ./surveyor
	rm -rf ./tests/.o
	rm -rf ./tests/getfilestest
