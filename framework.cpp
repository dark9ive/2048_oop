#include<time.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<math.h>
#include<climits>
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
	for(int a = 0; a < 4; a++){
		board[a] = 0;
	}
	points = 0;
	for(int a = 0; a < 2; a++){	//	Initialize with two blocks;
		new_block();
	}
}
game::game(const game &previous){
	board = new int[SIZE];
	points = previous.points;
	memcpy(board, previous.board, sizeof(int)*SIZE);
}

game::~game(){
	delete [] board;
}

int game::show_points(){
	return points;
}

void game::set_board(int* source){
	memcpy(board, source, sizeof(int)*SIZE);
	return;
}

int* game::board_pointer(){
	return board;
}

int* game::points_pointer(){
	return &points;
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

void game::get_line_index(int* array){
	int positive[8] = {0};
	//int negative[8] = {0};
	for(int a = 0; a < 4; a++){
		positive[2] += (((board[a]>>(0*4))&0xF)<<(4*a));
		positive[3] += (((board[a]>>(3*4))&0xF)<<(4*a));
		positive[6] += (((board[a]>>(1*4))&0xF)<<(4*a));
		positive[7] += (((board[a]>>(2*4))&0xF)<<(4*a));
		/*
		negative[0] += (((board[0]>>(4*a))&0xF)<<(4*(4-1-a)));
		negative[1] += (((board[3]>>(4*a))&0xF)<<(4*(4-1-a)));
		negative[4] += (((board[1]>>(4*a))&0xF)<<(4*(4-1-a)));
		negative[5] += (((board[2]>>(4*a))&0xF)<<(4*(4-1-a)));
		negative[2] += (((board[4-1-a]>>(0*4))&0xF)<<(4*a));
		negative[3] += (((board[4-1-a]>>(3*4))&0xF)<<(4*a));
		negative[6] += (((board[4-1-a]>>(1*4))&0xF)<<(4*a));
		negative[7] += (((board[4-1-a]>>(2*4))&0xF)<<(4*a));
		*/
	}
	positive[0] = board[0];
	positive[1] = board[3];
	positive[4] = board[1];
	positive[5] = board[2];
	for(int a = 0; a < 8; a++){
		//array[a] = std::min(positive[a], negative[a]);
		array[a] = positive[a];
	}
	return;
}

void game::get_axe_index(int* array){
	int array2d[4][4];
	for(int a = 0; a < 4; a++){
		for(int b = 0; b < 4; b++){
			array2d[a][b] = (board[a]>>(4*b))&0xF;
		}
	}
	array[0] = (array2d[0][3]<<(4*0)) + (array2d[0][2]<<(4*1)) + (array2d[0][1]<<(4*2)) + (array2d[0][0]<<(4*3)) + (array2d[1][0]<<(4*4)) + (array2d[1][1]<<(4*5));
	array[1] = (array2d[0][0]<<(4*0)) + (array2d[0][1]<<(4*1)) + (array2d[0][2]<<(4*2)) + (array2d[0][3]<<(4*3)) + (array2d[1][3]<<(4*4)) + (array2d[1][2]<<(4*5));
	array[2] = (array2d[3][3]<<(4*0)) + (array2d[3][2]<<(4*1)) + (array2d[3][1]<<(4*2)) + (array2d[3][0]<<(4*3)) + (array2d[2][0]<<(4*4)) + (array2d[2][1]<<(4*5));
	array[3] = (array2d[3][0]<<(4*0)) + (array2d[3][1]<<(4*1)) + (array2d[3][2]<<(4*2)) + (array2d[3][3]<<(4*3)) + (array2d[2][3]<<(4*4)) + (array2d[2][2]<<(4*5));

	array[4] = (array2d[3][0]<<(4*0)) + (array2d[2][0]<<(4*1)) + (array2d[1][0]<<(4*2)) + (array2d[0][0]<<(4*3)) + (array2d[0][1]<<(4*4)) + (array2d[1][1]<<(4*5));
	array[5] = (array2d[0][0]<<(4*0)) + (array2d[1][0]<<(4*1)) + (array2d[2][0]<<(4*2)) + (array2d[3][0]<<(4*3)) + (array2d[3][1]<<(4*4)) + (array2d[2][1]<<(4*5));
	array[6] = (array2d[3][3]<<(4*0)) + (array2d[2][3]<<(4*1)) + (array2d[1][3]<<(4*2)) + (array2d[0][3]<<(4*3)) + (array2d[0][2]<<(4*4)) + (array2d[1][2]<<(4*5));
	array[7] = (array2d[0][3]<<(4*0)) + (array2d[1][3]<<(4*1)) + (array2d[2][3]<<(4*2)) + (array2d[3][3]<<(4*3)) + (array2d[3][2]<<(4*4)) + (array2d[2][2]<<(4*5));

	array[8] = (array2d[1][3]<<(4*0)) + (array2d[1][2]<<(4*1)) + (array2d[1][1]<<(4*2)) + (array2d[1][0]<<(4*3)) + (array2d[2][0]<<(4*4)) + (array2d[2][1]<<(4*5));
	array[9] = (array2d[1][0]<<(4*0)) + (array2d[1][1]<<(4*1)) + (array2d[1][2]<<(4*2)) + (array2d[1][3]<<(4*3)) + (array2d[2][3]<<(4*4)) + (array2d[2][2]<<(4*5));
	array[10] = (array2d[2][3]<<(4*0)) + (array2d[2][2]<<(4*1)) + (array2d[2][1]<<(4*2)) + (array2d[2][0]<<(4*3)) + (array2d[1][0]<<(4*4)) + (array2d[1][1]<<(4*5));
	array[11] = (array2d[2][0]<<(4*0)) + (array2d[2][1]<<(4*1)) + (array2d[2][2]<<(4*2)) + (array2d[2][3]<<(4*3)) + (array2d[1][3]<<(4*4)) + (array2d[1][2]<<(4*5));

	array[12] = (array2d[3][1]<<(4*0)) + (array2d[2][1]<<(4*1)) + (array2d[1][1]<<(4*2)) + (array2d[0][1]<<(4*3)) + (array2d[0][2]<<(4*4)) + (array2d[1][2]<<(4*5));
	array[13] = (array2d[0][1]<<(4*0)) + (array2d[1][1]<<(4*1)) + (array2d[2][1]<<(4*2)) + (array2d[3][1]<<(4*3)) + (array2d[3][2]<<(4*4)) + (array2d[2][2]<<(4*5));
	array[14] = (array2d[3][2]<<(4*0)) + (array2d[2][2]<<(4*1)) + (array2d[1][2]<<(4*2)) + (array2d[0][2]<<(4*3)) + (array2d[0][1]<<(4*4)) + (array2d[1][1]<<(4*5));
	array[15] = (array2d[0][2]<<(4*0)) + (array2d[1][2]<<(4*1)) + (array2d[2][2]<<(4*2)) + (array2d[3][2]<<(4*3)) + (array2d[3][1]<<(4*4)) + (array2d[2][1]<<(4*5));
	return;
}

void game::get_box_index(int* array){
	int positive[8] = {0};
	int negative[8] = {0};
	int center[8] = {0};
	array[8] = INT_MAX;
	for(int a = 0; a < 4; a++){
		positive[0] += (((board[0+a/2]>>(4*(0+a%2)))&0xF)<<(4*a));
		positive[1] += (((board[0+a/2]>>(4*(3-a%2)))&0xF)<<(4*a));
		positive[2] += (((board[3-a/2]>>(4*(0+a%2)))&0xF)<<(4*a));
		positive[3] += (((board[3-a/2]>>(4*(3-a%2)))&0xF)<<(4*a));

		positive[4] += (((board[0+a/2]>>(4*(1+a%2)))&0xF)<<(4*a));
		positive[5] += (((board[1+a%2]>>(4*(3-a/2)))&0xF)<<(4*a));
		positive[6] += (((board[3-a/2]>>(4*(2-a%2)))&0xF)<<(4*a));
		positive[7] += (((board[2-a%2]>>(4*(0+a/2)))&0xF)<<(4*a));

		negative[0] += (((board[0+a%2]>>(4*(0+a/2)))&0xF)<<(4*a));
		negative[1] += (((board[0+a%2]>>(4*(3-a/2)))&0xF)<<(4*a));
		negative[2] += (((board[3-a%2]>>(4*(0+a/2)))&0xF)<<(4*a));
		negative[3] += (((board[3-a%2]>>(4*(3-a/2)))&0xF)<<(4*a));

		negative[4] += (((board[0+a/2]>>(4*(2-a%2)))&0xF)<<(4*a));
		negative[5] += (((board[2-a%2]>>(4*(3-a/2)))&0xF)<<(4*a));
		negative[6] += (((board[3-a/2]>>(4*(1+a%2)))&0xF)<<(4*a));
		negative[7] += (((board[1+a%2]>>(4*(0+a/2)))&0xF)<<(4*a));

		center[0] += (((board[1+a/2]>>(4*(1+a%2)))&0xF)<<(4*a));
		center[1] += (((board[1+a%2]>>(4*(1+a/2)))&0xF)<<(4*a));
		center[2] += (((board[1+a/2]>>(4*(2-a%2)))&0xF)<<(4*a));
		center[3] += (((board[1+a%2]>>(4*(2-a/2)))&0xF)<<(4*a));

		center[4] += (((board[2-a/2]>>(4*(1+a%2)))&0xF)<<(4*a));
		center[5] += (((board[2-a%2]>>(4*(1+a/2)))&0xF)<<(4*a));
		center[6] += (((board[2-a/2]>>(4*(2-a%2)))&0xF)<<(4*a));
		center[7] += (((board[2-a%2]>>(4*(2-a/2)))&0xF)<<(4*a));
	}
	for(int a = 0; a < 8; a++){
		array[a] = std::min(positive[a], negative[a]);
		array[8] = std::min(array[8], center[a]);
	}
	return;
}

void game::print()
{
    std::cout << "Points: " << points << std::endl;
    for (int a = 0; a < SIZE; a++)
    {
        printf("\e[48;2;187;173;160m\e[38;2;187;173;160m");
        std::cout << "------------";
    }
    std::cout << "--";
    printf("\e[0m");
    std::cout << std::endl;
    for (int a = 0; a < SIZE; a++)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int b = 0; b < SIZE; b++)
            {
                printf("\e[48;2;187;173;160m\e[38;2;187;173;160m");
                std::cout << "||";
                switch ((1 << ((board[a] >> b * 4) & 0xF)))
                {
                case 1:
                    printf("\e[48;2;205;193;180m\e[38;2;119;110;101m");
                    break;
                case 2:
                    printf("\e[48;2;238;228;218m\e[38;2;119;110;101m");
                    break;
                case 4:
                    printf("\e[48;2;238;225;201m\e[38;2;119;110;101m");
                    break;
                case 8:
                    printf("\e[48;2;243;178;122m\e[38;2;249;246;242m");
                    break;
                case 16:
                    printf("\e[48;2;246;150;100m\e[38;2;249;246;242m");
                    break;
                case 32:
                    printf("\e[48;2;247;124;95m\e[38;2;249;246;242m");
                    break;
                case 64:
                    printf("\e[48;2;247;95;59m\e[38;2;249;246;242m");
                    break;
                case 128:
                    printf("\e[48;2;237;208;115m\e[38;2;249;246;242m");
                    break;
                case 256:
                    printf("\e[48;2;237;204;98m\e[38;2;249;246;242m");
                    break;
                case 512:
                    printf("\e[48;2;237;201;80m\e[38;2;249;246;242m");
                    break;
                case 1024:
                    printf("\e[48;2;237;197;63m\e[38;2;249;246;242m");
                    break;
                case 2048:
                    printf("\e[48;2;237;194;46m\e[38;2;249;246;242m");
                    break;
                case 4096:
                    printf("\e[48;2;60;58;51m\e[38;2;249;246;242m");
                    break;
                case 8192:
                    printf("\e[48;2;60;58;51m\e[38;2;249;246;242m");
                    break;
                case 16384:
                    printf("\e[48;2;60;58;51m\e[38;2;249;246;242m");
                    break;
                case 32768:
                    printf("\e[48;2;60;58;51m\e[38;2;249;246;242m");
                    break;
                }
                std::cout << "          ";
            }
            printf("\e[48;2;187;173;160m\e[38;2;187;173;160m");
            std::cout << "||";
            printf("\e[0m");
            std::cout << std::endl;
        }
        for (int b = 0; b < SIZE; b++)
        {
            printf("\e[48;2;187;173;160m\e[38;2;187;173;160m");
            std::cout << "||";
            switch ((1 << ((board[a] >> b * 4) & 0xF)))
            {
            case 1:
                printf("\e[48;2;205;193;180m\e[38;2;119;110;101m");
                std::cout << "     0    ";
                break;
            case 2:
                printf("\e[48;2;238;228;218m\e[38;2;119;110;101m");
                std::cout << "     " << (1 << ((board[a] >> b * 4) & 0xF)) << "    ";
                break;
            case 4:
                printf("\e[48;2;238;225;201m\e[38;2;119;110;101m");
                std::cout << "     " << (1 << ((board[a] >> b * 4) & 0xF)) << "    ";
                break;
            case 8:
                printf("\e[48;2;243;178;122m\e[38;2;249;246;242m");
                std::cout << "     " << (1 << ((board[a] >> b * 4) & 0xF)) << "    ";
                break;
            case 16:
                printf("\e[48;2;246;150;100m\e[38;2;249;246;242m");
                std::cout << "    " << (1 << ((board[a] >> b * 4) & 0xF)) << "    ";
                break;
            case 32:
                printf("\e[48;2;247;124;95m\e[38;2;249;246;242m");
                std::cout << "    " << (1 << ((board[a] >> b * 4) & 0xF)) << "    ";
                break;
            case 64:
                printf("\e[48;2;247;95;59m\e[38;2;249;246;242m");
                std::cout << "    " << (1 << ((board[a] >> b * 4) & 0xF)) << "    ";
                break;
            case 128:
                printf("\e[48;2;237;208;115m\e[38;2;249;246;242m");
                std::cout << "   " << (1 << ((board[a] >> b * 4) & 0xF)) << "    ";
                break;
            case 256:
                printf("\e[48;2;237;204;98m\e[38;2;249;246;242m");
                std::cout << "   " << (1 << ((board[a] >> b * 4) & 0xF)) << "    ";
                break;
            case 512:
                printf("\e[48;2;237;201;80m\e[38;2;249;246;242m");
                std::cout << "   " << (1 << ((board[a] >> b * 4) & 0xF)) << "    ";
                break;
            case 1024:
                printf("\e[48;2;237;197;63m\e[38;2;249;246;242m");
                std::cout << "   " << (1 << ((board[a] >> b * 4) & 0xF)) << "   ";
                break;
            case 2048:
                printf("\e[48;2;237;194;46m\e[38;2;249;246;242m");
                std::cout << "   " << (1 << ((board[a] >> b * 4) & 0xF)) << "   ";
                break;
            case 4096:
                printf("\e[48;2;60;58;51m\e[38;2;249;246;242m");
                std::cout << "   " << (1 << ((board[a] >> b * 4) & 0xF)) << "   ";
                break;
            case 8192:
                printf("\e[48;2;60;58;51m\e[38;2;249;246;242m");
                std::cout << "   " << (1 << ((board[a] >> b * 4) & 0xF)) << "   ";
                break;
            case 16384:
                printf("\e[48;2;60;58;51m\e[38;2;249;246;242m");
                std::cout << "  " << (1 << ((board[a] >> b * 4) & 0xF)) << "   ";
                break;
            case 32768:
                printf("\e[48;2;60;58;51m\e[38;2;249;246;242m");
                std::cout << "  " << (1 << ((board[a] >> b * 4) & 0xF)) << "   ";
                break;
            }
        }
        printf("\e[48;2;187;173;160m\e[38;2;187;173;160m");
        std::cout << "||";
        printf("\e[0m");
        std::cout << std::endl;
        for (int i = 0; i < 2; i++)
        {
            for (int b = 0; b < SIZE; b++)
            {
                printf("\e[48;2;187;173;160m\e[38;2;187;173;160m");
                std::cout << "||";
                switch ((1 << ((board[a] >> b * 4) & 0xF)))
                {
                case 1:
                    printf("\e[48;2;205;193;180m\e[38;2;119;110;101m");
                    break;
                case 2:
                    printf("\e[48;2;238;228;218m\e[38;2;119;110;101m");
                    break;
                case 4:
                    printf("\e[48;2;238;225;201m\e[38;2;119;110;101m");
                    break;
                case 8:
                    printf("\e[48;2;243;178;122m\e[38;2;249;246;242m");
                    break;
                case 16:
                    printf("\e[48;2;246;150;100m\e[38;2;249;246;242m");
                    break;
                case 32:
                    printf("\e[48;2;247;124;95m\e[38;2;249;246;242m");
                    break;
                case 64:
                    printf("\e[48;2;247;95;59m\e[38;2;249;246;242m");
                    break;
                case 128:
                    printf("\e[48;2;237;208;115m\e[38;2;249;246;242m");
                    break;
                case 256:
                    printf("\e[48;2;237;204;98m\e[38;2;249;246;242m");
                    break;
                case 512:
                    printf("\e[48;2;237;201;80m\e[38;2;249;246;242m");
                    break;
                case 1024:
                    printf("\e[48;2;237;197;63m\e[38;2;249;246;242m");
                    break;
                case 2048:
                    printf("\e[48;2;237;194;46m\e[38;2;249;246;242m");
                    break;
                case 4096:
                    printf("\e[48;2;60;58;51m\e[38;2;249;246;242m");
                    break;
                case 8192:
                    printf("\e[48;2;60;58;51m\e[38;2;249;246;242m");
                    break;
                case 16384:
                    printf("\e[48;2;60;58;51m\e[38;2;249;246;242m");
                    break;
                case 32768:
                    printf("\e[48;2;60;58;51m\e[38;2;249;246;242m");
                    break;
                }
                std::cout << "          ";
            }
            printf("\e[48;2;187;173;160m\e[38;2;187;173;160m");
            std::cout << "||";
            printf("\e[0m");
            std::cout << std::endl;
        }
        if (a != SIZE - 1)
        {
            for (int b = 0; b < SIZE; b++)
            {
                printf("\e[48;2;187;173;160m\e[38;2;187;173;160m");
                std::cout << "||----------";
            }
            std::cout << "||";
            printf("\e[0m");
            std::cout << std::endl;
        }
    }
    for (int a = 0; a < SIZE; a++)
    {
        printf("\e[48;2;187;173;160m\e[38;2;187;173;160m");
        std::cout << "------------";
    }
    std::cout << "--";
    printf("\e[0m");
    std::cout << std::endl;
}
