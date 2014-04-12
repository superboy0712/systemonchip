/*****************************************************************
 * test_main.cpp
 * SystemC_testing_pool
 *
 *  Created on		: Mar 27, 2014 
 *  Author			: yulongb
 *	Email			: yulongb@stud.ntnu.no
 *  Description		:
 *****************************************************************/

#include"node.h"
#include<systemc.h>
//#include "gmock/gmock.h"
#include <string>
//#include "gtest/gtest.h"
#include "column_row_defs.h"

void collaborationAndSimmulation(void);
int sc_main(int argc, char **argv) {
	// initializing random number generator
	// the simulation time in seconds
	//assert(argc == 2);
	// int init_value = atoi(argv[1]);
	//sc_time sim_time(atof(argv[1]), SC_SEC);
	srand(time(NULL));
	sc_set_time_resolution(1, SC_PS);
	collaborationAndSimmulation();

	return 0;
}
struct direction {
	enum eDirection {
		UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3
	};

};
void Connect(Node * from, Node * to, direction::eDirection _direction) {
	from->port[_direction](*to);		//binding from's xx port to "to"
	cout << "binding " << from->name() << "'s port " << _direction << " to "
			<< to->name() << endl;
}
using namespace std;
void collaborationAndSimmulation(void) {
	typedef Node* PTR;
	PTR ptr[matrix::column * matrix::row];
	{
		char number2string[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
				'9' };

		for (int i = 0; i < matrix::column * matrix::row; i++) {
			char cstr[] = "Hello_node_000";
			cstr[11] = number2string[(i / 100) % 10];
			cstr[12] = number2string[(i / 10) % 10];
			cstr[13] = number2string[i % 10];
			ptr[i] = new Node(cstr, i, 0xff, false);
			cout << "\t\t" << ptr[i]->name() << " creates" << endl;
		}
	}

	for (int i = 0; i < matrix::row; i++) {
		for (int j = 0; j < matrix::column; j++) {
			int index = i * matrix::column + j;
			if (i == 0) {
				Connect(ptr[index], ptr[index], direction::UP);
			}
			else {
				Connect(ptr[index], ptr[index - matrix::column], direction::UP);
			}
			if (i == matrix::row - 1) {
				Connect(ptr[index], ptr[index], direction::DOWN);
			}
			else {
				Connect(ptr[index], ptr[index + matrix::column],
						direction::DOWN);
			}
			if (j == 0) {
				Connect(ptr[index], ptr[index], direction::LEFT);
			}
			else {
				Connect(ptr[index], ptr[index - 1], direction::LEFT);
			}
			if (j == matrix::column - 1) {
				Connect(ptr[index], ptr[index], direction::RIGHT);
			}
			else {
				Connect(ptr[index], ptr[index + 1], direction::RIGHT);
			}

		}
	}

	// set previous
	for (int i = 0; i < matrix::row; i++) {
		for (int j = 0; j < matrix::column; j++) {
			int index = i * matrix::column + j;
			if (i % 2 == 0) {
				if (j == 0) {
					ptr[index]->setPtrPrevNode(
							&(ptr[index]->port[direction::UP]));
				}
				else {
					ptr[index]->setPtrPrevNode(
							&(ptr[index]->port[direction::LEFT]));
				}
			}
			else {
				if (j == matrix::column - 1) {
					ptr[index]->setPtrPrevNode(
							&(ptr[index]->port[direction::UP]));
				}
				else {
					ptr[index]->setPtrPrevNode(
							&(ptr[index]->port[direction::RIGHT]));
				}
			}
		}
	}
	ptr[0]->setPtrPrevNode(NULL);// the first node doesn't necessarily to traverse other node.
	cout << endl;
	sc_start();
	for (int i = 0; i < matrix::row; i++) {
			for (int j = 0; j < matrix::column; j++) {
				int index = i * matrix::column + j;
				cout << ptr[index]->getVal() <<"\t";
			}
			cout << endl;
	}
	cout << "Status of Node No."  << " \t";
		cout << "Geration Counts - "  << " \t";
		cout << "Time Consuming - " << " \t";
		cout << "Value - "  << " \t" << endl;
	for (int i = 1; i < matrix::column * matrix::row; i++) {
		ptr[i]->printStatus();
	}




	for (int i = 0; i < matrix::column * matrix::row; i++) {
		delete ptr[i];
	}
}

