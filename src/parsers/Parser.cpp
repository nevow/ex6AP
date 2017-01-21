//
// Parser.
//
#include "Parser.h"

Driver *Parser::createDriver() {
    char id[11], age[4], status[2], experience[4], vehicleId[11];
    char buffer[40];
    char c;
    cin.getline(buffer, sizeof(buffer), '\n');
    int inputId = 0;
    int i = 0;
    int lastIndex = 0;
    do {
        c = buffer[i];
        if (c == ',' || c == '\0') {
            switch (inputId) {
                case 0: {
                    validInputAndCopy(id, buffer, sizeof(id), lastIndex, (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                case 1: {
                    validInputAndCopy(age, buffer, sizeof(age), lastIndex, (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                case 2: {
                    validInputAndCopy(status, buffer, sizeof(status), lastIndex, (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                case 3: {
                    validInputAndCopy(experience, buffer, sizeof(experience), lastIndex,
                                      (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                case 4: {
                    validInputAndCopy(vehicleId, buffer, sizeof(vehicleId), lastIndex, (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                default:
                    throw "bad input from user";
            }
        }
        i++;
    } while (c != '\0');

    int driverId, driverAge, driverExperience, taxiId;
    MartialStatues m;
    try {
        driverId = isValidId(id);
        driverAge = isValidAge(age);
        m = isValidMartialStatues(status);
        driverExperience = isValidExperience(experience);
        taxiId = isValidId(vehicleId);
        if (driverAge < driverExperience) {
            throw "experience can't be higher than driver age";
        }
        return new Driver(driverId, driverAge, m, driverExperience, taxiId);
    } catch (exception e) {
        throw e;
    }
}

Taxi *Parser::createTaxi() {
    char vehicleId[11], taxi_type[2], manufacturer[2], color[2];
    char buffer[20];
    char c;
    cin.getline(buffer, sizeof(buffer), '\n');
    int inputId = 0;
    int i = 0;
    int lastIndex = 0;

    do {
        c = buffer[i];
        if (c == ',' || c == '\0') {
            switch (inputId) {
                case 0: {
                    validInputAndCopy(vehicleId, buffer, sizeof(vehicleId), lastIndex, (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                case 1: {
                    validInputAndCopy(taxi_type, buffer, sizeof(taxi_type), lastIndex, (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                case 2: {
                    validInputAndCopy(manufacturer, buffer, sizeof(manufacturer), lastIndex,
                                      (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                case 3: {
                    validInputAndCopy(color, buffer, sizeof(color), lastIndex,
                                      (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                default:
                    throw "bad input from user";
            }
        }
        i++;
    } while (c != '\0');

    try {
        int taxiId = isValidId(vehicleId);
        Color clr = isValidColor(color);
        CarManufacture cm = isValidManufacture(manufacturer);
        if (taxi_type[0] == '1') {                     // create regular cab
            return new Cab(clr, cm, taxiId);
        } else if (taxi_type[0] == '2') {              // create LuxuryCab cab
            return new LuxuryCab(clr, cm, taxiId);
        } else {
            throw "bad taxi type from user";
        }
    } catch (exception e) {
        throw e;
    }
}

TripInfo *Parser::createTripInfo(int clock, int x, int y) {
    char id[11], startx[5], starty[5], endx[5], endy[5], amountOfPassengers[2],
        tariff[10], time[10];
    char buffer[100];
    char c;
    cin.getline(buffer, sizeof(buffer), '\n');
    int inputId = 0;
    int i = 0;
    int lastIndex = 0;
    do {
        c = buffer[i];
        if (c == ',' || c == '\0') {
            switch (inputId) {
                case 0: {
                    validInputAndCopy(id, buffer, sizeof(id), lastIndex, (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                case 1: {
                    validInputAndCopy(startx, buffer, sizeof(startx), lastIndex, (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                case 2: {
                    validInputAndCopy(starty, buffer, sizeof(starty), lastIndex, (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                case 3: {
                    validInputAndCopy(endx, buffer, sizeof(endx), lastIndex, (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                case 4: {
                    validInputAndCopy(endy, buffer, sizeof(endy), lastIndex, (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                case 5: {
                    validInputAndCopy(amountOfPassengers, buffer, sizeof(amountOfPassengers),
                                      lastIndex, (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                case 6: {
                    validInputAndCopy(tariff, buffer, sizeof(tariff), lastIndex, (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                case 7: {
                    validInputAndCopy(time, buffer, sizeof(time), lastIndex, (i - 1));
                    lastIndex = i + 1;
                    inputId++;
                    break;
                }
                default:
                    throw "bad input from user";
            }
        }
        i++;
    } while (c != '\0');

    int tripId, passengers, tripTariff, tripTime;
    Point *start, *end;
    try {
        tripId = isValidId(id);
        passengers = isValidAmountOfPassengers(amountOfPassengers);
        start = isValidPoint(startx, starty);
        end = isValidPoint(endx, endy);
        isValidPointOnGrid(start, x, y);
        isValidPointOnGrid(end, x, y);
        tripTariff = isValidTariff(tariff);
        tripTime = isValidTime(time, clock);
        return new TripInfo(tripId, start, end, passengers, tripTariff, tripTime);
    } catch (exception e) {
        throw e;
    }
}

Map *Parser::createMap() {
    int flag = 0;
    do {
        int flag2 = 0;
        char columns[5], r[5];
        char buffer[20];
        char c;
        cin.getline(buffer, sizeof(buffer), '\n');
        int inputId = 0;
        int i = 0;
        int lastIndex = 0;
        do {
            c = buffer[i];
            if (c == ' ' || c == '\0') {
                switch (inputId) {
                    case 0: {
                        validInputAndCopy(columns, buffer, sizeof(columns), lastIndex, (i - 1));
                        lastIndex = i + 1;
                        inputId++;
                        break;
                    }
                    case 1: {
                        validInputAndCopy(r, buffer, sizeof(r), lastIndex, (i - 1));
                        lastIndex = i + 1;
                        inputId++;
                        break;
                    }
                    default: {
                        flag2 = 1;
                        break;
                    }
                }
            }
            i++;
        } while (c != '\0');

        if (flag2 == 0) {
            int cols, rows;
            try {
                cols = isValidMapSize(columns);
                rows = isValidMapSize(r);
                return new Map(cols, rows);
            } catch (...) {
                cout << -1 << endl;
                flag = 1;
            }
        }
    } while (flag);
}

Point *Parser::createPoint() {
    int flag = 0;
    do {
        int flag2 = 0;
        char xCoord[5], yCoord[5];
        char buffer[20];
        char c;
        cin.getline(buffer, sizeof(buffer), '\n');
        int inputId = 0;
        int i = 0;
        int lastIndex = 0;
        do {
            c = buffer[i];
            if (c == ',' || c == '\0') {
                switch (inputId) {
                    case 0: {
                        validInputAndCopy(xCoord, buffer, sizeof(xCoord), lastIndex, (i - 1));
                        lastIndex = i + 1;
                        inputId++;
                        break;
                    }
                    case 1: {
                        validInputAndCopy(yCoord, buffer, sizeof(yCoord), lastIndex, (i - 1));
                        lastIndex = i + 1;
                        inputId++;
                        break;
                    }
                    default: {
                        flag2 = 1;
                        break;
                    }
                }
            }
            i++;
        } while (c != '\0');

        if (flag2 == 0) {
            Point *p;
            try {
                p = isValidPoint(xCoord, yCoord);
                return p;
            } catch (...) {
                cout << -1 << endl;
                flag = 1;
            }
        }
    } while (flag);
}

void Parser::validInputAndCopy(char *dst, char *src, int dstSize, int startIndex,
                               int endIndex) {
    int j;
    if (startIndex - endIndex > dstSize - 1) {
        throw "bad input from user";
    }
    for (j = startIndex; j <= endIndex; j++) {
        dst[j - startIndex] = src[j];
    }
    dst[(j - startIndex)] = '\0';
}

int Parser::isValidId(char *idInput) {
    try {
        int id = atoi(idInput);
        if (id < 0) {
            throw "negative id input from user";
        }
        return id;
    } catch (...) {
        throw "bad id input from user";
    }
}

int Parser::isValidAge(char *ageInput) {
    try {
        int age = atoi(ageInput);
        if ((age < 0) || (age > 120)) {
            throw "not a valid age input from user";
        }
        return age;
    } catch (...) {
        throw "bad age input from user";
    }
}

int Parser::isValidAmountOfPassengers(char *amountOfPassengers) {
    try {
        int amount = atoi(amountOfPassengers);
        if ((amount < 0) || (amount > 4)) {
            throw "not a valid amount of passengers input from user";
        }
        return amount;
    } catch (...) {
        throw "bad amount of passengers input from user";
    }
}

int Parser::isValidExperience(char *experienceInput) {
    try {
        int experience = atoi(experienceInput);
        if ((experience < 0) || (experience > 120)) {
            throw "not a valid experience input from user";
        }
        return experience;
    } catch (...) {
        throw "bad experience input from user";
    }
}

int Parser::isValidTariff(char *tariffInput) {
    try {
        int tariff = atoi(tariffInput);
        if (tariff < 0) {
            throw "not a valid tariff input from user";
        }
        return tariff;
    } catch (...) {
        throw "bad tariff input from user";
    }
}


int Parser::isValidTime(char *time, int clock) {
    try {
        int tripTime = atoi(time);
        if ((tripTime <= 0) || (tripTime < clock)) {
            throw "trip time can't be below the clock time";
        }
        return tripTime;
    } catch (...) {
        throw "not a valid time input from user";
    }
}

int Parser::isValidMapSize(char *Coord) {
    try {
        int size = atoi(Coord);
        if (size <= 0) {
            throw "can't create map out of not positive numbers";
        }
        return size;
    } catch (...) {
        throw "not a valid number input from user";
    }
}

MartialStatues Parser::isValidMartialStatues(char *statuesInput) {
    try {
        return MartialStatuesFactory::getMartialStatus(statuesInput[0]);
    } catch (...) {
        throw "bad MartialStatues input from user";
    }
}

Color Parser::isValidColor(char *color) {
    try {
        return ColorFactory::charToColor(color[0]);
    } catch (...) {
        throw "bad Color input from user";
    }
}

CarManufacture Parser::isValidManufacture(char *manufacture) {
    try {
        return CarManufactureFactory::charToFirm(manufacture[0]);
    } catch (...) {
        throw "bad CarManufacture input from user";
    }
}

Point *Parser::isValidPoint(char *x, char *y) {
    try {
        int xCoord = atoi(x);
        int yCoord = atoi(y);
        if ((xCoord < 0) || (yCoord < 0)) {
            throw "not a valid Coordinates input from user";
        }
        return new Point(xCoord, yCoord);
    } catch (...) {
        throw "bad Point input from user";
    }
}

void Parser::isValidPointOnGrid(Point *p, int cols, int rows) {
    try {
        if ((rows <= p->getY()) || (cols <= p->getX())) {
            throw "not a valid Coordinates input from user";
        }
    } catch (...) {
        throw "bad Coordinates input from user";
    }
}
