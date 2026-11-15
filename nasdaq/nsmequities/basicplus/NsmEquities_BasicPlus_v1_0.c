// nasdaq/nsmequities/basicplus/NsmEquities_BasicPlus_v1_0.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Basic Plus
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

/* ---- System Event Message: 9 bytes ------------------------------------------- */

/* System Event Messages is used to signal key market or data feed control events. */
typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
  uint8_t event_code;    /* byte 8 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->event_code == written->event_code);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 9);
  assert(decode_system_event_message(&got, wire, 0) == 9);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 9);
  assert(encode_system_event_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Quotation Message: 42 bytes -------------------------------- */

/* Consolidated BBO will broadcast a real-time update every time the Consolidated BBO across Nasdaq owned and operated exchanges is updated throughout the trading day. */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t stock[8];              /* bytes 8 to 15 */
  uint8_t best_bid_price[8];     /* bytes 16 to 23 */
  uint8_t best_bid_size[4];      /* bytes 24 to 27 */
  uint8_t best_offer_price[8];   /* bytes 28 to 35 */
  uint8_t best_offer_size[4];    /* bytes 36 to 39 */
  uint8_t best_bid_exchanges;    /* byte 40 */
  uint8_t best_offer_exchanges;  /* byte 41 */
} ConsolidatedQuotationMessage;

/* any Consolidated Quotation Message at all: every byte one the checker chooses */
static void any_consolidated_quotation_message(ConsolidatedQuotationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_offer_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_offer_size[i] = arbitrary(); }
  record->best_bid_exchanges = arbitrary();
  record->best_offer_exchanges = arbitrary();
}

/* Consolidated Quotation Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_quotation_message(const ConsolidatedQuotationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_bid_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_offer_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_offer_size[i]; }
  wire[at++] = record->best_bid_exchanges;
  wire[at++] = record->best_offer_exchanges;

  return at;
}

/* Consolidated Quotation Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_quotation_message(ConsolidatedQuotationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_offer_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_offer_size[i] = wire[at++]; }
  record->best_bid_exchanges = wire[at++];
  record->best_offer_exchanges = wire[at++];

  return at;
}

/* what was read of Consolidated Quotation Message is what was written, byte for byte */
static void equal_consolidated_quotation_message(const ConsolidatedQuotationMessage *read, const ConsolidatedQuotationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_bid_price[i] == written->best_bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_bid_size[i] == written->best_bid_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_offer_price[i] == written->best_offer_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_offer_size[i] == written->best_offer_size[i]); }
  assert(read->best_bid_exchanges == written->best_bid_exchanges);
  assert(read->best_offer_exchanges == written->best_offer_exchanges);
}

/* Consolidated Quotation Message: written and read back, then read and written back */
static void check_consolidated_quotation_message(void) {
  ConsolidatedQuotationMessage sent;
  ConsolidatedQuotationMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_consolidated_quotation_message(&sent);
  assert(encode_consolidated_quotation_message(&sent, wire, 0) == 42);
  assert(decode_consolidated_quotation_message(&got, wire, 0) == 42);
  equal_consolidated_quotation_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_quotation_message(&got, wire, 0) == 42);
  assert(encode_consolidated_quotation_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retail Price Improvement Message: 18 bytes ------------------------------ */

/* Indicates a retail interest indication of the Bid, Ask or both the Bid and Ask for Nasdaq-listed securities. Populated for the Nasdaq Texas market only. */
typedef struct {
  uint8_t timestamp[8];             /* bytes 0 to 7 */
  uint8_t stock[8];                 /* bytes 8 to 15 */
  uint8_t buy_side_rpi_exchanges;   /* byte 16 */
  uint8_t sell_side_rpi_exchanges;  /* byte 17 */
} RetailPriceImprovementMessage;

/* any Retail Price Improvement Message at all: every byte one the checker chooses */
static void any_retail_price_improvement_message(RetailPriceImprovementMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->buy_side_rpi_exchanges = arbitrary();
  record->sell_side_rpi_exchanges = arbitrary();
}

/* Retail Price Improvement Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_retail_price_improvement_message(const RetailPriceImprovementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->buy_side_rpi_exchanges;
  wire[at++] = record->sell_side_rpi_exchanges;

  return at;
}

/* Retail Price Improvement Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_retail_price_improvement_message(RetailPriceImprovementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->buy_side_rpi_exchanges = wire[at++];
  record->sell_side_rpi_exchanges = wire[at++];

  return at;
}

/* what was read of Retail Price Improvement Message is what was written, byte for byte */
static void equal_retail_price_improvement_message(const RetailPriceImprovementMessage *read, const RetailPriceImprovementMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->buy_side_rpi_exchanges == written->buy_side_rpi_exchanges);
  assert(read->sell_side_rpi_exchanges == written->sell_side_rpi_exchanges);
}

