#include"AI.h"
#include<fstream>
#include<iostream>
#include<cfloat>
#define SIZE 4
#define LearningRate 0.01
#define AI_MODE 7

AI::AI(){
	if(AI_MODE&7){
		if(!readfile(&played, "./bin/games_played.bin", sizeof(int))){
			played = 0;
			std::cout << "Count file not found." << std::endl;
		}
		if(getfilesize("./bin/highscore_replay.bin")>0){
			int file_size = getfilesize("./bin/highscore_replay.bin");
			int block_size = (sizeof(int)*SIZE+sizeof(int));
			for(int a = 0; a < (file_size/block_size); a++){
				game* buf = new game;
				int point_buf;
				int board_buf[4];
				if(readfile(board_buf, "./bin/highscore_replay.bin", a*block_size, sizeof(int)*SIZE)){
					buf->set_board(board_buf);
				}
				else{
					std::cout << "Read highscore error." << std::endl;
				}
				if(readfile(&point_buf, "./bin/highscore_replay.bin", a*block_size+sizeof(int)*SIZE, sizeof(int))){
					buf->add_points(point_buf);
				}
				else{
					std::cout << "Read highscore error." << std::endl;
				
				}
				top_history.push_back(buf);
			}
		}
		else{
			std::cout << "highscore not found." << std::endl;
		}
		std::cout << "AI MODE: ";
	}
	if(AI_MODE&1){		//	line open.
		std::cout << "line ";
		line_in = new double[1<<16];
		line_out = new double[1<<16];
		if(!readfile(line_in, "./bin/line_in.bin", (1<<19))){
			for(int a = 0; a < (1<<16); a++){
				line_in[a] = 0;
			}
			std::cout << "File not found." << std::endl;
		}
		if(!readfile(line_out, "./bin/line_out.bin", (1<<19))){
			for(int a = 0; a < (1<<16); a++){
				line_out[a] = 0;
			}
			std::cout << "File not found." << std::endl;
		}
	}
	if(AI_MODE&2){		//	axe open.
		std::cout << "axe ";
		axe_in = new double[1<<24];
		axe_out = new double[1<<24];
		if(!readfile(axe_in, "./bin/axe_in.bin", (1<<27))){
			for(int a = 0; a < (1<<24); a++){
				axe_in[a] = 0;
			}
			std::cout << "File not found." << std::endl;
		}
		if(!readfile(axe_out, "./bin/axe_out.bin", (1<<27))){
			for(int a = 0; a < (1<<24); a++){
				axe_out[a] = 0;
			}
			std::cout << "File not found." << std::endl;
		}
	}
	if(AI_MODE&4){		//	box open.
		std::cout << "box";
		box_corn = new double[1<<16];
		box_side = new double[1<<16];
		box_cent = new double[1<<16];
		if(!readfile(box_corn, "./bin/box_corn.bin", (1<<19))){
			for(int a = 0; a < (1<<16); a++){
				box_corn[a] = 0;
			}
			std::cout << "File not found." << std::endl;
		}
		if(!readfile(box_side, "./bin/box_side.bin", (1<<19))){
			for(int a = 0; a < (1<<16); a++){
				box_side[a] = 0;
			}
			std::cout << "File not found." << std::endl;
		}
		if(!readfile(box_cent, "./bin/box_cent.bin", (1<<19))){
			for(int a = 0; a < (1<<16); a++){
				box_cent[a] = 0;
			}
			std::cout << "File not found." << std::endl;
		}
	}
	std::cout << std::endl;
}

AI::~AI(){
	if(AI_MODE&1){
		delete [] line_in;
		delete [] line_out;
	}
	if(AI_MODE&2){
		delete [] axe_in;
		delete [] axe_out;
	}
	if(AI_MODE&4){
		delete [] box_corn;
		delete [] box_side;
		delete [] box_cent;
	}
}

