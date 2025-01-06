surveyor:
	gcc -D USE_LIBCURL -Ideps -Ideps/cwalk -pthread main.c -o  surveyor -lcurl

debug: 
	gcc -D USE_LIBCURL -Ideps -Ideps/cwalk -pthread -g main.c -o surveyor_debug -lcurl;
	gdb surveyor_debug;

local: 
	clib install;
	gcc -D USE_LIBCURL -Ideps -Ideps/cwalk -pthread main.c -o surveyor -lcurl;
	sudo rm -rf /usr/local/bin/surveyor;
	sudo mv ./surveyor /usr/local/bin;

leak:
	make clean;
	make;
	valgrind --leak-check=yes ./surveyor
	
test:
	make clean;
	cd ./tests; gcc -D USE_LIBCURL -I../deps -I../deps/cwalk -I../modules tests.c -o all_tests.o -pthread -lcheck -lcurl -lsubunit -lrt -lm; ./all_tests.o
	rm -rf ./tests/getfilestest

filetest:
	make clean;
	cd ./tests; gcc -D STANDALONE -I../deps -I../deps/cwalk file.c -o filetest -pthread -lcheck -lcurl -lsubunit -lrt -lm; ./filetest
	rm -rf ./tests/filestest

clean:
	rm -rf ./surveyor
	rm -rf ./filestest
	rm -rf ./tests/*.o
	rm -rf ./tests/getfilestest
	rm -rf ./tests/filetest
	rm -rf ./tests/*.gcov
	rm -rf ./tests/*.gcda
	rm -rf ./tests/*.gcno
	rm -rf ./tests/debug_tests

coverage:
	make clean;
	gcc -D USE_LIBCURL -fprofile-arcs -ftest-coverage -Ideps -Ideps/cwalk -Imodules tests/tests.c -o tests/coverage.o -pthread -lcheck -lsubunit -lcurl -lrt -lm; ./tests/coverage.o
	mv ./tests.gcda ./tests; mv ./tests.gcno ./tests; cd tests; gcov tests.c

debugt: 
	make clean;
	cd ./tests; gcc -D USE_LIBCURL -I../deps -I../deps/cwalk -I../modules -g tests.c -o debug_tests -pthread -lcheck -lsubunit -lcurl -lrt -lm; gdb debug_tests;
	rm -rf ./tests/getfilestest
