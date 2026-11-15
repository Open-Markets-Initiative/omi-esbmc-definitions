// nasdaq/nsmequities/qbbo/NsmEquities_Qbbo_v2_1.c
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

/* The System Event message is used to signal key market or data feed control events. */
typedef struct {
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t time_stamp[6];       /* bytes 2 to 7 */
  uint8_t event_code;          /* byte 8 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_stamp[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
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

/* ---- Stock Directory Message: 36 bytes --------------------------------------- */

/* At the start of each trading day, Nasdaq disseminates stock directory messages for all active symbols in its market center system. */
typedef struct {
  uint8_t tracking_number[2];              /* bytes 0 to 1 */
  uint8_t time_stamp[6];                   /* bytes 2 to 7 */
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
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = arbitrary(); }
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
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_stamp[i]; }
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
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = wire[at++]; }
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
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
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

/* ---- Stock Trading Action Message: 22 bytes ---------------------------------- */

/* Nasdaq uses this administrative message to indicate the current trading status of a security to the trading community. */
typedef struct {
  uint8_t tracking_number[2];     /* bytes 0 to 1 */
  uint8_t time_stamp[6];          /* bytes 2 to 7 */
  uint8_t stock[8];               /* bytes 8 to 15 */
  uint8_t security_class;         /* byte 16 */
  uint8_t current_trading_state;  /* byte 17 */
  uint8_t reason[4];              /* bytes 18 to 21 */
} StockTradingActionMessage;

/* any Stock Trading Action Message at all: every byte one the checker chooses */
static void any_stock_trading_action_message(StockTradingActionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->security_class = arbitrary();
  record->current_trading_state = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reason[i] = arbitrary(); }
}

/* Stock Trading Action Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_stock_trading_action_message(const StockTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_stamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->security_class;
  wire[at++] = record->current_trading_state;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Stock Trading Action Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_stock_trading_action_message(StockTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->security_class = wire[at++];
  record->current_trading_state = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Trading Action Message is what was written, byte for byte */
static void equal_stock_trading_action_message(const StockTradingActionMessage *read, const StockTradingActionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->security_class == written->security_class);
  assert(read->current_trading_state == written->current_trading_state);
  for (size_t i = 0; i < 4; i++) { assert(read->reason[i] == written->reason[i]); }
}

