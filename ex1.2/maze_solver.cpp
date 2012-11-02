#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <exception>

#include "oMatrix.h"

#define WALL 1
#define PATH 0

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
};

Matrix* read(char *);
Pair* findEntrance(const Matrix&);
Pair* findExit(const Matrix&);
void solve(const Matrix&, const Pair&, const Pair&);
void solve(const Matrix&);
void printSolution(const Matrix&, const Pair&, Node&);

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		// read matrix from file
		Matrix * m = read(argv[1]);
		solve(*m);
	}
	else
	{
		printf("usage: ./%s <file>\n", argv[0]);
	}
	return 0;
}

Matrix* read(char * file)
{
	std::string line;
	std::ifstream fileIn;
	fileIn.open(file);
	if(fileIn.is_open() == false)
	{
		 printf("Failed to open file %s\n",file);
	}
	int columns = 0, rows = 0;
	// count number of rows and columns
	while(fileIn.eof() == false)
	{
		std::getline(fileIn, line);
		if(columns == 0)
		{
			while(line[++columns] != '\0');
		}
		rows++;
	}
	fileIn.close();
	Matrix *m = new Matrix(rows,columns);
	fileIn.open(file);
	for(int i = 0; i < rows; ++i) {
		std::getline(fileIn,line);
		for(int j = 0; j < columns; ++j) {
			(*m)[i][j] = (line[j] == '#') ? 0 : 1;
		}
	}
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
	return p;
}

Pair* findExit(const Matrix& m) {
	unsigned int x = m.rows()-1, y = m.cols()-1, i = 0;
	// search last row
	for (; i < m.cols(); ++i) {
		if(m[m.rows()-1][i] == 1) {
			y = i;
		}
	}
	// search last column
	for (i = 0; i < m.rows(); ++i) {
		if(m[i][m.cols()-1] == 1) {
			x = i;
		}
	}
	Pair* p = new Pair(x,y);
	return p;
}

void solve(const Matrix& m)
{
	const Pair* start = findEntrance(m);
	const Pair* end = findExit(m);
	solve(m,*start,*end);
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
		if(*(*current).m_pair == exit) {
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
	else
	{
		printSolution(m,start,*path.top());
	}
}

void printSolution(const Matrix& m, const Pair& start, Node& last)
{
	std::cout << "\n** Printing solution **\n";

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