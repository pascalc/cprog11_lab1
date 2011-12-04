#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "../ex1.1/oMatrix.h"

class MazeSolver {
	public:
		MazeSolver() : matrix(0) { }

		void read(const char**);
		void print_path(const Node&);

	private:
		struct Node	{
			int m_x, m_y;
			const Node* m_parent;
			Node(int x, int y) : m_x(x), m_y(y), m_parent(0) {};	
			Node(int x, int y, const Node*& parent) : m_x(x), m_y(y), m_parent(parent) {};

			friend std::operator<<(std::ostream& os, const Node& n) {
				return os << "(" << n.x << ", " << n.y << ")";
			}
		};

		Matrix matrix;

		void solve(const Matrix&); // return Path&
};

MazeSolver::solve(const Matrix& m) {
	// define parent node = entry point in labyrint

	// perform DFS/BFS
}

MazeSolver::print_path(const Node& node) {
	if(node.parent == 0)
		std::cout << "Start at " << node.parent << " -> ";
	print_path(node.parent);

	std::cout << " -> " << node;
}

#endif