// tmx/tsx/quantumfeedlevel2/Tsx_QuantumFeedLevel2_v2_10.c
/*
 * TMX Group Quantum Feed Level 2
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
 *   - a length prefix framing what follows
 *   - a run counted by a field
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

/* ---- Frame Header: 11 bytes -------------------------------------------------- */

/* Xmt Udp Packet Frame Header */
typedef struct {
  uint8_t start_of_frame;         /* byte 0 */
  uint8_t protocol_name;          /* byte 1 */
  uint8_t protocol_version;       /* byte 2 */
  uint8_t message_length[2];      /* bytes 3 to 4 */
  uint8_t session_id[4];          /* bytes 5 to 8 */
  uint8_t ack_required_poss_dup;  /* byte 9 */
  uint8_t num_body;               /* byte 10 */
} FrameHeader;

/* any Frame Header at all: every byte one the checker chooses */
static void any_frame_header(FrameHeader *record) {
  record->start_of_frame = arbitrary();
  record->protocol_name = arbitrary();
  record->protocol_version = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  record->ack_required_poss_dup = arbitrary();
  record->num_body = arbitrary();
}

/* Frame Header to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_frame_header(const FrameHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->start_of_frame;
  wire[at++] = record->protocol_name;
  wire[at++] = record->protocol_version;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  wire[at++] = record->ack_required_poss_dup;
  wire[at++] = record->num_body;

  return at;
}

/* Frame Header off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_frame_header(FrameHeader *record, const uint8_t *wire, size_t at) {
  record->start_of_frame = wire[at++];
  record->protocol_name = wire[at++];
  record->protocol_version = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  record->ack_required_poss_dup = wire[at++];
  record->num_body = wire[at++];

  return at;
}

/* what was read of Frame Header is what was written, byte for byte */
static void equal_frame_header(const FrameHeader *read, const FrameHeader *written) {
  assert(read->start_of_frame == written->start_of_frame);
  assert(read->protocol_name == written->protocol_name);
  assert(read->protocol_version == written->protocol_version);
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  assert(read->ack_required_poss_dup == written->ack_required_poss_dup);
  assert(read->num_body == written->num_body);
}

/* Frame Header: written and read back, then read and written back */
static void check_frame_header(void) {
  FrameHeader sent;
  FrameHeader got;
  uint8_t wire[11];
  uint8_t again[11];

  any_frame_header(&sent);
  assert(encode_frame_header(&sent, wire, 0) == 11);
  assert(decode_frame_header(&got, wire, 0) == 11);
  equal_frame_header(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_frame_header(&got, wire, 0) == 11);
  assert(encode_frame_header(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Body Header: 3 bytes ---------------------------------------------------- */

/* Xmt Body Header */
typedef struct {
  uint8_t msg_length[2];  /* bytes 0 to 1 */
  uint8_t msg_type;       /* byte 2 */
} BodyHeader;

/* any Body Header at all: every byte one the checker chooses */
static void any_body_header(BodyHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = arbitrary(); }
  record->msg_type = arbitrary();
}

/* Body Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_body_header(const BodyHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_length[i]; }
  wire[at++] = record->msg_type;

  return at;
}

/* Body Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_body_header(BodyHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = wire[at++]; }
  record->msg_type = wire[at++];

  return at;
}

/* what was read of Body Header is what was written, byte for byte */
static void equal_body_header(const BodyHeader *read, const BodyHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->msg_length[i] == written->msg_length[i]); }
  assert(read->msg_type == written->msg_type);
}

/* Body Header: written and read back, then read and written back */
static void check_body_header(void) {
  BodyHeader sent;
  BodyHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_body_header(&sent);
  assert(encode_body_header(&sent, wire, 0) == 3);
  assert(decode_body_header(&got, wire, 0) == 3);
  equal_body_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_body_header(&got, wire, 0) == 3);
  assert(encode_body_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Business Header: 9 bytes ------------------------------------------------ */

/* Xmt Business Header */
typedef struct {
  uint8_t msg_version;    /* byte 0 */
  uint8_t source_id;      /* byte 1 */
  uint8_t stream_id[2];   /* bytes 2 to 3 */
  uint8_t sequence_0;     /* byte 4 */
  uint8_t sequence_1[4];  /* bytes 5 to 8 */
} BusinessHeader;

/* any Business Header at all: every byte one the checker chooses */
static void any_business_header(BusinessHeader *record) {
  record->msg_version = arbitrary();
  record->source_id = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->stream_id[i] = arbitrary(); }
  record->sequence_0 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_1[i] = arbitrary(); }
}

/* Business Header to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_business_header(const BusinessHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->msg_version;
  wire[at++] = record->source_id;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stream_id[i]; }
  wire[at++] = record->sequence_0;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_1[i]; }

  return at;
}

/* Business Header off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_business_header(BusinessHeader *record, const uint8_t *wire, size_t at) {
  record->msg_version = wire[at++];
  record->source_id = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->stream_id[i] = wire[at++]; }
  record->sequence_0 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_1[i] = wire[at++]; }

  return at;
}

/* what was read of Business Header is what was written, byte for byte */
static void equal_business_header(const BusinessHeader *read, const BusinessHeader *written) {
  assert(read->msg_version == written->msg_version);
  assert(read->source_id == written->source_id);
  for (size_t i = 0; i < 2; i++) { assert(read->stream_id[i] == written->stream_id[i]); }
  assert(read->sequence_0 == written->sequence_0);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_1[i] == written->sequence_1[i]); }
}

