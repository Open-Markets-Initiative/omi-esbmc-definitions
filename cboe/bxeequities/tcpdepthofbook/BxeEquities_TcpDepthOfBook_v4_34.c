// cboe/bxeequities/tcpdepthofbook/BxeEquities_TcpDepthOfBook_v4_34.c
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

/* ---- Sequenced Message Header: 12 bytes -------------------------------------- */

/* Cboe Europe ASCII Soup sequenced message header (microsecond timestamp) */
typedef struct {
  uint8_t timestamp[11];           /* bytes 0 to 10 */
  uint8_t sequenced_message_type;  /* byte 11 */
} SequencedMessageHeader;

/* any Sequenced Message Header at all: every byte one the checker chooses */
static void any_sequenced_message_header(SequencedMessageHeader *record) {
  for (size_t i = 0; i < 11; i++) { record->timestamp[i] = arbitrary(); }
  record->sequenced_message_type = arbitrary();
}

/* Sequenced Message Header to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_sequenced_message_header(const SequencedMessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->sequenced_message_type;

  return at;
}

/* Sequenced Message Header off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_sequenced_message_header(SequencedMessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->timestamp[i] = wire[at++]; }
  record->sequenced_message_type = wire[at++];

  return at;
}

/* what was read of Sequenced Message Header is what was written, byte for byte */
static void equal_sequenced_message_header(const SequencedMessageHeader *read, const SequencedMessageHeader *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->sequenced_message_type == written->sequenced_message_type);
}

