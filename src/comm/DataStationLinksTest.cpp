#include <iostream>
#include "DataStationLink.h"

using namespace std;

int main(){
    DataStationLink *dsLink = new DataStationLink("/dev/ttyUSB0");

    dsLink->writeDataStationLink("h", 1);

    cout << "sent\n";

    return 0;
}
