// nasdaq/nsmequities/totalview/NsmEquities_TotalView_AsciiItch_v3_1_f_Udp.c
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

/* ---- Seconds Message: 5 bytes ------------------------------------------------ */

/* This message is sent every second for which at least one TotalView-ITCH 3.1f message is being generated. */
typedef struct {
  uint8_t second[5];  /* bytes 0 to 4 */
} SecondsMessage;

/* any Seconds Message at all: every byte one the checker chooses */
static void any_seconds_message(SecondsMessage *record) {
  for (size_t i = 0; i < 5; i++) { record->second[i] = arbitrary(); }
}

/* Seconds Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_seconds_message(const SecondsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->second[i]; }

  return at;
}

/* Seconds Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_seconds_message(SecondsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->second[i] = wire[at++]; }

  return at;
}

/* what was read of Seconds Message is what was written, byte for byte */
static void equal_seconds_message(const SecondsMessage *read, const SecondsMessage *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->second[i] == written->second[i]); }
}

/* Seconds Message: written and read back, then read and written back */
static void check_seconds_message(void) {
  SecondsMessage sent;
  SecondsMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_seconds_message(&sent);
  assert(encode_seconds_message(&sent, wire, 0) == 5);
  assert(decode_seconds_message(&got, wire, 0) == 5);
  equal_seconds_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_seconds_message(&got, wire, 0) == 5);
  assert(encode_seconds_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Milliseconds Message: 3 bytes ------------------------------------------- */

/* This message is sent every millisecond for which at least one TotalView-ITCH 3.1f message is being generated. */
typedef struct {
  uint8_t millisecond[3];  /* bytes 0 to 2 */
} MillisecondsMessage;

/* any Milliseconds Message at all: every byte one the checker chooses */
static void any_milliseconds_message(MillisecondsMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->millisecond[i] = arbitrary(); }
}

/* Milliseconds Message to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_milliseconds_message(const MillisecondsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->millisecond[i]; }

  return at;
}

/* Milliseconds Message off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_milliseconds_message(MillisecondsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->millisecond[i] = wire[at++]; }

  return at;
}

/* what was read of Milliseconds Message is what was written, byte for byte */
static void equal_milliseconds_message(const MillisecondsMessage *read, const MillisecondsMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->millisecond[i] == written->millisecond[i]); }
}

/* Milliseconds Message: written and read back, then read and written back */
static void check_milliseconds_message(void) {
  MillisecondsMessage sent;
  MillisecondsMessage got;
  uint8_t wire[3];
  uint8_t again[3];

  any_milliseconds_message(&sent);
  assert(encode_milliseconds_message(&sent, wire, 0) == 3);
  assert(decode_milliseconds_message(&got, wire, 0) == 3);
  equal_milliseconds_message(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_milliseconds_message(&got, wire, 0) == 3);
  assert(encode_milliseconds_message(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
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

/* ---- Stock Directory Message: 15 bytes --------------------------------------- */

/* At the start of each trading day, NASDAQ disseminates stock directory messages for all active symbols in Single Book. */
typedef struct {
  uint8_t stock_alpha_6[6];            /* bytes 0 to 5 */
  uint8_t market_category;             /* byte 6 */
  uint8_t financial_status_indicator;  /* byte 7 */
  uint8_t round_lot_size[6];           /* bytes 8 to 13 */
  uint8_t round_lots_only;             /* byte 14 */
} StockDirectoryMessage;

/* any Stock Directory Message at all: every byte one the checker chooses */
static void any_stock_directory_message(StockDirectoryMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->stock_alpha_6[i] = arbitrary(); }
  record->market_category = arbitrary();
  record->financial_status_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->round_lot_size[i] = arbitrary(); }
  record->round_lots_only = arbitrary();
}

/* Stock Directory Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_stock_directory_message(const StockDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock_alpha_6[i]; }
  wire[at++] = record->market_category;
  wire[at++] = record->financial_status_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->round_lot_size[i]; }
  wire[at++] = record->round_lots_only;

  return at;
}

/* Stock Directory Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_stock_directory_message(StockDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->stock_alpha_6[i] = wire[at++]; }
  record->market_category = wire[at++];
  record->financial_status_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->round_lot_size[i] = wire[at++]; }
  record->round_lots_only = wire[at++];

  return at;
}

/* what was read of Stock Directory Message is what was written, byte for byte */
static void equal_stock_directory_message(const StockDirectoryMessage *read, const StockDirectoryMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->stock_alpha_6[i] == written->stock_alpha_6[i]); }
  assert(read->market_category == written->market_category);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->round_lot_size[i] == written->round_lot_size[i]); }
  assert(read->round_lots_only == written->round_lots_only);
}

