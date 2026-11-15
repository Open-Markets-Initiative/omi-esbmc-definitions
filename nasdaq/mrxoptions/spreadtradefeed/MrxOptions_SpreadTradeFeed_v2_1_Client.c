// nasdaq/mrxoptions/spreadtradefeed/MrxOptions_SpreadTradeFeed_v2_1_Client.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) MRX Options Spread Trade Feed
 *
 * Generated from the binary model. Every record is a run of fields, and esbmc checks two
 * claims of each, for every value its bytes can take rather than for chosen ones: that any
 * record written to the wire and read back is that record, and that any bytes read off the
 * wire and written back are those bytes. Each takes exactly the record's width, and no
 * write or read leaves the buffer it is made on.
 *
 * A field is the bytes it occupies. Nothing is read as an integer, so nothing is read in a
 * byte order, and no rule stated here depends on a value.
 *
 * Check the whole file:   esbmc <file>
 * Check one record:       esbmc <file> --function check_<record>
 *
 * Built with -DCONCRETE it is an ordinary program any C compiler runs: the bytes the
 * checker would choose are drawn from four patterns instead, so the definition can be
 * tried without the checker. That run is a test, and the checker's is the claim.
 *
 * What this definition does not state, and the model does:
 *   - a run filling what frames it
 *   - a length prefix framing what follows
 *
 * License: MIT No Attribution
 */

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

/* ---- Any byte ---------------------------------------------------------------- */

#ifdef CONCRETE

/* which pattern the bytes are drawn from, and how many have been drawn */
static unsigned pattern;
static size_t drawn;

/* a byte of the pattern: zero, a space, every bit set, or one more than the last */
static uint8_t arbitrary(void) {
  drawn++;

  switch (pattern) {
    case 0: return 0;
    case 1: return 32;
    case 2: return 255;
    default: return (uint8_t)(drawn % 256);
  }
}

#else

/* declared and never defined: a value the checker chooses */
unsigned char __VERIFIER_nondet_uchar(void);

/* a byte nobody chose, so what holds of it holds of all of them */
static uint8_t arbitrary(void) {
  return __VERIFIER_nondet_uchar();
}

#endif

/* ---- Client Packet Header: 3 bytes ------------------------------------------- */

/* Packet header of a packet sent by the client */
typedef struct {
  uint8_t packet_length[2];    /* bytes 0 to 1 */
  uint8_t client_packet_type;  /* byte 2 */
} ClientPacketHeader;

/* any Client Packet Header at all: every byte one the checker chooses */
static void any_client_packet_header(ClientPacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  record->client_packet_type = arbitrary();
}

/* Client Packet Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_client_packet_header(const ClientPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  wire[at++] = record->client_packet_type;

  return at;
}

/* Client Packet Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_client_packet_header(ClientPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  record->client_packet_type = wire[at++];

  return at;
}

/* what was read of Client Packet Header is what was written, byte for byte */
static void equal_client_packet_header(const ClientPacketHeader *read, const ClientPacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  assert(read->client_packet_type == written->client_packet_type);
}

/* Client Packet Header: written and read back, then read and written back */
static void check_client_packet_header(void) {
  ClientPacketHeader sent;
  ClientPacketHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_client_packet_header(&sent);
  assert(encode_client_packet_header(&sent, wire, 0) == 3);
  assert(decode_client_packet_header(&got, wire, 0) == 3);
  equal_client_packet_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_client_packet_header(&got, wire, 0) == 3);
  assert(encode_client_packet_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request Packet: 46 bytes ------------------------------------------ */

/* The SoupBinTCP client must send a Login Request Packet immediately upon establishing a new TCP/IP socket connection to the server */
typedef struct {
  uint8_t username[6];                    /* bytes 0 to 5 */
  uint8_t password[10];                   /* bytes 6 to 15 */
  uint8_t requested_session[10];          /* bytes 16 to 25 */
  uint8_t requested_sequence_number[20];  /* bytes 26 to 45 */
} LoginRequestPacket;

/* any Login Request Packet at all: every byte one the checker chooses */
static void any_login_request_packet(LoginRequestPacket *record) {
  for (size_t i = 0; i < 6; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->requested_session[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->requested_sequence_number[i] = arbitrary(); }
}

/* Login Request Packet to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_login_request_packet(const LoginRequestPacket *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->requested_session[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->requested_sequence_number[i]; }

  return at;
}

/* Login Request Packet off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_login_request_packet(LoginRequestPacket *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->requested_session[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->requested_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request Packet is what was written, byte for byte */
static void equal_login_request_packet(const LoginRequestPacket *read, const LoginRequestPacket *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->requested_session[i] == written->requested_session[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->requested_sequence_number[i] == written->requested_sequence_number[i]); }
}

/* Login Request Packet: written and read back, then read and written back */
static void check_login_request_packet(void) {
  LoginRequestPacket sent;
  LoginRequestPacket got;
  uint8_t wire[46];
  uint8_t again[46];

  any_login_request_packet(&sent);
  assert(encode_login_request_packet(&sent, wire, 0) == 46);
  assert(decode_login_request_packet(&got, wire, 0) == 46);
  equal_login_request_packet(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request_packet(&got, wire, 0) == 46);
  assert(encode_login_request_packet(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_client_packet_header();
  check_login_request_packet();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
