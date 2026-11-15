// nasdaq/iseoptions/orderfeed/IseOptions_OrderFeed_v1_1.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Ise Order Feed Market Data
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

/* ---- System Event Message: 13 bytes ------------------------------------------ */

/* The system event message type is used to signal a market or data feed handler event. */
typedef struct {
  uint8_t timestamp[6];     /* bytes 0 to 5 */
  uint8_t event_code;       /* byte 6 */
  uint8_t current_year[2];  /* bytes 7 to 8 */
  uint8_t current_month;    /* byte 9 */
  uint8_t current_day;      /* byte 10 */
  uint8_t version;          /* byte 11 */
  uint8_t sub_version;      /* byte 12 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  record->event_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->current_year[i] = arbitrary(); }
  record->current_month = arbitrary();
  record->current_day = arbitrary();
  record->version = arbitrary();
  record->sub_version = arbitrary();
}

/* System Event Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->current_year[i]; }
  wire[at++] = record->current_month;
  wire[at++] = record->current_day;
  wire[at++] = record->version;
  wire[at++] = record->sub_version;

  return at;
}

/* System Event Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  record->event_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->current_year[i] = wire[at++]; }
  record->current_month = wire[at++];
  record->current_day = wire[at++];
  record->version = wire[at++];
  record->sub_version = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->event_code == written->event_code);
  for (size_t i = 0; i < 2; i++) { assert(read->current_year[i] == written->current_year[i]); }
  assert(read->current_month == written->current_month);
  assert(read->current_day == written->current_day);
  assert(read->version == written->version);
  assert(read->sub_version == written->sub_version);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 13);
  assert(decode_system_event_message(&got, wire, 0) == 13);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 13);
  assert(encode_system_event_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Option Directory Message: 49 bytes -------------------------------------- */

/* At the start of each trading day, the options system disseminates directory messages for all symbols eligible for trading in the options system. */
typedef struct {
  uint8_t timestamp[6];           /* bytes 0 to 5 */
  uint8_t option_id[4];           /* bytes 6 to 9 */
  uint8_t security_symbol[6];     /* bytes 10 to 15 */
  uint8_t expiration_year;        /* byte 16 */
  uint8_t expiration_month;       /* byte 17 */
  uint8_t expiration_day;         /* byte 18 */
  uint8_t strike_price[8];        /* bytes 19 to 26 */
  uint8_t option_type;            /* byte 27 */
  uint8_t source;                 /* byte 28 */
  uint8_t underlying_symbol[13];  /* bytes 29 to 41 */
  uint8_t trading_type;           /* byte 42 */
  uint8_t contract_size[2];       /* bytes 43 to 44 */
  uint8_t option_closing_type;    /* byte 45 */
  uint8_t tradable;               /* byte 46 */
  uint8_t mpv;                    /* byte 47 */
  uint8_t closing_only;           /* byte 48 */
} OptionDirectoryMessage;

/* any Option Directory Message at all: every byte one the checker chooses */
static void any_option_directory_message(OptionDirectoryMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->security_symbol[i] = arbitrary(); }
  record->expiration_year = arbitrary();
  record->expiration_month = arbitrary();
  record->expiration_day = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->option_type = arbitrary();
  record->source = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->trading_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->contract_size[i] = arbitrary(); }
  record->option_closing_type = arbitrary();
  record->tradable = arbitrary();
  record->mpv = arbitrary();
  record->closing_only = arbitrary();
}

/* Option Directory Message to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_option_directory_message(const OptionDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->expiration_year;
  wire[at++] = record->expiration_month;
  wire[at++] = record->expiration_day;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->option_type;
  wire[at++] = record->source;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->trading_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->contract_size[i]; }
  wire[at++] = record->option_closing_type;
  wire[at++] = record->tradable;
  wire[at++] = record->mpv;
  wire[at++] = record->closing_only;

  return at;
}

/* Option Directory Message off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_option_directory_message(OptionDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->security_symbol[i] = wire[at++]; }
  record->expiration_year = wire[at++];
  record->expiration_month = wire[at++];
  record->expiration_day = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->option_type = wire[at++];
  record->source = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->trading_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->contract_size[i] = wire[at++]; }
  record->option_closing_type = wire[at++];
  record->tradable = wire[at++];
  record->mpv = wire[at++];
  record->closing_only = wire[at++];

  return at;
}

/* what was read of Option Directory Message is what was written, byte for byte */
static void equal_option_directory_message(const OptionDirectoryMessage *read, const OptionDirectoryMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->expiration_year == written->expiration_year);
  assert(read->expiration_month == written->expiration_month);
  assert(read->expiration_day == written->expiration_day);
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->option_type == written->option_type);
  assert(read->source == written->source);
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->trading_type == written->trading_type);
  for (size_t i = 0; i < 2; i++) { assert(read->contract_size[i] == written->contract_size[i]); }
  assert(read->option_closing_type == written->option_closing_type);
  assert(read->tradable == written->tradable);
  assert(read->mpv == written->mpv);
  assert(read->closing_only == written->closing_only);
}