/* Business Header: written and read back, then read and written back */
static void check_business_header(void) {
  BusinessHeader sent;
  BusinessHeader got;
  uint8_t wire[9];
  uint8_t again[9];

  any_business_header(&sent);
  assert(encode_business_header(&sent, wire, 0) == 9);
  assert(decode_business_header(&got, wire, 0) == 9);
  equal_business_header(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_business_header(&got, wire, 0) == 9);
  assert(encode_business_header(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Status Message: 41 bytes ----------------------------------------- */

typedef struct {
  uint8_t symbol[9];      /* bytes 0 to 8 */
  uint8_t stock_group;    /* byte 9 */
  uint8_t cusip[12];      /* bytes 10 to 21 */
  uint8_t board_lot[2];   /* bytes 22 to 23 */
  uint8_t currency;       /* byte 24 */
  uint8_t face_value[8];  /* bytes 25 to 32 */
  uint8_t last_sale[8];   /* bytes 33 to 40 */
} SymbolStatusMessage;

/* any Symbol Status Message at all: every byte one the checker chooses */
static void any_symbol_status_message(SymbolStatusMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  record->stock_group = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->cusip[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_lot[i] = arbitrary(); }
  record->currency = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->face_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_sale[i] = arbitrary(); }
}

/* Symbol Status Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_symbol_status_message(const SymbolStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->stock_group;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->cusip[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_lot[i]; }
  wire[at++] = record->currency;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->face_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_sale[i]; }

  return at;
}

/* Symbol Status Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_symbol_status_message(SymbolStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  record->stock_group = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->cusip[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_lot[i] = wire[at++]; }
  record->currency = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->face_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_sale[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Status Message is what was written, byte for byte */
static void equal_symbol_status_message(const SymbolStatusMessage *read, const SymbolStatusMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->stock_group == written->stock_group);
  for (size_t i = 0; i < 12; i++) { assert(read->cusip[i] == written->cusip[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_lot[i] == written->board_lot[i]); }
  assert(read->currency == written->currency);
  for (size_t i = 0; i < 8; i++) { assert(read->face_value[i] == written->face_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_sale[i] == written->last_sale[i]); }
}

/* Symbol Status Message: written and read back, then read and written back */
static void check_symbol_status_message(void) {
  SymbolStatusMessage sent;
  SymbolStatusMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_symbol_status_message(&sent);
  assert(encode_symbol_status_message(&sent, wire, 0) == 41);
  assert(decode_symbol_status_message(&got, wire, 0) == 41);
  equal_symbol_status_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_status_message(&got, wire, 0) == 41);
  assert(encode_symbol_status_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Book Message: 40 bytes -------------------------------------------- */

typedef struct {
  uint8_t symbol[9];               /* bytes 0 to 8 */
  uint8_t broker_number[2];        /* bytes 9 to 10 */
  uint8_t order_side;              /* byte 11 */
  uint8_t order_id[8];             /* bytes 12 to 19 */
  uint8_t price[8];                /* bytes 20 to 27 */
  uint8_t volume[4];               /* bytes 28 to 31 */
  uint8_t priority_time_stamp[8];  /* bytes 32 to 39 */
} OrderBookMessage;

/* any Order Book Message at all: every byte one the checker chooses */
static void any_order_book_message(OrderBookMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_number[i] = arbitrary(); }
  record->order_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->priority_time_stamp[i] = arbitrary(); }
}

/* Order Book Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_order_book_message(const OrderBookMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_number[i]; }
  wire[at++] = record->order_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->priority_time_stamp[i]; }

  return at;
}

/* Order Book Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_order_book_message(OrderBookMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_number[i] = wire[at++]; }
  record->order_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->priority_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Order Book Message is what was written, byte for byte */
static void equal_order_book_message(const OrderBookMessage *read, const OrderBookMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_number[i] == written->broker_number[i]); }
  assert(read->order_side == written->order_side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->priority_time_stamp[i] == written->priority_time_stamp[i]); }
}

/* Order Book Message: written and read back, then read and written back */
static void check_order_book_message(void) {
  OrderBookMessage sent;
  OrderBookMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_order_book_message(&sent);
  assert(encode_order_book_message(&sent, wire, 0) == 40);
  assert(decode_order_book_message(&got, wire, 0) == 40);
  equal_order_book_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_message(&got, wire, 0) == 40);
  assert(encode_order_book_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Book Terms Message: 46 bytes -------------------------------------- */

typedef struct {
  uint8_t symbol[9];               /* bytes 0 to 8 */
  uint8_t broker_number[2];        /* bytes 9 to 10 */
  uint8_t order_side;              /* byte 11 */
  uint8_t order_id[8];             /* bytes 12 to 19 */
  uint8_t price[8];                /* bytes 20 to 27 */
  uint8_t volume[4];               /* bytes 28 to 31 */
  uint8_t non_resident;            /* byte 32 */
  uint8_t settlement_terms;        /* byte 33 */
  uint8_t settlement_date[4];      /* bytes 34 to 37 */
  uint8_t priority_time_stamp[8];  /* bytes 38 to 45 */
} OrderBookTermsMessage;

/* any Order Book Terms Message at all: every byte one the checker chooses */
static void any_order_book_terms_message(OrderBookTermsMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_number[i] = arbitrary(); }
  record->order_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->non_resident = arbitrary();
  record->settlement_terms = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->settlement_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->priority_time_stamp[i] = arbitrary(); }
}

/* Order Book Terms Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_order_book_terms_message(const OrderBookTermsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_number[i]; }
  wire[at++] = record->order_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->non_resident;
  wire[at++] = record->settlement_terms;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settlement_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->priority_time_stamp[i]; }

  return at;
}

/* Order Book Terms Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_order_book_terms_message(OrderBookTermsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_number[i] = wire[at++]; }
  record->order_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->non_resident = wire[at++];
  record->settlement_terms = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->settlement_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->priority_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Order Book Terms Message is what was written, byte for byte */
static void equal_order_book_terms_message(const OrderBookTermsMessage *read, const OrderBookTermsMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_number[i] == written->broker_number[i]); }
  assert(read->order_side == written->order_side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->non_resident == written->non_resident);
  assert(read->settlement_terms == written->settlement_terms);
  for (size_t i = 0; i < 4; i++) { assert(read->settlement_date[i] == written->settlement_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->priority_time_stamp[i] == written->priority_time_stamp[i]); }
}

