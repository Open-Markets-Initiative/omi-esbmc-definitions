// cboe/byxequities/top/ByxEquities_Top_v1_3_2.c
/*
 * Chicago Board Options Exchange Top
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

/* ---- Logon Message: 17 bytes ------------------------------------------------- */

/* Logon Message */
typedef struct {
  uint8_t username[6];   /* bytes 0 to 5 */
  uint8_t password[10];  /* bytes 6 to 15 */
  uint8_t spin_flag;     /* byte 16 */
} LogonMessage;

/* any Logon Message at all: every byte one the checker chooses */
static void any_logon_message(LogonMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->password[i] = arbitrary(); }
  record->spin_flag = arbitrary();
}

/* Logon Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_logon_message(const LogonMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->password[i]; }
  wire[at++] = record->spin_flag;

  return at;
}

/* Logon Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_logon_message(LogonMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->password[i] = wire[at++]; }
  record->spin_flag = wire[at++];

  return at;
}

/* what was read of Logon Message is what was written, byte for byte */
static void equal_logon_message(const LogonMessage *read, const LogonMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->password[i] == written->password[i]); }
  assert(read->spin_flag == written->spin_flag);
}

/* Logon Message: written and read back, then read and written back */
static void check_logon_message(void) {
  LogonMessage sent;
  LogonMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_logon_message(&sent);
  assert(encode_logon_message(&sent, wire, 0) == 17);
  assert(decode_logon_message(&got, wire, 0) == 17);
  equal_logon_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_message(&got, wire, 0) == 17);
  assert(encode_logon_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Rejected Message: 1 byte ------------------------------------------ */

/* Logon Rejected Message */
typedef struct {
  uint8_t reject_reason;  /* byte 0 */
} LogonRejectedMessage;

/* any Logon Rejected Message at all: every byte one the checker chooses */
static void any_logon_rejected_message(LogonRejectedMessage *record) {
  record->reject_reason = arbitrary();
}

/* Logon Rejected Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_logon_rejected_message(const LogonRejectedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reject_reason;

  return at;
}

/* Logon Rejected Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_logon_rejected_message(LogonRejectedMessage *record, const uint8_t *wire, size_t at) {
  record->reject_reason = wire[at++];

  return at;
}

/* what was read of Logon Rejected Message is what was written, byte for byte */
static void equal_logon_rejected_message(const LogonRejectedMessage *read, const LogonRejectedMessage *written) {
  assert(read->reject_reason == written->reject_reason);
}

/* Logon Rejected Message: written and read back, then read and written back */
static void check_logon_rejected_message(void) {
  LogonRejectedMessage sent;
  LogonRejectedMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_logon_rejected_message(&sent);
  assert(encode_logon_rejected_message(&sent, wire, 0) == 1);
  assert(decode_logon_rejected_message(&got, wire, 0) == 1);
  equal_logon_rejected_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_rejected_message(&got, wire, 0) == 1);
  assert(encode_logon_rejected_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Seconds Message: 5 bytes ------------------------------------------------ */

/* Sent for every second for which at least one message is being generated. */
typedef struct {
  uint8_t seconds[5];  /* bytes 0 to 4 */
} SecondsMessage;

/* any Seconds Message at all: every byte one the checker chooses */
static void any_seconds_message(SecondsMessage *record) {
  for (size_t i = 0; i < 5; i++) { record->seconds[i] = arbitrary(); }
}

/* Seconds Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_seconds_message(const SecondsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->seconds[i]; }

  return at;
}

/* Seconds Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_seconds_message(SecondsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Seconds Message is what was written, byte for byte */
static void equal_seconds_message(const SecondsMessage *read, const SecondsMessage *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->seconds[i] == written->seconds[i]); }
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

/* Sent for every millisecond for which at least one message is being generated. */
typedef struct {
  uint8_t milliseconds[3];  /* bytes 0 to 2 */
} MillisecondsMessage;

/* any Milliseconds Message at all: every byte one the checker chooses */
static void any_milliseconds_message(MillisecondsMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->milliseconds[i] = arbitrary(); }
}

