// cnsx/cse2/multicast/Cse2_Multicast_v1_6.c
/*
 * Canadian Securities Exchange CSE2 Multicast Market Data Feed
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

/* ---- Block Header: 7 bytes --------------------------------------------------- */

/* Prefix of a block of messages, carrying the unique information to identify and route them */
typedef struct {
  uint8_t block_length[2];           /* bytes 0 to 1 */
  uint8_t block_number_of_messages;  /* byte 2 */
  uint8_t block_start_sequence[4];   /* bytes 3 to 6 */
} BlockHeader;

/* any Block Header at all: every byte one the checker chooses */
static void any_block_header(BlockHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  record->block_number_of_messages = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->block_start_sequence[i] = arbitrary(); }
}

/* Block Header to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_block_header(const BlockHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  wire[at++] = record->block_number_of_messages;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->block_start_sequence[i]; }

  return at;
}

/* Block Header off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_block_header(BlockHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  record->block_number_of_messages = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->block_start_sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Block Header is what was written, byte for byte */
static void equal_block_header(const BlockHeader *read, const BlockHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  assert(read->block_number_of_messages == written->block_number_of_messages);
  for (size_t i = 0; i < 4; i++) { assert(read->block_start_sequence[i] == written->block_start_sequence[i]); }
}

/* Block Header: written and read back, then read and written back */
static void check_block_header(void) {
  BlockHeader sent;
  BlockHeader got;
  uint8_t wire[7];
  uint8_t again[7];

  any_block_header(&sent);
  assert(encode_block_header(&sent, wire, 0) == 7);
  assert(decode_block_header(&got, wire, 0) == 7);
  equal_block_header(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_block_header(&got, wire, 0) == 7);
  assert(encode_block_header(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 2 bytes ------------------------------------------------- */

/* Two byte sub header prefixing every message, carrying its length and its type */
typedef struct {
  uint8_t sub_length;    /* byte 0 */
  uint8_t message_type;  /* byte 1 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->sub_length = arbitrary();
  record->message_type = arbitrary();
}

/* Message Header to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->sub_length;
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->sub_length = wire[at++];
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->sub_length == written->sub_length);
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[2];
  uint8_t again[2];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 2);
  assert(decode_message_header(&got, wire, 0) == 2);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 2);
  assert(encode_message_header(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Time Message: 6 bytes --------------------------------------------------- */

/* Anchors the feed clock. Every following message states its own time as nanoseconds elapsed since this message. */
typedef struct {
  uint8_t second[4];       /* bytes 0 to 3 */
  uint8_t millisecond[2];  /* bytes 4 to 5 */
} TimeMessage;

/* any Time Message at all: every byte one the checker chooses */
static void any_time_message(TimeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->millisecond[i] = arbitrary(); }
}

/* Time Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_time_message(const TimeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->second[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->millisecond[i]; }

  return at;
}

/* Time Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_time_message(TimeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->millisecond[i] = wire[at++]; }

  return at;
}

/* what was read of Time Message is what was written, byte for byte */
static void equal_time_message(const TimeMessage *read, const TimeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->second[i] == written->second[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->millisecond[i] == written->millisecond[i]); }
}

/* Time Message: written and read back, then read and written back */
static void check_time_message(void) {
  TimeMessage sent;
  TimeMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_time_message(&sent);
  assert(encode_time_message(&sent, wire, 0) == 6);
  assert(decode_time_message(&got, wire, 0) == 6);
  equal_time_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_time_message(&got, wire, 0) == 6);
  assert(encode_time_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 21 bytes ------------------------------------------ */

/* Signals a market or data feed handler event, either for the system as a whole or for one symbol group. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t group[8];               /* bytes 4 to 11 */
  uint8_t event_code;             /* byte 12 */
  uint8_t exchange_timestamp[8];  /* bytes 13 to 20 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->group[i] = arbitrary(); }
  record->event_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = arbitrary(); }
}

/* System Event Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->group[i]; }
  wire[at++] = record->event_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exchange_timestamp[i]; }

  return at;
}

/* System Event Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->group[i] = wire[at++]; }
  record->event_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->group[i] == written->group[i]); }
  assert(read->event_code == written->event_code);
  for (size_t i = 0; i < 8; i++) { assert(read->exchange_timestamp[i] == written->exchange_timestamp[i]); }
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 21);
  assert(decode_system_event_message(&got, wire, 0) == 21);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 21);
  assert(encode_system_event_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Directory Message: 195 bytes ------------------------------------- */

/* Static properties of a symbol. Sent for every symbol in the morning, and again during the day if a symbol changes. */
typedef struct {
  uint8_t time_offset[4];                 /* bytes 0 to 3 */
  uint8_t symbol[12];                     /* bytes 4 to 15 */
  uint8_t cusip[12];                      /* bytes 16 to 27 */
  uint8_t sec_name[15];                   /* bytes 28 to 42 */
  uint8_t currency[3];                    /* bytes 43 to 45 */
  uint8_t stock_group[8];                 /* bytes 46 to 53 */
  uint8_t listing[8];                     /* bytes 54 to 61 */
  uint8_t expiry[8];                      /* bytes 62 to 69 */
  uint8_t lot_size[4];                    /* bytes 70 to 73 */
  uint8_t settlement_term[8];             /* bytes 74 to 81 */
  uint8_t listing_market;                 /* byte 82 */
  uint8_t previous_closing_price[4];      /* bytes 83 to 86 */
  uint8_t listing_tier;                   /* byte 87 */
  uint8_t market_maker_name[20];          /* bytes 88 to 107 */
  uint8_t market_maker_phone_number[12];  /* bytes 108 to 119 */
  uint8_t full_sec_name[75];              /* bytes 120 to 194 */
} SymbolDirectoryMessage;

/* any Symbol Directory Message at all: every byte one the checker chooses */
static void any_symbol_directory_message(SymbolDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->cusip[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->sec_name[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock_group[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->listing[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expiry[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_term[i] = arbitrary(); }
  record->listing_market = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->previous_closing_price[i] = arbitrary(); }
  record->listing_tier = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->market_maker_name[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->market_maker_phone_number[i] = arbitrary(); }
  for (size_t i = 0; i < 75; i++) { record->full_sec_name[i] = arbitrary(); }
}

/* Symbol Directory Message to the wire: 195 bytes from at, returning where the next byte goes */
static size_t encode_symbol_directory_message(const SymbolDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->cusip[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->sec_name[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_group[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->listing[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expiry[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lot_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_term[i]; }
  wire[at++] = record->listing_market;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_closing_price[i]; }
  wire[at++] = record->listing_tier;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->market_maker_name[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->market_maker_phone_number[i]; }
  for (size_t i = 0; i < 75; i++) { wire[at++] = record->full_sec_name[i]; }

  return at;
}

/* Symbol Directory Message off the wire: 195 bytes from at, returning where the next byte lies */
static size_t decode_symbol_directory_message(SymbolDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->cusip[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->sec_name[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock_group[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->listing[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expiry[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_term[i] = wire[at++]; }
  record->listing_market = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->previous_closing_price[i] = wire[at++]; }
  record->listing_tier = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->market_maker_name[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->market_maker_phone_number[i] = wire[at++]; }
  for (size_t i = 0; i < 75; i++) { record->full_sec_name[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Directory Message is what was written, byte for byte */
static void equal_symbol_directory_message(const SymbolDirectoryMessage *read, const SymbolDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->cusip[i] == written->cusip[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->sec_name[i] == written->sec_name[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock_group[i] == written->stock_group[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->listing[i] == written->listing[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expiry[i] == written->expiry[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lot_size[i] == written->lot_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_term[i] == written->settlement_term[i]); }
  assert(read->listing_market == written->listing_market);
  for (size_t i = 0; i < 4; i++) { assert(read->previous_closing_price[i] == written->previous_closing_price[i]); }
  assert(read->listing_tier == written->listing_tier);
  for (size_t i = 0; i < 20; i++) { assert(read->market_maker_name[i] == written->market_maker_name[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->market_maker_phone_number[i] == written->market_maker_phone_number[i]); }
  for (size_t i = 0; i < 75; i++) { assert(read->full_sec_name[i] == written->full_sec_name[i]); }
}

/* Symbol Directory Message: written and read back, then read and written back */
static void check_symbol_directory_message(void) {
  SymbolDirectoryMessage sent;
  SymbolDirectoryMessage got;
  uint8_t wire[195];
  uint8_t again[195];

  any_symbol_directory_message(&sent);
  assert(encode_symbol_directory_message(&sent, wire, 0) == 195);
  assert(decode_symbol_directory_message(&got, wire, 0) == 195);
  equal_symbol_directory_message(&got, &sent);

  for (size_t i = 0; i < 195; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_directory_message(&got, wire, 0) == 195);
  assert(encode_symbol_directory_message(&got, again, 0) == 195);
  for (size_t i = 0; i < 195; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Dynamics Message: 35 bytes --------------------------------------- */

/* Values and rules for a symbol that can be updated intra-day. Sent for every symbol in the morning, and again during the day if a symbol changes. */
typedef struct {
  uint8_t time_offset[4];      /* bytes 0 to 3 */
  uint8_t symbol[12];          /* bytes 4 to 15 */
  uint8_t settlement_term[8];  /* bytes 16 to 23 */
  uint8_t gmf_setting;         /* byte 24 */
  uint8_t gmf_volume[8];       /* bytes 25 to 32 */
  uint8_t anonymous_setting;   /* byte 33 */
  uint8_t moc_eligible;        /* byte 34 */
} SymbolDynamicsMessage;

/* any Symbol Dynamics Message at all: every byte one the checker chooses */
static void any_symbol_dynamics_message(SymbolDynamicsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_term[i] = arbitrary(); }
  record->gmf_setting = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->gmf_volume[i] = arbitrary(); }
  record->anonymous_setting = arbitrary();
  record->moc_eligible = arbitrary();
}

/* Symbol Dynamics Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_symbol_dynamics_message(const SymbolDynamicsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_term[i]; }
  wire[at++] = record->gmf_setting;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->gmf_volume[i]; }
  wire[at++] = record->anonymous_setting;
  wire[at++] = record->moc_eligible;

  return at;
}

/* Symbol Dynamics Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_symbol_dynamics_message(SymbolDynamicsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_term[i] = wire[at++]; }
  record->gmf_setting = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->gmf_volume[i] = wire[at++]; }
  record->anonymous_setting = wire[at++];
  record->moc_eligible = wire[at++];

  return at;
}

/* what was read of Symbol Dynamics Message is what was written, byte for byte */
static void equal_symbol_dynamics_message(const SymbolDynamicsMessage *read, const SymbolDynamicsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_term[i] == written->settlement_term[i]); }
  assert(read->gmf_setting == written->gmf_setting);
  for (size_t i = 0; i < 8; i++) { assert(read->gmf_volume[i] == written->gmf_volume[i]); }
  assert(read->anonymous_setting == written->anonymous_setting);
  assert(read->moc_eligible == written->moc_eligible);
}

/* Symbol Dynamics Message: written and read back, then read and written back */
static void check_symbol_dynamics_message(void) {
  SymbolDynamicsMessage sent;
  SymbolDynamicsMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_symbol_dynamics_message(&sent);
  assert(encode_symbol_dynamics_message(&sent, wire, 0) == 35);
  assert(decode_symbol_dynamics_message(&got, wire, 0) == 35);
  equal_symbol_dynamics_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_dynamics_message(&got, wire, 0) == 35);
  assert(encode_symbol_dynamics_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Action Message: 25 bytes ---------------------------------------- */

/* Current trading state for a symbol. A symbol suspended intra-day with "V" is unsuspended with "N". */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t symbol[12];             /* bytes 4 to 15 */
  uint8_t trading_state;          /* byte 16 */
  uint8_t exchange_timestamp[8];  /* bytes 17 to 24 */
} TradingActionMessage;

/* any Trading Action Message at all: every byte one the checker chooses */
static void any_trading_action_message(TradingActionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  record->trading_state = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = arbitrary(); }
}

/* Trading Action Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_trading_action_message(const TradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->trading_state;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exchange_timestamp[i]; }

  return at;
}

/* Trading Action Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_trading_action_message(TradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  record->trading_state = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Action Message is what was written, byte for byte */
static void equal_trading_action_message(const TradingActionMessage *read, const TradingActionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->trading_state == written->trading_state);
  for (size_t i = 0; i < 8; i++) { assert(read->exchange_timestamp[i] == written->exchange_timestamp[i]); }
}

/* Trading Action Message: written and read back, then read and written back */
static void check_trading_action_message(void) {
  TradingActionMessage sent;
  TradingActionMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_trading_action_message(&sent);
  assert(encode_trading_action_message(&sent, wire, 0) == 25);
  assert(decode_trading_action_message(&got, wire, 0) == 25);
  equal_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_action_message(&got, wire, 0) == 25);
  assert(encode_trading_action_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message: 71 bytes --------------------------------------------- */

/* A new order added to the displayed book. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t order_number[18];       /* bytes 4 to 21 */
  uint8_t order_verb;             /* byte 22 */
  uint8_t quantity[4];            /* bytes 23 to 26 */
  uint8_t symbol[12];             /* bytes 27 to 38 */
  uint8_t price[4];               /* bytes 39 to 42 */
  uint8_t firm_id[3];             /* bytes 43 to 45 */
  uint8_t settlement_term[8];     /* bytes 46 to 53 */
  uint8_t odd_lot_flag;           /* byte 54 */
  uint8_t exchange_timestamp[8];  /* bytes 55 to 62 */
  uint8_t priority_timestamp[8];  /* bytes 63 to 70 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->order_number[i] = arbitrary(); }
  record->order_verb = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_term[i] = arbitrary(); }
  record->odd_lot_flag = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->priority_timestamp[i] = arbitrary(); }
}

/* Add Order Message to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->order_number[i]; }
  wire[at++] = record->order_verb;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_term[i]; }
  wire[at++] = record->odd_lot_flag;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exchange_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->priority_timestamp[i]; }

  return at;
}

/* Add Order Message off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->order_number[i] = wire[at++]; }
  record->order_verb = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_term[i] = wire[at++]; }
  record->odd_lot_flag = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->priority_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->order_number[i] == written->order_number[i]); }
  assert(read->order_verb == written->order_verb);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_term[i] == written->settlement_term[i]); }
  assert(read->odd_lot_flag == written->odd_lot_flag);
  for (size_t i = 0; i < 8; i++) { assert(read->exchange_timestamp[i] == written->exchange_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->priority_timestamp[i] == written->priority_timestamp[i]); }
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[71];
  uint8_t again[71];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 71);
  assert(decode_add_order_message(&got, wire, 0) == 71);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 71);
  assert(encode_add_order_message(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 52 bytes ---------------------------------------- */

/* An order on the book executed in whole or in part at the price it was displayed at. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t order_number[18];       /* bytes 4 to 21 */
  uint8_t executed_quantity[4];   /* bytes 22 to 25 */
  uint8_t match_number[18];       /* bytes 26 to 43 */
  uint8_t exchange_timestamp[8];  /* bytes 44 to 51 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exchange_timestamp[i]; }

  return at;
}

/* Order Executed Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exchange_timestamp[i] == written->exchange_timestamp[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 52);
  assert(decode_order_executed_message(&got, wire, 0) == 52);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 52);
  assert(encode_order_executed_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed With Price Message: 56 bytes ----------------------------- */

/* An order on the book executed in whole or in part at a price other than the one it was displayed at. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t order_number[18];       /* bytes 4 to 21 */
  uint8_t executed_quantity[4];   /* bytes 22 to 25 */
  uint8_t match_number[18];       /* bytes 26 to 43 */
  uint8_t execution_price[4];     /* bytes 44 to 47 */
  uint8_t exchange_timestamp[8];  /* bytes 48 to 55 */
} OrderExecutedWithPriceMessage;

/* any Order Executed With Price Message at all: every byte one the checker chooses */
static void any_order_executed_with_price_message(OrderExecutedWithPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = arbitrary(); }
}

/* Order Executed With Price Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_with_price_message(const OrderExecutedWithPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exchange_timestamp[i]; }

  return at;
}

/* Order Executed With Price Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_with_price_message(OrderExecutedWithPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed With Price Message is what was written, byte for byte */
static void equal_order_executed_with_price_message(const OrderExecutedWithPriceMessage *read, const OrderExecutedWithPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exchange_timestamp[i] == written->exchange_timestamp[i]); }
}

/* Order Executed With Price Message: written and read back, then read and written back */
static void check_order_executed_with_price_message(void) {
  OrderExecutedWithPriceMessage sent;
  OrderExecutedWithPriceMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_order_executed_with_price_message(&sent);
  assert(encode_order_executed_with_price_message(&sent, wire, 0) == 56);
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 56);
  equal_order_executed_with_price_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 56);
  assert(encode_order_executed_with_price_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 71 bytes ------------------------------------------------- */

/* A trade that does not change the displayed book, carrying the full attribution and classification of the execution. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t executed_quantity[4];   /* bytes 4 to 7 */
  uint8_t symbol[12];             /* bytes 8 to 19 */
  uint8_t execution_price[4];     /* bytes 20 to 23 */
  uint8_t match_number[18];       /* bytes 24 to 41 */
  uint8_t firm_id[3];             /* bytes 42 to 44 */
  uint8_t contra_firm_id[3];      /* bytes 45 to 47 */
  uint8_t settlement_term[8];     /* bytes 48 to 55 */
  uint8_t trade_attribute;        /* byte 56 */
  uint8_t cross_type;             /* byte 57 */
  uint8_t odd_lot_flag;           /* byte 58 */
  uint8_t sets_the_last_price;    /* byte 59 */
  uint8_t exchange_timestamp[8];  /* bytes 60 to 67 */
  uint8_t opening_trade;          /* byte 68 */
  uint8_t ccp_session_trade;      /* byte 69 */
  uint8_t moc_trade_marker;       /* byte 70 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->contra_firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_term[i] = arbitrary(); }
  record->trade_attribute = arbitrary();
  record->cross_type = arbitrary();
  record->odd_lot_flag = arbitrary();
  record->sets_the_last_price = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = arbitrary(); }
  record->opening_trade = arbitrary();
  record->ccp_session_trade = arbitrary();
  record->moc_trade_marker = arbitrary();
}

/* Trade Message to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_price[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->contra_firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_term[i]; }
  wire[at++] = record->trade_attribute;
  wire[at++] = record->cross_type;
  wire[at++] = record->odd_lot_flag;
  wire[at++] = record->sets_the_last_price;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exchange_timestamp[i]; }
  wire[at++] = record->opening_trade;
  wire[at++] = record->ccp_session_trade;
  wire[at++] = record->moc_trade_marker;

  return at;
}

/* Trade Message off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->contra_firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_term[i] = wire[at++]; }
  record->trade_attribute = wire[at++];
  record->cross_type = wire[at++];
  record->odd_lot_flag = wire[at++];
  record->sets_the_last_price = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = wire[at++]; }
  record->opening_trade = wire[at++];
  record->ccp_session_trade = wire[at++];
  record->moc_trade_marker = wire[at++];

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->contra_firm_id[i] == written->contra_firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_term[i] == written->settlement_term[i]); }
  assert(read->trade_attribute == written->trade_attribute);
  assert(read->cross_type == written->cross_type);
  assert(read->odd_lot_flag == written->odd_lot_flag);
  assert(read->sets_the_last_price == written->sets_the_last_price);
  for (size_t i = 0; i < 8; i++) { assert(read->exchange_timestamp[i] == written->exchange_timestamp[i]); }
  assert(read->opening_trade == written->opening_trade);
  assert(read->ccp_session_trade == written->ccp_session_trade);
  assert(read->moc_trade_marker == written->moc_trade_marker);
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[71];
  uint8_t again[71];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 71);
  assert(decode_trade_message(&got, wire, 0) == 71);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 71);
  assert(encode_trade_message(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broken Trade Message: 31 bytes ------------------------------------------ */

/* A previously transmitted execution that has been broken, naming the match number it cancels. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t match_number[18];       /* bytes 4 to 21 */
  uint8_t reason;                 /* byte 22 */
  uint8_t exchange_timestamp[8];  /* bytes 23 to 30 */
} BrokenTradeMessage;

/* any Broken Trade Message at all: every byte one the checker chooses */
static void any_broken_trade_message(BrokenTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->match_number[i] = arbitrary(); }
  record->reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = arbitrary(); }
}

/* Broken Trade Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_message(const BrokenTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exchange_timestamp[i]; }

  return at;
}

/* Broken Trade Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_message(BrokenTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->match_number[i] = wire[at++]; }
  record->reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Broken Trade Message is what was written, byte for byte */
static void equal_broken_trade_message(const BrokenTradeMessage *read, const BrokenTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->reason == written->reason);
  for (size_t i = 0; i < 8; i++) { assert(read->exchange_timestamp[i] == written->exchange_timestamp[i]); }
}

/* Broken Trade Message: written and read back, then read and written back */
static void check_broken_trade_message(void) {
  BrokenTradeMessage sent;
  BrokenTradeMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_broken_trade_message(&sent);
  assert(encode_broken_trade_message(&sent, wire, 0) == 31);
  assert(decode_broken_trade_message(&got, wire, 0) == 31);
  equal_broken_trade_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_broken_trade_message(&got, wire, 0) == 31);
  assert(encode_broken_trade_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Delete Message: 30 bytes ------------------------------------------ */

/* An order cancelled and removed from the displayed book. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t order_number[18];       /* bytes 4 to 21 */
  uint8_t exchange_timestamp[8];  /* bytes 22 to 29 */
} OrderDeleteMessage;

/* any Order Delete Message at all: every byte one the checker chooses */
static void any_order_delete_message(OrderDeleteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = arbitrary(); }
}

/* Order Delete Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_order_delete_message(const OrderDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exchange_timestamp[i]; }

  return at;
}

/* Order Delete Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_order_delete_message(OrderDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Order Delete Message is what was written, byte for byte */
static void equal_order_delete_message(const OrderDeleteMessage *read, const OrderDeleteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exchange_timestamp[i] == written->exchange_timestamp[i]); }
}

/* Order Delete Message: written and read back, then read and written back */
static void check_order_delete_message(void) {
  OrderDeleteMessage sent;
  OrderDeleteMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_order_delete_message(&sent);
  assert(encode_order_delete_message(&sent, wire, 0) == 30);
  assert(decode_order_delete_message(&got, wire, 0) == 30);
  equal_order_delete_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_order_delete_message(&got, wire, 0) == 30);
  assert(encode_order_delete_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replace Message: 38 bytes ----------------------------------------- */

/* An order on the book replaced with a new quantity and price, keeping its order number. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t order_number[18];       /* bytes 4 to 21 */
  uint8_t quantity[4];            /* bytes 22 to 25 */
  uint8_t price[4];               /* bytes 26 to 29 */
  uint8_t exchange_timestamp[8];  /* bytes 30 to 37 */
} OrderReplaceMessage;

/* any Order Replace Message at all: every byte one the checker chooses */
static void any_order_replace_message(OrderReplaceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = arbitrary(); }
}

/* Order Replace Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_order_replace_message(const OrderReplaceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exchange_timestamp[i]; }

  return at;
}

/* Order Replace Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_order_replace_message(OrderReplaceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Order Replace Message is what was written, byte for byte */
static void equal_order_replace_message(const OrderReplaceMessage *read, const OrderReplaceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exchange_timestamp[i] == written->exchange_timestamp[i]); }
}

/* Order Replace Message: written and read back, then read and written back */
static void check_order_replace_message(void) {
  OrderReplaceMessage sent;
  OrderReplaceMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_order_replace_message(&sent);
  assert(encode_order_replace_message(&sent, wire, 0) == 38);
  assert(decode_order_replace_message(&got, wire, 0) == 38);
  equal_order_replace_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replace_message(&got, wire, 0) == 38);
  assert(encode_order_replace_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Best Bid Offer Message: 40 bytes ---------------------------------------- */

/* The best bid and offer for a symbol with the quantity at each. During an auction with an indicative price set, the indicative price overwrites both sides. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t symbol[12];             /* bytes 4 to 15 */
  uint8_t best_bid[4];            /* bytes 16 to 19 */
  uint8_t best_bid_size[4];       /* bytes 20 to 23 */
  uint8_t best_offer[4];          /* bytes 24 to 27 */
  uint8_t best_offer_size[4];     /* bytes 28 to 31 */
  uint8_t exchange_timestamp[8];  /* bytes 32 to 39 */
} BestBidOfferMessage;

/* any Best Bid Offer Message at all: every byte one the checker chooses */
static void any_best_bid_offer_message(BestBidOfferMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_offer[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_offer_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = arbitrary(); }
}

/* Best Bid Offer Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_best_bid_offer_message(const BestBidOfferMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_bid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_bid_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_offer[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_offer_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exchange_timestamp[i]; }

  return at;
}

/* Best Bid Offer Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_best_bid_offer_message(BestBidOfferMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_offer[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_offer_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exchange_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Best Bid Offer Message is what was written, byte for byte */
static void equal_best_bid_offer_message(const BestBidOfferMessage *read, const BestBidOfferMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_bid[i] == written->best_bid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_bid_size[i] == written->best_bid_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_offer[i] == written->best_offer[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_offer_size[i] == written->best_offer_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exchange_timestamp[i] == written->exchange_timestamp[i]); }
}

/* Best Bid Offer Message: written and read back, then read and written back */
static void check_best_bid_offer_message(void) {
  BestBidOfferMessage sent;
  BestBidOfferMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_best_bid_offer_message(&sent);
  assert(encode_best_bid_offer_message(&sent, wire, 0) == 40);
  assert(decode_best_bid_offer_message(&got, wire, 0) == 40);
  equal_best_bid_offer_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_best_bid_offer_message(&got, wire, 0) == 40);
  assert(encode_best_bid_offer_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Closing Price Message: 20 bytes ----------------------------------------- */

/* The closing price for a symbol. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
  uint8_t symbol[12];      /* bytes 4 to 15 */
  uint8_t price[4];        /* bytes 16 to 19 */
} ClosingPriceMessage;

/* any Closing Price Message at all: every byte one the checker chooses */
static void any_closing_price_message(ClosingPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
}

/* Closing Price Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_closing_price_message(const ClosingPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Closing Price Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_closing_price_message(ClosingPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Closing Price Message is what was written, byte for byte */
static void equal_closing_price_message(const ClosingPriceMessage *read, const ClosingPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
}

/* Closing Price Message: written and read back, then read and written back */
static void check_closing_price_message(void) {
  ClosingPriceMessage sent;
  ClosingPriceMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_closing_price_message(&sent);
  assert(encode_closing_price_message(&sent, wire, 0) == 20);
  assert(decode_closing_price_message(&got, wire, 0) == 20);
  equal_closing_price_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_closing_price_message(&got, wire, 0) == 20);
  assert(encode_closing_price_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- General Message: 132 bytes ---------------------------------------------- */

/* Free text bulletin from the exchange. */
typedef struct {
  uint8_t time_offset[4];     /* bytes 0 to 3 */
  uint8_t message_text[128];  /* bytes 4 to 131 */
} GeneralMessage;

/* any General Message at all: every byte one the checker chooses */
static void any_general_message(GeneralMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 128; i++) { record->message_text[i] = arbitrary(); }
}

/* General Message to the wire: 132 bytes from at, returning where the next byte goes */
static size_t encode_general_message(const GeneralMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 128; i++) { wire[at++] = record->message_text[i]; }

  return at;
}

