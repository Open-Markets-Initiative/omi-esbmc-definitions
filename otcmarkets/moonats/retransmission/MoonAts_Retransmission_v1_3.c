// otcmarkets/moonats/retransmission/MoonAts_Retransmission_v1_3.c
/*
 * OTC Markets Group OTC Retransmission
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
 *   - a Reassemble rule
 *   - a length prefix framing what follows
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

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* MoonAts Tcp Message Header */
typedef struct {
  uint8_t message_size[2];  /* bytes 0 to 1 */
  uint8_t message_type;     /* byte 2 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_size[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_size[i] == written->message_size[i]); }
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

/* ---- Start Of Spin Message: 13 bytes ----------------------------------------- */

/* Appears within the TCP spin response cycle (between Spin Response 'S' and 'E') and also on the UDP multicast feeds at the daily spin-out. Indicates the beginning of a spin message cycle. */
typedef struct {
  uint8_t spin_type;                 /* byte 0 */
  uint8_t spin_start_time_milli[8];  /* bytes 1 to 8 */
  uint8_t spin_last_seq_num[4];      /* bytes 9 to 12 */
} StartOfSpinMessage;

/* any Start Of Spin Message at all: every byte one the checker chooses */
static void any_start_of_spin_message(StartOfSpinMessage *record) {
  record->spin_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->spin_start_time_milli[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->spin_last_seq_num[i] = arbitrary(); }
}

/* Start Of Spin Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_start_of_spin_message(const StartOfSpinMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->spin_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->spin_start_time_milli[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->spin_last_seq_num[i]; }

  return at;
}

/* Start Of Spin Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_start_of_spin_message(StartOfSpinMessage *record, const uint8_t *wire, size_t at) {
  record->spin_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->spin_start_time_milli[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->spin_last_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Start Of Spin Message is what was written, byte for byte */
static void equal_start_of_spin_message(const StartOfSpinMessage *read, const StartOfSpinMessage *written) {
  assert(read->spin_type == written->spin_type);
  for (size_t i = 0; i < 8; i++) { assert(read->spin_start_time_milli[i] == written->spin_start_time_milli[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->spin_last_seq_num[i] == written->spin_last_seq_num[i]); }
}

/* Start Of Spin Message: written and read back, then read and written back */
static void check_start_of_spin_message(void) {
  StartOfSpinMessage sent;
  StartOfSpinMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_start_of_spin_message(&sent);
  assert(encode_start_of_spin_message(&sent, wire, 0) == 13);
  assert(decode_start_of_spin_message(&got, wire, 0) == 13);
  equal_start_of_spin_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_spin_message(&got, wire, 0) == 13);
  assert(encode_start_of_spin_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Spin Message: 17 bytes ------------------------------------------- */

/* Appears within the TCP spin response cycle (between Spin Response 'S' and 'E') and also on the UDP multicast feeds at the daily spin-out. Indicates the end of a spin message cycle. */
typedef struct {
  uint8_t spin_type;               /* byte 0 */
  uint8_t spin_msg_ct[4];          /* bytes 1 to 4 */
  uint8_t spin_end_time_milli[8];  /* bytes 5 to 12 */
  uint8_t spin_last_seq_num[4];    /* bytes 13 to 16 */
} EndOfSpinMessage;

/* any End Of Spin Message at all: every byte one the checker chooses */
static void any_end_of_spin_message(EndOfSpinMessage *record) {
  record->spin_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->spin_msg_ct[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->spin_end_time_milli[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->spin_last_seq_num[i] = arbitrary(); }
}

/* End Of Spin Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_end_of_spin_message(const EndOfSpinMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->spin_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->spin_msg_ct[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->spin_end_time_milli[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->spin_last_seq_num[i]; }

  return at;
}

/* End Of Spin Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_end_of_spin_message(EndOfSpinMessage *record, const uint8_t *wire, size_t at) {
  record->spin_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->spin_msg_ct[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->spin_end_time_milli[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->spin_last_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Spin Message is what was written, byte for byte */
static void equal_end_of_spin_message(const EndOfSpinMessage *read, const EndOfSpinMessage *written) {
  assert(read->spin_type == written->spin_type);
  for (size_t i = 0; i < 4; i++) { assert(read->spin_msg_ct[i] == written->spin_msg_ct[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->spin_end_time_milli[i] == written->spin_end_time_milli[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->spin_last_seq_num[i] == written->spin_last_seq_num[i]); }
}

/* End Of Spin Message: written and read back, then read and written back */
static void check_end_of_spin_message(void) {
  EndOfSpinMessage sent;
  EndOfSpinMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_end_of_spin_message(&sent);
  assert(encode_end_of_spin_message(&sent, wire, 0) == 17);
  assert(decode_end_of_spin_message(&got, wire, 0) == 17);
  equal_end_of_spin_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_spin_message(&got, wire, 0) == 17);
  assert(encode_end_of_spin_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Session Message: 9 bytes ---------------------------------------- */

/* Appears in the TCP spin response payload (and on all UDP channels). Sent at the start of each MOON trading session: Order Acceptance at 7:30 PM, Market Open at 8:00 PM, Market Close at 4 AM. */
typedef struct {
  uint8_t session_time[8];  /* bytes 0 to 7 */
  uint8_t trading_session;  /* byte 8 */
} TradingSessionMessage;

/* any Trading Session Message at all: every byte one the checker chooses */
static void any_trading_session_message(TradingSessionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->session_time[i] = arbitrary(); }
  record->trading_session = arbitrary();
}

/* Trading Session Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_trading_session_message(const TradingSessionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_time[i]; }
  wire[at++] = record->trading_session;

  return at;
}

/* Trading Session Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_trading_session_message(TradingSessionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->session_time[i] = wire[at++]; }
  record->trading_session = wire[at++];

  return at;
}

/* what was read of Trading Session Message is what was written, byte for byte */
static void equal_trading_session_message(const TradingSessionMessage *read, const TradingSessionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->session_time[i] == written->session_time[i]); }
  assert(read->trading_session == written->trading_session);
}

/* Trading Session Message: written and read back, then read and written back */
static void check_trading_session_message(void) {
  TradingSessionMessage sent;
  TradingSessionMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_trading_session_message(&sent);
  assert(encode_trading_session_message(&sent, wire, 0) == 9);
  assert(decode_trading_session_message(&got, wire, 0) == 9);
  equal_trading_session_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_session_message(&got, wire, 0) == 9);
  assert(encode_trading_session_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Add Message: 52 bytes --------------------------------------------- */

/* Appears in the TCP spin response payload during DOB replay. Indicates a new order added to the book. */
typedef struct {
  uint8_t time[4];         /* bytes 0 to 3 */
  uint8_t order_id[14];    /* bytes 4 to 17 */
  uint8_t side_indicator;  /* byte 18 */
  uint8_t quantity[4];     /* bytes 19 to 22 */
  uint8_t symbol[14];      /* bytes 23 to 36 */
  uint8_t price[8];        /* bytes 37 to 44 */
  uint8_t firm_id[4];      /* bytes 45 to 48 */
  uint8_t unsolicited;     /* byte 49 */
  uint8_t order_flags[2];  /* bytes 50 to 51 */
} OrderAddMessage;

/* any Order Add Message at all: every byte one the checker chooses */
static void any_order_add_message(OrderAddMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  record->unsolicited = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->order_flags[i] = arbitrary(); }
}

/* Order Add Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_order_add_message(const OrderAddMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  wire[at++] = record->unsolicited;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->order_flags[i]; }

  return at;
}

/* Order Add Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_order_add_message(OrderAddMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  record->unsolicited = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->order_flags[i] = wire[at++]; }

  return at;
}

/* what was read of Order Add Message is what was written, byte for byte */
static void equal_order_add_message(const OrderAddMessage *read, const OrderAddMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  assert(read->unsolicited == written->unsolicited);
  for (size_t i = 0; i < 2; i++) { assert(read->order_flags[i] == written->order_flags[i]); }
}

/* Order Add Message: written and read back, then read and written back */
static void check_order_add_message(void) {
  OrderAddMessage sent;
  OrderAddMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_order_add_message(&sent);
  assert(encode_order_add_message(&sent, wire, 0) == 52);
  assert(decode_order_add_message(&got, wire, 0) == 52);
  equal_order_add_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_order_add_message(&got, wire, 0) == 52);
  assert(encode_order_add_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Update Message: 32 bytes ------------------------------------------ */

/* Appears in the TCP spin response payload during DOB replay. Indicates an existing order has been modified. */
typedef struct {
  uint8_t time[4];         /* bytes 0 to 3 */
  uint8_t order_id[14];    /* bytes 4 to 17 */
  uint8_t quantity[4];     /* bytes 18 to 21 */
  uint8_t price[8];        /* bytes 22 to 29 */
  uint8_t order_flags[2];  /* bytes 30 to 31 */
} OrderUpdateMessage;

/* any Order Update Message at all: every byte one the checker chooses */
static void any_order_update_message(OrderUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->order_flags[i] = arbitrary(); }
}

/* Order Update Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_order_update_message(const OrderUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->order_flags[i]; }

  return at;
}

/* Order Update Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_order_update_message(OrderUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->order_flags[i] = wire[at++]; }

  return at;
}

/* what was read of Order Update Message is what was written, byte for byte */
static void equal_order_update_message(const OrderUpdateMessage *read, const OrderUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->order_flags[i] == written->order_flags[i]); }
}

/* Order Update Message: written and read back, then read and written back */
static void check_order_update_message(void) {
  OrderUpdateMessage sent;
  OrderUpdateMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_order_update_message(&sent);
  assert(encode_order_update_message(&sent, wire, 0) == 32);
  assert(decode_order_update_message(&got, wire, 0) == 32);
  equal_order_update_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_order_update_message(&got, wire, 0) == 32);
  assert(encode_order_update_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Delete Message: 18 bytes ------------------------------------------ */

/* Appears in the TCP spin response payload during DOB replay. Indicates an existing order has been deleted from the book. */
typedef struct {
  uint8_t time[4];       /* bytes 0 to 3 */
  uint8_t order_id[14];  /* bytes 4 to 17 */
} OrderDeleteMessage;

/* any Order Delete Message at all: every byte one the checker chooses */
static void any_order_delete_message(OrderDeleteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_id[i] = arbitrary(); }
}

/* Order Delete Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_order_delete_message(const OrderDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Order Delete Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_order_delete_message(OrderDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Delete Message is what was written, byte for byte */
static void equal_order_delete_message(const OrderDeleteMessage *read, const OrderDeleteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_id[i] == written->order_id[i]); }
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

/* ---- Order Execution Message: 34 bytes --------------------------------------- */

/* Appears in the TCP spin response payload during DOB replay. Published when all or some of the displayed quantity of a previously published order executes at the published price. */
typedef struct {
  uint8_t time[4];                /* bytes 0 to 3 */
  uint8_t order_id[14];           /* bytes 4 to 17 */
  uint8_t executed_quantity[4];   /* bytes 18 to 21 */
  uint8_t remaining_quantity[4];  /* bytes 22 to 25 */
  uint8_t execution_id[8];        /* bytes 26 to 33 */
} OrderExecutionMessage;

/* any Order Execution Message at all: every byte one the checker chooses */
static void any_order_execution_message(OrderExecutionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
}

/* Order Execution Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_order_execution_message(const OrderExecutionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->remaining_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Order Execution Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_order_execution_message(OrderExecutionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Execution Message is what was written, byte for byte */
static void equal_order_execution_message(const OrderExecutionMessage *read, const OrderExecutionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->remaining_quantity[i] == written->remaining_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Order Execution Message: written and read back, then read and written back */
static void check_order_execution_message(void) {
  OrderExecutionMessage sent;
  OrderExecutionMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_order_execution_message(&sent);
  assert(encode_order_execution_message(&sent, wire, 0) == 34);
  assert(decode_order_execution_message(&got, wire, 0) == 34);
  equal_order_execution_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_order_execution_message(&got, wire, 0) == 34);
  assert(encode_order_execution_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Execution With Price Message: 42 bytes ---------------------------- */

/* Appears in the TCP spin response payload during DOB replay. Published when all or some of the displayed quantity of a previously published order executes at a price different than the published price. */
typedef struct {
  uint8_t time[4];                /* bytes 0 to 3 */
  uint8_t order_id[14];           /* bytes 4 to 17 */
  uint8_t executed_quantity[4];   /* bytes 18 to 21 */
  uint8_t remaining_quantity[4];  /* bytes 22 to 25 */
  uint8_t execution_id[8];        /* bytes 26 to 33 */
  uint8_t price[8];               /* bytes 34 to 41 */
} OrderExecutionWithPriceMessage;

/* any Order Execution With Price Message at all: every byte one the checker chooses */
static void any_order_execution_with_price_message(OrderExecutionWithPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Order Execution With Price Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_order_execution_with_price_message(const OrderExecutionWithPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->remaining_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Execution With Price Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_order_execution_with_price_message(OrderExecutionWithPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Execution With Price Message is what was written, byte for byte */
static void equal_order_execution_with_price_message(const OrderExecutionWithPriceMessage *read, const OrderExecutionWithPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->remaining_quantity[i] == written->remaining_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Execution With Price Message: written and read back, then read and written back */
static void check_order_execution_with_price_message(void) {
  OrderExecutionWithPriceMessage sent;
  OrderExecutionWithPriceMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_order_execution_with_price_message(&sent);
  assert(encode_order_execution_with_price_message(&sent, wire, 0) == 42);
  assert(decode_order_execution_with_price_message(&got, wire, 0) == 42);
  equal_order_execution_with_price_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_order_execution_with_price_message(&got, wire, 0) == 42);
  assert(encode_order_execution_with_price_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 47 bytes ------------------------------------------------- */

/* Appears in the TCP spin response payload during DOB replay. Published when non-displayed quantity of a previously published reserve order executes or when an order executes that is less than Min Quote Size and does not currently have an active Order Add message. */
typedef struct {
  uint8_t time[4];                    /* bytes 0 to 3 */
  uint8_t side_indicator;             /* byte 4 */
  uint8_t quantity[4];                /* bytes 5 to 8 */
  uint8_t symbol[14];                 /* bytes 9 to 22 */
  uint8_t price[8];                   /* bytes 23 to 30 */
  uint8_t execution_id[8];            /* bytes 31 to 38 */
  uint8_t reserved_binary_long_8[8];  /* bytes 39 to 46 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_binary_long_8[i] = arbitrary(); }
}

/* Trade Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_binary_long_8[i]; }

  return at;
}

/* Trade Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_binary_long_8[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_binary_long_8[i] == written->reserved_binary_long_8[i]); }
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

/* ---- Top Of Book Message: 43 bytes ------------------------------------------- */

/* Appears in the TCP spin response payload during TOB replay. Provides best bid and offer aggregated top-of-book. */
typedef struct {
  uint8_t time[4];        /* bytes 0 to 3 */
  uint8_t symbol[14];     /* bytes 4 to 17 */
  uint8_t ask_price[8];   /* bytes 18 to 25 */
  uint8_t ask_volume[4];  /* bytes 26 to 29 */
  uint8_t bid_price[8];   /* bytes 30 to 37 */
  uint8_t bid_volume[4];  /* bytes 38 to 41 */
  uint8_t unsolicited;    /* byte 42 */
} TopOfBookMessage;

/* any Top Of Book Message at all: every byte one the checker chooses */
static void any_top_of_book_message(TopOfBookMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_volume[i] = arbitrary(); }
  record->unsolicited = arbitrary();
}

/* Top Of Book Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_top_of_book_message(const TopOfBookMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_volume[i]; }
  wire[at++] = record->unsolicited;

  return at;
}

/* Top Of Book Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_top_of_book_message(TopOfBookMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_volume[i] = wire[at++]; }
  record->unsolicited = wire[at++];

  return at;
}

/* what was read of Top Of Book Message is what was written, byte for byte */
static void equal_top_of_book_message(const TopOfBookMessage *read, const TopOfBookMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_price[i] == written->ask_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_volume[i] == written->ask_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_volume[i] == written->bid_volume[i]); }
  assert(read->unsolicited == written->unsolicited);
}

/* Top Of Book Message: written and read back, then read and written back */
static void check_top_of_book_message(void) {
  TopOfBookMessage sent;
  TopOfBookMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_top_of_book_message(&sent);
  assert(encode_top_of_book_message(&sent, wire, 0) == 43);
  assert(decode_top_of_book_message(&got, wire, 0) == 43);
  equal_top_of_book_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_top_of_book_message(&got, wire, 0) == 43);
  assert(encode_top_of_book_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Imbalance Message: 52 bytes --------------------------------------------- */

/* Appears in the TCP spin response payload. Not available in the Overnight TradingSession. */
typedef struct {
  uint8_t time[4];                               /* bytes 0 to 3 */
  uint8_t symbol[14];                            /* bytes 4 to 17 */
  uint8_t current_inside_paired_shares[4];       /* bytes 18 to 21 */
  uint8_t current_inside_closing_price[8];       /* bytes 22 to 29 */
  uint8_t current_inside_imbalance_quantity[4];  /* bytes 30 to 33 */
  uint8_t current_inside_imbalance_side;         /* byte 34 */
  uint8_t full_closing_price[8];                 /* bytes 35 to 42 */
  uint8_t ocio_only_closing_price[8];            /* bytes 43 to 50 */
  uint8_t moc_shares_unmatched;                  /* byte 51 */
} ImbalanceMessage;

/* any Imbalance Message at all: every byte one the checker chooses */
static void any_imbalance_message(ImbalanceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->current_inside_paired_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->current_inside_closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->current_inside_imbalance_quantity[i] = arbitrary(); }
  record->current_inside_imbalance_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->full_closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ocio_only_closing_price[i] = arbitrary(); }
  record->moc_shares_unmatched = arbitrary();
}

/* Imbalance Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_imbalance_message(const ImbalanceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->current_inside_paired_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->current_inside_closing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->current_inside_imbalance_quantity[i]; }
  wire[at++] = record->current_inside_imbalance_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->full_closing_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ocio_only_closing_price[i]; }
  wire[at++] = record->moc_shares_unmatched;

  return at;
}

/* Imbalance Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_imbalance_message(ImbalanceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->current_inside_paired_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->current_inside_closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->current_inside_imbalance_quantity[i] = wire[at++]; }
  record->current_inside_imbalance_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->full_closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ocio_only_closing_price[i] = wire[at++]; }
  record->moc_shares_unmatched = wire[at++];

  return at;
}

/* what was read of Imbalance Message is what was written, byte for byte */
static void equal_imbalance_message(const ImbalanceMessage *read, const ImbalanceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->current_inside_paired_shares[i] == written->current_inside_paired_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->current_inside_closing_price[i] == written->current_inside_closing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->current_inside_imbalance_quantity[i] == written->current_inside_imbalance_quantity[i]); }
  assert(read->current_inside_imbalance_side == written->current_inside_imbalance_side);
  for (size_t i = 0; i < 8; i++) { assert(read->full_closing_price[i] == written->full_closing_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ocio_only_closing_price[i] == written->ocio_only_closing_price[i]); }
  assert(read->moc_shares_unmatched == written->moc_shares_unmatched);
}

/* Imbalance Message: written and read back, then read and written back */
static void check_imbalance_message(void) {
  ImbalanceMessage sent;
  ImbalanceMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_imbalance_message(&sent);
  assert(encode_imbalance_message(&sent, wire, 0) == 52);
  assert(decode_imbalance_message(&got, wire, 0) == 52);
  equal_imbalance_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_imbalance_message(&got, wire, 0) == 52);
  assert(encode_imbalance_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Recovery Event Message: 17 bytes --------------------------------- */

/* System Recovery event. The first event (type 'S') instructs clients to prepare and reset caches; clients must clean all cached state. A second event (type 'B') indicates recovery begins, after which the system performs a spin for all symbols and open orders. */
typedef struct {
  uint8_t deprecated[4];            /* bytes 0 to 3 */
  uint8_t recovery_type;            /* byte 4 */
  uint8_t next_sequence_number[4];  /* bytes 5 to 8 */
  uint8_t recovery_start_time[8];   /* bytes 9 to 16 */
} SystemRecoveryEventMessage;

/* any System Recovery Event Message at all: every byte one the checker chooses */
static void any_system_recovery_event_message(SystemRecoveryEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->deprecated[i] = arbitrary(); }
  record->recovery_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->next_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->recovery_start_time[i] = arbitrary(); }
}

/* System Recovery Event Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_system_recovery_event_message(const SystemRecoveryEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->deprecated[i]; }
  wire[at++] = record->recovery_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->recovery_start_time[i]; }

  return at;
}

/* System Recovery Event Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_system_recovery_event_message(SystemRecoveryEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->deprecated[i] = wire[at++]; }
  record->recovery_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->next_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->recovery_start_time[i] = wire[at++]; }

  return at;
}

/* what was read of System Recovery Event Message is what was written, byte for byte */
static void equal_system_recovery_event_message(const SystemRecoveryEventMessage *read, const SystemRecoveryEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->deprecated[i] == written->deprecated[i]); }
  assert(read->recovery_type == written->recovery_type);
  for (size_t i = 0; i < 4; i++) { assert(read->next_sequence_number[i] == written->next_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->recovery_start_time[i] == written->recovery_start_time[i]); }
}

