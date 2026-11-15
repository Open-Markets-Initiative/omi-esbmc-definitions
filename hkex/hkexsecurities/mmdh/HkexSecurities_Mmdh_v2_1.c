// hkex/hkexsecurities/mmdh/HkexSecurities_Mmdh_v2_1.c
/*
 * Hong Kong Exchanges and Clearing Orion Market Data Cash Mainland Market Data Hub
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
 *   - a length prefix framing what follows
 *   - a run counted by a field
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

/* ---- Message Header: 20 bytes ------------------------------------------------ */

/* Omd 20-byte per-message TCP session framing header (per §3.2). The MsgSize + MsgType payload prefix follows as siblings at the Message level. */
typedef struct {
  uint8_t msg_length[2];        /* bytes 0 to 1 */
  uint8_t filler[2];            /* bytes 2 to 3 */
  uint8_t seq_num[4];           /* bytes 4 to 7 */
  uint8_t internal_seq_num[4];  /* bytes 8 to 11 */
  uint8_t send_time[8];         /* bytes 12 to 19 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->internal_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = arbitrary(); }
}

/* Message Header to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->internal_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->send_time[i]; }

  return at;
}

/* Message Header off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->internal_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->msg_length[i] == written->msg_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler[i] == written->filler[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->seq_num[i] == written->seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->internal_seq_num[i] == written->internal_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->send_time[i] == written->send_time[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[20];
  uint8_t again[20];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 20);
  assert(decode_message_header(&got, wire, 0) == 20);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 20);
  assert(encode_message_header(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Odd Lot Order Message: 24 bytes ------------------------------------- */

/* The Add Odd Lot Order message is generated when a new odd lot order is inserted into the order book. */
typedef struct {
  uint8_t security_code[4];  /* bytes 0 to 3 */
  uint8_t order_id[8];       /* bytes 4 to 11 */
  uint8_t price[4];          /* bytes 12 to 15 */
  uint8_t quantity[4];       /* bytes 16 to 19 */
  uint8_t broker_id[2];      /* bytes 20 to 21 */
  uint8_t side[2];           /* bytes 22 to 23 */
} AddOddLotOrderMessage;

/* any Add Odd Lot Order Message at all: every byte one the checker chooses */
static void any_add_odd_lot_order_message(AddOddLotOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->side[i] = arbitrary(); }
}

/* Add Odd Lot Order Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_add_odd_lot_order_message(const AddOddLotOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->side[i]; }

  return at;
}

/* Add Odd Lot Order Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_add_odd_lot_order_message(AddOddLotOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->side[i] = wire[at++]; }

  return at;
}

/* what was read of Add Odd Lot Order Message is what was written, byte for byte */
static void equal_add_odd_lot_order_message(const AddOddLotOrderMessage *read, const AddOddLotOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->side[i] == written->side[i]); }
}

/* Add Odd Lot Order Message: written and read back, then read and written back */
static void check_add_odd_lot_order_message(void) {
  AddOddLotOrderMessage sent;
  AddOddLotOrderMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_add_odd_lot_order_message(&sent);
  assert(encode_add_odd_lot_order_message(&sent, wire, 0) == 24);
  assert(decode_add_odd_lot_order_message(&got, wire, 0) == 24);
  equal_add_odd_lot_order_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_add_odd_lot_order_message(&got, wire, 0) == 24);
  assert(encode_add_odd_lot_order_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Closing Price Message: 12 bytes ----------------------------------------- */

/* The Closing Price message is generated near the end of the business day for each security. If the closing price is not available, ClosingPrice is set to 0. NumberOfTrades is not populated for SS (OMD Securities Standard) clients. */
typedef struct {
  uint8_t security_code[4];  /* bytes 0 to 3 */
  uint8_t closing_price[4];  /* bytes 4 to 7 */
  uint8_t filler_4[4];       /* bytes 8 to 11 */
} ClosingPriceMessage;

/* any Closing Price Message at all: every byte one the checker chooses */
static void any_closing_price_message(ClosingPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
}

/* Closing Price Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_closing_price_message(const ClosingPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->closing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }

  return at;
}

/* Closing Price Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_closing_price_message(ClosingPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }

  return at;
}

/* what was read of Closing Price Message is what was written, byte for byte */
static void equal_closing_price_message(const ClosingPriceMessage *read, const ClosingPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
}

/* Closing Price Message: written and read back, then read and written back */
static void check_closing_price_message(void) {
  ClosingPriceMessage sent;
  ClosingPriceMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_closing_price_message(&sent);
  assert(encode_closing_price_message(&sent, wire, 0) == 12);
  assert(decode_closing_price_message(&got, wire, 0) == 12);
  equal_closing_price_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_closing_price_message(&got, wire, 0) == 12);
  assert(encode_closing_price_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Odd Lot Order Message: 16 bytes ---------------------------------- */

/* The Delete Odd Lot Order message is generated when an existing odd lot order identified by the OrderId is deleted. */
typedef struct {
  uint8_t security_code[4];  /* bytes 0 to 3 */
  uint8_t order_id[8];       /* bytes 4 to 11 */
  uint8_t broker_id[2];      /* bytes 12 to 13 */
  uint8_t side[2];           /* bytes 14 to 15 */
} DeleteOddLotOrderMessage;

/* any Delete Odd Lot Order Message at all: every byte one the checker chooses */
static void any_delete_odd_lot_order_message(DeleteOddLotOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->side[i] = arbitrary(); }
}

/* Delete Odd Lot Order Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_delete_odd_lot_order_message(const DeleteOddLotOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->side[i]; }

  return at;
}

/* Delete Odd Lot Order Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_delete_odd_lot_order_message(DeleteOddLotOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->side[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Odd Lot Order Message is what was written, byte for byte */
static void equal_delete_odd_lot_order_message(const DeleteOddLotOrderMessage *read, const DeleteOddLotOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->side[i] == written->side[i]); }
}

/* Delete Odd Lot Order Message: written and read back, then read and written back */
static void check_delete_odd_lot_order_message(void) {
  DeleteOddLotOrderMessage sent;
  DeleteOddLotOrderMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_delete_odd_lot_order_message(&sent);
  assert(encode_delete_odd_lot_order_message(&sent, wire, 0) == 16);
  assert(decode_delete_odd_lot_order_message(&got, wire, 0) == 16);
  equal_delete_odd_lot_order_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_odd_lot_order_message(&got, wire, 0) == 16);
  assert(encode_delete_odd_lot_order_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Definition Message: 16 bytes -------------------------------------- */

/* The Index Definition message contains the static referential data for the given index and is generated at the start of the business day. May be re-disseminated during trading hours. */
typedef struct {
  uint8_t index_code[11];    /* bytes 0 to 10 */
  uint8_t index_source;      /* byte 11 */
  uint8_t currency_code[3];  /* bytes 12 to 14 */
  uint8_t filler_1;          /* byte 15 */
} IndexDefinitionMessage;

/* any Index Definition Message at all: every byte one the checker chooses */
static void any_index_definition_message(IndexDefinitionMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->index_code[i] = arbitrary(); }
  record->index_source = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = arbitrary(); }
  record->filler_1 = arbitrary();
}

/* Index Definition Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_index_definition_message(const IndexDefinitionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->index_code[i]; }
  wire[at++] = record->index_source;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency_code[i]; }
  wire[at++] = record->filler_1;

  return at;
}

/* Index Definition Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_index_definition_message(IndexDefinitionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->index_code[i] = wire[at++]; }
  record->index_source = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = wire[at++]; }
  record->filler_1 = wire[at++];

  return at;
}

/* what was read of Index Definition Message is what was written, byte for byte */
static void equal_index_definition_message(const IndexDefinitionMessage *read, const IndexDefinitionMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->index_code[i] == written->index_code[i]); }
  assert(read->index_source == written->index_source);
  for (size_t i = 0; i < 3; i++) { assert(read->currency_code[i] == written->currency_code[i]); }
  assert(read->filler_1 == written->filler_1);
}

