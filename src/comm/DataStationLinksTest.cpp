#include <iostream>
#include "DataStationLink.h"

using namespace std;

int main(){
<<<<<<< HEAD
	char portName[256] = "/dev/ttyUSB0";

	cout << portName;
	DataStationLink * dataStationLink = new DataStationLink(portName);
	
	std::cout << "Sent!" << endl;

	char buffer[2] = {'!','\x00'};
	dataStationLink->writeDataStationLink(buffer, 2);
	
	std::cout << buffer << endl;
	
	char inputBuffer[1024];
	dataStationLink->readDataStationLink(inputBuffer, 1);
	
	std::cout << inputBuffer << endl;

	return 0;
=======
    DataStationLink *dsLink = new DataStationLink("/dev/ttyUSB0");

    dsLink->writeDataStationLink("h", 1);

    cout << "sent\n";

    return 0;
>>>>>>> 3eee0397a2667c848b8ce6d40f26af4ad6c6f74f
}