/* System Recovery Event Message: written and read back, then read and written back */
static void check_system_recovery_event_message(void) {
  SystemRecoveryEventMessage sent;
  SystemRecoveryEventMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_system_recovery_event_message(&sent);
  assert(encode_system_recovery_event_message(&sent, wire, 0) == 17);
  assert(decode_system_recovery_event_message(&got, wire, 0) == 17);
  equal_system_recovery_event_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_system_recovery_event_message(&got, wire, 0) == 17);
  assert(encode_system_recovery_event_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request Message: 32 bytes ----------------------------------------- */

/* "l" (lowercase L). Logon message is the first message required to send to the server once a connection is established. At minimum, the firm and user id should be provided. */
typedef struct {
  uint8_t user_id[16];   /* bytes 0 to 15 */
  uint8_t password[16];  /* bytes 16 to 31 */
} LoginRequestMessage;

/* any Login Request Message at all: every byte one the checker chooses */
static void any_login_request_message(LoginRequestMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->password[i] = arbitrary(); }
}

/* Login Request Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_login_request_message(const LoginRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->password[i]; }

  return at;
}

/* Login Request Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_login_request_message(LoginRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->password[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request Message is what was written, byte for byte */
static void equal_login_request_message(const LoginRequestMessage *read, const LoginRequestMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->password[i] == written->password[i]); }
}

