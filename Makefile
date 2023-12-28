surveyor:
	gcc -Ideps -Ideps/cwalk surveyor.c -o surveyor

leak:
	make clean;
	make;
	valgrind --leak-check=yes ./surveyor
	
clean:
	rm -rf ./surveyor
	rm -rf ./test/unit
