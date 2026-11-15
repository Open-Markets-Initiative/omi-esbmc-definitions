// nasdaq/phlxoptions/depthofmarket/PhlxOptions_DepthOfMarket_v1_6.c
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

/* ---- Seconds Message: 4 bytes ------------------------------------------------ */

/* This message is sent every second for which at least one PHLX Depth message is being generated. */
typedef struct {
  uint8_t second[4];  /* bytes 0 to 3 */
} SecondsMessage;

/* any Seconds Message at all: every byte one the checker chooses */
static void any_seconds_message(SecondsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = arbitrary(); }
}

/* Seconds Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_seconds_message(const SecondsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->second[i]; }

  return at;
}

/* Seconds Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_seconds_message(SecondsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = wire[at++]; }

  return at;
}

/* what was read of Seconds Message is what was written, byte for byte */
static void equal_seconds_message(const SecondsMessage *read, const SecondsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->second[i] == written->second[i]); }
}

/* Seconds Message: written and read back, then read and written back */
static void check_seconds_message(void) {
  SecondsMessage sent;
  SecondsMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_seconds_message(&sent);
  assert(encode_seconds_message(&sent, wire, 0) == 4);
  assert(decode_seconds_message(&got, wire, 0) == 4);
  equal_seconds_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_seconds_message(&got, wire, 0) == 4);
  assert(encode_seconds_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 5 bytes ------------------------------------------- */

/* The system event message type is used to signal a market or data feed handler event. */
typedef struct {
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t event_code;      /* byte 4 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  assert(read->event_code == written->event_code);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 5);
  assert(decode_system_event_message(&got, wire, 0) == 5);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 5);
  assert(encode_system_event_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Base Reference Message: 12 bytes ---------------------------------------- */

/* This message indicates the base reference number to which all the order/quote/trade reference number deltas must be added to obtain the absolute order/quote PHLX reference number. */
typedef struct {
  uint8_t nanoseconds[4];            /* bytes 0 to 3 */
  uint8_t base_reference_number[8];  /* bytes 4 to 11 */
} BaseReferenceMessage;

/* any Base Reference Message at all: every byte one the checker chooses */
static void any_base_reference_message(BaseReferenceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->base_reference_number[i] = arbitrary(); }
}

/* Base Reference Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_base_reference_message(const BaseReferenceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->base_reference_number[i]; }

  return at;
}

/* Base Reference Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_base_reference_message(BaseReferenceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->base_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Base Reference Message is what was written, byte for byte */
static void equal_base_reference_message(const BaseReferenceMessage *read, const BaseReferenceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->base_reference_number[i] == written->base_reference_number[i]); }
}

/* Base Reference Message: written and read back, then read and written back */
static void check_base_reference_message(void) {
  BaseReferenceMessage sent;
  BaseReferenceMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_base_reference_message(&sent);
  assert(encode_base_reference_message(&sent, wire, 0) == 12);
  assert(decode_base_reference_message(&got, wire, 0) == 12);
  equal_base_reference_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_base_reference_message(&got, wire, 0) == 12);
  assert(encode_base_reference_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Option Directory Message: 39 bytes -------------------------------------- */

/* At the start of each trading day, the options system disseminates option symbol directory messages for all active option symbols in the PHLX ® options system. */
typedef struct {
  uint8_t nanoseconds[4];            /* bytes 0 to 3 */
  uint8_t option_id[4];              /* bytes 4 to 7 */
  uint8_t security_symbol[6];        /* bytes 8 to 13 */
  uint8_t expiration_year;           /* byte 14 */
  uint8_t expiration_month;          /* byte 15 */
  uint8_t expiration_date;           /* byte 16 */
  uint8_t explicit_strike_price[4];  /* bytes 17 to 20 */
  uint8_t option_type;               /* byte 21 */
  uint8_t source;                    /* byte 22 */
  uint8_t underlying_symbol[13];     /* bytes 23 to 35 */
  uint8_t options_closing_type;      /* byte 36 */
  uint8_t tradable;                  /* byte 37 */
  uint8_t mpv;                       /* byte 38 */
} OptionDirectoryMessage;

/* any Option Directory Message at all: every byte one the checker chooses */
static void any_option_directory_message(OptionDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->security_symbol[i] = arbitrary(); }
  record->expiration_year = arbitrary();
  record->expiration_month = arbitrary();
  record->expiration_date = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->explicit_strike_price[i] = arbitrary(); }
  record->option_type = arbitrary();
  record->source = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->options_closing_type = arbitrary();
  record->tradable = arbitrary();
  record->mpv = arbitrary();
}

/* Option Directory Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_option_directory_message(const OptionDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->expiration_year;
  wire[at++] = record->expiration_month;
  wire[at++] = record->expiration_date;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->explicit_strike_price[i]; }
  wire[at++] = record->option_type;
  wire[at++] = record->source;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->options_closing_type;
  wire[at++] = record->tradable;
  wire[at++] = record->mpv;

  return at;
}

/* Option Directory Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_option_directory_message(OptionDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->security_symbol[i] = wire[at++]; }
  record->expiration_year = wire[at++];
  record->expiration_month = wire[at++];
  record->expiration_date = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->explicit_strike_price[i] = wire[at++]; }
  record->option_type = wire[at++];
  record->source = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->options_closing_type = wire[at++];
  record->tradable = wire[at++];
  record->mpv = wire[at++];

  return at;
}

/* what was read of Option Directory Message is what was written, byte for byte */
static void equal_option_directory_message(const OptionDirectoryMessage *read, const OptionDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->expiration_year == written->expiration_year);
  assert(read->expiration_month == written->expiration_month);
  assert(read->expiration_date == written->expiration_date);
  for (size_t i = 0; i < 4; i++) { assert(read->explicit_strike_price[i] == written->explicit_strike_price[i]); }
  assert(read->option_type == written->option_type);
  assert(read->source == written->source);
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->options_closing_type == written->options_closing_type);
  assert(read->tradable == written->tradable);
  assert(read->mpv == written->mpv);
}

