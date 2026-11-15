// nasdaq/iseoptions/depthofmarket/IseOptions_DepthOfMarket_Itch_v2_1_Udp.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Depth Of Market
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

/* ---- Add Order Short Form Message: 32 bytes ---------------------------------- */

/* An Add Order Message indicates that a new order has been accepted and was added to the displayable book. */
typedef struct {
  uint8_t tracking_number[2];         /* bytes 0 to 1 */
  uint8_t timestamp[8];               /* bytes 2 to 9 */
  uint8_t instrument_id[4];           /* bytes 10 to 13 */
  uint8_t order_reference_number[8];  /* bytes 14 to 21 */
  uint8_t side;                       /* byte 22 */
  uint8_t order_capacity;             /* byte 23 */
  uint8_t price_short[2];             /* bytes 24 to 25 */
  uint8_t volume_short[2];            /* bytes 26 to 27 */
  uint8_t reserved_4[4];              /* bytes 28 to 31 */
} AddOrderShortFormMessage;

/* any Add Order Short Form Message at all: every byte one the checker chooses */
static void any_add_order_short_form_message(AddOrderShortFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->side = arbitrary();
  record->order_capacity = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->volume_short[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Add Order Short Form Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_add_order_short_form_message(const AddOrderShortFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->side;
  wire[at++] = record->order_capacity;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->volume_short[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Add Order Short Form Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_add_order_short_form_message(AddOrderShortFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->side = wire[at++];
  record->order_capacity = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->volume_short[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Short Form Message is what was written, byte for byte */
static void equal_add_order_short_form_message(const AddOrderShortFormMessage *read, const AddOrderShortFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->side == written->side);
  assert(read->order_capacity == written->order_capacity);
  for (size_t i = 0; i < 2; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->volume_short[i] == written->volume_short[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Add Order Short Form Message: written and read back, then read and written back */
static void check_add_order_short_form_message(void) {
  AddOrderShortFormMessage sent;
  AddOrderShortFormMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_add_order_short_form_message(&sent);
  assert(encode_add_order_short_form_message(&sent, wire, 0) == 32);
  assert(decode_add_order_short_form_message(&got, wire, 0) == 32);
  equal_add_order_short_form_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_short_form_message(&got, wire, 0) == 32);
  assert(encode_add_order_short_form_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Long Form Message: 36 bytes ----------------------------------- */

/* An Add Order Message indicates that a new order has been accepted and was added to the displayable book. */
typedef struct {
  uint8_t tracking_number[2];         /* bytes 0 to 1 */
  uint8_t timestamp[8];               /* bytes 2 to 9 */
  uint8_t instrument_id[4];           /* bytes 10 to 13 */
  uint8_t order_reference_number[8];  /* bytes 14 to 21 */
  uint8_t side;                       /* byte 22 */
  uint8_t order_capacity;             /* byte 23 */
  uint8_t price_long[4];              /* bytes 24 to 27 */
  uint8_t volume_long[4];             /* bytes 28 to 31 */
  uint8_t reserved_4[4];              /* bytes 32 to 35 */
} AddOrderLongFormMessage;

/* any Add Order Long Form Message at all: every byte one the checker chooses */
static void any_add_order_long_form_message(AddOrderLongFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->side = arbitrary();
  record->order_capacity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Add Order Long Form Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_add_order_long_form_message(const AddOrderLongFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->side;
  wire[at++] = record->order_capacity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Add Order Long Form Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_add_order_long_form_message(AddOrderLongFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->side = wire[at++];
  record->order_capacity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Long Form Message is what was written, byte for byte */
static void equal_add_order_long_form_message(const AddOrderLongFormMessage *read, const AddOrderLongFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->side == written->side);
  assert(read->order_capacity == written->order_capacity);
  for (size_t i = 0; i < 4; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_long[i] == written->volume_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Add Order Long Form Message: written and read back, then read and written back */
static void check_add_order_long_form_message(void) {
  AddOrderLongFormMessage sent;
  AddOrderLongFormMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_add_order_long_form_message(&sent);
  assert(encode_add_order_long_form_message(&sent, wire, 0) == 36);
  assert(decode_add_order_long_form_message(&got, wire, 0) == 36);
  equal_add_order_long_form_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_long_form_message(&got, wire, 0) == 36);
  assert(encode_add_order_long_form_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Quote Short Form Message: 38 bytes ---------------------------------- */

/* An Add Quote Message indicates that a new quote has been accepted and was added to the displayable book. */
typedef struct {
  uint8_t tracking_number[2];       /* bytes 0 to 1 */
  uint8_t timestamp[8];             /* bytes 2 to 9 */
  uint8_t instrument_id[4];         /* bytes 10 to 13 */
  uint8_t bid_reference_number[8];  /* bytes 14 to 21 */
  uint8_t ask_reference_number[8];  /* bytes 22 to 29 */
  uint8_t bid_price_short[2];       /* bytes 30 to 31 */
  uint8_t bid_size_short[2];        /* bytes 32 to 33 */
  uint8_t ask_price_short[2];       /* bytes 34 to 35 */
  uint8_t ask_size_short[2];        /* bytes 36 to 37 */
} AddQuoteShortFormMessage;

/* any Add Quote Short Form Message at all: every byte one the checker chooses */
static void any_add_quote_short_form_message(AddQuoteShortFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_size_short[i] = arbitrary(); }
}

/* Add Quote Short Form Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_add_quote_short_form_message(const AddQuoteShortFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_reference_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_size_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_size_short[i]; }

  return at;
}

/* Add Quote Short Form Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_add_quote_short_form_message(AddQuoteShortFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_size_short[i] = wire[at++]; }

  return at;
}

/* what was read of Add Quote Short Form Message is what was written, byte for byte */
static void equal_add_quote_short_form_message(const AddQuoteShortFormMessage *read, const AddQuoteShortFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_reference_number[i] == written->bid_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_reference_number[i] == written->ask_reference_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_price_short[i] == written->bid_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_size_short[i] == written->bid_size_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_price_short[i] == written->ask_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_size_short[i] == written->ask_size_short[i]); }
}

/* Add Quote Short Form Message: written and read back, then read and written back */
static void check_add_quote_short_form_message(void) {
  AddQuoteShortFormMessage sent;
  AddQuoteShortFormMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_add_quote_short_form_message(&sent);
  assert(encode_add_quote_short_form_message(&sent, wire, 0) == 38);
  assert(decode_add_quote_short_form_message(&got, wire, 0) == 38);
  equal_add_quote_short_form_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_add_quote_short_form_message(&got, wire, 0) == 38);
  assert(encode_add_quote_short_form_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Quote Long Form Message: 46 bytes ----------------------------------- */

/* An Add Quote Message indicates that a new quote has been accepted and was added to the displayable book. */
typedef struct {
  uint8_t tracking_number[2];       /* bytes 0 to 1 */
  uint8_t timestamp[8];             /* bytes 2 to 9 */
  uint8_t instrument_id[4];         /* bytes 10 to 13 */
  uint8_t bid_reference_number[8];  /* bytes 14 to 21 */
  uint8_t ask_reference_number[8];  /* bytes 22 to 29 */
  uint8_t bid_price_long[4];        /* bytes 30 to 33 */
  uint8_t bid_size_long[4];         /* bytes 34 to 37 */
  uint8_t ask_price_long[4];        /* bytes 38 to 41 */
  uint8_t ask_size_long[4];         /* bytes 42 to 45 */
} AddQuoteLongFormMessage;

/* any Add Quote Long Form Message at all: every byte one the checker chooses */
static void any_add_quote_long_form_message(AddQuoteLongFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_long[i] = arbitrary(); }
}

/* Add Quote Long Form Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_add_quote_long_form_message(const AddQuoteLongFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_long[i]; }

  return at;
}

/* Add Quote Long Form Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_add_quote_long_form_message(AddQuoteLongFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_long[i] = wire[at++]; }

  return at;
}

/* what was read of Add Quote Long Form Message is what was written, byte for byte */
static void equal_add_quote_long_form_message(const AddQuoteLongFormMessage *read, const AddQuoteLongFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_reference_number[i] == written->bid_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_reference_number[i] == written->ask_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price_long[i] == written->bid_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_long[i] == written->bid_size_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_price_long[i] == written->ask_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_long[i] == written->ask_size_long[i]); }
}

/* Add Quote Long Form Message: written and read back, then read and written back */
static void check_add_quote_long_form_message(void) {
  AddQuoteLongFormMessage sent;
  AddQuoteLongFormMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_add_quote_long_form_message(&sent);
  assert(encode_add_quote_long_form_message(&sent, wire, 0) == 46);
  assert(decode_add_quote_long_form_message(&got, wire, 0) == 46);
  equal_add_quote_long_form_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_add_quote_long_form_message(&got, wire, 0) == 46);
  assert(encode_add_quote_long_form_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Executed Message: 43 bytes ---------------------------------- */

/* This message is sent whenever a Side order is executed in whole or in part. */
typedef struct {
  uint8_t tracking_number[2];         /* bytes 0 to 1 */
  uint8_t timestamp[8];               /* bytes 2 to 9 */
  uint8_t instrument_id[4];           /* bytes 10 to 13 */
  uint8_t strategy_id[4];             /* bytes 14 to 17 */
  uint8_t order_reference_number[8];  /* bytes 18 to 25 */
  uint8_t executed_volume[4];         /* bytes 26 to 29 */
  uint8_t trade_condition;            /* byte 30 */
  uint8_t auction_id[4];              /* bytes 31 to 34 */
  uint8_t cross_number[4];            /* bytes 35 to 38 */
  uint8_t match_number[4];            /* bytes 39 to 42 */
} SingleSideExecutedMessage;

/* any Single Side Executed Message at all: every byte one the checker chooses */
static void any_single_side_executed_message(SingleSideExecutedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_volume[i] = arbitrary(); }
  record->trade_condition = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
}

/* Single Side Executed Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_single_side_executed_message(const SingleSideExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_volume[i]; }
  wire[at++] = record->trade_condition;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Single Side Executed Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_single_side_executed_message(SingleSideExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_volume[i] = wire[at++]; }
  record->trade_condition = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Executed Message is what was written, byte for byte */
static void equal_single_side_executed_message(const SingleSideExecutedMessage *read, const SingleSideExecutedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_volume[i] == written->executed_volume[i]); }
  assert(read->trade_condition == written->trade_condition);
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_number[i] == written->cross_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Single Side Executed Message: written and read back, then read and written back */
static void check_single_side_executed_message(void) {
  SingleSideExecutedMessage sent;
  SingleSideExecutedMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_single_side_executed_message(&sent);
  assert(encode_single_side_executed_message(&sent, wire, 0) == 43);
  assert(decode_single_side_executed_message(&got, wire, 0) == 43);
  equal_single_side_executed_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_executed_message(&got, wire, 0) == 43);
  assert(encode_single_side_executed_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Executed With Price Message: 48 bytes ----------------------- */

/* This message is sent whenever an incoming Side order is executed against the book in whole or in part at a price different from the initial display price. */
typedef struct {
  uint8_t tracking_number[2];         /* bytes 0 to 1 */
  uint8_t timestamp[8];               /* bytes 2 to 9 */
  uint8_t instrument_id[4];           /* bytes 10 to 13 */
  uint8_t strategy_id[4];             /* bytes 14 to 17 */
  uint8_t order_reference_number[8];  /* bytes 18 to 25 */
  uint8_t cross_number[4];            /* bytes 26 to 29 */
  uint8_t match_number[4];            /* bytes 30 to 33 */
  uint8_t printable;                  /* byte 34 */
  uint8_t price_long[4];              /* bytes 35 to 38 */
  uint8_t volume_long[4];             /* bytes 39 to 42 */
  uint8_t trade_condition;            /* byte 43 */
  uint8_t auction_id[4];              /* bytes 44 to 47 */
} SingleSideExecutedWithPriceMessage;

/* any Single Side Executed With Price Message at all: every byte one the checker chooses */
static void any_single_side_executed_with_price_message(SingleSideExecutedWithPriceMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  record->printable = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = arbitrary(); }
  record->trade_condition = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
}

/* Single Side Executed With Price Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_single_side_executed_with_price_message(const SingleSideExecutedWithPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->printable;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_long[i]; }
  wire[at++] = record->trade_condition;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }

  return at;
}

/* Single Side Executed With Price Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_single_side_executed_with_price_message(SingleSideExecutedWithPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  record->printable = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = wire[at++]; }
  record->trade_condition = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Executed With Price Message is what was written, byte for byte */
static void equal_single_side_executed_with_price_message(const SingleSideExecutedWithPriceMessage *read, const SingleSideExecutedWithPriceMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_number[i] == written->cross_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->printable == written->printable);
  for (size_t i = 0; i < 4; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_long[i] == written->volume_long[i]); }
  assert(read->trade_condition == written->trade_condition);
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
}

/* Single Side Executed With Price Message: written and read back, then read and written back */
static void check_single_side_executed_with_price_message(void) {
  SingleSideExecutedWithPriceMessage sent;
  SingleSideExecutedWithPriceMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_single_side_executed_with_price_message(&sent);
  assert(encode_single_side_executed_with_price_message(&sent, wire, 0) == 48);
  assert(decode_single_side_executed_with_price_message(&got, wire, 0) == 48);
  equal_single_side_executed_with_price_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_executed_with_price_message(&got, wire, 0) == 48);
  assert(encode_single_side_executed_with_price_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Message: 26 bytes ------------------------------------------ */

/* This message is sent whenever an order on the book is modified as a result of a partial cancellation. */
typedef struct {
  uint8_t tracking_number[2];         /* bytes 0 to 1 */
  uint8_t timestamp[8];               /* bytes 2 to 9 */
  uint8_t instrument_id[4];           /* bytes 10 to 13 */
  uint8_t order_reference_number[8];  /* bytes 14 to 21 */
  uint8_t cancelled_volume[4];        /* bytes 22 to 25 */
} OrderCancelMessage;

/* any Order Cancel Message at all: every byte one the checker chooses */
static void any_order_cancel_message(OrderCancelMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancelled_volume[i] = arbitrary(); }
}

/* Order Cancel Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_message(const OrderCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancelled_volume[i]; }

  return at;
}

/* Order Cancel Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_message(OrderCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancelled_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Message is what was written, byte for byte */
static void equal_order_cancel_message(const OrderCancelMessage *read, const OrderCancelMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancelled_volume[i] == written->cancelled_volume[i]); }
}

/* Order Cancel Message: written and read back, then read and written back */
static void check_order_cancel_message(void) {
  OrderCancelMessage sent;
  OrderCancelMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_order_cancel_message(&sent);
  assert(encode_order_cancel_message(&sent, wire, 0) == 26);
  assert(decode_order_cancel_message(&got, wire, 0) == 26);
  equal_order_cancel_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_message(&got, wire, 0) == 26);
  assert(encode_order_cancel_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Replace Short Form Message: 34 bytes ------------------------ */

/* This message is sent whenever an order or one side of a quote on the book is replaced. */
typedef struct {
  uint8_t tracking_number[2];         /* bytes 0 to 1 */
  uint8_t timestamp[8];               /* bytes 2 to 9 */
  uint8_t instrument_id[4];           /* bytes 10 to 13 */
  uint8_t order_reference_number[8];  /* bytes 14 to 21 */
  uint8_t new_reference_number[8];    /* bytes 22 to 29 */
  uint8_t price_short[2];             /* bytes 30 to 31 */
  uint8_t volume_short[2];            /* bytes 32 to 33 */
} SingleSideReplaceShortFormMessage;

/* any Single Side Replace Short Form Message at all: every byte one the checker chooses */
static void any_single_side_replace_short_form_message(SingleSideReplaceShortFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->volume_short[i] = arbitrary(); }
}

/* Single Side Replace Short Form Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_single_side_replace_short_form_message(const SingleSideReplaceShortFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_reference_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->volume_short[i]; }

  return at;
}

/* Single Side Replace Short Form Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_single_side_replace_short_form_message(SingleSideReplaceShortFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->volume_short[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Replace Short Form Message is what was written, byte for byte */
static void equal_single_side_replace_short_form_message(const SingleSideReplaceShortFormMessage *read, const SingleSideReplaceShortFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_reference_number[i] == written->new_reference_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->volume_short[i] == written->volume_short[i]); }
}

/* Single Side Replace Short Form Message: written and read back, then read and written back */
static void check_single_side_replace_short_form_message(void) {
  SingleSideReplaceShortFormMessage sent;
  SingleSideReplaceShortFormMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_single_side_replace_short_form_message(&sent);
  assert(encode_single_side_replace_short_form_message(&sent, wire, 0) == 34);
  assert(decode_single_side_replace_short_form_message(&got, wire, 0) == 34);
  equal_single_side_replace_short_form_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_replace_short_form_message(&got, wire, 0) == 34);
  assert(encode_single_side_replace_short_form_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Replace Long Form Message: 38 bytes ------------------------- */

/* This message is sent whenever an order or one side of a quote on the book is replaced. */
typedef struct {
  uint8_t tracking_number[2];         /* bytes 0 to 1 */
  uint8_t timestamp[8];               /* bytes 2 to 9 */
  uint8_t instrument_id[4];           /* bytes 10 to 13 */
  uint8_t order_reference_number[8];  /* bytes 14 to 21 */
  uint8_t new_reference_number[8];    /* bytes 22 to 29 */
  uint8_t price_long[4];              /* bytes 30 to 33 */
  uint8_t volume_long[4];             /* bytes 34 to 37 */
} SingleSideReplaceLongFormMessage;

/* any Single Side Replace Long Form Message at all: every byte one the checker chooses */
static void any_single_side_replace_long_form_message(SingleSideReplaceLongFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = arbitrary(); }
}

/* Single Side Replace Long Form Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_single_side_replace_long_form_message(const SingleSideReplaceLongFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_long[i]; }

  return at;
}

/* Single Side Replace Long Form Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_single_side_replace_long_form_message(SingleSideReplaceLongFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Replace Long Form Message is what was written, byte for byte */
static void equal_single_side_replace_long_form_message(const SingleSideReplaceLongFormMessage *read, const SingleSideReplaceLongFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_reference_number[i] == written->new_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_long[i] == written->volume_long[i]); }
}

