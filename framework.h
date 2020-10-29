#include<cstring>

class game{
	private:			//	components
		int* board;
		int points;
	public:				//	some basic operaters
		game();
		game(const game &previous);
		~game();
		void add_points(int);
		void new_block();
		void print();
		bool isdead();
		void set_board(int*);
	public:				//	get pointers
		int* board_pointer();
		int* points_pointer();
	public:				//	move board
		int up();
		int down();
		int right();
		int left();
	public:				//	get informations
		void get_line_index(int*);
		void get_axe_index(int*);
		void get_box_index(int*);
		int show_points();
};
void Init();
