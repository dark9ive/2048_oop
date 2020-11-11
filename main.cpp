#include "framework.h"
#include "getch.h"
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
int main()
{
	game a;
	double start(clock());
	Init();
	double end(clock());
	system("clear");
	a.print();
	cout << "init used time : " << (end - start) / CLOCKS_PER_SEC << " s" << endl;
	cout << "Game Start!" << endl;
	char b;
	int step=0;
	while (1)
	{
		int point = 0;
		int c;
		c = getch();
		if (c == 27 || c == 119 || c == 115 || c == 100 || c == 97 || c == 113)
		{
			if (c == 27)
			{
				c = getch();
				if (c == 91)
				{
					c = getch();
					if (c > 64 && c < 69)
					{
						system("clear");
						switch (c)
						{
						case 65:
							point = a.up();
							break;
						case 66:
							point = a.down();
							break;
						case 67:
							point = a.right();
							break;
						case 68:
							point = a.left();
							break;
						}
						if (point == -1)
						{
							a.print();
							cout << "Use \'Q\' to Leave Game." << endl;
							cout<<"Step: "<<step<<endl;
							continue;
						}
						a.add_points(point);
						a.new_block();
						a.print();
						cout << "Use \'Q\' to Leave Game." << endl;
						cout<<"Step: "<<step++<<endl;
						if (a.isdead())
							break;
					}
				}
			}
			else
			{
				system("clear");
				switch (c)
				{
				case 119:
					point = a.up();
					break;
				case 115:
					point = a.down();
					break;
				case 100:
					point = a.right();
					break;
				case 97:
					point = a.left();
					break;
				case 113:
					a.print();
					cout << "You quit this game. " << endl;
					exit(0);
				}
				if (point == -1)
				{
					a.print();
					cout << "Use \'Q\' to Leave Game. " << endl;
					cout<<"Step: "<<step<<endl;
					continue;
				}
				a.add_points(point);
				a.new_block();
				a.print();
				cout << "Use \'Q\' to Leave Game." << endl;
				cout<<"Step: "<<step++<<endl;
				if (a.isdead())
					break;
			}
		}
		
	}
	system("clear");
	a.print();
	cout << "Game Over!!" << endl;
	return 0;
}