/* Sequenced Message Header: written and read back, then read and written back */
static void check_sequenced_message_header(void) {
  SequencedMessageHeader sent;
  SequencedMessageHeader got;
  uint8_t wire[12];
  uint8_t again[12];

  any_sequenced_message_header(&sent);
  assert(encode_sequenced_message_header(&sent, wire, 0) == 12);
  assert(decode_sequenced_message_header(&got, wire, 0) == 12);
  equal_sequenced_message_header(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_sequenced_message_header(&got, wire, 0) == 12);
  assert(encode_sequenced_message_header(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Clear Message: 8 bytes ------------------------------------------- */

/* Instructs feed recipients to clear all orders for the Cboe book in the specified symbol; sent in recovery events such as a data centre fail-over. */
typedef struct {
  uint8_t symbol_long[8];  /* bytes 0 to 7 */
} SymbolClearMessage;

/* any Symbol Clear Message at all: every byte one the checker chooses */
static void any_symbol_clear_message(SymbolClearMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = arbitrary(); }
}

/* Symbol Clear Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_symbol_clear_message(const SymbolClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_long[i]; }

  return at;
}

/* Symbol Clear Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_symbol_clear_message(SymbolClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Clear Message is what was written, byte for byte */
static void equal_symbol_clear_message(const SymbolClearMessage *read, const SymbolClearMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
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

/* ---- Add Order Message: 36 bytes --------------------------------------------- */

/* Represents a newly accepted visible order on the Cboe book with a day-specific Order ID. */
typedef struct {
  uint8_t order_id[12];     /* bytes 0 to 11 */
  uint8_t side_indicator;   /* byte 12 */
  uint8_t shares_short[6];  /* bytes 13 to 18 */
  uint8_t symbol_short[6];  /* bytes 19 to 24 */
  uint8_t price_short[10];  /* bytes 25 to 34 */
  uint8_t display;          /* byte 35 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares_short[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price_short[i] = arbitrary(); }
  record->display = arbitrary();
}

/* Add Order Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares_short[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price_short[i]; }
  wire[at++] = record->display;

  return at;
}

/* Add Order Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares_short[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price_short[i] = wire[at++]; }
  record->display = wire[at++];

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->shares_short[i] == written->shares_short[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price_short[i] == written->price_short[i]); }
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

/* ---- Add Order Message Long Form: 51 bytes ----------------------------------- */

/* Cboe European platform only. As Add Order Message but with longer Shares, Symbol and Price fields. */
typedef struct {
  uint8_t order_id[12];     /* bytes 0 to 11 */
  uint8_t side_indicator;   /* byte 12 */
  uint8_t shares_long[10];  /* bytes 13 to 22 */
  uint8_t symbol_long[8];   /* bytes 23 to 30 */
  uint8_t price_long[19];   /* bytes 31 to 49 */
  uint8_t display;          /* byte 50 */
} AddOrderMessageLongForm;

/* any Add Order Message Long Form at all: every byte one the checker chooses */
static void any_add_order_message_long_form(AddOrderMessageLongForm *record) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->shares_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 19; i++) { record->price_long[i] = arbitrary(); }
  record->display = arbitrary();
}

/* Add Order Message Long Form to the wire: 51 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message_long_form(const AddOrderMessageLongForm *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->shares_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 19; i++) { wire[at++] = record->price_long[i]; }
  wire[at++] = record->display;

  return at;
}

/* Add Order Message Long Form off the wire: 51 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message_long_form(AddOrderMessageLongForm *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->shares_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 19; i++) { record->price_long[i] = wire[at++]; }
  record->display = wire[at++];

  return at;
}

/* what was read of Add Order Message Long Form is what was written, byte for byte */
static void equal_add_order_message_long_form(const AddOrderMessageLongForm *read, const AddOrderMessageLongForm *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 10; i++) { assert(read->shares_long[i] == written->shares_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 19; i++) { assert(read->price_long[i] == written->price_long[i]); }
  assert(read->display == written->display);
}

/* Add Order Message Long Form: written and read back, then read and written back */
static void check_add_order_message_long_form(void) {
  AddOrderMessageLongForm sent;
  AddOrderMessageLongForm got;
  uint8_t wire[51];
  uint8_t again[51];

  any_add_order_message_long_form(&sent);
  assert(encode_add_order_message_long_form(&sent, wire, 0) == 51);
  assert(decode_add_order_message_long_form(&got, wire, 0) == 51);
  equal_add_order_message_long_form(&got, &sent);

  for (size_t i = 0; i < 51; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message_long_form(&got, wire, 0) == 51);
  assert(encode_add_order_message_long_form(&got, again, 0) == 51);
  for (size_t i = 0; i < 51; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 34 bytes ---------------------------------------- */

/* Sent when a visible order on the Cboe book is executed in whole or in part at the original Add Order price. */
typedef struct {
  uint8_t order_id[12];              /* bytes 0 to 11 */
  uint8_t executed_shares_short[6];  /* bytes 12 to 17 */
  uint8_t execution_id[12];          /* bytes 18 to 29 */
  uint8_t execution_flag[4];         /* bytes 30 to 33 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->executed_shares_short[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_flag[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->executed_shares_short[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_flag[i]; }

  return at;
}

/* Order Executed Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->executed_shares_short[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_flag[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->executed_shares_short[i] == written->executed_shares_short[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_flag[i] == written->execution_flag[i]); }
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

/* ---- Order Executed Message Long Form: 38 bytes ------------------------------ */

/* Cboe European platform only. As Order Executed Message but with a longer Executed Shares field. */
typedef struct {
  uint8_t order_id[12];              /* bytes 0 to 11 */
  uint8_t executed_shares_long[10];  /* bytes 12 to 21 */
  uint8_t execution_id[12];          /* bytes 22 to 33 */
  uint8_t execution_flags[4];        /* bytes 34 to 37 */
} OrderExecutedMessageLongForm;

/* any Order Executed Message Long Form at all: every byte one the checker chooses */
static void any_order_executed_message_long_form(OrderExecutedMessageLongForm *record) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->executed_shares_long[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_flags[i] = arbitrary(); }
}

/* Order Executed Message Long Form to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message_long_form(const OrderExecutedMessageLongForm *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->executed_shares_long[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_flags[i]; }

  return at;
}

/* Order Executed Message Long Form off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message_long_form(OrderExecutedMessageLongForm *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->executed_shares_long[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_flags[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message Long Form is what was written, byte for byte */
static void equal_order_executed_message_long_form(const OrderExecutedMessageLongForm *read, const OrderExecutedMessageLongForm *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->executed_shares_long[i] == written->executed_shares_long[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_flags[i] == written->execution_flags[i]); }
}

/* Order Executed Message Long Form: written and read back, then read and written back */
static void check_order_executed_message_long_form(void) {
  OrderExecutedMessageLongForm sent;
  OrderExecutedMessageLongForm got;
  uint8_t wire[38];
  uint8_t again[38];

  any_order_executed_message_long_form(&sent);
  assert(encode_order_executed_message_long_form(&sent, wire, 0) == 38);
  assert(decode_order_executed_message_long_form(&got, wire, 0) == 38);
  equal_order_executed_message_long_form(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message_long_form(&got, wire, 0) == 38);
  assert(encode_order_executed_message_long_form(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Message: 18 bytes ------------------------------------------ */

/* Sent when a visible order on the Cboe book is cancelled in whole or in part. */
typedef struct {
  uint8_t order_id[12];               /* bytes 0 to 11 */
  uint8_t cancelled_shares_short[6];  /* bytes 12 to 17 */
} OrderCancelMessage;

/* any Order Cancel Message at all: every byte one the checker chooses */
static void any_order_cancel_message(OrderCancelMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cancelled_shares_short[i] = arbitrary(); }
}

/* Order Cancel Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_message(const OrderCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cancelled_shares_short[i]; }

  return at;
}

/* Order Cancel Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_message(OrderCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cancelled_shares_short[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Message is what was written, byte for byte */
static void equal_order_cancel_message(const OrderCancelMessage *read, const OrderCancelMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cancelled_shares_short[i] == written->cancelled_shares_short[i]); }
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

/* ---- Order Cancel Message Long Form: 22 bytes -------------------------------- */

/* Cboe European platform only. As Order Cancel Message but with a longer Cancelled Shares field. */
typedef struct {
  uint8_t order_id[12];               /* bytes 0 to 11 */
  uint8_t cancelled_shares_long[10];  /* bytes 12 to 21 */
} OrderCancelMessageLongForm;

/* any Order Cancel Message Long Form at all: every byte one the checker chooses */
static void any_order_cancel_message_long_form(OrderCancelMessageLongForm *record) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cancelled_shares_long[i] = arbitrary(); }
}

/* Order Cancel Message Long Form to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_message_long_form(const OrderCancelMessageLongForm *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cancelled_shares_long[i]; }

  return at;
}

/* Order Cancel Message Long Form off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_message_long_form(OrderCancelMessageLongForm *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cancelled_shares_long[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Message Long Form is what was written, byte for byte */
static void equal_order_cancel_message_long_form(const OrderCancelMessageLongForm *read, const OrderCancelMessageLongForm *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cancelled_shares_long[i] == written->cancelled_shares_long[i]); }
}

