// nasdaq/nomoptions/bono/NomOptions_Bono_v3_3_Udp.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Best Of Nasdaq Options
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

/* ---- Timestamp Message: 4 bytes ---------------------------------------------- */

/* The system event message type is used to signal a market or data feed handler event. */
typedef struct {
  uint8_t second[4];  /* bytes 0 to 3 */
} TimestampMessage;

/* any Timestamp Message at all: every byte one the checker chooses */
static void any_timestamp_message(TimestampMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = arbitrary(); }
}

/* Timestamp Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_timestamp_message(const TimestampMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->second[i]; }

  return at;
}

/* Timestamp Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_timestamp_message(TimestampMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = wire[at++]; }

  return at;
}

/* what was read of Timestamp Message is what was written, byte for byte */
static void equal_timestamp_message(const TimestampMessage *read, const TimestampMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->second[i] == written->second[i]); }
}

/* Timestamp Message: written and read back, then read and written back */
static void check_timestamp_message(void) {
  TimestampMessage sent;
  TimestampMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_timestamp_message(&sent);
  assert(encode_timestamp_message(&sent, wire, 0) == 4);
  assert(decode_timestamp_message(&got, wire, 0) == 4);
  equal_timestamp_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_timestamp_message(&got, wire, 0) == 4);
  assert(encode_timestamp_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 7 bytes ------------------------------------------- */

/* The system event message type is used to signal a market or data feed handler event. */
typedef struct {
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t event_code;      /* byte 4 */
  uint8_t version;         /* byte 5 */
  uint8_t sub_version;     /* byte 6 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  record->event_code = arbitrary();
  record->version = arbitrary();
  record->sub_version = arbitrary();
}

/* System Event Message to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  wire[at++] = record->event_code;
  wire[at++] = record->version;
  wire[at++] = record->sub_version;

  return at;
}

/* System Event Message off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  record->event_code = wire[at++];
  record->version = wire[at++];
  record->sub_version = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  assert(read->event_code == written->event_code);
  assert(read->version == written->version);
  assert(read->sub_version == written->sub_version);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[7];
  uint8_t again[7];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 7);
  assert(decode_system_event_message(&got, wire, 0) == 7);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 7);
  assert(encode_system_event_message(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Directory Message: 39 bytes ------------------------------------- */

/* At the start of each trading day, the options system disseminates directory messages for all symbols eligible for the auction process in the options system. */
typedef struct {
  uint8_t nanoseconds[4];         /* bytes 0 to 3 */
  uint8_t option_id[4];           /* bytes 4 to 7 */
  uint8_t security_symbol[6];     /* bytes 8 to 13 */
  uint8_t expiration_year;        /* byte 14 */
  uint8_t expiration_month;       /* byte 15 */
  uint8_t expiration_day;         /* byte 16 */
  uint8_t strike_price[4];        /* bytes 17 to 20 */
  uint8_t option_type;            /* byte 21 */
  uint8_t source;                 /* byte 22 */
  uint8_t underlying_symbol[13];  /* bytes 23 to 35 */
  uint8_t option_closing_type;    /* byte 36 */
  uint8_t tradable;               /* byte 37 */
  uint8_t mpv;                    /* byte 38 */
} OptionsDirectoryMessage;

/* any Options Directory Message at all: every byte one the checker chooses */
static void any_options_directory_message(OptionsDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->security_symbol[i] = arbitrary(); }
  record->expiration_year = arbitrary();
  record->expiration_month = arbitrary();
  record->expiration_day = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  record->option_type = arbitrary();
  record->source = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->option_closing_type = arbitrary();
  record->tradable = arbitrary();
  record->mpv = arbitrary();
}

/* Options Directory Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_options_directory_message(const OptionsDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->expiration_year;
  wire[at++] = record->expiration_month;
  wire[at++] = record->expiration_day;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->option_type;
  wire[at++] = record->source;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->option_closing_type;
  wire[at++] = record->tradable;
  wire[at++] = record->mpv;

  return at;
}

/* Options Directory Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_options_directory_message(OptionsDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->security_symbol[i] = wire[at++]; }
  record->expiration_year = wire[at++];
  record->expiration_month = wire[at++];
  record->expiration_day = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  record->option_type = wire[at++];
  record->source = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->option_closing_type = wire[at++];
  record->tradable = wire[at++];
  record->mpv = wire[at++];

  return at;
}

/* what was read of Options Directory Message is what was written, byte for byte */
static void equal_options_directory_message(const OptionsDirectoryMessage *read, const OptionsDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->expiration_year == written->expiration_year);
  assert(read->expiration_month == written->expiration_month);
  assert(read->expiration_day == written->expiration_day);
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->option_type == written->option_type);
  assert(read->source == written->source);
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->option_closing_type == written->option_closing_type);
  assert(read->tradable == written->tradable);
  assert(read->mpv == written->mpv);
}

