all: 	
	cd src && $(MAKE)
clean:
	rm -f src/main
	rm -f src/*.o
	rm -f test/clouding.srv
	rm -f test/*.o

test:
	cd test && $(MAKE)
