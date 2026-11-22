// nasdaq/nasdaqcanada/basic/NasdaqCanada_Basic_v1_6.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Nasdaq Basic Canada
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
 *   - the dispatch that chooses a message by its type
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

/* ---- Packet Header: 20 bytes ------------------------------------------------- */

/* Itch Mold Udp 64 Packet Header */
typedef struct {
  uint8_t session[10];         /* bytes 0 to 9 */
  uint8_t sequence_number[8];  /* bytes 10 to 17 */
  uint8_t message_count[2];    /* bytes 18 to 19 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = arbitrary(); }
}

/* Packet Header to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_count[i]; }

  return at;
}

/* Packet Header off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_count[i] == written->message_count[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[20];
  uint8_t again[20];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 20);
  assert(decode_packet_header(&got, wire, 0) == 20);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 20);
  assert(encode_packet_header(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* Mold Udp 64 Message Header */
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

/* ---- Quotation Message: 58 bytes --------------------------------------------- */

/* Combined Quotation Report of the Nasdaq Canada best bid and offer, with size attributed to the CXC and CX2 trading books. */
typedef struct {
  uint8_t time_stamp[8];                    /* bytes 0 to 7 */
  uint8_t stock_symbol[10];                 /* bytes 8 to 17 */
  uint8_t nasdaq_canada_best_bid_price[8];  /* bytes 18 to 25 */
  uint8_t nasdaq_canada_best_bid_size[4];   /* bytes 26 to 29 */
  uint8_t nasdaq_cxc_best_bid_size[4];      /* bytes 30 to 33 */
  uint8_t nasdaq_cx_2_best_bid_size[4];     /* bytes 34 to 37 */
  uint8_t nasdaq_canada_best_ask_price[8];  /* bytes 38 to 45 */
  uint8_t nasdaq_canada_best_ask_size[4];   /* bytes 46 to 49 */
  uint8_t nasdaq_cxc_best_ask_size[4];      /* bytes 50 to 53 */
  uint8_t nasdaq_cx_2_best_ask_size[4];     /* bytes 54 to 57 */
} QuotationMessage;

/* any Quotation Message at all: every byte one the checker chooses */
static void any_quotation_message(QuotationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nasdaq_canada_best_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nasdaq_canada_best_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nasdaq_cxc_best_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nasdaq_cx_2_best_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nasdaq_canada_best_ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nasdaq_canada_best_ask_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nasdaq_cxc_best_ask_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nasdaq_cx_2_best_ask_size[i] = arbitrary(); }
}

/* Quotation Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_quotation_message(const QuotationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nasdaq_canada_best_bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nasdaq_canada_best_bid_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nasdaq_cxc_best_bid_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nasdaq_cx_2_best_bid_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nasdaq_canada_best_ask_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nasdaq_canada_best_ask_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nasdaq_cxc_best_ask_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nasdaq_cx_2_best_ask_size[i]; }

  return at;
}

/* Quotation Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_quotation_message(QuotationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nasdaq_canada_best_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nasdaq_canada_best_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nasdaq_cxc_best_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nasdaq_cx_2_best_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nasdaq_canada_best_ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nasdaq_canada_best_ask_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nasdaq_cxc_best_ask_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nasdaq_cx_2_best_ask_size[i] = wire[at++]; }

  return at;
}

/* what was read of Quotation Message is what was written, byte for byte */
static void equal_quotation_message(const QuotationMessage *read, const QuotationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nasdaq_canada_best_bid_price[i] == written->nasdaq_canada_best_bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nasdaq_canada_best_bid_size[i] == written->nasdaq_canada_best_bid_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nasdaq_cxc_best_bid_size[i] == written->nasdaq_cxc_best_bid_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nasdaq_cx_2_best_bid_size[i] == written->nasdaq_cx_2_best_bid_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nasdaq_canada_best_ask_price[i] == written->nasdaq_canada_best_ask_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nasdaq_canada_best_ask_size[i] == written->nasdaq_canada_best_ask_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nasdaq_cxc_best_ask_size[i] == written->nasdaq_cxc_best_ask_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nasdaq_cx_2_best_ask_size[i] == written->nasdaq_cx_2_best_ask_size[i]); }
}