/* Milliseconds Message to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_milliseconds_message(const MillisecondsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->milliseconds[i]; }

  return at;
}

/* Milliseconds Message off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_milliseconds_message(MillisecondsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->milliseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Milliseconds Message is what was written, byte for byte */
static void equal_milliseconds_message(const MillisecondsMessage *read, const MillisecondsMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->milliseconds[i] == written->milliseconds[i]); }
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

/* ---- Expanded Spin Message: 85 bytes ----------------------------------------- */

/* Expanded Spin Message */
typedef struct {
  uint8_t timestamp[8];               /* bytes 0 to 7 */
  uint8_t symbol_expanded[8];         /* bytes 8 to 15 */
  uint8_t bid_price_long[10];         /* bytes 16 to 25 */
  uint8_t bid_quantity_long[6];       /* bytes 26 to 31 */
  uint8_t ask_price_long[10];         /* bytes 32 to 41 */
  uint8_t ask_quantity_long[6];       /* bytes 42 to 47 */
  uint8_t last_trade_time[8];         /* bytes 48 to 55 */
  uint8_t last_trade_price[10];       /* bytes 56 to 65 */
  uint8_t last_trade_size[6];         /* bytes 66 to 71 */
  uint8_t cumulative_volume_long[9];  /* bytes 72 to 80 */
  uint8_t halt_status;                /* byte 81 */
  uint8_t reg_sho_action;             /* byte 82 */
  uint8_t reserved_1;                 /* byte 83 */
  uint8_t reserved_2;                 /* byte 84 */
} ExpandedSpinMessage;

