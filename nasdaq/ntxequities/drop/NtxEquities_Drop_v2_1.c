// nasdaq/ntxequities/drop/NtxEquities_Drop_v2_1.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Drop
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

/* ---- Message Header: 11 bytes ------------------------------------------------ */

/* Time Stamp and Type opening every Drop message line */
typedef struct {
  uint8_t time_stamp[9];  /* bytes 0 to 8 */
  uint8_t comma;          /* byte 9 */
  uint8_t message_type;   /* byte 10 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 9; i++) { record->time_stamp[i] = arbitrary(); }
  record->comma = arbitrary();
  record->message_type = arbitrary();
}

/* Message Header to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->time_stamp[i]; }
  wire[at++] = record->comma;
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->time_stamp[i] = wire[at++]; }
  record->comma = wire[at++];
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  assert(read->comma == written->comma);
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[11];
  uint8_t again[11];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 11);
  assert(decode_message_header(&got, wire, 0) == 11);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 11);
  assert(encode_message_header(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Accepted Message: 99 bytes ------------------------------------ */

/* New order accepted. */
typedef struct {
  uint8_t separator_1;         /* byte 0 */
  uint8_t source[6];           /* bytes 1 to 6 */
  uint8_t separator_2;         /* byte 7 */
  uint8_t user[4];             /* bytes 8 to 11 */
  uint8_t separator_3;         /* byte 12 */
  uint8_t token[10];           /* bytes 13 to 22 */
  uint8_t separator_4;         /* byte 23 */
  uint8_t replaced_token[10];  /* bytes 24 to 33 */
  uint8_t separator_5;         /* byte 34 */
  uint8_t buy_sell;            /* byte 35 */
  uint8_t separator_6;         /* byte 36 */
  uint8_t shares[6];           /* bytes 37 to 42 */
  uint8_t separator_7;         /* byte 43 */
  uint8_t stock[6];            /* bytes 44 to 49 */
  uint8_t separator_8;         /* byte 50 */
  uint8_t price[11];           /* bytes 51 to 61 */
  uint8_t separator_9;         /* byte 62 */
  uint8_t firm[4];             /* bytes 63 to 66 */
  uint8_t separator_10;        /* byte 67 */
  uint8_t reference[12];       /* bytes 68 to 79 */
  uint8_t separator_11;        /* byte 80 */
  uint8_t time_in_force[12];   /* bytes 81 to 92 */
  uint8_t separator_12;        /* byte 93 */
  uint8_t capacity;            /* byte 94 */
  uint8_t separator_13;        /* byte 95 */
  uint8_t liquidity_code;      /* byte 96 */
  uint8_t separator_14;        /* byte 97 */
  uint8_t clearing_code;       /* byte 98 */
} NewOrderAcceptedMessage;

/* any New Order Accepted Message at all: every byte one the checker chooses */
static void any_new_order_accepted_message(NewOrderAcceptedMessage *record) {
  record->separator_1 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->source[i] = arbitrary(); }
  record->separator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->user[i] = arbitrary(); }
  record->separator_3 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->token[i] = arbitrary(); }
  record->separator_4 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = arbitrary(); }
  record->separator_5 = arbitrary();
  record->buy_sell = arbitrary();
  record->separator_6 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  record->separator_7 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->stock[i] = arbitrary(); }
  record->separator_8 = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->price[i] = arbitrary(); }
  record->separator_9 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->firm[i] = arbitrary(); }
  record->separator_10 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->reference[i] = arbitrary(); }
  record->separator_11 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->time_in_force[i] = arbitrary(); }
  record->separator_12 = arbitrary();
  record->capacity = arbitrary();
  record->separator_13 = arbitrary();
  record->liquidity_code = arbitrary();
  record->separator_14 = arbitrary();
  record->clearing_code = arbitrary();
}

/* New Order Accepted Message to the wire: 99 bytes from at, returning where the next byte goes */
static size_t encode_new_order_accepted_message(const NewOrderAcceptedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->separator_1;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->source[i]; }
  wire[at++] = record->separator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user[i]; }
  wire[at++] = record->separator_3;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->token[i]; }
  wire[at++] = record->separator_4;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->replaced_token[i]; }
  wire[at++] = record->separator_5;
  wire[at++] = record->buy_sell;
  wire[at++] = record->separator_6;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  wire[at++] = record->separator_7;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->separator_8;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->separator_9;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm[i]; }
  wire[at++] = record->separator_10;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reference[i]; }
  wire[at++] = record->separator_11;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->time_in_force[i]; }
  wire[at++] = record->separator_12;
  wire[at++] = record->capacity;
  wire[at++] = record->separator_13;
  wire[at++] = record->liquidity_code;
  wire[at++] = record->separator_14;
  wire[at++] = record->clearing_code;

  return at;
}

