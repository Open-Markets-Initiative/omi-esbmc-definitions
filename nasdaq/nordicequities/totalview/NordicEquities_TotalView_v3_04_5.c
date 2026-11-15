// nasdaq/nordicequities/totalview/NordicEquities_TotalView_v3_04_5.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Nordic Equity TotalView
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

/* Signals a market or data feed handler event */
typedef struct {
  uint8_t timestamp[8];        /* bytes 0 to 7 */
  uint8_t tracking_number[2];  /* bytes 8 to 9 */
  uint8_t event_code;          /* byte 10 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
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

/* ---- Order Book Trading Action Message: 20 bytes ----------------------------- */

/* Indicates the current trading status of a security */
typedef struct {
  uint8_t timestamp[8];        /* bytes 0 to 7 */
  uint8_t tracking_number[2];  /* bytes 8 to 9 */
  uint8_t order_book[4];       /* bytes 10 to 13 */
  uint8_t symbol_state;        /* byte 14 */
  uint8_t extension;           /* byte 15 */
  uint8_t reason[4];           /* bytes 16 to 19 */
} OrderBookTradingActionMessage;

/* any Order Book Trading Action Message at all: every byte one the checker chooses */
static void any_order_book_trading_action_message(OrderBookTradingActionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = arbitrary(); }
  record->symbol_state = arbitrary();
  record->extension = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reason[i] = arbitrary(); }
}

/* Order Book Trading Action Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_order_book_trading_action_message(const OrderBookTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book[i]; }
  wire[at++] = record->symbol_state;
  wire[at++] = record->extension;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Order Book Trading Action Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_order_book_trading_action_message(OrderBookTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = wire[at++]; }
  record->symbol_state = wire[at++];
  record->extension = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Order Book Trading Action Message is what was written, byte for byte */
static void equal_order_book_trading_action_message(const OrderBookTradingActionMessage *read, const OrderBookTradingActionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book[i] == written->order_book[i]); }
  assert(read->symbol_state == written->symbol_state);
  assert(read->extension == written->extension);
  for (size_t i = 0; i < 4; i++) { assert(read->reason[i] == written->reason[i]); }
}

/* Order Book Trading Action Message: written and read back, then read and written back */
static void check_order_book_trading_action_message(void) {
  OrderBookTradingActionMessage sent;
  OrderBookTradingActionMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_order_book_trading_action_message(&sent);
  assert(encode_order_book_trading_action_message(&sent, wire, 0) == 20);
  assert(decode_order_book_trading_action_message(&got, wire, 0) == 20);
  equal_order_book_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_trading_action_message(&got, wire, 0) == 20);
  assert(encode_order_book_trading_action_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message: 31 bytes --------------------------------------------- */

/* An order added to the book without Mpid attribution */
typedef struct {
  uint8_t timestamp[8];               /* bytes 0 to 7 */
  uint8_t tracking_number[2];         /* bytes 8 to 9 */
  uint8_t order_reference_number[8];  /* bytes 10 to 17 */
  uint8_t buy_sell_indicator;         /* byte 18 */
  uint8_t quantity[4];                /* bytes 19 to 22 */
  uint8_t order_book[4];              /* bytes 23 to 26 */
  uint8_t price[4];                   /* bytes 27 to 30 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
}

/* Add Order Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Add Order Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book[i] == written->order_book[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 31);
  assert(decode_add_order_message(&got, wire, 0) == 31);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 31);
  assert(encode_add_order_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Mpid Attribution Message: 35 bytes ---------------------------- */

/* An order added to the book with Mpid attribution */
typedef struct {
  uint8_t timestamp[8];               /* bytes 0 to 7 */
  uint8_t tracking_number[2];         /* bytes 8 to 9 */
  uint8_t order_reference_number[8];  /* bytes 10 to 17 */
  uint8_t buy_sell_indicator;         /* byte 18 */
  uint8_t quantity[4];                /* bytes 19 to 22 */
  uint8_t order_book[4];              /* bytes 23 to 26 */
  uint8_t price[4];                   /* bytes 27 to 30 */
  uint8_t attribution[4];             /* bytes 31 to 34 */
} AddOrderMpidAttributionMessage;

/* any Add Order Mpid Attribution Message at all: every byte one the checker chooses */
static void any_add_order_mpid_attribution_message(AddOrderMpidAttributionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->attribution[i] = arbitrary(); }
}

/* Add Order Mpid Attribution Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_add_order_mpid_attribution_message(const AddOrderMpidAttributionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->attribution[i]; }

  return at;
}

/* Add Order Mpid Attribution Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_add_order_mpid_attribution_message(AddOrderMpidAttributionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->attribution[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Mpid Attribution Message is what was written, byte for byte */
static void equal_add_order_mpid_attribution_message(const AddOrderMpidAttributionMessage *read, const AddOrderMpidAttributionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book[i] == written->order_book[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->attribution[i] == written->attribution[i]); }
}