/* Order Cancel Message Long Form: written and read back, then read and written back */
static void check_order_cancel_message_long_form(void) {
  OrderCancelMessageLongForm sent;
  OrderCancelMessageLongForm got;
  uint8_t wire[22];
  uint8_t again[22];

  any_order_cancel_message_long_form(&sent);
  assert(encode_order_cancel_message_long_form(&sent, wire, 0) == 22);
  assert(decode_order_cancel_message_long_form(&got, wire, 0) == 22);
  equal_order_cancel_message_long_form(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_message_long_form(&got, wire, 0) == 22);
  assert(encode_order_cancel_message_long_form(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 52 bytes ------------------------------------------------- */

/* Provides information about executions of non-displayed orders/shares and negotiated trades. Does not alter the book. */
typedef struct {
  uint8_t order_id[12];      /* bytes 0 to 11 */
  uint8_t side_indicator;    /* byte 12 */
  uint8_t shares_short[6];   /* bytes 13 to 18 */
  uint8_t symbol_short[6];   /* bytes 19 to 24 */
  uint8_t price_short[10];   /* bytes 25 to 34 */
  uint8_t execution_id[12];  /* bytes 35 to 46 */
  uint8_t trade_flags[5];    /* bytes 47 to 51 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares_short[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->trade_flags[i] = arbitrary(); }
}

/* Trade Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares_short[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->trade_flags[i]; }

  return at;
}

/* Trade Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares_short[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->trade_flags[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->shares_short[i] == written->shares_short[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->trade_flags[i] == written->trade_flags[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 52);
  assert(decode_trade_message(&got, wire, 0) == 52);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 52);
  assert(encode_trade_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message Long Form: 67 bytes --------------------------------------- */

/* Cboe European platform only. As Trade Message but with longer Shares and Price fields. */
typedef struct {
  uint8_t order_id[12];      /* bytes 0 to 11 */
  uint8_t side_indicator;    /* byte 12 */
  uint8_t shares_long[10];   /* bytes 13 to 22 */
  uint8_t symbol_long[8];    /* bytes 23 to 30 */
  uint8_t price_long[19];    /* bytes 31 to 49 */
  uint8_t execution_id[12];  /* bytes 50 to 61 */
  uint8_t trade_flags[5];    /* bytes 62 to 66 */
} TradeMessageLongForm;

/* any Trade Message Long Form at all: every byte one the checker chooses */
static void any_trade_message_long_form(TradeMessageLongForm *record) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->shares_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 19; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->trade_flags[i] = arbitrary(); }
}

/* Trade Message Long Form to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_trade_message_long_form(const TradeMessageLongForm *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->shares_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 19; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->trade_flags[i]; }

  return at;
}

/* Trade Message Long Form off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_trade_message_long_form(TradeMessageLongForm *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->shares_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 19; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->trade_flags[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message Long Form is what was written, byte for byte */
static void equal_trade_message_long_form(const TradeMessageLongForm *read, const TradeMessageLongForm *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 10; i++) { assert(read->shares_long[i] == written->shares_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 19; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->trade_flags[i] == written->trade_flags[i]); }
}

/* Trade Message Long Form: written and read back, then read and written back */
static void check_trade_message_long_form(void) {
  TradeMessageLongForm sent;
  TradeMessageLongForm got;
  uint8_t wire[67];
  uint8_t again[67];

  any_trade_message_long_form(&sent);
  assert(encode_trade_message_long_form(&sent, wire, 0) == 67);
  assert(decode_trade_message_long_form(&got, wire, 0) == 67);
  equal_trade_message_long_form(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message_long_form(&got, wire, 0) == 67);
  assert(encode_trade_message_long_form(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message Extended Form: 89 bytes ----------------------------------- */

/* Cboe European platform only. Extended details of trades reported to or executed by Cboe (e.g. privately negotiated trades brought on-exchange). */
typedef struct {
  uint8_t shares_extended[12];       /* bytes 0 to 11 */
  uint8_t symbol_long[8];            /* bytes 12 to 19 */
  uint8_t price_long[19];            /* bytes 20 to 38 */
  uint8_t trade_id[12];              /* bytes 39 to 50 */
  uint8_t trade_date[8];             /* bytes 51 to 58 */
  uint8_t trade_time[8];             /* bytes 59 to 66 */
  uint8_t execution_venue[4];        /* bytes 67 to 70 */
  uint8_t currency[3];               /* bytes 71 to 73 */
  uint8_t cboe_trade_flags;          /* byte 74 */
  uint8_t extended_trade_flags[14];  /* bytes 75 to 88 */
} TradeMessageExtendedForm;

/* any Trade Message Extended Form at all: every byte one the checker chooses */
static void any_trade_message_extended_form(TradeMessageExtendedForm *record) {
  for (size_t i = 0; i < 12; i++) { record->shares_extended[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 19; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  record->cboe_trade_flags = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->extended_trade_flags[i] = arbitrary(); }
}

/* Trade Message Extended Form to the wire: 89 bytes from at, returning where the next byte goes */
static size_t encode_trade_message_extended_form(const TradeMessageExtendedForm *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->shares_extended[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 19; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_venue[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->cboe_trade_flags;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->extended_trade_flags[i]; }

  return at;
}

/* Trade Message Extended Form off the wire: 89 bytes from at, returning where the next byte lies */
static size_t decode_trade_message_extended_form(TradeMessageExtendedForm *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->shares_extended[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 19; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  record->cboe_trade_flags = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->extended_trade_flags[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message Extended Form is what was written, byte for byte */
static void equal_trade_message_extended_form(const TradeMessageExtendedForm *read, const TradeMessageExtendedForm *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->shares_extended[i] == written->shares_extended[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 19; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_time[i] == written->trade_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_venue[i] == written->execution_venue[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->cboe_trade_flags == written->cboe_trade_flags);
  for (size_t i = 0; i < 14; i++) { assert(read->extended_trade_flags[i] == written->extended_trade_flags[i]); }
}

/* Trade Message Extended Form: written and read back, then read and written back */
static void check_trade_message_extended_form(void) {
  TradeMessageExtendedForm sent;
  TradeMessageExtendedForm got;
  uint8_t wire[89];
  uint8_t again[89];

  any_trade_message_extended_form(&sent);
  assert(encode_trade_message_extended_form(&sent, wire, 0) == 89);
  assert(decode_trade_message_extended_form(&got, wire, 0) == 89);
  equal_trade_message_extended_form(&got, &sent);

  for (size_t i = 0; i < 89; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message_extended_form(&got, wire, 0) == 89);
  assert(encode_trade_message_extended_form(&got, again, 0) == 89);
  for (size_t i = 0; i < 89; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message Unknown Symbol: 93 bytes ---------------------------------- */

/* Cboe European Trade Reporting Facility only. Trades reported to Cboe on a symbol not currently known, identified by ISIN and currency. */
typedef struct {
  uint8_t shares_extended[12];       /* bytes 0 to 11 */
  uint8_t symbol_extended[12];       /* bytes 12 to 23 */
  uint8_t price_long[19];            /* bytes 24 to 42 */
  uint8_t trade_id[12];              /* bytes 43 to 54 */
  uint8_t trade_date[8];             /* bytes 55 to 62 */
  uint8_t trade_time[8];             /* bytes 63 to 70 */
  uint8_t execution_venue[4];        /* bytes 71 to 74 */
  uint8_t currency[3];               /* bytes 75 to 77 */
  uint8_t cboe_trade_flags;          /* byte 78 */
  uint8_t extended_trade_flags[14];  /* bytes 79 to 92 */
} TradeMessageUnknownSymbol;

/* any Trade Message Unknown Symbol at all: every byte one the checker chooses */
static void any_trade_message_unknown_symbol(TradeMessageUnknownSymbol *record) {
  for (size_t i = 0; i < 12; i++) { record->shares_extended[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol_extended[i] = arbitrary(); }
  for (size_t i = 0; i < 19; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  record->cboe_trade_flags = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->extended_trade_flags[i] = arbitrary(); }
}

/* Trade Message Unknown Symbol to the wire: 93 bytes from at, returning where the next byte goes */
static size_t encode_trade_message_unknown_symbol(const TradeMessageUnknownSymbol *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->shares_extended[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol_extended[i]; }
  for (size_t i = 0; i < 19; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_venue[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->cboe_trade_flags;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->extended_trade_flags[i]; }

  return at;
}

/* Trade Message Unknown Symbol off the wire: 93 bytes from at, returning where the next byte lies */
static size_t decode_trade_message_unknown_symbol(TradeMessageUnknownSymbol *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->shares_extended[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol_extended[i] = wire[at++]; }
  for (size_t i = 0; i < 19; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  record->cboe_trade_flags = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->extended_trade_flags[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message Unknown Symbol is what was written, byte for byte */
static void equal_trade_message_unknown_symbol(const TradeMessageUnknownSymbol *read, const TradeMessageUnknownSymbol *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->shares_extended[i] == written->shares_extended[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol_extended[i] == written->symbol_extended[i]); }
  for (size_t i = 0; i < 19; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_time[i] == written->trade_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_venue[i] == written->execution_venue[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->cboe_trade_flags == written->cboe_trade_flags);
  for (size_t i = 0; i < 14; i++) { assert(read->extended_trade_flags[i] == written->extended_trade_flags[i]); }
}

/* Trade Message Unknown Symbol: written and read back, then read and written back */
static void check_trade_message_unknown_symbol(void) {
  TradeMessageUnknownSymbol sent;
  TradeMessageUnknownSymbol got;
  uint8_t wire[93];
  uint8_t again[93];

  any_trade_message_unknown_symbol(&sent);
  assert(encode_trade_message_unknown_symbol(&sent, wire, 0) == 93);
  assert(decode_trade_message_unknown_symbol(&got, wire, 0) == 93);
  equal_trade_message_unknown_symbol(&got, &sent);

  for (size_t i = 0; i < 93; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message_unknown_symbol(&got, wire, 0) == 93);
  assert(encode_trade_message_unknown_symbol(&got, again, 0) == 93);
  for (size_t i = 0; i < 93; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 12 bytes ---------------------------------------- */

/* Indicates the current trading status of a security; sent whenever the status changes and for all Suspended securities before trading hours. */
typedef struct {
  uint8_t symbol_long[8];  /* bytes 0 to 7 */
  uint8_t status;          /* byte 8 */
  uint8_t reserved[3];     /* bytes 9 to 11 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = arbitrary(); }
  record->status = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved[i] = arbitrary(); }
}

/* Trading Status Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->status;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved[i]; }

  return at;
}

/* Trading Status Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = wire[at++]; }
  record->status = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->status == written->status);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved[i] == written->reserved[i]); }
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

/* ---- Statistics Message: 29 bytes -------------------------------------------- */

/* Cboe European platform only. Disseminates statistics prices: opening, closing, high, low, previous close. */
typedef struct {
  uint8_t symbol_long[8];       /* bytes 0 to 7 */
  uint8_t price_long[19];       /* bytes 8 to 26 */
  uint8_t statistic_type;       /* byte 27 */
  uint8_t price_determination;  /* byte 28 */
} StatisticsMessage;

/* any Statistics Message at all: every byte one the checker chooses */
static void any_statistics_message(StatisticsMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 19; i++) { record->price_long[i] = arbitrary(); }
  record->statistic_type = arbitrary();
  record->price_determination = arbitrary();
}

/* Statistics Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_statistics_message(const StatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 19; i++) { wire[at++] = record->price_long[i]; }
  wire[at++] = record->statistic_type;
  wire[at++] = record->price_determination;

  return at;
}

/* Statistics Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_statistics_message(StatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 19; i++) { record->price_long[i] = wire[at++]; }
  record->statistic_type = wire[at++];
  record->price_determination = wire[at++];

  return at;
}

/* what was read of Statistics Message is what was written, byte for byte */
static void equal_statistics_message(const StatisticsMessage *read, const StatisticsMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 19; i++) { assert(read->price_long[i] == written->price_long[i]); }
  assert(read->statistic_type == written->statistic_type);
  assert(read->price_determination == written->price_determination);
}

/* Statistics Message: written and read back, then read and written back */
static void check_statistics_message(void) {
  StatisticsMessage sent;
  StatisticsMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_statistics_message(&sent);
  assert(encode_statistics_message(&sent, wire, 0) == 29);
  assert(decode_statistics_message(&got, wire, 0) == 29);
  equal_statistics_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_statistics_message(&got, wire, 0) == 29);
  assert(encode_statistics_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Update Message: 59 bytes ---------------------------------------- */

/* Disseminates indicative price and size information during auctions for Cboe auction-eligible securities. */
typedef struct {
  uint8_t symbol_long[8];         /* bytes 0 to 7 */
  uint8_t auction_type;           /* byte 8 */
  uint8_t reference_price[19];    /* bytes 9 to 27 */
  uint8_t indicative_price[19];   /* bytes 28 to 46 */
  uint8_t indicative_shares[10];  /* bytes 47 to 56 */
  uint8_t outside_tolerance;      /* byte 57 */
  uint8_t includes_primary;       /* byte 58 */
} AuctionUpdateMessage;

/* any Auction Update Message at all: every byte one the checker chooses */
static void any_auction_update_message(AuctionUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 19; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 19; i++) { record->indicative_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->indicative_shares[i] = arbitrary(); }
  record->outside_tolerance = arbitrary();
  record->includes_primary = arbitrary();
}

/* Auction Update Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_auction_update_message(const AuctionUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 19; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 19; i++) { wire[at++] = record->indicative_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->indicative_shares[i]; }
  wire[at++] = record->outside_tolerance;
  wire[at++] = record->includes_primary;

  return at;
}

/* Auction Update Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_auction_update_message(AuctionUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 19; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 19; i++) { record->indicative_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->indicative_shares[i] = wire[at++]; }
  record->outside_tolerance = wire[at++];
  record->includes_primary = wire[at++];

  return at;
}

/* what was read of Auction Update Message is what was written, byte for byte */
static void equal_auction_update_message(const AuctionUpdateMessage *read, const AuctionUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 19; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 19; i++) { assert(read->indicative_price[i] == written->indicative_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->indicative_shares[i] == written->indicative_shares[i]); }
  assert(read->outside_tolerance == written->outside_tolerance);
  assert(read->includes_primary == written->includes_primary);
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

/* ---- Auction Summary Message: 38 bytes --------------------------------------- */

/* Disseminates the results of an auction in a Cboe auction-eligible security. */
typedef struct {
  uint8_t symbol_long[8];   /* bytes 0 to 7 */
  uint8_t auction_type;     /* byte 8 */
  uint8_t price_long[19];   /* bytes 9 to 27 */
  uint8_t shares_long[10];  /* bytes 28 to 37 */
} AuctionSummaryMessage;

/* any Auction Summary Message at all: every byte one the checker chooses */
static void any_auction_summary_message(AuctionSummaryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 19; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->shares_long[i] = arbitrary(); }
}

/* Auction Summary Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_auction_summary_message(const AuctionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 19; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->shares_long[i]; }

  return at;
}

/* Auction Summary Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_auction_summary_message(AuctionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 19; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->shares_long[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Summary Message is what was written, byte for byte */
static void equal_auction_summary_message(const AuctionSummaryMessage *read, const AuctionSummaryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 19; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->shares_long[i] == written->shares_long[i]); }
}

/* Auction Summary Message: written and read back, then read and written back */
static void check_auction_summary_message(void) {
  AuctionSummaryMessage sent;
  AuctionSummaryMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_auction_summary_message(&sent);
  assert(encode_auction_summary_message(&sent, wire, 0) == 38);
  assert(decode_auction_summary_message(&got, wire, 0) == 38);
  equal_auction_summary_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_summary_message(&got, wire, 0) == 38);
  assert(encode_auction_summary_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
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
  check_add_order_message();
  check_add_order_message_long_form();
  check_order_executed_message();
  check_order_executed_message_long_form();
  check_order_cancel_message();
  check_order_cancel_message_long_form();
  check_trade_message();
  check_trade_message_long_form();
  check_trade_message_extended_form();
  check_trade_message_unknown_symbol();
  check_trading_status_message();
  check_statistics_message();
  check_auction_update_message();
  check_auction_summary_message();
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