/* Option Directory Message: written and read back, then read and written back */
static void check_option_directory_message(void) {
  OptionDirectoryMessage sent;
  OptionDirectoryMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_option_directory_message(&sent);
  assert(encode_option_directory_message(&sent, wire, 0) == 39);
  assert(decode_option_directory_message(&got, wire, 0) == 39);
  equal_option_directory_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_option_directory_message(&got, wire, 0) == 39);
  assert(encode_option_directory_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Action Message: 9 bytes ----------------------------------------- */

/* The options system uses this administrative message to indicate the current trading status of an index or equity option within the PHLX Options Market. */
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

/* ---- Security Open Message: 9 bytes ------------------------------------------ */

/* The options system plans to disseminate the Option Open Message for each option as soon as the opening is completed. Upon receipt of the open state message, firms should be advised that the option denoted in the message is now available for auto execution within the PHLX ® Options Market System. Upon receipt of the closed state message, firms should be advised that the option is no longer eligible for auto-execution within the Options Market System. */
typedef struct {
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t option_id[4];    /* bytes 4 to 7 */
  uint8_t open_state;      /* byte 8 */
} SecurityOpenMessage;

/* any Security Open Message at all: every byte one the checker chooses */
static void any_security_open_message(SecurityOpenMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  record->open_state = arbitrary();
}

/* Security Open Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_security_open_message(const SecurityOpenMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  wire[at++] = record->open_state;

  return at;
}

/* Security Open Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_security_open_message(SecurityOpenMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  record->open_state = wire[at++];

  return at;
}

/* what was read of Security Open Message is what was written, byte for byte */
static void equal_security_open_message(const SecurityOpenMessage *read, const SecurityOpenMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  assert(read->open_state == written->open_state);
}

/* Security Open Message: written and read back, then read and written back */
static void check_security_open_message(void) {
  SecurityOpenMessage sent;
  SecurityOpenMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_security_open_message(&sent);
  assert(encode_security_open_message(&sent, wire, 0) == 9);
  assert(decode_security_open_message(&got, wire, 0) == 9);
  equal_security_open_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_security_open_message(&got, wire, 0) == 9);
  assert(encode_security_open_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Short Message: 21 bytes --------------------------------------- */

/* An Add Order Message indicates that a new order has been accepted by the options system and was added to the displayable book. The message includes a day-unique Order Reference Number used by options system to track the order. */
typedef struct {
  uint8_t nanoseconds[4];                   /* bytes 0 to 3 */
  uint8_t order_reference_number_delta[4];  /* bytes 4 to 7 */
  uint8_t market_side;                      /* byte 8 */
  uint8_t option_id[4];                     /* bytes 9 to 12 */
  uint8_t short_price[2];                   /* bytes 13 to 14 */
  uint8_t short_volume[2];                  /* bytes 15 to 16 */
  uint8_t order_id[4];                      /* bytes 17 to 20 */
} AddOrderShortMessage;

/* any Add Order Short Message at all: every byte one the checker chooses */
static void any_add_order_short_message(AddOrderShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number_delta[i] = arbitrary(); }
  record->market_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->short_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->short_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
}

/* Add Order Short Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_add_order_short_message(const AddOrderShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_reference_number_delta[i]; }
  wire[at++] = record->market_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->short_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->short_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Add Order Short Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_add_order_short_message(AddOrderShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number_delta[i] = wire[at++]; }
  record->market_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->short_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->short_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Short Message is what was written, byte for byte */
static void equal_add_order_short_message(const AddOrderShortMessage *read, const AddOrderShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_reference_number_delta[i] == written->order_reference_number_delta[i]); }
  assert(read->market_side == written->market_side);
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->short_price[i] == written->short_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->short_volume[i] == written->short_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Add Order Short Message: written and read back, then read and written back */
static void check_add_order_short_message(void) {
  AddOrderShortMessage sent;
  AddOrderShortMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_add_order_short_message(&sent);
  assert(encode_add_order_short_message(&sent, wire, 0) == 21);
  assert(decode_add_order_short_message(&got, wire, 0) == 21);
  equal_add_order_short_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_short_message(&got, wire, 0) == 21);
  assert(encode_add_order_short_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Long Message: 25 bytes ---------------------------------------- */

/* An Add Order Message indicates that a new order has been accepted by the options system and was added to the displayable book. The message includes a day-unique Order Reference Number used by options system to track the order. */
typedef struct {
  uint8_t nanoseconds[4];                   /* bytes 0 to 3 */
  uint8_t order_reference_number_delta[4];  /* bytes 4 to 7 */
  uint8_t market_side;                      /* byte 8 */
  uint8_t option_id[4];                     /* bytes 9 to 12 */
  uint8_t price[4];                         /* bytes 13 to 16 */
  uint8_t volume[4];                        /* bytes 17 to 20 */
  uint8_t order_id[4];                      /* bytes 21 to 24 */
} AddOrderLongMessage;

/* any Add Order Long Message at all: every byte one the checker chooses */
static void any_add_order_long_message(AddOrderLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number_delta[i] = arbitrary(); }
  record->market_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
}

/* Add Order Long Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_add_order_long_message(const AddOrderLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_reference_number_delta[i]; }
  wire[at++] = record->market_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Add Order Long Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_add_order_long_message(AddOrderLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number_delta[i] = wire[at++]; }
  record->market_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Long Message is what was written, byte for byte */
static void equal_add_order_long_message(const AddOrderLongMessage *read, const AddOrderLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_reference_number_delta[i] == written->order_reference_number_delta[i]); }
  assert(read->market_side == written->market_side);
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Add Order Long Message: written and read back, then read and written back */
static void check_add_order_long_message(void) {
  AddOrderLongMessage sent;
  AddOrderLongMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_add_order_long_message(&sent);
  assert(encode_add_order_long_message(&sent, wire, 0) == 25);
  assert(decode_add_order_long_message(&got, wire, 0) == 25);
  equal_add_order_long_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_long_message(&got, wire, 0) == 25);
  assert(encode_add_order_long_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Quote Short Message: 24 bytes --------------------------------------- */

/* An Add Quote Message indicates that a new quote has been accepted by the PHLX ® options system and was added to the displayable book. The message includes a unique Bid/Ask Reference Numbers used by the options system to track the quote. */
typedef struct {
  uint8_t nanoseconds[4];                 /* bytes 0 to 3 */
  uint8_t bid_reference_number_delta[4];  /* bytes 4 to 7 */
  uint8_t ask_reference_number_delta[4];  /* bytes 8 to 11 */
  uint8_t option_id[4];                   /* bytes 12 to 15 */
  uint8_t short_bid_price[2];             /* bytes 16 to 17 */
  uint8_t short_bid_size[2];              /* bytes 18 to 19 */
  uint8_t short_ask_price[2];             /* bytes 20 to 21 */
  uint8_t short_ask_size[2];              /* bytes 22 to 23 */
} AddQuoteShortMessage;

/* any Add Quote Short Message at all: every byte one the checker chooses */
static void any_add_quote_short_message(AddQuoteShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->short_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->short_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->short_ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->short_ask_size[i] = arbitrary(); }
}

