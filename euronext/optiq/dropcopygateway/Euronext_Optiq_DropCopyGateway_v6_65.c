// euronext/optiq/dropcopygateway/Euronext_Optiq_DropCopyGateway_v6_65.c
/*
 * Euronext Drop Copy Gateway
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
 *   - a block whose stated length holds more than its fields
 *   - a run counted by a field
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

/* ---- Frame Header: 2 bytes --------------------------------------------------- */

/* Optiq length prefix, read before the message it frames */
typedef struct {
  uint8_t frame[2];  /* bytes 0 to 1 */
} FrameHeader;

/* any Frame Header at all: every byte one the checker chooses */
static void any_frame_header(FrameHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->frame[i] = arbitrary(); }
}

/* Frame Header to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_frame_header(const FrameHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->frame[i]; }

  return at;
}

/* Frame Header off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_frame_header(FrameHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->frame[i] = wire[at++]; }

  return at;
}

/* what was read of Frame Header is what was written, byte for byte */
static void equal_frame_header(const FrameHeader *read, const FrameHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->frame[i] == written->frame[i]); }
}

/* Frame Header: written and read back, then read and written back */
static void check_frame_header(void) {
  FrameHeader sent;
  FrameHeader got;
  uint8_t wire[2];
  uint8_t again[2];

  any_frame_header(&sent);
  assert(encode_frame_header(&sent, wire, 0) == 2);
  assert(decode_frame_header(&got, wire, 0) == 2);
  equal_frame_header(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_frame_header(&got, wire, 0) == 2);
  assert(encode_frame_header(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 8 bytes ------------------------------------------------- */

/* Optiq Sbe message header — message identifiers and length of message root */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id[2];   /* bytes 2 to 3 */
  uint8_t schema_id[2];     /* bytes 4 to 5 */
  uint8_t version[2];       /* bytes 6 to 7 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Message Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->schema_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Message Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->schema_id[i] == written->schema_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 8);
  assert(decode_message_header(&got, wire, 0) == 8);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 8);
  assert(encode_message_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dc Price Update Message: 67 bytes --------------------------------------- */

/* DCPriceUpdateMessage */
typedef struct {
  uint8_t msg_seq_num[4];        /* bytes 0 to 3 */
  uint8_t produce_time[8];       /* bytes 4 to 11 */
  uint8_t consume_time[8];       /* bytes 12 to 19 */
  uint8_t emm;                   /* byte 20 */
  uint8_t event_id[8];           /* bytes 21 to 28 */
  uint8_t event_time[8];         /* bytes 29 to 36 */
  uint8_t price_type;            /* byte 37 */
  uint8_t symbol_index[4];       /* bytes 38 to 41 */
  uint8_t price_optional[8];     /* bytes 42 to 49 */
  uint8_t quantity_optional[8];  /* bytes 50 to 57 */
  uint8_t imbalance_qty[8];      /* bytes 58 to 65 */
  uint8_t imbalance_qty_side;    /* byte 66 */
} DcPriceUpdateMessage;

/* any Dc Price Update Message at all: every byte one the checker chooses */
static void any_dc_price_update_message(DcPriceUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = arbitrary(); }
  record->emm = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_time[i] = arbitrary(); }
  record->price_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->imbalance_qty[i] = arbitrary(); }
  record->imbalance_qty_side = arbitrary();
}

/* Dc Price Update Message to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_dc_price_update_message(const DcPriceUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->produce_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consume_time[i]; }
  wire[at++] = record->emm;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_time[i]; }
  wire[at++] = record->price_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->imbalance_qty[i]; }
  wire[at++] = record->imbalance_qty_side;

  return at;
}

/* Dc Price Update Message off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_dc_price_update_message(DcPriceUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = wire[at++]; }
  record->emm = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_time[i] = wire[at++]; }
  record->price_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->imbalance_qty[i] = wire[at++]; }
  record->imbalance_qty_side = wire[at++];

  return at;
}

/* what was read of Dc Price Update Message is what was written, byte for byte */
static void equal_dc_price_update_message(const DcPriceUpdateMessage *read, const DcPriceUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->produce_time[i] == written->produce_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consume_time[i] == written->consume_time[i]); }
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 8; i++) { assert(read->event_id[i] == written->event_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_time[i] == written->event_time[i]); }
  assert(read->price_type == written->price_type);
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_optional[i] == written->price_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_optional[i] == written->quantity_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->imbalance_qty[i] == written->imbalance_qty[i]); }
  assert(read->imbalance_qty_side == written->imbalance_qty_side);
}

