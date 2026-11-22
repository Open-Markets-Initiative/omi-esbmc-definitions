// nse/nsefo/orderentry/NseFo_OrderEntry_NnfDirect_v9_50_Server.c
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
 *   - a Composite rule
 *   - a field read in bits
 *   - the dispatch that chooses a message by its type
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

/* ---- Sign Off Request Out Message: 149 bytes --------------------------------- */

/* Breaks the virtual circuit between the host and the front end */
typedef struct {
  uint8_t user_id[4];         /* bytes 0 to 3 */
  uint8_t reserved_145[145];  /* bytes 4 to 148 */
} SignOffRequestOutMessage;

/* any Sign Off Request Out Message at all: every byte one the checker chooses */
static void any_sign_off_request_out_message(SignOffRequestOutMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 145; i++) { record->reserved_145[i] = arbitrary(); }
}

/* Sign Off Request Out Message to the wire: 149 bytes from at, returning where the next byte goes */
static size_t encode_sign_off_request_out_message(const SignOffRequestOutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 145; i++) { wire[at++] = record->reserved_145[i]; }

  return at;
}

/* Sign Off Request Out Message off the wire: 149 bytes from at, returning where the next byte lies */
static size_t decode_sign_off_request_out_message(SignOffRequestOutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 145; i++) { record->reserved_145[i] = wire[at++]; }

  return at;
}

/* what was read of Sign Off Request Out Message is what was written, byte for byte */
static void equal_sign_off_request_out_message(const SignOffRequestOutMessage *read, const SignOffRequestOutMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 145; i++) { assert(read->reserved_145[i] == written->reserved_145[i]); }
}

/* Sign Off Request Out Message: written and read back, then read and written back */
static void check_sign_off_request_out_message(void) {
  SignOffRequestOutMessage sent;
  SignOffRequestOutMessage got;
  uint8_t wire[149];
  uint8_t again[149];

  any_sign_off_request_out_message(&sent);
  assert(encode_sign_off_request_out_message(&sent, wire, 0) == 149);
  assert(decode_sign_off_request_out_message(&got, wire, 0) == 149);
  equal_sign_off_request_out_message(&got, &sent);

  for (size_t i = 0; i < 149; i++) { wire[i] = arbitrary(); }
  assert(decode_sign_off_request_out_message(&got, wire, 0) == 149);
  assert(encode_sign_off_request_out_message(&got, again, 0) == 149);
  for (size_t i = 0; i < 149; i++) { assert(again[i] == wire[i]); }
}

/* ---- St Market Status: 8 bytes ----------------------------------------------- */

/* ST_MARKET_STATUS */
typedef struct {
  uint8_t market_status_normal[2];   /* bytes 0 to 1 */
  uint8_t market_status_oddlot[2];   /* bytes 2 to 3 */
  uint8_t market_status_spot[2];     /* bytes 4 to 5 */
  uint8_t market_status_auction[2];  /* bytes 6 to 7 */
} StMarketStatus;

/* any St Market Status at all: every byte one the checker chooses */
static void any_st_market_status(StMarketStatus *record) {
  for (size_t i = 0; i < 2; i++) { record->market_status_normal[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_status_oddlot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_status_spot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_status_auction[i] = arbitrary(); }
}

/* St Market Status to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_st_market_status(const StMarketStatus *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_status_normal[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_status_oddlot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_status_spot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_status_auction[i]; }

  return at;
}

/* St Market Status off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_st_market_status(StMarketStatus *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->market_status_normal[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_status_oddlot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_status_spot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_status_auction[i] = wire[at++]; }

  return at;
}

/* what was read of St Market Status is what was written, byte for byte */
static void equal_st_market_status(const StMarketStatus *read, const StMarketStatus *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->market_status_normal[i] == written->market_status_normal[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_status_oddlot[i] == written->market_status_oddlot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_status_spot[i] == written->market_status_spot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_status_auction[i] == written->market_status_auction[i]); }
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
  uint8_t ex_market_status_normal[2];   /* bytes 0 to 1 */
  uint8_t ex_market_status_oddlot[2];   /* bytes 2 to 3 */
  uint8_t ex_market_status_spot[2];     /* bytes 4 to 5 */
  uint8_t ex_market_status_auction[2];  /* bytes 6 to 7 */
} StExMarketStatus;