/* Add Quote Short Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_add_quote_short_message(const AddQuoteShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->short_bid_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->short_bid_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->short_ask_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->short_ask_size[i]; }

  return at;
}

/* Add Quote Short Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_add_quote_short_message(AddQuoteShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->short_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->short_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->short_ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->short_ask_size[i] = wire[at++]; }

  return at;
}

/* what was read of Add Quote Short Message is what was written, byte for byte */
static void equal_add_quote_short_message(const AddQuoteShortMessage *read, const AddQuoteShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_reference_number_delta[i] == written->bid_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_reference_number_delta[i] == written->ask_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->short_bid_price[i] == written->short_bid_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->short_bid_size[i] == written->short_bid_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->short_ask_price[i] == written->short_ask_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->short_ask_size[i] == written->short_ask_size[i]); }
}

/* Add Quote Short Message: written and read back, then read and written back */
static void check_add_quote_short_message(void) {
  AddQuoteShortMessage sent;
  AddQuoteShortMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_add_quote_short_message(&sent);
  assert(encode_add_quote_short_message(&sent, wire, 0) == 24);
  assert(decode_add_quote_short_message(&got, wire, 0) == 24);
  equal_add_quote_short_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_add_quote_short_message(&got, wire, 0) == 24);
  assert(encode_add_quote_short_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Quote Long Message: 32 bytes ---------------------------------------- */

/* An Add Quote Message indicates that a new quote has been accepted by the PHLX ® options system and was added to the displayable book. The message includes a unique Bid/Ask Reference Numbers used by the options system to track the quote. */
typedef struct {
  uint8_t nanoseconds[4];                 /* bytes 0 to 3 */
  uint8_t bid_reference_number_delta[4];  /* bytes 4 to 7 */
  uint8_t ask_reference_number_delta[4];  /* bytes 8 to 11 */
  uint8_t option_id[4];                   /* bytes 12 to 15 */
  uint8_t bid_price[4];                   /* bytes 16 to 19 */
  uint8_t bid_size[4];                    /* bytes 20 to 23 */
  uint8_t ask_price[4];                   /* bytes 24 to 27 */
  uint8_t ask_size[4];                    /* bytes 28 to 31 */
} AddQuoteLongMessage;

/* any Add Quote Long Message at all: every byte one the checker chooses */
static void any_add_quote_long_message(AddQuoteLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size[i] = arbitrary(); }
}

/* Add Quote Long Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_add_quote_long_message(const AddQuoteLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size[i]; }

  return at;
}

/* Add Quote Long Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_add_quote_long_message(AddQuoteLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size[i] = wire[at++]; }

  return at;
}

/* what was read of Add Quote Long Message is what was written, byte for byte */
static void equal_add_quote_long_message(const AddQuoteLongMessage *read, const AddQuoteLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_reference_number_delta[i] == written->bid_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_reference_number_delta[i] == written->ask_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size[i] == written->bid_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_price[i] == written->ask_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size[i] == written->ask_size[i]); }
}