/* Index Definition Message: written and read back, then read and written back */
static void check_index_definition_message(void) {
  IndexDefinitionMessage sent;
  IndexDefinitionMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_index_definition_message(&sent);
  assert(encode_index_definition_message(&sent, wire, 0) == 16);
  assert(decode_index_definition_message(&got, wire, 0) == 16);
  equal_index_definition_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_index_definition_message(&got, wire, 0) == 16);
  assert(encode_index_definition_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Data Message: 108 bytes ------------------------------------------- */

/* The Index Data message contains all the real-time data for a given index. Fields may be populated with null values to indicate when an update is not provided. */
typedef struct {
  uint8_t index_code[11];           /* bytes 0 to 10 */
  uint8_t index_status;             /* byte 11 */
  uint8_t index_time[8];            /* bytes 12 to 19 */
  uint8_t index_value[8];           /* bytes 20 to 27 */
  uint8_t net_chg_prev_day[8];      /* bytes 28 to 35 */
  uint8_t high_value[8];            /* bytes 36 to 43 */
  uint8_t low_value[8];             /* bytes 44 to 51 */
  uint8_t eas_value[8];             /* bytes 52 to 59 */
  uint8_t index_turnover[8];        /* bytes 60 to 67 */
  uint8_t opening_value[8];         /* bytes 68 to 75 */
  uint8_t closing_value[8];         /* bytes 76 to 83 */
  uint8_t previous_ses_close[8];    /* bytes 84 to 91 */
  uint8_t index_volume[8];          /* bytes 92 to 99 */
  uint8_t net_chg_prev_day_pct[4];  /* bytes 100 to 103 */
  uint8_t exception;                /* byte 104 */
  uint8_t filler_3[3];              /* bytes 105 to 107 */
} IndexDataMessage;

/* any Index Data Message at all: every byte one the checker chooses */
static void any_index_data_message(IndexDataMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->index_code[i] = arbitrary(); }
  record->index_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->index_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->net_chg_prev_day[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->eas_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_turnover[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_ses_close[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->net_chg_prev_day_pct[i] = arbitrary(); }
  record->exception = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = arbitrary(); }
}

/* Index Data Message to the wire: 108 bytes from at, returning where the next byte goes */
static size_t encode_index_data_message(const IndexDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->index_code[i]; }
  wire[at++] = record->index_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->net_chg_prev_day[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->eas_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_turnover[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_ses_close[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->net_chg_prev_day_pct[i]; }
  wire[at++] = record->exception;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_3[i]; }

  return at;
}

/* Index Data Message off the wire: 108 bytes from at, returning where the next byte lies */
static size_t decode_index_data_message(IndexDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->index_code[i] = wire[at++]; }
  record->index_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->index_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->net_chg_prev_day[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->eas_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_turnover[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_ses_close[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->net_chg_prev_day_pct[i] = wire[at++]; }
  record->exception = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = wire[at++]; }

  return at;
}

/* what was read of Index Data Message is what was written, byte for byte */
static void equal_index_data_message(const IndexDataMessage *read, const IndexDataMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->index_code[i] == written->index_code[i]); }
  assert(read->index_status == written->index_status);
  for (size_t i = 0; i < 8; i++) { assert(read->index_time[i] == written->index_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_value[i] == written->index_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->net_chg_prev_day[i] == written->net_chg_prev_day[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_value[i] == written->high_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_value[i] == written->low_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->eas_value[i] == written->eas_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_turnover[i] == written->index_turnover[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_value[i] == written->opening_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_value[i] == written->closing_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_ses_close[i] == written->previous_ses_close[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_volume[i] == written->index_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->net_chg_prev_day_pct[i] == written->net_chg_prev_day_pct[i]); }
  assert(read->exception == written->exception);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
}

/* Index Data Message: written and read back, then read and written back */
static void check_index_data_message(void) {
  IndexDataMessage sent;
  IndexDataMessage got;
  uint8_t wire[108];
  uint8_t again[108];

  any_index_data_message(&sent);
  assert(encode_index_data_message(&sent, wire, 0) == 108);
  assert(decode_index_data_message(&got, wire, 0) == 108);
  equal_index_data_message(&got, &sent);

  for (size_t i = 0; i < 108; i++) { wire[i] = arbitrary(); }
  assert(decode_index_data_message(&got, wire, 0) == 108);
  assert(encode_index_data_message(&got, again, 0) == 108);
  for (size_t i = 0; i < 108; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indicative Equilibrium Price Message: 16 bytes -------------------------- */

/* The Indicative Equilibrium Price (IEP) message is generated whenever there is change of the IEP or Indicative Equilibrium Volume (IEV) during Pre-Opening Session (POS) or Closing Auction Session (CAS). The IEP is 0 when IEP does not exist. */
typedef struct {
  uint8_t security_code[4];       /* bytes 0 to 3 */
  uint8_t price[4];               /* bytes 4 to 7 */
  uint8_t aggregate_quantity[8];  /* bytes 8 to 15 */
} IndicativeEquilibriumPriceMessage;

/* any Indicative Equilibrium Price Message at all: every byte one the checker chooses */
static void any_indicative_equilibrium_price_message(IndicativeEquilibriumPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->aggregate_quantity[i] = arbitrary(); }
}

/* Indicative Equilibrium Price Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_indicative_equilibrium_price_message(const IndicativeEquilibriumPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->aggregate_quantity[i]; }

  return at;
}

/* Indicative Equilibrium Price Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_indicative_equilibrium_price_message(IndicativeEquilibriumPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->aggregate_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Indicative Equilibrium Price Message is what was written, byte for byte */
static void equal_indicative_equilibrium_price_message(const IndicativeEquilibriumPriceMessage *read, const IndicativeEquilibriumPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->aggregate_quantity[i] == written->aggregate_quantity[i]); }
}

/* Indicative Equilibrium Price Message: written and read back, then read and written back */
static void check_indicative_equilibrium_price_message(void) {
  IndicativeEquilibriumPriceMessage sent;
  IndicativeEquilibriumPriceMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_indicative_equilibrium_price_message(&sent);
  assert(encode_indicative_equilibrium_price_message(&sent, wire, 0) == 16);
  assert(decode_indicative_equilibrium_price_message(&got, wire, 0) == 16);
  equal_indicative_equilibrium_price_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_indicative_equilibrium_price_message(&got, wire, 0) == 16);
  assert(encode_indicative_equilibrium_price_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Nominal Price Message: 8 bytes ------------------------------------------ */

/* The Nominal message may be generated when an order is added, deleted or modified in a book or when trade or trade cancel is performed. Before the first Nominal Price message, the nominal price should be the same as the previous closing price provided in Security Definition (11). */
typedef struct {
  uint8_t security_code[4];  /* bytes 0 to 3 */
  uint8_t nominal_price[4];  /* bytes 4 to 7 */
} NominalPriceMessage;

/* any Nominal Price Message at all: every byte one the checker chooses */
static void any_nominal_price_message(NominalPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nominal_price[i] = arbitrary(); }
}

/* Nominal Price Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_nominal_price_message(const NominalPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nominal_price[i]; }

  return at;
}

/* Nominal Price Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_nominal_price_message(NominalPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nominal_price[i] = wire[at++]; }

  return at;
}

/* what was read of Nominal Price Message is what was written, byte for byte */
static void equal_nominal_price_message(const NominalPriceMessage *read, const NominalPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nominal_price[i] == written->nominal_price[i]); }
}