/* New Order Accepted Message off the wire: 99 bytes from at, returning where the next byte lies */
static size_t decode_new_order_accepted_message(NewOrderAcceptedMessage *record, const uint8_t *wire, size_t at) {
  record->separator_1 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->source[i] = wire[at++]; }
  record->separator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->user[i] = wire[at++]; }
  record->separator_3 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->token[i] = wire[at++]; }
  record->separator_4 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = wire[at++]; }
  record->separator_5 = wire[at++];
  record->buy_sell = wire[at++];
  record->separator_6 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  record->separator_7 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->stock[i] = wire[at++]; }
  record->separator_8 = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->price[i] = wire[at++]; }
  record->separator_9 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->firm[i] = wire[at++]; }
  record->separator_10 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->reference[i] = wire[at++]; }
  record->separator_11 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->time_in_force[i] = wire[at++]; }
  record->separator_12 = wire[at++];
  record->capacity = wire[at++];
  record->separator_13 = wire[at++];
  record->liquidity_code = wire[at++];
  record->separator_14 = wire[at++];
  record->clearing_code = wire[at++];

  return at;
}

/* what was read of New Order Accepted Message is what was written, byte for byte */
static void equal_new_order_accepted_message(const NewOrderAcceptedMessage *read, const NewOrderAcceptedMessage *written) {
  assert(read->separator_1 == written->separator_1);
  for (size_t i = 0; i < 6; i++) { assert(read->source[i] == written->source[i]); }
  assert(read->separator_2 == written->separator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->user[i] == written->user[i]); }
  assert(read->separator_3 == written->separator_3);
  for (size_t i = 0; i < 10; i++) { assert(read->token[i] == written->token[i]); }
  assert(read->separator_4 == written->separator_4);
  for (size_t i = 0; i < 10; i++) { assert(read->replaced_token[i] == written->replaced_token[i]); }
  assert(read->separator_5 == written->separator_5);
  assert(read->buy_sell == written->buy_sell);
  assert(read->separator_6 == written->separator_6);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  assert(read->separator_7 == written->separator_7);
  for (size_t i = 0; i < 6; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->separator_8 == written->separator_8);
  for (size_t i = 0; i < 11; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->separator_9 == written->separator_9);
  for (size_t i = 0; i < 4; i++) { assert(read->firm[i] == written->firm[i]); }
  assert(read->separator_10 == written->separator_10);
  for (size_t i = 0; i < 12; i++) { assert(read->reference[i] == written->reference[i]); }
  assert(read->separator_11 == written->separator_11);
  for (size_t i = 0; i < 12; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  assert(read->separator_12 == written->separator_12);
  assert(read->capacity == written->capacity);
  assert(read->separator_13 == written->separator_13);
  assert(read->liquidity_code == written->liquidity_code);
  assert(read->separator_14 == written->separator_14);
  assert(read->clearing_code == written->clearing_code);
}

/* New Order Accepted Message: written and read back, then read and written back */
static void check_new_order_accepted_message(void) {
  NewOrderAcceptedMessage sent;
  NewOrderAcceptedMessage got;
  uint8_t wire[99];
  uint8_t again[99];

  any_new_order_accepted_message(&sent);
  assert(encode_new_order_accepted_message(&sent, wire, 0) == 99);
  assert(decode_new_order_accepted_message(&got, wire, 0) == 99);
  equal_new_order_accepted_message(&got, &sent);

  for (size_t i = 0; i < 99; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_accepted_message(&got, wire, 0) == 99);
  assert(encode_new_order_accepted_message(&got, again, 0) == 99);
  for (size_t i = 0; i < 99; i++) { assert(again[i] == wire[i]); }
}

/* ---- Existing Order Executed Message: 99 bytes ------------------------------- */

/* Existing order executed. */
typedef struct {
  uint8_t separator_1;         /* byte 0 */
  uint8_t source[6];           /* bytes 1 to 6 */
  uint8_t separator_2;         /* byte 7 */
  uint8_t user[4];             /* bytes 8 to 11 */
  uint8_t separator_3;         /* byte 12 */
  uint8_t token[10];           /* bytes 13 to 22 */
  uint8_t separator_4;         /* byte 23 */
  uint8_t replaced_token[10];  /* bytes 24 to 33 */
  uint8_t separator_5;         /* byte 34 */
  uint8_t buy_sell;            /* byte 35 */
  uint8_t separator_6;         /* byte 36 */
  uint8_t shares[6];           /* bytes 37 to 42 */
  uint8_t separator_7;         /* byte 43 */
  uint8_t stock[6];            /* bytes 44 to 49 */
  uint8_t separator_8;         /* byte 50 */
  uint8_t price[11];           /* bytes 51 to 61 */
  uint8_t separator_9;         /* byte 62 */
  uint8_t firm[4];             /* bytes 63 to 66 */
  uint8_t separator_10;        /* byte 67 */
  uint8_t reference[12];       /* bytes 68 to 79 */
  uint8_t separator_11;        /* byte 80 */
  uint8_t match_number[12];    /* bytes 81 to 92 */
  uint8_t separator_12;        /* byte 93 */
  uint8_t capacity;            /* byte 94 */
  uint8_t separator_13;        /* byte 95 */
  uint8_t liquidity_code;      /* byte 96 */
  uint8_t separator_14;        /* byte 97 */
  uint8_t clearing_code;       /* byte 98 */
} ExistingOrderExecutedMessage;

