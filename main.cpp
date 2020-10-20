#include "framework.h"
#include<unistd.h>
#include<iostream>
using namespace std;

int main(){
	game a;
	a.print();
	Init();
	char b;
	while(cin >> b){
		system("clear");
		int point = 0;
		switch(b){
			case 'w':
				point = a.up();
				break;
			case 'a':
				point = a.left();
				break;
			case 's':
				point = a.down();
				break;
			case 'd':
				point = a.right();
				break;
		}
		if(point == -1){
			a.print();
			continue;
		}
		a.add_points(point);
		a.new_block();
		a.print();
		if(a.isdead()){
			break;
		}
	}
	return 0;
}