/* Nominal Price Message: written and read back, then read and written back */
static void check_nominal_price_message(void) {
  NominalPriceMessage sent;
  NominalPriceMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_nominal_price_message(&sent);
  assert(encode_nominal_price_message(&sent, wire, 0) == 8);
  assert(decode_nominal_price_message(&got, wire, 0) == 8);
  equal_nominal_price_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_nominal_price_message(&got, wire, 0) == 8);
  assert(encode_nominal_price_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Imbalance Message: 16 bytes --------------------------------------- */

/* The Order Imbalance message provides order imbalance information at the Indicative Equilibrium Price (IEP) during the Pre-Opening Session (POS) and Closing Auction Session (CAS). */
typedef struct {
  uint8_t security_code[4];             /* bytes 0 to 3 */
  uint8_t order_imbalance_direction;    /* byte 4 */
  uint8_t filler_1;                     /* byte 5 */
  uint8_t order_imbalance_quantity[8];  /* bytes 6 to 13 */
  uint8_t filler_2[2];                  /* bytes 14 to 15 */
} OrderImbalanceMessage;

/* any Order Imbalance Message at all: every byte one the checker chooses */
static void any_order_imbalance_message(OrderImbalanceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  record->order_imbalance_direction = arbitrary();
  record->filler_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_imbalance_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
}

/* Order Imbalance Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_order_imbalance_message(const OrderImbalanceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  wire[at++] = record->order_imbalance_direction;
  wire[at++] = record->filler_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_imbalance_quantity[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }

  return at;
}

/* Order Imbalance Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_order_imbalance_message(OrderImbalanceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  record->order_imbalance_direction = wire[at++];
  record->filler_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_imbalance_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }

  return at;
}

/* what was read of Order Imbalance Message is what was written, byte for byte */
static void equal_order_imbalance_message(const OrderImbalanceMessage *read, const OrderImbalanceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  assert(read->order_imbalance_direction == written->order_imbalance_direction);
  assert(read->filler_1 == written->filler_1);
  for (size_t i = 0; i < 8; i++) { assert(read->order_imbalance_quantity[i] == written->order_imbalance_quantity[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
}

/* Order Imbalance Message: written and read back, then read and written back */
static void check_order_imbalance_message(void) {
  OrderImbalanceMessage sent;
  OrderImbalanceMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_order_imbalance_message(&sent);
  assert(encode_order_imbalance_message(&sent, wire, 0) == 16);
  assert(decode_order_imbalance_message(&got, wire, 0) == 16);
  equal_order_imbalance_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_order_imbalance_message(&got, wire, 0) == 16);
  assert(encode_order_imbalance_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Definition Message: 36 bytes ------------------------------------- */

/* The Market Definition message is generated at the start of the business day for each market segment. */
typedef struct {
  uint8_t market_code[4];           /* bytes 0 to 3 */
  uint8_t market_name[25];          /* bytes 4 to 28 */
  uint8_t currency_code[3];         /* bytes 29 to 31 */
  uint8_t number_of_securities[4];  /* bytes 32 to 35 */
} MarketDefinitionMessage;

/* any Market Definition Message at all: every byte one the checker chooses */
static void any_market_definition_message(MarketDefinitionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->market_name[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_securities[i] = arbitrary(); }
}

/* Market Definition Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_market_definition_message(const MarketDefinitionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_code[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->market_name[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_securities[i]; }

  return at;
}

/* Market Definition Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_market_definition_message(MarketDefinitionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->market_name[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_securities[i] = wire[at++]; }

  return at;
}

/* what was read of Market Definition Message is what was written, byte for byte */
static void equal_market_definition_message(const MarketDefinitionMessage *read, const MarketDefinitionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_code[i] == written->market_code[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->market_name[i] == written->market_name[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency_code[i] == written->currency_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_securities[i] == written->number_of_securities[i]); }
}

/* Market Definition Message: written and read back, then read and written back */
static void check_market_definition_message(void) {
  MarketDefinitionMessage sent;
  MarketDefinitionMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_market_definition_message(&sent);
  assert(encode_market_definition_message(&sent, wire, 0) == 36);
  assert(decode_market_definition_message(&got, wire, 0) == 36);
  equal_market_definition_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_market_definition_message(&got, wire, 0) == 36);
  assert(encode_market_definition_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Face Value Composite: 9 bytes ------------------------------------------- */

/* Bond face value scaled at runtime by DecimalsInFaceValue. 0 mantissa means Not available. */
typedef struct {
  uint8_t face_value[8];           /* bytes 0 to 7 */
  uint8_t decimals_in_face_value;  /* byte 8 */
} FaceValueComposite;

/* any Face Value Composite at all: every byte one the checker chooses */
static void any_face_value_composite(FaceValueComposite *record) {
  for (size_t i = 0; i < 8; i++) { record->face_value[i] = arbitrary(); }
  record->decimals_in_face_value = arbitrary();
}

/* Face Value Composite to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_face_value_composite(const FaceValueComposite *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->face_value[i]; }
  wire[at++] = record->decimals_in_face_value;

  return at;
}

/* Face Value Composite off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_face_value_composite(FaceValueComposite *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->face_value[i] = wire[at++]; }
  record->decimals_in_face_value = wire[at++];

  return at;
}

/* what was read of Face Value Composite is what was written, byte for byte */
static void equal_face_value_composite(const FaceValueComposite *read, const FaceValueComposite *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->face_value[i] == written->face_value[i]); }
  assert(read->decimals_in_face_value == written->decimals_in_face_value);
}

/* Face Value Composite: written and read back, then read and written back */
static void check_face_value_composite(void) {
  FaceValueComposite sent;
  FaceValueComposite got;
  uint8_t wire[9];
  uint8_t again[9];

  any_face_value_composite(&sent);
  assert(encode_face_value_composite(&sent, wire, 0) == 9);
  assert(decode_face_value_composite(&got, wire, 0) == 9);
  equal_face_value_composite(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_face_value_composite(&got, wire, 0) == 9);
  assert(encode_face_value_composite(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Call Price Composite: 5 bytes ------------------------------------------- */

/* CBBC call price scaled at runtime by DecimalsInCallPrice. 0 mantissa means Not available. */
typedef struct {
  uint8_t call_price[4];           /* bytes 0 to 3 */
  uint8_t decimals_in_call_price;  /* byte 4 */
} CallPriceComposite;

/* any Call Price Composite at all: every byte one the checker chooses */
static void any_call_price_composite(CallPriceComposite *record) {
  for (size_t i = 0; i < 4; i++) { record->call_price[i] = arbitrary(); }
  record->decimals_in_call_price = arbitrary();
}

/* Call Price Composite to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_call_price_composite(const CallPriceComposite *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->call_price[i]; }
  wire[at++] = record->decimals_in_call_price;

  return at;
}

/* Call Price Composite off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_call_price_composite(CallPriceComposite *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->call_price[i] = wire[at++]; }
  record->decimals_in_call_price = wire[at++];

  return at;
}

/* what was read of Call Price Composite is what was written, byte for byte */
static void equal_call_price_composite(const CallPriceComposite *read, const CallPriceComposite *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->call_price[i] == written->call_price[i]); }
  assert(read->decimals_in_call_price == written->decimals_in_call_price);
}

/* Call Price Composite: written and read back, then read and written back */
static void check_call_price_composite(void) {
  CallPriceComposite sent;
  CallPriceComposite got;
  uint8_t wire[5];
  uint8_t again[5];

  any_call_price_composite(&sent);
  assert(encode_call_price_composite(&sent, wire, 0) == 5);
  assert(decode_call_price_composite(&got, wire, 0) == 5);
  equal_call_price_composite(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_call_price_composite(&got, wire, 0) == 5);
  assert(encode_call_price_composite(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Entitlement Composite: 5 bytes ------------------------------------------ */

/* Warrant entitlement scaled at runtime by DecimalsInEntitlement. 0 mantissa means Not available. */
typedef struct {
  uint8_t entitlement[4];           /* bytes 0 to 3 */
  uint8_t decimals_in_entitlement;  /* byte 4 */
} EntitlementComposite;

/* any Entitlement Composite at all: every byte one the checker chooses */
static void any_entitlement_composite(EntitlementComposite *record) {
  for (size_t i = 0; i < 4; i++) { record->entitlement[i] = arbitrary(); }
  record->decimals_in_entitlement = arbitrary();
}

/* Entitlement Composite to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_entitlement_composite(const EntitlementComposite *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entitlement[i]; }
  wire[at++] = record->decimals_in_entitlement;

  return at;
}

/* Entitlement Composite off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_entitlement_composite(EntitlementComposite *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->entitlement[i] = wire[at++]; }
  record->decimals_in_entitlement = wire[at++];

  return at;
}

/* what was read of Entitlement Composite is what was written, byte for byte */
static void equal_entitlement_composite(const EntitlementComposite *read, const EntitlementComposite *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->entitlement[i] == written->entitlement[i]); }
  assert(read->decimals_in_entitlement == written->decimals_in_entitlement);
}

/* Entitlement Composite: written and read back, then read and written back */
static void check_entitlement_composite(void) {
  EntitlementComposite sent;
  EntitlementComposite got;
  uint8_t wire[5];
  uint8_t again[5];

  any_entitlement_composite(&sent);
  assert(encode_entitlement_composite(&sent, wire, 0) == 5);
  assert(decode_entitlement_composite(&got, wire, 0) == 5);
  equal_entitlement_composite(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_entitlement_composite(&got, wire, 0) == 5);
  assert(encode_entitlement_composite(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Currency Rate Message: 12 bytes ----------------------------------------- */

/* The Currency Rate message provides the foreign exchange conversion rates between various foreign currencies and the Hong Kong dollar. */
typedef struct {
  uint8_t currency_code[3];    /* bytes 0 to 2 */
  uint8_t filler_1;            /* byte 3 */
  uint8_t currency_factor[2];  /* bytes 4 to 5 */
  uint8_t filler_2[2];         /* bytes 6 to 7 */
  uint8_t currency_rate[4];    /* bytes 8 to 11 */
} CurrencyRateMessage;

/* any Currency Rate Message at all: every byte one the checker chooses */
static void any_currency_rate_message(CurrencyRateMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = arbitrary(); }
  record->filler_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->currency_factor[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->currency_rate[i] = arbitrary(); }
}

/* Currency Rate Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_currency_rate_message(const CurrencyRateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency_code[i]; }
  wire[at++] = record->filler_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->currency_factor[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->currency_rate[i]; }

  return at;
}

/* Currency Rate Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_currency_rate_message(CurrencyRateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = wire[at++]; }
  record->filler_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->currency_factor[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->currency_rate[i] = wire[at++]; }

  return at;
}

/* what was read of Currency Rate Message is what was written, byte for byte */
static void equal_currency_rate_message(const CurrencyRateMessage *read, const CurrencyRateMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->currency_code[i] == written->currency_code[i]); }
  assert(read->filler_1 == written->filler_1);
  for (size_t i = 0; i < 2; i++) { assert(read->currency_factor[i] == written->currency_factor[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->currency_rate[i] == written->currency_rate[i]); }
}

/* Currency Rate Message: written and read back, then read and written back */
static void check_currency_rate_message(void) {
  CurrencyRateMessage sent;
  CurrencyRateMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_currency_rate_message(&sent);
  assert(encode_currency_rate_message(&sent, wire, 0) == 12);
  assert(decode_currency_rate_message(&got, wire, 0) == 12);
  equal_currency_rate_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_currency_rate_message(&got, wire, 0) == 12);
  assert(encode_currency_rate_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reference Price Message: 16 bytes --------------------------------------- */

/* Reference price, lower and upper price limits for order input during an applicable auction session (POS or CAS). Sent again when there is any change. */
typedef struct {
  uint8_t security_code[4];    /* bytes 0 to 3 */
  uint8_t reference_price[4];  /* bytes 4 to 7 */
  uint8_t lower_price[4];      /* bytes 8 to 11 */
  uint8_t upper_price[4];      /* bytes 12 to 15 */
} ReferencePriceMessage;

/* any Reference Price Message at all: every byte one the checker chooses */
static void any_reference_price_message(ReferencePriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lower_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->upper_price[i] = arbitrary(); }
}

/* Reference Price Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_reference_price_message(const ReferencePriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lower_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->upper_price[i]; }

  return at;
}

/* Reference Price Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_reference_price_message(ReferencePriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lower_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->upper_price[i] = wire[at++]; }

  return at;
}

/* what was read of Reference Price Message is what was written, byte for byte */
static void equal_reference_price_message(const ReferencePriceMessage *read, const ReferencePriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lower_price[i] == written->lower_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->upper_price[i] == written->upper_price[i]); }
}

/* Reference Price Message: written and read back, then read and written back */
static void check_reference_price_message(void) {
  ReferencePriceMessage sent;
  ReferencePriceMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_reference_price_message(&sent);
  assert(encode_reference_price_message(&sent, wire, 0) == 16);
  assert(decode_reference_price_message(&got, wire, 0) == 16);
  equal_reference_price_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_reference_price_message(&got, wire, 0) == 16);
  assert(encode_reference_price_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Response Message: 4 bytes --------------------------------------- */

/* Server acknowledgement of a client Refresh Request. */
typedef struct {
  uint8_t refresh_status;  /* byte 0 */
  uint8_t filler_3[3];     /* bytes 1 to 3 */
} RefreshResponseMessage;

/* any Refresh Response Message at all: every byte one the checker chooses */
static void any_refresh_response_message(RefreshResponseMessage *record) {
  record->refresh_status = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = arbitrary(); }
}

/* Refresh Response Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_refresh_response_message(const RefreshResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->refresh_status;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_3[i]; }

  return at;
}

/* Refresh Response Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_refresh_response_message(RefreshResponseMessage *record, const uint8_t *wire, size_t at) {
  record->refresh_status = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = wire[at++]; }

  return at;
}

/* what was read of Refresh Response Message is what was written, byte for byte */
static void equal_refresh_response_message(const RefreshResponseMessage *read, const RefreshResponseMessage *written) {
  assert(read->refresh_status == written->refresh_status);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
}

/* Refresh Response Message: written and read back, then read and written back */
static void check_refresh_response_message(void) {
  RefreshResponseMessage sent;
  RefreshResponseMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_refresh_response_message(&sent);
  assert(encode_refresh_response_message(&sent, wire, 0) == 4);
  assert(decode_refresh_response_message(&got, wire, 0) == 4);
  equal_refresh_response_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_response_message(&got, wire, 0) == 4);
  assert(encode_refresh_response_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Complete Message: 4 bytes --------------------------------------- */

/* Published at the end of a refresh cycle. Once received, the client is up to date and will resume receiving normal data flow. */
typedef struct {
  uint8_t last_internal_seq_num[4];  /* bytes 0 to 3 */
} RefreshCompleteMessage;

/* any Refresh Complete Message at all: every byte one the checker chooses */
static void any_refresh_complete_message(RefreshCompleteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->last_internal_seq_num[i] = arbitrary(); }
}

/* Refresh Complete Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_refresh_complete_message(const RefreshCompleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_internal_seq_num[i]; }

  return at;
}

/* Refresh Complete Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_refresh_complete_message(RefreshCompleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_internal_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Refresh Complete Message is what was written, byte for byte */
static void equal_refresh_complete_message(const RefreshCompleteMessage *read, const RefreshCompleteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_internal_seq_num[i] == written->last_internal_seq_num[i]); }
}

/* Refresh Complete Message: written and read back, then read and written back */
static void check_refresh_complete_message(void) {
  RefreshCompleteMessage sent;
  RefreshCompleteMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_refresh_complete_message(&sent);
  assert(encode_refresh_complete_message(&sent, wire, 0) == 4);
  assert(decode_refresh_complete_message(&got, wire, 0) == 4);
  equal_refresh_complete_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_complete_message(&got, wire, 0) == 4);
  assert(encode_refresh_complete_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Send Key Message: 528 bytes --------------------------------------------- */

/* Sent by MMDH to the client on TCP session establishment. Carries Diffie-Hellman parameters (Prime, Generator, PrimeOrderSubgroup) and the OMD Public Key concatenated with a 16-byte Initialization Vector for AES-CFB password encryption during Logon. */
typedef struct {
  uint8_t prime[128];                 /* bytes 0 to 127 */
  uint8_t generator[128];             /* bytes 128 to 255 */
  uint8_t prime_order_subgroup[128];  /* bytes 256 to 383 */
  uint8_t omd_public_key[144];        /* bytes 384 to 527 */
} SendKeyMessage;

/* any Send Key Message at all: every byte one the checker chooses */
static void any_send_key_message(SendKeyMessage *record) {
  for (size_t i = 0; i < 128; i++) { record->prime[i] = arbitrary(); }
  for (size_t i = 0; i < 128; i++) { record->generator[i] = arbitrary(); }
  for (size_t i = 0; i < 128; i++) { record->prime_order_subgroup[i] = arbitrary(); }
  for (size_t i = 0; i < 144; i++) { record->omd_public_key[i] = arbitrary(); }
}

/* Send Key Message to the wire: 528 bytes from at, returning where the next byte goes */
static size_t encode_send_key_message(const SendKeyMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 128; i++) { wire[at++] = record->prime[i]; }
  for (size_t i = 0; i < 128; i++) { wire[at++] = record->generator[i]; }
  for (size_t i = 0; i < 128; i++) { wire[at++] = record->prime_order_subgroup[i]; }
  for (size_t i = 0; i < 144; i++) { wire[at++] = record->omd_public_key[i]; }

  return at;
}

/* Send Key Message off the wire: 528 bytes from at, returning where the next byte lies */
static size_t decode_send_key_message(SendKeyMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 128; i++) { record->prime[i] = wire[at++]; }
  for (size_t i = 0; i < 128; i++) { record->generator[i] = wire[at++]; }
  for (size_t i = 0; i < 128; i++) { record->prime_order_subgroup[i] = wire[at++]; }
  for (size_t i = 0; i < 144; i++) { record->omd_public_key[i] = wire[at++]; }

  return at;
}

/* what was read of Send Key Message is what was written, byte for byte */
static void equal_send_key_message(const SendKeyMessage *read, const SendKeyMessage *written) {
  for (size_t i = 0; i < 128; i++) { assert(read->prime[i] == written->prime[i]); }
  for (size_t i = 0; i < 128; i++) { assert(read->generator[i] == written->generator[i]); }
  for (size_t i = 0; i < 128; i++) { assert(read->prime_order_subgroup[i] == written->prime_order_subgroup[i]); }
  for (size_t i = 0; i < 144; i++) { assert(read->omd_public_key[i] == written->omd_public_key[i]); }
}

/* Send Key Message: written and read back, then read and written back */
static void check_send_key_message(void) {
  SendKeyMessage sent;
  SendKeyMessage got;
  uint8_t wire[528];
  uint8_t again[528];

  any_send_key_message(&sent);
  assert(encode_send_key_message(&sent, wire, 0) == 528);
  assert(decode_send_key_message(&got, wire, 0) == 528);
  equal_send_key_message(&got, &sent);

  for (size_t i = 0; i < 528; i++) { wire[i] = arbitrary(); }
  assert(decode_send_key_message(&got, wire, 0) == 528);
  assert(encode_send_key_message(&got, again, 0) == 528);
  for (size_t i = 0; i < 528; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Message: 186 bytes ------------------------------------------------ */

/* Client-to-server message initiating authentication. Password is encrypted using an AES key derived from the Diffie-Hellman shared secret (SHA-256 hashed) with the IV received in SendKey. InternalSeqNum is 0 at start of day or the last received internal sequence number for intraday recovery. If EncryptedNewPasswordLen/EncryptedNewPassword are populated, the logon is treated as a password-change attempt. */
typedef struct {
  uint8_t username[12];                /* bytes 0 to 11 */
  uint8_t internal_seq_num[4];         /* bytes 12 to 15 */
  uint8_t client_public_key[128];      /* bytes 16 to 143 */
  uint8_t encrypted_password_len;      /* byte 144 */
  uint8_t encrypted_password[20];      /* bytes 145 to 164 */
  uint8_t encrypted_new_password_len;  /* byte 165 */
  uint8_t encrypted_new_password[20];  /* bytes 166 to 185 */
} LogonMessage;

/* any Logon Message at all: every byte one the checker chooses */
static void any_logon_message(LogonMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->internal_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 128; i++) { record->client_public_key[i] = arbitrary(); }
  record->encrypted_password_len = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->encrypted_password[i] = arbitrary(); }
  record->encrypted_new_password_len = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->encrypted_new_password[i] = arbitrary(); }
}

/* Logon Message to the wire: 186 bytes from at, returning where the next byte goes */
static size_t encode_logon_message(const LogonMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->internal_seq_num[i]; }
  for (size_t i = 0; i < 128; i++) { wire[at++] = record->client_public_key[i]; }
  wire[at++] = record->encrypted_password_len;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->encrypted_password[i]; }
  wire[at++] = record->encrypted_new_password_len;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->encrypted_new_password[i]; }

  return at;
}