/* Options Directory Message: written and read back, then read and written back */
static void check_options_directory_message(void) {
  OptionsDirectoryMessage sent;
  OptionsDirectoryMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_options_directory_message(&sent);
  assert(encode_options_directory_message(&sent, wire, 0) == 39);
  assert(decode_options_directory_message(&got, wire, 0) == 39);
  equal_options_directory_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_options_directory_message(&got, wire, 0) == 39);
  assert(encode_options_directory_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Action Message: 9 bytes ----------------------------------------- */

/* The options system uses this administrative message to indicate the current trading status of an index or equity option within the options market. */
typedef struct {
  uint8_t nanoseconds[4];         /* bytes 0 to 3 */
  uint8_t option_id[4];           /* bytes 4 to 7 */
  uint8_t current_trading_state;  /* byte 8 */
} TradingActionMessage;

/* any Trading Action Message at all: every byte one the checker chooses */
static void any_trading_action_message(TradingActionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  record->current_trading_state = arbitrary();
}

/* Trading Action Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_trading_action_message(const TradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  wire[at++] = record->current_trading_state;

  return at;
}

/* Trading Action Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_trading_action_message(TradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  record->current_trading_state = wire[at++];

  return at;
}

/* what was read of Trading Action Message is what was written, byte for byte */
static void equal_trading_action_message(const TradingActionMessage *read, const TradingActionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  assert(read->current_trading_state == written->current_trading_state);
}

/* Trading Action Message: written and read back, then read and written back */
static void check_trading_action_message(void) {
  TradingActionMessage sent;
  TradingActionMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_trading_action_message(&sent);
  assert(encode_trading_action_message(&sent, wire, 0) == 9);
  assert(decode_trading_action_message(&got, wire, 0) == 9);
  equal_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_action_message(&got, wire, 0) == 9);
  assert(encode_trading_action_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Open Closed Message: 9 bytes ----------------------------------- */

/* The options system uses this administrative message to indicate when an option has completed the opening process and is now available for auto execution or when the option has closed and is no longer available for auto execution. */
typedef struct {
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t option_id[4];    /* bytes 4 to 7 */
  uint8_t open_state;      /* byte 8 */
} SecurityOpenClosedMessage;

/* any Security Open Closed Message at all: every byte one the checker chooses */
static void any_security_open_closed_message(SecurityOpenClosedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  record->open_state = arbitrary();
}

/* Security Open Closed Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_security_open_closed_message(const SecurityOpenClosedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  wire[at++] = record->open_state;

  return at;
}

/* Security Open Closed Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_security_open_closed_message(SecurityOpenClosedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  record->open_state = wire[at++];

  return at;
}

/* what was read of Security Open Closed Message is what was written, byte for byte */
static void equal_security_open_closed_message(const SecurityOpenClosedMessage *read, const SecurityOpenClosedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  assert(read->open_state == written->open_state);
}

/* Security Open Closed Message: written and read back, then read and written back */
static void check_security_open_closed_message(void) {
  SecurityOpenClosedMessage sent;
  SecurityOpenClosedMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_security_open_closed_message(&sent);
  assert(encode_security_open_closed_message(&sent, wire, 0) == 9);
  assert(decode_security_open_closed_message(&got, wire, 0) == 9);
  equal_security_open_closed_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_security_open_closed_message(&got, wire, 0) == 9);
  assert(encode_security_open_closed_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Best Bid And Ask Update Message: 17 bytes ------------------------- */

/* Whenever the best bid and ask position changes on both sides, the options system will send its best bid and ask update via the data feed for the affected security. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t option_id[4];     /* bytes 4 to 7 */
  uint8_t quote_condition;  /* byte 8 */
  uint8_t bid_price_2[2];   /* bytes 9 to 10 */
  uint8_t bid_size_2[2];    /* bytes 11 to 12 */
  uint8_t ask_price_2[2];   /* bytes 13 to 14 */
  uint8_t ask_size_2[2];    /* bytes 15 to 16 */
} ShortBestBidAndAskUpdateMessage;

/* any Short Best Bid And Ask Update Message at all: every byte one the checker chooses */
static void any_short_best_bid_and_ask_update_message(ShortBestBidAndAskUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  record->quote_condition = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->bid_price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_size_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_size_2[i] = arbitrary(); }
}

/* Short Best Bid And Ask Update Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_short_best_bid_and_ask_update_message(const ShortBestBidAndAskUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  wire[at++] = record->quote_condition;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_price_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_size_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_price_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_size_2[i]; }

  return at;
}

/* Short Best Bid And Ask Update Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_short_best_bid_and_ask_update_message(ShortBestBidAndAskUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  record->quote_condition = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->bid_price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_size_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_size_2[i] = wire[at++]; }

  return at;
}

/* what was read of Short Best Bid And Ask Update Message is what was written, byte for byte */
static void equal_short_best_bid_and_ask_update_message(const ShortBestBidAndAskUpdateMessage *read, const ShortBestBidAndAskUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  assert(read->quote_condition == written->quote_condition);
  for (size_t i = 0; i < 2; i++) { assert(read->bid_price_2[i] == written->bid_price_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_size_2[i] == written->bid_size_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_price_2[i] == written->ask_price_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_size_2[i] == written->ask_size_2[i]); }
}

/* Short Best Bid And Ask Update Message: written and read back, then read and written back */
static void check_short_best_bid_and_ask_update_message(void) {
  ShortBestBidAndAskUpdateMessage sent;
  ShortBestBidAndAskUpdateMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_short_best_bid_and_ask_update_message(&sent);
  assert(encode_short_best_bid_and_ask_update_message(&sent, wire, 0) == 17);
  assert(decode_short_best_bid_and_ask_update_message(&got, wire, 0) == 17);
  equal_short_best_bid_and_ask_update_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_short_best_bid_and_ask_update_message(&got, wire, 0) == 17);
  assert(encode_short_best_bid_and_ask_update_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Best Bid And Ask Update Message: 25 bytes -------------------------- */

/* This message is the same as the Best Bid AND Ask Update Message – Short Form described above except that Prices and Sizes are 4 byte Integers, the prices having 4 implied decimal places. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t option_id[4];     /* bytes 4 to 7 */
  uint8_t quote_condition;  /* byte 8 */
  uint8_t bid_price_4[4];   /* bytes 9 to 12 */
  uint8_t bid_size_4[4];    /* bytes 13 to 16 */
  uint8_t ask_price_4[4];   /* bytes 17 to 20 */
  uint8_t ask_size_4[4];    /* bytes 21 to 24 */
} LongBestBidAndAskUpdateMessage;

/* any Long Best Bid And Ask Update Message at all: every byte one the checker chooses */
static void any_long_best_bid_and_ask_update_message(LongBestBidAndAskUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  record->quote_condition = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->bid_price_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_price_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_4[i] = arbitrary(); }
}