void AI::save(){
	if(AI_MODE&1){		//	line open.
		std::cout << "save 1" << std::endl;
		if(!savefile(line_in, "./bin/line_in.bin", (1<<19))){
			std::cout << "File save error!" << std::endl;
		}
		if(!savefile(line_out, "./bin/line_out.bin", (1<<19))){
			std::cout << "File save error!" << std::endl;
		}
	}
	if(AI_MODE&2){		//	axe open.
		std::cout << "save 2" << std::endl;
		if(!savefile(axe_in, "./bin/axe_in.bin", (1<<27))){
			std::cout << "File save error!" << std::endl;
		}
		if(!savefile(axe_out, "./bin/axe_out.bin", (1<<27))){
			std::cout << "File save error!" << std::endl;
		}
	}
	if(AI_MODE&4){		//	box open.
		std::cout << "save 4" << std::endl;
		if(!savefile(box_corn, "./bin/box_corn.bin", (1<<19))){
			std::cout << "File save error!" << std::endl;
		}
		if(!savefile(box_side, "./bin/box_side.bin", (1<<19))){
			std::cout << "File save error!" << std::endl;
		}
		if(!savefile(box_cent, "./bin/box_cent.bin", (1<<19))){
			std::cout << "File save error!" << std::endl;
		}
	}
	if(AI_MODE&7){
		if(!savefile(&played, "./bin/games_played.bin", sizeof(int))){
			std::cout << "File save error!" << std::endl;
		}
		savefile(NULL, "./bin/highscore_replay.bin", 0);
		for(int a = 0; a < top_history.size(); a++){
			if(!appendfile(top_history[a]->board_pointer(), "./bin/highscore_replay.bin", sizeof(int)*SIZE)){
				std::cout << "File save error!" << std::endl;
			}
			if(!appendfile(top_history[a]->points_pointer(), "./bin/highscore_replay.bin", sizeof(int))){
				std::cout << "File save error!" << std::endl;
			}
		}
	}
}

bool AI::savefile(void* data_ptr, std::string filename, int size){
	std::fstream outfile;
	outfile.open(filename, std::ios::out|std::ios::binary);
	if(outfile.is_open()){
		outfile.write((char*)data_ptr, size);
		return true;
	}
	else{
		return false;
	}
}

bool AI::appendfile(void* data_ptr, std::string filename, int size){
	std::fstream outfile;
	outfile.open(filename, std::ios::out|std::ios::binary|std::ios::app);
	if(outfile.is_open()){
		outfile.write((char*)data_ptr, size);
		return true;
	}
	else{
		return false;
	}
}

bool AI::readfile(void* data_ptr, std::string filename, int size){
	std::fstream infile;
	infile.open(filename, std::ios::in|std::ios::binary);
	if(infile.is_open()){
		infile.read((char*)data_ptr, size);
		return true;
	}
	else{
		return false;
	}
}

bool AI::readfile(void* data_ptr, std::string filename, const unsigned int start, const int size){
	std::fstream infile;
	infile.open(filename, std::ios::in|std::ios::binary);
	if(infile.is_open()){
		infile.seekg(start);
		infile.read((char*)data_ptr, size);
		return true;
	}
	else{
		return false;
	}
}

int AI::getfilesize(std::string filename){
	std::fstream infile;
	infile.open(filename, std::ios::in|std::ios::binary|std::ios::ate);
	if(infile.is_open()){
		return infile.tellg();
	}
	else{
		return -1;
	}
}

void AI::newgame(){
	if(curr_history.size() == 0){
		//
	}
	else if(top_history.size() == 0){
		top_history = curr_history;
	}
	else if(top_history.back()->show_points() < curr_history.back()->show_points()){
		free_history(top_history);
		top_history = curr_history;
	}
	else{
		free_history(curr_history);
	}
	curr_history.clear();
	curr_history.push_back(new game);
	return;
}

void AI::free_history(std::vector<game*> history){
	for(int a = 0; a < history.size(); a++){
		delete history[a];
	}
	return;
}

void AI::train(){
	while(!(curr_history.back()->isdead())){
		double _value_[4];
		double max_value = -DBL_MAX + 1;
		int max_index = -1;
		game* game_copy[4];
		for(int a = 0; a < 4; a++){
			game_copy[a] = new game(*curr_history.back());
		}
		_value_[0] = game_copy[0]->up();
		_value_[1] = game_copy[1]->down();
		_value_[2] = game_copy[2]->right();
		_value_[3] = game_copy[3]->left();
		for(int a = 0; a < 4; a++){
			game_copy[a]->add_points(_value_[a]);
			if(_value_[a] != -1){
				_value_[a] += get_value(game_copy[a]);
			}
			else{
				_value_[a] = -DBL_MAX;
			}
			if(max_value < _value_[a]){
				max_value = _value_[a];
				max_index = a;
			}
		}
		for(int a = 0; a < 4; a++){
			if(a != max_index){
				delete game_copy[a];
			}
			else{
				game_copy[a]->new_block();
				curr_history.push_back(game_copy[a]);
			}
		}
	}
	update();
	total_points += curr_history.back()->show_points();
	played++;
	runtime_played++;
	return;
}