/* Retail Price Improvement Message: written and read back, then read and written back */
static void check_retail_price_improvement_message(void) {
  RetailPriceImprovementMessage sent;
  RetailPriceImprovementMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_retail_price_improvement_message(&sent);
  assert(encode_retail_price_improvement_message(&sent, wire, 0) == 18);
  assert(decode_retail_price_improvement_message(&got, wire, 0) == 18);
  equal_retail_price_improvement_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_retail_price_improvement_message(&got, wire, 0) == 18);
  assert(encode_retail_price_improvement_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Action Message: 21 bytes ---------------------------------------- */

/* Nasdaq uses this administrative message to indicate the current trading status of a security to the trading community. The message originates from the Nasdaq market center system. */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t stock[8];        /* bytes 8 to 15 */
  uint8_t trading_state;   /* byte 16 */
  uint8_t reason_code[4];  /* bytes 17 to 20 */
} TradingActionMessage;

/* any Trading Action Message at all: every byte one the checker chooses */
static void any_trading_action_message(TradingActionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->trading_state = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reason_code[i] = arbitrary(); }
}

/* Trading Action Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_trading_action_message(const TradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->trading_state;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reason_code[i]; }

  return at;
}

/* Trading Action Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_trading_action_message(TradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->trading_state = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reason_code[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Action Message is what was written, byte for byte */
static void equal_trading_action_message(const TradingActionMessage *read, const TradingActionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->trading_state == written->trading_state);
  for (size_t i = 0; i < 4; i++) { assert(read->reason_code[i] == written->reason_code[i]); }
}

/* Trading Action Message: written and read back, then read and written back */
static void check_trading_action_message(void) {
  TradingActionMessage sent;
  TradingActionMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_trading_action_message(&sent);
  assert(encode_trading_action_message(&sent, wire, 0) == 21);
  assert(decode_trading_action_message(&got, wire, 0) == 21);
  equal_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_action_message(&got, wire, 0) == 21);
  assert(encode_trading_action_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reg Sho Restriction Message: 17 bytes ----------------------------------- */

/* Reg SHO Short Sale Price Test Restricted Indicator. Sends updates for the Nasdaq market only. */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t stock[8];        /* bytes 8 to 15 */
  uint8_t reg_sho_action;  /* byte 16 */
} RegShoRestrictionMessage;

/* any Reg Sho Restriction Message at all: every byte one the checker chooses */
static void any_reg_sho_restriction_message(RegShoRestrictionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->reg_sho_action = arbitrary();
}

/* Reg Sho Restriction Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_reg_sho_restriction_message(const RegShoRestrictionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->reg_sho_action;

  return at;
}

/* Reg Sho Restriction Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_reg_sho_restriction_message(RegShoRestrictionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->reg_sho_action = wire[at++];

  return at;
}

/* what was read of Reg Sho Restriction Message is what was written, byte for byte */
static void equal_reg_sho_restriction_message(const RegShoRestrictionMessage *read, const RegShoRestrictionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->reg_sho_action == written->reg_sho_action);
}

