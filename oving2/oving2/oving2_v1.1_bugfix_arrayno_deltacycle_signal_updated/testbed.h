
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
	sc_port < Push_if > port2Button[10];///10!!!!

	void testbed_process(void);

	testbed (sc_module_name nm): sc_module(nm){

		SC_HAS_PROCESS(testbed);

		SC_THREAD(testbed_process);
	}

};

void testbed::testbed_process(void){
	int successful_rounds = 0;
	int successful_counts = 0;
	int try_times = 0;
	int correct[10];// restore the successful tests.
	cout << "TestBench launched, test is running !" << endl;

	while(true){

		int i = 1 + rand() % 9;  //  1 <= i <= 9, IS % 9!!!!! 0 - 8
		//int i = 3;
		port2Button[i]->Push();
		try_times++; // to show how many times have been tried
				cout << try_times <<"-th try: ";
				//wait(1,SC_MS);////WAIT THE SIGNAL GET UPDATED!!!!
		bool bl_temp;
		bl_temp = port2Button[i]->Checklight();
		if(bl_temp) {
			cout << i << " successful " << endl;
			correct[successful_counts]=i;
			cout << "Current get secrete code order : " ;
			for( int j = 0; j <= successful_counts; j++ ){
				cout << correct[j] << ", ";
			}
			cout << endl;
			        successful_counts++;

		}
		else {
			cout << "fail " << i << endl;
			int j;

			for ( j = 0; j < successful_counts; j++){// successful counts = 0 should be careful
				port2Button[correct[j]]->Push();// once failed , try the restored correct ones from beginning
			}

		}

		if( successful_counts == 9){
			successful_counts = 0;
			successful_rounds++;
		}

		if((successful_rounds == 1)||(try_times == 130)){
			cout<<endl;
			cout<< "overall try "<< try_times <<" times to achieve the results." << endl;
			sc_stop();
		}
		//wait(10,SC_PS);
		//

	}
}

#endif
