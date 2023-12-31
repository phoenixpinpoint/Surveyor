surveyor:
	gcc -Ideps -Ideps/cwalk surveyor.c -o surveyor

local: 
	clib install;
	gcc -Ideps -Ideps/cwalk surveyor.c -o surveyor;
	mv ./surveyor /usr/local/bin;

leak:
	make clean;
	make;
	valgrind --leak-check=yes ./surveyor
	
clean:
	rm -rf ./surveyor
	rm -rf ./test/unit
