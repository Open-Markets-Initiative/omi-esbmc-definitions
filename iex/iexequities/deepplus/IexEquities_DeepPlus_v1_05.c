// iex/iexequities/deepplus/IexEquities_DeepPlus_v1_05.c
/*
 * Investors Exchange DeepPlus
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
 *   - a field read in bits
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

/* ---- Iextp Header: 40 bytes -------------------------------------------------- */

/* IexTp packet header */
typedef struct {
  uint8_t version;                           /* byte 0 */
  uint8_t reserved;                          /* byte 1 */
  uint8_t message_protocol_id[2];            /* bytes 2 to 3 */
  uint8_t channel_id[4];                     /* bytes 4 to 7 */
  uint8_t session_id[4];                     /* bytes 8 to 11 */
  uint8_t payload_length[2];                 /* bytes 12 to 13 */
  uint8_t message_count[2];                  /* bytes 14 to 15 */
  uint8_t stream_offset[8];                  /* bytes 16 to 23 */
  uint8_t first_message_sequence_number[8];  /* bytes 24 to 31 */
  uint8_t send_time[8];                      /* bytes 32 to 39 */
} IextpHeader;

/* any Iextp Header at all: every byte one the checker chooses */
static void any_iextp_header(IextpHeader *record) {
  record->version = arbitrary();
  record->reserved = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->message_protocol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->channel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->payload_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stream_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->first_message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = arbitrary(); }
}

/* Iextp Header to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_iextp_header(const IextpHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->version;
  wire[at++] = record->reserved;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_protocol_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->channel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->payload_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stream_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->first_message_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->send_time[i]; }

  return at;
}

/* Iextp Header off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_iextp_header(IextpHeader *record, const uint8_t *wire, size_t at) {
  record->version = wire[at++];
  record->reserved = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->message_protocol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->channel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->payload_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stream_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->first_message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = wire[at++]; }

  return at;
}

/* what was read of Iextp Header is what was written, byte for byte */
static void equal_iextp_header(const IextpHeader *read, const IextpHeader *written) {
  assert(read->version == written->version);
  assert(read->reserved == written->reserved);
  for (size_t i = 0; i < 2; i++) { assert(read->message_protocol_id[i] == written->message_protocol_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->channel_id[i] == written->channel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->payload_length[i] == written->payload_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_count[i] == written->message_count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stream_offset[i] == written->stream_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->first_message_sequence_number[i] == written->first_message_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->send_time[i] == written->send_time[i]); }
}