/* Single Side Replace Long Form Message: written and read back, then read and written back */
static void check_single_side_replace_long_form_message(void) {
  SingleSideReplaceLongFormMessage sent;
  SingleSideReplaceLongFormMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_single_side_replace_long_form_message(&sent);
  assert(encode_single_side_replace_long_form_message(&sent, wire, 0) == 38);
  assert(decode_single_side_replace_long_form_message(&got, wire, 0) == 38);
  equal_single_side_replace_long_form_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_replace_long_form_message(&got, wire, 0) == 38);
  assert(encode_single_side_replace_long_form_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Delete Message: 22 bytes ------------------------------------ */

/* The message is sent when an order or a side of a quote is being cancelled. All remaining contracts are no longer accessible so the side should be removed from the book. */
typedef struct {
  uint8_t tracking_number[2];         /* bytes 0 to 1 */
  uint8_t timestamp[8];               /* bytes 2 to 9 */
  uint8_t instrument_id[4];           /* bytes 10 to 13 */
  uint8_t order_reference_number[8];  /* bytes 14 to 21 */
} SingleSideDeleteMessage;

/* any Single Side Delete Message at all: every byte one the checker chooses */
static void any_single_side_delete_message(SingleSideDeleteMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
}

/* Single Side Delete Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_single_side_delete_message(const SingleSideDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }

  return at;
}

/* Single Side Delete Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_single_side_delete_message(SingleSideDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Delete Message is what was written, byte for byte */
static void equal_single_side_delete_message(const SingleSideDeleteMessage *read, const SingleSideDeleteMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
}

/* Single Side Delete Message: written and read back, then read and written back */
static void check_single_side_delete_message(void) {
  SingleSideDeleteMessage sent;
  SingleSideDeleteMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_single_side_delete_message(&sent);
  assert(encode_single_side_delete_message(&sent, wire, 0) == 22);
  assert(decode_single_side_delete_message(&got, wire, 0) == 22);
  equal_single_side_delete_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_delete_message(&got, wire, 0) == 22);
  assert(encode_single_side_delete_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Update Message: 31 bytes ------------------------------------ */

/* This message is sent whenever an order or a side of a quote is being updated for price and (or) contracts. */
typedef struct {
  uint8_t tracking_number[2];         /* bytes 0 to 1 */
  uint8_t timestamp[8];               /* bytes 2 to 9 */
  uint8_t instrument_id[4];           /* bytes 10 to 13 */
  uint8_t order_reference_number[8];  /* bytes 14 to 21 */
  uint8_t change_reason;              /* byte 22 */
  uint8_t price_long[4];              /* bytes 23 to 26 */
  uint8_t volume_long[4];             /* bytes 27 to 30 */
} SingleSideUpdateMessage;

/* any Single Side Update Message at all: every byte one the checker chooses */
static void any_single_side_update_message(SingleSideUpdateMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->change_reason = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = arbitrary(); }
}

/* Single Side Update Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_single_side_update_message(const SingleSideUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->change_reason;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_long[i]; }

  return at;
}

/* Single Side Update Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_single_side_update_message(SingleSideUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->change_reason = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Update Message is what was written, byte for byte */
static void equal_single_side_update_message(const SingleSideUpdateMessage *read, const SingleSideUpdateMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->change_reason == written->change_reason);
  for (size_t i = 0; i < 4; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_long[i] == written->volume_long[i]); }
}

