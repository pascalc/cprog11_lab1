#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include <algorithm>
#include <stack>
#include <iostream>

#include "oMatrix.h"

#define WALL 1 // "#"
#define EMPTY 2 // " "
#define SOLUTION 3 // "."

#define VISITED 1
#define NOT_VISITED 2

namespace maze_solver 
{

class MazeSolver {
	public:
		MazeSolver() : matrix_(0), visited_(0), path_() { }

		void read(const char**);
		void solve();
		void printPath() const;

		struct Pair {
			const int x_, y_;
			Pair(const int x, const int y) : x_(x), y_(y) {}
			friend struct Node;
			friend std::ostream& operator<<(std::ostream& os, const Pair& pair) {
				return os << "(" << pair.x_ << "," << pair.y_ << ")";
			}
			friend bool operator==(const Pair& p1, const Pair& p2) {
				return p1.x_ == p2.x_ && p1.y_ == p2.y_;
			}
		};

		struct Node {
			const Pair* pair_;
			const Node* parent_;
			Node(const Pair& pair) :
				pair_(&pair), parent_(0) {}
			Node(const Pair& pair, const Node& parent) :
				pair_(&pair), parent_(&parent) {}
			int x() { return (*pair_).x_; }
			int y() { return (*pair_).y_; }
			friend std::ostream& operator<<(std::ostream& os, const Node& node) {
				if(node.parent_ != 0) {
					Node n = *(node.parent_);
					os << *(n.pair_) << " -> ";
				}
				return os << *(node.pair_);
			}
		};

		private:
			const Pair findEntrance();
			const Pair findExit();

			Matrix matrix_, visited_;
			std::stack<Node*> path_;
};

}

#endif