/* Login Request Message: written and read back, then read and written back */
static void check_login_request_message(void) {
  LoginRequestMessage sent;
  LoginRequestMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_login_request_message(&sent);
  assert(encode_login_request_message(&sent, wire, 0) == 32);
  assert(decode_login_request_message(&got, wire, 0) == 32);
  equal_login_request_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request_message(&got, wire, 0) == 32);
  assert(encode_login_request_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Response Message: 17 bytes ---------------------------------------- */

/* "a". The Login Response Message is sent to a client's response to a TCP/IP Login Message. The status field is used to reflect an accepted login or the reason the session was not accepted. If login fails, the TCP/IP connection will be dropped. */
typedef struct {
  uint8_t user_id[16];   /* bytes 0 to 15 */
  uint8_t login_status;  /* byte 16 */
} LoginResponseMessage;

/* any Login Response Message at all: every byte one the checker chooses */
static void any_login_response_message(LoginResponseMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->user_id[i] = arbitrary(); }
  record->login_status = arbitrary();
}

/* Login Response Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_login_response_message(const LoginResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->user_id[i]; }
  wire[at++] = record->login_status;

  return at;
}

/* Login Response Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_login_response_message(LoginResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->user_id[i] = wire[at++]; }
  record->login_status = wire[at++];

  return at;
}

/* what was read of Login Response Message is what was written, byte for byte */
static void equal_login_response_message(const LoginResponseMessage *read, const LoginResponseMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->user_id[i] == written->user_id[i]); }
  assert(read->login_status == written->login_status);
}