/* Long Best Bid And Ask Update Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_long_best_bid_and_ask_update_message(const LongBestBidAndAskUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  wire[at++] = record->quote_condition;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_price_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_4[i]; }

  return at;
}

/* Long Best Bid And Ask Update Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_long_best_bid_and_ask_update_message(LongBestBidAndAskUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  record->quote_condition = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->bid_price_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_price_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_4[i] = wire[at++]; }

  return at;
}

/* what was read of Long Best Bid And Ask Update Message is what was written, byte for byte */
static void equal_long_best_bid_and_ask_update_message(const LongBestBidAndAskUpdateMessage *read, const LongBestBidAndAskUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  assert(read->quote_condition == written->quote_condition);
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price_4[i] == written->bid_price_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_4[i] == written->bid_size_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_price_4[i] == written->ask_price_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_4[i] == written->ask_size_4[i]); }
}

/* Long Best Bid And Ask Update Message: written and read back, then read and written back */
static void check_long_best_bid_and_ask_update_message(void) {
  LongBestBidAndAskUpdateMessage sent;
  LongBestBidAndAskUpdateMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_long_best_bid_and_ask_update_message(&sent);
  assert(encode_long_best_bid_and_ask_update_message(&sent, wire, 0) == 25);
  assert(decode_long_best_bid_and_ask_update_message(&got, wire, 0) == 25);
  equal_long_best_bid_and_ask_update_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_long_best_bid_and_ask_update_message(&got, wire, 0) == 25);
  assert(encode_long_best_bid_and_ask_update_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Best Ask Update Message: 13 bytes --------------------------------- */

/* The options system will continuously calculate its best bid and offer position for active options contracts on the options market during the trading day. Whenever the best bid or ask position changes on one side but not the other side, the options system will send its best bid or ask update via this feed for the affected security. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t option_id[4];     /* bytes 4 to 7 */
  uint8_t quote_condition;  /* byte 8 */
  uint8_t price_2[2];       /* bytes 9 to 10 */
  uint8_t size_2[2];        /* bytes 11 to 12 */
} ShortBestAskUpdateMessage;

