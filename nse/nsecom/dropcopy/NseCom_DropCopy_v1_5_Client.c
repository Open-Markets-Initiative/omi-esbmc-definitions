// nse/nsecom/dropcopy/NseCom_DropCopy_v1_5_Client.c
/*
 * National Stock Exchange of India Ltd Drop Copy
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
 *   - a Integrity rule
 *   - a Composite rule
 *   - the dispatch that chooses a message by its type
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

/* ---- Packet Header: 6 bytes -------------------------------------------------- */

/* Packet Length and Sequence number, the first six bytes of the direct interface's twenty two byte packet header; its last sixteen open each packet body branch */
typedef struct {
  uint8_t packet_length[2];           /* bytes 0 to 1 */
  uint8_t packet_sequence_number[4];  /* bytes 2 to 5 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->packet_sequence_number[i] = arbitrary(); }
}

/* Packet Header to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->packet_sequence_number[i]; }

  return at;
}

/* Packet Header off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->packet_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->packet_sequence_number[i] == written->packet_sequence_number[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[6];
  uint8_t again[6];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 6);
  assert(decode_packet_header(&got, wire, 0) == 6);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 6);
  assert(encode_packet_header(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 40 bytes ------------------------------------------------ */

/* MESSAGE_HEADER */
typedef struct {
  uint8_t transaction_code[2];  /* bytes 0 to 1 */
  uint8_t log_time[4];          /* bytes 2 to 5 */
  uint8_t alpha_char[2];        /* bytes 6 to 7 */
  uint8_t trader_id[4];         /* bytes 8 to 11 */
  uint8_t error_code[2];        /* bytes 12 to 13 */
  uint8_t header_timestamp[8];  /* bytes 14 to 21 */
  uint8_t time_stamp_1[8];      /* bytes 22 to 29 */
  uint8_t time_stamp_2[8];      /* bytes 30 to 37 */
  uint8_t message_length[2];    /* bytes 38 to 39 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->transaction_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->log_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->alpha_char[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->header_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
}

/* Message Header to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->transaction_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->log_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->alpha_char[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->header_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }

  return at;
}

/* Message Header off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->transaction_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->log_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->alpha_char[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->header_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->transaction_code[i] == written->transaction_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->log_time[i] == written->log_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->alpha_char[i] == written->alpha_char[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->error_code[i] == written->error_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->header_timestamp[i] == written->header_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp_1[i] == written->time_stamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp_2[i] == written->time_stamp_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[40];
  uint8_t again[40];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 40);
  assert(decode_message_header(&got, wire, 0) == 40);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 40);
  assert(encode_message_header(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Signon In Message: 238 bytes -------------------------------------------- */

/* Logs the user on to the drop copy feed */
typedef struct {
  uint8_t user_id[4];              /* bytes 0 to 3 */
  uint8_t reserved_8[8];           /* bytes 4 to 11 */
  uint8_t password[8];             /* bytes 12 to 19 */
  uint8_t second_reserved_8[8];    /* bytes 20 to 27 */
  uint8_t reserved_38[38];         /* bytes 28 to 65 */
  uint8_t broker_id[5];            /* bytes 66 to 70 */
  uint8_t reserved_119[119];       /* bytes 71 to 189 */
  uint8_t reserved_16[16];         /* bytes 190 to 205 */
  uint8_t second_reserved_16[16];  /* bytes 206 to 221 */
  uint8_t third_reserved_16[16];   /* bytes 222 to 237 */
} SignonInMessage;

/* any Signon In Message at all: every byte one the checker chooses */
static void any_signon_in_message(SignonInMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->second_reserved_8[i] = arbitrary(); }
  for (size_t i = 0; i < 38; i++) { record->reserved_38[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 119; i++) { record->reserved_119[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->second_reserved_16[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->third_reserved_16[i] = arbitrary(); }
}

/* Signon In Message to the wire: 238 bytes from at, returning where the next byte goes */
static size_t encode_signon_in_message(const SignonInMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->second_reserved_8[i]; }
  for (size_t i = 0; i < 38; i++) { wire[at++] = record->reserved_38[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 119; i++) { wire[at++] = record->reserved_119[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->second_reserved_16[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->third_reserved_16[i]; }

  return at;
}

/* Signon In Message off the wire: 238 bytes from at, returning where the next byte lies */
static size_t decode_signon_in_message(SignonInMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->second_reserved_8[i] = wire[at++]; }
  for (size_t i = 0; i < 38; i++) { record->reserved_38[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 119; i++) { record->reserved_119[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->second_reserved_16[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->third_reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Signon In Message is what was written, byte for byte */
static void equal_signon_in_message(const SignonInMessage *read, const SignonInMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->second_reserved_8[i] == written->second_reserved_8[i]); }
  for (size_t i = 0; i < 38; i++) { assert(read->reserved_38[i] == written->reserved_38[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 119; i++) { assert(read->reserved_119[i] == written->reserved_119[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->second_reserved_16[i] == written->second_reserved_16[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->third_reserved_16[i] == written->third_reserved_16[i]); }
}

/* Signon In Message: written and read back, then read and written back */
static void check_signon_in_message(void) {
  SignonInMessage sent;
  SignonInMessage got;
  uint8_t wire[238];
  uint8_t again[238];

  any_signon_in_message(&sent);
  assert(encode_signon_in_message(&sent, wire, 0) == 238);
  assert(decode_signon_in_message(&got, wire, 0) == 238);
  equal_signon_in_message(&got, &sent);

  for (size_t i = 0; i < 238; i++) { wire[i] = arbitrary(); }
  assert(decode_signon_in_message(&got, wire, 0) == 238);
  assert(encode_signon_in_message(&got, again, 0) == 238);
  for (size_t i = 0; i < 238; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_signon_in_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
