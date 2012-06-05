#include "maze_solver.h"

namespace maze_solver 
{

void MazeSolver::read(const char** data) {
	unsigned int rows = 0, cols = 0, i = 0, j = 0;

	for (; data[i] != 0; ++i) {
		if(cols == 0) {
			while(data[i][cols] != 0) {
				++cols;
			}
		}
		++rows;
	}
	std::cout << "Counted " << rows << " rows and " << cols << " columns" << std::endl;
	Matrix matrix(rows, cols);
	std::cout << matrix;
	this->matrix_ = matrix;
	for(i = 0; i < rows; ++i) {
		for(j = 0; j < cols; ++j) {
			this->matrix_[i][j] = (data[i][j] == '#') ? WALL : EMPTY;
		}
	}
	std::cout << "Created matrix" << std::endl << this->matrix_ << std::endl;
}

void MazeSolver::solve() {
	std::cout << (*this).matrix_;
	const Pair start = findEntrance();
	const Pair finish = findExit();
	std::cout << "Start: " << start << std::endl << "Finish: " << finish << std::endl;
	for(unsigned int i = 0; i < matrix_.rows(); ++i) {
		for(unsigned int j = 0; j < matrix_.cols(); ++j) {
			visited_[i][j] = NOT_VISITED;
		}
	}

	int left[] = {-1,0}, right[] = {1,0}, up[] = {0,1}, down[] = {0,-1};
	const int* adjacent[] = {left, right, up, down}; // left, right, up, down (x,y) where (0,0) is upper left corner
	path_.push(new Node(start));
	while(!path_.empty()) {
		Node* current = path_.top();
		visited_[(*current).x()][(*current).y()] = VISITED;
		//std::cout << "Currently at " << *(*current).m_pair << std::endl;
		if(*(*current).pair_ == finish) {
			// std::cout << "Reached the exit, terminating search!" << std::endl;
			// std::cout << "Last path visited " << *current << std::endl;
			break;
		}
		path_.pop();
		// find adjacent cells
		for (int i = 0; i < 4; ++i) {
			const int* dir = adjacent[i];
			unsigned int x = (*current).x() + dir[0], y = (*current).y() + dir[1];
			Pair* p = new Pair(x,y);
			Node* n = new Node(*p, *current);
			// check if adjacent cells are not visited and allowed transitions
			if(x < matrix_.rows() && y < matrix_.cols()) {
				if(matrix_[x][y] == EMPTY && visited_[x][y] == NOT_VISITED) {
					path_.push(n);
				}
			}
		}
	}
}

const MazeSolver::Pair MazeSolver::findEntrance() {
	unsigned int x = 0, y = 0, i = 0;
	// search first row
	for (; i < matrix_.cols(); ++i) {
		if(matrix_[0][i] == EMPTY) {
			y = i;
		}
	}
	// search first column
	for (i = 0; i < matrix_.rows(); ++i) {
		if(matrix_[i][0] == EMPTY) {
			x = i;
		}
	}
	Pair p(x,y);
	return p;
}

const MazeSolver::Pair MazeSolver::findExit() {
	unsigned int x = matrix_.rows()-1, y = matrix_.cols()-1, i = 0;
	// search last row
	for (; i < y+1; ++i) {
		if(matrix_[x][i] == EMPTY) {
			y = i;
		}
	}
	// search last column
	for (i = 0; i < x+1; ++i) {
		if(matrix_[i][y] == EMPTY) {
			x = i;
		}
	}
	Pair p(x,y);
	return p;
}

void MazeSolver::printPath() const {
	Node last = *(path_.top());
	Matrix sol(visited_);

	while(last.parent_ != 0) {
			sol[last.x()][last.y()] = SOLUTION;
			last = (*last.parent_);
	}
	sol[last.x()][last.y()] = SOLUTION;
	for (unsigned int i = 0; i < matrix_.rows(); ++i) {
		for (unsigned int j = 0; j < matrix_.cols(); ++j) {
			switch(sol[i][j]) {
				case EMPTY:
					std::cout << " ";
					break;
				case SOLUTION:
					std::cout << ".";
					break;
				default: // WALL
					std::cout << "#";
			}
		}
		std::cout << std::endl;
	}
}

}