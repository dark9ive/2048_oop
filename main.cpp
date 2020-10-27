#include"AI.h"
#include<iostream>

using namespace std;

int main(){
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
