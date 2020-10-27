All: framework.o ./O/ AI.o ./bin/
	g++ ./main.cpp ./O/framework.o ./O/AI.o -O3
framework.o: ./O/
	g++ -c ./framework.cpp -o ./O/framework.o -O3
AI.o: ./O/
	g++ -c ./AI.cpp -o ./O/AI.o -O3
./O/:
	mkdir ./O
./bin/:
	mkdir ./bin
clean:
	rm -r ./O
	rm ./a.out
	rm ./bin/*.bin
