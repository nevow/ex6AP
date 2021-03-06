//
// client.
//

#include "../server/tripOperations/Driver.h"
#include "../server/sockets/Tcp.h"
#include "../parsers/Parser.h"

using namespace std;

int main(int argc, char *argv[]) {
    Driver *driver;
    Parser parse;
    try {
        // get a driver with the user input
        driver = parse.createDriver();
    } catch (char const *s) {
        return 1;
    }

    char buffer[50];

    // create a socket for transferring data between the server and the client
    Socket *sock = new Tcp(0, atoi(argv[2]));
    int connected = sock->initialize(0);
    if (connected == ERROR_CONNECT) {
        delete driver;
        delete sock;
        return 2;
    }

    // serialize and sendData the driver
    DataSender<Driver>::sendData(sock, driver, 0);

    // deserialize the taxi from the server
    Taxi *cab = DataSender<Taxi>::receiveData(sock, 0); // wait to receive a cab from the server
    driver->setCab(cab);                                // set the cab to the driver

    TripInfo *ti = NULL;
    std::list<CoordinatedItem *> *tempRoad = NULL;      // to save the road of  the trip info
    // do while the server still sends orders different from the exit order "exit"
    do {
        sock->receiveData(buffer, sizeof(buffer), 0);   // wait for the orders from the server
        sock->sendData("received", 0);                  // send the massage for received
        if (!strcmp(buffer, "get_ready_for_trip_info")) {
            // deserialize the trip info from the server
            ti = DataSender<TripInfo>::receiveData(sock, 0);
            sock->sendData("received", 0);              // send confirmation for the trip info
            tempRoad = new list<CoordinatedItem *>;
            std::list<CoordinatedItem *> *road = ti->getRoad();
            // pass the coordinated items of the road to the tempRoad
            for (std::list<CoordinatedItem *>::const_iterator iterator = road->begin(),
                         end = road->end(); iterator != end; ++iterator) {
                tempRoad->push_back(*(iterator));
            }

            driver->setTi(ti);                           // set the driver with the trip info
        } else if (!strcmp(buffer, "9") && (ti != NULL)) {
            driver->moveOneStep();                       // move the driver one step

            if (driver->getTi()->checkEnd(cab->getLocation()->getP())) { // if reached the end
                delete ti;                               // delete the trip info
                while (!tempRoad->empty()) {             // delete all the items of the tempRoad
                    delete tempRoad->front();
                    tempRoad->pop_front();
                }
                delete tempRoad;
                // set all to null
                tempRoad = NULL;
                driver->setTi(NULL);
                ti = NULL;
            }

        }
        // if the client received the advance order
    } while (strcmp(buffer, "exit"));

    // delete all objects in the client
    if (tempRoad != NULL) {
        while (!tempRoad->empty()) {
            delete tempRoad->front();
            tempRoad->pop_front();
        }
        delete tempRoad;
    }
    delete cab;
    delete driver;
    delete sock;
    return 0;
}