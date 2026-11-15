// nasdaq/nsmequities/nois/NsmEquities_Nois_v2_2_2022.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Net Order Imbalance Snapshot
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

/* Itch Mold Udp Packet Header */
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

/* Mold Udp Message Header */
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

/* ---- Stock Directory: 20 bytes ----------------------------------------------- */

/* At the start of each trading day, Nasdaq disseminates stock directory messages for all active symbols in the Nasdaq execution system. */
typedef struct {
  uint8_t symbol[8];             /* bytes 0 to 7 */
  uint8_t market_category;       /* byte 8 */
  uint8_t rfu;                   /* byte 9 */
  uint8_t round_lot_size[6];     /* bytes 10 to 15 */
  uint8_t round_lots_only;       /* byte 16 */
  uint8_t issue_classification;  /* byte 17 */
  uint8_t issue_sub_type[2];     /* bytes 18 to 19 */
} StockDirectory;

/* any Stock Directory at all: every byte one the checker chooses */
static void any_stock_directory(StockDirectory *record) {
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->market_category = arbitrary();
  record->rfu = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->round_lot_size[i] = arbitrary(); }
  record->round_lots_only = arbitrary();
  record->issue_classification = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->issue_sub_type[i] = arbitrary(); }
}

/* Stock Directory to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_stock_directory(const StockDirectory *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->market_category;
  wire[at++] = record->rfu;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->round_lot_size[i]; }
  wire[at++] = record->round_lots_only;
  wire[at++] = record->issue_classification;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->issue_sub_type[i]; }

  return at;
}

/* Stock Directory off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_stock_directory(StockDirectory *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->market_category = wire[at++];
  record->rfu = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->round_lot_size[i] = wire[at++]; }
  record->round_lots_only = wire[at++];
  record->issue_classification = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->issue_sub_type[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Directory is what was written, byte for byte */
static void equal_stock_directory(const StockDirectory *read, const StockDirectory *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->market_category == written->market_category);
  assert(read->rfu == written->rfu);
  for (size_t i = 0; i < 6; i++) { assert(read->round_lot_size[i] == written->round_lot_size[i]); }
  assert(read->round_lots_only == written->round_lots_only);
  assert(read->issue_classification == written->issue_classification);
  for (size_t i = 0; i < 2; i++) { assert(read->issue_sub_type[i] == written->issue_sub_type[i]); }
}

/* Stock Directory: written and read back, then read and written back */
static void check_stock_directory(void) {
  StockDirectory sent;
  StockDirectory got;
  uint8_t wire[20];
  uint8_t again[20];

  any_stock_directory(&sent);
  assert(encode_stock_directory(&sent, wire, 0) == 20);
  assert(decode_stock_directory(&got, wire, 0) == 20);
  equal_stock_directory(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_directory(&got, wire, 0) == 20);
  assert(encode_stock_directory(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Trading Action: 10 bytes ------------------------------------------ */

/* Nasdaq uses this administrative message to indicate the current trading status of a security to the trading community. */
typedef struct {
  uint8_t symbol[8];      /* bytes 0 to 7 */
  uint8_t trading_state;  /* byte 8 */
  uint8_t reason;         /* byte 9 */
} StockTradingAction;

/* any Stock Trading Action at all: every byte one the checker chooses */
static void any_stock_trading_action(StockTradingAction *record) {
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->trading_state = arbitrary();
  record->reason = arbitrary();
}

/* Stock Trading Action to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_stock_trading_action(const StockTradingAction *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->trading_state;
  wire[at++] = record->reason;

  return at;
}

/* Stock Trading Action off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_stock_trading_action(StockTradingAction *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->trading_state = wire[at++];
  record->reason = wire[at++];

  return at;
}

/* what was read of Stock Trading Action is what was written, byte for byte */
static void equal_stock_trading_action(const StockTradingAction *read, const StockTradingAction *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->trading_state == written->trading_state);
  assert(read->reason == written->reason);
}

/* Stock Trading Action: written and read back, then read and written back */
static void check_stock_trading_action(void) {
  StockTradingAction sent;
  StockTradingAction got;
  uint8_t wire[10];
  uint8_t again[10];

  any_stock_trading_action(&sent);
  assert(encode_stock_trading_action(&sent, wire, 0) == 10);
  assert(decode_stock_trading_action(&got, wire, 0) == 10);
  equal_stock_trading_action(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_trading_action(&got, wire, 0) == 10);
  assert(encode_stock_trading_action(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Nois Message: 39 bytes -------------------------------------------------- */

/* Nasdaq Net Order Imbalance Snapshot (NOIS) provides a snapshot of the Nasdaq net order imbalance data at selected time intervals. */
typedef struct {
  uint8_t imbalance_shares[9];          /* bytes 0 to 8 */
  uint8_t imbalance_direction;          /* byte 9 */
  uint8_t symbol[8];                    /* bytes 10 to 17 */
  uint8_t near_price[10];               /* bytes 18 to 27 */
  uint8_t current_reference_price[10];  /* bytes 28 to 37 */
  uint8_t cross_type;                   /* byte 38 */
} NoisMessage;

/* any Nois Message at all: every byte one the checker chooses */
static void any_nois_message(NoisMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->imbalance_shares[i] = arbitrary(); }
  record->imbalance_direction = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->near_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->current_reference_price[i] = arbitrary(); }
  record->cross_type = arbitrary();
}

/* Nois Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_nois_message(const NoisMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->imbalance_shares[i]; }
  wire[at++] = record->imbalance_direction;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->near_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->current_reference_price[i]; }
  wire[at++] = record->cross_type;

  return at;
}

/* Nois Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_nois_message(NoisMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->imbalance_shares[i] = wire[at++]; }
  record->imbalance_direction = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->near_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->current_reference_price[i] = wire[at++]; }
  record->cross_type = wire[at++];

  return at;
}

/* what was read of Nois Message is what was written, byte for byte */
static void equal_nois_message(const NoisMessage *read, const NoisMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->imbalance_shares[i] == written->imbalance_shares[i]); }
  assert(read->imbalance_direction == written->imbalance_direction);
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->near_price[i] == written->near_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->current_reference_price[i] == written->current_reference_price[i]); }
  assert(read->cross_type == written->cross_type);
}

/* Nois Message: written and read back, then read and written back */
static void check_nois_message(void) {
  NoisMessage sent;
  NoisMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_nois_message(&sent);
  assert(encode_nois_message(&sent, wire, 0) == 39);
  assert(decode_nois_message(&got, wire, 0) == 39);
  equal_nois_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_nois_message(&got, wire, 0) == 39);
  assert(encode_nois_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_system_event_message();
  check_stock_directory();
  check_stock_trading_action();
  check_nois_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