/* Reg Sho Restriction Message: written and read back, then read and written back */
static void check_reg_sho_restriction_message(void) {
  RegShoRestrictionMessage sent;
  RegShoRestrictionMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_reg_sho_restriction_message(&sent);
  assert(encode_reg_sho_restriction_message(&sent, wire, 0) == 17);
  assert(decode_reg_sho_restriction_message(&got, wire, 0) == 17);
  equal_reg_sho_restriction_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_reg_sho_restriction_message(&got, wire, 0) == 17);
  assert(encode_reg_sho_restriction_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Directory Message: 36 bytes --------------------------------------- */

/* At the start of each trading day, Nasdaq disseminates stock directory messages for all active Nasdaq and non Nasdaq listed security symbols. The Stock Directory can be sent again during the trading day if any value changes. */
typedef struct {
  uint8_t timestamp[8];                    /* bytes 0 to 7 */
  uint8_t stock[8];                        /* bytes 8 to 15 */
  uint8_t market_category;                 /* byte 16 */
  uint8_t financial_status_indicator;      /* byte 17 */
  uint8_t round_lot_size[4];               /* bytes 18 to 21 */
  uint8_t round_lots_only;                 /* byte 22 */
  uint8_t issue_classification;            /* byte 23 */
  uint8_t issue_sub_type[2];               /* bytes 24 to 25 */
  uint8_t authenticity;                    /* byte 26 */
  uint8_t short_sale_threshold_indicator;  /* byte 27 */
  uint8_t ipo_flag;                        /* byte 28 */
  uint8_t luld_reference_price_tier;       /* byte 29 */
  uint8_t etp_flag;                        /* byte 30 */
  uint8_t etp_leverage_factor[4];          /* bytes 31 to 34 */
  uint8_t inverse_indicator;               /* byte 35 */
} StockDirectoryMessage;

/* any Stock Directory Message at all: every byte one the checker chooses */
static void any_stock_directory_message(StockDirectoryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->market_category = arbitrary();
  record->financial_status_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->round_lot_size[i] = arbitrary(); }
  record->round_lots_only = arbitrary();
  record->issue_classification = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->issue_sub_type[i] = arbitrary(); }
  record->authenticity = arbitrary();
  record->short_sale_threshold_indicator = arbitrary();
  record->ipo_flag = arbitrary();
  record->luld_reference_price_tier = arbitrary();
  record->etp_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->etp_leverage_factor[i] = arbitrary(); }
  record->inverse_indicator = arbitrary();
}

/* Stock Directory Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_stock_directory_message(const StockDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->market_category;
  wire[at++] = record->financial_status_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->round_lot_size[i]; }
  wire[at++] = record->round_lots_only;
  wire[at++] = record->issue_classification;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->issue_sub_type[i]; }
  wire[at++] = record->authenticity;
  wire[at++] = record->short_sale_threshold_indicator;
  wire[at++] = record->ipo_flag;
  wire[at++] = record->luld_reference_price_tier;
  wire[at++] = record->etp_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->etp_leverage_factor[i]; }
  wire[at++] = record->inverse_indicator;

  return at;
}

/* Stock Directory Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_stock_directory_message(StockDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->market_category = wire[at++];
  record->financial_status_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->round_lot_size[i] = wire[at++]; }
  record->round_lots_only = wire[at++];
  record->issue_classification = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->issue_sub_type[i] = wire[at++]; }
  record->authenticity = wire[at++];
  record->short_sale_threshold_indicator = wire[at++];
  record->ipo_flag = wire[at++];
  record->luld_reference_price_tier = wire[at++];
  record->etp_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->etp_leverage_factor[i] = wire[at++]; }
  record->inverse_indicator = wire[at++];

  return at;
}

/* what was read of Stock Directory Message is what was written, byte for byte */
static void equal_stock_directory_message(const StockDirectoryMessage *read, const StockDirectoryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->market_category == written->market_category);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->round_lot_size[i] == written->round_lot_size[i]); }
  assert(read->round_lots_only == written->round_lots_only);
  assert(read->issue_classification == written->issue_classification);
  for (size_t i = 0; i < 2; i++) { assert(read->issue_sub_type[i] == written->issue_sub_type[i]); }
  assert(read->authenticity == written->authenticity);
  assert(read->short_sale_threshold_indicator == written->short_sale_threshold_indicator);
  assert(read->ipo_flag == written->ipo_flag);
  assert(read->luld_reference_price_tier == written->luld_reference_price_tier);
  assert(read->etp_flag == written->etp_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->etp_leverage_factor[i] == written->etp_leverage_factor[i]); }
  assert(read->inverse_indicator == written->inverse_indicator);
}

