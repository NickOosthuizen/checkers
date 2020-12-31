class GameBoard;

class Test {
	public:
		Test(GameBoard* board);
		~Test();
		void constructionTest() const;
		void moveTest() const;

	private:
		GameBoard* m_testBoard;
};