/* any Existing Order Executed Message at all: every byte one the checker chooses */
static void any_existing_order_executed_message(ExistingOrderExecutedMessage *record) {
  record->separator_1 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->source[i] = arbitrary(); }
  record->separator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->user[i] = arbitrary(); }
  record->separator_3 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->token[i] = arbitrary(); }
  record->separator_4 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = arbitrary(); }
  record->separator_5 = arbitrary();
  record->buy_sell = arbitrary();
  record->separator_6 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  record->separator_7 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->stock[i] = arbitrary(); }
  record->separator_8 = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->price[i] = arbitrary(); }
  record->separator_9 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->firm[i] = arbitrary(); }
  record->separator_10 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->reference[i] = arbitrary(); }
  record->separator_11 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = arbitrary(); }
  record->separator_12 = arbitrary();
  record->capacity = arbitrary();
  record->separator_13 = arbitrary();
  record->liquidity_code = arbitrary();
  record->separator_14 = arbitrary();
  record->clearing_code = arbitrary();
}

/* Existing Order Executed Message to the wire: 99 bytes from at, returning where the next byte goes */
static size_t encode_existing_order_executed_message(const ExistingOrderExecutedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->separator_1;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->source[i]; }
  wire[at++] = record->separator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user[i]; }
  wire[at++] = record->separator_3;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->token[i]; }
  wire[at++] = record->separator_4;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->replaced_token[i]; }
  wire[at++] = record->separator_5;
  wire[at++] = record->buy_sell;
  wire[at++] = record->separator_6;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  wire[at++] = record->separator_7;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->separator_8;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->separator_9;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm[i]; }
  wire[at++] = record->separator_10;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reference[i]; }
  wire[at++] = record->separator_11;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->separator_12;
  wire[at++] = record->capacity;
  wire[at++] = record->separator_13;
  wire[at++] = record->liquidity_code;
  wire[at++] = record->separator_14;
  wire[at++] = record->clearing_code;

  return at;
}

/* Existing Order Executed Message off the wire: 99 bytes from at, returning where the next byte lies */
static size_t decode_existing_order_executed_message(ExistingOrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  record->separator_1 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->source[i] = wire[at++]; }
  record->separator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->user[i] = wire[at++]; }
  record->separator_3 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->token[i] = wire[at++]; }
  record->separator_4 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = wire[at++]; }
  record->separator_5 = wire[at++];
  record->buy_sell = wire[at++];
  record->separator_6 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  record->separator_7 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->stock[i] = wire[at++]; }
  record->separator_8 = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->price[i] = wire[at++]; }
  record->separator_9 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->firm[i] = wire[at++]; }
  record->separator_10 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->reference[i] = wire[at++]; }
  record->separator_11 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = wire[at++]; }
  record->separator_12 = wire[at++];
  record->capacity = wire[at++];
  record->separator_13 = wire[at++];
  record->liquidity_code = wire[at++];
  record->separator_14 = wire[at++];
  record->clearing_code = wire[at++];

  return at;
}

/* what was read of Existing Order Executed Message is what was written, byte for byte */
static void equal_existing_order_executed_message(const ExistingOrderExecutedMessage *read, const ExistingOrderExecutedMessage *written) {
  assert(read->separator_1 == written->separator_1);
  for (size_t i = 0; i < 6; i++) { assert(read->source[i] == written->source[i]); }
  assert(read->separator_2 == written->separator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->user[i] == written->user[i]); }
  assert(read->separator_3 == written->separator_3);
  for (size_t i = 0; i < 10; i++) { assert(read->token[i] == written->token[i]); }
  assert(read->separator_4 == written->separator_4);
  for (size_t i = 0; i < 10; i++) { assert(read->replaced_token[i] == written->replaced_token[i]); }
  assert(read->separator_5 == written->separator_5);
  assert(read->buy_sell == written->buy_sell);
  assert(read->separator_6 == written->separator_6);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  assert(read->separator_7 == written->separator_7);
  for (size_t i = 0; i < 6; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->separator_8 == written->separator_8);
  for (size_t i = 0; i < 11; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->separator_9 == written->separator_9);
  for (size_t i = 0; i < 4; i++) { assert(read->firm[i] == written->firm[i]); }
  assert(read->separator_10 == written->separator_10);
  for (size_t i = 0; i < 12; i++) { assert(read->reference[i] == written->reference[i]); }
  assert(read->separator_11 == written->separator_11);
  for (size_t i = 0; i < 12; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->separator_12 == written->separator_12);
  assert(read->capacity == written->capacity);
  assert(read->separator_13 == written->separator_13);
  assert(read->liquidity_code == written->liquidity_code);
  assert(read->separator_14 == written->separator_14);
  assert(read->clearing_code == written->clearing_code);
}

