// gpw/wse/snapshotbbo/Wse_SnapshotBbo_v1_7_6_20.c
/*
 * Giełda Papierów Wartościowych w Warszawie Warsaw Stock Exchange BBO Snapshot
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
 *   - a run of a stated number of entries
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

/* ---- Message Header: 42 bytes ------------------------------------------------ */

/* Every market data message opens with the same 42 byte header */
typedef struct {
  uint8_t message_length[2];     /* bytes 0 to 1 */
  uint8_t message_type[2];       /* bytes 2 to 3 */
  uint8_t message_version[2];    /* bytes 4 to 5 */
  uint8_t sequence_number[4];    /* bytes 6 to 9 */
  uint8_t timestamp[8];          /* bytes 10 to 17 */
  uint8_t source_timestamp[8];   /* bytes 18 to 25 */
  uint8_t is_encrypted;          /* byte 26 */
  uint8_t encryption_offset[8];  /* bytes 27 to 34 */
  uint8_t encryption_key_id[4];  /* bytes 35 to 38 */
  uint8_t session_id[2];         /* bytes 39 to 40 */
  uint8_t stream_id;             /* byte 41 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_version[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->source_timestamp[i] = arbitrary(); }
  record->is_encrypted = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->encryption_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->encryption_key_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  record->stream_id = arbitrary();
}

/* Message Header to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_version[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->source_timestamp[i]; }
  wire[at++] = record->is_encrypted;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->encryption_offset[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->encryption_key_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  wire[at++] = record->stream_id;

  return at;
}

/* Message Header off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_version[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->source_timestamp[i] = wire[at++]; }
  record->is_encrypted = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->encryption_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->encryption_key_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  record->stream_id = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_type[i] == written->message_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_version[i] == written->message_version[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->source_timestamp[i] == written->source_timestamp[i]); }
  assert(read->is_encrypted == written->is_encrypted);
  for (size_t i = 0; i < 8; i++) { assert(read->encryption_offset[i] == written->encryption_offset[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->encryption_key_id[i] == written->encryption_key_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  assert(read->stream_id == written->stream_id);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[42];
  uint8_t again[42];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 42);
  assert(decode_message_header(&got, wire, 0) == 42);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 42);
  assert(encode_message_header(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Calendar Exception: 9 bytes --------------------------------------------- */

/* Upcoming calendar day exception */
typedef struct {
  uint8_t calendar_id[4];              /* bytes 0 to 3 */
  uint8_t calendar_exception_date[4];  /* bytes 4 to 7 */
  uint8_t calendar_exception_type;     /* byte 8 */
} CalendarException;

/* any Calendar Exception at all: every byte one the checker chooses */
static void any_calendar_exception(CalendarException *record) {
  for (size_t i = 0; i < 4; i++) { record->calendar_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->calendar_exception_date[i] = arbitrary(); }
  record->calendar_exception_type = arbitrary();
}

/* Calendar Exception to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_calendar_exception(const CalendarException *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->calendar_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->calendar_exception_date[i]; }
  wire[at++] = record->calendar_exception_type;

  return at;
}

/* Calendar Exception off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_calendar_exception(CalendarException *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->calendar_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->calendar_exception_date[i] = wire[at++]; }
  record->calendar_exception_type = wire[at++];

  return at;
}

/* what was read of Calendar Exception is what was written, byte for byte */
static void equal_calendar_exception(const CalendarException *read, const CalendarException *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->calendar_id[i] == written->calendar_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->calendar_exception_date[i] == written->calendar_exception_date[i]); }
  assert(read->calendar_exception_type == written->calendar_exception_type);
}

