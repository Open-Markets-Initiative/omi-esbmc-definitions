// nasdaq/psxequities/totalview/PsxEquities_TotalView_v5_0_2018.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) TotalView Itch
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

/* ---- System Event Message: 11 bytes ------------------------------------------ */

/* Reflects the number of seconds past midnight that the Timestamp message was generated. */
typedef struct {
  uint8_t stock_locate[2];     /* bytes 0 to 1 */
  uint8_t tracking_number[2];  /* bytes 2 to 3 */
  uint8_t timestamp[6];        /* bytes 4 to 9 */
  uint8_t event_code;          /* byte 10 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->event_code == written->event_code);
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

/* ---- Stock Directory Message: 38 bytes --------------------------------------- */

/* Market data redistributors should process this message to populate the Financial Status Indicator (required display field) and the Market Category (recommended display field) for NASDAQ-listed issues. */
typedef struct {
  uint8_t stock_locate[2];                 /* bytes 0 to 1 */
  uint8_t tracking_number[2];              /* bytes 2 to 3 */
  uint8_t timestamp[6];                    /* bytes 4 to 9 */
  uint8_t stock[8];                        /* bytes 10 to 17 */
  uint8_t market_category;                 /* byte 18 */
  uint8_t financial_status_indicator;      /* byte 19 */
  uint8_t round_lot_size[4];               /* bytes 20 to 23 */
  uint8_t round_lots_only;                 /* byte 24 */
  uint8_t issue_classification;            /* byte 25 */
  uint8_t issue_sub_type[2];               /* bytes 26 to 27 */
  uint8_t authenticity;                    /* byte 28 */
  uint8_t short_sale_threshold_indicator;  /* byte 29 */
  uint8_t ipo_flag;                        /* byte 30 */
  uint8_t luld_reference_price_tier;       /* byte 31 */
  uint8_t etp_flag;                        /* byte 32 */
  uint8_t etp_leverage_factor[4];          /* bytes 33 to 36 */
  uint8_t inverse_indicator;               /* byte 37 */
} StockDirectoryMessage;

/* any Stock Directory Message at all: every byte one the checker chooses */
static void any_stock_directory_message(StockDirectoryMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
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

/* Stock Directory Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_stock_directory_message(const StockDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
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

/* Stock Directory Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_stock_directory_message(StockDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
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
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
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
  uint8_t wire[38];
  uint8_t again[38];

  any_stock_directory_message(&sent);
  assert(encode_stock_directory_message(&sent, wire, 0) == 38);
  assert(decode_stock_directory_message(&got, wire, 0) == 38);
  equal_stock_directory_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_directory_message(&got, wire, 0) == 38);
  assert(encode_stock_directory_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Trading Action Message: 24 bytes ---------------------------------- */

/* Nasdaq PSX uses this administrative message to indicate the current trading status of a security to the trading community. */
typedef struct {
  uint8_t stock_locate[2];     /* bytes 0 to 1 */
  uint8_t tracking_number[2];  /* bytes 2 to 3 */
  uint8_t timestamp[6];        /* bytes 4 to 9 */
  uint8_t stock[8];            /* bytes 10 to 17 */
  uint8_t trading_state;       /* byte 18 */
  uint8_t reserved;            /* byte 19 */
  uint8_t reason[4];           /* bytes 20 to 23 */
} StockTradingActionMessage;

/* any Stock Trading Action Message at all: every byte one the checker chooses */
static void any_stock_trading_action_message(StockTradingActionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->trading_state = arbitrary();
  record->reserved = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reason[i] = arbitrary(); }
}

/* Stock Trading Action Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_stock_trading_action_message(const StockTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->trading_state;
  wire[at++] = record->reserved;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Stock Trading Action Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_stock_trading_action_message(StockTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->trading_state = wire[at++];
  record->reserved = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Trading Action Message is what was written, byte for byte */
static void equal_stock_trading_action_message(const StockTradingActionMessage *read, const StockTradingActionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->trading_state == written->trading_state);
  assert(read->reserved == written->reserved);
  for (size_t i = 0; i < 4; i++) { assert(read->reason[i] == written->reason[i]); }
}