/* Dc Price Update Message: written and read back, then read and written back */
static void check_dc_price_update_message(void) {
  DcPriceUpdateMessage sent;
  DcPriceUpdateMessage got;
  uint8_t wire[67];
  uint8_t again[67];

  any_dc_price_update_message(&sent);
  assert(encode_dc_price_update_message(&sent, wire, 0) == 67);
  assert(decode_dc_price_update_message(&got, wire, 0) == 67);
  equal_dc_price_update_message(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_dc_price_update_message(&got, wire, 0) == 67);
  assert(encode_dc_price_update_message(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Size Encoding: 2 bytes -------------------------------------------- */

/* groupSizeEncoding */
typedef struct {
  uint8_t block_length_short;  /* byte 0 */
  uint8_t num_in_group;        /* byte 1 */
} GroupSizeEncoding;

/* any Group Size Encoding at all: every byte one the checker chooses */
static void any_group_size_encoding(GroupSizeEncoding *record) {
  record->block_length_short = arbitrary();
  record->num_in_group = arbitrary();
}

/* Group Size Encoding to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_group_size_encoding(const GroupSizeEncoding *record, uint8_t *wire, size_t at) {
  wire[at++] = record->block_length_short;
  wire[at++] = record->num_in_group;

  return at;
}

/* Group Size Encoding off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_group_size_encoding(GroupSizeEncoding *record, const uint8_t *wire, size_t at) {
  record->block_length_short = wire[at++];
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Group Size Encoding is what was written, byte for byte */
static void equal_group_size_encoding(const GroupSizeEncoding *read, const GroupSizeEncoding *written) {
  assert(read->block_length_short == written->block_length_short);
  assert(read->num_in_group == written->num_in_group);
}

/* Group Size Encoding: written and read back, then read and written back */
static void check_group_size_encoding(void) {
  GroupSizeEncoding sent;
  GroupSizeEncoding got;
  uint8_t wire[2];
  uint8_t again[2];

  any_group_size_encoding(&sent);
  assert(encode_group_size_encoding(&sent, wire, 0) == 2);
  assert(decode_group_size_encoding(&got, wire, 0) == 2);
  equal_group_size_encoding(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_group_size_encoding(&got, wire, 0) == 2);
  assert(encode_group_size_encoding(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dc Short Trade Cancellation Message: 77 bytes --------------------------- */

/* DCShortTradeCancellationMessage */
typedef struct {
  uint8_t msg_seq_num[4];               /* bytes 0 to 3 */
  uint8_t produce_time[8];              /* bytes 4 to 11 */
  uint8_t consume_time[8];              /* bytes 12 to 19 */
  uint8_t execution_id[4];              /* bytes 20 to 23 */
  uint8_t emm;                          /* byte 24 */
  uint8_t event_id[8];                  /* bytes 25 to 32 */
  uint8_t symbol_index[4];              /* bytes 33 to 36 */
  uint8_t book_in[8];                   /* bytes 37 to 44 */
  uint8_t last_traded_px[8];            /* bytes 45 to 52 */
  uint8_t last_shares[8];               /* bytes 53 to 60 */
  uint8_t trade_unique_identifier[16];  /* bytes 61 to 76 */
} DcShortTradeCancellationMessage;

/* any Dc Short Trade Cancellation Message at all: every byte one the checker chooses */
static void any_dc_short_trade_cancellation_message(DcShortTradeCancellationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_id[i] = arbitrary(); }
  record->emm = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_traded_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->trade_unique_identifier[i] = arbitrary(); }
}

/* Dc Short Trade Cancellation Message to the wire: 77 bytes from at, returning where the next byte goes */
static size_t encode_dc_short_trade_cancellation_message(const DcShortTradeCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->produce_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consume_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->emm;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_traded_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_shares[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->trade_unique_identifier[i]; }

  return at;
}

/* Dc Short Trade Cancellation Message off the wire: 77 bytes from at, returning where the next byte lies */
static size_t decode_dc_short_trade_cancellation_message(DcShortTradeCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_id[i] = wire[at++]; }
  record->emm = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_traded_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->trade_unique_identifier[i] = wire[at++]; }

  return at;
}

/* what was read of Dc Short Trade Cancellation Message is what was written, byte for byte */
static void equal_dc_short_trade_cancellation_message(const DcShortTradeCancellationMessage *read, const DcShortTradeCancellationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->produce_time[i] == written->produce_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consume_time[i] == written->consume_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 8; i++) { assert(read->event_id[i] == written->event_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_in[i] == written->book_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_traded_px[i] == written->last_traded_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->trade_unique_identifier[i] == written->trade_unique_identifier[i]); }
}

/* Dc Short Trade Cancellation Message: written and read back, then read and written back */
static void check_dc_short_trade_cancellation_message(void) {
  DcShortTradeCancellationMessage sent;
  DcShortTradeCancellationMessage got;
  uint8_t wire[77];
  uint8_t again[77];

  any_dc_short_trade_cancellation_message(&sent);
  assert(encode_dc_short_trade_cancellation_message(&sent, wire, 0) == 77);
  assert(decode_dc_short_trade_cancellation_message(&got, wire, 0) == 77);
  equal_dc_short_trade_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 77; i++) { wire[i] = arbitrary(); }
  assert(decode_dc_short_trade_cancellation_message(&got, wire, 0) == 77);
  assert(encode_dc_short_trade_cancellation_message(&got, again, 0) == 77);
  for (size_t i = 0; i < 77; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dcafqrfe Message: 59 bytes ---------------------------------------------- */

/* DCAFQRFEMessage */
typedef struct {
  uint8_t msg_seq_num[4];    /* bytes 0 to 3 */
  uint8_t produce_time[8];   /* bytes 4 to 11 */
  uint8_t consume_time[8];   /* bytes 12 to 19 */
  uint8_t afq_reason;        /* byte 20 */
  uint8_t book_out_time[8];  /* bytes 21 to 28 */
  uint8_t emm;               /* byte 29 */
  uint8_t event_id[8];       /* bytes 30 to 37 */
  uint8_t symbol_index[4];   /* bytes 38 to 41 */
  uint8_t firm_id[8];        /* bytes 42 to 49 */
  uint8_t afq_indicator;     /* byte 50 */
  uint8_t oe_session_id[8];  /* bytes 51 to 58 */
} DcafqrfeMessage;

/* any Dcafqrfe Message at all: every byte one the checker chooses */
static void any_dcafqrfe_message(DcafqrfeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = arbitrary(); }
  record->afq_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->book_out_time[i] = arbitrary(); }
  record->emm = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  record->afq_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->oe_session_id[i] = arbitrary(); }
}

/* Dcafqrfe Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_dcafqrfe_message(const DcafqrfeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->produce_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consume_time[i]; }
  wire[at++] = record->afq_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_out_time[i]; }
  wire[at++] = record->emm;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  wire[at++] = record->afq_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oe_session_id[i]; }

  return at;
}

/* Dcafqrfe Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_dcafqrfe_message(DcafqrfeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = wire[at++]; }
  record->afq_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->book_out_time[i] = wire[at++]; }
  record->emm = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  record->afq_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->oe_session_id[i] = wire[at++]; }

  return at;
}

/* what was read of Dcafqrfe Message is what was written, byte for byte */
static void equal_dcafqrfe_message(const DcafqrfeMessage *read, const DcafqrfeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->produce_time[i] == written->produce_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consume_time[i] == written->consume_time[i]); }
  assert(read->afq_reason == written->afq_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->book_out_time[i] == written->book_out_time[i]); }
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 8; i++) { assert(read->event_id[i] == written->event_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  assert(read->afq_indicator == written->afq_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->oe_session_id[i] == written->oe_session_id[i]); }
}

