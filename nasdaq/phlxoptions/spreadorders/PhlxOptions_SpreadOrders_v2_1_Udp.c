// nasdaq/phlxoptions/spreadorders/PhlxOptions_SpreadOrders_v2_1_Udp.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Spread Orders
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

/* ---- System Event Message: 11 bytes ------------------------------------------ */

/* The system event message type is used to signal a market or data feed handler event. */
typedef struct {
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t timestamp[8];        /* bytes 2 to 9 */
  uint8_t event_code;          /* byte 10 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->event_code == written->event_code);
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

/* ---- Strategy Trading Action Message: 15 bytes ------------------------------- */

/* The options system uses this administrative message to indicate the current trading status of an index or equity option within the options market. */
typedef struct {
  uint8_t tracking_number[2];     /* bytes 0 to 1 */
  uint8_t timestamp[8];           /* bytes 2 to 9 */
  uint8_t strategy_id[4];         /* bytes 10 to 13 */
  uint8_t current_trading_state;  /* byte 14 */
} StrategyTradingActionMessage;

/* any Strategy Trading Action Message at all: every byte one the checker chooses */
static void any_strategy_trading_action_message(StrategyTradingActionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  record->current_trading_state = arbitrary();
}

/* Strategy Trading Action Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_strategy_trading_action_message(const StrategyTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  wire[at++] = record->current_trading_state;

  return at;
}

/* Strategy Trading Action Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_strategy_trading_action_message(StrategyTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  record->current_trading_state = wire[at++];

  return at;
}

/* what was read of Strategy Trading Action Message is what was written, byte for byte */
static void equal_strategy_trading_action_message(const StrategyTradingActionMessage *read, const StrategyTradingActionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  assert(read->current_trading_state == written->current_trading_state);
}

/* Strategy Trading Action Message: written and read back, then read and written back */
static void check_strategy_trading_action_message(void) {
  StrategyTradingActionMessage sent;
  StrategyTradingActionMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_strategy_trading_action_message(&sent);
  assert(encode_strategy_trading_action_message(&sent, wire, 0) == 15);
  assert(decode_strategy_trading_action_message(&got, wire, 0) == 15);
  equal_strategy_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_strategy_trading_action_message(&got, wire, 0) == 15);
  assert(encode_strategy_trading_action_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Add Order Message: 58 bytes ------------------------------------- */

/* A Complex Add Order message is generated for all the following situations whenever an order free from any display restrictions is reported by the matching engine. */
typedef struct {
  uint8_t tracking_number[2];          /* bytes 0 to 1 */
  uint8_t timestamp[8];                /* bytes 2 to 9 */
  uint8_t strategy_id[4];              /* bytes 10 to 13 */
  uint8_t order_reference_number[8];   /* bytes 14 to 21 */
  uint8_t side;                        /* byte 22 */
  uint8_t original_order_volume[4];    /* bytes 23 to 26 */
  uint8_t executable_order_volume[4];  /* bytes 27 to 30 */
  uint8_t order_status;                /* byte 31 */
  uint8_t order_type;                  /* byte 32 */
  uint8_t limit_price[4];              /* bytes 33 to 36 */
  uint8_t time_in_force;               /* byte 37 */
  uint8_t order_capacity;              /* byte 38 */
  uint8_t scope;                       /* byte 39 */
  uint8_t owner_id[6];                 /* bytes 40 to 45 */
  uint8_t giveup[6];                   /* bytes 46 to 51 */
  uint8_t cmta[6];                     /* bytes 52 to 57 */
} ComplexAddOrderMessage;

/* any Complex Add Order Message at all: every byte one the checker chooses */
static void any_complex_add_order_message(ComplexAddOrderMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->original_order_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executable_order_volume[i] = arbitrary(); }
  record->order_status = arbitrary();
  record->order_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->limit_price[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->order_capacity = arbitrary();
  record->scope = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->owner_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->giveup[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cmta[i] = arbitrary(); }
}

/* Complex Add Order Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_complex_add_order_message(const ComplexAddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_order_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executable_order_volume[i]; }
  wire[at++] = record->order_status;
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->limit_price[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->order_capacity;
  wire[at++] = record->scope;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->owner_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->giveup[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cmta[i]; }

  return at;
}

/* Complex Add Order Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_complex_add_order_message(ComplexAddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->original_order_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executable_order_volume[i] = wire[at++]; }
  record->order_status = wire[at++];
  record->order_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->limit_price[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->order_capacity = wire[at++];
  record->scope = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->owner_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->giveup[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cmta[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Add Order Message is what was written, byte for byte */
static void equal_complex_add_order_message(const ComplexAddOrderMessage *read, const ComplexAddOrderMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->original_order_volume[i] == written->original_order_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executable_order_volume[i] == written->executable_order_volume[i]); }
  assert(read->order_status == written->order_status);
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 4; i++) { assert(read->limit_price[i] == written->limit_price[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->order_capacity == written->order_capacity);
  assert(read->scope == written->scope);
  for (size_t i = 0; i < 6; i++) { assert(read->owner_id[i] == written->owner_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->giveup[i] == written->giveup[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cmta[i] == written->cmta[i]); }
}

/* Complex Add Order Message: written and read back, then read and written back */
static void check_complex_add_order_message(void) {
  ComplexAddOrderMessage sent;
  ComplexAddOrderMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_complex_add_order_message(&sent);
  assert(encode_complex_add_order_message(&sent, wire, 0) == 58);
  assert(decode_complex_add_order_message(&got, wire, 0) == 58);
  equal_complex_add_order_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_add_order_message(&got, wire, 0) == 58);
  assert(encode_complex_add_order_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_system_event_message();
  check_strategy_trading_action_message();
  check_complex_add_order_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
