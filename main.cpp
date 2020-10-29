#include"AI.h"
#include<iostream>

using namespace std;

int main(int argc, char* argv[]){
	if(argc == 1){
		cout << "Too few arguments!" << endl;
		return 0;
	}
	if(argc >= 3){
		cout << "Too many arguments!" << endl;
		return 0;
	}
	if(argv[1][0] == '0'){
		AI AI_player;
		Init();
		AI_player.newgame();
		for(int b = 0; b < 10; b++){
			for(int a = 0; a < 10000; a++){
				AI_player.train();
				//AI_player.print_status();
				AI_player.newgame();
			}
			AI_player.print_status();
			AI_player.clear_status();
		}
		AI_player.save();
		return 0;
	}
	else{
		AI AI_player;
		Init();
		AI_player.high_replay();
		return 0;
	}
}