/* Stock Trading Action Message: written and read back, then read and written back */
static void check_stock_trading_action_message(void) {
  StockTradingActionMessage sent;
  StockTradingActionMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_stock_trading_action_message(&sent);
  assert(encode_stock_trading_action_message(&sent, wire, 0) == 24);
  assert(decode_stock_trading_action_message(&got, wire, 0) == 24);
  equal_stock_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_trading_action_message(&got, wire, 0) == 24);
  assert(encode_stock_trading_action_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reg Sho Short Sale Price Test Restricted Indicator Message: 19 bytes ---- */

/* NASDAQ PSX processes orders based on the most Reg SHO Restriction status value. */
typedef struct {
  uint8_t locate_code[2];      /* bytes 0 to 1 */
  uint8_t tracking_number[2];  /* bytes 2 to 3 */
  uint8_t timestamp[6];        /* bytes 4 to 9 */
  uint8_t stock[8];            /* bytes 10 to 17 */
  uint8_t reg_sho_action;      /* byte 18 */
} RegShoShortSalePriceTestRestrictedIndicatorMessage;

/* any Reg Sho Short Sale Price Test Restricted Indicator Message at all: every byte one the checker chooses */
static void any_reg_sho_short_sale_price_test_restricted_indicator_message(RegShoShortSalePriceTestRestrictedIndicatorMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->locate_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->reg_sho_action = arbitrary();
}

/* Reg Sho Short Sale Price Test Restricted Indicator Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_reg_sho_short_sale_price_test_restricted_indicator_message(const RegShoShortSalePriceTestRestrictedIndicatorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->locate_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->reg_sho_action;

  return at;
}

/* Reg Sho Short Sale Price Test Restricted Indicator Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_reg_sho_short_sale_price_test_restricted_indicator_message(RegShoShortSalePriceTestRestrictedIndicatorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->locate_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->reg_sho_action = wire[at++];

  return at;
}

/* what was read of Reg Sho Short Sale Price Test Restricted Indicator Message is what was written, byte for byte */
static void equal_reg_sho_short_sale_price_test_restricted_indicator_message(const RegShoShortSalePriceTestRestrictedIndicatorMessage *read, const RegShoShortSalePriceTestRestrictedIndicatorMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->locate_code[i] == written->locate_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->reg_sho_action == written->reg_sho_action);
}

/* Reg Sho Short Sale Price Test Restricted Indicator Message: written and read back, then read and written back */
static void check_reg_sho_short_sale_price_test_restricted_indicator_message(void) {
  RegShoShortSalePriceTestRestrictedIndicatorMessage sent;
  RegShoShortSalePriceTestRestrictedIndicatorMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_reg_sho_short_sale_price_test_restricted_indicator_message(&sent);
  assert(encode_reg_sho_short_sale_price_test_restricted_indicator_message(&sent, wire, 0) == 19);
  assert(decode_reg_sho_short_sale_price_test_restricted_indicator_message(&got, wire, 0) == 19);
  equal_reg_sho_short_sale_price_test_restricted_indicator_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_reg_sho_short_sale_price_test_restricted_indicator_message(&got, wire, 0) == 19);
  assert(encode_reg_sho_short_sale_price_test_restricted_indicator_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Participant Position Message: 25 bytes --------------------------- */

/* Throughout the day, Nasdaq PSX will send out this message only if Nasdaq Operations changes the status of a market participant firm in an issue. */
typedef struct {
  uint8_t stock_locate[2];           /* bytes 0 to 1 */
  uint8_t tracking_number[2];        /* bytes 2 to 3 */
  uint8_t timestamp[6];              /* bytes 4 to 9 */
  uint8_t mpid[4];                   /* bytes 10 to 13 */
  uint8_t stock[8];                  /* bytes 14 to 21 */
  uint8_t primary_market_maker;      /* byte 22 */
  uint8_t market_maker_mode;         /* byte 23 */
  uint8_t market_participant_state;  /* byte 24 */
} MarketParticipantPositionMessage;

/* any Market Participant Position Message at all: every byte one the checker chooses */
static void any_market_participant_position_message(MarketParticipantPositionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->primary_market_maker = arbitrary();
  record->market_maker_mode = arbitrary();
  record->market_participant_state = arbitrary();
}

/* Market Participant Position Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_market_participant_position_message(const MarketParticipantPositionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->primary_market_maker;
  wire[at++] = record->market_maker_mode;
  wire[at++] = record->market_participant_state;

  return at;
}

/* Market Participant Position Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_market_participant_position_message(MarketParticipantPositionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->primary_market_maker = wire[at++];
  record->market_maker_mode = wire[at++];
  record->market_participant_state = wire[at++];

  return at;
}

/* what was read of Market Participant Position Message is what was written, byte for byte */
static void equal_market_participant_position_message(const MarketParticipantPositionMessage *read, const MarketParticipantPositionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->primary_market_maker == written->primary_market_maker);
  assert(read->market_maker_mode == written->market_maker_mode);
  assert(read->market_participant_state == written->market_participant_state);
}

/* Market Participant Position Message: written and read back, then read and written back */
static void check_market_participant_position_message(void) {
  MarketParticipantPositionMessage sent;
  MarketParticipantPositionMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_market_participant_position_message(&sent);
  assert(encode_market_participant_position_message(&sent, wire, 0) == 25);
  assert(decode_market_participant_position_message(&got, wire, 0) == 25);
  equal_market_participant_position_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_market_participant_position_message(&got, wire, 0) == 25);
  assert(encode_market_participant_position_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mwcb Decline Level Message: 34 bytes ------------------------------------ */

/* Informs data recipients what the daily MWCB breach points are set to for the current trading day. */
typedef struct {
  uint8_t stock_locate[2];     /* bytes 0 to 1 */
  uint8_t tracking_number[2];  /* bytes 2 to 3 */
  uint8_t timestamp[6];        /* bytes 4 to 9 */
  uint8_t level_1[8];          /* bytes 10 to 17 */
  uint8_t level_2[8];          /* bytes 18 to 25 */
  uint8_t level_3[8];          /* bytes 26 to 33 */
} MwcbDeclineLevelMessage;

/* any Mwcb Decline Level Message at all: every byte one the checker chooses */
static void any_mwcb_decline_level_message(MwcbDeclineLevelMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->level_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->level_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->level_3[i] = arbitrary(); }
}

