// nasdaq/utdf/output/Nasdaq_Utdf_Output_v1_5.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Output
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
 *   - a run counted by a field
 *   - the dispatch that chooses a message by its type
 *   - a length prefix framing what follows
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

/* ---- Message Header: 4 bytes ------------------------------------------------- */

/* Mold Udp Message Header */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t version;            /* byte 2 */
  uint8_t message_category;   /* byte 3 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  record->version = arbitrary();
  record->message_category = arbitrary();
}

/* Message Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  wire[at++] = record->version;
  wire[at++] = record->message_category;

  return at;
}

/* Message Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  record->version = wire[at++];
  record->message_category = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  assert(read->version == written->version);
  assert(read->message_category == written->message_category);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 4);
  assert(decode_message_header(&got, wire, 0) == 4);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 4);
  assert(encode_message_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Info: 26 bytes -------------------------------------------------- */

/* Message Info */
typedef struct {
  uint8_t market_center_originator_id;  /* byte 0 */
  uint8_t sub_market_center_id;         /* byte 1 */
  uint8_t sip_timestamp[8];             /* bytes 2 to 9 */
  uint8_t participant_timestamp[8];     /* bytes 10 to 17 */
  uint8_t participant_token[8];         /* bytes 18 to 25 */
} MessageInfo;

/* any Message Info at all: every byte one the checker chooses */
static void any_message_info(MessageInfo *record) {
  record->market_center_originator_id = arbitrary();
  record->sub_market_center_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = arbitrary(); }
}

/* Message Info to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_message_info(const MessageInfo *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_originator_id;
  wire[at++] = record->sub_market_center_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_token[i]; }

  return at;
}

/* Message Info off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_message_info(MessageInfo *record, const uint8_t *wire, size_t at) {
  record->market_center_originator_id = wire[at++];
  record->sub_market_center_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = wire[at++]; }

  return at;
}

/* what was read of Message Info is what was written, byte for byte */
static void equal_message_info(const MessageInfo *read, const MessageInfo *written) {
  assert(read->market_center_originator_id == written->market_center_originator_id);
  assert(read->sub_market_center_id == written->sub_market_center_id);
  for (size_t i = 0; i < 8; i++) { assert(read->sip_timestamp[i] == written->sip_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_timestamp[i] == written->participant_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_token[i] == written->participant_token[i]); }
}

