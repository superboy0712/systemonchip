/*****************************************************************
 * if.h
 * SystemC_testing_pool
 *
 *  Created on: Mar 25, 2014 
 *      Author: yulongb
 *	email: yulongb@stud.ntnu.no
 *  
 *****************************************************************/

#ifndef IF_H_
#define IF_H_

#include<systemc.h>

template<class T>
class node_if: public sc_interface {
public:
	virtual bool isTest(const T) const = 0;
	virtual bool isFree(void) const = 0;
	typedef sc_port<node_if<T> > PRT;
	virtual const PRT* getPtrPrevNode() const = 0;
	virtual const char* getModuleName(void) const = 0;
};
// interfaces for test bench
class node_test_if: public sc_interface {
public:
	virtual void printStatus(void) const = 0;
};

#endif /* IF_H_ */
