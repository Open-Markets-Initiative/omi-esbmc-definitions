// currenex/esp/CurrenexForex_Esp_v9.c
/*
 * Currenex Executable Streaming Prices
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

/* Currenex Itch Market Data Message Header */
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

/* A MP initiates a session by submitting a Logon message to Currenex */
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

/* Currenex or a MP can terminate a session by sending a Logout message */
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

/* To ensure session integrity, Currenex sends a heartbeat message every fifteen seconds */
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

/* ---- Instrument Info: 35 bytes ----------------------------------------------- */

/* Included in the InstrumentInfo message is the InstrumentType, a free form instrument definition, and the InstrumentIndex used to request quotes and manage price updates */
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

/* ---- Instrument Info Ack: 6 bytes -------------------------------------------- */

/* A MP should respond to each received InstrumentInfo message with an InstrumentInfoAck message */
typedef struct {
  uint8_t session_id[4];        /* bytes 0 to 3 */
  uint8_t instrument_index[2];  /* bytes 4 to 5 */
} InstrumentInfoAck;

/* any Instrument Info Ack at all: every byte one the checker chooses */
static void any_instrument_info_ack(InstrumentInfoAck *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
}

/* Instrument Info Ack to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_instrument_info_ack(const InstrumentInfoAck *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }

  return at;
}

/* Instrument Info Ack off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_instrument_info_ack(InstrumentInfoAck *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Info Ack is what was written, byte for byte */
static void equal_instrument_info_ack(const InstrumentInfoAck *read, const InstrumentInfoAck *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
}