/* Logon Message off the wire: 186 bytes from at, returning where the next byte lies */
static size_t decode_logon_message(LogonMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->internal_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 128; i++) { record->client_public_key[i] = wire[at++]; }
  record->encrypted_password_len = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->encrypted_password[i] = wire[at++]; }
  record->encrypted_new_password_len = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->encrypted_new_password[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Message is what was written, byte for byte */
static void equal_logon_message(const LogonMessage *read, const LogonMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->internal_seq_num[i] == written->internal_seq_num[i]); }
  for (size_t i = 0; i < 128; i++) { assert(read->client_public_key[i] == written->client_public_key[i]); }
  assert(read->encrypted_password_len == written->encrypted_password_len);
  for (size_t i = 0; i < 20; i++) { assert(read->encrypted_password[i] == written->encrypted_password[i]); }
  assert(read->encrypted_new_password_len == written->encrypted_new_password_len);
  for (size_t i = 0; i < 20; i++) { assert(read->encrypted_new_password[i] == written->encrypted_new_password[i]); }
}

/* Logon Message: written and read back, then read and written back */
static void check_logon_message(void) {
  LogonMessage sent;
  LogonMessage got;
  uint8_t wire[186];
  uint8_t again[186];

  any_logon_message(&sent);
  assert(encode_logon_message(&sent, wire, 0) == 186);
  assert(decode_logon_message(&got, wire, 0) == 186);
  equal_logon_message(&got, &sent);

  for (size_t i = 0; i < 186; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_message(&got, wire, 0) == 186);
  assert(encode_logon_message(&got, again, 0) == 186);
  for (size_t i = 0; i < 186; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Response Message: 4 bytes ----------------------------------------- */

/* Server response to a Logon request. Carries HeartBtInterval (heartbeat interval the client must honour), SessionStatus, and PasswordExpiryDays. A TCP disconnect follows SessionStatus 5, 6, 104 or 105 — client should reconnect and wait for a new SendKey before re-attempting Logon. */
typedef struct {
  uint8_t heart_bt_interval[2];  /* bytes 0 to 1 */
  uint8_t session_status;        /* byte 2 */
  uint8_t password_expiry_days;  /* byte 3 */
} LogonResponseMessage;

/* any Logon Response Message at all: every byte one the checker chooses */
static void any_logon_response_message(LogonResponseMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->heart_bt_interval[i] = arbitrary(); }
  record->session_status = arbitrary();
  record->password_expiry_days = arbitrary();
}

/* Logon Response Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_logon_response_message(const LogonResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->heart_bt_interval[i]; }
  wire[at++] = record->session_status;
  wire[at++] = record->password_expiry_days;

  return at;
}

/* Logon Response Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_logon_response_message(LogonResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->heart_bt_interval[i] = wire[at++]; }
  record->session_status = wire[at++];
  record->password_expiry_days = wire[at++];

  return at;
}

/* what was read of Logon Response Message is what was written, byte for byte */
static void equal_logon_response_message(const LogonResponseMessage *read, const LogonResponseMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->heart_bt_interval[i] == written->heart_bt_interval[i]); }
  assert(read->session_status == written->session_status);
  assert(read->password_expiry_days == written->password_expiry_days);
}

