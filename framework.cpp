#include<time.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<math.h>
#include"framework.h"
#define SIZE 4

int move_table[0x10<<(SIZE*4)] = {0};
int get_points[0x10<<(SIZE*4)] = {0};

void Init(){
	for(int index = 0; index < (0x10<<(SIZE*4)); index++){
		int row[SIZE] = {0};
		std::vector<int> row_vec;
		for(int a = 0; a < SIZE; a++){
			row[a] = (index >> (a*4))&0xF;
			if(row[a] != 0){
				row_vec.push_back(row[a]);
			}
		}
		for(int a = 0; a < (int)row_vec.size()-1; a++){
			if(row_vec[a] == row_vec[a+1]){
				row_vec[a] += 1;
				row_vec.erase(row_vec.begin()+a+1);
				get_points[index] += 1<<row_vec[a];
			}
		}
		for(int a = 0; a < SIZE; a++){
			if(a < row_vec.size()){
				row[a] = row_vec[a];
			}
			else{
				row[a] = 0;
			}
		}
		for(int a = SIZE-1; a >= 0; a--){
			move_table[index] <<= 4;
			move_table[index] += row[a];
		}
	}
}

game::game(){
	board = new int[SIZE];
	for(int a = 0; a < 2; a++){	//	Initialize with two blocks;
		new_block();
	}
}

game::~game(){
	delete [] board;
}

int game::up(){
	int row[SIZE] = {0};
	int returnval = 0;
	for(int a = 0; a < SIZE; a++){
		for(int b = 0; b < SIZE; b++){
			row[a] += (((board[b]>>(4*a))&0xF)<<(4*b));
		}
	}
	int buf_row;
	int same = 0;
	for(int a = 0; a < SIZE; a++){
		returnval += get_points[row[a]];
		buf_row = move_table[row[a]];
		if(buf_row == row[a]){
			same += 1;
		}
		else{
			row[a] = buf_row;
		}
	}
	if(same == SIZE){
		return -1;
	}
	for(int a = 0; a < SIZE; a++){
		board[a] = 0;
		for(int b = 0; b < SIZE; b++){
			board[a] += (((row[b]>>(4*a))&0xF)<<(4*b));
		}
	}
	return returnval;
}

int game::down(){
	int returnval = 0;
	int row[SIZE] = {0};
	for(int a = 0; a < SIZE; a++){
		row[a] = 0;
		for(int b = 0; b < SIZE; b++){
			row[a] += (((board[b]>>(4*a))&0xF)<<(4*(SIZE-1-b)));
		}
	}
	int buf_row;
	int same = 0;
	for(int a = 0; a < SIZE; a++){
		returnval += get_points[row[a]];
		buf_row = move_table[row[a]];
		if(buf_row == row[a]){
			same += 1;
		}
		else{
			row[a] = buf_row;
		}
	}
	if(same == SIZE){
		return -1;
	}
	for(int a = 0; a < SIZE; a++){
		board[a] = 0;
		for(int b = 0; b < SIZE; b++){
			board[a] += (((row[b]>>(4*(SIZE-a-1)))&0xF)<<(4*b));
		}
	}
	return returnval;
}

int game::left(){
	int returnval = 0;
	int buf_row;
	int same = 0;
	for(int a = 0; a < SIZE; a++){
		returnval += get_points[board[a]];
		buf_row = move_table[board[a]];
		if(buf_row == board[a]){
			same += 1;
		}
		else{
			board[a] = buf_row;
		}
	}
	if(same == SIZE){
		return -1;
	}
	return returnval;
}

int game::right(){
	int returnval = 0;
	int row[SIZE] = {0};
	for(int a = 0; a < SIZE; a++){
		for(int b = 0; b < SIZE; b++){
			row[a] += (((board[a]>>(4*(SIZE-1-b)))&0xF)<<(4*b));
		}
	}
	int buf_row;
	int same = 0;
	for(int a = 0; a < SIZE; a++){
		returnval += get_points[row[a]];
		buf_row = move_table[row[a]];
		if(buf_row == row[a]){
			same += 1;
		}
		else{
			row[a] = buf_row;
		}
	}
	if(same == SIZE){
		return -1;
	}
	for(int a = 0; a < SIZE; a++){
		board[a] = 0;
		for(int b = 0; b < SIZE; b++){
			board[a] += (((row[a]>>(4*(SIZE-1-b)))&0xF)<<(4*b));
		}
	}
	return returnval;
}

