// nasdaq/ntxequities/lastsale/NtxEquities_LastSale_v2_1.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Last Sale
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
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t timestamp[6];        /* bytes 2 to 7 */
  uint8_t event_code;          /* byte 8 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
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

/* ---- Trade Report Message: 40 bytes ------------------------------------------ */

/* The following message is used to relay BX execution system transactions that are reported for the current business day. Please note that BX only reports one-side of a trade execution on the BX Last Sale (PLS) feed and other data feed products. */
typedef struct {
  uint8_t tracking_number[2];               /* bytes 0 to 1 */
  uint8_t timestamp[6];                     /* bytes 2 to 7 */
  uint8_t market_center_identifier;         /* byte 8 */
  uint8_t issue_symbol[8];                  /* bytes 9 to 16 */
  uint8_t security_class;                   /* byte 17 */
  uint8_t trade_control_number[10];         /* bytes 18 to 27 */
  uint8_t trade_price[4];                   /* bytes 28 to 31 */
  uint8_t trade_size[4];                    /* bytes 32 to 35 */
  uint8_t sale_condition_modifier_level_1;  /* byte 36 */
  uint8_t sale_condition_modifier_level_2;  /* byte 37 */
  uint8_t sale_condition_modifier_level_3;  /* byte 38 */
  uint8_t sale_condition_modifier_level_4;  /* byte 39 */
} TradeReportMessage;

/* any Trade Report Message at all: every byte one the checker chooses */
static void any_trade_report_message(TradeReportMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  record->market_center_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = arbitrary(); }
  record->sale_condition_modifier_level_1 = arbitrary();
  record->sale_condition_modifier_level_2 = arbitrary();
  record->sale_condition_modifier_level_3 = arbitrary();
  record->sale_condition_modifier_level_4 = arbitrary();
}

/* Trade Report Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_trade_report_message(const TradeReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->market_center_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_control_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_size[i]; }
  wire[at++] = record->sale_condition_modifier_level_1;
  wire[at++] = record->sale_condition_modifier_level_2;
  wire[at++] = record->sale_condition_modifier_level_3;
  wire[at++] = record->sale_condition_modifier_level_4;

  return at;
}

/* Trade Report Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_trade_report_message(TradeReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  record->market_center_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = wire[at++]; }
  record->sale_condition_modifier_level_1 = wire[at++];
  record->sale_condition_modifier_level_2 = wire[at++];
  record->sale_condition_modifier_level_3 = wire[at++];
  record->sale_condition_modifier_level_4 = wire[at++];

  return at;
}

/* what was read of Trade Report Message is what was written, byte for byte */
static void equal_trade_report_message(const TradeReportMessage *read, const TradeReportMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->market_center_identifier == written->market_center_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->trade_control_number[i] == written->trade_control_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_size[i] == written->trade_size[i]); }
  assert(read->sale_condition_modifier_level_1 == written->sale_condition_modifier_level_1);
  assert(read->sale_condition_modifier_level_2 == written->sale_condition_modifier_level_2);
  assert(read->sale_condition_modifier_level_3 == written->sale_condition_modifier_level_3);
  assert(read->sale_condition_modifier_level_4 == written->sale_condition_modifier_level_4);
}

