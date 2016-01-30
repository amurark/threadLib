all: Test 
	./Test
	
Test: threadLib.c
	gcc -o Test threadLib.c passing.c queue.c -w

clean:
	rm -rf *o Test
