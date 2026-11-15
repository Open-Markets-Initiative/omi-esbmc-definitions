// cboe/neoequities/gaprequestproxy/NeoEquities_GapRequestProxy_v1_0_14.c
/*
 * Chicago Board Options Exchange Gap Request Proxy
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
 *   - a Reassemble rule
 *   - a run filling what frames it
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

/* ---- Packet Header: 8 bytes -------------------------------------------------- */

typedef struct {
  uint8_t length[2];      /* bytes 0 to 1 */
  uint8_t message_count;  /* byte 2 */
  uint8_t unit;           /* byte 3 */
  uint8_t sequence[4];    /* bytes 4 to 7 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  record->message_count = arbitrary();
  record->unit = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
}

/* Packet Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  wire[at++] = record->message_count;
  wire[at++] = record->unit;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }

  return at;
}

/* Packet Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  record->message_count = wire[at++];
  record->unit = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  assert(read->message_count == written->message_count);
  assert(read->unit == written->unit);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 8);
  assert(decode_packet_header(&got, wire, 0) == 8);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 8);
  assert(encode_packet_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 2 bytes ------------------------------------------------- */

typedef struct {
  uint8_t message_length;  /* byte 0 */
  uint8_t message_type;    /* byte 1 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->message_length = arbitrary();
  record->message_type = arbitrary();
}

/* Message Header to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_length;
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->message_length = wire[at++];
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->message_length == written->message_length);
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[2];
  uint8_t again[2];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 2);
  assert(decode_message_header(&got, wire, 0) == 2);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 2);
  assert(encode_message_header(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Message: 20 bytes ------------------------------------------------- */

/* The first message the Member process sends to the GRP after connection to the GRP is established. Failure to login before sending any other message type will result in the connection being dropped by the GRP. */
typedef struct {
  uint8_t session_sub_id[4];  /* bytes 0 to 3 */
  uint8_t username[4];        /* bytes 4 to 7 */
  uint8_t filler[2];          /* bytes 8 to 9 */
  uint8_t password[10];       /* bytes 10 to 19 */
} LoginMessage;

/* any Login Message at all: every byte one the checker chooses */
static void any_login_message(LoginMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_sub_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->password[i] = arbitrary(); }
}

/* Login Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_login_message(const LoginMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_sub_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->password[i]; }

  return at;
}

/* Login Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_login_message(LoginMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_sub_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->password[i] = wire[at++]; }

  return at;
}

/* what was read of Login Message is what was written, byte for byte */
static void equal_login_message(const LoginMessage *read, const LoginMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_sub_id[i] == written->session_sub_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler[i] == written->filler[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->password[i] == written->password[i]); }
}

