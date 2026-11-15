// nasdaq/nsmequities/noiview/NsmEquities_NoiView_v3_0_2013.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Net Order Imbalance View
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

/* The system event message type is used to signal a market or data feed handler event. */
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

/* ---- Stock Directory Message: 31 bytes --------------------------------------- */

/* At the start of each trading day, NASDAQ disseminates stock directory messages for all active symbols. */
typedef struct {
  uint8_t stock_alphanumeric_8[8];         /* bytes 0 to 7 */
  uint8_t market_category;                 /* byte 8 */
  uint8_t financial_status_indicator;      /* byte 9 */
  uint8_t round_lot_size[6];               /* bytes 10 to 15 */
  uint8_t round_lots_only;                 /* byte 16 */
  uint8_t issue_classification;            /* byte 17 */
  uint8_t issue_sub_type[2];               /* bytes 18 to 19 */
  uint8_t authenticity;                    /* byte 20 */
  uint8_t short_sale_threshold_indicator;  /* byte 21 */
  uint8_t ipo_flag;                        /* byte 22 */
  uint8_t luld_reference_price_tier;       /* byte 23 */
  uint8_t etp_flag;                        /* byte 24 */
  uint8_t etp_leverage_factor[5];          /* bytes 25 to 29 */
  uint8_t inverse_indicator;               /* byte 30 */
} StockDirectoryMessage;

/* any Stock Directory Message at all: every byte one the checker chooses */
static void any_stock_directory_message(StockDirectoryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock_alphanumeric_8[i] = arbitrary(); }
  record->market_category = arbitrary();
  record->financial_status_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->round_lot_size[i] = arbitrary(); }
  record->round_lots_only = arbitrary();
  record->issue_classification = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->issue_sub_type[i] = arbitrary(); }
  record->authenticity = arbitrary();
  record->short_sale_threshold_indicator = arbitrary();
  record->ipo_flag = arbitrary();
  record->luld_reference_price_tier = arbitrary();
  record->etp_flag = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->etp_leverage_factor[i] = arbitrary(); }
  record->inverse_indicator = arbitrary();
}

/* Stock Directory Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_stock_directory_message(const StockDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_alphanumeric_8[i]; }
  wire[at++] = record->market_category;
  wire[at++] = record->financial_status_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->round_lot_size[i]; }
  wire[at++] = record->round_lots_only;
  wire[at++] = record->issue_classification;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->issue_sub_type[i]; }
  wire[at++] = record->authenticity;
  wire[at++] = record->short_sale_threshold_indicator;
  wire[at++] = record->ipo_flag;
  wire[at++] = record->luld_reference_price_tier;
  wire[at++] = record->etp_flag;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->etp_leverage_factor[i]; }
  wire[at++] = record->inverse_indicator;

  return at;
}

/* Stock Directory Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_stock_directory_message(StockDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock_alphanumeric_8[i] = wire[at++]; }
  record->market_category = wire[at++];
  record->financial_status_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->round_lot_size[i] = wire[at++]; }
  record->round_lots_only = wire[at++];
  record->issue_classification = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->issue_sub_type[i] = wire[at++]; }
  record->authenticity = wire[at++];
  record->short_sale_threshold_indicator = wire[at++];
  record->ipo_flag = wire[at++];
  record->luld_reference_price_tier = wire[at++];
  record->etp_flag = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->etp_leverage_factor[i] = wire[at++]; }
  record->inverse_indicator = wire[at++];

  return at;
}

/* what was read of Stock Directory Message is what was written, byte for byte */
static void equal_stock_directory_message(const StockDirectoryMessage *read, const StockDirectoryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock_alphanumeric_8[i] == written->stock_alphanumeric_8[i]); }
  assert(read->market_category == written->market_category);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->round_lot_size[i] == written->round_lot_size[i]); }
  assert(read->round_lots_only == written->round_lots_only);
  assert(read->issue_classification == written->issue_classification);
  for (size_t i = 0; i < 2; i++) { assert(read->issue_sub_type[i] == written->issue_sub_type[i]); }
  assert(read->authenticity == written->authenticity);
  assert(read->short_sale_threshold_indicator == written->short_sale_threshold_indicator);
  assert(read->ipo_flag == written->ipo_flag);
  assert(read->luld_reference_price_tier == written->luld_reference_price_tier);
  assert(read->etp_flag == written->etp_flag);
  for (size_t i = 0; i < 5; i++) { assert(read->etp_leverage_factor[i] == written->etp_leverage_factor[i]); }
  assert(read->inverse_indicator == written->inverse_indicator);
}