/* Add Order Mpid Attribution Message: written and read back, then read and written back */
static void check_add_order_mpid_attribution_message(void) {
  AddOrderMpidAttributionMessage sent;
  AddOrderMpidAttributionMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_add_order_mpid_attribution_message(&sent);
  assert(encode_add_order_mpid_attribution_message(&sent, wire, 0) == 35);
  assert(decode_add_order_mpid_attribution_message(&got, wire, 0) == 35);
  equal_add_order_mpid_attribution_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_mpid_attribution_message(&got, wire, 0) == 35);
  assert(encode_add_order_mpid_attribution_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 34 bytes ---------------------------------------- */

/* Sent whenever an order on the book is executed in whole or in part */
typedef struct {
  uint8_t timestamp[8];               /* bytes 0 to 7 */
  uint8_t tracking_number[2];         /* bytes 8 to 9 */
  uint8_t order_reference_number[8];  /* bytes 10 to 17 */
  uint8_t executed_quantity[4];       /* bytes 18 to 21 */
  uint8_t match_number[4];            /* bytes 22 to 25 */
  uint8_t mpid[4];                    /* bytes 26 to 29 */
  uint8_t mpid_counterparty[4];       /* bytes 30 to 33 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid_counterparty[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid_counterparty[i]; }

  return at;
}

/* Order Executed Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid_counterparty[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid_counterparty[i] == written->mpid_counterparty[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 34);
  assert(decode_order_executed_message(&got, wire, 0) == 34);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 34);
  assert(encode_order_executed_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed With Price Message: 39 bytes ----------------------------- */

/* An order executed at a price different to its display price */
typedef struct {
  uint8_t timestamp[8];               /* bytes 0 to 7 */
  uint8_t tracking_number[2];         /* bytes 8 to 9 */
  uint8_t order_reference_number[8];  /* bytes 10 to 17 */
  uint8_t executed_quantity[4];       /* bytes 18 to 21 */
  uint8_t match_number[4];            /* bytes 22 to 25 */
  uint8_t printable;                  /* byte 26 */
  uint8_t trade_price[4];             /* bytes 27 to 30 */
  uint8_t mpid_owner[4];              /* bytes 31 to 34 */
  uint8_t mpid_counterparty[4];       /* bytes 35 to 38 */
} OrderExecutedWithPriceMessage;

/* any Order Executed With Price Message at all: every byte one the checker chooses */
static void any_order_executed_with_price_message(OrderExecutedWithPriceMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  record->printable = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid_owner[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid_counterparty[i] = arbitrary(); }
}

/* Order Executed With Price Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_with_price_message(const OrderExecutedWithPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->printable;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid_owner[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid_counterparty[i]; }

  return at;
}

/* Order Executed With Price Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_with_price_message(OrderExecutedWithPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  record->printable = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid_owner[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid_counterparty[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed With Price Message is what was written, byte for byte */
static void equal_order_executed_with_price_message(const OrderExecutedWithPriceMessage *read, const OrderExecutedWithPriceMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->printable == written->printable);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid_owner[i] == written->mpid_owner[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid_counterparty[i] == written->mpid_counterparty[i]); }
}

/* Order Executed With Price Message: written and read back, then read and written back */
static void check_order_executed_with_price_message(void) {
  OrderExecutedWithPriceMessage sent;
  OrderExecutedWithPriceMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_order_executed_with_price_message(&sent);
  assert(encode_order_executed_with_price_message(&sent, wire, 0) == 39);
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 39);
  equal_order_executed_with_price_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 39);
  assert(encode_order_executed_with_price_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Message: 22 bytes ------------------------------------------ */

/* An order on the book modified by a partial cancellation */
typedef struct {
  uint8_t timestamp[8];               /* bytes 0 to 7 */
  uint8_t tracking_number[2];         /* bytes 8 to 9 */
  uint8_t order_reference_number[8];  /* bytes 10 to 17 */
  uint8_t canceled_quantity[4];       /* bytes 18 to 21 */
} OrderCancelMessage;

/* any Order Cancel Message at all: every byte one the checker chooses */
static void any_order_cancel_message(OrderCancelMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->canceled_quantity[i] = arbitrary(); }
}