/* Mwcb Decline Level Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_mwcb_decline_level_message(const MwcbDeclineLevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->level_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->level_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->level_3[i]; }

  return at;
}

/* Mwcb Decline Level Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_mwcb_decline_level_message(MwcbDeclineLevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->level_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->level_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->level_3[i] = wire[at++]; }

  return at;
}

/* what was read of Mwcb Decline Level Message is what was written, byte for byte */
static void equal_mwcb_decline_level_message(const MwcbDeclineLevelMessage *read, const MwcbDeclineLevelMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->level_1[i] == written->level_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->level_2[i] == written->level_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->level_3[i] == written->level_3[i]); }
}

/* Mwcb Decline Level Message: written and read back, then read and written back */
static void check_mwcb_decline_level_message(void) {
  MwcbDeclineLevelMessage sent;
  MwcbDeclineLevelMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_mwcb_decline_level_message(&sent);
  assert(encode_mwcb_decline_level_message(&sent, wire, 0) == 34);
  assert(decode_mwcb_decline_level_message(&got, wire, 0) == 34);
  equal_mwcb_decline_level_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_mwcb_decline_level_message(&got, wire, 0) == 34);
  assert(encode_mwcb_decline_level_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mwcb Status Level Message: 11 bytes ------------------------------------- */

/* Informs data recipients when a MWCB has breached one of the established levels */
typedef struct {
  uint8_t stock_locate[2];     /* bytes 0 to 1 */
  uint8_t tracking_number[2];  /* bytes 2 to 3 */
  uint8_t timestamp[6];        /* bytes 4 to 9 */
  uint8_t breached_level;      /* byte 10 */
} MwcbStatusLevelMessage;

/* any Mwcb Status Level Message at all: every byte one the checker chooses */
static void any_mwcb_status_level_message(MwcbStatusLevelMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  record->breached_level = arbitrary();
}

/* Mwcb Status Level Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_mwcb_status_level_message(const MwcbStatusLevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->breached_level;

  return at;
}

/* Mwcb Status Level Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_mwcb_status_level_message(MwcbStatusLevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  record->breached_level = wire[at++];

  return at;
}

/* what was read of Mwcb Status Level Message is what was written, byte for byte */
static void equal_mwcb_status_level_message(const MwcbStatusLevelMessage *read, const MwcbStatusLevelMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->breached_level == written->breached_level);
}

/* Mwcb Status Level Message: written and read back, then read and written back */
static void check_mwcb_status_level_message(void) {
  MwcbStatusLevelMessage sent;
  MwcbStatusLevelMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_mwcb_status_level_message(&sent);
  assert(encode_mwcb_status_level_message(&sent, wire, 0) == 11);
  assert(decode_mwcb_status_level_message(&got, wire, 0) == 11);
  equal_mwcb_status_level_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_mwcb_status_level_message(&got, wire, 0) == 11);
  assert(encode_mwcb_status_level_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Luld Auction Collar Message: 34 bytes ----------------------------------- */

/* Indicates the auction collar thresholds within which a paused security can reopen following a LULD Trading Pause */
typedef struct {
  uint8_t stock_locate[2];                    /* bytes 0 to 1 */
  uint8_t tracking_number[2];                 /* bytes 2 to 3 */
  uint8_t timestamp[6];                       /* bytes 4 to 9 */
  uint8_t stock[8];                           /* bytes 10 to 17 */
  uint8_t auction_collar_reference_price[4];  /* bytes 18 to 21 */
  uint8_t upper_auction_collar_price[4];      /* bytes 22 to 25 */
  uint8_t lower_auction_collar_price[4];      /* bytes 26 to 29 */
  uint8_t auction_collar_extension[4];        /* bytes 30 to 33 */
} LuldAuctionCollarMessage;

/* any Luld Auction Collar Message at all: every byte one the checker chooses */
static void any_luld_auction_collar_message(LuldAuctionCollarMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_collar_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->upper_auction_collar_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lower_auction_collar_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_collar_extension[i] = arbitrary(); }
}

