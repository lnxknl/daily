#include <stdint.h>
#include <stdbool.h>
#include <string.h>


#define START_BYTE 0xAA
#define END_BYTE 0x55

#define MAX_DATA_LENGTH 16

typedef enum {
    PACKET_TYPE_COMMAND = 0x01,
    PACKET_TYPE_RESPONSE = 0x02,
    PACKET_TYPE_DATA = 0x03,
    PACKET_TYPE_ACK = 0x04,
    PACKET_TYPE_ERROR = 0x05
} PacketType;

typedef struct {
    uint8_t start;
    uint8_t type;
    uint16_t length;
    uint8_t data[MAX_DATA_LENGTH];
    uint16_t crc;
    uint8_t end;
} Packet;

// parse packet from buffer
void parse_packet(uint8_t *buffer, uint16_t length, Packet *packet){
    if (length < 5) {
	return;
    }
    packet->start = buffer[0];
    packet->type = buffer[1];
//    packet->length = buffer[2] << 8 | buffer[3];
    // convert to little endian
    packet->length = buffer[3] << 8 | buffer[2];

    printf("length: %d\n", packet->length);
    if (length < packet->length + 5) {
	return;
    }
    memcpy(packet->data, buffer + 4, packet->length);
    // print packet data
    // print length
    printf("length: %d\n", packet->length);
    for (int i = 0; i < packet->length; i++) {
	printf("%c", packet->data[i]);
    }
    printf("\n");
    packet->crc = buffer[packet->length + 4] << 8 | buffer[packet->length + 5];
    packet->end = buffer[packet->length + 6];
}

// calculate crc
uint16_t calculate_crc(uint8_t *data, uint16_t length){
    uint16_t crc = 0;
    for (uint16_t i = 0; i < length; i++) {
	crc += data[i];
    }
    return crc;
}

// write a instance of Packet to buffer
int main(){
	Packet packet;
	packet.start = START_BYTE;
	packet.type = PACKET_TYPE_COMMAND;
//	packet.length = 0;
	packet.end = END_BYTE;
	// simulate sending packet
//	uint8_t buffer[10];
	// set buffer to "hello world"
	char *str = "hello world";
	memcpy(packet.data, str, strlen(str));
	packet.length = strlen(str);
	// calculate crc
	packet.crc = calculate_crc(packet.data, packet.length);

	// parse packet
	uint8_t buffer[32];


	// print pakcet size
	printf("packet size: %d\n", sizeof(Packet));

	memcpy(buffer, &packet, sizeof(Packet));
	Packet packet2;
	parse_packet(buffer, sizeof(Packet), &packet2);
	// check if packet2 is the same as packet
	// send packet
	return 0;
}