/* Login Message: written and read back, then read and written back */
static void check_login_message(void) {
  LoginMessage sent;
  LoginMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_login_message(&sent);
  assert(encode_login_message(&sent, wire, 0) == 20);
  assert(decode_login_message(&got, wire, 0) == 20);
  equal_login_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_login_message(&got, wire, 0) == 20);
  assert(encode_login_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Response Message: 1 byte ------------------------------------------ */

/* Sent by the GRP to the Member process in response to a Login message. The Status field reflects an accepted login or the reason the session was not accepted. If login fails, the connection will be dropped after the Login Response message is sent. */
typedef struct {
  uint8_t login_response_status;  /* byte 0 */
} LoginResponseMessage;

/* any Login Response Message at all: every byte one the checker chooses */
static void any_login_response_message(LoginResponseMessage *record) {
  record->login_response_status = arbitrary();
}

/* Login Response Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_login_response_message(const LoginResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->login_response_status;

  return at;
}

/* Login Response Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_login_response_message(LoginResponseMessage *record, const uint8_t *wire, size_t at) {
  record->login_response_status = wire[at++];

  return at;
}

/* what was read of Login Response Message is what was written, byte for byte */
static void equal_login_response_message(const LoginResponseMessage *read, const LoginResponseMessage *written) {
  assert(read->login_response_status == written->login_response_status);
}

/* Login Response Message: written and read back, then read and written back */
static void check_login_response_message(void) {
  LoginResponseMessage sent;
  LoginResponseMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_login_response_message(&sent);
  assert(encode_login_response_message(&sent, wire, 0) == 1);
  assert(decode_login_response_message(&got, wire, 0) == 1);
  equal_login_response_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_login_response_message(&got, wire, 0) == 1);
  assert(encode_login_response_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Gap Request Message: 7 bytes -------------------------------------------- */

/* Used by a Member's process to request retransmission of a sequenced message (or messages) by one of Cboe Canada's gap servers. */
typedef struct {
  uint8_t gap_unit;         /* byte 0 */
  uint8_t gap_sequence[4];  /* bytes 1 to 4 */
  uint8_t count[2];         /* bytes 5 to 6 */
} GapRequestMessage;

/* any Gap Request Message at all: every byte one the checker chooses */
static void any_gap_request_message(GapRequestMessage *record) {
  record->gap_unit = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->gap_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->count[i] = arbitrary(); }
}

/* Gap Request Message to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_gap_request_message(const GapRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->gap_unit;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->gap_sequence[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->count[i]; }

  return at;
}

/* Gap Request Message off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_gap_request_message(GapRequestMessage *record, const uint8_t *wire, size_t at) {
  record->gap_unit = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->gap_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->count[i] = wire[at++]; }

  return at;
}

/* what was read of Gap Request Message is what was written, byte for byte */
static void equal_gap_request_message(const GapRequestMessage *read, const GapRequestMessage *written) {
  assert(read->gap_unit == written->gap_unit);
  for (size_t i = 0; i < 4; i++) { assert(read->gap_sequence[i] == written->gap_sequence[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->count[i] == written->count[i]); }
}

/* Gap Request Message: written and read back, then read and written back */
static void check_gap_request_message(void) {
  GapRequestMessage sent;
  GapRequestMessage got;
  uint8_t wire[7];
  uint8_t again[7];

  any_gap_request_message(&sent);
  assert(encode_gap_request_message(&sent, wire, 0) == 7);
  assert(decode_gap_request_message(&got, wire, 0) == 7);
  equal_gap_request_message(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_gap_request_message(&got, wire, 0) == 7);
  assert(encode_gap_request_message(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Gap Response Message: 8 bytes ------------------------------------------- */

/* Sent by the GRP in response to a Gap Request message. The Unit and Sequence fields will match the values supplied in the Gap Request message. A Gap Response message, with a Status of Accepted or reason for failure, will be sent for each Gap Request message received by the GRP. */
typedef struct {
  uint8_t gap_unit;             /* byte 0 */
  uint8_t gap_sequence[4];      /* bytes 1 to 4 */
  uint8_t count[2];             /* bytes 5 to 6 */
  uint8_t gap_response_status;  /* byte 7 */
} GapResponseMessage;

/* any Gap Response Message at all: every byte one the checker chooses */
static void any_gap_response_message(GapResponseMessage *record) {
  record->gap_unit = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->gap_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->count[i] = arbitrary(); }
  record->gap_response_status = arbitrary();
}

/* Gap Response Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_gap_response_message(const GapResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->gap_unit;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->gap_sequence[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->count[i]; }
  wire[at++] = record->gap_response_status;

  return at;
}

/* Gap Response Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_gap_response_message(GapResponseMessage *record, const uint8_t *wire, size_t at) {
  record->gap_unit = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->gap_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->count[i] = wire[at++]; }
  record->gap_response_status = wire[at++];

  return at;
}

/* what was read of Gap Response Message is what was written, byte for byte */
static void equal_gap_response_message(const GapResponseMessage *read, const GapResponseMessage *written) {
  assert(read->gap_unit == written->gap_unit);
  for (size_t i = 0; i < 4; i++) { assert(read->gap_sequence[i] == written->gap_sequence[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->count[i] == written->count[i]); }
  assert(read->gap_response_status == written->gap_response_status);
}

/* Gap Response Message: written and read back, then read and written back */
static void check_gap_response_message(void) {
  GapResponseMessage sent;
  GapResponseMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_gap_response_message(&sent);
  assert(encode_gap_response_message(&sent, wire, 0) == 8);
  assert(decode_gap_response_message(&got, wire, 0) == 8);
  equal_gap_response_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_gap_response_message(&got, wire, 0) == 8);
  assert(encode_gap_response_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_login_message();
  check_login_response_message();
  check_gap_request_message();
  check_gap_response_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