/* any St Ex Market Status at all: every byte one the checker chooses */
static void any_st_ex_market_status(StExMarketStatus *record) {
  for (size_t i = 0; i < 2; i++) { record->ex_market_status_normal[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ex_market_status_oddlot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ex_market_status_spot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ex_market_status_auction[i] = arbitrary(); }
}

/* St Ex Market Status to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_st_ex_market_status(const StExMarketStatus *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ex_market_status_normal[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ex_market_status_oddlot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ex_market_status_spot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ex_market_status_auction[i]; }

  return at;
}

/* St Ex Market Status off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_st_ex_market_status(StExMarketStatus *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->ex_market_status_normal[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ex_market_status_oddlot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ex_market_status_spot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ex_market_status_auction[i] = wire[at++]; }

  return at;
}

/* what was read of St Ex Market Status is what was written, byte for byte */
static void equal_st_ex_market_status(const StExMarketStatus *read, const StExMarketStatus *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->ex_market_status_normal[i] == written->ex_market_status_normal[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ex_market_status_oddlot[i] == written->ex_market_status_oddlot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ex_market_status_spot[i] == written->ex_market_status_spot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ex_market_status_auction[i] == written->ex_market_status_auction[i]); }
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
  uint8_t pl_market_status_normal[2];   /* bytes 0 to 1 */
  uint8_t pl_market_status_oddlot[2];   /* bytes 2 to 3 */
  uint8_t pl_market_status_spot[2];     /* bytes 4 to 5 */
  uint8_t pl_market_status_auction[2];  /* bytes 6 to 7 */
} StPlMarketStatus;

