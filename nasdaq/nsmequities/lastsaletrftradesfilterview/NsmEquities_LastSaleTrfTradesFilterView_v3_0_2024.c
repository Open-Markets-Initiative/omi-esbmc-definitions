// nasdaq/nsmequities/lastsaletrftradesfilterview/NsmEquities_LastSaleTrfTradesFilterView_v3_0_2024.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Last Sale Trf Trades FilterView
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

/* ---- Message Header: 11 bytes ------------------------------------------------ */

typedef struct {
  uint8_t message_length[2];   /* bytes 0 to 1 */
  uint8_t tracking_number[2];  /* bytes 2 to 3 */
  uint8_t timestamp[6];        /* bytes 4 to 9 */
  uint8_t message_type;        /* byte 10 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
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

/* ---- System Event Message: 1 byte -------------------------------------------- */

/* System Event Messages is used to signal key market or data feed control events. */
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

/* ---- Sale Condition Modifier: 4 bytes ---------------------------------------- */

/* Sale condition modifier consists of four levels */
typedef struct {
  uint8_t settlement_type;              /* byte 0 */
  uint8_t trade_through_exemption;      /* byte 1 */
  uint8_t extended_hours_or_sold_code;  /* byte 2 */
  uint8_t special_sale_condition;       /* byte 3 */
} SaleConditionModifier;

/* any Sale Condition Modifier at all: every byte one the checker chooses */
static void any_sale_condition_modifier(SaleConditionModifier *record) {
  record->settlement_type = arbitrary();
  record->trade_through_exemption = arbitrary();
  record->extended_hours_or_sold_code = arbitrary();
  record->special_sale_condition = arbitrary();
}

/* Sale Condition Modifier to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_sale_condition_modifier(const SaleConditionModifier *record, uint8_t *wire, size_t at) {
  wire[at++] = record->settlement_type;
  wire[at++] = record->trade_through_exemption;
  wire[at++] = record->extended_hours_or_sold_code;
  wire[at++] = record->special_sale_condition;

  return at;
}

/* Sale Condition Modifier off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_sale_condition_modifier(SaleConditionModifier *record, const uint8_t *wire, size_t at) {
  record->settlement_type = wire[at++];
  record->trade_through_exemption = wire[at++];
  record->extended_hours_or_sold_code = wire[at++];
  record->special_sale_condition = wire[at++];

  return at;
}

/* what was read of Sale Condition Modifier is what was written, byte for byte */
static void equal_sale_condition_modifier(const SaleConditionModifier *read, const SaleConditionModifier *written) {
  assert(read->settlement_type == written->settlement_type);
  assert(read->trade_through_exemption == written->trade_through_exemption);
  assert(read->extended_hours_or_sold_code == written->extended_hours_or_sold_code);
  assert(read->special_sale_condition == written->special_sale_condition);
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

/* ---- Trade Report Message: 32 bytes ------------------------------------------ */

/* The following message is used to relay Nasdaq execution system and TRF trade transactions that are reported for the current business day. Please note that Nasdaq only reports one-side of a trade execution on the Nasdaq Last Sale (NLS) feed and other data feed products. */
typedef struct {
  uint8_t market_center_identifier;               /* byte 0 */
  uint8_t issue_symbol[8];                        /* bytes 1 to 8 */
  uint8_t security_class;                         /* byte 9 */
  uint8_t trade_control_number[10];               /* bytes 10 to 19 */
  uint8_t trade_price[4];                         /* bytes 20 to 23 */
  uint8_t trade_size[4];                          /* bytes 24 to 27 */
  SaleConditionModifier sale_condition_modifier;  /* bytes 28 to 31 */
} TradeReportMessage;

/* any Trade Report Message at all: every byte one the checker chooses */
static void any_trade_report_message(TradeReportMessage *record) {
  record->market_center_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = arbitrary(); }
  any_sale_condition_modifier(&record->sale_condition_modifier);
}

/* Trade Report Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_trade_report_message(const TradeReportMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_control_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_size[i]; }
  at = encode_sale_condition_modifier(&record->sale_condition_modifier, wire, at);

  return at;
}

/* Trade Report Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_trade_report_message(TradeReportMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = wire[at++]; }
  at = decode_sale_condition_modifier(&record->sale_condition_modifier, wire, at);

  return at;
}

/* what was read of Trade Report Message is what was written, byte for byte */
static void equal_trade_report_message(const TradeReportMessage *read, const TradeReportMessage *written) {
  assert(read->market_center_identifier == written->market_center_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->trade_control_number[i] == written->trade_control_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_size[i] == written->trade_size[i]); }
  equal_sale_condition_modifier(&read->sale_condition_modifier, &written->sale_condition_modifier);
}

/* Trade Report Message: written and read back, then read and written back */
static void check_trade_report_message(void) {
  TradeReportMessage sent;
  TradeReportMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_trade_report_message(&sent);
  assert(encode_trade_report_message(&sent, wire, 0) == 32);
  assert(decode_trade_report_message(&got, wire, 0) == 32);
  equal_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_message(&got, wire, 0) == 32);
  assert(encode_trade_report_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Form Trade Report Message: 36 bytes -------------------------------- */

/* The following message is used to relay Nasdaq execution system and TRF trade transactions that are reported for the current business day, for long form trades exceeding the upper limit of a 4-byte price. */
typedef struct {
  uint8_t originating_market_center_identifier;   /* byte 0 */
  uint8_t issue_symbol[8];                        /* bytes 1 to 8 */
  uint8_t security_class;                         /* byte 9 */
  uint8_t trade_control_number[10];               /* bytes 10 to 19 */
  uint8_t trade_price_long[8];                    /* bytes 20 to 27 */
  uint8_t trade_size[4];                          /* bytes 28 to 31 */
  SaleConditionModifier sale_condition_modifier;  /* bytes 32 to 35 */
} LongFormTradeReportMessage;

/* any Long Form Trade Report Message at all: every byte one the checker chooses */
static void any_long_form_trade_report_message(LongFormTradeReportMessage *record) {
  record->originating_market_center_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = arbitrary(); }
  any_sale_condition_modifier(&record->sale_condition_modifier);
}