/* Add Quote Long Message: written and read back, then read and written back */
static void check_add_quote_long_message(void) {
  AddQuoteLongMessage sent;
  AddQuoteLongMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_add_quote_long_message(&sent);
  assert(encode_add_quote_long_message(&sent, wire, 0) == 32);
  assert(decode_add_quote_long_message(&got, wire, 0) == 32);
  equal_add_quote_long_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_add_quote_long_message(&got, wire, 0) == 32);
  assert(encode_add_quote_long_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Executed Message: 20 bytes ---------------------------------- */

/* This message is sent whenever a Side order is executed in whole or in part. It is possible to receive several Single Side Executed Messages for the same Side order if that Side order is executed in several parts. The multiple Single Side Executed Messages on the same order are cumulative. By combining the executions received separately via two types of Single Side Executed Messages and Trade Messages, it is possible to build a complete view of all non-auction executions that happen on PHLX ®. Auction execution information is available in one bulk print via the Auction Trade Message. */
typedef struct {
  uint8_t nanoseconds[4];             /* bytes 0 to 3 */
  uint8_t reference_number_delta[4];  /* bytes 4 to 7 */
  uint8_t executed_contracts[4];      /* bytes 8 to 11 */
  uint8_t cross_number[4];            /* bytes 12 to 15 */
  uint8_t match_number[4];            /* bytes 16 to 19 */
} SingleSideExecutedMessage;

/* any Single Side Executed Message at all: every byte one the checker chooses */
static void any_single_side_executed_message(SingleSideExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_contracts[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
}

/* Single Side Executed Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_single_side_executed_message(const SingleSideExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_contracts[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Single Side Executed Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_single_side_executed_message(SingleSideExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_contracts[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Executed Message is what was written, byte for byte */
static void equal_single_side_executed_message(const SingleSideExecutedMessage *read, const SingleSideExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_number_delta[i] == written->reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_contracts[i] == written->executed_contracts[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_number[i] == written->cross_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Single Side Executed Message: written and read back, then read and written back */
static void check_single_side_executed_message(void) {
  SingleSideExecutedMessage sent;
  SingleSideExecutedMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_single_side_executed_message(&sent);
  assert(encode_single_side_executed_message(&sent, wire, 0) == 20);
  assert(decode_single_side_executed_message(&got, wire, 0) == 20);
  equal_single_side_executed_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_executed_message(&got, wire, 0) == 20);
  assert(encode_single_side_executed_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Executed With Price Message: 25 bytes ----------------------- */

/* This message is sent whenever an incoming Side order is executed against the book in whole or in part at a price different from the initial display price. Since the execution price is different than the display price of the original Add/Replace, the options system includes a price field within this execution message. It is possible to receive multiple Single Side Executed and Single Side Executed with Price messages for the same Side order if that Side order is executed in several parts. The multiple Single Side Executed messages on the same Side order are cumulative. */
typedef struct {
  uint8_t nanoseconds[4];             /* bytes 0 to 3 */
  uint8_t reference_number_delta[4];  /* bytes 4 to 7 */
  uint8_t cross_number[4];            /* bytes 8 to 11 */
  uint8_t match_number[4];            /* bytes 12 to 15 */
  uint8_t printable;                  /* byte 16 */
  uint8_t price[4];                   /* bytes 17 to 20 */
  uint8_t volume[4];                  /* bytes 21 to 24 */
} SingleSideExecutedWithPriceMessage;

/* any Single Side Executed With Price Message at all: every byte one the checker chooses */
static void any_single_side_executed_with_price_message(SingleSideExecutedWithPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  record->printable = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
}

/* Single Side Executed With Price Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_single_side_executed_with_price_message(const SingleSideExecutedWithPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->printable;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }

  return at;
}

/* Single Side Executed With Price Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_single_side_executed_with_price_message(SingleSideExecutedWithPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  record->printable = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Executed With Price Message is what was written, byte for byte */
static void equal_single_side_executed_with_price_message(const SingleSideExecutedWithPriceMessage *read, const SingleSideExecutedWithPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_number_delta[i] == written->reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_number[i] == written->cross_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->printable == written->printable);
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
}

/* Single Side Executed With Price Message: written and read back, then read and written back */
static void check_single_side_executed_with_price_message(void) {
  SingleSideExecutedWithPriceMessage sent;
  SingleSideExecutedWithPriceMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_single_side_executed_with_price_message(&sent);
  assert(encode_single_side_executed_with_price_message(&sent, wire, 0) == 25);
  assert(decode_single_side_executed_with_price_message(&got, wire, 0) == 25);
  equal_single_side_executed_with_price_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_executed_with_price_message(&got, wire, 0) == 25);
  assert(encode_single_side_executed_with_price_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Cancel Message: 12 bytes ------------------------------------ */

/* This message is sent whenever an order or a side of a quote on the book is modified as a result of a partial cancellation. */
typedef struct {
  uint8_t nanoseconds[4];             /* bytes 0 to 3 */
  uint8_t reference_number_delta[4];  /* bytes 4 to 7 */
  uint8_t cancelled_contracts[4];     /* bytes 8 to 11 */
} SingleSideCancelMessage;

/* any Single Side Cancel Message at all: every byte one the checker chooses */
static void any_single_side_cancel_message(SingleSideCancelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancelled_contracts[i] = arbitrary(); }
}

/* Single Side Cancel Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_single_side_cancel_message(const SingleSideCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancelled_contracts[i]; }

  return at;
}

/* Single Side Cancel Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_single_side_cancel_message(SingleSideCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancelled_contracts[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Cancel Message is what was written, byte for byte */
static void equal_single_side_cancel_message(const SingleSideCancelMessage *read, const SingleSideCancelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_number_delta[i] == written->reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancelled_contracts[i] == written->cancelled_contracts[i]); }
}

/* Single Side Cancel Message: written and read back, then read and written back */
static void check_single_side_cancel_message(void) {
  SingleSideCancelMessage sent;
  SingleSideCancelMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_single_side_cancel_message(&sent);
  assert(encode_single_side_cancel_message(&sent, wire, 0) == 12);
  assert(decode_single_side_cancel_message(&got, wire, 0) == 12);
  equal_single_side_cancel_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_cancel_message(&got, wire, 0) == 12);
  assert(encode_single_side_cancel_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Replace Short Message: 16 bytes ----------------------------- */

/* This message is sent whenever one side of a quote on the book is replaced. The replacement has a new reference number and replaces the prior reference number. */
typedef struct {
  uint8_t nanoseconds[4];                      /* bytes 0 to 3 */
  uint8_t original_reference_number_delta[4];  /* bytes 4 to 7 */
  uint8_t new_reference_number_delta[4];       /* bytes 8 to 11 */
  uint8_t short_price[2];                      /* bytes 12 to 13 */
  uint8_t short_volume[2];                     /* bytes 14 to 15 */
} SingleSideReplaceShortMessage;

/* any Single Side Replace Short Message at all: every byte one the checker chooses */
static void any_single_side_replace_short_message(SingleSideReplaceShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->new_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->short_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->short_volume[i] = arbitrary(); }
}

/* Single Side Replace Short Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_single_side_replace_short_message(const SingleSideReplaceShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_reference_number_delta[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->short_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->short_volume[i]; }

  return at;
}

/* Single Side Replace Short Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_single_side_replace_short_message(SingleSideReplaceShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->new_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->short_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->short_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Replace Short Message is what was written, byte for byte */
static void equal_single_side_replace_short_message(const SingleSideReplaceShortMessage *read, const SingleSideReplaceShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_reference_number_delta[i] == written->original_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->new_reference_number_delta[i] == written->new_reference_number_delta[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->short_price[i] == written->short_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->short_volume[i] == written->short_volume[i]); }
}

/* Single Side Replace Short Message: written and read back, then read and written back */
static void check_single_side_replace_short_message(void) {
  SingleSideReplaceShortMessage sent;
  SingleSideReplaceShortMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_single_side_replace_short_message(&sent);
  assert(encode_single_side_replace_short_message(&sent, wire, 0) == 16);
  assert(decode_single_side_replace_short_message(&got, wire, 0) == 16);
  equal_single_side_replace_short_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_replace_short_message(&got, wire, 0) == 16);
  assert(encode_single_side_replace_short_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Replace Long Message: 20 bytes ------------------------------ */

/* This message is sent whenever one side of a quote on the book is replaced. The replacement has a new reference number and replaces the prior reference number. */
typedef struct {
  uint8_t nanoseconds[4];                      /* bytes 0 to 3 */
  uint8_t original_reference_number_delta[4];  /* bytes 4 to 7 */
  uint8_t new_reference_number_delta[4];       /* bytes 8 to 11 */
  uint8_t price[4];                            /* bytes 12 to 15 */
  uint8_t volume[4];                           /* bytes 16 to 19 */
} SingleSideReplaceLongMessage;

/* any Single Side Replace Long Message at all: every byte one the checker chooses */
static void any_single_side_replace_long_message(SingleSideReplaceLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->new_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
}

/* Single Side Replace Long Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_single_side_replace_long_message(const SingleSideReplaceLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }

  return at;
}

/* Single Side Replace Long Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_single_side_replace_long_message(SingleSideReplaceLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->new_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Replace Long Message is what was written, byte for byte */
static void equal_single_side_replace_long_message(const SingleSideReplaceLongMessage *read, const SingleSideReplaceLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_reference_number_delta[i] == written->original_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->new_reference_number_delta[i] == written->new_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
}

/* Single Side Replace Long Message: written and read back, then read and written back */
static void check_single_side_replace_long_message(void) {
  SingleSideReplaceLongMessage sent;
  SingleSideReplaceLongMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_single_side_replace_long_message(&sent);
  assert(encode_single_side_replace_long_message(&sent, wire, 0) == 20);
  assert(decode_single_side_replace_long_message(&got, wire, 0) == 20);
  equal_single_side_replace_long_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_replace_long_message(&got, wire, 0) == 20);
  assert(encode_single_side_replace_long_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replace Short Message: 20 bytes ----------------------------------- */

/* This message is sent whenever an order on the book is replaced. The replacement has a new reference number and replaces the prior reference number. */
typedef struct {
  uint8_t nanoseconds[4];                      /* bytes 0 to 3 */
  uint8_t original_reference_number_delta[4];  /* bytes 4 to 7 */
  uint8_t new_reference_number_delta[4];       /* bytes 8 to 11 */
  uint8_t short_price[2];                      /* bytes 12 to 13 */
  uint8_t short_volume[2];                     /* bytes 14 to 15 */
  uint8_t order_id[4];                         /* bytes 16 to 19 */
} OrderReplaceShortMessage;

/* any Order Replace Short Message at all: every byte one the checker chooses */
static void any_order_replace_short_message(OrderReplaceShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->new_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->short_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->short_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
}

/* Order Replace Short Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_order_replace_short_message(const OrderReplaceShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_reference_number_delta[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->short_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->short_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Order Replace Short Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_order_replace_short_message(OrderReplaceShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->new_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->short_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->short_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Replace Short Message is what was written, byte for byte */
static void equal_order_replace_short_message(const OrderReplaceShortMessage *read, const OrderReplaceShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_reference_number_delta[i] == written->original_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->new_reference_number_delta[i] == written->new_reference_number_delta[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->short_price[i] == written->short_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->short_volume[i] == written->short_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Order Replace Short Message: written and read back, then read and written back */
static void check_order_replace_short_message(void) {
  OrderReplaceShortMessage sent;
  OrderReplaceShortMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_order_replace_short_message(&sent);
  assert(encode_order_replace_short_message(&sent, wire, 0) == 20);
  assert(decode_order_replace_short_message(&got, wire, 0) == 20);
  equal_order_replace_short_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replace_short_message(&got, wire, 0) == 20);
  assert(encode_order_replace_short_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replace Long Message: 24 bytes ------------------------------------ */

/* This message is sent whenever an order on the book is replaced. The replacement has a new reference number and replaces the prior reference number. */
typedef struct {
  uint8_t nanoseconds[4];                      /* bytes 0 to 3 */
  uint8_t original_reference_number_delta[4];  /* bytes 4 to 7 */
  uint8_t new_reference_number_delta[4];       /* bytes 8 to 11 */
  uint8_t price[4];                            /* bytes 12 to 15 */
  uint8_t volume[4];                           /* bytes 16 to 19 */
  uint8_t order_id[4];                         /* bytes 20 to 23 */
} OrderReplaceLongMessage;

/* any Order Replace Long Message at all: every byte one the checker chooses */
static void any_order_replace_long_message(OrderReplaceLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->new_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
}

/* Order Replace Long Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_order_replace_long_message(const OrderReplaceLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Order Replace Long Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_order_replace_long_message(OrderReplaceLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->new_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Replace Long Message is what was written, byte for byte */
static void equal_order_replace_long_message(const OrderReplaceLongMessage *read, const OrderReplaceLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_reference_number_delta[i] == written->original_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->new_reference_number_delta[i] == written->new_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Order Replace Long Message: written and read back, then read and written back */
static void check_order_replace_long_message(void) {
  OrderReplaceLongMessage sent;
  OrderReplaceLongMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_order_replace_long_message(&sent);
  assert(encode_order_replace_long_message(&sent, wire, 0) == 24);
  assert(decode_order_replace_long_message(&got, wire, 0) == 24);
  equal_order_replace_long_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replace_long_message(&got, wire, 0) == 24);
  assert(encode_order_replace_long_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Delete Message: 8 bytes ------------------------------------- */

/* The message is sent when an order or a side of a quote is being cancelled. All remaining contracts are no longer accessible so the side should be removed from the book. */
typedef struct {
  uint8_t nanoseconds[4];             /* bytes 0 to 3 */
  uint8_t reference_number_delta[4];  /* bytes 4 to 7 */
} SingleSideDeleteMessage;

/* any Single Side Delete Message at all: every byte one the checker chooses */
static void any_single_side_delete_message(SingleSideDeleteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_number_delta[i] = arbitrary(); }
}

/* Single Side Delete Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_single_side_delete_message(const SingleSideDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_number_delta[i]; }

  return at;
}

/* Single Side Delete Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_single_side_delete_message(SingleSideDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_number_delta[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Delete Message is what was written, byte for byte */
static void equal_single_side_delete_message(const SingleSideDeleteMessage *read, const SingleSideDeleteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_number_delta[i] == written->reference_number_delta[i]); }
}

/* Single Side Delete Message: written and read back, then read and written back */
static void check_single_side_delete_message(void) {
  SingleSideDeleteMessage sent;
  SingleSideDeleteMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_single_side_delete_message(&sent);
  assert(encode_single_side_delete_message(&sent, wire, 0) == 8);
  assert(decode_single_side_delete_message(&got, wire, 0) == 8);
  equal_single_side_delete_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_delete_message(&got, wire, 0) == 8);
  assert(encode_single_side_delete_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Update Message: 17 bytes ------------------------------------ */

/* This message is sent whenever an order or a side of a quote is being updated for price and (or) contracts. The reference number associated with the order quote is unchanged. */
typedef struct {
  uint8_t nanoseconds[4];             /* bytes 0 to 3 */
  uint8_t reference_number_delta[4];  /* bytes 4 to 7 */
  uint8_t change_reason;              /* byte 8 */
  uint8_t price[4];                   /* bytes 9 to 12 */
  uint8_t volume[4];                  /* bytes 13 to 16 */
} SingleSideUpdateMessage;

/* any Single Side Update Message at all: every byte one the checker chooses */
static void any_single_side_update_message(SingleSideUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_number_delta[i] = arbitrary(); }
  record->change_reason = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
}

/* Single Side Update Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_single_side_update_message(const SingleSideUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_number_delta[i]; }
  wire[at++] = record->change_reason;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }

  return at;
}

/* Single Side Update Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_single_side_update_message(SingleSideUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_number_delta[i] = wire[at++]; }
  record->change_reason = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Update Message is what was written, byte for byte */
static void equal_single_side_update_message(const SingleSideUpdateMessage *read, const SingleSideUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_number_delta[i] == written->reference_number_delta[i]); }
  assert(read->change_reason == written->change_reason);
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
}

/* Single Side Update Message: written and read back, then read and written back */
static void check_single_side_update_message(void) {
  SingleSideUpdateMessage sent;
  SingleSideUpdateMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_single_side_update_message(&sent);
  assert(encode_single_side_update_message(&sent, wire, 0) == 17);
  assert(decode_single_side_update_message(&got, wire, 0) == 17);
  equal_single_side_update_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_update_message(&got, wire, 0) == 17);
  assert(encode_single_side_update_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Replace Short Message: 28 bytes ----------------------------------- */

/* This message is sent whenever a quote on the book is replaced. The replaced quote has new reference numbers on both sides. */
typedef struct {
  uint8_t nanoseconds[4];                          /* bytes 0 to 3 */
  uint8_t original_bid_reference_number_delta[4];  /* bytes 4 to 7 */
  uint8_t bid_reference_number_delta[4];           /* bytes 8 to 11 */
  uint8_t original_ask_reference_number_delta[4];  /* bytes 12 to 15 */
  uint8_t ask_reference_number_delta[4];           /* bytes 16 to 19 */
  uint8_t short_bid_price[2];                      /* bytes 20 to 21 */
  uint8_t short_bid_size[2];                       /* bytes 22 to 23 */
  uint8_t short_ask_price[2];                      /* bytes 24 to 25 */
  uint8_t short_ask_size[2];                       /* bytes 26 to 27 */
} QuoteReplaceShortMessage;

/* any Quote Replace Short Message at all: every byte one the checker chooses */
static void any_quote_replace_short_message(QuoteReplaceShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_bid_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_ask_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->short_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->short_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->short_ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->short_ask_size[i] = arbitrary(); }
}

/* Quote Replace Short Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_quote_replace_short_message(const QuoteReplaceShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_bid_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_ask_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_reference_number_delta[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->short_bid_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->short_bid_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->short_ask_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->short_ask_size[i]; }

  return at;
}

/* Quote Replace Short Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_quote_replace_short_message(QuoteReplaceShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_bid_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_ask_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->short_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->short_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->short_ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->short_ask_size[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Replace Short Message is what was written, byte for byte */
static void equal_quote_replace_short_message(const QuoteReplaceShortMessage *read, const QuoteReplaceShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_bid_reference_number_delta[i] == written->original_bid_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_reference_number_delta[i] == written->bid_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_ask_reference_number_delta[i] == written->original_ask_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_reference_number_delta[i] == written->ask_reference_number_delta[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->short_bid_price[i] == written->short_bid_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->short_bid_size[i] == written->short_bid_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->short_ask_price[i] == written->short_ask_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->short_ask_size[i] == written->short_ask_size[i]); }
}

/* Quote Replace Short Message: written and read back, then read and written back */
static void check_quote_replace_short_message(void) {
  QuoteReplaceShortMessage sent;
  QuoteReplaceShortMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_quote_replace_short_message(&sent);
  assert(encode_quote_replace_short_message(&sent, wire, 0) == 28);
  assert(decode_quote_replace_short_message(&got, wire, 0) == 28);
  equal_quote_replace_short_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_replace_short_message(&got, wire, 0) == 28);
  assert(encode_quote_replace_short_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Replace Long Message: 36 bytes ------------------------------------ */

/* This message is sent whenever a quote on the book is replaced. The replaced quote has new reference numbers on both sides. */
typedef struct {
  uint8_t nanoseconds[4];                          /* bytes 0 to 3 */
  uint8_t original_bid_reference_number_delta[4];  /* bytes 4 to 7 */
  uint8_t bid_reference_number_delta[4];           /* bytes 8 to 11 */
  uint8_t original_ask_reference_number_delta[4];  /* bytes 12 to 15 */
  uint8_t ask_reference_number_delta[4];           /* bytes 16 to 19 */
  uint8_t bid_price[4];                            /* bytes 20 to 23 */
  uint8_t bid_size[4];                             /* bytes 24 to 27 */
  uint8_t ask_price[4];                            /* bytes 28 to 31 */
  uint8_t ask_size[4];                             /* bytes 32 to 35 */
} QuoteReplaceLongMessage;

/* any Quote Replace Long Message at all: every byte one the checker chooses */
static void any_quote_replace_long_message(QuoteReplaceLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_bid_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_ask_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size[i] = arbitrary(); }
}

/* Quote Replace Long Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_quote_replace_long_message(const QuoteReplaceLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_bid_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_ask_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size[i]; }

  return at;
}

/* Quote Replace Long Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_quote_replace_long_message(QuoteReplaceLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_bid_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_ask_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Replace Long Message is what was written, byte for byte */
static void equal_quote_replace_long_message(const QuoteReplaceLongMessage *read, const QuoteReplaceLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_bid_reference_number_delta[i] == written->original_bid_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_reference_number_delta[i] == written->bid_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_ask_reference_number_delta[i] == written->original_ask_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_reference_number_delta[i] == written->ask_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size[i] == written->bid_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_price[i] == written->ask_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size[i] == written->ask_size[i]); }
}

