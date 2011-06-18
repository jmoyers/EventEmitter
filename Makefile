test: test.o
	g++ -o build/test build/test.o

test.o:
	g++ -Ideps/boost_1_46_1/ -c src/test.cpp -o build/test.o 
	
# event.o:
# 	g++ -Ideps/boost_1_46_1/ -c src/event.hpp -o build/event.o
	
clean:
	rm -rf build/*.o