/* Luld Auction Collar Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_luld_auction_collar_message(const LuldAuctionCollarMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_collar_reference_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->upper_auction_collar_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lower_auction_collar_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_collar_extension[i]; }

  return at;
}

/* Luld Auction Collar Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_luld_auction_collar_message(LuldAuctionCollarMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_collar_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->upper_auction_collar_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lower_auction_collar_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_collar_extension[i] = wire[at++]; }

  return at;
}

/* what was read of Luld Auction Collar Message is what was written, byte for byte */
static void equal_luld_auction_collar_message(const LuldAuctionCollarMessage *read, const LuldAuctionCollarMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_collar_reference_price[i] == written->auction_collar_reference_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->upper_auction_collar_price[i] == written->upper_auction_collar_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lower_auction_collar_price[i] == written->lower_auction_collar_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_collar_extension[i] == written->auction_collar_extension[i]); }
}

/* Luld Auction Collar Message: written and read back, then read and written back */
static void check_luld_auction_collar_message(void) {
  LuldAuctionCollarMessage sent;
  LuldAuctionCollarMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_luld_auction_collar_message(&sent);
  assert(encode_luld_auction_collar_message(&sent, wire, 0) == 34);
  assert(decode_luld_auction_collar_message(&got, wire, 0) == 34);
  equal_luld_auction_collar_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_luld_auction_collar_message(&got, wire, 0) == 34);
  assert(encode_luld_auction_collar_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Operational Halt Message: 20 bytes -------------------------------------- */

/* Nasdaq uses this administrative message to indicate the current trading status of the three market centers operated by Nasdaq. */
typedef struct {
  uint8_t stock_locate[2];          /* bytes 0 to 1 */
  uint8_t tracking_number[2];       /* bytes 2 to 3 */
  uint8_t timestamp[6];             /* bytes 4 to 9 */
  uint8_t stock[8];                 /* bytes 10 to 17 */
  uint8_t market_code;              /* byte 18 */
  uint8_t operational_halt_action;  /* byte 19 */
} OperationalHaltMessage;

/* any Operational Halt Message at all: every byte one the checker chooses */
static void any_operational_halt_message(OperationalHaltMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->market_code = arbitrary();
  record->operational_halt_action = arbitrary();
}

/* Operational Halt Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_operational_halt_message(const OperationalHaltMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->market_code;
  wire[at++] = record->operational_halt_action;

  return at;
}

/* Operational Halt Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_operational_halt_message(OperationalHaltMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->market_code = wire[at++];
  record->operational_halt_action = wire[at++];

  return at;
}

/* what was read of Operational Halt Message is what was written, byte for byte */
static void equal_operational_halt_message(const OperationalHaltMessage *read, const OperationalHaltMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->market_code == written->market_code);
  assert(read->operational_halt_action == written->operational_halt_action);
}

/* Operational Halt Message: written and read back, then read and written back */
static void check_operational_halt_message(void) {
  OperationalHaltMessage sent;
  OperationalHaltMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_operational_halt_message(&sent);
  assert(encode_operational_halt_message(&sent, wire, 0) == 20);
  assert(decode_operational_halt_message(&got, wire, 0) == 20);
  equal_operational_halt_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_operational_halt_message(&got, wire, 0) == 20);
  assert(encode_operational_halt_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order No Mpid Attribution Message: 35 bytes ------------------------- */

/* This message will be generated for unattributed orders accepted by the NASDAQ PSX system. */
typedef struct {
  uint8_t stock_locate[2];            /* bytes 0 to 1 */
  uint8_t tracking_number[2];         /* bytes 2 to 3 */
  uint8_t timestamp[6];               /* bytes 4 to 9 */
  uint8_t order_reference_number[8];  /* bytes 10 to 17 */
  uint8_t buy_sell_indicator;         /* byte 18 */
  uint8_t shares[4];                  /* bytes 19 to 22 */
  uint8_t stock[8];                   /* bytes 23 to 30 */
  uint8_t price[4];                   /* bytes 31 to 34 */
} AddOrderNoMpidAttributionMessage;

/* any Add Order No Mpid Attribution Message at all: every byte one the checker chooses */
static void any_add_order_no_mpid_attribution_message(AddOrderNoMpidAttributionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
}

/* Add Order No Mpid Attribution Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_add_order_no_mpid_attribution_message(const AddOrderNoMpidAttributionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Add Order No Mpid Attribution Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_add_order_no_mpid_attribution_message(AddOrderNoMpidAttributionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order No Mpid Attribution Message is what was written, byte for byte */
static void equal_add_order_no_mpid_attribution_message(const AddOrderNoMpidAttributionMessage *read, const AddOrderNoMpidAttributionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
}

/* Add Order No Mpid Attribution Message: written and read back, then read and written back */
static void check_add_order_no_mpid_attribution_message(void) {
  AddOrderNoMpidAttributionMessage sent;
  AddOrderNoMpidAttributionMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_add_order_no_mpid_attribution_message(&sent);
  assert(encode_add_order_no_mpid_attribution_message(&sent, wire, 0) == 35);
  assert(decode_add_order_no_mpid_attribution_message(&got, wire, 0) == 35);
  equal_add_order_no_mpid_attribution_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_no_mpid_attribution_message(&got, wire, 0) == 35);
  assert(encode_add_order_no_mpid_attribution_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order With Mpid Attribution Message: 39 bytes ----------------------- */

/* This message will be generated for attributed orders and quotations accepted by the NASDAQ PSX system. */
typedef struct {
  uint8_t stock_locate[2];            /* bytes 0 to 1 */
  uint8_t tracking_number[2];         /* bytes 2 to 3 */
  uint8_t timestamp[6];               /* bytes 4 to 9 */
  uint8_t order_reference_number[8];  /* bytes 10 to 17 */
  uint8_t buy_sell_indicator;         /* byte 18 */
  uint8_t shares[4];                  /* bytes 19 to 22 */
  uint8_t stock[8];                   /* bytes 23 to 30 */
  uint8_t price[4];                   /* bytes 31 to 34 */
  uint8_t attribution[4];             /* bytes 35 to 38 */
} AddOrderWithMpidAttributionMessage;

/* any Add Order With Mpid Attribution Message at all: every byte one the checker chooses */
static void any_add_order_with_mpid_attribution_message(AddOrderWithMpidAttributionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->attribution[i] = arbitrary(); }
}

/* Add Order With Mpid Attribution Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_add_order_with_mpid_attribution_message(const AddOrderWithMpidAttributionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->attribution[i]; }

  return at;
}

/* Add Order With Mpid Attribution Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_add_order_with_mpid_attribution_message(AddOrderWithMpidAttributionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->attribution[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order With Mpid Attribution Message is what was written, byte for byte */
static void equal_add_order_with_mpid_attribution_message(const AddOrderWithMpidAttributionMessage *read, const AddOrderWithMpidAttributionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->attribution[i] == written->attribution[i]); }
}