/* Trade Report Message: written and read back, then read and written back */
static void check_trade_report_message(void) {
  TradeReportMessage sent;
  TradeReportMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_trade_report_message(&sent);
  assert(encode_trade_report_message(&sent, wire, 0) == 40);
  assert(decode_trade_report_message(&got, wire, 0) == 40);
  equal_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_message(&got, wire, 0) == 40);
  assert(encode_trade_report_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Next Shares Trade Report Message: 44 bytes ------------------------------ */

/* The following message is used to relay BX execution system and TRF trade transactions for Exchange Traded Managed Funds (NextShares) that are reported for the current business day. */
typedef struct {
  uint8_t tracking_number[2];               /* bytes 0 to 1 */
  uint8_t timestamp[6];                     /* bytes 2 to 7 */
  uint8_t market_center_identifier;         /* byte 8 */
  uint8_t next_shares_symbol[8];            /* bytes 9 to 16 */
  uint8_t security_class;                   /* byte 17 */
  uint8_t trade_control_number[10];         /* bytes 18 to 27 */
  uint8_t proxy_price[4];                   /* bytes 28 to 31 */
  uint8_t trade_size[4];                    /* bytes 32 to 35 */
  uint8_t nav_premium_discount_amount[4];   /* bytes 36 to 39 */
  uint8_t sale_condition_modifier_level_1;  /* byte 40 */
  uint8_t sale_condition_modifier_level_2;  /* byte 41 */
  uint8_t sale_condition_modifier_level_3;  /* byte 42 */
  uint8_t sale_condition_modifier_level_4;  /* byte 43 */
} NextSharesTradeReportMessage;

/* any Next Shares Trade Report Message at all: every byte one the checker chooses */
static void any_next_shares_trade_report_message(NextSharesTradeReportMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  record->market_center_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->next_shares_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->proxy_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nav_premium_discount_amount[i] = arbitrary(); }
  record->sale_condition_modifier_level_1 = arbitrary();
  record->sale_condition_modifier_level_2 = arbitrary();
  record->sale_condition_modifier_level_3 = arbitrary();
  record->sale_condition_modifier_level_4 = arbitrary();
}

/* Next Shares Trade Report Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_next_shares_trade_report_message(const NextSharesTradeReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->market_center_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_shares_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_control_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->proxy_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nav_premium_discount_amount[i]; }
  wire[at++] = record->sale_condition_modifier_level_1;
  wire[at++] = record->sale_condition_modifier_level_2;
  wire[at++] = record->sale_condition_modifier_level_3;
  wire[at++] = record->sale_condition_modifier_level_4;

  return at;
}

/* Next Shares Trade Report Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_next_shares_trade_report_message(NextSharesTradeReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  record->market_center_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->next_shares_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->proxy_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nav_premium_discount_amount[i] = wire[at++]; }
  record->sale_condition_modifier_level_1 = wire[at++];
  record->sale_condition_modifier_level_2 = wire[at++];
  record->sale_condition_modifier_level_3 = wire[at++];
  record->sale_condition_modifier_level_4 = wire[at++];

  return at;
}

/* what was read of Next Shares Trade Report Message is what was written, byte for byte */
static void equal_next_shares_trade_report_message(const NextSharesTradeReportMessage *read, const NextSharesTradeReportMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->market_center_identifier == written->market_center_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->next_shares_symbol[i] == written->next_shares_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->trade_control_number[i] == written->trade_control_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->proxy_price[i] == written->proxy_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_size[i] == written->trade_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nav_premium_discount_amount[i] == written->nav_premium_discount_amount[i]); }
  assert(read->sale_condition_modifier_level_1 == written->sale_condition_modifier_level_1);
  assert(read->sale_condition_modifier_level_2 == written->sale_condition_modifier_level_2);
  assert(read->sale_condition_modifier_level_3 == written->sale_condition_modifier_level_3);
  assert(read->sale_condition_modifier_level_4 == written->sale_condition_modifier_level_4);
}

/* Next Shares Trade Report Message: written and read back, then read and written back */
static void check_next_shares_trade_report_message(void) {
  NextSharesTradeReportMessage sent;
  NextSharesTradeReportMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_next_shares_trade_report_message(&sent);
  assert(encode_next_shares_trade_report_message(&sent, wire, 0) == 44);
  assert(decode_next_shares_trade_report_message(&got, wire, 0) == 44);
  equal_next_shares_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_next_shares_trade_report_message(&got, wire, 0) == 44);
  assert(encode_next_shares_trade_report_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Error Message: 40 bytes ------------------------------------ */

/* The following message is used in the event that a BX trade transaction is cancelled on the same business day that it is reported */
typedef struct {
  uint8_t tracking_number[2];                   /* bytes 0 to 1 */
  uint8_t timestamp[6];                         /* bytes 2 to 7 */
  uint8_t market_center_identifier;             /* byte 8 */
  uint8_t issue_symbol[8];                      /* bytes 9 to 16 */
  uint8_t security_class;                       /* byte 17 */
  uint8_t original_trade_control_number[10];    /* bytes 18 to 27 */
  uint8_t original_trade_price[4];              /* bytes 28 to 31 */
  uint8_t original_trade_size[4];               /* bytes 32 to 35 */
  uint8_t original_sale_condition_modifier[4];  /* bytes 36 to 39 */
} TradeCancelErrorMessage;

/* any Trade Cancel Error Message at all: every byte one the checker chooses */
static void any_trade_cancel_error_message(TradeCancelErrorMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  record->market_center_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_sale_condition_modifier[i] = arbitrary(); }
}