/* Option Directory Message: written and read back, then read and written back */
static void check_option_directory_message(void) {
  OptionDirectoryMessage sent;
  OptionDirectoryMessage got;
  uint8_t wire[49];
  uint8_t again[49];

  any_option_directory_message(&sent);
  assert(encode_option_directory_message(&sent, wire, 0) == 49);
  assert(decode_option_directory_message(&got, wire, 0) == 49);
  equal_option_directory_message(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_option_directory_message(&got, wire, 0) == 49);
  assert(encode_option_directory_message(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Action Message: 11 bytes ---------------------------------------- */

/* The options system uses this administrative message to indicate the current trading status of an index or equity option within the options market. */
typedef struct {
  uint8_t timestamp[6];           /* bytes 0 to 5 */
  uint8_t option_id[4];           /* bytes 6 to 9 */
  uint8_t current_trading_state;  /* byte 10 */
} TradingActionMessage;

/* any Trading Action Message at all: every byte one the checker chooses */
static void any_trading_action_message(TradingActionMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  record->current_trading_state = arbitrary();
}

/* Trading Action Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_trading_action_message(const TradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  wire[at++] = record->current_trading_state;

  return at;
}

/* Trading Action Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_trading_action_message(TradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  record->current_trading_state = wire[at++];

  return at;
}

/* what was read of Trading Action Message is what was written, byte for byte */
static void equal_trading_action_message(const TradingActionMessage *read, const TradingActionMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  assert(read->current_trading_state == written->current_trading_state);
}

/* Trading Action Message: written and read back, then read and written back */
static void check_trading_action_message(void) {
  TradingActionMessage sent;
  TradingActionMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_trading_action_message(&sent);
  assert(encode_trading_action_message(&sent, wire, 0) == 11);
  assert(decode_trading_action_message(&got, wire, 0) == 11);
  equal_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_action_message(&got, wire, 0) == 11);
  assert(encode_trading_action_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Open Closed Message: 11 bytes ---------------------------------- */

/* The options system uses this administrative message to indicate when an option has completed the opening process and is now available for auto execution or when the option has closed and is no longer available for auto execution. */
typedef struct {
  uint8_t timestamp[6];  /* bytes 0 to 5 */
  uint8_t option_id[4];  /* bytes 6 to 9 */
  uint8_t open_state;    /* byte 10 */
} SecurityOpenClosedMessage;

/* any Security Open Closed Message at all: every byte one the checker chooses */
static void any_security_open_closed_message(SecurityOpenClosedMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  record->open_state = arbitrary();
}

/* Security Open Closed Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_security_open_closed_message(const SecurityOpenClosedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  wire[at++] = record->open_state;

  return at;
}

/* Security Open Closed Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_security_open_closed_message(SecurityOpenClosedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  record->open_state = wire[at++];

  return at;
}

/* what was read of Security Open Closed Message is what was written, byte for byte */
static void equal_security_open_closed_message(const SecurityOpenClosedMessage *read, const SecurityOpenClosedMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  assert(read->open_state == written->open_state);
}

/* Security Open Closed Message: written and read back, then read and written back */
static void check_security_open_closed_message(void) {
  SecurityOpenClosedMessage sent;
  SecurityOpenClosedMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_security_open_closed_message(&sent);
  assert(encode_security_open_closed_message(&sent, wire, 0) == 11);
  assert(decode_security_open_closed_message(&got, wire, 0) == 11);
  equal_security_open_closed_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_security_open_closed_message(&got, wire, 0) == 11);
  assert(encode_security_open_closed_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Imbalance Message: 23 bytes ------------------------------------- */

/* Nasdaq disseminates Opening Imbalance information at regular intervals in the time leading up to the Nasdaq Opening Auction events. */
typedef struct {
  uint8_t timestamp[6];         /* bytes 0 to 5 */
  uint8_t option_id[4];         /* bytes 6 to 9 */
  uint8_t paired_contracts[4];  /* bytes 10 to 13 */
  uint8_t imbalance_direction;  /* byte 14 */
  uint8_t imbalance_price[4];   /* bytes 15 to 18 */
  uint8_t imbalance_volume[4];  /* bytes 19 to 22 */
} OpeningImbalanceMessage;

/* any Opening Imbalance Message at all: every byte one the checker chooses */
static void any_opening_imbalance_message(OpeningImbalanceMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->paired_contracts[i] = arbitrary(); }
  record->imbalance_direction = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->imbalance_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->imbalance_volume[i] = arbitrary(); }
}

/* Opening Imbalance Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_opening_imbalance_message(const OpeningImbalanceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->paired_contracts[i]; }
  wire[at++] = record->imbalance_direction;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->imbalance_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->imbalance_volume[i]; }

  return at;
}

/* Opening Imbalance Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_opening_imbalance_message(OpeningImbalanceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->paired_contracts[i] = wire[at++]; }
  record->imbalance_direction = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->imbalance_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->imbalance_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Opening Imbalance Message is what was written, byte for byte */
static void equal_opening_imbalance_message(const OpeningImbalanceMessage *read, const OpeningImbalanceMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->paired_contracts[i] == written->paired_contracts[i]); }
  assert(read->imbalance_direction == written->imbalance_direction);
  for (size_t i = 0; i < 4; i++) { assert(read->imbalance_price[i] == written->imbalance_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->imbalance_volume[i] == written->imbalance_volume[i]); }
}

/* Opening Imbalance Message: written and read back, then read and written back */
static void check_opening_imbalance_message(void) {
  OpeningImbalanceMessage sent;
  OpeningImbalanceMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_opening_imbalance_message(&sent);
  assert(encode_opening_imbalance_message(&sent, wire, 0) == 23);
  assert(decode_opening_imbalance_message(&got, wire, 0) == 23);
  equal_opening_imbalance_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_imbalance_message(&got, wire, 0) == 23);
  assert(encode_opening_imbalance_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order On Book Message: 40 bytes ----------------------------------------- */

/* An Order on Book message is generated for all the following situations whenever an order free from any display restrictions is reported by the matching engine. */
typedef struct {
  uint8_t timestamp[6];    /* bytes 0 to 5 */
  uint8_t option_id[4];    /* bytes 6 to 9 */
  uint8_t order_type;      /* byte 10 */
  uint8_t side;            /* byte 11 */
  uint8_t price[4];        /* bytes 12 to 15 */
  uint8_t size[4];         /* bytes 16 to 19 */
  uint8_t exec_flag;       /* byte 20 */
  uint8_t order_capacity;  /* byte 21 */
  uint8_t owner_id[6];     /* bytes 22 to 27 */
  uint8_t giveup[6];       /* bytes 28 to 33 */
  uint8_t cmta[6];         /* bytes 34 to 39 */
} OrderOnBookMessage;

/* any Order On Book Message at all: every byte one the checker chooses */
static void any_order_on_book_message(OrderOnBookMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  record->order_type = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  record->exec_flag = arbitrary();
  record->order_capacity = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->owner_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->giveup[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cmta[i] = arbitrary(); }
}

/* Order On Book Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_order_on_book_message(const OrderOnBookMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  wire[at++] = record->order_type;
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  wire[at++] = record->exec_flag;
  wire[at++] = record->order_capacity;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->owner_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->giveup[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cmta[i]; }

  return at;
}

/* Order On Book Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_order_on_book_message(OrderOnBookMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  record->order_type = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  record->exec_flag = wire[at++];
  record->order_capacity = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->owner_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->giveup[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cmta[i] = wire[at++]; }

  return at;
}

/* what was read of Order On Book Message is what was written, byte for byte */
static void equal_order_on_book_message(const OrderOnBookMessage *read, const OrderOnBookMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  assert(read->order_type == written->order_type);
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  assert(read->exec_flag == written->exec_flag);
  assert(read->order_capacity == written->order_capacity);
  for (size_t i = 0; i < 6; i++) { assert(read->owner_id[i] == written->owner_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->giveup[i] == written->giveup[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cmta[i] == written->cmta[i]); }
}

/* Order On Book Message: written and read back, then read and written back */
static void check_order_on_book_message(void) {
  OrderOnBookMessage sent;
  OrderOnBookMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_order_on_book_message(&sent);
  assert(encode_order_on_book_message(&sent, wire, 0) == 40);
  assert(decode_order_on_book_message(&got, wire, 0) == 40);
  equal_order_on_book_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_order_on_book_message(&got, wire, 0) == 40);
  assert(encode_order_on_book_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_system_event_message();
  check_option_directory_message();
  check_trading_action_message();
  check_security_open_closed_message();
  check_opening_imbalance_message();
  check_order_on_book_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
