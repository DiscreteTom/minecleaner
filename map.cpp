#include "map.h"

/* ==========================================
	class Map::MapCube
========================================== */
bool Map::MapCube::open(){
	if (!visible){
		visible = 1;
		if (data == -1){
			//bomb
			return 0;
		}
	}
	return 1;//safe
}//open
void Map::MapCube::show() const {
	if (visible){
		if (data == -1){
			//bomb
			cout << 'B';
		} else {
			cout << data;
		}
	} else if (flag){
		cout << 'F';
	} else {
		cout << '-';
	}
}//show

/* ==============================================
	class Map
============================================== */
Map::Map(int width, int height, int bomb){
	//get value
	m_width = width;
	m_height = height;
	m_bomb = bomb;
	m_x = m_y = 0;

	//get memory
	m_cubes = new MapCube * [height];
	do {
		--height;
		m_cubes[height] = new MapCube[width];
	} while (height);

	//random set bomb
	srand(time(NULL));
	while (bomb){
		--bomb;
		int x = rand() % m_width;
		int y = rand() % m_height;
		m_cubes[y][x].data = -1;

		//nearby cubes data+1 if not bomb
		for (int i = y - 1; i <= y + 1; ++i){
			for (int j = x - 1; j <= x + 1; ++j){
				if (0 <= i && i < m_height && 0 <= j && j < m_width && m_cubes[i][j].data != -1){
					//in the map and not a bomb
					++m_cubes[i][j].data;
				}
			}
		}
	}
}//ctor
Map::Map(const Map & src){
	copy(src);
}//copy ctor
Map::Map(Map && src){
	//copy value
	m_width = src.m_width;
	m_height = src.m_height;
	m_bomb = src.m_bomb;
	m_x = src.m_x;
	m_y = src.m_y;

	//steal memory
	m_cubes = src.m_cubes;
	src.m_cubes = NULL;
}//move ctor
Map::~Map(){
	if (m_cubes){
		do {
			--m_height;
			delete m_cubes[m_height];
		} while (m_height);
		delete m_cubes;
	}
}//dtor
/* -----------------------------------------
	private methods
----------------------------------------- */
Map & Map::copy(const Map & src){
	if (this == &src){
		//self copy
		return *this;
	}

	//copy value
	m_width = src.m_width;
	m_height = src.m_height;
	m_bomb = src.m_bomb;
	m_x = src.m_x;
	m_y = src.m_y;

	//get memory
	m_cubes = new MapCube * [m_height];
	for (int i = 0; i < m_height; ++i){
		m_cubes[i] = new MapCube[m_width];
	}

	//copy state
	for (int i = 0; i < m_height; ++i){
		for (int j = 0; j < m_width; ++j){
			m_cubes[i][j] = src.m_cubes[i][j];
		}
	}

	return *this;
}//copy
/* ---------------------------------------------
	public methods
--------------------------------------------- */
bool Map::open(){
	if (!m_cubes[m_y][m_x].open()){
		//bomb
		return 0;
	}
	if (m_cubes[m_y][m_x].data == 0){
		for (int i = -1; i < 2; ++i){
			for (int j = -1; j < 2; ++j){
				if (m_x + i >= 0 && m_x + i < m_width && m_y + j >= 0 && m_y + j < m_height && !m_cubes[m_y + j][m_x + i].visible){
					m_x += i;
					m_y += j;
					open();
					m_x -= i;
					m_y -= j;
				}
			}
		}
	}
	return 1;
}//open
void Map::show() const {
	system("cls");
	for (int i = 0; i < m_height; ++i){
		for (int j = 0; j < m_width * 2; ++j){
			if (m_x * 2 == j && m_y == i){
				//show player
				cout << '>';
			} else if (j % 2){
				//show mapcube
				m_cubes[i][(j - 1) / 2].show();
			} else {
				//show blank
				cout << " ";
			}
		}
		cout << endl;
	}
}//show
void Map::move(MOVE direction){
	switch (direction){
		case UP : {
			if (m_y){
				--m_y;
			}
			break;
		}
		case DOWN : {
			if (m_y != m_height - 1){
				++m_y;
			}
			break;
		}
		case LEFT : {
			if (m_x){
				--m_x;
			}
			break;
		}
		case RIGHT : {
			if (m_x != m_width - 1){
				++m_x;
			}
			break;
		}
	}
}//move
bool Map::win() const {
	for (int i = 0; i < m_height; ++i){
		for (int j = 0; j < m_width; ++j){
			if (m_cubes[i][j].data != -1 && !m_cubes[i][j].visible){
				return 0;
			} else if (m_cubes[i][j].data == -1 && !m_cubes[i][j].flag){
				return 0;
			}
		}
	}
	return 1;
}//win
void Map::setFlag(){
	m_cubes[m_y][m_x].flag = !m_cubes[m_y][m_x].flag;
}//setFlag
void Map::showAll() const {
	for (int i = 0; i < m_height; ++i){
		for (int j = 0; j < m_width; ++j){
			m_cubes[i][j].visible = 1;
		}
	}
	show();
}
/* -----------------------------------------------
	operator reload
----------------------------------------------- */
Map Map::operator=(const Map & src){
	return copy(src);
}//=
Map Map::operator=(Map && src){
	int n;
	//switch height for dtor
	n = m_height;
	m_height = src.m_height;
	src.m_height = n;

	//get value
	m_width = src.m_width;
	m_bomb = src.m_bomb;
	m_x = src.m_x;
	m_y = src.m_y;

	//switch memory
	auto p = m_cubes;
	m_cubes = src.m_cubes;
	src.m_cubes = p;

	return *this;
}