/* Login Response Message: written and read back, then read and written back */
static void check_login_response_message(void) {
  LoginResponseMessage sent;
  LoginResponseMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_login_response_message(&sent);
  assert(encode_login_response_message(&sent, wire, 0) == 17);
  assert(decode_login_response_message(&got, wire, 0) == 17);
  equal_login_response_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_login_response_message(&got, wire, 0) == 17);
  assert(encode_login_response_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Request Message: 9 bytes --------------------------------- */

/* "r". Request retransmission of a range of messages. */
typedef struct {
  uint8_t start_sequence[4];      /* bytes 0 to 3 */
  uint8_t number_of_messages[4];  /* bytes 4 to 7 */
  uint8_t retran_via_tcp;         /* byte 8 */
} RetransmissionRequestMessage;

/* any Retransmission Request Message at all: every byte one the checker chooses */
static void any_retransmission_request_message(RetransmissionRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->start_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_messages[i] = arbitrary(); }
  record->retran_via_tcp = arbitrary();
}

/* Retransmission Request Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_request_message(const RetransmissionRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->start_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_messages[i]; }
  wire[at++] = record->retran_via_tcp;

  return at;
}

/* Retransmission Request Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_request_message(RetransmissionRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->start_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_messages[i] = wire[at++]; }
  record->retran_via_tcp = wire[at++];

  return at;
}

/* what was read of Retransmission Request Message is what was written, byte for byte */
static void equal_retransmission_request_message(const RetransmissionRequestMessage *read, const RetransmissionRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->start_sequence[i] == written->start_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_messages[i] == written->number_of_messages[i]); }
  assert(read->retran_via_tcp == written->retran_via_tcp);
}