/* Existing Order Executed Message: written and read back, then read and written back */
static void check_existing_order_executed_message(void) {
  ExistingOrderExecutedMessage sent;
  ExistingOrderExecutedMessage got;
  uint8_t wire[99];
  uint8_t again[99];

  any_existing_order_executed_message(&sent);
  assert(encode_existing_order_executed_message(&sent, wire, 0) == 99);
  assert(decode_existing_order_executed_message(&got, wire, 0) == 99);
  equal_existing_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 99; i++) { wire[i] = arbitrary(); }
  assert(decode_existing_order_executed_message(&got, wire, 0) == 99);
  assert(encode_existing_order_executed_message(&got, again, 0) == 99);
  for (size_t i = 0; i < 99; i++) { assert(again[i] == wire[i]); }
}

/* ---- Existing Order Canceled Message: 99 bytes ------------------------------- */

/* Existing order canceled. */
typedef struct {
  uint8_t separator_1;         /* byte 0 */
  uint8_t source[6];           /* bytes 1 to 6 */
  uint8_t separator_2;         /* byte 7 */
  uint8_t user[4];             /* bytes 8 to 11 */
  uint8_t separator_3;         /* byte 12 */
  uint8_t token[10];           /* bytes 13 to 22 */
  uint8_t separator_4;         /* byte 23 */
  uint8_t replaced_token[10];  /* bytes 24 to 33 */
  uint8_t separator_5;         /* byte 34 */
  uint8_t buy_sell;            /* byte 35 */
  uint8_t separator_6;         /* byte 36 */
  uint8_t shares[6];           /* bytes 37 to 42 */
  uint8_t separator_7;         /* byte 43 */
  uint8_t stock[6];            /* bytes 44 to 49 */
  uint8_t separator_8;         /* byte 50 */
  uint8_t price[11];           /* bytes 51 to 61 */
  uint8_t separator_9;         /* byte 62 */
  uint8_t firm[4];             /* bytes 63 to 66 */
  uint8_t separator_10;        /* byte 67 */
  uint8_t reference[12];       /* bytes 68 to 79 */
  uint8_t separator_11;        /* byte 80 */
  uint8_t time_in_force[12];   /* bytes 81 to 92 */
  uint8_t separator_12;        /* byte 93 */
  uint8_t capacity;            /* byte 94 */
  uint8_t separator_13;        /* byte 95 */
  uint8_t liquidity_code;      /* byte 96 */
  uint8_t separator_14;        /* byte 97 */
  uint8_t clearing_code;       /* byte 98 */
} ExistingOrderCanceledMessage;

/* any Existing Order Canceled Message at all: every byte one the checker chooses */
static void any_existing_order_canceled_message(ExistingOrderCanceledMessage *record) {
  record->separator_1 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->source[i] = arbitrary(); }
  record->separator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->user[i] = arbitrary(); }
  record->separator_3 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->token[i] = arbitrary(); }
  record->separator_4 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = arbitrary(); }
  record->separator_5 = arbitrary();
  record->buy_sell = arbitrary();
  record->separator_6 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  record->separator_7 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->stock[i] = arbitrary(); }
  record->separator_8 = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->price[i] = arbitrary(); }
  record->separator_9 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->firm[i] = arbitrary(); }
  record->separator_10 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->reference[i] = arbitrary(); }
  record->separator_11 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->time_in_force[i] = arbitrary(); }
  record->separator_12 = arbitrary();
  record->capacity = arbitrary();
  record->separator_13 = arbitrary();
  record->liquidity_code = arbitrary();
  record->separator_14 = arbitrary();
  record->clearing_code = arbitrary();
}

/* Existing Order Canceled Message to the wire: 99 bytes from at, returning where the next byte goes */
static size_t encode_existing_order_canceled_message(const ExistingOrderCanceledMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->separator_1;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->source[i]; }
  wire[at++] = record->separator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user[i]; }
  wire[at++] = record->separator_3;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->token[i]; }
  wire[at++] = record->separator_4;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->replaced_token[i]; }
  wire[at++] = record->separator_5;
  wire[at++] = record->buy_sell;
  wire[at++] = record->separator_6;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  wire[at++] = record->separator_7;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->separator_8;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->separator_9;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm[i]; }
  wire[at++] = record->separator_10;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reference[i]; }
  wire[at++] = record->separator_11;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->time_in_force[i]; }
  wire[at++] = record->separator_12;
  wire[at++] = record->capacity;
  wire[at++] = record->separator_13;
  wire[at++] = record->liquidity_code;
  wire[at++] = record->separator_14;
  wire[at++] = record->clearing_code;

  return at;
}