/* Single Side Update Message: written and read back, then read and written back */
static void check_single_side_update_message(void) {
  SingleSideUpdateMessage sent;
  SingleSideUpdateMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_single_side_update_message(&sent);
  assert(encode_single_side_update_message(&sent, wire, 0) == 31);
  assert(decode_single_side_update_message(&got, wire, 0) == 31);
  equal_single_side_update_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_update_message(&got, wire, 0) == 31);
  assert(encode_single_side_update_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Replace Short Form Message: 54 bytes ------------------------------ */

/* This message is sent whenever a quote on the book is replaced. */
typedef struct {
  uint8_t tracking_number[2];                /* bytes 0 to 1 */
  uint8_t timestamp[8];                      /* bytes 2 to 9 */
  uint8_t instrument_id[4];                  /* bytes 10 to 13 */
  uint8_t original_bid_reference_number[8];  /* bytes 14 to 21 */
  uint8_t bid_reference_number[8];           /* bytes 22 to 29 */
  uint8_t original_ask_reference_number[8];  /* bytes 30 to 37 */
  uint8_t ask_reference_number[8];           /* bytes 38 to 45 */
  uint8_t bid_price_short[2];                /* bytes 46 to 47 */
  uint8_t bid_size_short[2];                 /* bytes 48 to 49 */
  uint8_t ask_price_short[2];                /* bytes 50 to 51 */
  uint8_t ask_size_short[2];                 /* bytes 52 to 53 */
} QuoteReplaceShortFormMessage;

/* any Quote Replace Short Form Message at all: every byte one the checker chooses */
static void any_quote_replace_short_form_message(QuoteReplaceShortFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_bid_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_ask_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_size_short[i] = arbitrary(); }
}

