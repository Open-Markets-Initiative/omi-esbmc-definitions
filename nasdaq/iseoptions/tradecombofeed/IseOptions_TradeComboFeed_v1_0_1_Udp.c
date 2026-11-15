// nasdaq/iseoptions/tradecombofeed/IseOptions_TradeComboFeed_v1_0_1_Udp.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Ise Trade Combo Feed
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

/* ---- System Event Message: 13 bytes ------------------------------------------ */

/* The system event message type is used to signal a market or data feed handler event. */
typedef struct {
  uint8_t timestamp[6];     /* bytes 0 to 5 */
  uint8_t event_code;       /* byte 6 */
  uint8_t current_year[2];  /* bytes 7 to 8 */
  uint8_t current_month;    /* byte 9 */
  uint8_t current_day;      /* byte 10 */
  uint8_t version;          /* byte 11 */
  uint8_t sub_version;      /* byte 12 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  record->event_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->current_year[i] = arbitrary(); }
  record->current_month = arbitrary();
  record->current_day = arbitrary();
  record->version = arbitrary();
  record->sub_version = arbitrary();
}

/* System Event Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->current_year[i]; }
  wire[at++] = record->current_month;
  wire[at++] = record->current_day;
  wire[at++] = record->version;
  wire[at++] = record->sub_version;

  return at;
}

/* System Event Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  record->event_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->current_year[i] = wire[at++]; }
  record->current_month = wire[at++];
  record->current_day = wire[at++];
  record->version = wire[at++];
  record->sub_version = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->event_code == written->event_code);
  for (size_t i = 0; i < 2; i++) { assert(read->current_year[i] == written->current_year[i]); }
  assert(read->current_month == written->current_month);
  assert(read->current_day == written->current_day);
  assert(read->version == written->version);
  assert(read->sub_version == written->sub_version);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 13);
  assert(decode_system_event_message(&got, wire, 0) == 13);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 13);
  assert(encode_system_event_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strategy Trading Action Message: 11 bytes ------------------------------- */

/* ISE uses this administrative message to indicate the current trading status of a strategy within the ISE Options Market. Messages will be sent when the strategy is halted or is released for trading. */
typedef struct {
  uint8_t timestamp[6];           /* bytes 0 to 5 */
  uint8_t strategy_id[4];         /* bytes 6 to 9 */
  uint8_t current_trading_state;  /* byte 10 */
} StrategyTradingActionMessage;

/* any Strategy Trading Action Message at all: every byte one the checker chooses */
static void any_strategy_trading_action_message(StrategyTradingActionMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  record->current_trading_state = arbitrary();
}

/* Strategy Trading Action Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_strategy_trading_action_message(const StrategyTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  wire[at++] = record->current_trading_state;

  return at;
}

/* Strategy Trading Action Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_strategy_trading_action_message(StrategyTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  record->current_trading_state = wire[at++];

  return at;
}

/* what was read of Strategy Trading Action Message is what was written, byte for byte */
static void equal_strategy_trading_action_message(const StrategyTradingActionMessage *read, const StrategyTradingActionMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  assert(read->current_trading_state == written->current_trading_state);
}

/* Strategy Trading Action Message: written and read back, then read and written back */
static void check_strategy_trading_action_message(void) {
  StrategyTradingActionMessage sent;
  StrategyTradingActionMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_strategy_trading_action_message(&sent);
  assert(encode_strategy_trading_action_message(&sent, wire, 0) == 11);
  assert(decode_strategy_trading_action_message(&got, wire, 0) == 11);
  equal_strategy_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_strategy_trading_action_message(&got, wire, 0) == 11);
  assert(encode_strategy_trading_action_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strategy Open Closed Message: 11 bytes ---------------------------------- */

/* The options system uses this administrative message to indicate when a strategy has completed the opening process and is now available for auto execution or when the option has closed and is no longer available for auto execution. */
typedef struct {
  uint8_t timestamp[6];    /* bytes 0 to 5 */
  uint8_t strategy_id[4];  /* bytes 6 to 9 */
  uint8_t open_state;      /* byte 10 */
} StrategyOpenClosedMessage;

/* any Strategy Open Closed Message at all: every byte one the checker chooses */
static void any_strategy_open_closed_message(StrategyOpenClosedMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  record->open_state = arbitrary();
}

/* Strategy Open Closed Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_strategy_open_closed_message(const StrategyOpenClosedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  wire[at++] = record->open_state;

  return at;
}

/* Strategy Open Closed Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_strategy_open_closed_message(StrategyOpenClosedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  record->open_state = wire[at++];

  return at;
}

/* what was read of Strategy Open Closed Message is what was written, byte for byte */
static void equal_strategy_open_closed_message(const StrategyOpenClosedMessage *read, const StrategyOpenClosedMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  assert(read->open_state == written->open_state);
}

/* Strategy Open Closed Message: written and read back, then read and written back */
static void check_strategy_open_closed_message(void) {
  StrategyOpenClosedMessage sent;
  StrategyOpenClosedMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_strategy_open_closed_message(&sent);
  assert(encode_strategy_open_closed_message(&sent, wire, 0) == 11);
  assert(decode_strategy_open_closed_message(&got, wire, 0) == 11);
  equal_strategy_open_closed_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_strategy_open_closed_message(&got, wire, 0) == 11);
  assert(encode_strategy_open_closed_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Strategy Ticker Message: 51 bytes ------------------------------- */

/* The ticker message is used to send real time trade information. */
typedef struct {
  uint8_t timestamp[6];     /* bytes 0 to 5 */
  uint8_t strategy_id[4];   /* bytes 6 to 9 */
  uint8_t last_price[8];    /* bytes 10 to 17 */
  uint8_t size[4];          /* bytes 18 to 21 */
  uint8_t volume[4];        /* bytes 22 to 25 */
  uint8_t high[8];          /* bytes 26 to 33 */
  uint8_t low[8];           /* bytes 34 to 41 */
  uint8_t first[8];         /* bytes 42 to 49 */
  uint8_t trade_condition;  /* byte 50 */
} ComplexStrategyTickerMessage;

/* any Complex Strategy Ticker Message at all: every byte one the checker chooses */
static void any_complex_strategy_ticker_message(ComplexStrategyTickerMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->first[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Complex Strategy Ticker Message to the wire: 51 bytes from at, returning where the next byte goes */
static size_t encode_complex_strategy_ticker_message(const ComplexStrategyTickerMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->first[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Complex Strategy Ticker Message off the wire: 51 bytes from at, returning where the next byte lies */
static size_t decode_complex_strategy_ticker_message(ComplexStrategyTickerMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->first[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Complex Strategy Ticker Message is what was written, byte for byte */
static void equal_complex_strategy_ticker_message(const ComplexStrategyTickerMessage *read, const ComplexStrategyTickerMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high[i] == written->high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low[i] == written->low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->first[i] == written->first[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Complex Strategy Ticker Message: written and read back, then read and written back */
static void check_complex_strategy_ticker_message(void) {
  ComplexStrategyTickerMessage sent;
  ComplexStrategyTickerMessage got;
  uint8_t wire[51];
  uint8_t again[51];

  any_complex_strategy_ticker_message(&sent);
  assert(encode_complex_strategy_ticker_message(&sent, wire, 0) == 51);
  assert(decode_complex_strategy_ticker_message(&got, wire, 0) == 51);
  equal_complex_strategy_ticker_message(&got, &sent);

  for (size_t i = 0; i < 51; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_strategy_ticker_message(&got, wire, 0) == 51);
  assert(encode_complex_strategy_ticker_message(&got, again, 0) == 51);
  for (size_t i = 0; i < 51; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_system_event_message();
  check_strategy_trading_action_message();
  check_strategy_open_closed_message();
  check_complex_strategy_ticker_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