/* Existing Order Canceled Message off the wire: 99 bytes from at, returning where the next byte lies */
static size_t decode_existing_order_canceled_message(ExistingOrderCanceledMessage *record, const uint8_t *wire, size_t at) {
  record->separator_1 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->source[i] = wire[at++]; }
  record->separator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->user[i] = wire[at++]; }
  record->separator_3 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->token[i] = wire[at++]; }
  record->separator_4 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = wire[at++]; }
  record->separator_5 = wire[at++];
  record->buy_sell = wire[at++];
  record->separator_6 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  record->separator_7 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->stock[i] = wire[at++]; }
  record->separator_8 = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->price[i] = wire[at++]; }
  record->separator_9 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->firm[i] = wire[at++]; }
  record->separator_10 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->reference[i] = wire[at++]; }
  record->separator_11 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->time_in_force[i] = wire[at++]; }
  record->separator_12 = wire[at++];
  record->capacity = wire[at++];
  record->separator_13 = wire[at++];
  record->liquidity_code = wire[at++];
  record->separator_14 = wire[at++];
  record->clearing_code = wire[at++];

  return at;
}

/* what was read of Existing Order Canceled Message is what was written, byte for byte */
static void equal_existing_order_canceled_message(const ExistingOrderCanceledMessage *read, const ExistingOrderCanceledMessage *written) {
  assert(read->separator_1 == written->separator_1);
  for (size_t i = 0; i < 6; i++) { assert(read->source[i] == written->source[i]); }
  assert(read->separator_2 == written->separator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->user[i] == written->user[i]); }
  assert(read->separator_3 == written->separator_3);
  for (size_t i = 0; i < 10; i++) { assert(read->token[i] == written->token[i]); }
  assert(read->separator_4 == written->separator_4);
  for (size_t i = 0; i < 10; i++) { assert(read->replaced_token[i] == written->replaced_token[i]); }
  assert(read->separator_5 == written->separator_5);
  assert(read->buy_sell == written->buy_sell);
  assert(read->separator_6 == written->separator_6);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  assert(read->separator_7 == written->separator_7);
  for (size_t i = 0; i < 6; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->separator_8 == written->separator_8);
  for (size_t i = 0; i < 11; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->separator_9 == written->separator_9);
  for (size_t i = 0; i < 4; i++) { assert(read->firm[i] == written->firm[i]); }
  assert(read->separator_10 == written->separator_10);
  for (size_t i = 0; i < 12; i++) { assert(read->reference[i] == written->reference[i]); }
  assert(read->separator_11 == written->separator_11);
  for (size_t i = 0; i < 12; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  assert(read->separator_12 == written->separator_12);
  assert(read->capacity == written->capacity);
  assert(read->separator_13 == written->separator_13);
  assert(read->liquidity_code == written->liquidity_code);
  assert(read->separator_14 == written->separator_14);
  assert(read->clearing_code == written->clearing_code);
}