/* Stock Directory Message: written and read back, then read and written back */
static void check_stock_directory_message(void) {
  StockDirectoryMessage sent;
  StockDirectoryMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_stock_directory_message(&sent);
  assert(encode_stock_directory_message(&sent, wire, 0) == 15);
  assert(decode_stock_directory_message(&got, wire, 0) == 15);
  equal_stock_directory_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_directory_message(&got, wire, 0) == 15);
  assert(encode_stock_directory_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Trading Action Message: 12 bytes ---------------------------------- */

/* NASDAQ uses this administrative message to indicate the current trading status of a security to the trading community. */
typedef struct {
  uint8_t stock_alpha_6[6];  /* bytes 0 to 5 */
  uint8_t trading_state;     /* byte 6 */
  uint8_t reserved_1;        /* byte 7 */
  uint8_t reason[4];         /* bytes 8 to 11 */
} StockTradingActionMessage;

/* any Stock Trading Action Message at all: every byte one the checker chooses */
static void any_stock_trading_action_message(StockTradingActionMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->stock_alpha_6[i] = arbitrary(); }
  record->trading_state = arbitrary();
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reason[i] = arbitrary(); }
}

/* Stock Trading Action Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_stock_trading_action_message(const StockTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock_alpha_6[i]; }
  wire[at++] = record->trading_state;
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Stock Trading Action Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_stock_trading_action_message(StockTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->stock_alpha_6[i] = wire[at++]; }
  record->trading_state = wire[at++];
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Trading Action Message is what was written, byte for byte */
static void equal_stock_trading_action_message(const StockTradingActionMessage *read, const StockTradingActionMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->stock_alpha_6[i] == written->stock_alpha_6[i]); }
  assert(read->trading_state == written->trading_state);
  assert(read->reserved_1 == written->reserved_1);
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

/* ---- Market Participant Position Message: 13 bytes --------------------------- */

/* At the start of each trading day, NASDAQ disseminates a spin of market participant position messages. Throughout the day, NASDAQ will send out this message only if NASDAQ Operations changes the status of a market participant firm in an issue. */
typedef struct {
  uint8_t mpid[4];                   /* bytes 0 to 3 */
  uint8_t stock_alphanumeric_6[6];   /* bytes 4 to 9 */
  uint8_t primary_market_maker;      /* byte 10 */
  uint8_t market_maker_mode;         /* byte 11 */
  uint8_t market_participant_state;  /* byte 12 */
} MarketParticipantPositionMessage;

/* any Market Participant Position Message at all: every byte one the checker chooses */
static void any_market_participant_position_message(MarketParticipantPositionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->stock_alphanumeric_6[i] = arbitrary(); }
  record->primary_market_maker = arbitrary();
  record->market_maker_mode = arbitrary();
  record->market_participant_state = arbitrary();
}

/* Market Participant Position Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_market_participant_position_message(const MarketParticipantPositionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock_alphanumeric_6[i]; }
  wire[at++] = record->primary_market_maker;
  wire[at++] = record->market_maker_mode;
  wire[at++] = record->market_participant_state;

  return at;
}

/* Market Participant Position Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_market_participant_position_message(MarketParticipantPositionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->stock_alphanumeric_6[i] = wire[at++]; }
  record->primary_market_maker = wire[at++];
  record->market_maker_mode = wire[at++];
  record->market_participant_state = wire[at++];

  return at;
}

/* what was read of Market Participant Position Message is what was written, byte for byte */
static void equal_market_participant_position_message(const MarketParticipantPositionMessage *read, const MarketParticipantPositionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->stock_alphanumeric_6[i] == written->stock_alphanumeric_6[i]); }
  assert(read->primary_market_maker == written->primary_market_maker);
  assert(read->market_maker_mode == written->market_maker_mode);
  assert(read->market_participant_state == written->market_participant_state);
}

