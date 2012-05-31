
#include "oMatrix.h"         // inkludera din headerfil h�r
//#include "maze_solver.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stack>

struct Pair {
	const int m_x, m_y;
	Pair(const int x, const int y) :
		m_x(x), m_y(y) {}
	friend struct Node;
	friend std::ostream& operator<<(std::ostream& os, const Pair& pair) {
		return os << "(" << pair.m_x << "," << pair.m_y << ")";
	}
	friend bool operator==(const Pair& p1, const Pair& p2) {
		return p1.m_x == p2.m_x && p1.m_y == p2.m_y;
	}
};

struct Node {
	const Pair* m_pair;
	const Node* m_parent;
	Node(const Pair& pair) :
		m_pair(&pair), m_parent(0) {}
	Node(const Pair& pair, const Node& parent) :
		m_pair(&pair), m_parent(&parent) {}
	int x() { return (*m_pair).m_x; }
	int y() { return (*m_pair).m_y; }
	friend std::ostream& operator<<(std::ostream& os, const Node& node) {
		if(node.m_parent != 0) {
			Node n = *(node.m_parent);
			os << *(n.m_pair) << " -> ";
		}
		return os << *(node.m_pair);
	}
	friend bool operator==(const Node& n1, const Node& n2) {
		return n1.m_pair == n2.m_pair;
	}
};

Matrix* read(const char**);
Pair* findEntrance(const Matrix&);
Pair* findExit(const Matrix&);
void solve(const Matrix&, const Pair&, const Pair&);

