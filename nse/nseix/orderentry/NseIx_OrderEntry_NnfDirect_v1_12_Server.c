// nse/nseix/orderentry/NseIx_OrderEntry_NnfDirect_v1_12_Server.c
/*
 * National Stock Exchange of India Ltd Order Entry
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
 *   - the dispatch that chooses a message by its type
 *   - a Composite rule
 *   - a field read in bits
 *   - a length prefix framing what follows
 *   - a run of a stated number of entries
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

/* ---- Error Response Body: 142 bytes ------------------------------------------ */

/* Error Response Body */
typedef struct {
  uint8_t key[14];             /* bytes 0 to 13 */
  uint8_t error_message[128];  /* bytes 14 to 141 */
} ErrorResponseBody;

/* any Error Response Body at all: every byte one the checker chooses */
static void any_error_response_body(ErrorResponseBody *record) {
  for (size_t i = 0; i < 14; i++) { record->key[i] = arbitrary(); }
  for (size_t i = 0; i < 128; i++) { record->error_message[i] = arbitrary(); }
}

/* Error Response Body to the wire: 142 bytes from at, returning where the next byte goes */
static size_t encode_error_response_body(const ErrorResponseBody *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->key[i]; }
  for (size_t i = 0; i < 128; i++) { wire[at++] = record->error_message[i]; }

  return at;
}

/* Error Response Body off the wire: 142 bytes from at, returning where the next byte lies */
static size_t decode_error_response_body(ErrorResponseBody *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->key[i] = wire[at++]; }
  for (size_t i = 0; i < 128; i++) { record->error_message[i] = wire[at++]; }

  return at;
}

/* what was read of Error Response Body is what was written, byte for byte */
static void equal_error_response_body(const ErrorResponseBody *read, const ErrorResponseBody *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->key[i] == written->key[i]); }
  for (size_t i = 0; i < 128; i++) { assert(read->error_message[i] == written->error_message[i]); }
}