/* Quotation Message: written and read back, then read and written back */
static void check_quotation_message(void) {
  QuotationMessage sent;
  QuotationMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_quotation_message(&sent);
  assert(encode_quotation_message(&sent, wire, 0) == 58);
  assert(decode_quotation_message(&got, wire, 0) == 58);
  equal_quotation_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_quotation_message(&got, wire, 0) == 58);
  assert(encode_quotation_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sale Condition Modifier: 4 bytes ---------------------------------------- */

/* Sale condition modifier consists of four levels */
typedef struct {
  uint8_t sale_condition_modifier_level_1;   /* byte 0 */
  uint8_t sales_condition_modifier_level_2;  /* byte 1 */
  uint8_t sales_condition_modifier_level_3;  /* byte 2 */
  uint8_t sales_condition_modifier_level_4;  /* byte 3 */
} SaleConditionModifier;

/* any Sale Condition Modifier at all: every byte one the checker chooses */
static void any_sale_condition_modifier(SaleConditionModifier *record) {
  record->sale_condition_modifier_level_1 = arbitrary();
  record->sales_condition_modifier_level_2 = arbitrary();
  record->sales_condition_modifier_level_3 = arbitrary();
  record->sales_condition_modifier_level_4 = arbitrary();
}

/* Sale Condition Modifier to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_sale_condition_modifier(const SaleConditionModifier *record, uint8_t *wire, size_t at) {
  wire[at++] = record->sale_condition_modifier_level_1;
  wire[at++] = record->sales_condition_modifier_level_2;
  wire[at++] = record->sales_condition_modifier_level_3;
  wire[at++] = record->sales_condition_modifier_level_4;

  return at;
}

/* Sale Condition Modifier off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_sale_condition_modifier(SaleConditionModifier *record, const uint8_t *wire, size_t at) {
  record->sale_condition_modifier_level_1 = wire[at++];
  record->sales_condition_modifier_level_2 = wire[at++];
  record->sales_condition_modifier_level_3 = wire[at++];
  record->sales_condition_modifier_level_4 = wire[at++];

  return at;
}

/* what was read of Sale Condition Modifier is what was written, byte for byte */
static void equal_sale_condition_modifier(const SaleConditionModifier *read, const SaleConditionModifier *written) {
  assert(read->sale_condition_modifier_level_1 == written->sale_condition_modifier_level_1);
  assert(read->sales_condition_modifier_level_2 == written->sales_condition_modifier_level_2);
  assert(read->sales_condition_modifier_level_3 == written->sales_condition_modifier_level_3);
  assert(read->sales_condition_modifier_level_4 == written->sales_condition_modifier_level_4);
}

/* Sale Condition Modifier: written and read back, then read and written back */
static void check_sale_condition_modifier(void) {
  SaleConditionModifier sent;
  SaleConditionModifier got;
  uint8_t wire[4];
  uint8_t again[4];

  any_sale_condition_modifier(&sent);
  assert(encode_sale_condition_modifier(&sent, wire, 0) == 4);
  assert(decode_sale_condition_modifier(&got, wire, 0) == 4);
  equal_sale_condition_modifier(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_sale_condition_modifier(&got, wire, 0) == 4);
  assert(encode_sale_condition_modifier(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Report Message: 53 bytes ------------------------------------------ */

/* Relays all transactions available from or reported by the three Nasdaq Canada Trading Books for the current business day. */
typedef struct {
  uint8_t time_stamp[8];                          /* bytes 0 to 7 */
  uint8_t originating_market_center_identifier;   /* byte 8 */
  uint8_t stock_symbol[10];                       /* bytes 9 to 18 */
  uint8_t trade_number[4];                        /* bytes 19 to 22 */
  uint8_t trade_price[8];                         /* bytes 23 to 30 */
  uint8_t trade_size[4];                          /* bytes 31 to 34 */
  uint8_t broker[3];                              /* bytes 35 to 37 */
  uint8_t contra_broker[3];                       /* bytes 38 to 40 */
  SaleConditionModifier sale_condition_modifier;  /* bytes 41 to 44 */
  uint8_t consolidated_trade_volume[8];           /* bytes 45 to 52 */
} TradeReportMessage;

/* any Trade Report Message at all: every byte one the checker chooses */
static void any_trade_report_message(TradeReportMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = arbitrary(); }
  record->originating_market_center_identifier = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = arbitrary(); }
  any_sale_condition_modifier(&record->sale_condition_modifier);
  for (size_t i = 0; i < 8; i++) { record->consolidated_trade_volume[i] = arbitrary(); }
}

/* Trade Report Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_trade_report_message(const TradeReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp[i]; }
  wire[at++] = record->originating_market_center_identifier;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_size[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->contra_broker[i]; }
  at = encode_sale_condition_modifier(&record->sale_condition_modifier, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_trade_volume[i]; }

  return at;
}

/* Trade Report Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_trade_report_message(TradeReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = wire[at++]; }
  record->originating_market_center_identifier = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = wire[at++]; }
  at = decode_sale_condition_modifier(&record->sale_condition_modifier, wire, at);
  for (size_t i = 0; i < 8; i++) { record->consolidated_trade_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Report Message is what was written, byte for byte */
static void equal_trade_report_message(const TradeReportMessage *read, const TradeReportMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  assert(read->originating_market_center_identifier == written->originating_market_center_identifier);
  for (size_t i = 0; i < 10; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_size[i] == written->trade_size[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->broker[i] == written->broker[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->contra_broker[i] == written->contra_broker[i]); }
  equal_sale_condition_modifier(&read->sale_condition_modifier, &written->sale_condition_modifier);
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_trade_volume[i] == written->consolidated_trade_volume[i]); }
}

/* Trade Report Message: written and read back, then read and written back */
static void check_trade_report_message(void) {
  TradeReportMessage sent;
  TradeReportMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_trade_report_message(&sent);
  assert(encode_trade_report_message(&sent, wire, 0) == 53);
  assert(decode_trade_report_message(&got, wire, 0) == 53);
  equal_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_message(&got, wire, 0) == 53);
  assert(encode_trade_report_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Break Message: 13 bytes ------------------------------------------- */

/* Sent if a Trade is cancelled during the same day as its execution. */
typedef struct {
  uint8_t time_stamp[8];                         /* bytes 0 to 7 */
  uint8_t trade_control_number[4];               /* bytes 8 to 11 */
  uint8_t originating_market_center_identifier;  /* byte 12 */
} TradeBreakMessage;

/* any Trade Break Message at all: every byte one the checker chooses */
static void any_trade_break_message(TradeBreakMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_control_number[i] = arbitrary(); }
  record->originating_market_center_identifier = arbitrary();
}

/* Trade Break Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_trade_break_message(const TradeBreakMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_control_number[i]; }
  wire[at++] = record->originating_market_center_identifier;

  return at;
}

/* Trade Break Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_trade_break_message(TradeBreakMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_control_number[i] = wire[at++]; }
  record->originating_market_center_identifier = wire[at++];

  return at;
}

/* what was read of Trade Break Message is what was written, byte for byte */
static void equal_trade_break_message(const TradeBreakMessage *read, const TradeBreakMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_control_number[i] == written->trade_control_number[i]); }
  assert(read->originating_market_center_identifier == written->originating_market_center_identifier);
}

