#include"framework.h"
#include<string>
#include<vector>

class AI{
	private:
		std::vector<game*> curr_history;
		std::vector<game*> top_history;
		int played;
		int top_played;
		int total_points = 0;
		int runtime_played = 0;
	private:			//	tuples
		double* line_in;
		double* line_out;
		double* axe_in;
		double* axe_out;
		double* box_corn;
		double* box_side;
		double* box_cent;
	public:
		AI();
		~AI();
		void save();
		void train();
		bool readfile(void*, std::string, int);
		bool savefile(void*, std::string, int);
		void newgame();
		void print_status();
		void print_board(game*);
		void free_history(std::vector<game*>);
		double get_value(game*);
		void update();
		void clear_status();

};