/* any Short Best Ask Update Message at all: every byte one the checker chooses */
static void any_short_best_ask_update_message(ShortBestAskUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  record->quote_condition = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->size_2[i] = arbitrary(); }
}

/* Short Best Ask Update Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_short_best_ask_update_message(const ShortBestAskUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  wire[at++] = record->quote_condition;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->size_2[i]; }

  return at;
}

/* Short Best Ask Update Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_short_best_ask_update_message(ShortBestAskUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  record->quote_condition = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->size_2[i] = wire[at++]; }

  return at;
}

/* what was read of Short Best Ask Update Message is what was written, byte for byte */
static void equal_short_best_ask_update_message(const ShortBestAskUpdateMessage *read, const ShortBestAskUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  assert(read->quote_condition == written->quote_condition);
  for (size_t i = 0; i < 2; i++) { assert(read->price_2[i] == written->price_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->size_2[i] == written->size_2[i]); }
}

/* Short Best Ask Update Message: written and read back, then read and written back */
static void check_short_best_ask_update_message(void) {
  ShortBestAskUpdateMessage sent;
  ShortBestAskUpdateMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_short_best_ask_update_message(&sent);
  assert(encode_short_best_ask_update_message(&sent, wire, 0) == 13);
  assert(decode_short_best_ask_update_message(&got, wire, 0) == 13);
  equal_short_best_ask_update_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_short_best_ask_update_message(&got, wire, 0) == 13);
  assert(encode_short_best_ask_update_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Best Bid Update Message: 13 bytes --------------------------------- */

/* The options system will continuously calculate its best bid and offer position for active options contracts on the options market during the trading day. Whenever the best bid or ask position changes on one side but not the other side, the options system will send its best bid or ask update via this feed for the affected security. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t option_id[4];     /* bytes 4 to 7 */
  uint8_t quote_condition;  /* byte 8 */
  uint8_t price_2[2];       /* bytes 9 to 10 */
  uint8_t size_2[2];        /* bytes 11 to 12 */
} ShortBestBidUpdateMessage;

/* any Short Best Bid Update Message at all: every byte one the checker chooses */
static void any_short_best_bid_update_message(ShortBestBidUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  record->quote_condition = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->size_2[i] = arbitrary(); }
}

/* Short Best Bid Update Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_short_best_bid_update_message(const ShortBestBidUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  wire[at++] = record->quote_condition;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->size_2[i]; }

  return at;
}

/* Short Best Bid Update Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_short_best_bid_update_message(ShortBestBidUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  record->quote_condition = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->size_2[i] = wire[at++]; }

  return at;
}

/* what was read of Short Best Bid Update Message is what was written, byte for byte */
static void equal_short_best_bid_update_message(const ShortBestBidUpdateMessage *read, const ShortBestBidUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  assert(read->quote_condition == written->quote_condition);
  for (size_t i = 0; i < 2; i++) { assert(read->price_2[i] == written->price_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->size_2[i] == written->size_2[i]); }
}

