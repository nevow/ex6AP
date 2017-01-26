//
// Parser.
//

#ifndef EX6AP_DRIVERPARSER_H
#define EX6AP_DRIVERPARSER_H

#include "../server/tripOperations/Driver.h"
#include "../server/enum/MartialStatuesFactory.h"
#include "../server/taxi/Cab.h"
#include "../server/taxi/LuxuryCab.h"
#include "../server/enum/ColorFactory.h"
#include "../server/enum/CarManufactureFactory.h"
#include "../server/coordinates/Map.h"

using namespace std;

class Parser {
private:
    int gridCols;
    int gridRows;
public:
    Driver *createDriver();

    Taxi *createTaxi();

    TripInfo *createTripInfo(int clock, int x, int y);

    Map *createMap();

    Point *createPoint();

    void validInputAndCopy(char *dst, char *src, int dstSize, int startIndex, int endIndex);

    int isValidId(char *id);

    int isValidAge(char *ageInput);

    int isValidAmountOfPassengers(char *amountOfPassengers);

    int isValidExperience(char *experienceInput);

    int isValidTariff(char *tariffInput);

    int isValidTime(char *time, int clock);

    int isValidMapSize(char *x);

    MartialStatues isValidMartialStatues(char *statuesInput);

    Color isValidColor(char *color);

    CarManufacture isValidManufacture(char *manufacture);

    Point *isValidPoint(char *x, char *y);

    void isValidPointOnGrid(Point *p, int cols, int rows);

    int checksIfNumberIsValid(char *c);

    int getPositiveNumberFromUser();

    int isObstacle(Point *, list<Node *> *obstacles);

};


#endif //EX6AP_DRIVERPARSER_H
