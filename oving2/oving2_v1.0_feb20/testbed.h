
#ifndef TEST_BED_H
#define TEST_BED_H

#include "if.h"
#include "iostream"

//basic ideas: random generagtes some "push", once the light on, push the next one, restore the current correct push order and number.
//if all off, then repeat the correct orders restored
//print each tests.
// sc_stop() here.
class testbed : public sc_module {
	public:
	sc_port < Push_if > port2Button[9];

	void testbed_process(void);

	testbed (sc_module_name nm): sc_module(nm){

		SC_HAS_PROCESS(testbed);

		SC_THREAD(testbed_process);
	}

};

void testbed::testbed_process(void){
	int successful_rounds = 0;
	int successful_counts = 0;
	int try_times = 1;
	cout << "TestBench launched, test is running !" << endl;
	cout << try_times <<"-th try: ";
	while(true){

		int i = 1 + rand() % 8;  //  1 <= i <= 9
		port2Button[i]->Push();
		if(port2Button[i]->Checklight()) {
			cout << i << ", ";
			successful_counts++;
		}
		else {
			cout << "fail" << endl;
			try_times++;
		}

		if( successful_counts == 9){
			successful_counts = 0;
			successful_rounds++;
		}

		if(successful_rounds == 3){
			cout<<endl;
			cout<< "overall try"<< try_times <<" times to achieve the results." << endl;
			sc_stop();
		}
		//wait(10,SC_PS);
		//
	}
}

#endif
