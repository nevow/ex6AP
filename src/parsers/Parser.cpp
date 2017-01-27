//
// Parser.
//
#include "Parser.h"

Driver *Parser::createDriver() {
    char id[12], age[5], status[3], experience[5], vehicleId[12];
    char buffer[60];
    char c;
    cin.getline(buffer, sizeof(buffer), '\n');
    int inputId = 0, flag2 = 0;
    int i = 0;
    int lastIndex = 0;
    do {
        c = buffer[i];
        if ((c == ' ') && (flag2 == 0)) {
            i++;
            lastIndex++;
            continue;
        } else {
            flag2 = 1;
        }
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
    char vehicleId[12], taxi_type[3], manufacturer[3], color[3];
    char buffer[40];
    char c;
    cin.getline(buffer, sizeof(buffer), '\n');
    int inputId = 0, flag = 0, flag2 = 0;
    int i = 0;
    int lastIndex = 0;

    do {
        c = buffer[i];
        if ((c == ' ') && (flag2 == 0)) {
            i++;
            lastIndex++;
            continue;
        } else {
            flag2 = 1;
        }
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
                    flag = 1;
                    break;
            }
        }
        i++;
    } while (c != '\0');
    if (flag == 0 && inputId == 4) {
        try {
            int taxiId = isValidId(vehicleId);
            Color clr = isValidColor(color);
            CarManufacture cm = isValidManufacture(manufacturer);
            if (taxi_type[0] == '1') {                     // create regular cab
                return new Cab(clr, cm, taxiId);
            } else if (taxi_type[0] == '2') {              // create LuxuryCab cab
                return new LuxuryCab(clr, cm, taxiId);
            } else {
                return NULL;
            }
        } catch (...) {
            return NULL;
        }
    }
    return NULL;
}

TripInfo *Parser::createTripInfo(int clock, int x, int y) {
    char id[12], startx[6], starty[6], endx[6], endy[6], amountOfPassengers[3],
        tariff[11], time[11];
    char buffer[120];
    char c;
    cin.getline(buffer, sizeof(buffer), '\n');
    int inputId = 0, flag = 0, flag2 = 0;
    int i = 0;
    int lastIndex = 0;
    do {
        c = buffer[i];
        if ((c == ' ') && (flag2 == 0)) {
            i++;
            lastIndex++;
            continue;
        } else {
            flag2 = 1;
        }
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
                    flag = 1;
                    break;
            }
        }
        i++;
    } while (c != '\0');
    if (flag == 0 && inputId == 8) {
        int tripId, passengers, tripTariff, tripTime;
        Point *start = NULL, *end = NULL;
        try {
            tripId = isValidId(id);
            passengers = isValidAmountOfPassengers(amountOfPassengers);
            start = isValidPoint(startx, starty);
            if (start == NULL) {
                return NULL;
            }
            end = isValidPoint(endx, endy);
            if (end == NULL) {
                delete start;
                return NULL;
            }
            isValidPointOnGrid(start, x, y);
            isValidPointOnGrid(end, x, y);
            tripTariff = isValidTariff(tariff);
            tripTime = isValidTime(time, clock);
            return new TripInfo(tripId, start, end, passengers, tripTariff, tripTime);
        } catch (...) {
            delete start;
            delete end;
        }
    }
    return NULL;

}

Map *Parser::createMap() {
    int flag = 0;
    char columns[6], r[6];
    char buffer[40];
    char c;
    cin.getline(buffer, sizeof(buffer), '\n');
    int inputId = 0, flag2 = 0;
    int i = 0;
    int lastIndex = 0;
    do {
        c = buffer[i];
        if ((c == ' ') && (flag2 == 0)) {
            i++;
            lastIndex++;
            continue;
        } else {
            flag2 = 1;
        }
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
                    flag = 1;
                    c = '\0';
                    break;
                }
            }
        }
        i++;
    } while (c != '\0');

    if (flag == 0 && inputId == 2) {
        int cols, rows;
        cols = isValidMapSize(columns);
        rows = isValidMapSize(r);
        if (cols == -1 || rows == -1) {
            return NULL;
        }
        gridCols = cols;
        gridRows = rows;
        return new Map(cols, rows);
    }
    return NULL;
}