/* any Expanded Spin Message at all: every byte one the checker chooses */
static void any_expanded_spin_message(ExpandedSpinMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol_expanded[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->bid_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->bid_quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->ask_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->ask_quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_trade_time[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->last_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->last_trade_size[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->cumulative_volume_long[i] = arbitrary(); }
  record->halt_status = arbitrary();
  record->reg_sho_action = arbitrary();
  record->reserved_1 = arbitrary();
  record->reserved_2 = arbitrary();
}

/* Expanded Spin Message to the wire: 85 bytes from at, returning where the next byte goes */
static size_t encode_expanded_spin_message(const ExpandedSpinMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_expanded[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->bid_price_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->bid_quantity_long[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->ask_price_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->ask_quantity_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_trade_time[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->last_trade_price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->last_trade_size[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->cumulative_volume_long[i]; }
  wire[at++] = record->halt_status;
  wire[at++] = record->reg_sho_action;
  wire[at++] = record->reserved_1;
  wire[at++] = record->reserved_2;

  return at;
}

/* Expanded Spin Message off the wire: 85 bytes from at, returning where the next byte lies */
static size_t decode_expanded_spin_message(ExpandedSpinMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol_expanded[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->bid_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->bid_quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->ask_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->ask_quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_trade_time[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->last_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->last_trade_size[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->cumulative_volume_long[i] = wire[at++]; }
  record->halt_status = wire[at++];
  record->reg_sho_action = wire[at++];
  record->reserved_1 = wire[at++];
  record->reserved_2 = wire[at++];

  return at;
}

/* what was read of Expanded Spin Message is what was written, byte for byte */
static void equal_expanded_spin_message(const ExpandedSpinMessage *read, const ExpandedSpinMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_expanded[i] == written->symbol_expanded[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->bid_price_long[i] == written->bid_price_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->bid_quantity_long[i] == written->bid_quantity_long[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->ask_price_long[i] == written->ask_price_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->ask_quantity_long[i] == written->ask_quantity_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_trade_time[i] == written->last_trade_time[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->last_trade_price[i] == written->last_trade_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->last_trade_size[i] == written->last_trade_size[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->cumulative_volume_long[i] == written->cumulative_volume_long[i]); }
  assert(read->halt_status == written->halt_status);
  assert(read->reg_sho_action == written->reg_sho_action);
  assert(read->reserved_1 == written->reserved_1);
  assert(read->reserved_2 == written->reserved_2);
}

/* Expanded Spin Message: written and read back, then read and written back */
static void check_expanded_spin_message(void) {
  ExpandedSpinMessage sent;
  ExpandedSpinMessage got;
  uint8_t wire[85];
  uint8_t again[85];

  any_expanded_spin_message(&sent);
  assert(encode_expanded_spin_message(&sent, wire, 0) == 85);
  assert(decode_expanded_spin_message(&got, wire, 0) == 85);
  equal_expanded_spin_message(&got, &sent);

  for (size_t i = 0; i < 85; i++) { wire[i] = arbitrary(); }
  assert(decode_expanded_spin_message(&got, wire, 0) == 85);
  assert(encode_expanded_spin_message(&got, again, 0) == 85);
  for (size_t i = 0; i < 85; i++) { assert(again[i] == wire[i]); }
}

/* ---- Expanded Bid Update Message: 24 bytes ----------------------------------- */

/* Expanded Bid Update Message */
typedef struct {
  uint8_t symbol_expanded[8];    /* bytes 0 to 7 */
  uint8_t bid_price_long[10];    /* bytes 8 to 17 */
  uint8_t bid_quantity_long[6];  /* bytes 18 to 23 */
} ExpandedBidUpdateMessage;

/* any Expanded Bid Update Message at all: every byte one the checker chooses */
static void any_expanded_bid_update_message(ExpandedBidUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->symbol_expanded[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->bid_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->bid_quantity_long[i] = arbitrary(); }
}

/* Expanded Bid Update Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_expanded_bid_update_message(const ExpandedBidUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_expanded[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->bid_price_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->bid_quantity_long[i]; }

  return at;
}

/* Expanded Bid Update Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_expanded_bid_update_message(ExpandedBidUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->symbol_expanded[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->bid_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->bid_quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Expanded Bid Update Message is what was written, byte for byte */
static void equal_expanded_bid_update_message(const ExpandedBidUpdateMessage *read, const ExpandedBidUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_expanded[i] == written->symbol_expanded[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->bid_price_long[i] == written->bid_price_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->bid_quantity_long[i] == written->bid_quantity_long[i]); }
}

/* Expanded Bid Update Message: written and read back, then read and written back */
static void check_expanded_bid_update_message(void) {
  ExpandedBidUpdateMessage sent;
  ExpandedBidUpdateMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_expanded_bid_update_message(&sent);
  assert(encode_expanded_bid_update_message(&sent, wire, 0) == 24);
  assert(decode_expanded_bid_update_message(&got, wire, 0) == 24);
  equal_expanded_bid_update_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_expanded_bid_update_message(&got, wire, 0) == 24);
  assert(encode_expanded_bid_update_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Bid Update Message: 22 bytes --------------------------------------- */

/* Long Bid Update Message */
typedef struct {
  uint8_t symbol_long[6];        /* bytes 0 to 5 */
  uint8_t bid_price_long[10];    /* bytes 6 to 15 */
  uint8_t bid_quantity_long[6];  /* bytes 16 to 21 */
} LongBidUpdateMessage;

/* any Long Bid Update Message at all: every byte one the checker chooses */
static void any_long_bid_update_message(LongBidUpdateMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->bid_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->bid_quantity_long[i] = arbitrary(); }
}

/* Long Bid Update Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_long_bid_update_message(const LongBidUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->bid_price_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->bid_quantity_long[i]; }

  return at;
}

/* Long Bid Update Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_long_bid_update_message(LongBidUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->bid_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->bid_quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Long Bid Update Message is what was written, byte for byte */
static void equal_long_bid_update_message(const LongBidUpdateMessage *read, const LongBidUpdateMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->bid_price_long[i] == written->bid_price_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->bid_quantity_long[i] == written->bid_quantity_long[i]); }
}

/* Long Bid Update Message: written and read back, then read and written back */
static void check_long_bid_update_message(void) {
  LongBidUpdateMessage sent;
  LongBidUpdateMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_long_bid_update_message(&sent);
  assert(encode_long_bid_update_message(&sent, wire, 0) == 22);
  assert(decode_long_bid_update_message(&got, wire, 0) == 22);
  equal_long_bid_update_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_long_bid_update_message(&got, wire, 0) == 22);
  assert(encode_long_bid_update_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Bid Update Message: 14 bytes -------------------------------------- */

/* Short Bid Update Message */
typedef struct {
  uint8_t symbol_short[4];        /* bytes 0 to 3 */
  uint8_t bid_price_short[5];     /* bytes 4 to 8 */
  uint8_t bid_quantity_short[5];  /* bytes 9 to 13 */
} ShortBidUpdateMessage;

/* any Short Bid Update Message at all: every byte one the checker chooses */
static void any_short_bid_update_message(ShortBidUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->bid_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->bid_quantity_short[i] = arbitrary(); }
}

/* Short Bid Update Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_short_bid_update_message(const ShortBidUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->bid_price_short[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->bid_quantity_short[i]; }

  return at;
}

/* Short Bid Update Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_short_bid_update_message(ShortBidUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->bid_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->bid_quantity_short[i] = wire[at++]; }

  return at;
}

/* what was read of Short Bid Update Message is what was written, byte for byte */
static void equal_short_bid_update_message(const ShortBidUpdateMessage *read, const ShortBidUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->bid_price_short[i] == written->bid_price_short[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->bid_quantity_short[i] == written->bid_quantity_short[i]); }
}

/* Short Bid Update Message: written and read back, then read and written back */
static void check_short_bid_update_message(void) {
  ShortBidUpdateMessage sent;
  ShortBidUpdateMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_short_bid_update_message(&sent);
  assert(encode_short_bid_update_message(&sent, wire, 0) == 14);
  assert(decode_short_bid_update_message(&got, wire, 0) == 14);
  equal_short_bid_update_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_short_bid_update_message(&got, wire, 0) == 14);
  assert(encode_short_bid_update_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Expanded Ask Update Message: 24 bytes ----------------------------------- */

/* Expanded Ask Update Message */
typedef struct {
  uint8_t symbol_expanded[8];    /* bytes 0 to 7 */
  uint8_t ask_price_long[10];    /* bytes 8 to 17 */
  uint8_t ask_quantity_long[6];  /* bytes 18 to 23 */
} ExpandedAskUpdateMessage;

/* any Expanded Ask Update Message at all: every byte one the checker chooses */
static void any_expanded_ask_update_message(ExpandedAskUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->symbol_expanded[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->ask_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->ask_quantity_long[i] = arbitrary(); }
}

/* Expanded Ask Update Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_expanded_ask_update_message(const ExpandedAskUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_expanded[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->ask_price_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->ask_quantity_long[i]; }

  return at;
}

/* Expanded Ask Update Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_expanded_ask_update_message(ExpandedAskUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->symbol_expanded[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->ask_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->ask_quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Expanded Ask Update Message is what was written, byte for byte */
static void equal_expanded_ask_update_message(const ExpandedAskUpdateMessage *read, const ExpandedAskUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_expanded[i] == written->symbol_expanded[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->ask_price_long[i] == written->ask_price_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->ask_quantity_long[i] == written->ask_quantity_long[i]); }
}

/* Expanded Ask Update Message: written and read back, then read and written back */
static void check_expanded_ask_update_message(void) {
  ExpandedAskUpdateMessage sent;
  ExpandedAskUpdateMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_expanded_ask_update_message(&sent);
  assert(encode_expanded_ask_update_message(&sent, wire, 0) == 24);
  assert(decode_expanded_ask_update_message(&got, wire, 0) == 24);
  equal_expanded_ask_update_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_expanded_ask_update_message(&got, wire, 0) == 24);
  assert(encode_expanded_ask_update_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Ask Update Message: 22 bytes --------------------------------------- */

/* Long Ask Update Message */
typedef struct {
  uint8_t symbol_long[6];        /* bytes 0 to 5 */
  uint8_t ask_price_long[10];    /* bytes 6 to 15 */
  uint8_t ask_quantity_long[6];  /* bytes 16 to 21 */
} LongAskUpdateMessage;

/* any Long Ask Update Message at all: every byte one the checker chooses */
static void any_long_ask_update_message(LongAskUpdateMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->ask_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->ask_quantity_long[i] = arbitrary(); }
}

/* Long Ask Update Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_long_ask_update_message(const LongAskUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->ask_price_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->ask_quantity_long[i]; }

  return at;
}

/* Long Ask Update Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_long_ask_update_message(LongAskUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->ask_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->ask_quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Long Ask Update Message is what was written, byte for byte */
static void equal_long_ask_update_message(const LongAskUpdateMessage *read, const LongAskUpdateMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->ask_price_long[i] == written->ask_price_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->ask_quantity_long[i] == written->ask_quantity_long[i]); }
}

/* Long Ask Update Message: written and read back, then read and written back */
static void check_long_ask_update_message(void) {
  LongAskUpdateMessage sent;
  LongAskUpdateMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_long_ask_update_message(&sent);
  assert(encode_long_ask_update_message(&sent, wire, 0) == 22);
  assert(decode_long_ask_update_message(&got, wire, 0) == 22);
  equal_long_ask_update_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_long_ask_update_message(&got, wire, 0) == 22);
  assert(encode_long_ask_update_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Ask Update Message: 14 bytes -------------------------------------- */

/* Short Ask Update Message */
typedef struct {
  uint8_t symbol_short[4];        /* bytes 0 to 3 */
  uint8_t ask_price_short[5];     /* bytes 4 to 8 */
  uint8_t ask_quantity_short[5];  /* bytes 9 to 13 */
} ShortAskUpdateMessage;

/* any Short Ask Update Message at all: every byte one the checker chooses */
static void any_short_ask_update_message(ShortAskUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->ask_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->ask_quantity_short[i] = arbitrary(); }
}

/* Short Ask Update Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_short_ask_update_message(const ShortAskUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->ask_price_short[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->ask_quantity_short[i]; }

  return at;
}

/* Short Ask Update Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_short_ask_update_message(ShortAskUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->ask_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->ask_quantity_short[i] = wire[at++]; }

  return at;
}

/* what was read of Short Ask Update Message is what was written, byte for byte */
static void equal_short_ask_update_message(const ShortAskUpdateMessage *read, const ShortAskUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->ask_price_short[i] == written->ask_price_short[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->ask_quantity_short[i] == written->ask_quantity_short[i]); }
}

/* Short Ask Update Message: written and read back, then read and written back */
static void check_short_ask_update_message(void) {
  ShortAskUpdateMessage sent;
  ShortAskUpdateMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_short_ask_update_message(&sent);
  assert(encode_short_ask_update_message(&sent, wire, 0) == 14);
  assert(decode_short_ask_update_message(&got, wire, 0) == 14);
  equal_short_ask_update_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_short_ask_update_message(&got, wire, 0) == 14);
  assert(encode_short_ask_update_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Expanded Two Sided Update Message: 40 bytes ----------------------------- */

/* Expanded Two-Sided Update Message */
typedef struct {
  uint8_t symbol_expanded[8];    /* bytes 0 to 7 */
  uint8_t bid_price_long[10];    /* bytes 8 to 17 */
  uint8_t bid_quantity_long[6];  /* bytes 18 to 23 */
  uint8_t ask_price_long[10];    /* bytes 24 to 33 */
  uint8_t ask_quantity_long[6];  /* bytes 34 to 39 */
} ExpandedTwoSidedUpdateMessage;

/* any Expanded Two Sided Update Message at all: every byte one the checker chooses */
static void any_expanded_two_sided_update_message(ExpandedTwoSidedUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->symbol_expanded[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->bid_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->bid_quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->ask_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->ask_quantity_long[i] = arbitrary(); }
}

/* Expanded Two Sided Update Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_expanded_two_sided_update_message(const ExpandedTwoSidedUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_expanded[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->bid_price_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->bid_quantity_long[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->ask_price_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->ask_quantity_long[i]; }

  return at;
}

/* Expanded Two Sided Update Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_expanded_two_sided_update_message(ExpandedTwoSidedUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->symbol_expanded[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->bid_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->bid_quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->ask_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->ask_quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Expanded Two Sided Update Message is what was written, byte for byte */
static void equal_expanded_two_sided_update_message(const ExpandedTwoSidedUpdateMessage *read, const ExpandedTwoSidedUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_expanded[i] == written->symbol_expanded[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->bid_price_long[i] == written->bid_price_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->bid_quantity_long[i] == written->bid_quantity_long[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->ask_price_long[i] == written->ask_price_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->ask_quantity_long[i] == written->ask_quantity_long[i]); }
}

/* Expanded Two Sided Update Message: written and read back, then read and written back */
static void check_expanded_two_sided_update_message(void) {
  ExpandedTwoSidedUpdateMessage sent;
  ExpandedTwoSidedUpdateMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_expanded_two_sided_update_message(&sent);
  assert(encode_expanded_two_sided_update_message(&sent, wire, 0) == 40);
  assert(decode_expanded_two_sided_update_message(&got, wire, 0) == 40);
  equal_expanded_two_sided_update_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_expanded_two_sided_update_message(&got, wire, 0) == 40);
  assert(encode_expanded_two_sided_update_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Two Sided Update Message: 38 bytes --------------------------------- */

/* Long Two-Sided Update Message */
typedef struct {
  uint8_t symbol_long[6];        /* bytes 0 to 5 */
  uint8_t bid_price_long[10];    /* bytes 6 to 15 */
  uint8_t bid_quantity_long[6];  /* bytes 16 to 21 */
  uint8_t ask_price_long[10];    /* bytes 22 to 31 */
  uint8_t ask_quantity_long[6];  /* bytes 32 to 37 */
} LongTwoSidedUpdateMessage;

/* any Long Two Sided Update Message at all: every byte one the checker chooses */
static void any_long_two_sided_update_message(LongTwoSidedUpdateMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->bid_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->bid_quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->ask_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->ask_quantity_long[i] = arbitrary(); }
}

/* Long Two Sided Update Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_long_two_sided_update_message(const LongTwoSidedUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->bid_price_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->bid_quantity_long[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->ask_price_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->ask_quantity_long[i]; }

  return at;
}

/* Long Two Sided Update Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_long_two_sided_update_message(LongTwoSidedUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->bid_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->bid_quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->ask_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->ask_quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Long Two Sided Update Message is what was written, byte for byte */
static void equal_long_two_sided_update_message(const LongTwoSidedUpdateMessage *read, const LongTwoSidedUpdateMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->bid_price_long[i] == written->bid_price_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->bid_quantity_long[i] == written->bid_quantity_long[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->ask_price_long[i] == written->ask_price_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->ask_quantity_long[i] == written->ask_quantity_long[i]); }
}

/* Long Two Sided Update Message: written and read back, then read and written back */
static void check_long_two_sided_update_message(void) {
  LongTwoSidedUpdateMessage sent;
  LongTwoSidedUpdateMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_long_two_sided_update_message(&sent);
  assert(encode_long_two_sided_update_message(&sent, wire, 0) == 38);
  assert(decode_long_two_sided_update_message(&got, wire, 0) == 38);
  equal_long_two_sided_update_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_long_two_sided_update_message(&got, wire, 0) == 38);
  assert(encode_long_two_sided_update_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Two Sided Update Message: 24 bytes -------------------------------- */

/* Short Two-Sided Update Message */
typedef struct {
  uint8_t symbol_short[4];        /* bytes 0 to 3 */
  uint8_t bid_price_short[5];     /* bytes 4 to 8 */
  uint8_t bid_quantity_short[5];  /* bytes 9 to 13 */
  uint8_t ask_price_short[5];     /* bytes 14 to 18 */
  uint8_t ask_quantity_short[5];  /* bytes 19 to 23 */
} ShortTwoSidedUpdateMessage;

/* any Short Two Sided Update Message at all: every byte one the checker chooses */
static void any_short_two_sided_update_message(ShortTwoSidedUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->bid_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->bid_quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->ask_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->ask_quantity_short[i] = arbitrary(); }
}

/* Short Two Sided Update Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_short_two_sided_update_message(const ShortTwoSidedUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->bid_price_short[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->bid_quantity_short[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->ask_price_short[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->ask_quantity_short[i]; }

  return at;
}

/* Short Two Sided Update Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_short_two_sided_update_message(ShortTwoSidedUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->bid_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->bid_quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->ask_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->ask_quantity_short[i] = wire[at++]; }

  return at;
}

/* what was read of Short Two Sided Update Message is what was written, byte for byte */
static void equal_short_two_sided_update_message(const ShortTwoSidedUpdateMessage *read, const ShortTwoSidedUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->bid_price_short[i] == written->bid_price_short[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->bid_quantity_short[i] == written->bid_quantity_short[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->ask_price_short[i] == written->ask_price_short[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->ask_quantity_short[i] == written->ask_quantity_short[i]); }
}

/* Short Two Sided Update Message: written and read back, then read and written back */
static void check_short_two_sided_update_message(void) {
  ShortTwoSidedUpdateMessage sent;
  ShortTwoSidedUpdateMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_short_two_sided_update_message(&sent);
  assert(encode_short_two_sided_update_message(&sent, wire, 0) == 24);
  assert(decode_short_two_sided_update_message(&got, wire, 0) == 24);
  equal_short_two_sided_update_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_short_two_sided_update_message(&got, wire, 0) == 24);
  assert(encode_short_two_sided_update_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Expanded Trade Message: 33 bytes ---------------------------------------- */

/* Expanded Trade Message */
typedef struct {
  uint8_t symbol_expanded[8];         /* bytes 0 to 7 */
  uint8_t last_price_long[10];        /* bytes 8 to 17 */
  uint8_t last_quantity_long[6];      /* bytes 18 to 23 */
  uint8_t cumulative_volume_long[9];  /* bytes 24 to 32 */
} ExpandedTradeMessage;

/* any Expanded Trade Message at all: every byte one the checker chooses */
static void any_expanded_trade_message(ExpandedTradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->symbol_expanded[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->last_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->last_quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->cumulative_volume_long[i] = arbitrary(); }
}

/* Expanded Trade Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_expanded_trade_message(const ExpandedTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_expanded[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->last_price_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->last_quantity_long[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->cumulative_volume_long[i]; }

  return at;
}

/* Expanded Trade Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_expanded_trade_message(ExpandedTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->symbol_expanded[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->last_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->last_quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->cumulative_volume_long[i] = wire[at++]; }

  return at;
}

/* what was read of Expanded Trade Message is what was written, byte for byte */
static void equal_expanded_trade_message(const ExpandedTradeMessage *read, const ExpandedTradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_expanded[i] == written->symbol_expanded[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->last_price_long[i] == written->last_price_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->last_quantity_long[i] == written->last_quantity_long[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->cumulative_volume_long[i] == written->cumulative_volume_long[i]); }
}

/* Expanded Trade Message: written and read back, then read and written back */
static void check_expanded_trade_message(void) {
  ExpandedTradeMessage sent;
  ExpandedTradeMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_expanded_trade_message(&sent);
  assert(encode_expanded_trade_message(&sent, wire, 0) == 33);
  assert(decode_expanded_trade_message(&got, wire, 0) == 33);
  equal_expanded_trade_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_expanded_trade_message(&got, wire, 0) == 33);
  assert(encode_expanded_trade_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Trade Message: 31 bytes -------------------------------------------- */

/* Long Trade Message */
typedef struct {
  uint8_t symbol_long[6];             /* bytes 0 to 5 */
  uint8_t last_price_long[10];        /* bytes 6 to 15 */
  uint8_t last_quantity_long[6];      /* bytes 16 to 21 */
  uint8_t cumulative_volume_long[9];  /* bytes 22 to 30 */
} LongTradeMessage;

/* any Long Trade Message at all: every byte one the checker chooses */
static void any_long_trade_message(LongTradeMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->last_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->last_quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->cumulative_volume_long[i] = arbitrary(); }
}

/* Long Trade Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_long_trade_message(const LongTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->last_price_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->last_quantity_long[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->cumulative_volume_long[i]; }

  return at;
}

/* Long Trade Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_long_trade_message(LongTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->last_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->last_quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->cumulative_volume_long[i] = wire[at++]; }

  return at;
}

/* what was read of Long Trade Message is what was written, byte for byte */
static void equal_long_trade_message(const LongTradeMessage *read, const LongTradeMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->last_price_long[i] == written->last_price_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->last_quantity_long[i] == written->last_quantity_long[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->cumulative_volume_long[i] == written->cumulative_volume_long[i]); }
}

/* Long Trade Message: written and read back, then read and written back */
static void check_long_trade_message(void) {
  LongTradeMessage sent;
  LongTradeMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_long_trade_message(&sent);
  assert(encode_long_trade_message(&sent, wire, 0) == 31);
  assert(decode_long_trade_message(&got, wire, 0) == 31);
  equal_long_trade_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_long_trade_message(&got, wire, 0) == 31);
  assert(encode_long_trade_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Trade Message: 21 bytes ------------------------------------------- */

/* Short Trade Message */
typedef struct {
  uint8_t symbol_short[4];             /* bytes 0 to 3 */
  uint8_t last_price_short[5];         /* bytes 4 to 8 */
  uint8_t last_quantity_short[5];      /* bytes 9 to 13 */
  uint8_t cumulative_volume_short[7];  /* bytes 14 to 20 */
} ShortTradeMessage;

/* any Short Trade Message at all: every byte one the checker chooses */
static void any_short_trade_message(ShortTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->last_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->last_quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->cumulative_volume_short[i] = arbitrary(); }
}

/* Short Trade Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_short_trade_message(const ShortTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->last_price_short[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->last_quantity_short[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->cumulative_volume_short[i]; }

  return at;
}

/* Short Trade Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_short_trade_message(ShortTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->last_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->last_quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->cumulative_volume_short[i] = wire[at++]; }

  return at;
}

/* what was read of Short Trade Message is what was written, byte for byte */
static void equal_short_trade_message(const ShortTradeMessage *read, const ShortTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->last_price_short[i] == written->last_price_short[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->last_quantity_short[i] == written->last_quantity_short[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->cumulative_volume_short[i] == written->cumulative_volume_short[i]); }
}

/* Short Trade Message: written and read back, then read and written back */
static void check_short_trade_message(void) {
  ShortTradeMessage sent;
  ShortTradeMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_short_trade_message(&sent);
  assert(encode_short_trade_message(&sent, wire, 0) == 21);
  assert(decode_short_trade_message(&got, wire, 0) == 21);
  equal_short_trade_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_short_trade_message(&got, wire, 0) == 21);
  assert(encode_short_trade_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 12 bytes ---------------------------------------- */

/* The Trading Status Message is used to indicate the current trading status of a security. */
typedef struct {
  uint8_t symbol_expanded[8];  /* bytes 0 to 7 */
  uint8_t halt_status;         /* byte 8 */
  uint8_t reg_sho_action;      /* byte 9 */
  uint8_t reserved_1;          /* byte 10 */
  uint8_t reserved_2;          /* byte 11 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->symbol_expanded[i] = arbitrary(); }
  record->halt_status = arbitrary();
  record->reg_sho_action = arbitrary();
  record->reserved_1 = arbitrary();
  record->reserved_2 = arbitrary();
}

/* Trading Status Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_expanded[i]; }
  wire[at++] = record->halt_status;
  wire[at++] = record->reg_sho_action;
  wire[at++] = record->reserved_1;
  wire[at++] = record->reserved_2;

  return at;
}

/* Trading Status Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->symbol_expanded[i] = wire[at++]; }
  record->halt_status = wire[at++];
  record->reg_sho_action = wire[at++];
  record->reserved_1 = wire[at++];
  record->reserved_2 = wire[at++];

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_expanded[i] == written->symbol_expanded[i]); }
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

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_logon_message();
  check_logon_rejected_message();
  check_seconds_message();
  check_milliseconds_message();
  check_expanded_spin_message();
  check_expanded_bid_update_message();
  check_long_bid_update_message();
  check_short_bid_update_message();
  check_expanded_ask_update_message();
  check_long_ask_update_message();
  check_short_ask_update_message();
  check_expanded_two_sided_update_message();
  check_long_two_sided_update_message();
  check_short_two_sided_update_message();
  check_expanded_trade_message();
  check_long_trade_message();
  check_short_trade_message();
  check_trading_status_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