/* Order Cancel Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_message(const OrderCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->canceled_quantity[i]; }

  return at;
}

/* Order Cancel Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_message(OrderCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->canceled_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Message is what was written, byte for byte */
static void equal_order_cancel_message(const OrderCancelMessage *read, const OrderCancelMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->canceled_quantity[i] == written->canceled_quantity[i]); }
}

/* Order Cancel Message: written and read back, then read and written back */
static void check_order_cancel_message(void) {
  OrderCancelMessage sent;
  OrderCancelMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_order_cancel_message(&sent);
  assert(encode_order_cancel_message(&sent, wire, 0) == 22);
  assert(decode_order_cancel_message(&got, wire, 0) == 22);
  equal_order_cancel_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_message(&got, wire, 0) == 22);
  assert(encode_order_cancel_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Delete Message: 18 bytes ------------------------------------------ */

/* An order on the book being cancelled in full */
typedef struct {
  uint8_t timestamp[8];               /* bytes 0 to 7 */
  uint8_t tracking_number[2];         /* bytes 8 to 9 */
  uint8_t order_reference_number[8];  /* bytes 10 to 17 */
} OrderDeleteMessage;

/* any Order Delete Message at all: every byte one the checker chooses */
static void any_order_delete_message(OrderDeleteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
}

/* Order Delete Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_order_delete_message(const OrderDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }

  return at;
}

/* Order Delete Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_order_delete_message(OrderDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Delete Message is what was written, byte for byte */
static void equal_order_delete_message(const OrderDeleteMessage *read, const OrderDeleteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
}

/* Order Delete Message: written and read back, then read and written back */
static void check_order_delete_message(void) {
  OrderDeleteMessage sent;
  OrderDeleteMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_order_delete_message(&sent);
  assert(encode_order_delete_message(&sent, wire, 0) == 18);
  assert(decode_order_delete_message(&got, wire, 0) == 18);
  equal_order_delete_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_order_delete_message(&got, wire, 0) == 18);
  assert(encode_order_delete_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Book Flush Message: 14 bytes -------------------------------------- */

/* An order book is flushed and all orders removed */
typedef struct {
  uint8_t timestamp[8];        /* bytes 0 to 7 */
  uint8_t tracking_number[2];  /* bytes 8 to 9 */
  uint8_t order_book[4];       /* bytes 10 to 13 */
} OrderBookFlushMessage;

/* any Order Book Flush Message at all: every byte one the checker chooses */
static void any_order_book_flush_message(OrderBookFlushMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = arbitrary(); }
}

/* Order Book Flush Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_order_book_flush_message(const OrderBookFlushMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book[i]; }

  return at;
}

/* Order Book Flush Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_order_book_flush_message(OrderBookFlushMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = wire[at++]; }

  return at;
}

/* what was read of Order Book Flush Message is what was written, byte for byte */
static void equal_order_book_flush_message(const OrderBookFlushMessage *read, const OrderBookFlushMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book[i] == written->order_book[i]); }
}