/* Retransmission Request Message: written and read back, then read and written back */
static void check_retransmission_request_message(void) {
  RetransmissionRequestMessage sent;
  RetransmissionRequestMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_retransmission_request_message(&sent);
  assert(encode_retransmission_request_message(&sent, wire, 0) == 9);
  assert(decode_retransmission_request_message(&got, wire, 0) == 9);
  equal_retransmission_request_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_request_message(&got, wire, 0) == 9);
  assert(encode_retransmission_request_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Response Message: 9 bytes -------------------------------- */

/* "b". Response to a Retransmission Request. The replay server sends a heartbeat message every second. If the server replay response to a request takes too much time, then it is up to the client to either wait for a few heartbeats, or arbitrary time, then disconnect and send another replay request. */
typedef struct {
  uint8_t start_sequence[4];      /* bytes 0 to 3 */
  uint8_t number_of_messages[4];  /* bytes 4 to 7 */
  uint8_t retransmission_status;  /* byte 8 */
} RetransmissionResponseMessage;

/* any Retransmission Response Message at all: every byte one the checker chooses */
static void any_retransmission_response_message(RetransmissionResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->start_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_messages[i] = arbitrary(); }
  record->retransmission_status = arbitrary();
}

/* Retransmission Response Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_response_message(const RetransmissionResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->start_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_messages[i]; }
  wire[at++] = record->retransmission_status;

  return at;
}

/* Retransmission Response Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_response_message(RetransmissionResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->start_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_messages[i] = wire[at++]; }
  record->retransmission_status = wire[at++];

  return at;
}

/* what was read of Retransmission Response Message is what was written, byte for byte */
static void equal_retransmission_response_message(const RetransmissionResponseMessage *read, const RetransmissionResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->start_sequence[i] == written->start_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_messages[i] == written->number_of_messages[i]); }
  assert(read->retransmission_status == written->retransmission_status);
}

