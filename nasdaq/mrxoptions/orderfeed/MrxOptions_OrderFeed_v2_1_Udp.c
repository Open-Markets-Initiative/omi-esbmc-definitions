// nasdaq/mrxoptions/orderfeed/MrxOptions_OrderFeed_v2_1_Udp.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Order Feed
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

/* ---- System Event Message: 11 bytes ------------------------------------------ */

/* The system event message type is used to signal a market or data feed handler event. */
typedef struct {
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t timestamp[8];        /* bytes 2 to 9 */
  uint8_t event_code;          /* byte 10 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
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

/* ---- Derivative Directory Message: 62 bytes ---------------------------------- */

/* Derivative Directory Message for active options symbols. */
typedef struct {
  uint8_t tracking_number[2];        /* bytes 0 to 1 */
  uint8_t timestamp[8];              /* bytes 2 to 9 */
  uint8_t instrument_id[4];          /* bytes 10 to 13 */
  uint8_t security_symbol[8];        /* bytes 14 to 21 */
  uint8_t expiration_year;           /* byte 22 */
  uint8_t expiration_month;          /* byte 23 */
  uint8_t expiration_day;            /* byte 24 */
  uint8_t explicit_strike_price[4];  /* bytes 25 to 28 */
  uint8_t option_type;               /* byte 29 */
  uint8_t underlying_symbol[13];     /* bytes 30 to 42 */
  uint8_t closing_type;              /* byte 43 */
  uint8_t tradable;                  /* byte 44 */
  uint8_t mpv;                       /* byte 45 */
  uint8_t reserved_16[16];           /* bytes 46 to 61 */
} DerivativeDirectoryMessage;

/* any Derivative Directory Message at all: every byte one the checker chooses */
static void any_derivative_directory_message(DerivativeDirectoryMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_symbol[i] = arbitrary(); }
  record->expiration_year = arbitrary();
  record->expiration_month = arbitrary();
  record->expiration_day = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->explicit_strike_price[i] = arbitrary(); }
  record->option_type = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->closing_type = arbitrary();
  record->tradable = arbitrary();
  record->mpv = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Derivative Directory Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_derivative_directory_message(const DerivativeDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->expiration_year;
  wire[at++] = record->expiration_month;
  wire[at++] = record->expiration_day;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->explicit_strike_price[i]; }
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->closing_type;
  wire[at++] = record->tradable;
  wire[at++] = record->mpv;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Derivative Directory Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_derivative_directory_message(DerivativeDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_symbol[i] = wire[at++]; }
  record->expiration_year = wire[at++];
  record->expiration_month = wire[at++];
  record->expiration_day = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->explicit_strike_price[i] = wire[at++]; }
  record->option_type = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->closing_type = wire[at++];
  record->tradable = wire[at++];
  record->mpv = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Derivative Directory Message is what was written, byte for byte */
static void equal_derivative_directory_message(const DerivativeDirectoryMessage *read, const DerivativeDirectoryMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->expiration_year == written->expiration_year);
  assert(read->expiration_month == written->expiration_month);
  assert(read->expiration_day == written->expiration_day);
  for (size_t i = 0; i < 4; i++) { assert(read->explicit_strike_price[i] == written->explicit_strike_price[i]); }
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->closing_type == written->closing_type);
  assert(read->tradable == written->tradable);
  assert(read->mpv == written->mpv);
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Derivative Directory Message: written and read back, then read and written back */
static void check_derivative_directory_message(void) {
  DerivativeDirectoryMessage sent;
  DerivativeDirectoryMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_derivative_directory_message(&sent);
  assert(encode_derivative_directory_message(&sent, wire, 0) == 62);
  assert(decode_derivative_directory_message(&got, wire, 0) == 62);
  equal_derivative_directory_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_derivative_directory_message(&got, wire, 0) == 62);
  assert(encode_derivative_directory_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Action Message: 15 bytes ---------------------------------------- */

/* The options system uses this administrative message to indicate the current trading status of an index or equity option within the options market. */
typedef struct {
  uint8_t tracking_number[2];     /* bytes 0 to 1 */
  uint8_t timestamp[8];           /* bytes 2 to 9 */
  uint8_t instrument_id[4];       /* bytes 10 to 13 */
  uint8_t current_trading_state;  /* byte 14 */
} TradingActionMessage;

/* any Trading Action Message at all: every byte one the checker chooses */
static void any_trading_action_message(TradingActionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->current_trading_state = arbitrary();
}

/* Trading Action Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_trading_action_message(const TradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->current_trading_state;

  return at;
}

/* Trading Action Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_trading_action_message(TradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->current_trading_state = wire[at++];

  return at;
}

/* what was read of Trading Action Message is what was written, byte for byte */
static void equal_trading_action_message(const TradingActionMessage *read, const TradingActionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->current_trading_state == written->current_trading_state);
}

