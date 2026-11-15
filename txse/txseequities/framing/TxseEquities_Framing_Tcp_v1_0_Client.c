// txse/txseequities/framing/TxseEquities_Framing_Tcp_v1_0_Client.c
/*
 * Texas Stock Exchange
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

/* ---- Rake Message Header: 3 bytes -------------------------------------------- */

/* Rake Tcp per-message header carrying the frame length and packet-level dispatch byte */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t packet_type;        /* byte 2 */
} RakeMessageHeader;

/* any Rake Message Header at all: every byte one the checker chooses */
static void any_rake_message_header(RakeMessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  record->packet_type = arbitrary();
}

/* Rake Message Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_rake_message_header(const RakeMessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  wire[at++] = record->packet_type;

  return at;
}

/* Rake Message Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_rake_message_header(RakeMessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  record->packet_type = wire[at++];

  return at;
}

/* what was read of Rake Message Header is what was written, byte for byte */
static void equal_rake_message_header(const RakeMessageHeader *read, const RakeMessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  assert(read->packet_type == written->packet_type);
}

/* Rake Message Header: written and read back, then read and written back */
static void check_rake_message_header(void) {
  RakeMessageHeader sent;
  RakeMessageHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_rake_message_header(&sent);
  assert(encode_rake_message_header(&sent, wire, 0) == 3);
  assert(decode_rake_message_header(&got, wire, 0) == 3);
  equal_rake_message_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_rake_message_header(&got, wire, 0) == 3);
  assert(encode_rake_message_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Request Packet: 32 bytes ------------------------------------------ */

/* Must be the first message a Member sends to the Exchange after establishing a TCP/IP connection */
typedef struct {
  uint8_t session[8];               /* bytes 0 to 7 */
  uint8_t sender_comp[8];           /* bytes 8 to 15 */
  uint8_t token[8];                 /* bytes 16 to 23 */
  uint8_t next_sequence_number[8];  /* bytes 24 to 31 */
} LogonRequestPacket;

/* any Logon Request Packet at all: every byte one the checker chooses */
static void any_logon_request_packet(LogonRequestPacket *record) {
  for (size_t i = 0; i < 8; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sender_comp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = arbitrary(); }
}

/* Logon Request Packet to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_logon_request_packet(const LogonRequestPacket *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sender_comp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_sequence_number[i]; }

  return at;
}

/* Logon Request Packet off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_logon_request_packet(LogonRequestPacket *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sender_comp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Request Packet is what was written, byte for byte */
static void equal_logon_request_packet(const LogonRequestPacket *read, const LogonRequestPacket *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sender_comp[i] == written->sender_comp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->token[i] == written->token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->next_sequence_number[i] == written->next_sequence_number[i]); }
}

/* Logon Request Packet: written and read back, then read and written back */
static void check_logon_request_packet(void) {
  LogonRequestPacket sent;
  LogonRequestPacket got;
  uint8_t wire[32];
  uint8_t again[32];

  any_logon_request_packet(&sent);
  assert(encode_logon_request_packet(&sent, wire, 0) == 32);
  assert(decode_logon_request_packet(&got, wire, 0) == 32);
  equal_logon_request_packet(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_request_packet(&got, wire, 0) == 32);
  assert(encode_logon_request_packet(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_rake_message_header();
  check_logon_request_packet();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
