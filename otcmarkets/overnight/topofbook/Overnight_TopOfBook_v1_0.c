// otcmarkets/overnight/topofbook/Overnight_TopOfBook_v1_0.c
/*
 * OTC Markets Group OTC Top of Book
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
 *   - a field read in bits
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

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* Otc Udp Message Header */
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

/* After a Spin Response Message, with status 'S', this message appears on all channels and indicates the beginning of a spin message cycle. */
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

/* This message appears on all channels and indicates the end of a spin message cycle. It will be followed by a Spin Response Message, with status 'E'. */
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

/* This message appears on all channels and is sent out at the start of each Overnight OTC IDQS trading session: Order Acceptance at 7:00 PM, Market Open at 8:00 PM, Market Close at 7:45 AM. The message can also be sent mid-day if a technical outage caused a temporary closure of the market. */
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

/* ---- Top Of Book Message: 43 bytes ------------------------------------------- */

/* This message appears on the TOB channel. Provides best bid and offer aggregated top-of-book. */
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

/* This message appears on all channels. This message is not available in the Overnight TradingSession. */
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

/* In case of a catastrophic issue at the exchange, the system sends a System Recovery Event. The first event (type 'S') instructs clients to prepare and reset caches; clients must clean all cached state. A second event (type 'B') indicates recovery begins, after which the system performs a spin for all symbols and open orders. */
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

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_start_of_spin_message();
  check_end_of_spin_message();
  check_trading_session_message();
  check_top_of_book_message();
  check_imbalance_message();
  check_system_recovery_event_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