/* Message Info: written and read back, then read and written back */
static void check_message_info(void) {
  MessageInfo sent;
  MessageInfo got;
  uint8_t wire[26];
  uint8_t again[26];

  any_message_info(&sent);
  assert(encode_message_info(&sent, wire, 0) == 26);
  assert(decode_message_info(&got, wire, 0) == 26);
  equal_message_info(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_message_info(&got, wire, 0) == 26);
  assert(encode_message_info(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sale Condition: 4 bytes ------------------------------------------------- */

/* Sale Condition */
typedef struct {
  uint8_t level_1;  /* byte 0 */
  uint8_t level_2;  /* byte 1 */
  uint8_t level_3;  /* byte 2 */
  uint8_t level_4;  /* byte 3 */
} SaleCondition;

/* any Sale Condition at all: every byte one the checker chooses */
static void any_sale_condition(SaleCondition *record) {
  record->level_1 = arbitrary();
  record->level_2 = arbitrary();
  record->level_3 = arbitrary();
  record->level_4 = arbitrary();
}

/* Sale Condition to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_sale_condition(const SaleCondition *record, uint8_t *wire, size_t at) {
  wire[at++] = record->level_1;
  wire[at++] = record->level_2;
  wire[at++] = record->level_3;
  wire[at++] = record->level_4;

  return at;
}

/* Sale Condition off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_sale_condition(SaleCondition *record, const uint8_t *wire, size_t at) {
  record->level_1 = wire[at++];
  record->level_2 = wire[at++];
  record->level_3 = wire[at++];
  record->level_4 = wire[at++];

  return at;
}

/* what was read of Sale Condition is what was written, byte for byte */
static void equal_sale_condition(const SaleCondition *read, const SaleCondition *written) {
  assert(read->level_1 == written->level_1);
  assert(read->level_2 == written->level_2);
  assert(read->level_3 == written->level_3);
  assert(read->level_4 == written->level_4);
}

/* Sale Condition: written and read back, then read and written back */
static void check_sale_condition(void) {
  SaleCondition sent;
  SaleCondition got;
  uint8_t wire[4];
  uint8_t again[4];

  any_sale_condition(&sent);
  assert(encode_sale_condition(&sent, wire, 0) == 4);
  assert(decode_sale_condition(&got, wire, 0) == 4);
  equal_sale_condition(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_sale_condition(&got, wire, 0) == 4);
  assert(encode_sale_condition(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Report Message Short Form Message: 58 bytes ----------------------- */

/* Used to disseminate Trade Reports */
typedef struct {
  MessageInfo message_info;                     /* bytes 0 to 25 */
  uint8_t finra_timestamp[8];                   /* bytes 26 to 33 */
  uint8_t symbol_short[5];                      /* bytes 34 to 38 */
  uint8_t trade_id[8];                          /* bytes 39 to 46 */
  uint8_t trade_price_short[2];                 /* bytes 47 to 48 */
  uint8_t trade_volume_short[2];                /* bytes 49 to 50 */
  SaleCondition sale_condition;                 /* bytes 51 to 54 */
  uint8_t trade_through_exempt_flag;            /* byte 55 */
  uint8_t consolidated_price_change_indicator;  /* byte 56 */
  uint8_t participant_price_change_indicator;   /* byte 57 */
} TradeReportMessageShortFormMessage;

/* any Trade Report Message Short Form Message at all: every byte one the checker chooses */
static void any_trade_report_message_short_form_message(TradeReportMessageShortFormMessage *record) {
  any_message_info(&record->message_info);
  for (size_t i = 0; i < 8; i++) { record->finra_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_volume_short[i] = arbitrary(); }
  any_sale_condition(&record->sale_condition);
  record->trade_through_exempt_flag = arbitrary();
  record->consolidated_price_change_indicator = arbitrary();
  record->participant_price_change_indicator = arbitrary();
}

/* Trade Report Message Short Form Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_trade_report_message_short_form_message(const TradeReportMessageShortFormMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->finra_timestamp[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_volume_short[i]; }
  at = encode_sale_condition(&record->sale_condition, wire, at);
  wire[at++] = record->trade_through_exempt_flag;
  wire[at++] = record->consolidated_price_change_indicator;
  wire[at++] = record->participant_price_change_indicator;

  return at;
}

/* Trade Report Message Short Form Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_trade_report_message_short_form_message(TradeReportMessageShortFormMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 8; i++) { record->finra_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_volume_short[i] = wire[at++]; }
  at = decode_sale_condition(&record->sale_condition, wire, at);
  record->trade_through_exempt_flag = wire[at++];
  record->consolidated_price_change_indicator = wire[at++];
  record->participant_price_change_indicator = wire[at++];

  return at;
}

/* what was read of Trade Report Message Short Form Message is what was written, byte for byte */
static void equal_trade_report_message_short_form_message(const TradeReportMessageShortFormMessage *read, const TradeReportMessageShortFormMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
  for (size_t i = 0; i < 8; i++) { assert(read->finra_timestamp[i] == written->finra_timestamp[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_price_short[i] == written->trade_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_volume_short[i] == written->trade_volume_short[i]); }
  equal_sale_condition(&read->sale_condition, &written->sale_condition);
  assert(read->trade_through_exempt_flag == written->trade_through_exempt_flag);
  assert(read->consolidated_price_change_indicator == written->consolidated_price_change_indicator);
  assert(read->participant_price_change_indicator == written->participant_price_change_indicator);
}

/* Trade Report Message Short Form Message: written and read back, then read and written back */
static void check_trade_report_message_short_form_message(void) {
  TradeReportMessageShortFormMessage sent;
  TradeReportMessageShortFormMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_trade_report_message_short_form_message(&sent);
  assert(encode_trade_report_message_short_form_message(&sent, wire, 0) == 58);
  assert(decode_trade_report_message_short_form_message(&got, wire, 0) == 58);
  equal_trade_report_message_short_form_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_message_short_form_message(&got, wire, 0) == 58);
  assert(encode_trade_report_message_short_form_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Report Message Long Form Message: 74 bytes ------------------------ */

/* Used to disseminate Trade Reports */
typedef struct {
  MessageInfo message_info;                     /* bytes 0 to 25 */
  uint8_t finra_timestamp[8];                   /* bytes 26 to 33 */
  uint8_t symbol_long[11];                      /* bytes 34 to 44 */
  uint8_t trade_id[8];                          /* bytes 45 to 52 */
  uint8_t trade_price[8];                       /* bytes 53 to 60 */
  uint8_t trade_volume[4];                      /* bytes 61 to 64 */
  SaleCondition sale_condition;                 /* bytes 65 to 68 */
  uint8_t trade_through_exempt_flag;            /* byte 69 */
  uint8_t sellers_sale_days[2];                 /* bytes 70 to 71 */
  uint8_t consolidated_price_change_indicator;  /* byte 72 */
  uint8_t participant_price_change_indicator;   /* byte 73 */
} TradeReportMessageLongFormMessage;

/* any Trade Report Message Long Form Message at all: every byte one the checker chooses */
static void any_trade_report_message_long_form_message(TradeReportMessageLongFormMessage *record) {
  any_message_info(&record->message_info);
  for (size_t i = 0; i < 8; i++) { record->finra_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = arbitrary(); }
  any_sale_condition(&record->sale_condition);
  record->trade_through_exempt_flag = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->sellers_sale_days[i] = arbitrary(); }
  record->consolidated_price_change_indicator = arbitrary();
  record->participant_price_change_indicator = arbitrary();
}

/* Trade Report Message Long Form Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_trade_report_message_long_form_message(const TradeReportMessageLongFormMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->finra_timestamp[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_volume[i]; }
  at = encode_sale_condition(&record->sale_condition, wire, at);
  wire[at++] = record->trade_through_exempt_flag;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sellers_sale_days[i]; }
  wire[at++] = record->consolidated_price_change_indicator;
  wire[at++] = record->participant_price_change_indicator;

  return at;
}

/* Trade Report Message Long Form Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_trade_report_message_long_form_message(TradeReportMessageLongFormMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 8; i++) { record->finra_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = wire[at++]; }
  at = decode_sale_condition(&record->sale_condition, wire, at);
  record->trade_through_exempt_flag = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->sellers_sale_days[i] = wire[at++]; }
  record->consolidated_price_change_indicator = wire[at++];
  record->participant_price_change_indicator = wire[at++];

  return at;
}

/* what was read of Trade Report Message Long Form Message is what was written, byte for byte */
static void equal_trade_report_message_long_form_message(const TradeReportMessageLongFormMessage *read, const TradeReportMessageLongFormMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
  for (size_t i = 0; i < 8; i++) { assert(read->finra_timestamp[i] == written->finra_timestamp[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_volume[i] == written->trade_volume[i]); }
  equal_sale_condition(&read->sale_condition, &written->sale_condition);
  assert(read->trade_through_exempt_flag == written->trade_through_exempt_flag);
  for (size_t i = 0; i < 2; i++) { assert(read->sellers_sale_days[i] == written->sellers_sale_days[i]); }
  assert(read->consolidated_price_change_indicator == written->consolidated_price_change_indicator);
  assert(read->participant_price_change_indicator == written->participant_price_change_indicator);
}

/* Trade Report Message Long Form Message: written and read back, then read and written back */
static void check_trade_report_message_long_form_message(void) {
  TradeReportMessageLongFormMessage sent;
  TradeReportMessageLongFormMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_trade_report_message_long_form_message(&sent);
  assert(encode_trade_report_message_long_form_message(&sent, wire, 0) == 74);
  assert(decode_trade_report_message_long_form_message(&got, wire, 0) == 74);
  equal_trade_report_message_long_form_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_message_long_form_message(&got, wire, 0) == 74);
  assert(encode_trade_report_message_long_form_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Original Sale Condition: 4 bytes ---------------------------------------- */

/* Original Sale Condition */
typedef struct {
  uint8_t level_1;  /* byte 0 */
  uint8_t level_2;  /* byte 1 */
  uint8_t level_3;  /* byte 2 */
  uint8_t level_4;  /* byte 3 */
} OriginalSaleCondition;

/* any Original Sale Condition at all: every byte one the checker chooses */
static void any_original_sale_condition(OriginalSaleCondition *record) {
  record->level_1 = arbitrary();
  record->level_2 = arbitrary();
  record->level_3 = arbitrary();
  record->level_4 = arbitrary();
}

/* Original Sale Condition to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_original_sale_condition(const OriginalSaleCondition *record, uint8_t *wire, size_t at) {
  wire[at++] = record->level_1;
  wire[at++] = record->level_2;
  wire[at++] = record->level_3;
  wire[at++] = record->level_4;

  return at;
}

/* Original Sale Condition off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_original_sale_condition(OriginalSaleCondition *record, const uint8_t *wire, size_t at) {
  record->level_1 = wire[at++];
  record->level_2 = wire[at++];
  record->level_3 = wire[at++];
  record->level_4 = wire[at++];

  return at;
}

/* what was read of Original Sale Condition is what was written, byte for byte */
static void equal_original_sale_condition(const OriginalSaleCondition *read, const OriginalSaleCondition *written) {
  assert(read->level_1 == written->level_1);
  assert(read->level_2 == written->level_2);
  assert(read->level_3 == written->level_3);
  assert(read->level_4 == written->level_4);
}

/* Original Sale Condition: written and read back, then read and written back */
static void check_original_sale_condition(void) {
  OriginalSaleCondition sent;
  OriginalSaleCondition got;
  uint8_t wire[4];
  uint8_t again[4];

  any_original_sale_condition(&sent);
  assert(encode_original_sale_condition(&sent, wire, 0) == 4);
  assert(decode_original_sale_condition(&got, wire, 0) == 4);
  equal_original_sale_condition(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_original_sale_condition(&got, wire, 0) == 4);
  assert(encode_original_sale_condition(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Error Message: 139 bytes ----------------------------------- */

/* Used to disseminate trade cancels or errors */
typedef struct {
  MessageInfo message_info;                       /* bytes 0 to 25 */
  uint8_t finra_timestamp[8];                     /* bytes 26 to 33 */
  uint8_t symbol_long[11];                        /* bytes 34 to 44 */
  uint8_t trade_cancellation_type;                /* byte 45 */
  uint8_t original_trade_id[8];                   /* bytes 46 to 53 */
  uint8_t original_trade_price[8];                /* bytes 54 to 61 */
  uint8_t original_volume[4];                     /* bytes 62 to 65 */
  OriginalSaleCondition original_sale_condition;  /* bytes 66 to 69 */
  uint8_t original_trade_through_exempt_flag;     /* byte 70 */
  uint8_t original_sellers_sale_days[2];          /* bytes 71 to 72 */
  uint8_t consolidated_high_price[8];             /* bytes 73 to 80 */
  uint8_t consolidated_low_price[8];              /* bytes 81 to 88 */
  uint8_t consolidated_last_price[8];             /* bytes 89 to 96 */
  uint8_t consolidated_volume[8];                 /* bytes 97 to 104 */
  uint8_t consolidated_price_change_indicator;    /* byte 105 */
  uint8_t market_center_originator_id;            /* byte 106 */
  uint8_t market_participant_high_price[8];       /* bytes 107 to 114 */
  uint8_t market_participant_low_price[8];        /* bytes 115 to 122 */
  uint8_t market_participant_last_price[8];       /* bytes 123 to 130 */
  uint8_t market_participant_volume[8];           /* bytes 131 to 138 */
} TradeCancelErrorMessage;

/* any Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_trade_cancel_error_message(TradeCancelErrorMessage *record) {
  any_message_info(&record->message_info);
  for (size_t i = 0; i < 8; i++) { record->finra_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  record->trade_cancellation_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->original_trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_volume[i] = arbitrary(); }
  any_original_sale_condition(&record->original_sale_condition);
  record->original_trade_through_exempt_flag = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->original_sellers_sale_days[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_volume[i] = arbitrary(); }
  record->consolidated_price_change_indicator = arbitrary();
  record->market_center_originator_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->market_participant_high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->market_participant_low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->market_participant_last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->market_participant_volume[i] = arbitrary(); }
}

/* Trade Cancel Error Message to the wire: 139 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_error_message(const TradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->finra_timestamp[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->trade_cancellation_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_volume[i]; }
  at = encode_original_sale_condition(&record->original_sale_condition, wire, at);
  wire[at++] = record->original_trade_through_exempt_flag;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->original_sellers_sale_days[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_volume[i]; }
  wire[at++] = record->consolidated_price_change_indicator;
  wire[at++] = record->market_center_originator_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_participant_high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_participant_low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_participant_last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_participant_volume[i]; }

  return at;
}

/* Trade Cancel Error Message off the wire: 139 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_error_message(TradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 8; i++) { record->finra_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  record->trade_cancellation_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->original_trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_volume[i] = wire[at++]; }
  at = decode_original_sale_condition(&record->original_sale_condition, wire, at);
  record->original_trade_through_exempt_flag = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->original_sellers_sale_days[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_volume[i] = wire[at++]; }
  record->consolidated_price_change_indicator = wire[at++];
  record->market_center_originator_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->market_participant_high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->market_participant_low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->market_participant_last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->market_participant_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancel Error Message is what was written, byte for byte */
static void equal_trade_cancel_error_message(const TradeCancelErrorMessage *read, const TradeCancelErrorMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
  for (size_t i = 0; i < 8; i++) { assert(read->finra_timestamp[i] == written->finra_timestamp[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->trade_cancellation_type == written->trade_cancellation_type);
  for (size_t i = 0; i < 8; i++) { assert(read->original_trade_id[i] == written->original_trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_volume[i] == written->original_volume[i]); }
  equal_original_sale_condition(&read->original_sale_condition, &written->original_sale_condition);
  assert(read->original_trade_through_exempt_flag == written->original_trade_through_exempt_flag);
  for (size_t i = 0; i < 2; i++) { assert(read->original_sellers_sale_days[i] == written->original_sellers_sale_days[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_high_price[i] == written->consolidated_high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_low_price[i] == written->consolidated_low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_last_price[i] == written->consolidated_last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_volume[i] == written->consolidated_volume[i]); }
  assert(read->consolidated_price_change_indicator == written->consolidated_price_change_indicator);
  assert(read->market_center_originator_id == written->market_center_originator_id);
  for (size_t i = 0; i < 8; i++) { assert(read->market_participant_high_price[i] == written->market_participant_high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->market_participant_low_price[i] == written->market_participant_low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->market_participant_last_price[i] == written->market_participant_last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->market_participant_volume[i] == written->market_participant_volume[i]); }
}

/* Trade Cancel Error Message: written and read back, then read and written back */
static void check_trade_cancel_error_message(void) {
  TradeCancelErrorMessage sent;
  TradeCancelErrorMessage got;
  uint8_t wire[139];
  uint8_t again[139];

  any_trade_cancel_error_message(&sent);
  assert(encode_trade_cancel_error_message(&sent, wire, 0) == 139);
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 139);
  equal_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 139; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 139);
  assert(encode_trade_cancel_error_message(&got, again, 0) == 139);
  for (size_t i = 0; i < 139; i++) { assert(again[i] == wire[i]); }
}

/* ---- Corrected Sale Condition: 4 bytes --------------------------------------- */

/* Corrected Sale Condition */
typedef struct {
  uint8_t level_1;  /* byte 0 */
  uint8_t level_2;  /* byte 1 */
  uint8_t level_3;  /* byte 2 */
  uint8_t level_4;  /* byte 3 */
} CorrectedSaleCondition;

/* any Corrected Sale Condition at all: every byte one the checker chooses */
static void any_corrected_sale_condition(CorrectedSaleCondition *record) {
  record->level_1 = arbitrary();
  record->level_2 = arbitrary();
  record->level_3 = arbitrary();
  record->level_4 = arbitrary();
}

/* Corrected Sale Condition to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_corrected_sale_condition(const CorrectedSaleCondition *record, uint8_t *wire, size_t at) {
  wire[at++] = record->level_1;
  wire[at++] = record->level_2;
  wire[at++] = record->level_3;
  wire[at++] = record->level_4;

  return at;
}

/* Corrected Sale Condition off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_corrected_sale_condition(CorrectedSaleCondition *record, const uint8_t *wire, size_t at) {
  record->level_1 = wire[at++];
  record->level_2 = wire[at++];
  record->level_3 = wire[at++];
  record->level_4 = wire[at++];

  return at;
}

/* what was read of Corrected Sale Condition is what was written, byte for byte */
static void equal_corrected_sale_condition(const CorrectedSaleCondition *read, const CorrectedSaleCondition *written) {
  assert(read->level_1 == written->level_1);
  assert(read->level_2 == written->level_2);
  assert(read->level_3 == written->level_3);
  assert(read->level_4 == written->level_4);
}

/* Corrected Sale Condition: written and read back, then read and written back */
static void check_corrected_sale_condition(void) {
  CorrectedSaleCondition sent;
  CorrectedSaleCondition got;
  uint8_t wire[4];
  uint8_t again[4];

  any_corrected_sale_condition(&sent);
  assert(encode_corrected_sale_condition(&sent, wire, 0) == 4);
  assert(decode_corrected_sale_condition(&got, wire, 0) == 4);
  equal_corrected_sale_condition(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_corrected_sale_condition(&got, wire, 0) == 4);
  assert(encode_corrected_sale_condition(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 165 bytes ------------------------------------- */

/* Used to disseminate trade corrections */
typedef struct {
  MessageInfo message_info;                         /* bytes 0 to 25 */
  uint8_t finra_timestamp[8];                       /* bytes 26 to 33 */
  uint8_t symbol_long[11];                          /* bytes 34 to 44 */
  uint8_t original_trade_id[8];                     /* bytes 45 to 52 */
  uint8_t original_trade_price[8];                  /* bytes 53 to 60 */
  uint8_t original_volume[4];                       /* bytes 61 to 64 */
  OriginalSaleCondition original_sale_condition;    /* bytes 65 to 68 */
  uint8_t original_trade_through_exempt_flag;       /* byte 69 */
  uint8_t original_sellers_sale_days[2];            /* bytes 70 to 71 */
  uint8_t corrected_trade_id[8];                    /* bytes 72 to 79 */
  uint8_t corrected_trade_price[8];                 /* bytes 80 to 87 */
  uint8_t corrected_volume[4];                      /* bytes 88 to 91 */
  CorrectedSaleCondition corrected_sale_condition;  /* bytes 92 to 95 */
  uint8_t corrected_trade_through_exempt_flag;      /* byte 96 */
  uint8_t corrected_sellers_sale_days[2];           /* bytes 97 to 98 */
  uint8_t consolidated_high_price[8];               /* bytes 99 to 106 */
  uint8_t consolidated_low_price[8];                /* bytes 107 to 114 */
  uint8_t consolidated_last_price[8];               /* bytes 115 to 122 */
  uint8_t consolidated_volume[8];                   /* bytes 123 to 130 */
  uint8_t consolidated_price_change_indicator;      /* byte 131 */
  uint8_t market_center_originator_id;              /* byte 132 */
  uint8_t market_participant_high_price[8];         /* bytes 133 to 140 */
  uint8_t market_participant_low_price[8];          /* bytes 141 to 148 */
  uint8_t market_participant_last_price[8];         /* bytes 149 to 156 */
  uint8_t market_participant_volume[8];             /* bytes 157 to 164 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  any_message_info(&record->message_info);
  for (size_t i = 0; i < 8; i++) { record->finra_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_volume[i] = arbitrary(); }
  any_original_sale_condition(&record->original_sale_condition);
  record->original_trade_through_exempt_flag = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->original_sellers_sale_days[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_volume[i] = arbitrary(); }
  any_corrected_sale_condition(&record->corrected_sale_condition);
  record->corrected_trade_through_exempt_flag = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->corrected_sellers_sale_days[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_volume[i] = arbitrary(); }
  record->consolidated_price_change_indicator = arbitrary();
  record->market_center_originator_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->market_participant_high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->market_participant_low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->market_participant_last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->market_participant_volume[i] = arbitrary(); }
}

/* Trade Correction Message to the wire: 165 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->finra_timestamp[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_volume[i]; }
  at = encode_original_sale_condition(&record->original_sale_condition, wire, at);
  wire[at++] = record->original_trade_through_exempt_flag;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->original_sellers_sale_days[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_volume[i]; }
  at = encode_corrected_sale_condition(&record->corrected_sale_condition, wire, at);
  wire[at++] = record->corrected_trade_through_exempt_flag;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->corrected_sellers_sale_days[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_volume[i]; }
  wire[at++] = record->consolidated_price_change_indicator;
  wire[at++] = record->market_center_originator_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_participant_high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_participant_low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_participant_last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_participant_volume[i]; }

  return at;
}

/* Trade Correction Message off the wire: 165 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 8; i++) { record->finra_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_volume[i] = wire[at++]; }
  at = decode_original_sale_condition(&record->original_sale_condition, wire, at);
  record->original_trade_through_exempt_flag = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->original_sellers_sale_days[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_volume[i] = wire[at++]; }
  at = decode_corrected_sale_condition(&record->corrected_sale_condition, wire, at);
  record->corrected_trade_through_exempt_flag = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->corrected_sellers_sale_days[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_volume[i] = wire[at++]; }
  record->consolidated_price_change_indicator = wire[at++];
  record->market_center_originator_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->market_participant_high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->market_participant_low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->market_participant_last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->market_participant_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Correction Message is what was written, byte for byte */
static void equal_trade_correction_message(const TradeCorrectionMessage *read, const TradeCorrectionMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
  for (size_t i = 0; i < 8; i++) { assert(read->finra_timestamp[i] == written->finra_timestamp[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_trade_id[i] == written->original_trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_volume[i] == written->original_volume[i]); }
  equal_original_sale_condition(&read->original_sale_condition, &written->original_sale_condition);
  assert(read->original_trade_through_exempt_flag == written->original_trade_through_exempt_flag);
  for (size_t i = 0; i < 2; i++) { assert(read->original_sellers_sale_days[i] == written->original_sellers_sale_days[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_trade_id[i] == written->corrected_trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_trade_price[i] == written->corrected_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_volume[i] == written->corrected_volume[i]); }
  equal_corrected_sale_condition(&read->corrected_sale_condition, &written->corrected_sale_condition);
  assert(read->corrected_trade_through_exempt_flag == written->corrected_trade_through_exempt_flag);
  for (size_t i = 0; i < 2; i++) { assert(read->corrected_sellers_sale_days[i] == written->corrected_sellers_sale_days[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_high_price[i] == written->consolidated_high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_low_price[i] == written->consolidated_low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_last_price[i] == written->consolidated_last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_volume[i] == written->consolidated_volume[i]); }
  assert(read->consolidated_price_change_indicator == written->consolidated_price_change_indicator);
  assert(read->market_center_originator_id == written->market_center_originator_id);
  for (size_t i = 0; i < 8; i++) { assert(read->market_participant_high_price[i] == written->market_participant_high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->market_participant_low_price[i] == written->market_participant_low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->market_participant_last_price[i] == written->market_participant_last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->market_participant_volume[i] == written->market_participant_volume[i]); }
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[165];
  uint8_t again[165];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 165);
  assert(decode_trade_correction_message(&got, wire, 0) == 165);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 165; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 165);
  assert(encode_trade_correction_message(&got, again, 0) == 165);
  for (size_t i = 0; i < 165; i++) { assert(again[i] == wire[i]); }
}

/* ---- Prior Day As Of Trade Message: 81 bytes --------------------------------- */

/* Used to disseminate trade prior day as of action */
typedef struct {
  MessageInfo message_info;           /* bytes 0 to 25 */
  uint8_t finra_timestamp[8];         /* bytes 26 to 33 */
  uint8_t symbol_long[11];            /* bytes 34 to 44 */
  uint8_t trade_id[8];                /* bytes 45 to 52 */
  uint8_t trade_price[8];             /* bytes 53 to 60 */
  uint8_t trade_volume[4];            /* bytes 61 to 64 */
  SaleCondition sale_condition;       /* bytes 65 to 68 */
  uint8_t trade_through_exempt_flag;  /* byte 69 */
  uint8_t sellers_sale_days[2];       /* bytes 70 to 71 */
  uint8_t as_of_action;               /* byte 72 */
  uint8_t timestamp_of_trade[8];      /* bytes 73 to 80 */
} PriorDayAsOfTradeMessage;

/* any Prior Day As Of Trade Message at all: every byte one the checker chooses */
static void any_prior_day_as_of_trade_message(PriorDayAsOfTradeMessage *record) {
  any_message_info(&record->message_info);
  for (size_t i = 0; i < 8; i++) { record->finra_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = arbitrary(); }
  any_sale_condition(&record->sale_condition);
  record->trade_through_exempt_flag = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->sellers_sale_days[i] = arbitrary(); }
  record->as_of_action = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp_of_trade[i] = arbitrary(); }
}

/* Prior Day As Of Trade Message to the wire: 81 bytes from at, returning where the next byte goes */
static size_t encode_prior_day_as_of_trade_message(const PriorDayAsOfTradeMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->finra_timestamp[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_volume[i]; }
  at = encode_sale_condition(&record->sale_condition, wire, at);
  wire[at++] = record->trade_through_exempt_flag;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sellers_sale_days[i]; }
  wire[at++] = record->as_of_action;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_of_trade[i]; }

  return at;
}

/* Prior Day As Of Trade Message off the wire: 81 bytes from at, returning where the next byte lies */
static size_t decode_prior_day_as_of_trade_message(PriorDayAsOfTradeMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 8; i++) { record->finra_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = wire[at++]; }
  at = decode_sale_condition(&record->sale_condition, wire, at);
  record->trade_through_exempt_flag = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->sellers_sale_days[i] = wire[at++]; }
  record->as_of_action = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp_of_trade[i] = wire[at++]; }

  return at;
}

/* what was read of Prior Day As Of Trade Message is what was written, byte for byte */
static void equal_prior_day_as_of_trade_message(const PriorDayAsOfTradeMessage *read, const PriorDayAsOfTradeMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
  for (size_t i = 0; i < 8; i++) { assert(read->finra_timestamp[i] == written->finra_timestamp[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_volume[i] == written->trade_volume[i]); }
  equal_sale_condition(&read->sale_condition, &written->sale_condition);
  assert(read->trade_through_exempt_flag == written->trade_through_exempt_flag);
  for (size_t i = 0; i < 2; i++) { assert(read->sellers_sale_days[i] == written->sellers_sale_days[i]); }
  assert(read->as_of_action == written->as_of_action);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_of_trade[i] == written->timestamp_of_trade[i]); }
}

/* Prior Day As Of Trade Message: written and read back, then read and written back */
static void check_prior_day_as_of_trade_message(void) {
  PriorDayAsOfTradeMessage sent;
  PriorDayAsOfTradeMessage got;
  uint8_t wire[81];
  uint8_t again[81];

  any_prior_day_as_of_trade_message(&sent);
  assert(encode_prior_day_as_of_trade_message(&sent, wire, 0) == 81);
  assert(decode_prior_day_as_of_trade_message(&got, wire, 0) == 81);
  equal_prior_day_as_of_trade_message(&got, &sent);

  for (size_t i = 0; i < 81; i++) { wire[i] = arbitrary(); }
  assert(decode_prior_day_as_of_trade_message(&got, wire, 0) == 81);
  assert(encode_prior_day_as_of_trade_message(&got, again, 0) == 81);
  for (size_t i = 0; i < 81; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cross Sro Trading Action Message: 56 bytes ------------------------------ */

/* This fixed format message will be used to inform subscribers of trading actions – such as halts, pauses, quotation resumptions and trading resumptions */
typedef struct {
  MessageInfo message_info;                   /* bytes 0 to 25 */
  uint8_t symbol_long[11];                    /* bytes 26 to 36 */
  uint8_t trading_action_code;                /* byte 37 */
  uint8_t trading_action_sequence_number[4];  /* bytes 38 to 41 */
  uint8_t action_timestamp[8];                /* bytes 42 to 49 */
  uint8_t trading_action_reason[6];           /* bytes 50 to 55 */
} CrossSroTradingActionMessage;

/* any Cross Sro Trading Action Message at all: every byte one the checker chooses */
static void any_cross_sro_trading_action_message(CrossSroTradingActionMessage *record) {
  any_message_info(&record->message_info);
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  record->trading_action_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trading_action_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->action_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->trading_action_reason[i] = arbitrary(); }
}

/* Cross Sro Trading Action Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_cross_sro_trading_action_message(const CrossSroTradingActionMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->trading_action_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_action_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->action_timestamp[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trading_action_reason[i]; }

  return at;
}

/* Cross Sro Trading Action Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_cross_sro_trading_action_message(CrossSroTradingActionMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  record->trading_action_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trading_action_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->action_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->trading_action_reason[i] = wire[at++]; }

  return at;
}

/* what was read of Cross Sro Trading Action Message is what was written, byte for byte */
static void equal_cross_sro_trading_action_message(const CrossSroTradingActionMessage *read, const CrossSroTradingActionMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->trading_action_code == written->trading_action_code);
  for (size_t i = 0; i < 4; i++) { assert(read->trading_action_sequence_number[i] == written->trading_action_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->action_timestamp[i] == written->action_timestamp[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->trading_action_reason[i] == written->trading_action_reason[i]); }
}

/* Cross Sro Trading Action Message: written and read back, then read and written back */
static void check_cross_sro_trading_action_message(void) {
  CrossSroTradingActionMessage sent;
  CrossSroTradingActionMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_cross_sro_trading_action_message(&sent);
  assert(encode_cross_sro_trading_action_message(&sent, wire, 0) == 56);
  assert(decode_cross_sro_trading_action_message(&got, wire, 0) == 56);
  equal_cross_sro_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_cross_sro_trading_action_message(&got, wire, 0) == 56);
  assert(encode_cross_sro_trading_action_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Center Trading Action Message: 47 bytes -------------------------- */

/* This fixed format message will inform UTP data feed subscribers of when a UTP participant invokes or releases a market center-specific trading halt for a NASDAQ-listed security. */
typedef struct {
  MessageInfo message_info;          /* bytes 0 to 25 */
  uint8_t symbol_long[11];           /* bytes 26 to 36 */
  uint8_t trading_action_code;       /* byte 37 */
  uint8_t action_timestamp[8];       /* bytes 38 to 45 */
  uint8_t market_center_identifier;  /* byte 46 */
} MarketCenterTradingActionMessage;

/* any Market Center Trading Action Message at all: every byte one the checker chooses */
static void any_market_center_trading_action_message(MarketCenterTradingActionMessage *record) {
  any_message_info(&record->message_info);
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  record->trading_action_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->action_timestamp[i] = arbitrary(); }
  record->market_center_identifier = arbitrary();
}

/* Market Center Trading Action Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_market_center_trading_action_message(const MarketCenterTradingActionMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->trading_action_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->action_timestamp[i]; }
  wire[at++] = record->market_center_identifier;

  return at;
}

/* Market Center Trading Action Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_market_center_trading_action_message(MarketCenterTradingActionMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  record->trading_action_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->action_timestamp[i] = wire[at++]; }
  record->market_center_identifier = wire[at++];

  return at;
}

/* what was read of Market Center Trading Action Message is what was written, byte for byte */
static void equal_market_center_trading_action_message(const MarketCenterTradingActionMessage *read, const MarketCenterTradingActionMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->trading_action_code == written->trading_action_code);
  for (size_t i = 0; i < 8; i++) { assert(read->action_timestamp[i] == written->action_timestamp[i]); }
  assert(read->market_center_identifier == written->market_center_identifier);
}

/* Market Center Trading Action Message: written and read back, then read and written back */
static void check_market_center_trading_action_message(void) {
  MarketCenterTradingActionMessage sent;
  MarketCenterTradingActionMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_market_center_trading_action_message(&sent);
  assert(encode_market_center_trading_action_message(&sent, wire, 0) == 47);
  assert(decode_market_center_trading_action_message(&got, wire, 0) == 47);
  equal_market_center_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_market_center_trading_action_message(&got, wire, 0) == 47);
  assert(encode_market_center_trading_action_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Issue Symbol Directory Message: 87 bytes -------------------------------- */

/* General Administrative */
typedef struct {
  MessageInfo message_info;                /* bytes 0 to 25 */
  uint8_t symbol_long[11];                 /* bytes 26 to 36 */
  uint8_t old_symbol[11];                  /* bytes 37 to 47 */
  uint8_t issue_name[30];                  /* bytes 48 to 77 */
  uint8_t issue_type;                      /* byte 78 */
  uint8_t issue_subtype[2];                /* bytes 79 to 80 */
  uint8_t market_tier;                     /* byte 81 */
  uint8_t authenticity;                    /* byte 82 */
  uint8_t short_sale_threshold_indicator;  /* byte 83 */
  uint8_t round_lot_size[2];               /* bytes 84 to 85 */
  uint8_t financial_status_indicator;      /* byte 86 */
} IssueSymbolDirectoryMessage;

/* any Issue Symbol Directory Message at all: every byte one the checker chooses */
static void any_issue_symbol_directory_message(IssueSymbolDirectoryMessage *record) {
  any_message_info(&record->message_info);
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->old_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->issue_name[i] = arbitrary(); }
  record->issue_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->issue_subtype[i] = arbitrary(); }
  record->market_tier = arbitrary();
  record->authenticity = arbitrary();
  record->short_sale_threshold_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->round_lot_size[i] = arbitrary(); }
  record->financial_status_indicator = arbitrary();
}

/* Issue Symbol Directory Message to the wire: 87 bytes from at, returning where the next byte goes */
static size_t encode_issue_symbol_directory_message(const IssueSymbolDirectoryMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->old_symbol[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->issue_name[i]; }
  wire[at++] = record->issue_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->issue_subtype[i]; }
  wire[at++] = record->market_tier;
  wire[at++] = record->authenticity;
  wire[at++] = record->short_sale_threshold_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->round_lot_size[i]; }
  wire[at++] = record->financial_status_indicator;

  return at;
}

/* Issue Symbol Directory Message off the wire: 87 bytes from at, returning where the next byte lies */
static size_t decode_issue_symbol_directory_message(IssueSymbolDirectoryMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->old_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->issue_name[i] = wire[at++]; }
  record->issue_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->issue_subtype[i] = wire[at++]; }
  record->market_tier = wire[at++];
  record->authenticity = wire[at++];
  record->short_sale_threshold_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->round_lot_size[i] = wire[at++]; }
  record->financial_status_indicator = wire[at++];

  return at;
}

/* what was read of Issue Symbol Directory Message is what was written, byte for byte */
static void equal_issue_symbol_directory_message(const IssueSymbolDirectoryMessage *read, const IssueSymbolDirectoryMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->old_symbol[i] == written->old_symbol[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->issue_name[i] == written->issue_name[i]); }
  assert(read->issue_type == written->issue_type);
  for (size_t i = 0; i < 2; i++) { assert(read->issue_subtype[i] == written->issue_subtype[i]); }
  assert(read->market_tier == written->market_tier);
  assert(read->authenticity == written->authenticity);
  assert(read->short_sale_threshold_indicator == written->short_sale_threshold_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->round_lot_size[i] == written->round_lot_size[i]); }
  assert(read->financial_status_indicator == written->financial_status_indicator);
}

/* Issue Symbol Directory Message: written and read back, then read and written back */
static void check_issue_symbol_directory_message(void) {
  IssueSymbolDirectoryMessage sent;
  IssueSymbolDirectoryMessage got;
  uint8_t wire[87];
  uint8_t again[87];

  any_issue_symbol_directory_message(&sent);
  assert(encode_issue_symbol_directory_message(&sent, wire, 0) == 87);
  assert(decode_issue_symbol_directory_message(&got, wire, 0) == 87);
  equal_issue_symbol_directory_message(&got, &sent);

  for (size_t i = 0; i < 87; i++) { wire[i] = arbitrary(); }
  assert(decode_issue_symbol_directory_message(&got, wire, 0) == 87);
  assert(encode_issue_symbol_directory_message(&got, again, 0) == 87);
  for (size_t i = 0; i < 87; i++) { assert(again[i] == wire[i]); }
}

/* ---- Regulation Sho Short Sale Price Test Restricted Indicator Message: 32 bytes ---- */

/* Used to disseminate quotation data for NASDAQ listed securities */
typedef struct {
  MessageInfo message_info;  /* bytes 0 to 25 */
  uint8_t symbol_short[5];   /* bytes 26 to 30 */
  uint8_t reg_sho_action;    /* byte 31 */
} RegulationShoShortSalePriceTestRestrictedIndicatorMessage;

/* any Regulation Sho Short Sale Price Test Restricted Indicator Message at all: every byte one the checker chooses */
static void any_regulation_sho_short_sale_price_test_restricted_indicator_message(RegulationShoShortSalePriceTestRestrictedIndicatorMessage *record) {
  any_message_info(&record->message_info);
  for (size_t i = 0; i < 5; i++) { record->symbol_short[i] = arbitrary(); }
  record->reg_sho_action = arbitrary();
}

/* Regulation Sho Short Sale Price Test Restricted Indicator Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_regulation_sho_short_sale_price_test_restricted_indicator_message(const RegulationShoShortSalePriceTestRestrictedIndicatorMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->symbol_short[i]; }
  wire[at++] = record->reg_sho_action;

  return at;
}

/* Regulation Sho Short Sale Price Test Restricted Indicator Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_regulation_sho_short_sale_price_test_restricted_indicator_message(RegulationShoShortSalePriceTestRestrictedIndicatorMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 5; i++) { record->symbol_short[i] = wire[at++]; }
  record->reg_sho_action = wire[at++];

  return at;
}

/* what was read of Regulation Sho Short Sale Price Test Restricted Indicator Message is what was written, byte for byte */
static void equal_regulation_sho_short_sale_price_test_restricted_indicator_message(const RegulationShoShortSalePriceTestRestrictedIndicatorMessage *read, const RegulationShoShortSalePriceTestRestrictedIndicatorMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
  for (size_t i = 0; i < 5; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  assert(read->reg_sho_action == written->reg_sho_action);
}

/* Regulation Sho Short Sale Price Test Restricted Indicator Message: written and read back, then read and written back */
static void check_regulation_sho_short_sale_price_test_restricted_indicator_message(void) {
  RegulationShoShortSalePriceTestRestrictedIndicatorMessage sent;
  RegulationShoShortSalePriceTestRestrictedIndicatorMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_regulation_sho_short_sale_price_test_restricted_indicator_message(&sent);
  assert(encode_regulation_sho_short_sale_price_test_restricted_indicator_message(&sent, wire, 0) == 32);
  assert(decode_regulation_sho_short_sale_price_test_restricted_indicator_message(&got, wire, 0) == 32);
  equal_regulation_sho_short_sale_price_test_restricted_indicator_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_regulation_sho_short_sale_price_test_restricted_indicator_message(&got, wire, 0) == 32);
  assert(encode_regulation_sho_short_sale_price_test_restricted_indicator_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Limit Up Limit Down Price Band Message: 62 bytes ------------------------ */

/* Designed to prevent trades in individual NMS Stocks from occurring outside of specified Upper and Lower Limit Price Bands */
typedef struct {
  MessageInfo message_info;           /* bytes 0 to 25 */
  uint8_t symbol_long[11];            /* bytes 26 to 36 */
  uint8_t luld_price_band_indicator;  /* byte 37 */
  uint8_t luld_timestamp[8];          /* bytes 38 to 45 */
  uint8_t limit_down_price[8];        /* bytes 46 to 53 */
  uint8_t limit_up_price[8];          /* bytes 54 to 61 */
} LimitUpLimitDownPriceBandMessage;

/* any Limit Up Limit Down Price Band Message at all: every byte one the checker chooses */
static void any_limit_up_limit_down_price_band_message(LimitUpLimitDownPriceBandMessage *record) {
  any_message_info(&record->message_info);
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  record->luld_price_band_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->luld_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->limit_down_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->limit_up_price[i] = arbitrary(); }
}

/* Limit Up Limit Down Price Band Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_limit_up_limit_down_price_band_message(const LimitUpLimitDownPriceBandMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->luld_price_band_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->luld_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->limit_down_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->limit_up_price[i]; }

  return at;
}

/* Limit Up Limit Down Price Band Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_limit_up_limit_down_price_band_message(LimitUpLimitDownPriceBandMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  record->luld_price_band_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->luld_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->limit_down_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->limit_up_price[i] = wire[at++]; }

  return at;
}

/* what was read of Limit Up Limit Down Price Band Message is what was written, byte for byte */
static void equal_limit_up_limit_down_price_band_message(const LimitUpLimitDownPriceBandMessage *read, const LimitUpLimitDownPriceBandMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->luld_price_band_indicator == written->luld_price_band_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->luld_timestamp[i] == written->luld_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->limit_down_price[i] == written->limit_down_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->limit_up_price[i] == written->limit_up_price[i]); }
}