/* Trading Action Message: written and read back, then read and written back */
static void check_trading_action_message(void) {
  TradingActionMessage sent;
  TradingActionMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_trading_action_message(&sent);
  assert(encode_trading_action_message(&sent, wire, 0) == 15);
  assert(decode_trading_action_message(&got, wire, 0) == 15);
  equal_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_action_message(&got, wire, 0) == 15);
  assert(encode_trading_action_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message: 60 bytes --------------------------------------------- */

/* The Order Message indicates a new order has been accepted and was added to the displayable book. */
typedef struct {
  uint8_t tracking_number[2];          /* bytes 0 to 1 */
  uint8_t timestamp[8];                /* bytes 2 to 9 */
  uint8_t instrument_id[4];            /* bytes 10 to 13 */
  uint8_t order_reference_number[8];   /* bytes 14 to 21 */
  uint8_t side;                        /* byte 22 */
  uint8_t original_order_volume[4];    /* bytes 23 to 26 */
  uint8_t executable_order_volume[4];  /* bytes 27 to 30 */
  uint8_t order_status;                /* byte 31 */
  uint8_t order_type;                  /* byte 32 */
  uint8_t order_qualifier;             /* byte 33 */
  uint8_t limit_price[4];              /* bytes 34 to 37 */
  uint8_t all_or_none;                 /* byte 38 */
  uint8_t time_in_force;               /* byte 39 */
  uint8_t order_capacity;              /* byte 40 */
  uint8_t open_close_indicator;        /* byte 41 */
  uint8_t owner_id[6];                 /* bytes 42 to 47 */
  uint8_t giveup[6];                   /* bytes 48 to 53 */
  uint8_t cmta[6];                     /* bytes 54 to 59 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->original_order_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executable_order_volume[i] = arbitrary(); }
  record->order_status = arbitrary();
  record->order_type = arbitrary();
  record->order_qualifier = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->limit_price[i] = arbitrary(); }
  record->all_or_none = arbitrary();
  record->time_in_force = arbitrary();
  record->order_capacity = arbitrary();
  record->open_close_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->owner_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->giveup[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cmta[i] = arbitrary(); }
}

/* Add Order Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_order_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executable_order_volume[i]; }
  wire[at++] = record->order_status;
  wire[at++] = record->order_type;
  wire[at++] = record->order_qualifier;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->limit_price[i]; }
  wire[at++] = record->all_or_none;
  wire[at++] = record->time_in_force;
  wire[at++] = record->order_capacity;
  wire[at++] = record->open_close_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->owner_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->giveup[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cmta[i]; }

  return at;
}

/* Add Order Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->original_order_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executable_order_volume[i] = wire[at++]; }
  record->order_status = wire[at++];
  record->order_type = wire[at++];
  record->order_qualifier = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->limit_price[i] = wire[at++]; }
  record->all_or_none = wire[at++];
  record->time_in_force = wire[at++];
  record->order_capacity = wire[at++];
  record->open_close_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->owner_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->giveup[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cmta[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->original_order_volume[i] == written->original_order_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executable_order_volume[i] == written->executable_order_volume[i]); }
  assert(read->order_status == written->order_status);
  assert(read->order_type == written->order_type);
  assert(read->order_qualifier == written->order_qualifier);
  for (size_t i = 0; i < 4; i++) { assert(read->limit_price[i] == written->limit_price[i]); }
  assert(read->all_or_none == written->all_or_none);
  assert(read->time_in_force == written->time_in_force);
  assert(read->order_capacity == written->order_capacity);
  assert(read->open_close_indicator == written->open_close_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->owner_id[i] == written->owner_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->giveup[i] == written->giveup[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cmta[i] == written->cmta[i]); }
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 60);
  assert(decode_add_order_message(&got, wire, 0) == 60);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 60);
  assert(encode_add_order_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Message: 73 bytes ----------------------------------------------- */

/* This message is used to announce auctions, including the opening auction. */
typedef struct {
  uint8_t tracking_number[2];   /* bytes 0 to 1 */
  uint8_t timestamp[8];         /* bytes 2 to 9 */
  uint8_t instrument_id[4];     /* bytes 10 to 13 */
  uint8_t auction_id[4];        /* bytes 14 to 17 */
  uint8_t auction_type;         /* byte 18 */
  uint8_t auction_duration[4];  /* bytes 19 to 22 */
  uint8_t auction_event;        /* byte 23 */
  uint8_t quantity[4];          /* bytes 24 to 27 */
  uint8_t side;                 /* byte 28 */
  uint8_t price[4];             /* bytes 29 to 32 */
  uint8_t imbalance_volume[4];  /* bytes 33 to 36 */
  uint8_t exec_flag;            /* byte 37 */
  uint8_t order_capacity;       /* byte 38 */
  uint8_t owner_id[6];          /* bytes 39 to 44 */
  uint8_t giveup[6];            /* bytes 45 to 50 */
  uint8_t cmta[6];              /* bytes 51 to 56 */
  uint8_t reserved_16[16];      /* bytes 57 to 72 */
} AuctionMessage;

/* any Auction Message at all: every byte one the checker chooses */
static void any_auction_message(AuctionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->auction_duration[i] = arbitrary(); }
  record->auction_event = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->imbalance_volume[i] = arbitrary(); }
  record->exec_flag = arbitrary();
  record->order_capacity = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->owner_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->giveup[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cmta[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Auction Message to the wire: 73 bytes from at, returning where the next byte goes */
static size_t encode_auction_message(const AuctionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_duration[i]; }
  wire[at++] = record->auction_event;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->imbalance_volume[i]; }
  wire[at++] = record->exec_flag;
  wire[at++] = record->order_capacity;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->owner_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->giveup[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cmta[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Auction Message off the wire: 73 bytes from at, returning where the next byte lies */
static size_t decode_auction_message(AuctionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->auction_duration[i] = wire[at++]; }
  record->auction_event = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->imbalance_volume[i] = wire[at++]; }
  record->exec_flag = wire[at++];
  record->order_capacity = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->owner_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->giveup[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cmta[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Message is what was written, byte for byte */
static void equal_auction_message(const AuctionMessage *read, const AuctionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 4; i++) { assert(read->auction_duration[i] == written->auction_duration[i]); }
  assert(read->auction_event == written->auction_event);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->imbalance_volume[i] == written->imbalance_volume[i]); }
  assert(read->exec_flag == written->exec_flag);
  assert(read->order_capacity == written->order_capacity);
  for (size_t i = 0; i < 6; i++) { assert(read->owner_id[i] == written->owner_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->giveup[i] == written->giveup[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cmta[i] == written->cmta[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Auction Message: written and read back, then read and written back */
static void check_auction_message(void) {
  AuctionMessage sent;
  AuctionMessage got;
  uint8_t wire[73];
  uint8_t again[73];

  any_auction_message(&sent);
  assert(encode_auction_message(&sent, wire, 0) == 73);
  assert(decode_auction_message(&got, wire, 0) == 73);
  equal_auction_message(&got, &sent);

  for (size_t i = 0; i < 73; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_message(&got, wire, 0) == 73);
  assert(encode_auction_message(&got, again, 0) == 73);
  for (size_t i = 0; i < 73; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_system_event_message();
  check_derivative_directory_message();
  check_trading_action_message();
  check_add_order_message();
  check_auction_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
