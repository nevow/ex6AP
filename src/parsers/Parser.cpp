//
// Parser.
//
#include "Parser.h"

/**
 * @return a Driver or throw exception for bad input
 */
Driver *Parser::createDriver() {
    char id[12], age[5], status[3], experience[5], vehicleId[12];  // buffers for the info
    char buffer[60];
    char c;
    cin.getline(buffer, sizeof(buffer), '\n');
    int inputId = 0, flag2 = 0;
    int i = 0;
    int lastIndex = 0;
    // keep traversing over the letters until all the buffer got rinserted to the rights arrays
    do {
        c = buffer[i];
        // if the start of the buffer is space
        if ((c == ' ') && (flag2 == 0)) {
            i++;
            lastIndex++;
            continue;
        } else {
            // reached the a letter not space. stop ignoring spaces
            flag2 = 1;
        }
        // cut the buffer with the ',' and the '\0' letters
        if (c == ',' || c == '\0') {
            // input id represents the array to save the letters to
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
    // validate all the info in the arrays
    // if one of the data is not valid or incorrect, throw an exception
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

/**
 * @return a Taxi or NULL for bad input
 */
Taxi *Parser::createTaxi() {
    char vehicleId[12], taxi_type[3], manufacturer[3], color[3];
    char buffer[40];
    char c;
    cin.getline(buffer, sizeof(buffer), '\n');
    int inputId = 0, flag = 0, flag2 = 0;
    int i = 0;
    int lastIndex = 0;
    // keep traversing over the letters until all the buffer got rinserted to the rights arrays
    do {
        c = buffer[i];
        // if the start of the buffer is space
        if ((c == ' ') && (flag2 == 0)) {
            i++;
            lastIndex++;
            continue;
        } else {
            // reached the a letter not space. stop ignoring spaces
            flag2 = 1;
        }
        // cut the buffer with the ',' and the '\0' letters
        if (c == ',' || c == '\0') {
            // input id represents the array to save the letters to
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
    // if the flag is 1 or the input id is not 4, there is an error, return NULL
    if (flag == 0 && inputId == 4) {
        // validate all the info in the arrays
        // if one of the data is not valid or incorrect, return NULL
        try {
            int taxiId = isValidId(vehicleId);
            Color clr = isValidColor(color);
            CarManufacture cm = isValidManufacture(manufacturer);
            if (taxi_type[0] == '1') {                     // create regular cab
                return new Cab(clr, cm, taxiId);
            } else if (taxi_type[0] == '2') {              // create LuxuryCab cab
                return new LuxuryCab(clr, cm, taxiId);
            }
        } catch (...) {
            return NULL;
        }
    }
    return NULL;
}

/**
 * @return a TripInfo or NULL for bad input
 */
TripInfo *Parser::createTripInfo(int clock, int x, int y) {
    char id[12], startx[6], starty[6], endx[6], endy[6], amountOfPassengers[3],
            tariff[11], time[11];
    char buffer[120];
    char c;
    cin.getline(buffer, sizeof(buffer), '\n');
    int inputId = 0, flag = 0, flag2 = 0;
    int i = 0;
    int lastIndex = 0;
    // keep traversing over the letters until all the buffer got rinserted to the rights arrays
    do {
        c = buffer[i];
        // if the start of the buffer is space
        if ((c == ' ') && (flag2 == 0)) {
            i++;
            lastIndex++;
            continue;
        } else {
            // reached the a letter not space. stop ignoring spaces
            flag2 = 1;
        }
        // cut the buffer with the ',' and the '\0' letters
        if (c == ',' || c == '\0') {
            // input id represents the array to save the letters to
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

    // if the flag is 1 or the input id is not 4, there is an error, return NULL
    if (flag == 0 && inputId == 8) {
        int tripId, passengers, tripTariff, tripTime;
        Point *start = NULL, *end = NULL;
        // validate all the info in the arrays
        // if one of the data is not valid or incorrect, return NULL
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

/**
 * @return a Map or NULL for bad input
 */
Map *Parser::createMap() {
    int flag = 0;
    char columns[6], r[6];
    char buffer[40];
    char c;
    cin.getline(buffer, sizeof(buffer), '\n');
    int inputId = 0;
    int i = 0;
    int lastIndex = 0;
    // keep traversing over the letters until all the buffer got rinserted to the rights arrays
    do {
        c = buffer[i];
        // if the start of the buffer is space
        if (c == ' ') {
            i++;
            lastIndex++;
            continue;
        }
        while ((c != ' ') && (c != '\0')) {
            i++;
            c = buffer[i];
        }
        // cut the buffer with the ' ' and the '\0' letters
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

        i++;
    } while (c != '\0');
    // validate all the info in the arrays
    // if one of the data is not valid or incorrect, return NULL
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

/**
 * @return a Point or NULL for bad input
 */
Point *Parser::createPoint() {
    int flag = 0;
    char xCoord[6], yCoord[6];
    char buffer[30];
    char c;
    cin.getline(buffer, sizeof(buffer), '\n');
    int inputId = 0, flag2 = 0;
    int i = 0;
    int lastIndex = 0;
    // keep traversing over the letters until all the buffer got rinserted to the rights arrays
    do {
        c = buffer[i];
        // if the start of the buffer is space
        if ((c == ' ') && (flag2 == 0)) {
            i++;
            lastIndex++;
            continue;
        } else {
            // reached the a letter not space. stop ignoring spaces
            flag2 = 1;
        }
        // cut the buffer with the ',' and the '\0' letters
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
        // validate all the info in the arrays
        // if one of the data is not valid or incorrect, return NULL
        try {
            p = isValidPoint(xCoord, yCoord);
            return p;
        } catch (...) {
            return NULL;
        }
    }
    return NULL;
}

/**
 * @param dst to copy to
 * @param src to copy from
 * @param dstSize size of the dst
 * @param startIndex start index to copy from the src
 * @param endIndex end index to copy from the src
 */
void Parser::validInputAndCopy(char *dst, char *src, int dstSize, int startIndex,
                               int endIndex) {
    int j;
    // if no enough space in the dst to receive the data throw exception
    if (startIndex - endIndex > dstSize - 1) {
        throw "bad input from user";
    }
    // copy the data to dst
    for (j = startIndex; j <= endIndex; j++) {
        dst[j - startIndex] = src[j];
    }
    dst[(j - startIndex)] = '\0';
}

/**
 * @param idInput buffer that needs to hold an id
 * @return the id if valid or throw exception
 */
int Parser::isValidId(char *idInput) {
    try {
        // if the buffer is not a number
        if (!checksIfNumberIsValid(idInput)) {
            throw "not a valid number input from user";
        }
        // id gets the number
        int id = stoi(idInput);
        if (id < 0) {
            throw "negative id input from user";
        }
        return id;
    } catch (...) {
        throw "bad id input from user";
    }
}

/**
 * @param ageInput buffer that needs to hold an age
 * @return the age if valid or throw exception
 */
int Parser::isValidAge(char *ageInput) {
    try {
        // if the buffer is not a number
        if (!checksIfNumberIsValid(ageInput)) {
            throw "not a valid number input from user";
        }
        // age gets the number
        int age = stoi(ageInput);
        // if the age is negative or above 120
        if ((age < 0) || (age > 120)) {
            throw "not a valid age input from user";
        }
        return age;
    } catch (...) {
        throw "bad age input from user";
    }
}

/**
 * @param amountOfPassengers buffer that needs to hold an amount
 * @return the amount if valid or throw exception
 */
int Parser::isValidAmountOfPassengers(char *amountOfPassengers) {
    try {
        // if the buffer is not a number
        if (!checksIfNumberIsValid(amountOfPassengers)) {
            throw "not a valid number input from user";
        }
        // amount gets the number
        int amount = stoi(amountOfPassengers);
        // if the amount is negative or above 4
        if ((amount < 0) || (amount > 4)) {
            throw "not a valid amount of passengers input from user";
        }
        return amount;
    } catch (...) {
        throw "bad amount of passengers input from user";
    }
}

/**
 * @param experienceInput buffer that needs to hold an experience
 * @return the experience if valid or throw exception
 */
int Parser::isValidExperience(char *experienceInput) {
    try {
        // if the buffer is not a number
        if (!checksIfNumberIsValid(experienceInput)) {
            throw "not a valid number input from user";
        }
        // experience gets the number
        int experience = stoi(experienceInput);
        // if the experience is negative or above 120
        if ((experience < 0) || (experience > 120)) {
            throw "not a valid experience input from user";
        }
        return experience;
    } catch (...) {
        throw "bad experience input from user";
    }
}

/**
 * @param tariffInput buffer that needs to hold a tariff
 * @return the tariff if valid or throw exception
 */
int Parser::isValidTariff(char *tariffInput) {
    try {
        // if the buffer is not a number
        if (!checksIfNumberIsValid(tariffInput)) {
            throw "not a valid number input from user";
        }
        // tariff gets the number
        int tariff = stoi(tariffInput);
        // if the tariff is negative
        if (tariff < 0) {
            throw "not a valid tariff input from user";
        }
        return tariff;
    } catch (...) {
        throw "bad tariff input from user";
    }
}

/**
 * @param time buffer that needs to hold a time
 * @param clock represents the time
 * @return the time if valid or throw exception
 */
int Parser::isValidTime(char *time, int clock) {
    try {
        // if the buffer is not a number
        if (!checksIfNumberIsValid(time)) {
            throw "not a valid number input from user";
        }
        // tripTime gets the number
        int tripTime = stoi(time);
        // if the experience is negative or below clock
        if ((tripTime <= 0) || (tripTime < clock)) {
            throw "trip time can't be below the clock time";
        }
        return tripTime;
    } catch (...) {
        throw "not a valid time input from user";
    }
}

/**
 * @param Coord buffer that needs to hold a size
 * @return the size if valid or -1 if not
 */
int Parser::isValidMapSize(char *Coord) {
    try {
        // if the buffer is not a number
        if (!checksIfNumberIsValid(Coord)) {
            return -1;
        }
        // size gets the number
        int size = stoi(Coord);
        // if the size is zero and below
        if (size <= 0) {
            return -1;
        }
        return size;
    } catch (...) {
        return -1;
    }
}

/**
 * @param statuesInput buffer that needs to hold a statues letter
 * @return the statues if valid or throw exception
 */
MartialStatues Parser::isValidMartialStatues(char *statuesInput) {
    char c = statuesInput[0];
    int i = 0;
    while (c != '\0') {
        i++;
        c = statuesInput[i];
    }
    try {
        // if i == 1 then input is a single letter
        if (i == 1) {
            return MartialStatuesFactory::getMartialStatus(statuesInput[0]);
        }
        throw "bad MartialStatues input from user";
    } catch (...) {
        throw "bad MartialStatues input from user";
    }

}

/**
 * @param color buffer that needs to hold a color letter
 * @return the color if valid or throw exception
 */
Color Parser::isValidColor(char *color) {
    char c = color[0];
    int i = 0;
    while (c != '\0') {
        i++;
        c = color[i];
    }
    try {
        // if i == 1 then input is a single letter
        if (i == 1) {
            return ColorFactory::charToColor(color[0]);
        }
        throw "bad Color input from user";
    } catch (...) {
        throw "bad Color input from user";
    }
}

/**
 * @param manufacture buffer that needs to hold a manufacture letter
 * @return the manufacture if valid or throw exception
 */
CarManufacture Parser::isValidManufacture(char *manufacture) {
    char c = manufacture[0];
    int i = 0;
    while (c != '\0') {
        i++;
        c = manufacture[i];
    }
    try {
        // if i == 1 then input is a single letter
        if (i == 1) {
            return CarManufactureFactory::charToFirm(manufacture[0]);
        }
        throw "bad CarManufacture input from user";
    } catch (...) {
        throw "bad CarManufacture input from user";
    }
}

/**
 * @param x buffer that needs to hold a x coord
 * @param y buffer that needs to hold a y coord
 * @return the Point if valid or throw exception
 */
Point *Parser::isValidPoint(char *x, char *y) {
    try {
        // if the one of the buffers is not a number
        if (!checksIfNumberIsValid(x) || !checksIfNumberIsValid(y)) {
            throw "bad Point input from user";
        }
        int xCoord = stoi(x);
        int yCoord = stoi(y);
        // if the one of the coords is negative
        if ((xCoord < 0) || (yCoord < 0)) {
            throw "not a valid Coordinates input from user";
        }
        Point point(xCoord, yCoord);
        // validate that the point is on grid boundaries
        isValidPointOnGrid(&point, gridCols, gridRows);
        return new Point(xCoord, yCoord);
    } catch (...) {
        throw "bad Point input from user";
    }
}

/**
 * @param p point to check
 * @param cols of the grid
 * @param rows of the grid
 */
void Parser::isValidPointOnGrid(Point *p, int cols, int rows) {
    // throws exception if the point is not on the grid boundaries
    if ((rows <= p->getY()) || (cols <= p->getX())) {
        throw "not a valid Coordinates input from user";
    }
}

/**
 * @param c array to check if all values are numbers
 * @return 0 if not a number, 1 if a number
 */
int Parser::checksIfNumberIsValid(char *c) {
    if (c[0] == '\0') {
        return false;
    }
    // check all letter in the array
    for (int i = 0; c[i] != '\0'; i++) {
        if (!(isdigit(c[i]))) {
            return false;
        }
    }
    // all chars are numbers
    return true;
}

/**
 * @return get input from user. if it is a positive number return it, -1 otherwise
 */
int Parser::getPositiveNumberFromUser() {
    char c[12];
    cin.getline(c, sizeof(c), '\n');
    // check if the input is a number
    if (checksIfNumberIsValid(c)) {
        // return its value
        return atoi(c);
    } else {
        return -1;
    }
}

/**
 * @param p to check
 * @param obstacles list to check if point is one of them
 * @return 1 if the point is an obstacle, 0 otherwise
 */
int Parser::isObstacle(Point *p, list<Node *> *obstacles) {
    // iterate over all the obstacles, compare them with p
    for (std::list<Node *>::const_iterator iterator = obstacles->begin(),
                 end = obstacles->end(); iterator != end; ++iterator) {
        // if p is the same as one of the obstacles, return 1;
        if (*((*iterator)->getP()) == *p) {
            return 1;
        }
    }
    // p is not an obstacle, return 0
    return 0;
}
