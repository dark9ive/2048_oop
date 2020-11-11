All: framework.o ./O/ AI.o demo.o ./bin/
	g++ ./main.cpp ./O/framework.o ./O/AI.o ./O/demo.o -o Game.out
	g++ ./replay.cpp ./O/framework.o ./O/AI.o ./O/demo.o -O3 -o Replay.out
	g++ ./train.cpp ./O/framework.o ./O/AI.o ./O/demo.o -O3 -o Train.out
framework.o: ./O/
	g++ -c ./framework.cpp -o ./O/framework.o
AI.o: ./O/
	g++ -c ./AI.cpp -o ./O/AI.o
demo.o: ./O/
	g++ -c ./demo.cpp -o ./O/demo.o
./O/:
	mkdir ./O
./bin/:
	mkdir ./bin
clean:
	rm -r ./O
	rm ./a.out
	rm ./bin/*.bin