/* Stock Directory Message: written and read back, then read and written back */
static void check_stock_directory_message(void) {
  StockDirectoryMessage sent;
  StockDirectoryMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_stock_directory_message(&sent);
  assert(encode_stock_directory_message(&sent, wire, 0) == 31);
  assert(decode_stock_directory_message(&got, wire, 0) == 31);
  equal_stock_directory_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_directory_message(&got, wire, 0) == 31);
  assert(encode_stock_directory_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Trading Action Message: 26 bytes ---------------------------------- */

/* NASDAQ uses this administrative message to indicate the current trading status of a security to the trading community. */
typedef struct {
  uint8_t stock_alphanumeric_8[8];  /* bytes 0 to 7 */
  uint8_t current_trading_state;    /* byte 8 */
  uint8_t reason[4];                /* bytes 9 to 12 */
  uint8_t tracking_id[13];          /* bytes 13 to 25 */
} StockTradingActionMessage;

/* any Stock Trading Action Message at all: every byte one the checker chooses */
static void any_stock_trading_action_message(StockTradingActionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock_alphanumeric_8[i] = arbitrary(); }
  record->current_trading_state = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reason[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->tracking_id[i] = arbitrary(); }
}

/* Stock Trading Action Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_stock_trading_action_message(const StockTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_alphanumeric_8[i]; }
  wire[at++] = record->current_trading_state;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reason[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->tracking_id[i]; }

  return at;
}

/* Stock Trading Action Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_stock_trading_action_message(StockTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock_alphanumeric_8[i] = wire[at++]; }
  record->current_trading_state = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reason[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->tracking_id[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Trading Action Message is what was written, byte for byte */
static void equal_stock_trading_action_message(const StockTradingActionMessage *read, const StockTradingActionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock_alphanumeric_8[i] == written->stock_alphanumeric_8[i]); }
  assert(read->current_trading_state == written->current_trading_state);
  for (size_t i = 0; i < 4; i++) { assert(read->reason[i] == written->reason[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->tracking_id[i] == written->tracking_id[i]); }
}

/* Stock Trading Action Message: written and read back, then read and written back */
static void check_stock_trading_action_message(void) {
  StockTradingActionMessage sent;
  StockTradingActionMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_stock_trading_action_message(&sent);
  assert(encode_stock_trading_action_message(&sent, wire, 0) == 26);
  assert(decode_stock_trading_action_message(&got, wire, 0) == 26);
  equal_stock_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_trading_action_message(&got, wire, 0) == 26);
  assert(encode_stock_trading_action_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reg Sho Restriction Message: 9 bytes ------------------------------------ */

/* Denotes the Reg SHO Short Sale Price Test Restriction status for the issue at the time of the message dissemination. */
typedef struct {
  uint8_t stock_alpha_8[8];  /* bytes 0 to 7 */
  uint8_t reg_sho_action;    /* byte 8 */
} RegShoRestrictionMessage;

/* any Reg Sho Restriction Message at all: every byte one the checker chooses */
static void any_reg_sho_restriction_message(RegShoRestrictionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock_alpha_8[i] = arbitrary(); }
  record->reg_sho_action = arbitrary();
}

/* Reg Sho Restriction Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_reg_sho_restriction_message(const RegShoRestrictionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_alpha_8[i]; }
  wire[at++] = record->reg_sho_action;

  return at;
}

/* Reg Sho Restriction Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_reg_sho_restriction_message(RegShoRestrictionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock_alpha_8[i] = wire[at++]; }
  record->reg_sho_action = wire[at++];

  return at;
}

/* what was read of Reg Sho Restriction Message is what was written, byte for byte */
static void equal_reg_sho_restriction_message(const RegShoRestrictionMessage *read, const RegShoRestrictionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock_alpha_8[i] == written->stock_alpha_8[i]); }
  assert(read->reg_sho_action == written->reg_sho_action);
}