/* any St Pl Market Status at all: every byte one the checker chooses */
static void any_st_pl_market_status(StPlMarketStatus *record) {
  for (size_t i = 0; i < 2; i++) { record->pl_market_status_normal[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->pl_market_status_oddlot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->pl_market_status_spot[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->pl_market_status_auction[i] = arbitrary(); }
}

/* St Pl Market Status to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_st_pl_market_status(const StPlMarketStatus *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->pl_market_status_normal[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->pl_market_status_oddlot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->pl_market_status_spot[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->pl_market_status_auction[i]; }

  return at;
}

/* St Pl Market Status off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_st_pl_market_status(StPlMarketStatus *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->pl_market_status_normal[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->pl_market_status_oddlot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->pl_market_status_spot[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->pl_market_status_auction[i] = wire[at++]; }

  return at;
}

/* what was read of St Pl Market Status is what was written, byte for byte */
static void equal_st_pl_market_status(const StPlMarketStatus *read, const StPlMarketStatus *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->pl_market_status_normal[i] == written->pl_market_status_normal[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->pl_market_status_oddlot[i] == written->pl_market_status_oddlot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->pl_market_status_spot[i] == written->pl_market_status_spot[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->pl_market_status_auction[i] == written->pl_market_status_auction[i]); }
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

/* ---- Existing Encryption Tail: 16 bytes -------------------------------------- */

/* Initialisation vector used by the existing encryption */
typedef struct {
  uint8_t cryptographic_iv[16];  /* bytes 0 to 15 */
} ExistingEncryptionTail;

/* any Existing Encryption Tail at all: every byte one the checker chooses */
static void any_existing_encryption_tail(ExistingEncryptionTail *record) {
  for (size_t i = 0; i < 16; i++) { record->cryptographic_iv[i] = arbitrary(); }
}

/* Existing Encryption Tail to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_existing_encryption_tail(const ExistingEncryptionTail *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cryptographic_iv[i]; }

  return at;
}

/* Existing Encryption Tail off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_existing_encryption_tail(ExistingEncryptionTail *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->cryptographic_iv[i] = wire[at++]; }

  return at;
}

/* what was read of Existing Encryption Tail is what was written, byte for byte */
static void equal_existing_encryption_tail(const ExistingEncryptionTail *read, const ExistingEncryptionTail *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->cryptographic_iv[i] == written->cryptographic_iv[i]); }
}

/* Existing Encryption Tail: written and read back, then read and written back */
static void check_existing_encryption_tail(void) {
  ExistingEncryptionTail sent;
  ExistingEncryptionTail got;
  uint8_t wire[16];
  uint8_t again[16];

  any_existing_encryption_tail(&sent);
  assert(encode_existing_encryption_tail(&sent, wire, 0) == 16);
  assert(decode_existing_encryption_tail(&got, wire, 0) == 16);
  equal_existing_encryption_tail(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_existing_encryption_tail(&got, wire, 0) == 16);
  assert(encode_existing_encryption_tail(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Encryption Tail: 28 bytes ------------------------------------------- */

/* Initialisation vectors used by the new authenticated encryption */
typedef struct {
  uint8_t static_cryptographic_iv[8];        /* bytes 0 to 7 */
  uint8_t dynamic_cryptographic_iv[8];       /* bytes 8 to 15 */
  uint8_t cryptographic_additional_key[12];  /* bytes 16 to 27 */
} NewEncryptionTail;

/* any New Encryption Tail at all: every byte one the checker chooses */
static void any_new_encryption_tail(NewEncryptionTail *record) {
  for (size_t i = 0; i < 8; i++) { record->static_cryptographic_iv[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->dynamic_cryptographic_iv[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->cryptographic_additional_key[i] = arbitrary(); }
}

/* New Encryption Tail to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_new_encryption_tail(const NewEncryptionTail *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->static_cryptographic_iv[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->dynamic_cryptographic_iv[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->cryptographic_additional_key[i]; }

  return at;
}

/* New Encryption Tail off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_new_encryption_tail(NewEncryptionTail *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->static_cryptographic_iv[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->dynamic_cryptographic_iv[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->cryptographic_additional_key[i] = wire[at++]; }

  return at;
}

/* what was read of New Encryption Tail is what was written, byte for byte */
static void equal_new_encryption_tail(const NewEncryptionTail *read, const NewEncryptionTail *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->static_cryptographic_iv[i] == written->static_cryptographic_iv[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->dynamic_cryptographic_iv[i] == written->dynamic_cryptographic_iv[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->cryptographic_additional_key[i] == written->cryptographic_additional_key[i]); }
}

/* New Encryption Tail: written and read back, then read and written back */
static void check_new_encryption_tail(void) {
  NewEncryptionTail sent;
  NewEncryptionTail got;
  uint8_t wire[28];
  uint8_t again[28];

  any_new_encryption_tail(&sent);
  assert(encode_new_encryption_tail(&sent, wire, 0) == 28);
  assert(decode_new_encryption_tail(&got, wire, 0) == 28);
  equal_new_encryption_tail(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_new_encryption_tail(&got, wire, 0) == 28);
  assert(encode_new_encryption_tail(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
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

/* ---- Download Header: 40 bytes ----------------------------------------------- */

/* MESSAGE_HEADER of the downloaded message */
typedef struct {
  uint8_t inner_transaction_code[2];  /* bytes 0 to 1 */
  uint8_t inner_log_time[4];          /* bytes 2 to 5 */
  uint8_t inner_alpha_char[2];        /* bytes 6 to 7 */
  uint8_t inner_trader_id[4];         /* bytes 8 to 11 */
  uint8_t inner_error_code[2];        /* bytes 12 to 13 */
  uint8_t inner_timestamp[8];         /* bytes 14 to 21 */
  uint8_t inner_time_stamp_1[8];      /* bytes 22 to 29 */
  uint8_t inner_time_stamp_2[8];      /* bytes 30 to 37 */
  uint8_t inner_message_length[2];    /* bytes 38 to 39 */
} DownloadHeader;

/* any Download Header at all: every byte one the checker chooses */
static void any_download_header(DownloadHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->inner_transaction_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->inner_log_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->inner_alpha_char[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->inner_trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->inner_error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->inner_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->inner_time_stamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->inner_time_stamp_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->inner_message_length[i] = arbitrary(); }
}

/* Download Header to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_download_header(const DownloadHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->inner_transaction_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->inner_log_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->inner_alpha_char[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->inner_trader_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->inner_error_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->inner_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->inner_time_stamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->inner_time_stamp_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->inner_message_length[i]; }

  return at;
}

/* Download Header off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_download_header(DownloadHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->inner_transaction_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->inner_log_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->inner_alpha_char[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->inner_trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->inner_error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->inner_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->inner_time_stamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->inner_time_stamp_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->inner_message_length[i] = wire[at++]; }

  return at;
}

/* what was read of Download Header is what was written, byte for byte */
static void equal_download_header(const DownloadHeader *read, const DownloadHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->inner_transaction_code[i] == written->inner_transaction_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->inner_log_time[i] == written->inner_log_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->inner_alpha_char[i] == written->inner_alpha_char[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->inner_trader_id[i] == written->inner_trader_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->inner_error_code[i] == written->inner_error_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->inner_timestamp[i] == written->inner_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->inner_time_stamp_1[i] == written->inner_time_stamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->inner_time_stamp_2[i] == written->inner_time_stamp_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->inner_message_length[i] == written->inner_message_length[i]); }
}

/* Download Header: written and read back, then read and written back */
static void check_download_header(void) {
  DownloadHeader sent;
  DownloadHeader got;
  uint8_t wire[40];
  uint8_t again[40];

  any_download_header(&sent);
  assert(encode_download_header(&sent, wire, 0) == 40);
  assert(decode_download_header(&got, wire, 0) == 40);
  equal_download_header(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_download_header(&got, wire, 0) == 40);
  assert(encode_download_header(&got, again, 0) == 40);
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

/* ---- Control Message To Trader Message: 249 bytes ---------------------------- */

/* Interactive message sent to the trader from Nse Control */
typedef struct {
  uint8_t trader_id[4];                  /* bytes 0 to 3 */
  uint8_t action_code[3];                /* bytes 4 to 6 */
  uint8_t reserved_1;                    /* byte 7 */
  uint8_t broad_cast_message_length[2];  /* bytes 8 to 9 */
  uint8_t broad_cast_message[239];       /* bytes 10 to 248 */
} ControlMessageToTraderMessage;

/* any Control Message To Trader Message at all: every byte one the checker chooses */
static void any_control_message_to_trader_message(ControlMessageToTraderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->action_code[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->broad_cast_message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 239; i++) { record->broad_cast_message[i] = arbitrary(); }
}

/* Control Message To Trader Message to the wire: 249 bytes from at, returning where the next byte goes */
static size_t encode_control_message_to_trader_message(const ControlMessageToTraderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->action_code[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broad_cast_message_length[i]; }
  for (size_t i = 0; i < 239; i++) { wire[at++] = record->broad_cast_message[i]; }

  return at;
}

/* Control Message To Trader Message off the wire: 249 bytes from at, returning where the next byte lies */
static size_t decode_control_message_to_trader_message(ControlMessageToTraderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->action_code[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->broad_cast_message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 239; i++) { record->broad_cast_message[i] = wire[at++]; }

  return at;
}

/* what was read of Control Message To Trader Message is what was written, byte for byte */
static void equal_control_message_to_trader_message(const ControlMessageToTraderMessage *read, const ControlMessageToTraderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->action_code[i] == written->action_code[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->broad_cast_message_length[i] == written->broad_cast_message_length[i]); }
  for (size_t i = 0; i < 239; i++) { assert(read->broad_cast_message[i] == written->broad_cast_message[i]); }
}

/* Control Message To Trader Message: written and read back, then read and written back */
static void check_control_message_to_trader_message(void) {
  ControlMessageToTraderMessage sent;
  ControlMessageToTraderMessage got;
  uint8_t wire[249];
  uint8_t again[249];

  any_control_message_to_trader_message(&sent);
  assert(encode_control_message_to_trader_message(&sent, wire, 0) == 249);
  assert(decode_control_message_to_trader_message(&got, wire, 0) == 249);
  equal_control_message_to_trader_message(&got, &sent);

  for (size_t i = 0; i < 249; i++) { wire[i] = arbitrary(); }
  assert(decode_control_message_to_trader_message(&got, wire, 0) == 249);
  assert(encode_control_message_to_trader_message(&got, again, 0) == 249);
  for (size_t i = 0; i < 249; i++) { assert(again[i] == wire[i]); }
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

/* ---- Mkt Index: 10 bytes ----------------------------------------------------- */

/* MKT_INDEX */
typedef struct {
  uint8_t market_opening_index[2];  /* bytes 0 to 1 */
  uint8_t market_high_index[2];     /* bytes 2 to 3 */
  uint8_t market_low_index[2];      /* bytes 4 to 5 */
  uint8_t market_closing_index[2];  /* bytes 6 to 7 */
  uint8_t market_start_index[2];    /* bytes 8 to 9 */
} MktIndex;

/* any Mkt Index at all: every byte one the checker chooses */
static void any_mkt_index(MktIndex *record) {
  for (size_t i = 0; i < 2; i++) { record->market_opening_index[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_high_index[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_low_index[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_closing_index[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_start_index[i] = arbitrary(); }
}

/* Mkt Index to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_mkt_index(const MktIndex *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_opening_index[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_high_index[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_low_index[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_closing_index[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_start_index[i]; }

  return at;
}

/* Mkt Index off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_mkt_index(MktIndex *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->market_opening_index[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_high_index[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_low_index[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_closing_index[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_start_index[i] = wire[at++]; }

  return at;
}

/* what was read of Mkt Index is what was written, byte for byte */
static void equal_mkt_index(const MktIndex *read, const MktIndex *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->market_opening_index[i] == written->market_opening_index[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_high_index[i] == written->market_high_index[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_low_index[i] == written->market_low_index[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_closing_index[i] == written->market_closing_index[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_start_index[i] == written->market_start_index[i]); }
}

/* Mkt Index: written and read back, then read and written back */
static void check_mkt_index(void) {
  MktIndex sent;
  MktIndex got;
  uint8_t wire[10];
  uint8_t again[10];

  any_mkt_index(&sent);
  assert(encode_mkt_index(&sent, wire, 0) == 10);
  assert(decode_mkt_index(&got, wire, 0) == 10);
  equal_mkt_index(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_mkt_index(&got, wire, 0) == 10);
  assert(encode_mkt_index(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Index Report Message: 26 bytes ----------------------------------- */

/* Bhavcopy market index report */
typedef struct {
  uint8_t message_type;    /* byte 0 */
  uint8_t index_name[15];  /* bytes 1 to 15 */
  MktIndex mkt_index;      /* bytes 16 to 25 */
} MarketIndexReportMessage;

/* any Market Index Report Message at all: every byte one the checker chooses */
static void any_market_index_report_message(MarketIndexReportMessage *record) {
  record->message_type = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->index_name[i] = arbitrary(); }
  any_mkt_index(&record->mkt_index);
}

/* Market Index Report Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_market_index_report_message(const MarketIndexReportMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_type;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->index_name[i]; }
  at = encode_mkt_index(&record->mkt_index, wire, at);

  return at;
}

/* Market Index Report Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_market_index_report_message(MarketIndexReportMessage *record, const uint8_t *wire, size_t at) {
  record->message_type = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->index_name[i] = wire[at++]; }
  at = decode_mkt_index(&record->mkt_index, wire, at);

  return at;
}

/* what was read of Market Index Report Message is what was written, byte for byte */
static void equal_market_index_report_message(const MarketIndexReportMessage *read, const MarketIndexReportMessage *written) {
  assert(read->message_type == written->message_type);
  for (size_t i = 0; i < 15; i++) { assert(read->index_name[i] == written->index_name[i]); }
  equal_mkt_index(&read->mkt_index, &written->mkt_index);
}

/* Market Index Report Message: written and read back, then read and written back */
static void check_market_index_report_message(void) {
  MarketIndexReportMessage sent;
  MarketIndexReportMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_market_index_report_message(&sent);
  assert(encode_market_index_report_message(&sent, wire, 0) == 26);
  assert(decode_market_index_report_message(&got, wire, 0) == 26);
  equal_market_index_report_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_market_index_report_message(&got, wire, 0) == 26);
  assert(encode_market_index_report_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
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

/* ---- Index Details: 98 bytes ------------------------------------------------- */

/* INDEX_DETAILS */
typedef struct {
  uint8_t token[4];       /* bytes 0 to 3 */
  uint8_t name[50];       /* bytes 4 to 53 */
  uint8_t open[4];        /* bytes 54 to 57 */
  uint8_t high[4];        /* bytes 58 to 61 */
  uint8_t low[4];         /* bytes 62 to 65 */
  uint8_t last[4];        /* bytes 66 to 69 */
  uint8_t close[4];       /* bytes 70 to 73 */
  uint8_t prev_close[4];  /* bytes 74 to 77 */
  uint8_t life_high[4];   /* bytes 78 to 81 */
  uint8_t life_low[4];    /* bytes 82 to 85 */
  uint8_t filler_4[4];    /* bytes 86 to 89 */
  uint8_t filler_2[4];    /* bytes 90 to 93 */
  uint8_t filler_3[4];    /* bytes 94 to 97 */
} IndexDetails;

/* any Index Details at all: every byte one the checker chooses */
static void any_index_details(IndexDetails *record) {
  for (size_t i = 0; i < 4; i++) { record->token[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->name[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->high[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->low[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->close[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->prev_close[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->life_high[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->life_low[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_3[i] = arbitrary(); }
}

/* Index Details to the wire: 98 bytes from at, returning where the next byte goes */
static size_t encode_index_details(const IndexDetails *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->token[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->name[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->high[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->low[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->close[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->prev_close[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->life_high[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->life_low[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_3[i]; }

  return at;
}

/* Index Details off the wire: 98 bytes from at, returning where the next byte lies */
static size_t decode_index_details(IndexDetails *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->token[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->name[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->high[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->low[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->close[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->prev_close[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->life_high[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->life_low[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_3[i] = wire[at++]; }

  return at;
}

/* what was read of Index Details is what was written, byte for byte */
static void equal_index_details(const IndexDetails *read, const IndexDetails *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->token[i] == written->token[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->name[i] == written->name[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open[i] == written->open[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->high[i] == written->high[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->low[i] == written->low[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last[i] == written->last[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->close[i] == written->close[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->prev_close[i] == written->prev_close[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->life_high[i] == written->life_high[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->life_low[i] == written->life_low[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
}

/* Index Details: written and read back, then read and written back */
static void check_index_details(void) {
  IndexDetails sent;
  IndexDetails got;
  uint8_t wire[98];
  uint8_t again[98];

  any_index_details(&sent);
  assert(encode_index_details(&sent, wire, 0) == 98);
  assert(decode_index_details(&got, wire, 0) == 98);
  equal_index_details(&got, &sent);

  for (size_t i = 0; i < 98; i++) { wire[i] = arbitrary(); }
  assert(decode_index_details(&got, wire, 0) == 98);
  assert(encode_index_details(&got, again, 0) == 98);
  for (size_t i = 0; i < 98; i++) { assert(again[i] == wire[i]); }
}

/* ---- Global Indices Message: 98 bytes ---------------------------------------- */

/* Carries the values of a global index */
typedef struct {
  IndexDetails index_details;  /* bytes 0 to 97 */
} GlobalIndicesMessage;

/* any Global Indices Message at all: every byte one the checker chooses */
static void any_global_indices_message(GlobalIndicesMessage *record) {
  any_index_details(&record->index_details);
}

/* Global Indices Message to the wire: 98 bytes from at, returning where the next byte goes */
static size_t encode_global_indices_message(const GlobalIndicesMessage *record, uint8_t *wire, size_t at) {
  at = encode_index_details(&record->index_details, wire, at);

  return at;
}

/* Global Indices Message off the wire: 98 bytes from at, returning where the next byte lies */
static size_t decode_global_indices_message(GlobalIndicesMessage *record, const uint8_t *wire, size_t at) {
  at = decode_index_details(&record->index_details, wire, at);

  return at;
}

/* what was read of Global Indices Message is what was written, byte for byte */
static void equal_global_indices_message(const GlobalIndicesMessage *read, const GlobalIndicesMessage *written) {
  equal_index_details(&read->index_details, &written->index_details);
}

/* Global Indices Message: written and read back, then read and written back */
static void check_global_indices_message(void) {
  GlobalIndicesMessage sent;
  GlobalIndicesMessage got;
  uint8_t wire[98];
  uint8_t again[98];

  any_global_indices_message(&sent);
  assert(encode_global_indices_message(&sent, wire, 0) == 98);
  assert(decode_global_indices_message(&got, wire, 0) == 98);
  equal_global_indices_message(&got, &sent);

  for (size_t i = 0; i < 98; i++) { wire[i] = arbitrary(); }
  assert(decode_global_indices_message(&got, wire, 0) == 98);
  assert(encode_global_indices_message(&got, again, 0) == 98);
  for (size_t i = 0; i < 98; i++) { assert(again[i] == wire[i]); }
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

/* ---- Collateral User Status Change Response Message: 6 bytes ----------------- */

/* Confirms the collateral status change */
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

/* Confirms the trade modify and cancel permission change */
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

/* Confirms that the unlock request was received */
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

/* Approves the unlock of a user address */
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

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_sign_off_request_out_message();
  check_st_market_status();
  check_st_ex_market_status();
  check_st_pl_market_status();
  check_existing_encryption_tail();
  check_new_encryption_tail();
  check_update_local_database_header_message();
  check_update_local_database_trailer_message();
  check_inner_header();
  check_download_header();
  check_contract_desc();
  check_control_message_to_trader_message();
  check_report_header_body();
  check_report_trailer_body();
  check_mkt_index();
  check_market_index_report_message();
  check_spread_report_header_body();
  check_index_details();
  check_global_indices_message();
  check_box_sign_on_request_out_message();
  check_contingency_broadcast_message();
  check_collateral_user_status_change_response_message();
  check_user_trade_modify_cancel_status_change_response_message();
  check_user_address_unlock_confirm_message();
  check_user_address_unlock_approve_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