/* Trade Break Message: written and read back, then read and written back */
static void check_trade_break_message(void) {
  TradeBreakMessage sent;
  TradeBreakMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_trade_break_message(&sent);
  assert(encode_trade_break_message(&sent, wire, 0) == 13);
  assert(decode_trade_break_message(&got, wire, 0) == 13);
  equal_trade_break_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_break_message(&got, wire, 0) == 13);
  assert(encode_trade_break_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 47 bytes -------------------------------------- */

/* Sent if a Trade is corrected during the same day as its execution. */
typedef struct {
  uint8_t time_stamp[8];                         /* bytes 0 to 7 */
  uint8_t originating_market_center_identifier;  /* byte 8 */
  uint8_t stock_symbol[10];                      /* bytes 9 to 18 */
  uint8_t original_trade_number[4];              /* bytes 19 to 22 */
  uint8_t original_trade_price[8];               /* bytes 23 to 30 */
  uint8_t original_trade_size[4];                /* bytes 31 to 34 */
  uint8_t corrected_trade_price[8];              /* bytes 35 to 42 */
  uint8_t corrected_trade_size[4];               /* bytes 43 to 46 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = arbitrary(); }
  record->originating_market_center_identifier = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_size[i] = arbitrary(); }
}

/* Trade Correction Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp[i]; }
  wire[at++] = record->originating_market_center_identifier;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_trade_size[i]; }

  return at;
}

/* Trade Correction Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = wire[at++]; }
  record->originating_market_center_identifier = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_size[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Correction Message is what was written, byte for byte */
static void equal_trade_correction_message(const TradeCorrectionMessage *read, const TradeCorrectionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  assert(read->originating_market_center_identifier == written->originating_market_center_identifier);
  for (size_t i = 0; i < 10; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_number[i] == written->original_trade_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_size[i] == written->original_trade_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_trade_price[i] == written->corrected_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_trade_size[i] == written->corrected_trade_size[i]); }
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 47);
  assert(decode_trade_correction_message(&got, wire, 0) == 47);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 47);
  assert(encode_trade_correction_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 10 bytes ------------------------------------------ */

/* Issued to indicate a market state event. */
typedef struct {
  uint8_t time_stamp[8];                         /* bytes 0 to 7 */
  uint8_t originating_market_center_identifier;  /* byte 8 */
  uint8_t event_code;                            /* byte 9 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = arbitrary(); }
  record->originating_market_center_identifier = arbitrary();
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp[i]; }
  wire[at++] = record->originating_market_center_identifier;
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = wire[at++]; }
  record->originating_market_center_identifier = wire[at++];
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  assert(read->originating_market_center_identifier == written->originating_market_center_identifier);
  assert(read->event_code == written->event_code);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 10);
  assert(decode_system_event_message(&got, wire, 0) == 10);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 10);
  assert(encode_system_event_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Directory Message: 64 bytes --------------------------------------- */

/* Disseminated at the start of each trading day for all active symbols in the Nasdaq Execution system. */
typedef struct {
  uint8_t time_stamp[8];           /* bytes 0 to 7 */
  uint8_t stock_symbol[10];        /* bytes 8 to 17 */
  uint8_t stock_display_name[40];  /* bytes 18 to 57 */
  uint8_t listing_market;          /* byte 58 */
  uint8_t board_lot_size[4];       /* bytes 59 to 62 */
  uint8_t currency;                /* byte 63 */
} StockDirectoryMessage;

/* any Stock Directory Message at all: every byte one the checker chooses */
static void any_stock_directory_message(StockDirectoryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->stock_display_name[i] = arbitrary(); }
  record->listing_market = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = arbitrary(); }
  record->currency = arbitrary();
}

