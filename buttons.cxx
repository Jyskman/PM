// cpp file for the buttons

#include <iostream>
#include "buttons.h"
#include <sr595.h>
#include <wiringPi.h>


#include <sys/time.h>
#include <unistd.h>
// working on millis and debounce -


using namespace std;


int add(int x, int y)
{
    return x + y;
}

button_input::button_input(int a){

//sr595Setup (100, 10, 0, 1, 2) ;
//    Use wiringPi pins 0, 1 & 2 for data, clock and latch
sr595Setup (100, nr_buttons, 21, 22, 23) ;
fill(button_array[0], button_array[0] + 4 * 15, 0);


}

void button_input::setJumpstate(int state){
	button_array[0][0] = state;

	};

void button_input::updateState(){

    //digitalWrite (101, 1) ; - remove if no function, unsure

    // reset reading and verification, also transfer last cycle state to the 4th row

    for (int i = 0; i < nr_buttons-1; i++) {
		button_array[0][i] = 0;
		button_array[1][i] = 0;
		button_array[3][i] = button_array[2][i];
	}


	// Reading
	for (int i = 0; i < nr_buttons-1; i++) {
		digitalWrite(101+i,1);
				if ( digitalRead(27) == 1 ) {
					//setJumpstate(1);
					button_array[0][i] = 1;
				} else {
					//setJumpstate(0);
					button_array[0][i] = 0;
				}
		digitalWrite(101+i,0);
	}
	usleep(5 * 1000); //ms

	// Verification after delay
	for (int i = 0; i < nr_buttons-1; i++) {
		digitalWrite(101+i,1);
				if ( digitalRead(27) == 1 ) {
					//setJumpstate(1);
					button_array[1][i] = 1;
				} else {
					//setJumpstate(0);
					button_array[1][i] = 0;
				}
		digitalWrite(101+i,0);
	}

	// comparison and set of current state
	for (int i = 0; i < nr_buttons-1; i++) {

		if (button_array[0][i] == button_array[1][i] ) {
			button_array[2][i] = button_array[1][i];
		} else {
			button_array[2][i] = button_array[3][i];
		}

	}

};

bool button_input::getJumpState(){


	if ( button_array[2][2] == 1 ) {
		return true;
	} else {
		return false;
	}

};

bool button_input::getJumpstate_justpressed() {
	
	if( button_array[2][2] == 1 && button_array[3][2] == 0 ) {
		return true;
	} else {
		return false;
	};
	
	
	
};

bool button_input::getJumpstate_justreleased() {
	
	if( button_array[2][2] == 0 && button_array[3][2] == 1 ) {
		return true;
	} else {
		return false;
	};
	
	
	
};

bool button_input::getXstate_justpressed() {

	if( button_array[2][4] == 1 && button_array[3][4] == 0 ) {
		return true;
	} else {
		return false;
	};


};




bool button_input::getShootState(){


	if ( button_array[2][3] == 1 ) {
		return true;
	} else {
		return false;
	}

};

bool button_input::getXState(){


	if ( button_array[2][4] == 1 ) {
		return true;
	} else {
		return false;
	}

};

bool button_input::getAState(){


	if ( button_array[2][5] == 1 ) {
		return true;
	} else {
		return false;
	}

};

bool button_input::getUpState(){


	if ( button_array[2][8] == 1 ) {
		return true;
	} else {
		return false;
	}

};

bool button_input::getDownState(){


	if ( button_array[2][0] == 1 ) {
		return true;
	} else {
		return false;
	}

};

bool button_input::getLeftState(){


	if ( button_array[2][1] == 1 ) {
		return true;
	} else {
		return false;
	}

};

bool button_input::getRightState(){


	if ( button_array[2][9] == 1 ) {
		return true;
	} else {
		return false;
	}

};

bool button_input::getStartState(){


	if ( button_array[2][11] == 1 ) {
		return true;
	} else {
		return false;
	}

};

bool button_input::getSelectState(){


	if ( button_array[2][10] == 1 ) {
		return true;
	} else {
		return false;
	}

};

void button_input::printAll(){

for (int i = 0; i < nr_buttons; i++){
	printf("%d", button_array[0][i]);
}
printf("\n");

for (int i = 0; i < nr_buttons; i++){
	printf("%d", button_array[1][i]);
}
printf("\n");

for (int i = 0; i < nr_buttons; i++){
	printf("%d", button_array[2][i]);
}
printf("\n");
for (int i = 0; i < nr_buttons; i++){
	printf("%d", button_array[3][i]);
}
printf("\n");
printf("\n");
};