/* Limit Up Limit Down Price Band Message: written and read back, then read and written back */
static void check_limit_up_limit_down_price_band_message(void) {
  LimitUpLimitDownPriceBandMessage sent;
  LimitUpLimitDownPriceBandMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_limit_up_limit_down_price_band_message(&sent);
  assert(encode_limit_up_limit_down_price_band_message(&sent, wire, 0) == 62);
  assert(decode_limit_up_limit_down_price_band_message(&got, wire, 0) == 62);
  equal_limit_up_limit_down_price_band_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_limit_up_limit_down_price_band_message(&got, wire, 0) == 62);
  assert(encode_limit_up_limit_down_price_band_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Wide Circuit Breaker Decline Level Message: 50 bytes ------------- */

/* A Market Wide Circuit Breaker (MWCB) Level message will inform participants and the UTP data recipients what the daily MWCB breach points are set to for the current trading day */
typedef struct {
  MessageInfo message_info;  /* bytes 0 to 25 */
  uint8_t mwcb_level_1[8];   /* bytes 26 to 33 */
  uint8_t mwcb_level_2[8];   /* bytes 34 to 41 */
  uint8_t mwcb_level_3[8];   /* bytes 42 to 49 */
} MarketWideCircuitBreakerDeclineLevelMessage;

/* any Market Wide Circuit Breaker Decline Level Message at all: every byte one the checker chooses */
static void any_market_wide_circuit_breaker_decline_level_message(MarketWideCircuitBreakerDeclineLevelMessage *record) {
  any_message_info(&record->message_info);
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_3[i] = arbitrary(); }
}

