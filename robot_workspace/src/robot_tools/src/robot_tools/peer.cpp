// Declarations
#include "robot_tools/peer.h"

// ROS
#include "ros/ros.h"			// ROS_FATAL

// System
#include <cstring>				// memset, strcmp

// Constructor
Peer::Peer(char* ip, int port) {
	// Create socket
	sock = socket(AF_INET , SOCK_DGRAM, IPPROTO_UDP);
		
	// Check whether socket is valid
	if (sock == -1) {
		ROS_FATAL("Could not create socket!");
	}

	// Set robot IP and general address length
	robotIP = ip;
	addrLength = sizeof(struct sockaddr_in);

	// Set sender address information
	sendAddr.sin_addr.s_addr = inet_addr(robotIP);
	sendAddr.sin_family = AF_INET;
	sendAddr.sin_port = htons(port);

	// Define communication over port <port>
	sockaddr_in selfAddr;
	selfAddr.sin_addr.s_addr = INADDR_ANY;
	selfAddr.sin_family = AF_INET;
	selfAddr.sin_port = htons(port);

	// Bind socket if possible, else throw error
	bind(sock, (const sockaddr*)&selfAddr, addrLength);

}

// Receives messages
char* Peer::receiveMessage() {
	// Flush output and clear buffer
	fflush(stdout);
	memset(buffer, '\0', BUFFER_SIZE);

	// Receive message and store sender address
	int nBytes = recvfrom(sock, buffer, BUFFER_SIZE, 0, (sockaddr*) &recvAddr, &addrLength);

	// Get IP addres of sender
	char ipAddress[addrLength];
	inet_ntop(AF_INET, &recvAddr.sin_addr.s_addr, ipAddress, addrLength);

	// If the message came from the desired IP address
	if (strcmp(robotIP, ipAddress) == 0) {
		// Return message
		return buffer;
	}
	// If message came from an unknown sender
	else {
		// Return INVALID_MESSAGE
		return INVALID_MESSAGE;
	}
}

// Sends messages
void Peer::sendMessage(char* msg) {
	// If sendto is unsuccesful
	if (sendto(sock, msg, BUFFER_SIZE, 0, (sockaddr*) &sendAddr, addrLength) == -1 ) {
		// And the error is not ECONNREFUSED (no one is listening)
		if (errno != ECONNREFUSED) {
			ROS_FATAL("Could not send message!");
		}
	}
}