/* Reg Sho Restriction Message: written and read back, then read and written back */
static void check_reg_sho_restriction_message(void) {
  RegShoRestrictionMessage sent;
  RegShoRestrictionMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_reg_sho_restriction_message(&sent);
  assert(encode_reg_sho_restriction_message(&sent, wire, 0) == 9);
  assert(decode_reg_sho_restriction_message(&got, wire, 0) == 9);
  equal_reg_sho_restriction_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_reg_sho_restriction_message(&got, wire, 0) == 9);
  assert(encode_reg_sho_restriction_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Noii Message: 59 bytes -------------------------------------------------- */

/* NASDAQ disseminates NOII data in the minutes leading up to the NASDAQ Opening and Closing Crosses as well as the IPO/Halt Crosses. */
typedef struct {
  uint8_t paired_shares[9];             /* bytes 0 to 8 */
  uint8_t imbalance_shares[9];          /* bytes 9 to 17 */
  uint8_t imbalance_direction;          /* byte 18 */
  uint8_t stock_alpha_8[8];             /* bytes 19 to 26 */
  uint8_t far_price[10];                /* bytes 27 to 36 */
  uint8_t near_price[10];               /* bytes 37 to 46 */
  uint8_t current_reference_price[10];  /* bytes 47 to 56 */
  uint8_t cross_type;                   /* byte 57 */
  uint8_t price_variation_indicator;    /* byte 58 */
} NoiiMessage;

/* any Noii Message at all: every byte one the checker chooses */
static void any_noii_message(NoiiMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->paired_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->imbalance_shares[i] = arbitrary(); }
  record->imbalance_direction = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->stock_alpha_8[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->far_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->near_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->current_reference_price[i] = arbitrary(); }
  record->cross_type = arbitrary();
  record->price_variation_indicator = arbitrary();
}

/* Noii Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_noii_message(const NoiiMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->paired_shares[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->imbalance_shares[i]; }
  wire[at++] = record->imbalance_direction;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_alpha_8[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->far_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->near_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->current_reference_price[i]; }
  wire[at++] = record->cross_type;
  wire[at++] = record->price_variation_indicator;

  return at;
}

/* Noii Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_noii_message(NoiiMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->paired_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->imbalance_shares[i] = wire[at++]; }
  record->imbalance_direction = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->stock_alpha_8[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->far_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->near_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->current_reference_price[i] = wire[at++]; }
  record->cross_type = wire[at++];
  record->price_variation_indicator = wire[at++];

  return at;
}

/* what was read of Noii Message is what was written, byte for byte */
static void equal_noii_message(const NoiiMessage *read, const NoiiMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->paired_shares[i] == written->paired_shares[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->imbalance_shares[i] == written->imbalance_shares[i]); }
  assert(read->imbalance_direction == written->imbalance_direction);
  for (size_t i = 0; i < 8; i++) { assert(read->stock_alpha_8[i] == written->stock_alpha_8[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->far_price[i] == written->far_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->near_price[i] == written->near_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->current_reference_price[i] == written->current_reference_price[i]); }
  assert(read->cross_type == written->cross_type);
  assert(read->price_variation_indicator == written->price_variation_indicator);
}

/* Noii Message: written and read back, then read and written back */
static void check_noii_message(void) {
  NoiiMessage sent;
  NoiiMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_noii_message(&sent);
  assert(encode_noii_message(&sent, wire, 0) == 59);
  assert(decode_noii_message(&got, wire, 0) == 59);
  equal_noii_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_noii_message(&got, wire, 0) == 59);
  assert(encode_noii_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cross Trade Message: 53 bytes ------------------------------------------- */

/* Cross Trade message indicates that NASDAQ has completed its cross process for a specific security. */
typedef struct {
  uint8_t shares[9];         /* bytes 0 to 8 */
  uint8_t stock_alpha_8[8];  /* bytes 9 to 16 */
  uint8_t cross_price[10];   /* bytes 17 to 26 */
  uint8_t match_number[12];  /* bytes 27 to 38 */
  uint8_t cross_type;        /* byte 39 */
  uint8_t tracking_id[13];   /* bytes 40 to 52 */
} CrossTradeMessage;

/* any Cross Trade Message at all: every byte one the checker chooses */
static void any_cross_trade_message(CrossTradeMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock_alpha_8[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cross_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = arbitrary(); }
  record->cross_type = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->tracking_id[i] = arbitrary(); }
}