bool game::isdead(){
	for(int a = 0; a < SIZE; a++){
		for(int b = 0; b < SIZE; b++){
			if(((board[a]>>(4*b))&0xF) == 0){
				return false;
			}
		}
	}
	for(int a = 0; a < SIZE; a++){
		for(int b = 0; b < SIZE-1; b++){
			if(((board[a]>>(4*b))&0xF) == (((board[a]>>(4*(b+1)))&0xF))){
				return false;
			}
		}
	}
	for(int a = 0; a < SIZE-1; a++){
		for(int b = 0; b < SIZE; b++){
			if(((board[a]>>(4*b))&0xF) == (((board[a+1]>>(4*b))&0xF))){
				return false;
			}
		}
	}
	return true;
}

void game::add_points(int sigma){
	points += sigma;
	return;
}

void game::new_block(){		//	To maximum the efficiency, do &0x7 instead of mod 10.
	srand(clock());
	if(SIZE == 4){
		int posi = rand();
		while((board[(posi&0xC)>>2]&(0xF<<((posi&3)<<2))) != 0){
			posi = rand();
		}
		if(((posi&0x70)>>4) != 0){
			board[(posi&0xC)>>2] += (1<<((posi&3)<<2));
		}
		else{
			board[(posi&0xC)>>2] += (2<<((posi&3)<<2));
		}
		return;
	}
	else{
		int posi_x = rand()%SIZE;
		int posi_y = rand()%SIZE;
		while((board[posi_x]&(0xF<<(posi_y*4))) != 0){
			posi_x = rand()%SIZE;
			posi_y = rand()%SIZE;
		}
		if((rand()&7) != 0){
			board[posi_x] += 1<<(posi_y*4);
		}
		else{
			board[posi_x] += 2<<(posi_y*4);
		}
		return;
	}
}

void game::print(){
	std::cout << "Points: " << points << std::endl;
	for(int a = 0; a < SIZE; a++){
		std::cout << "--------";
	}
	std::cout << "-" << std::endl;
	for(int a = 0; a < SIZE; a++){
		for(int b = 0; b < SIZE; b++){
			std::cout << "|       ";
		}
		std::cout << "|" << std::endl;
		for(int b = 0; b < SIZE; b++){
			if(1<<((board[a]>>b*4)&0xF) == 1){
				std::cout << "|   0   ";
			}
			else{
				switch((int)log10(1<<((board[a]>>b*4)&0xF))){
					case 0:
						std::cout << "|   " << (1<<((board[a]>>b*4)&0xF)) << "   ";
						break;
					case 1:
						std::cout << "|  " << (1<<((board[a]>>b*4)&0xF)) << "   ";
						break;
					case 2:
						std::cout << "|  " << (1<<((board[a]>>b*4)&0xF)) << "  ";
						break;
					case 3:
						std::cout << "| " << (1<<((board[a]>>b*4)&0xF)) << "  ";
						break;
					case 4:
						std::cout << "| " << (1<<((board[a]>>b*4)&0xF)) << " ";
						break;
					case 5:
						std::cout << "|" << (1<<((board[a]>>b*4)&0xF)) << " ";
						break;
					case 6:
						std::cout << "|" << (1<<((board[a]>>b*4)&0xF));
						break;		
				}
			}
		}
		std::cout << "|" << std::endl;
		for(int b = 0; b < SIZE; b++){
			std::cout << "|       ";
		}
		std::cout << "|" << std::endl;
		if(a != SIZE-1){
			for(int b = 0; b < SIZE; b++){
				std::cout << "|-------";
			}
			std::cout << "|" << std::endl;
		}
	}
	for(int a = 0; a < SIZE; a++){
		std::cout << "--------";
	}
	std::cout << "-" << std::endl;
}