/* Trade Cancel Error Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_error_message(const TradeCancelErrorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->market_center_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->original_trade_control_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_sale_condition_modifier[i]; }

  return at;
}

/* Trade Cancel Error Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_error_message(TradeCancelErrorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  record->market_center_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_sale_condition_modifier[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancel Error Message is what was written, byte for byte */
static void equal_trade_cancel_error_message(const TradeCancelErrorMessage *read, const TradeCancelErrorMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->market_center_identifier == written->market_center_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->original_trade_control_number[i] == written->original_trade_control_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_size[i] == written->original_trade_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_sale_condition_modifier[i] == written->original_sale_condition_modifier[i]); }
}

/* Trade Cancel Error Message: written and read back, then read and written back */
static void check_trade_cancel_error_message(void) {
  TradeCancelErrorMessage sent;
  TradeCancelErrorMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_trade_cancel_error_message(&sent);
  assert(encode_trade_cancel_error_message(&sent, wire, 0) == 40);
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 40);
  equal_trade_cancel_error_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_error_message(&got, wire, 0) == 40);
  assert(encode_trade_cancel_error_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Error For Next Shares Message: 44 bytes -------------------- */

/* The following message is used in the event that a Nasdaq or TRF trade transaction for an NextShares is cancelled on the same business day that it is reported. */
typedef struct {
  uint8_t tracking_number[2];                       /* bytes 0 to 1 */
  uint8_t timestamp[6];                             /* bytes 2 to 7 */
  uint8_t market_center_identifier;                 /* byte 8 */
  uint8_t issue_symbol[8];                          /* bytes 9 to 16 */
  uint8_t security_class;                           /* byte 17 */
  uint8_t original_trade_control_number[10];        /* bytes 18 to 27 */
  uint8_t original_trade_price[4];                  /* bytes 28 to 31 */
  uint8_t original_nav_premium_discount_amount[4];  /* bytes 32 to 35 */
  uint8_t original_trade_size[4];                   /* bytes 36 to 39 */
  uint8_t original_sale_condition_modifier[4];      /* bytes 40 to 43 */
} TradeCancelErrorForNextSharesMessage;

/* any Trade Cancel Error For Next Shares Message at all: every byte one the checker chooses */
static void any_trade_cancel_error_for_next_shares_message(TradeCancelErrorForNextSharesMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  record->market_center_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_nav_premium_discount_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_sale_condition_modifier[i] = arbitrary(); }
}

/* Trade Cancel Error For Next Shares Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_error_for_next_shares_message(const TradeCancelErrorForNextSharesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->market_center_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->original_trade_control_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_nav_premium_discount_amount[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_sale_condition_modifier[i]; }

  return at;
}

/* Trade Cancel Error For Next Shares Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_error_for_next_shares_message(TradeCancelErrorForNextSharesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  record->market_center_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_nav_premium_discount_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_sale_condition_modifier[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancel Error For Next Shares Message is what was written, byte for byte */
static void equal_trade_cancel_error_for_next_shares_message(const TradeCancelErrorForNextSharesMessage *read, const TradeCancelErrorForNextSharesMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->market_center_identifier == written->market_center_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->original_trade_control_number[i] == written->original_trade_control_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_nav_premium_discount_amount[i] == written->original_nav_premium_discount_amount[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_size[i] == written->original_trade_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_sale_condition_modifier[i] == written->original_sale_condition_modifier[i]); }
}