/* Quote Replace Long Message: written and read back, then read and written back */
static void check_quote_replace_long_message(void) {
  QuoteReplaceLongMessage sent;
  QuoteReplaceLongMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_quote_replace_long_message(&sent);
  assert(encode_quote_replace_long_message(&sent, wire, 0) == 36);
  assert(decode_quote_replace_long_message(&got, wire, 0) == 36);
  equal_quote_replace_long_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_replace_long_message(&got, wire, 0) == 36);
  assert(encode_quote_replace_long_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Delete Message: 12 bytes ------------------------------------------ */

/* The message is sent when a single quote is being cancelled. All remaining contracts are no longer accessible so the quote should be removed from the book. */
typedef struct {
  uint8_t nanoseconds[4];                 /* bytes 0 to 3 */
  uint8_t bid_reference_number_delta[4];  /* bytes 4 to 7 */
  uint8_t ask_reference_number_delta[4];  /* bytes 8 to 11 */
} QuoteDeleteMessage;

/* any Quote Delete Message at all: every byte one the checker chooses */
static void any_quote_delete_message(QuoteDeleteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_reference_number_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_reference_number_delta[i] = arbitrary(); }
}

/* Quote Delete Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_quote_delete_message(const QuoteDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_reference_number_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_reference_number_delta[i]; }

  return at;
}

/* Quote Delete Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_quote_delete_message(QuoteDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_reference_number_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_reference_number_delta[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Delete Message is what was written, byte for byte */
static void equal_quote_delete_message(const QuoteDeleteMessage *read, const QuoteDeleteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_reference_number_delta[i] == written->bid_reference_number_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_reference_number_delta[i] == written->ask_reference_number_delta[i]); }
}