/* Calendar Exception: written and read back, then read and written back */
static void check_calendar_exception(void) {
  CalendarException sent;
  CalendarException got;
  uint8_t wire[9];
  uint8_t again[9];

  any_calendar_exception(&sent);
  assert(encode_calendar_exception(&sent, wire, 0) == 9);
  assert(decode_calendar_exception(&got, wire, 0) == 9);
  equal_calendar_exception(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_calendar_exception(&got, wire, 0) == 9);
  assert(encode_calendar_exception(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Table Entry: 20 bytes ---------------------------------------------- */

/* Tick size definition */
typedef struct {
  uint8_t tick_size[8];      /* bytes 0 to 7 */
  uint8_t lower_bound[8];    /* bytes 8 to 15 */
  uint8_t tick_table_id[4];  /* bytes 16 to 19 */
} TickTableEntry;

/* any Tick Table Entry at all: every byte one the checker chooses */
static void any_tick_table_entry(TickTableEntry *record) {
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lower_bound[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tick_table_id[i] = arbitrary(); }
}

/* Tick Table Entry to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_tick_table_entry(const TickTableEntry *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_bound[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tick_table_id[i]; }

  return at;
}

/* Tick Table Entry off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_tick_table_entry(TickTableEntry *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lower_bound[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tick_table_id[i] = wire[at++]; }

  return at;
}

/* what was read of Tick Table Entry is what was written, byte for byte */
static void equal_tick_table_entry(const TickTableEntry *read, const TickTableEntry *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->tick_size[i] == written->tick_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lower_bound[i] == written->lower_bound[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tick_table_id[i] == written->tick_table_id[i]); }
}

/* Tick Table Entry: written and read back, then read and written back */
static void check_tick_table_entry(void) {
  TickTableEntry sent;
  TickTableEntry got;
  uint8_t wire[20];
  uint8_t again[20];

  any_tick_table_entry(&sent);
  assert(encode_tick_table_entry(&sent, wire, 0) == 20);
  assert(decode_tick_table_entry(&got, wire, 0) == 20);
  equal_tick_table_entry(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_table_entry(&got, wire, 0) == 20);
  assert(encode_tick_table_entry(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Collar Table Entry: 54 bytes -------------------------------------------- */

/* Collar table definition */
typedef struct {
  uint8_t collar_table_id[4];     /* bytes 0 to 3 */
  uint8_t collar_mode;            /* byte 4 */
  uint8_t collar_expression;      /* byte 5 */
  uint8_t collar_lower_bound[8];  /* bytes 6 to 13 */
  uint8_t collar_value[8];        /* bytes 14 to 21 */
  uint8_t collar_lower_bid[8];    /* bytes 22 to 29 */
  uint8_t collar_upper_bid[8];    /* bytes 30 to 37 */
  uint8_t collar_upper_ask[8];    /* bytes 38 to 45 */
  uint8_t collar_lower_ask[8];    /* bytes 46 to 53 */
} CollarTableEntry;

/* any Collar Table Entry at all: every byte one the checker chooses */
static void any_collar_table_entry(CollarTableEntry *record) {
  for (size_t i = 0; i < 4; i++) { record->collar_table_id[i] = arbitrary(); }
  record->collar_mode = arbitrary();
  record->collar_expression = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->collar_lower_bound[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->collar_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->collar_lower_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->collar_upper_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->collar_upper_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->collar_lower_ask[i] = arbitrary(); }
}

/* Collar Table Entry to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_collar_table_entry(const CollarTableEntry *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->collar_table_id[i]; }
  wire[at++] = record->collar_mode;
  wire[at++] = record->collar_expression;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->collar_lower_bound[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->collar_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->collar_lower_bid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->collar_upper_bid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->collar_upper_ask[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->collar_lower_ask[i]; }

  return at;
}

/* Collar Table Entry off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_collar_table_entry(CollarTableEntry *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->collar_table_id[i] = wire[at++]; }
  record->collar_mode = wire[at++];
  record->collar_expression = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->collar_lower_bound[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->collar_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->collar_lower_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->collar_upper_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->collar_upper_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->collar_lower_ask[i] = wire[at++]; }

  return at;
}

/* what was read of Collar Table Entry is what was written, byte for byte */
static void equal_collar_table_entry(const CollarTableEntry *read, const CollarTableEntry *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->collar_table_id[i] == written->collar_table_id[i]); }
  assert(read->collar_mode == written->collar_mode);
  assert(read->collar_expression == written->collar_expression);
  for (size_t i = 0; i < 8; i++) { assert(read->collar_lower_bound[i] == written->collar_lower_bound[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->collar_value[i] == written->collar_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->collar_lower_bid[i] == written->collar_lower_bid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->collar_upper_bid[i] == written->collar_upper_bid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->collar_upper_ask[i] == written->collar_upper_ask[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->collar_lower_ask[i] == written->collar_lower_ask[i]); }
}

/* Collar Table Entry: written and read back, then read and written back */
static void check_collar_table_entry(void) {
  CollarTableEntry sent;
  CollarTableEntry got;
  uint8_t wire[54];
  uint8_t again[54];

  any_collar_table_entry(&sent);
  assert(encode_collar_table_entry(&sent, wire, 0) == 54);
  assert(decode_collar_table_entry(&got, wire, 0) == 54);
  equal_collar_table_entry(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_collar_table_entry(&got, wire, 0) == 54);
  assert(encode_collar_table_entry(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Phase Schedule Entry: 40 bytes ---------------------------------- */

/* Trading phase definition */
typedef struct {
  uint8_t trading_schedule_id[4];                       /* bytes 0 to 3 */
  uint8_t trading_phase_id[4];                          /* bytes 4 to 7 */
  uint8_t trading_phase_settlement_cycle;               /* byte 8 */
  uint8_t trading_phase_max_block_settlement_cycle;     /* byte 9 */
  uint8_t static_collar_volatility_auction_id[4];       /* bytes 10 to 13 */
  uint8_t dynamic_collar_volatility_auction_id[4];      /* bytes 14 to 17 */
  uint8_t trading_phase_start_time[8];                  /* bytes 18 to 25 */
  uint8_t trading_phase_type;                           /* byte 26 */
  uint8_t uncrossing;                                   /* byte 27 */
  uint8_t ext_static_collar_volatility_auction_id[4];   /* bytes 28 to 31 */
  uint8_t ext_dynamic_collar_volatility_auction_id[4];  /* bytes 32 to 35 */
  uint8_t clat_id[4];                                   /* bytes 36 to 39 */
} TradingPhaseScheduleEntry;

/* any Trading Phase Schedule Entry at all: every byte one the checker chooses */
static void any_trading_phase_schedule_entry(TradingPhaseScheduleEntry *record) {
  for (size_t i = 0; i < 4; i++) { record->trading_schedule_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_phase_id[i] = arbitrary(); }
  record->trading_phase_settlement_cycle = arbitrary();
  record->trading_phase_max_block_settlement_cycle = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->static_collar_volatility_auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->dynamic_collar_volatility_auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_phase_start_time[i] = arbitrary(); }
  record->trading_phase_type = arbitrary();
  record->uncrossing = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->ext_static_collar_volatility_auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ext_dynamic_collar_volatility_auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clat_id[i] = arbitrary(); }
}

/* Trading Phase Schedule Entry to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_trading_phase_schedule_entry(const TradingPhaseScheduleEntry *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_schedule_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_phase_id[i]; }
  wire[at++] = record->trading_phase_settlement_cycle;
  wire[at++] = record->trading_phase_max_block_settlement_cycle;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->static_collar_volatility_auction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->dynamic_collar_volatility_auction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_phase_start_time[i]; }
  wire[at++] = record->trading_phase_type;
  wire[at++] = record->uncrossing;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ext_static_collar_volatility_auction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ext_dynamic_collar_volatility_auction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clat_id[i]; }

  return at;
}

/* Trading Phase Schedule Entry off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_trading_phase_schedule_entry(TradingPhaseScheduleEntry *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->trading_schedule_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_phase_id[i] = wire[at++]; }
  record->trading_phase_settlement_cycle = wire[at++];
  record->trading_phase_max_block_settlement_cycle = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->static_collar_volatility_auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->dynamic_collar_volatility_auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_phase_start_time[i] = wire[at++]; }
  record->trading_phase_type = wire[at++];
  record->uncrossing = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->ext_static_collar_volatility_auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ext_dynamic_collar_volatility_auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clat_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Phase Schedule Entry is what was written, byte for byte */
static void equal_trading_phase_schedule_entry(const TradingPhaseScheduleEntry *read, const TradingPhaseScheduleEntry *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->trading_schedule_id[i] == written->trading_schedule_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_phase_id[i] == written->trading_phase_id[i]); }
  assert(read->trading_phase_settlement_cycle == written->trading_phase_settlement_cycle);
  assert(read->trading_phase_max_block_settlement_cycle == written->trading_phase_max_block_settlement_cycle);
  for (size_t i = 0; i < 4; i++) { assert(read->static_collar_volatility_auction_id[i] == written->static_collar_volatility_auction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->dynamic_collar_volatility_auction_id[i] == written->dynamic_collar_volatility_auction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_phase_start_time[i] == written->trading_phase_start_time[i]); }
  assert(read->trading_phase_type == written->trading_phase_type);
  assert(read->uncrossing == written->uncrossing);
  for (size_t i = 0; i < 4; i++) { assert(read->ext_static_collar_volatility_auction_id[i] == written->ext_static_collar_volatility_auction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ext_dynamic_collar_volatility_auction_id[i] == written->ext_dynamic_collar_volatility_auction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clat_id[i] == written->clat_id[i]); }
}

/* Trading Phase Schedule Entry: written and read back, then read and written back */
static void check_trading_phase_schedule_entry(void) {
  TradingPhaseScheduleEntry sent;
  TradingPhaseScheduleEntry got;
  uint8_t wire[40];
  uint8_t again[40];

  any_trading_phase_schedule_entry(&sent);
  assert(encode_trading_phase_schedule_entry(&sent, wire, 0) == 40);
  assert(decode_trading_phase_schedule_entry(&got, wire, 0) == 40);
  equal_trading_phase_schedule_entry(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_phase_schedule_entry(&got, wire, 0) == 40);
  assert(encode_trading_phase_schedule_entry(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Structure: 63 bytes ---------------------------------------------- */

/* Messages defining the Trading Venue’s market structure */
typedef struct {
  uint8_t id[4];              /* bytes 0 to 3 */
  uint8_t parent_id[4];       /* bytes 4 to 7 */
  uint8_t mic[4];             /* bytes 8 to 11 */
  uint8_t name[50];           /* bytes 12 to 61 */
  uint8_t market_model_type;  /* byte 62 */
} MarketStructure;

/* any Market Structure at all: every byte one the checker chooses */
static void any_market_structure(MarketStructure *record) {
  for (size_t i = 0; i < 4; i++) { record->id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->parent_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->name[i] = arbitrary(); }
  record->market_model_type = arbitrary();
}

/* Market Structure to the wire: 63 bytes from at, returning where the next byte goes */
static size_t encode_market_structure(const MarketStructure *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->parent_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mic[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->name[i]; }
  wire[at++] = record->market_model_type;

  return at;
}

/* Market Structure off the wire: 63 bytes from at, returning where the next byte lies */
static size_t decode_market_structure(MarketStructure *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->parent_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->name[i] = wire[at++]; }
  record->market_model_type = wire[at++];

  return at;
}

/* what was read of Market Structure is what was written, byte for byte */
static void equal_market_structure(const MarketStructure *read, const MarketStructure *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->id[i] == written->id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->parent_id[i] == written->parent_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mic[i] == written->mic[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->name[i] == written->name[i]); }
  assert(read->market_model_type == written->market_model_type);
}

/* Market Structure: written and read back, then read and written back */
static void check_market_structure(void) {
  MarketStructure sent;
  MarketStructure got;
  uint8_t wire[63];
  uint8_t again[63];

  any_market_structure(&sent);
  assert(encode_market_structure(&sent, wire, 0) == 63);
  assert(decode_market_structure(&got, wire, 0) == 63);
  equal_market_structure(&got, &sent);

  for (size_t i = 0; i < 63; i++) { wire[i] = arbitrary(); }
  assert(decode_market_structure(&got, wire, 0) == 63);
  assert(encode_market_structure(&got, again, 0) == 63);
  for (size_t i = 0; i < 63; i++) { assert(again[i] == wire[i]); }
}

/* ---- Collar Group: 20 bytes -------------------------------------------------- */

/* Message defining a collar group */
typedef struct {
  uint8_t id[4];                             /* bytes 0 to 3 */
  uint8_t order_static_collar_table_id[4];   /* bytes 4 to 7 */
  uint8_t order_dynamic_collar_table_id[4];  /* bytes 8 to 11 */
  uint8_t trade_static_collar_table_id[4];   /* bytes 12 to 15 */
  uint8_t trade_dynamic_collar_table_id[4];  /* bytes 16 to 19 */
} CollarGroup;

/* any Collar Group at all: every byte one the checker chooses */
static void any_collar_group(CollarGroup *record) {
  for (size_t i = 0; i < 4; i++) { record->id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_static_collar_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_dynamic_collar_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_static_collar_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_dynamic_collar_table_id[i] = arbitrary(); }
}

/* Collar Group to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_collar_group(const CollarGroup *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_static_collar_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_dynamic_collar_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_static_collar_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_dynamic_collar_table_id[i]; }

  return at;
}

/* Collar Group off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_collar_group(CollarGroup *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_static_collar_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_dynamic_collar_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_static_collar_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_dynamic_collar_table_id[i] = wire[at++]; }

  return at;
}

/* what was read of Collar Group is what was written, byte for byte */
static void equal_collar_group(const CollarGroup *read, const CollarGroup *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->id[i] == written->id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_static_collar_table_id[i] == written->order_static_collar_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_dynamic_collar_table_id[i] == written->order_dynamic_collar_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_static_collar_table_id[i] == written->trade_static_collar_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_dynamic_collar_table_id[i] == written->trade_dynamic_collar_table_id[i]); }
}

/* Collar Group: written and read back, then read and written back */
static void check_collar_group(void) {
  CollarGroup sent;
  CollarGroup got;
  uint8_t wire[20];
  uint8_t again[20];

  any_collar_group(&sent);
  assert(encode_collar_group(&sent, wire, 0) == 20);
  assert(decode_collar_group(&got, wire, 0) == 20);
  equal_collar_group(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_collar_group(&got, wire, 0) == 20);
  assert(encode_collar_group(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- External Underlying: 113 bytes ------------------------------------------ */

/* The message contains a list of underlyings not traded in WATS. It concerns underlyings for derivatives and structured products */
typedef struct {
  uint8_t external_underlying_id[4];                          /* bytes 0 to 3 */
  uint8_t product_identification_product_identification[30];  /* bytes 4 to 33 */
  uint8_t product_identification_type;                        /* byte 34 */
  uint8_t product_code[20];                                   /* bytes 35 to 54 */
  uint8_t product_name[50];                                   /* bytes 55 to 104 */
  uint8_t mic[4];                                             /* bytes 105 to 108 */
  uint8_t nominal_currency[2];                                /* bytes 109 to 110 */
  uint8_t trading_currency[2];                                /* bytes 111 to 112 */
} ExternalUnderlying;

/* any External Underlying at all: every byte one the checker chooses */
static void any_external_underlying(ExternalUnderlying *record) {
  for (size_t i = 0; i < 4; i++) { record->external_underlying_id[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->product_identification_product_identification[i] = arbitrary(); }
  record->product_identification_type = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->product_code[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->product_name[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->nominal_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_currency[i] = arbitrary(); }
}

/* External Underlying to the wire: 113 bytes from at, returning where the next byte goes */
static size_t encode_external_underlying(const ExternalUnderlying *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->external_underlying_id[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->product_identification_product_identification[i]; }
  wire[at++] = record->product_identification_type;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->product_code[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->product_name[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mic[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->nominal_currency[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_currency[i]; }

  return at;
}

/* External Underlying off the wire: 113 bytes from at, returning where the next byte lies */
static size_t decode_external_underlying(ExternalUnderlying *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->external_underlying_id[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->product_identification_product_identification[i] = wire[at++]; }
  record->product_identification_type = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->product_code[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->product_name[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->nominal_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_currency[i] = wire[at++]; }

  return at;
}

/* what was read of External Underlying is what was written, byte for byte */
static void equal_external_underlying(const ExternalUnderlying *read, const ExternalUnderlying *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->external_underlying_id[i] == written->external_underlying_id[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->product_identification_product_identification[i] == written->product_identification_product_identification[i]); }
  assert(read->product_identification_type == written->product_identification_type);
  for (size_t i = 0; i < 20; i++) { assert(read->product_code[i] == written->product_code[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->product_name[i] == written->product_name[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mic[i] == written->mic[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->nominal_currency[i] == written->nominal_currency[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_currency[i] == written->trading_currency[i]); }
}

/* External Underlying: written and read back, then read and written back */
static void check_external_underlying(void) {
  ExternalUnderlying sent;
  ExternalUnderlying got;
  uint8_t wire[113];
  uint8_t again[113];

  any_external_underlying(&sent);
  assert(encode_external_underlying(&sent, wire, 0) == 113);
  assert(decode_external_underlying(&got, wire, 0) == 113);
  equal_external_underlying(&got, &sent);

  for (size_t i = 0; i < 113; i++) { wire[i] = arbitrary(); }
  assert(decode_external_underlying(&got, wire, 0) == 113);
  assert(encode_external_underlying(&got, again, 0) == 113);
  for (size_t i = 0; i < 113; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument: 699 bytes --------------------------------------------------- */

/* Definition of a financial instrument */
typedef struct {
  uint8_t instrument_id[4];                                   /* bytes 0 to 3 */
  uint8_t product_type;                                       /* byte 4 */
  uint8_t product_subtype;                                    /* byte 5 */
  uint8_t first_trading_date[4];                              /* bytes 6 to 9 */
  uint8_t last_trading_date[4];                               /* bytes 10 to 13 */
  uint8_t product_id[4];                                      /* bytes 14 to 17 */
  uint8_t currency[2];                                        /* bytes 18 to 19 */
  uint8_t iceberg_min_value[8];                               /* bytes 20 to 27 */
  uint8_t lot_size[4];                                        /* bytes 28 to 31 */
  uint8_t price_expression_type;                              /* byte 32 */
  uint8_t calendar_id[4];                                     /* bytes 33 to 36 */
  uint8_t market_structure_id[4];                             /* bytes 37 to 40 */
  uint8_t tick_table_id[4];                                   /* bytes 41 to 44 */
  uint8_t reference_instrument_id[4];                         /* bytes 45 to 48 */
  uint8_t collar_group_id[4];                                 /* bytes 49 to 52 */
  uint8_t trading_schedule_id[4];                             /* bytes 53 to 56 */
  uint8_t description[64];                                    /* bytes 57 to 120 */
  uint8_t mic[4];                                             /* bytes 121 to 124 */
  uint8_t nominal_value_price[8];                             /* bytes 125 to 132 */
  uint8_t nominal_value_type;                                 /* byte 133 */
  uint8_t multiplier_multiplier[8];                           /* bytes 134 to 141 */
  uint8_t strike_price[8];                                    /* bytes 142 to 149 */
  uint8_t strike_price_currency[2];                           /* bytes 150 to 151 */
  uint8_t product_identification_product_identification[30];  /* bytes 152 to 181 */
  uint8_t product_identification_type;                        /* byte 182 */
  uint8_t settlement_calendar_id[4];                          /* bytes 183 to 186 */
  uint8_t bond_coupon_type;                                   /* byte 187 */
  uint8_t pre_trade_check_min_price[8];                       /* bytes 188 to 195 */
  uint8_t pre_trade_check_max_price[8];                       /* bytes 196 to 203 */
  uint8_t pre_trade_check_min_quantity[8];                    /* bytes 204 to 211 */
  uint8_t pre_trade_check_max_quantity[8];                    /* bytes 212 to 219 */
  uint8_t pre_trade_check_max_value[8];                       /* bytes 220 to 227 */
  uint8_t pre_trade_check_min_value[8];                       /* bytes 228 to 235 */
  uint8_t liquidity;                                          /* byte 236 */
  uint8_t market_model_type;                                  /* byte 237 */
  uint8_t issuer[150];                                        /* bytes 238 to 387 */
  uint8_t issuer_reg_country[2];                              /* bytes 388 to 389 */
  uint8_t underlying_instrument_id[4];                        /* bytes 390 to 393 */
  uint8_t product_code[20];                                   /* bytes 394 to 413 */
  uint8_t cfi[6];                                             /* bytes 414 to 419 */
  uint8_t fisn[35];                                           /* bytes 420 to 454 */
  uint8_t issue_size[8];                                      /* bytes 455 to 462 */
  uint8_t nominal_currency[2];                                /* bytes 463 to 464 */
  uint8_t us_indicator;                                       /* byte 465 */
  uint8_t expiry_date[4];                                     /* bytes 466 to 469 */
  uint8_t version_number;                                     /* byte 470 */
  uint8_t settlement_type;                                    /* byte 471 */
  uint8_t option_type;                                        /* byte 472 */
  uint8_t exercise_type;                                      /* byte 473 */
  uint8_t product_name[50];                                   /* bytes 474 to 523 */
  uint8_t reference_price[8];                                 /* bytes 524 to 531 */
  uint8_t status;                                             /* byte 532 */
  uint8_t initial_phase_id[4];                                /* bytes 533 to 536 */
  uint8_t threshold_max[8];                                   /* bytes 537 to 544 */
  uint8_t threshold_min[8];                                   /* bytes 545 to 552 */
  uint8_t is_leverage;                                        /* byte 553 */
  uint8_t accrued_interest_value[8];                          /* bytes 554 to 561 */
  uint8_t kid[128];                                           /* bytes 562 to 689 */
  uint8_t kid_issue_date[4];                                  /* bytes 690 to 693 */
  uint8_t value_at_risk;                                      /* byte 694 */
  uint8_t external_underlying_id[4];                          /* bytes 695 to 698 */
} Instrument;

/* any Instrument at all: every byte one the checker chooses */
static void any_instrument(Instrument *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->product_type = arbitrary();
  record->product_subtype = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->first_trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->iceberg_min_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lot_size[i] = arbitrary(); }
  record->price_expression_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->calendar_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_structure_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tick_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->collar_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_schedule_id[i] = arbitrary(); }
  for (size_t i = 0; i < 64; i++) { record->description[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nominal_value_price[i] = arbitrary(); }
  record->nominal_value_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->multiplier_multiplier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->strike_price_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->product_identification_product_identification[i] = arbitrary(); }
  record->product_identification_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->settlement_calendar_id[i] = arbitrary(); }
  record->bond_coupon_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->pre_trade_check_min_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->pre_trade_check_max_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->pre_trade_check_min_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->pre_trade_check_max_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->pre_trade_check_max_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->pre_trade_check_min_value[i] = arbitrary(); }
  record->liquidity = arbitrary();
  record->market_model_type = arbitrary();
  for (size_t i = 0; i < 150; i++) { record->issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->issuer_reg_country[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->product_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cfi[i] = arbitrary(); }
  for (size_t i = 0; i < 35; i++) { record->fisn[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->issue_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->nominal_currency[i] = arbitrary(); }
  record->us_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = arbitrary(); }
  record->version_number = arbitrary();
  record->settlement_type = arbitrary();
  record->option_type = arbitrary();
  record->exercise_type = arbitrary();
  for (size_t i = 0; i < 50; i++) { record->product_name[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  record->status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->initial_phase_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->threshold_max[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->threshold_min[i] = arbitrary(); }
  record->is_leverage = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_value[i] = arbitrary(); }
  for (size_t i = 0; i < 128; i++) { record->kid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->kid_issue_date[i] = arbitrary(); }
  record->value_at_risk = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->external_underlying_id[i] = arbitrary(); }
}

/* Instrument to the wire: 699 bytes from at, returning where the next byte goes */
static size_t encode_instrument(const Instrument *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->product_type;
  wire[at++] = record->product_subtype;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_trading_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trading_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->iceberg_min_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lot_size[i]; }
  wire[at++] = record->price_expression_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->calendar_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_structure_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tick_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->collar_group_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_schedule_id[i]; }
  for (size_t i = 0; i < 64; i++) { wire[at++] = record->description[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mic[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nominal_value_price[i]; }
  wire[at++] = record->nominal_value_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->multiplier_multiplier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->strike_price_currency[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->product_identification_product_identification[i]; }
  wire[at++] = record->product_identification_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settlement_calendar_id[i]; }
  wire[at++] = record->bond_coupon_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pre_trade_check_min_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pre_trade_check_max_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pre_trade_check_min_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pre_trade_check_max_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pre_trade_check_max_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pre_trade_check_min_value[i]; }
  wire[at++] = record->liquidity;
  wire[at++] = record->market_model_type;
  for (size_t i = 0; i < 150; i++) { wire[at++] = record->issuer[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->issuer_reg_country[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_instrument_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->product_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cfi[i]; }
  for (size_t i = 0; i < 35; i++) { wire[at++] = record->fisn[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->nominal_currency[i]; }
  wire[at++] = record->us_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expiry_date[i]; }
  wire[at++] = record->version_number;
  wire[at++] = record->settlement_type;
  wire[at++] = record->option_type;
  wire[at++] = record->exercise_type;
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->product_name[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  wire[at++] = record->status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->initial_phase_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->threshold_max[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->threshold_min[i]; }
  wire[at++] = record->is_leverage;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accrued_interest_value[i]; }
  for (size_t i = 0; i < 128; i++) { wire[at++] = record->kid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->kid_issue_date[i]; }
  wire[at++] = record->value_at_risk;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->external_underlying_id[i]; }

  return at;
}

/* Instrument off the wire: 699 bytes from at, returning where the next byte lies */
static size_t decode_instrument(Instrument *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->product_type = wire[at++];
  record->product_subtype = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->first_trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->iceberg_min_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lot_size[i] = wire[at++]; }
  record->price_expression_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->calendar_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_structure_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tick_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->collar_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_schedule_id[i] = wire[at++]; }
  for (size_t i = 0; i < 64; i++) { record->description[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nominal_value_price[i] = wire[at++]; }
  record->nominal_value_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->multiplier_multiplier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->strike_price_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->product_identification_product_identification[i] = wire[at++]; }
  record->product_identification_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->settlement_calendar_id[i] = wire[at++]; }
  record->bond_coupon_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->pre_trade_check_min_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->pre_trade_check_max_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->pre_trade_check_min_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->pre_trade_check_max_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->pre_trade_check_max_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->pre_trade_check_min_value[i] = wire[at++]; }
  record->liquidity = wire[at++];
  record->market_model_type = wire[at++];
  for (size_t i = 0; i < 150; i++) { record->issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->issuer_reg_country[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->product_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cfi[i] = wire[at++]; }
  for (size_t i = 0; i < 35; i++) { record->fisn[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->issue_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->nominal_currency[i] = wire[at++]; }
  record->us_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = wire[at++]; }
  record->version_number = wire[at++];
  record->settlement_type = wire[at++];
  record->option_type = wire[at++];
  record->exercise_type = wire[at++];
  for (size_t i = 0; i < 50; i++) { record->product_name[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  record->status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->initial_phase_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->threshold_max[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->threshold_min[i] = wire[at++]; }
  record->is_leverage = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_value[i] = wire[at++]; }
  for (size_t i = 0; i < 128; i++) { record->kid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->kid_issue_date[i] = wire[at++]; }
  record->value_at_risk = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->external_underlying_id[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument is what was written, byte for byte */
static void equal_instrument(const Instrument *read, const Instrument *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->product_type == written->product_type);
  assert(read->product_subtype == written->product_subtype);
  for (size_t i = 0; i < 4; i++) { assert(read->first_trading_date[i] == written->first_trading_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trading_date[i] == written->last_trading_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->iceberg_min_value[i] == written->iceberg_min_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lot_size[i] == written->lot_size[i]); }
  assert(read->price_expression_type == written->price_expression_type);
  for (size_t i = 0; i < 4; i++) { assert(read->calendar_id[i] == written->calendar_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_structure_id[i] == written->market_structure_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tick_table_id[i] == written->tick_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_instrument_id[i] == written->reference_instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->collar_group_id[i] == written->collar_group_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_schedule_id[i] == written->trading_schedule_id[i]); }
  for (size_t i = 0; i < 64; i++) { assert(read->description[i] == written->description[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mic[i] == written->mic[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nominal_value_price[i] == written->nominal_value_price[i]); }
  assert(read->nominal_value_type == written->nominal_value_type);
  for (size_t i = 0; i < 8; i++) { assert(read->multiplier_multiplier[i] == written->multiplier_multiplier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->strike_price_currency[i] == written->strike_price_currency[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->product_identification_product_identification[i] == written->product_identification_product_identification[i]); }
  assert(read->product_identification_type == written->product_identification_type);
  for (size_t i = 0; i < 4; i++) { assert(read->settlement_calendar_id[i] == written->settlement_calendar_id[i]); }
  assert(read->bond_coupon_type == written->bond_coupon_type);
  for (size_t i = 0; i < 8; i++) { assert(read->pre_trade_check_min_price[i] == written->pre_trade_check_min_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->pre_trade_check_max_price[i] == written->pre_trade_check_max_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->pre_trade_check_min_quantity[i] == written->pre_trade_check_min_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->pre_trade_check_max_quantity[i] == written->pre_trade_check_max_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->pre_trade_check_max_value[i] == written->pre_trade_check_max_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->pre_trade_check_min_value[i] == written->pre_trade_check_min_value[i]); }
  assert(read->liquidity == written->liquidity);
  assert(read->market_model_type == written->market_model_type);
  for (size_t i = 0; i < 150; i++) { assert(read->issuer[i] == written->issuer[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->issuer_reg_country[i] == written->issuer_reg_country[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_instrument_id[i] == written->underlying_instrument_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->product_code[i] == written->product_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cfi[i] == written->cfi[i]); }
  for (size_t i = 0; i < 35; i++) { assert(read->fisn[i] == written->fisn[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->issue_size[i] == written->issue_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->nominal_currency[i] == written->nominal_currency[i]); }
  assert(read->us_indicator == written->us_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->expiry_date[i] == written->expiry_date[i]); }
  assert(read->version_number == written->version_number);
  assert(read->settlement_type == written->settlement_type);
  assert(read->option_type == written->option_type);
  assert(read->exercise_type == written->exercise_type);
  for (size_t i = 0; i < 50; i++) { assert(read->product_name[i] == written->product_name[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  assert(read->status == written->status);
  for (size_t i = 0; i < 4; i++) { assert(read->initial_phase_id[i] == written->initial_phase_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->threshold_max[i] == written->threshold_max[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->threshold_min[i] == written->threshold_min[i]); }
  assert(read->is_leverage == written->is_leverage);
  for (size_t i = 0; i < 8; i++) { assert(read->accrued_interest_value[i] == written->accrued_interest_value[i]); }
  for (size_t i = 0; i < 128; i++) { assert(read->kid[i] == written->kid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->kid_issue_date[i] == written->kid_issue_date[i]); }
  assert(read->value_at_risk == written->value_at_risk);
  for (size_t i = 0; i < 4; i++) { assert(read->external_underlying_id[i] == written->external_underlying_id[i]); }
}

/* Instrument: written and read back, then read and written back */
static void check_instrument(void) {
  Instrument sent;
  Instrument got;
  uint8_t wire[699];
  uint8_t again[699];

  any_instrument(&sent);
  assert(encode_instrument(&sent, wire, 0) == 699);
  assert(decode_instrument(&got, wire, 0) == 699);
  equal_instrument(&got, &sent);

  for (size_t i = 0; i < 699; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument(&got, wire, 0) == 699);
  assert(encode_instrument(&got, again, 0) == 699);
  for (size_t i = 0; i < 699; i++) { assert(again[i] == wire[i]); }
}

/* ---- Accrued Interest Table Entry: 16 bytes ---------------------------------- */

/* Message describing an accrued interest table entry */
typedef struct {
  uint8_t product_id[4];                          /* bytes 0 to 3 */
  uint8_t accrued_interest_table_entry_date[4];   /* bytes 4 to 7 */
  uint8_t accrued_interest_table_entry_value[8];  /* bytes 8 to 15 */
} AccruedInterestTableEntry;

/* any Accrued Interest Table Entry at all: every byte one the checker chooses */
static void any_accrued_interest_table_entry(AccruedInterestTableEntry *record) {
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->accrued_interest_table_entry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_table_entry_value[i] = arbitrary(); }
}

/* Accrued Interest Table Entry to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_accrued_interest_table_entry(const AccruedInterestTableEntry *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->accrued_interest_table_entry_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accrued_interest_table_entry_value[i]; }

  return at;
}

/* Accrued Interest Table Entry off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_accrued_interest_table_entry(AccruedInterestTableEntry *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->accrued_interest_table_entry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_table_entry_value[i] = wire[at++]; }

  return at;
}

/* what was read of Accrued Interest Table Entry is what was written, byte for byte */
static void equal_accrued_interest_table_entry(const AccruedInterestTableEntry *read, const AccruedInterestTableEntry *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->accrued_interest_table_entry_date[i] == written->accrued_interest_table_entry_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accrued_interest_table_entry_value[i] == written->accrued_interest_table_entry_value[i]); }
}

/* Accrued Interest Table Entry: written and read back, then read and written back */
static void check_accrued_interest_table_entry(void) {
  AccruedInterestTableEntry sent;
  AccruedInterestTableEntry got;
  uint8_t wire[16];
  uint8_t again[16];

  any_accrued_interest_table_entry(&sent);
  assert(encode_accrued_interest_table_entry(&sent, wire, 0) == 16);
  assert(decode_accrued_interest_table_entry(&got, wire, 0) == 16);
  equal_accrued_interest_table_entry(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_accrued_interest_table_entry(&got, wire, 0) == 16);
  assert(encode_accrued_interest_table_entry(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indexation Table Entry: 16 bytes ---------------------------------------- */

/* Message describing an indexation table entry */
typedef struct {
  uint8_t product_id[4];                    /* bytes 0 to 3 */
  uint8_t indexation_table_entry_date[4];   /* bytes 4 to 7 */
  uint8_t indexation_table_entry_value[8];  /* bytes 8 to 15 */
} IndexationTableEntry;

/* any Indexation Table Entry at all: every byte one the checker chooses */
static void any_indexation_table_entry(IndexationTableEntry *record) {
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->indexation_table_entry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indexation_table_entry_value[i] = arbitrary(); }
}

/* Indexation Table Entry to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_indexation_table_entry(const IndexationTableEntry *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->indexation_table_entry_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indexation_table_entry_value[i]; }

  return at;
}

/* Indexation Table Entry off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_indexation_table_entry(IndexationTableEntry *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->indexation_table_entry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indexation_table_entry_value[i] = wire[at++]; }

  return at;
}

/* what was read of Indexation Table Entry is what was written, byte for byte */
static void equal_indexation_table_entry(const IndexationTableEntry *read, const IndexationTableEntry *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->indexation_table_entry_date[i] == written->indexation_table_entry_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indexation_table_entry_value[i] == written->indexation_table_entry_value[i]); }
}

/* Indexation Table Entry: written and read back, then read and written back */
static void check_indexation_table_entry(void) {
  IndexationTableEntry sent;
  IndexationTableEntry got;
  uint8_t wire[16];
  uint8_t again[16];

  any_indexation_table_entry(&sent);
  assert(encode_indexation_table_entry(&sent, wire, 0) == 16);
  assert(decode_indexation_table_entry(&got, wire, 0) == 16);
  equal_indexation_table_entry(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_indexation_table_entry(&got, wire, 0) == 16);
  assert(encode_indexation_table_entry(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Product Identification Public Product Identification: 31 bytes ---------- */

/* PublicProductIdentification */
typedef struct {
  uint8_t product_identification_product_identification[30];  /* bytes 0 to 29 */
  uint8_t product_identification_type;                        /* byte 30 */
} ProductIdentificationPublicProductIdentification;

/* any Product Identification Public Product Identification at all: every byte one the checker chooses */
static void any_product_identification_public_product_identification(ProductIdentificationPublicProductIdentification *record) {
  for (size_t i = 0; i < 30; i++) { record->product_identification_product_identification[i] = arbitrary(); }
  record->product_identification_type = arbitrary();
}

/* Product Identification Public Product Identification to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_product_identification_public_product_identification(const ProductIdentificationPublicProductIdentification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->product_identification_product_identification[i]; }
  wire[at++] = record->product_identification_type;

  return at;
}

/* Product Identification Public Product Identification off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_product_identification_public_product_identification(ProductIdentificationPublicProductIdentification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 30; i++) { record->product_identification_product_identification[i] = wire[at++]; }
  record->product_identification_type = wire[at++];

  return at;
}

/* what was read of Product Identification Public Product Identification is what was written, byte for byte */
static void equal_product_identification_public_product_identification(const ProductIdentificationPublicProductIdentification *read, const ProductIdentificationPublicProductIdentification *written) {
  for (size_t i = 0; i < 30; i++) { assert(read->product_identification_product_identification[i] == written->product_identification_product_identification[i]); }
  assert(read->product_identification_type == written->product_identification_type);
}

/* Product Identification Public Product Identification: written and read back, then read and written back */
static void check_product_identification_public_product_identification(void) {
  ProductIdentificationPublicProductIdentification sent;
  ProductIdentificationPublicProductIdentification got;
  uint8_t wire[31];
  uint8_t again[31];

  any_product_identification_public_product_identification(&sent);
  assert(encode_product_identification_public_product_identification(&sent, wire, 0) == 31);
  assert(decode_product_identification_public_product_identification(&got, wire, 0) == 31);
  equal_product_identification_public_product_identification(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_product_identification_public_product_identification(&got, wire, 0) == 31);
  assert(encode_product_identification_public_product_identification(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Underlying: 32 bytes ---------------------------------------------- */

/* IndexUnderlying */
typedef struct {
  ProductIdentificationPublicProductIdentification product_identification_public_product_identification;  /* bytes 0 to 30 */
  uint8_t index_underlying_type;                                                                          /* byte 31 */
} IndexUnderlying;

/* any Index Underlying at all: every byte one the checker chooses */
static void any_index_underlying(IndexUnderlying *record) {
  any_product_identification_public_product_identification(&record->product_identification_public_product_identification);
  record->index_underlying_type = arbitrary();
}

/* Index Underlying to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_index_underlying(const IndexUnderlying *record, uint8_t *wire, size_t at) {
  at = encode_product_identification_public_product_identification(&record->product_identification_public_product_identification, wire, at);
  wire[at++] = record->index_underlying_type;

  return at;
}

/* Index Underlying off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_index_underlying(IndexUnderlying *record, const uint8_t *wire, size_t at) {
  at = decode_product_identification_public_product_identification(&record->product_identification_public_product_identification, wire, at);
  record->index_underlying_type = wire[at++];

  return at;
}

/* what was read of Index Underlying is what was written, byte for byte */
static void equal_index_underlying(const IndexUnderlying *read, const IndexUnderlying *written) {
  equal_product_identification_public_product_identification(&read->product_identification_public_product_identification, &written->product_identification_public_product_identification);
  assert(read->index_underlying_type == written->index_underlying_type);
}

/* Index Underlying: written and read back, then read and written back */
static void check_index_underlying(void) {
  IndexUnderlying sent;
  IndexUnderlying got;
  uint8_t wire[32];
  uint8_t again[32];

  any_index_underlying(&sent);
  assert(encode_index_underlying(&sent, wire, 0) == 32);
  assert(decode_index_underlying(&got, wire, 0) == 32);
  equal_index_underlying(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_index_underlying(&got, wire, 0) == 32);
  assert(encode_index_underlying(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Public Product Identification: 31 bytes --------------------------------- */

/* PublicProductIdentification */
typedef struct {
  uint8_t product_identification_product_identification[30];  /* bytes 0 to 29 */
  uint8_t product_identification_type;                        /* byte 30 */
} PublicProductIdentification;

/* any Public Product Identification at all: every byte one the checker chooses */
static void any_public_product_identification(PublicProductIdentification *record) {
  for (size_t i = 0; i < 30; i++) { record->product_identification_product_identification[i] = arbitrary(); }
  record->product_identification_type = arbitrary();
}

/* Public Product Identification to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_public_product_identification(const PublicProductIdentification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->product_identification_product_identification[i]; }
  wire[at++] = record->product_identification_type;

  return at;
}

/* Public Product Identification off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_public_product_identification(PublicProductIdentification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 30; i++) { record->product_identification_product_identification[i] = wire[at++]; }
  record->product_identification_type = wire[at++];

  return at;
}

/* what was read of Public Product Identification is what was written, byte for byte */
static void equal_public_product_identification(const PublicProductIdentification *read, const PublicProductIdentification *written) {
  for (size_t i = 0; i < 30; i++) { assert(read->product_identification_product_identification[i] == written->product_identification_product_identification[i]); }
  assert(read->product_identification_type == written->product_identification_type);
}

/* Public Product Identification: written and read back, then read and written back */
static void check_public_product_identification(void) {
  PublicProductIdentification sent;
  PublicProductIdentification got;
  uint8_t wire[31];
  uint8_t again[31];

  any_public_product_identification(&sent);
  assert(encode_public_product_identification(&sent, wire, 0) == 31);
  assert(decode_public_product_identification(&got, wire, 0) == 31);
  equal_public_product_identification(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_public_product_identification(&got, wire, 0) == 31);
  assert(encode_public_product_identification(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Summary: 21 bytes ----------------------------------------------- */

/* Auction summary, including auction price and quantity */
typedef struct {
  uint8_t instrument_id[4];  /* bytes 0 to 3 */
  uint8_t price[8];          /* bytes 4 to 11 */
  uint8_t quantity[8];       /* bytes 12 to 19 */
  uint8_t auction_type;      /* byte 20 */
} AuctionSummary;

/* any Auction Summary at all: every byte one the checker chooses */
static void any_auction_summary(AuctionSummary *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  record->auction_type = arbitrary();
}

/* Auction Summary to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_auction_summary(const AuctionSummary *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->auction_type;

  return at;
}

/* Auction Summary off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_auction_summary(AuctionSummary *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  record->auction_type = wire[at++];

  return at;
}

/* what was read of Auction Summary is what was written, byte for byte */
static void equal_auction_summary(const AuctionSummary *read, const AuctionSummary *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->auction_type == written->auction_type);
}

/* Auction Summary: written and read back, then read and written back */
static void check_auction_summary(void) {
  AuctionSummary sent;
  AuctionSummary got;
  uint8_t wire[21];
  uint8_t again[21];

  any_auction_summary(&sent);
  assert(encode_auction_summary(&sent, wire, 0) == 21);
  assert(decode_auction_summary(&got, wire, 0) == 21);
  equal_auction_summary(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_summary(&got, wire, 0) == 21);
  assert(encode_auction_summary(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Update: 68 bytes ------------------------------------------------ */

/* Updates IMP/IMV and BBO during an auction */
typedef struct {
  uint8_t instrument_id[4];               /* bytes 0 to 3 */
  uint8_t indicative_matching_price[8];   /* bytes 4 to 11 */
  uint8_t indicative_matching_volume[8];  /* bytes 12 to 19 */
  uint8_t total_sell_quantity_at_imp[8];  /* bytes 20 to 27 */
  uint8_t total_buy_quantity_at_imp[8];   /* bytes 28 to 35 */
  uint8_t best_sell_level[8];             /* bytes 36 to 43 */
  uint8_t best_sell_level_quantity[8];    /* bytes 44 to 51 */
  uint8_t best_buy_level[8];              /* bytes 52 to 59 */
  uint8_t best_buy_level_quantity[8];     /* bytes 60 to 67 */
} AuctionUpdate;

/* any Auction Update at all: every byte one the checker chooses */
static void any_auction_update(AuctionUpdate *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_matching_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_matching_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_sell_quantity_at_imp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_buy_quantity_at_imp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_sell_level[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_sell_level_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_buy_level[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_buy_level_quantity[i] = arbitrary(); }
}

/* Auction Update to the wire: 68 bytes from at, returning where the next byte goes */
static size_t encode_auction_update(const AuctionUpdate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_matching_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_matching_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_sell_quantity_at_imp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_buy_quantity_at_imp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_sell_level[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_sell_level_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_buy_level[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_buy_level_quantity[i]; }

  return at;
}

/* Auction Update off the wire: 68 bytes from at, returning where the next byte lies */
static size_t decode_auction_update(AuctionUpdate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_matching_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_matching_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_sell_quantity_at_imp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_buy_quantity_at_imp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_sell_level[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_sell_level_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_buy_level[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_buy_level_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Update is what was written, byte for byte */
static void equal_auction_update(const AuctionUpdate *read, const AuctionUpdate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_matching_price[i] == written->indicative_matching_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_matching_volume[i] == written->indicative_matching_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_sell_quantity_at_imp[i] == written->total_sell_quantity_at_imp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_buy_quantity_at_imp[i] == written->total_buy_quantity_at_imp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_sell_level[i] == written->best_sell_level[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_sell_level_quantity[i] == written->best_sell_level_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_buy_level[i] == written->best_buy_level[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_buy_level_quantity[i] == written->best_buy_level_quantity[i]); }
}

/* Auction Update: written and read back, then read and written back */
static void check_auction_update(void) {
  AuctionUpdate sent;
  AuctionUpdate got;
  uint8_t wire[68];
  uint8_t again[68];

  any_auction_update(&sent);
  assert(encode_auction_update(&sent, wire, 0) == 68);
  assert(decode_auction_update(&got, wire, 0) == 68);
  equal_auction_update(&got, &sent);

  for (size_t i = 0; i < 68; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_update(&got, wire, 0) == 68);
  assert(encode_auction_update(&got, again, 0) == 68);
  for (size_t i = 0; i < 68; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Level: 31 bytes --------------------------------------------------- */

/* PriceLevel */
typedef struct {
  uint8_t is_encrypted;          /* byte 0 */
  uint8_t encryption_offset[8];  /* bytes 1 to 8 */
  uint8_t encryption_key_id[4];  /* bytes 9 to 12 */
  uint8_t price[8];              /* bytes 13 to 20 */
  uint8_t quantity[8];           /* bytes 21 to 28 */
  uint8_t order_count[2];        /* bytes 29 to 30 */
} PriceLevel;

/* any Price Level at all: every byte one the checker chooses */
static void any_price_level(PriceLevel *record) {
  record->is_encrypted = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->encryption_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->encryption_key_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->order_count[i] = arbitrary(); }
}

/* Price Level to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_price_level(const PriceLevel *record, uint8_t *wire, size_t at) {
  wire[at++] = record->is_encrypted;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->encryption_offset[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->encryption_key_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->order_count[i]; }

  return at;
}

/* Price Level off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_price_level(PriceLevel *record, const uint8_t *wire, size_t at) {
  record->is_encrypted = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->encryption_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->encryption_key_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->order_count[i] = wire[at++]; }

  return at;
}

/* what was read of Price Level is what was written, byte for byte */
static void equal_price_level(const PriceLevel *read, const PriceLevel *written) {
  assert(read->is_encrypted == written->is_encrypted);
  for (size_t i = 0; i < 8; i++) { assert(read->encryption_offset[i] == written->encryption_offset[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->encryption_key_id[i] == written->encryption_key_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->order_count[i] == written->order_count[i]); }
}

/* Price Level: written and read back, then read and written back */
static void check_price_level(void) {
  PriceLevel sent;
  PriceLevel got;
  uint8_t wire[31];
  uint8_t again[31];

  any_price_level(&sent);
  assert(encode_price_level(&sent, wire, 0) == 31);
  assert(decode_price_level(&got, wire, 0) == 31);
  equal_price_level(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_price_level(&got, wire, 0) == 31);
  assert(encode_price_level(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Top Price Level Update: 23 bytes ---------------------------------------- */

/* BBO Level 1 */
typedef struct {
  uint8_t instrument_id[4];  /* bytes 0 to 3 */
  uint8_t price[8];          /* bytes 4 to 11 */
  uint8_t quantity[8];       /* bytes 12 to 19 */
  uint8_t side;              /* byte 20 */
  uint8_t order_count[2];    /* bytes 21 to 22 */
} TopPriceLevelUpdate;

/* any Top Price Level Update at all: every byte one the checker chooses */
static void any_top_price_level_update(TopPriceLevelUpdate *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->order_count[i] = arbitrary(); }
}

/* Top Price Level Update to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_top_price_level_update(const TopPriceLevelUpdate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->order_count[i]; }

  return at;
}

/* Top Price Level Update off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_top_price_level_update(TopPriceLevelUpdate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->order_count[i] = wire[at++]; }

  return at;
}

/* what was read of Top Price Level Update is what was written, byte for byte */
static void equal_top_price_level_update(const TopPriceLevelUpdate *read, const TopPriceLevelUpdate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 2; i++) { assert(read->order_count[i] == written->order_count[i]); }
}

/* Top Price Level Update: written and read back, then read and written back */
static void check_top_price_level_update(void) {
  TopPriceLevelUpdate sent;
  TopPriceLevelUpdate got;
  uint8_t wire[23];
  uint8_t again[23];

  any_top_price_level_update(&sent);
  assert(encode_top_price_level_update(&sent, wire, 0) == 23);
  assert(decode_top_price_level_update(&got, wire, 0) == 23);
  equal_top_price_level_update(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_top_price_level_update(&got, wire, 0) == 23);
  assert(encode_top_price_level_update(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade: 178 bytes -------------------------------------------------------- */

/* Enriched trade report */
typedef struct {
  uint8_t instrument_id[4];                                   /* bytes 0 to 3 */
  uint8_t settlement_value_value[8];                          /* bytes 4 to 11 */
  uint8_t settlement_date[4];                                 /* bytes 12 to 15 */
  uint8_t trading_timestamp[8];                               /* bytes 16 to 23 */
  PublicProductIdentification public_product_identification;  /* bytes 24 to 54 */
  uint8_t price[8];                                           /* bytes 55 to 62 */
  uint8_t price_currency[2];                                  /* bytes 63 to 64 */
  uint8_t price_notation;                                     /* byte 65 */
  uint8_t quantity[8];                                        /* bytes 66 to 73 */
  uint8_t nominal_value_value[8];                             /* bytes 74 to 81 */
  uint8_t nominal_currency[2];                                /* bytes 82 to 83 */
  uint8_t mic[4];                                             /* bytes 84 to 87 */
  uint8_t publication_timestamp[8];                           /* bytes 88 to 95 */
  uint8_t trade_id[4];                                        /* bytes 96 to 99 */
  uint8_t trade_to_be_cleared;                                /* byte 100 */
  uint8_t pct_change[8];                                      /* bytes 101 to 108 */
  uint8_t vwap[8];                                            /* bytes 109 to 116 */
  uint8_t no_trades[8];                                       /* bytes 117 to 124 */
  uint8_t total_volume[8];                                    /* bytes 125 to 132 */
  uint8_t total_value[8];                                     /* bytes 133 to 140 */
  uint8_t opening_price[8];                                   /* bytes 141 to 148 */
  uint8_t max_price[8];                                       /* bytes 149 to 156 */
  uint8_t min_price[8];                                       /* bytes 157 to 164 */
  uint8_t mmt_market_mechanism;                               /* byte 165 */
  uint8_t mmt_trading_mode;                                   /* byte 166 */
  uint8_t mmt_transaction_category;                           /* byte 167 */
  uint8_t mmt_negotiation_indicator;                          /* byte 168 */
  uint8_t mmt_agency_cross_trade_indicator;                   /* byte 169 */
  uint8_t mmt_modification_indicator;                         /* byte 170 */
  uint8_t mmt_benchmark_reference_price_indicator;            /* byte 171 */
  uint8_t mmt_special_dividend_indicator;                     /* byte 172 */
  uint8_t mmt_off_book_automated_indicator;                   /* byte 173 */
  uint8_t mmt_ordinary_trade_indicator;                       /* byte 174 */
  uint8_t mmt_algorithmic_indicator;                          /* byte 175 */
  uint8_t mmt_post_trade_deferral_reason;                     /* byte 176 */
  uint8_t mmt_post_trade_deferral_type;                       /* byte 177 */
} Trade;

/* any Trade at all: every byte one the checker chooses */
static void any_trade(Trade *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_value_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->settlement_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_timestamp[i] = arbitrary(); }
  any_public_product_identification(&record->public_product_identification);
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_currency[i] = arbitrary(); }
  record->price_notation = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nominal_value_value[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->nominal_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->publication_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  record->trade_to_be_cleared = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->pct_change[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->no_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_price[i] = arbitrary(); }
  record->mmt_market_mechanism = arbitrary();
  record->mmt_trading_mode = arbitrary();
  record->mmt_transaction_category = arbitrary();
  record->mmt_negotiation_indicator = arbitrary();
  record->mmt_agency_cross_trade_indicator = arbitrary();
  record->mmt_modification_indicator = arbitrary();
  record->mmt_benchmark_reference_price_indicator = arbitrary();
  record->mmt_special_dividend_indicator = arbitrary();
  record->mmt_off_book_automated_indicator = arbitrary();
  record->mmt_ordinary_trade_indicator = arbitrary();
  record->mmt_algorithmic_indicator = arbitrary();
  record->mmt_post_trade_deferral_reason = arbitrary();
  record->mmt_post_trade_deferral_type = arbitrary();
}

/* Trade to the wire: 178 bytes from at, returning where the next byte goes */
static size_t encode_trade(const Trade *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_value_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settlement_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_timestamp[i]; }
  at = encode_public_product_identification(&record->public_product_identification, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_currency[i]; }
  wire[at++] = record->price_notation;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nominal_value_value[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->nominal_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mic[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->publication_timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->trade_to_be_cleared;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pct_change[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->no_trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_price[i]; }
  wire[at++] = record->mmt_market_mechanism;
  wire[at++] = record->mmt_trading_mode;
  wire[at++] = record->mmt_transaction_category;
  wire[at++] = record->mmt_negotiation_indicator;
  wire[at++] = record->mmt_agency_cross_trade_indicator;
  wire[at++] = record->mmt_modification_indicator;
  wire[at++] = record->mmt_benchmark_reference_price_indicator;
  wire[at++] = record->mmt_special_dividend_indicator;
  wire[at++] = record->mmt_off_book_automated_indicator;
  wire[at++] = record->mmt_ordinary_trade_indicator;
  wire[at++] = record->mmt_algorithmic_indicator;
  wire[at++] = record->mmt_post_trade_deferral_reason;
  wire[at++] = record->mmt_post_trade_deferral_type;

  return at;
}

/* Trade off the wire: 178 bytes from at, returning where the next byte lies */
static size_t decode_trade(Trade *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_value_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->settlement_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_timestamp[i] = wire[at++]; }
  at = decode_public_product_identification(&record->public_product_identification, wire, at);
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_currency[i] = wire[at++]; }
  record->price_notation = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nominal_value_value[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->nominal_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->publication_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  record->trade_to_be_cleared = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->pct_change[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->no_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_price[i] = wire[at++]; }
  record->mmt_market_mechanism = wire[at++];
  record->mmt_trading_mode = wire[at++];
  record->mmt_transaction_category = wire[at++];
  record->mmt_negotiation_indicator = wire[at++];
  record->mmt_agency_cross_trade_indicator = wire[at++];
  record->mmt_modification_indicator = wire[at++];
  record->mmt_benchmark_reference_price_indicator = wire[at++];
  record->mmt_special_dividend_indicator = wire[at++];
  record->mmt_off_book_automated_indicator = wire[at++];
  record->mmt_ordinary_trade_indicator = wire[at++];
  record->mmt_algorithmic_indicator = wire[at++];
  record->mmt_post_trade_deferral_reason = wire[at++];
  record->mmt_post_trade_deferral_type = wire[at++];

  return at;
}

/* what was read of Trade is what was written, byte for byte */
static void equal_trade(const Trade *read, const Trade *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_value_value[i] == written->settlement_value_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->settlement_date[i] == written->settlement_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_timestamp[i] == written->trading_timestamp[i]); }
  equal_public_product_identification(&read->public_product_identification, &written->public_product_identification);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_currency[i] == written->price_currency[i]); }
  assert(read->price_notation == written->price_notation);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nominal_value_value[i] == written->nominal_value_value[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->nominal_currency[i] == written->nominal_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mic[i] == written->mic[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->publication_timestamp[i] == written->publication_timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->trade_to_be_cleared == written->trade_to_be_cleared);
  for (size_t i = 0; i < 8; i++) { assert(read->pct_change[i] == written->pct_change[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap[i] == written->vwap[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->no_trades[i] == written->no_trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_value[i] == written->total_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_price[i] == written->max_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_price[i] == written->min_price[i]); }
  assert(read->mmt_market_mechanism == written->mmt_market_mechanism);
  assert(read->mmt_trading_mode == written->mmt_trading_mode);
  assert(read->mmt_transaction_category == written->mmt_transaction_category);
  assert(read->mmt_negotiation_indicator == written->mmt_negotiation_indicator);
  assert(read->mmt_agency_cross_trade_indicator == written->mmt_agency_cross_trade_indicator);
  assert(read->mmt_modification_indicator == written->mmt_modification_indicator);
  assert(read->mmt_benchmark_reference_price_indicator == written->mmt_benchmark_reference_price_indicator);
  assert(read->mmt_special_dividend_indicator == written->mmt_special_dividend_indicator);
  assert(read->mmt_off_book_automated_indicator == written->mmt_off_book_automated_indicator);
  assert(read->mmt_ordinary_trade_indicator == written->mmt_ordinary_trade_indicator);
  assert(read->mmt_algorithmic_indicator == written->mmt_algorithmic_indicator);
  assert(read->mmt_post_trade_deferral_reason == written->mmt_post_trade_deferral_reason);
  assert(read->mmt_post_trade_deferral_type == written->mmt_post_trade_deferral_type);
}

/* Trade: written and read back, then read and written back */
static void check_trade(void) {
  Trade sent;
  Trade got;
  uint8_t wire[178];
  uint8_t again[178];

  any_trade(&sent);
  assert(encode_trade(&sent, wire, 0) == 178);
  assert(decode_trade(&got, wire, 0) == 178);
  equal_trade(&got, &sent);

  for (size_t i = 0; i < 178; i++) { wire[i] = arbitrary(); }
  assert(decode_trade(&got, wire, 0) == 178);
  assert(encode_trade(&got, again, 0) == 178);
  for (size_t i = 0; i < 178; i++) { assert(again[i] == wire[i]); }
}

/* ---- Position Report: 40 bytes ----------------------------------------------- */

/* Report of open positions */
typedef struct {
  PublicProductIdentification public_product_identification;  /* bytes 0 to 30 */
  uint8_t pos_type;                                           /* byte 31 */
  uint8_t open_positions[4];                                  /* bytes 32 to 35 */
  uint8_t trade_id[4];                                        /* bytes 36 to 39 */
} PositionReport;

/* any Position Report at all: every byte one the checker chooses */
static void any_position_report(PositionReport *record) {
  any_public_product_identification(&record->public_product_identification);
  record->pos_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->open_positions[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
}

/* Position Report to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_position_report(const PositionReport *record, uint8_t *wire, size_t at) {
  at = encode_public_product_identification(&record->public_product_identification, wire, at);
  wire[at++] = record->pos_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_positions[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }

  return at;
}

/* Position Report off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_position_report(PositionReport *record, const uint8_t *wire, size_t at) {
  at = decode_public_product_identification(&record->public_product_identification, wire, at);
  record->pos_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->open_positions[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }

  return at;
}

/* what was read of Position Report is what was written, byte for byte */
static void equal_position_report(const PositionReport *read, const PositionReport *written) {
  equal_public_product_identification(&read->public_product_identification, &written->public_product_identification);
  assert(read->pos_type == written->pos_type);
  for (size_t i = 0; i < 4; i++) { assert(read->open_positions[i] == written->open_positions[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
}

/* Position Report: written and read back, then read and written back */
static void check_position_report(void) {
  PositionReport sent;
  PositionReport got;
  uint8_t wire[40];
  uint8_t again[40];

  any_position_report(&sent);
  assert(encode_position_report(&sent, wire, 0) == 40);
  assert(decode_position_report(&got, wire, 0) == 40);
  equal_position_report(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_position_report(&got, wire, 0) == 40);
  assert(encode_position_report(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Status Change: 11 bytes -------------------------------------- */

/* Start of a new trading phase */
typedef struct {
  uint8_t instrument_id[4];     /* bytes 0 to 3 */
  uint8_t trading_phase_id[4];  /* bytes 4 to 7 */
  uint8_t trading_phase_type;   /* byte 8 */
  uint8_t status;               /* byte 9 */
  uint8_t stressed_market;      /* byte 10 */
} InstrumentStatusChange;

/* any Instrument Status Change at all: every byte one the checker chooses */
static void any_instrument_status_change(InstrumentStatusChange *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_phase_id[i] = arbitrary(); }
  record->trading_phase_type = arbitrary();
  record->status = arbitrary();
  record->stressed_market = arbitrary();
}

/* Instrument Status Change to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_instrument_status_change(const InstrumentStatusChange *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_phase_id[i]; }
  wire[at++] = record->trading_phase_type;
  wire[at++] = record->status;
  wire[at++] = record->stressed_market;

  return at;
}

/* Instrument Status Change off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_instrument_status_change(InstrumentStatusChange *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_phase_id[i] = wire[at++]; }
  record->trading_phase_type = wire[at++];
  record->status = wire[at++];
  record->stressed_market = wire[at++];

  return at;
}

/* what was read of Instrument Status Change is what was written, byte for byte */
static void equal_instrument_status_change(const InstrumentStatusChange *read, const InstrumentStatusChange *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_phase_id[i] == written->trading_phase_id[i]); }
  assert(read->trading_phase_type == written->trading_phase_type);
  assert(read->status == written->status);
  assert(read->stressed_market == written->stressed_market);
}

/* Instrument Status Change: written and read back, then read and written back */
static void check_instrument_status_change(void) {
  InstrumentStatusChange sent;
  InstrumentStatusChange got;
  uint8_t wire[11];
  uint8_t again[11];

  any_instrument_status_change(&sent);
  assert(encode_instrument_status_change(&sent, wire, 0) == 11);
  assert(decode_instrument_status_change(&got, wire, 0) == 11);
  equal_instrument_status_change(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_status_change(&got, wire, 0) == 11);
  assert(encode_instrument_status_change(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Collars: 45 bytes ------------------------------------------------- */

/* New order price collars */
typedef struct {
  uint8_t instrument_id[4];  /* bytes 0 to 3 */
  uint8_t collar_type;       /* byte 4 */
  uint8_t price[8];          /* bytes 5 to 12 */
  uint8_t lower_bid[8];      /* bytes 13 to 20 */
  uint8_t upper_bid[8];      /* bytes 21 to 28 */
  uint8_t lower_ask[8];      /* bytes 29 to 36 */
  uint8_t upper_ask[8];      /* bytes 37 to 44 */
} OrderCollars;

/* any Order Collars at all: every byte one the checker chooses */
static void any_order_collars(OrderCollars *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->collar_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lower_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->upper_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lower_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->upper_ask[i] = arbitrary(); }
}

/* Order Collars to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_order_collars(const OrderCollars *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->collar_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_bid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->upper_bid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_ask[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->upper_ask[i]; }

  return at;
}

/* Order Collars off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_order_collars(OrderCollars *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->collar_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lower_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->upper_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lower_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->upper_ask[i] = wire[at++]; }

  return at;
}

/* what was read of Order Collars is what was written, byte for byte */
static void equal_order_collars(const OrderCollars *read, const OrderCollars *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->collar_type == written->collar_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lower_bid[i] == written->lower_bid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->upper_bid[i] == written->upper_bid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lower_ask[i] == written->lower_ask[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->upper_ask[i] == written->upper_ask[i]); }
}

/* Order Collars: written and read back, then read and written back */
static void check_order_collars(void) {
  OrderCollars sent;
  OrderCollars got;
  uint8_t wire[45];
  uint8_t again[45];

  any_order_collars(&sent);
  assert(encode_order_collars(&sent, wire, 0) == 45);
  assert(decode_order_collars(&got, wire, 0) == 45);
  equal_order_collars(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_order_collars(&got, wire, 0) == 45);
  assert(encode_order_collars(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Collars: 29 bytes ------------------------------------------------- */

/* New trade price collars */
typedef struct {
  uint8_t instrument_id[4];  /* bytes 0 to 3 */
  uint8_t collar_type;       /* byte 4 */
  uint8_t price[8];          /* bytes 5 to 12 */
  uint8_t lower[8];          /* bytes 13 to 20 */
  uint8_t upper[8];          /* bytes 21 to 28 */
} TradeCollars;

/* any Trade Collars at all: every byte one the checker chooses */
static void any_trade_collars(TradeCollars *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->collar_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lower[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->upper[i] = arbitrary(); }
}

/* Trade Collars to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_trade_collars(const TradeCollars *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->collar_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->upper[i]; }

  return at;
}

/* Trade Collars off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_trade_collars(TradeCollars *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->collar_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lower[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->upper[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Collars is what was written, byte for byte */
static void equal_trade_collars(const TradeCollars *read, const TradeCollars *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->collar_type == written->collar_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lower[i] == written->lower[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->upper[i] == written->upper[i]); }
}

/* Trade Collars: written and read back, then read and written back */
static void check_trade_collars(void) {
  TradeCollars sent;
  TradeCollars got;
  uint8_t wire[29];
  uint8_t again[29];

  any_trade_collars(&sent);
  assert(encode_trade_collars(&sent, wire, 0) == 29);
  assert(decode_trade_collars(&got, wire, 0) == 29);
  equal_trade_collars(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_collars(&got, wire, 0) == 29);
  assert(encode_trade_collars(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Summary: 95 bytes -------------------------------------------- */

/* Provides brief instrument summary */
typedef struct {
  uint8_t instrument_id[4];               /* bytes 0 to 3 */
  uint8_t last_traded_price[8];           /* bytes 4 to 11 */
  uint8_t closing_price[8];               /* bytes 12 to 19 */
  uint8_t closing_price_type;             /* byte 20 */
  uint8_t adjusted_closing_price[8];      /* bytes 21 to 28 */
  uint8_t adjusted_closing_price_reason;  /* byte 29 */
  uint8_t pct_change[8];                  /* bytes 30 to 37 */
  uint8_t vwap[8];                        /* bytes 38 to 45 */
  uint8_t no_trades[8];                   /* bytes 46 to 53 */
  uint8_t total_volume[8];                /* bytes 54 to 61 */
  uint8_t total_value[8];                 /* bytes 62 to 69 */
  uint8_t opening_price[8];               /* bytes 70 to 77 */
  uint8_t max_price[8];                   /* bytes 78 to 85 */
  uint8_t min_price[8];                   /* bytes 86 to 93 */
  uint8_t is_correction;                  /* byte 94 */
} InstrumentSummary;

/* any Instrument Summary at all: every byte one the checker chooses */
static void any_instrument_summary(InstrumentSummary *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_traded_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = arbitrary(); }
  record->closing_price_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->adjusted_closing_price[i] = arbitrary(); }
  record->adjusted_closing_price_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->pct_change[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->no_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_price[i] = arbitrary(); }
  record->is_correction = arbitrary();
}

/* Instrument Summary to the wire: 95 bytes from at, returning where the next byte goes */
static size_t encode_instrument_summary(const InstrumentSummary *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_traded_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price[i]; }
  wire[at++] = record->closing_price_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->adjusted_closing_price[i]; }
  wire[at++] = record->adjusted_closing_price_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pct_change[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->no_trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_price[i]; }
  wire[at++] = record->is_correction;

  return at;
}

/* Instrument Summary off the wire: 95 bytes from at, returning where the next byte lies */
static size_t decode_instrument_summary(InstrumentSummary *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_traded_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = wire[at++]; }
  record->closing_price_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->adjusted_closing_price[i] = wire[at++]; }
  record->adjusted_closing_price_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->pct_change[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->no_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_price[i] = wire[at++]; }
  record->is_correction = wire[at++];

  return at;
}

/* what was read of Instrument Summary is what was written, byte for byte */
static void equal_instrument_summary(const InstrumentSummary *read, const InstrumentSummary *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_traded_price[i] == written->last_traded_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  assert(read->closing_price_type == written->closing_price_type);
  for (size_t i = 0; i < 8; i++) { assert(read->adjusted_closing_price[i] == written->adjusted_closing_price[i]); }
  assert(read->adjusted_closing_price_reason == written->adjusted_closing_price_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->pct_change[i] == written->pct_change[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap[i] == written->vwap[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->no_trades[i] == written->no_trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_value[i] == written->total_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_price[i] == written->max_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_price[i] == written->min_price[i]); }
  assert(read->is_correction == written->is_correction);
}

/* Instrument Summary: written and read back, then read and written back */
static void check_instrument_summary(void) {
  InstrumentSummary sent;
  InstrumentSummary got;
  uint8_t wire[95];
  uint8_t again[95];

  any_instrument_summary(&sent);
  assert(encode_instrument_summary(&sent, wire, 0) == 95);
  assert(decode_instrument_summary(&got, wire, 0) == 95);
  equal_instrument_summary(&got, &sent);

  for (size_t i = 0; i < 95; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_summary(&got, wire, 0) == 95);
  assert(encode_instrument_summary(&got, again, 0) == 95);
  for (size_t i = 0; i < 95; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clob Instrument: 119 bytes ---------------------------------------------- */

/* SingleInstrumentSummary */
typedef struct {
  uint8_t instrument_id[4];               /* bytes 0 to 3 */
  uint8_t market_model_type;              /* byte 4 */
  uint8_t last_traded_price[8];           /* bytes 5 to 12 */
  uint8_t closing_price[8];               /* bytes 13 to 20 */
  uint8_t closing_price_type;             /* byte 21 */
  uint8_t adjusted_closing_price[8];      /* bytes 22 to 29 */
  uint8_t adjusted_closing_price_reason;  /* byte 30 */
  uint8_t pct_change[8];                  /* bytes 31 to 38 */
  uint8_t vwap[8];                        /* bytes 39 to 46 */
  uint8_t no_trades[8];                   /* bytes 47 to 54 */
  uint8_t total_volume[8];                /* bytes 55 to 62 */
  uint8_t total_value[8];                 /* bytes 63 to 70 */
  uint8_t opening_price[8];               /* bytes 71 to 78 */
  uint8_t max_price[8];                   /* bytes 79 to 86 */
  uint8_t min_price[8];                   /* bytes 87 to 94 */
  uint8_t settlement_price[8];            /* bytes 95 to 102 */
  uint8_t settlement_value_price[8];      /* bytes 103 to 110 */
  uint8_t end_trading_date[4];            /* bytes 111 to 114 */
  uint8_t last_trade_date[4];             /* bytes 115 to 118 */
} ClobInstrument;

/* any Clob Instrument at all: every byte one the checker chooses */
static void any_clob_instrument(ClobInstrument *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->market_model_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_traded_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = arbitrary(); }
  record->closing_price_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->adjusted_closing_price[i] = arbitrary(); }
  record->adjusted_closing_price_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->pct_change[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->no_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_value_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trade_date[i] = arbitrary(); }
}

/* Clob Instrument to the wire: 119 bytes from at, returning where the next byte goes */
static size_t encode_clob_instrument(const ClobInstrument *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->market_model_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_traded_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price[i]; }
  wire[at++] = record->closing_price_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->adjusted_closing_price[i]; }
  wire[at++] = record->adjusted_closing_price_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pct_change[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->no_trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_value_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_trading_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trade_date[i]; }

  return at;
}

/* Clob Instrument off the wire: 119 bytes from at, returning where the next byte lies */
static size_t decode_clob_instrument(ClobInstrument *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->market_model_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_traded_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = wire[at++]; }
  record->closing_price_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->adjusted_closing_price[i] = wire[at++]; }
  record->adjusted_closing_price_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->pct_change[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->no_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_value_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trade_date[i] = wire[at++]; }

  return at;
}

/* what was read of Clob Instrument is what was written, byte for byte */
static void equal_clob_instrument(const ClobInstrument *read, const ClobInstrument *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->market_model_type == written->market_model_type);
  for (size_t i = 0; i < 8; i++) { assert(read->last_traded_price[i] == written->last_traded_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  assert(read->closing_price_type == written->closing_price_type);
  for (size_t i = 0; i < 8; i++) { assert(read->adjusted_closing_price[i] == written->adjusted_closing_price[i]); }
  assert(read->adjusted_closing_price_reason == written->adjusted_closing_price_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->pct_change[i] == written->pct_change[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap[i] == written->vwap[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->no_trades[i] == written->no_trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_value[i] == written->total_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_price[i] == written->max_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_price[i] == written->min_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_value_price[i] == written->settlement_value_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_trading_date[i] == written->end_trading_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trade_date[i] == written->last_trade_date[i]); }
}

/* Clob Instrument: written and read back, then read and written back */
static void check_clob_instrument(void) {
  ClobInstrument sent;
  ClobInstrument got;
  uint8_t wire[119];
  uint8_t again[119];

  any_clob_instrument(&sent);
  assert(encode_clob_instrument(&sent, wire, 0) == 119);
  assert(decode_clob_instrument(&got, wire, 0) == 119);
  equal_clob_instrument(&got, &sent);

  for (size_t i = 0; i < 119; i++) { wire[i] = arbitrary(); }
  assert(decode_clob_instrument(&got, wire, 0) == 119);
  assert(encode_clob_instrument(&got, again, 0) == 119);
  for (size_t i = 0; i < 119; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cross Instrument: 119 bytes --------------------------------------------- */

/* SingleInstrumentSummary */
typedef struct {
  uint8_t instrument_id[4];               /* bytes 0 to 3 */
  uint8_t market_model_type;              /* byte 4 */
  uint8_t last_traded_price[8];           /* bytes 5 to 12 */
  uint8_t closing_price[8];               /* bytes 13 to 20 */
  uint8_t closing_price_type;             /* byte 21 */
  uint8_t adjusted_closing_price[8];      /* bytes 22 to 29 */
  uint8_t adjusted_closing_price_reason;  /* byte 30 */
  uint8_t pct_change[8];                  /* bytes 31 to 38 */
  uint8_t vwap[8];                        /* bytes 39 to 46 */
  uint8_t no_trades[8];                   /* bytes 47 to 54 */
  uint8_t total_volume[8];                /* bytes 55 to 62 */
  uint8_t total_value[8];                 /* bytes 63 to 70 */
  uint8_t opening_price[8];               /* bytes 71 to 78 */
  uint8_t max_price[8];                   /* bytes 79 to 86 */
  uint8_t min_price[8];                   /* bytes 87 to 94 */
  uint8_t settlement_price[8];            /* bytes 95 to 102 */
  uint8_t settlement_value_price[8];      /* bytes 103 to 110 */
  uint8_t end_trading_date[4];            /* bytes 111 to 114 */
  uint8_t last_trade_date[4];             /* bytes 115 to 118 */
} CrossInstrument;

/* any Cross Instrument at all: every byte one the checker chooses */
static void any_cross_instrument(CrossInstrument *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->market_model_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_traded_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = arbitrary(); }
  record->closing_price_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->adjusted_closing_price[i] = arbitrary(); }
  record->adjusted_closing_price_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->pct_change[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->no_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_value_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trade_date[i] = arbitrary(); }
}

/* Cross Instrument to the wire: 119 bytes from at, returning where the next byte goes */
static size_t encode_cross_instrument(const CrossInstrument *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->market_model_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_traded_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price[i]; }
  wire[at++] = record->closing_price_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->adjusted_closing_price[i]; }
  wire[at++] = record->adjusted_closing_price_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pct_change[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->no_trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_value_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_trading_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trade_date[i]; }

  return at;
}

/* Cross Instrument off the wire: 119 bytes from at, returning where the next byte lies */
static size_t decode_cross_instrument(CrossInstrument *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->market_model_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_traded_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = wire[at++]; }
  record->closing_price_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->adjusted_closing_price[i] = wire[at++]; }
  record->adjusted_closing_price_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->pct_change[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->no_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_value_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trade_date[i] = wire[at++]; }

  return at;
}

/* what was read of Cross Instrument is what was written, byte for byte */
static void equal_cross_instrument(const CrossInstrument *read, const CrossInstrument *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->market_model_type == written->market_model_type);
  for (size_t i = 0; i < 8; i++) { assert(read->last_traded_price[i] == written->last_traded_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  assert(read->closing_price_type == written->closing_price_type);
  for (size_t i = 0; i < 8; i++) { assert(read->adjusted_closing_price[i] == written->adjusted_closing_price[i]); }
  assert(read->adjusted_closing_price_reason == written->adjusted_closing_price_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->pct_change[i] == written->pct_change[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap[i] == written->vwap[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->no_trades[i] == written->no_trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_value[i] == written->total_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_price[i] == written->max_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_price[i] == written->min_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_value_price[i] == written->settlement_value_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_trading_date[i] == written->end_trading_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trade_date[i] == written->last_trade_date[i]); }
}

/* Cross Instrument: written and read back, then read and written back */
static void check_cross_instrument(void) {
  CrossInstrument sent;
  CrossInstrument got;
  uint8_t wire[119];
  uint8_t again[119];

  any_cross_instrument(&sent);
  assert(encode_cross_instrument(&sent, wire, 0) == 119);
  assert(decode_cross_instrument(&got, wire, 0) == 119);
  equal_cross_instrument(&got, &sent);

  for (size_t i = 0; i < 119; i++) { wire[i] = arbitrary(); }
  assert(decode_cross_instrument(&got, wire, 0) == 119);
  assert(encode_cross_instrument(&got, again, 0) == 119);
  for (size_t i = 0; i < 119; i++) { assert(again[i] == wire[i]); }
}

/* ---- Block Instrument: 119 bytes --------------------------------------------- */

/* SingleInstrumentSummary */
typedef struct {
  uint8_t instrument_id[4];               /* bytes 0 to 3 */
  uint8_t market_model_type;              /* byte 4 */
  uint8_t last_traded_price[8];           /* bytes 5 to 12 */
  uint8_t closing_price[8];               /* bytes 13 to 20 */
  uint8_t closing_price_type;             /* byte 21 */
  uint8_t adjusted_closing_price[8];      /* bytes 22 to 29 */
  uint8_t adjusted_closing_price_reason;  /* byte 30 */
  uint8_t pct_change[8];                  /* bytes 31 to 38 */
  uint8_t vwap[8];                        /* bytes 39 to 46 */
  uint8_t no_trades[8];                   /* bytes 47 to 54 */
  uint8_t total_volume[8];                /* bytes 55 to 62 */
  uint8_t total_value[8];                 /* bytes 63 to 70 */
  uint8_t opening_price[8];               /* bytes 71 to 78 */
  uint8_t max_price[8];                   /* bytes 79 to 86 */
  uint8_t min_price[8];                   /* bytes 87 to 94 */
  uint8_t settlement_price[8];            /* bytes 95 to 102 */
  uint8_t settlement_value_price[8];      /* bytes 103 to 110 */
  uint8_t end_trading_date[4];            /* bytes 111 to 114 */
  uint8_t last_trade_date[4];             /* bytes 115 to 118 */
} BlockInstrument;

/* any Block Instrument at all: every byte one the checker chooses */
static void any_block_instrument(BlockInstrument *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->market_model_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_traded_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = arbitrary(); }
  record->closing_price_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->adjusted_closing_price[i] = arbitrary(); }
  record->adjusted_closing_price_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->pct_change[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->no_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_value_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trade_date[i] = arbitrary(); }
}

/* Block Instrument to the wire: 119 bytes from at, returning where the next byte goes */
static size_t encode_block_instrument(const BlockInstrument *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->market_model_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_traded_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price[i]; }
  wire[at++] = record->closing_price_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->adjusted_closing_price[i]; }
  wire[at++] = record->adjusted_closing_price_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pct_change[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->no_trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_value_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_trading_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trade_date[i]; }

  return at;
}

/* Block Instrument off the wire: 119 bytes from at, returning where the next byte lies */
static size_t decode_block_instrument(BlockInstrument *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->market_model_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_traded_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = wire[at++]; }
  record->closing_price_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->adjusted_closing_price[i] = wire[at++]; }
  record->adjusted_closing_price_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->pct_change[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->no_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_value_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trade_date[i] = wire[at++]; }

  return at;
}

/* what was read of Block Instrument is what was written, byte for byte */
static void equal_block_instrument(const BlockInstrument *read, const BlockInstrument *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->market_model_type == written->market_model_type);
  for (size_t i = 0; i < 8; i++) { assert(read->last_traded_price[i] == written->last_traded_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  assert(read->closing_price_type == written->closing_price_type);
  for (size_t i = 0; i < 8; i++) { assert(read->adjusted_closing_price[i] == written->adjusted_closing_price[i]); }
  assert(read->adjusted_closing_price_reason == written->adjusted_closing_price_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->pct_change[i] == written->pct_change[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap[i] == written->vwap[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->no_trades[i] == written->no_trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_value[i] == written->total_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_price[i] == written->max_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_price[i] == written->min_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_value_price[i] == written->settlement_value_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_trading_date[i] == written->end_trading_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trade_date[i] == written->last_trade_date[i]); }
}

/* Block Instrument: written and read back, then read and written back */
static void check_block_instrument(void) {
  BlockInstrument sent;
  BlockInstrument got;
  uint8_t wire[119];
  uint8_t again[119];

  any_block_instrument(&sent);
  assert(encode_block_instrument(&sent, wire, 0) == 119);
  assert(decode_block_instrument(&got, wire, 0) == 119);
  equal_block_instrument(&got, &sent);

  for (size_t i = 0; i < 119; i++) { wire[i] = arbitrary(); }
  assert(decode_block_instrument(&got, wire, 0) == 119);
  assert(encode_block_instrument(&got, again, 0) == 119);
  for (size_t i = 0; i < 119; i++) { assert(again[i] == wire[i]); }
}

/* ---- Hybrid Instrument: 119 bytes -------------------------------------------- */

/* SingleInstrumentSummary */
typedef struct {
  uint8_t instrument_id[4];               /* bytes 0 to 3 */
  uint8_t market_model_type;              /* byte 4 */
  uint8_t last_traded_price[8];           /* bytes 5 to 12 */
  uint8_t closing_price[8];               /* bytes 13 to 20 */
  uint8_t closing_price_type;             /* byte 21 */
  uint8_t adjusted_closing_price[8];      /* bytes 22 to 29 */
  uint8_t adjusted_closing_price_reason;  /* byte 30 */
  uint8_t pct_change[8];                  /* bytes 31 to 38 */
  uint8_t vwap[8];                        /* bytes 39 to 46 */
  uint8_t no_trades[8];                   /* bytes 47 to 54 */
  uint8_t total_volume[8];                /* bytes 55 to 62 */
  uint8_t total_value[8];                 /* bytes 63 to 70 */
  uint8_t opening_price[8];               /* bytes 71 to 78 */
  uint8_t max_price[8];                   /* bytes 79 to 86 */
  uint8_t min_price[8];                   /* bytes 87 to 94 */
  uint8_t settlement_price[8];            /* bytes 95 to 102 */
  uint8_t settlement_value_price[8];      /* bytes 103 to 110 */
  uint8_t end_trading_date[4];            /* bytes 111 to 114 */
  uint8_t last_trade_date[4];             /* bytes 115 to 118 */
} HybridInstrument;

/* any Hybrid Instrument at all: every byte one the checker chooses */
static void any_hybrid_instrument(HybridInstrument *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->market_model_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_traded_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = arbitrary(); }
  record->closing_price_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->adjusted_closing_price[i] = arbitrary(); }
  record->adjusted_closing_price_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->pct_change[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->no_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_value_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trade_date[i] = arbitrary(); }
}

/* Hybrid Instrument to the wire: 119 bytes from at, returning where the next byte goes */
static size_t encode_hybrid_instrument(const HybridInstrument *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->market_model_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_traded_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price[i]; }
  wire[at++] = record->closing_price_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->adjusted_closing_price[i]; }
  wire[at++] = record->adjusted_closing_price_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pct_change[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->no_trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_value_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_trading_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trade_date[i]; }

  return at;
}

/* Hybrid Instrument off the wire: 119 bytes from at, returning where the next byte lies */
static size_t decode_hybrid_instrument(HybridInstrument *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->market_model_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_traded_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = wire[at++]; }
  record->closing_price_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->adjusted_closing_price[i] = wire[at++]; }
  record->adjusted_closing_price_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->pct_change[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->no_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_value_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trade_date[i] = wire[at++]; }

  return at;
}

/* what was read of Hybrid Instrument is what was written, byte for byte */
static void equal_hybrid_instrument(const HybridInstrument *read, const HybridInstrument *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->market_model_type == written->market_model_type);
  for (size_t i = 0; i < 8; i++) { assert(read->last_traded_price[i] == written->last_traded_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  assert(read->closing_price_type == written->closing_price_type);
  for (size_t i = 0; i < 8; i++) { assert(read->adjusted_closing_price[i] == written->adjusted_closing_price[i]); }
  assert(read->adjusted_closing_price_reason == written->adjusted_closing_price_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->pct_change[i] == written->pct_change[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap[i] == written->vwap[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->no_trades[i] == written->no_trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_value[i] == written->total_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_price[i] == written->max_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_price[i] == written->min_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_value_price[i] == written->settlement_value_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_trading_date[i] == written->end_trading_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trade_date[i] == written->last_trade_date[i]); }
}

/* Hybrid Instrument: written and read back, then read and written back */
static void check_hybrid_instrument(void) {
  HybridInstrument sent;
  HybridInstrument got;
  uint8_t wire[119];
  uint8_t again[119];

  any_hybrid_instrument(&sent);
  assert(encode_hybrid_instrument(&sent, wire, 0) == 119);
  assert(decode_hybrid_instrument(&got, wire, 0) == 119);
  equal_hybrid_instrument(&got, &sent);

  for (size_t i = 0; i < 119; i++) { wire[i] = arbitrary(); }
  assert(decode_hybrid_instrument(&got, wire, 0) == 119);
  assert(encode_hybrid_instrument(&got, again, 0) == 119);
  for (size_t i = 0; i < 119; i++) { assert(again[i] == wire[i]); }
}

/* ---- Product Summary: 629 bytes ---------------------------------------------- */

/* Session day product summary */
typedef struct {
  ClobInstrument clob_instrument;                             /* bytes 0 to 118 */
  CrossInstrument cross_instrument;                           /* bytes 119 to 237 */
  BlockInstrument block_instrument;                           /* bytes 238 to 356 */
  HybridInstrument hybrid_instrument;                         /* bytes 357 to 475 */
  uint8_t product_identification_type;                        /* byte 476 */
  uint8_t product_identification_product_identification[30];  /* bytes 477 to 506 */
  uint8_t product_id[4];                                      /* bytes 507 to 510 */
  uint8_t mic[4];                                             /* bytes 511 to 514 */
  uint8_t accumulated_interest[8];                            /* bytes 515 to 522 */
  uint8_t interest_rate[8];                                   /* bytes 523 to 530 */
  uint8_t currency[2];                                        /* bytes 531 to 532 */
  uint8_t session_date[4];                                    /* bytes 533 to 536 */
  uint8_t trading_value_currency[8];                          /* bytes 537 to 544 */
  uint8_t status;                                             /* byte 545 */
  uint8_t sector[2];                                          /* bytes 546 to 547 */
  uint8_t market;                                             /* byte 548 */
  uint8_t marker_price_change;                                /* byte 549 */
  uint8_t lower_liquidity;                                    /* byte 550 */
  uint8_t multiplier_number[8];                               /* bytes 551 to 558 */
  uint8_t dividend_rate[8];                                   /* bytes 559 to 566 */
  uint8_t delta[8];                                           /* bytes 567 to 574 */
  uint8_t gamma[8];                                           /* bytes 575 to 582 */
  uint8_t rho[8];                                             /* bytes 583 to 590 */
  uint8_t theta[8];                                           /* bytes 591 to 598 */
  uint8_t vega[8];                                            /* bytes 599 to 606 */
  uint8_t volatility[8];                                      /* bytes 607 to 614 */
  uint8_t options_strike_price[8];                            /* bytes 615 to 622 */
  uint8_t dividend;                                           /* byte 623 */
  uint8_t subscription_right;                                 /* byte 624 */
  uint8_t interim_dividend_right;                             /* byte 625 */
  uint8_t split;                                              /* byte 626 */
  uint8_t quotation_system;                                   /* byte 627 */
  uint8_t liquidity_support_pge;                              /* byte 628 */
} ProductSummary;

/* any Product Summary at all: every byte one the checker chooses */
static void any_product_summary(ProductSummary *record) {
  any_clob_instrument(&record->clob_instrument);
  any_cross_instrument(&record->cross_instrument);
  any_block_instrument(&record->block_instrument);
  any_hybrid_instrument(&record->hybrid_instrument);
  record->product_identification_type = arbitrary();
  for (size_t i = 0; i < 30; i++) { record->product_identification_product_identification[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accumulated_interest[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->interest_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_value_currency[i] = arbitrary(); }
  record->status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->sector[i] = arbitrary(); }
  record->market = arbitrary();
  record->marker_price_change = arbitrary();
  record->lower_liquidity = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->multiplier_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->dividend_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->delta[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->gamma[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->rho[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->theta[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vega[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->options_strike_price[i] = arbitrary(); }
  record->dividend = arbitrary();
  record->subscription_right = arbitrary();
  record->interim_dividend_right = arbitrary();
  record->split = arbitrary();
  record->quotation_system = arbitrary();
  record->liquidity_support_pge = arbitrary();
}

/* Product Summary to the wire: 629 bytes from at, returning where the next byte goes */
static size_t encode_product_summary(const ProductSummary *record, uint8_t *wire, size_t at) {
  at = encode_clob_instrument(&record->clob_instrument, wire, at);
  at = encode_cross_instrument(&record->cross_instrument, wire, at);
  at = encode_block_instrument(&record->block_instrument, wire, at);
  at = encode_hybrid_instrument(&record->hybrid_instrument, wire, at);
  wire[at++] = record->product_identification_type;
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->product_identification_product_identification[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mic[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accumulated_interest[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->interest_rate[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_value_currency[i]; }
  wire[at++] = record->status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sector[i]; }
  wire[at++] = record->market;
  wire[at++] = record->marker_price_change;
  wire[at++] = record->lower_liquidity;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->multiplier_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->dividend_rate[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->delta[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->gamma[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->rho[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->theta[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vega[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->options_strike_price[i]; }
  wire[at++] = record->dividend;
  wire[at++] = record->subscription_right;
  wire[at++] = record->interim_dividend_right;
  wire[at++] = record->split;
  wire[at++] = record->quotation_system;
  wire[at++] = record->liquidity_support_pge;

  return at;
}

/* Product Summary off the wire: 629 bytes from at, returning where the next byte lies */
static size_t decode_product_summary(ProductSummary *record, const uint8_t *wire, size_t at) {
  at = decode_clob_instrument(&record->clob_instrument, wire, at);
  at = decode_cross_instrument(&record->cross_instrument, wire, at);
  at = decode_block_instrument(&record->block_instrument, wire, at);
  at = decode_hybrid_instrument(&record->hybrid_instrument, wire, at);
  record->product_identification_type = wire[at++];
  for (size_t i = 0; i < 30; i++) { record->product_identification_product_identification[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accumulated_interest[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->interest_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_value_currency[i] = wire[at++]; }
  record->status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->sector[i] = wire[at++]; }
  record->market = wire[at++];
  record->marker_price_change = wire[at++];
  record->lower_liquidity = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->multiplier_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->dividend_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->delta[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->gamma[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->rho[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->theta[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vega[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->options_strike_price[i] = wire[at++]; }
  record->dividend = wire[at++];
  record->subscription_right = wire[at++];
  record->interim_dividend_right = wire[at++];
  record->split = wire[at++];
  record->quotation_system = wire[at++];
  record->liquidity_support_pge = wire[at++];

  return at;
}

/* what was read of Product Summary is what was written, byte for byte */
static void equal_product_summary(const ProductSummary *read, const ProductSummary *written) {
  equal_clob_instrument(&read->clob_instrument, &written->clob_instrument);
  equal_cross_instrument(&read->cross_instrument, &written->cross_instrument);
  equal_block_instrument(&read->block_instrument, &written->block_instrument);
  equal_hybrid_instrument(&read->hybrid_instrument, &written->hybrid_instrument);
  assert(read->product_identification_type == written->product_identification_type);
  for (size_t i = 0; i < 30; i++) { assert(read->product_identification_product_identification[i] == written->product_identification_product_identification[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mic[i] == written->mic[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accumulated_interest[i] == written->accumulated_interest[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->interest_rate[i] == written->interest_rate[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_date[i] == written->session_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_value_currency[i] == written->trading_value_currency[i]); }
  assert(read->status == written->status);
  for (size_t i = 0; i < 2; i++) { assert(read->sector[i] == written->sector[i]); }
  assert(read->market == written->market);
  assert(read->marker_price_change == written->marker_price_change);
  assert(read->lower_liquidity == written->lower_liquidity);
  for (size_t i = 0; i < 8; i++) { assert(read->multiplier_number[i] == written->multiplier_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->dividend_rate[i] == written->dividend_rate[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->delta[i] == written->delta[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->gamma[i] == written->gamma[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->rho[i] == written->rho[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->theta[i] == written->theta[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vega[i] == written->vega[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->options_strike_price[i] == written->options_strike_price[i]); }
  assert(read->dividend == written->dividend);
  assert(read->subscription_right == written->subscription_right);
  assert(read->interim_dividend_right == written->interim_dividend_right);
  assert(read->split == written->split);
  assert(read->quotation_system == written->quotation_system);
  assert(read->liquidity_support_pge == written->liquidity_support_pge);
}

/* Product Summary: written and read back, then read and written back */
static void check_product_summary(void) {
  ProductSummary sent;
  ProductSummary got;
  uint8_t wire[629];
  uint8_t again[629];

  any_product_summary(&sent);
  assert(encode_product_summary(&sent, wire, 0) == 629);
  assert(decode_product_summary(&got, wire, 0) == 629);
  equal_product_summary(&got, &sent);

  for (size_t i = 0; i < 629; i++) { wire[i] = arbitrary(); }
  assert(decode_product_summary(&got, wire, 0) == 629);
  assert(encode_product_summary(&got, again, 0) == 629);
  for (size_t i = 0; i < 629; i++) { assert(again[i] == wire[i]); }
}

/* ---- News: 890 bytes --------------------------------------------------------- */

/* News message */
typedef struct {
  uint8_t market_structure_id[4];  /* bytes 0 to 3 */
  uint8_t news_id[4];              /* bytes 4 to 7 */
  uint8_t title[80];               /* bytes 8 to 87 */
  uint8_t entry_number;            /* byte 88 */
  uint8_t total;                   /* byte 89 */
  uint8_t text[800];               /* bytes 90 to 889 */
} News;

/* any News at all: every byte one the checker chooses */
static void any_news(News *record) {
  for (size_t i = 0; i < 4; i++) { record->market_structure_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->news_id[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->title[i] = arbitrary(); }
  record->entry_number = arbitrary();
  record->total = arbitrary();
  for (size_t i = 0; i < 800; i++) { record->text[i] = arbitrary(); }
}

/* News to the wire: 890 bytes from at, returning where the next byte goes */
static size_t encode_news(const News *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_structure_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->news_id[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->title[i]; }
  wire[at++] = record->entry_number;
  wire[at++] = record->total;
  for (size_t i = 0; i < 800; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* News off the wire: 890 bytes from at, returning where the next byte lies */
static size_t decode_news(News *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_structure_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->news_id[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->title[i] = wire[at++]; }
  record->entry_number = wire[at++];
  record->total = wire[at++];
  for (size_t i = 0; i < 800; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of News is what was written, byte for byte */
static void equal_news(const News *read, const News *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_structure_id[i] == written->market_structure_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->news_id[i] == written->news_id[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->title[i] == written->title[i]); }
  assert(read->entry_number == written->entry_number);
  assert(read->total == written->total);
  for (size_t i = 0; i < 800; i++) { assert(read->text[i] == written->text[i]); }
}

/* News: written and read back, then read and written back */
static void check_news(void) {
  News sent;
  News got;
  uint8_t wire[890];
  uint8_t again[890];

  any_news(&sent);
  assert(encode_news(&sent, wire, 0) == 890);
  assert(decode_news(&got, wire, 0) == 890);
  equal_news(&got, &sent);

  for (size_t i = 0; i < 890; i++) { wire[i] = arbitrary(); }
  assert(decode_news(&got, wire, 0) == 890);
  assert(encode_news(&got, again, 0) == 890);
  for (size_t i = 0; i < 890; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Session Status: 13 bytes ---------------------------------------- */

/* The Trading Session Status provides information on the status of a market and on a trading day events */
typedef struct {
  uint8_t market_id[4];            /* bytes 0 to 3 */
  uint8_t market_structure_id[4];  /* bytes 4 to 7 */
  uint8_t trading_session_event;   /* byte 8 */
  uint8_t date[4];                 /* bytes 9 to 12 */
} TradingSessionStatus;

/* any Trading Session Status at all: every byte one the checker chooses */
static void any_trading_session_status(TradingSessionStatus *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_structure_id[i] = arbitrary(); }
  record->trading_session_event = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->date[i] = arbitrary(); }
}

/* Trading Session Status to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_trading_session_status(const TradingSessionStatus *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_structure_id[i]; }
  wire[at++] = record->trading_session_event;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->date[i]; }

  return at;
}

/* Trading Session Status off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_trading_session_status(TradingSessionStatus *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_structure_id[i] = wire[at++]; }
  record->trading_session_event = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->date[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Session Status is what was written, byte for byte */
static void equal_trading_session_status(const TradingSessionStatus *read, const TradingSessionStatus *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_structure_id[i] == written->market_structure_id[i]); }
  assert(read->trading_session_event == written->trading_session_event);
  for (size_t i = 0; i < 4; i++) { assert(read->date[i] == written->date[i]); }
}

/* Trading Session Status: written and read back, then read and written back */
static void check_trading_session_status(void) {
  TradingSessionStatus sent;
  TradingSessionStatus got;
  uint8_t wire[13];
  uint8_t again[13];

  any_trading_session_status(&sent);
  assert(encode_trading_session_status(&sent, wire, 0) == 13);
  assert(decode_trading_session_status(&got, wire, 0) == 13);
  equal_trading_session_status(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_session_status(&got, wire, 0) == 13);
  assert(encode_trading_session_status(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Test Event: 201 bytes --------------------------------------------------- */

/* Test event */
typedef struct {
  uint8_t scenario_name[200];  /* bytes 0 to 199 */
  uint8_t event_type;          /* byte 200 */
} TestEvent;

/* any Test Event at all: every byte one the checker chooses */
static void any_test_event(TestEvent *record) {
  for (size_t i = 0; i < 200; i++) { record->scenario_name[i] = arbitrary(); }
  record->event_type = arbitrary();
}

/* Test Event to the wire: 201 bytes from at, returning where the next byte goes */
static size_t encode_test_event(const TestEvent *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 200; i++) { wire[at++] = record->scenario_name[i]; }
  wire[at++] = record->event_type;

  return at;
}

/* Test Event off the wire: 201 bytes from at, returning where the next byte lies */
static size_t decode_test_event(TestEvent *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 200; i++) { record->scenario_name[i] = wire[at++]; }
  record->event_type = wire[at++];

  return at;
}

/* what was read of Test Event is what was written, byte for byte */
static void equal_test_event(const TestEvent *read, const TestEvent *written) {
  for (size_t i = 0; i < 200; i++) { assert(read->scenario_name[i] == written->scenario_name[i]); }
  assert(read->event_type == written->event_type);
}

/* Test Event: written and read back, then read and written back */
static void check_test_event(void) {
  TestEvent sent;
  TestEvent got;
  uint8_t wire[201];
  uint8_t again[201];

  any_test_event(&sent);
  assert(encode_test_event(&sent, wire, 0) == 201);
  assert(decode_test_event(&got, wire, 0) == 201);
  equal_test_event(&got, &sent);

  for (size_t i = 0; i < 201; i++) { wire[i] = arbitrary(); }
  assert(decode_test_event(&got, wire, 0) == 201);
  assert(encode_test_event(&got, again, 0) == 201);
  for (size_t i = 0; i < 201; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Response: 1 byte -------------------------------------------------- */

/* Response to a Login message */
typedef struct {
  uint8_t result;  /* byte 0 */
} LoginResponse;

/* any Login Response at all: every byte one the checker chooses */
static void any_login_response(LoginResponse *record) {
  record->result = arbitrary();
}

/* Login Response to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_login_response(const LoginResponse *record, uint8_t *wire, size_t at) {
  wire[at++] = record->result;

  return at;
}

/* Login Response off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_login_response(LoginResponse *record, const uint8_t *wire, size_t at) {
  record->result = wire[at++];

  return at;
}

/* what was read of Login Response is what was written, byte for byte */
static void equal_login_response(const LoginResponse *read, const LoginResponse *written) {
  assert(read->result == written->result);
}

/* Login Response: written and read back, then read and written back */
static void check_login_response(void) {
  LoginResponse sent;
  LoginResponse got;
  uint8_t wire[1];
  uint8_t again[1];

  any_login_response(&sent);
  assert(encode_login_response(&sent, wire, 0) == 1);
  assert(decode_login_response(&got, wire, 0) == 1);
  equal_login_response(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_login_response(&got, wire, 0) == 1);
  assert(encode_login_response(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Snapshot: 4 bytes ------------------------------------------------ */

/* Marks the end of a snapshot */
typedef struct {
  uint8_t last_seq_num[4];  /* bytes 0 to 3 */
} EndOfSnapshot;

/* any End Of Snapshot at all: every byte one the checker chooses */
static void any_end_of_snapshot(EndOfSnapshot *record) {
  for (size_t i = 0; i < 4; i++) { record->last_seq_num[i] = arbitrary(); }
}

/* End Of Snapshot to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_end_of_snapshot(const EndOfSnapshot *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_seq_num[i]; }

  return at;
}

/* End Of Snapshot off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_end_of_snapshot(EndOfSnapshot *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Snapshot is what was written, byte for byte */
static void equal_end_of_snapshot(const EndOfSnapshot *read, const EndOfSnapshot *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_seq_num[i] == written->last_seq_num[i]); }
}

/* End Of Snapshot: written and read back, then read and written back */
static void check_end_of_snapshot(void) {
  EndOfSnapshot sent;
  EndOfSnapshot got;
  uint8_t wire[4];
  uint8_t again[4];

  any_end_of_snapshot(&sent);
  assert(encode_end_of_snapshot(&sent, wire, 0) == 4);
  assert(decode_end_of_snapshot(&got, wire, 0) == 4);
  equal_end_of_snapshot(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_snapshot(&got, wire, 0) == 4);
  assert(encode_end_of_snapshot(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_calendar_exception();
  check_tick_table_entry();
  check_collar_table_entry();
  check_trading_phase_schedule_entry();
  check_market_structure();
  check_collar_group();
  check_external_underlying();
  check_instrument();
  check_accrued_interest_table_entry();
  check_indexation_table_entry();
  check_product_identification_public_product_identification();
  check_index_underlying();
  check_public_product_identification();
  check_auction_summary();
  check_auction_update();
  check_price_level();
  check_top_price_level_update();
  check_trade();
  check_position_report();
  check_instrument_status_change();
  check_order_collars();
  check_trade_collars();
  check_instrument_summary();
  check_clob_instrument();
  check_cross_instrument();
  check_block_instrument();
  check_hybrid_instrument();
  check_product_summary();
  check_news();
  check_trading_session_status();
  check_test_event();
  check_login_response();
  check_end_of_snapshot();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