/* Quote Replace Short Form Message to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_quote_replace_short_form_message(const QuoteReplaceShortFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_bid_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_ask_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_reference_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_size_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_size_short[i]; }

  return at;
}

/* Quote Replace Short Form Message off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_quote_replace_short_form_message(QuoteReplaceShortFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_bid_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_ask_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_size_short[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Replace Short Form Message is what was written, byte for byte */
static void equal_quote_replace_short_form_message(const QuoteReplaceShortFormMessage *read, const QuoteReplaceShortFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_bid_reference_number[i] == written->original_bid_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_reference_number[i] == written->bid_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_ask_reference_number[i] == written->original_ask_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_reference_number[i] == written->ask_reference_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_price_short[i] == written->bid_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_size_short[i] == written->bid_size_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_price_short[i] == written->ask_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_size_short[i] == written->ask_size_short[i]); }
}

/* Quote Replace Short Form Message: written and read back, then read and written back */
static void check_quote_replace_short_form_message(void) {
  QuoteReplaceShortFormMessage sent;
  QuoteReplaceShortFormMessage got;
  uint8_t wire[54];
  uint8_t again[54];

  any_quote_replace_short_form_message(&sent);
  assert(encode_quote_replace_short_form_message(&sent, wire, 0) == 54);
  assert(decode_quote_replace_short_form_message(&got, wire, 0) == 54);
  equal_quote_replace_short_form_message(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_replace_short_form_message(&got, wire, 0) == 54);
  assert(encode_quote_replace_short_form_message(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Replace Long Form Message: 62 bytes ------------------------------- */

/* This message is sent whenever a quote on the book is replaced. */
typedef struct {
  uint8_t tracking_number[2];                /* bytes 0 to 1 */
  uint8_t timestamp[8];                      /* bytes 2 to 9 */
  uint8_t instrument_id[4];                  /* bytes 10 to 13 */
  uint8_t original_bid_reference_number[8];  /* bytes 14 to 21 */
  uint8_t bid_reference_number[8];           /* bytes 22 to 29 */
  uint8_t original_ask_reference_number[8];  /* bytes 30 to 37 */
  uint8_t ask_reference_number[8];           /* bytes 38 to 45 */
  uint8_t bid_price_long[4];                 /* bytes 46 to 49 */
  uint8_t bid_size_long[4];                  /* bytes 50 to 53 */
  uint8_t ask_price_long[4];                 /* bytes 54 to 57 */
  uint8_t ask_size_long[4];                  /* bytes 58 to 61 */
} QuoteReplaceLongFormMessage;

/* any Quote Replace Long Form Message at all: every byte one the checker chooses */
static void any_quote_replace_long_form_message(QuoteReplaceLongFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_bid_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_ask_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_long[i] = arbitrary(); }
}

/* Quote Replace Long Form Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_quote_replace_long_form_message(const QuoteReplaceLongFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_bid_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_ask_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_long[i]; }

  return at;
}

/* Quote Replace Long Form Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_quote_replace_long_form_message(QuoteReplaceLongFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_bid_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_ask_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_long[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Replace Long Form Message is what was written, byte for byte */
static void equal_quote_replace_long_form_message(const QuoteReplaceLongFormMessage *read, const QuoteReplaceLongFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_bid_reference_number[i] == written->original_bid_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_reference_number[i] == written->bid_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_ask_reference_number[i] == written->original_ask_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_reference_number[i] == written->ask_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price_long[i] == written->bid_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_long[i] == written->bid_size_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_price_long[i] == written->ask_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_long[i] == written->ask_size_long[i]); }
}

