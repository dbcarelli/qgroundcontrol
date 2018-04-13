#include <iostream>
#include "DataStationLink.h"

using namespace std;

int main(){
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
}