/* Order Book Terms Message: written and read back, then read and written back */
static void check_order_book_terms_message(void) {
  OrderBookTermsMessage sent;
  OrderBookTermsMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_order_book_terms_message(&sent);
  assert(encode_order_book_terms_message(&sent, wire, 0) == 46);
  assert(decode_order_book_terms_message(&got, wire, 0) == 46);
  equal_order_book_terms_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_terms_message(&got, wire, 0) == 46);
  assert(encode_order_book_terms_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Assign Cop No Orders Message: 25 bytes ---------------------------------- */

typedef struct {
  uint8_t symbol[9];                     /* bytes 0 to 8 */
  uint8_t calculated_opening_price[8];   /* bytes 9 to 16 */
  uint8_t trading_system_time_stamp[8];  /* bytes 17 to 24 */
} AssignCopNoOrdersMessage;

/* any Assign Cop No Orders Message at all: every byte one the checker chooses */
static void any_assign_cop_no_orders_message(AssignCopNoOrdersMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->calculated_opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Assign Cop No Orders Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_assign_cop_no_orders_message(const AssignCopNoOrdersMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->calculated_opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Assign Cop No Orders Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_assign_cop_no_orders_message(AssignCopNoOrdersMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->calculated_opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Assign Cop No Orders Message is what was written, byte for byte */
static void equal_assign_cop_no_orders_message(const AssignCopNoOrdersMessage *read, const AssignCopNoOrdersMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->calculated_opening_price[i] == written->calculated_opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Assign Cop No Orders Message: written and read back, then read and written back */
static void check_assign_cop_no_orders_message(void) {
  AssignCopNoOrdersMessage sent;
  AssignCopNoOrdersMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_assign_cop_no_orders_message(&sent);
  assert(encode_assign_cop_no_orders_message(&sent, wire, 0) == 25);
  assert(decode_assign_cop_no_orders_message(&got, wire, 0) == 25);
  equal_assign_cop_no_orders_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_assign_cop_no_orders_message(&got, wire, 0) == 25);
  assert(encode_assign_cop_no_orders_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market State Update Message: 10 bytes ----------------------------------- */

typedef struct {
  uint8_t market_state;                  /* byte 0 */
  uint8_t stock_group;                   /* byte 1 */
  uint8_t trading_system_time_stamp[8];  /* bytes 2 to 9 */
} MarketStateUpdateMessage;

/* any Market State Update Message at all: every byte one the checker chooses */
static void any_market_state_update_message(MarketStateUpdateMessage *record) {
  record->market_state = arbitrary();
  record->stock_group = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Market State Update Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_market_state_update_message(const MarketStateUpdateMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_state;
  wire[at++] = record->stock_group;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Market State Update Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_market_state_update_message(MarketStateUpdateMessage *record, const uint8_t *wire, size_t at) {
  record->market_state = wire[at++];
  record->stock_group = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Market State Update Message is what was written, byte for byte */
static void equal_market_state_update_message(const MarketStateUpdateMessage *read, const MarketStateUpdateMessage *written) {
  assert(read->market_state == written->market_state);
  assert(read->stock_group == written->stock_group);
  for (size_t i = 0; i < 8; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Market State Update Message: written and read back, then read and written back */
static void check_market_state_update_message(void) {
  MarketStateUpdateMessage sent;
  MarketStateUpdateMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_market_state_update_message(&sent);
  assert(encode_market_state_update_message(&sent, wire, 0) == 10);
  assert(decode_market_state_update_message(&got, wire, 0) == 10);
  equal_market_state_update_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_market_state_update_message(&got, wire, 0) == 10);
  assert(encode_market_state_update_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Moc Imbalance Message: 30 bytes ----------------------------------------- */

typedef struct {
  uint8_t symbol[9];                     /* bytes 0 to 8 */
  uint8_t imbalance_side;                /* byte 9 */
  uint8_t imbalance_volume[4];           /* bytes 10 to 13 */
  uint8_t trading_system_time_stamp[8];  /* bytes 14 to 21 */
  uint8_t imbalance_reference_price[8];  /* bytes 22 to 29 */
} MocImbalanceMessage;

/* any Moc Imbalance Message at all: every byte one the checker chooses */
static void any_moc_imbalance_message(MocImbalanceMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  record->imbalance_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->imbalance_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->imbalance_reference_price[i] = arbitrary(); }
}

/* Moc Imbalance Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_moc_imbalance_message(const MocImbalanceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->imbalance_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->imbalance_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_system_time_stamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->imbalance_reference_price[i]; }

  return at;
}

/* Moc Imbalance Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_moc_imbalance_message(MocImbalanceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  record->imbalance_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->imbalance_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->imbalance_reference_price[i] = wire[at++]; }

  return at;
}

/* what was read of Moc Imbalance Message is what was written, byte for byte */
static void equal_moc_imbalance_message(const MocImbalanceMessage *read, const MocImbalanceMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->imbalance_side == written->imbalance_side);
  for (size_t i = 0; i < 4; i++) { assert(read->imbalance_volume[i] == written->imbalance_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->imbalance_reference_price[i] == written->imbalance_reference_price[i]); }
}

/* Moc Imbalance Message: written and read back, then read and written back */
static void check_moc_imbalance_message(void) {
  MocImbalanceMessage sent;
  MocImbalanceMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_moc_imbalance_message(&sent);
  assert(encode_moc_imbalance_message(&sent, wire, 0) == 30);
  assert(decode_moc_imbalance_message(&got, wire, 0) == 30);
  equal_moc_imbalance_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_moc_imbalance_message(&got, wire, 0) == 30);
  assert(encode_moc_imbalance_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Booked Message: 48 bytes ------------------------------------------ */

typedef struct {
  uint8_t symbol[9];                     /* bytes 0 to 8 */
  uint8_t broker_number[2];              /* bytes 9 to 10 */
  uint8_t order_side;                    /* byte 11 */
  uint8_t order_id[8];                   /* bytes 12 to 19 */
  uint8_t price[8];                      /* bytes 20 to 27 */
  uint8_t volume[4];                     /* bytes 28 to 31 */
  uint8_t priority_time_stamp[8];        /* bytes 32 to 39 */
  uint8_t trading_system_time_stamp[8];  /* bytes 40 to 47 */
} OrderBookedMessage;

/* any Order Booked Message at all: every byte one the checker chooses */
static void any_order_booked_message(OrderBookedMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_number[i] = arbitrary(); }
  record->order_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->priority_time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Order Booked Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_order_booked_message(const OrderBookedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_number[i]; }
  wire[at++] = record->order_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->priority_time_stamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Order Booked Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_order_booked_message(OrderBookedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_number[i] = wire[at++]; }
  record->order_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->priority_time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Order Booked Message is what was written, byte for byte */
static void equal_order_booked_message(const OrderBookedMessage *read, const OrderBookedMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_number[i] == written->broker_number[i]); }
  assert(read->order_side == written->order_side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->priority_time_stamp[i] == written->priority_time_stamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Order Booked Message: written and read back, then read and written back */
static void check_order_booked_message(void) {
  OrderBookedMessage sent;
  OrderBookedMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_order_booked_message(&sent);
  assert(encode_order_booked_message(&sent, wire, 0) == 48);
  assert(decode_order_booked_message(&got, wire, 0) == 48);
  equal_order_booked_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_order_booked_message(&got, wire, 0) == 48);
  assert(encode_order_booked_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Booked Terms Message: 54 bytes ------------------------------------ */

typedef struct {
  uint8_t symbol[9];                     /* bytes 0 to 8 */
  uint8_t broker_number[2];              /* bytes 9 to 10 */
  uint8_t order_side;                    /* byte 11 */
  uint8_t order_id[8];                   /* bytes 12 to 19 */
  uint8_t price[8];                      /* bytes 20 to 27 */
  uint8_t volume[4];                     /* bytes 28 to 31 */
  uint8_t non_resident;                  /* byte 32 */
  uint8_t settlement_terms;              /* byte 33 */
  uint8_t settlement_date[4];            /* bytes 34 to 37 */
  uint8_t priority_time_stamp[8];        /* bytes 38 to 45 */
  uint8_t trading_system_time_stamp[8];  /* bytes 46 to 53 */
} OrderBookedTermsMessage;

/* any Order Booked Terms Message at all: every byte one the checker chooses */
static void any_order_booked_terms_message(OrderBookedTermsMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_number[i] = arbitrary(); }
  record->order_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->non_resident = arbitrary();
  record->settlement_terms = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->settlement_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->priority_time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Order Booked Terms Message to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_order_booked_terms_message(const OrderBookedTermsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_number[i]; }
  wire[at++] = record->order_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->non_resident;
  wire[at++] = record->settlement_terms;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settlement_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->priority_time_stamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Order Booked Terms Message off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_order_booked_terms_message(OrderBookedTermsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_number[i] = wire[at++]; }
  record->order_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->non_resident = wire[at++];
  record->settlement_terms = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->settlement_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->priority_time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Order Booked Terms Message is what was written, byte for byte */
static void equal_order_booked_terms_message(const OrderBookedTermsMessage *read, const OrderBookedTermsMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_number[i] == written->broker_number[i]); }
  assert(read->order_side == written->order_side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->non_resident == written->non_resident);
  assert(read->settlement_terms == written->settlement_terms);
  for (size_t i = 0; i < 4; i++) { assert(read->settlement_date[i] == written->settlement_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->priority_time_stamp[i] == written->priority_time_stamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Order Booked Terms Message: written and read back, then read and written back */
static void check_order_booked_terms_message(void) {
  OrderBookedTermsMessage sent;
  OrderBookedTermsMessage got;
  uint8_t wire[54];
  uint8_t again[54];

  any_order_booked_terms_message(&sent);
  assert(encode_order_booked_terms_message(&sent, wire, 0) == 54);
  assert(decode_order_booked_terms_message(&got, wire, 0) == 54);
  equal_order_booked_terms_message(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_order_booked_terms_message(&got, wire, 0) == 54);
  assert(encode_order_booked_terms_message(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancelled Message: 28 bytes --------------------------------------- */

typedef struct {
  uint8_t symbol[9];                     /* bytes 0 to 8 */
  uint8_t broker_number[2];              /* bytes 9 to 10 */
  uint8_t order_side;                    /* byte 11 */
  uint8_t order_id[8];                   /* bytes 12 to 19 */
  uint8_t trading_system_time_stamp[8];  /* bytes 20 to 27 */
} OrderCancelledMessage;

/* any Order Cancelled Message at all: every byte one the checker chooses */
static void any_order_cancelled_message(OrderCancelledMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_number[i] = arbitrary(); }
  record->order_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Order Cancelled Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_order_cancelled_message(const OrderCancelledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_number[i]; }
  wire[at++] = record->order_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Order Cancelled Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_order_cancelled_message(OrderCancelledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_number[i] = wire[at++]; }
  record->order_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancelled Message is what was written, byte for byte */
static void equal_order_cancelled_message(const OrderCancelledMessage *read, const OrderCancelledMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_number[i] == written->broker_number[i]); }
  assert(read->order_side == written->order_side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Order Cancelled Message: written and read back, then read and written back */
static void check_order_cancelled_message(void) {
  OrderCancelledMessage sent;
  OrderCancelledMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_order_cancelled_message(&sent);
  assert(encode_order_cancelled_message(&sent, wire, 0) == 28);
  assert(decode_order_cancelled_message(&got, wire, 0) == 28);
  equal_order_cancelled_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancelled_message(&got, wire, 0) == 28);
  assert(encode_order_cancelled_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancelled Terms Message: 28 bytes --------------------------------- */

typedef struct {
  uint8_t symbol[9];                     /* bytes 0 to 8 */
  uint8_t broker_number[2];              /* bytes 9 to 10 */
  uint8_t order_side;                    /* byte 11 */
  uint8_t order_id[8];                   /* bytes 12 to 19 */
  uint8_t trading_system_time_stamp[8];  /* bytes 20 to 27 */
} OrderCancelledTermsMessage;

/* any Order Cancelled Terms Message at all: every byte one the checker chooses */
static void any_order_cancelled_terms_message(OrderCancelledTermsMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_number[i] = arbitrary(); }
  record->order_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Order Cancelled Terms Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_order_cancelled_terms_message(const OrderCancelledTermsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_number[i]; }
  wire[at++] = record->order_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Order Cancelled Terms Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_order_cancelled_terms_message(OrderCancelledTermsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_number[i] = wire[at++]; }
  record->order_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancelled Terms Message is what was written, byte for byte */
static void equal_order_cancelled_terms_message(const OrderCancelledTermsMessage *read, const OrderCancelledTermsMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_number[i] == written->broker_number[i]); }
  assert(read->order_side == written->order_side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Order Cancelled Terms Message: written and read back, then read and written back */
static void check_order_cancelled_terms_message(void) {
  OrderCancelledTermsMessage sent;
  OrderCancelledTermsMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_order_cancelled_terms_message(&sent);
  assert(encode_order_cancelled_terms_message(&sent, wire, 0) == 28);
  assert(decode_order_cancelled_terms_message(&got, wire, 0) == 28);
  equal_order_cancelled_terms_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancelled_terms_message(&got, wire, 0) == 28);
  assert(encode_order_cancelled_terms_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Price Time Assigned Message: 48 bytes ----------------------------- */

typedef struct {
  uint8_t symbol[9];                     /* bytes 0 to 8 */
  uint8_t broker_number[2];              /* bytes 9 to 10 */
  uint8_t order_side;                    /* byte 11 */
  uint8_t order_id[8];                   /* bytes 12 to 19 */
  uint8_t price[8];                      /* bytes 20 to 27 */
  uint8_t volume[4];                     /* bytes 28 to 31 */
  uint8_t priority_time_stamp[8];        /* bytes 32 to 39 */
  uint8_t trading_system_time_stamp[8];  /* bytes 40 to 47 */
} OrderPriceTimeAssignedMessage;

/* any Order Price Time Assigned Message at all: every byte one the checker chooses */
static void any_order_price_time_assigned_message(OrderPriceTimeAssignedMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_number[i] = arbitrary(); }
  record->order_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->priority_time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Order Price Time Assigned Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_order_price_time_assigned_message(const OrderPriceTimeAssignedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_number[i]; }
  wire[at++] = record->order_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->priority_time_stamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Order Price Time Assigned Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_order_price_time_assigned_message(OrderPriceTimeAssignedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_number[i] = wire[at++]; }
  record->order_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->priority_time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Order Price Time Assigned Message is what was written, byte for byte */
static void equal_order_price_time_assigned_message(const OrderPriceTimeAssignedMessage *read, const OrderPriceTimeAssignedMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_number[i] == written->broker_number[i]); }
  assert(read->order_side == written->order_side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->priority_time_stamp[i] == written->priority_time_stamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Order Price Time Assigned Message: written and read back, then read and written back */
static void check_order_price_time_assigned_message(void) {
  OrderPriceTimeAssignedMessage sent;
  OrderPriceTimeAssignedMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_order_price_time_assigned_message(&sent);
  assert(encode_order_price_time_assigned_message(&sent, wire, 0) == 48);
  assert(decode_order_price_time_assigned_message(&got, wire, 0) == 48);
  equal_order_price_time_assigned_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_order_price_time_assigned_message(&got, wire, 0) == 48);
  assert(encode_order_price_time_assigned_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Price Time Assigned Terms Message: 48 bytes ----------------------- */

typedef struct {
  uint8_t symbol[9];                     /* bytes 0 to 8 */
  uint8_t broker_number[2];              /* bytes 9 to 10 */
  uint8_t order_side;                    /* byte 11 */
  uint8_t order_id[8];                   /* bytes 12 to 19 */
  uint8_t price[8];                      /* bytes 20 to 27 */
  uint8_t volume[4];                     /* bytes 28 to 31 */
  uint8_t priority_time_stamp[8];        /* bytes 32 to 39 */
  uint8_t trading_system_time_stamp[8];  /* bytes 40 to 47 */
} OrderPriceTimeAssignedTermsMessage;

/* any Order Price Time Assigned Terms Message at all: every byte one the checker chooses */
static void any_order_price_time_assigned_terms_message(OrderPriceTimeAssignedTermsMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_number[i] = arbitrary(); }
  record->order_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->priority_time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Order Price Time Assigned Terms Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_order_price_time_assigned_terms_message(const OrderPriceTimeAssignedTermsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_number[i]; }
  wire[at++] = record->order_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->priority_time_stamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Order Price Time Assigned Terms Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_order_price_time_assigned_terms_message(OrderPriceTimeAssignedTermsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_number[i] = wire[at++]; }
  record->order_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->priority_time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Order Price Time Assigned Terms Message is what was written, byte for byte */
static void equal_order_price_time_assigned_terms_message(const OrderPriceTimeAssignedTermsMessage *read, const OrderPriceTimeAssignedTermsMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_number[i] == written->broker_number[i]); }
  assert(read->order_side == written->order_side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->priority_time_stamp[i] == written->priority_time_stamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Order Price Time Assigned Terms Message: written and read back, then read and written back */
static void check_order_price_time_assigned_terms_message(void) {
  OrderPriceTimeAssignedTermsMessage sent;
  OrderPriceTimeAssignedTermsMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_order_price_time_assigned_terms_message(&sent);
  assert(encode_order_price_time_assigned_terms_message(&sent, wire, 0) == 48);
  assert(decode_order_price_time_assigned_terms_message(&got, wire, 0) == 48);
  equal_order_price_time_assigned_terms_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_order_price_time_assigned_terms_message(&got, wire, 0) == 48);
  assert(encode_order_price_time_assigned_terms_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Status Message: 59 bytes ------------------------------------------ */

typedef struct {
  uint8_t symbol[9];                     /* bytes 0 to 8 */
  uint8_t comment[40];                   /* bytes 9 to 48 */
  uint8_t stock_state[2];                /* bytes 49 to 50 */
  uint8_t trading_system_time_stamp[8];  /* bytes 51 to 58 */
} StockStatusMessage;

/* any Stock Status Message at all: every byte one the checker chooses */
static void any_stock_status_message(StockStatusMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->comment[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->stock_state[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Stock Status Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_stock_status_message(const StockStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->comment[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_state[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Stock Status Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_stock_status_message(StockStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->comment[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->stock_state[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Status Message is what was written, byte for byte */
static void equal_stock_status_message(const StockStatusMessage *read, const StockStatusMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->comment[i] == written->comment[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->stock_state[i] == written->stock_state[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Stock Status Message: written and read back, then read and written back */
static void check_stock_status_message(void) {
  StockStatusMessage sent;
  StockStatusMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_stock_status_message(&sent);
  assert(encode_stock_status_message(&sent, wire, 0) == 59);
  assert(decode_stock_status_message(&got, wire, 0) == 59);
  equal_stock_status_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_status_message(&got, wire, 0) == 59);
  assert(encode_stock_status_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Report Message: 67 bytes ------------------------------------------ */

typedef struct {
  uint8_t symbol[9];                     /* bytes 0 to 8 */
  uint8_t trade_number[4];               /* bytes 9 to 12 */
  uint8_t price[8];                      /* bytes 13 to 20 */
  uint8_t volume[4];                     /* bytes 21 to 24 */
  uint8_t buy_broker_number[2];          /* bytes 25 to 26 */
  uint8_t buy_order_id[8];               /* bytes 27 to 34 */
  uint8_t buy_display_volume[4];         /* bytes 35 to 38 */
  uint8_t sell_broker_number[2];         /* bytes 39 to 40 */
  uint8_t sell_order_id[8];              /* bytes 41 to 48 */
  uint8_t sell_display_volume[4];        /* bytes 49 to 52 */
  uint8_t bypass;                        /* byte 53 */
  uint8_t trade_time_stamp[4];           /* bytes 54 to 57 */
  uint8_t cross_type;                    /* byte 58 */
  uint8_t trading_system_time_stamp[8];  /* bytes 59 to 66 */
} TradeReportMessage;

/* any Trade Report Message at all: every byte one the checker chooses */
static void any_trade_report_message(TradeReportMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->buy_broker_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_display_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->sell_broker_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_display_volume[i] = arbitrary(); }
  record->bypass = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trade_time_stamp[i] = arbitrary(); }
  record->cross_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Trade Report Message to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_trade_report_message(const TradeReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->buy_broker_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_display_volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sell_broker_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_display_volume[i]; }
  wire[at++] = record->bypass;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_time_stamp[i]; }
  wire[at++] = record->cross_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Trade Report Message off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_trade_report_message(TradeReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->buy_broker_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_display_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->sell_broker_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_display_volume[i] = wire[at++]; }
  record->bypass = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trade_time_stamp[i] = wire[at++]; }
  record->cross_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Report Message is what was written, byte for byte */
static void equal_trade_report_message(const TradeReportMessage *read, const TradeReportMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->buy_broker_number[i] == written->buy_broker_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_order_id[i] == written->buy_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_display_volume[i] == written->buy_display_volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->sell_broker_number[i] == written->sell_broker_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell_order_id[i] == written->sell_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_display_volume[i] == written->sell_display_volume[i]); }
  assert(read->bypass == written->bypass);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_time_stamp[i] == written->trade_time_stamp[i]); }
  assert(read->cross_type == written->cross_type);
  for (size_t i = 0; i < 8; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Trade Report Message: written and read back, then read and written back */
static void check_trade_report_message(void) {
  TradeReportMessage sent;
  TradeReportMessage got;
  uint8_t wire[67];
  uint8_t again[67];

  any_trade_report_message(&sent);
  assert(encode_trade_report_message(&sent, wire, 0) == 67);
  assert(decode_trade_report_message(&got, wire, 0) == 67);
  equal_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_message(&got, wire, 0) == 67);
  assert(encode_trade_report_message(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Report Terms Message: 72 bytes ------------------------------------ */

typedef struct {
  uint8_t symbol[9];                     /* bytes 0 to 8 */
  uint8_t trade_number[4];               /* bytes 9 to 12 */
  uint8_t price[8];                      /* bytes 13 to 20 */
  uint8_t volume[4];                     /* bytes 21 to 24 */
  uint8_t buy_broker_number[2];          /* bytes 25 to 26 */
  uint8_t buy_order_id[8];               /* bytes 27 to 34 */
  uint8_t buy_display_volume[4];         /* bytes 35 to 38 */
  uint8_t sell_broker_number[2];         /* bytes 39 to 40 */
  uint8_t sell_order_id[8];              /* bytes 41 to 48 */
  uint8_t sell_display_volume[4];        /* bytes 49 to 52 */
  uint8_t trade_time_stamp[4];           /* bytes 53 to 56 */
  uint8_t non_resident;                  /* byte 57 */
  uint8_t settlement_terms;              /* byte 58 */
  uint8_t settlement_date[4];            /* bytes 59 to 62 */
  uint8_t cross_type;                    /* byte 63 */
  uint8_t trading_system_time_stamp[8];  /* bytes 64 to 71 */
} TradeReportTermsMessage;

/* any Trade Report Terms Message at all: every byte one the checker chooses */
static void any_trade_report_terms_message(TradeReportTermsMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->buy_broker_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_display_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->sell_broker_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_display_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_time_stamp[i] = arbitrary(); }
  record->non_resident = arbitrary();
  record->settlement_terms = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->settlement_date[i] = arbitrary(); }
  record->cross_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Trade Report Terms Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_trade_report_terms_message(const TradeReportTermsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->buy_broker_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_display_volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sell_broker_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_display_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_time_stamp[i]; }
  wire[at++] = record->non_resident;
  wire[at++] = record->settlement_terms;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settlement_date[i]; }
  wire[at++] = record->cross_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Trade Report Terms Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_trade_report_terms_message(TradeReportTermsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->buy_broker_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_display_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->sell_broker_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_display_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_time_stamp[i] = wire[at++]; }
  record->non_resident = wire[at++];
  record->settlement_terms = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->settlement_date[i] = wire[at++]; }
  record->cross_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Report Terms Message is what was written, byte for byte */
static void equal_trade_report_terms_message(const TradeReportTermsMessage *read, const TradeReportTermsMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->buy_broker_number[i] == written->buy_broker_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_order_id[i] == written->buy_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_display_volume[i] == written->buy_display_volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->sell_broker_number[i] == written->sell_broker_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell_order_id[i] == written->sell_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_display_volume[i] == written->sell_display_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_time_stamp[i] == written->trade_time_stamp[i]); }
  assert(read->non_resident == written->non_resident);
  assert(read->settlement_terms == written->settlement_terms);
  for (size_t i = 0; i < 4; i++) { assert(read->settlement_date[i] == written->settlement_date[i]); }
  assert(read->cross_type == written->cross_type);
  for (size_t i = 0; i < 8; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Trade Report Terms Message: written and read back, then read and written back */
static void check_trade_report_terms_message(void) {
  TradeReportTermsMessage sent;
  TradeReportTermsMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_trade_report_terms_message(&sent);
  assert(encode_trade_report_terms_message(&sent, wire, 0) == 72);
  assert(decode_trade_report_terms_message(&got, wire, 0) == 72);
  equal_trade_report_terms_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_terms_message(&got, wire, 0) == 72);
  assert(encode_trade_report_terms_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancelled Message: 21 bytes --------------------------------------- */

typedef struct {
  uint8_t symbol[9];                     /* bytes 0 to 8 */
  uint8_t trade_number[4];               /* bytes 9 to 12 */
  uint8_t trading_system_time_stamp[8];  /* bytes 13 to 20 */
} TradeCancelledMessage;

/* any Trade Cancelled Message at all: every byte one the checker chooses */
static void any_trade_cancelled_message(TradeCancelledMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Trade Cancelled Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancelled_message(const TradeCancelledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Trade Cancelled Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancelled_message(TradeCancelledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancelled Message is what was written, byte for byte */
static void equal_trade_cancelled_message(const TradeCancelledMessage *read, const TradeCancelledMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Trade Cancelled Message: written and read back, then read and written back */
static void check_trade_cancelled_message(void) {
  TradeCancelledMessage sent;
  TradeCancelledMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_trade_cancelled_message(&sent);
  assert(encode_trade_cancelled_message(&sent, wire, 0) == 21);
  assert(decode_trade_cancelled_message(&got, wire, 0) == 21);
  equal_trade_cancelled_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancelled_message(&got, wire, 0) == 21);
  assert(encode_trade_cancelled_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancelled Terms Message: 21 bytes --------------------------------- */

typedef struct {
  uint8_t symbol[9];                     /* bytes 0 to 8 */
  uint8_t trade_number[4];               /* bytes 9 to 12 */
  uint8_t trading_system_time_stamp[8];  /* bytes 13 to 20 */
} TradeCancelledTermsMessage;

/* any Trade Cancelled Terms Message at all: every byte one the checker chooses */
static void any_trade_cancelled_terms_message(TradeCancelledTermsMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Trade Cancelled Terms Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancelled_terms_message(const TradeCancelledTermsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Trade Cancelled Terms Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancelled_terms_message(TradeCancelledTermsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancelled Terms Message is what was written, byte for byte */
static void equal_trade_cancelled_terms_message(const TradeCancelledTermsMessage *read, const TradeCancelledTermsMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Trade Cancelled Terms Message: written and read back, then read and written back */
static void check_trade_cancelled_terms_message(void) {
  TradeCancelledTermsMessage sent;
  TradeCancelledTermsMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_trade_cancelled_terms_message(&sent);
  assert(encode_trade_cancelled_terms_message(&sent, wire, 0) == 21);
  assert(decode_trade_cancelled_terms_message(&got, wire, 0) == 21);
  equal_trade_cancelled_terms_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancelled_terms_message(&got, wire, 0) == 21);
  assert(encode_trade_cancelled_terms_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 48 bytes -------------------------------------- */

typedef struct {
  uint8_t symbol[9];                     /* bytes 0 to 8 */
  uint8_t trade_number[4];               /* bytes 9 to 12 */
  uint8_t price[8];                      /* bytes 13 to 20 */
  uint8_t volume[4];                     /* bytes 21 to 24 */
  uint8_t buy_broker_number[2];          /* bytes 25 to 26 */
  uint8_t sell_broker_number[2];         /* bytes 27 to 28 */
  uint8_t initiated_by;                  /* byte 29 */
  uint8_t orig_trade_number[4];          /* bytes 30 to 33 */
  uint8_t bypass;                        /* byte 34 */
  uint8_t trade_time_stamp[4];           /* bytes 35 to 38 */
  uint8_t cross_type;                    /* byte 39 */
  uint8_t trading_system_time_stamp[8];  /* bytes 40 to 47 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->buy_broker_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->sell_broker_number[i] = arbitrary(); }
  record->initiated_by = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->orig_trade_number[i] = arbitrary(); }
  record->bypass = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trade_time_stamp[i] = arbitrary(); }
  record->cross_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Trade Correction Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->buy_broker_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sell_broker_number[i]; }
  wire[at++] = record->initiated_by;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orig_trade_number[i]; }
  wire[at++] = record->bypass;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_time_stamp[i]; }
  wire[at++] = record->cross_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Trade Correction Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->buy_broker_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->sell_broker_number[i] = wire[at++]; }
  record->initiated_by = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->orig_trade_number[i] = wire[at++]; }
  record->bypass = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trade_time_stamp[i] = wire[at++]; }
  record->cross_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Correction Message is what was written, byte for byte */
static void equal_trade_correction_message(const TradeCorrectionMessage *read, const TradeCorrectionMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->buy_broker_number[i] == written->buy_broker_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->sell_broker_number[i] == written->sell_broker_number[i]); }
  assert(read->initiated_by == written->initiated_by);
  for (size_t i = 0; i < 4; i++) { assert(read->orig_trade_number[i] == written->orig_trade_number[i]); }
  assert(read->bypass == written->bypass);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_time_stamp[i] == written->trade_time_stamp[i]); }
  assert(read->cross_type == written->cross_type);
  for (size_t i = 0; i < 8; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 48);
  assert(decode_trade_correction_message(&got, wire, 0) == 48);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 48);
  assert(encode_trade_correction_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Terms Message: 53 bytes -------------------------------- */

typedef struct {
  uint8_t symbol[9];                     /* bytes 0 to 8 */
  uint8_t trade_number[4];               /* bytes 9 to 12 */
  uint8_t price[8];                      /* bytes 13 to 20 */
  uint8_t volume[4];                     /* bytes 21 to 24 */
  uint8_t buy_broker_number[2];          /* bytes 25 to 26 */
  uint8_t sell_broker_number[2];         /* bytes 27 to 28 */
  uint8_t initiated_by;                  /* byte 29 */
  uint8_t orig_trade_number[4];          /* bytes 30 to 33 */
  uint8_t trade_time_stamp[4];           /* bytes 34 to 37 */
  uint8_t non_resident;                  /* byte 38 */
  uint8_t settlement_terms;              /* byte 39 */
  uint8_t settlement_date[4];            /* bytes 40 to 43 */
  uint8_t cross_type;                    /* byte 44 */
  uint8_t trading_system_time_stamp[8];  /* bytes 45 to 52 */
} TradeCorrectionTermsMessage;

/* any Trade Correction Terms Message at all: every byte one the checker chooses */
static void any_trade_correction_terms_message(TradeCorrectionTermsMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->buy_broker_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->sell_broker_number[i] = arbitrary(); }
  record->initiated_by = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->orig_trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_time_stamp[i] = arbitrary(); }
  record->non_resident = arbitrary();
  record->settlement_terms = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->settlement_date[i] = arbitrary(); }
  record->cross_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = arbitrary(); }
}

/* Trade Correction Terms Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_terms_message(const TradeCorrectionTermsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->buy_broker_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sell_broker_number[i]; }
  wire[at++] = record->initiated_by;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orig_trade_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_time_stamp[i]; }
  wire[at++] = record->non_resident;
  wire[at++] = record->settlement_terms;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settlement_date[i]; }
  wire[at++] = record->cross_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_system_time_stamp[i]; }

  return at;
}

/* Trade Correction Terms Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_terms_message(TradeCorrectionTermsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->buy_broker_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->sell_broker_number[i] = wire[at++]; }
  record->initiated_by = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->orig_trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_time_stamp[i] = wire[at++]; }
  record->non_resident = wire[at++];
  record->settlement_terms = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->settlement_date[i] = wire[at++]; }
  record->cross_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trading_system_time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Correction Terms Message is what was written, byte for byte */
static void equal_trade_correction_terms_message(const TradeCorrectionTermsMessage *read, const TradeCorrectionTermsMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->buy_broker_number[i] == written->buy_broker_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->sell_broker_number[i] == written->sell_broker_number[i]); }
  assert(read->initiated_by == written->initiated_by);
  for (size_t i = 0; i < 4; i++) { assert(read->orig_trade_number[i] == written->orig_trade_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_time_stamp[i] == written->trade_time_stamp[i]); }
  assert(read->non_resident == written->non_resident);
  assert(read->settlement_terms == written->settlement_terms);
  for (size_t i = 0; i < 4; i++) { assert(read->settlement_date[i] == written->settlement_date[i]); }
  assert(read->cross_type == written->cross_type);
  for (size_t i = 0; i < 8; i++) { assert(read->trading_system_time_stamp[i] == written->trading_system_time_stamp[i]); }
}

/* Trade Correction Terms Message: written and read back, then read and written back */
static void check_trade_correction_terms_message(void) {
  TradeCorrectionTermsMessage sent;
  TradeCorrectionTermsMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_trade_correction_terms_message(&sent);
  assert(encode_trade_correction_terms_message(&sent, wire, 0) == 53);
  assert(decode_trade_correction_terms_message(&got, wire, 0) == 53);
  equal_trade_correction_terms_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_terms_message(&got, wire, 0) == 53);
  assert(encode_trade_correction_terms_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_frame_header();
  check_body_header();
  check_business_header();
  check_symbol_status_message();
  check_order_book_message();
  check_order_book_terms_message();
  check_assign_cop_no_orders_message();
  check_market_state_update_message();
  check_moc_imbalance_message();
  check_order_booked_message();
  check_order_booked_terms_message();
  check_order_cancelled_message();
  check_order_cancelled_terms_message();
  check_order_price_time_assigned_message();
  check_order_price_time_assigned_terms_message();
  check_stock_status_message();
  check_trade_report_message();
  check_trade_report_terms_message();
  check_trade_cancelled_message();
  check_trade_cancelled_terms_message();
  check_trade_correction_message();
  check_trade_correction_terms_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