/* Long Form Trade Report Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_long_form_trade_report_message(const LongFormTradeReportMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->originating_market_center_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_control_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_size[i]; }
  at = encode_sale_condition_modifier(&record->sale_condition_modifier, wire, at);

  return at;
}

/* Long Form Trade Report Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_long_form_trade_report_message(LongFormTradeReportMessage *record, const uint8_t *wire, size_t at) {
  record->originating_market_center_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = wire[at++]; }
  at = decode_sale_condition_modifier(&record->sale_condition_modifier, wire, at);

  return at;
}

/* what was read of Long Form Trade Report Message is what was written, byte for byte */
static void equal_long_form_trade_report_message(const LongFormTradeReportMessage *read, const LongFormTradeReportMessage *written) {
  assert(read->originating_market_center_identifier == written->originating_market_center_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->trade_control_number[i] == written->trade_control_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price_long[i] == written->trade_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_size[i] == written->trade_size[i]); }
  equal_sale_condition_modifier(&read->sale_condition_modifier, &written->sale_condition_modifier);
}

/* Long Form Trade Report Message: written and read back, then read and written back */
static void check_long_form_trade_report_message(void) {
  LongFormTradeReportMessage sent;
  LongFormTradeReportMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_long_form_trade_report_message(&sent);
  assert(encode_long_form_trade_report_message(&sent, wire, 0) == 36);
  assert(decode_long_form_trade_report_message(&got, wire, 0) == 36);
  equal_long_form_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_long_form_trade_report_message(&got, wire, 0) == 36);
  assert(encode_long_form_trade_report_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Next Shares Trade Report Message: 36 bytes ------------------------------ */

/* The following message is used to relay Nasdaq execution system and TRF trade transactions for Exchange Traded Managed Funds (NextShares) that are reported for the current business day. */
typedef struct {
  uint8_t market_center_identifier;               /* byte 0 */
  uint8_t next_shares_symbol[8];                  /* bytes 1 to 8 */
  uint8_t security_class;                         /* byte 9 */
  uint8_t trade_control_number[10];               /* bytes 10 to 19 */
  uint8_t proxy_price[4];                         /* bytes 20 to 23 */
  uint8_t trade_size[4];                          /* bytes 24 to 27 */
  uint8_t nav_premium_discount_amount[4];         /* bytes 28 to 31 */
  SaleConditionModifier sale_condition_modifier;  /* bytes 32 to 35 */
} NextSharesTradeReportMessage;

/* any Next Shares Trade Report Message at all: every byte one the checker chooses */
static void any_next_shares_trade_report_message(NextSharesTradeReportMessage *record) {
  record->market_center_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->next_shares_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->proxy_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nav_premium_discount_amount[i] = arbitrary(); }
  any_sale_condition_modifier(&record->sale_condition_modifier);
}

/* Next Shares Trade Report Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_next_shares_trade_report_message(const NextSharesTradeReportMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_shares_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_control_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->proxy_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nav_premium_discount_amount[i]; }
  at = encode_sale_condition_modifier(&record->sale_condition_modifier, wire, at);

  return at;
}

/* Next Shares Trade Report Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_next_shares_trade_report_message(NextSharesTradeReportMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->next_shares_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->proxy_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nav_premium_discount_amount[i] = wire[at++]; }
  at = decode_sale_condition_modifier(&record->sale_condition_modifier, wire, at);

  return at;
}

/* what was read of Next Shares Trade Report Message is what was written, byte for byte */
static void equal_next_shares_trade_report_message(const NextSharesTradeReportMessage *read, const NextSharesTradeReportMessage *written) {
  assert(read->market_center_identifier == written->market_center_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->next_shares_symbol[i] == written->next_shares_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->trade_control_number[i] == written->trade_control_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->proxy_price[i] == written->proxy_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_size[i] == written->trade_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nav_premium_discount_amount[i] == written->nav_premium_discount_amount[i]); }
  equal_sale_condition_modifier(&read->sale_condition_modifier, &written->sale_condition_modifier);
}