/* Quote Delete Message: written and read back, then read and written back */
static void check_quote_delete_message(void) {
  QuoteDeleteMessage sent;
  QuoteDeleteMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_quote_delete_message(&sent);
  assert(encode_quote_delete_message(&sent, wire, 0) == 12);
  assert(decode_quote_delete_message(&got, wire, 0) == 12);
  equal_quote_delete_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_delete_message(&got, wire, 0) == 12);
  assert(encode_quote_delete_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Block Delete Message: 10 bytes ------------------------------------------ */

/* This message contains a block of Single Side Deletes. Each reference number inside the block represents an order or a side of a quote that is being cancelled. All remaining contracts are no longer accessible so the side should be removed from the book. */
typedef struct {
  uint8_t nanoseconds[4];                        /* bytes 0 to 3 */
  uint8_t number_of_reference_number_deltas[2];  /* bytes 4 to 5 */
  uint8_t reference_number_delta[4];             /* bytes 6 to 9 */
} BlockDeleteMessage;

/* any Block Delete Message at all: every byte one the checker chooses */
static void any_block_delete_message(BlockDeleteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_reference_number_deltas[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_number_delta[i] = arbitrary(); }
}

/* Block Delete Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_block_delete_message(const BlockDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_reference_number_deltas[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_number_delta[i]; }

  return at;
}

/* Block Delete Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_block_delete_message(BlockDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_reference_number_deltas[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_number_delta[i] = wire[at++]; }

  return at;
}

/* what was read of Block Delete Message is what was written, byte for byte */
static void equal_block_delete_message(const BlockDeleteMessage *read, const BlockDeleteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_reference_number_deltas[i] == written->number_of_reference_number_deltas[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_number_delta[i] == written->reference_number_delta[i]); }
}

