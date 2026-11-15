// currenex/orderservice/CurrenexForex_OrderService_v26.c
/*
 * Currenex Order Service
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

/* ---- Message Header: 9 bytes ------------------------------------------------- */

/* Currenex Market Data Message Header */
typedef struct {
  uint8_t sequence_number[4];  /* bytes 0 to 3 */
  uint8_t timestamp[4];        /* bytes 4 to 7 */
  uint8_t message_type;        /* byte 8 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[9];
  uint8_t again[9];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 9);
  assert(decode_message_header(&got, wire, 0) == 9);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 9);
  assert(encode_message_header(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon: 44 bytes --------------------------------------------------------- */

/* Client initiates a session by submitting a Logon message */
typedef struct {
  uint8_t user_id[20];    /* bytes 0 to 19 */
  uint8_t password[20];   /* bytes 20 to 39 */
  uint8_t session_id[4];  /* bytes 40 to 43 */
} Logon;

/* any Logon at all: every byte one the checker chooses */
static void any_logon(Logon *record) {
  for (size_t i = 0; i < 20; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
}

/* Logon to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_logon(const Logon *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }

  return at;
}

/* Logon off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_logon(Logon *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }

  return at;
}

/* what was read of Logon is what was written, byte for byte */
static void equal_logon(const Logon *read, const Logon *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
}

/* Logon: written and read back, then read and written back */
static void check_logon(void) {
  Logon sent;
  Logon got;
  uint8_t wire[44];
  uint8_t again[44];

  any_logon(&sent);
  assert(encode_logon(&sent, wire, 0) == 44);
  assert(decode_logon(&got, wire, 0) == 44);
  equal_logon(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_logon(&got, wire, 0) == 44);
  assert(encode_logon(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout: 27 bytes -------------------------------------------------------- */

/* Terminate a session by sending a Logout message */
typedef struct {
  uint8_t user_id[20];    /* bytes 0 to 19 */
  uint8_t session_id[4];  /* bytes 20 to 23 */
  uint8_t reason[3];      /* bytes 24 to 26 */
} Logout;

/* any Logout at all: every byte one the checker chooses */
static void any_logout(Logout *record) {
  for (size_t i = 0; i < 20; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->reason[i] = arbitrary(); }
}

/* Logout to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_logout(const Logout *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Logout off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_logout(Logout *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Logout is what was written, byte for byte */
static void equal_logout(const Logout *read, const Logout *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->reason[i] == written->reason[i]); }
}

/* Logout: written and read back, then read and written back */
static void check_logout(void) {
  Logout sent;
  Logout got;
  uint8_t wire[27];
  uint8_t again[27];

  any_logout(&sent);
  assert(encode_logout(&sent, wire, 0) == 27);
  assert(decode_logout(&got, wire, 0) == 27);
  equal_logout(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_logout(&got, wire, 0) == 27);
  assert(encode_logout(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heartbeat: 4 bytes ------------------------------------------------------ */

/* Keep-alive ping sent every three seconds; client must respond */
typedef struct {
  uint8_t session_id[4];  /* bytes 0 to 3 */
} Heartbeat;

/* any Heartbeat at all: every byte one the checker chooses */
static void any_heartbeat(Heartbeat *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
}

/* Heartbeat to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat(const Heartbeat *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }

  return at;
}

/* Heartbeat off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat(Heartbeat *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat is what was written, byte for byte */
static void equal_heartbeat(const Heartbeat *read, const Heartbeat *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
}

/* Heartbeat: written and read back, then read and written back */
static void check_heartbeat(void) {
  Heartbeat sent;
  Heartbeat got;
  uint8_t wire[4];
  uint8_t again[4];

  any_heartbeat(&sent);
  assert(encode_heartbeat(&sent, wire, 0) == 4);
  assert(decode_heartbeat(&got, wire, 0) == 4);
  equal_heartbeat(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_heartbeat(&got, wire, 0) == 4);
  assert(encode_heartbeat(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Info Request: 4 bytes ---------------------------------------- */

/* Request list of supported instruments */
typedef struct {
  uint8_t session_id[4];  /* bytes 0 to 3 */
} InstrumentInfoRequest;

/* any Instrument Info Request at all: every byte one the checker chooses */
static void any_instrument_info_request(InstrumentInfoRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
}

/* Instrument Info Request to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_instrument_info_request(const InstrumentInfoRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }

  return at;
}

/* Instrument Info Request off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_instrument_info_request(InstrumentInfoRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Info Request is what was written, byte for byte */
static void equal_instrument_info_request(const InstrumentInfoRequest *read, const InstrumentInfoRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
}

/* Instrument Info Request: written and read back, then read and written back */
static void check_instrument_info_request(void) {
  InstrumentInfoRequest sent;
  InstrumentInfoRequest got;
  uint8_t wire[4];
  uint8_t again[4];

  any_instrument_info_request(&sent);
  assert(encode_instrument_info_request(&sent, wire, 0) == 4);
  assert(decode_instrument_info_request(&got, wire, 0) == 4);
  equal_instrument_info_request(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_info_request(&got, wire, 0) == 4);
  assert(encode_instrument_info_request(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Info: 35 bytes ----------------------------------------------- */

/* Definition of a currency or metal instrument */
typedef struct {
  uint8_t session_id[4];        /* bytes 0 to 3 */
  uint8_t instrument_index[2];  /* bytes 4 to 5 */
  uint8_t instrument_type;      /* byte 6 */
  uint8_t instrument_id[20];    /* bytes 7 to 26 */
  uint8_t settlement_date[8];   /* bytes 27 to 34 */
} InstrumentInfo;

/* any Instrument Info at all: every byte one the checker chooses */
static void any_instrument_info(InstrumentInfo *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_date[i] = arbitrary(); }
}

/* Instrument Info to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_instrument_info(const InstrumentInfo *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_date[i]; }

  return at;
}

/* Instrument Info off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_instrument_info(InstrumentInfo *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_date[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Info is what was written, byte for byte */
static void equal_instrument_info(const InstrumentInfo *read, const InstrumentInfo *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 20; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_date[i] == written->settlement_date[i]); }
}

/* Instrument Info: written and read back, then read and written back */
static void check_instrument_info(void) {
  InstrumentInfo sent;
  InstrumentInfo got;
  uint8_t wire[35];
  uint8_t again[35];

  any_instrument_info(&sent);
  assert(encode_instrument_info(&sent, wire, 0) == 35);
  assert(decode_instrument_info(&got, wire, 0) == 35);
  equal_instrument_info(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_info(&got, wire, 0) == 35);
  assert(encode_instrument_info(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Request: 37 bytes --------------------------------------------- */

/* Submit a new order request */
typedef struct {
  uint8_t cl_order_id[4];       /* bytes 0 to 3 */
  uint8_t order_type;           /* byte 4 */
  uint8_t instrument_index[2];  /* bytes 5 to 6 */
  uint8_t side;                 /* byte 7 */
  uint8_t order_amt[8];         /* bytes 8 to 15 */
  uint8_t min_amt[8];           /* bytes 16 to 23 */
  uint8_t price[4];             /* bytes 24 to 27 */
  uint8_t show_amt[8];          /* bytes 28 to 35 */
  uint8_t expire_type;          /* byte 36 */
} NewOrderRequest;

/* any New Order Request at all: every byte one the checker chooses */
static void any_new_order_request(NewOrderRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->cl_order_id[i] = arbitrary(); }
  record->order_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_amt[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_amt[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->show_amt[i] = arbitrary(); }
  record->expire_type = arbitrary();
}

/* New Order Request to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_new_order_request(const NewOrderRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cl_order_id[i]; }
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_amt[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_amt[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->show_amt[i]; }
  wire[at++] = record->expire_type;

  return at;
}

/* New Order Request off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_new_order_request(NewOrderRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->cl_order_id[i] = wire[at++]; }
  record->order_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_amt[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_amt[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->show_amt[i] = wire[at++]; }
  record->expire_type = wire[at++];

  return at;
}

/* what was read of New Order Request is what was written, byte for byte */
static void equal_new_order_request(const NewOrderRequest *read, const NewOrderRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->cl_order_id[i] == written->cl_order_id[i]); }
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_amt[i] == written->order_amt[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_amt[i] == written->min_amt[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->show_amt[i] == written->show_amt[i]); }
  assert(read->expire_type == written->expire_type);
}

/* New Order Request: written and read back, then read and written back */
static void check_new_order_request(void) {
  NewOrderRequest sent;
  NewOrderRequest got;
  uint8_t wire[37];
  uint8_t again[37];

  any_new_order_request(&sent);
  assert(encode_new_order_request(&sent, wire, 0) == 37);
  assert(decode_new_order_request(&got, wire, 0) == 37);
  equal_new_order_request(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_request(&got, wire, 0) == 37);
  assert(encode_new_order_request(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Ack: 15 bytes ------------------------------------------------- */

/* Acknowledge new order */
typedef struct {
  uint8_t cl_order_id[4];  /* bytes 0 to 3 */
  uint8_t order_id[8];     /* bytes 4 to 11 */
  uint8_t ack_status;      /* byte 12 */
  uint8_t error_code[2];   /* bytes 13 to 14 */
} NewOrderAck;

/* any New Order Ack at all: every byte one the checker chooses */
static void any_new_order_ack(NewOrderAck *record) {
  for (size_t i = 0; i < 4; i++) { record->cl_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->ack_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = arbitrary(); }
}

/* New Order Ack to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_new_order_ack(const NewOrderAck *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cl_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->ack_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_code[i]; }

  return at;
}

/* New Order Ack off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_new_order_ack(NewOrderAck *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->cl_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->ack_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = wire[at++]; }

  return at;
}

/* what was read of New Order Ack is what was written, byte for byte */
static void equal_new_order_ack(const NewOrderAck *read, const NewOrderAck *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->cl_order_id[i] == written->cl_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->ack_status == written->ack_status);
  for (size_t i = 0; i < 2; i++) { assert(read->error_code[i] == written->error_code[i]); }
}

/* New Order Ack: written and read back, then read and written back */
static void check_new_order_ack(void) {
  NewOrderAck sent;
  NewOrderAck got;
  uint8_t wire[15];
  uint8_t again[15];

  any_new_order_ack(&sent);
  assert(encode_new_order_ack(&sent, wire, 0) == 15);
  assert(decode_new_order_ack(&got, wire, 0) == 15);
  equal_new_order_ack(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_ack(&got, wire, 0) == 15);
  assert(encode_new_order_ack(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Request: 10 bytes ------------------------------------------ */

/* Request cancellation of an order */
typedef struct {
  uint8_t new_cl_order_id[4];   /* bytes 0 to 3 */
  uint8_t prev_cl_order_id[4];  /* bytes 4 to 7 */
  uint8_t instrument_index[2];  /* bytes 8 to 9 */
} OrderCancelRequest;

/* any Order Cancel Request at all: every byte one the checker chooses */
static void any_order_cancel_request(OrderCancelRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->new_cl_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->prev_cl_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
}

/* Order Cancel Request to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_request(const OrderCancelRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_cl_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->prev_cl_order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }

  return at;
}

/* Order Cancel Request off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_request(OrderCancelRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->new_cl_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->prev_cl_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Request is what was written, byte for byte */
static void equal_order_cancel_request(const OrderCancelRequest *read, const OrderCancelRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->new_cl_order_id[i] == written->new_cl_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->prev_cl_order_id[i] == written->prev_cl_order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
}

/* Order Cancel Request: written and read back, then read and written back */
static void check_order_cancel_request(void) {
  OrderCancelRequest sent;
  OrderCancelRequest got;
  uint8_t wire[10];
  uint8_t again[10];

  any_order_cancel_request(&sent);
  assert(encode_order_cancel_request(&sent, wire, 0) == 10);
  assert(decode_order_cancel_request(&got, wire, 0) == 10);
  equal_order_cancel_request(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_request(&got, wire, 0) == 10);
  assert(encode_order_cancel_request(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Reject: 10 bytes ------------------------------------------- */

/* Rejection of Order Cancel Request */
typedef struct {
  uint8_t new_cl_order_id[4];   /* bytes 0 to 3 */
  uint8_t prev_cl_order_id[4];  /* bytes 4 to 7 */
  uint8_t error_code[2];        /* bytes 8 to 9 */
} OrderCancelReject;

/* any Order Cancel Reject at all: every byte one the checker chooses */
static void any_order_cancel_reject(OrderCancelReject *record) {
  for (size_t i = 0; i < 4; i++) { record->new_cl_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->prev_cl_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = arbitrary(); }
}

/* Order Cancel Reject to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_reject(const OrderCancelReject *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_cl_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->prev_cl_order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_code[i]; }

  return at;
}

/* Order Cancel Reject off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_reject(OrderCancelReject *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->new_cl_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->prev_cl_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Reject is what was written, byte for byte */
static void equal_order_cancel_reject(const OrderCancelReject *read, const OrderCancelReject *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->new_cl_order_id[i] == written->new_cl_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->prev_cl_order_id[i] == written->prev_cl_order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->error_code[i] == written->error_code[i]); }
}

/* Order Cancel Reject: written and read back, then read and written back */
static void check_order_cancel_reject(void) {
  OrderCancelReject sent;
  OrderCancelReject got;
  uint8_t wire[10];
  uint8_t again[10];

  any_order_cancel_reject(&sent);
  assert(encode_order_cancel_reject(&sent, wire, 0) == 10);
  assert(decode_order_cancel_reject(&got, wire, 0) == 10);
  equal_order_cancel_reject(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_reject(&got, wire, 0) == 10);
  assert(encode_order_cancel_reject(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replace Or Cancel Request: 22 bytes ------------------------------- */

/* Replace or cancel an order */
typedef struct {
  uint8_t new_cl_order_id[4];   /* bytes 0 to 3 */
  uint8_t orig_cl_order_id[4];  /* bytes 4 to 7 */
  uint8_t order_amt[8];         /* bytes 8 to 15 */
  uint8_t price[4];             /* bytes 16 to 19 */
  uint8_t instrument_index[2];  /* bytes 20 to 21 */
} OrderReplaceOrCancelRequest;

/* any Order Replace Or Cancel Request at all: every byte one the checker chooses */
static void any_order_replace_or_cancel_request(OrderReplaceOrCancelRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->new_cl_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orig_cl_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_amt[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
}

/* Order Replace Or Cancel Request to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_order_replace_or_cancel_request(const OrderReplaceOrCancelRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_cl_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orig_cl_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_amt[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }

  return at;
}

/* Order Replace Or Cancel Request off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_order_replace_or_cancel_request(OrderReplaceOrCancelRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->new_cl_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orig_cl_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_amt[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }

  return at;
}

/* what was read of Order Replace Or Cancel Request is what was written, byte for byte */
static void equal_order_replace_or_cancel_request(const OrderReplaceOrCancelRequest *read, const OrderReplaceOrCancelRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->new_cl_order_id[i] == written->new_cl_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orig_cl_order_id[i] == written->orig_cl_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_amt[i] == written->order_amt[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
}

/* Order Replace Or Cancel Request: written and read back, then read and written back */
static void check_order_replace_or_cancel_request(void) {
  OrderReplaceOrCancelRequest sent;
  OrderReplaceOrCancelRequest got;
  uint8_t wire[22];
  uint8_t again[22];

  any_order_replace_or_cancel_request(&sent);
  assert(encode_order_replace_or_cancel_request(&sent, wire, 0) == 22);
  assert(decode_order_replace_or_cancel_request(&got, wire, 0) == 22);
  equal_order_replace_or_cancel_request(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replace_or_cancel_request(&got, wire, 0) == 22);
  assert(encode_order_replace_or_cancel_request(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replace Or Cancel Ack: 11 bytes ----------------------------------- */

/* Acknowledge replace/cancel */
typedef struct {
  uint8_t new_cl_order_id[4];   /* bytes 0 to 3 */
  uint8_t prev_cl_order_id[4];  /* bytes 4 to 7 */
  uint8_t status;               /* byte 8 */
  uint8_t error_code[2];        /* bytes 9 to 10 */
} OrderReplaceOrCancelAck;

/* any Order Replace Or Cancel Ack at all: every byte one the checker chooses */
static void any_order_replace_or_cancel_ack(OrderReplaceOrCancelAck *record) {
  for (size_t i = 0; i < 4; i++) { record->new_cl_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->prev_cl_order_id[i] = arbitrary(); }
  record->status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = arbitrary(); }
}

/* Order Replace Or Cancel Ack to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_order_replace_or_cancel_ack(const OrderReplaceOrCancelAck *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_cl_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->prev_cl_order_id[i]; }
  wire[at++] = record->status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_code[i]; }

  return at;
}

/* Order Replace Or Cancel Ack off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_order_replace_or_cancel_ack(OrderReplaceOrCancelAck *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->new_cl_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->prev_cl_order_id[i] = wire[at++]; }
  record->status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = wire[at++]; }

  return at;
}

/* what was read of Order Replace Or Cancel Ack is what was written, byte for byte */
static void equal_order_replace_or_cancel_ack(const OrderReplaceOrCancelAck *read, const OrderReplaceOrCancelAck *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->new_cl_order_id[i] == written->new_cl_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->prev_cl_order_id[i] == written->prev_cl_order_id[i]); }
  assert(read->status == written->status);
  for (size_t i = 0; i < 2; i++) { assert(read->error_code[i] == written->error_code[i]); }
}

/* Order Replace Or Cancel Ack: written and read back, then read and written back */
static void check_order_replace_or_cancel_ack(void) {
  OrderReplaceOrCancelAck sent;
  OrderReplaceOrCancelAck got;
  uint8_t wire[11];
  uint8_t again[11];

  any_order_replace_or_cancel_ack(&sent);
  assert(encode_order_replace_or_cancel_ack(&sent, wire, 0) == 11);
  assert(decode_order_replace_or_cancel_ack(&got, wire, 0) == 11);
  equal_order_replace_or_cancel_ack(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replace_or_cancel_ack(&got, wire, 0) == 11);
  assert(encode_order_replace_or_cancel_ack(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Canceled Or Expired: 15 bytes ------------------------------------- */

/* Unsolicited cancellation/expiry notice */
typedef struct {
  uint8_t cl_order_id[4];  /* bytes 0 to 3 */
  uint8_t order_id[8];     /* bytes 4 to 11 */
  uint8_t status;          /* byte 12 */
  uint8_t type[2];         /* bytes 13 to 14 */
} OrderCanceledOrExpired;

/* any Order Canceled Or Expired at all: every byte one the checker chooses */
static void any_order_canceled_or_expired(OrderCanceledOrExpired *record) {
  for (size_t i = 0; i < 4; i++) { record->cl_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->type[i] = arbitrary(); }
}

/* Order Canceled Or Expired to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_order_canceled_or_expired(const OrderCanceledOrExpired *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cl_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->type[i]; }

  return at;
}

/* Order Canceled Or Expired off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_order_canceled_or_expired(OrderCanceledOrExpired *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->cl_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->type[i] = wire[at++]; }

  return at;
}

/* what was read of Order Canceled Or Expired is what was written, byte for byte */
static void equal_order_canceled_or_expired(const OrderCanceledOrExpired *read, const OrderCanceledOrExpired *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->cl_order_id[i] == written->cl_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->status == written->status);
  for (size_t i = 0; i < 2; i++) { assert(read->type[i] == written->type[i]); }
}

/* Order Canceled Or Expired: written and read back, then read and written back */
static void check_order_canceled_or_expired(void) {
  OrderCanceledOrExpired sent;
  OrderCanceledOrExpired got;
  uint8_t wire[15];
  uint8_t again[15];

  any_order_canceled_or_expired(&sent);
  assert(encode_order_canceled_or_expired(&sent, wire, 0) == 15);
  assert(decode_order_canceled_or_expired(&got, wire, 0) == 15);
  equal_order_canceled_or_expired(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_order_canceled_or_expired(&got, wire, 0) == 15);
  assert(encode_order_canceled_or_expired(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade: 85 bytes --------------------------------------------------------- */

/* Trade execution notification */
typedef struct {
  uint8_t cl_order_id[4];       /* bytes 0 to 3 */
  uint8_t order_id[8];          /* bytes 4 to 11 */
  uint8_t instrument_index[2];  /* bytes 12 to 13 */
  uint8_t side;                 /* byte 14 */
  uint8_t fill_amt[8];          /* bytes 15 to 22 */
  uint8_t fill_rate[4];         /* bytes 23 to 26 */
  uint8_t exec_broker[4];       /* bytes 27 to 30 */
  uint8_t execution_id[20];     /* bytes 31 to 50 */
  uint8_t exec_type;            /* byte 51 */
  uint8_t settle_date[8];       /* bytes 52 to 59 */
  uint8_t trade_date[8];        /* bytes 60 to 67 */
  uint8_t transact_time[8];     /* bytes 68 to 75 */
  uint8_t leaves_amt[8];        /* bytes 76 to 83 */
  uint8_t aggressor_flag;       /* byte 84 */
} Trade;

/* any Trade at all: every byte one the checker chooses */
static void any_trade(Trade *record) {
  for (size_t i = 0; i < 4; i++) { record->cl_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->fill_amt[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->fill_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->exec_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->execution_id[i] = arbitrary(); }
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->settle_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leaves_amt[i] = arbitrary(); }
  record->aggressor_flag = arbitrary();
}

/* Trade to the wire: 85 bytes from at, returning where the next byte goes */
static size_t encode_trade(const Trade *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cl_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fill_amt[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fill_rate[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exec_broker[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settle_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leaves_amt[i]; }
  wire[at++] = record->aggressor_flag;

  return at;
}

/* Trade off the wire: 85 bytes from at, returning where the next byte lies */
static size_t decode_trade(Trade *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->cl_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->fill_amt[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->fill_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->exec_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->execution_id[i] = wire[at++]; }
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->settle_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leaves_amt[i] = wire[at++]; }
  record->aggressor_flag = wire[at++];

  return at;
}

/* what was read of Trade is what was written, byte for byte */
static void equal_trade(const Trade *read, const Trade *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->cl_order_id[i] == written->cl_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->fill_amt[i] == written->fill_amt[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->fill_rate[i] == written->fill_rate[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->exec_broker[i] == written->exec_broker[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 8; i++) { assert(read->settle_date[i] == written->settle_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leaves_amt[i] == written->leaves_amt[i]); }
  assert(read->aggressor_flag == written->aggressor_flag);
}

/* Trade: written and read back, then read and written back */
static void check_trade(void) {
  Trade sent;
  Trade got;
  uint8_t wire[85];
  uint8_t again[85];

  any_trade(&sent);
  assert(encode_trade(&sent, wire, 0) == 85);
  assert(decode_trade(&got, wire, 0) == 85);
  equal_trade(&got, &sent);

  for (size_t i = 0; i < 85; i++) { wire[i] = arbitrary(); }
  assert(decode_trade(&got, wire, 0) == 85);
  assert(encode_trade(&got, again, 0) == 85);
  for (size_t i = 0; i < 85; i++) { assert(again[i] == wire[i]); }
}

/* ---- Pending Fill: 33 bytes -------------------------------------------------- */

/* Notification of expected fill */
typedef struct {
  uint8_t cl_order_id[4];    /* bytes 0 to 3 */
  uint8_t order_id[8];       /* bytes 4 to 11 */
  uint8_t trade_link_id[4];  /* bytes 12 to 15 */
  uint8_t fill_amt[8];       /* bytes 16 to 23 */
  uint8_t fill_rate[4];      /* bytes 24 to 27 */
  uint8_t aggressor_flag;    /* byte 28 */
  uint8_t exec_broker[4];    /* bytes 29 to 32 */
} PendingFill;

/* any Pending Fill at all: every byte one the checker chooses */
static void any_pending_fill(PendingFill *record) {
  for (size_t i = 0; i < 4; i++) { record->cl_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_link_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fill_amt[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->fill_rate[i] = arbitrary(); }
  record->aggressor_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->exec_broker[i] = arbitrary(); }
}

/* Pending Fill to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_pending_fill(const PendingFill *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cl_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_link_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fill_amt[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fill_rate[i]; }
  wire[at++] = record->aggressor_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exec_broker[i]; }

  return at;
}

/* Pending Fill off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_pending_fill(PendingFill *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->cl_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_link_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fill_amt[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->fill_rate[i] = wire[at++]; }
  record->aggressor_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->exec_broker[i] = wire[at++]; }

  return at;
}

/* what was read of Pending Fill is what was written, byte for byte */
static void equal_pending_fill(const PendingFill *read, const PendingFill *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->cl_order_id[i] == written->cl_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_link_id[i] == written->trade_link_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fill_amt[i] == written->fill_amt[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->fill_rate[i] == written->fill_rate[i]); }
  assert(read->aggressor_flag == written->aggressor_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->exec_broker[i] == written->exec_broker[i]); }
}

/* Pending Fill: written and read back, then read and written back */
static void check_pending_fill(void) {
  PendingFill sent;
  PendingFill got;
  uint8_t wire[33];
  uint8_t again[33];

  any_pending_fill(&sent);
  assert(encode_pending_fill(&sent, wire, 0) == 33);
  assert(decode_pending_fill(&got, wire, 0) == 33);
  equal_pending_fill(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_pending_fill(&got, wire, 0) == 33);
  assert(encode_pending_fill(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Pending Fill Cancel: 16 bytes ------------------------------------------- */

/* Notification of pending fill cancellation */
typedef struct {
  uint8_t cl_order_id[4];    /* bytes 0 to 3 */
  uint8_t order_id[8];       /* bytes 4 to 11 */
  uint8_t trade_link_id[4];  /* bytes 12 to 15 */
} PendingFillCancel;

/* any Pending Fill Cancel at all: every byte one the checker chooses */
static void any_pending_fill_cancel(PendingFillCancel *record) {
  for (size_t i = 0; i < 4; i++) { record->cl_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_link_id[i] = arbitrary(); }
}

/* Pending Fill Cancel to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_pending_fill_cancel(const PendingFillCancel *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cl_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_link_id[i]; }

  return at;
}

/* Pending Fill Cancel off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_pending_fill_cancel(PendingFillCancel *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->cl_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_link_id[i] = wire[at++]; }

  return at;
}

/* what was read of Pending Fill Cancel is what was written, byte for byte */
static void equal_pending_fill_cancel(const PendingFillCancel *read, const PendingFillCancel *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->cl_order_id[i] == written->cl_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_link_id[i] == written->trade_link_id[i]); }
}

/* Pending Fill Cancel: written and read back, then read and written back */
static void check_pending_fill_cancel(void) {
  PendingFillCancel sent;
  PendingFillCancel got;
  uint8_t wire[16];
  uint8_t again[16];

  any_pending_fill_cancel(&sent);
  assert(encode_pending_fill_cancel(&sent, wire, 0) == 16);
  assert(decode_pending_fill_cancel(&got, wire, 0) == 16);
  equal_pending_fill_cancel(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_pending_fill_cancel(&got, wire, 0) == 16);
  assert(encode_pending_fill_cancel(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Pending: 34 bytes ------------------------------------------------- */

/* Trade notification linked to pending fill */
typedef struct {
  uint8_t exec_type;         /* byte 0 */
  uint8_t settle_date[8];    /* bytes 1 to 8 */
  uint8_t trade_date[8];     /* bytes 9 to 16 */
  uint8_t transact_time[8];  /* bytes 17 to 24 */
  uint8_t leaves_amt[8];     /* bytes 25 to 32 */
  uint8_t aggressor_flag;    /* byte 33 */
} TradePending;

/* any Trade Pending at all: every byte one the checker chooses */
static void any_trade_pending(TradePending *record) {
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->settle_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leaves_amt[i] = arbitrary(); }
  record->aggressor_flag = arbitrary();
}

/* Trade Pending to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_trade_pending(const TradePending *record, uint8_t *wire, size_t at) {
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settle_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leaves_amt[i]; }
  wire[at++] = record->aggressor_flag;

  return at;
}

/* Trade Pending off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_trade_pending(TradePending *record, const uint8_t *wire, size_t at) {
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->settle_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leaves_amt[i] = wire[at++]; }
  record->aggressor_flag = wire[at++];

  return at;
}

/* what was read of Trade Pending is what was written, byte for byte */
static void equal_trade_pending(const TradePending *read, const TradePending *written) {
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 8; i++) { assert(read->settle_date[i] == written->settle_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leaves_amt[i] == written->leaves_amt[i]); }
  assert(read->aggressor_flag == written->aggressor_flag);
}

/* Trade Pending: written and read back, then read and written back */
static void check_trade_pending(void) {
  TradePending sent;
  TradePending got;
  uint8_t wire[34];
  uint8_t again[34];

  any_trade_pending(&sent);
  assert(encode_trade_pending(&sent, wire, 0) == 34);
  assert(decode_trade_pending(&got, wire, 0) == 34);
  equal_trade_pending(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_pending(&got, wire, 0) == 34);
  assert(encode_trade_pending(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Resend Request: 4 bytes ------------------------------------------------- */

/* Request retransmission of missed messages */
typedef struct {
  uint8_t begin_seq_no[4];  /* bytes 0 to 3 */
} ResendRequest;

/* any Resend Request at all: every byte one the checker chooses */
static void any_resend_request(ResendRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_no[i] = arbitrary(); }
}

/* Resend Request to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_resend_request(const ResendRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->begin_seq_no[i]; }

  return at;
}

/* Resend Request off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_resend_request(ResendRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Resend Request is what was written, byte for byte */
static void equal_resend_request(const ResendRequest *read, const ResendRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->begin_seq_no[i] == written->begin_seq_no[i]); }
}

/* Resend Request: written and read back, then read and written back */
static void check_resend_request(void) {
  ResendRequest sent;
  ResendRequest got;
  uint8_t wire[4];
  uint8_t again[4];

  any_resend_request(&sent);
  assert(encode_resend_request(&sent, wire, 0) == 4);
  assert(decode_resend_request(&got, wire, 0) == 4);
  equal_resend_request(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_resend_request(&got, wire, 0) == 4);
  assert(encode_resend_request(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Gap Fill: 5 bytes ------------------------------------------------------- */

/* Skip non-resendable or unavailable messages */
typedef struct {
  uint8_t new_seq_no[4];  /* bytes 0 to 3 */
  uint8_t reason_code;    /* byte 4 */
} GapFill;

/* any Gap Fill at all: every byte one the checker chooses */
static void any_gap_fill(GapFill *record) {
  for (size_t i = 0; i < 4; i++) { record->new_seq_no[i] = arbitrary(); }
  record->reason_code = arbitrary();
}

/* Gap Fill to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_gap_fill(const GapFill *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_seq_no[i]; }
  wire[at++] = record->reason_code;

  return at;
}

/* Gap Fill off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_gap_fill(GapFill *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->new_seq_no[i] = wire[at++]; }
  record->reason_code = wire[at++];

  return at;
}

/* what was read of Gap Fill is what was written, byte for byte */
static void equal_gap_fill(const GapFill *read, const GapFill *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->new_seq_no[i] == written->new_seq_no[i]); }
  assert(read->reason_code == written->reason_code);
}

/* Gap Fill: written and read back, then read and written back */
static void check_gap_fill(void) {
  GapFill sent;
  GapFill got;
  uint8_t wire[5];
  uint8_t again[5];

  any_gap_fill(&sent);
  assert(encode_gap_fill(&sent, wire, 0) == 5);
  assert(decode_gap_fill(&got, wire, 0) == 5);
  equal_gap_fill(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_gap_fill(&got, wire, 0) == 5);
  assert(encode_gap_fill(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_logon();
  check_logout();
  check_heartbeat();
  check_instrument_info_request();
  check_instrument_info();
  check_new_order_request();
  check_new_order_ack();
  check_order_cancel_request();
  check_order_cancel_reject();
  check_order_replace_or_cancel_request();
  check_order_replace_or_cancel_ack();
  check_order_canceled_or_expired();
  check_trade();
  check_pending_fill();
  check_pending_fill_cancel();
  check_trade_pending();
  check_resend_request();
  check_gap_fill();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