/* Stock Trading Action Message: written and read back, then read and written back */
static void check_stock_trading_action_message(void) {
  StockTradingActionMessage sent;
  StockTradingActionMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_stock_trading_action_message(&sent);
  assert(encode_stock_trading_action_message(&sent, wire, 0) == 22);
  assert(decode_stock_trading_action_message(&got, wire, 0) == 22);
  equal_stock_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_trading_action_message(&got, wire, 0) == 22);
  assert(encode_stock_trading_action_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reg Sho Restriction Message: 17 bytes ----------------------------------- */

/* Nasdaq introduced the Reg SHO Short Sale Price Test Restricted Indicator message format. */
typedef struct {
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t time_stamp[6];       /* bytes 2 to 7 */
  uint8_t stock[8];            /* bytes 8 to 15 */
  uint8_t reg_sho_action;      /* byte 16 */
} RegShoRestrictionMessage;

/* any Reg Sho Restriction Message at all: every byte one the checker chooses */
static void any_reg_sho_restriction_message(RegShoRestrictionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->reg_sho_action = arbitrary();
}

/* Reg Sho Restriction Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_reg_sho_restriction_message(const RegShoRestrictionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_stamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->reg_sho_action;

  return at;
}

/* Reg Sho Restriction Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_reg_sho_restriction_message(RegShoRestrictionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->reg_sho_action = wire[at++];

  return at;
}

/* what was read of Reg Sho Restriction Message is what was written, byte for byte */
static void equal_reg_sho_restriction_message(const RegShoRestrictionMessage *read, const RegShoRestrictionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
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

/* ---- Mwcb Decline Level Message: 32 bytes ------------------------------------ */

/* Informs data recipients what the daily MWCB breach points are set to for the current trading day. */
typedef struct {
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t time_stamp[6];       /* bytes 2 to 7 */
  uint8_t level_1[8];          /* bytes 8 to 15 */
  uint8_t level_2[8];          /* bytes 16 to 23 */
  uint8_t level_3[8];          /* bytes 24 to 31 */
} MwcbDeclineLevelMessage;

/* any Mwcb Decline Level Message at all: every byte one the checker chooses */
static void any_mwcb_decline_level_message(MwcbDeclineLevelMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->level_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->level_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->level_3[i] = arbitrary(); }
}

/* Mwcb Decline Level Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_mwcb_decline_level_message(const MwcbDeclineLevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_stamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->level_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->level_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->level_3[i]; }

  return at;
}

/* Mwcb Decline Level Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_mwcb_decline_level_message(MwcbDeclineLevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->level_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->level_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->level_3[i] = wire[at++]; }

  return at;
}

/* what was read of Mwcb Decline Level Message is what was written, byte for byte */
static void equal_mwcb_decline_level_message(const MwcbDeclineLevelMessage *read, const MwcbDeclineLevelMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
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

/* ---- Mwcb Breach Message: 9 bytes -------------------------------------------- */

/* Informs data recipients when a MWCB has breached one of the established levels */
typedef struct {
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t time_stamp[6];       /* bytes 2 to 7 */
  uint8_t breached_level;      /* byte 8 */
} MwcbBreachMessage;

/* any Mwcb Breach Message at all: every byte one the checker chooses */
static void any_mwcb_breach_message(MwcbBreachMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = arbitrary(); }
  record->breached_level = arbitrary();
}

/* Mwcb Breach Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_mwcb_breach_message(const MwcbBreachMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_stamp[i]; }
  wire[at++] = record->breached_level;

  return at;
}

/* Mwcb Breach Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_mwcb_breach_message(MwcbBreachMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = wire[at++]; }
  record->breached_level = wire[at++];

  return at;
}

/* what was read of Mwcb Breach Message is what was written, byte for byte */
static void equal_mwcb_breach_message(const MwcbBreachMessage *read, const MwcbBreachMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  assert(read->breached_level == written->breached_level);
}

/* Mwcb Breach Message: written and read back, then read and written back */
static void check_mwcb_breach_message(void) {
  MwcbBreachMessage sent;
  MwcbBreachMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_mwcb_breach_message(&sent);
  assert(encode_mwcb_breach_message(&sent, wire, 0) == 9);
  assert(decode_mwcb_breach_message(&got, wire, 0) == 9);
  equal_mwcb_breach_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_mwcb_breach_message(&got, wire, 0) == 9);
  assert(encode_mwcb_breach_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Operational Halt Message: 18 bytes -------------------------------------- */

/* The Exchange uses this message to indicate the current Operational Status of a security to the trading community. */
typedef struct {
  uint8_t tracking_number[2];       /* bytes 0 to 1 */
  uint8_t time_stamp[6];            /* bytes 2 to 7 */
  uint8_t stock[8];                 /* bytes 8 to 15 */
  uint8_t market_code;              /* byte 16 */
  uint8_t operational_halt_action;  /* byte 17 */
} OperationalHaltMessage;

/* any Operational Halt Message at all: every byte one the checker chooses */
static void any_operational_halt_message(OperationalHaltMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->market_code = arbitrary();
  record->operational_halt_action = arbitrary();
}

/* Operational Halt Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_operational_halt_message(const OperationalHaltMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_stamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->market_code;
  wire[at++] = record->operational_halt_action;

  return at;
}

/* Operational Halt Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_operational_halt_message(OperationalHaltMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->market_code = wire[at++];
  record->operational_halt_action = wire[at++];

  return at;
}

/* what was read of Operational Halt Message is what was written, byte for byte */
static void equal_operational_halt_message(const OperationalHaltMessage *read, const OperationalHaltMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
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

/* ---- Bbo Quotation Message: 33 bytes ----------------------------------------- */

/* BBO products will broadcast a real-time update every time that the exchange's best bid and offer quote is updated during the trading day. */
typedef struct {
  uint8_t tracking_number[2];   /* bytes 0 to 1 */
  uint8_t time_stamp[6];        /* bytes 2 to 7 */
  uint8_t stock[8];             /* bytes 8 to 15 */
  uint8_t security_class;       /* byte 16 */
  uint8_t best_bid_price[4];    /* bytes 17 to 20 */
  uint8_t best_bid_size[4];     /* bytes 21 to 24 */
  uint8_t best_offer_price[4];  /* bytes 25 to 28 */
  uint8_t best_offer_size[4];   /* bytes 29 to 32 */
} BboQuotationMessage;

/* any Bbo Quotation Message at all: every byte one the checker chooses */
static void any_bbo_quotation_message(BboQuotationMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->best_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_offer_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_offer_size[i] = arbitrary(); }
}

/* Bbo Quotation Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_bbo_quotation_message(const BboQuotationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_stamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_bid_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_offer_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_offer_size[i]; }

  return at;
}

/* Bbo Quotation Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_bbo_quotation_message(BboQuotationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->best_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_offer_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_offer_size[i] = wire[at++]; }

  return at;
}

/* what was read of Bbo Quotation Message is what was written, byte for byte */
static void equal_bbo_quotation_message(const BboQuotationMessage *read, const BboQuotationMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 4; i++) { assert(read->best_bid_price[i] == written->best_bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_bid_size[i] == written->best_bid_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_offer_price[i] == written->best_offer_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_offer_size[i] == written->best_offer_size[i]); }
}

/* Bbo Quotation Message: written and read back, then read and written back */
static void check_bbo_quotation_message(void) {
  BboQuotationMessage sent;
  BboQuotationMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_bbo_quotation_message(&sent);
  assert(encode_bbo_quotation_message(&sent, wire, 0) == 33);
  assert(decode_bbo_quotation_message(&got, wire, 0) == 33);
  equal_bbo_quotation_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_bbo_quotation_message(&got, wire, 0) == 33);
  assert(encode_bbo_quotation_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Improvement Message: 17 bytes ------------------------------------- */

/* Indicates a retail interest indication of the Bid, Ask or both the Bid and Ask for Nasdaq-listed securities. */
typedef struct {
  uint8_t tracking[2];    /* bytes 0 to 1 */
  uint8_t time_stamp[6];  /* bytes 2 to 7 */
  uint8_t stock[8];       /* bytes 8 to 15 */
  uint8_t interest_flag;  /* byte 16 */
} PriceImprovementMessage;

/* any Price Improvement Message at all: every byte one the checker chooses */
static void any_price_improvement_message(PriceImprovementMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->interest_flag = arbitrary();
}

/* Price Improvement Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_price_improvement_message(const PriceImprovementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_stamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->interest_flag;

  return at;
}

/* Price Improvement Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_price_improvement_message(PriceImprovementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->interest_flag = wire[at++];

  return at;
}

/* what was read of Price Improvement Message is what was written, byte for byte */
static void equal_price_improvement_message(const PriceImprovementMessage *read, const PriceImprovementMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking[i] == written->tracking[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->interest_flag == written->interest_flag);
}

/* Price Improvement Message: written and read back, then read and written back */
static void check_price_improvement_message(void) {
  PriceImprovementMessage sent;
  PriceImprovementMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_price_improvement_message(&sent);
  assert(encode_price_improvement_message(&sent, wire, 0) == 17);
  assert(decode_price_improvement_message(&got, wire, 0) == 17);
  equal_price_improvement_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_price_improvement_message(&got, wire, 0) == 17);
  assert(encode_price_improvement_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ipo Quoting Period Update Message: 25 bytes ----------------------------- */

/* Indicates the anticipated IPO quotation release time of a security. */
typedef struct {
  uint8_t tracking[2];                      /* bytes 0 to 1 */
  uint8_t time_stamp[6];                    /* bytes 2 to 7 */
  uint8_t stock[8];                         /* bytes 8 to 15 */
  uint8_t ipo_quotation_release_time[4];    /* bytes 16 to 19 */
  uint8_t ipo_quotation_release_qualifier;  /* byte 20 */
  uint8_t ipo_price[4];                     /* bytes 21 to 24 */
} IpoQuotingPeriodUpdateMessage;

/* any Ipo Quoting Period Update Message at all: every byte one the checker chooses */
static void any_ipo_quoting_period_update_message(IpoQuotingPeriodUpdateMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ipo_quotation_release_time[i] = arbitrary(); }
  record->ipo_quotation_release_qualifier = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->ipo_price[i] = arbitrary(); }
}

/* Ipo Quoting Period Update Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_ipo_quoting_period_update_message(const IpoQuotingPeriodUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_stamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ipo_quotation_release_time[i]; }
  wire[at++] = record->ipo_quotation_release_qualifier;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ipo_price[i]; }

  return at;
}

/* Ipo Quoting Period Update Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_ipo_quoting_period_update_message(IpoQuotingPeriodUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ipo_quotation_release_time[i] = wire[at++]; }
  record->ipo_quotation_release_qualifier = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->ipo_price[i] = wire[at++]; }

  return at;
}

/* what was read of Ipo Quoting Period Update Message is what was written, byte for byte */
static void equal_ipo_quoting_period_update_message(const IpoQuotingPeriodUpdateMessage *read, const IpoQuotingPeriodUpdateMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking[i] == written->tracking[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ipo_quotation_release_time[i] == written->ipo_quotation_release_time[i]); }
  assert(read->ipo_quotation_release_qualifier == written->ipo_quotation_release_qualifier);
  for (size_t i = 0; i < 4; i++) { assert(read->ipo_price[i] == written->ipo_price[i]); }
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
  check_mwcb_decline_level_message();
  check_mwcb_breach_message();
  check_operational_halt_message();
  check_bbo_quotation_message();
  check_price_improvement_message();
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