/* Iextp Header: written and read back, then read and written back */
static void check_iextp_header(void) {
  IextpHeader sent;
  IextpHeader got;
  uint8_t wire[40];
  uint8_t again[40];

  any_iextp_header(&sent);
  assert(encode_iextp_header(&sent, wire, 0) == 40);
  assert(decode_iextp_header(&got, wire, 0) == 40);
  equal_iextp_header(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_iextp_header(&got, wire, 0) == 40);
  assert(encode_iextp_header(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* IexTp message header */
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

/* The System Event Message is used to indicate events that apply to the market or the data feed. */
typedef struct {
  uint8_t system_event;  /* byte 0 */
  uint8_t timestamp[8];  /* bytes 1 to 8 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  record->system_event = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* System Event Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->system_event;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* System Event Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  record->system_event = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  assert(read->system_event == written->system_event);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
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

/* ---- Trading Status Message: 21 bytes ---------------------------------------- */

/* The Trading Status Message is used to indicate the current trading status of a security. */
typedef struct {
  uint8_t trading_status;  /* byte 0 */
  uint8_t timestamp[8];    /* bytes 1 to 8 */
  uint8_t symbol[8];       /* bytes 9 to 16 */
  uint8_t reason[4];       /* bytes 17 to 20 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  record->trading_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reason[i] = arbitrary(); }
}

/* Trading Status Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Trading Status Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  record->trading_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  assert(read->trading_status == written->trading_status);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reason[i] == written->reason[i]); }
}

/* Trading Status Message: written and read back, then read and written back */
static void check_trading_status_message(void) {
  TradingStatusMessage sent;
  TradingStatusMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_trading_status_message(&sent);
  assert(encode_trading_status_message(&sent, wire, 0) == 21);
  assert(decode_trading_status_message(&got, wire, 0) == 21);
  equal_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_message(&got, wire, 0) == 21);
  assert(encode_trading_status_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retail Liquidity Indicator Message: 17 bytes ---------------------------- */

/* broadcasts a real-time Retail Liquidity Indicator Message each time there is an update to IEX's eligible retail liquidity interest during the trading day */
typedef struct {
  uint8_t retail_liquidity_indicator;  /* byte 0 */
  uint8_t timestamp[8];                /* bytes 1 to 8 */
  uint8_t symbol[8];                   /* bytes 9 to 16 */
} RetailLiquidityIndicatorMessage;

/* any Retail Liquidity Indicator Message at all: every byte one the checker chooses */
static void any_retail_liquidity_indicator_message(RetailLiquidityIndicatorMessage *record) {
  record->retail_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
}

/* Retail Liquidity Indicator Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_retail_liquidity_indicator_message(const RetailLiquidityIndicatorMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->retail_liquidity_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }

  return at;
}

/* Retail Liquidity Indicator Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_retail_liquidity_indicator_message(RetailLiquidityIndicatorMessage *record, const uint8_t *wire, size_t at) {
  record->retail_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Retail Liquidity Indicator Message is what was written, byte for byte */
static void equal_retail_liquidity_indicator_message(const RetailLiquidityIndicatorMessage *read, const RetailLiquidityIndicatorMessage *written) {
  assert(read->retail_liquidity_indicator == written->retail_liquidity_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
}

/* Retail Liquidity Indicator Message: written and read back, then read and written back */
static void check_retail_liquidity_indicator_message(void) {
  RetailLiquidityIndicatorMessage sent;
  RetailLiquidityIndicatorMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_retail_liquidity_indicator_message(&sent);
  assert(encode_retail_liquidity_indicator_message(&sent, wire, 0) == 17);
  assert(decode_retail_liquidity_indicator_message(&got, wire, 0) == 17);
  equal_retail_liquidity_indicator_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_retail_liquidity_indicator_message(&got, wire, 0) == 17);
  assert(encode_retail_liquidity_indicator_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Operational Halt Status Message: 17 bytes ------------------------------- */

/* The Exchange may suspend trading of one or more securities on IEX for operational reasons and indicates such operational halt using the Operational Halt Status Message. */
typedef struct {
  uint8_t operational_halt_status;  /* byte 0 */
  uint8_t timestamp[8];             /* bytes 1 to 8 */
  uint8_t symbol[8];                /* bytes 9 to 16 */
} OperationalHaltStatusMessage;

/* any Operational Halt Status Message at all: every byte one the checker chooses */
static void any_operational_halt_status_message(OperationalHaltStatusMessage *record) {
  record->operational_halt_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
}

/* Operational Halt Status Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_operational_halt_status_message(const OperationalHaltStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->operational_halt_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }

  return at;
}

/* Operational Halt Status Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_operational_halt_status_message(OperationalHaltStatusMessage *record, const uint8_t *wire, size_t at) {
  record->operational_halt_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Operational Halt Status Message is what was written, byte for byte */
static void equal_operational_halt_status_message(const OperationalHaltStatusMessage *read, const OperationalHaltStatusMessage *written) {
  assert(read->operational_halt_status == written->operational_halt_status);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
}

/* Operational Halt Status Message: written and read back, then read and written back */
static void check_operational_halt_status_message(void) {
  OperationalHaltStatusMessage sent;
  OperationalHaltStatusMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_operational_halt_status_message(&sent);
  assert(encode_operational_halt_status_message(&sent, wire, 0) == 17);
  assert(decode_operational_halt_status_message(&got, wire, 0) == 17);
  equal_operational_halt_status_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_operational_halt_status_message(&got, wire, 0) == 17);
  assert(encode_operational_halt_status_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Sale Price Test Status Message: 18 bytes -------------------------- */

/* The Short Sale Price Test Message is used to indicate when a short sale price test restriction is in effect for a security. */
typedef struct {
  uint8_t short_sale_price_test_status;  /* byte 0 */
  uint8_t timestamp[8];                  /* bytes 1 to 8 */
  uint8_t symbol[8];                     /* bytes 9 to 16 */
  uint8_t detail;                        /* byte 17 */
} ShortSalePriceTestStatusMessage;

/* any Short Sale Price Test Status Message at all: every byte one the checker chooses */
static void any_short_sale_price_test_status_message(ShortSalePriceTestStatusMessage *record) {
  record->short_sale_price_test_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->detail = arbitrary();
}

/* Short Sale Price Test Status Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_short_sale_price_test_status_message(const ShortSalePriceTestStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->short_sale_price_test_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->detail;

  return at;
}

/* Short Sale Price Test Status Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_short_sale_price_test_status_message(ShortSalePriceTestStatusMessage *record, const uint8_t *wire, size_t at) {
  record->short_sale_price_test_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->detail = wire[at++];

  return at;
}

/* what was read of Short Sale Price Test Status Message is what was written, byte for byte */
static void equal_short_sale_price_test_status_message(const ShortSalePriceTestStatusMessage *read, const ShortSalePriceTestStatusMessage *written) {
  assert(read->short_sale_price_test_status == written->short_sale_price_test_status);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->detail == written->detail);
}

/* Short Sale Price Test Status Message: written and read back, then read and written back */
static void check_short_sale_price_test_status_message(void) {
  ShortSalePriceTestStatusMessage sent;
  ShortSalePriceTestStatusMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_short_sale_price_test_status_message(&sent);
  assert(encode_short_sale_price_test_status_message(&sent, wire, 0) == 18);
  assert(decode_short_sale_price_test_status_message(&got, wire, 0) == 18);
  equal_short_sale_price_test_status_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_short_sale_price_test_status_message(&got, wire, 0) == 18);
  assert(encode_short_sale_price_test_status_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Event Message: 17 bytes ---------------------------------------- */

/* The Security Event Message is used to indicate events that apply to a security */
typedef struct {
  uint8_t security_event;  /* byte 0 */
  uint8_t timestamp[8];    /* bytes 1 to 8 */
  uint8_t symbol[8];       /* bytes 9 to 16 */
} SecurityEventMessage;

/* any Security Event Message at all: every byte one the checker chooses */
static void any_security_event_message(SecurityEventMessage *record) {
  record->security_event = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
}

/* Security Event Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_security_event_message(const SecurityEventMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->security_event;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }

  return at;
}

/* Security Event Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_security_event_message(SecurityEventMessage *record, const uint8_t *wire, size_t at) {
  record->security_event = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Security Event Message is what was written, byte for byte */
static void equal_security_event_message(const SecurityEventMessage *read, const SecurityEventMessage *written) {
  assert(read->security_event == written->security_event);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
}

/* Security Event Message: written and read back, then read and written back */
static void check_security_event_message(void) {
  SecurityEventMessage sent;
  SecurityEventMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_security_event_message(&sent);
  assert(encode_security_event_message(&sent, wire, 0) == 17);
  assert(decode_security_event_message(&got, wire, 0) == 17);
  equal_security_event_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_security_event_message(&got, wire, 0) == 17);
  assert(encode_security_event_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message: 37 bytes --------------------------------------------- */

/* A displayed order that has been added to the IEX Book */
typedef struct {
  uint8_t side;          /* byte 0 */
  uint8_t timestamp[8];  /* bytes 1 to 8 */
  uint8_t symbol[8];     /* bytes 9 to 16 */
  uint8_t order_id[8];   /* bytes 17 to 24 */
  uint8_t size[4];       /* bytes 25 to 28 */
  uint8_t price[8];      /* bytes 29 to 36 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Add Order Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Add Order Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 37);
  assert(decode_add_order_message(&got, wire, 0) == 37);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 37);
  assert(encode_add_order_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Delete Message: 25 bytes ------------------------------------------ */

/* A displayed order that was removed from the IEX Book */
typedef struct {
  uint8_t reserved_1;             /* byte 0 */
  uint8_t timestamp[8];           /* bytes 1 to 8 */
  uint8_t symbol[8];              /* bytes 9 to 16 */
  uint8_t order_id_reference[8];  /* bytes 17 to 24 */
} OrderDeleteMessage;

/* any Order Delete Message at all: every byte one the checker chooses */
static void any_order_delete_message(OrderDeleteMessage *record) {
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id_reference[i] = arbitrary(); }
}

/* Order Delete Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_order_delete_message(const OrderDeleteMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id_reference[i]; }

  return at;
}

/* Order Delete Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_order_delete_message(OrderDeleteMessage *record, const uint8_t *wire, size_t at) {
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id_reference[i] = wire[at++]; }

  return at;
}

/* what was read of Order Delete Message is what was written, byte for byte */
static void equal_order_delete_message(const OrderDeleteMessage *read, const OrderDeleteMessage *written) {
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id_reference[i] == written->order_id_reference[i]); }
}

/* Order Delete Message: written and read back, then read and written back */
static void check_order_delete_message(void) {
  OrderDeleteMessage sent;
  OrderDeleteMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_order_delete_message(&sent);
  assert(encode_order_delete_message(&sent, wire, 0) == 25);
  assert(decode_order_delete_message(&got, wire, 0) == 25);
  equal_order_delete_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_order_delete_message(&got, wire, 0) == 25);
  assert(encode_order_delete_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clear Book Message: 17 bytes -------------------------------------------- */

/* This message is used to indicate that the IEX Book for a symbol has been cleared of all orders */
typedef struct {
  uint8_t reserved_1;    /* byte 0 */
  uint8_t timestamp[8];  /* bytes 1 to 8 */
  uint8_t symbol[8];     /* bytes 9 to 16 */
} ClearBookMessage;

/* any Clear Book Message at all: every byte one the checker chooses */
static void any_clear_book_message(ClearBookMessage *record) {
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
}

/* Clear Book Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_clear_book_message(const ClearBookMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }

  return at;
}

/* Clear Book Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_clear_book_message(ClearBookMessage *record, const uint8_t *wire, size_t at) {
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Clear Book Message is what was written, byte for byte */
static void equal_clear_book_message(const ClearBookMessage *read, const ClearBookMessage *written) {
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
}

/* Clear Book Message: written and read back, then read and written back */
static void check_clear_book_message(void) {
  ClearBookMessage sent;
  ClearBookMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_clear_book_message(&sent);
  assert(encode_clear_book_message(&sent, wire, 0) == 17);
  assert(decode_clear_book_message(&got, wire, 0) == 17);
  equal_clear_book_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_clear_book_message(&got, wire, 0) == 17);
  assert(encode_clear_book_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_iextp_header();
  check_message_header();
  check_system_event_message();
  check_trading_status_message();
  check_retail_liquidity_indicator_message();
  check_operational_halt_status_message();
  check_short_sale_price_test_status_message();
  check_security_event_message();
  check_add_order_message();
  check_order_delete_message();
  check_clear_book_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