/* Stock Directory Message: written and read back, then read and written back */
static void check_stock_directory_message(void) {
  StockDirectoryMessage sent;
  StockDirectoryMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_stock_directory_message(&sent);
  assert(encode_stock_directory_message(&sent, wire, 0) == 36);
  assert(decode_stock_directory_message(&got, wire, 0) == 36);
  equal_stock_directory_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_directory_message(&got, wire, 0) == 36);
  assert(encode_stock_directory_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mwcb Decline Level Message: 32 bytes ------------------------------------ */

/* Informs data recipients what the daily MWCB breach points are set to for the current trading day. */
typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
  uint8_t level_1[8];    /* bytes 8 to 15 */
  uint8_t level_2[8];    /* bytes 16 to 23 */
  uint8_t level_3[8];    /* bytes 24 to 31 */
} MwcbDeclineLevelMessage;

/* any Mwcb Decline Level Message at all: every byte one the checker chooses */
static void any_mwcb_decline_level_message(MwcbDeclineLevelMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->level_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->level_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->level_3[i] = arbitrary(); }
}

/* Mwcb Decline Level Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_mwcb_decline_level_message(const MwcbDeclineLevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->level_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->level_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->level_3[i]; }

  return at;
}

/* Mwcb Decline Level Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_mwcb_decline_level_message(MwcbDeclineLevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->level_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->level_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->level_3[i] = wire[at++]; }

  return at;
}

/* what was read of Mwcb Decline Level Message is what was written, byte for byte */
static void equal_mwcb_decline_level_message(const MwcbDeclineLevelMessage *read, const MwcbDeclineLevelMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->level_1[i] == written->level_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->level_2[i] == written->level_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->level_3[i] == written->level_3[i]); }
}

/* Mwcb Decline Level Message: written and read back, then read and written back */
static void check_mwcb_decline_level_message(void) {
  MwcbDeclineLevelMessage sent;
  MwcbDeclineLevelMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_mwcb_decline_level_message(&sent);
  assert(encode_mwcb_decline_level_message(&sent, wire, 0) == 32);
  assert(decode_mwcb_decline_level_message(&got, wire, 0) == 32);
  equal_mwcb_decline_level_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_mwcb_decline_level_message(&got, wire, 0) == 32);
  assert(encode_mwcb_decline_level_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mwcb Status Message: 9 bytes -------------------------------------------- */

/* Informs data recipients when a MWCB has breached one of the established levels. */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t breached_level;  /* byte 8 */
} MwcbStatusMessage;

/* any Mwcb Status Message at all: every byte one the checker chooses */
static void any_mwcb_status_message(MwcbStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->breached_level = arbitrary();
}

/* Mwcb Status Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_mwcb_status_message(const MwcbStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->breached_level;

  return at;
}

/* Mwcb Status Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_mwcb_status_message(MwcbStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->breached_level = wire[at++];

  return at;
}

/* what was read of Mwcb Status Message is what was written, byte for byte */
static void equal_mwcb_status_message(const MwcbStatusMessage *read, const MwcbStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->breached_level == written->breached_level);
}

/* Mwcb Status Message: written and read back, then read and written back */
static void check_mwcb_status_message(void) {
  MwcbStatusMessage sent;
  MwcbStatusMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_mwcb_status_message(&sent);
  assert(encode_mwcb_status_message(&sent, wire, 0) == 9);
  assert(decode_mwcb_status_message(&got, wire, 0) == 9);
  equal_mwcb_status_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_mwcb_status_message(&got, wire, 0) == 9);
  assert(encode_mwcb_status_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ipo Quoting Period Update: 29 bytes ------------------------------------- */

/* Indicates the anticipated IPO quotation release time of a security. Populated for the Nasdaq market only. */
typedef struct {
  uint8_t timestamp[8];                     /* bytes 0 to 7 */
  uint8_t stock[8];                         /* bytes 8 to 15 */
  uint8_t ipo_quotation_release_time[4];    /* bytes 16 to 19 */
  uint8_t ipo_quotation_release_qualifier;  /* byte 20 */
  uint8_t ipo_price[8];                     /* bytes 21 to 28 */
} IpoQuotingPeriodUpdate;

/* any Ipo Quoting Period Update at all: every byte one the checker chooses */
static void any_ipo_quoting_period_update(IpoQuotingPeriodUpdate *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ipo_quotation_release_time[i] = arbitrary(); }
  record->ipo_quotation_release_qualifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->ipo_price[i] = arbitrary(); }
}

