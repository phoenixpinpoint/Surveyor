surveyor:
	gcc -Ideps -Ideps/cwalk surveyor.c -o surveyor
clean:
	rm -rf ./surveyor
	rm -rf ./test/unit