/* Retransmission Response Message: written and read back, then read and written back */
static void check_retransmission_response_message(void) {
  RetransmissionResponseMessage sent;
  RetransmissionResponseMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_retransmission_response_message(&sent);
  assert(encode_retransmission_response_message(&sent, wire, 0) == 9);
  assert(decode_retransmission_response_message(&got, wire, 0) == 9);
  equal_retransmission_response_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_response_message(&got, wire, 0) == 9);
  assert(encode_retransmission_response_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spin Request Message: 4 bytes ------------------------------------------- */

/* "s". Request a refresh spin of state from the server. */
typedef struct {
  uint8_t client_identifier[4];  /* bytes 0 to 3 */
} SpinRequestMessage;

/* any Spin Request Message at all: every byte one the checker chooses */
static void any_spin_request_message(SpinRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->client_identifier[i] = arbitrary(); }
}

/* Spin Request Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_spin_request_message(const SpinRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_identifier[i]; }

  return at;
}

/* Spin Request Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_spin_request_message(SpinRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_identifier[i] = wire[at++]; }

  return at;
}

/* what was read of Spin Request Message is what was written, byte for byte */
static void equal_spin_request_message(const SpinRequestMessage *read, const SpinRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_identifier[i] == written->client_identifier[i]); }
}

/* Spin Request Message: written and read back, then read and written back */
static void check_spin_request_message(void) {
  SpinRequestMessage sent;
  SpinRequestMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_spin_request_message(&sent);
  assert(encode_spin_request_message(&sent, wire, 0) == 4);
  assert(decode_spin_request_message(&got, wire, 0) == 4);
  equal_spin_request_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_spin_request_message(&got, wire, 0) == 4);
  assert(encode_spin_request_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spin Response Message: 5 bytes ------------------------------------------ */

/* "c". The server will send a Spin Response ("c") with status Start of Spin ("S"). It will then transmit Trading Session, Security, Orders or TOB, etc., followed by another Spin Response ("c") with status End of Spin ("E"). Ignore any Heartbeat messages. Spin messages are always returned to the same TCP socket from where they originated. */
typedef struct {
  uint8_t client_identifier[4];  /* bytes 0 to 3 */
  uint8_t spin_status;           /* byte 4 */
} SpinResponseMessage;

/* any Spin Response Message at all: every byte one the checker chooses */
static void any_spin_response_message(SpinResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->client_identifier[i] = arbitrary(); }
  record->spin_status = arbitrary();
}

