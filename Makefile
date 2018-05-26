GCC=gcc -Wall

lib: src/lib.c
	mkdir -p target
	$(GCC) -c src/lib.c -o target/lib.o -fPIC -L codigo-pato/target -lcodp
	$(GCC) target/lib.o -shared -o target/codp.so

clean:
	rm -r target