/* Add Order With Mpid Attribution Message: written and read back, then read and written back */
static void check_add_order_with_mpid_attribution_message(void) {
  AddOrderWithMpidAttributionMessage sent;
  AddOrderWithMpidAttributionMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_add_order_with_mpid_attribution_message(&sent);
  assert(encode_add_order_with_mpid_attribution_message(&sent, wire, 0) == 39);
  assert(decode_add_order_with_mpid_attribution_message(&got, wire, 0) == 39);
  equal_add_order_with_mpid_attribution_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_with_mpid_attribution_message(&got, wire, 0) == 39);
  assert(encode_add_order_with_mpid_attribution_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 30 bytes ---------------------------------------- */

/* This message is sent whenever an order on the book is executed in whole or in part. It is possible to receive several Order Executed Messages for the same order reference number if that order is executed in several parts. The multiple Order Executed Messages on the same order are cumulative. */
typedef struct {
  uint8_t stock_locate[2];            /* bytes 0 to 1 */
  uint8_t tracking_number[2];         /* bytes 2 to 3 */
  uint8_t timestamp[6];               /* bytes 4 to 9 */
  uint8_t order_reference_number[8];  /* bytes 10 to 17 */
  uint8_t executed_shares[4];         /* bytes 18 to 21 */
  uint8_t match_number[8];            /* bytes 22 to 29 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Order Executed Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_shares[i] == written->executed_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 30);
  assert(decode_order_executed_message(&got, wire, 0) == 30);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 30);
  assert(encode_order_executed_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed With Price Message: 35 bytes ----------------------------- */

/* This message is sent whenever an order on the book is executed in whole or in part at a price different from the initial display price. Since the execution price is different than the display price of the original Add Order, Nasdaq PSX includes a price field within this execution message. */
typedef struct {
  uint8_t stock_locate[2];            /* bytes 0 to 1 */
  uint8_t tracking_number[2];         /* bytes 2 to 3 */
  uint8_t timestamp[6];               /* bytes 4 to 9 */
  uint8_t order_reference_number[8];  /* bytes 10 to 17 */
  uint8_t executed_shares[4];         /* bytes 18 to 21 */
  uint8_t match_number[8];            /* bytes 22 to 29 */
  uint8_t printable;                  /* byte 30 */
  uint8_t execution_price[4];         /* bytes 31 to 34 */
} OrderExecutedWithPriceMessage;

/* any Order Executed With Price Message at all: every byte one the checker chooses */
static void any_order_executed_with_price_message(OrderExecutedWithPriceMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
  record->printable = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = arbitrary(); }
}

/* Order Executed With Price Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_with_price_message(const OrderExecutedWithPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->printable;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_price[i]; }

  return at;
}

/* Order Executed With Price Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_with_price_message(OrderExecutedWithPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }
  record->printable = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed With Price Message is what was written, byte for byte */
static void equal_order_executed_with_price_message(const OrderExecutedWithPriceMessage *read, const OrderExecutedWithPriceMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_shares[i] == written->executed_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->printable == written->printable);
  for (size_t i = 0; i < 4; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
}

/* Order Executed With Price Message: written and read back, then read and written back */
static void check_order_executed_with_price_message(void) {
  OrderExecutedWithPriceMessage sent;
  OrderExecutedWithPriceMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_order_executed_with_price_message(&sent);
  assert(encode_order_executed_with_price_message(&sent, wire, 0) == 35);
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 35);
  equal_order_executed_with_price_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 35);
  assert(encode_order_executed_with_price_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Message: 22 bytes ------------------------------------------ */

/* This message is sent whenever an order on the book is modified as a result of a partial cancellation. */
typedef struct {
  uint8_t stock_locate[2];            /* bytes 0 to 1 */
  uint8_t tracking_number[2];         /* bytes 2 to 3 */
  uint8_t timestamp[6];               /* bytes 4 to 9 */
  uint8_t order_reference_number[8];  /* bytes 10 to 17 */
  uint8_t canceled_shares[4];         /* bytes 18 to 21 */
} OrderCancelMessage;

/* any Order Cancel Message at all: every byte one the checker chooses */
static void any_order_cancel_message(OrderCancelMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->canceled_shares[i] = arbitrary(); }
}