/* Block Delete Message: written and read back, then read and written back */
static void check_block_delete_message(void) {
  BlockDeleteMessage sent;
  BlockDeleteMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_block_delete_message(&sent);
  assert(encode_block_delete_message(&sent, wire, 0) == 10);
  assert(decode_block_delete_message(&got, wire, 0) == 10);
  equal_block_delete_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_block_delete_message(&got, wire, 0) == 10);
  assert(encode_block_delete_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Non Auction Options Trade Message: 25 bytes ----------------------------- */

/* This Options Trade Message is designed to provide execution details for match events involving non-displayable order types and Complex orders. (Note: There is a separate message for Option auction events.) */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t trade_indicator;  /* byte 4 */
  uint8_t option_id[4];     /* bytes 5 to 8 */
  uint8_t cross_number[4];  /* bytes 9 to 12 */
  uint8_t match_number[4];  /* bytes 13 to 16 */
  uint8_t price[4];         /* bytes 17 to 20 */
  uint8_t volume[4];        /* bytes 21 to 24 */
} NonAuctionOptionsTradeMessage;

/* any Non Auction Options Trade Message at all: every byte one the checker chooses */
static void any_non_auction_options_trade_message(NonAuctionOptionsTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  record->trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
}

/* Non Auction Options Trade Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_non_auction_options_trade_message(const NonAuctionOptionsTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  wire[at++] = record->trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }

  return at;
}

/* Non Auction Options Trade Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_non_auction_options_trade_message(NonAuctionOptionsTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  record->trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }

  return at;
}

/* what was read of Non Auction Options Trade Message is what was written, byte for byte */
static void equal_non_auction_options_trade_message(const NonAuctionOptionsTradeMessage *read, const NonAuctionOptionsTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  assert(read->trade_indicator == written->trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_number[i] == written->cross_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
}

/* Non Auction Options Trade Message: written and read back, then read and written back */
static void check_non_auction_options_trade_message(void) {
  NonAuctionOptionsTradeMessage sent;
  NonAuctionOptionsTradeMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_non_auction_options_trade_message(&sent);
  assert(encode_non_auction_options_trade_message(&sent, wire, 0) == 25);
  assert(decode_non_auction_options_trade_message(&got, wire, 0) == 25);
  equal_non_auction_options_trade_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_non_auction_options_trade_message(&got, wire, 0) == 25);
  assert(encode_non_auction_options_trade_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Cross Trade Message: 25 bytes ----------------------------------- */

/* Options Auction Trade message is sent for every option when an auction in that option is completed. The message indicates the bulk volume associated with the auction event. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t option_id[4];     /* bytes 4 to 7 */
  uint8_t cross_number[4];  /* bytes 8 to 11 */
  uint8_t match_number[4];  /* bytes 12 to 15 */
  uint8_t cross_type;       /* byte 16 */
  uint8_t price[4];         /* bytes 17 to 20 */
  uint8_t volume[4];        /* bytes 21 to 24 */
} OptionsCrossTradeMessage;

/* any Options Cross Trade Message at all: every byte one the checker chooses */
static void any_options_cross_trade_message(OptionsCrossTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  record->cross_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
}

/* Options Cross Trade Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_options_cross_trade_message(const OptionsCrossTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->cross_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }

  return at;
}

/* Options Cross Trade Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_options_cross_trade_message(OptionsCrossTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  record->cross_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }

  return at;
}

/* what was read of Options Cross Trade Message is what was written, byte for byte */
static void equal_options_cross_trade_message(const OptionsCrossTradeMessage *read, const OptionsCrossTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_number[i] == written->cross_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->cross_type == written->cross_type);
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
}