/* Quote Replace Long Form Message: written and read back, then read and written back */
static void check_quote_replace_long_form_message(void) {
  QuoteReplaceLongFormMessage sent;
  QuoteReplaceLongFormMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_quote_replace_long_form_message(&sent);
  assert(encode_quote_replace_long_form_message(&sent, wire, 0) == 62);
  assert(decode_quote_replace_long_form_message(&got, wire, 0) == 62);
  equal_quote_replace_long_form_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_replace_long_form_message(&got, wire, 0) == 62);
  assert(encode_quote_replace_long_form_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Delete Message: 30 bytes ------------------------------------------ */

/* The message is sent when a single quote is being cancelled. */
typedef struct {
  uint8_t tracking_number[2];       /* bytes 0 to 1 */
  uint8_t timestamp[8];             /* bytes 2 to 9 */
  uint8_t instrument_id[4];         /* bytes 10 to 13 */
  uint8_t bid_reference_number[8];  /* bytes 14 to 21 */
  uint8_t ask_reference_number[8];  /* bytes 22 to 29 */
} QuoteDeleteMessage;

/* any Quote Delete Message at all: every byte one the checker chooses */
static void any_quote_delete_message(QuoteDeleteMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = arbitrary(); }
}

/* Quote Delete Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_quote_delete_message(const QuoteDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_reference_number[i]; }

  return at;
}

/* Quote Delete Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_quote_delete_message(QuoteDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Delete Message is what was written, byte for byte */
static void equal_quote_delete_message(const QuoteDeleteMessage *read, const QuoteDeleteMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_reference_number[i] == written->bid_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_reference_number[i] == written->ask_reference_number[i]); }
}