/* Logon Response Message: written and read back, then read and written back */
static void check_logon_response_message(void) {
  LogonResponseMessage sent;
  LogonResponseMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_logon_response_message(&sent);
  assert(encode_logon_response_message(&sent, wire, 0) == 4);
  assert(decode_logon_response_message(&got, wire, 0) == 4);
  equal_logon_response_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_response_message(&got, wire, 0) == 4);
  assert(encode_logon_response_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Message: 4 bytes ------------------------------------------------- */

/* Server-initiated message informing the client they have been logged out. The server follows with a TCP disconnect. */
typedef struct {
  uint8_t session_status;  /* byte 0 */
  uint8_t filler_3[3];     /* bytes 1 to 3 */
} LogoutMessage;

/* any Logout Message at all: every byte one the checker chooses */
static void any_logout_message(LogoutMessage *record) {
  record->session_status = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = arbitrary(); }
}

/* Logout Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_logout_message(const LogoutMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->session_status;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_3[i]; }

  return at;
}

/* Logout Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_logout_message(LogoutMessage *record, const uint8_t *wire, size_t at) {
  record->session_status = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = wire[at++]; }

  return at;
}

/* what was read of Logout Message is what was written, byte for byte */
static void equal_logout_message(const LogoutMessage *read, const LogoutMessage *written) {
  assert(read->session_status == written->session_status);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
}