/* Stock Directory Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_stock_directory_message(const StockDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock_symbol[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->stock_display_name[i]; }
  wire[at++] = record->listing_market;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->board_lot_size[i]; }
  wire[at++] = record->currency;

  return at;
}

/* Stock Directory Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_stock_directory_message(StockDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->stock_display_name[i] = wire[at++]; }
  record->listing_market = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = wire[at++]; }
  record->currency = wire[at++];

  return at;
}

/* what was read of Stock Directory Message is what was written, byte for byte */
static void equal_stock_directory_message(const StockDirectoryMessage *read, const StockDirectoryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->stock_display_name[i] == written->stock_display_name[i]); }
  assert(read->listing_market == written->listing_market);
  for (size_t i = 0; i < 4; i++) { assert(read->board_lot_size[i] == written->board_lot_size[i]); }
  assert(read->currency == written->currency);
}

/* Stock Directory Message: written and read back, then read and written back */
static void check_stock_directory_message(void) {
  StockDirectoryMessage sent;
  StockDirectoryMessage got;
  uint8_t wire[64];
  uint8_t again[64];

  any_stock_directory_message(&sent);
  assert(encode_stock_directory_message(&sent, wire, 0) == 64);
  assert(decode_stock_directory_message(&got, wire, 0) == 64);
  equal_stock_directory_message(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_directory_message(&got, wire, 0) == 64);
  assert(encode_stock_directory_message(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Status Message: 20 bytes ------------------------------------------ */

/* Indicates the current trading status of a stock. */
typedef struct {
  uint8_t time_stamp[8];     /* bytes 0 to 7 */
  uint8_t stock_symbol[10];  /* bytes 8 to 17 */
  uint8_t market;            /* byte 18 */
  uint8_t system_status;     /* byte 19 */
} StockStatusMessage;

/* any Stock Status Message at all: every byte one the checker chooses */
static void any_stock_status_message(StockStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = arbitrary(); }
  record->market = arbitrary();
  record->system_status = arbitrary();
}

/* Stock Status Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_stock_status_message(const StockStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock_symbol[i]; }
  wire[at++] = record->market;
  wire[at++] = record->system_status;

  return at;
}

/* Stock Status Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_stock_status_message(StockStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = wire[at++]; }
  record->market = wire[at++];
  record->system_status = wire[at++];

  return at;
}

/* what was read of Stock Status Message is what was written, byte for byte */
static void equal_stock_status_message(const StockStatusMessage *read, const StockStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  assert(read->market == written->market);
  assert(read->system_status == written->system_status);
}

/* Stock Status Message: written and read back, then read and written back */
static void check_stock_status_message(void) {
  StockStatusMessage sent;
  StockStatusMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_stock_status_message(&sent);
  assert(encode_stock_status_message(&sent, wire, 0) == 20);
  assert(decode_stock_status_message(&got, wire, 0) == 20);
  equal_stock_status_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_status_message(&got, wire, 0) == 20);
  assert(encode_stock_status_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Day Trade Summary Message: 74 bytes ------------------------------ */

/* Published once at 4:15PM and again at 5:15PM, including all traded symbols from the day. */
typedef struct {
  uint8_t time_stamp[8];                  /* bytes 0 to 7 */
  uint8_t stock_symbol[10];               /* bytes 8 to 17 */
  uint8_t consolidated_high_price[8];     /* bytes 18 to 25 */
  uint8_t consolidated_low_price[8];      /* bytes 26 to 33 */
  uint8_t consolidated_open_price[8];     /* bytes 34 to 41 */
  uint8_t listing_center_open_price[8];   /* bytes 42 to 49 */
  uint8_t consolidated_close_price[8];    /* bytes 50 to 57 */
  uint8_t listing_center_close_price[8];  /* bytes 58 to 65 */
  uint8_t consolidated_volume[8];         /* bytes 66 to 73 */
} EndOfDayTradeSummaryMessage;

/* any End Of Day Trade Summary Message at all: every byte one the checker chooses */
static void any_end_of_day_trade_summary_message(EndOfDayTradeSummaryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_open_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->listing_center_open_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_close_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->listing_center_close_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_volume[i] = arbitrary(); }
}

/* End Of Day Trade Summary Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_end_of_day_trade_summary_message(const EndOfDayTradeSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_open_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->listing_center_open_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_close_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->listing_center_close_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_volume[i]; }

  return at;
}

/* End Of Day Trade Summary Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_end_of_day_trade_summary_message(EndOfDayTradeSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->stock_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_open_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->listing_center_open_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_close_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->listing_center_close_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_volume[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Day Trade Summary Message is what was written, byte for byte */
static void equal_end_of_day_trade_summary_message(const EndOfDayTradeSummaryMessage *read, const EndOfDayTradeSummaryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_high_price[i] == written->consolidated_high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_low_price[i] == written->consolidated_low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_open_price[i] == written->consolidated_open_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->listing_center_open_price[i] == written->listing_center_open_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_close_price[i] == written->consolidated_close_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->listing_center_close_price[i] == written->listing_center_close_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_volume[i] == written->consolidated_volume[i]); }
}