/* Market Participant Position Message: written and read back, then read and written back */
static void check_market_participant_position_message(void) {
  MarketParticipantPositionMessage sent;
  MarketParticipantPositionMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_market_participant_position_message(&sent);
  assert(encode_market_participant_position_message(&sent, wire, 0) == 13);
  assert(decode_market_participant_position_message(&got, wire, 0) == 13);
  equal_market_participant_position_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_market_participant_position_message(&got, wire, 0) == 13);
  assert(encode_market_participant_position_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message: 36 bytes --------------------------------------------- */

/* An Add Order Message indicates that a new order has been accepted by the NASDAQ system and was added to the displayable book. The message includes a day-unique Order Reference Number used by NASDAQ to track the order. This message will be generated for unattributed orders in the NASDAQ Single Book system. This is the Add Order Anonymous format, which in 3.1f carries a Display field. */
typedef struct {
  uint8_t order_reference_number[12];  /* bytes 0 to 11 */
  uint8_t side;                        /* byte 12 */
  uint8_t shares_numeric_6[6];         /* bytes 13 to 18 */
  uint8_t stock_alpha_6[6];            /* bytes 19 to 24 */
  uint8_t price[10];                   /* bytes 25 to 34 */
  uint8_t display;                     /* byte 35 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares_numeric_6[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->stock_alpha_6[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  record->display = arbitrary();
}

/* Add Order Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares_numeric_6[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock_alpha_6[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->display;

  return at;
}

/* Add Order Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares_numeric_6[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->stock_alpha_6[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  record->display = wire[at++];

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->shares_numeric_6[i] == written->shares_numeric_6[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->stock_alpha_6[i] == written->stock_alpha_6[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->display == written->display);
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 36);
  assert(decode_add_order_message(&got, wire, 0) == 36);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 36);
  assert(encode_add_order_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order With Mpid Message: 39 bytes ----------------------------------- */

/* This message will be generated for attributed orders and quotations entered into the NASDAQ Single Book system. */
typedef struct {
  uint8_t order_reference_number[12];  /* bytes 0 to 11 */
  uint8_t side;                        /* byte 12 */
  uint8_t shares_numeric_6[6];         /* bytes 13 to 18 */
  uint8_t stock_alpha_6[6];            /* bytes 19 to 24 */
  uint8_t price[10];                   /* bytes 25 to 34 */
  uint8_t attribution[4];              /* bytes 35 to 38 */
} AddOrderWithMpidMessage;

/* any Add Order With Mpid Message at all: every byte one the checker chooses */
static void any_add_order_with_mpid_message(AddOrderWithMpidMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares_numeric_6[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->stock_alpha_6[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->attribution[i] = arbitrary(); }
}

/* Add Order With Mpid Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_add_order_with_mpid_message(const AddOrderWithMpidMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares_numeric_6[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock_alpha_6[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->attribution[i]; }

  return at;
}

/* Add Order With Mpid Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_add_order_with_mpid_message(AddOrderWithMpidMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares_numeric_6[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->stock_alpha_6[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->attribution[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order With Mpid Message is what was written, byte for byte */
static void equal_add_order_with_mpid_message(const AddOrderWithMpidMessage *read, const AddOrderWithMpidMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->shares_numeric_6[i] == written->shares_numeric_6[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->stock_alpha_6[i] == written->stock_alpha_6[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->attribution[i] == written->attribution[i]); }
}

/* Add Order With Mpid Message: written and read back, then read and written back */
static void check_add_order_with_mpid_message(void) {
  AddOrderWithMpidMessage sent;
  AddOrderWithMpidMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_add_order_with_mpid_message(&sent);
  assert(encode_add_order_with_mpid_message(&sent, wire, 0) == 39);
  assert(decode_add_order_with_mpid_message(&got, wire, 0) == 39);
  equal_add_order_with_mpid_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_with_mpid_message(&got, wire, 0) == 39);
  assert(encode_add_order_with_mpid_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 30 bytes ---------------------------------------- */

/* This message is sent whenever an order on the book is executed in whole or in part. */
typedef struct {
  uint8_t order_reference_number[12];  /* bytes 0 to 11 */
  uint8_t executed_shares[6];          /* bytes 12 to 17 */
  uint8_t match_number[12];            /* bytes 18 to 29 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->executed_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->executed_shares[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Order Executed Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->executed_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->executed_shares[i] == written->executed_shares[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->match_number[i] == written->match_number[i]); }
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

/* ---- Order Executed With Price Message: 41 bytes ----------------------------- */

/* This message is sent whenever an order on the book is executed in whole or in part at a price different from the initial display price. */
typedef struct {
  uint8_t order_reference_number[12];  /* bytes 0 to 11 */
  uint8_t executed_shares[6];          /* bytes 12 to 17 */
  uint8_t match_number[12];            /* bytes 18 to 29 */
  uint8_t printable;                   /* byte 30 */
  uint8_t execution_price[10];         /* bytes 31 to 40 */
} OrderExecutedWithPriceMessage;

/* any Order Executed With Price Message at all: every byte one the checker chooses */
static void any_order_executed_with_price_message(OrderExecutedWithPriceMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->executed_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = arbitrary(); }
  record->printable = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->execution_price[i] = arbitrary(); }
}

/* Order Executed With Price Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_with_price_message(const OrderExecutedWithPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->executed_shares[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->printable;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->execution_price[i]; }

  return at;
}

/* Order Executed With Price Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_with_price_message(OrderExecutedWithPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->executed_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = wire[at++]; }
  record->printable = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->execution_price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed With Price Message is what was written, byte for byte */
static void equal_order_executed_with_price_message(const OrderExecutedWithPriceMessage *read, const OrderExecutedWithPriceMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->executed_shares[i] == written->executed_shares[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->printable == written->printable);
  for (size_t i = 0; i < 10; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
}

/* Order Executed With Price Message: written and read back, then read and written back */
static void check_order_executed_with_price_message(void) {
  OrderExecutedWithPriceMessage sent;
  OrderExecutedWithPriceMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_order_executed_with_price_message(&sent);
  assert(encode_order_executed_with_price_message(&sent, wire, 0) == 41);
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 41);
  equal_order_executed_with_price_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 41);
  assert(encode_order_executed_with_price_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Message: 18 bytes ------------------------------------------ */

/* This message is sent whenever an order on the book is modified as a result of a partial cancellation. */
typedef struct {
  uint8_t order_reference_number[12];  /* bytes 0 to 11 */
  uint8_t canceled_shares[6];          /* bytes 12 to 17 */
} OrderCancelMessage;

/* any Order Cancel Message at all: every byte one the checker chooses */
static void any_order_cancel_message(OrderCancelMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->canceled_shares[i] = arbitrary(); }
}

/* Order Cancel Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_message(const OrderCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->canceled_shares[i]; }

  return at;
}

/* Order Cancel Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_message(OrderCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->canceled_shares[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Message is what was written, byte for byte */
static void equal_order_cancel_message(const OrderCancelMessage *read, const OrderCancelMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->canceled_shares[i] == written->canceled_shares[i]); }
}

/* Order Cancel Message: written and read back, then read and written back */
static void check_order_cancel_message(void) {
  OrderCancelMessage sent;
  OrderCancelMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_order_cancel_message(&sent);
  assert(encode_order_cancel_message(&sent, wire, 0) == 18);
  assert(decode_order_cancel_message(&got, wire, 0) == 18);
  equal_order_cancel_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_message(&got, wire, 0) == 18);
  assert(encode_order_cancel_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Delete Message: 12 bytes ------------------------------------------ */

/* This message is sent whenever an order on the book is being cancelled. All remaining shares are no longer accessible so the order should be removed from the book. */
typedef struct {
  uint8_t order_reference_number[12];  /* bytes 0 to 11 */
} OrderDeleteMessage;

/* any Order Delete Message at all: every byte one the checker chooses */
static void any_order_delete_message(OrderDeleteMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = arbitrary(); }
}

/* Order Delete Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_order_delete_message(const OrderDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_reference_number[i]; }

  return at;
}

/* Order Delete Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_order_delete_message(OrderDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Delete Message is what was written, byte for byte */
static void equal_order_delete_message(const OrderDeleteMessage *read, const OrderDeleteMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
}

/* Order Delete Message: written and read back, then read and written back */
static void check_order_delete_message(void) {
  OrderDeleteMessage sent;
  OrderDeleteMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_order_delete_message(&sent);
  assert(encode_order_delete_message(&sent, wire, 0) == 12);
  assert(decode_order_delete_message(&got, wire, 0) == 12);
  equal_order_delete_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_order_delete_message(&got, wire, 0) == 12);
  assert(encode_order_delete_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replace Message: 41 bytes ----------------------------------------- */

/* This message is sent whenever an order on the book has been cancel and replaced. All remaining shares from the original order are no longer accessible, and must be removed. The new order details are provided for the replacement, along with a new order reference number which will be used henceforth. The side, stock, and attribution (if any) remain the same as the original order, so they are not given in this message. */
typedef struct {
  uint8_t original_order_reference_number[12];  /* bytes 0 to 11 */
  uint8_t new_order_reference_number[12];       /* bytes 12 to 23 */
  uint8_t shares_numeric_6[6];                  /* bytes 24 to 29 */
  uint8_t price[10];                            /* bytes 30 to 39 */
  uint8_t display;                              /* byte 40 */
} OrderReplaceMessage;

/* any Order Replace Message at all: every byte one the checker chooses */
static void any_order_replace_message(OrderReplaceMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->original_order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->new_order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->shares_numeric_6[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  record->display = arbitrary();
}

/* Order Replace Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_order_replace_message(const OrderReplaceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->original_order_reference_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->new_order_reference_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares_numeric_6[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->display;

  return at;
}

/* Order Replace Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_order_replace_message(OrderReplaceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->original_order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->new_order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->shares_numeric_6[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  record->display = wire[at++];

  return at;
}

/* what was read of Order Replace Message is what was written, byte for byte */
static void equal_order_replace_message(const OrderReplaceMessage *read, const OrderReplaceMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->original_order_reference_number[i] == written->original_order_reference_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->new_order_reference_number[i] == written->new_order_reference_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->shares_numeric_6[i] == written->shares_numeric_6[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->display == written->display);
}

/* Order Replace Message: written and read back, then read and written back */
static void check_order_replace_message(void) {
  OrderReplaceMessage sent;
  OrderReplaceMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_order_replace_message(&sent);
  assert(encode_order_replace_message(&sent, wire, 0) == 41);
  assert(decode_order_replace_message(&got, wire, 0) == 41);
  equal_order_replace_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replace_message(&got, wire, 0) == 41);
  assert(encode_order_replace_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Display Message: 12 bytes ----------------------------------------- */

/* This message is disseminated to alert the TotalView-ITCH users that a Flash order has been added to the continuous order book for display on all NASDAQ data feeds. */
typedef struct {
  uint8_t order_reference_number[12];  /* bytes 0 to 11 */
} OrderDisplayMessage;

/* any Order Display Message at all: every byte one the checker chooses */
static void any_order_display_message(OrderDisplayMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = arbitrary(); }
}

/* Order Display Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_order_display_message(const OrderDisplayMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_reference_number[i]; }

  return at;
}

/* Order Display Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_order_display_message(OrderDisplayMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Display Message is what was written, byte for byte */
static void equal_order_display_message(const OrderDisplayMessage *read, const OrderDisplayMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
}

/* Order Display Message: written and read back, then read and written back */
static void check_order_display_message(void) {
  OrderDisplayMessage sent;
  OrderDisplayMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_order_display_message(&sent);
  assert(encode_order_display_message(&sent, wire, 0) == 12);
  assert(decode_order_display_message(&got, wire, 0) == 12);
  equal_order_display_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_order_display_message(&got, wire, 0) == 12);
  assert(encode_order_display_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 47 bytes ------------------------------------------------- */

/* The Trade Message is designed to provide execution details for normal match events involving non-displayable order types. */
typedef struct {
  uint8_t order_reference_number[12];  /* bytes 0 to 11 */
  uint8_t side;                        /* byte 12 */
  uint8_t shares_numeric_6[6];         /* bytes 13 to 18 */
  uint8_t stock_alpha_6[6];            /* bytes 19 to 24 */
  uint8_t price[10];                   /* bytes 25 to 34 */
  uint8_t match_number[12];            /* bytes 35 to 46 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares_numeric_6[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->stock_alpha_6[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = arbitrary(); }
}

/* Trade Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares_numeric_6[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock_alpha_6[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Trade Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_reference_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares_numeric_6[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->stock_alpha_6[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->shares_numeric_6[i] == written->shares_numeric_6[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->stock_alpha_6[i] == written->stock_alpha_6[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 47);
  assert(decode_trade_message(&got, wire, 0) == 47);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 47);
  assert(encode_trade_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cross Trade Message: 38 bytes ------------------------------------------- */

/* Cross Trade message indicates that NASDAQ has completed its cross process for a specific security. */
typedef struct {
  uint8_t shares_numeric_9[9];  /* bytes 0 to 8 */
  uint8_t stock_alpha_6[6];     /* bytes 9 to 14 */
  uint8_t cross_price[10];      /* bytes 15 to 24 */
  uint8_t match_number[12];     /* bytes 25 to 36 */
  uint8_t cross_type;           /* byte 37 */
} CrossTradeMessage;

/* any Cross Trade Message at all: every byte one the checker chooses */
static void any_cross_trade_message(CrossTradeMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->shares_numeric_9[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->stock_alpha_6[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cross_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = arbitrary(); }
  record->cross_type = arbitrary();
}

/* Cross Trade Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_cross_trade_message(const CrossTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->shares_numeric_9[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock_alpha_6[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cross_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->cross_type;

  return at;
}

/* Cross Trade Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_cross_trade_message(CrossTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->shares_numeric_9[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->stock_alpha_6[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cross_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = wire[at++]; }
  record->cross_type = wire[at++];

  return at;
}

/* what was read of Cross Trade Message is what was written, byte for byte */
static void equal_cross_trade_message(const CrossTradeMessage *read, const CrossTradeMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->shares_numeric_9[i] == written->shares_numeric_9[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->stock_alpha_6[i] == written->stock_alpha_6[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cross_price[i] == written->cross_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->cross_type == written->cross_type);
}

/* Cross Trade Message: written and read back, then read and written back */
static void check_cross_trade_message(void) {
  CrossTradeMessage sent;
  CrossTradeMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_cross_trade_message(&sent);
  assert(encode_cross_trade_message(&sent, wire, 0) == 38);
  assert(decode_cross_trade_message(&got, wire, 0) == 38);
  equal_cross_trade_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_cross_trade_message(&got, wire, 0) == 38);
  assert(encode_cross_trade_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broken Trade Message: 12 bytes ------------------------------------------ */

/* The Broken Trade Message is sent whenever an execution on NASDAQ is broken. */
typedef struct {
  uint8_t match_number[12];  /* bytes 0 to 11 */
} BrokenTradeMessage;

/* any Broken Trade Message at all: every byte one the checker chooses */
static void any_broken_trade_message(BrokenTradeMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = arbitrary(); }
}

/* Broken Trade Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_message(const BrokenTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Broken Trade Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_message(BrokenTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Broken Trade Message is what was written, byte for byte */
static void equal_broken_trade_message(const BrokenTradeMessage *read, const BrokenTradeMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Broken Trade Message: written and read back, then read and written back */
static void check_broken_trade_message(void) {
  BrokenTradeMessage sent;
  BrokenTradeMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_broken_trade_message(&sent);
  assert(encode_broken_trade_message(&sent, wire, 0) == 12);
  assert(decode_broken_trade_message(&got, wire, 0) == 12);
  equal_broken_trade_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_broken_trade_message(&got, wire, 0) == 12);
  assert(encode_broken_trade_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Order Imbalance Indicator Message: 57 bytes ------------------------- */

/* NASDAQ disseminates NOII data at 5-second intervals in the minutes leading up to the NASDAQ Opening Cross, NASDAQ Closing Cross and NASDAQ IPO/Halt Cross. */
typedef struct {
  uint8_t paired_shares[9];             /* bytes 0 to 8 */
  uint8_t imbalance_shares[9];          /* bytes 9 to 17 */
  uint8_t imbalance_direction;          /* byte 18 */
  uint8_t stock_alpha_6[6];             /* bytes 19 to 24 */
  uint8_t far_price[10];                /* bytes 25 to 34 */
  uint8_t near_price[10];               /* bytes 35 to 44 */
  uint8_t current_reference_price[10];  /* bytes 45 to 54 */
  uint8_t cross_type;                   /* byte 55 */
  uint8_t price_variation_indicator;    /* byte 56 */
} NetOrderImbalanceIndicatorMessage;

/* any Net Order Imbalance Indicator Message at all: every byte one the checker chooses */
static void any_net_order_imbalance_indicator_message(NetOrderImbalanceIndicatorMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->paired_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->imbalance_shares[i] = arbitrary(); }
  record->imbalance_direction = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->stock_alpha_6[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->far_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->near_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->current_reference_price[i] = arbitrary(); }
  record->cross_type = arbitrary();
  record->price_variation_indicator = arbitrary();
}

/* Net Order Imbalance Indicator Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_net_order_imbalance_indicator_message(const NetOrderImbalanceIndicatorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->paired_shares[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->imbalance_shares[i]; }
  wire[at++] = record->imbalance_direction;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock_alpha_6[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->far_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->near_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->current_reference_price[i]; }
  wire[at++] = record->cross_type;
  wire[at++] = record->price_variation_indicator;

  return at;
}

/* Net Order Imbalance Indicator Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_net_order_imbalance_indicator_message(NetOrderImbalanceIndicatorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->paired_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->imbalance_shares[i] = wire[at++]; }
  record->imbalance_direction = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->stock_alpha_6[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->far_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->near_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->current_reference_price[i] = wire[at++]; }
  record->cross_type = wire[at++];
  record->price_variation_indicator = wire[at++];

  return at;
}

/* what was read of Net Order Imbalance Indicator Message is what was written, byte for byte */
static void equal_net_order_imbalance_indicator_message(const NetOrderImbalanceIndicatorMessage *read, const NetOrderImbalanceIndicatorMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->paired_shares[i] == written->paired_shares[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->imbalance_shares[i] == written->imbalance_shares[i]); }
  assert(read->imbalance_direction == written->imbalance_direction);
  for (size_t i = 0; i < 6; i++) { assert(read->stock_alpha_6[i] == written->stock_alpha_6[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->far_price[i] == written->far_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->near_price[i] == written->near_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->current_reference_price[i] == written->current_reference_price[i]); }
  assert(read->cross_type == written->cross_type);
  assert(read->price_variation_indicator == written->price_variation_indicator);
}

/* Net Order Imbalance Indicator Message: written and read back, then read and written back */
static void check_net_order_imbalance_indicator_message(void) {
  NetOrderImbalanceIndicatorMessage sent;
  NetOrderImbalanceIndicatorMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_net_order_imbalance_indicator_message(&sent);
  assert(encode_net_order_imbalance_indicator_message(&sent, wire, 0) == 57);
  assert(decode_net_order_imbalance_indicator_message(&got, wire, 0) == 57);
  equal_net_order_imbalance_indicator_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_net_order_imbalance_indicator_message(&got, wire, 0) == 57);
  assert(encode_net_order_imbalance_indicator_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_seconds_message();
  check_milliseconds_message();
  check_system_event_message();
  check_stock_directory_message();
  check_stock_trading_action_message();
  check_market_participant_position_message();
  check_add_order_message();
  check_add_order_with_mpid_message();
  check_order_executed_message();
  check_order_executed_with_price_message();
  check_order_cancel_message();
  check_order_delete_message();
  check_order_replace_message();
  check_order_display_message();
  check_trade_message();
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
