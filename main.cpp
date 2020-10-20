#include "framework.h"
#include <bits/stdc++.h>
#include <termios.h>
#include <unistd.h>
using namespace std;
int getch(void)
{
	int c = 0;
	struct termios org_opts, new_opts;
	int res = 0;
	/*---- store old settings ----*/
	res = tcgetattr(STDIN_FILENO, &org_opts);
	assert(res == 0);
	/*---- set new terminal parms ----*/
	memcpy(&new_opts, &org_opts, sizeof(new_opts));
	new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
	c = getchar();
	/*---- restore old settings ----*/
	res = tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
	assert(res == 0);
	return c;
}
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
		if (c == 27)
		{
			c = getch();
			if (c == 91)
			{
				c = getch();
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
				default:
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
		{
			break;
		}
	}
	return 0;
}