/* Next Shares Trade Report Message: written and read back, then read and written back */
static void check_next_shares_trade_report_message(void) {
  NextSharesTradeReportMessage sent;
  NextSharesTradeReportMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_next_shares_trade_report_message(&sent);
  assert(encode_next_shares_trade_report_message(&sent, wire, 0) == 36);
  assert(decode_next_shares_trade_report_message(&got, wire, 0) == 36);
  equal_next_shares_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_next_shares_trade_report_message(&got, wire, 0) == 36);
  assert(encode_next_shares_trade_report_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Original Sale Condition Modifier: 4 bytes ------------------------------- */

/* The sale condition modifiers as reported on the original trade transaction */
typedef struct {
  uint8_t original_settlement_type;              /* byte 0 */
  uint8_t original_trade_through_exemption;      /* byte 1 */
  uint8_t original_extended_hours_or_sold_code;  /* byte 2 */
  uint8_t original_special_sale_condition;       /* byte 3 */
} OriginalSaleConditionModifier;

/* any Original Sale Condition Modifier at all: every byte one the checker chooses */
static void any_original_sale_condition_modifier(OriginalSaleConditionModifier *record) {
  record->original_settlement_type = arbitrary();
  record->original_trade_through_exemption = arbitrary();
  record->original_extended_hours_or_sold_code = arbitrary();
  record->original_special_sale_condition = arbitrary();
}

/* Original Sale Condition Modifier to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_original_sale_condition_modifier(const OriginalSaleConditionModifier *record, uint8_t *wire, size_t at) {
  wire[at++] = record->original_settlement_type;
  wire[at++] = record->original_trade_through_exemption;
  wire[at++] = record->original_extended_hours_or_sold_code;
  wire[at++] = record->original_special_sale_condition;

  return at;
}

/* Original Sale Condition Modifier off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_original_sale_condition_modifier(OriginalSaleConditionModifier *record, const uint8_t *wire, size_t at) {
  record->original_settlement_type = wire[at++];
  record->original_trade_through_exemption = wire[at++];
  record->original_extended_hours_or_sold_code = wire[at++];
  record->original_special_sale_condition = wire[at++];

  return at;
}

/* what was read of Original Sale Condition Modifier is what was written, byte for byte */
static void equal_original_sale_condition_modifier(const OriginalSaleConditionModifier *read, const OriginalSaleConditionModifier *written) {
  assert(read->original_settlement_type == written->original_settlement_type);
  assert(read->original_trade_through_exemption == written->original_trade_through_exemption);
  assert(read->original_extended_hours_or_sold_code == written->original_extended_hours_or_sold_code);
  assert(read->original_special_sale_condition == written->original_special_sale_condition);
}

/* Original Sale Condition Modifier: written and read back, then read and written back */
static void check_original_sale_condition_modifier(void) {
  OriginalSaleConditionModifier sent;
  OriginalSaleConditionModifier got;
  uint8_t wire[4];
  uint8_t again[4];

  any_original_sale_condition_modifier(&sent);
  assert(encode_original_sale_condition_modifier(&sent, wire, 0) == 4);
  assert(decode_original_sale_condition_modifier(&got, wire, 0) == 4);
  equal_original_sale_condition_modifier(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_original_sale_condition_modifier(&got, wire, 0) == 4);
  assert(encode_original_sale_condition_modifier(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Error Message: 32 bytes ------------------------------------ */

/* The following message is used in the event that a Nasdaq or TRF trade transaction is cancelled on the same business day that it is reported. */
typedef struct {
  uint8_t market_center_identifier;                                /* byte 0 */
  uint8_t issue_symbol[8];                                         /* bytes 1 to 8 */
  uint8_t security_class;                                          /* byte 9 */
  uint8_t original_trade_control_number[10];                       /* bytes 10 to 19 */
  uint8_t original_trade_price[4];                                 /* bytes 20 to 23 */
  uint8_t original_trade_size[4];                                  /* bytes 24 to 27 */
  OriginalSaleConditionModifier original_sale_condition_modifier;  /* bytes 28 to 31 */
} TradeCancelErrorMessage;

/* any Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_trade_cancel_error_message(TradeCancelErrorMessage *record) {
  record->market_center_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = arbitrary(); }
  any_original_sale_condition_modifier(&record->original_sale_condition_modifier);
}

/* Trade Cancel Error Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_error_message(const TradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->original_trade_control_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_size[i]; }
  at = encode_original_sale_condition_modifier(&record->original_sale_condition_modifier, wire, at);

  return at;
}

/* Trade Cancel Error Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_error_message(TradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = wire[at++]; }
  at = decode_original_sale_condition_modifier(&record->original_sale_condition_modifier, wire, at);

  return at;
}

/* what was read of Trade Cancel Error Message is what was written, byte for byte */
static void equal_trade_cancel_error_message(const TradeCancelErrorMessage *read, const TradeCancelErrorMessage *written) {
  assert(read->market_center_identifier == written->market_center_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->original_trade_control_number[i] == written->original_trade_control_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_size[i] == written->original_trade_size[i]); }
  equal_original_sale_condition_modifier(&read->original_sale_condition_modifier, &written->original_sale_condition_modifier);
}

/* Trade Cancel Error Message: written and read back, then read and written back */
static void check_trade_cancel_error_message(void) {
  TradeCancelErrorMessage sent;
  TradeCancelErrorMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_trade_cancel_error_message(&sent);
  assert(encode_trade_cancel_error_message(&sent, wire, 0) == 32);
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 32);
  equal_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 32);
  assert(encode_trade_cancel_error_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Form Trade Cancel Error Message: 36 bytes -------------------------- */

/* The following message is used in the event that a Nasdaq trade transaction, exceeding the upper limit of a 4-byte price, is cancelled on the same business day that it is reported. */
typedef struct {
  uint8_t originating_market_center_identifier;                    /* byte 0 */
  uint8_t issue_symbol[8];                                         /* bytes 1 to 8 */
  uint8_t security_class;                                          /* byte 9 */
  uint8_t original_trade_control_number[10];                       /* bytes 10 to 19 */
  uint8_t original_trade_price_long[8];                            /* bytes 20 to 27 */
  uint8_t original_trade_size[4];                                  /* bytes 28 to 31 */
  OriginalSaleConditionModifier original_sale_condition_modifier;  /* bytes 32 to 35 */
} LongFormTradeCancelErrorMessage;

/* any Long Form Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_long_form_trade_cancel_error_message(LongFormTradeCancelErrorMessage *record) {
  record->originating_market_center_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = arbitrary(); }
  any_original_sale_condition_modifier(&record->original_sale_condition_modifier);
}

/* Long Form Trade Cancel Error Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_long_form_trade_cancel_error_message(const LongFormTradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->originating_market_center_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->original_trade_control_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_trade_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_size[i]; }
  at = encode_original_sale_condition_modifier(&record->original_sale_condition_modifier, wire, at);

  return at;
}

/* Long Form Trade Cancel Error Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_long_form_trade_cancel_error_message(LongFormTradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  record->originating_market_center_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = wire[at++]; }
  at = decode_original_sale_condition_modifier(&record->original_sale_condition_modifier, wire, at);

  return at;
}

/* what was read of Long Form Trade Cancel Error Message is what was written, byte for byte */
static void equal_long_form_trade_cancel_error_message(const LongFormTradeCancelErrorMessage *read, const LongFormTradeCancelErrorMessage *written) {
  assert(read->originating_market_center_identifier == written->originating_market_center_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->original_trade_control_number[i] == written->original_trade_control_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_trade_price_long[i] == written->original_trade_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_size[i] == written->original_trade_size[i]); }
  equal_original_sale_condition_modifier(&read->original_sale_condition_modifier, &written->original_sale_condition_modifier);
}

/* Long Form Trade Cancel Error Message: written and read back, then read and written back */
static void check_long_form_trade_cancel_error_message(void) {
  LongFormTradeCancelErrorMessage sent;
  LongFormTradeCancelErrorMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_long_form_trade_cancel_error_message(&sent);
  assert(encode_long_form_trade_cancel_error_message(&sent, wire, 0) == 36);
  assert(decode_long_form_trade_cancel_error_message(&got, wire, 0) == 36);
  equal_long_form_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_long_form_trade_cancel_error_message(&got, wire, 0) == 36);
  assert(encode_long_form_trade_cancel_error_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Next Shares Trade Cancel Error Message: 36 bytes ------------------------ */

/* The following message is used in the event that a Nasdaq or TRF trade transaction for an NextShares is cancelled on the same business day that it is reported. */
typedef struct {
  uint8_t market_center_identifier;                                /* byte 0 */
  uint8_t issue_symbol[8];                                         /* bytes 1 to 8 */
  uint8_t security_class;                                          /* byte 9 */
  uint8_t original_trade_control_number[10];                       /* bytes 10 to 19 */
  uint8_t original_trade_price[4];                                 /* bytes 20 to 23 */
  uint8_t original_nav_premium_discount_amount[4];                 /* bytes 24 to 27 */
  uint8_t original_trade_size[4];                                  /* bytes 28 to 31 */
  OriginalSaleConditionModifier original_sale_condition_modifier;  /* bytes 32 to 35 */
} NextSharesTradeCancelErrorMessage;

/* any Next Shares Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_next_shares_trade_cancel_error_message(NextSharesTradeCancelErrorMessage *record) {
  record->market_center_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_nav_premium_discount_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = arbitrary(); }
  any_original_sale_condition_modifier(&record->original_sale_condition_modifier);
}

/* Next Shares Trade Cancel Error Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_next_shares_trade_cancel_error_message(const NextSharesTradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->original_trade_control_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_nav_premium_discount_amount[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_size[i]; }
  at = encode_original_sale_condition_modifier(&record->original_sale_condition_modifier, wire, at);

  return at;
}

/* Next Shares Trade Cancel Error Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_next_shares_trade_cancel_error_message(NextSharesTradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_nav_premium_discount_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = wire[at++]; }
  at = decode_original_sale_condition_modifier(&record->original_sale_condition_modifier, wire, at);

  return at;
}

/* what was read of Next Shares Trade Cancel Error Message is what was written, byte for byte */
static void equal_next_shares_trade_cancel_error_message(const NextSharesTradeCancelErrorMessage *read, const NextSharesTradeCancelErrorMessage *written) {
  assert(read->market_center_identifier == written->market_center_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->original_trade_control_number[i] == written->original_trade_control_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_nav_premium_discount_amount[i] == written->original_nav_premium_discount_amount[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_size[i] == written->original_trade_size[i]); }
  equal_original_sale_condition_modifier(&read->original_sale_condition_modifier, &written->original_sale_condition_modifier);
}

/* Next Shares Trade Cancel Error Message: written and read back, then read and written back */
static void check_next_shares_trade_cancel_error_message(void) {
  NextSharesTradeCancelErrorMessage sent;
  NextSharesTradeCancelErrorMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_next_shares_trade_cancel_error_message(&sent);
  assert(encode_next_shares_trade_cancel_error_message(&sent, wire, 0) == 36);
  assert(decode_next_shares_trade_cancel_error_message(&got, wire, 0) == 36);
  equal_next_shares_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_next_shares_trade_cancel_error_message(&got, wire, 0) == 36);
  assert(encode_next_shares_trade_cancel_error_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Corrected Sale Condition Modifier: 4 bytes ------------------------------ */

/* The sale condition modifiers associated with the corrected trade transaction */
typedef struct {
  uint8_t corrected_settlement_type;              /* byte 0 */
  uint8_t corrected_trade_through_exemption;      /* byte 1 */
  uint8_t corrected_extended_hours_or_sold_code;  /* byte 2 */
  uint8_t corrected_special_sale_condition;       /* byte 3 */
} CorrectedSaleConditionModifier;

/* any Corrected Sale Condition Modifier at all: every byte one the checker chooses */
static void any_corrected_sale_condition_modifier(CorrectedSaleConditionModifier *record) {
  record->corrected_settlement_type = arbitrary();
  record->corrected_trade_through_exemption = arbitrary();
  record->corrected_extended_hours_or_sold_code = arbitrary();
  record->corrected_special_sale_condition = arbitrary();
}

/* Corrected Sale Condition Modifier to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_corrected_sale_condition_modifier(const CorrectedSaleConditionModifier *record, uint8_t *wire, size_t at) {
  wire[at++] = record->corrected_settlement_type;
  wire[at++] = record->corrected_trade_through_exemption;
  wire[at++] = record->corrected_extended_hours_or_sold_code;
  wire[at++] = record->corrected_special_sale_condition;

  return at;
}

/* Corrected Sale Condition Modifier off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_corrected_sale_condition_modifier(CorrectedSaleConditionModifier *record, const uint8_t *wire, size_t at) {
  record->corrected_settlement_type = wire[at++];
  record->corrected_trade_through_exemption = wire[at++];
  record->corrected_extended_hours_or_sold_code = wire[at++];
  record->corrected_special_sale_condition = wire[at++];

  return at;
}

/* what was read of Corrected Sale Condition Modifier is what was written, byte for byte */
static void equal_corrected_sale_condition_modifier(const CorrectedSaleConditionModifier *read, const CorrectedSaleConditionModifier *written) {
  assert(read->corrected_settlement_type == written->corrected_settlement_type);
  assert(read->corrected_trade_through_exemption == written->corrected_trade_through_exemption);
  assert(read->corrected_extended_hours_or_sold_code == written->corrected_extended_hours_or_sold_code);
  assert(read->corrected_special_sale_condition == written->corrected_special_sale_condition);
}

/* Corrected Sale Condition Modifier: written and read back, then read and written back */
static void check_corrected_sale_condition_modifier(void) {
  CorrectedSaleConditionModifier sent;
  CorrectedSaleConditionModifier got;
  uint8_t wire[4];
  uint8_t again[4];

  any_corrected_sale_condition_modifier(&sent);
  assert(encode_corrected_sale_condition_modifier(&sent, wire, 0) == 4);
  assert(decode_corrected_sale_condition_modifier(&got, wire, 0) == 4);
  equal_corrected_sale_condition_modifier(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_corrected_sale_condition_modifier(&got, wire, 0) == 4);
  assert(encode_corrected_sale_condition_modifier(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 54 bytes -------------------------------------- */

/* The following message is used in the event that a TRF trade transaction is corrected on the same business day that it is reported. */
typedef struct {
  uint8_t market_center_identifier;                                  /* byte 0 */
  uint8_t issue_symbol[8];                                           /* bytes 1 to 8 */
  uint8_t security_class;                                            /* byte 9 */
  uint8_t original_trade_control_number[10];                         /* bytes 10 to 19 */
  uint8_t original_trade_price[4];                                   /* bytes 20 to 23 */
  uint8_t original_trade_size[4];                                    /* bytes 24 to 27 */
  OriginalSaleConditionModifier original_sale_condition_modifier;    /* bytes 28 to 31 */
  uint8_t corrected_trade_control_number[10];                        /* bytes 32 to 41 */
  uint8_t corrected_trade_price[4];                                  /* bytes 42 to 45 */
  uint8_t corrected_trade_size[4];                                   /* bytes 46 to 49 */
  CorrectedSaleConditionModifier corrected_sale_condition_modifier;  /* bytes 50 to 53 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  record->market_center_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = arbitrary(); }
  any_original_sale_condition_modifier(&record->original_sale_condition_modifier);
  for (size_t i = 0; i < 10; i++) { record->corrected_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_size[i] = arbitrary(); }
  any_corrected_sale_condition_modifier(&record->corrected_sale_condition_modifier);
}

/* Trade Correction Message to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->original_trade_control_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_size[i]; }
  at = encode_original_sale_condition_modifier(&record->original_sale_condition_modifier, wire, at);
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->corrected_trade_control_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_trade_size[i]; }
  at = encode_corrected_sale_condition_modifier(&record->corrected_sale_condition_modifier, wire, at);

  return at;
}

/* Trade Correction Message off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = wire[at++]; }
  at = decode_original_sale_condition_modifier(&record->original_sale_condition_modifier, wire, at);
  for (size_t i = 0; i < 10; i++) { record->corrected_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_size[i] = wire[at++]; }
  at = decode_corrected_sale_condition_modifier(&record->corrected_sale_condition_modifier, wire, at);

  return at;
}

/* what was read of Trade Correction Message is what was written, byte for byte */
static void equal_trade_correction_message(const TradeCorrectionMessage *read, const TradeCorrectionMessage *written) {
  assert(read->market_center_identifier == written->market_center_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->original_trade_control_number[i] == written->original_trade_control_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_size[i] == written->original_trade_size[i]); }
  equal_original_sale_condition_modifier(&read->original_sale_condition_modifier, &written->original_sale_condition_modifier);
  for (size_t i = 0; i < 10; i++) { assert(read->corrected_trade_control_number[i] == written->corrected_trade_control_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_trade_price[i] == written->corrected_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_trade_size[i] == written->corrected_trade_size[i]); }
  equal_corrected_sale_condition_modifier(&read->corrected_sale_condition_modifier, &written->corrected_sale_condition_modifier);
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[54];
  uint8_t again[54];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 54);
  assert(decode_trade_correction_message(&got, wire, 0) == 54);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 54);
  assert(encode_trade_correction_message(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Form Trade Correction Message: 62 bytes ---------------------------- */

/* The following message is used in the event that a Nasdaq trade transaction is corrected on the same business day that it is reported, only for trades that have exceeded the upper limit of a 4-byte price. */
typedef struct {
  uint8_t originating_market_center_identifier;                      /* byte 0 */
  uint8_t issue_symbol[8];                                           /* bytes 1 to 8 */
  uint8_t security_class;                                            /* byte 9 */
  uint8_t original_trade_control_number[10];                         /* bytes 10 to 19 */
  uint8_t original_trade_price_long[8];                              /* bytes 20 to 27 */
  uint8_t original_trade_size[4];                                    /* bytes 28 to 31 */
  OriginalSaleConditionModifier original_sale_condition_modifier;    /* bytes 32 to 35 */
  uint8_t corrected_trade_control_number[10];                        /* bytes 36 to 45 */
  uint8_t corrected_trade_price_long[8];                             /* bytes 46 to 53 */
  uint8_t corrected_trade_size[4];                                   /* bytes 54 to 57 */
  CorrectedSaleConditionModifier corrected_sale_condition_modifier;  /* bytes 58 to 61 */
} LongFormTradeCorrectionMessage;

/* any Long Form Trade Correction Message at all: every byte one the checker chooses */
static void any_long_form_trade_correction_message(LongFormTradeCorrectionMessage *record) {
  record->originating_market_center_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = arbitrary(); }
  any_original_sale_condition_modifier(&record->original_sale_condition_modifier);
  for (size_t i = 0; i < 10; i++) { record->corrected_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_size[i] = arbitrary(); }
  any_corrected_sale_condition_modifier(&record->corrected_sale_condition_modifier);
}

/* Long Form Trade Correction Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_long_form_trade_correction_message(const LongFormTradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->originating_market_center_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->original_trade_control_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_trade_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_size[i]; }
  at = encode_original_sale_condition_modifier(&record->original_sale_condition_modifier, wire, at);
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->corrected_trade_control_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_trade_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_trade_size[i]; }
  at = encode_corrected_sale_condition_modifier(&record->corrected_sale_condition_modifier, wire, at);

  return at;
}

/* Long Form Trade Correction Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_long_form_trade_correction_message(LongFormTradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  record->originating_market_center_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = wire[at++]; }
  at = decode_original_sale_condition_modifier(&record->original_sale_condition_modifier, wire, at);
  for (size_t i = 0; i < 10; i++) { record->corrected_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_size[i] = wire[at++]; }
  at = decode_corrected_sale_condition_modifier(&record->corrected_sale_condition_modifier, wire, at);

  return at;
}

/* what was read of Long Form Trade Correction Message is what was written, byte for byte */
static void equal_long_form_trade_correction_message(const LongFormTradeCorrectionMessage *read, const LongFormTradeCorrectionMessage *written) {
  assert(read->originating_market_center_identifier == written->originating_market_center_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->original_trade_control_number[i] == written->original_trade_control_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_trade_price_long[i] == written->original_trade_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_size[i] == written->original_trade_size[i]); }
  equal_original_sale_condition_modifier(&read->original_sale_condition_modifier, &written->original_sale_condition_modifier);
  for (size_t i = 0; i < 10; i++) { assert(read->corrected_trade_control_number[i] == written->corrected_trade_control_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_trade_price_long[i] == written->corrected_trade_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_trade_size[i] == written->corrected_trade_size[i]); }
  equal_corrected_sale_condition_modifier(&read->corrected_sale_condition_modifier, &written->corrected_sale_condition_modifier);
}

/* Long Form Trade Correction Message: written and read back, then read and written back */
static void check_long_form_trade_correction_message(void) {
  LongFormTradeCorrectionMessage sent;
  LongFormTradeCorrectionMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_long_form_trade_correction_message(&sent);
  assert(encode_long_form_trade_correction_message(&sent, wire, 0) == 62);
  assert(decode_long_form_trade_correction_message(&got, wire, 0) == 62);
  equal_long_form_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_long_form_trade_correction_message(&got, wire, 0) == 62);
  assert(encode_long_form_trade_correction_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Next Shares Trade Correction Message: 62 bytes -------------------------- */

/* The following message is used in the event that a TRF trade transaction for an NextShares is corrected on the same business day that it is reported. */
typedef struct {
  uint8_t market_center_identifier;                                  /* byte 0 */
  uint8_t issue_symbol[8];                                           /* bytes 1 to 8 */
  uint8_t security_class;                                            /* byte 9 */
  uint8_t original_trade_control_number[10];                         /* bytes 10 to 19 */
  uint8_t original_trade_price[4];                                   /* bytes 20 to 23 */
  uint8_t original_nav_premium_discount_amount[4];                   /* bytes 24 to 27 */
  uint8_t original_trade_size[4];                                    /* bytes 28 to 31 */
  OriginalSaleConditionModifier original_sale_condition_modifier;    /* bytes 32 to 35 */
  uint8_t corrected_trade_control_number[10];                        /* bytes 36 to 45 */
  uint8_t corrected_trade_price[4];                                  /* bytes 46 to 49 */
  uint8_t corrected_nav_premium_discount_amount[4];                  /* bytes 50 to 53 */
  uint8_t corrected_trade_size[4];                                   /* bytes 54 to 57 */
  CorrectedSaleConditionModifier corrected_sale_condition_modifier;  /* bytes 58 to 61 */
} NextSharesTradeCorrectionMessage;

/* any Next Shares Trade Correction Message at all: every byte one the checker chooses */
static void any_next_shares_trade_correction_message(NextSharesTradeCorrectionMessage *record) {
  record->market_center_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_nav_premium_discount_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = arbitrary(); }
  any_original_sale_condition_modifier(&record->original_sale_condition_modifier);
  for (size_t i = 0; i < 10; i++) { record->corrected_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_nav_premium_discount_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_size[i] = arbitrary(); }
  any_corrected_sale_condition_modifier(&record->corrected_sale_condition_modifier);
}

/* Next Shares Trade Correction Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_next_shares_trade_correction_message(const NextSharesTradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->original_trade_control_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_nav_premium_discount_amount[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_size[i]; }
  at = encode_original_sale_condition_modifier(&record->original_sale_condition_modifier, wire, at);
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->corrected_trade_control_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_nav_premium_discount_amount[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_trade_size[i]; }
  at = encode_corrected_sale_condition_modifier(&record->corrected_sale_condition_modifier, wire, at);

  return at;
}

/* Next Shares Trade Correction Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_next_shares_trade_correction_message(NextSharesTradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_nav_premium_discount_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = wire[at++]; }
  at = decode_original_sale_condition_modifier(&record->original_sale_condition_modifier, wire, at);
  for (size_t i = 0; i < 10; i++) { record->corrected_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_nav_premium_discount_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_size[i] = wire[at++]; }
  at = decode_corrected_sale_condition_modifier(&record->corrected_sale_condition_modifier, wire, at);

  return at;
}

/* what was read of Next Shares Trade Correction Message is what was written, byte for byte */
static void equal_next_shares_trade_correction_message(const NextSharesTradeCorrectionMessage *read, const NextSharesTradeCorrectionMessage *written) {
  assert(read->market_center_identifier == written->market_center_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->original_trade_control_number[i] == written->original_trade_control_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_nav_premium_discount_amount[i] == written->original_nav_premium_discount_amount[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_size[i] == written->original_trade_size[i]); }
  equal_original_sale_condition_modifier(&read->original_sale_condition_modifier, &written->original_sale_condition_modifier);
  for (size_t i = 0; i < 10; i++) { assert(read->corrected_trade_control_number[i] == written->corrected_trade_control_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_trade_price[i] == written->corrected_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_nav_premium_discount_amount[i] == written->corrected_nav_premium_discount_amount[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_trade_size[i] == written->corrected_trade_size[i]); }
  equal_corrected_sale_condition_modifier(&read->corrected_sale_condition_modifier, &written->corrected_sale_condition_modifier);
}

/* Next Shares Trade Correction Message: written and read back, then read and written back */
static void check_next_shares_trade_correction_message(void) {
  NextSharesTradeCorrectionMessage sent;
  NextSharesTradeCorrectionMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_next_shares_trade_correction_message(&sent);
  assert(encode_next_shares_trade_correction_message(&sent, wire, 0) == 62);
  assert(decode_next_shares_trade_correction_message(&got, wire, 0) == 62);
  equal_next_shares_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_next_shares_trade_correction_message(&got, wire, 0) == 62);
  assert(encode_next_shares_trade_correction_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Trading Action Message: 14 bytes ---------------------------------- */

/* Nasdaq uses this administrative message to indicate the current trading status of a security to the trading community. */
typedef struct {
  uint8_t issue_symbol[8];        /* bytes 0 to 7 */
  uint8_t security_class;         /* byte 8 */
  uint8_t current_trading_state;  /* byte 9 */
  uint8_t reason[4];              /* bytes 10 to 13 */
} StockTradingActionMessage;

/* any Stock Trading Action Message at all: every byte one the checker chooses */
static void any_stock_trading_action_message(StockTradingActionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  record->current_trading_state = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reason[i] = arbitrary(); }
}

/* Stock Trading Action Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_stock_trading_action_message(const StockTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  wire[at++] = record->current_trading_state;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Stock Trading Action Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_stock_trading_action_message(StockTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  record->current_trading_state = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Trading Action Message is what was written, byte for byte */
static void equal_stock_trading_action_message(const StockTradingActionMessage *read, const StockTradingActionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
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

/* Nasdaq processes orders based on the most recent Reg SHO Restriction status value. */
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

/* ---- Stock Directory Message: 40 bytes --------------------------------------- */

/* At the start of each trading day, Nasdaq disseminates stock directory messages for all active symbols in the Nasdaq system. */
typedef struct {
  uint8_t stock[8];                        /* bytes 0 to 7 */
  uint8_t market_category;                 /* byte 8 */
  uint8_t financial_status_indicator;      /* byte 9 */
  uint8_t round_lot_size[4];               /* bytes 10 to 13 */
  uint8_t round_lots_only;                 /* byte 14 */
  uint8_t issue_classification;            /* byte 15 */
  uint8_t issue_sub_type[2];               /* bytes 16 to 17 */
  uint8_t authenticity;                    /* byte 18 */
  uint8_t short_sale_threshold_indicator;  /* byte 19 */
  uint8_t ipo_flag;                        /* byte 20 */
  uint8_t luld_reference_price_tier;       /* byte 21 */
  uint8_t etp_flag;                        /* byte 22 */
  uint8_t etp_leverage_factor[4];          /* bytes 23 to 26 */
  uint8_t inverse_indicator;               /* byte 27 */
  uint8_t bloomberg_id[12];                /* bytes 28 to 39 */
} StockDirectoryMessage;

/* any Stock Directory Message at all: every byte one the checker chooses */
static void any_stock_directory_message(StockDirectoryMessage *record) {
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
  for (size_t i = 0; i < 12; i++) { record->bloomberg_id[i] = arbitrary(); }
}

/* Stock Directory Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_stock_directory_message(const StockDirectoryMessage *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bloomberg_id[i]; }

  return at;
}

/* Stock Directory Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_stock_directory_message(StockDirectoryMessage *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 12; i++) { record->bloomberg_id[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Directory Message is what was written, byte for byte */
static void equal_stock_directory_message(const StockDirectoryMessage *read, const StockDirectoryMessage *written) {
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
  for (size_t i = 0; i < 12; i++) { assert(read->bloomberg_id[i] == written->bloomberg_id[i]); }
}

/* Stock Directory Message: written and read back, then read and written back */
static void check_stock_directory_message(void) {
  StockDirectoryMessage sent;
  StockDirectoryMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_stock_directory_message(&sent);
  assert(encode_stock_directory_message(&sent, wire, 0) == 40);
  assert(decode_stock_directory_message(&got, wire, 0) == 40);
  equal_stock_directory_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_directory_message(&got, wire, 0) == 40);
  assert(encode_stock_directory_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Adjusted Closing Price Message: 13 bytes -------------------------------- */

/* At the start of each trading day, Nasdaq disseminates the adjusted closing price for all active symbols in the Nasdaq system. */
typedef struct {
  uint8_t stock[8];                   /* bytes 0 to 7 */
  uint8_t security_class;             /* byte 8 */
  uint8_t adjusted_closing_price[4];  /* bytes 9 to 12 */
} AdjustedClosingPriceMessage;

/* any Adjusted Closing Price Message at all: every byte one the checker chooses */
static void any_adjusted_closing_price_message(AdjustedClosingPriceMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->adjusted_closing_price[i] = arbitrary(); }
}

/* Adjusted Closing Price Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_adjusted_closing_price_message(const AdjustedClosingPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->adjusted_closing_price[i]; }

  return at;
}

/* Adjusted Closing Price Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_adjusted_closing_price_message(AdjustedClosingPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->adjusted_closing_price[i] = wire[at++]; }

  return at;
}

/* what was read of Adjusted Closing Price Message is what was written, byte for byte */
static void equal_adjusted_closing_price_message(const AdjustedClosingPriceMessage *read, const AdjustedClosingPriceMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 4; i++) { assert(read->adjusted_closing_price[i] == written->adjusted_closing_price[i]); }
}

/* Adjusted Closing Price Message: written and read back, then read and written back */
static void check_adjusted_closing_price_message(void) {
  AdjustedClosingPriceMessage sent;
  AdjustedClosingPriceMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_adjusted_closing_price_message(&sent);
  assert(encode_adjusted_closing_price_message(&sent, wire, 0) == 13);
  assert(decode_adjusted_closing_price_message(&got, wire, 0) == 13);
  equal_adjusted_closing_price_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_adjusted_closing_price_message(&got, wire, 0) == 13);
  assert(encode_adjusted_closing_price_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Form Adjusted Closing Price Message: 17 bytes ---------------------- */

/* At the start of each trading day, Nasdaq disseminates the adjusted closing price for all active symbols in the Nasdaq system, only for securities that have exceeded the upper limit of a 4-byte price. */
typedef struct {
  uint8_t issue_symbol[8];                 /* bytes 0 to 7 */
  uint8_t security_class;                  /* byte 8 */
  uint8_t adjusted_closing_price_long[8];  /* bytes 9 to 16 */
} LongFormAdjustedClosingPriceMessage;

/* any Long Form Adjusted Closing Price Message at all: every byte one the checker chooses */
static void any_long_form_adjusted_closing_price_message(LongFormAdjustedClosingPriceMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->adjusted_closing_price_long[i] = arbitrary(); }
}

/* Long Form Adjusted Closing Price Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_long_form_adjusted_closing_price_message(const LongFormAdjustedClosingPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->adjusted_closing_price_long[i]; }

  return at;
}

/* Long Form Adjusted Closing Price Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_long_form_adjusted_closing_price_message(LongFormAdjustedClosingPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->adjusted_closing_price_long[i] = wire[at++]; }

  return at;
}

/* what was read of Long Form Adjusted Closing Price Message is what was written, byte for byte */
static void equal_long_form_adjusted_closing_price_message(const LongFormAdjustedClosingPriceMessage *read, const LongFormAdjustedClosingPriceMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 8; i++) { assert(read->adjusted_closing_price_long[i] == written->adjusted_closing_price_long[i]); }
}

/* Long Form Adjusted Closing Price Message: written and read back, then read and written back */
static void check_long_form_adjusted_closing_price_message(void) {
  LongFormAdjustedClosingPriceMessage sent;
  LongFormAdjustedClosingPriceMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_long_form_adjusted_closing_price_message(&sent);
  assert(encode_long_form_adjusted_closing_price_message(&sent, wire, 0) == 17);
  assert(decode_long_form_adjusted_closing_price_message(&got, wire, 0) == 17);
  equal_long_form_adjusted_closing_price_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_long_form_adjusted_closing_price_message(&got, wire, 0) == 17);
  assert(encode_long_form_adjusted_closing_price_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mwcb Decline Level Message: 24 bytes ------------------------------------ */

/* Informs data recipients what the daily MWCB breach points are set to for the current trading day. */
typedef struct {
  uint8_t level_1[8];  /* bytes 0 to 7 */
  uint8_t level_2[8];  /* bytes 8 to 15 */
  uint8_t level_3[8];  /* bytes 16 to 23 */
} MwcbDeclineLevelMessage;

/* any Mwcb Decline Level Message at all: every byte one the checker chooses */
static void any_mwcb_decline_level_message(MwcbDeclineLevelMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->level_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->level_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->level_3[i] = arbitrary(); }
}

/* Mwcb Decline Level Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_mwcb_decline_level_message(const MwcbDeclineLevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->level_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->level_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->level_3[i]; }

  return at;
}

/* Mwcb Decline Level Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_mwcb_decline_level_message(MwcbDeclineLevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->level_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->level_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->level_3[i] = wire[at++]; }

  return at;
}

/* what was read of Mwcb Decline Level Message is what was written, byte for byte */
static void equal_mwcb_decline_level_message(const MwcbDeclineLevelMessage *read, const MwcbDeclineLevelMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->level_1[i] == written->level_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->level_2[i] == written->level_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->level_3[i] == written->level_3[i]); }
}

/* Mwcb Decline Level Message: written and read back, then read and written back */
static void check_mwcb_decline_level_message(void) {
  MwcbDeclineLevelMessage sent;
  MwcbDeclineLevelMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_mwcb_decline_level_message(&sent);
  assert(encode_mwcb_decline_level_message(&sent, wire, 0) == 24);
  assert(decode_mwcb_decline_level_message(&got, wire, 0) == 24);
  equal_mwcb_decline_level_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_mwcb_decline_level_message(&got, wire, 0) == 24);
  assert(encode_mwcb_decline_level_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mwcb Status Message: 1 byte --------------------------------------------- */

/* Informs data recipients when a MWCB has breached one of the established levels. */
typedef struct {
  uint8_t breached_level;  /* byte 0 */
} MwcbStatusMessage;

/* any Mwcb Status Message at all: every byte one the checker chooses */
static void any_mwcb_status_message(MwcbStatusMessage *record) {
  record->breached_level = arbitrary();
}

/* Mwcb Status Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_mwcb_status_message(const MwcbStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->breached_level;

  return at;
}

/* Mwcb Status Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_mwcb_status_message(MwcbStatusMessage *record, const uint8_t *wire, size_t at) {
  record->breached_level = wire[at++];

  return at;
}

/* what was read of Mwcb Status Message is what was written, byte for byte */
static void equal_mwcb_status_message(const MwcbStatusMessage *read, const MwcbStatusMessage *written) {
  assert(read->breached_level == written->breached_level);
}

/* Mwcb Status Message: written and read back, then read and written back */
static void check_mwcb_status_message(void) {
  MwcbStatusMessage sent;
  MwcbStatusMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_mwcb_status_message(&sent);
  assert(encode_mwcb_status_message(&sent, wire, 0) == 1);
  assert(decode_mwcb_status_message(&got, wire, 0) == 1);
  equal_mwcb_status_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_mwcb_status_message(&got, wire, 0) == 1);
  assert(encode_mwcb_status_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ipo Quoting Period Update Message: 17 bytes ----------------------------- */

/* Indicates the anticipated IPO quotation release time of a security. */
typedef struct {
  uint8_t stock[8];                         /* bytes 0 to 7 */
  uint8_t ipo_quotation_release_time[4];    /* bytes 8 to 11 */
  uint8_t ipo_quotation_release_qualifier;  /* byte 12 */
  uint8_t ipo_price[4];                     /* bytes 13 to 16 */
} IpoQuotingPeriodUpdateMessage;

/* any Ipo Quoting Period Update Message at all: every byte one the checker chooses */
static void any_ipo_quoting_period_update_message(IpoQuotingPeriodUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ipo_quotation_release_time[i] = arbitrary(); }
  record->ipo_quotation_release_qualifier = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->ipo_price[i] = arbitrary(); }
}

/* Ipo Quoting Period Update Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_ipo_quoting_period_update_message(const IpoQuotingPeriodUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ipo_quotation_release_time[i]; }
  wire[at++] = record->ipo_quotation_release_qualifier;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ipo_price[i]; }

  return at;
}

/* Ipo Quoting Period Update Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_ipo_quoting_period_update_message(IpoQuotingPeriodUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ipo_quotation_release_time[i] = wire[at++]; }
  record->ipo_quotation_release_qualifier = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->ipo_price[i] = wire[at++]; }

  return at;
}

/* what was read of Ipo Quoting Period Update Message is what was written, byte for byte */
static void equal_ipo_quoting_period_update_message(const IpoQuotingPeriodUpdateMessage *read, const IpoQuotingPeriodUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ipo_quotation_release_time[i] == written->ipo_quotation_release_time[i]); }
  assert(read->ipo_quotation_release_qualifier == written->ipo_quotation_release_qualifier);
  for (size_t i = 0; i < 4; i++) { assert(read->ipo_price[i] == written->ipo_price[i]); }
}

/* Ipo Quoting Period Update Message: written and read back, then read and written back */
static void check_ipo_quoting_period_update_message(void) {
  IpoQuotingPeriodUpdateMessage sent;
  IpoQuotingPeriodUpdateMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_ipo_quoting_period_update_message(&sent);
  assert(encode_ipo_quoting_period_update_message(&sent, wire, 0) == 17);
  assert(decode_ipo_quoting_period_update_message(&got, wire, 0) == 17);
  equal_ipo_quoting_period_update_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_ipo_quoting_period_update_message(&got, wire, 0) == 17);
  assert(encode_ipo_quoting_period_update_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Operational Halt Message: 10 bytes -------------------------------------- */

/* An Operational Halt means that there has been an interruption of service on the identified security impacting only the designated Market Center. */
typedef struct {
  uint8_t stock[8];                 /* bytes 0 to 7 */
  uint8_t market_code;              /* byte 8 */
  uint8_t operational_halt_action;  /* byte 9 */
} OperationalHaltMessage;

/* any Operational Halt Message at all: every byte one the checker chooses */
static void any_operational_halt_message(OperationalHaltMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->market_code = arbitrary();
  record->operational_halt_action = arbitrary();
}

/* Operational Halt Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_operational_halt_message(const OperationalHaltMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->market_code;
  wire[at++] = record->operational_halt_action;

  return at;
}

/* Operational Halt Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_operational_halt_message(OperationalHaltMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->market_code = wire[at++];
  record->operational_halt_action = wire[at++];

  return at;
}

/* what was read of Operational Halt Message is what was written, byte for byte */
static void equal_operational_halt_message(const OperationalHaltMessage *read, const OperationalHaltMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->market_code == written->market_code);
  assert(read->operational_halt_action == written->operational_halt_action);
}

/* Operational Halt Message: written and read back, then read and written back */
static void check_operational_halt_message(void) {
  OperationalHaltMessage sent;
  OperationalHaltMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_operational_halt_message(&sent);
  assert(encode_operational_halt_message(&sent, wire, 0) == 10);
  assert(decode_operational_halt_message(&got, wire, 0) == 10);
  equal_operational_halt_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_operational_halt_message(&got, wire, 0) == 10);
  assert(encode_operational_halt_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_system_event_message();
  check_sale_condition_modifier();
  check_trade_report_message();
  check_long_form_trade_report_message();
  check_next_shares_trade_report_message();
  check_original_sale_condition_modifier();
  check_trade_cancel_error_message();
  check_long_form_trade_cancel_error_message();
  check_next_shares_trade_cancel_error_message();
  check_corrected_sale_condition_modifier();
  check_trade_correction_message();
  check_long_form_trade_correction_message();
  check_next_shares_trade_correction_message();
  check_stock_trading_action_message();
  check_reg_sho_short_sale_price_test_restricted_indicator_message();
  check_stock_directory_message();
  check_adjusted_closing_price_message();
  check_long_form_adjusted_closing_price_message();
  check_mwcb_decline_level_message();
  check_mwcb_status_message();
  check_ipo_quoting_period_update_message();
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
