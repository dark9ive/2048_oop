#include"framework.h"
#include<string>
#include<vector>

class AI{
	private:			//	components
		std::vector<game*> curr_history;
		std::vector<game*> top_history;
		int played;
		int top_played;		//	not used
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
	public:				//	main functions
		AI();
		~AI();
		void save();
		void train();
		void newgame();
		void free_history(std::vector<game*>);
		void update();
		void clear_status();
	public:				//	get status
		void print_status();
		void print_board(game*);
		double get_value(game*);
	public:				//	file IO
		bool readfile(void*, std::string, int);
		bool readfile(void*, std::string, const unsigned int, const int);
		bool savefile(void*, std::string, int);
		bool appendfile(void*, std::string, int);
		int getfilesize(std::string);
	public:				//	replays
		void high_replay();
		void demo_play();

};