/* Short Best Bid Update Message: written and read back, then read and written back */
static void check_short_best_bid_update_message(void) {
  ShortBestBidUpdateMessage sent;
  ShortBestBidUpdateMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_short_best_bid_update_message(&sent);
  assert(encode_short_best_bid_update_message(&sent, wire, 0) == 13);
  assert(decode_short_best_bid_update_message(&got, wire, 0) == 13);
  equal_short_best_bid_update_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_short_best_bid_update_message(&got, wire, 0) == 13);
  assert(encode_short_best_bid_update_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Best Ask Update Message: 17 bytes ---------------------------------- */

/* This message is the same as the Best Bid OR Ask Update Message – Short Form described above except that Prices and Sizes are 4 byte Integers, the price having 4 implied decimal places. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t option_id[4];     /* bytes 4 to 7 */
  uint8_t quote_condition;  /* byte 8 */
  uint8_t price_4[4];       /* bytes 9 to 12 */
  uint8_t size_4[4];        /* bytes 13 to 16 */
} LongBestAskUpdateMessage;

/* any Long Best Ask Update Message at all: every byte one the checker chooses */
static void any_long_best_ask_update_message(LongBestAskUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  record->quote_condition = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size_4[i] = arbitrary(); }
}

/* Long Best Ask Update Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_long_best_ask_update_message(const LongBestAskUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  wire[at++] = record->quote_condition;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size_4[i]; }

  return at;
}

/* Long Best Ask Update Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_long_best_ask_update_message(LongBestAskUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  record->quote_condition = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size_4[i] = wire[at++]; }

  return at;
}

/* what was read of Long Best Ask Update Message is what was written, byte for byte */
static void equal_long_best_ask_update_message(const LongBestAskUpdateMessage *read, const LongBestAskUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  assert(read->quote_condition == written->quote_condition);
  for (size_t i = 0; i < 4; i++) { assert(read->price_4[i] == written->price_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size_4[i] == written->size_4[i]); }
}

/* Long Best Ask Update Message: written and read back, then read and written back */
static void check_long_best_ask_update_message(void) {
  LongBestAskUpdateMessage sent;
  LongBestAskUpdateMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_long_best_ask_update_message(&sent);
  assert(encode_long_best_ask_update_message(&sent, wire, 0) == 17);
  assert(decode_long_best_ask_update_message(&got, wire, 0) == 17);
  equal_long_best_ask_update_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_long_best_ask_update_message(&got, wire, 0) == 17);
  assert(encode_long_best_ask_update_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Best Bid Update Message: 17 bytes ---------------------------------- */

/* This message is the same as the Best Bid OR Ask Update Message – Short Form described above except that Prices and Sizes are 4 byte Integers, the price having 4 implied decimal places. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t option_id[4];     /* bytes 4 to 7 */
  uint8_t quote_condition;  /* byte 8 */
  uint8_t price_4[4];       /* bytes 9 to 12 */
  uint8_t size_4[4];        /* bytes 13 to 16 */
} LongBestBidUpdateMessage;

/* any Long Best Bid Update Message at all: every byte one the checker chooses */
static void any_long_best_bid_update_message(LongBestBidUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  record->quote_condition = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size_4[i] = arbitrary(); }
}

/* Long Best Bid Update Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_long_best_bid_update_message(const LongBestBidUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  wire[at++] = record->quote_condition;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size_4[i]; }

  return at;
}

/* Long Best Bid Update Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_long_best_bid_update_message(LongBestBidUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  record->quote_condition = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size_4[i] = wire[at++]; }

  return at;
}

/* what was read of Long Best Bid Update Message is what was written, byte for byte */
static void equal_long_best_bid_update_message(const LongBestBidUpdateMessage *read, const LongBestBidUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  assert(read->quote_condition == written->quote_condition);
  for (size_t i = 0; i < 4; i++) { assert(read->price_4[i] == written->price_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size_4[i] == written->size_4[i]); }
}

