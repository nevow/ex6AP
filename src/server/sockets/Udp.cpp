// UDP implementation.
// the class inherit from socket.
// methods of udp socket type.


#include "Udp.h"

/**
 * creating new Udp socket.
 * @param isServers  true - if server, false if client
 * @param port_num is the port number
 */
Udp::Udp(bool isServers, int port_num) {
    this->port_number = port_num;
    this->isServer = isServers;
}

/**
 * default destructor
 */
Udp::~Udp() {
}

/**
 * initialize the Socket object by using socket(), and bind() if server
 * @return int number representing the return status
 */
int Udp::initialize() {
    //creating new socket and getting his descriptor
    this->socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (this->socketDescriptor < 0) {
        return ERROR_SOCKET;
    }
    //if server
    if (this->isServer) {
        struct sockaddr_in sin;
        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = INADDR_ANY;
        sin.sin_port = htons(this->port_number);
        //bind
        if (bind(this->socketDescriptor, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
            return ERROR_BIND;
        }
    }
    //return correct if there were no problems
    return CORRECT;
}

/**
 * sending the input data to the socket who connect to this socket, check if send successfully.
 * @param data to send
 * @return int number representing the return status
 */
int Udp::sendData(string data) {
    //initialize the struct
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(this->ip_address.c_str());
    sin.sin_port = htons(this->port_number);
    const char *datas = data.c_str();
    int data_len = data.length() + 1;
    //sendData
    int sent_bytes = sendto(this->socketDescriptor, datas, data_len, 0, (struct sockaddr *) &sin,
                            sizeof(sin));
    //cout << sent_bytes << endl;
    //check if sendData successfully
    if (sent_bytes < 0) {
        return ERROR_SEND;
    }
    //return correct if there were no problems
    return CORRECT;
}

/**
 * getting data from the other socket check if there were no error receiving and print
 * @param buffer is string representing the data that has been send.
 * @param size is the size of the data
 * @return int number representing the return status
 */
int Udp::receiveData(char *buffer, int size) {
    struct sockaddr_in to;
    unsigned int to_len = sizeof(struct sockaddr_in);
    //receive
    int bytes = recvfrom(this->socketDescriptor,
                         buffer, size, 0, (struct sockaddr *) &to, &to_len);
    //set the port number to the new one which we get with the data
    this->port_number = ntohs(to.sin_port);
    //check if receive successfully

    //cout << bytes << endl;
    if (bytes < 0) {
        return -1;
    }
    //print the data
    //cout<<buffer<<endl;
    //return correct if there were no error
    return bytes;
}
