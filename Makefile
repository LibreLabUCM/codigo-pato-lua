GCC=gcc -Wall

codp: codigo-pato/src
	mkdir -p target/codp
	cd target/codp; $(GCC) -fPIC -c ../../codigo-pato/src/*.c

lib: src/lib.c codp
	mkdir -p target
	$(GCC) -fPIC -shared target/codp/*.o src/lib.c -o target/codp.so

clean:
	rm -r target
