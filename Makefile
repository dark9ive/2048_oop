All: framework.o ./O/
	g++ ./main.cpp ./O/framework.o
framework.o: ./O/
	g++ -c ./framework.cpp -o ./O/framework.o
./O/:
	mkdir ./O
clean:
	rm -r ./O
	rm ./a.out