/* Quote Delete Message: written and read back, then read and written back */
static void check_quote_delete_message(void) {
  QuoteDeleteMessage sent;
  QuoteDeleteMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_quote_delete_message(&sent);
  assert(encode_quote_delete_message(&sent, wire, 0) == 30);
  assert(decode_quote_delete_message(&got, wire, 0) == 30);
  equal_quote_delete_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_delete_message(&got, wire, 0) == 30);
  assert(encode_quote_delete_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 58 bytes ------------------------------------------------- */

/* This Options Trade Message is designed to provide execution details for normal match events involving non-displayable order types. */
typedef struct {
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t timestamp[8];        /* bytes 2 to 9 */
  uint8_t instrument_id[4];    /* bytes 10 to 13 */
  uint8_t cross_number[4];     /* bytes 14 to 17 */
  uint8_t match_number[4];     /* bytes 18 to 21 */
  uint8_t strategy_id[4];      /* bytes 22 to 25 */
  uint8_t cross_type;          /* byte 26 */
  uint8_t price_long[4];       /* bytes 27 to 30 */
  uint8_t volume_long[4];      /* bytes 31 to 34 */
  uint8_t trade_condition;     /* byte 35 */
  uint8_t auction_id[4];       /* bytes 36 to 39 */
  uint8_t printable;           /* byte 40 */
  uint8_t trade_type;          /* byte 41 */
  uint8_t reserved_16[16];     /* bytes 42 to 57 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  record->cross_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = arbitrary(); }
  record->trade_condition = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  record->printable = arbitrary();
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Trade Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  wire[at++] = record->cross_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_long[i]; }
  wire[at++] = record->trade_condition;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  wire[at++] = record->printable;
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Trade Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  record->cross_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = wire[at++]; }
  record->trade_condition = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  record->printable = wire[at++];
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_number[i] == written->cross_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  assert(read->cross_type == written->cross_type);
  for (size_t i = 0; i < 4; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_long[i] == written->volume_long[i]); }
  assert(read->trade_condition == written->trade_condition);
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  assert(read->printable == written->printable);
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 58);
  assert(decode_trade_message(&got, wire, 0) == 58);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 58);
  assert(encode_trade_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- Net Order Imbalance Message: 33 bytes ----------------------------------- */

/* This message is used to announce opening and re-opening auctions only. */
typedef struct {
  uint8_t tracking_number[2];        /* bytes 0 to 1 */
  uint8_t timestamp[8];              /* bytes 2 to 9 */
  uint8_t instrument_id[4];          /* bytes 10 to 13 */
  uint8_t auction_id[4];             /* bytes 14 to 17 */
  uint8_t auction_type;              /* byte 18 */
  uint8_t paired_quantity[4];        /* bytes 19 to 22 */
  uint8_t side_imbalance_direction;  /* byte 23 */
  uint8_t price_imbalance_price[4];  /* bytes 24 to 27 */
  uint8_t imbalance_volume[4];       /* bytes 28 to 31 */
  uint8_t order_capacity;            /* byte 32 */
} NetOrderImbalanceMessage;

/* any Net Order Imbalance Message at all: every byte one the checker chooses */
static void any_net_order_imbalance_message(NetOrderImbalanceMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->paired_quantity[i] = arbitrary(); }
  record->side_imbalance_direction = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_imbalance_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->imbalance_volume[i] = arbitrary(); }
  record->order_capacity = arbitrary();
}

