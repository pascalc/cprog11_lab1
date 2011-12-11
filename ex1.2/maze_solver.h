#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include <algorithm>
#include <list>
#include <vector>

#include "../ex1.1/oMatrix.h"

#define WALL 1 // "#"
#define EMPTY 2 // " "

#define VISITED 1
#define NOT_VISITED 2

class MazeSolver {
	public:
		MazeSolver() : matrix(0) { }

		void read(const char**);
		void print_path();

	private:
		Matrix m_matrix, m_visited;
		list<Node> m_path;

		void solve(const Matrix&);

		struct Pair {
			int m_x, m_y;
			Pair(int x, int y) :
				m_x(x),
				m_y(y) {}
			friend struct Node;
			friend std::operator<<(std::ostream& os, const Pair& p) {
				return os << "(" << p.m_x << "," << p.m_y << ")"; 
			}
		};

		struct Node	{
			const Pair* m_pair;
			const Node* m_parent;
			Node(const Pair& pair, const Node& parent) : 
				m_pair(pair),
				m_parent(parent) { }

			friend std::operator<<(std::ostream& os, const Node& n) {
				os << n.(*m_pair);
				if(m_parent != 0) {
					os << " [Parent: " << n.(*m_parent) << "]";
				}
				return os;
			}
		};
};

void MazeSolver::read(const char** m) {
	
}

void MazeSolver::solve(const Matrix& m) {
	// m_path.push_back( node( pair(x,y), 0 ) ); // start (entrance) node
	// m_visited[x][y] = VISITED;
	// bool found_exit = false;
	/*while(!found_exit) {
		Node tmp = m_path.back();
	}*/

	// perform DFS/BFS
}

void MazeSolver::print_path() {
	while(!m_path.empty()) {
		std::cout << m_path.pop_front();
	}
	std::cout << std::endl;
	/*
	if(node->m_parent == 0)
		std::cout << "Start at " << node->m_parent << " -> ";
	print_path(node->m_parent);

	std::cout << " -> " << node;
	*/
}

#endif