/* Logout Message: written and read back, then read and written back */
static void check_logout_message(void) {
  LogoutMessage sent;
  LogoutMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_logout_message(&sent);
  assert(encode_logout_message(&sent, wire, 0) == 4);
  assert(decode_logout_message(&got, wire, 0) == 4);
  equal_logout_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_logout_message(&got, wire, 0) == 4);
  assert(encode_logout_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Statistics Message: 48 bytes -------------------------------------------- */

/* The Statistics message provides statistics including volume-weighted average price and turnover. Generated (excluding overseas trades) once after CTS/auction match, manual trade, odd lot trade, or trade cancel. VWAP is not populated for SS (OMD Securities Standard) clients. */
typedef struct {
  uint8_t security_code[4];             /* bytes 0 to 3 */
  uint8_t shares_traded[8];             /* bytes 4 to 11 */
  uint8_t turnover[8];                  /* bytes 12 to 19 */
  uint8_t high_price[4];                /* bytes 20 to 23 */
  uint8_t low_price[4];                 /* bytes 24 to 27 */
  uint8_t last_price[4];                /* bytes 28 to 31 */
  uint8_t filler_4[4];                  /* bytes 32 to 35 */
  uint8_t short_sell_shares_traded[4];  /* bytes 36 to 39 */
  uint8_t short_sell_turnover[8];       /* bytes 40 to 47 */
} StatisticsMessage;

/* any Statistics Message at all: every byte one the checker chooses */
static void any_statistics_message(StatisticsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->shares_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_shares_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->short_sell_turnover[i] = arbitrary(); }
}

/* Statistics Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_statistics_message(const StatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->shares_traded[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_shares_traded[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->short_sell_turnover[i]; }

  return at;
}

/* Statistics Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_statistics_message(StatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->shares_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_shares_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->short_sell_turnover[i] = wire[at++]; }

  return at;
}

/* what was read of Statistics Message is what was written, byte for byte */
static void equal_statistics_message(const StatisticsMessage *read, const StatisticsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->shares_traded[i] == written->shares_traded[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover[i] == written->turnover[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_shares_traded[i] == written->short_sell_shares_traded[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->short_sell_turnover[i] == written->short_sell_turnover[i]); }
}

/* Statistics Message: written and read back, then read and written back */
static void check_statistics_message(void) {
  StatisticsMessage sent;
  StatisticsMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_statistics_message(&sent);
  assert(encode_statistics_message(&sent, wire, 0) == 48);
  assert(decode_statistics_message(&got, wire, 0) == 48);
  equal_statistics_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_statistics_message(&got, wire, 0) == 48);
  assert(encode_statistics_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Turnover Message: 16 bytes --------------------------------------- */

/* The Market Turnover message contains the total turnover (excluding overseas trades) for all securities on a given market segment for a given trading currency. When CurrencyCode is blank, the turnover represents the total for all trading currencies, expressed in HKD. Updates disseminated around every 2 seconds during trading hours. */
typedef struct {
  uint8_t market_code[4];    /* bytes 0 to 3 */
  uint8_t currency_code[3];  /* bytes 4 to 6 */
  uint8_t filler_1;          /* byte 7 */
  uint8_t turnover[8];       /* bytes 8 to 15 */
} MarketTurnoverMessage;

/* any Market Turnover Message at all: every byte one the checker chooses */
static void any_market_turnover_message(MarketTurnoverMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = arbitrary(); }
  record->filler_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = arbitrary(); }
}

/* Market Turnover Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_market_turnover_message(const MarketTurnoverMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency_code[i]; }
  wire[at++] = record->filler_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover[i]; }

  return at;
}

/* Market Turnover Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_market_turnover_message(MarketTurnoverMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = wire[at++]; }
  record->filler_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = wire[at++]; }

  return at;
}

/* what was read of Market Turnover Message is what was written, byte for byte */
static void equal_market_turnover_message(const MarketTurnoverMessage *read, const MarketTurnoverMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_code[i] == written->market_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency_code[i] == written->currency_code[i]); }
  assert(read->filler_1 == written->filler_1);
  for (size_t i = 0; i < 8; i++) { assert(read->turnover[i] == written->turnover[i]); }
}

/* Market Turnover Message: written and read back, then read and written back */
static void check_market_turnover_message(void) {
  MarketTurnoverMessage sent;
  MarketTurnoverMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_market_turnover_message(&sent);
  assert(encode_market_turnover_message(&sent, wire, 0) == 16);
  assert(decode_market_turnover_message(&got, wire, 0) == 16);
  equal_market_turnover_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_market_turnover_message(&got, wire, 0) == 16);
  assert(encode_market_turnover_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Yield Message: 8 bytes -------------------------------------------------- */

/* The Yield message is generated for bond securities when their yield percentage changes. */
typedef struct {
  uint8_t security_code[4];  /* bytes 0 to 3 */
  uint8_t yield[4];          /* bytes 4 to 7 */
} YieldMessage;

/* any Yield Message at all: every byte one the checker chooses */
static void any_yield_message(YieldMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->yield[i] = arbitrary(); }
}

/* Yield Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_yield_message(const YieldMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->yield[i]; }

  return at;
}

/* Yield Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_yield_message(YieldMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->yield[i] = wire[at++]; }

  return at;
}

/* what was read of Yield Message is what was written, byte for byte */
static void equal_yield_message(const YieldMessage *read, const YieldMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->yield[i] == written->yield[i]); }
}