/* Cross Trade Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_cross_trade_message(const CrossTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_alpha_8[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cross_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->cross_type;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->tracking_id[i]; }

  return at;
}

/* Cross Trade Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_cross_trade_message(CrossTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock_alpha_8[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cross_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = wire[at++]; }
  record->cross_type = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->tracking_id[i] = wire[at++]; }

  return at;
}

/* what was read of Cross Trade Message is what was written, byte for byte */
static void equal_cross_trade_message(const CrossTradeMessage *read, const CrossTradeMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock_alpha_8[i] == written->stock_alpha_8[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cross_price[i] == written->cross_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->cross_type == written->cross_type);
  for (size_t i = 0; i < 13; i++) { assert(read->tracking_id[i] == written->tracking_id[i]); }
}

/* Cross Trade Message: written and read back, then read and written back */
static void check_cross_trade_message(void) {
  CrossTradeMessage sent;
  CrossTradeMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_cross_trade_message(&sent);
  assert(encode_cross_trade_message(&sent, wire, 0) == 53);
  assert(decode_cross_trade_message(&got, wire, 0) == 53);
  equal_cross_trade_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_cross_trade_message(&got, wire, 0) == 53);
  assert(encode_cross_trade_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ipo Quoting Period Update Message: 25 bytes ----------------------------- */

/* Denotes the IPO release time for quotation and the IPO price for the issue. */
typedef struct {
  uint8_t stock_alphanumeric_8[8];          /* bytes 0 to 7 */
  uint8_t ipo_quotation_release_time[6];    /* bytes 8 to 13 */
  uint8_t ipo_quotation_release_qualifier;  /* byte 14 */
  uint8_t ipo_price[10];                    /* bytes 15 to 24 */
} IpoQuotingPeriodUpdateMessage;

/* any Ipo Quoting Period Update Message at all: every byte one the checker chooses */
static void any_ipo_quoting_period_update_message(IpoQuotingPeriodUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock_alphanumeric_8[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->ipo_quotation_release_time[i] = arbitrary(); }
  record->ipo_quotation_release_qualifier = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->ipo_price[i] = arbitrary(); }
}

/* Ipo Quoting Period Update Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_ipo_quoting_period_update_message(const IpoQuotingPeriodUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_alphanumeric_8[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->ipo_quotation_release_time[i]; }
  wire[at++] = record->ipo_quotation_release_qualifier;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->ipo_price[i]; }

  return at;
}

/* Ipo Quoting Period Update Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_ipo_quoting_period_update_message(IpoQuotingPeriodUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock_alphanumeric_8[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->ipo_quotation_release_time[i] = wire[at++]; }
  record->ipo_quotation_release_qualifier = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->ipo_price[i] = wire[at++]; }

  return at;
}

/* what was read of Ipo Quoting Period Update Message is what was written, byte for byte */
static void equal_ipo_quoting_period_update_message(const IpoQuotingPeriodUpdateMessage *read, const IpoQuotingPeriodUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock_alphanumeric_8[i] == written->stock_alphanumeric_8[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->ipo_quotation_release_time[i] == written->ipo_quotation_release_time[i]); }
  assert(read->ipo_quotation_release_qualifier == written->ipo_quotation_release_qualifier);
  for (size_t i = 0; i < 10; i++) { assert(read->ipo_price[i] == written->ipo_price[i]); }
}

/* Ipo Quoting Period Update Message: written and read back, then read and written back */
static void check_ipo_quoting_period_update_message(void) {
  IpoQuotingPeriodUpdateMessage sent;
  IpoQuotingPeriodUpdateMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_ipo_quoting_period_update_message(&sent);
  assert(encode_ipo_quoting_period_update_message(&sent, wire, 0) == 25);
  assert(decode_ipo_quoting_period_update_message(&got, wire, 0) == 25);
  equal_ipo_quoting_period_update_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_ipo_quoting_period_update_message(&got, wire, 0) == 25);
  assert(encode_ipo_quoting_period_update_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_system_event_message();
  check_stock_directory_message();
  check_stock_trading_action_message();
  check_reg_sho_restriction_message();
  check_noii_message();
  check_cross_trade_message();
  check_ipo_quoting_period_update_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