/* Spin Response Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_spin_response_message(const SpinResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_identifier[i]; }
  wire[at++] = record->spin_status;

  return at;
}

/* Spin Response Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_spin_response_message(SpinResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_identifier[i] = wire[at++]; }
  record->spin_status = wire[at++];

  return at;
}

/* what was read of Spin Response Message is what was written, byte for byte */
static void equal_spin_response_message(const SpinResponseMessage *read, const SpinResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_identifier[i] == written->client_identifier[i]); }
  assert(read->spin_status == written->spin_status);
}

/* Spin Response Message: written and read back, then read and written back */
static void check_spin_response_message(void) {
  SpinResponseMessage sent;
  SpinResponseMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_spin_response_message(&sent);
  assert(encode_spin_response_message(&sent, wire, 0) == 5);
  assert(decode_spin_response_message(&got, wire, 0) == 5);
  equal_spin_response_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_spin_response_message(&got, wire, 0) == 5);
  assert(encode_spin_response_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Enhanced Spin Request Message: 4 bytes ---------------------------------- */

/* "t". Request an enhanced spin which includes a last-sequence-number marker for syncing real time data. */
typedef struct {
  uint8_t client_identifier[4];  /* bytes 0 to 3 */
} EnhancedSpinRequestMessage;

/* any Enhanced Spin Request Message at all: every byte one the checker chooses */
static void any_enhanced_spin_request_message(EnhancedSpinRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->client_identifier[i] = arbitrary(); }
}

/* Enhanced Spin Request Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_enhanced_spin_request_message(const EnhancedSpinRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_identifier[i]; }

  return at;
}

/* Enhanced Spin Request Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_enhanced_spin_request_message(EnhancedSpinRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_identifier[i] = wire[at++]; }

  return at;
}

/* what was read of Enhanced Spin Request Message is what was written, byte for byte */
static void equal_enhanced_spin_request_message(const EnhancedSpinRequestMessage *read, const EnhancedSpinRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_identifier[i] == written->client_identifier[i]); }
}