/* Yield Message: written and read back, then read and written back */
static void check_yield_message(void) {
  YieldMessage sent;
  YieldMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_yield_message(&sent);
  assert(encode_yield_message(&sent, wire, 0) == 8);
  assert(decode_yield_message(&got, wire, 0) == 8);
  equal_yield_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_yield_message(&got, wire, 0) == 8);
  assert(encode_yield_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Session Status Message: 28 bytes -------------------------------- */

/* The Trading Session Status provides information on the status of a market segment. It is sent whenever there is change of trading session. This message may be sent on a separate multicast channel from order and trade data and therefore may not be synchronized. */
typedef struct {
  uint8_t market_code[4];            /* bytes 0 to 3 */
  uint8_t filler_1;                  /* byte 4 */
  uint8_t trading_session_sub_id;    /* byte 5 */
  uint8_t trading_ses_status;        /* byte 6 */
  uint8_t trading_ses_control_flag;  /* byte 7 */
  uint8_t filler_4[4];               /* bytes 8 to 11 */
  uint8_t start_date_time[8];        /* bytes 12 to 19 */
  uint8_t end_date_time[8];          /* bytes 20 to 27 */
} TradingSessionStatusMessage;

/* any Trading Session Status Message at all: every byte one the checker chooses */
static void any_trading_session_status_message(TradingSessionStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = arbitrary(); }
  record->filler_1 = arbitrary();
  record->trading_session_sub_id = arbitrary();
  record->trading_ses_status = arbitrary();
  record->trading_ses_control_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->start_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_date_time[i] = arbitrary(); }
}

/* Trading Session Status Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_trading_session_status_message(const TradingSessionStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_code[i]; }
  wire[at++] = record->filler_1;
  wire[at++] = record->trading_session_sub_id;
  wire[at++] = record->trading_ses_status;
  wire[at++] = record->trading_ses_control_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->start_date_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_date_time[i]; }

  return at;
}

/* Trading Session Status Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_trading_session_status_message(TradingSessionStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = wire[at++]; }
  record->filler_1 = wire[at++];
  record->trading_session_sub_id = wire[at++];
  record->trading_ses_status = wire[at++];
  record->trading_ses_control_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->start_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_date_time[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Session Status Message is what was written, byte for byte */
static void equal_trading_session_status_message(const TradingSessionStatusMessage *read, const TradingSessionStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_code[i] == written->market_code[i]); }
  assert(read->filler_1 == written->filler_1);
  assert(read->trading_session_sub_id == written->trading_session_sub_id);
  assert(read->trading_ses_status == written->trading_ses_status);
  assert(read->trading_ses_control_flag == written->trading_ses_control_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->start_date_time[i] == written->start_date_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_date_time[i] == written->end_date_time[i]); }
}

/* Trading Session Status Message: written and read back, then read and written back */
static void check_trading_session_status_message(void) {
  TradingSessionStatusMessage sent;
  TradingSessionStatusMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_trading_session_status_message(&sent);
  assert(encode_trading_session_status_message(&sent, wire, 0) == 28);
  assert(decode_trading_session_status_message(&got, wire, 0) == 28);
  equal_trading_session_status_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_session_status_message(&got, wire, 0) == 28);
  assert(encode_trading_session_status_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Status Message: 8 bytes ---------------------------------------- */

/* The Security Status message is generated at the start of the business day if the security is not available for trading, and whenever a security state changes. */
typedef struct {
  uint8_t security_code[4];      /* bytes 0 to 3 */
  uint8_t suspension_indicator;  /* byte 4 */
  uint8_t filler_3[3];           /* bytes 5 to 7 */
} SecurityStatusMessage;

/* any Security Status Message at all: every byte one the checker chooses */
static void any_security_status_message(SecurityStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  record->suspension_indicator = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = arbitrary(); }
}

/* Security Status Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_security_status_message(const SecurityStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  wire[at++] = record->suspension_indicator;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_3[i]; }

  return at;
}

/* Security Status Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_security_status_message(SecurityStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  record->suspension_indicator = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = wire[at++]; }

  return at;
}

/* what was read of Security Status Message is what was written, byte for byte */
static void equal_security_status_message(const SecurityStatusMessage *read, const SecurityStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  assert(read->suspension_indicator == written->suspension_indicator);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
}