/* Options Cross Trade Message: written and read back, then read and written back */
static void check_options_cross_trade_message(void) {
  OptionsCrossTradeMessage sent;
  OptionsCrossTradeMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_options_cross_trade_message(&sent);
  assert(encode_options_cross_trade_message(&sent, wire, 0) == 25);
  assert(decode_options_cross_trade_message(&got, wire, 0) == 25);
  equal_options_cross_trade_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_options_cross_trade_message(&got, wire, 0) == 25);
  assert(encode_options_cross_trade_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broken Trade Order Executed Message: 12 bytes --------------------------- */

/* The Broken Trade Message is sent whenever an execution on PHLX ® is broken. An execution may be broken if it is found to be “clearly erroneous” pursuant to PHLX ® Clearly Erroneous Policy. A trade break is final; once a trade is broken, it cannot be reinstated. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t cross_number[4];  /* bytes 4 to 7 */
  uint8_t match_number[4];  /* bytes 8 to 11 */
} BrokenTradeOrderExecutedMessage;

/* any Broken Trade Order Executed Message at all: every byte one the checker chooses */
static void any_broken_trade_order_executed_message(BrokenTradeOrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
}

/* Broken Trade Order Executed Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_order_executed_message(const BrokenTradeOrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Broken Trade Order Executed Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_order_executed_message(BrokenTradeOrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Broken Trade Order Executed Message is what was written, byte for byte */
static void equal_broken_trade_order_executed_message(const BrokenTradeOrderExecutedMessage *read, const BrokenTradeOrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_number[i] == written->cross_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Broken Trade Order Executed Message: written and read back, then read and written back */
static void check_broken_trade_order_executed_message(void) {
  BrokenTradeOrderExecutedMessage sent;
  BrokenTradeOrderExecutedMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_broken_trade_order_executed_message(&sent);
  assert(encode_broken_trade_order_executed_message(&sent, wire, 0) == 12);
  assert(decode_broken_trade_order_executed_message(&got, wire, 0) == 12);
  equal_broken_trade_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_broken_trade_order_executed_message(&got, wire, 0) == 12);
  assert(encode_broken_trade_order_executed_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Notification Message: 30 bytes ---------------------------------- */

/* This message is also sent as notification that there is an exposed buy (sell) order available for execution at the National Best Offer (Bid). */
typedef struct {
  uint8_t nanoseconds[4];       /* bytes 0 to 3 */
  uint8_t auction_id[4];        /* bytes 4 to 7 */
  uint8_t auction_type;         /* byte 8 */
  uint8_t paired_contracts[4];  /* bytes 9 to 12 */
  uint8_t imbalance_direction;  /* byte 13 */
  uint8_t option_id[4];         /* bytes 14 to 17 */
  uint8_t imbalance_price[4];   /* bytes 18 to 21 */
  uint8_t imbalance_volume[4];  /* bytes 22 to 25 */
  uint8_t customer_indicator;   /* byte 26 */
  uint8_t reserved_3[3];        /* bytes 27 to 29 */
} AuctionNotificationMessage;

/* any Auction Notification Message at all: every byte one the checker chooses */
static void any_auction_notification_message(AuctionNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->paired_contracts[i] = arbitrary(); }
  record->imbalance_direction = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->imbalance_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->imbalance_volume[i] = arbitrary(); }
  record->customer_indicator = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Auction Notification Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_auction_notification_message(const AuctionNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->paired_contracts[i]; }
  wire[at++] = record->imbalance_direction;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->imbalance_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->imbalance_volume[i]; }
  wire[at++] = record->customer_indicator;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Auction Notification Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_auction_notification_message(AuctionNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->paired_contracts[i] = wire[at++]; }
  record->imbalance_direction = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->imbalance_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->imbalance_volume[i] = wire[at++]; }
  record->customer_indicator = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Notification Message is what was written, byte for byte */
static void equal_auction_notification_message(const AuctionNotificationMessage *read, const AuctionNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 4; i++) { assert(read->paired_contracts[i] == written->paired_contracts[i]); }
  assert(read->imbalance_direction == written->imbalance_direction);
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->imbalance_price[i] == written->imbalance_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->imbalance_volume[i] == written->imbalance_volume[i]); }
  assert(read->customer_indicator == written->customer_indicator);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Auction Notification Message: written and read back, then read and written back */
static void check_auction_notification_message(void) {
  AuctionNotificationMessage sent;
  AuctionNotificationMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_auction_notification_message(&sent);
  assert(encode_auction_notification_message(&sent, wire, 0) == 30);
  assert(decode_auction_notification_message(&got, wire, 0) == 30);
  equal_auction_notification_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_notification_message(&got, wire, 0) == 30);
  assert(encode_auction_notification_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_seconds_message();
  check_system_event_message();
  check_base_reference_message();
  check_option_directory_message();
  check_trading_action_message();
  check_security_open_message();
  check_add_order_short_message();
  check_add_order_long_message();
  check_add_quote_short_message();
  check_add_quote_long_message();
  check_single_side_executed_message();
  check_single_side_executed_with_price_message();
  check_single_side_cancel_message();
  check_single_side_replace_short_message();
  check_single_side_replace_long_message();
  check_order_replace_short_message();
  check_order_replace_long_message();
  check_single_side_delete_message();
  check_single_side_update_message();
  check_quote_replace_short_message();
  check_quote_replace_long_message();
  check_quote_delete_message();
  check_block_delete_message();
  check_non_auction_options_trade_message();
  check_options_cross_trade_message();
  check_broken_trade_order_executed_message();
  check_auction_notification_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
