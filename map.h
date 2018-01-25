#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum MOVE{UP, DOWN, LEFT, RIGHT};

/* =====================================================
	class Map
===================================================== */
class Map{
private:
	//nested class
	class MapCube{
	public:
		int data;//-1 means bomb
		bool visible;
		bool flag;

		MapCube(int n = 0) : data(n), visible(0), flag(0){};

		bool open();//return 0 if this is a bomb
		void show() const ;
	};

	int m_width;
	int m_height;
	int m_bomb;//number of bombs

	int m_x;//player x
	int m_y;//player y

	MapCube ** m_cubes;

	//private methods
	Map & copy(const Map & src);
public:
	Map(int width = 10, int height = 10, int bomb = 10);
	Map(const Map & src);//copy ctor
	Map(Map && src);//move ctor
	~Map();

	bool open();//return 0 if bomb
	void show() const ;
	void move(MOVE direction);
	bool win() const ;
	void setFlag();
	void showAll() const ;
	//operator reload
	Map operator=(const Map & src);
	Map operator=(Map && src);
};
