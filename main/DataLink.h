#pragma once
#include "SString.h"
#include "types.h"


/**
 *
 * DataLink.cpp
 * This software parses a data stream to extract UBX and NMEA frame information from unspecified data packet
 * Part derived from combined implementation thanks to
 * Aurelien & Jean-Luc Derouineau 2022
 *
 */

// state machine definition
enum state_t {
	GET_NMEA_UBX_SYNC,
	GET_NMEA_STREAM,
	GET_UBX_SYNC2,
	GET_UBX_CLASS,
	GET_UBX_ID,
	GET_UBX_LENGTH1,
	GET_UBX_LENGTH2,
	GET_UBX_PAYLOAD,
	GET_UBX_CHKA,
	GET_UBX_CHKB
};


class DataLink {
	public:
		DataLink();
		void process( char *packet, int len, int port );

	private:
		void parse_NMEA_UBX( char c, int port );
		void processNMEA( char * buffer, int len, int port );
		void addChk(const char c);
		void routeSerialData( char *data, int len, int port, bool nmea );
		enum state_t state;
		char framebuffer[128];
		int pos;
		char chkA; // checksum variables
		char chkB;
		char chkBuf;
		bool nmeaFound;
		bool ubxFound;
};
