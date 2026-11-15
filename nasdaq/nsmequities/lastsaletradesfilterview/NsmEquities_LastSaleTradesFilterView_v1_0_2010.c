// nasdaq/nsmequities/lastsaletradesfilterview/NsmEquities_LastSaleTradesFilterView_v1_0_2010.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Last Sale Trades FilterView
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

/* Sale Condition Modifier */
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

/* ---- Trade Report Message: 41 bytes ------------------------------------------ */

/* The following message is used to relay NASDAQ execution system and TRF trade transactions that are reported for the current business day. Please note that NASDAQ only reports one-side of a trade execution on the NASDAQ Last Sale (NLS) feed and other data feed products. */
typedef struct {
  uint8_t market_center_identifier;               /* byte 0 */
  uint8_t issue_symbol[6];                        /* bytes 1 to 6 */
  uint8_t security_class;                         /* byte 7 */
  uint8_t trade_control_number[10];               /* bytes 8 to 17 */
  uint8_t trade_price[10];                        /* bytes 18 to 27 */
  uint8_t trade_size[9];                          /* bytes 28 to 36 */
  SaleConditionModifier sale_condition_modifier;  /* bytes 37 to 40 */
} TradeReportMessage;

/* any Trade Report Message at all: every byte one the checker chooses */
static void any_trade_report_message(TradeReportMessage *record) {
  record->market_center_identifier = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->trade_size[i] = arbitrary(); }
  any_sale_condition_modifier(&record->sale_condition_modifier);
}

/* Trade Report Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_trade_report_message(const TradeReportMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_identifier;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_control_number[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->trade_size[i]; }
  at = encode_sale_condition_modifier(&record->sale_condition_modifier, wire, at);

  return at;
}

/* Trade Report Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_trade_report_message(TradeReportMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_identifier = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->trade_size[i] = wire[at++]; }
  at = decode_sale_condition_modifier(&record->sale_condition_modifier, wire, at);

  return at;
}

/* what was read of Trade Report Message is what was written, byte for byte */
static void equal_trade_report_message(const TradeReportMessage *read, const TradeReportMessage *written) {
  assert(read->market_center_identifier == written->market_center_identifier);
  for (size_t i = 0; i < 6; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->trade_control_number[i] == written->trade_control_number[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->trade_size[i] == written->trade_size[i]); }
  equal_sale_condition_modifier(&read->sale_condition_modifier, &written->sale_condition_modifier);
}