/* Security Status Message: written and read back, then read and written back */
static void check_security_status_message(void) {
  SecurityStatusMessage sent;
  SecurityStatusMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_security_status_message(&sent);
  assert(encode_security_status_message(&sent, wire, 0) == 8);
  assert(decode_security_status_message(&got, wire, 0) == 8);
  equal_security_status_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_security_status_message(&got, wire, 0) == 8);
  assert(encode_security_status_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Connect Daily Quota Balance Message: 20 bytes --------------------- */

/* Provides updates on the Northbound Daily Quota Balance (DQB) for Shanghai-Hong Kong Stock Connect and Shenzhen-Hong Kong Stock Connect separately. Updates disseminated around every 5 seconds during trading hours. */
typedef struct {
  uint8_t stock_connect_market[2];      /* bytes 0 to 1 */
  uint8_t trading_direction[2];         /* bytes 2 to 3 */
  uint8_t daily_quota_balance[8];       /* bytes 4 to 11 */
  uint8_t daily_quota_balance_time[8];  /* bytes 12 to 19 */
} StockConnectDailyQuotaBalanceMessage;

/* any Stock Connect Daily Quota Balance Message at all: every byte one the checker chooses */
static void any_stock_connect_daily_quota_balance_message(StockConnectDailyQuotaBalanceMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_connect_market[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_direction[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->daily_quota_balance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->daily_quota_balance_time[i] = arbitrary(); }
}

/* Stock Connect Daily Quota Balance Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_stock_connect_daily_quota_balance_message(const StockConnectDailyQuotaBalanceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_connect_market[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_direction[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->daily_quota_balance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->daily_quota_balance_time[i]; }

  return at;
}

/* Stock Connect Daily Quota Balance Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_stock_connect_daily_quota_balance_message(StockConnectDailyQuotaBalanceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_connect_market[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_direction[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->daily_quota_balance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->daily_quota_balance_time[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Connect Daily Quota Balance Message is what was written, byte for byte */
static void equal_stock_connect_daily_quota_balance_message(const StockConnectDailyQuotaBalanceMessage *read, const StockConnectDailyQuotaBalanceMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_connect_market[i] == written->stock_connect_market[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_direction[i] == written->trading_direction[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->daily_quota_balance[i] == written->daily_quota_balance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->daily_quota_balance_time[i] == written->daily_quota_balance_time[i]); }
}

/* Stock Connect Daily Quota Balance Message: written and read back, then read and written back */
static void check_stock_connect_daily_quota_balance_message(void) {
  StockConnectDailyQuotaBalanceMessage sent;
  StockConnectDailyQuotaBalanceMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_stock_connect_daily_quota_balance_message(&sent);
  assert(encode_stock_connect_daily_quota_balance_message(&sent, wire, 0) == 20);
  assert(decode_stock_connect_daily_quota_balance_message(&got, wire, 0) == 20);
  equal_stock_connect_daily_quota_balance_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_connect_daily_quota_balance_message(&got, wire, 0) == 20);
  assert(encode_stock_connect_daily_quota_balance_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Connect Market Turnover Message: 28 bytes ------------------------- */

/* Provides aggregate turnover under Shanghai-Hong Kong and Shenzhen-Hong Kong Stock Connect programs. Aggregate turnover provided separately for Northbound and Southbound trading. For Northbound, Buy+Sell Turnover only provided after market close (typically by 16:00). For Southbound, updates disseminated around every minute during trading hours. */
typedef struct {
  uint8_t stock_connect_market[2];  /* bytes 0 to 1 */
  uint8_t trading_direction[2];     /* bytes 2 to 3 */
  uint8_t buy_turnover[8];          /* bytes 4 to 11 */
  uint8_t sell_turnover[8];         /* bytes 12 to 19 */
  uint8_t buy_sell_turnover[8];     /* bytes 20 to 27 */
} StockConnectMarketTurnoverMessage;

/* any Stock Connect Market Turnover Message at all: every byte one the checker chooses */
static void any_stock_connect_market_turnover_message(StockConnectMarketTurnoverMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_connect_market[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_direction[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_turnover[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell_turnover[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_sell_turnover[i] = arbitrary(); }
}

/* Stock Connect Market Turnover Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_stock_connect_market_turnover_message(const StockConnectMarketTurnoverMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_connect_market[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_direction[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_turnover[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell_turnover[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_sell_turnover[i]; }

  return at;
}

/* Stock Connect Market Turnover Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_stock_connect_market_turnover_message(StockConnectMarketTurnoverMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_connect_market[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_direction[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_turnover[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell_turnover[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_sell_turnover[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Connect Market Turnover Message is what was written, byte for byte */
static void equal_stock_connect_market_turnover_message(const StockConnectMarketTurnoverMessage *read, const StockConnectMarketTurnoverMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_connect_market[i] == written->stock_connect_market[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_direction[i] == written->trading_direction[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_turnover[i] == written->buy_turnover[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell_turnover[i] == written->sell_turnover[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_sell_turnover[i] == written->buy_sell_turnover[i]); }
}

/* Stock Connect Market Turnover Message: written and read back, then read and written back */
static void check_stock_connect_market_turnover_message(void) {
  StockConnectMarketTurnoverMessage sent;
  StockConnectMarketTurnoverMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_stock_connect_market_turnover_message(&sent);
  assert(encode_stock_connect_market_turnover_message(&sent, wire, 0) == 28);
  assert(decode_stock_connect_market_turnover_message(&got, wire, 0) == 28);
  equal_stock_connect_market_turnover_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_connect_market_turnover_message(&got, wire, 0) == 28);
  assert(encode_stock_connect_market_turnover_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Ticker Message: 32 bytes ------------------------------------------ */

/* The Trade Ticker is an aggregation of several trades into one message, combining quantities of subsequent trades made on a given instrument at a given fixed price. */
typedef struct {
  uint8_t security_code[4];       /* bytes 0 to 3 */
  uint8_t ticker_id[4];           /* bytes 4 to 7 */
  uint8_t price[4];               /* bytes 8 to 11 */
  uint8_t aggregate_quantity[8];  /* bytes 12 to 19 */
  uint8_t trade_time[8];          /* bytes 20 to 27 */
  uint8_t trd_type[2];            /* bytes 28 to 29 */
  uint8_t trd_cancel_flag;        /* byte 30 */
  uint8_t filler_1;               /* byte 31 */
} TradeTickerMessage;

/* any Trade Ticker Message at all: every byte one the checker chooses */
static void any_trade_ticker_message(TradeTickerMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ticker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->aggregate_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  record->trd_cancel_flag = arbitrary();
  record->filler_1 = arbitrary();
}

/* Trade Ticker Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_trade_ticker_message(const TradeTickerMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ticker_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->aggregate_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  wire[at++] = record->trd_cancel_flag;
  wire[at++] = record->filler_1;

  return at;
}

/* Trade Ticker Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_trade_ticker_message(TradeTickerMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ticker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->aggregate_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  record->trd_cancel_flag = wire[at++];
  record->filler_1 = wire[at++];

  return at;
}

/* what was read of Trade Ticker Message is what was written, byte for byte */
static void equal_trade_ticker_message(const TradeTickerMessage *read, const TradeTickerMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ticker_id[i] == written->ticker_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->aggregate_quantity[i] == written->aggregate_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_time[i] == written->trade_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  assert(read->trd_cancel_flag == written->trd_cancel_flag);
  assert(read->filler_1 == written->filler_1);
}

/* Trade Ticker Message: written and read back, then read and written back */
static void check_trade_ticker_message(void) {
  TradeTickerMessage sent;
  TradeTickerMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_trade_ticker_message(&sent);
  assert(encode_trade_ticker_message(&sent, wire, 0) == 32);
  assert(decode_trade_ticker_message(&got, wire, 0) == 32);
  equal_trade_ticker_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_ticker_message(&got, wire, 0) == 32);
  assert(encode_trade_ticker_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Vcm Trigger Message: 32 bytes ------------------------------------------- */

/* The VCM Trigger message is generated whenever a cooling off period is triggered by Volatility Control Mechanism (VCM). */
typedef struct {
  uint8_t security_code[4];           /* bytes 0 to 3 */
  uint8_t cooling_off_start_time[8];  /* bytes 4 to 11 */
  uint8_t cooling_off_end_time[8];    /* bytes 12 to 19 */
  uint8_t vcm_reference_price[4];     /* bytes 20 to 23 */
  uint8_t vcm_lower_price[4];         /* bytes 24 to 27 */
  uint8_t vcm_upper_price[4];         /* bytes 28 to 31 */
} VcmTriggerMessage;

/* any Vcm Trigger Message at all: every byte one the checker chooses */
static void any_vcm_trigger_message(VcmTriggerMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cooling_off_start_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cooling_off_end_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->vcm_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->vcm_lower_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->vcm_upper_price[i] = arbitrary(); }
}

/* Vcm Trigger Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_vcm_trigger_message(const VcmTriggerMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cooling_off_start_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cooling_off_end_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->vcm_reference_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->vcm_lower_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->vcm_upper_price[i]; }

  return at;
}

/* Vcm Trigger Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_vcm_trigger_message(VcmTriggerMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cooling_off_start_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cooling_off_end_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->vcm_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->vcm_lower_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->vcm_upper_price[i] = wire[at++]; }

  return at;
}

/* what was read of Vcm Trigger Message is what was written, byte for byte */
static void equal_vcm_trigger_message(const VcmTriggerMessage *read, const VcmTriggerMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cooling_off_start_time[i] == written->cooling_off_start_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cooling_off_end_time[i] == written->cooling_off_end_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->vcm_reference_price[i] == written->vcm_reference_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->vcm_lower_price[i] == written->vcm_lower_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->vcm_upper_price[i] == written->vcm_upper_price[i]); }
}

/* Vcm Trigger Message: written and read back, then read and written back */
static void check_vcm_trigger_message(void) {
  VcmTriggerMessage sent;
  VcmTriggerMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_vcm_trigger_message(&sent);
  assert(encode_vcm_trigger_message(&sent, wire, 0) == 32);
  assert(decode_vcm_trigger_message(&got, wire, 0) == 32);
  equal_vcm_trigger_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_vcm_trigger_message(&got, wire, 0) == 32);
  assert(encode_vcm_trigger_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_add_odd_lot_order_message();
  check_closing_price_message();
  check_delete_odd_lot_order_message();
  check_index_definition_message();
  check_index_data_message();
  check_indicative_equilibrium_price_message();
  check_nominal_price_message();
  check_order_imbalance_message();
  check_market_definition_message();
  check_face_value_composite();
  check_call_price_composite();
  check_entitlement_composite();
  check_currency_rate_message();
  check_reference_price_message();
  check_refresh_response_message();
  check_refresh_complete_message();
  check_send_key_message();
  check_logon_message();
  check_logon_response_message();
  check_logout_message();
  check_statistics_message();
  check_market_turnover_message();
  check_yield_message();
  check_trading_session_status_message();
  check_security_status_message();
  check_stock_connect_daily_quota_balance_message();
  check_stock_connect_market_turnover_message();
  check_trade_ticker_message();
  check_vcm_trigger_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
