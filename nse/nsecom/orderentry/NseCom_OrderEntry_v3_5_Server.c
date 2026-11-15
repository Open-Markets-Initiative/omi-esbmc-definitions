// nse/nsecom/orderentry/NseCom_OrderEntry_v3_5_Server.c
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
 *   - a field read in bits
 *   - a Composite rule
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

/* ---- Open Order Report Message: 68 bytes ------------------------------------- */

/* 1821 MS_RP_HDR 108 I, carried in the MS_RP_HDR structure */
typedef struct {
  uint8_t message_type;      /* byte 0 */
  uint8_t report_date[4];    /* bytes 1 to 4 */
  uint8_t user_type[2];      /* bytes 5 to 6 */
  uint8_t broker_id[5];      /* bytes 7 to 11 */
  uint8_t firm_name[25];     /* bytes 12 to 36 */
  uint8_t trader_number[4];  /* bytes 37 to 40 */
  uint8_t trader_name[26];   /* bytes 41 to 66 */
  uint8_t reserved_1;        /* byte 67 */
} OpenOrderReportMessage;

/* any Open Order Report Message at all: every byte one the checker chooses */
static void any_open_order_report_message(OpenOrderReportMessage *record) {
  record->message_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->report_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->user_type[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->firm_name[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_number[i] = arbitrary(); }
  for (size_t i = 0; i < 26; i++) { record->trader_name[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Open Order Report Message to the wire: 68 bytes from at, returning where the next byte goes */
static size_t encode_open_order_report_message(const OpenOrderReportMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->report_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->user_type[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->firm_name[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_number[i]; }
  for (size_t i = 0; i < 26; i++) { wire[at++] = record->trader_name[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Open Order Report Message off the wire: 68 bytes from at, returning where the next byte lies */
static size_t decode_open_order_report_message(OpenOrderReportMessage *record, const uint8_t *wire, size_t at) {
  record->message_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->report_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->user_type[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->firm_name[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_number[i] = wire[at++]; }
  for (size_t i = 0; i < 26; i++) { record->trader_name[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Open Order Report Message is what was written, byte for byte */
static void equal_open_order_report_message(const OpenOrderReportMessage *read, const OpenOrderReportMessage *written) {
  assert(read->message_type == written->message_type);
  for (size_t i = 0; i < 4; i++) { assert(read->report_date[i] == written->report_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->user_type[i] == written->user_type[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->firm_name[i] == written->firm_name[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_number[i] == written->trader_number[i]); }
  for (size_t i = 0; i < 26; i++) { assert(read->trader_name[i] == written->trader_name[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Open Order Report Message: written and read back, then read and written back */
static void check_open_order_report_message(void) {
  OpenOrderReportMessage sent;
  OpenOrderReportMessage got;
  uint8_t wire[68];
  uint8_t again[68];

  any_open_order_report_message(&sent);
  assert(encode_open_order_report_message(&sent, wire, 0) == 68);
  assert(decode_open_order_report_message(&got, wire, 0) == 68);
  equal_open_order_report_message(&got, &sent);

  for (size_t i = 0; i < 68; i++) { wire[i] = arbitrary(); }
  assert(decode_open_order_report_message(&got, wire, 0) == 68);
  assert(encode_open_order_report_message(&got, again, 0) == 68);
  for (size_t i = 0; i < 68; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spread Order Log Report Message: 68 bytes ------------------------------- */

/* 1992 MS_RP_HDR 108 I, carried in the MS_RP_HDR structure */
typedef struct {
  uint8_t message_type;      /* byte 0 */
  uint8_t report_date[4];    /* bytes 1 to 4 */
  uint8_t user_type[2];      /* bytes 5 to 6 */
  uint8_t broker_id[5];      /* bytes 7 to 11 */
  uint8_t firm_name[25];     /* bytes 12 to 36 */
  uint8_t trader_number[4];  /* bytes 37 to 40 */
  uint8_t trader_name[26];   /* bytes 41 to 66 */
  uint8_t reserved_1;        /* byte 67 */
} SpreadOrderLogReportMessage;

/* any Spread Order Log Report Message at all: every byte one the checker chooses */
static void any_spread_order_log_report_message(SpreadOrderLogReportMessage *record) {
  record->message_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->report_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->user_type[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->firm_name[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_number[i] = arbitrary(); }
  for (size_t i = 0; i < 26; i++) { record->trader_name[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Spread Order Log Report Message to the wire: 68 bytes from at, returning where the next byte goes */
static size_t encode_spread_order_log_report_message(const SpreadOrderLogReportMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->report_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->user_type[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->firm_name[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_number[i]; }
  for (size_t i = 0; i < 26; i++) { wire[at++] = record->trader_name[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Spread Order Log Report Message off the wire: 68 bytes from at, returning where the next byte lies */
static size_t decode_spread_order_log_report_message(SpreadOrderLogReportMessage *record, const uint8_t *wire, size_t at) {
  record->message_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->report_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->user_type[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->firm_name[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_number[i] = wire[at++]; }
  for (size_t i = 0; i < 26; i++) { record->trader_name[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Spread Order Log Report Message is what was written, byte for byte */
static void equal_spread_order_log_report_message(const SpreadOrderLogReportMessage *read, const SpreadOrderLogReportMessage *written) {
  assert(read->message_type == written->message_type);
  for (size_t i = 0; i < 4; i++) { assert(read->report_date[i] == written->report_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->user_type[i] == written->user_type[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->firm_name[i] == written->firm_name[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_number[i] == written->trader_number[i]); }
  for (size_t i = 0; i < 26; i++) { assert(read->trader_name[i] == written->trader_name[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Spread Order Log Report Message: written and read back, then read and written back */
static void check_spread_order_log_report_message(void) {
  SpreadOrderLogReportMessage sent;
  SpreadOrderLogReportMessage got;
  uint8_t wire[68];
  uint8_t again[68];

  any_spread_order_log_report_message(&sent);
  assert(encode_spread_order_log_report_message(&sent, wire, 0) == 68);
  assert(decode_spread_order_log_report_message(&got, wire, 0) == 68);
  equal_spread_order_log_report_message(&got, &sent);

  for (size_t i = 0; i < 68; i++) { wire[i] = arbitrary(); }
  assert(decode_spread_order_log_report_message(&got, wire, 0) == 68);
  assert(encode_spread_order_log_report_message(&got, again, 0) == 68);
  for (size_t i = 0; i < 68; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spread Trade Report Message: 68 bytes ----------------------------------- */

/* 1993 MS_RP_HDR 108 I, carried in the MS_RP_HDR structure */
typedef struct {
  uint8_t message_type;      /* byte 0 */
  uint8_t report_date[4];    /* bytes 1 to 4 */
  uint8_t user_type[2];      /* bytes 5 to 6 */
  uint8_t broker_id[5];      /* bytes 7 to 11 */
  uint8_t firm_name[25];     /* bytes 12 to 36 */
  uint8_t trader_number[4];  /* bytes 37 to 40 */
  uint8_t trader_name[26];   /* bytes 41 to 66 */
  uint8_t reserved_1;        /* byte 67 */
} SpreadTradeReportMessage;

/* any Spread Trade Report Message at all: every byte one the checker chooses */
static void any_spread_trade_report_message(SpreadTradeReportMessage *record) {
  record->message_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->report_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->user_type[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->firm_name[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_number[i] = arbitrary(); }
  for (size_t i = 0; i < 26; i++) { record->trader_name[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Spread Trade Report Message to the wire: 68 bytes from at, returning where the next byte goes */
static size_t encode_spread_trade_report_message(const SpreadTradeReportMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->report_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->user_type[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->firm_name[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_number[i]; }
  for (size_t i = 0; i < 26; i++) { wire[at++] = record->trader_name[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Spread Trade Report Message off the wire: 68 bytes from at, returning where the next byte lies */
static size_t decode_spread_trade_report_message(SpreadTradeReportMessage *record, const uint8_t *wire, size_t at) {
  record->message_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->report_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->user_type[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->firm_name[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_number[i] = wire[at++]; }
  for (size_t i = 0; i < 26; i++) { record->trader_name[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Spread Trade Report Message is what was written, byte for byte */
static void equal_spread_trade_report_message(const SpreadTradeReportMessage *read, const SpreadTradeReportMessage *written) {
  assert(read->message_type == written->message_type);
  for (size_t i = 0; i < 4; i++) { assert(read->report_date[i] == written->report_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->user_type[i] == written->user_type[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->firm_name[i] == written->firm_name[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_number[i] == written->trader_number[i]); }
  for (size_t i = 0; i < 26; i++) { assert(read->trader_name[i] == written->trader_name[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Spread Trade Report Message: written and read back, then read and written back */
static void check_spread_trade_report_message(void) {
  SpreadTradeReportMessage sent;
  SpreadTradeReportMessage got;
  uint8_t wire[68];
  uint8_t again[68];

  any_spread_trade_report_message(&sent);
  assert(encode_spread_trade_report_message(&sent, wire, 0) == 68);
  assert(decode_spread_trade_report_message(&got, wire, 0) == 68);
  equal_spread_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 68; i++) { wire[i] = arbitrary(); }
  assert(decode_spread_trade_report_message(&got, wire, 0) == 68);
  assert(encode_spread_trade_report_message(&got, again, 0) == 68);
  for (size_t i = 0; i < 68; i++) { assert(again[i] == wire[i]); }
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

/* ---- Trade Error Message: 194 bytes ------------------------------------------ */

/* 2223 MS_TRADE_INQ_DATA 234 I, carried in the MS_TRADE_INQ_DATA structure */
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
  uint8_t buy_pan[10];              /* bytes 114 to 123 */
  uint8_t sell_pan[10];             /* bytes 124 to 133 */
  uint8_t reserved_60[60];          /* bytes 134 to 193 */
} TradeErrorMessage;

/* any Trade Error Message at all: every byte one the checker chooses */
static void any_trade_error_message(TradeErrorMessage *record) {
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
  for (size_t i = 0; i < 10; i++) { record->buy_pan[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->sell_pan[i] = arbitrary(); }
  for (size_t i = 0; i < 60; i++) { record->reserved_60[i] = arbitrary(); }
}

/* Trade Error Message to the wire: 194 bytes from at, returning where the next byte goes */
static size_t encode_trade_error_message(const TradeErrorMessage *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->buy_pan[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sell_pan[i]; }
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->reserved_60[i]; }

  return at;
}

/* Trade Error Message off the wire: 194 bytes from at, returning where the next byte lies */
static size_t decode_trade_error_message(TradeErrorMessage *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 10; i++) { record->buy_pan[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->sell_pan[i] = wire[at++]; }
  for (size_t i = 0; i < 60; i++) { record->reserved_60[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Error Message is what was written, byte for byte */
static void equal_trade_error_message(const TradeErrorMessage *read, const TradeErrorMessage *written) {
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
  for (size_t i = 0; i < 10; i++) { assert(read->buy_pan[i] == written->buy_pan[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->sell_pan[i] == written->sell_pan[i]); }
  for (size_t i = 0; i < 60; i++) { assert(read->reserved_60[i] == written->reserved_60[i]); }
}

/* Trade Error Message: written and read back, then read and written back */
static void check_trade_error_message(void) {
  TradeErrorMessage sent;
  TradeErrorMessage got;
  uint8_t wire[194];
  uint8_t again[194];

  any_trade_error_message(&sent);
  assert(encode_trade_error_message(&sent, wire, 0) == 194);
  assert(decode_trade_error_message(&got, wire, 0) == 194);
  equal_trade_error_message(&got, &sent);

  for (size_t i = 0; i < 194; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_error_message(&got, wire, 0) == 194);
  assert(encode_trade_error_message(&got, again, 0) == 194);
  for (size_t i = 0; i < 194; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Out Message: 194 bytes ------------------------------------- */

/* 5441 MS_TRADE_INQ_DATA 234 I, carried in the MS_TRADE_INQ_DATA structure */
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
  uint8_t buy_pan[10];              /* bytes 114 to 123 */
  uint8_t sell_pan[10];             /* bytes 124 to 133 */
  uint8_t reserved_60[60];          /* bytes 134 to 193 */
} TradeCancelOutMessage;

/* any Trade Cancel Out Message at all: every byte one the checker chooses */
static void any_trade_cancel_out_message(TradeCancelOutMessage *record) {
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
  for (size_t i = 0; i < 10; i++) { record->buy_pan[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->sell_pan[i] = arbitrary(); }
  for (size_t i = 0; i < 60; i++) { record->reserved_60[i] = arbitrary(); }
}

/* Trade Cancel Out Message to the wire: 194 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_out_message(const TradeCancelOutMessage *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->buy_pan[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sell_pan[i]; }
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->reserved_60[i]; }

  return at;
}

/* Trade Cancel Out Message off the wire: 194 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_out_message(TradeCancelOutMessage *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 10; i++) { record->buy_pan[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->sell_pan[i] = wire[at++]; }
  for (size_t i = 0; i < 60; i++) { record->reserved_60[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancel Out Message is what was written, byte for byte */
static void equal_trade_cancel_out_message(const TradeCancelOutMessage *read, const TradeCancelOutMessage *written) {
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
  for (size_t i = 0; i < 10; i++) { assert(read->buy_pan[i] == written->buy_pan[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->sell_pan[i] == written->sell_pan[i]); }
  for (size_t i = 0; i < 60; i++) { assert(read->reserved_60[i] == written->reserved_60[i]); }
}

/* Trade Cancel Out Message: written and read back, then read and written back */
static void check_trade_cancel_out_message(void) {
  TradeCancelOutMessage sent;
  TradeCancelOutMessage got;
  uint8_t wire[194];
  uint8_t again[194];

  any_trade_cancel_out_message(&sent);
  assert(encode_trade_cancel_out_message(&sent, wire, 0) == 194);
  assert(decode_trade_cancel_out_message(&got, wire, 0) == 194);
  equal_trade_cancel_out_message(&got, &sent);

  for (size_t i = 0; i < 194; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_out_message(&got, wire, 0) == 194);
  assert(encode_trade_cancel_out_message(&got, again, 0) == 194);
  for (size_t i = 0; i < 194; i++) { assert(again[i] == wire[i]); }
}

/* ---- Error Response Out Message: 142 bytes ----------------------------------- */

/* 2302 MS_ERROR_RESPONSE 182 I, carried in the MS_ERROR_RESPONSE structure */
typedef struct {
  uint8_t key[14];             /* bytes 0 to 13 */
  uint8_t error_message[128];  /* bytes 14 to 141 */
} ErrorResponseOutMessage;

/* any Error Response Out Message at all: every byte one the checker chooses */
static void any_error_response_out_message(ErrorResponseOutMessage *record) {
  for (size_t i = 0; i < 14; i++) { record->key[i] = arbitrary(); }
  for (size_t i = 0; i < 128; i++) { record->error_message[i] = arbitrary(); }
}

/* Error Response Out Message to the wire: 142 bytes from at, returning where the next byte goes */
static size_t encode_error_response_out_message(const ErrorResponseOutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->key[i]; }
  for (size_t i = 0; i < 128; i++) { wire[at++] = record->error_message[i]; }

  return at;
}

/* Error Response Out Message off the wire: 142 bytes from at, returning where the next byte lies */
static size_t decode_error_response_out_message(ErrorResponseOutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->key[i] = wire[at++]; }
  for (size_t i = 0; i < 128; i++) { record->error_message[i] = wire[at++]; }

  return at;
}

/* what was read of Error Response Out Message is what was written, byte for byte */
static void equal_error_response_out_message(const ErrorResponseOutMessage *read, const ErrorResponseOutMessage *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->key[i] == written->key[i]); }
  for (size_t i = 0; i < 128; i++) { assert(read->error_message[i] == written->error_message[i]); }
}

/* Error Response Out Message: written and read back, then read and written back */
static void check_error_response_out_message(void) {
  ErrorResponseOutMessage sent;
  ErrorResponseOutMessage got;
  uint8_t wire[142];
  uint8_t again[142];

  any_error_response_out_message(&sent);
  assert(encode_error_response_out_message(&sent, wire, 0) == 142);
  assert(decode_error_response_out_message(&got, wire, 0) == 142);
  equal_error_response_out_message(&got, &sent);

  for (size_t i = 0; i < 142; i++) { wire[i] = arbitrary(); }
  assert(decode_error_response_out_message(&got, wire, 0) == 142);
  assert(encode_error_response_out_message(&got, again, 0) == 142);
  for (size_t i = 0; i < 142; i++) { assert(again[i] == wire[i]); }
}

/* ---- Gr Response Message: 84 bytes ------------------------------------------- */

/* 2401 MS_GR_RESPONSE 124 I, carried in the MS_GR_RESPONSE structure */
typedef struct {
  uint8_t box_id[2];              /* bytes 0 to 1 */
  uint8_t broker_id[5];           /* bytes 2 to 6 */
  uint8_t filler;                 /* byte 7 */
  uint8_t ip_address[16];         /* bytes 8 to 23 */
  uint8_t port[4];                /* bytes 24 to 27 */
  uint8_t session_key[8];         /* bytes 28 to 35 */
  uint8_t cryptographic_key[32];  /* bytes 36 to 67 */
  uint8_t cryptographic_iv[16];   /* bytes 68 to 83 */
} GrResponseMessage;

/* any Gr Response Message at all: every byte one the checker chooses */
static void any_gr_response_message(GrResponseMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = arbitrary(); }
  record->filler = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->ip_address[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->port[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->session_key[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->cryptographic_key[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cryptographic_iv[i] = arbitrary(); }
}

/* Gr Response Message to the wire: 84 bytes from at, returning where the next byte goes */
static size_t encode_gr_response_message(const GrResponseMessage *record, uint8_t *wire, size_t at) {
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

/* Gr Response Message off the wire: 84 bytes from at, returning where the next byte lies */
static size_t decode_gr_response_message(GrResponseMessage *record, const uint8_t *wire, size_t at) {
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

/* what was read of Gr Response Message is what was written, byte for byte */
static void equal_gr_response_message(const GrResponseMessage *read, const GrResponseMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->box_id[i] == written->box_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  assert(read->filler == written->filler);
  for (size_t i = 0; i < 16; i++) { assert(read->ip_address[i] == written->ip_address[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->port[i] == written->port[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->session_key[i] == written->session_key[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->cryptographic_key[i] == written->cryptographic_key[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cryptographic_iv[i] == written->cryptographic_iv[i]); }
}

/* Gr Response Message: written and read back, then read and written back */
static void check_gr_response_message(void) {
  GrResponseMessage sent;
  GrResponseMessage got;
  uint8_t wire[84];
  uint8_t again[84];

  any_gr_response_message(&sent);
  assert(encode_gr_response_message(&sent, wire, 0) == 84);
  assert(decode_gr_response_message(&got, wire, 0) == 84);
  equal_gr_response_message(&got, &sent);

  for (size_t i = 0; i < 84; i++) { wire[i] = arbitrary(); }
  assert(decode_gr_response_message(&got, wire, 0) == 84);
  assert(encode_gr_response_message(&got, again, 0) == 84);
  for (size_t i = 0; i < 84; i++) { assert(again[i] == wire[i]); }
}

/* ---- User Addr Unlock Confirm Out Message: 40 bytes -------------------------- */

/* 5428 USER_ADDR_UNLOCK_CONFIR 322 I M_FO, carried in the USER_ADDR_UNLOCK_CONFIRM_FO structure */
typedef struct {
  uint8_t user_id[4];       /* bytes 0 to 3 */
  uint8_t reserved_36[36];  /* bytes 4 to 39 */
} UserAddrUnlockConfirmOutMessage;

/* any User Addr Unlock Confirm Out Message at all: every byte one the checker chooses */
static void any_user_addr_unlock_confirm_out_message(UserAddrUnlockConfirmOutMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 36; i++) { record->reserved_36[i] = arbitrary(); }
}

/* User Addr Unlock Confirm Out Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_user_addr_unlock_confirm_out_message(const UserAddrUnlockConfirmOutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 36; i++) { wire[at++] = record->reserved_36[i]; }

  return at;
}

/* User Addr Unlock Confirm Out Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_user_addr_unlock_confirm_out_message(UserAddrUnlockConfirmOutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 36; i++) { record->reserved_36[i] = wire[at++]; }

  return at;
}

/* what was read of User Addr Unlock Confirm Out Message is what was written, byte for byte */
static void equal_user_addr_unlock_confirm_out_message(const UserAddrUnlockConfirmOutMessage *read, const UserAddrUnlockConfirmOutMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 36; i++) { assert(read->reserved_36[i] == written->reserved_36[i]); }
}

/* User Addr Unlock Confirm Out Message: written and read back, then read and written back */
static void check_user_addr_unlock_confirm_out_message(void) {
  UserAddrUnlockConfirmOutMessage sent;
  UserAddrUnlockConfirmOutMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_user_addr_unlock_confirm_out_message(&sent);
  assert(encode_user_addr_unlock_confirm_out_message(&sent, wire, 0) == 40);
  assert(decode_user_addr_unlock_confirm_out_message(&got, wire, 0) == 40);
  equal_user_addr_unlock_confirm_out_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_user_addr_unlock_confirm_out_message(&got, wire, 0) == 40);
  assert(encode_user_addr_unlock_confirm_out_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- User Addr Unlock Approve Out Message: 40 bytes -------------------------- */

/* 5483 USER_ADDR_UNLOCK_APPRO 76 I VE_FO, carried in the USER_ADDR_UNLOCK_APPROVE_FO structure */
typedef struct {
  uint8_t user_id[4];       /* bytes 0 to 3 */
  uint8_t reserved_36[36];  /* bytes 4 to 39 */
} UserAddrUnlockApproveOutMessage;

/* any User Addr Unlock Approve Out Message at all: every byte one the checker chooses */
static void any_user_addr_unlock_approve_out_message(UserAddrUnlockApproveOutMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 36; i++) { record->reserved_36[i] = arbitrary(); }
}

/* User Addr Unlock Approve Out Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_user_addr_unlock_approve_out_message(const UserAddrUnlockApproveOutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 36; i++) { wire[at++] = record->reserved_36[i]; }

  return at;
}

/* User Addr Unlock Approve Out Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_user_addr_unlock_approve_out_message(UserAddrUnlockApproveOutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 36; i++) { record->reserved_36[i] = wire[at++]; }

  return at;
}

/* what was read of User Addr Unlock Approve Out Message is what was written, byte for byte */
static void equal_user_addr_unlock_approve_out_message(const UserAddrUnlockApproveOutMessage *read, const UserAddrUnlockApproveOutMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 36; i++) { assert(read->reserved_36[i] == written->reserved_36[i]); }
}

/* User Addr Unlock Approve Out Message: written and read back, then read and written back */
static void check_user_addr_unlock_approve_out_message(void) {
  UserAddrUnlockApproveOutMessage sent;
  UserAddrUnlockApproveOutMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_user_addr_unlock_approve_out_message(&sent);
  assert(encode_user_addr_unlock_approve_out_message(&sent, wire, 0) == 40);
  assert(decode_user_addr_unlock_approve_out_message(&got, wire, 0) == 40);
  equal_user_addr_unlock_approve_out_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_user_addr_unlock_approve_out_message(&got, wire, 0) == 40);
  assert(encode_user_addr_unlock_approve_out_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- User Addr Unlock Reject Out Message: 40 bytes --------------------------- */

/* 5484 USER_ADDR_UNLOCK_APPRO 76 I VE_FO, carried in the USER_ADDR_UNLOCK_APPROVE_FO structure */
typedef struct {
  uint8_t user_id[4];       /* bytes 0 to 3 */
  uint8_t reserved_36[36];  /* bytes 4 to 39 */
} UserAddrUnlockRejectOutMessage;

/* any User Addr Unlock Reject Out Message at all: every byte one the checker chooses */
static void any_user_addr_unlock_reject_out_message(UserAddrUnlockRejectOutMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 36; i++) { record->reserved_36[i] = arbitrary(); }
}

/* User Addr Unlock Reject Out Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_user_addr_unlock_reject_out_message(const UserAddrUnlockRejectOutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 36; i++) { wire[at++] = record->reserved_36[i]; }

  return at;
}

/* User Addr Unlock Reject Out Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_user_addr_unlock_reject_out_message(UserAddrUnlockRejectOutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 36; i++) { record->reserved_36[i] = wire[at++]; }

  return at;
}

/* what was read of User Addr Unlock Reject Out Message is what was written, byte for byte */
static void equal_user_addr_unlock_reject_out_message(const UserAddrUnlockRejectOutMessage *read, const UserAddrUnlockRejectOutMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 36; i++) { assert(read->reserved_36[i] == written->reserved_36[i]); }
}

/* User Addr Unlock Reject Out Message: written and read back, then read and written back */
static void check_user_addr_unlock_reject_out_message(void) {
  UserAddrUnlockRejectOutMessage sent;
  UserAddrUnlockRejectOutMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_user_addr_unlock_reject_out_message(&sent);
  assert(encode_user_addr_unlock_reject_out_message(&sent, wire, 0) == 40);
  assert(decode_user_addr_unlock_reject_out_message(&got, wire, 0) == 40);
  equal_user_addr_unlock_reject_out_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_user_addr_unlock_reject_out_message(&got, wire, 0) == 40);
  assert(encode_user_addr_unlock_reject_out_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reset User Password Out Message: 18 bytes ------------------------------- */

/* 5741 RESET_USER_PASSWORD_IN_ 58 I FO, carried in the RESET_USER_PASSWORD_IN_FO structure */
typedef struct {
  uint8_t user_id[4];       /* bytes 0 to 3 */
  uint8_t reserved_14[14];  /* bytes 4 to 17 */
} ResetUserPasswordOutMessage;

/* any Reset User Password Out Message at all: every byte one the checker chooses */
static void any_reset_user_password_out_message(ResetUserPasswordOutMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->reserved_14[i] = arbitrary(); }
}

/* Reset User Password Out Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_reset_user_password_out_message(const ResetUserPasswordOutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->reserved_14[i]; }

  return at;
}

/* Reset User Password Out Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_reset_user_password_out_message(ResetUserPasswordOutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->reserved_14[i] = wire[at++]; }

  return at;
}

/* what was read of Reset User Password Out Message is what was written, byte for byte */
static void equal_reset_user_password_out_message(const ResetUserPasswordOutMessage *read, const ResetUserPasswordOutMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->reserved_14[i] == written->reserved_14[i]); }
}

/* Reset User Password Out Message: written and read back, then read and written back */
static void check_reset_user_password_out_message(void) {
  ResetUserPasswordOutMessage sent;
  ResetUserPasswordOutMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_reset_user_password_out_message(&sent);
  assert(encode_reset_user_password_out_message(&sent, wire, 0) == 18);
  assert(decode_reset_user_password_out_message(&got, wire, 0) == 18);
  equal_reset_user_password_out_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_reset_user_password_out_message(&got, wire, 0) == 18);
  assert(encode_reset_user_password_out_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Col User Status Change Out Message: 6 bytes ----------------------------- */

/* 5745 COL_USER_STATUS_CHANGE_ 46 I RESP, carried in the COL_USER_STATUS_CHANGE_RESP structure */
typedef struct {
  uint8_t user_id[4];    /* bytes 0 to 3 */
  uint8_t col_user_bit;  /* byte 4 */
  uint8_t reserved_1;    /* byte 5 */
} ColUserStatusChangeOutMessage;

/* any Col User Status Change Out Message at all: every byte one the checker chooses */
static void any_col_user_status_change_out_message(ColUserStatusChangeOutMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  record->col_user_bit = arbitrary();
  record->reserved_1 = arbitrary();
}

/* Col User Status Change Out Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_col_user_status_change_out_message(const ColUserStatusChangeOutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  wire[at++] = record->col_user_bit;
  wire[at++] = record->reserved_1;

  return at;
}

/* Col User Status Change Out Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_col_user_status_change_out_message(ColUserStatusChangeOutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  record->col_user_bit = wire[at++];
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Col User Status Change Out Message is what was written, byte for byte */
static void equal_col_user_status_change_out_message(const ColUserStatusChangeOutMessage *read, const ColUserStatusChangeOutMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  assert(read->col_user_bit == written->col_user_bit);
  assert(read->reserved_1 == written->reserved_1);
}

/* Col User Status Change Out Message: written and read back, then read and written back */
static void check_col_user_status_change_out_message(void) {
  ColUserStatusChangeOutMessage sent;
  ColUserStatusChangeOutMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_col_user_status_change_out_message(&sent);
  assert(encode_col_user_status_change_out_message(&sent, wire, 0) == 6);
  assert(decode_col_user_status_change_out_message(&got, wire, 0) == 6);
  equal_col_user_status_change_out_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_col_user_status_change_out_message(&got, wire, 0) == 6);
  assert(encode_col_user_status_change_out_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Update Localdb Header Message: 2 bytes ---------------------------------- */

/* 7307 UPDATE_LDB_HEADER 42 I, carried in the UPDATE_LDB_HEADER structure */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
} UpdateLocaldbHeaderMessage;

/* any Update Localdb Header Message at all: every byte one the checker chooses */
static void any_update_localdb_header_message(UpdateLocaldbHeaderMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Update Localdb Header Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_update_localdb_header_message(const UpdateLocaldbHeaderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Update Localdb Header Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_update_localdb_header_message(UpdateLocaldbHeaderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Update Localdb Header Message is what was written, byte for byte */
static void equal_update_localdb_header_message(const UpdateLocaldbHeaderMessage *read, const UpdateLocaldbHeaderMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Update Localdb Header Message: written and read back, then read and written back */
static void check_update_localdb_header_message(void) {
  UpdateLocaldbHeaderMessage sent;
  UpdateLocaldbHeaderMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_update_localdb_header_message(&sent);
  assert(encode_update_localdb_header_message(&sent, wire, 0) == 2);
  assert(decode_update_localdb_header_message(&got, wire, 0) == 2);
  equal_update_localdb_header_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_update_localdb_header_message(&got, wire, 0) == 2);
  assert(encode_update_localdb_header_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Update Localdb Trailer Message: 2 bytes --------------------------------- */

/* 7308 UPDATE_LDB_HEADER 42 I, carried in the UPDATE_LOCAL_DB_TRAILER structure */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
} UpdateLocaldbTrailerMessage;

/* any Update Localdb Trailer Message at all: every byte one the checker chooses */
static void any_update_localdb_trailer_message(UpdateLocaldbTrailerMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Update Localdb Trailer Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_update_localdb_trailer_message(const UpdateLocaldbTrailerMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Update Localdb Trailer Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_update_localdb_trailer_message(UpdateLocaldbTrailerMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Update Localdb Trailer Message is what was written, byte for byte */
static void equal_update_localdb_trailer_message(const UpdateLocaldbTrailerMessage *read, const UpdateLocaldbTrailerMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Update Localdb Trailer Message: written and read back, then read and written back */
static void check_update_localdb_trailer_message(void) {
  UpdateLocaldbTrailerMessage sent;
  UpdateLocaldbTrailerMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_update_localdb_trailer_message(&sent);
  assert(encode_update_localdb_trailer_message(&sent, wire, 0) == 2);
  assert(decode_update_localdb_trailer_message(&got, wire, 0) == 2);
  equal_update_localdb_trailer_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_update_localdb_trailer_message(&got, wire, 0) == 2);
  assert(encode_update_localdb_trailer_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bcast Asset Mstr Chg Message: 392 bytes --------------------------------- */

/* Bcast Asset Mstr Chg, carried in the MS_DOWNLOAD_ASSET structure */
typedef struct {
  uint8_t no_of_records[2];   /* bytes 0 to 1 */
  uint8_t reserved_390[390];  /* bytes 2 to 391 */
} BcastAssetMstrChgMessage;

/* any Bcast Asset Mstr Chg Message at all: every byte one the checker chooses */
static void any_bcast_asset_mstr_chg_message(BcastAssetMstrChgMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->no_of_records[i] = arbitrary(); }
  for (size_t i = 0; i < 390; i++) { record->reserved_390[i] = arbitrary(); }
}

/* Bcast Asset Mstr Chg Message to the wire: 392 bytes from at, returning where the next byte goes */
static size_t encode_bcast_asset_mstr_chg_message(const BcastAssetMstrChgMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->no_of_records[i]; }
  for (size_t i = 0; i < 390; i++) { wire[at++] = record->reserved_390[i]; }

  return at;
}

/* Bcast Asset Mstr Chg Message off the wire: 392 bytes from at, returning where the next byte lies */
static size_t decode_bcast_asset_mstr_chg_message(BcastAssetMstrChgMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->no_of_records[i] = wire[at++]; }
  for (size_t i = 0; i < 390; i++) { record->reserved_390[i] = wire[at++]; }

  return at;
}

/* what was read of Bcast Asset Mstr Chg Message is what was written, byte for byte */
static void equal_bcast_asset_mstr_chg_message(const BcastAssetMstrChgMessage *read, const BcastAssetMstrChgMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->no_of_records[i] == written->no_of_records[i]); }
  for (size_t i = 0; i < 390; i++) { assert(read->reserved_390[i] == written->reserved_390[i]); }
}

/* Bcast Asset Mstr Chg Message: written and read back, then read and written back */
static void check_bcast_asset_mstr_chg_message(void) {
  BcastAssetMstrChgMessage sent;
  BcastAssetMstrChgMessage got;
  uint8_t wire[392];
  uint8_t again[392];

  any_bcast_asset_mstr_chg_message(&sent);
  assert(encode_bcast_asset_mstr_chg_message(&sent, wire, 0) == 392);
  assert(decode_bcast_asset_mstr_chg_message(&got, wire, 0) == 392);
  equal_bcast_asset_mstr_chg_message(&got, &sent);

  for (size_t i = 0; i < 392; i++) { wire[i] = arbitrary(); }
  assert(decode_bcast_asset_mstr_chg_message(&got, wire, 0) == 392);
  assert(encode_bcast_asset_mstr_chg_message(&got, again, 0) == 392);
  for (size_t i = 0; i < 392; i++) { assert(again[i] == wire[i]); }
}

/* ---- Box Sign On Request Out Message: 12 bytes ------------------------------- */

/* 23001 MS_BOX_SIGN_ON_REQUEST 54 I _OUT, carried in the MS_BOX_SIGN_ON_REQUEST_OUT structure */
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

/* 20322 MS_BOX_SIGN_OFF 42 I * I/B - Interactive/Broadcast List of Transaction Codes Containing Timestamp in Nanoseconds The trascation codes that will contain timestamp in nanoseconds from 01-Jan-1980 00:00:00 are listed in following table, carried in the MS_BOX_SIGN_OFF structure */
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

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_st_market_status();
  check_st_ex_market_status();
  check_st_pl_market_status();
  check_open_order_report_message();
  check_spread_order_log_report_message();
  check_spread_trade_report_message();
  check_contract_desc();
  check_trade_error_message();
  check_trade_cancel_out_message();
  check_error_response_out_message();
  check_gr_response_message();
  check_user_addr_unlock_confirm_out_message();
  check_user_addr_unlock_approve_out_message();
  check_user_addr_unlock_reject_out_message();
  check_reset_user_password_out_message();
  check_col_user_status_change_out_message();
  check_update_localdb_header_message();
  check_update_localdb_trailer_message();
  check_bcast_asset_mstr_chg_message();
  check_box_sign_on_request_out_message();
  check_box_sign_off_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