/* Existing Order Canceled Message: written and read back, then read and written back */
static void check_existing_order_canceled_message(void) {
  ExistingOrderCanceledMessage sent;
  ExistingOrderCanceledMessage got;
  uint8_t wire[99];
  uint8_t again[99];

  any_existing_order_canceled_message(&sent);
  assert(encode_existing_order_canceled_message(&sent, wire, 0) == 99);
  assert(decode_existing_order_canceled_message(&got, wire, 0) == 99);
  equal_existing_order_canceled_message(&got, &sent);

  for (size_t i = 0; i < 99; i++) { wire[i] = arbitrary(); }
  assert(decode_existing_order_canceled_message(&got, wire, 0) == 99);
  assert(encode_existing_order_canceled_message(&got, again, 0) == 99);
  for (size_t i = 0; i < 99; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Execution Broken Message: 99 bytes ----------------------------- */

/* Previous execution broken. */
typedef struct {
  uint8_t separator_1;         /* byte 0 */
  uint8_t source[6];           /* bytes 1 to 6 */
  uint8_t separator_2;         /* byte 7 */
  uint8_t user[4];             /* bytes 8 to 11 */
  uint8_t separator_3;         /* byte 12 */
  uint8_t token[10];           /* bytes 13 to 22 */
  uint8_t separator_4;         /* byte 23 */
  uint8_t replaced_token[10];  /* bytes 24 to 33 */
  uint8_t separator_5;         /* byte 34 */
  uint8_t buy_sell;            /* byte 35 */
  uint8_t separator_6;         /* byte 36 */
  uint8_t shares[6];           /* bytes 37 to 42 */
  uint8_t separator_7;         /* byte 43 */
  uint8_t stock[6];            /* bytes 44 to 49 */
  uint8_t separator_8;         /* byte 50 */
  uint8_t price[11];           /* bytes 51 to 61 */
  uint8_t separator_9;         /* byte 62 */
  uint8_t firm[4];             /* bytes 63 to 66 */
  uint8_t separator_10;        /* byte 67 */
  uint8_t reference[12];       /* bytes 68 to 79 */
  uint8_t separator_11;        /* byte 80 */
  uint8_t match_number[12];    /* bytes 81 to 92 */
  uint8_t separator_12;        /* byte 93 */
  uint8_t capacity;            /* byte 94 */
  uint8_t separator_13;        /* byte 95 */
  uint8_t liquidity_code;      /* byte 96 */
  uint8_t separator_14;        /* byte 97 */
  uint8_t clearing_code;       /* byte 98 */
} PreviousExecutionBrokenMessage;

/* any Previous Execution Broken Message at all: every byte one the checker chooses */
static void any_previous_execution_broken_message(PreviousExecutionBrokenMessage *record) {
  record->separator_1 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->source[i] = arbitrary(); }
  record->separator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->user[i] = arbitrary(); }
  record->separator_3 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->token[i] = arbitrary(); }
  record->separator_4 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = arbitrary(); }
  record->separator_5 = arbitrary();
  record->buy_sell = arbitrary();
  record->separator_6 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  record->separator_7 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->stock[i] = arbitrary(); }
  record->separator_8 = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->price[i] = arbitrary(); }
  record->separator_9 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->firm[i] = arbitrary(); }
  record->separator_10 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->reference[i] = arbitrary(); }
  record->separator_11 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = arbitrary(); }
  record->separator_12 = arbitrary();
  record->capacity = arbitrary();
  record->separator_13 = arbitrary();
  record->liquidity_code = arbitrary();
  record->separator_14 = arbitrary();
  record->clearing_code = arbitrary();
}

/* Previous Execution Broken Message to the wire: 99 bytes from at, returning where the next byte goes */
static size_t encode_previous_execution_broken_message(const PreviousExecutionBrokenMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->separator_1;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->source[i]; }
  wire[at++] = record->separator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user[i]; }
  wire[at++] = record->separator_3;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->token[i]; }
  wire[at++] = record->separator_4;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->replaced_token[i]; }
  wire[at++] = record->separator_5;
  wire[at++] = record->buy_sell;
  wire[at++] = record->separator_6;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  wire[at++] = record->separator_7;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->separator_8;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->separator_9;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm[i]; }
  wire[at++] = record->separator_10;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reference[i]; }
  wire[at++] = record->separator_11;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->separator_12;
  wire[at++] = record->capacity;
  wire[at++] = record->separator_13;
  wire[at++] = record->liquidity_code;
  wire[at++] = record->separator_14;
  wire[at++] = record->clearing_code;

  return at;
}

/* Previous Execution Broken Message off the wire: 99 bytes from at, returning where the next byte lies */
static size_t decode_previous_execution_broken_message(PreviousExecutionBrokenMessage *record, const uint8_t *wire, size_t at) {
  record->separator_1 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->source[i] = wire[at++]; }
  record->separator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->user[i] = wire[at++]; }
  record->separator_3 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->token[i] = wire[at++]; }
  record->separator_4 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = wire[at++]; }
  record->separator_5 = wire[at++];
  record->buy_sell = wire[at++];
  record->separator_6 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  record->separator_7 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->stock[i] = wire[at++]; }
  record->separator_8 = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->price[i] = wire[at++]; }
  record->separator_9 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->firm[i] = wire[at++]; }
  record->separator_10 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->reference[i] = wire[at++]; }
  record->separator_11 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = wire[at++]; }
  record->separator_12 = wire[at++];
  record->capacity = wire[at++];
  record->separator_13 = wire[at++];
  record->liquidity_code = wire[at++];
  record->separator_14 = wire[at++];
  record->clearing_code = wire[at++];

  return at;
}

