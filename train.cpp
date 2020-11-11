#include "AI.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)
		cout << "Usage: ./train.out <train round>" << endl;
	else
	{
		const int N = atoi(argv[1]);
		AI AI_player;
		Init();
		AI_player.newgame();
		for (int a = 1; a <= N; a++)
		{
			AI_player.train();
			AI_player.newgame();
			if (a % 10000 == 0)
			{
				AI_player.print_status();
				AI_player.clear_status();
			}
		}
		AI_player.save();
		return 0;
	}
}