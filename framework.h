class game{
	private:
		int* board;
		int points = 0;
	public:
		game();
		~game();
		void add_points(int);
		void new_block();
		void print();
		int up();
		int down();
		int right();
		int left();
		bool isdead();
};
void Init();