/* Net Order Imbalance Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_net_order_imbalance_message(const NetOrderImbalanceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->paired_quantity[i]; }
  wire[at++] = record->side_imbalance_direction;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_imbalance_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->imbalance_volume[i]; }
  wire[at++] = record->order_capacity;

  return at;
}

/* Net Order Imbalance Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_net_order_imbalance_message(NetOrderImbalanceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->paired_quantity[i] = wire[at++]; }
  record->side_imbalance_direction = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_imbalance_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->imbalance_volume[i] = wire[at++]; }
  record->order_capacity = wire[at++];

  return at;
}

/* what was read of Net Order Imbalance Message is what was written, byte for byte */
static void equal_net_order_imbalance_message(const NetOrderImbalanceMessage *read, const NetOrderImbalanceMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 4; i++) { assert(read->paired_quantity[i] == written->paired_quantity[i]); }
  assert(read->side_imbalance_direction == written->side_imbalance_direction);
  for (size_t i = 0; i < 4; i++) { assert(read->price_imbalance_price[i] == written->price_imbalance_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->imbalance_volume[i] == written->imbalance_volume[i]); }
  assert(read->order_capacity == written->order_capacity);
}

/* Net Order Imbalance Message: written and read back, then read and written back */
static void check_net_order_imbalance_message(void) {
  NetOrderImbalanceMessage sent;
  NetOrderImbalanceMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_net_order_imbalance_message(&sent);
  assert(encode_net_order_imbalance_message(&sent, wire, 0) == 33);
  assert(decode_net_order_imbalance_message(&got, wire, 0) == 33);
  equal_net_order_imbalance_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_net_order_imbalance_message(&got, wire, 0) == 33);
  assert(encode_net_order_imbalance_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_system_event_message();
  check_derivative_directory_message();
  check_trading_action_message();
  check_add_order_short_form_message();
  check_add_order_long_form_message();
  check_add_quote_short_form_message();
  check_add_quote_long_form_message();
  check_single_side_executed_message();
  check_single_side_executed_with_price_message();
  check_order_cancel_message();
  check_single_side_replace_short_form_message();
  check_single_side_replace_long_form_message();
  check_single_side_delete_message();
  check_single_side_update_message();
  check_quote_replace_short_form_message();
  check_quote_replace_long_form_message();
  check_quote_delete_message();
  check_trade_message();
  check_net_order_imbalance_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