/* Order Book Flush Message: written and read back, then read and written back */
static void check_order_book_flush_message(void) {
  OrderBookFlushMessage sent;
  OrderBookFlushMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_order_book_flush_message(&sent);
  assert(encode_order_book_flush_message(&sent, wire, 0) == 14);
  assert(decode_order_book_flush_message(&got, wire, 0) == 14);
  equal_order_book_flush_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_flush_message(&got, wire, 0) == 14);
  assert(encode_order_book_flush_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replace Message: 34 bytes ----------------------------------------- */

/* An order on the book has been cancel replaced */
typedef struct {
  uint8_t timestamp[8];                        /* bytes 0 to 7 */
  uint8_t tracking_number[2];                  /* bytes 8 to 9 */
  uint8_t original_order_reference_number[8];  /* bytes 10 to 17 */
  uint8_t new_order_reference_number[8];       /* bytes 18 to 25 */
  uint8_t quantity[4];                         /* bytes 26 to 29 */
  uint8_t price[4];                            /* bytes 30 to 33 */
} OrderReplaceMessage;

/* any Order Replace Message at all: every byte one the checker chooses */
static void any_order_replace_message(OrderReplaceMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
}

/* Order Replace Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_order_replace_message(const OrderReplaceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Replace Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_order_replace_message(OrderReplaceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Replace Message is what was written, byte for byte */
static void equal_order_replace_message(const OrderReplaceMessage *read, const OrderReplaceMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_reference_number[i] == written->original_order_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_order_reference_number[i] == written->new_order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Replace Message: written and read back, then read and written back */
static void check_order_replace_message(void) {
  OrderReplaceMessage sent;
  OrderReplaceMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_order_replace_message(&sent);
  assert(encode_order_replace_message(&sent, wire, 0) == 34);
  assert(decode_order_replace_message(&got, wire, 0) == 34);
  equal_order_replace_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replace_message(&got, wire, 0) == 34);
  assert(encode_order_replace_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 43 bytes ------------------------------------------------- */

/* Execution details for a match involving non displayable order types */
typedef struct {
  uint8_t timestamp[8];               /* bytes 0 to 7 */
  uint8_t tracking_number[2];         /* bytes 8 to 9 */
  uint8_t order_reference_number[8];  /* bytes 10 to 17 */
  uint8_t trade_type;                 /* byte 18 */
  uint8_t quantity[4];                /* bytes 19 to 22 */
  uint8_t order_book[4];              /* bytes 23 to 26 */
  uint8_t match_number[4];            /* bytes 27 to 30 */
  uint8_t trade_price[4];             /* bytes 31 to 34 */
  uint8_t participant_id_buyer[4];    /* bytes 35 to 38 */
  uint8_t participant_id_seller[4];   /* bytes 39 to 42 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->participant_id_buyer[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->participant_id_seller[i] = arbitrary(); }
}

/* Trade Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_id_buyer[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_id_seller[i]; }

  return at;
}

/* Trade Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->participant_id_buyer[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->participant_id_seller[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book[i] == written->order_book[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->participant_id_buyer[i] == written->participant_id_buyer[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->participant_id_seller[i] == written->participant_id_seller[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 43);
  assert(decode_trade_message(&got, wire, 0) == 43);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 43);
  assert(encode_trade_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cross Trade Message: 31 bytes ------------------------------------------- */

/* The cross process has completed for a specific security */
typedef struct {
  uint8_t timestamp[8];         /* bytes 0 to 7 */
  uint8_t tracking_number[2];   /* bytes 8 to 9 */
  uint8_t quantity[4];          /* bytes 10 to 13 */
  uint8_t order_book[4];        /* bytes 14 to 17 */
  uint8_t cross_price[4];       /* bytes 18 to 21 */
  uint8_t match_number[4];      /* bytes 22 to 25 */
  uint8_t cross_type;           /* byte 26 */
  uint8_t number_of_trades[4];  /* bytes 27 to 30 */
} CrossTradeMessage;

/* any Cross Trade Message at all: every byte one the checker chooses */
static void any_cross_trade_message(CrossTradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  record->cross_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->number_of_trades[i] = arbitrary(); }
}

/* Cross Trade Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_cross_trade_message(const CrossTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->cross_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_trades[i]; }

  return at;
}

/* Cross Trade Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_cross_trade_message(CrossTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  record->cross_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->number_of_trades[i] = wire[at++]; }

  return at;
}

/* what was read of Cross Trade Message is what was written, byte for byte */
static void equal_cross_trade_message(const CrossTradeMessage *read, const CrossTradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book[i] == written->order_book[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_price[i] == written->cross_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->cross_type == written->cross_type);
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_trades[i] == written->number_of_trades[i]); }
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

/* ---- Broken Trade Message: 14 bytes ------------------------------------------ */

/* An execution has been broken and cannot be reinstated */
typedef struct {
  uint8_t timestamp[8];        /* bytes 0 to 7 */
  uint8_t tracking_number[2];  /* bytes 8 to 9 */
  uint8_t match_number[4];     /* bytes 10 to 13 */
} BrokenTradeMessage;

/* any Broken Trade Message at all: every byte one the checker chooses */
static void any_broken_trade_message(BrokenTradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
}

/* Broken Trade Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_message(const BrokenTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Broken Trade Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_message(BrokenTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Broken Trade Message is what was written, byte for byte */
static void equal_broken_trade_message(const BrokenTradeMessage *read, const BrokenTradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Broken Trade Message: written and read back, then read and written back */
static void check_broken_trade_message(void) {
  BrokenTradeMessage sent;
  BrokenTradeMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_broken_trade_message(&sent);
  assert(encode_broken_trade_message(&sent, wire, 0) == 14);
  assert(decode_broken_trade_message(&got, wire, 0) == 14);
  equal_broken_trade_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_broken_trade_message(&got, wire, 0) == 14);
  assert(encode_broken_trade_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Noii Message: 60 bytes -------------------------------------------------- */

/* Net order imbalance indicator disseminated during a cross auction */
typedef struct {
  uint8_t timestamp[8];           /* bytes 0 to 7 */
  uint8_t tracking_number[2];     /* bytes 8 to 9 */
  uint8_t paired_quantity[8];     /* bytes 10 to 17 */
  uint8_t imbalance_quantity[8];  /* bytes 18 to 25 */
  uint8_t imbalance_direction;    /* byte 26 */
  uint8_t order_book[4];          /* bytes 27 to 30 */
  uint8_t equilibrium_price[4];   /* bytes 31 to 34 */
  uint8_t cross_type;             /* byte 35 */
  uint8_t best_bid_price[4];      /* bytes 36 to 39 */
  uint8_t best_bid_quantity[8];   /* bytes 40 to 47 */
  uint8_t best_ask_price[4];      /* bytes 48 to 51 */
  uint8_t best_ask_quantity[8];   /* bytes 52 to 59 */
} NoiiMessage;

/* any Noii Message at all: every byte one the checker chooses */
static void any_noii_message(NoiiMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->paired_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->imbalance_quantity[i] = arbitrary(); }
  record->imbalance_direction = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->equilibrium_price[i] = arbitrary(); }
  record->cross_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->best_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_bid_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_ask_quantity[i] = arbitrary(); }
}

/* Noii Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_noii_message(const NoiiMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->paired_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->imbalance_quantity[i]; }
  wire[at++] = record->imbalance_direction;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->equilibrium_price[i]; }
  wire[at++] = record->cross_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_bid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_bid_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_ask_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_ask_quantity[i]; }

  return at;
}

/* Noii Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_noii_message(NoiiMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->paired_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->imbalance_quantity[i] = wire[at++]; }
  record->imbalance_direction = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->equilibrium_price[i] = wire[at++]; }
  record->cross_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->best_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_bid_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_ask_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Noii Message is what was written, byte for byte */
static void equal_noii_message(const NoiiMessage *read, const NoiiMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->paired_quantity[i] == written->paired_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->imbalance_quantity[i] == written->imbalance_quantity[i]); }
  assert(read->imbalance_direction == written->imbalance_direction);
  for (size_t i = 0; i < 4; i++) { assert(read->order_book[i] == written->order_book[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->equilibrium_price[i] == written->equilibrium_price[i]); }
  assert(read->cross_type == written->cross_type);
  for (size_t i = 0; i < 4; i++) { assert(read->best_bid_price[i] == written->best_bid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_bid_quantity[i] == written->best_bid_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_ask_price[i] == written->best_ask_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_ask_quantity[i] == written->best_ask_quantity[i]); }
}