/* End Of Day Trade Summary Message: written and read back, then read and written back */
static void check_end_of_day_trade_summary_message(void) {
  EndOfDayTradeSummaryMessage sent;
  EndOfDayTradeSummaryMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_end_of_day_trade_summary_message(&sent);
  assert(encode_end_of_day_trade_summary_message(&sent, wire, 0) == 74);
  assert(decode_end_of_day_trade_summary_message(&got, wire, 0) == 74);
  equal_end_of_day_trade_summary_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_day_trade_summary_message(&got, wire, 0) == 74);
  assert(encode_end_of_day_trade_summary_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Adjusted Closing Price Message: 27 bytes -------------------------------- */

/* Previous Day Adjusted Close Price, sent at 7:00AM to reflect any adjustments made overnight. */
typedef struct {
  uint8_t time_stamp[8];              /* bytes 0 to 7 */
  uint8_t issue_symbol[10];           /* bytes 8 to 17 */
  uint8_t security_class;             /* byte 18 */
  uint8_t adjusted_closing_price[8];  /* bytes 19 to 26 */
} AdjustedClosingPriceMessage;

/* any Adjusted Closing Price Message at all: every byte one the checker chooses */
static void any_adjusted_closing_price_message(AdjustedClosingPriceMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->adjusted_closing_price[i] = arbitrary(); }
}

