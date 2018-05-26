GCC=gcc -Wall
FLAGS=-L codigo-pato/target -lcodp

OBJECTS = $(patsubst src/%.c, target/%.o, $(wildcard src/*.c))
HEADERS = $(wildcard src/*.h)

target/%.o: src/%.c $(HEADERS)
	mkdir -p target
	$(GCC) -c $< -o $@ $(FLAGS)

run: $(OBJECTS)
	mkdir -p target
	$(GCC) target/*.o -o target/main $(FLAGS)
	./target/main

clean:
	rm -r target