/* Error Response Body: written and read back, then read and written back */
static void check_error_response_body(void) {
  ErrorResponseBody sent;
  ErrorResponseBody got;
  uint8_t wire[142];
  uint8_t again[142];

  any_error_response_body(&sent);
  assert(encode_error_response_body(&sent, wire, 0) == 142);
  assert(decode_error_response_body(&got, wire, 0) == 142);
  equal_error_response_body(&got, &sent);

  for (size_t i = 0; i < 142; i++) { wire[i] = arbitrary(); }
  assert(decode_error_response_body(&got, wire, 0) == 142);
  assert(encode_error_response_body(&got, again, 0) == 142);
  for (size_t i = 0; i < 142; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sign Off Request Out Message: 150 bytes --------------------------------- */

/* Details of the user's last log off, sent when the user logs on again */
typedef struct {
  uint8_t user_id[4];         /* bytes 0 to 3 */
  uint8_t reserved_145[145];  /* bytes 4 to 148 */
  uint8_t reserved_1;         /* byte 149 */
} SignOffRequestOutMessage;

/* any Sign Off Request Out Message at all: every byte one the checker chooses */
static void any_sign_off_request_out_message(SignOffRequestOutMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 145; i++) { record->reserved_145[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Sign Off Request Out Message to the wire: 150 bytes from at, returning where the next byte goes */
static size_t encode_sign_off_request_out_message(const SignOffRequestOutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 145; i++) { wire[at++] = record->reserved_145[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Sign Off Request Out Message off the wire: 150 bytes from at, returning where the next byte lies */
static size_t decode_sign_off_request_out_message(SignOffRequestOutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 145; i++) { record->reserved_145[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Sign Off Request Out Message is what was written, byte for byte */
static void equal_sign_off_request_out_message(const SignOffRequestOutMessage *read, const SignOffRequestOutMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 145; i++) { assert(read->reserved_145[i] == written->reserved_145[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Sign Off Request Out Message: written and read back, then read and written back */
static void check_sign_off_request_out_message(void) {
  SignOffRequestOutMessage sent;
  SignOffRequestOutMessage got;
  uint8_t wire[150];
  uint8_t again[150];

  any_sign_off_request_out_message(&sent);
  assert(encode_sign_off_request_out_message(&sent, wire, 0) == 150);
  assert(decode_sign_off_request_out_message(&got, wire, 0) == 150);
  equal_sign_off_request_out_message(&got, &sent);

  for (size_t i = 0; i < 150; i++) { wire[i] = arbitrary(); }
  assert(decode_sign_off_request_out_message(&got, wire, 0) == 150);
  assert(encode_sign_off_request_out_message(&got, again, 0) == 150);
  for (size_t i = 0; i < 150; i++) { assert(again[i] == wire[i]); }
}

/* ---- St Market Status: 8 bytes ----------------------------------------------- */

/* ST_MARKET_STATUS */
typedef struct {
  uint8_t normal[2];   /* bytes 0 to 1 */
  uint8_t oddlot[2];   /* bytes 2 to 3 */
  uint8_t spot[2];     /* bytes 4 to 5 */
  uint8_t auction[2];  /* bytes 6 to 7 */
} StMarketStatus;

/* any St Market Status at all: every byte one the checker chooses */
static void any_st_market_status(StMarketStatus *record) {
  for (size_t i = 0; i < 2; i++) { record->normal[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->oddlot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->spot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->auction[i] = arbitrary(); }
}

/* St Market Status to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_st_market_status(const StMarketStatus *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->normal[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->oddlot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->spot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->auction[i]; }

  return at;
}

/* St Market Status off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_st_market_status(StMarketStatus *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->normal[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->oddlot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->spot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->auction[i] = wire[at++]; }

  return at;
}

/* what was read of St Market Status is what was written, byte for byte */
static void equal_st_market_status(const StMarketStatus *read, const StMarketStatus *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->normal[i] == written->normal[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->oddlot[i] == written->oddlot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->spot[i] == written->spot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->auction[i] == written->auction[i]); }
}

/* St Market Status: written and read back, then read and written back */
static void check_st_market_status(void) {
  StMarketStatus sent;
  StMarketStatus got;
  uint8_t wire[8];
  uint8_t again[8];

  any_st_market_status(&sent);
  assert(encode_st_market_status(&sent, wire, 0) == 8);
  assert(decode_st_market_status(&got, wire, 0) == 8);
  equal_st_market_status(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_st_market_status(&got, wire, 0) == 8);
  assert(encode_st_market_status(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- St Ex Market Status: 8 bytes -------------------------------------------- */

/* ST_EX_MARKET_STATUS */
typedef struct {
  uint8_t normal[2];   /* bytes 0 to 1 */
  uint8_t oddlot[2];   /* bytes 2 to 3 */
  uint8_t spot[2];     /* bytes 4 to 5 */
  uint8_t auction[2];  /* bytes 6 to 7 */
} StExMarketStatus;

/* any St Ex Market Status at all: every byte one the checker chooses */
static void any_st_ex_market_status(StExMarketStatus *record) {
  for (size_t i = 0; i < 2; i++) { record->normal[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->oddlot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->spot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->auction[i] = arbitrary(); }
}

/* St Ex Market Status to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_st_ex_market_status(const StExMarketStatus *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->normal[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->oddlot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->spot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->auction[i]; }

  return at;
}

/* St Ex Market Status off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_st_ex_market_status(StExMarketStatus *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->normal[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->oddlot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->spot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->auction[i] = wire[at++]; }

  return at;
}

/* what was read of St Ex Market Status is what was written, byte for byte */
static void equal_st_ex_market_status(const StExMarketStatus *read, const StExMarketStatus *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->normal[i] == written->normal[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->oddlot[i] == written->oddlot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->spot[i] == written->spot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->auction[i] == written->auction[i]); }
}

/* St Ex Market Status: written and read back, then read and written back */
static void check_st_ex_market_status(void) {
  StExMarketStatus sent;
  StExMarketStatus got;
  uint8_t wire[8];
  uint8_t again[8];

  any_st_ex_market_status(&sent);
  assert(encode_st_ex_market_status(&sent, wire, 0) == 8);
  assert(decode_st_ex_market_status(&got, wire, 0) == 8);
  equal_st_ex_market_status(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_st_ex_market_status(&got, wire, 0) == 8);
  assert(encode_st_ex_market_status(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- St Pl Market Status: 8 bytes -------------------------------------------- */

/* ST_PL_MARKET_STATUS */
typedef struct {
  uint8_t normal[2];   /* bytes 0 to 1 */
  uint8_t oddlot[2];   /* bytes 2 to 3 */
  uint8_t spot[2];     /* bytes 4 to 5 */
  uint8_t auction[2];  /* bytes 6 to 7 */
} StPlMarketStatus;

/* any St Pl Market Status at all: every byte one the checker chooses */
static void any_st_pl_market_status(StPlMarketStatus *record) {
  for (size_t i = 0; i < 2; i++) { record->normal[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->oddlot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->spot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->auction[i] = arbitrary(); }
}

/* St Pl Market Status to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_st_pl_market_status(const StPlMarketStatus *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->normal[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->oddlot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->spot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->auction[i]; }

  return at;
}

/* St Pl Market Status off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_st_pl_market_status(StPlMarketStatus *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->normal[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->oddlot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->spot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->auction[i] = wire[at++]; }

  return at;
}

/* what was read of St Pl Market Status is what was written, byte for byte */
static void equal_st_pl_market_status(const StPlMarketStatus *read, const StPlMarketStatus *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->normal[i] == written->normal[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->oddlot[i] == written->oddlot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->spot[i] == written->spot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->auction[i] == written->auction[i]); }
}

/* St Pl Market Status: written and read back, then read and written back */
static void check_st_pl_market_status(void) {
  StPlMarketStatus sent;
  StPlMarketStatus got;
  uint8_t wire[8];
  uint8_t again[8];

  any_st_pl_market_status(&sent);
  assert(encode_st_pl_market_status(&sent, wire, 0) == 8);
  assert(decode_st_pl_market_status(&got, wire, 0) == 8);
  equal_st_pl_market_status(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_st_pl_market_status(&got, wire, 0) == 8);
  assert(encode_st_pl_market_status(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Update Local Database Header Message: 2 bytes --------------------------- */

/* Opens the local database download */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
} UpdateLocalDatabaseHeaderMessage;

/* any Update Local Database Header Message at all: every byte one the checker chooses */
static void any_update_local_database_header_message(UpdateLocalDatabaseHeaderMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Update Local Database Header Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_update_local_database_header_message(const UpdateLocalDatabaseHeaderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Update Local Database Header Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_update_local_database_header_message(UpdateLocalDatabaseHeaderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Update Local Database Header Message is what was written, byte for byte */
static void equal_update_local_database_header_message(const UpdateLocalDatabaseHeaderMessage *read, const UpdateLocalDatabaseHeaderMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Update Local Database Header Message: written and read back, then read and written back */
static void check_update_local_database_header_message(void) {
  UpdateLocalDatabaseHeaderMessage sent;
  UpdateLocalDatabaseHeaderMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_update_local_database_header_message(&sent);
  assert(encode_update_local_database_header_message(&sent, wire, 0) == 2);
  assert(decode_update_local_database_header_message(&got, wire, 0) == 2);
  equal_update_local_database_header_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_update_local_database_header_message(&got, wire, 0) == 2);
  assert(encode_update_local_database_header_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Update Local Database Trailer Message: 2 bytes -------------------------- */

/* Closes the local database download */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
} UpdateLocalDatabaseTrailerMessage;

/* any Update Local Database Trailer Message at all: every byte one the checker chooses */
static void any_update_local_database_trailer_message(UpdateLocalDatabaseTrailerMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Update Local Database Trailer Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_update_local_database_trailer_message(const UpdateLocalDatabaseTrailerMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Update Local Database Trailer Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_update_local_database_trailer_message(UpdateLocalDatabaseTrailerMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Update Local Database Trailer Message is what was written, byte for byte */
static void equal_update_local_database_trailer_message(const UpdateLocalDatabaseTrailerMessage *read, const UpdateLocalDatabaseTrailerMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Update Local Database Trailer Message: written and read back, then read and written back */
static void check_update_local_database_trailer_message(void) {
  UpdateLocalDatabaseTrailerMessage sent;
  UpdateLocalDatabaseTrailerMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_update_local_database_trailer_message(&sent);
  assert(encode_update_local_database_trailer_message(&sent, wire, 0) == 2);
  assert(decode_update_local_database_trailer_message(&got, wire, 0) == 2);
  equal_update_local_database_trailer_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_update_local_database_trailer_message(&got, wire, 0) == 2);
  assert(encode_update_local_database_trailer_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Inner Header: 40 bytes -------------------------------------------------- */

/* INNER_MESSAGE_HEADER */
typedef struct {
  uint8_t inner_trader_id[4];         /* bytes 0 to 3 */
  uint8_t inner_log_time[4];          /* bytes 4 to 7 */
  uint8_t inner_alpha_char[2];        /* bytes 8 to 9 */
  uint8_t inner_transaction_code[2];  /* bytes 10 to 11 */
  uint8_t inner_error_code[2];        /* bytes 12 to 13 */
  uint8_t inner_timestamp[8];         /* bytes 14 to 21 */
  uint8_t inner_time_stamp_1[8];      /* bytes 22 to 29 */
  uint8_t inner_time_stamp_2[8];      /* bytes 30 to 37 */
  uint8_t inner_message_length[2];    /* bytes 38 to 39 */
} InnerHeader;

/* any Inner Header at all: every byte one the checker chooses */
static void any_inner_header(InnerHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->inner_trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->inner_log_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->inner_alpha_char[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->inner_transaction_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->inner_error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->inner_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->inner_time_stamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->inner_time_stamp_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->inner_message_length[i] = arbitrary(); }
}

/* Inner Header to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_inner_header(const InnerHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->inner_trader_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->inner_log_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->inner_alpha_char[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->inner_transaction_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->inner_error_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->inner_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->inner_time_stamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->inner_time_stamp_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->inner_message_length[i]; }

  return at;
}

/* Inner Header off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_inner_header(InnerHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->inner_trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->inner_log_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->inner_alpha_char[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->inner_transaction_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->inner_error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->inner_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->inner_time_stamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->inner_time_stamp_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->inner_message_length[i] = wire[at++]; }

  return at;
}

/* what was read of Inner Header is what was written, byte for byte */
static void equal_inner_header(const InnerHeader *read, const InnerHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->inner_trader_id[i] == written->inner_trader_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->inner_log_time[i] == written->inner_log_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->inner_alpha_char[i] == written->inner_alpha_char[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->inner_transaction_code[i] == written->inner_transaction_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->inner_error_code[i] == written->inner_error_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->inner_timestamp[i] == written->inner_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->inner_time_stamp_1[i] == written->inner_time_stamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->inner_time_stamp_2[i] == written->inner_time_stamp_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->inner_message_length[i] == written->inner_message_length[i]); }
}

/* Inner Header: written and read back, then read and written back */
static void check_inner_header(void) {
  InnerHeader sent;
  InnerHeader got;
  uint8_t wire[40];
  uint8_t again[40];

  any_inner_header(&sent);
  assert(encode_inner_header(&sent, wire, 0) == 40);
  assert(decode_inner_header(&got, wire, 0) == 40);
  equal_inner_header(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_inner_header(&got, wire, 0) == 40);
  assert(encode_inner_header(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Contract Desc: 28 bytes ------------------------------------------------- */

/* CONTRACT_DESC */
typedef struct {
  uint8_t instrument_name[6];  /* bytes 0 to 5 */
  uint8_t symbol[10];          /* bytes 6 to 15 */
  uint8_t expiry_date[4];      /* bytes 16 to 19 */
  uint8_t strike_price[4];     /* bytes 20 to 23 */
  uint8_t option_type[2];      /* bytes 24 to 25 */
  uint8_t ca_level[2];         /* bytes 26 to 27 */
} ContractDesc;

/* any Contract Desc at all: every byte one the checker chooses */
static void any_contract_desc(ContractDesc *record) {
  for (size_t i = 0; i < 6; i++) { record->instrument_name[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->option_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ca_level[i] = arbitrary(); }
}

/* Contract Desc to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_contract_desc(const ContractDesc *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->instrument_name[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expiry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->option_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ca_level[i]; }

  return at;
}

/* Contract Desc off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_contract_desc(ContractDesc *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->instrument_name[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->option_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ca_level[i] = wire[at++]; }

  return at;
}

/* what was read of Contract Desc is what was written, byte for byte */
static void equal_contract_desc(const ContractDesc *read, const ContractDesc *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->instrument_name[i] == written->instrument_name[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expiry_date[i] == written->expiry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->option_type[i] == written->option_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ca_level[i] == written->ca_level[i]); }
}

/* Contract Desc: written and read back, then read and written back */
static void check_contract_desc(void) {
  ContractDesc sent;
  ContractDesc got;
  uint8_t wire[28];
  uint8_t again[28];

  any_contract_desc(&sent);
  assert(encode_contract_desc(&sent, wire, 0) == 28);
  assert(decode_contract_desc(&got, wire, 0) == 28);
  equal_contract_desc(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_contract_desc(&got, wire, 0) == 28);
  assert(encode_contract_desc(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Inquiry Body: 194 bytes ------------------------------------------- */

/* Trade Inquiry Body */
typedef struct {
  uint8_t token_no[4];              /* bytes 0 to 3 */
  ContractDesc contract_desc;       /* bytes 4 to 31 */
  uint8_t fill_number[4];           /* bytes 32 to 35 */
  uint8_t fill_quantity[4];         /* bytes 36 to 39 */
  uint8_t fill_price[4];            /* bytes 40 to 43 */
  uint8_t mkt_type;                 /* byte 44 */
  uint8_t buy_open_close;           /* byte 45 */
  uint8_t new_volume[4];            /* bytes 46 to 49 */
  uint8_t buy_broker_id[5];         /* bytes 50 to 54 */
  uint8_t sell_broker_id[5];        /* bytes 55 to 59 */
  uint8_t trader_id[4];             /* bytes 60 to 63 */
  uint8_t requested_by;             /* byte 64 */
  uint8_t sell_open_close;          /* byte 65 */
  uint8_t buy_account_number[10];   /* bytes 66 to 75 */
  uint8_t sell_account_number[10];  /* bytes 76 to 85 */
  uint8_t buy_participant[12];      /* bytes 86 to 97 */
  uint8_t sell_participant[12];     /* bytes 98 to 109 */
  uint8_t reserved_2[2];            /* bytes 110 to 111 */
  uint8_t buy_giveup_flag;          /* byte 112 */
  uint8_t sell_giveup_flag;         /* byte 113 */
  uint8_t reserved_80[80];          /* bytes 114 to 193 */
} TradeInquiryBody;

/* any Trade Inquiry Body at all: every byte one the checker chooses */
static void any_trade_inquiry_body(TradeInquiryBody *record) {
  for (size_t i = 0; i < 4; i++) { record->token_no[i] = arbitrary(); }
  any_contract_desc(&record->contract_desc);
  for (size_t i = 0; i < 4; i++) { record->fill_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->fill_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->fill_price[i] = arbitrary(); }
  record->mkt_type = arbitrary();
  record->buy_open_close = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->new_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->buy_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->sell_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  record->requested_by = arbitrary();
  record->sell_open_close = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->buy_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->sell_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->buy_participant[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->sell_participant[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->buy_giveup_flag = arbitrary();
  record->sell_giveup_flag = arbitrary();
  for (size_t i = 0; i < 80; i++) { record->reserved_80[i] = arbitrary(); }
}

/* Trade Inquiry Body to the wire: 194 bytes from at, returning where the next byte goes */
static size_t encode_trade_inquiry_body(const TradeInquiryBody *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->token_no[i]; }
  at = encode_contract_desc(&record->contract_desc, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fill_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fill_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fill_price[i]; }
  wire[at++] = record->mkt_type;
  wire[at++] = record->buy_open_close;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_volume[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->buy_broker_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sell_broker_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  wire[at++] = record->requested_by;
  wire[at++] = record->sell_open_close;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->buy_account_number[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sell_account_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->buy_participant[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->sell_participant[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->buy_giveup_flag;
  wire[at++] = record->sell_giveup_flag;
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->reserved_80[i]; }

  return at;
}

/* Trade Inquiry Body off the wire: 194 bytes from at, returning where the next byte lies */
static size_t decode_trade_inquiry_body(TradeInquiryBody *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->token_no[i] = wire[at++]; }
  at = decode_contract_desc(&record->contract_desc, wire, at);
  for (size_t i = 0; i < 4; i++) { record->fill_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->fill_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->fill_price[i] = wire[at++]; }
  record->mkt_type = wire[at++];
  record->buy_open_close = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->new_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->buy_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->sell_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  record->requested_by = wire[at++];
  record->sell_open_close = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->buy_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->sell_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->buy_participant[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->sell_participant[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->buy_giveup_flag = wire[at++];
  record->sell_giveup_flag = wire[at++];
  for (size_t i = 0; i < 80; i++) { record->reserved_80[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Inquiry Body is what was written, byte for byte */
static void equal_trade_inquiry_body(const TradeInquiryBody *read, const TradeInquiryBody *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->token_no[i] == written->token_no[i]); }
  equal_contract_desc(&read->contract_desc, &written->contract_desc);
  for (size_t i = 0; i < 4; i++) { assert(read->fill_number[i] == written->fill_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->fill_quantity[i] == written->fill_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->fill_price[i] == written->fill_price[i]); }
  assert(read->mkt_type == written->mkt_type);
  assert(read->buy_open_close == written->buy_open_close);
  for (size_t i = 0; i < 4; i++) { assert(read->new_volume[i] == written->new_volume[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->buy_broker_id[i] == written->buy_broker_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->sell_broker_id[i] == written->sell_broker_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  assert(read->requested_by == written->requested_by);
  assert(read->sell_open_close == written->sell_open_close);
  for (size_t i = 0; i < 10; i++) { assert(read->buy_account_number[i] == written->buy_account_number[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->sell_account_number[i] == written->sell_account_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->buy_participant[i] == written->buy_participant[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->sell_participant[i] == written->sell_participant[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->buy_giveup_flag == written->buy_giveup_flag);
  assert(read->sell_giveup_flag == written->sell_giveup_flag);
  for (size_t i = 0; i < 80; i++) { assert(read->reserved_80[i] == written->reserved_80[i]); }
}

/* Trade Inquiry Body: written and read back, then read and written back */
static void check_trade_inquiry_body(void) {
  TradeInquiryBody sent;
  TradeInquiryBody got;
  uint8_t wire[194];
  uint8_t again[194];

  any_trade_inquiry_body(&sent);
  assert(encode_trade_inquiry_body(&sent, wire, 0) == 194);
  assert(decode_trade_inquiry_body(&got, wire, 0) == 194);
  equal_trade_inquiry_body(&got, &sent);

  for (size_t i = 0; i < 194; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_inquiry_body(&got, wire, 0) == 194);
  assert(encode_trade_inquiry_body(&got, again, 0) == 194);
  for (size_t i = 0; i < 194; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Inquiry Response Message: 194 bytes ------------------------------- */

/* Trade cancellation response, trade error, trade modification rejection and the negotiated large trade rejections and cancellation confirmation, carried in the shared trade structure. Transaction Code in the header names the response */
typedef struct {
  TradeInquiryBody trade_inquiry_body;  /* bytes 0 to 193 */
} TradeInquiryResponseMessage;

/* any Trade Inquiry Response Message at all: every byte one the checker chooses */
static void any_trade_inquiry_response_message(TradeInquiryResponseMessage *record) {
  any_trade_inquiry_body(&record->trade_inquiry_body);
}

/* Trade Inquiry Response Message to the wire: 194 bytes from at, returning where the next byte goes */
static size_t encode_trade_inquiry_response_message(const TradeInquiryResponseMessage *record, uint8_t *wire, size_t at) {
  at = encode_trade_inquiry_body(&record->trade_inquiry_body, wire, at);

  return at;
}

/* Trade Inquiry Response Message off the wire: 194 bytes from at, returning where the next byte lies */
static size_t decode_trade_inquiry_response_message(TradeInquiryResponseMessage *record, const uint8_t *wire, size_t at) {
  at = decode_trade_inquiry_body(&record->trade_inquiry_body, wire, at);

  return at;
}

/* what was read of Trade Inquiry Response Message is what was written, byte for byte */
static void equal_trade_inquiry_response_message(const TradeInquiryResponseMessage *read, const TradeInquiryResponseMessage *written) {
  equal_trade_inquiry_body(&read->trade_inquiry_body, &written->trade_inquiry_body);
}

/* Trade Inquiry Response Message: written and read back, then read and written back */
static void check_trade_inquiry_response_message(void) {
  TradeInquiryResponseMessage sent;
  TradeInquiryResponseMessage got;
  uint8_t wire[194];
  uint8_t again[194];

  any_trade_inquiry_response_message(&sent);
  assert(encode_trade_inquiry_response_message(&sent, wire, 0) == 194);
  assert(decode_trade_inquiry_response_message(&got, wire, 0) == 194);
  equal_trade_inquiry_response_message(&got, &sent);

  for (size_t i = 0; i < 194; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_inquiry_response_message(&got, wire, 0) == 194);
  assert(encode_trade_inquiry_response_message(&got, again, 0) == 194);
  for (size_t i = 0; i < 194; i++) { assert(again[i] == wire[i]); }
}

/* ---- Control Message To Trader Message: 250 bytes ---------------------------- */

/* Interactive message sent to the trader from Nse Ix Control */
typedef struct {
  uint8_t trader_id[4];                  /* bytes 0 to 3 */
  uint8_t action_code[3];                /* bytes 4 to 6 */
  uint8_t reserved_1;                    /* byte 7 */
  uint8_t broad_cast_message_length[2];  /* bytes 8 to 9 */
  uint8_t broad_cast_message[239];       /* bytes 10 to 248 */
  uint8_t second_reserved_1;             /* byte 249 */
} ControlMessageToTraderMessage;

/* any Control Message To Trader Message at all: every byte one the checker chooses */
static void any_control_message_to_trader_message(ControlMessageToTraderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->action_code[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->broad_cast_message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 239; i++) { record->broad_cast_message[i] = arbitrary(); }
  record->second_reserved_1 = arbitrary();
}

/* Control Message To Trader Message to the wire: 250 bytes from at, returning where the next byte goes */
static size_t encode_control_message_to_trader_message(const ControlMessageToTraderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->action_code[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broad_cast_message_length[i]; }
  for (size_t i = 0; i < 239; i++) { wire[at++] = record->broad_cast_message[i]; }
  wire[at++] = record->second_reserved_1;

  return at;
}

/* Control Message To Trader Message off the wire: 250 bytes from at, returning where the next byte lies */
static size_t decode_control_message_to_trader_message(ControlMessageToTraderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->action_code[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->broad_cast_message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 239; i++) { record->broad_cast_message[i] = wire[at++]; }
  record->second_reserved_1 = wire[at++];

  return at;
}

/* what was read of Control Message To Trader Message is what was written, byte for byte */
static void equal_control_message_to_trader_message(const ControlMessageToTraderMessage *read, const ControlMessageToTraderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->action_code[i] == written->action_code[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->broad_cast_message_length[i] == written->broad_cast_message_length[i]); }
  for (size_t i = 0; i < 239; i++) { assert(read->broad_cast_message[i] == written->broad_cast_message[i]); }
  assert(read->second_reserved_1 == written->second_reserved_1);
}

/* Control Message To Trader Message: written and read back, then read and written back */
static void check_control_message_to_trader_message(void) {
  ControlMessageToTraderMessage sent;
  ControlMessageToTraderMessage got;
  uint8_t wire[250];
  uint8_t again[250];

  any_control_message_to_trader_message(&sent);
  assert(encode_control_message_to_trader_message(&sent, wire, 0) == 250);
  assert(decode_control_message_to_trader_message(&got, wire, 0) == 250);
  equal_control_message_to_trader_message(&got, &sent);

  for (size_t i = 0; i < 250; i++) { wire[i] = arbitrary(); }
  assert(decode_control_message_to_trader_message(&got, wire, 0) == 250);
  assert(encode_control_message_to_trader_message(&got, again, 0) == 250);
  for (size_t i = 0; i < 250; i++) { assert(again[i] == wire[i]); }
}

/* ---- Report Header Body: 67 bytes -------------------------------------------- */

/* Report Header Body */
typedef struct {
  uint8_t org_scope;         /* byte 0 */
  uint8_t report_date[4];    /* bytes 1 to 4 */
  uint8_t user_type[2];      /* bytes 5 to 6 */
  uint8_t broker_id[5];      /* bytes 7 to 11 */
  uint8_t firm_name[25];     /* bytes 12 to 36 */
  uint8_t trader_number[4];  /* bytes 37 to 40 */
  uint8_t trader_name[26];   /* bytes 41 to 66 */
} ReportHeaderBody;

/* any Report Header Body at all: every byte one the checker chooses */
static void any_report_header_body(ReportHeaderBody *record) {
  record->org_scope = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->report_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->user_type[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->firm_name[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_number[i] = arbitrary(); }
  for (size_t i = 0; i < 26; i++) { record->trader_name[i] = arbitrary(); }
}

/* Report Header Body to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_report_header_body(const ReportHeaderBody *record, uint8_t *wire, size_t at) {
  wire[at++] = record->org_scope;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->report_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->user_type[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->firm_name[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_number[i]; }
  for (size_t i = 0; i < 26; i++) { wire[at++] = record->trader_name[i]; }

  return at;
}

/* Report Header Body off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_report_header_body(ReportHeaderBody *record, const uint8_t *wire, size_t at) {
  record->org_scope = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->report_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->user_type[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->firm_name[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_number[i] = wire[at++]; }
  for (size_t i = 0; i < 26; i++) { record->trader_name[i] = wire[at++]; }

  return at;
}

/* what was read of Report Header Body is what was written, byte for byte */
static void equal_report_header_body(const ReportHeaderBody *read, const ReportHeaderBody *written) {
  assert(read->org_scope == written->org_scope);
  for (size_t i = 0; i < 4; i++) { assert(read->report_date[i] == written->report_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->user_type[i] == written->user_type[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->firm_name[i] == written->firm_name[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_number[i] == written->trader_number[i]); }
  for (size_t i = 0; i < 26; i++) { assert(read->trader_name[i] == written->trader_name[i]); }
}

/* Report Header Body: written and read back, then read and written back */
static void check_report_header_body(void) {
  ReportHeaderBody sent;
  ReportHeaderBody got;
  uint8_t wire[67];
  uint8_t again[67];

  any_report_header_body(&sent);
  assert(encode_report_header_body(&sent, wire, 0) == 67);
  assert(decode_report_header_body(&got, wire, 0) == 67);
  equal_report_header_body(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_report_header_body(&got, wire, 0) == 67);
  assert(encode_report_header_body(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Report Trailer Body: 5 bytes -------------------------------------------- */

/* Report Trailer Body */
typedef struct {
  uint8_t number_of_packets[4];  /* bytes 0 to 3 */
  uint8_t reserved_1;            /* byte 4 */
} ReportTrailerBody;

/* any Report Trailer Body at all: every byte one the checker chooses */
static void any_report_trailer_body(ReportTrailerBody *record) {
  for (size_t i = 0; i < 4; i++) { record->number_of_packets[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Report Trailer Body to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_report_trailer_body(const ReportTrailerBody *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_packets[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Report Trailer Body off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_report_trailer_body(ReportTrailerBody *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->number_of_packets[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Report Trailer Body is what was written, byte for byte */
static void equal_report_trailer_body(const ReportTrailerBody *read, const ReportTrailerBody *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_packets[i] == written->number_of_packets[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Report Trailer Body: written and read back, then read and written back */
static void check_report_trailer_body(void) {
  ReportTrailerBody sent;
  ReportTrailerBody got;
  uint8_t wire[5];
  uint8_t again[5];

  any_report_trailer_body(&sent);
  assert(encode_report_trailer_body(&sent, wire, 0) == 5);
  assert(decode_report_trailer_body(&got, wire, 0) == 5);
  equal_report_trailer_body(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_report_trailer_body(&got, wire, 0) == 5);
  assert(encode_report_trailer_body(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spread Report Header Body: 67 bytes ------------------------------------- */

/* Spread Report Header Body */
typedef struct {
  uint8_t org_scope;         /* byte 0 */
  uint8_t report_date[4];    /* bytes 1 to 4 */
  uint8_t user_type[2];      /* bytes 5 to 6 */
  uint8_t broker_number[5];  /* bytes 7 to 11 */
  uint8_t broker_name[25];   /* bytes 12 to 36 */
  uint8_t trader_number[4];  /* bytes 37 to 40 */
  uint8_t trader_name[26];   /* bytes 41 to 66 */
} SpreadReportHeaderBody;

/* any Spread Report Header Body at all: every byte one the checker chooses */
static void any_spread_report_header_body(SpreadReportHeaderBody *record) {
  record->org_scope = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->report_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->user_type[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->broker_number[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->broker_name[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_number[i] = arbitrary(); }
  for (size_t i = 0; i < 26; i++) { record->trader_name[i] = arbitrary(); }
}

/* Spread Report Header Body to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_spread_report_header_body(const SpreadReportHeaderBody *record, uint8_t *wire, size_t at) {
  wire[at++] = record->org_scope;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->report_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->user_type[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_number[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->broker_name[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_number[i]; }
  for (size_t i = 0; i < 26; i++) { wire[at++] = record->trader_name[i]; }

  return at;
}

/* Spread Report Header Body off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_spread_report_header_body(SpreadReportHeaderBody *record, const uint8_t *wire, size_t at) {
  record->org_scope = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->report_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->user_type[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->broker_number[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->broker_name[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_number[i] = wire[at++]; }
  for (size_t i = 0; i < 26; i++) { record->trader_name[i] = wire[at++]; }

  return at;
}

/* what was read of Spread Report Header Body is what was written, byte for byte */
static void equal_spread_report_header_body(const SpreadReportHeaderBody *read, const SpreadReportHeaderBody *written) {
  assert(read->org_scope == written->org_scope);
  for (size_t i = 0; i < 4; i++) { assert(read->report_date[i] == written->report_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->user_type[i] == written->user_type[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->broker_number[i] == written->broker_number[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->broker_name[i] == written->broker_name[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_number[i] == written->trader_number[i]); }
  for (size_t i = 0; i < 26; i++) { assert(read->trader_name[i] == written->trader_name[i]); }
}

/* Spread Report Header Body: written and read back, then read and written back */
static void check_spread_report_header_body(void) {
  SpreadReportHeaderBody sent;
  SpreadReportHeaderBody got;
  uint8_t wire[67];
  uint8_t again[67];

  any_spread_report_header_body(&sent);
  assert(encode_spread_report_header_body(&sent, wire, 0) == 67);
  assert(decode_spread_report_header_body(&got, wire, 0) == 67);
  equal_spread_report_header_body(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_spread_report_header_body(&got, wire, 0) == 67);
  assert(encode_spread_report_header_body(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Gateway Router Response Message: 84 bytes ------------------------------- */

/* Returns the allocated gateway server and the keys used to encrypt the session */
typedef struct {
  uint8_t box_id[2];              /* bytes 0 to 1 */
  uint8_t broker_id[5];           /* bytes 2 to 6 */
  uint8_t filler;                 /* byte 7 */
  uint8_t ip_address[16];         /* bytes 8 to 23 */
  uint8_t port[4];                /* bytes 24 to 27 */
  uint8_t session_key[8];         /* bytes 28 to 35 */
  uint8_t cryptographic_key[32];  /* bytes 36 to 67 */
  uint8_t cryptographic_iv[16];   /* bytes 68 to 83 */
} GatewayRouterResponseMessage;

/* any Gateway Router Response Message at all: every byte one the checker chooses */
static void any_gateway_router_response_message(GatewayRouterResponseMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = arbitrary(); }
  record->filler = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->ip_address[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->port[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->session_key[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->cryptographic_key[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cryptographic_iv[i] = arbitrary(); }
}

/* Gateway Router Response Message to the wire: 84 bytes from at, returning where the next byte goes */
static size_t encode_gateway_router_response_message(const GatewayRouterResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->box_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_id[i]; }
  wire[at++] = record->filler;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->ip_address[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->port[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_key[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->cryptographic_key[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cryptographic_iv[i]; }

  return at;
}

/* Gateway Router Response Message off the wire: 84 bytes from at, returning where the next byte lies */
static size_t decode_gateway_router_response_message(GatewayRouterResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = wire[at++]; }
  record->filler = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->ip_address[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->port[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->session_key[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->cryptographic_key[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cryptographic_iv[i] = wire[at++]; }

  return at;
}

/* what was read of Gateway Router Response Message is what was written, byte for byte */
static void equal_gateway_router_response_message(const GatewayRouterResponseMessage *read, const GatewayRouterResponseMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->box_id[i] == written->box_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  assert(read->filler == written->filler);
  for (size_t i = 0; i < 16; i++) { assert(read->ip_address[i] == written->ip_address[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->port[i] == written->port[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->session_key[i] == written->session_key[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->cryptographic_key[i] == written->cryptographic_key[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cryptographic_iv[i] == written->cryptographic_iv[i]); }
}

/* Gateway Router Response Message: written and read back, then read and written back */
static void check_gateway_router_response_message(void) {
  GatewayRouterResponseMessage sent;
  GatewayRouterResponseMessage got;
  uint8_t wire[84];
  uint8_t again[84];

  any_gateway_router_response_message(&sent);
  assert(encode_gateway_router_response_message(&sent, wire, 0) == 84);
  assert(decode_gateway_router_response_message(&got, wire, 0) == 84);
  equal_gateway_router_response_message(&got, &sent);

  for (size_t i = 0; i < 84; i++) { wire[i] = arbitrary(); }
  assert(decode_gateway_router_response_message(&got, wire, 0) == 84);
  assert(encode_gateway_router_response_message(&got, again, 0) == 84);
  for (size_t i = 0; i < 84; i++) { assert(again[i] == wire[i]); }
}

/* ---- Box Sign On Request Out Message: 12 bytes ------------------------------- */

/* Confirms the box sign on */
typedef struct {
  uint8_t box_id[2];        /* bytes 0 to 1 */
  uint8_t reserved_10[10];  /* bytes 2 to 11 */
} BoxSignOnRequestOutMessage;

/* any Box Sign On Request Out Message at all: every byte one the checker chooses */
static void any_box_sign_on_request_out_message(BoxSignOnRequestOutMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* Box Sign On Request Out Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_box_sign_on_request_out_message(const BoxSignOnRequestOutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->box_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* Box Sign On Request Out Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_box_sign_on_request_out_message(BoxSignOnRequestOutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of Box Sign On Request Out Message is what was written, byte for byte */
static void equal_box_sign_on_request_out_message(const BoxSignOnRequestOutMessage *read, const BoxSignOnRequestOutMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->box_id[i] == written->box_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* Box Sign On Request Out Message: written and read back, then read and written back */
static void check_box_sign_on_request_out_message(void) {
  BoxSignOnRequestOutMessage sent;
  BoxSignOnRequestOutMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_box_sign_on_request_out_message(&sent);
  assert(encode_box_sign_on_request_out_message(&sent, wire, 0) == 12);
  assert(decode_box_sign_on_request_out_message(&got, wire, 0) == 12);
  equal_box_sign_on_request_out_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_box_sign_on_request_out_message(&got, wire, 0) == 12);
  assert(encode_box_sign_on_request_out_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Box Sign Off Message: 2 bytes ------------------------------------------- */

/* Signs the box off the gateway server when the exchange terminates the connection */
typedef struct {
  uint8_t box_id[2];  /* bytes 0 to 1 */
} BoxSignOffMessage;

/* any Box Sign Off Message at all: every byte one the checker chooses */
static void any_box_sign_off_message(BoxSignOffMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = arbitrary(); }
}

/* Box Sign Off Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_box_sign_off_message(const BoxSignOffMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->box_id[i]; }

  return at;
}

/* Box Sign Off Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_box_sign_off_message(BoxSignOffMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = wire[at++]; }

  return at;
}

/* what was read of Box Sign Off Message is what was written, byte for byte */
static void equal_box_sign_off_message(const BoxSignOffMessage *read, const BoxSignOffMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->box_id[i] == written->box_id[i]); }
}

/* Box Sign Off Message: written and read back, then read and written back */
static void check_box_sign_off_message(void) {
  BoxSignOffMessage sent;
  BoxSignOffMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_box_sign_off_message(&sent);
  assert(encode_box_sign_off_message(&sent, wire, 0) == 2);
  assert(decode_box_sign_off_message(&got, wire, 0) == 2);
  equal_box_sign_off_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_box_sign_off_message(&got, wire, 0) == 2);
  assert(encode_box_sign_off_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Contingency Broadcast Message: 204 bytes -------------------------------- */

/* Signals the start or end of an outage on one or all matching engine streams */
typedef struct {
  uint8_t stream_number[2];   /* bytes 0 to 1 */
  uint8_t status[2];          /* bytes 2 to 3 */
  uint8_t reserved_200[200];  /* bytes 4 to 203 */
} ContingencyBroadcastMessage;

/* any Contingency Broadcast Message at all: every byte one the checker chooses */
static void any_contingency_broadcast_message(ContingencyBroadcastMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stream_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->status[i] = arbitrary(); }
  for (size_t i = 0; i < 200; i++) { record->reserved_200[i] = arbitrary(); }
}

/* Contingency Broadcast Message to the wire: 204 bytes from at, returning where the next byte goes */
static size_t encode_contingency_broadcast_message(const ContingencyBroadcastMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stream_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->status[i]; }
  for (size_t i = 0; i < 200; i++) { wire[at++] = record->reserved_200[i]; }

  return at;
}

/* Contingency Broadcast Message off the wire: 204 bytes from at, returning where the next byte lies */
static size_t decode_contingency_broadcast_message(ContingencyBroadcastMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stream_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->status[i] = wire[at++]; }
  for (size_t i = 0; i < 200; i++) { record->reserved_200[i] = wire[at++]; }

  return at;
}

/* what was read of Contingency Broadcast Message is what was written, byte for byte */
static void equal_contingency_broadcast_message(const ContingencyBroadcastMessage *read, const ContingencyBroadcastMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stream_number[i] == written->stream_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->status[i] == written->status[i]); }
  for (size_t i = 0; i < 200; i++) { assert(read->reserved_200[i] == written->reserved_200[i]); }
}

/* Contingency Broadcast Message: written and read back, then read and written back */
static void check_contingency_broadcast_message(void) {
  ContingencyBroadcastMessage sent;
  ContingencyBroadcastMessage got;
  uint8_t wire[204];
  uint8_t again[204];

  any_contingency_broadcast_message(&sent);
  assert(encode_contingency_broadcast_message(&sent, wire, 0) == 204);
  assert(decode_contingency_broadcast_message(&got, wire, 0) == 204);
  equal_contingency_broadcast_message(&got, &sent);

  for (size_t i = 0; i < 204; i++) { wire[i] = arbitrary(); }
  assert(decode_contingency_broadcast_message(&got, wire, 0) == 204);
  assert(encode_contingency_broadcast_message(&got, again, 0) == 204);
  for (size_t i = 0; i < 204; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reset User Password Response Message: 18 bytes -------------------------- */

/* Answers the password reset request, Error Code in the header saying whether it succeeded */
typedef struct {
  uint8_t user_id[4];       /* bytes 0 to 3 */
  uint8_t reserved_14[14];  /* bytes 4 to 17 */
} ResetUserPasswordResponseMessage;

/* any Reset User Password Response Message at all: every byte one the checker chooses */
static void any_reset_user_password_response_message(ResetUserPasswordResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->reserved_14[i] = arbitrary(); }
}

/* Reset User Password Response Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_reset_user_password_response_message(const ResetUserPasswordResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->reserved_14[i]; }

  return at;
}

/* Reset User Password Response Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_reset_user_password_response_message(ResetUserPasswordResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->reserved_14[i] = wire[at++]; }

  return at;
}

/* what was read of Reset User Password Response Message is what was written, byte for byte */
static void equal_reset_user_password_response_message(const ResetUserPasswordResponseMessage *read, const ResetUserPasswordResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->reserved_14[i] == written->reserved_14[i]); }
}

/* Reset User Password Response Message: written and read back, then read and written back */
static void check_reset_user_password_response_message(void) {
  ResetUserPasswordResponseMessage sent;
  ResetUserPasswordResponseMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_reset_user_password_response_message(&sent);
  assert(encode_reset_user_password_response_message(&sent, wire, 0) == 18);
  assert(decode_reset_user_password_response_message(&got, wire, 0) == 18);
  equal_reset_user_password_response_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_reset_user_password_response_message(&got, wire, 0) == 18);
  assert(encode_reset_user_password_response_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Collateral User Status Change Response Message: 6 bytes ----------------- */

/* Answers the cancel on logout status change */
typedef struct {
  uint8_t user_id[4];    /* bytes 0 to 3 */
  uint8_t col_user_bit;  /* byte 4 */
  uint8_t reserved_1;    /* byte 5 */
} CollateralUserStatusChangeResponseMessage;

/* any Collateral User Status Change Response Message at all: every byte one the checker chooses */
static void any_collateral_user_status_change_response_message(CollateralUserStatusChangeResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  record->col_user_bit = arbitrary();
  record->reserved_1 = arbitrary();
}

/* Collateral User Status Change Response Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_collateral_user_status_change_response_message(const CollateralUserStatusChangeResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  wire[at++] = record->col_user_bit;
  wire[at++] = record->reserved_1;

  return at;
}

/* Collateral User Status Change Response Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_collateral_user_status_change_response_message(CollateralUserStatusChangeResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  record->col_user_bit = wire[at++];
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Collateral User Status Change Response Message is what was written, byte for byte */
static void equal_collateral_user_status_change_response_message(const CollateralUserStatusChangeResponseMessage *read, const CollateralUserStatusChangeResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  assert(read->col_user_bit == written->col_user_bit);
  assert(read->reserved_1 == written->reserved_1);
}

/* Collateral User Status Change Response Message: written and read back, then read and written back */
static void check_collateral_user_status_change_response_message(void) {
  CollateralUserStatusChangeResponseMessage sent;
  CollateralUserStatusChangeResponseMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_collateral_user_status_change_response_message(&sent);
  assert(encode_collateral_user_status_change_response_message(&sent, wire, 0) == 6);
  assert(decode_collateral_user_status_change_response_message(&got, wire, 0) == 6);
  equal_collateral_user_status_change_response_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_collateral_user_status_change_response_message(&got, wire, 0) == 6);
  assert(encode_collateral_user_status_change_response_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- User Trade Modify Cancel Status Change Response Message: 6 bytes -------- */

/* Answers the trade modification or cancellation status change */
typedef struct {
  uint8_t user_id[4];       /* bytes 0 to 3 */
  uint8_t trd_mod_cxl_bit;  /* byte 4 */
  uint8_t reserved_1;       /* byte 5 */
} UserTradeModifyCancelStatusChangeResponseMessage;

/* any User Trade Modify Cancel Status Change Response Message at all: every byte one the checker chooses */
static void any_user_trade_modify_cancel_status_change_response_message(UserTradeModifyCancelStatusChangeResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  record->trd_mod_cxl_bit = arbitrary();
  record->reserved_1 = arbitrary();
}

/* User Trade Modify Cancel Status Change Response Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_user_trade_modify_cancel_status_change_response_message(const UserTradeModifyCancelStatusChangeResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  wire[at++] = record->trd_mod_cxl_bit;
  wire[at++] = record->reserved_1;

  return at;
}

/* User Trade Modify Cancel Status Change Response Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_user_trade_modify_cancel_status_change_response_message(UserTradeModifyCancelStatusChangeResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  record->trd_mod_cxl_bit = wire[at++];
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of User Trade Modify Cancel Status Change Response Message is what was written, byte for byte */
static void equal_user_trade_modify_cancel_status_change_response_message(const UserTradeModifyCancelStatusChangeResponseMessage *read, const UserTradeModifyCancelStatusChangeResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  assert(read->trd_mod_cxl_bit == written->trd_mod_cxl_bit);
  assert(read->reserved_1 == written->reserved_1);
}

/* User Trade Modify Cancel Status Change Response Message: written and read back, then read and written back */
static void check_user_trade_modify_cancel_status_change_response_message(void) {
  UserTradeModifyCancelStatusChangeResponseMessage sent;
  UserTradeModifyCancelStatusChangeResponseMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_user_trade_modify_cancel_status_change_response_message(&sent);
  assert(encode_user_trade_modify_cancel_status_change_response_message(&sent, wire, 0) == 6);
  assert(decode_user_trade_modify_cancel_status_change_response_message(&got, wire, 0) == 6);
  equal_user_trade_modify_cancel_status_change_response_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_user_trade_modify_cancel_status_change_response_message(&got, wire, 0) == 6);
  assert(encode_user_trade_modify_cancel_status_change_response_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- User Address Unlock Confirm Message: 40 bytes --------------------------- */

/* Acknowledges that the unlock request reached the trading system */
typedef struct {
  uint8_t user_id[4];       /* bytes 0 to 3 */
  uint8_t reserved_36[36];  /* bytes 4 to 39 */
} UserAddressUnlockConfirmMessage;

/* any User Address Unlock Confirm Message at all: every byte one the checker chooses */
static void any_user_address_unlock_confirm_message(UserAddressUnlockConfirmMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 36; i++) { record->reserved_36[i] = arbitrary(); }
}

/* User Address Unlock Confirm Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_user_address_unlock_confirm_message(const UserAddressUnlockConfirmMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 36; i++) { wire[at++] = record->reserved_36[i]; }

  return at;
}

/* User Address Unlock Confirm Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_user_address_unlock_confirm_message(UserAddressUnlockConfirmMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 36; i++) { record->reserved_36[i] = wire[at++]; }

  return at;
}

/* what was read of User Address Unlock Confirm Message is what was written, byte for byte */
static void equal_user_address_unlock_confirm_message(const UserAddressUnlockConfirmMessage *read, const UserAddressUnlockConfirmMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 36; i++) { assert(read->reserved_36[i] == written->reserved_36[i]); }
}

/* User Address Unlock Confirm Message: written and read back, then read and written back */
static void check_user_address_unlock_confirm_message(void) {
  UserAddressUnlockConfirmMessage sent;
  UserAddressUnlockConfirmMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_user_address_unlock_confirm_message(&sent);
  assert(encode_user_address_unlock_confirm_message(&sent, wire, 0) == 40);
  assert(decode_user_address_unlock_confirm_message(&got, wire, 0) == 40);
  equal_user_address_unlock_confirm_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_user_address_unlock_confirm_message(&got, wire, 0) == 40);
  assert(encode_user_address_unlock_confirm_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- User Address Unlock Approve Message: 40 bytes --------------------------- */

/* Approves or rejects the unlock of a user. Transaction Code in the header names which */
typedef struct {
  uint8_t user_id[4];       /* bytes 0 to 3 */
  uint8_t reserved_36[36];  /* bytes 4 to 39 */
} UserAddressUnlockApproveMessage;

/* any User Address Unlock Approve Message at all: every byte one the checker chooses */
static void any_user_address_unlock_approve_message(UserAddressUnlockApproveMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 36; i++) { record->reserved_36[i] = arbitrary(); }
}

/* User Address Unlock Approve Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_user_address_unlock_approve_message(const UserAddressUnlockApproveMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 36; i++) { wire[at++] = record->reserved_36[i]; }

  return at;
}

/* User Address Unlock Approve Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_user_address_unlock_approve_message(UserAddressUnlockApproveMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 36; i++) { record->reserved_36[i] = wire[at++]; }

  return at;
}

/* what was read of User Address Unlock Approve Message is what was written, byte for byte */
static void equal_user_address_unlock_approve_message(const UserAddressUnlockApproveMessage *read, const UserAddressUnlockApproveMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 36; i++) { assert(read->reserved_36[i] == written->reserved_36[i]); }
}

/* User Address Unlock Approve Message: written and read back, then read and written back */
static void check_user_address_unlock_approve_message(void) {
  UserAddressUnlockApproveMessage sent;
  UserAddressUnlockApproveMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_user_address_unlock_approve_message(&sent);
  assert(encode_user_address_unlock_approve_message(&sent, wire, 0) == 40);
  assert(decode_user_address_unlock_approve_message(&got, wire, 0) == 40);
  equal_user_address_unlock_approve_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_user_address_unlock_approve_message(&got, wire, 0) == 40);
  assert(encode_user_address_unlock_approve_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Nlt Order Message To Trader Message: 276 bytes -------------------------- */

/* Tells the counter member's corporate manager of a negotiated large trade order placed against it */
typedef struct {
  uint8_t message_buffer[276];  /* bytes 0 to 275 */
} NltOrderMessageToTraderMessage;

/* any Nlt Order Message To Trader Message at all: every byte one the checker chooses */
static void any_nlt_order_message_to_trader_message(NltOrderMessageToTraderMessage *record) {
  for (size_t i = 0; i < 276; i++) { record->message_buffer[i] = arbitrary(); }
}

/* Nlt Order Message To Trader Message to the wire: 276 bytes from at, returning where the next byte goes */
static size_t encode_nlt_order_message_to_trader_message(const NltOrderMessageToTraderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 276; i++) { wire[at++] = record->message_buffer[i]; }

  return at;
}

/* Nlt Order Message To Trader Message off the wire: 276 bytes from at, returning where the next byte lies */
static size_t decode_nlt_order_message_to_trader_message(NltOrderMessageToTraderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 276; i++) { record->message_buffer[i] = wire[at++]; }

  return at;
}

/* what was read of Nlt Order Message To Trader Message is what was written, byte for byte */
static void equal_nlt_order_message_to_trader_message(const NltOrderMessageToTraderMessage *read, const NltOrderMessageToTraderMessage *written) {
  for (size_t i = 0; i < 276; i++) { assert(read->message_buffer[i] == written->message_buffer[i]); }
}

/* Nlt Order Message To Trader Message: written and read back, then read and written back */
static void check_nlt_order_message_to_trader_message(void) {
  NltOrderMessageToTraderMessage sent;
  NltOrderMessageToTraderMessage got;
  uint8_t wire[276];
  uint8_t again[276];

  any_nlt_order_message_to_trader_message(&sent);
  assert(encode_nlt_order_message_to_trader_message(&sent, wire, 0) == 276);
  assert(decode_nlt_order_message_to_trader_message(&got, wire, 0) == 276);
  equal_nlt_order_message_to_trader_message(&got, &sent);

  for (size_t i = 0; i < 276; i++) { wire[i] = arbitrary(); }
  assert(decode_nlt_order_message_to_trader_message(&got, wire, 0) == 276);
  assert(encode_nlt_order_message_to_trader_message(&got, again, 0) == 276);
  for (size_t i = 0; i < 276; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_error_response_body();
  check_sign_off_request_out_message();
  check_st_market_status();
  check_st_ex_market_status();
  check_st_pl_market_status();
  check_update_local_database_header_message();
  check_update_local_database_trailer_message();
  check_inner_header();
  check_contract_desc();
  check_trade_inquiry_body();
  check_trade_inquiry_response_message();
  check_control_message_to_trader_message();
  check_report_header_body();
  check_report_trailer_body();
  check_spread_report_header_body();
  check_gateway_router_response_message();
  check_box_sign_on_request_out_message();
  check_box_sign_off_message();
  check_contingency_broadcast_message();
  check_reset_user_password_response_message();
  check_collateral_user_status_change_response_message();
  check_user_trade_modify_cancel_status_change_response_message();
  check_user_address_unlock_confirm_message();
  check_user_address_unlock_approve_message();
  check_nlt_order_message_to_trader_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