/* Ipo Quoting Period Update to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_ipo_quoting_period_update(const IpoQuotingPeriodUpdate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ipo_quotation_release_time[i]; }
  wire[at++] = record->ipo_quotation_release_qualifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ipo_price[i]; }

  return at;
}

/* Ipo Quoting Period Update off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_ipo_quoting_period_update(IpoQuotingPeriodUpdate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ipo_quotation_release_time[i] = wire[at++]; }
  record->ipo_quotation_release_qualifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->ipo_price[i] = wire[at++]; }

  return at;
}

/* what was read of Ipo Quoting Period Update is what was written, byte for byte */
static void equal_ipo_quoting_period_update(const IpoQuotingPeriodUpdate *read, const IpoQuotingPeriodUpdate *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ipo_quotation_release_time[i] == written->ipo_quotation_release_time[i]); }
  assert(read->ipo_quotation_release_qualifier == written->ipo_quotation_release_qualifier);
  for (size_t i = 0; i < 8; i++) { assert(read->ipo_price[i] == written->ipo_price[i]); }
}

/* Ipo Quoting Period Update: written and read back, then read and written back */
static void check_ipo_quoting_period_update(void) {
  IpoQuotingPeriodUpdate sent;
  IpoQuotingPeriodUpdate got;
  uint8_t wire[29];
  uint8_t again[29];

  any_ipo_quoting_period_update(&sent);
  assert(encode_ipo_quoting_period_update(&sent, wire, 0) == 29);
  assert(decode_ipo_quoting_period_update(&got, wire, 0) == 29);
  equal_ipo_quoting_period_update(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_ipo_quoting_period_update(&got, wire, 0) == 29);
  assert(encode_ipo_quoting_period_update(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Operational Halt Message: 18 bytes -------------------------------------- */

/* The Exchange uses this message to indicate the current Operational Status of a security to the trading community, for the three market centers operated by Nasdaq. */
typedef struct {
  uint8_t timestamp[8];             /* bytes 0 to 7 */
  uint8_t stock[8];                 /* bytes 8 to 15 */
  uint8_t market_code;              /* byte 16 */
  uint8_t operational_halt_action;  /* byte 17 */
} OperationalHaltMessage;

/* any Operational Halt Message at all: every byte one the checker chooses */
static void any_operational_halt_message(OperationalHaltMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->market_code = arbitrary();
  record->operational_halt_action = arbitrary();
}

/* Operational Halt Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_operational_halt_message(const OperationalHaltMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->market_code;
  wire[at++] = record->operational_halt_action;

  return at;
}

/* Operational Halt Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_operational_halt_message(OperationalHaltMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->market_code = wire[at++];
  record->operational_halt_action = wire[at++];

  return at;
}

/* what was read of Operational Halt Message is what was written, byte for byte */
static void equal_operational_halt_message(const OperationalHaltMessage *read, const OperationalHaltMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->market_code == written->market_code);
  assert(read->operational_halt_action == written->operational_halt_action);
}

/* Operational Halt Message: written and read back, then read and written back */
static void check_operational_halt_message(void) {
  OperationalHaltMessage sent;
  OperationalHaltMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_operational_halt_message(&sent);
  assert(encode_operational_halt_message(&sent, wire, 0) == 18);
  assert(decode_operational_halt_message(&got, wire, 0) == 18);
  equal_operational_halt_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_operational_halt_message(&got, wire, 0) == 18);
  assert(encode_operational_halt_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_system_event_message();
  check_consolidated_quotation_message();
  check_retail_price_improvement_message();
  check_trading_action_message();
  check_reg_sho_restriction_message();
  check_stock_directory_message();
  check_mwcb_decline_level_message();
  check_mwcb_status_message();
  check_ipo_quoting_period_update();
  check_operational_halt_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
