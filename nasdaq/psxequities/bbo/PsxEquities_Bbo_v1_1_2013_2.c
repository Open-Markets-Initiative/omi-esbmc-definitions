// nasdaq/psxequities/bbo/PsxEquities_Bbo_v1_1_2013_2.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Best Bid And Offer
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

/* ---- Packet Header: 16 bytes ------------------------------------------------- */

typedef struct {
  uint8_t session[10];         /* bytes 0 to 9 */
  uint8_t sequence_number[4];  /* bytes 10 to 13 */
  uint8_t message_count[2];    /* bytes 14 to 15 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = arbitrary(); }
}

/* Packet Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_count[i]; }

  return at;
}

/* Packet Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_count[i] == written->message_count[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[16];
  uint8_t again[16];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 16);
  assert(decode_packet_header(&got, wire, 0) == 16);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 16);
  assert(encode_packet_header(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 9 bytes ------------------------------------------------- */

typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
  uint8_t message_type;  /* byte 8 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
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

/* ---- System Event Message: 1 byte -------------------------------------------- */

/* The System Event message is used to signal key market or data feed control events. */
typedef struct {
  uint8_t event_code;  /* byte 0 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  assert(read->event_code == written->event_code);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 1);
  assert(decode_system_event_message(&got, wire, 0) == 1);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 1);
  assert(encode_system_event_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Directory Message: 10 bytes --------------------------------------- */

/* At the start of each trading day, NASDAQ PSX disseminates stock directory messages for all active symbols in its market center system. */
typedef struct {
  uint8_t issue_symbol[8];             /* bytes 0 to 7 */
  uint8_t market_category;             /* byte 8 */
  uint8_t financial_status_indicator;  /* byte 9 */
} StockDirectoryMessage;

/* any Stock Directory Message at all: every byte one the checker chooses */
static void any_stock_directory_message(StockDirectoryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->market_category = arbitrary();
  record->financial_status_indicator = arbitrary();
}

/* Stock Directory Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_stock_directory_message(const StockDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->market_category;
  wire[at++] = record->financial_status_indicator;

  return at;
}

/* Stock Directory Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_stock_directory_message(StockDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->market_category = wire[at++];
  record->financial_status_indicator = wire[at++];

  return at;
}

/* what was read of Stock Directory Message is what was written, byte for byte */
static void equal_stock_directory_message(const StockDirectoryMessage *read, const StockDirectoryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->market_category == written->market_category);
  assert(read->financial_status_indicator == written->financial_status_indicator);
}

/* Stock Directory Message: written and read back, then read and written back */
static void check_stock_directory_message(void) {
  StockDirectoryMessage sent;
  StockDirectoryMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_stock_directory_message(&sent);
  assert(encode_stock_directory_message(&sent, wire, 0) == 10);
  assert(decode_stock_directory_message(&got, wire, 0) == 10);
  equal_stock_directory_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_directory_message(&got, wire, 0) == 10);
  assert(encode_stock_directory_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Trading Action Message: 14 bytes ---------------------------------- */

/* NASDAQ OMX uses this administrative message to indicate the current trading status of a security to the trading community. */
typedef struct {
  uint8_t stock[8];               /* bytes 0 to 7 */
  uint8_t security_class;         /* byte 8 */
  uint8_t current_trading_state;  /* byte 9 */
  uint8_t reason[4];              /* bytes 10 to 13 */
} StockTradingActionMessage;

/* any Stock Trading Action Message at all: every byte one the checker chooses */
static void any_stock_trading_action_message(StockTradingActionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->security_class = arbitrary();
  record->current_trading_state = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reason[i] = arbitrary(); }
}

/* Stock Trading Action Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_stock_trading_action_message(const StockTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->security_class;
  wire[at++] = record->current_trading_state;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Stock Trading Action Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_stock_trading_action_message(StockTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->security_class = wire[at++];
  record->current_trading_state = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Trading Action Message is what was written, byte for byte */
static void equal_stock_trading_action_message(const StockTradingActionMessage *read, const StockTradingActionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->security_class == written->security_class);
  assert(read->current_trading_state == written->current_trading_state);
  for (size_t i = 0; i < 4; i++) { assert(read->reason[i] == written->reason[i]); }
}