/* Trade Cancel Error For Next Shares Message: written and read back, then read and written back */
static void check_trade_cancel_error_for_next_shares_message(void) {
  TradeCancelErrorForNextSharesMessage sent;
  TradeCancelErrorForNextSharesMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_trade_cancel_error_for_next_shares_message(&sent);
  assert(encode_trade_cancel_error_for_next_shares_message(&sent, wire, 0) == 44);
  assert(decode_trade_cancel_error_for_next_shares_message(&got, wire, 0) == 44);
  equal_trade_cancel_error_for_next_shares_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_error_for_next_shares_message(&got, wire, 0) == 44);
  assert(encode_trade_cancel_error_for_next_shares_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 62 bytes -------------------------------------- */

/* The following message is used in the event that a TRF trade transaction is corrected on the same business day that it is reported. */
typedef struct {
  uint8_t tracking_number[2];                    /* bytes 0 to 1 */
  uint8_t timestamp[6];                          /* bytes 2 to 7 */
  uint8_t market_center_identifier;              /* byte 8 */
  uint8_t issue_symbol[8];                       /* bytes 9 to 16 */
  uint8_t security_class;                        /* byte 17 */
  uint8_t original_trade_control_number[10];     /* bytes 18 to 27 */
  uint8_t original_trade_price[4];               /* bytes 28 to 31 */
  uint8_t original_trade_size[4];                /* bytes 32 to 35 */
  uint8_t original_sale_condition_modifier[4];   /* bytes 36 to 39 */
  uint8_t corrected_trade_control_number[10];    /* bytes 40 to 49 */
  uint8_t corrected_trade_price[4];              /* bytes 50 to 53 */
  uint8_t corrected_trade_size[4];               /* bytes 54 to 57 */
  uint8_t corrected_sale_condition_modifier[4];  /* bytes 58 to 61 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  record->market_center_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_sale_condition_modifier[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->corrected_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_sale_condition_modifier[i] = arbitrary(); }
}

/* Trade Correction Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->market_center_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->original_trade_control_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_sale_condition_modifier[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->corrected_trade_control_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_trade_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_sale_condition_modifier[i]; }

  return at;
}

/* Trade Correction Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  record->market_center_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_sale_condition_modifier[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->corrected_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_sale_condition_modifier[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Correction Message is what was written, byte for byte */
static void equal_trade_correction_message(const TradeCorrectionMessage *read, const TradeCorrectionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->market_center_identifier == written->market_center_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->original_trade_control_number[i] == written->original_trade_control_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_size[i] == written->original_trade_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_sale_condition_modifier[i] == written->original_sale_condition_modifier[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->corrected_trade_control_number[i] == written->corrected_trade_control_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_trade_price[i] == written->corrected_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_trade_size[i] == written->corrected_trade_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_sale_condition_modifier[i] == written->corrected_sale_condition_modifier[i]); }
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 62);
  assert(decode_trade_correction_message(&got, wire, 0) == 62);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 62);
  assert(encode_trade_correction_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction For Next Shares Message: 70 bytes ---------------------- */

/* The following message is used in the event that a TRF trade transaction for a NextShares is corrected on the same business day that it is reported. */
typedef struct {
  uint8_t tracking_number[2];                        /* bytes 0 to 1 */
  uint8_t timestamp[6];                              /* bytes 2 to 7 */
  uint8_t market_center_identifier;                  /* byte 8 */
  uint8_t issue_symbol[8];                           /* bytes 9 to 16 */
  uint8_t security_class;                            /* byte 17 */
  uint8_t original_trade_control_number[10];         /* bytes 18 to 27 */
  uint8_t original_trade_price[4];                   /* bytes 28 to 31 */
  uint8_t original_nav_premium_discount_amount[4];   /* bytes 32 to 35 */
  uint8_t original_trade_size[4];                    /* bytes 36 to 39 */
  uint8_t original_sale_condition_modifier[4];       /* bytes 40 to 43 */
  uint8_t corrected_trade_control_number[10];        /* bytes 44 to 53 */
  uint8_t corrected_trade_price[4];                  /* bytes 54 to 57 */
  uint8_t corrected_nav_premium_discount_amount[4];  /* bytes 58 to 61 */
  uint8_t corrected_trade_size[4];                   /* bytes 62 to 65 */
  uint8_t corrected_sale_condition_modifier[4];      /* bytes 66 to 69 */
} TradeCorrectionForNextSharesMessage;

/* any Trade Correction For Next Shares Message at all: every byte one the checker chooses */
static void any_trade_correction_for_next_shares_message(TradeCorrectionForNextSharesMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  record->market_center_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_nav_premium_discount_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_sale_condition_modifier[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->corrected_trade_control_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_nav_premium_discount_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_sale_condition_modifier[i] = arbitrary(); }
}

/* Trade Correction For Next Shares Message to the wire: 70 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_for_next_shares_message(const TradeCorrectionForNextSharesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->market_center_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->original_trade_control_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_nav_premium_discount_amount[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_sale_condition_modifier[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->corrected_trade_control_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_nav_premium_discount_amount[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_trade_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_sale_condition_modifier[i]; }

  return at;
}

/* Trade Correction For Next Shares Message off the wire: 70 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_for_next_shares_message(TradeCorrectionForNextSharesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  record->market_center_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->original_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_nav_premium_discount_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_sale_condition_modifier[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->corrected_trade_control_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_nav_premium_discount_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_sale_condition_modifier[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Correction For Next Shares Message is what was written, byte for byte */
static void equal_trade_correction_for_next_shares_message(const TradeCorrectionForNextSharesMessage *read, const TradeCorrectionForNextSharesMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->market_center_identifier == written->market_center_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  for (size_t i = 0; i < 10; i++) { assert(read->original_trade_control_number[i] == written->original_trade_control_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_nav_premium_discount_amount[i] == written->original_nav_premium_discount_amount[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_size[i] == written->original_trade_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_sale_condition_modifier[i] == written->original_sale_condition_modifier[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->corrected_trade_control_number[i] == written->corrected_trade_control_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_trade_price[i] == written->corrected_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_nav_premium_discount_amount[i] == written->corrected_nav_premium_discount_amount[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_trade_size[i] == written->corrected_trade_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_sale_condition_modifier[i] == written->corrected_sale_condition_modifier[i]); }
}

/* Trade Correction For Next Shares Message: written and read back, then read and written back */
static void check_trade_correction_for_next_shares_message(void) {
  TradeCorrectionForNextSharesMessage sent;
  TradeCorrectionForNextSharesMessage got;
  uint8_t wire[70];
  uint8_t again[70];

  any_trade_correction_for_next_shares_message(&sent);
  assert(encode_trade_correction_for_next_shares_message(&sent, wire, 0) == 70);
  assert(decode_trade_correction_for_next_shares_message(&got, wire, 0) == 70);
  equal_trade_correction_for_next_shares_message(&got, &sent);

  for (size_t i = 0; i < 70; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_for_next_shares_message(&got, wire, 0) == 70);
  assert(encode_trade_correction_for_next_shares_message(&got, again, 0) == 70);
  for (size_t i = 0; i < 70; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Action Message: 22 bytes ---------------------------------------- */

/* BX uses this administrative message to indicate the current trading status of a security to the trading community. */
typedef struct {
  uint8_t tracking_number[2];        /* bytes 0 to 1 */
  uint8_t timestamp[6];              /* bytes 2 to 7 */
  uint8_t issue_symbol[8];           /* bytes 8 to 15 */
  uint8_t security_class;            /* byte 16 */
  uint8_t current_trading_state;     /* byte 17 */
  uint8_t trading_action_reason[4];  /* bytes 18 to 21 */
} TradingActionMessage;

/* any Trading Action Message at all: every byte one the checker chooses */
static void any_trading_action_message(TradingActionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = arbitrary(); }
  record->security_class = arbitrary();
  record->current_trading_state = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trading_action_reason[i] = arbitrary(); }
}

/* Trading Action Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_trading_action_message(const TradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_symbol[i]; }
  wire[at++] = record->security_class;
  wire[at++] = record->current_trading_state;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_action_reason[i]; }

  return at;
}

/* Trading Action Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_trading_action_message(TradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->issue_symbol[i] = wire[at++]; }
  record->security_class = wire[at++];
  record->current_trading_state = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trading_action_reason[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Action Message is what was written, byte for byte */
static void equal_trading_action_message(const TradingActionMessage *read, const TradingActionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->issue_symbol[i] == written->issue_symbol[i]); }
  assert(read->security_class == written->security_class);
  assert(read->current_trading_state == written->current_trading_state);
  for (size_t i = 0; i < 4; i++) { assert(read->trading_action_reason[i] == written->trading_action_reason[i]); }
}

/* Trading Action Message: written and read back, then read and written back */
static void check_trading_action_message(void) {
  TradingActionMessage sent;
  TradingActionMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_trading_action_message(&sent);
  assert(encode_trading_action_message(&sent, wire, 0) == 22);
  assert(decode_trading_action_message(&got, wire, 0) == 22);
  equal_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_action_message(&got, wire, 0) == 22);
  assert(encode_trading_action_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reg Sho Short Sale Price Test Restricted Indicator Message: 17 bytes ---- */

/* For Nasdaq-listed issues, Nasdaq supports a full pre-opening spin of Reg SHO Short Sale Price Test Restricted Indicator messages indicating the Rule 201 status for all active issues. Nasdaq also sends the Reg SHO Short Sale Price Test Restricted Indicator message in the event of an intraday status change. For other exchange-listed issues, Nasdaq relays the Reg SHO Short Sale Price Test Restricted Indicator message when it receives an update from the primary listing exchange. */
typedef struct {
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t timestamp[6];        /* bytes 2 to 7 */
  uint8_t stock[8];            /* bytes 8 to 15 */
  uint8_t reg_sho_action;      /* byte 16 */
} RegShoShortSalePriceTestRestrictedIndicatorMessage;

/* any Reg Sho Short Sale Price Test Restricted Indicator Message at all: every byte one the checker chooses */
static void any_reg_sho_short_sale_price_test_restricted_indicator_message(RegShoShortSalePriceTestRestrictedIndicatorMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->reg_sho_action = arbitrary();
}

/* Reg Sho Short Sale Price Test Restricted Indicator Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_reg_sho_short_sale_price_test_restricted_indicator_message(const RegShoShortSalePriceTestRestrictedIndicatorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->reg_sho_action;

  return at;
}

/* Reg Sho Short Sale Price Test Restricted Indicator Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_reg_sho_short_sale_price_test_restricted_indicator_message(RegShoShortSalePriceTestRestrictedIndicatorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->reg_sho_action = wire[at++];

  return at;
}

/* what was read of Reg Sho Short Sale Price Test Restricted Indicator Message is what was written, byte for byte */
static void equal_reg_sho_short_sale_price_test_restricted_indicator_message(const RegShoShortSalePriceTestRestrictedIndicatorMessage *read, const RegShoShortSalePriceTestRestrictedIndicatorMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->reg_sho_action == written->reg_sho_action);
}

/* Reg Sho Short Sale Price Test Restricted Indicator Message: written and read back, then read and written back */
static void check_reg_sho_short_sale_price_test_restricted_indicator_message(void) {
  RegShoShortSalePriceTestRestrictedIndicatorMessage sent;
  RegShoShortSalePriceTestRestrictedIndicatorMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_reg_sho_short_sale_price_test_restricted_indicator_message(&sent);
  assert(encode_reg_sho_short_sale_price_test_restricted_indicator_message(&sent, wire, 0) == 17);
  assert(decode_reg_sho_short_sale_price_test_restricted_indicator_message(&got, wire, 0) == 17);
  equal_reg_sho_short_sale_price_test_restricted_indicator_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_reg_sho_short_sale_price_test_restricted_indicator_message(&got, wire, 0) == 17);
  assert(encode_reg_sho_short_sale_price_test_restricted_indicator_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Directory Message: 36 bytes --------------------------------------- */

/* At the start of each trading day, BX disseminates stock directory messages for all active symbols in the BX system */
typedef struct {
  uint8_t tracking_number[2];              /* bytes 0 to 1 */
  uint8_t timestamp[6];                    /* bytes 2 to 7 */
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

/* Stock Directory Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_stock_directory_message(const StockDirectoryMessage *record, uint8_t *wire, size_t at) {
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

/* Stock Directory Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_stock_directory_message(StockDirectoryMessage *record, const uint8_t *wire, size_t at) {
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
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t timestamp[6];        /* bytes 2 to 7 */
  uint8_t level_1[8];          /* bytes 8 to 15 */
  uint8_t level_2[8];          /* bytes 16 to 23 */
  uint8_t level_3[8];          /* bytes 24 to 31 */
} MwcbDeclineLevelMessage;

/* any Mwcb Decline Level Message at all: every byte one the checker chooses */
static void any_mwcb_decline_level_message(MwcbDeclineLevelMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->level_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->level_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->level_3[i] = arbitrary(); }
}

/* Mwcb Decline Level Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_mwcb_decline_level_message(const MwcbDeclineLevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->level_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->level_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->level_3[i]; }

  return at;
}

/* Mwcb Decline Level Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_mwcb_decline_level_message(MwcbDeclineLevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->level_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->level_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->level_3[i] = wire[at++]; }

  return at;
}

/* what was read of Mwcb Decline Level Message is what was written, byte for byte */
static void equal_mwcb_decline_level_message(const MwcbDeclineLevelMessage *read, const MwcbDeclineLevelMessage *written) {
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
  uint8_t timestamp[6];        /* bytes 2 to 7 */
  uint8_t breached_level;      /* byte 8 */
} MwcbBreachMessage;

/* any Mwcb Breach Message at all: every byte one the checker chooses */
static void any_mwcb_breach_message(MwcbBreachMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  record->breached_level = arbitrary();
}

/* Mwcb Breach Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_mwcb_breach_message(const MwcbBreachMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->breached_level;

  return at;
}

/* Mwcb Breach Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_mwcb_breach_message(MwcbBreachMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  record->breached_level = wire[at++];

  return at;
}

/* what was read of Mwcb Breach Message is what was written, byte for byte */
static void equal_mwcb_breach_message(const MwcbBreachMessage *read, const MwcbBreachMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
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

/* Nasdaq uses this administrative message to indicate the current trading status of the three market centers operated by Nasdaq. */
typedef struct {
  uint8_t tracking_number[2];       /* bytes 0 to 1 */
  uint8_t timestamp[6];             /* bytes 2 to 7 */
  uint8_t stock[8];                 /* bytes 8 to 15 */
  uint8_t market_code;              /* byte 16 */
  uint8_t operational_halt_action;  /* byte 17 */
} OperationalHaltMessage;

/* any Operational Halt Message at all: every byte one the checker chooses */
static void any_operational_halt_message(OperationalHaltMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->market_code = arbitrary();
  record->operational_halt_action = arbitrary();
}

/* Operational Halt Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_operational_halt_message(const OperationalHaltMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->market_code;
  wire[at++] = record->operational_halt_action;

  return at;
}

/* Operational Halt Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_operational_halt_message(OperationalHaltMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->market_code = wire[at++];
  record->operational_halt_action = wire[at++];

  return at;
}

/* what was read of Operational Halt Message is what was written, byte for byte */
static void equal_operational_halt_message(const OperationalHaltMessage *read, const OperationalHaltMessage *written) {
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
  check_trade_report_message();
  check_next_shares_trade_report_message();
  check_trade_cancel_error_message();
  check_trade_cancel_error_for_next_shares_message();
  check_trade_correction_message();
  check_trade_correction_for_next_shares_message();
  check_trading_action_message();
  check_reg_sho_short_sale_price_test_restricted_indicator_message();
  check_stock_directory_message();
  check_mwcb_decline_level_message();
  check_mwcb_breach_message();
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