/* Trade Report Message: written and read back, then read and written back */
static void check_trade_report_message(void) {
  TradeReportMessage sent;
  TradeReportMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_trade_report_message(&sent);
  assert(encode_trade_report_message(&sent, wire, 0) == 41);
  assert(decode_trade_report_message(&got, wire, 0) == 41);
  equal_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_message(&got, wire, 0) == 41);
  assert(encode_trade_report_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Original Sale Condition Modifier: 4 bytes ------------------------------- */

/* Original Sale Condition Modifier */
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

/* ---- Trade Cancel Error Message: 41 bytes ------------------------------------ */

/* The following message is used in the event that a NASDAQ or TRF trade transaction is cancelled on the same business day that it is reported. */
typedef struct {
  uint8_t market_center_identifier;                                /* byte 0 */
  uint8_t issue_symbol[6];                                         /* bytes 1 to 6 */
  uint8_t security_class;                                          /* byte 7 */
  uint8_t original_trade_control_number[10];                       /* bytes 8 to 17 */
  uint8_t original_trade_price[10];                                /* bytes 18 to 27 */
  uint8_t original_trade_size[9];                                  /* bytes 28 to 36 */
  OriginalSaleConditionModifier original_sale_condition_modifier;  /* bytes 37 to 40 */
} TradeCancelErrorMessage;

/* any Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_trade_cancel_error_message(TradeCancelErrorMessage *record) {
  record->market_center_identifier = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->original_trade_size[i] = arbitrary(); }
  any_original_sale_condition_modifier(&record->original_sale_condition_modifier);
}

/* Trade Cancel Error Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_error_message(const TradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_identifier;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->original_trade_control_number[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->original_trade_size[i]; }
  at = encode_original_sale_condition_modifier(&record->original_sale_condition_modifier, wire, at);

  return at;
}

/* Trade Cancel Error Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_error_message(TradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_identifier = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->original_trade_size[i] = wire[at++]; }
  at = decode_original_sale_condition_modifier(&record->original_sale_condition_modifier, wire, at);

  return at;
}

/* what was read of Trade Cancel Error Message is what was written, byte for byte */
static void equal_trade_cancel_error_message(const TradeCancelErrorMessage *read, const TradeCancelErrorMessage *written) {
  assert(read->market_center_identifier == written->market_center_identifier);
  for (size_t i = 0; i < 6; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->original_trade_control_number[i] == written->original_trade_control_number[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->original_trade_size[i] == written->original_trade_size[i]); }
  equal_original_sale_condition_modifier(&read->original_sale_condition_modifier, &written->original_sale_condition_modifier);
}

/* Trade Cancel Error Message: written and read back, then read and written back */
static void check_trade_cancel_error_message(void) {
  TradeCancelErrorMessage sent;
  TradeCancelErrorMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_trade_cancel_error_message(&sent);
  assert(encode_trade_cancel_error_message(&sent, wire, 0) == 41);
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 41);
  equal_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 41);
  assert(encode_trade_cancel_error_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Corrected Sale Condition Modifier: 4 bytes ------------------------------ */

/* Corrected Sale Condition Modifier */
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

/* ---- Trade Correction Message: 74 bytes -------------------------------------- */

/* The following message is used in the event that a TRF trade transaction is corrected on the same business day that it is reported. */
typedef struct {
  uint8_t market_center_identifier;                                  /* byte 0 */
  uint8_t issue_symbol[6];                                           /* bytes 1 to 6 */
  uint8_t security_class;                                            /* byte 7 */
  uint8_t original_trade_control_number[10];                         /* bytes 8 to 17 */
  uint8_t original_trade_price[10];                                  /* bytes 18 to 27 */
  uint8_t original_trade_size[9];                                    /* bytes 28 to 36 */
  OriginalSaleConditionModifier original_sale_condition_modifier;    /* bytes 37 to 40 */
  uint8_t corrected_trade_control_number[10];                        /* bytes 41 to 50 */
  uint8_t corrected_trade_price[10];                                 /* bytes 51 to 60 */
  uint8_t corrected_trade_size[9];                                   /* bytes 61 to 69 */
  CorrectedSaleConditionModifier corrected_sale_condition_modifier;  /* bytes 70 to 73 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  record->market_center_identifier = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->original_trade_size[i] = arbitrary(); }
  any_original_sale_condition_modifier(&record->original_sale_condition_modifier);
  for (size_t i = 0; i < 10; i++) { record->corrected_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->corrected_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->corrected_trade_size[i] = arbitrary(); }
  any_corrected_sale_condition_modifier(&record->corrected_sale_condition_modifier);
}

/* Trade Correction Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_identifier;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->original_trade_control_number[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->original_trade_size[i]; }
  at = encode_original_sale_condition_modifier(&record->original_sale_condition_modifier, wire, at);
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->corrected_trade_control_number[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->corrected_trade_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->corrected_trade_size[i]; }
  at = encode_corrected_sale_condition_modifier(&record->corrected_sale_condition_modifier, wire, at);

  return at;
}

/* Trade Correction Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_identifier = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->original_trade_size[i] = wire[at++]; }
  at = decode_original_sale_condition_modifier(&record->original_sale_condition_modifier, wire, at);
  for (size_t i = 0; i < 10; i++) { record->corrected_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->corrected_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->corrected_trade_size[i] = wire[at++]; }
  at = decode_corrected_sale_condition_modifier(&record->corrected_sale_condition_modifier, wire, at);

  return at;
}

/* what was read of Trade Correction Message is what was written, byte for byte */
static void equal_trade_correction_message(const TradeCorrectionMessage *read, const TradeCorrectionMessage *written) {
  assert(read->market_center_identifier == written->market_center_identifier);
  for (size_t i = 0; i < 6; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->original_trade_control_number[i] == written->original_trade_control_number[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->original_trade_size[i] == written->original_trade_size[i]); }
  equal_original_sale_condition_modifier(&read->original_sale_condition_modifier, &written->original_sale_condition_modifier);
  for (size_t i = 0; i < 10; i++) { assert(read->corrected_trade_control_number[i] == written->corrected_trade_control_number[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->corrected_trade_price[i] == written->corrected_trade_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->corrected_trade_size[i] == written->corrected_trade_size[i]); }
  equal_corrected_sale_condition_modifier(&read->corrected_sale_condition_modifier, &written->corrected_sale_condition_modifier);
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 74);
  assert(decode_trade_correction_message(&got, wire, 0) == 74);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 74);
  assert(encode_trade_correction_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Trading Action Message: 12 bytes ---------------------------------- */

/* NASDAQ uses this administrative message to indicate the current trading status of a security to the trading community. */
typedef struct {
  uint8_t issue_symbol[6];        /* bytes 0 to 5 */
  uint8_t security_class;         /* byte 6 */
  uint8_t current_trading_state;  /* byte 7 */
  uint8_t reason[4];              /* bytes 8 to 11 */
} StockTradingActionMessage;

/* any Stock Trading Action Message at all: every byte one the checker chooses */
static void any_stock_trading_action_message(StockTradingActionMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  record->current_trading_state = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reason[i] = arbitrary(); }
}

/* Stock Trading Action Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_stock_trading_action_message(const StockTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  wire[at++] = record->current_trading_state;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Stock Trading Action Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_stock_trading_action_message(StockTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  record->current_trading_state = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Trading Action Message is what was written, byte for byte */
static void equal_stock_trading_action_message(const StockTradingActionMessage *read, const StockTradingActionMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  assert(read->current_trading_state == written->current_trading_state);
  for (size_t i = 0; i < 4; i++) { assert(read->reason[i] == written->reason[i]); }
}

/* Stock Trading Action Message: written and read back, then read and written back */
static void check_stock_trading_action_message(void) {
  StockTradingActionMessage sent;
  StockTradingActionMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_stock_trading_action_message(&sent);
  assert(encode_stock_trading_action_message(&sent, wire, 0) == 12);
  assert(decode_stock_trading_action_message(&got, wire, 0) == 12);
  equal_stock_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_trading_action_message(&got, wire, 0) == 12);
  assert(encode_stock_trading_action_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Directory Message: 8 bytes ---------------------------------------- */

/* At the start of each trading day, NASDAQ disseminates stock directory messages for all active symbols in the NASDAQ system. */
typedef struct {
  uint8_t issue_symbol[6];             /* bytes 0 to 5 */
  uint8_t market_category;             /* byte 6 */
  uint8_t financial_status_indicator;  /* byte 7 */
} StockDirectoryMessage;

/* any Stock Directory Message at all: every byte one the checker chooses */
static void any_stock_directory_message(StockDirectoryMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->issue_symbol[i] = arbitrary(); }
  record->market_category = arbitrary();
  record->financial_status_indicator = arbitrary();
}

/* Stock Directory Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_stock_directory_message(const StockDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->market_category;
  wire[at++] = record->financial_status_indicator;

  return at;
}

/* Stock Directory Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_stock_directory_message(StockDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->issue_symbol[i] = wire[at++]; }
  record->market_category = wire[at++];
  record->financial_status_indicator = wire[at++];

  return at;
}

/* what was read of Stock Directory Message is what was written, byte for byte */
static void equal_stock_directory_message(const StockDirectoryMessage *read, const StockDirectoryMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->market_category == written->market_category);
  assert(read->financial_status_indicator == written->financial_status_indicator);
}

/* Stock Directory Message: written and read back, then read and written back */
static void check_stock_directory_message(void) {
  StockDirectoryMessage sent;
  StockDirectoryMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_stock_directory_message(&sent);
  assert(encode_stock_directory_message(&sent, wire, 0) == 8);
  assert(decode_stock_directory_message(&got, wire, 0) == 8);
  equal_stock_directory_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_directory_message(&got, wire, 0) == 8);
  assert(encode_stock_directory_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_system_event_message();
  check_sale_condition_modifier();
  check_trade_report_message();
  check_original_sale_condition_modifier();
  check_trade_cancel_error_message();
  check_corrected_sale_condition_modifier();
  check_trade_correction_message();
  check_stock_trading_action_message();
  check_stock_directory_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
