// tradelogiq/lynxats/multicastlevel2/LynxAts_MulticastLevel2_v2_01_Udp.c
/*
 * Tradelogiq Markets Inc. Lynx Multicast Level 2
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

/* Tradelogiq Qtp Downstream Packet Header */
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

/* Tradelogiq Qtp Message Block Header */
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

/* The system event message type is used to signal a market or data feed handler event. */
typedef struct {
  uint8_t event_code;     /* byte 0 */
  uint8_t reserved_2[2];  /* bytes 1 to 2 */
  uint8_t timestamp[8];   /* bytes 3 to 10 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  record->event_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* System Event Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->event_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* System Event Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  record->event_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  assert(read->event_code == written->event_code);
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
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

/* ---- Stock Directory Message: 39 bytes --------------------------------------- */

/* At the start of each trading day, Tradelogiq disseminates stock directory messages for all supported securities. */
typedef struct {
  uint8_t market;              /* byte 0 */
  uint8_t stock[10];           /* bytes 1 to 10 */
  uint8_t timestamp[8];        /* bytes 11 to 18 */
  uint8_t board_lot_size[4];   /* bytes 19 to 22 */
  uint8_t instrument_id[2];    /* bytes 23 to 24 */
  uint8_t shortable;           /* byte 25 */
  uint8_t dividend_indicator;  /* byte 26 */
  uint8_t reserved_9[9];       /* bytes 27 to 35 */
  uint8_t currency[3];         /* bytes 36 to 38 */
} StockDirectoryMessage;

/* any Stock Directory Message at all: every byte one the checker chooses */
static void any_stock_directory_message(StockDirectoryMessage *record) {
  record->market = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  record->shortable = arbitrary();
  record->dividend_indicator = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
}

/* Stock Directory Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_stock_directory_message(const StockDirectoryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->board_lot_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->shortable;
  wire[at++] = record->dividend_indicator;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->reserved_9[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }

  return at;
}

/* Stock Directory Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_stock_directory_message(StockDirectoryMessage *record, const uint8_t *wire, size_t at) {
  record->market = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  record->shortable = wire[at++];
  record->dividend_indicator = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Directory Message is what was written, byte for byte */
static void equal_stock_directory_message(const StockDirectoryMessage *read, const StockDirectoryMessage *written) {
  assert(read->market == written->market);
  for (size_t i = 0; i < 10; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->board_lot_size[i] == written->board_lot_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->shortable == written->shortable);
  assert(read->dividend_indicator == written->dividend_indicator);
  for (size_t i = 0; i < 9; i++) { assert(read->reserved_9[i] == written->reserved_9[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
}

/* Stock Directory Message: written and read back, then read and written back */
static void check_stock_directory_message(void) {
  StockDirectoryMessage sent;
  StockDirectoryMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_stock_directory_message(&sent);
  assert(encode_stock_directory_message(&sent, wire, 0) == 39);
  assert(decode_stock_directory_message(&got, wire, 0) == 39);
  equal_stock_directory_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_directory_message(&got, wire, 0) == 39);
  assert(encode_stock_directory_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Extended Stock Directory Message: 71 bytes ------------------------------ */

/* Extended Stock Directory messages carry the additional reference data of bonds, debentures, rights, notes and warrants. */
typedef struct {
  uint8_t market;             /* byte 0 */
  uint8_t stock[10];          /* bytes 1 to 10 */
  uint8_t timestamp[8];       /* bytes 11 to 18 */
  uint8_t board_lot_size[4];  /* bytes 19 to 22 */
  uint8_t instrument_id[2];   /* bytes 23 to 24 */
  uint8_t shortable;          /* byte 25 */
  uint8_t frequency;          /* byte 26 */
  uint8_t reserved_9[9];      /* bytes 27 to 35 */
  uint8_t currency[3];        /* bytes 36 to 38 */
  uint8_t security_type;      /* byte 39 */
  uint8_t expiry_date[8];     /* bytes 40 to 47 */
  uint8_t description[20];    /* bytes 48 to 67 */
  uint8_t reserved_3[3];      /* bytes 68 to 70 */
} ExtendedStockDirectoryMessage;

/* any Extended Stock Directory Message at all: every byte one the checker chooses */
static void any_extended_stock_directory_message(ExtendedStockDirectoryMessage *record) {
  record->market = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  record->shortable = arbitrary();
  record->frequency = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  record->security_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->expiry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->description[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Extended Stock Directory Message to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_extended_stock_directory_message(const ExtendedStockDirectoryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->board_lot_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->shortable;
  wire[at++] = record->frequency;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->reserved_9[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->security_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expiry_date[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->description[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Extended Stock Directory Message off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_extended_stock_directory_message(ExtendedStockDirectoryMessage *record, const uint8_t *wire, size_t at) {
  record->market = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  record->shortable = wire[at++];
  record->frequency = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  record->security_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->expiry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->description[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Extended Stock Directory Message is what was written, byte for byte */
static void equal_extended_stock_directory_message(const ExtendedStockDirectoryMessage *read, const ExtendedStockDirectoryMessage *written) {
  assert(read->market == written->market);
  for (size_t i = 0; i < 10; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->board_lot_size[i] == written->board_lot_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->shortable == written->shortable);
  assert(read->frequency == written->frequency);
  for (size_t i = 0; i < 9; i++) { assert(read->reserved_9[i] == written->reserved_9[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->security_type == written->security_type);
  for (size_t i = 0; i < 8; i++) { assert(read->expiry_date[i] == written->expiry_date[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->description[i] == written->description[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Extended Stock Directory Message: written and read back, then read and written back */
static void check_extended_stock_directory_message(void) {
  ExtendedStockDirectoryMessage sent;
  ExtendedStockDirectoryMessage got;
  uint8_t wire[71];
  uint8_t again[71];

  any_extended_stock_directory_message(&sent);
  assert(encode_extended_stock_directory_message(&sent, wire, 0) == 71);
  assert(decode_extended_stock_directory_message(&got, wire, 0) == 71);
  equal_extended_stock_directory_message(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_extended_stock_directory_message(&got, wire, 0) == 71);
  assert(encode_extended_stock_directory_message(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Trading Action Message: 15 bytes ---------------------------------- */

/* Tradelogiq uses this administrative message to indicate the current trading status of a security. */
typedef struct {
  uint8_t trading_state;     /* byte 0 */
  uint8_t instrument_id[2];  /* bytes 1 to 2 */
  uint8_t timestamp[8];      /* bytes 3 to 10 */
  uint8_t reason[4];         /* bytes 11 to 14 */
} StockTradingActionMessage;

/* any Stock Trading Action Message at all: every byte one the checker chooses */
static void any_stock_trading_action_message(StockTradingActionMessage *record) {
  record->trading_state = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reason[i] = arbitrary(); }
}

/* Stock Trading Action Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_stock_trading_action_message(const StockTradingActionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_state;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Stock Trading Action Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_stock_trading_action_message(StockTradingActionMessage *record, const uint8_t *wire, size_t at) {
  record->trading_state = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Trading Action Message is what was written, byte for byte */
static void equal_stock_trading_action_message(const StockTradingActionMessage *read, const StockTradingActionMessage *written) {
  assert(read->trading_state == written->trading_state);
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reason[i] == written->reason[i]); }
}

/* Stock Trading Action Message: written and read back, then read and written back */
static void check_stock_trading_action_message(void) {
  StockTradingActionMessage sent;
  StockTradingActionMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_stock_trading_action_message(&sent);
  assert(encode_stock_trading_action_message(&sent, wire, 0) == 15);
  assert(decode_stock_trading_action_message(&got, wire, 0) == 15);
  equal_stock_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_trading_action_message(&got, wire, 0) == 15);
  assert(encode_stock_trading_action_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message: 27 bytes --------------------------------------------- */

/* An Add Order Message indicates that a new order has been accepted by Omega ATS or Lynx ATS and was added to the visible order book. */
typedef struct {
  uint8_t buy_sell_indicator;         /* byte 0 */
  uint8_t instrument_id[2];           /* bytes 1 to 2 */
  uint8_t timestamp[8];               /* bytes 3 to 10 */
  uint8_t order_reference_number[4];  /* bytes 11 to 14 */
  uint8_t shares[4];                  /* bytes 15 to 18 */
  uint8_t price[4];                   /* bytes 19 to 22 */
  uint8_t exec_broker_id[2];          /* bytes 23 to 24 */
  uint8_t reserved_2[2];              /* bytes 25 to 26 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->exec_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Add Order Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->exec_broker_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Add Order Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->exec_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->exec_broker_id[i] == written->exec_broker_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 27);
  assert(decode_add_order_message(&got, wire, 0) == 27);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 27);
  assert(encode_add_order_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 27 bytes ---------------------------------------- */

/* This message is sent whenever an order on the book is executed in whole or in part. */
typedef struct {
  uint8_t marker;                     /* byte 0 */
  uint8_t instrument_id[2];           /* bytes 1 to 2 */
  uint8_t timestamp[8];               /* bytes 3 to 10 */
  uint8_t order_reference_number[4];  /* bytes 11 to 14 */
  uint8_t executed_shares[4];         /* bytes 15 to 18 */
  uint8_t match_number[4];            /* bytes 19 to 22 */
  uint8_t contra_broker_id[2];        /* bytes 23 to 24 */
  uint8_t reserved_2[2];              /* bytes 25 to 26 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  record->marker = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->contra_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->marker;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->contra_broker_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Order Executed Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  record->marker = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->contra_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  assert(read->marker == written->marker);
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_shares[i] == written->executed_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->contra_broker_id[i] == written->contra_broker_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 27);
  assert(decode_order_executed_message(&got, wire, 0) == 27);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 27);
  assert(encode_order_executed_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed With Price Message: 31 bytes ----------------------------- */

/* This message is sent whenever an order on the book is executed at a display price different from the original. */
typedef struct {
  uint8_t marker;                     /* byte 0 */
  uint8_t instrument_id[2];           /* bytes 1 to 2 */
  uint8_t timestamp[8];               /* bytes 3 to 10 */
  uint8_t order_reference_number[4];  /* bytes 11 to 14 */
  uint8_t executed_shares[4];         /* bytes 15 to 18 */
  uint8_t execution_price[4];         /* bytes 19 to 22 */
  uint8_t match_number[4];            /* bytes 23 to 26 */
  uint8_t contra_broker_id[2];        /* bytes 27 to 28 */
  uint8_t reserved_2[2];              /* bytes 29 to 30 */
} OrderExecutedWithPriceMessage;

/* any Order Executed With Price Message at all: every byte one the checker chooses */
static void any_order_executed_with_price_message(OrderExecutedWithPriceMessage *record) {
  record->marker = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->contra_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Order Executed With Price Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_with_price_message(const OrderExecutedWithPriceMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->marker;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->contra_broker_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Order Executed With Price Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_with_price_message(OrderExecutedWithPriceMessage *record, const uint8_t *wire, size_t at) {
  record->marker = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->contra_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed With Price Message is what was written, byte for byte */
static void equal_order_executed_with_price_message(const OrderExecutedWithPriceMessage *read, const OrderExecutedWithPriceMessage *written) {
  assert(read->marker == written->marker);
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_shares[i] == written->executed_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->contra_broker_id[i] == written->contra_broker_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Order Executed With Price Message: written and read back, then read and written back */
static void check_order_executed_with_price_message(void) {
  OrderExecutedWithPriceMessage sent;
  OrderExecutedWithPriceMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_order_executed_with_price_message(&sent);
  assert(encode_order_executed_with_price_message(&sent, wire, 0) == 31);
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 31);
  equal_order_executed_with_price_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 31);
  assert(encode_order_executed_with_price_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Delete Message: 15 bytes ------------------------------------------ */

/* This message is sent whenever an order on the book is being cancelled. */
typedef struct {
  uint8_t reserved_1;                 /* byte 0 */
  uint8_t instrument_id[2];           /* bytes 1 to 2 */
  uint8_t timestamp[8];               /* bytes 3 to 10 */
  uint8_t order_reference_number[4];  /* bytes 11 to 14 */
} OrderDeleteMessage;

/* any Order Delete Message at all: every byte one the checker chooses */
static void any_order_delete_message(OrderDeleteMessage *record) {
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = arbitrary(); }
}

/* Order Delete Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_order_delete_message(const OrderDeleteMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_reference_number[i]; }

  return at;
}

/* Order Delete Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_order_delete_message(OrderDeleteMessage *record, const uint8_t *wire, size_t at) {
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Delete Message is what was written, byte for byte */
static void equal_order_delete_message(const OrderDeleteMessage *read, const OrderDeleteMessage *written) {
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
}

/* Order Delete Message: written and read back, then read and written back */
static void check_order_delete_message(void) {
  OrderDeleteMessage sent;
  OrderDeleteMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_order_delete_message(&sent);
  assert(encode_order_delete_message(&sent, wire, 0) == 15);
  assert(decode_order_delete_message(&got, wire, 0) == 15);
  equal_order_delete_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_order_delete_message(&got, wire, 0) == 15);
  assert(encode_order_delete_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replace Message: 27 bytes ----------------------------------------- */

/* This message is sent whenever an order on the book has been cancelled and replaced. */
typedef struct {
  uint8_t reserved_1;                          /* byte 0 */
  uint8_t instrument_id[2];                    /* bytes 1 to 2 */
  uint8_t timestamp[8];                        /* bytes 3 to 10 */
  uint8_t original_order_reference_number[4];  /* bytes 11 to 14 */
  uint8_t new_order_reference_number[4];       /* bytes 15 to 18 */
  uint8_t shares[4];                           /* bytes 19 to 22 */
  uint8_t price[4];                            /* bytes 23 to 26 */
} OrderReplaceMessage;

/* any Order Replace Message at all: every byte one the checker chooses */
static void any_order_replace_message(OrderReplaceMessage *record) {
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->new_order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
}

/* Order Replace Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_order_replace_message(const OrderReplaceMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Replace Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_order_replace_message(OrderReplaceMessage *record, const uint8_t *wire, size_t at) {
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->new_order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Replace Message is what was written, byte for byte */
static void equal_order_replace_message(const OrderReplaceMessage *read, const OrderReplaceMessage *written) {
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_order_reference_number[i] == written->original_order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->new_order_reference_number[i] == written->new_order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Replace Message: written and read back, then read and written back */
static void check_order_replace_message(void) {
  OrderReplaceMessage sent;
  OrderReplaceMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_order_replace_message(&sent);
  assert(encode_order_replace_message(&sent, wire, 0) == 27);
  assert(decode_order_replace_message(&got, wire, 0) == 27);
  equal_order_replace_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replace_message(&got, wire, 0) == 27);
  assert(encode_order_replace_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Message: 19 bytes ------------------------------------------ */

/* This message is sent whenever an order on the book is modified as a result of a partial cancellation. */
typedef struct {
  uint8_t reserved_1;                 /* byte 0 */
  uint8_t instrument_id[2];           /* bytes 1 to 2 */
  uint8_t timestamp[8];               /* bytes 3 to 10 */
  uint8_t order_reference_number[4];  /* bytes 11 to 14 */
  uint8_t cancelled_shares[4];        /* bytes 15 to 18 */
} OrderCancelMessage;

/* any Order Cancel Message at all: every byte one the checker chooses */
static void any_order_cancel_message(OrderCancelMessage *record) {
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancelled_shares[i] = arbitrary(); }
}

/* Order Cancel Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_message(const OrderCancelMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancelled_shares[i]; }

  return at;
}

/* Order Cancel Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_message(OrderCancelMessage *record, const uint8_t *wire, size_t at) {
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancelled_shares[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Message is what was written, byte for byte */
static void equal_order_cancel_message(const OrderCancelMessage *read, const OrderCancelMessage *written) {
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancelled_shares[i] == written->cancelled_shares[i]); }
}

/* Order Cancel Message: written and read back, then read and written back */
static void check_order_cancel_message(void) {
  OrderCancelMessage sent;
  OrderCancelMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_order_cancel_message(&sent);
  assert(encode_order_cancel_message(&sent, wire, 0) == 19);
  assert(decode_order_cancel_message(&got, wire, 0) == 19);
  equal_order_cancel_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_message(&got, wire, 0) == 19);
  assert(encode_order_cancel_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 31 bytes ------------------------------------------------- */

/* The Trade Message is designed to provide execution details for normal match events involving non-displayed order types. */
typedef struct {
  uint8_t side;                    /* byte 0 */
  uint8_t instrument_id[2];        /* bytes 1 to 2 */
  uint8_t timestamp[8];            /* bytes 3 to 10 */
  uint8_t midpoint_book_trade[4];  /* bytes 11 to 14 */
  uint8_t shares[4];               /* bytes 15 to 18 */
  uint8_t price[4];                /* bytes 19 to 22 */
  uint8_t match_number[4];         /* bytes 23 to 26 */
  uint8_t buy_broker_id[2];        /* bytes 27 to 28 */
  uint8_t sell_broker_id[2];       /* bytes 29 to 30 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  record->side = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->midpoint_book_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->buy_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->sell_broker_id[i] = arbitrary(); }
}

/* Trade Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->side;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->midpoint_book_trade[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->buy_broker_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sell_broker_id[i]; }

  return at;
}

/* Trade Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  record->side = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->midpoint_book_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->buy_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->sell_broker_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  assert(read->side == written->side);
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->midpoint_book_trade[i] == written->midpoint_book_trade[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->buy_broker_id[i] == written->buy_broker_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->sell_broker_id[i] == written->sell_broker_id[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 31);
  assert(decode_trade_message(&got, wire, 0) == 31);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 31);
  assert(encode_trade_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cross Trade Message: 31 bytes ------------------------------------------- */

/* Cross trades are only accepted on Omega ATS. */
typedef struct {
  uint8_t cross_type;         /* byte 0 */
  uint8_t instrument_id[2];   /* bytes 1 to 2 */
  uint8_t timestamp[8];       /* bytes 3 to 10 */
  uint8_t shares[4];          /* bytes 11 to 14 */
  uint8_t price[4];           /* bytes 15 to 18 */
  uint8_t match_number[4];    /* bytes 19 to 22 */
  uint8_t buy_broker_id[2];   /* bytes 23 to 24 */
  uint8_t sell_broker_id[2];  /* bytes 25 to 26 */
  uint8_t bypass;             /* byte 27 */
  uint8_t settlement_type;    /* byte 28 */
  uint8_t reserved_2[2];      /* bytes 29 to 30 */
} CrossTradeMessage;

/* any Cross Trade Message at all: every byte one the checker chooses */
static void any_cross_trade_message(CrossTradeMessage *record) {
  record->cross_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->buy_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->sell_broker_id[i] = arbitrary(); }
  record->bypass = arbitrary();
  record->settlement_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Cross Trade Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_cross_trade_message(const CrossTradeMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->cross_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->buy_broker_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sell_broker_id[i]; }
  wire[at++] = record->bypass;
  wire[at++] = record->settlement_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Cross Trade Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_cross_trade_message(CrossTradeMessage *record, const uint8_t *wire, size_t at) {
  record->cross_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->buy_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->sell_broker_id[i] = wire[at++]; }
  record->bypass = wire[at++];
  record->settlement_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Cross Trade Message is what was written, byte for byte */
static void equal_cross_trade_message(const CrossTradeMessage *read, const CrossTradeMessage *written) {
  assert(read->cross_type == written->cross_type);
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->buy_broker_id[i] == written->buy_broker_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->sell_broker_id[i] == written->sell_broker_id[i]); }
  assert(read->bypass == written->bypass);
  assert(read->settlement_type == written->settlement_type);
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Cross Trade Message: written and read back, then read and written back */
static void check_cross_trade_message(void) {
  CrossTradeMessage sent;
  CrossTradeMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_cross_trade_message(&sent);
  assert(encode_cross_trade_message(&sent, wire, 0) == 31);
  assert(decode_cross_trade_message(&got, wire, 0) == 31);
  equal_cross_trade_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_cross_trade_message(&got, wire, 0) == 31);
  assert(encode_cross_trade_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Bust Message: 15 bytes -------------------------------------------- */

/* The Trade Bust message is sent whenever an execution on Omega ATS or Lynx ATS is cancelled. */
typedef struct {
  uint8_t reserved_1;        /* byte 0 */
  uint8_t instrument_id[2];  /* bytes 1 to 2 */
  uint8_t timestamp[8];      /* bytes 3 to 10 */
  uint8_t match_number[4];   /* bytes 11 to 14 */
} TradeBustMessage;

/* any Trade Bust Message at all: every byte one the checker chooses */
static void any_trade_bust_message(TradeBustMessage *record) {
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
}

/* Trade Bust Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_trade_bust_message(const TradeBustMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Trade Bust Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_trade_bust_message(TradeBustMessage *record, const uint8_t *wire, size_t at) {
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Bust Message is what was written, byte for byte */
static void equal_trade_bust_message(const TradeBustMessage *read, const TradeBustMessage *written) {
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Trade Bust Message: written and read back, then read and written back */
static void check_trade_bust_message(void) {
  TradeBustMessage sent;
  TradeBustMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_trade_bust_message(&sent);
  assert(encode_trade_bust_message(&sent, wire, 0) == 15);
  assert(decode_trade_bust_message(&got, wire, 0) == 15);
  equal_trade_bust_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_bust_message(&got, wire, 0) == 15);
  assert(encode_trade_bust_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Amend Message: 39 bytes ------------------------------------------- */

/* The Trade Amend/Correction message is sent whenever an execution on Omega ATS or Lynx ATS is amended. */
typedef struct {
  uint8_t reserved_1;                /* byte 0 */
  uint8_t instrument_id[2];          /* bytes 1 to 2 */
  uint8_t timestamp[8];              /* bytes 3 to 10 */
  uint8_t original_trade_id[4];      /* bytes 11 to 14 */
  uint8_t original_trade_price[8];   /* bytes 15 to 22 */
  uint8_t original_trade_size[4];    /* bytes 23 to 26 */
  uint8_t corrected_trade_price[8];  /* bytes 27 to 34 */
  uint8_t corrected_trade_size[4];   /* bytes 35 to 38 */
} TradeAmendMessage;

/* any Trade Amend Message at all: every byte one the checker chooses */
static void any_trade_amend_message(TradeAmendMessage *record) {
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_size[i] = arbitrary(); }
}

/* Trade Amend Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_trade_amend_message(const TradeAmendMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_trade_size[i]; }

  return at;
}

/* Trade Amend Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_trade_amend_message(TradeAmendMessage *record, const uint8_t *wire, size_t at) {
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_trade_size[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Amend Message is what was written, byte for byte */
static void equal_trade_amend_message(const TradeAmendMessage *read, const TradeAmendMessage *written) {
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_id[i] == written->original_trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_trade_price[i] == written->original_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_size[i] == written->original_trade_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_trade_price[i] == written->corrected_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_trade_size[i] == written->corrected_trade_size[i]); }
}

/* Trade Amend Message: written and read back, then read and written back */
static void check_trade_amend_message(void) {
  TradeAmendMessage sent;
  TradeAmendMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_trade_amend_message(&sent);
  assert(encode_trade_amend_message(&sent, wire, 0) == 39);
  assert(decode_trade_amend_message(&got, wire, 0) == 39);
  equal_trade_amend_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_amend_message(&got, wire, 0) == 39);
  assert(encode_trade_amend_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_system_event_message();
  check_stock_directory_message();
  check_extended_stock_directory_message();
  check_stock_trading_action_message();
  check_add_order_message();
  check_order_executed_message();
  check_order_executed_with_price_message();
  check_order_delete_message();
  check_order_replace_message();
  check_order_cancel_message();
  check_trade_message();
  check_cross_trade_message();
  check_trade_bust_message();
  check_trade_amend_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