/* Adjusted Closing Price Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_adjusted_closing_price_message(const AdjustedClosingPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->adjusted_closing_price[i]; }

  return at;
}

/* Adjusted Closing Price Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_adjusted_closing_price_message(AdjustedClosingPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->adjusted_closing_price[i] = wire[at++]; }

  return at;
}

/* what was read of Adjusted Closing Price Message is what was written, byte for byte */
static void equal_adjusted_closing_price_message(const AdjustedClosingPriceMessage *read, const AdjustedClosingPriceMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 8; i++) { assert(read->adjusted_closing_price[i] == written->adjusted_closing_price[i]); }
}

/* Adjusted Closing Price Message: written and read back, then read and written back */
static void check_adjusted_closing_price_message(void) {
  AdjustedClosingPriceMessage sent;
  AdjustedClosingPriceMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_adjusted_closing_price_message(&sent);
  assert(encode_adjusted_closing_price_message(&sent, wire, 0) == 27);
  assert(decode_adjusted_closing_price_message(&got, wire, 0) == 27);
  equal_adjusted_closing_price_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_adjusted_closing_price_message(&got, wire, 0) == 27);
  assert(encode_adjusted_closing_price_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_quotation_message();
  check_sale_condition_modifier();
  check_trade_report_message();
  check_trade_break_message();
  check_trade_correction_message();
  check_system_event_message();
  check_stock_directory_message();
  check_stock_status_message();
  check_end_of_day_trade_summary_message();
  check_adjusted_closing_price_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