/* Dcafqrfe Message: written and read back, then read and written back */
static void check_dcafqrfe_message(void) {
  DcafqrfeMessage sent;
  DcafqrfeMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_dcafqrfe_message(&sent);
  assert(encode_dcafqrfe_message(&sent, wire, 0) == 59);
  assert(decode_dcafqrfe_message(&got, wire, 0) == 59);
  equal_dcafqrfe_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_dcafqrfe_message(&got, wire, 0) == 59);
  assert(encode_dcafqrfe_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dc Declaration New Message: 221 bytes ----------------------------------- */

/* DCDeclarationNewMessage */
typedef struct {
  uint8_t msg_seq_num[4];                /* bytes 0 to 3 */
  uint8_t produce_time[8];               /* bytes 4 to 11 */
  uint8_t consume_time[8];               /* bytes 12 to 19 */
  uint8_t message_sending_time[8];       /* bytes 20 to 27 */
  uint8_t book_in[8];                    /* bytes 28 to 35 */
  uint8_t book_out_time[8];              /* bytes 36 to 43 */
  uint8_t oegin_from_member[8];          /* bytes 44 to 51 */
  uint8_t oegout_time_to_me[8];          /* bytes 52 to 59 */
  uint8_t event_id[8];                   /* bytes 60 to 67 */
  uint8_t declaration_event_type;        /* byte 68 */
  uint8_t firm_id[8];                    /* bytes 69 to 76 */
  uint8_t oe_session_id[8];              /* bytes 77 to 84 */
  uint8_t account_type;                  /* byte 85 */
  uint8_t client_order_id[8];            /* bytes 86 to 93 */
  uint8_t emm;                           /* byte 94 */
  uint8_t declaration_id[8];             /* bytes 95 to 102 */
  uint8_t declaration_status;            /* byte 103 */
  uint8_t price_optional[8];             /* bytes 104 to 111 */
  uint8_t quantity_optional[8];          /* bytes 112 to 119 */
  uint8_t side;                          /* byte 120 */
  uint8_t symbol_index[4];               /* bytes 121 to 124 */
  uint8_t operation_type;                /* byte 125 */
  uint8_t cross_order_indicator;         /* byte 126 */
  uint8_t entering_counterparty[8];      /* bytes 127 to 134 */
  uint8_t trader_id[16];                 /* bytes 135 to 150 */
  uint8_t investor_id[16];               /* bytes 151 to 166 */
  uint8_t free_text[18];                 /* bytes 167 to 184 */
  uint8_t principal_code[8];             /* bytes 185 to 192 */
  uint8_t clearing_firm_id_optional[8];  /* bytes 193 to 200 */
  uint8_t clearing_account[16];          /* bytes 201 to 216 */
  uint8_t settlement_period;             /* byte 217 */
  uint8_t settlement_flag;               /* byte 218 */
  uint8_t guarantee_flag;                /* byte 219 */
  uint8_t transaction_price_type;        /* byte 220 */
} DcDeclarationNewMessage;

/* any Dc Declaration New Message at all: every byte one the checker chooses */
static void any_dc_declaration_new_message(DcDeclarationNewMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_out_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oegin_from_member[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oegout_time_to_me[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = arbitrary(); }
  record->declaration_event_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oe_session_id[i] = arbitrary(); }
  record->account_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  record->emm = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->declaration_id[i] = arbitrary(); }
  record->declaration_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_optional[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->operation_type = arbitrary();
  record->cross_order_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->entering_counterparty[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->investor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->free_text[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->principal_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->clearing_firm_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->clearing_account[i] = arbitrary(); }
  record->settlement_period = arbitrary();
  record->settlement_flag = arbitrary();
  record->guarantee_flag = arbitrary();
  record->transaction_price_type = arbitrary();
}

/* Dc Declaration New Message to the wire: 221 bytes from at, returning where the next byte goes */
static size_t encode_dc_declaration_new_message(const DcDeclarationNewMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->produce_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consume_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_out_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oegin_from_member[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oegout_time_to_me[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_id[i]; }
  wire[at++] = record->declaration_event_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oe_session_id[i]; }
  wire[at++] = record->account_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  wire[at++] = record->emm;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->declaration_id[i]; }
  wire[at++] = record->declaration_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_optional[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->operation_type;
  wire[at++] = record->cross_order_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->entering_counterparty[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->investor_id[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->free_text[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->principal_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->clearing_firm_id_optional[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->clearing_account[i]; }
  wire[at++] = record->settlement_period;
  wire[at++] = record->settlement_flag;
  wire[at++] = record->guarantee_flag;
  wire[at++] = record->transaction_price_type;

  return at;
}

/* Dc Declaration New Message off the wire: 221 bytes from at, returning where the next byte lies */
static size_t decode_dc_declaration_new_message(DcDeclarationNewMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_out_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oegin_from_member[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oegout_time_to_me[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = wire[at++]; }
  record->declaration_event_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oe_session_id[i] = wire[at++]; }
  record->account_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  record->emm = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->declaration_id[i] = wire[at++]; }
  record->declaration_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_optional[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->operation_type = wire[at++];
  record->cross_order_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->entering_counterparty[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->investor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->free_text[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->principal_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->clearing_firm_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->clearing_account[i] = wire[at++]; }
  record->settlement_period = wire[at++];
  record->settlement_flag = wire[at++];
  record->guarantee_flag = wire[at++];
  record->transaction_price_type = wire[at++];

  return at;
}

/* what was read of Dc Declaration New Message is what was written, byte for byte */
static void equal_dc_declaration_new_message(const DcDeclarationNewMessage *read, const DcDeclarationNewMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->produce_time[i] == written->produce_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consume_time[i] == written->consume_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_sending_time[i] == written->message_sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_in[i] == written->book_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_out_time[i] == written->book_out_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oegin_from_member[i] == written->oegin_from_member[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oegout_time_to_me[i] == written->oegout_time_to_me[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_id[i] == written->event_id[i]); }
  assert(read->declaration_event_type == written->declaration_event_type);
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oe_session_id[i] == written->oe_session_id[i]); }
  assert(read->account_type == written->account_type);
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 8; i++) { assert(read->declaration_id[i] == written->declaration_id[i]); }
  assert(read->declaration_status == written->declaration_status);
  for (size_t i = 0; i < 8; i++) { assert(read->price_optional[i] == written->price_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_optional[i] == written->quantity_optional[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->operation_type == written->operation_type);
  assert(read->cross_order_indicator == written->cross_order_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->entering_counterparty[i] == written->entering_counterparty[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->investor_id[i] == written->investor_id[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->free_text[i] == written->free_text[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->principal_code[i] == written->principal_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->clearing_firm_id_optional[i] == written->clearing_firm_id_optional[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  assert(read->settlement_period == written->settlement_period);
  assert(read->settlement_flag == written->settlement_flag);
  assert(read->guarantee_flag == written->guarantee_flag);
  assert(read->transaction_price_type == written->transaction_price_type);
}

/* Dc Declaration New Message: written and read back, then read and written back */
static void check_dc_declaration_new_message(void) {
  DcDeclarationNewMessage sent;
  DcDeclarationNewMessage got;
  uint8_t wire[221];
  uint8_t again[221];

  any_dc_declaration_new_message(&sent);
  assert(encode_dc_declaration_new_message(&sent, wire, 0) == 221);
  assert(decode_dc_declaration_new_message(&got, wire, 0) == 221);
  equal_dc_declaration_new_message(&got, &sent);

  for (size_t i = 0; i < 221; i++) { wire[i] = arbitrary(); }
  assert(decode_dc_declaration_new_message(&got, wire, 0) == 221);
  assert(encode_dc_declaration_new_message(&got, again, 0) == 221);
  for (size_t i = 0; i < 221; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dc Short Declaration Reject Message: 102 bytes -------------------------- */

/* DCShortDeclarationRejectMessage */
typedef struct {
  uint8_t msg_seq_num[4];           /* bytes 0 to 3 */
  uint8_t produce_time[8];          /* bytes 4 to 11 */
  uint8_t consume_time[8];          /* bytes 12 to 19 */
  uint8_t message_sending_time[8];  /* bytes 20 to 27 */
  uint8_t book_in[8];               /* bytes 28 to 35 */
  uint8_t book_out_time[8];         /* bytes 36 to 43 */
  uint8_t oegin_from_member[8];     /* bytes 44 to 51 */
  uint8_t oegout_time_to_me[8];     /* bytes 52 to 59 */
  uint8_t event_id[8];              /* bytes 60 to 67 */
  uint8_t declaration_event_type;   /* byte 68 */
  uint8_t firm_id[8];               /* bytes 69 to 76 */
  uint8_t client_order_id[8];       /* bytes 77 to 84 */
  uint8_t emm;                      /* byte 85 */
  uint8_t declaration_id[8];        /* bytes 86 to 93 */
  uint8_t symbol_index[4];          /* bytes 94 to 97 */
  uint8_t error_code[2];            /* bytes 98 to 99 */
  uint8_t rejected_message_id[2];   /* bytes 100 to 101 */
} DcShortDeclarationRejectMessage;

/* any Dc Short Declaration Reject Message at all: every byte one the checker chooses */
static void any_dc_short_declaration_reject_message(DcShortDeclarationRejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_out_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oegin_from_member[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oegout_time_to_me[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = arbitrary(); }
  record->declaration_event_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  record->emm = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->declaration_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->rejected_message_id[i] = arbitrary(); }
}

/* Dc Short Declaration Reject Message to the wire: 102 bytes from at, returning where the next byte goes */
static size_t encode_dc_short_declaration_reject_message(const DcShortDeclarationRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->produce_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consume_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_out_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oegin_from_member[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oegout_time_to_me[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_id[i]; }
  wire[at++] = record->declaration_event_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  wire[at++] = record->emm;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->declaration_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->rejected_message_id[i]; }

  return at;
}

/* Dc Short Declaration Reject Message off the wire: 102 bytes from at, returning where the next byte lies */
static size_t decode_dc_short_declaration_reject_message(DcShortDeclarationRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_out_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oegin_from_member[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oegout_time_to_me[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = wire[at++]; }
  record->declaration_event_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  record->emm = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->declaration_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->rejected_message_id[i] = wire[at++]; }

  return at;
}

/* what was read of Dc Short Declaration Reject Message is what was written, byte for byte */
static void equal_dc_short_declaration_reject_message(const DcShortDeclarationRejectMessage *read, const DcShortDeclarationRejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->produce_time[i] == written->produce_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consume_time[i] == written->consume_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_sending_time[i] == written->message_sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_in[i] == written->book_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_out_time[i] == written->book_out_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oegin_from_member[i] == written->oegin_from_member[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oegout_time_to_me[i] == written->oegout_time_to_me[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_id[i] == written->event_id[i]); }
  assert(read->declaration_event_type == written->declaration_event_type);
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 8; i++) { assert(read->declaration_id[i] == written->declaration_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->error_code[i] == written->error_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->rejected_message_id[i] == written->rejected_message_id[i]); }
}

/* Dc Short Declaration Reject Message: written and read back, then read and written back */
static void check_dc_short_declaration_reject_message(void) {
  DcShortDeclarationRejectMessage sent;
  DcShortDeclarationRejectMessage got;
  uint8_t wire[102];
  uint8_t again[102];

  any_dc_short_declaration_reject_message(&sent);
  assert(encode_dc_short_declaration_reject_message(&sent, wire, 0) == 102);
  assert(decode_dc_short_declaration_reject_message(&got, wire, 0) == 102);
  equal_dc_short_declaration_reject_message(&got, &sent);

  for (size_t i = 0; i < 102; i++) { wire[i] = arbitrary(); }
  assert(decode_dc_short_declaration_reject_message(&got, wire, 0) == 102);
  assert(encode_dc_short_declaration_reject_message(&got, again, 0) == 102);
  for (size_t i = 0; i < 102; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dc Short Declaration Cancel Message: 107 bytes -------------------------- */

/* DCShortDeclarationCancelMessage */
typedef struct {
  uint8_t msg_seq_num[4];           /* bytes 0 to 3 */
  uint8_t produce_time[8];          /* bytes 4 to 11 */
  uint8_t consume_time[8];          /* bytes 12 to 19 */
  uint8_t message_sending_time[8];  /* bytes 20 to 27 */
  uint8_t book_in[8];               /* bytes 28 to 35 */
  uint8_t book_out_time[8];         /* bytes 36 to 43 */
  uint8_t oegin_from_member[8];     /* bytes 44 to 51 */
  uint8_t oegout_time_to_me[8];     /* bytes 52 to 59 */
  uint8_t event_id[8];              /* bytes 60 to 67 */
  uint8_t declaration_event_type;   /* byte 68 */
  uint8_t firm_id[8];               /* bytes 69 to 76 */
  uint8_t oe_session_id[8];         /* bytes 77 to 84 */
  uint8_t client_order_id[8];       /* bytes 85 to 92 */
  uint8_t emm;                      /* byte 93 */
  uint8_t declaration_id[8];        /* bytes 94 to 101 */
  uint8_t symbol_index[4];          /* bytes 102 to 105 */
  uint8_t declaration_kill_reason;  /* byte 106 */
} DcShortDeclarationCancelMessage;

/* any Dc Short Declaration Cancel Message at all: every byte one the checker chooses */
static void any_dc_short_declaration_cancel_message(DcShortDeclarationCancelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_out_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oegin_from_member[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oegout_time_to_me[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = arbitrary(); }
  record->declaration_event_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oe_session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  record->emm = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->declaration_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->declaration_kill_reason = arbitrary();
}

/* Dc Short Declaration Cancel Message to the wire: 107 bytes from at, returning where the next byte goes */
static size_t encode_dc_short_declaration_cancel_message(const DcShortDeclarationCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->produce_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consume_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_out_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oegin_from_member[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oegout_time_to_me[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_id[i]; }
  wire[at++] = record->declaration_event_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oe_session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  wire[at++] = record->emm;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->declaration_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->declaration_kill_reason;

  return at;
}

/* Dc Short Declaration Cancel Message off the wire: 107 bytes from at, returning where the next byte lies */
static size_t decode_dc_short_declaration_cancel_message(DcShortDeclarationCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_out_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oegin_from_member[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oegout_time_to_me[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = wire[at++]; }
  record->declaration_event_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oe_session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  record->emm = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->declaration_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->declaration_kill_reason = wire[at++];

  return at;
}

/* what was read of Dc Short Declaration Cancel Message is what was written, byte for byte */
static void equal_dc_short_declaration_cancel_message(const DcShortDeclarationCancelMessage *read, const DcShortDeclarationCancelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->produce_time[i] == written->produce_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consume_time[i] == written->consume_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_sending_time[i] == written->message_sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_in[i] == written->book_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_out_time[i] == written->book_out_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oegin_from_member[i] == written->oegin_from_member[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oegout_time_to_me[i] == written->oegout_time_to_me[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_id[i] == written->event_id[i]); }
  assert(read->declaration_event_type == written->declaration_event_type);
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oe_session_id[i] == written->oe_session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 8; i++) { assert(read->declaration_id[i] == written->declaration_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->declaration_kill_reason == written->declaration_kill_reason);
}

/* Dc Short Declaration Cancel Message: written and read back, then read and written back */
static void check_dc_short_declaration_cancel_message(void) {
  DcShortDeclarationCancelMessage sent;
  DcShortDeclarationCancelMessage got;
  uint8_t wire[107];
  uint8_t again[107];

  any_dc_short_declaration_cancel_message(&sent);
  assert(encode_dc_short_declaration_cancel_message(&sent, wire, 0) == 107);
  assert(decode_dc_short_declaration_cancel_message(&got, wire, 0) == 107);
  equal_dc_short_declaration_cancel_message(&got, &sent);

  for (size_t i = 0; i < 107; i++) { wire[i] = arbitrary(); }
  assert(decode_dc_short_declaration_cancel_message(&got, wire, 0) == 107);
  assert(encode_dc_short_declaration_cancel_message(&got, again, 0) == 107);
  for (size_t i = 0; i < 107; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dc Short Trade Declaration Cancellation Message: 61 bytes --------------- */

/* DCShortTradeDeclarationCancellationMessage */
typedef struct {
  uint8_t msg_seq_num[4];   /* bytes 0 to 3 */
  uint8_t produce_time[8];  /* bytes 4 to 11 */
  uint8_t consume_time[8];  /* bytes 12 to 19 */
  uint8_t book_in[8];       /* bytes 20 to 27 */
  uint8_t event_id[8];      /* bytes 28 to 35 */
  uint8_t emm;              /* byte 36 */
  uint8_t execution_id[4];  /* bytes 37 to 40 */
  uint8_t symbol_index[4];  /* bytes 41 to 44 */
  uint8_t price[8];         /* bytes 45 to 52 */
  uint8_t quantity[8];      /* bytes 53 to 60 */
} DcShortTradeDeclarationCancellationMessage;

/* any Dc Short Trade Declaration Cancellation Message at all: every byte one the checker chooses */
static void any_dc_short_trade_declaration_cancellation_message(DcShortTradeDeclarationCancellationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = arbitrary(); }
  record->emm = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
}

/* Dc Short Trade Declaration Cancellation Message to the wire: 61 bytes from at, returning where the next byte goes */
static size_t encode_dc_short_trade_declaration_cancellation_message(const DcShortTradeDeclarationCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->produce_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consume_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_id[i]; }
  wire[at++] = record->emm;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Dc Short Trade Declaration Cancellation Message off the wire: 61 bytes from at, returning where the next byte lies */
static size_t decode_dc_short_trade_declaration_cancellation_message(DcShortTradeDeclarationCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = wire[at++]; }
  record->emm = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Dc Short Trade Declaration Cancellation Message is what was written, byte for byte */
static void equal_dc_short_trade_declaration_cancellation_message(const DcShortTradeDeclarationCancellationMessage *read, const DcShortTradeDeclarationCancellationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->produce_time[i] == written->produce_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consume_time[i] == written->consume_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_in[i] == written->book_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_id[i] == written->event_id[i]); }
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 4; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Dc Short Trade Declaration Cancellation Message: written and read back, then read and written back */
static void check_dc_short_trade_declaration_cancellation_message(void) {
  DcShortTradeDeclarationCancellationMessage sent;
  DcShortTradeDeclarationCancellationMessage got;
  uint8_t wire[61];
  uint8_t again[61];

  any_dc_short_trade_declaration_cancellation_message(&sent);
  assert(encode_dc_short_trade_declaration_cancellation_message(&sent, wire, 0) == 61);
  assert(decode_dc_short_trade_declaration_cancellation_message(&got, wire, 0) == 61);
  equal_dc_short_trade_declaration_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 61; i++) { wire[i] = arbitrary(); }
  assert(decode_dc_short_trade_declaration_cancellation_message(&got, wire, 0) == 61);
  assert(encode_dc_short_trade_declaration_cancellation_message(&got, again, 0) == 61);
  for (size_t i = 0; i < 61; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dc Trade Bust Declaration Message: 208 bytes ---------------------------- */

/* DCTradeBustDeclarationMessage */
typedef struct {
  uint8_t msg_seq_num[4];                /* bytes 0 to 3 */
  uint8_t produce_time[8];               /* bytes 4 to 11 */
  uint8_t consume_time[8];               /* bytes 12 to 19 */
  uint8_t message_sending_time[8];       /* bytes 20 to 27 */
  uint8_t book_in[8];                    /* bytes 28 to 35 */
  uint8_t book_out_time[8];              /* bytes 36 to 43 */
  uint8_t oegin_from_member[8];          /* bytes 44 to 51 */
  uint8_t oegout_time_to_me[8];          /* bytes 52 to 59 */
  uint8_t event_id[8];                   /* bytes 60 to 67 */
  uint8_t declaration_event_type;        /* byte 68 */
  uint8_t firm_id[8];                    /* bytes 69 to 76 */
  uint8_t oe_session_id[8];              /* bytes 77 to 84 */
  uint8_t account_type;                  /* byte 85 */
  uint8_t client_order_id[8];            /* bytes 86 to 93 */
  uint8_t emm;                           /* byte 94 */
  uint8_t declaration_id[8];             /* bytes 95 to 102 */
  uint8_t declaration_status;            /* byte 103 */
  uint8_t price_optional[8];             /* bytes 104 to 111 */
  uint8_t quantity_optional[8];          /* bytes 112 to 119 */
  uint8_t side;                          /* byte 120 */
  uint8_t symbol_index[4];               /* bytes 121 to 124 */
  uint8_t operation_type;                /* byte 125 */
  uint8_t entering_counterparty[8];      /* bytes 126 to 133 */
  uint8_t trader_id[16];                 /* bytes 134 to 149 */
  uint8_t investor_id[16];               /* bytes 150 to 165 */
  uint8_t free_text[18];                 /* bytes 166 to 183 */
  uint8_t clearing_firm_id_optional[8];  /* bytes 184 to 191 */
  uint8_t clearing_account[16];          /* bytes 192 to 207 */
} DcTradeBustDeclarationMessage;

/* any Dc Trade Bust Declaration Message at all: every byte one the checker chooses */
static void any_dc_trade_bust_declaration_message(DcTradeBustDeclarationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_out_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oegin_from_member[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oegout_time_to_me[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = arbitrary(); }
  record->declaration_event_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oe_session_id[i] = arbitrary(); }
  record->account_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  record->emm = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->declaration_id[i] = arbitrary(); }
  record->declaration_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_optional[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->operation_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->entering_counterparty[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->investor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->free_text[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->clearing_firm_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->clearing_account[i] = arbitrary(); }
}

/* Dc Trade Bust Declaration Message to the wire: 208 bytes from at, returning where the next byte goes */
static size_t encode_dc_trade_bust_declaration_message(const DcTradeBustDeclarationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->produce_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consume_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_out_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oegin_from_member[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oegout_time_to_me[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_id[i]; }
  wire[at++] = record->declaration_event_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oe_session_id[i]; }
  wire[at++] = record->account_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  wire[at++] = record->emm;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->declaration_id[i]; }
  wire[at++] = record->declaration_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_optional[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->operation_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->entering_counterparty[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->investor_id[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->free_text[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->clearing_firm_id_optional[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->clearing_account[i]; }

  return at;
}

/* Dc Trade Bust Declaration Message off the wire: 208 bytes from at, returning where the next byte lies */
static size_t decode_dc_trade_bust_declaration_message(DcTradeBustDeclarationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_out_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oegin_from_member[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oegout_time_to_me[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = wire[at++]; }
  record->declaration_event_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oe_session_id[i] = wire[at++]; }
  record->account_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  record->emm = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->declaration_id[i] = wire[at++]; }
  record->declaration_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_optional[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->operation_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->entering_counterparty[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->investor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->free_text[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->clearing_firm_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->clearing_account[i] = wire[at++]; }

  return at;
}

/* what was read of Dc Trade Bust Declaration Message is what was written, byte for byte */
static void equal_dc_trade_bust_declaration_message(const DcTradeBustDeclarationMessage *read, const DcTradeBustDeclarationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->produce_time[i] == written->produce_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consume_time[i] == written->consume_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_sending_time[i] == written->message_sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_in[i] == written->book_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_out_time[i] == written->book_out_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oegin_from_member[i] == written->oegin_from_member[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oegout_time_to_me[i] == written->oegout_time_to_me[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_id[i] == written->event_id[i]); }
  assert(read->declaration_event_type == written->declaration_event_type);
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oe_session_id[i] == written->oe_session_id[i]); }
  assert(read->account_type == written->account_type);
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 8; i++) { assert(read->declaration_id[i] == written->declaration_id[i]); }
  assert(read->declaration_status == written->declaration_status);
  for (size_t i = 0; i < 8; i++) { assert(read->price_optional[i] == written->price_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_optional[i] == written->quantity_optional[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->operation_type == written->operation_type);
  for (size_t i = 0; i < 8; i++) { assert(read->entering_counterparty[i] == written->entering_counterparty[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->investor_id[i] == written->investor_id[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->free_text[i] == written->free_text[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->clearing_firm_id_optional[i] == written->clearing_firm_id_optional[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
}

/* Dc Trade Bust Declaration Message: written and read back, then read and written back */
static void check_dc_trade_bust_declaration_message(void) {
  DcTradeBustDeclarationMessage sent;
  DcTradeBustDeclarationMessage got;
  uint8_t wire[208];
  uint8_t again[208];

  any_dc_trade_bust_declaration_message(&sent);
  assert(encode_dc_trade_bust_declaration_message(&sent, wire, 0) == 208);
  assert(decode_dc_trade_bust_declaration_message(&got, wire, 0) == 208);
  equal_dc_trade_bust_declaration_message(&got, &sent);

  for (size_t i = 0; i < 208; i++) { wire[i] = arbitrary(); }
  assert(decode_dc_trade_bust_declaration_message(&got, wire, 0) == 208);
  assert(encode_dc_trade_bust_declaration_message(&got, again, 0) == 208);
  for (size_t i = 0; i < 208; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dc Short Declaration Fill Message: 228 bytes ---------------------------- */

/* DCShortDeclarationFillMessage */
typedef struct {
  uint8_t msg_seq_num[4];                /* bytes 0 to 3 */
  uint8_t produce_time[8];               /* bytes 4 to 11 */
  uint8_t consume_time[8];               /* bytes 12 to 19 */
  uint8_t message_sending_time[8];       /* bytes 20 to 27 */
  uint8_t book_in[8];                    /* bytes 28 to 35 */
  uint8_t book_out_time[8];              /* bytes 36 to 43 */
  uint8_t oegin_from_member[8];          /* bytes 44 to 51 */
  uint8_t oegout_time_to_me[8];          /* bytes 52 to 59 */
  uint8_t operation_type;                /* byte 60 */
  uint8_t declaration_event_type;        /* byte 61 */
  uint8_t declaration_status;            /* byte 62 */
  uint8_t event_id[8];                   /* bytes 63 to 70 */
  uint8_t emm;                           /* byte 71 */
  uint8_t symbol_index[4];               /* bytes 72 to 75 */
  uint8_t declaration_id[8];             /* bytes 76 to 83 */
  uint8_t price[8];                      /* bytes 84 to 91 */
  uint8_t quantity[8];                   /* bytes 92 to 99 */
  uint8_t side;                          /* byte 100 */
  uint8_t cross_order_indicator;         /* byte 101 */
  uint8_t trade_time[8];                 /* bytes 102 to 109 */
  uint8_t entering_counterparty[8];      /* bytes 110 to 117 */
  uint8_t session_optional;              /* byte 118 */
  uint8_t trade_type;                    /* byte 119 */
  uint8_t firm_id[8];                    /* bytes 120 to 127 */
  uint8_t oe_partition_id[2];            /* bytes 128 to 129 */
  uint8_t logical_access_id[4];          /* bytes 130 to 133 */
  uint8_t trader_id[16];                 /* bytes 134 to 149 */
  uint8_t investor_id[16];               /* bytes 150 to 165 */
  uint8_t principal_code[8];             /* bytes 166 to 173 */
  uint8_t clearing_firm_id_optional[8];  /* bytes 174 to 181 */
  uint8_t clearing_account[16];          /* bytes 182 to 197 */
  uint8_t account_type;                  /* byte 198 */
  uint8_t client_order_id[8];            /* bytes 199 to 206 */
  uint8_t free_text[18];                 /* bytes 207 to 224 */
  uint8_t settlement_period_optional;    /* byte 225 */
  uint8_t settlement_flag_optional;      /* byte 226 */
  uint8_t guarantee_flag_optional;       /* byte 227 */
} DcShortDeclarationFillMessage;

/* any Dc Short Declaration Fill Message at all: every byte one the checker chooses */
static void any_dc_short_declaration_fill_message(DcShortDeclarationFillMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_out_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oegin_from_member[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oegout_time_to_me[i] = arbitrary(); }
  record->operation_type = arbitrary();
  record->declaration_event_type = arbitrary();
  record->declaration_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = arbitrary(); }
  record->emm = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->declaration_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  record->side = arbitrary();
  record->cross_order_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->entering_counterparty[i] = arbitrary(); }
  record->session_optional = arbitrary();
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->oe_partition_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->logical_access_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->investor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->principal_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->clearing_firm_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->clearing_account[i] = arbitrary(); }
  record->account_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->free_text[i] = arbitrary(); }
  record->settlement_period_optional = arbitrary();
  record->settlement_flag_optional = arbitrary();
  record->guarantee_flag_optional = arbitrary();
}

/* Dc Short Declaration Fill Message to the wire: 228 bytes from at, returning where the next byte goes */
static size_t encode_dc_short_declaration_fill_message(const DcShortDeclarationFillMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->produce_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consume_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_out_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oegin_from_member[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oegout_time_to_me[i]; }
  wire[at++] = record->operation_type;
  wire[at++] = record->declaration_event_type;
  wire[at++] = record->declaration_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_id[i]; }
  wire[at++] = record->emm;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->declaration_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->side;
  wire[at++] = record->cross_order_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->entering_counterparty[i]; }
  wire[at++] = record->session_optional;
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->oe_partition_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->logical_access_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->investor_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->principal_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->clearing_firm_id_optional[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->clearing_account[i]; }
  wire[at++] = record->account_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->free_text[i]; }
  wire[at++] = record->settlement_period_optional;
  wire[at++] = record->settlement_flag_optional;
  wire[at++] = record->guarantee_flag_optional;

  return at;
}

/* Dc Short Declaration Fill Message off the wire: 228 bytes from at, returning where the next byte lies */
static size_t decode_dc_short_declaration_fill_message(DcShortDeclarationFillMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_out_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oegin_from_member[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oegout_time_to_me[i] = wire[at++]; }
  record->operation_type = wire[at++];
  record->declaration_event_type = wire[at++];
  record->declaration_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->event_id[i] = wire[at++]; }
  record->emm = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->declaration_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  record->side = wire[at++];
  record->cross_order_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->entering_counterparty[i] = wire[at++]; }
  record->session_optional = wire[at++];
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->oe_partition_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->logical_access_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->investor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->principal_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->clearing_firm_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->clearing_account[i] = wire[at++]; }
  record->account_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->free_text[i] = wire[at++]; }
  record->settlement_period_optional = wire[at++];
  record->settlement_flag_optional = wire[at++];
  record->guarantee_flag_optional = wire[at++];

  return at;
}

/* what was read of Dc Short Declaration Fill Message is what was written, byte for byte */
static void equal_dc_short_declaration_fill_message(const DcShortDeclarationFillMessage *read, const DcShortDeclarationFillMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->produce_time[i] == written->produce_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consume_time[i] == written->consume_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_sending_time[i] == written->message_sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_in[i] == written->book_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_out_time[i] == written->book_out_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oegin_from_member[i] == written->oegin_from_member[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oegout_time_to_me[i] == written->oegout_time_to_me[i]); }
  assert(read->operation_type == written->operation_type);
  assert(read->declaration_event_type == written->declaration_event_type);
  assert(read->declaration_status == written->declaration_status);
  for (size_t i = 0; i < 8; i++) { assert(read->event_id[i] == written->event_id[i]); }
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->declaration_id[i] == written->declaration_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->side == written->side);
  assert(read->cross_order_indicator == written->cross_order_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_time[i] == written->trade_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->entering_counterparty[i] == written->entering_counterparty[i]); }
  assert(read->session_optional == written->session_optional);
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->oe_partition_id[i] == written->oe_partition_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->logical_access_id[i] == written->logical_access_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->investor_id[i] == written->investor_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->principal_code[i] == written->principal_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->clearing_firm_id_optional[i] == written->clearing_firm_id_optional[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  assert(read->account_type == written->account_type);
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->free_text[i] == written->free_text[i]); }
  assert(read->settlement_period_optional == written->settlement_period_optional);
  assert(read->settlement_flag_optional == written->settlement_flag_optional);
  assert(read->guarantee_flag_optional == written->guarantee_flag_optional);
}

/* Dc Short Declaration Fill Message: written and read back, then read and written back */
static void check_dc_short_declaration_fill_message(void) {
  DcShortDeclarationFillMessage sent;
  DcShortDeclarationFillMessage got;
  uint8_t wire[228];
  uint8_t again[228];

  any_dc_short_declaration_fill_message(&sent);
  assert(encode_dc_short_declaration_fill_message(&sent, wire, 0) == 228);
  assert(decode_dc_short_declaration_fill_message(&got, wire, 0) == 228);
  equal_dc_short_declaration_fill_message(&got, &sent);

  for (size_t i = 0; i < 228; i++) { wire[i] = arbitrary(); }
  assert(decode_dc_short_declaration_fill_message(&got, wire, 0) == 228);
  assert(encode_dc_short_declaration_fill_message(&got, again, 0) == 228);
  for (size_t i = 0; i < 228; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dc Clear Book Message: 38 bytes ----------------------------------------- */

/* DCClearBookMessage */
typedef struct {
  uint8_t produce_time[8];    /* bytes 0 to 7 */
  uint8_t consume_time[8];    /* bytes 8 to 15 */
  uint8_t sequence_time[8];   /* bytes 16 to 23 */
  uint8_t book_in_time[8];    /* bytes 24 to 31 */
  uint8_t symbol_index[4];    /* bytes 32 to 35 */
  uint8_t emm;                /* byte 36 */
  uint8_t clear_book_origin;  /* byte 37 */
} DcClearBookMessage;

/* any Dc Clear Book Message at all: every byte one the checker chooses */
static void any_dc_clear_book_message(DcClearBookMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_in_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->emm = arbitrary();
  record->clear_book_origin = arbitrary();
}

/* Dc Clear Book Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_dc_clear_book_message(const DcClearBookMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->produce_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consume_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_in_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->emm;
  wire[at++] = record->clear_book_origin;

  return at;
}

/* Dc Clear Book Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_dc_clear_book_message(DcClearBookMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->produce_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consume_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_in_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->emm = wire[at++];
  record->clear_book_origin = wire[at++];

  return at;
}

/* what was read of Dc Clear Book Message is what was written, byte for byte */
static void equal_dc_clear_book_message(const DcClearBookMessage *read, const DcClearBookMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->produce_time[i] == written->produce_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consume_time[i] == written->consume_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_time[i] == written->sequence_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_in_time[i] == written->book_in_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->emm == written->emm);
  assert(read->clear_book_origin == written->clear_book_origin);
}

/* Dc Clear Book Message: written and read back, then read and written back */
static void check_dc_clear_book_message(void) {
  DcClearBookMessage sent;
  DcClearBookMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_dc_clear_book_message(&sent);
  assert(encode_dc_clear_book_message(&sent, wire, 0) == 38);
  assert(decode_dc_clear_book_message(&got, wire, 0) == 38);
  equal_dc_clear_book_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_dc_clear_book_message(&got, wire, 0) == 38);
  assert(encode_dc_clear_book_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_frame_header();
  check_message_header();
  check_dc_price_update_message();
  check_group_size_encoding();
  check_dc_short_trade_cancellation_message();
  check_dcafqrfe_message();
  check_dc_declaration_new_message();
  check_dc_short_declaration_reject_message();
  check_dc_short_declaration_cancel_message();
  check_dc_short_trade_declaration_cancellation_message();
  check_dc_trade_bust_declaration_message();
  check_dc_short_declaration_fill_message();
  check_dc_clear_book_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