/* Noii Message: written and read back, then read and written back */
static void check_noii_message(void) {
  NoiiMessage sent;
  NoiiMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_noii_message(&sent);
  assert(encode_noii_message(&sent, wire, 0) == 60);
  assert(decode_noii_message(&got, wire, 0) == 60);
  equal_noii_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_noii_message(&got, wire, 0) == 60);
  assert(encode_noii_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Moii Message: 28 bytes -------------------------------------------------- */

/* Auction on demand order imbalance indicator */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t tracking_number[2];    /* bytes 8 to 9 */
  uint8_t paired_quantity[8];    /* bytes 10 to 17 */
  uint8_t order_book[4];         /* bytes 18 to 21 */
  uint8_t equilibrium_price[4];  /* bytes 22 to 25 */
  uint8_t cross_type;            /* byte 26 */
  uint8_t cross_level;           /* byte 27 */
} MoiiMessage;

/* any Moii Message at all: every byte one the checker chooses */
static void any_moii_message(MoiiMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->paired_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->equilibrium_price[i] = arbitrary(); }
  record->cross_type = arbitrary();
  record->cross_level = arbitrary();
}

/* Moii Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_moii_message(const MoiiMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->paired_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->equilibrium_price[i]; }
  wire[at++] = record->cross_type;
  wire[at++] = record->cross_level;

  return at;
}

/* Moii Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_moii_message(MoiiMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->paired_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->equilibrium_price[i] = wire[at++]; }
  record->cross_type = wire[at++];
  record->cross_level = wire[at++];

  return at;
}

/* what was read of Moii Message is what was written, byte for byte */
static void equal_moii_message(const MoiiMessage *read, const MoiiMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->paired_quantity[i] == written->paired_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book[i] == written->order_book[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->equilibrium_price[i] == written->equilibrium_price[i]); }
  assert(read->cross_type == written->cross_type);
  assert(read->cross_level == written->cross_level);
}