/* Instrument Info Ack: written and read back, then read and written back */
static void check_instrument_info_ack(void) {
  InstrumentInfoAck sent;
  InstrumentInfoAck got;
  uint8_t wire[6];
  uint8_t again[6];

  any_instrument_info_ack(&sent);
  assert(encode_instrument_info_ack(&sent, wire, 0) == 6);
  assert(decode_instrument_info_ack(&got, wire, 0) == 6);
  equal_instrument_info_ack(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_info_ack(&got, wire, 0) == 6);
  assert(encode_instrument_info_ack(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Subscription Request: 8 bytes ------------------------------------------- */

/* Currenex will stream ESP messages to a MP once it receives a SubscriptionRequest message for the pair */
typedef struct {
  uint8_t session_id[4];        /* bytes 0 to 3 */
  uint8_t subscription_type;    /* byte 4 */
  uint8_t instrument_index[2];  /* bytes 5 to 6 */
  uint8_t subscribe_to_ticker;  /* byte 7 */
} SubscriptionRequest;

/* any Subscription Request at all: every byte one the checker chooses */
static void any_subscription_request(SubscriptionRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  record->subscription_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
  record->subscribe_to_ticker = arbitrary();
}

/* Subscription Request to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_subscription_request(const SubscriptionRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  wire[at++] = record->subscription_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }
  wire[at++] = record->subscribe_to_ticker;

  return at;
}

/* Subscription Request off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_subscription_request(SubscriptionRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  record->subscription_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }
  record->subscribe_to_ticker = wire[at++];

  return at;
}

/* what was read of Subscription Request is what was written, byte for byte */
static void equal_subscription_request(const SubscriptionRequest *read, const SubscriptionRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  assert(read->subscription_type == written->subscription_type);
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
  assert(read->subscribe_to_ticker == written->subscribe_to_ticker);
}

/* Subscription Request: written and read back, then read and written back */
static void check_subscription_request(void) {
  SubscriptionRequest sent;
  SubscriptionRequest got;
  uint8_t wire[8];
  uint8_t again[8];

  any_subscription_request(&sent);
  assert(encode_subscription_request(&sent, wire, 0) == 8);
  assert(decode_subscription_request(&got, wire, 0) == 8);
  equal_subscription_request(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_subscription_request(&got, wire, 0) == 8);
  assert(encode_subscription_request(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Subscription Reply: 57 bytes -------------------------------------------- */

/* Currenex responds to a SubscriptionRequest with a SubscriptionReply message */
typedef struct {
  uint8_t session_id[4];        /* bytes 0 to 3 */
  uint8_t instrument_index[2];  /* bytes 4 to 5 */
  uint8_t reply_type;           /* byte 6 */
  uint8_t reject_reason[50];    /* bytes 7 to 56 */
} SubscriptionReply;

/* any Subscription Reply at all: every byte one the checker chooses */
static void any_subscription_reply(SubscriptionReply *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
  record->reply_type = arbitrary();
  for (size_t i = 0; i < 50; i++) { record->reject_reason[i] = arbitrary(); }
}

/* Subscription Reply to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_subscription_reply(const SubscriptionReply *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }
  wire[at++] = record->reply_type;
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->reject_reason[i]; }

  return at;
}

/* Subscription Reply off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_subscription_reply(SubscriptionReply *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }
  record->reply_type = wire[at++];
  for (size_t i = 0; i < 50; i++) { record->reject_reason[i] = wire[at++]; }

  return at;
}

/* what was read of Subscription Reply is what was written, byte for byte */
static void equal_subscription_reply(const SubscriptionReply *read, const SubscriptionReply *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
  assert(read->reply_type == written->reply_type);
  for (size_t i = 0; i < 50; i++) { assert(read->reject_reason[i] == written->reject_reason[i]); }
}

/* Subscription Reply: written and read back, then read and written back */
static void check_subscription_reply(void) {
  SubscriptionReply sent;
  SubscriptionReply got;
  uint8_t wire[57];
  uint8_t again[57];

  any_subscription_reply(&sent);
  assert(encode_subscription_reply(&sent, wire, 0) == 57);
  assert(decode_subscription_reply(&got, wire, 0) == 57);
  equal_subscription_reply(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_subscription_reply(&got, wire, 0) == 57);
  assert(encode_subscription_reply(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Message: 32 bytes ------------------------------------------------- */

/* Price Message */
typedef struct {
  uint8_t instrument_index[2];  /* bytes 0 to 1 */
  uint8_t price_id[4];          /* bytes 2 to 5 */
  uint8_t side;                 /* byte 6 */
  uint8_t max_amount[8];        /* bytes 7 to 14 */
  uint8_t min_amount[8];        /* bytes 15 to 22 */
  uint8_t price[4];             /* bytes 23 to 26 */
  uint8_t attributed;           /* byte 27 */
  uint8_t price_provider[4];    /* bytes 28 to 31 */
} PriceMessage;

/* any Price Message at all: every byte one the checker chooses */
static void any_price_message(PriceMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->max_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->attributed = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_provider[i] = arbitrary(); }
}

/* Price Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_price_message(const PriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_amount[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_amount[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->attributed;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_provider[i]; }

  return at;
}

/* Price Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_price_message(PriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->max_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->attributed = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_provider[i] = wire[at++]; }

  return at;
}

/* what was read of Price Message is what was written, byte for byte */
static void equal_price_message(const PriceMessage *read, const PriceMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_id[i] == written->price_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->max_amount[i] == written->max_amount[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_amount[i] == written->min_amount[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->attributed == written->attributed);
  for (size_t i = 0; i < 4; i++) { assert(read->price_provider[i] == written->price_provider[i]); }
}

/* Price Message: written and read back, then read and written back */
static void check_price_message(void) {
  PriceMessage sent;
  PriceMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_price_message(&sent);
  assert(encode_price_message(&sent, wire, 0) == 32);
  assert(decode_price_message(&got, wire, 0) == 32);
  equal_price_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_price_message(&got, wire, 0) == 32);
  assert(encode_price_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Cancel Message: 6 bytes ------------------------------------------- */

/* Price Cancel */
typedef struct {
  uint8_t instrument_index[2];  /* bytes 0 to 1 */
  uint8_t price_id[4];          /* bytes 2 to 5 */
} PriceCancelMessage;

/* any Price Cancel Message at all: every byte one the checker chooses */
static void any_price_cancel_message(PriceCancelMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_id[i] = arbitrary(); }
}

/* Price Cancel Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_price_cancel_message(const PriceCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_id[i]; }

  return at;
}

/* Price Cancel Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_price_cancel_message(PriceCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_id[i] = wire[at++]; }

  return at;
}

/* what was read of Price Cancel Message is what was written, byte for byte */
static void equal_price_cancel_message(const PriceCancelMessage *read, const PriceCancelMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_id[i] == written->price_id[i]); }
}

/* Price Cancel Message: written and read back, then read and written back */
static void check_price_cancel_message(void) {
  PriceCancelMessage sent;
  PriceCancelMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_price_cancel_message(&sent);
  assert(encode_price_cancel_message(&sent, wire, 0) == 6);
  assert(decode_price_cancel_message(&got, wire, 0) == 6);
  equal_price_cancel_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_price_cancel_message(&got, wire, 0) == 6);
  assert(encode_price_cancel_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Ticker Message: 15 bytes ------------------------------------------ */

/* A MP can subscribe to TradeTicker messages by setting SubscribeToTicker=0 in the SubscriptionRequest message */
typedef struct {
  uint8_t instrument_index[2];  /* bytes 0 to 1 */
  uint8_t rate[4];              /* bytes 2 to 5 */
  uint8_t ticker_type;          /* byte 6 */
  uint8_t transact_time[8];     /* bytes 7 to 14 */
} TradeTickerMessage;

/* any Trade Ticker Message at all: every byte one the checker chooses */
static void any_trade_ticker_message(TradeTickerMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->rate[i] = arbitrary(); }
  record->ticker_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Trade Ticker Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_trade_ticker_message(const TradeTickerMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->rate[i]; }
  wire[at++] = record->ticker_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Trade Ticker Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_trade_ticker_message(TradeTickerMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->rate[i] = wire[at++]; }
  record->ticker_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Ticker Message is what was written, byte for byte */
static void equal_trade_ticker_message(const TradeTickerMessage *read, const TradeTickerMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->rate[i] == written->rate[i]); }
  assert(read->ticker_type == written->ticker_type);
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Trade Ticker Message: written and read back, then read and written back */
static void check_trade_ticker_message(void) {
  TradeTickerMessage sent;
  TradeTickerMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_trade_ticker_message(&sent);
  assert(encode_trade_ticker_message(&sent, wire, 0) == 15);
  assert(decode_trade_ticker_message(&got, wire, 0) == 15);
  equal_trade_ticker_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_ticker_message(&got, wire, 0) == 15);
  assert(encode_trade_ticker_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reject Message: 55 bytes ------------------------------------------------ */

/* Included in the InstrumentInfo message is the InstrumentType, a free form instrument definition, and the InstrumentIndex used to request quotes and manage price updates */
typedef struct {
  uint8_t session_id[4];      /* bytes 0 to 3 */
  uint8_t reject_msg_type;    /* byte 4 */
  uint8_t reject_reason[50];  /* bytes 5 to 54 */
} RejectMessage;

/* any Reject Message at all: every byte one the checker chooses */
static void any_reject_message(RejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  record->reject_msg_type = arbitrary();
  for (size_t i = 0; i < 50; i++) { record->reject_reason[i] = arbitrary(); }
}

/* Reject Message to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_reject_message(const RejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  wire[at++] = record->reject_msg_type;
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->reject_reason[i]; }

  return at;
}

/* Reject Message off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_reject_message(RejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  record->reject_msg_type = wire[at++];
  for (size_t i = 0; i < 50; i++) { record->reject_reason[i] = wire[at++]; }

  return at;
}

/* what was read of Reject Message is what was written, byte for byte */
static void equal_reject_message(const RejectMessage *read, const RejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  assert(read->reject_msg_type == written->reject_msg_type);
  for (size_t i = 0; i < 50; i++) { assert(read->reject_reason[i] == written->reject_reason[i]); }
}

/* Reject Message: written and read back, then read and written back */
static void check_reject_message(void) {
  RejectMessage sent;
  RejectMessage got;
  uint8_t wire[55];
  uint8_t again[55];

  any_reject_message(&sent);
  assert(encode_reject_message(&sent, wire, 0) == 55);
  assert(decode_reject_message(&got, wire, 0) == 55);
  equal_reject_message(&got, &sent);

  for (size_t i = 0; i < 55; i++) { wire[i] = arbitrary(); }
  assert(decode_reject_message(&got, wire, 0) == 55);
  assert(encode_reject_message(&got, again, 0) == 55);
  for (size_t i = 0; i < 55; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_logon();
  check_logout();
  check_heartbeat();
  check_instrument_info();
  check_instrument_info_ack();
  check_subscription_request();
  check_subscription_reply();
  check_price_message();
  check_price_cancel_message();
  check_trade_ticker_message();
  check_reject_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