/* Stock Trading Action Message: written and read back, then read and written back */
static void check_stock_trading_action_message(void) {
  StockTradingActionMessage sent;
  StockTradingActionMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_stock_trading_action_message(&sent);
  assert(encode_stock_trading_action_message(&sent, wire, 0) == 14);
  assert(decode_stock_trading_action_message(&got, wire, 0) == 14);
  equal_stock_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_trading_action_message(&got, wire, 0) == 14);
  assert(encode_stock_trading_action_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reg Sho Short Sale Price Test Restricted Indicator Message: 9 bytes ----- */

/* Denotes the Reg SHO Short Sale Price Test Restriction (Rule 201) status for an issue: a full pre-opening spin for NASDAQ-listed issues and intraday status changes. */
typedef struct {
  uint8_t stock[8];        /* bytes 0 to 7 */
  uint8_t reg_sho_action;  /* byte 8 */
} RegShoShortSalePriceTestRestrictedIndicatorMessage;

/* any Reg Sho Short Sale Price Test Restricted Indicator Message at all: every byte one the checker chooses */
static void any_reg_sho_short_sale_price_test_restricted_indicator_message(RegShoShortSalePriceTestRestrictedIndicatorMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->reg_sho_action = arbitrary();
}

/* Reg Sho Short Sale Price Test Restricted Indicator Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_reg_sho_short_sale_price_test_restricted_indicator_message(const RegShoShortSalePriceTestRestrictedIndicatorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->reg_sho_action;

  return at;
}

/* Reg Sho Short Sale Price Test Restricted Indicator Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_reg_sho_short_sale_price_test_restricted_indicator_message(RegShoShortSalePriceTestRestrictedIndicatorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->reg_sho_action = wire[at++];

  return at;
}

/* what was read of Reg Sho Short Sale Price Test Restricted Indicator Message is what was written, byte for byte */
static void equal_reg_sho_short_sale_price_test_restricted_indicator_message(const RegShoShortSalePriceTestRestrictedIndicatorMessage *read, const RegShoShortSalePriceTestRestrictedIndicatorMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->reg_sho_action == written->reg_sho_action);
}

/* Reg Sho Short Sale Price Test Restricted Indicator Message: written and read back, then read and written back */
static void check_reg_sho_short_sale_price_test_restricted_indicator_message(void) {
  RegShoShortSalePriceTestRestrictedIndicatorMessage sent;
  RegShoShortSalePriceTestRestrictedIndicatorMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_reg_sho_short_sale_price_test_restricted_indicator_message(&sent);
  assert(encode_reg_sho_short_sale_price_test_restricted_indicator_message(&sent, wire, 0) == 9);
  assert(decode_reg_sho_short_sale_price_test_restricted_indicator_message(&got, wire, 0) == 9);
  equal_reg_sho_short_sale_price_test_restricted_indicator_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_reg_sho_short_sale_price_test_restricted_indicator_message(&got, wire, 0) == 9);
  assert(encode_reg_sho_short_sale_price_test_restricted_indicator_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quotation Message: 47 bytes --------------------------------------------- */

/* PSX BBO will broadcast a real-time update every time that the exchange's best bid and offer quote is updated during the trading day. */
typedef struct {
  uint8_t stock[8];                  /* bytes 0 to 7 */
  uint8_t security_class;            /* byte 8 */
  uint8_t psx_best_bid_price[10];    /* bytes 9 to 18 */
  uint8_t psx_best_bid_size[9];      /* bytes 19 to 27 */
  uint8_t psx_best_offer_price[10];  /* bytes 28 to 37 */
  uint8_t psx_best_offer_size[9];    /* bytes 38 to 46 */
} QuotationMessage;

/* any Quotation Message at all: every byte one the checker chooses */
static void any_quotation_message(QuotationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->psx_best_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->psx_best_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->psx_best_offer_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->psx_best_offer_size[i] = arbitrary(); }
}

/* Quotation Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_quotation_message(const QuotationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->psx_best_bid_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->psx_best_bid_size[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->psx_best_offer_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->psx_best_offer_size[i]; }

  return at;
}

/* Quotation Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_quotation_message(QuotationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->psx_best_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->psx_best_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->psx_best_offer_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->psx_best_offer_size[i] = wire[at++]; }

  return at;
}

/* what was read of Quotation Message is what was written, byte for byte */
static void equal_quotation_message(const QuotationMessage *read, const QuotationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->psx_best_bid_price[i] == written->psx_best_bid_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->psx_best_bid_size[i] == written->psx_best_bid_size[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->psx_best_offer_price[i] == written->psx_best_offer_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->psx_best_offer_size[i] == written->psx_best_offer_size[i]); }
}

/* Quotation Message: written and read back, then read and written back */
static void check_quotation_message(void) {
  QuotationMessage sent;
  QuotationMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_quotation_message(&sent);
  assert(encode_quotation_message(&sent, wire, 0) == 47);
  assert(decode_quotation_message(&got, wire, 0) == 47);
  equal_quotation_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_quotation_message(&got, wire, 0) == 47);
  assert(encode_quotation_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_system_event_message();
  check_stock_directory_message();
  check_stock_trading_action_message();
  check_reg_sho_short_sale_price_test_restricted_indicator_message();
  check_quotation_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