int main()
{
	const char *small[] =
	{
			"#####################",
			"      # # #   # # # #",
			"##### #     # #   # #",
			"#     ##### # # #   #",
			"### # #   # #   # # #",
			"# # # # # # ####### #",
			"#   #   #   #       #",
			"## ############ #####",
			"#   #                ",
			"#####################",
			0};

	const char *medium[] =
	{
			"# #######################################",
			"# #                   #     #   #     # #",
			"# # ### ############# # # ### # # ### # #",
			"# #   #     #   #   #   #     # #   # # #",
			"# ### # ### # # # # ##### ####### # # # #",
			"#   # # # #   #   #     #   #   # # # # #",
			"### # # # # ########### ##### # ### # # #",
			"#   # #   #   # #             # #   # # #",
			"# # # ####### # # ############# # ### # #",
			"# # #     #   # #             # #   # # #",
			"# ### ### # ### ############# # ### # # #",
			"#   #   # #   #   #     #   # # #   # # #",
			"### ##### ### ### # # ### # # # # ### # #",
			"#   #     # # #     #     # # # # # #   #",
			"# ### ##### # # ############# # # # # ###",
			"#     #     # #               # # # #   #",
			"####### ##### ################### # # ###",
			"#         #   #     #             # #   #",
			"# ####### # ### # # # ############# ### #",
			"#       #       # #               #     #",
			"####################################### #",
			0};

	const char *large[] =
	{
			"# ###############################################################################",
			"# #         # #     #       #         #       #   #     #     #   #             #",
			"# ### ##### # # ### # ##### # ##### # # ### ### # # ### ##### # # # # ##### #####",
			"#   # #   # # # # #   #     # #   # #   # #   # # # # #     # # #   # #   # #   #",
			"# # # # # # # # # ### # ##### # # # ##### # # # # # # # ### # # ##### # # ### # #",
			"# #   # #     # # #   #     #   # # #   #   #   # # # # # #   #     #   # #   # #",
			"####### ####### # # ### ######### ### ####### ### # # # # # # ##### ##### # ### #",
			"#   #   #     # # # # #         #   #   #     #   # #   #   #   # #     #   #   #",
			"# # # ### ### # # # # # ####### ### ### # # ### ##### ######### # # ### ##### ###",
			"# #   #   # #   #   # # #     #   # #   # #   #     # #   #   #   # # # #   #   #",
			"# ##### ### # ####### # ##### # # # # ### ######### # ### # # ##### # # # # # ###",
			"#     #     #   #     #     # # #   #     #   #   # #   # # #       # # # # #   #",
			"# ##### # ##### # ######### # ####### ##### # ### # # # # # ######### # ### # # #",
			"#   #   # #   #     #     #   #     #     # #   # # # #   #   #       #     # # #",
			"### # ### # ####### # ### ##### ### ##### # ### # # # ######### # ########### # #",
			"#   # # #       # #   #       #   #     # # # #     # #         #   #     #   # #",
			"# ### # ####### # ##### ######### ##### ### # # ##### # ######### # # ##### # # #",
			"# #   #   #     #       #   #     #   #     # # #   # # #     #   # #   #   # # #",
			"# # ##### # ############# ### ### # # ####### # # # # # ### # # ### ### # ##### #",
			"#   #   # #             #   #   # # # #   #   #   # # # #   # #   # #   # #   # #",
			"##### # # ######### ### ### ### ### # # # # ####### # # # ##### # # # ### # # # #",
			"#   # #           #   #   #   #     #   # #   #       # # #     # # #   # # #   #",
			"# ### ########### ### # ### ### ######### # # ######### # # ##### ### # # # #####",
			"# #   #     #   # #   #   #   # #     #   # #   #     # #   # #   #   # # # #   #",
			"# # ### ### # # # # ##### ### # # ### # ####### # # # # ##### # ### # # # # # ###",
			"# # #     #   #   # #   #     # # #   #         # # # #       #   # # # # #     #",
			"# # # ### ########### # # ##### # ######### ##### # ### ######### # ### # ##### #",
			"#   #   # #       #   #   #     #         #       #     #   #     #   # # #     #",
			"####### # # ##### # ##################### ########### ### # # ####### # # # #####",
			"#     # # # #   #   #     #     #   #   # #     #   # #   # # #       # # #     #",
			"# ### # ### # ####### # # # ### ### # # # # # # # # # # ##### # # ####### #######",
			"# # #       # #       # #   #   #   # # #   # # # # # # #     # #   # #   #     #",
			"# # # ####### # ####### ##### ### ### # ##### # # # ### # ### # # # # # ### ### #",
			"#   # #     # #       # #   #   #     #   # # #   #     #   #   # #   #     # # #",
			"##### # ### # ####### ### # # ########### # # # ### ####### ####### ######### # #",
			"#   #     #         #   # # #       #   # # # # # #   #     #     #   #   #   # #",
			"# ### # ########### ### # # ####### # # # # # # # # # # ##### ### ### # # # ### #",
			"# #   # #   #   #     #   #       #   #     # # # # #   #     #   # # # #     # #",
			"# # ##### ### # ########### ############# ### # # ####### ##### ### # ### # # # #",
			"# #     #   # #     #   #   #     #     #   # # #       # #     #   #     # #   #",
			"# ### # ### # ##### # # # ### ### # ### ##### # # ##### # # ##### ######### #####",
			"#   # #   # # #     # #   #   #   #   #       # #     #   #   #   #   #     #   #",
			"### ##### # # ####### # ### ### ##### ########### ### ####### # ### # ####### # #",
			"#     #   # #       # #   # #   #   #           # #   #       #   # #       # # #",
			"### # # ### ####### # ### # # ### # ########### ### ####### ### # # ####### # # #",
			"#   # # #   #   #   #   #   #   # #   #             #     #   # # #   #   # # # #",
			"# ##### # # # # # ##### # ##### ### # ############### ### ##### # ### # # # ### #",
			"#         # # # # #     # #   # #   #         #     #   #       # #   # # #   # #",
			"# ##### ### # # # # ####### # # # ##### ##### # ##### # ######### # ### # ### # #",
			"# #   #   #   # # #     #   # # # #   # # #   #   #   # # #   #   # #   #   #   #",
			"# # # ######### # ##### # ### # # # # # # # # ### # # # # # ### # ### ##### # ###",
			"# # #   #     # #     # #   # #     # #   # #     # # # # #   # #   #     #     #",
			"### # # # ### # ##### # # # ######### ##### ####### # # # ### # ### ########### #",
			"#   # #   #   #   #   # # #         # #   #   # #   # #   # #   #       #   #   #",
			"# ##### ####### # # ### # ######### # # # ### # # ####### # # ### ####### # # ###",
			"# #   # #     # # #   # #   #   # # # # #   #   # #     # # #   #         # #   #",
			"# # # # # ### # ### # # ### # # # # # # # ### ### # ##### # # # ########### ### #",
			"#   # #   # #   #   # # # # # #   #   # # #   #   #     #   # #   #   #   #     #",
			"##### ##### # ### ### # # # # # ####### # # ### ####### ##### ### # # # #########",
			"#           #       #     #   #         # #           #         #   #           #",
			"############################################################################### #",
			0};

	// anv�nd matrisklassen f�r att l�sa matriserna ovan!
	const char** maze[] = {small, medium, large};
	for (int i = 0; i < 3; ++i) {
		Matrix* m = read(maze[i]);
		Pair* start = findEntrance(*m);
		Pair* exit = findExit(*m);
		solve(*m, *start, *exit);
	}
	return 0;
}