/* Enhanced Spin Request Message: written and read back, then read and written back */
static void check_enhanced_spin_request_message(void) {
  EnhancedSpinRequestMessage sent;
  EnhancedSpinRequestMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_enhanced_spin_request_message(&sent);
  assert(encode_enhanced_spin_request_message(&sent, wire, 0) == 4);
  assert(decode_enhanced_spin_request_message(&got, wire, 0) == 4);
  equal_enhanced_spin_request_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_enhanced_spin_request_message(&got, wire, 0) == 4);
  assert(encode_enhanced_spin_request_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Enhanced Spin Response Message: 9 bytes --------------------------------- */

/* "d". The server will send an Enhanced Spin Response ("d") with status Start of Spin ("S"). It will then transmit Trading Session, Security, Orders or TOB, etc., followed by another Enhanced Spin Response ("d") with status End of Spin ("E"). Ignore any Heartbeat messages. Spin messages are always returned to the same TCP socket from where they originated. */
typedef struct {
  uint8_t client_identifier[4];  /* bytes 0 to 3 */
  uint8_t enhanced_spin_status;  /* byte 4 */
  uint8_t last_seq_num[4];       /* bytes 5 to 8 */
} EnhancedSpinResponseMessage;

/* any Enhanced Spin Response Message at all: every byte one the checker chooses */
static void any_enhanced_spin_response_message(EnhancedSpinResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->client_identifier[i] = arbitrary(); }
  record->enhanced_spin_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_seq_num[i] = arbitrary(); }
}

/* Enhanced Spin Response Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_enhanced_spin_response_message(const EnhancedSpinResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_identifier[i]; }
  wire[at++] = record->enhanced_spin_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_seq_num[i]; }

  return at;
}

/* Enhanced Spin Response Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_enhanced_spin_response_message(EnhancedSpinResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_identifier[i] = wire[at++]; }
  record->enhanced_spin_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->last_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Enhanced Spin Response Message is what was written, byte for byte */
static void equal_enhanced_spin_response_message(const EnhancedSpinResponseMessage *read, const EnhancedSpinResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_identifier[i] == written->client_identifier[i]); }
  assert(read->enhanced_spin_status == written->enhanced_spin_status);
  for (size_t i = 0; i < 4; i++) { assert(read->last_seq_num[i] == written->last_seq_num[i]); }
}

/* Enhanced Spin Response Message: written and read back, then read and written back */
static void check_enhanced_spin_response_message(void) {
  EnhancedSpinResponseMessage sent;
  EnhancedSpinResponseMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_enhanced_spin_response_message(&sent);
  assert(encode_enhanced_spin_response_message(&sent, wire, 0) == 9);
  assert(decode_enhanced_spin_response_message(&got, wire, 0) == 9);
  equal_enhanced_spin_response_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_enhanced_spin_response_message(&got, wire, 0) == 9);
  assert(encode_enhanced_spin_response_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heartbeat Message: 4 bytes ---------------------------------------------- */

/* "h". After login successful, FI will send a client a heartbeat once every 60 seconds. If there is no heartbeat from client for more than 5 minutes, system will disconnect. */
typedef struct {
  uint8_t client_identifier[4];  /* bytes 0 to 3 */
} HeartbeatMessage;

/* any Heartbeat Message at all: every byte one the checker chooses */
static void any_heartbeat_message(HeartbeatMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->client_identifier[i] = arbitrary(); }
}

/* Heartbeat Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat_message(const HeartbeatMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_identifier[i]; }

  return at;
}

/* Heartbeat Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat_message(HeartbeatMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_identifier[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat Message is what was written, byte for byte */
static void equal_heartbeat_message(const HeartbeatMessage *read, const HeartbeatMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_identifier[i] == written->client_identifier[i]); }
}

/* Heartbeat Message: written and read back, then read and written back */
static void check_heartbeat_message(void) {
  HeartbeatMessage sent;
  HeartbeatMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_heartbeat_message(&sent);
  assert(encode_heartbeat_message(&sent, wire, 0) == 4);
  assert(decode_heartbeat_message(&got, wire, 0) == 4);
  equal_heartbeat_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_heartbeat_message(&got, wire, 0) == 4);
  assert(encode_heartbeat_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_start_of_spin_message();
  check_end_of_spin_message();
  check_trading_session_message();
  check_order_add_message();
  check_order_update_message();
  check_order_delete_message();
  check_order_execution_message();
  check_order_execution_with_price_message();
  check_trade_message();
  check_top_of_book_message();
  check_imbalance_message();
  check_system_recovery_event_message();
  check_login_request_message();
  check_login_response_message();
  check_retransmission_request_message();
  check_retransmission_response_message();
  check_spin_request_message();
  check_spin_response_message();
  check_enhanced_spin_request_message();
  check_enhanced_spin_response_message();
  check_heartbeat_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