Point *Parser::createPoint() {
    int flag = 0;
    char xCoord[6], yCoord[6];
    char buffer[30];
    char c;
    cin.getline(buffer, sizeof(buffer), '\n');
    int inputId = 0, flag2 = 0;
    int i = 0;
    int lastIndex = 0;
    do {
        c = buffer[i];
        if ((c == ' ') && (flag2 == 0)) {
            i++;
            lastIndex++;
            continue;
        } else {
            flag2 = 1;
        }
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
                    flag = 1;
                    break;
                }
            }
        }
        i++;
    } while (c != '\0');

    if (flag == 0 && inputId == 2) {
        Point *p;
        try {
            p = isValidPoint(xCoord, yCoord);
            return p;
        } catch (...) {
            return NULL;
        }
    }
    return NULL;
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
        if (!checksIfNumberIsValid(idInput)) {
            throw "not a valid number input from user";
        }
        int id = stoi(idInput);
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
        if (!checksIfNumberIsValid(ageInput)) {
            throw "not a valid number input from user";
        }
        int age = stoi(ageInput);
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
        if (!checksIfNumberIsValid(amountOfPassengers)) {
            throw "not a valid number input from user";
        }
        int amount = stoi(amountOfPassengers);
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
        if (!checksIfNumberIsValid(experienceInput)) {
            throw "not a valid number input from user";
        }
        int experience = stoi(experienceInput);
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
        if (!checksIfNumberIsValid(tariffInput)) {
            throw "not a valid number input from user";
        }
        int tariff = stoi(tariffInput);
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
        if (!checksIfNumberIsValid(time)) {
            throw "not a valid number input from user";
        }
        int tripTime = stoi(time);
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
        if (!checksIfNumberIsValid(Coord)) {
            return -1;
        }
        int size = stoi(Coord);
        if (size <= 0) {
            return -1;
        }
        return size;
    } catch (...) {
        return -1;
    }
}

MartialStatues Parser::isValidMartialStatues(char *statuesInput) {
    char c = statuesInput[0];
    int i = 0;
    while (c != '\0') {
        i++;
        c = statuesInput[i];
    }
    try {
        if (i == 1) {
            return MartialStatuesFactory::getMartialStatus(statuesInput[0]);
        }
        throw "bad MartialStatues input from user";
    } catch (...) {
        throw "bad MartialStatues input from user";
    }

}

Color Parser::isValidColor(char *color) {
    char c = color[0];
    int i = 0;
    while (c != '\0') {
        i++;
        c = color[i];
    }
    try {
        if (i == 1) {
            return ColorFactory::charToColor(color[0]);
        }
        throw "bad Color input from user";
    } catch (...) {
        throw "bad Color input from user";
    }
}

CarManufacture Parser::isValidManufacture(char *manufacture) {
    char c = manufacture[0];
    int i = 0;
    while (c != '\0') {
        i++;
        c = manufacture[i];
    }
    try {
        if (i == 1) {
            return CarManufactureFactory::charToFirm(manufacture[0]);
        }
        throw "bad CarManufacture input from user";
    } catch (...) {
        throw "bad CarManufacture input from user";
    }
}

Point *Parser::isValidPoint(char *x, char *y) {
    try {
        if (!checksIfNumberIsValid(x) || !checksIfNumberIsValid(y)) {
            throw "bad Point input from user";
        }
        int xCoord = stoi(x);
        int yCoord = stoi(y);
        if ((xCoord < 0) || (yCoord < 0)) {
            throw "not a valid Coordinates input from user";
        }
        Point point(xCoord, yCoord);
        isValidPointOnGrid(&point, gridCols, gridRows);
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

int Parser::checksIfNumberIsValid(char *c) {
    if (c[0] == '\0') {
        return false;
    }
    for (int i = 0; c[i] != '\0'; i++) {
        if (!(isdigit(c[i]))) {
            return false;
        }
    }
    return true;
}

int Parser::getPositiveNumberFromUser() {
    char c[10];
    cin.getline(c, sizeof(c), '\n');
    if (checksIfNumberIsValid(c)) {
        return atoi(c);
    } else {
        return -1;
    }
}

int Parser::isObstacle(Point *p, list<Node *> *obstacles) {
    for (std::list<Node *>::const_iterator iterator = obstacles->begin(),
             end = obstacles->end(); iterator != end; ++iterator) {
        if (*((*iterator)->getP()) == *p) {
            return 1;
        }
    }
    return 0;
}
