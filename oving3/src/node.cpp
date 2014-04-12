/*****************************************************************
 * node.cpp
 * SystemC_testing_pool
 *
 *  Created on		: Mar 26, 2014 
 *  Author			: yulongb
 *	Email			: yulongb@stud.ntnu.no
 *  Description		:
 *****************************************************************/
#include"node.h"
#include"column_row_defs.h"// some constants of column and row
#include<vector>// vector
#include<algorithm>// random_shuffle
#include<iostream>
#include<fstream>
#include<systemc.h>
//#include <boost/filesystem.hpp>

typedef sc_port<node_if<int> > PORT_t;

inline bool Node::isTest(const int val) const {
	return (!(val == this->val_));
}

inline bool Node::isFree(void) const {
	return freeFlag_;
}

inline int Node::getNodeId() const {
	return nodeId_;
}

inline void Node::setNodeId(int nodeId) {
	nodeId_ = nodeId;
}

inline int Node::getVal() const {
	return val_;
}

inline void Node::setVal(int val) {
	this->val_ = val;
}

const PORT_t* Node::getPtrPrevNode() const {
	return ptrPortBindToPreviousNode_;
}

void Node::setPtrPrevNode(const PORT_t* ptrPrevNode) {
	ptrPortBindToPreviousNode_ = ptrPrevNode;
}
//// constructor
SC_HAS_PROCESS(Node);
Node::Node(sc_module_name _name, int _id , int _val , bool _flag ) :
				sc_module(_name),
				nodeId_(_id),
				val_(_val),
				freeFlag_(_flag) {
	ptrPortBindToPreviousNode_ = NULL;    // by default
	generateCounts_= 0;
	timeConsuming_= sc_time(SC_ZERO_TIME);
	SC_THREAD(node_process);
}

using namespace std;
int generator(vector<int>& vec) {
	random_shuffle(vec.begin(), vec.end());
	return vec.back();
}
void init_vector(vector<int>& vec) {
	for (int i = 0; i < matrix::column * matrix::row; i++) {
		vec.push_back(i);
	}
}

void Node::printStatus(void) const {
	cout <<  this->getNodeId() << " \t\t\t";
	cout << generateCounts_ << " \t\t\t";
	cout << timeConsuming_ /generateCounts_<< " \t\t\t";
	cout << getVal() << " \t\t\t" << endl;
}

const char* Node::getModuleName(void) const {
	return this->name();
}
//// loop function for testing values.
template<class T>
string numberToString(T Number){
	ostringstream convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	return convert.str(); // set 'Result' to the contents of the stream
}
void Node::testLoop(void) {
	// some variables declaration
	const PORT_t* tmp_ptr2pre = this->ptrPortBindToPreviousNode_;
	vector<int> Candidate_val_pool;
	init_vector(Candidate_val_pool);    // init from 0 to Maximum -1 ;
	string stringBuffer = string("\t\t ***** Testing begins ***** \n");
	 timeConsuming_ = sc_time_stamp();
	 generateCounts_ = 0;
	while (1) {
		//generate a new value
		int temp = generator(Candidate_val_pool);
		generateCounts_++;
		stringBuffer += string(" newly generated value :") + numberToString<int>(temp) + string("\n");
		while (1) {
			stringBuffer += string(" testing value :") + numberToString<int>(temp);
			stringBuffer += string(" against the value from ");
			stringBuffer += (*tmp_ptr2pre->get_interface(0)).getModuleName();
			wait(10,SC_PS); // advances time
			if ((*tmp_ptr2pre)->isTest(temp)) {

				// current node test pass
				stringBuffer += string(" - pass .") + string("\n");
				if (((*tmp_ptr2pre)->getPtrPrevNode()) == NULL) {    // previous node doesn't exist, so this is the first node
					this->setVal(temp);
					string nodeName = string(this->name());
					stringBuffer += string("\n\t\t") +  nodeName;
					stringBuffer += string(" get val ") + numberToString<int>(this->getVal()) + string("\n") + string("\n");
					timeConsuming_ = sc_time_stamp() - timeConsuming_;
					stringBuffer += string("Time consuming: ") + timeConsuming_.to_string() +string("\n");
					string filename = string("log_") + nodeName + string(".txt");
					ofstream myfile;
					myfile.open( filename.c_str(),ios::out);
					myfile << stringBuffer
							<< "Number generation Counts :"<< generateCounts_ << '\n'
							<< "Average time per number (10 ps per test) :" << timeConsuming_/generateCounts_
							<< "\n This is the end of the file \n";
					myfile.close();
					this->freeFlag_ = 1;    //
					// tests to all the previous free nodes passed, assign the generated valued.
					return;///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!deep nested loop!!!!!!!!!!!!!!!!!!!!! here's the exit.
					// better to clean up the cache
				}
				else {		// previous node exists, traverse one step further
					tmp_ptr2pre = (*tmp_ptr2pre)->getPtrPrevNode();
				}

			}
			else {
				// current node test failed
				stringBuffer += string(" - failed .") + string("\n");
				tmp_ptr2pre = this->ptrPortBindToPreviousNode_;    // back from the first node
				Candidate_val_pool.pop_back();    // throw the failed value, improve generation efficiency
				break;    // to get a new generated value
			}
		}
	}
}
//// process
void Node::node_process() {
	this->freeFlag_ = false;    // make sure every nodes initialized busy
	wait(SC_ZERO_TIME);    // suspended for scheduling

	//
	while (!isFree()) {
		// if the node is the first one
		if (ptrPortBindToPreviousNode_ == NULL) {
			this->setVal(rand() % (matrix::column * matrix::row)); // generate a random number
			this->freeFlag_ = 1; // set to free
			return;
		}

		// step 1, wait till the "previous one" free
		while (!(*ptrPortBindToPreviousNode_)->isFree()) {
			wait(10, SC_PS);
		}
		// step 2, test if the new generated not yet used.
		testLoop();

	}
}
