#include"AI.h"
#include<unistd.h>

void AI::high_replay(){
	for(int a = 0; a < top_history.size(); a++){
		int foo = system("clear");
		top_history[a]->print();
		usleep(10000);
	}
	return;
}

void AI::demo_play(){
	return;
}