Matrix* read(const char** data) {
	unsigned int rows = 0, cols = 0, i = 0, j = 0;

	for (i = 0; data[i] != 0; ++i) {
		if(cols == 0) {
			while(data[i][cols] != 0) {
				++cols;
			}
		}
		++rows;
	}
	Matrix* m = new Matrix(rows, cols);
	for(i = 0; i < rows; ++i) {
		for(j = 0; j < cols; ++j) {
			(*m)[i][j] = (data[i][j] == '#') ? 0 : 1;
		}
	}
	printf("Maze with %i rows and %i columns was converted to matrix successfully\n", (*m).rows(), (*m).cols());
	//std::cout << (*m) << std::endl;
	return m;
}

Pair* findEntrance(const Matrix& m) {
	unsigned int x = 0, y = 0, i = 0;
	// search first row
	for (; i < m.cols(); ++i) {
		if(m[0][i] == 1) {
			y = i;
		}
	}
	// search first column
	for (i = 0; i < m.rows(); ++i) {
		if(m[i][0] == 1) {
			x = i;
		}
	}
	Pair* p = new Pair(x,y);
	std::cout << "Entrance found at coordinate " << *p << std::endl;
	return p;
}

Pair* findExit(const Matrix& m) {
	unsigned int x = m.rows()-1, y = m.cols()-1, i = 0;
	// search first row
	for (; i < m.cols(); ++i) {
		if(m[m.rows()-1][i] == 1) {
			y = i;
		}
	}
	// search first column
	for (i = 0; i < m.rows(); ++i) {
		if(m[i][m.cols()-1] == 1) {
			x = i;
		}
	}
	Pair* p = new Pair(x,y);
	std::cout << "Exit found at coordinate " << *p << std::endl;
	return p;
}


void solve(const Matrix& m, const Pair& start, const Pair& exit) {
	printf("\nCommensing search...\nMatrix size is %ix%i\n", m.rows(), m.cols());
	std::cout << "Starting at " << start << std::endl << "Finish at " << exit << std::endl;
	const int VISITED = 1;
	std::stack<Node*> path;
	Matrix* visited = new Matrix(m.rows(), m.cols());
	int left[] = {-1,0}, right[] = {1,0}, up[] = {0,1}, down[] = {0,-1};
	const int* adjacent[] = {left, right, up, down}; // left, right, up, down (x,y) where (0,0) is upper left corner
	path.push(new Node(start));
	while(!path.empty()) {
		Node* current = path.top();
		(*visited)[(*current).x()][(*current).y()] = VISITED;
		//std::cout << "Currently at " << *(*current).m_pair << std::endl;
		if(*(*current).m_pair == exit) {
			// std::cout << "Reached the exit, terminating search!" << std::endl;
			// std::cout << "Last path visited " << *current << std::endl;
			break;
		}
		path.pop();
		// find adjacent cells
		for (int i = 0; i < 4; ++i) {
			const int* dir = adjacent[i];
			unsigned int x = (*current).x() + dir[0], y = (*current).y() + dir[1];
			Pair* p = new Pair(x,y);
			Node* n = new Node(*p, *current);
			// if adjacent cells are not visited and allowed transitions, create node and add to queue.
			if(x < m.rows() && y < m.cols()) {
				if(m[x][y] == 1 && (*visited)[x][y] == 0) {
					path.push(n);
				}
			}
		}
	}
	if(path.empty()) {
		std::cout << "Could not find any solution" << std::endl;
	}
	else {
		std::cout << "\n** The solution **\n";
		Node last = *path.top();
		Matrix solution(m);
		while(last.m_parent != 0) {
			solution[last.x()][last.y()] = 2;
			last = *(last.m_parent);
		}
		solution[start.m_x][start.m_y] = 2;
		for (unsigned int i = 0; i < m.rows(); ++i) {
			for (unsigned int j = 0; j < m.cols(); ++j) {
				switch(solution[i][j]) {
					case 1:
						std::cout << " ";
						break;
					case 2:
						std::cout << ".";
						break;
					default:
						std::cout << "#";
				}
			}
			std::cout << std::endl;
		}
	}
}