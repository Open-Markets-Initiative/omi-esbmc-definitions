// lseg/turquoise/level2incremental/Turquoise_Level2Incremental_v26_3.c
/*
 * London Stock Exchange Level 2 Incremental
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
 *   - a run counted by a field
 *   - a field read in bits
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

/* ---- Unit Header: 8 bytes ---------------------------------------------------- */

typedef struct {
  uint8_t length[2];           /* bytes 0 to 1 */
  uint8_t message_count;       /* byte 2 */
  uint8_t market_data_group;   /* byte 3 */
  uint8_t sequence_number[4];  /* bytes 4 to 7 */
} UnitHeader;

/* any Unit Header at all: every byte one the checker chooses */
static void any_unit_header(UnitHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  record->message_count = arbitrary();
  record->market_data_group = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Unit Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_unit_header(const UnitHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  wire[at++] = record->message_count;
  wire[at++] = record->market_data_group;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Unit Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_unit_header(UnitHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  record->message_count = wire[at++];
  record->market_data_group = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Unit Header is what was written, byte for byte */
static void equal_unit_header(const UnitHeader *read, const UnitHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  assert(read->message_count == written->message_count);
  assert(read->market_data_group == written->market_data_group);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Unit Header: written and read back, then read and written back */
static void check_unit_header(void) {
  UnitHeader sent;
  UnitHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_unit_header(&sent);
  assert(encode_unit_header(&sent, wire, 0) == 8);
  assert(decode_unit_header(&got, wire, 0) == 8);
  equal_unit_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_unit_header(&got, wire, 0) == 8);
  assert(encode_unit_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* Gtp Udp Message Header */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t message_type;       /* byte 2 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 3);
  assert(decode_message_header(&got, wire, 0) == 3);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 3);
  assert(encode_message_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 11 bytes ------------------------------------------ */

/* Sent to indicate the start and end of the day. */
typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t event_code;       /* byte 8 */
  uint8_t source_venue[2];  /* bytes 9 to 10 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->event_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
}

/* System Event Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }

  return at;
}

/* System Event Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->event_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->event_code == written->event_code);
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 11);
  assert(decode_system_event_message(&got, wire, 0) == 11);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 11);
  assert(encode_system_event_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Status Message: 27 bytes ------------------------------------- */

/* Used to communicate scheduled and unscheduled session changes */
typedef struct {
  uint8_t timestamp[8];           /* bytes 0 to 7 */
  uint8_t instrument[8];          /* bytes 8 to 15 */
  uint8_t source_venue[2];        /* bytes 16 to 17 */
  uint8_t trading_status;         /* byte 18 */
  uint8_t session_change_reason;  /* byte 19 */
  uint8_t new_end_time[6];        /* bytes 20 to 25 */
  uint8_t order_book_type;        /* byte 26 */
} InstrumentStatusMessage;

/* any Instrument Status Message at all: every byte one the checker chooses */
static void any_instrument_status_message(InstrumentStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->session_change_reason = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->new_end_time[i] = arbitrary(); }
  record->order_book_type = arbitrary();
}

/* Instrument Status Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_instrument_status_message(const InstrumentStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  wire[at++] = record->trading_status;
  wire[at++] = record->session_change_reason;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->new_end_time[i]; }
  wire[at++] = record->order_book_type;

  return at;
}

/* Instrument Status Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_instrument_status_message(InstrumentStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  record->trading_status = wire[at++];
  record->session_change_reason = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->new_end_time[i] = wire[at++]; }
  record->order_book_type = wire[at++];

  return at;
}

/* what was read of Instrument Status Message is what was written, byte for byte */
static void equal_instrument_status_message(const InstrumentStatusMessage *read, const InstrumentStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  assert(read->trading_status == written->trading_status);
  assert(read->session_change_reason == written->session_change_reason);
  for (size_t i = 0; i < 6; i++) { assert(read->new_end_time[i] == written->new_end_time[i]); }
  assert(read->order_book_type == written->order_book_type);
}

/* Instrument Status Message: written and read back, then read and written back */
static void check_instrument_status_message(void) {
  InstrumentStatusMessage sent;
  InstrumentStatusMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_instrument_status_message(&sent);
  assert(encode_instrument_status_message(&sent, wire, 0) == 27);
  assert(decode_instrument_status_message(&got, wire, 0) == 27);
  equal_instrument_status_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_status_message(&got, wire, 0) == 27);
  assert(encode_instrument_status_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Incremental Message: 74 bytes --------------------------------- */

/* Sent to instruct recipients to add a new displayable order to the retrospective order book */
typedef struct {
  uint8_t timestamp[8];         /* bytes 0 to 7 */
  uint8_t order_id[8];          /* bytes 8 to 15 */
  uint8_t side;                 /* byte 16 */
  uint8_t size[8];              /* bytes 17 to 24 */
  uint8_t instrument[8];        /* bytes 25 to 32 */
  uint8_t price[8];             /* bytes 33 to 40 */
  uint8_t transaction_time[8];  /* bytes 41 to 48 */
  uint8_t source_venue[2];      /* bytes 49 to 50 */
  uint8_t order_book_type;      /* byte 51 */
  uint8_t participant[11];      /* bytes 52 to 62 */
  uint8_t order_type;           /* byte 63 */
  uint8_t rfq_id[10];           /* bytes 64 to 73 */
} AddOrderIncrementalMessage;

/* any Add Order Incremental Message at all: every byte one the checker chooses */
static void any_add_order_incremental_message(AddOrderIncrementalMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  record->order_book_type = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->participant[i] = arbitrary(); }
  record->order_type = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->rfq_id[i] = arbitrary(); }
}

/* Add Order Incremental Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_add_order_incremental_message(const AddOrderIncrementalMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  wire[at++] = record->order_book_type;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->participant[i]; }
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->rfq_id[i]; }

  return at;
}

/* Add Order Incremental Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_add_order_incremental_message(AddOrderIncrementalMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  record->order_book_type = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->participant[i] = wire[at++]; }
  record->order_type = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->rfq_id[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Incremental Message is what was written, byte for byte */
static void equal_add_order_incremental_message(const AddOrderIncrementalMessage *read, const AddOrderIncrementalMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->size[i] == written->size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  assert(read->order_book_type == written->order_book_type);
  for (size_t i = 0; i < 11; i++) { assert(read->participant[i] == written->participant[i]); }
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 10; i++) { assert(read->rfq_id[i] == written->rfq_id[i]); }
}

/* Add Order Incremental Message: written and read back, then read and written back */
static void check_add_order_incremental_message(void) {
  AddOrderIncrementalMessage sent;
  AddOrderIncrementalMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_add_order_incremental_message(&sent);
  assert(encode_add_order_incremental_message(&sent, wire, 0) == 74);
  assert(decode_add_order_incremental_message(&got, wire, 0) == 74);
  equal_add_order_incremental_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_incremental_message(&got, wire, 0) == 74);
  assert(encode_add_order_incremental_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Order Message: 52 bytes ------------------------------------------ */

/* Sent to instruct recipients to delete an order from the retrospective order book */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t order_id[8];           /* bytes 8 to 15 */
  uint8_t instrument[8];         /* bytes 16 to 23 */
  uint8_t side;                  /* byte 24 */
  uint8_t order_book_type;       /* byte 25 */
  uint8_t source_venue[2];       /* bytes 26 to 27 */
  uint8_t previous_price[8];     /* bytes 28 to 35 */
  uint8_t previous_quantity[8];  /* bytes 36 to 43 */
  uint8_t transaction_time[8];   /* bytes 44 to 51 */
} DeleteOrderMessage;

/* any Delete Order Message at all: every byte one the checker chooses */
static void any_delete_order_message(DeleteOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  record->side = arbitrary();
  record->order_book_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
}

/* Delete Order Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_delete_order_message(const DeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  wire[at++] = record->side;
  wire[at++] = record->order_book_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }

  return at;
}

/* Delete Order Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_delete_order_message(DeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  record->side = wire[at++];
  record->order_book_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Order Message is what was written, byte for byte */
static void equal_delete_order_message(const DeleteOrderMessage *read, const DeleteOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  assert(read->side == written->side);
  assert(read->order_book_type == written->order_book_type);
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_price[i] == written->previous_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_quantity[i] == written->previous_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
}

/* Delete Order Message: written and read back, then read and written back */
static void check_delete_order_message(void) {
  DeleteOrderMessage sent;
  DeleteOrderMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_delete_order_message(&sent);
  assert(encode_delete_order_message(&sent, wire, 0) == 52);
  assert(decode_delete_order_message(&got, wire, 0) == 52);
  equal_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_order_message(&got, wire, 0) == 52);
  assert(encode_delete_order_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Book Clear Message: 19 bytes -------------------------------------- */

/* Sent to instruct recipients to remove all orders from the order book for the specified instrument */
typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t source_venue[2];  /* bytes 8 to 9 */
  uint8_t instrument[8];    /* bytes 10 to 17 */
  uint8_t order_book_type;  /* byte 18 */
} OrderBookClearMessage;

/* any Order Book Clear Message at all: every byte one the checker chooses */
static void any_order_book_clear_message(OrderBookClearMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  record->order_book_type = arbitrary();
}

/* Order Book Clear Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_order_book_clear_message(const OrderBookClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  wire[at++] = record->order_book_type;

  return at;
}

/* Order Book Clear Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_order_book_clear_message(OrderBookClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  record->order_book_type = wire[at++];

  return at;
}

/* what was read of Order Book Clear Message is what was written, byte for byte */
static void equal_order_book_clear_message(const OrderBookClearMessage *read, const OrderBookClearMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  assert(read->order_book_type == written->order_book_type);
}

/* Order Book Clear Message: written and read back, then read and written back */
static void check_order_book_clear_message(void) {
  OrderBookClearMessage sent;
  OrderBookClearMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_order_book_clear_message(&sent);
  assert(encode_order_book_clear_message(&sent, wire, 0) == 19);
  assert(decode_order_book_clear_message(&got, wire, 0) == 19);
  equal_order_book_clear_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_clear_message(&got, wire, 0) == 19);
  assert(encode_order_book_clear_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Statistics Message: 74 bytes -------------------------------------------- */

/* Contains a set of statistics that are updated frequently, usually as a result of executions */
typedef struct {
  uint8_t timestamp[8];                      /* bytes 0 to 7 */
  uint8_t instrument[8];                     /* bytes 8 to 15 */
  uint8_t source_venue[2];                   /* bytes 16 to 17 */
  uint8_t volume[8];                         /* bytes 18 to 25 */
  uint8_t volume_on_book_only[8];            /* bytes 26 to 33 */
  uint8_t vwap[8];                           /* bytes 34 to 41 */
  uint8_t vwap_on_book_only[8];              /* bytes 42 to 49 */
  uint8_t number_of_trades[4];               /* bytes 50 to 53 */
  uint8_t number_of_trades_on_book_only[4];  /* bytes 54 to 57 */
  uint8_t turnover[8];                       /* bytes 58 to 65 */
  uint8_t turnover_on_book_only[8];          /* bytes 66 to 73 */
} StatisticsMessage;

/* any Statistics Message at all: every byte one the checker chooses */
static void any_statistics_message(StatisticsMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_on_book_only[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap_on_book_only[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_trades_on_book_only[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover_on_book_only[i] = arbitrary(); }
}

/* Statistics Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_statistics_message(const StatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_on_book_only[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap_on_book_only[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_trades[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_trades_on_book_only[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover_on_book_only[i]; }

  return at;
}

/* Statistics Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_statistics_message(StatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_on_book_only[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap_on_book_only[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_trades_on_book_only[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover_on_book_only[i] = wire[at++]; }

  return at;
}

/* what was read of Statistics Message is what was written, byte for byte */
static void equal_statistics_message(const StatisticsMessage *read, const StatisticsMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_on_book_only[i] == written->volume_on_book_only[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap[i] == written->vwap[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap_on_book_only[i] == written->vwap_on_book_only[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_trades[i] == written->number_of_trades[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_trades_on_book_only[i] == written->number_of_trades_on_book_only[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover[i] == written->turnover[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover_on_book_only[i] == written->turnover_on_book_only[i]); }
}

/* Statistics Message: written and read back, then read and written back */
static void check_statistics_message(void) {
  StatisticsMessage sent;
  StatisticsMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_statistics_message(&sent);
  assert(encode_statistics_message(&sent, wire, 0) == 74);
  assert(decode_statistics_message(&got, wire, 0) == 74);
  equal_statistics_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_statistics_message(&got, wire, 0) == 74);
  assert(encode_statistics_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Statistics Update Message: 47 bytes ------------------------------------- */

/* Contains a set of statistics that are not updated frequently */
typedef struct {
  uint8_t timestamp[8];                     /* bytes 0 to 7 */
  uint8_t instrument[8];                    /* bytes 8 to 15 */
  uint8_t source_venue[2];                  /* bytes 16 to 17 */
  uint8_t statistic_type[2];                /* bytes 18 to 19 */
  uint8_t statistic_price[8];               /* bytes 20 to 27 */
  uint8_t statistic_size[8];                /* bytes 28 to 35 */
  uint8_t auction_type;                     /* byte 36 */
  uint8_t imbalance_quantity[8];            /* bytes 37 to 44 */
  uint8_t auction_info;                     /* byte 45 */
  uint8_t opening_closing_price_indicator;  /* byte 46 */
} StatisticsUpdateMessage;

/* any Statistics Update Message at all: every byte one the checker chooses */
static void any_statistics_update_message(StatisticsUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->statistic_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->statistic_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->statistic_size[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->imbalance_quantity[i] = arbitrary(); }
  record->auction_info = arbitrary();
  record->opening_closing_price_indicator = arbitrary();
}

/* Statistics Update Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_statistics_update_message(const StatisticsUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->statistic_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->statistic_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->statistic_size[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->imbalance_quantity[i]; }
  wire[at++] = record->auction_info;
  wire[at++] = record->opening_closing_price_indicator;

  return at;
}

/* Statistics Update Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_statistics_update_message(StatisticsUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->statistic_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->statistic_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->statistic_size[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->imbalance_quantity[i] = wire[at++]; }
  record->auction_info = wire[at++];
  record->opening_closing_price_indicator = wire[at++];

  return at;
}

/* what was read of Statistics Update Message is what was written, byte for byte */
static void equal_statistics_update_message(const StatisticsUpdateMessage *read, const StatisticsUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->statistic_type[i] == written->statistic_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->statistic_price[i] == written->statistic_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->statistic_size[i] == written->statistic_size[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->imbalance_quantity[i] == written->imbalance_quantity[i]); }
  assert(read->auction_info == written->auction_info);
  assert(read->opening_closing_price_indicator == written->opening_closing_price_indicator);
}

/* Statistics Update Message: written and read back, then read and written back */
static void check_statistics_update_message(void) {
  StatisticsUpdateMessage sent;
  StatisticsUpdateMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_statistics_update_message(&sent);
  assert(encode_statistics_update_message(&sent, wire, 0) == 47);
  assert(decode_statistics_update_message(&got, wire, 0) == 47);
  equal_statistics_update_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_statistics_update_message(&got, wire, 0) == 47);
  assert(encode_statistics_update_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Summary Message: 91 bytes ----------------------------------------- */

/* Trade Summary message is used to disseminate results of multi and single fill trade events */
typedef struct {
  uint8_t timestamp[8];                       /* bytes 0 to 7 */
  uint8_t instrument[8];                      /* bytes 8 to 15 */
  uint8_t source_venue[2];                    /* bytes 16 to 17 */
  uint8_t transaction_time[8];                /* bytes 18 to 25 */
  uint8_t far_price[8];                       /* bytes 26 to 33 */
  uint8_t total_executed_quantity[8];         /* bytes 34 to 41 */
  uint8_t total_hidden_executed_quantity[8];  /* bytes 42 to 49 */
  uint8_t deleted_order_quantity[8];          /* bytes 50 to 57 */
  uint8_t trade_summary_side;                 /* byte 58 */
  uint8_t best_bid_size[8];                   /* bytes 59 to 66 */
  uint8_t best_bid_price[8];                  /* bytes 67 to 74 */
  uint8_t best_offer_size[8];                 /* bytes 75 to 82 */
  uint8_t best_offer_price[8];                /* bytes 83 to 90 */
} TradeSummaryMessage;

/* any Trade Summary Message at all: every byte one the checker chooses */
static void any_trade_summary_message(TradeSummaryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->far_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_hidden_executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->deleted_order_quantity[i] = arbitrary(); }
  record->trade_summary_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->best_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_offer_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_offer_price[i] = arbitrary(); }
}

/* Trade Summary Message to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_trade_summary_message(const TradeSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->far_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_hidden_executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->deleted_order_quantity[i]; }
  wire[at++] = record->trade_summary_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_bid_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_bid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_offer_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_offer_price[i]; }

  return at;
}

/* Trade Summary Message off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_trade_summary_message(TradeSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->far_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_hidden_executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->deleted_order_quantity[i] = wire[at++]; }
  record->trade_summary_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->best_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_offer_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_offer_price[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Summary Message is what was written, byte for byte */
static void equal_trade_summary_message(const TradeSummaryMessage *read, const TradeSummaryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->far_price[i] == written->far_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_executed_quantity[i] == written->total_executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_hidden_executed_quantity[i] == written->total_hidden_executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->deleted_order_quantity[i] == written->deleted_order_quantity[i]); }
  assert(read->trade_summary_side == written->trade_summary_side);
  for (size_t i = 0; i < 8; i++) { assert(read->best_bid_size[i] == written->best_bid_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_bid_price[i] == written->best_bid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_offer_size[i] == written->best_offer_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_offer_price[i] == written->best_offer_price[i]); }
}

/* Trade Summary Message: written and read back, then read and written back */
static void check_trade_summary_message(void) {
  TradeSummaryMessage sent;
  TradeSummaryMessage got;
  uint8_t wire[91];
  uint8_t again[91];

  any_trade_summary_message(&sent);
  assert(encode_trade_summary_message(&sent, wire, 0) == 91);
  assert(decode_trade_summary_message(&got, wire, 0) == 91);
  equal_trade_summary_message(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_summary_message(&got, wire, 0) == 91);
  assert(encode_trade_summary_message(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_unit_header();
  check_message_header();
  check_system_event_message();
  check_instrument_status_message();
  check_add_order_incremental_message();
  check_delete_order_message();
  check_order_book_clear_message();
  check_statistics_message();
  check_statistics_update_message();
  check_trade_summary_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