/* what was read of Previous Execution Broken Message is what was written, byte for byte */
static void equal_previous_execution_broken_message(const PreviousExecutionBrokenMessage *read, const PreviousExecutionBrokenMessage *written) {
  assert(read->separator_1 == written->separator_1);
  for (size_t i = 0; i < 6; i++) { assert(read->source[i] == written->source[i]); }
  assert(read->separator_2 == written->separator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->user[i] == written->user[i]); }
  assert(read->separator_3 == written->separator_3);
  for (size_t i = 0; i < 10; i++) { assert(read->token[i] == written->token[i]); }
  assert(read->separator_4 == written->separator_4);
  for (size_t i = 0; i < 10; i++) { assert(read->replaced_token[i] == written->replaced_token[i]); }
  assert(read->separator_5 == written->separator_5);
  assert(read->buy_sell == written->buy_sell);
  assert(read->separator_6 == written->separator_6);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  assert(read->separator_7 == written->separator_7);
  for (size_t i = 0; i < 6; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->separator_8 == written->separator_8);
  for (size_t i = 0; i < 11; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->separator_9 == written->separator_9);
  for (size_t i = 0; i < 4; i++) { assert(read->firm[i] == written->firm[i]); }
  assert(read->separator_10 == written->separator_10);
  for (size_t i = 0; i < 12; i++) { assert(read->reference[i] == written->reference[i]); }
  assert(read->separator_11 == written->separator_11);
  for (size_t i = 0; i < 12; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->separator_12 == written->separator_12);
  assert(read->capacity == written->capacity);
  assert(read->separator_13 == written->separator_13);
  assert(read->liquidity_code == written->liquidity_code);
  assert(read->separator_14 == written->separator_14);
  assert(read->clearing_code == written->clearing_code);
}

/* Previous Execution Broken Message: written and read back, then read and written back */
static void check_previous_execution_broken_message(void) {
  PreviousExecutionBrokenMessage sent;
  PreviousExecutionBrokenMessage got;
  uint8_t wire[99];
  uint8_t again[99];

  any_previous_execution_broken_message(&sent);
  assert(encode_previous_execution_broken_message(&sent, wire, 0) == 99);
  assert(decode_previous_execution_broken_message(&got, wire, 0) == 99);
  equal_previous_execution_broken_message(&got, &sent);

  for (size_t i = 0; i < 99; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_execution_broken_message(&got, wire, 0) == 99);
  assert(encode_previous_execution_broken_message(&got, again, 0) == 99);
  for (size_t i = 0; i < 99; i++) { assert(again[i] == wire[i]); }
}

/* ---- Existing Order Replaced Message: 99 bytes ------------------------------- */

/* Existing order replaced. */
typedef struct {
  uint8_t separator_1;         /* byte 0 */
  uint8_t source[6];           /* bytes 1 to 6 */
  uint8_t separator_2;         /* byte 7 */
  uint8_t user[4];             /* bytes 8 to 11 */
  uint8_t separator_3;         /* byte 12 */
  uint8_t token[10];           /* bytes 13 to 22 */
  uint8_t separator_4;         /* byte 23 */
  uint8_t replaced_token[10];  /* bytes 24 to 33 */
  uint8_t separator_5;         /* byte 34 */
  uint8_t buy_sell;            /* byte 35 */
  uint8_t separator_6;         /* byte 36 */
  uint8_t shares[6];           /* bytes 37 to 42 */
  uint8_t separator_7;         /* byte 43 */
  uint8_t stock[6];            /* bytes 44 to 49 */
  uint8_t separator_8;         /* byte 50 */
  uint8_t price[11];           /* bytes 51 to 61 */
  uint8_t separator_9;         /* byte 62 */
  uint8_t firm[4];             /* bytes 63 to 66 */
  uint8_t separator_10;        /* byte 67 */
  uint8_t reference[12];       /* bytes 68 to 79 */
  uint8_t separator_11;        /* byte 80 */
  uint8_t time_in_force[12];   /* bytes 81 to 92 */
  uint8_t separator_12;        /* byte 93 */
  uint8_t capacity;            /* byte 94 */
  uint8_t separator_13;        /* byte 95 */
  uint8_t liquidity_code;      /* byte 96 */
  uint8_t separator_14;        /* byte 97 */
  uint8_t clearing_code;       /* byte 98 */
} ExistingOrderReplacedMessage;

/* any Existing Order Replaced Message at all: every byte one the checker chooses */
static void any_existing_order_replaced_message(ExistingOrderReplacedMessage *record) {
  record->separator_1 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->source[i] = arbitrary(); }
  record->separator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->user[i] = arbitrary(); }
  record->separator_3 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->token[i] = arbitrary(); }
  record->separator_4 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = arbitrary(); }
  record->separator_5 = arbitrary();
  record->buy_sell = arbitrary();
  record->separator_6 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  record->separator_7 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->stock[i] = arbitrary(); }
  record->separator_8 = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->price[i] = arbitrary(); }
  record->separator_9 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->firm[i] = arbitrary(); }
  record->separator_10 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->reference[i] = arbitrary(); }
  record->separator_11 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->time_in_force[i] = arbitrary(); }
  record->separator_12 = arbitrary();
  record->capacity = arbitrary();
  record->separator_13 = arbitrary();
  record->liquidity_code = arbitrary();
  record->separator_14 = arbitrary();
  record->clearing_code = arbitrary();
}