/* Market Wide Circuit Breaker Decline Level Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_market_wide_circuit_breaker_decline_level_message(const MarketWideCircuitBreakerDeclineLevelMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mwcb_level_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mwcb_level_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mwcb_level_3[i]; }

  return at;
}

/* Market Wide Circuit Breaker Decline Level Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_market_wide_circuit_breaker_decline_level_message(MarketWideCircuitBreakerDeclineLevelMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_3[i] = wire[at++]; }

  return at;
}

/* what was read of Market Wide Circuit Breaker Decline Level Message is what was written, byte for byte */
static void equal_market_wide_circuit_breaker_decline_level_message(const MarketWideCircuitBreakerDeclineLevelMessage *read, const MarketWideCircuitBreakerDeclineLevelMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
  for (size_t i = 0; i < 8; i++) { assert(read->mwcb_level_1[i] == written->mwcb_level_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mwcb_level_2[i] == written->mwcb_level_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mwcb_level_3[i] == written->mwcb_level_3[i]); }
}

/* Market Wide Circuit Breaker Decline Level Message: written and read back, then read and written back */
static void check_market_wide_circuit_breaker_decline_level_message(void) {
  MarketWideCircuitBreakerDeclineLevelMessage sent;
  MarketWideCircuitBreakerDeclineLevelMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_market_wide_circuit_breaker_decline_level_message(&sent);
  assert(encode_market_wide_circuit_breaker_decline_level_message(&sent, wire, 0) == 50);
  assert(decode_market_wide_circuit_breaker_decline_level_message(&got, wire, 0) == 50);
  equal_market_wide_circuit_breaker_decline_level_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_market_wide_circuit_breaker_decline_level_message(&got, wire, 0) == 50);
  assert(encode_market_wide_circuit_breaker_decline_level_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Wide Circuit Breaker Status Message: 27 bytes -------------------- */

/* A Market Wide Circuit Breaker (MWCB) Status message will inform participants and the UTP data recipients when a MWCB has breached one of the established levels. */
typedef struct {
  MessageInfo message_info;             /* bytes 0 to 25 */
  uint8_t mwcb_status_level_indicator;  /* byte 26 */
} MarketWideCircuitBreakerStatusMessage;

/* any Market Wide Circuit Breaker Status Message at all: every byte one the checker chooses */
static void any_market_wide_circuit_breaker_status_message(MarketWideCircuitBreakerStatusMessage *record) {
  any_message_info(&record->message_info);
  record->mwcb_status_level_indicator = arbitrary();
}

/* Market Wide Circuit Breaker Status Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_market_wide_circuit_breaker_status_message(const MarketWideCircuitBreakerStatusMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);
  wire[at++] = record->mwcb_status_level_indicator;

  return at;
}

/* Market Wide Circuit Breaker Status Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_market_wide_circuit_breaker_status_message(MarketWideCircuitBreakerStatusMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);
  record->mwcb_status_level_indicator = wire[at++];

  return at;
}

/* what was read of Market Wide Circuit Breaker Status Message is what was written, byte for byte */
static void equal_market_wide_circuit_breaker_status_message(const MarketWideCircuitBreakerStatusMessage *read, const MarketWideCircuitBreakerStatusMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
  assert(read->mwcb_status_level_indicator == written->mwcb_status_level_indicator);
}

/* Market Wide Circuit Breaker Status Message: written and read back, then read and written back */
static void check_market_wide_circuit_breaker_status_message(void) {
  MarketWideCircuitBreakerStatusMessage sent;
  MarketWideCircuitBreakerStatusMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_market_wide_circuit_breaker_status_message(&sent);
  assert(encode_market_wide_circuit_breaker_status_message(&sent, wire, 0) == 27);
  assert(decode_market_wide_circuit_breaker_status_message(&got, wire, 0) == 27);
  equal_market_wide_circuit_breaker_status_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_market_wide_circuit_breaker_status_message(&got, wire, 0) == 27);
  assert(encode_market_wide_circuit_breaker_status_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Collar Message: 66 bytes ---------------------------------------- */

/* Primary markets using an automated reopening will calculate new Auction Collars, in compliance with rules around prices for re-opening, when applicable and publish this new Auction Collar Message */
typedef struct {
  MessageInfo message_info;                   /* bytes 0 to 25 */
  uint8_t symbol_long[11];                    /* bytes 26 to 36 */
  uint8_t trading_action_sequence_number[4];  /* bytes 37 to 40 */
  uint8_t collar_reference_price[8];          /* bytes 41 to 48 */
  uint8_t collar_up_price[8];                 /* bytes 49 to 56 */
  uint8_t collar_down_price[8];               /* bytes 57 to 64 */
  uint8_t collar_extension_indicator;         /* byte 65 */
} AuctionCollarMessage;

/* any Auction Collar Message at all: every byte one the checker chooses */
static void any_auction_collar_message(AuctionCollarMessage *record) {
  any_message_info(&record->message_info);
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_action_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->collar_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->collar_up_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->collar_down_price[i] = arbitrary(); }
  record->collar_extension_indicator = arbitrary();
}

/* Auction Collar Message to the wire: 66 bytes from at, returning where the next byte goes */
static size_t encode_auction_collar_message(const AuctionCollarMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_action_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->collar_reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->collar_up_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->collar_down_price[i]; }
  wire[at++] = record->collar_extension_indicator;

  return at;
}

