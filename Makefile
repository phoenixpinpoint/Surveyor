all:
	gcc -Ideps -Ideps/cwalk surveyor.c -o surveyor
test:
	cd ./tests; gcc -I../deps -I../deps/cwalk unit.c -lcheck -pthread -lrt -lm -lsubunit -o unit; ./unit
clean:
	rm -rf ./surveyor
	rm -rf ./test/unit
