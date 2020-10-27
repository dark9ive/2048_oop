#include<cstring>

class game{
	private:
		int* board;
		int points;
	public:
		game();
		game(const game &previous);
		~game();
		void add_points(int);
		void new_block();
		void print();
		int show_points();
		int up();
		int down();
		int right();
		int left();
		bool isdead();
	public:				//	get informations
		void get_line_index(int*);
		void get_axe_index(int*);
		void get_box_index(int*);
};
void Init();