double AI::get_value(game* Game){
	double returnval = 0;
	double mode_count = 0;
	if(AI_MODE&1){		//	Get the line value.
		int index[8];
		double buf = 0;
		Game->get_line_index(index);
		for(int a = 0; a < 4; a++){
			buf += line_out[index[a]];
		}
		for(int a = 4; a < 8; a++){
			buf += line_in[index[a]];
		}
		returnval += buf;
		mode_count += 8;
	}
	if(AI_MODE&2){		//	Get the axe value.
		int index[16];
		double buf = 0;
		Game->get_axe_index(index);
		for(int a = 0; a < 8; a++){
			buf += axe_out[index[a]];
		}
		for(int a = 8; a < 16; a++){
			buf += axe_in[index[a]];
		}
		returnval += buf;
		mode_count += 16;
	}
	if(AI_MODE&4){		//	Get the box value.
		int index[9];
		double buf = 0;
		Game->get_box_index(index);
		for(int a = 0; a < 4; a++){
			buf += box_corn[index[a]];
		}
		for(int a = 4; a < 8; a++){
			buf += box_side[index[a]];
		}
		for(int a = 8; a < 9; a++){
			buf += box_cent[index[a]];
		}
		returnval += buf;
		mode_count += 9;
	}
	return returnval/mode_count;
	//return returnval;
}

void AI::update(){
	const double final_score = curr_history.back()->show_points();

	double parts = 0;
	if(AI_MODE&1){
		parts += 8;
	}
	if(AI_MODE&2){
		parts += 16;
	}
	if(AI_MODE&4){
		parts += 9;
	}
	const double delta = -get_value(curr_history.back()) * LearningRate / parts;
	if(AI_MODE&1){		//	Update the line value.
		int index[8];
		curr_history.back()->get_line_index(index);
		for(int b = 0; b < 4; b++){
			line_out[index[b]] += delta;
		}
		for(int b = 4; b < 8; b++){
			line_in[index[b]] += delta;
		}
	}
	if(AI_MODE&2){		//	Update the axe value.
		int index[16];
		curr_history.back()->get_axe_index(index);
		for(int b = 0; b < 8; b++){
			axe_out[index[b]] += delta;
		}
		for(int b = 8; b < 16; b++){
			axe_in[index[b]] += delta;
		}

	}
	if(AI_MODE&4){		//	Update the box value.
		int index[9];
		curr_history.back()->get_box_index(index);
		for(int b = 0; b < 4; b++){
			box_corn[index[b]] += delta;
		}
		for(int b = 4; b < 8; b++){
			box_side[index[b]] += delta;
		}
		for(int b = 8; b < 9; b++){
			box_cent[index[b]] += delta;
		}
	}
	for(int a = curr_history.size()-2; a >= 0; a--){
		const double delta = ((double)curr_history[a+1]->show_points() - (double)curr_history[a]->show_points() - (get_value(curr_history[a]) - get_value(curr_history[a+1]))) * LearningRate / parts;
		if(AI_MODE&1){		//	Update the line value.
			int index[8];
			curr_history[a]->get_line_index(index);
			for(int b = 0; b < 4; b++){
				line_out[index[b]] += delta;
			}
			for(int b = 4; b < 8; b++){
				line_in[index[b]] += delta;
			}
		}
		if(AI_MODE&2){		//	Update the axe value.
			int index[16];
			curr_history[a]->get_axe_index(index);
			for(int b = 0; b < 8; b++){
				axe_out[index[b]] += delta;
			}
			for(int b = 8; b < 16; b++){
				axe_in[index[b]] += delta;
			}

		}
		if(AI_MODE&4){		//	Update the box value.
			int index[9];
			curr_history[a]->get_box_index(index);
			for(int b = 0; b < 4; b++){
				box_corn[index[b]] += delta;
			}
			for(int b = 4; b < 8; b++){
				box_side[index[b]] += delta;
			}
			for(int b = 8; b < 9; b++){
				box_cent[index[b]] += delta;
			}
		}
	}
	return;
}

void AI::clear_status(){
	total_points = 0;
	runtime_played = 0;
	//free_history(top_history);
	//top_history.clear();
	return;
}

void AI::print_board(game* Game){
	Game->print();
	return;
}

void AI::print_status(){
	std::cout << std::endl << std::endl;
	std::cout << "Current AI Status:" << std::endl;
	std::cout << "----------------------------------" << std::endl << std::endl;
	std::cout << "Games played: " << played << std::endl;
	std::cout << "Runtime Avg.: " << (double)total_points/(double)runtime_played << std::endl;
	std::cout << "Top Game Board:" << std::endl;
	top_history.back()->print();
	std::cout << "----------------------------------" << std::endl << std::endl;
	return;
}