/* Order Cancel Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_message(const OrderCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->canceled_shares[i]; }

  return at;
}

/* Order Cancel Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_message(OrderCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->canceled_shares[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Message is what was written, byte for byte */
static void equal_order_cancel_message(const OrderCancelMessage *read, const OrderCancelMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->canceled_shares[i] == written->canceled_shares[i]); }
}

/* Order Cancel Message: written and read back, then read and written back */
static void check_order_cancel_message(void) {
  OrderCancelMessage sent;
  OrderCancelMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_order_cancel_message(&sent);
  assert(encode_order_cancel_message(&sent, wire, 0) == 22);
  assert(decode_order_cancel_message(&got, wire, 0) == 22);
  equal_order_cancel_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_message(&got, wire, 0) == 22);
  assert(encode_order_cancel_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Delete Message: 18 bytes ------------------------------------------ */

/* This message is sent whenever an order on the book is being cancelled. All remaining shares are no longer accessible so the order must be removed from the book. */
typedef struct {
  uint8_t stock_locate[2];            /* bytes 0 to 1 */
  uint8_t tracking_number[2];         /* bytes 2 to 3 */
  uint8_t timestamp[6];               /* bytes 4 to 9 */
  uint8_t order_reference_number[8];  /* bytes 10 to 17 */
} OrderDeleteMessage;

/* any Order Delete Message at all: every byte one the checker chooses */
static void any_order_delete_message(OrderDeleteMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
}

/* Order Delete Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_order_delete_message(const OrderDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }

  return at;
}

/* Order Delete Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_order_delete_message(OrderDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Delete Message is what was written, byte for byte */
static void equal_order_delete_message(const OrderDeleteMessage *read, const OrderDeleteMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
}

/* Order Delete Message: written and read back, then read and written back */
static void check_order_delete_message(void) {
  OrderDeleteMessage sent;
  OrderDeleteMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_order_delete_message(&sent);
  assert(encode_order_delete_message(&sent, wire, 0) == 18);
  assert(decode_order_delete_message(&got, wire, 0) == 18);
  equal_order_delete_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_order_delete_message(&got, wire, 0) == 18);
  assert(encode_order_delete_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replace Message: 34 bytes ----------------------------------------- */

/* This message is sent whenever an order on the book has been cancel-replaced. All remaining shares from the original order are no longer accessible, and must be removed. The new order details are provided for the replacement, along with a new order reference number which will be used henceforth. Since the side, stock symbol and attribution (if any) cannot be changed by an Order Replace event, these fields are not included in the message. Firms should retain the side, stock symbol and MPID from the original Add Order message. */
typedef struct {
  uint8_t stock_locate[2];                     /* bytes 0 to 1 */
  uint8_t tracking_number[2];                  /* bytes 2 to 3 */
  uint8_t timestamp[6];                        /* bytes 4 to 9 */
  uint8_t original_order_reference_number[8];  /* bytes 10 to 17 */
  uint8_t new_order_reference_number[8];       /* bytes 18 to 25 */
  uint8_t shares[4];                           /* bytes 26 to 29 */
  uint8_t price[4];                            /* bytes 30 to 33 */
} OrderReplaceMessage;

/* any Order Replace Message at all: every byte one the checker chooses */
static void any_order_replace_message(OrderReplaceMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
}

/* Order Replace Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_order_replace_message(const OrderReplaceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Replace Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_order_replace_message(OrderReplaceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Replace Message is what was written, byte for byte */
static void equal_order_replace_message(const OrderReplaceMessage *read, const OrderReplaceMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_reference_number[i] == written->original_order_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_order_reference_number[i] == written->new_order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Replace Message: written and read back, then read and written back */
static void check_order_replace_message(void) {
  OrderReplaceMessage sent;
  OrderReplaceMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_order_replace_message(&sent);
  assert(encode_order_replace_message(&sent, wire, 0) == 34);
  assert(decode_order_replace_message(&got, wire, 0) == 34);
  equal_order_replace_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replace_message(&got, wire, 0) == 34);
  assert(encode_order_replace_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message Non Cross: 43 bytes --------------------------------------- */

/* The Trade Message is designed to provide execution details for normal match events involving non-displayable order types. (Note: There is a separate message for Nasdaq PSX cross events.) */
typedef struct {
  uint8_t stock_locate[2];            /* bytes 0 to 1 */
  uint8_t tracking_number[2];         /* bytes 2 to 3 */
  uint8_t timestamp[6];               /* bytes 4 to 9 */
  uint8_t order_reference_number[8];  /* bytes 10 to 17 */
  uint8_t buy_sell_indicator;         /* byte 18 */
  uint8_t shares[4];                  /* bytes 19 to 22 */
  uint8_t stock[8];                   /* bytes 23 to 30 */
  uint8_t price[4];                   /* bytes 31 to 34 */
  uint8_t match_number[8];            /* bytes 35 to 42 */
} TradeMessageNonCross;

/* any Trade Message Non Cross at all: every byte one the checker chooses */
static void any_trade_message_non_cross(TradeMessageNonCross *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
}

/* Trade Message Non Cross to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_trade_message_non_cross(const TradeMessageNonCross *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Trade Message Non Cross off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_trade_message_non_cross(TradeMessageNonCross *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message Non Cross is what was written, byte for byte */
static void equal_trade_message_non_cross(const TradeMessageNonCross *read, const TradeMessageNonCross *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Trade Message Non Cross: written and read back, then read and written back */
static void check_trade_message_non_cross(void) {
  TradeMessageNonCross sent;
  TradeMessageNonCross got;
  uint8_t wire[43];
  uint8_t again[43];

  any_trade_message_non_cross(&sent);
  assert(encode_trade_message_non_cross(&sent, wire, 0) == 43);
  assert(decode_trade_message_non_cross(&got, wire, 0) == 43);
  equal_trade_message_non_cross(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message_non_cross(&got, wire, 0) == 43);
  assert(encode_trade_message_non_cross(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cross Trade Message: 39 bytes ------------------------------------------- */

/* Cross Trade message indicates that Nasdaq PSX has completed its cross process for a specific security. Nasdaq PSX sends out a Cross Trade message for all active issues in the system following the Opening, Closing and EMC cross events. Firms may use the Cross Trade message to determine when the cross for each security has been completed. (Note: For the halted / paused securities, firms should use the Trading Action message to determine when an issue has been released for trading.) */
typedef struct {
  uint8_t stock_locate[2];     /* bytes 0 to 1 */
  uint8_t tracking_number[2];  /* bytes 2 to 3 */
  uint8_t timestamp[6];        /* bytes 4 to 9 */
  uint8_t cross_shares[8];     /* bytes 10 to 17 */
  uint8_t stock[8];            /* bytes 18 to 25 */
  uint8_t cross_price[4];      /* bytes 26 to 29 */
  uint8_t match_number[8];     /* bytes 30 to 37 */
  uint8_t cross_type;          /* byte 38 */
} CrossTradeMessage;

/* any Cross Trade Message at all: every byte one the checker chooses */
static void any_cross_trade_message(CrossTradeMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cross_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
  record->cross_type = arbitrary();
}

/* Cross Trade Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_cross_trade_message(const CrossTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cross_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->cross_type;

  return at;
}

/* Cross Trade Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_cross_trade_message(CrossTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cross_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }
  record->cross_type = wire[at++];

  return at;
}

/* what was read of Cross Trade Message is what was written, byte for byte */
static void equal_cross_trade_message(const CrossTradeMessage *read, const CrossTradeMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cross_shares[i] == written->cross_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_price[i] == written->cross_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->cross_type == written->cross_type);
}

/* Cross Trade Message: written and read back, then read and written back */
static void check_cross_trade_message(void) {
  CrossTradeMessage sent;
  CrossTradeMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_cross_trade_message(&sent);
  assert(encode_cross_trade_message(&sent, wire, 0) == 39);
  assert(decode_cross_trade_message(&got, wire, 0) == 39);
  equal_cross_trade_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_cross_trade_message(&got, wire, 0) == 39);
  assert(encode_cross_trade_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broken Trade Message: 18 bytes ------------------------------------------ */

/* The Broken Trade Message is sent whenever an execution on Nasdaq PSX is broken. An execution may be broken if it is found to be “clearly erroneous” pursuant to Nasdaq’s Clearly Erroneous Policy. A trade break is final; once a trade is broken, it cannot be reinstated. */
typedef struct {
  uint8_t stock_locate[2];     /* bytes 0 to 1 */
  uint8_t tracking_number[2];  /* bytes 2 to 3 */
  uint8_t timestamp[6];        /* bytes 4 to 9 */
  uint8_t match_number[8];     /* bytes 10 to 17 */
} BrokenTradeMessage;

/* any Broken Trade Message at all: every byte one the checker chooses */
static void any_broken_trade_message(BrokenTradeMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
}

/* Broken Trade Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_message(const BrokenTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Broken Trade Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_message(BrokenTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Broken Trade Message is what was written, byte for byte */
static void equal_broken_trade_message(const BrokenTradeMessage *read, const BrokenTradeMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Broken Trade Message: written and read back, then read and written back */
static void check_broken_trade_message(void) {
  BrokenTradeMessage sent;
  BrokenTradeMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_broken_trade_message(&sent);
  assert(encode_broken_trade_message(&sent, wire, 0) == 18);
  assert(decode_broken_trade_message(&got, wire, 0) == 18);
  equal_broken_trade_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_broken_trade_message(&got, wire, 0) == 18);
  assert(encode_broken_trade_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Order Imbalance Indicator Message: 49 bytes ------------------------- */

/* NASDAQ PSX disseminates NOII data at 5-second intervals in the minutes leading up to the NASDAQ Opening Cross and NASDAQ Closing Cross */
typedef struct {
  uint8_t stock_locate[2];             /* bytes 0 to 1 */
  uint8_t tracking_number[2];          /* bytes 2 to 3 */
  uint8_t timestamp[6];                /* bytes 4 to 9 */
  uint8_t paired_shares[8];            /* bytes 10 to 17 */
  uint8_t imbalance_shares[8];         /* bytes 18 to 25 */
  uint8_t imbalance_direction;         /* byte 26 */
  uint8_t stock[8];                    /* bytes 27 to 34 */
  uint8_t far_price[4];                /* bytes 35 to 38 */
  uint8_t near_price[4];               /* bytes 39 to 42 */
  uint8_t current_reference_price[4];  /* bytes 43 to 46 */
  uint8_t cross_type;                  /* byte 47 */
  uint8_t price_variation_indicator;   /* byte 48 */
} NetOrderImbalanceIndicatorMessage;

/* any Net Order Imbalance Indicator Message at all: every byte one the checker chooses */
static void any_net_order_imbalance_indicator_message(NetOrderImbalanceIndicatorMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->paired_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->imbalance_shares[i] = arbitrary(); }
  record->imbalance_direction = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->far_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->near_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->current_reference_price[i] = arbitrary(); }
  record->cross_type = arbitrary();
  record->price_variation_indicator = arbitrary();
}

/* Net Order Imbalance Indicator Message to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_net_order_imbalance_indicator_message(const NetOrderImbalanceIndicatorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_locate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->paired_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->imbalance_shares[i]; }
  wire[at++] = record->imbalance_direction;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->far_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->near_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->current_reference_price[i]; }
  wire[at++] = record->cross_type;
  wire[at++] = record->price_variation_indicator;

  return at;
}

/* Net Order Imbalance Indicator Message off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_net_order_imbalance_indicator_message(NetOrderImbalanceIndicatorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stock_locate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->paired_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->imbalance_shares[i] = wire[at++]; }
  record->imbalance_direction = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->far_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->near_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->current_reference_price[i] = wire[at++]; }
  record->cross_type = wire[at++];
  record->price_variation_indicator = wire[at++];

  return at;
}

/* what was read of Net Order Imbalance Indicator Message is what was written, byte for byte */
static void equal_net_order_imbalance_indicator_message(const NetOrderImbalanceIndicatorMessage *read, const NetOrderImbalanceIndicatorMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stock_locate[i] == written->stock_locate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->paired_shares[i] == written->paired_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->imbalance_shares[i] == written->imbalance_shares[i]); }
  assert(read->imbalance_direction == written->imbalance_direction);
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->far_price[i] == written->far_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->near_price[i] == written->near_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->current_reference_price[i] == written->current_reference_price[i]); }
  assert(read->cross_type == written->cross_type);
  assert(read->price_variation_indicator == written->price_variation_indicator);
}

/* Net Order Imbalance Indicator Message: written and read back, then read and written back */
static void check_net_order_imbalance_indicator_message(void) {
  NetOrderImbalanceIndicatorMessage sent;
  NetOrderImbalanceIndicatorMessage got;
  uint8_t wire[49];
  uint8_t again[49];

  any_net_order_imbalance_indicator_message(&sent);
  assert(encode_net_order_imbalance_indicator_message(&sent, wire, 0) == 49);
  assert(decode_net_order_imbalance_indicator_message(&got, wire, 0) == 49);
  equal_net_order_imbalance_indicator_message(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_net_order_imbalance_indicator_message(&got, wire, 0) == 49);
  assert(encode_net_order_imbalance_indicator_message(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
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
  check_market_participant_position_message();
  check_mwcb_decline_level_message();
  check_mwcb_status_level_message();
  check_luld_auction_collar_message();
  check_operational_halt_message();
  check_add_order_no_mpid_attribution_message();
  check_add_order_with_mpid_attribution_message();
  check_order_executed_message();
  check_order_executed_with_price_message();
  check_order_cancel_message();
  check_order_delete_message();
  check_order_replace_message();
  check_trade_message_non_cross();
  check_cross_trade_message();
  check_broken_trade_message();
  check_net_order_imbalance_indicator_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