/* Moii Message: written and read back, then read and written back */
static void check_moii_message(void) {
  MoiiMessage sent;
  MoiiMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_moii_message(&sent);
  assert(encode_moii_message(&sent, wire, 0) == 28);
  assert(decode_moii_message(&got, wire, 0) == 28);
  equal_moii_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_moii_message(&got, wire, 0) == 28);
  assert(encode_moii_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Summary Message: 37 bytes ------------------------------------- */

/* Summary information disseminated before the individual trades */
typedef struct {
  uint8_t timestamp[8];                 /* bytes 0 to 7 */
  uint8_t tracking_number[2];           /* bytes 8 to 9 */
  uint8_t order_book[4];                /* bytes 10 to 13 */
  uint8_t aggressing_side;              /* byte 14 */
  uint8_t quantity[4];                  /* bytes 15 to 18 */
  uint8_t hidden_quantity[4];           /* bytes 19 to 22 */
  uint8_t stp_cancel_quantity[4];       /* bytes 23 to 26 */
  uint8_t far_price[4];                 /* bytes 27 to 30 */
  uint8_t add_quantity[4];              /* bytes 31 to 34 */
  uint8_t number_of_lit_executions[2];  /* bytes 35 to 36 */
} ExecutionSummaryMessage;

/* any Execution Summary Message at all: every byte one the checker chooses */
static void any_execution_summary_message(ExecutionSummaryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = arbitrary(); }
  record->aggressing_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->hidden_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->stp_cancel_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->far_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->add_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_lit_executions[i] = arbitrary(); }
}

/* Execution Summary Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_execution_summary_message(const ExecutionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book[i]; }
  wire[at++] = record->aggressing_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->hidden_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->stp_cancel_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->far_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->add_quantity[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_lit_executions[i]; }

  return at;
}

/* Execution Summary Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_execution_summary_message(ExecutionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = wire[at++]; }
  record->aggressing_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->hidden_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->stp_cancel_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->far_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->add_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_lit_executions[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Summary Message is what was written, byte for byte */
static void equal_execution_summary_message(const ExecutionSummaryMessage *read, const ExecutionSummaryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book[i] == written->order_book[i]); }
  assert(read->aggressing_side == written->aggressing_side);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->hidden_quantity[i] == written->hidden_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->stp_cancel_quantity[i] == written->stp_cancel_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->far_price[i] == written->far_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->add_quantity[i] == written->add_quantity[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_lit_executions[i] == written->number_of_lit_executions[i]); }
}

/* Execution Summary Message: written and read back, then read and written back */
static void check_execution_summary_message(void) {
  ExecutionSummaryMessage sent;
  ExecutionSummaryMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_execution_summary_message(&sent);
  assert(encode_execution_summary_message(&sent, wire, 0) == 37);
  assert(decode_execution_summary_message(&got, wire, 0) == 37);
  equal_execution_summary_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_summary_message(&got, wire, 0) == 37);
  assert(encode_execution_summary_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_system_event_message();
  check_order_book_trading_action_message();
  check_add_order_message();
  check_add_order_mpid_attribution_message();
  check_order_executed_message();
  check_order_executed_with_price_message();
  check_order_cancel_message();
  check_order_delete_message();
  check_order_book_flush_message();
  check_order_replace_message();
  check_trade_message();
  check_cross_trade_message();
  check_broken_trade_message();
  check_noii_message();
  check_moii_message();
  check_execution_summary_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