/* Existing Order Replaced Message to the wire: 99 bytes from at, returning where the next byte goes */
static size_t encode_existing_order_replaced_message(const ExistingOrderReplacedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->separator_1;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->source[i]; }
  wire[at++] = record->separator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user[i]; }
  wire[at++] = record->separator_3;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->token[i]; }
  wire[at++] = record->separator_4;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->replaced_token[i]; }
  wire[at++] = record->separator_5;
  wire[at++] = record->buy_sell;
  wire[at++] = record->separator_6;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  wire[at++] = record->separator_7;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->separator_8;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->separator_9;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm[i]; }
  wire[at++] = record->separator_10;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reference[i]; }
  wire[at++] = record->separator_11;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->time_in_force[i]; }
  wire[at++] = record->separator_12;
  wire[at++] = record->capacity;
  wire[at++] = record->separator_13;
  wire[at++] = record->liquidity_code;
  wire[at++] = record->separator_14;
  wire[at++] = record->clearing_code;

  return at;
}

/* Existing Order Replaced Message off the wire: 99 bytes from at, returning where the next byte lies */
static size_t decode_existing_order_replaced_message(ExistingOrderReplacedMessage *record, const uint8_t *wire, size_t at) {
  record->separator_1 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->source[i] = wire[at++]; }
  record->separator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->user[i] = wire[at++]; }
  record->separator_3 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->token[i] = wire[at++]; }
  record->separator_4 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = wire[at++]; }
  record->separator_5 = wire[at++];
  record->buy_sell = wire[at++];
  record->separator_6 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  record->separator_7 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->stock[i] = wire[at++]; }
  record->separator_8 = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->price[i] = wire[at++]; }
  record->separator_9 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->firm[i] = wire[at++]; }
  record->separator_10 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->reference[i] = wire[at++]; }
  record->separator_11 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->time_in_force[i] = wire[at++]; }
  record->separator_12 = wire[at++];
  record->capacity = wire[at++];
  record->separator_13 = wire[at++];
  record->liquidity_code = wire[at++];
  record->separator_14 = wire[at++];
  record->clearing_code = wire[at++];

  return at;
}

/* what was read of Existing Order Replaced Message is what was written, byte for byte */
static void equal_existing_order_replaced_message(const ExistingOrderReplacedMessage *read, const ExistingOrderReplacedMessage *written) {
  assert(read->separator_1 == written->separator_1);
  for (size_t i = 0; i < 6; i++) { assert(read->source[i] == written->source[i]); }
  assert(read->separator_2 == written->separator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->user[i] == written->user[i]); }
  assert(read->separator_3 == written->separator_3);
  for (size_t i = 0; i < 10; i++) { assert(read->token[i] == written->token[i]); }
  assert(read->separator_4 == written->separator_4);
  for (size_t i = 0; i < 10; i++) { assert(read->replaced_token[i] == written->replaced_token[i]); }
  assert(read->separator_5 == written->separator_5);
  assert(read->buy_sell == written->buy_sell);
  assert(read->separator_6 == written->separator_6);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  assert(read->separator_7 == written->separator_7);
  for (size_t i = 0; i < 6; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->separator_8 == written->separator_8);
  for (size_t i = 0; i < 11; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->separator_9 == written->separator_9);
  for (size_t i = 0; i < 4; i++) { assert(read->firm[i] == written->firm[i]); }
  assert(read->separator_10 == written->separator_10);
  for (size_t i = 0; i < 12; i++) { assert(read->reference[i] == written->reference[i]); }
  assert(read->separator_11 == written->separator_11);
  for (size_t i = 0; i < 12; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  assert(read->separator_12 == written->separator_12);
  assert(read->capacity == written->capacity);
  assert(read->separator_13 == written->separator_13);
  assert(read->liquidity_code == written->liquidity_code);
  assert(read->separator_14 == written->separator_14);
  assert(read->clearing_code == written->clearing_code);
}

/* Existing Order Replaced Message: written and read back, then read and written back */
static void check_existing_order_replaced_message(void) {
  ExistingOrderReplacedMessage sent;
  ExistingOrderReplacedMessage got;
  uint8_t wire[99];
  uint8_t again[99];

  any_existing_order_replaced_message(&sent);
  assert(encode_existing_order_replaced_message(&sent, wire, 0) == 99);
  assert(decode_existing_order_replaced_message(&got, wire, 0) == 99);
  equal_existing_order_replaced_message(&got, &sent);

  for (size_t i = 0; i < 99; i++) { wire[i] = arbitrary(); }
  assert(decode_existing_order_replaced_message(&got, wire, 0) == 99);
  assert(encode_existing_order_replaced_message(&got, again, 0) == 99);
  for (size_t i = 0; i < 99; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_new_order_accepted_message();
  check_existing_order_executed_message();
  check_existing_order_canceled_message();
  check_previous_execution_broken_message();
  check_existing_order_replaced_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