/* General Message off the wire: 132 bytes from at, returning where the next byte lies */
static size_t decode_general_message(GeneralMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 128; i++) { record->message_text[i] = wire[at++]; }

  return at;
}

/* what was read of General Message is what was written, byte for byte */
static void equal_general_message(const GeneralMessage *read, const GeneralMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 128; i++) { assert(read->message_text[i] == written->message_text[i]); }
}

/* General Message: written and read back, then read and written back */
static void check_general_message(void) {
  GeneralMessage sent;
  GeneralMessage got;
  uint8_t wire[132];
  uint8_t again[132];

  any_general_message(&sent);
  assert(encode_general_message(&sent, wire, 0) == 132);
  assert(decode_general_message(&got, wire, 0) == 132);
  equal_general_message(&got, &sent);

  for (size_t i = 0; i < 132; i++) { wire[i] = arbitrary(); }
  assert(decode_general_message(&got, wire, 0) == 132);
  assert(encode_general_message(&got, again, 0) == 132);
  for (size_t i = 0; i < 132; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_block_header();
  check_message_header();
  check_time_message();
  check_system_event_message();
  check_symbol_directory_message();
  check_symbol_dynamics_message();
  check_trading_action_message();
  check_add_order_message();
  check_order_executed_message();
  check_order_executed_with_price_message();
  check_trade_message();
  check_broken_trade_message();
  check_order_delete_message();
  check_order_replace_message();
  check_best_bid_offer_message();
  check_closing_price_message();
  check_general_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
