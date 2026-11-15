// cboe/edgxequities/tcpdepthofbook/EdgxEquities_TcpDepthOfBook_v1_15_13.c
/*
 * Chicago Board Options Exchange Tcp Depth Of Book
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
 *   - a run filling what frames it
 *   - the dispatch that chooses a message by its type
 *   - a field filling what is left of what holds it
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

/* ---- Debug Packet: 1 byte ---------------------------------------------------- */

/* Debug packets are intended to provide human readable text that may aid in debugging problems. */
typedef struct {
  uint8_t text;  /* byte 0 */
} DebugPacket;

/* any Debug Packet at all: every byte one the checker chooses */
static void any_debug_packet(DebugPacket *record) {
  record->text = arbitrary();
}

/* Debug Packet to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_debug_packet(const DebugPacket *record, uint8_t *wire, size_t at) {
  wire[at++] = record->text;

  return at;
}

/* Debug Packet off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_debug_packet(DebugPacket *record, const uint8_t *wire, size_t at) {
  record->text = wire[at++];

  return at;
}

/* what was read of Debug Packet is what was written, byte for byte */
static void equal_debug_packet(const DebugPacket *read, const DebugPacket *written) {
  assert(read->text == written->text);
}

/* Debug Packet: written and read back, then read and written back */
static void check_debug_packet(void) {
  DebugPacket sent;
  DebugPacket got;
  uint8_t wire[1];
  uint8_t again[1];

  any_debug_packet(&sent);
  assert(encode_debug_packet(&sent, wire, 0) == 1);
  assert(decode_debug_packet(&got, wire, 0) == 1);
  equal_debug_packet(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_debug_packet(&got, wire, 0) == 1);
  assert(encode_debug_packet(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Accepted Packet: 20 bytes ----------------------------------------- */

/* The Soup 2.0 server sends a Login Accepted Packet in response to receiving a valid Login Request  from the client. */
typedef struct {
  uint8_t session[10];          /* bytes 0 to 9 */
  uint8_t sequence_number[10];  /* bytes 10 to 19 */
} LoginAcceptedPacket;

/* any Login Accepted Packet at all: every byte one the checker chooses */
static void any_login_accepted_packet(LoginAcceptedPacket *record) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Login Accepted Packet to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_login_accepted_packet(const LoginAcceptedPacket *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Login Accepted Packet off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_login_accepted_packet(LoginAcceptedPacket *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Accepted Packet is what was written, byte for byte */
static void equal_login_accepted_packet(const LoginAcceptedPacket *read, const LoginAcceptedPacket *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Login Accepted Packet: written and read back, then read and written back */
static void check_login_accepted_packet(void) {
  LoginAcceptedPacket sent;
  LoginAcceptedPacket got;
  uint8_t wire[20];
  uint8_t again[20];

  any_login_accepted_packet(&sent);
  assert(encode_login_accepted_packet(&sent, wire, 0) == 20);
  assert(decode_login_accepted_packet(&got, wire, 0) == 20);
  equal_login_accepted_packet(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_login_accepted_packet(&got, wire, 0) == 20);
  assert(encode_login_accepted_packet(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Rejected Packet: 1 byte ------------------------------------------- */

/* The Soup 2.0 server sends this packet in response to an invalid Login Request Packet from the client. */
typedef struct {
  uint8_t reject_reason_code;  /* byte 0 */
} LoginRejectedPacket;

/* any Login Rejected Packet at all: every byte one the checker chooses */
static void any_login_rejected_packet(LoginRejectedPacket *record) {
  record->reject_reason_code = arbitrary();
}

/* Login Rejected Packet to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_login_rejected_packet(const LoginRejectedPacket *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reject_reason_code;

  return at;
}

/* Login Rejected Packet off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_login_rejected_packet(LoginRejectedPacket *record, const uint8_t *wire, size_t at) {
  record->reject_reason_code = wire[at++];

  return at;
}

/* what was read of Login Rejected Packet is what was written, byte for byte */
static void equal_login_rejected_packet(const LoginRejectedPacket *read, const LoginRejectedPacket *written) {
  assert(read->reject_reason_code == written->reject_reason_code);
}

/* Login Rejected Packet: written and read back, then read and written back */
static void check_login_rejected_packet(void) {
  LoginRejectedPacket sent;
  LoginRejectedPacket got;
  uint8_t wire[1];
  uint8_t again[1];

  any_login_rejected_packet(&sent);
  assert(encode_login_rejected_packet(&sent, wire, 0) == 1);
  assert(decode_login_rejected_packet(&got, wire, 0) == 1);
  equal_login_rejected_packet(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_login_rejected_packet(&got, wire, 0) == 1);
  assert(encode_login_rejected_packet(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequenced Message Header: 9 bytes --------------------------------------- */

/* Sequenced Message Header */
typedef struct {
  uint8_t timestamp[8];            /* bytes 0 to 7 */
  uint8_t sequenced_message_type;  /* byte 8 */
} SequencedMessageHeader;

/* any Sequenced Message Header at all: every byte one the checker chooses */
static void any_sequenced_message_header(SequencedMessageHeader *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->sequenced_message_type = arbitrary();
}

/* Sequenced Message Header to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_sequenced_message_header(const SequencedMessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->sequenced_message_type;

  return at;
}

/* Sequenced Message Header off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_sequenced_message_header(SequencedMessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->sequenced_message_type = wire[at++];

  return at;
}

/* what was read of Sequenced Message Header is what was written, byte for byte */
static void equal_sequenced_message_header(const SequencedMessageHeader *read, const SequencedMessageHeader *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->sequenced_message_type == written->sequenced_message_type);
}

/* Sequenced Message Header: written and read back, then read and written back */
static void check_sequenced_message_header(void) {
  SequencedMessageHeader sent;
  SequencedMessageHeader got;
  uint8_t wire[9];
  uint8_t again[9];

  any_sequenced_message_header(&sent);
  assert(encode_sequenced_message_header(&sent, wire, 0) == 9);
  assert(decode_sequenced_message_header(&got, wire, 0) == 9);
  equal_sequenced_message_header(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_sequenced_message_header(&got, wire, 0) == 9);
  assert(encode_sequenced_message_header(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Clear Message: 8 bytes ------------------------------------------- */

/* The Symbol Clear message instructs feed recipients to clear all orders for the Cboe book in the specified symbol. */
typedef struct {
  uint8_t stock_symbol_long[8];  /* bytes 0 to 7 */
} SymbolClearMessage;

/* any Symbol Clear Message at all: every byte one the checker chooses */
static void any_symbol_clear_message(SymbolClearMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = arbitrary(); }
}

/* Symbol Clear Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_symbol_clear_message(const SymbolClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_symbol_long[i]; }

  return at;
}

/* Symbol Clear Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_symbol_clear_message(SymbolClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Clear Message is what was written, byte for byte */
static void equal_symbol_clear_message(const SymbolClearMessage *read, const SymbolClearMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock_symbol_long[i] == written->stock_symbol_long[i]); }
}

/* Symbol Clear Message: written and read back, then read and written back */
static void check_symbol_clear_message(void) {
  SymbolClearMessage sent;
  SymbolClearMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_symbol_clear_message(&sent);
  assert(encode_symbol_clear_message(&sent, wire, 0) == 8);
  assert(decode_symbol_clear_message(&got, wire, 0) == 8);
  equal_symbol_clear_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_clear_message(&got, wire, 0) == 8);
  assert(encode_symbol_clear_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Short Message: 36 bytes --------------------------------------- */

/* An Add Order message represents a newly accepted visible order on the Cboe book. */
typedef struct {
  uint8_t order_id[12];           /* bytes 0 to 11 */
  uint8_t side_indicator;         /* byte 12 */
  uint8_t shares_short[6];        /* bytes 13 to 18 */
  uint8_t stock_symbol_short[6];  /* bytes 19 to 24 */
  uint8_t price_short[10];        /* bytes 25 to 34 */
  uint8_t reserved;               /* byte 35 */
} AddOrderShortMessage;

/* any Add Order Short Message at all: every byte one the checker chooses */
static void any_add_order_short_message(AddOrderShortMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares_short[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->stock_symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price_short[i] = arbitrary(); }
  record->reserved = arbitrary();
}

/* Add Order Short Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_add_order_short_message(const AddOrderShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares_short[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock_symbol_short[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price_short[i]; }
  wire[at++] = record->reserved;

  return at;
}

/* Add Order Short Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_add_order_short_message(AddOrderShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares_short[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->stock_symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price_short[i] = wire[at++]; }
  record->reserved = wire[at++];

  return at;
}

/* what was read of Add Order Short Message is what was written, byte for byte */
static void equal_add_order_short_message(const AddOrderShortMessage *read, const AddOrderShortMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->shares_short[i] == written->shares_short[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->stock_symbol_short[i] == written->stock_symbol_short[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price_short[i] == written->price_short[i]); }
  assert(read->reserved == written->reserved);
}

/* Add Order Short Message: written and read back, then read and written back */
static void check_add_order_short_message(void) {
  AddOrderShortMessage sent;
  AddOrderShortMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_add_order_short_message(&sent);
  assert(encode_add_order_short_message(&sent, wire, 0) == 36);
  assert(decode_add_order_short_message(&got, wire, 0) == 36);
  equal_add_order_short_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_short_message(&got, wire, 0) == 36);
  assert(encode_add_order_short_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Long Message: 43 bytes ---------------------------------------- */

/* The long version of the Add Order message accommodates larger symbol sizes possible through the ISRA plan. */
typedef struct {
  uint8_t order_id[12];          /* bytes 0 to 11 */
  uint8_t side_indicator;        /* byte 12 */
  uint8_t shares_short[6];       /* bytes 13 to 18 */
  uint8_t stock_symbol_long[8];  /* bytes 19 to 26 */
  uint8_t price_short[10];       /* bytes 27 to 36 */
  uint8_t reserved;              /* byte 37 */
  uint8_t participant_id[4];     /* bytes 38 to 41 */
  uint8_t customer_indicator;    /* byte 42 */
} AddOrderLongMessage;

/* any Add Order Long Message at all: every byte one the checker chooses */
static void any_add_order_long_message(AddOrderLongMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price_short[i] = arbitrary(); }
  record->reserved = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_id[i] = arbitrary(); }
  record->customer_indicator = arbitrary();
}

/* Add Order Long Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_add_order_long_message(const AddOrderLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_symbol_long[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price_short[i]; }
  wire[at++] = record->reserved;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_id[i]; }
  wire[at++] = record->customer_indicator;

  return at;
}

/* Add Order Long Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_add_order_long_message(AddOrderLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price_short[i] = wire[at++]; }
  record->reserved = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_id[i] = wire[at++]; }
  record->customer_indicator = wire[at++];

  return at;
}

/* what was read of Add Order Long Message is what was written, byte for byte */
static void equal_add_order_long_message(const AddOrderLongMessage *read, const AddOrderLongMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->shares_short[i] == written->shares_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock_symbol_long[i] == written->stock_symbol_long[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price_short[i] == written->price_short[i]); }
  assert(read->reserved == written->reserved);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_id[i] == written->participant_id[i]); }
  assert(read->customer_indicator == written->customer_indicator);
}

/* Add Order Long Message: written and read back, then read and written back */
static void check_add_order_long_message(void) {
  AddOrderLongMessage sent;
  AddOrderLongMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_add_order_long_message(&sent);
  assert(encode_add_order_long_message(&sent, wire, 0) == 43);
  assert(decode_add_order_long_message(&got, wire, 0) == 43);
  equal_add_order_long_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_long_message(&got, wire, 0) == 43);
  assert(encode_add_order_long_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Extended Message: 47 bytes ------------------------------------ */

/* The extended version of the Add Order message accommodates larger prices. */
typedef struct {
  uint8_t order_id[12];          /* bytes 0 to 11 */
  uint8_t side_indicator;        /* byte 12 */
  uint8_t shares_short[6];       /* bytes 13 to 18 */
  uint8_t stock_symbol_long[8];  /* bytes 19 to 26 */
  uint8_t price_long[14];        /* bytes 27 to 40 */
  uint8_t display;               /* byte 41 */
  uint8_t participant_id[4];     /* bytes 42 to 45 */
  uint8_t customer_indicator;    /* byte 46 */
} AddOrderExtendedMessage;

/* any Add Order Extended Message at all: every byte one the checker chooses */
static void any_add_order_extended_message(AddOrderExtendedMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->price_long[i] = arbitrary(); }
  record->display = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_id[i] = arbitrary(); }
  record->customer_indicator = arbitrary();
}

/* Add Order Extended Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_add_order_extended_message(const AddOrderExtendedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_symbol_long[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->price_long[i]; }
  wire[at++] = record->display;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_id[i]; }
  wire[at++] = record->customer_indicator;

  return at;
}

/* Add Order Extended Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_add_order_extended_message(AddOrderExtendedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->price_long[i] = wire[at++]; }
  record->display = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_id[i] = wire[at++]; }
  record->customer_indicator = wire[at++];

  return at;
}

/* what was read of Add Order Extended Message is what was written, byte for byte */
static void equal_add_order_extended_message(const AddOrderExtendedMessage *read, const AddOrderExtendedMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->shares_short[i] == written->shares_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock_symbol_long[i] == written->stock_symbol_long[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->price_long[i] == written->price_long[i]); }
  assert(read->display == written->display);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_id[i] == written->participant_id[i]); }
  assert(read->customer_indicator == written->customer_indicator);
}

/* Add Order Extended Message: written and read back, then read and written back */
static void check_add_order_extended_message(void) {
  AddOrderExtendedMessage sent;
  AddOrderExtendedMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_add_order_extended_message(&sent);
  assert(encode_add_order_extended_message(&sent, wire, 0) == 47);
  assert(decode_add_order_extended_message(&got, wire, 0) == 47);
  equal_add_order_extended_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_extended_message(&got, wire, 0) == 47);
  assert(encode_add_order_extended_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 30 bytes ---------------------------------------- */

/* Order Executed messages are sent when a visible order on the Cboe book is executed in whole or in part. */
typedef struct {
  uint8_t order_id[12];        /* bytes 0 to 11 */
  uint8_t executed_shares[6];  /* bytes 12 to 17 */
  uint8_t execution_id[12];    /* bytes 18 to 29 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->executed_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->executed_shares[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Order Executed Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->executed_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->executed_shares[i] == written->executed_shares[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
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

/* ---- Order Cancel Message: 18 bytes ------------------------------------------ */

/* Order Cancel messages are sent when a visible order on the Cboe book is canceled in whole or in part. */
typedef struct {
  uint8_t order_id[12];        /* bytes 0 to 11 */
  uint8_t canceled_shares[6];  /* bytes 12 to 17 */
} OrderCancelMessage;

/* any Order Cancel Message at all: every byte one the checker chooses */
static void any_order_cancel_message(OrderCancelMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->canceled_shares[i] = arbitrary(); }
}

/* Order Cancel Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_message(const OrderCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->canceled_shares[i]; }

  return at;
}

/* Order Cancel Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_message(OrderCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->canceled_shares[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Message is what was written, byte for byte */
static void equal_order_cancel_message(const OrderCancelMessage *read, const OrderCancelMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
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

/* ---- Trade Short Message: 47 bytes ------------------------------------------- */

/* The Trade message provides information about executions of non-displayed orders or shares on the Cboe book and routed orders. */
typedef struct {
  uint8_t order_id[12];           /* bytes 0 to 11 */
  uint8_t side_indicator;         /* byte 12 */
  uint8_t shares_short[6];        /* bytes 13 to 18 */
  uint8_t stock_symbol_short[6];  /* bytes 19 to 24 */
  uint8_t price_short[10];        /* bytes 25 to 34 */
  uint8_t execution_id[12];       /* bytes 35 to 46 */
} TradeShortMessage;

/* any Trade Short Message at all: every byte one the checker chooses */
static void any_trade_short_message(TradeShortMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares_short[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->stock_symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = arbitrary(); }
}

/* Trade Short Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_trade_short_message(const TradeShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares_short[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock_symbol_short[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Trade Short Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_trade_short_message(TradeShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares_short[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->stock_symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Short Message is what was written, byte for byte */
static void equal_trade_short_message(const TradeShortMessage *read, const TradeShortMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->shares_short[i] == written->shares_short[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->stock_symbol_short[i] == written->stock_symbol_short[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Trade Short Message: written and read back, then read and written back */
static void check_trade_short_message(void) {
  TradeShortMessage sent;
  TradeShortMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_trade_short_message(&sent);
  assert(encode_trade_short_message(&sent, wire, 0) == 47);
  assert(decode_trade_short_message(&got, wire, 0) == 47);
  equal_trade_short_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_short_message(&got, wire, 0) == 47);
  assert(encode_trade_short_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Long Message: 49 bytes -------------------------------------------- */

/* The long version of the Trade message accommodates larger symbol sizes possible through the ISRA plan. */
typedef struct {
  uint8_t order_id[12];          /* bytes 0 to 11 */
  uint8_t side_indicator;        /* byte 12 */
  uint8_t shares_short[6];       /* bytes 13 to 18 */
  uint8_t stock_symbol_long[8];  /* bytes 19 to 26 */
  uint8_t price_short[10];       /* bytes 27 to 36 */
  uint8_t execution_id[12];      /* bytes 37 to 48 */
} TradeLongMessage;

/* any Trade Long Message at all: every byte one the checker chooses */
static void any_trade_long_message(TradeLongMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = arbitrary(); }
}

/* Trade Long Message to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_trade_long_message(const TradeLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_symbol_long[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Trade Long Message off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_trade_long_message(TradeLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Long Message is what was written, byte for byte */
static void equal_trade_long_message(const TradeLongMessage *read, const TradeLongMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->shares_short[i] == written->shares_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock_symbol_long[i] == written->stock_symbol_long[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Trade Long Message: written and read back, then read and written back */
static void check_trade_long_message(void) {
  TradeLongMessage sent;
  TradeLongMessage got;
  uint8_t wire[49];
  uint8_t again[49];

  any_trade_long_message(&sent);
  assert(encode_trade_long_message(&sent, wire, 0) == 49);
  assert(decode_trade_long_message(&got, wire, 0) == 49);
  equal_trade_long_message(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_long_message(&got, wire, 0) == 49);
  assert(encode_trade_long_message(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Extended Message: 53 bytes ---------------------------------------- */

/* The extended version of the Trade message accommodates larger prices. */
typedef struct {
  uint8_t order_id[12];          /* bytes 0 to 11 */
  uint8_t side_indicator;        /* byte 12 */
  uint8_t shares_short[6];       /* bytes 13 to 18 */
  uint8_t stock_symbol_long[8];  /* bytes 19 to 26 */
  uint8_t price_long[14];        /* bytes 27 to 40 */
  uint8_t execution_id[12];      /* bytes 41 to 52 */
} TradeExtendedMessage;

/* any Trade Extended Message at all: every byte one the checker chooses */
static void any_trade_extended_message(TradeExtendedMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = arbitrary(); }
}

/* Trade Extended Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_trade_extended_message(const TradeExtendedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_symbol_long[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Trade Extended Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_trade_extended_message(TradeExtendedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Extended Message is what was written, byte for byte */
static void equal_trade_extended_message(const TradeExtendedMessage *read, const TradeExtendedMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->shares_short[i] == written->shares_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock_symbol_long[i] == written->stock_symbol_long[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Trade Extended Message: written and read back, then read and written back */
static void check_trade_extended_message(void) {
  TradeExtendedMessage sent;
  TradeExtendedMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_trade_extended_message(&sent);
  assert(encode_trade_extended_message(&sent, wire, 0) == 53);
  assert(decode_trade_extended_message(&got, wire, 0) == 53);
  equal_trade_extended_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_extended_message(&got, wire, 0) == 53);
  assert(encode_trade_extended_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Break Message: 12 bytes ------------------------------------------- */

/* The Trade Break message is sent whenever an execution on Cboe is broken. */
typedef struct {
  uint8_t execution_id[12];  /* bytes 0 to 11 */
} TradeBreakMessage;

/* any Trade Break Message at all: every byte one the checker chooses */
static void any_trade_break_message(TradeBreakMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = arbitrary(); }
}

/* Trade Break Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_trade_break_message(const TradeBreakMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Trade Break Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_trade_break_message(TradeBreakMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Break Message is what was written, byte for byte */
static void equal_trade_break_message(const TradeBreakMessage *read, const TradeBreakMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Trade Break Message: written and read back, then read and written back */
static void check_trade_break_message(void) {
  TradeBreakMessage sent;
  TradeBreakMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_trade_break_message(&sent);
  assert(encode_trade_break_message(&sent, wire, 0) == 12);
  assert(decode_trade_break_message(&got, wire, 0) == 12);
  equal_trade_break_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_break_message(&got, wire, 0) == 12);
  assert(encode_trade_break_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 12 bytes ---------------------------------------- */

/* The Trading Status message is used to indicate the current trading status of a security. */
typedef struct {
  uint8_t stock_symbol_long[8];  /* bytes 0 to 7 */
  uint8_t halt_status;           /* byte 8 */
  uint8_t reg_sho_action;        /* byte 9 */
  uint8_t reserved_1;            /* byte 10 */
  uint8_t reserved_2;            /* byte 11 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = arbitrary(); }
  record->halt_status = arbitrary();
  record->reg_sho_action = arbitrary();
  record->reserved_1 = arbitrary();
  record->reserved_2 = arbitrary();
}

/* Trading Status Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_symbol_long[i]; }
  wire[at++] = record->halt_status;
  wire[at++] = record->reg_sho_action;
  wire[at++] = record->reserved_1;
  wire[at++] = record->reserved_2;

  return at;
}

/* Trading Status Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = wire[at++]; }
  record->halt_status = wire[at++];
  record->reg_sho_action = wire[at++];
  record->reserved_1 = wire[at++];
  record->reserved_2 = wire[at++];

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock_symbol_long[i] == written->stock_symbol_long[i]); }
  assert(read->halt_status == written->halt_status);
  assert(read->reg_sho_action == written->reg_sho_action);
  assert(read->reserved_1 == written->reserved_1);
  assert(read->reserved_2 == written->reserved_2);
}

/* Trading Status Message: written and read back, then read and written back */
static void check_trading_status_message(void) {
  TradingStatusMessage sent;
  TradingStatusMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_trading_status_message(&sent);
  assert(encode_trading_status_message(&sent, wire, 0) == 12);
  assert(decode_trading_status_message(&got, wire, 0) == 12);
  equal_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_message(&got, wire, 0) == 12);
  assert(encode_trading_status_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Update Message: 59 bytes ---------------------------------------- */

/* Auction Update messages are used to disseminate Cboe price and size information during auctions for Cboe listed securities on BZX, and for Periodic Auctions on BYX. */
typedef struct {
  uint8_t stock_symbol_long[8];          /* bytes 0 to 7 */
  uint8_t auction_type;                  /* byte 8 */
  uint8_t reference_price_short[10];     /* bytes 9 to 18 */
  uint8_t buy_shares[10];                /* bytes 19 to 28 */
  uint8_t sell_shares[10];               /* bytes 29 to 38 */
  uint8_t indicative_price_short[10];    /* bytes 39 to 48 */
  uint8_t auction_only_price_short[10];  /* bytes 49 to 58 */
} AuctionUpdateMessage;

/* any Auction Update Message at all: every byte one the checker chooses */
static void any_auction_update_message(AuctionUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->reference_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->buy_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->sell_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->indicative_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->auction_only_price_short[i] = arbitrary(); }
}

/* Auction Update Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_auction_update_message(const AuctionUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_symbol_long[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reference_price_short[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->buy_shares[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sell_shares[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->indicative_price_short[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->auction_only_price_short[i]; }

  return at;
}

/* Auction Update Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_auction_update_message(AuctionUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->reference_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->buy_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->sell_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->indicative_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->auction_only_price_short[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Update Message is what was written, byte for byte */
static void equal_auction_update_message(const AuctionUpdateMessage *read, const AuctionUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock_symbol_long[i] == written->stock_symbol_long[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 10; i++) { assert(read->reference_price_short[i] == written->reference_price_short[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->buy_shares[i] == written->buy_shares[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->sell_shares[i] == written->sell_shares[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->indicative_price_short[i] == written->indicative_price_short[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->auction_only_price_short[i] == written->auction_only_price_short[i]); }
}

/* Auction Update Message: written and read back, then read and written back */
static void check_auction_update_message(void) {
  AuctionUpdateMessage sent;
  AuctionUpdateMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_auction_update_message(&sent);
  assert(encode_auction_update_message(&sent, wire, 0) == 59);
  assert(decode_auction_update_message(&got, wire, 0) == 59);
  equal_auction_update_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_update_message(&got, wire, 0) == 59);
  assert(encode_auction_update_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- Extended Auction Update Message: 71 bytes ------------------------------- */

/* The extended version of the BZX Auction Update message accommodates larger prices. */
typedef struct {
  uint8_t stock_symbol_long[8];         /* bytes 0 to 7 */
  uint8_t auction_type;                 /* byte 8 */
  uint8_t reference_price_long[14];     /* bytes 9 to 22 */
  uint8_t buy_shares[10];               /* bytes 23 to 32 */
  uint8_t sell_shares[10];              /* bytes 33 to 42 */
  uint8_t indicative_price_long[14];    /* bytes 43 to 56 */
  uint8_t auction_only_price_long[14];  /* bytes 57 to 70 */
} ExtendedAuctionUpdateMessage;

/* any Extended Auction Update Message at all: every byte one the checker chooses */
static void any_extended_auction_update_message(ExtendedAuctionUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->reference_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->buy_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->sell_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->indicative_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->auction_only_price_long[i] = arbitrary(); }
}

/* Extended Auction Update Message to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_extended_auction_update_message(const ExtendedAuctionUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_symbol_long[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->reference_price_long[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->buy_shares[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sell_shares[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->indicative_price_long[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->auction_only_price_long[i]; }

  return at;
}

/* Extended Auction Update Message off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_extended_auction_update_message(ExtendedAuctionUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->reference_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->buy_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->sell_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->indicative_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->auction_only_price_long[i] = wire[at++]; }

  return at;
}

/* what was read of Extended Auction Update Message is what was written, byte for byte */
static void equal_extended_auction_update_message(const ExtendedAuctionUpdateMessage *read, const ExtendedAuctionUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock_symbol_long[i] == written->stock_symbol_long[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 14; i++) { assert(read->reference_price_long[i] == written->reference_price_long[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->buy_shares[i] == written->buy_shares[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->sell_shares[i] == written->sell_shares[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->indicative_price_long[i] == written->indicative_price_long[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->auction_only_price_long[i] == written->auction_only_price_long[i]); }
}

/* Extended Auction Update Message: written and read back, then read and written back */
static void check_extended_auction_update_message(void) {
  ExtendedAuctionUpdateMessage sent;
  ExtendedAuctionUpdateMessage got;
  uint8_t wire[71];
  uint8_t again[71];

  any_extended_auction_update_message(&sent);
  assert(encode_extended_auction_update_message(&sent, wire, 0) == 71);
  assert(decode_extended_auction_update_message(&got, wire, 0) == 71);
  equal_extended_auction_update_message(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_extended_auction_update_message(&got, wire, 0) == 71);
  assert(encode_extended_auction_update_message(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Summary Message: 29 bytes --------------------------------------- */

/* Auction Summary messages are used to disseminate the results of an auction of a Cboe listed security on BZX, and for Periodic Auctions on BYX. */
typedef struct {
  uint8_t stock_symbol_long[8];  /* bytes 0 to 7 */
  uint8_t auction_type;          /* byte 8 */
  uint8_t price_short[10];       /* bytes 9 to 18 */
  uint8_t shares_long[10];       /* bytes 19 to 28 */
} AuctionSummaryMessage;

/* any Auction Summary Message at all: every byte one the checker chooses */
static void any_auction_summary_message(AuctionSummaryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->shares_long[i] = arbitrary(); }
}

/* Auction Summary Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_auction_summary_message(const AuctionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_symbol_long[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->shares_long[i]; }

  return at;
}

/* Auction Summary Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_auction_summary_message(AuctionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->shares_long[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Summary Message is what was written, byte for byte */
static void equal_auction_summary_message(const AuctionSummaryMessage *read, const AuctionSummaryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock_symbol_long[i] == written->stock_symbol_long[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 10; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->shares_long[i] == written->shares_long[i]); }
}

/* Auction Summary Message: written and read back, then read and written back */
static void check_auction_summary_message(void) {
  AuctionSummaryMessage sent;
  AuctionSummaryMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_auction_summary_message(&sent);
  assert(encode_auction_summary_message(&sent, wire, 0) == 29);
  assert(decode_auction_summary_message(&got, wire, 0) == 29);
  equal_auction_summary_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_summary_message(&got, wire, 0) == 29);
  assert(encode_auction_summary_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Extended Auction Summary Message: 33 bytes ------------------------------ */

/* The extended version of the Auction Summary message accommodates larger prices. */
typedef struct {
  uint8_t stock_symbol_long[8];  /* bytes 0 to 7 */
  uint8_t auction_type;          /* byte 8 */
  uint8_t price_long[14];        /* bytes 9 to 22 */
  uint8_t shares_long[10];       /* bytes 23 to 32 */
} ExtendedAuctionSummaryMessage;

/* any Extended Auction Summary Message at all: every byte one the checker chooses */
static void any_extended_auction_summary_message(ExtendedAuctionSummaryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->shares_long[i] = arbitrary(); }
}

/* Extended Auction Summary Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_extended_auction_summary_message(const ExtendedAuctionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_symbol_long[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->shares_long[i]; }

  return at;
}

/* Extended Auction Summary Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_extended_auction_summary_message(ExtendedAuctionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->shares_long[i] = wire[at++]; }

  return at;
}

/* what was read of Extended Auction Summary Message is what was written, byte for byte */
static void equal_extended_auction_summary_message(const ExtendedAuctionSummaryMessage *read, const ExtendedAuctionSummaryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock_symbol_long[i] == written->stock_symbol_long[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 14; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->shares_long[i] == written->shares_long[i]); }
}

/* Extended Auction Summary Message: written and read back, then read and written back */
static void check_extended_auction_summary_message(void) {
  ExtendedAuctionSummaryMessage sent;
  ExtendedAuctionSummaryMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_extended_auction_summary_message(&sent);
  assert(encode_extended_auction_summary_message(&sent, wire, 0) == 33);
  assert(decode_extended_auction_summary_message(&got, wire, 0) == 33);
  equal_extended_auction_summary_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_extended_auction_summary_message(&got, wire, 0) == 33);
  assert(encode_extended_auction_summary_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retail Price Improvement Message: 9 bytes ------------------------------- */

/* The Retail Price Improvement message is only available on the BYX Exchange. This message is a Retail Liquidity Indicator (RLI) that includes symbol and side, but not price and size. */
typedef struct {
  uint8_t stock_symbol_long[8];      /* bytes 0 to 7 */
  uint8_t retail_price_improvement;  /* byte 8 */
} RetailPriceImprovementMessage;

/* any Retail Price Improvement Message at all: every byte one the checker chooses */
static void any_retail_price_improvement_message(RetailPriceImprovementMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = arbitrary(); }
  record->retail_price_improvement = arbitrary();
}

/* Retail Price Improvement Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_retail_price_improvement_message(const RetailPriceImprovementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_symbol_long[i]; }
  wire[at++] = record->retail_price_improvement;

  return at;
}

/* Retail Price Improvement Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_retail_price_improvement_message(RetailPriceImprovementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->stock_symbol_long[i] = wire[at++]; }
  record->retail_price_improvement = wire[at++];

  return at;
}

/* what was read of Retail Price Improvement Message is what was written, byte for byte */
static void equal_retail_price_improvement_message(const RetailPriceImprovementMessage *read, const RetailPriceImprovementMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->stock_symbol_long[i] == written->stock_symbol_long[i]); }
  assert(read->retail_price_improvement == written->retail_price_improvement);
}

/* Retail Price Improvement Message: written and read back, then read and written back */
static void check_retail_price_improvement_message(void) {
  RetailPriceImprovementMessage sent;
  RetailPriceImprovementMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_retail_price_improvement_message(&sent);
  assert(encode_retail_price_improvement_message(&sent, wire, 0) == 9);
  assert(decode_retail_price_improvement_message(&got, wire, 0) == 9);
  equal_retail_price_improvement_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_retail_price_improvement_message(&got, wire, 0) == 9);
  assert(encode_retail_price_improvement_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request Packet: 36 bytes ------------------------------------------ */

/* The Soup 2.0 client must send a Login Request Packet immediately upon establishing a new TCP/IP socket connection to the server. */
typedef struct {
  uint8_t username[6];                    /* bytes 0 to 5 */
  uint8_t password[10];                   /* bytes 6 to 15 */
  uint8_t requested_session[10];          /* bytes 16 to 25 */
  uint8_t requested_sequence_number[10];  /* bytes 26 to 35 */
} LoginRequestPacket;

/* any Login Request Packet at all: every byte one the checker chooses */
static void any_login_request_packet(LoginRequestPacket *record) {
  for (size_t i = 0; i < 6; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->requested_session[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->requested_sequence_number[i] = arbitrary(); }
}

/* Login Request Packet to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_login_request_packet(const LoginRequestPacket *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->requested_session[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->requested_sequence_number[i]; }

  return at;
}

/* Login Request Packet off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_login_request_packet(LoginRequestPacket *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->requested_session[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->requested_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request Packet is what was written, byte for byte */
static void equal_login_request_packet(const LoginRequestPacket *read, const LoginRequestPacket *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->requested_session[i] == written->requested_session[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->requested_sequence_number[i] == written->requested_sequence_number[i]); }
}

/* Login Request Packet: written and read back, then read and written back */
static void check_login_request_packet(void) {
  LoginRequestPacket sent;
  LoginRequestPacket got;
  uint8_t wire[36];
  uint8_t again[36];

  any_login_request_packet(&sent);
  assert(encode_login_request_packet(&sent, wire, 0) == 36);
  assert(decode_login_request_packet(&got, wire, 0) == 36);
  equal_login_request_packet(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request_packet(&got, wire, 0) == 36);
  assert(encode_login_request_packet(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_debug_packet();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_sequenced_message_header();
  check_symbol_clear_message();
  check_add_order_short_message();
  check_add_order_long_message();
  check_add_order_extended_message();
  check_order_executed_message();
  check_order_cancel_message();
  check_trade_short_message();
  check_trade_long_message();
  check_trade_extended_message();
  check_trade_break_message();
  check_trading_status_message();
  check_auction_update_message();
  check_extended_auction_update_message();
  check_auction_summary_message();
  check_extended_auction_summary_message();
  check_retail_price_improvement_message();
  check_login_request_packet();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