/* Long Best Bid Update Message: written and read back, then read and written back */
static void check_long_best_bid_update_message(void) {
  LongBestBidUpdateMessage sent;
  LongBestBidUpdateMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_long_best_bid_update_message(&sent);
  assert(encode_long_best_bid_update_message(&sent, wire, 0) == 17);
  assert(decode_long_best_bid_update_message(&got, wire, 0) == 17);
  equal_long_best_bid_update_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_long_best_bid_update_message(&got, wire, 0) == 17);
  assert(encode_long_best_bid_update_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Report Message: 21 bytes ------------------------------------------ */

/* The Trade Report message will be used to relay execution system transactions that are reported during the current business day. The options system only reports one-side of a trade execution on the feed and other data feed products. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t option_id[4];     /* bytes 4 to 7 */
  uint8_t cross_id[4];      /* bytes 8 to 11 */
  uint8_t trade_condition;  /* byte 12 */
  uint8_t price_4[4];       /* bytes 13 to 16 */
  uint8_t volume[4];        /* bytes 17 to 20 */
} TradeReportMessage;

/* any Trade Report Message at all: every byte one the checker chooses */
static void any_trade_report_message(TradeReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  record->trade_condition = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
}

/* Trade Report Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_trade_report_message(const TradeReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  wire[at++] = record->trade_condition;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }

  return at;
}

/* Trade Report Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_trade_report_message(TradeReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  record->trade_condition = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Report Message is what was written, byte for byte */
static void equal_trade_report_message(const TradeReportMessage *read, const TradeReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  assert(read->trade_condition == written->trade_condition);
  for (size_t i = 0; i < 4; i++) { assert(read->price_4[i] == written->price_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
}

/* Trade Report Message: written and read back, then read and written back */
static void check_trade_report_message(void) {
  TradeReportMessage sent;
  TradeReportMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_trade_report_message(&sent);
  assert(encode_trade_report_message(&sent, wire, 0) == 21);
  assert(decode_trade_report_message(&got, wire, 0) == 21);
  equal_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report_message(&got, wire, 0) == 21);
  assert(encode_trade_report_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broken Trade Report Message: 20 bytes ----------------------------------- */

/* The following message is used in the event that an options trade transaction is broken on the same business day that it is reported. */
typedef struct {
  uint8_t nanoseconds[4];        /* bytes 0 to 3 */
  uint8_t option_id[4];          /* bytes 4 to 7 */
  uint8_t original_cross_id[4];  /* bytes 8 to 11 */
  uint8_t original_price[4];     /* bytes 12 to 15 */
  uint8_t original_volume[4];    /* bytes 16 to 19 */
} BrokenTradeReportMessage;

/* any Broken Trade Report Message at all: every byte one the checker chooses */
static void any_broken_trade_report_message(BrokenTradeReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_volume[i] = arbitrary(); }
}

/* Broken Trade Report Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_report_message(const BrokenTradeReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_cross_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_volume[i]; }

  return at;
}

/* Broken Trade Report Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_report_message(BrokenTradeReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Broken Trade Report Message is what was written, byte for byte */
static void equal_broken_trade_report_message(const BrokenTradeReportMessage *read, const BrokenTradeReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_cross_id[i] == written->original_cross_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_price[i] == written->original_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_volume[i] == written->original_volume[i]); }
}

/* Broken Trade Report Message: written and read back, then read and written back */
static void check_broken_trade_report_message(void) {
  BrokenTradeReportMessage sent;
  BrokenTradeReportMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_broken_trade_report_message(&sent);
  assert(encode_broken_trade_report_message(&sent, wire, 0) == 20);
  assert(decode_broken_trade_report_message(&got, wire, 0) == 20);
  equal_broken_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_broken_trade_report_message(&got, wire, 0) == 20);
  assert(encode_broken_trade_report_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_timestamp_message();
  check_system_event_message();
  check_options_directory_message();
  check_trading_action_message();
  check_security_open_closed_message();
  check_short_best_bid_and_ask_update_message();
  check_long_best_bid_and_ask_update_message();
  check_short_best_ask_update_message();
  check_short_best_bid_update_message();
  check_long_best_ask_update_message();
  check_long_best_bid_update_message();
  check_trade_report_message();
  check_broken_trade_report_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
