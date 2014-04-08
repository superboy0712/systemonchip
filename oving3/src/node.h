/*****************************************************************
 * node.h
 * SystemC_testing_pool
 *
 *  Created on		: Mar 26, 2014 
 *  Author			: yulongb
 *	Email			: yulongb@stud.ntnu.no
 *  Description		:
 *****************************************************************/

#ifndef NODE_H_
#define NODE_H_

#include"if.h"
#include<systemc.h>
typedef sc_port<node_if<int> > PORT_t;
class Node: public sc_module, public node_if<int>, public node_test_if {
public:
	sc_port<node_if<int> > port[4];    // 0 - up, 1 - left, 2 - down, 3 - right
	bool isTest(const int) const;
	bool isFree(void) const;
	Node(sc_module_name _name);
	Node(sc_module_name _name, int _id, int _val, bool);
	const char* getModuleName(void) const;
	void node_process(void);
	// FOLLOWING INTERFACES FOR TEST BENCH PRINTING
	void setPtrPrevNode(const PORT_t* ptrPrevNode);
	const PORT_t* getPtrPrevNode() const;
	int getNodeId() const;
	void setNodeId(int nodeId);
	int getVal() const;
	void setVal(int val);
	// for printing status
	void printStatus(void) const;

private:
	Node(const Node& node_inst);    //avoid shallow copy
	Node& operator=(const Node& node_inst);    //avoid shallow copy
	int nodeId_;
	int val_;    // store the value
	bool freeFlag_;
	const PORT_t* ptrPortBindToPreviousNode_;    // point to the port which connects to the previous ready node
	int generateCounts_;
	sc_time timeConsuming_;
	void testLoop(void);
};

#endif /* NODE_H_ */