/* Auction Collar Message off the wire: 66 bytes from at, returning where the next byte lies */
static size_t decode_auction_collar_message(AuctionCollarMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);
  for (size_t i = 0; i < 11; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_action_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->collar_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->collar_up_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->collar_down_price[i] = wire[at++]; }
  record->collar_extension_indicator = wire[at++];

  return at;
}

/* what was read of Auction Collar Message is what was written, byte for byte */
static void equal_auction_collar_message(const AuctionCollarMessage *read, const AuctionCollarMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
  for (size_t i = 0; i < 11; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_action_sequence_number[i] == written->trading_action_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->collar_reference_price[i] == written->collar_reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->collar_up_price[i] == written->collar_up_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->collar_down_price[i] == written->collar_down_price[i]); }
  assert(read->collar_extension_indicator == written->collar_extension_indicator);
}

/* Auction Collar Message: written and read back, then read and written back */
static void check_auction_collar_message(void) {
  AuctionCollarMessage sent;
  AuctionCollarMessage got;
  uint8_t wire[66];
  uint8_t again[66];

  any_auction_collar_message(&sent);
  assert(encode_auction_collar_message(&sent, wire, 0) == 66);
  assert(decode_auction_collar_message(&got, wire, 0) == 66);
  equal_auction_collar_message(&got, &sent);

  for (size_t i = 0; i < 66; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_collar_message(&got, wire, 0) == 66);
  assert(encode_auction_collar_message(&got, again, 0) == 66);
  for (size_t i = 0; i < 66; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Day Message: 26 bytes ------------------------------------------ */

/* The Start of Day control message signifies the beginning of each operational cycle for SIP Processing */
typedef struct {
  MessageInfo message_info;  /* bytes 0 to 25 */
} StartOfDayMessage;

/* any Start Of Day Message at all: every byte one the checker chooses */
static void any_start_of_day_message(StartOfDayMessage *record) {
  any_message_info(&record->message_info);
}

/* Start Of Day Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_start_of_day_message(const StartOfDayMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);

  return at;
}

/* Start Of Day Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_start_of_day_message(StartOfDayMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);

  return at;
}

/* what was read of Start Of Day Message is what was written, byte for byte */
static void equal_start_of_day_message(const StartOfDayMessage *read, const StartOfDayMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
}

/* Start Of Day Message: written and read back, then read and written back */
static void check_start_of_day_message(void) {
  StartOfDayMessage sent;
  StartOfDayMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_start_of_day_message(&sent);
  assert(encode_start_of_day_message(&sent, wire, 0) == 26);
  assert(decode_start_of_day_message(&got, wire, 0) == 26);
  equal_start_of_day_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_day_message(&got, wire, 0) == 26);
  assert(encode_start_of_day_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Day Message: 26 bytes -------------------------------------------- */

/* The End of Day control message signals the end of active message dissemination for the UTP SIP operational cycle */
typedef struct {
  MessageInfo message_info;  /* bytes 0 to 25 */
} EndOfDayMessage;

/* any End Of Day Message at all: every byte one the checker chooses */
static void any_end_of_day_message(EndOfDayMessage *record) {
  any_message_info(&record->message_info);
}

/* End Of Day Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_end_of_day_message(const EndOfDayMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);

  return at;
}

/* End Of Day Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_end_of_day_message(EndOfDayMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);

  return at;
}

/* what was read of End Of Day Message is what was written, byte for byte */
static void equal_end_of_day_message(const EndOfDayMessage *read, const EndOfDayMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
}

/* End Of Day Message: written and read back, then read and written back */
static void check_end_of_day_message(void) {
  EndOfDayMessage sent;
  EndOfDayMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_end_of_day_message(&sent);
  assert(encode_end_of_day_message(&sent, wire, 0) == 26);
  assert(decode_end_of_day_message(&got, wire, 0) == 26);
  equal_end_of_day_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_day_message(&got, wire, 0) == 26);
  assert(encode_end_of_day_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Session Open Message: 26 bytes ----------------------------------- */

/* The Market Session Open Control Message signifies the opening of market systems for the session indicated in the Message Header */
typedef struct {
  MessageInfo message_info;  /* bytes 0 to 25 */
} MarketSessionOpenMessage;

/* any Market Session Open Message at all: every byte one the checker chooses */
static void any_market_session_open_message(MarketSessionOpenMessage *record) {
  any_message_info(&record->message_info);
}

/* Market Session Open Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_market_session_open_message(const MarketSessionOpenMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);

  return at;
}

/* Market Session Open Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_market_session_open_message(MarketSessionOpenMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);

  return at;
}

/* what was read of Market Session Open Message is what was written, byte for byte */
static void equal_market_session_open_message(const MarketSessionOpenMessage *read, const MarketSessionOpenMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
}

/* Market Session Open Message: written and read back, then read and written back */
static void check_market_session_open_message(void) {
  MarketSessionOpenMessage sent;
  MarketSessionOpenMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_market_session_open_message(&sent);
  assert(encode_market_session_open_message(&sent, wire, 0) == 26);
  assert(decode_market_session_open_message(&got, wire, 0) == 26);
  equal_market_session_open_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_market_session_open_message(&got, wire, 0) == 26);
  assert(encode_market_session_open_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Session Close Message: 26 bytes ---------------------------------- */

/* The Session Close Control Message signals the closing of market systems for the session indicated in the Message Header */
typedef struct {
  MessageInfo message_info;  /* bytes 0 to 25 */
} MarketSessionCloseMessage;

/* any Market Session Close Message at all: every byte one the checker chooses */
static void any_market_session_close_message(MarketSessionCloseMessage *record) {
  any_message_info(&record->message_info);
}

/* Market Session Close Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_market_session_close_message(const MarketSessionCloseMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);

  return at;
}

/* Market Session Close Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_market_session_close_message(MarketSessionCloseMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);

  return at;
}

/* what was read of Market Session Close Message is what was written, byte for byte */
static void equal_market_session_close_message(const MarketSessionCloseMessage *read, const MarketSessionCloseMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
}

/* Market Session Close Message: written and read back, then read and written back */
static void check_market_session_close_message(void) {
  MarketSessionCloseMessage sent;
  MarketSessionCloseMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_market_session_close_message(&sent);
  assert(encode_market_session_close_message(&sent, wire, 0) == 26);
  assert(decode_market_session_close_message(&got, wire, 0) == 26);
  equal_market_session_close_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_market_session_close_message(&got, wire, 0) == 26);
  assert(encode_market_session_close_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Transmissions Message: 26 bytes ---------------------------------- */

/* The End of Transmissions Message signals that there will be no further transmissions of data sent through the UTP SIP line */
typedef struct {
  MessageInfo message_info;  /* bytes 0 to 25 */
} EndOfTransmissionsMessage;

/* any End Of Transmissions Message at all: every byte one the checker chooses */
static void any_end_of_transmissions_message(EndOfTransmissionsMessage *record) {
  any_message_info(&record->message_info);
}

/* End Of Transmissions Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_end_of_transmissions_message(const EndOfTransmissionsMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);

  return at;
}

/* End Of Transmissions Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_end_of_transmissions_message(EndOfTransmissionsMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);

  return at;
}

/* what was read of End Of Transmissions Message is what was written, byte for byte */
static void equal_end_of_transmissions_message(const EndOfTransmissionsMessage *read, const EndOfTransmissionsMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
}

/* End Of Transmissions Message: written and read back, then read and written back */
static void check_end_of_transmissions_message(void) {
  EndOfTransmissionsMessage sent;
  EndOfTransmissionsMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_end_of_transmissions_message(&sent);
  assert(encode_end_of_transmissions_message(&sent, wire, 0) == 26);
  assert(decode_end_of_transmissions_message(&got, wire, 0) == 26);
  equal_end_of_transmissions_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_transmissions_message(&got, wire, 0) == 26);
  assert(encode_end_of_transmissions_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Trade Reporting Message: 26 bytes -------------------------------- */

/* The End of Trade Reporting Control Message signals that SIP has completed its trade entry eligibility and that no further data will be accepted by the UTP SIP for the market session */
typedef struct {
  MessageInfo message_info;  /* bytes 0 to 25 */
} EndOfTradeReportingMessage;

/* any End Of Trade Reporting Message at all: every byte one the checker chooses */
static void any_end_of_trade_reporting_message(EndOfTradeReportingMessage *record) {
  any_message_info(&record->message_info);
}

/* End Of Trade Reporting Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_end_of_trade_reporting_message(const EndOfTradeReportingMessage *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);

  return at;
}

/* End Of Trade Reporting Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_end_of_trade_reporting_message(EndOfTradeReportingMessage *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);

  return at;
}

/* what was read of End Of Trade Reporting Message is what was written, byte for byte */
static void equal_end_of_trade_reporting_message(const EndOfTradeReportingMessage *read, const EndOfTradeReportingMessage *written) {
  equal_message_info(&read->message_info, &written->message_info);
}

/* End Of Trade Reporting Message: written and read back, then read and written back */
static void check_end_of_trade_reporting_message(void) {
  EndOfTradeReportingMessage sent;
  EndOfTradeReportingMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_end_of_trade_reporting_message(&sent);
  assert(encode_end_of_trade_reporting_message(&sent, wire, 0) == 26);
  assert(decode_end_of_trade_reporting_message(&got, wire, 0) == 26);
  equal_end_of_trade_reporting_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_trade_reporting_message(&got, wire, 0) == 26);
  assert(encode_end_of_trade_reporting_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Consolidated Last Sale Eligibility: 26 bytes --------------------- */

/* The End of Consolidated Last Sale Eligibility control message signals the closing of the trade-reporting window for consolidated last sale calculation eligibility */
typedef struct {
  MessageInfo message_info;  /* bytes 0 to 25 */
} EndOfConsolidatedLastSaleEligibility;

/* any End Of Consolidated Last Sale Eligibility at all: every byte one the checker chooses */
static void any_end_of_consolidated_last_sale_eligibility(EndOfConsolidatedLastSaleEligibility *record) {
  any_message_info(&record->message_info);
}

/* End Of Consolidated Last Sale Eligibility to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_end_of_consolidated_last_sale_eligibility(const EndOfConsolidatedLastSaleEligibility *record, uint8_t *wire, size_t at) {
  at = encode_message_info(&record->message_info, wire, at);

  return at;
}

/* End Of Consolidated Last Sale Eligibility off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_end_of_consolidated_last_sale_eligibility(EndOfConsolidatedLastSaleEligibility *record, const uint8_t *wire, size_t at) {
  at = decode_message_info(&record->message_info, wire, at);

  return at;
}

/* what was read of End Of Consolidated Last Sale Eligibility is what was written, byte for byte */
static void equal_end_of_consolidated_last_sale_eligibility(const EndOfConsolidatedLastSaleEligibility *read, const EndOfConsolidatedLastSaleEligibility *written) {
  equal_message_info(&read->message_info, &written->message_info);
}

/* End Of Consolidated Last Sale Eligibility: written and read back, then read and written back */
static void check_end_of_consolidated_last_sale_eligibility(void) {
  EndOfConsolidatedLastSaleEligibility sent;
  EndOfConsolidatedLastSaleEligibility got;
  uint8_t wire[26];
  uint8_t again[26];

  any_end_of_consolidated_last_sale_eligibility(&sent);
  assert(encode_end_of_consolidated_last_sale_eligibility(&sent, wire, 0) == 26);
  assert(decode_end_of_consolidated_last_sale_eligibility(&got, wire, 0) == 26);
  equal_end_of_consolidated_last_sale_eligibility(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_consolidated_last_sale_eligibility(&got, wire, 0) == 26);
  assert(encode_end_of_consolidated_last_sale_eligibility(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_message_info();
  check_sale_condition();
  check_trade_report_message_short_form_message();
  check_trade_report_message_long_form_message();
  check_original_sale_condition();
  check_trade_cancel_error_message();
  check_corrected_sale_condition();
  check_trade_correction_message();
  check_prior_day_as_of_trade_message();
  check_cross_sro_trading_action_message();
  check_market_center_trading_action_message();
  check_issue_symbol_directory_message();
  check_regulation_sho_short_sale_price_test_restricted_indicator_message();
  check_limit_up_limit_down_price_band_message();
  check_market_wide_circuit_breaker_decline_level_message();
  check_market_wide_circuit_breaker_status_message();
  check_auction_collar_message();
  check_start_of_day_message();
  check_end_of_day_message();
  check_market_session_open_message();
  check_market_session_close_message();
  check_end_of_transmissions_message();
  check_end_of_trade_reporting_message();
  check_end_of_consolidated_last_sale_eligibility();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
