#include "framework.h"
#include "getch.h"
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
int main()
{
	game a;
	a.print();
	Init();
	char b;
	while (1)
	{

		int point = 0;
		int c;
		c = getch();
		if (c == 27 || c == 119 || c == 115 || c == 100 || c == 97)
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
							continue;
						}
						a.add_points(point);
						a.new_block();
						a.print();
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
				default:
					break;
				}
				if (point == -1)
				{
					a.print();
					continue;
				}
				a.add_points(point);
				a.new_block();
				a.print();
				if (a.isdead())
					break;
			}
		}
	}
	cout << "Game Over!!" << endl;
	return 0;
}
