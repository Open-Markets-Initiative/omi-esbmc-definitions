// nasdaq/nomoptions/itto/NomOptions_Itto_v4_0_2025_Udp.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Itch To Trade Options
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

/* ---- System Event Message: 9 bytes ------------------------------------------- */

/* The system event message type is used to signal a market or data feed handler event. */
typedef struct {
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t timestamp[6];        /* bytes 2 to 7 */
  uint8_t event_code;          /* byte 8 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->event_code == written->event_code);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 9);
  assert(decode_system_event_message(&got, wire, 0) == 9);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 9);
  assert(encode_system_event_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Directory Message: 43 bytes ------------------------------------- */

/* At the start of each trading day, NASDAQ disseminates options symbol directory messages for all active options symbols in the NASDAQ option system. */
typedef struct {
  uint8_t tracking_number[2];        /* bytes 0 to 1 */
  uint8_t timestamp[6];              /* bytes 2 to 7 */
  uint8_t option_id[4];              /* bytes 8 to 11 */
  uint8_t security_symbol[6];        /* bytes 12 to 17 */
  uint8_t expiration_year;           /* byte 18 */
  uint8_t expiration_month;          /* byte 19 */
  uint8_t expiration_date;           /* byte 20 */
  uint8_t explicit_strike_price[4];  /* bytes 21 to 24 */
  uint8_t option_type;               /* byte 25 */
  uint8_t source;                    /* byte 26 */
  uint8_t underlying_symbol[13];     /* bytes 27 to 39 */
  uint8_t options_closing_type;      /* byte 40 */
  uint8_t tradable;                  /* byte 41 */
  uint8_t mpv;                       /* byte 42 */
} OptionsDirectoryMessage;

/* any Options Directory Message at all: every byte one the checker chooses */
static void any_options_directory_message(OptionsDirectoryMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
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

/* Options Directory Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_options_directory_message(const OptionsDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
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

/* Options Directory Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_options_directory_message(OptionsDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
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

/* what was read of Options Directory Message is what was written, byte for byte */
static void equal_options_directory_message(const OptionsDirectoryMessage *read, const OptionsDirectoryMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
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

/* Options Directory Message: written and read back, then read and written back */
static void check_options_directory_message(void) {
  OptionsDirectoryMessage sent;
  OptionsDirectoryMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_options_directory_message(&sent);
  assert(encode_options_directory_message(&sent, wire, 0) == 43);
  assert(decode_options_directory_message(&got, wire, 0) == 43);
  equal_options_directory_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_options_directory_message(&got, wire, 0) == 43);
  assert(encode_options_directory_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Action Message: 13 bytes ---------------------------------------- */

/* After the start of system hours, NASDAQ will use the Trading Action message to relay changes in trading status for an individual option. Messages will be sent when an option is halted, is released for quotation, released for trading, or temporarily suspended for trading on the buy or sell side. */
typedef struct {
  uint8_t tracking_number[2];     /* bytes 0 to 1 */
  uint8_t timestamp[6];           /* bytes 2 to 7 */
  uint8_t option_id[4];           /* bytes 8 to 11 */
  uint8_t current_trading_state;  /* byte 12 */
} TradingActionMessage;

/* any Trading Action Message at all: every byte one the checker chooses */
static void any_trading_action_message(TradingActionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  record->current_trading_state = arbitrary();
}

/* Trading Action Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_trading_action_message(const TradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  wire[at++] = record->current_trading_state;

  return at;
}

/* Trading Action Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_trading_action_message(TradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  record->current_trading_state = wire[at++];

  return at;
}

/* what was read of Trading Action Message is what was written, byte for byte */
static void equal_trading_action_message(const TradingActionMessage *read, const TradingActionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  assert(read->current_trading_state == written->current_trading_state);
}

/* Trading Action Message: written and read back, then read and written back */
static void check_trading_action_message(void) {
  TradingActionMessage sent;
  TradingActionMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_trading_action_message(&sent);
  assert(encode_trading_action_message(&sent, wire, 0) == 13);
  assert(decode_trading_action_message(&got, wire, 0) == 13);
  equal_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_action_message(&got, wire, 0) == 13);
  assert(encode_trading_action_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Open Message: 13 bytes ----------------------------------------- */

/* NASDAQ plans to disseminate the Option Open Message for each option as soon as the opening is completed. Upon receipt of the open state message, firms should be advised that the option denoted in the message is now available for auto execution within the NASDAQ Options Market System. Upon receipt of the closed state message, firms should be advised that the option is no longer eligible for auto-execution within the NASDAQ Options Market System. */
typedef struct {
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t timestamp[6];        /* bytes 2 to 7 */
  uint8_t option_id[4];        /* bytes 8 to 11 */
  uint8_t open_state;          /* byte 12 */
} SecurityOpenMessage;

/* any Security Open Message at all: every byte one the checker chooses */
static void any_security_open_message(SecurityOpenMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  record->open_state = arbitrary();
}

/* Security Open Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_security_open_message(const SecurityOpenMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  wire[at++] = record->open_state;

  return at;
}

/* Security Open Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_security_open_message(SecurityOpenMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  record->open_state = wire[at++];

  return at;
}

/* what was read of Security Open Message is what was written, byte for byte */
static void equal_security_open_message(const SecurityOpenMessage *read, const SecurityOpenMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  assert(read->open_state == written->open_state);
}

/* Security Open Message: written and read back, then read and written back */
static void check_security_open_message(void) {
  SecurityOpenMessage sent;
  SecurityOpenMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_security_open_message(&sent);
  assert(encode_security_open_message(&sent, wire, 0) == 13);
  assert(decode_security_open_message(&got, wire, 0) == 13);
  equal_security_open_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_security_open_message(&got, wire, 0) == 13);
  assert(encode_security_open_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message Short Message Form: 25 bytes -------------------------- */

/* For bandwidth efficiency reasons, this message can be published in either short or long format. */
typedef struct {
  uint8_t tracking_number[2];         /* bytes 0 to 1 */
  uint8_t timestamp[6];               /* bytes 2 to 7 */
  uint8_t order_reference_number[8];  /* bytes 8 to 15 */
  uint8_t market_side;                /* byte 16 */
  uint8_t option_id[4];               /* bytes 17 to 20 */
  uint8_t price_short[2];             /* bytes 21 to 22 */
  uint8_t volume_short[2];            /* bytes 23 to 24 */
} AddOrderMessageShortMessageForm;

/* any Add Order Message Short Message Form at all: every byte one the checker chooses */
static void any_add_order_message_short_message_form(AddOrderMessageShortMessageForm *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->market_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->volume_short[i] = arbitrary(); }
}

/* Add Order Message Short Message Form to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message_short_message_form(const AddOrderMessageShortMessageForm *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->market_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->volume_short[i]; }

  return at;
}

/* Add Order Message Short Message Form off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message_short_message_form(AddOrderMessageShortMessageForm *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->market_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->volume_short[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Message Short Message Form is what was written, byte for byte */
static void equal_add_order_message_short_message_form(const AddOrderMessageShortMessageForm *read, const AddOrderMessageShortMessageForm *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->market_side == written->market_side);
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->volume_short[i] == written->volume_short[i]); }
}

/* Add Order Message Short Message Form: written and read back, then read and written back */
static void check_add_order_message_short_message_form(void) {
  AddOrderMessageShortMessageForm sent;
  AddOrderMessageShortMessageForm got;
  uint8_t wire[25];
  uint8_t again[25];

  any_add_order_message_short_message_form(&sent);
  assert(encode_add_order_message_short_message_form(&sent, wire, 0) == 25);
  assert(decode_add_order_message_short_message_form(&got, wire, 0) == 25);
  equal_add_order_message_short_message_form(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message_short_message_form(&got, wire, 0) == 25);
  assert(encode_add_order_message_short_message_form(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message Long Form Message: 29 bytes --------------------------- */

/* For bandwidth efficiency reasons, this message can be published in either short or long format. */
typedef struct {
  uint8_t tracking_number[2];         /* bytes 0 to 1 */
  uint8_t timestamp[6];               /* bytes 2 to 7 */
  uint8_t order_reference_number[8];  /* bytes 8 to 15 */
  uint8_t market_side;                /* byte 16 */
  uint8_t option_id[4];               /* bytes 17 to 20 */
  uint8_t price_long[4];              /* bytes 21 to 24 */
  uint8_t volume_long[4];             /* bytes 25 to 28 */
} AddOrderMessageLongFormMessage;

/* any Add Order Message Long Form Message at all: every byte one the checker chooses */
static void any_add_order_message_long_form_message(AddOrderMessageLongFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->market_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = arbitrary(); }
}

/* Add Order Message Long Form Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message_long_form_message(const AddOrderMessageLongFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->market_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_long[i]; }

  return at;
}

/* Add Order Message Long Form Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message_long_form_message(AddOrderMessageLongFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->market_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Message Long Form Message is what was written, byte for byte */
static void equal_add_order_message_long_form_message(const AddOrderMessageLongFormMessage *read, const AddOrderMessageLongFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->market_side == written->market_side);
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_long[i] == written->volume_long[i]); }
}

/* Add Order Message Long Form Message: written and read back, then read and written back */
static void check_add_order_message_long_form_message(void) {
  AddOrderMessageLongFormMessage sent;
  AddOrderMessageLongFormMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_add_order_message_long_form_message(&sent);
  assert(encode_add_order_message_long_form_message(&sent, wire, 0) == 29);
  assert(decode_add_order_message_long_form_message(&got, wire, 0) == 29);
  equal_add_order_message_long_form_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message_long_form_message(&got, wire, 0) == 29);
  assert(encode_add_order_message_long_form_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Quote Message Short Form Message: 36 bytes -------------------------- */

/* For bandwidth efficiency reasons, this message can be published in either short or long format. */
typedef struct {
  uint8_t tracking_number[2];       /* bytes 0 to 1 */
  uint8_t timestamp[6];             /* bytes 2 to 7 */
  uint8_t bid_reference_number[8];  /* bytes 8 to 15 */
  uint8_t ask_reference_number[8];  /* bytes 16 to 23 */
  uint8_t option_id[4];             /* bytes 24 to 27 */
  uint8_t bid_price_short[2];       /* bytes 28 to 29 */
  uint8_t bid_size_short[2];        /* bytes 30 to 31 */
  uint8_t ask_price_short[2];       /* bytes 32 to 33 */
  uint8_t ask_size_short[2];        /* bytes 34 to 35 */
} AddQuoteMessageShortFormMessage;

/* any Add Quote Message Short Form Message at all: every byte one the checker chooses */
static void any_add_quote_message_short_form_message(AddQuoteMessageShortFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_size_short[i] = arbitrary(); }
}

/* Add Quote Message Short Form Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_add_quote_message_short_form_message(const AddQuoteMessageShortFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_size_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_size_short[i]; }

  return at;
}

/* Add Quote Message Short Form Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_add_quote_message_short_form_message(AddQuoteMessageShortFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_size_short[i] = wire[at++]; }

  return at;
}

/* what was read of Add Quote Message Short Form Message is what was written, byte for byte */
static void equal_add_quote_message_short_form_message(const AddQuoteMessageShortFormMessage *read, const AddQuoteMessageShortFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_reference_number[i] == written->bid_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_reference_number[i] == written->ask_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_price_short[i] == written->bid_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_size_short[i] == written->bid_size_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_price_short[i] == written->ask_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_size_short[i] == written->ask_size_short[i]); }
}

/* Add Quote Message Short Form Message: written and read back, then read and written back */
static void check_add_quote_message_short_form_message(void) {
  AddQuoteMessageShortFormMessage sent;
  AddQuoteMessageShortFormMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_add_quote_message_short_form_message(&sent);
  assert(encode_add_quote_message_short_form_message(&sent, wire, 0) == 36);
  assert(decode_add_quote_message_short_form_message(&got, wire, 0) == 36);
  equal_add_quote_message_short_form_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_add_quote_message_short_form_message(&got, wire, 0) == 36);
  assert(encode_add_quote_message_short_form_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Quote Message Long Form Message: 44 bytes --------------------------- */

/* For bandwidth efficiency reasons, this message can be published in either short or long format. */
typedef struct {
  uint8_t tracking_number[2];       /* bytes 0 to 1 */
  uint8_t timestamp[6];             /* bytes 2 to 7 */
  uint8_t bid_reference_number[8];  /* bytes 8 to 15 */
  uint8_t ask_reference_number[8];  /* bytes 16 to 23 */
  uint8_t option_id[4];             /* bytes 24 to 27 */
  uint8_t bid[4];                   /* bytes 28 to 31 */
  uint8_t bid_size_long[4];         /* bytes 32 to 35 */
  uint8_t ask[4];                   /* bytes 36 to 39 */
  uint8_t ask_size_long[4];         /* bytes 40 to 43 */
} AddQuoteMessageLongFormMessage;

/* any Add Quote Message Long Form Message at all: every byte one the checker chooses */
static void any_add_quote_message_long_form_message(AddQuoteMessageLongFormMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_long[i] = arbitrary(); }
}

/* Add Quote Message Long Form Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_add_quote_message_long_form_message(const AddQuoteMessageLongFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_long[i]; }

  return at;
}

/* Add Quote Message Long Form Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_add_quote_message_long_form_message(AddQuoteMessageLongFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_long[i] = wire[at++]; }

  return at;
}

/* what was read of Add Quote Message Long Form Message is what was written, byte for byte */
static void equal_add_quote_message_long_form_message(const AddQuoteMessageLongFormMessage *read, const AddQuoteMessageLongFormMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_reference_number[i] == written->bid_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_reference_number[i] == written->ask_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid[i] == written->bid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_long[i] == written->bid_size_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask[i] == written->ask[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_long[i] == written->ask_size_long[i]); }
}

/* Add Quote Message Long Form Message: written and read back, then read and written back */
static void check_add_quote_message_long_form_message(void) {
  AddQuoteMessageLongFormMessage sent;
  AddQuoteMessageLongFormMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_add_quote_message_long_form_message(&sent);
  assert(encode_add_quote_message_long_form_message(&sent, wire, 0) == 44);
  assert(decode_add_quote_message_long_form_message(&got, wire, 0) == 44);
  equal_add_quote_message_long_form_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_add_quote_message_long_form_message(&got, wire, 0) == 44);
  assert(encode_add_quote_message_long_form_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Executed Message: 28 bytes ---------------------------------- */

/* This message is sent whenever a Side order is executed in whole or in part. It is possible to receive several Single Side Executed Messages for the same Side order if that Side order is executed in several parts. The multiple Single Side Executed Messages on the same order are cumulative. By combining the executions received separately via two types of Single Side Executed Messages and Trade Messages, it is possible to build a complete view of all non-auction executions that happen on NASDAQ. Auction execution information is available in one bulk print via the Auction Trade Message. */
typedef struct {
  uint8_t tracking_number[2];     /* bytes 0 to 1 */
  uint8_t timestamp[6];           /* bytes 2 to 7 */
  uint8_t reference_number[8];    /* bytes 8 to 15 */
  uint8_t executed_contracts[4];  /* bytes 16 to 19 */
  uint8_t cross_number[4];        /* bytes 20 to 23 */
  uint8_t match_number[4];        /* bytes 24 to 27 */
} SingleSideExecutedMessage;

/* any Single Side Executed Message at all: every byte one the checker chooses */
static void any_single_side_executed_message(SingleSideExecutedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_contracts[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
}

/* Single Side Executed Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_single_side_executed_message(const SingleSideExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_contracts[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Single Side Executed Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_single_side_executed_message(SingleSideExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_contracts[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Executed Message is what was written, byte for byte */
static void equal_single_side_executed_message(const SingleSideExecutedMessage *read, const SingleSideExecutedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_number[i] == written->reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_contracts[i] == written->executed_contracts[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_number[i] == written->cross_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Single Side Executed Message: written and read back, then read and written back */
static void check_single_side_executed_message(void) {
  SingleSideExecutedMessage sent;
  SingleSideExecutedMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_single_side_executed_message(&sent);
  assert(encode_single_side_executed_message(&sent, wire, 0) == 28);
  assert(decode_single_side_executed_message(&got, wire, 0) == 28);
  equal_single_side_executed_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_executed_message(&got, wire, 0) == 28);
  assert(encode_single_side_executed_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Executed With Price Message: 33 bytes ----------------------- */

/* These executions may be marked as non-printable. If the execution is marked as non-printed, it means that the contracts will be included into a later bulk print (e.g., in the case of auction executions). If a firm is looking to use the ITTO data in time-and-sales displays or volume calculations, NASDAQ recommends that firms ignore messages marked as non-printable to prevent double counting. */
typedef struct {
  uint8_t tracking_number[2];   /* bytes 0 to 1 */
  uint8_t timestamp[6];         /* bytes 2 to 7 */
  uint8_t reference_number[8];  /* bytes 8 to 15 */
  uint8_t cross_number[4];      /* bytes 16 to 19 */
  uint8_t match_number[4];      /* bytes 20 to 23 */
  uint8_t printable;            /* byte 24 */
  uint8_t price_long[4];        /* bytes 25 to 28 */
  uint8_t volume_long[4];       /* bytes 29 to 32 */
} SingleSideExecutedWithPriceMessage;

/* any Single Side Executed With Price Message at all: every byte one the checker chooses */
static void any_single_side_executed_with_price_message(SingleSideExecutedWithPriceMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  record->printable = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = arbitrary(); }
}

/* Single Side Executed With Price Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_single_side_executed_with_price_message(const SingleSideExecutedWithPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->printable;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_long[i]; }

  return at;
}

/* Single Side Executed With Price Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_single_side_executed_with_price_message(SingleSideExecutedWithPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  record->printable = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Executed With Price Message is what was written, byte for byte */
static void equal_single_side_executed_with_price_message(const SingleSideExecutedWithPriceMessage *read, const SingleSideExecutedWithPriceMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_number[i] == written->reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_number[i] == written->cross_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->printable == written->printable);
  for (size_t i = 0; i < 4; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_long[i] == written->volume_long[i]); }
}

/* Single Side Executed With Price Message: written and read back, then read and written back */
static void check_single_side_executed_with_price_message(void) {
  SingleSideExecutedWithPriceMessage sent;
  SingleSideExecutedWithPriceMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_single_side_executed_with_price_message(&sent);
  assert(encode_single_side_executed_with_price_message(&sent, wire, 0) == 33);
  assert(decode_single_side_executed_with_price_message(&got, wire, 0) == 33);
  equal_single_side_executed_with_price_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_executed_with_price_message(&got, wire, 0) == 33);
  assert(encode_single_side_executed_with_price_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Message: 20 bytes ------------------------------------------ */

/* This message is sent whenever an order on the book is modified as a result of a partial cancellation. */
typedef struct {
  uint8_t tracking_number[2];         /* bytes 0 to 1 */
  uint8_t timestamp[6];               /* bytes 2 to 7 */
  uint8_t order_reference_number[8];  /* bytes 8 to 15 */
  uint8_t cancelled_contracts[4];     /* bytes 16 to 19 */
} OrderCancelMessage;

/* any Order Cancel Message at all: every byte one the checker chooses */
static void any_order_cancel_message(OrderCancelMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancelled_contracts[i] = arbitrary(); }
}

/* Order Cancel Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_message(const OrderCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancelled_contracts[i]; }

  return at;
}

/* Order Cancel Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_message(OrderCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancelled_contracts[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Message is what was written, byte for byte */
static void equal_order_cancel_message(const OrderCancelMessage *read, const OrderCancelMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancelled_contracts[i] == written->cancelled_contracts[i]); }
}

/* Order Cancel Message: written and read back, then read and written back */
static void check_order_cancel_message(void) {
  OrderCancelMessage sent;
  OrderCancelMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_order_cancel_message(&sent);
  assert(encode_order_cancel_message(&sent, wire, 0) == 20);
  assert(decode_order_cancel_message(&got, wire, 0) == 20);
  equal_order_cancel_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_message(&got, wire, 0) == 20);
  assert(encode_order_cancel_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Replace Message Short Form: 28 bytes ------------------------ */

/* This message is sent whenever an order or one side of a quote on the book is replaced. The replacement has a new sequence number and replaces the prior sequence number. */
typedef struct {
  uint8_t tracking_number[2];            /* bytes 0 to 1 */
  uint8_t timestamp[6];                  /* bytes 2 to 7 */
  uint8_t original_reference_number[8];  /* bytes 8 to 15 */
  uint8_t new_reference_number[8];       /* bytes 16 to 23 */
  uint8_t price_short[2];                /* bytes 24 to 25 */
  uint8_t volume_short[2];               /* bytes 26 to 27 */
} SingleSideReplaceMessageShortForm;

/* any Single Side Replace Message Short Form at all: every byte one the checker chooses */
static void any_single_side_replace_message_short_form(SingleSideReplaceMessageShortForm *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->volume_short[i] = arbitrary(); }
}

/* Single Side Replace Message Short Form to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_single_side_replace_message_short_form(const SingleSideReplaceMessageShortForm *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_reference_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->volume_short[i]; }

  return at;
}

/* Single Side Replace Message Short Form off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_single_side_replace_message_short_form(SingleSideReplaceMessageShortForm *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->volume_short[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Replace Message Short Form is what was written, byte for byte */
static void equal_single_side_replace_message_short_form(const SingleSideReplaceMessageShortForm *read, const SingleSideReplaceMessageShortForm *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_reference_number[i] == written->original_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_reference_number[i] == written->new_reference_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->volume_short[i] == written->volume_short[i]); }
}

/* Single Side Replace Message Short Form: written and read back, then read and written back */
static void check_single_side_replace_message_short_form(void) {
  SingleSideReplaceMessageShortForm sent;
  SingleSideReplaceMessageShortForm got;
  uint8_t wire[28];
  uint8_t again[28];

  any_single_side_replace_message_short_form(&sent);
  assert(encode_single_side_replace_message_short_form(&sent, wire, 0) == 28);
  assert(decode_single_side_replace_message_short_form(&got, wire, 0) == 28);
  equal_single_side_replace_message_short_form(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_replace_message_short_form(&got, wire, 0) == 28);
  assert(encode_single_side_replace_message_short_form(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Replace Message Long Form: 32 bytes ------------------------- */

/* This message is sent whenever an order or one side of a quote on the book is replaced. The replacement has a new sequence number and replaces the prior sequence number. */
typedef struct {
  uint8_t tracking_number[2];            /* bytes 0 to 1 */
  uint8_t timestamp[6];                  /* bytes 2 to 7 */
  uint8_t original_reference_number[8];  /* bytes 8 to 15 */
  uint8_t new_reference_number[8];       /* bytes 16 to 23 */
  uint8_t price_long[4];                 /* bytes 24 to 27 */
  uint8_t volume_long[4];                /* bytes 28 to 31 */
} SingleSideReplaceMessageLongForm;

/* any Single Side Replace Message Long Form at all: every byte one the checker chooses */
static void any_single_side_replace_message_long_form(SingleSideReplaceMessageLongForm *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = arbitrary(); }
}

/* Single Side Replace Message Long Form to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_single_side_replace_message_long_form(const SingleSideReplaceMessageLongForm *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_long[i]; }

  return at;
}

/* Single Side Replace Message Long Form off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_single_side_replace_message_long_form(SingleSideReplaceMessageLongForm *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Replace Message Long Form is what was written, byte for byte */
static void equal_single_side_replace_message_long_form(const SingleSideReplaceMessageLongForm *read, const SingleSideReplaceMessageLongForm *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_reference_number[i] == written->original_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_reference_number[i] == written->new_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_long[i] == written->volume_long[i]); }
}

/* Single Side Replace Message Long Form: written and read back, then read and written back */
static void check_single_side_replace_message_long_form(void) {
  SingleSideReplaceMessageLongForm sent;
  SingleSideReplaceMessageLongForm got;
  uint8_t wire[32];
  uint8_t again[32];

  any_single_side_replace_message_long_form(&sent);
  assert(encode_single_side_replace_message_long_form(&sent, wire, 0) == 32);
  assert(decode_single_side_replace_message_long_form(&got, wire, 0) == 32);
  equal_single_side_replace_message_long_form(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_replace_message_long_form(&got, wire, 0) == 32);
  assert(encode_single_side_replace_message_long_form(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Delete Message: 16 bytes ------------------------------------ */

/* The message is sent when an order or a side of a quote is being cancelled. All remaining contracts are no longer accessible so the side should be removed from the book. */
typedef struct {
  uint8_t tracking_number[2];   /* bytes 0 to 1 */
  uint8_t timestamp[6];         /* bytes 2 to 7 */
  uint8_t reference_number[8];  /* bytes 8 to 15 */
} SingleSideDeleteMessage;

/* any Single Side Delete Message at all: every byte one the checker chooses */
static void any_single_side_delete_message(SingleSideDeleteMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_number[i] = arbitrary(); }
}

/* Single Side Delete Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_single_side_delete_message(const SingleSideDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_number[i]; }

  return at;
}

/* Single Side Delete Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_single_side_delete_message(SingleSideDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Delete Message is what was written, byte for byte */
static void equal_single_side_delete_message(const SingleSideDeleteMessage *read, const SingleSideDeleteMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_number[i] == written->reference_number[i]); }
}

/* Single Side Delete Message: written and read back, then read and written back */
static void check_single_side_delete_message(void) {
  SingleSideDeleteMessage sent;
  SingleSideDeleteMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_single_side_delete_message(&sent);
  assert(encode_single_side_delete_message(&sent, wire, 0) == 16);
  assert(decode_single_side_delete_message(&got, wire, 0) == 16);
  equal_single_side_delete_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_delete_message(&got, wire, 0) == 16);
  assert(encode_single_side_delete_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Change Message: 25 bytes ------------------------------------ */

/* This message is sent whenever an order or a side of a quote is being updated for price and (or) contracts. The reference number associated with the order quote is unchanged. */
typedef struct {
  uint8_t tracking_number[2];   /* bytes 0 to 1 */
  uint8_t timestamp[6];         /* bytes 2 to 7 */
  uint8_t reference_number[8];  /* bytes 8 to 15 */
  uint8_t change_reason;        /* byte 16 */
  uint8_t price_long[4];        /* bytes 17 to 20 */
  uint8_t volume_long[4];       /* bytes 21 to 24 */
} SingleSideChangeMessage;

/* any Single Side Change Message at all: every byte one the checker chooses */
static void any_single_side_change_message(SingleSideChangeMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_number[i] = arbitrary(); }
  record->change_reason = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = arbitrary(); }
}

/* Single Side Change Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_single_side_change_message(const SingleSideChangeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_number[i]; }
  wire[at++] = record->change_reason;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_long[i]; }

  return at;
}

/* Single Side Change Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_single_side_change_message(SingleSideChangeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_number[i] = wire[at++]; }
  record->change_reason = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Change Message is what was written, byte for byte */
static void equal_single_side_change_message(const SingleSideChangeMessage *read, const SingleSideChangeMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_number[i] == written->reference_number[i]); }
  assert(read->change_reason == written->change_reason);
  for (size_t i = 0; i < 4; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_long[i] == written->volume_long[i]); }
}

/* Single Side Change Message: written and read back, then read and written back */
static void check_single_side_change_message(void) {
  SingleSideChangeMessage sent;
  SingleSideChangeMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_single_side_change_message(&sent);
  assert(encode_single_side_change_message(&sent, wire, 0) == 25);
  assert(decode_single_side_change_message(&got, wire, 0) == 25);
  equal_single_side_change_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_change_message(&got, wire, 0) == 25);
  assert(encode_single_side_change_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Replace Message Short Form: 48 bytes ------------------------------ */

/* This message is sent whenever a quote on the book is replaced. The replaced quote has new sequence numbers on both sides. These new sequence numbers replace the prior sequence numbers on the quote. */
typedef struct {
  uint8_t tracking_number[2];                /* bytes 0 to 1 */
  uint8_t timestamp[6];                      /* bytes 2 to 7 */
  uint8_t original_bid_reference_number[8];  /* bytes 8 to 15 */
  uint8_t bid_reference_number[8];           /* bytes 16 to 23 */
  uint8_t original_ask_reference_number[8];  /* bytes 24 to 31 */
  uint8_t ask_reference_number[8];           /* bytes 32 to 39 */
  uint8_t bid_price_short[2];                /* bytes 40 to 41 */
  uint8_t bid_size_short[2];                 /* bytes 42 to 43 */
  uint8_t ask_price_short[2];                /* bytes 44 to 45 */
  uint8_t ask_size_short[2];                 /* bytes 46 to 47 */
} QuoteReplaceMessageShortForm;

/* any Quote Replace Message Short Form at all: every byte one the checker chooses */
static void any_quote_replace_message_short_form(QuoteReplaceMessageShortForm *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_bid_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_ask_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_size_short[i] = arbitrary(); }
}

/* Quote Replace Message Short Form to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_quote_replace_message_short_form(const QuoteReplaceMessageShortForm *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
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

/* Quote Replace Message Short Form off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_quote_replace_message_short_form(QuoteReplaceMessageShortForm *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
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

/* what was read of Quote Replace Message Short Form is what was written, byte for byte */
static void equal_quote_replace_message_short_form(const QuoteReplaceMessageShortForm *read, const QuoteReplaceMessageShortForm *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_bid_reference_number[i] == written->original_bid_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_reference_number[i] == written->bid_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_ask_reference_number[i] == written->original_ask_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_reference_number[i] == written->ask_reference_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_price_short[i] == written->bid_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_size_short[i] == written->bid_size_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_price_short[i] == written->ask_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_size_short[i] == written->ask_size_short[i]); }
}

/* Quote Replace Message Short Form: written and read back, then read and written back */
static void check_quote_replace_message_short_form(void) {
  QuoteReplaceMessageShortForm sent;
  QuoteReplaceMessageShortForm got;
  uint8_t wire[48];
  uint8_t again[48];

  any_quote_replace_message_short_form(&sent);
  assert(encode_quote_replace_message_short_form(&sent, wire, 0) == 48);
  assert(decode_quote_replace_message_short_form(&got, wire, 0) == 48);
  equal_quote_replace_message_short_form(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_replace_message_short_form(&got, wire, 0) == 48);
  assert(encode_quote_replace_message_short_form(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Replace Message Long Form: 56 bytes ------------------------------- */

/* This message is sent whenever a quote on the book is replaced. The replaced quote has new sequence numbers on both sides. These new sequence numbers replace the prior sequence numbers on the quote. */
typedef struct {
  uint8_t tracking_number[2];                /* bytes 0 to 1 */
  uint8_t timestamp[6];                      /* bytes 2 to 7 */
  uint8_t original_bid_reference_number[8];  /* bytes 8 to 15 */
  uint8_t bid_reference_number[8];           /* bytes 16 to 23 */
  uint8_t original_ask_reference_number[8];  /* bytes 24 to 31 */
  uint8_t ask_reference_number[8];           /* bytes 32 to 39 */
  uint8_t bid_price_long[4];                 /* bytes 40 to 43 */
  uint8_t bid_size_long[4];                  /* bytes 44 to 47 */
  uint8_t ask_price_long[4];                 /* bytes 48 to 51 */
  uint8_t ask_size_long[4];                  /* bytes 52 to 55 */
} QuoteReplaceMessageLongForm;

/* any Quote Replace Message Long Form at all: every byte one the checker chooses */
static void any_quote_replace_message_long_form(QuoteReplaceMessageLongForm *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_bid_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_ask_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_long[i] = arbitrary(); }
}

/* Quote Replace Message Long Form to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_quote_replace_message_long_form(const QuoteReplaceMessageLongForm *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
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

/* Quote Replace Message Long Form off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_quote_replace_message_long_form(QuoteReplaceMessageLongForm *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
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

/* what was read of Quote Replace Message Long Form is what was written, byte for byte */
static void equal_quote_replace_message_long_form(const QuoteReplaceMessageLongForm *read, const QuoteReplaceMessageLongForm *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_bid_reference_number[i] == written->original_bid_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_reference_number[i] == written->bid_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_ask_reference_number[i] == written->original_ask_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_reference_number[i] == written->ask_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price_long[i] == written->bid_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_long[i] == written->bid_size_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_price_long[i] == written->ask_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_long[i] == written->ask_size_long[i]); }
}

/* Quote Replace Message Long Form: written and read back, then read and written back */
static void check_quote_replace_message_long_form(void) {
  QuoteReplaceMessageLongForm sent;
  QuoteReplaceMessageLongForm got;
  uint8_t wire[56];
  uint8_t again[56];

  any_quote_replace_message_long_form(&sent);
  assert(encode_quote_replace_message_long_form(&sent, wire, 0) == 56);
  assert(decode_quote_replace_message_long_form(&got, wire, 0) == 56);
  equal_quote_replace_message_long_form(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_replace_message_long_form(&got, wire, 0) == 56);
  assert(encode_quote_replace_message_long_form(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Delete Message: 24 bytes ------------------------------------------ */

/* The message is sent when a single quote is being cancelled. All remaining contracts are no longer accessible so the quote should be removed from the book. */
typedef struct {
  uint8_t tracking_number[2];       /* bytes 0 to 1 */
  uint8_t timestamp[6];             /* bytes 2 to 7 */
  uint8_t bid_reference_number[8];  /* bytes 8 to 15 */
  uint8_t ask_reference_number[8];  /* bytes 16 to 23 */
} QuoteDeleteMessage;

/* any Quote Delete Message at all: every byte one the checker chooses */
static void any_quote_delete_message(QuoteDeleteMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = arbitrary(); }
}

/* Quote Delete Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_quote_delete_message(const QuoteDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_reference_number[i]; }

  return at;
}

/* Quote Delete Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_quote_delete_message(QuoteDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Delete Message is what was written, byte for byte */
static void equal_quote_delete_message(const QuoteDeleteMessage *read, const QuoteDeleteMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_reference_number[i] == written->bid_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_reference_number[i] == written->ask_reference_number[i]); }
}

/* Quote Delete Message: written and read back, then read and written back */
static void check_quote_delete_message(void) {
  QuoteDeleteMessage sent;
  QuoteDeleteMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_quote_delete_message(&sent);
  assert(encode_quote_delete_message(&sent, wire, 0) == 24);
  assert(decode_quote_delete_message(&got, wire, 0) == 24);
  equal_quote_delete_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_delete_message(&got, wire, 0) == 24);
  assert(encode_quote_delete_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Trade Messages Non Auction: 29 bytes ---------------------------- */

/* This Options Trade Message is designed to provide execution details for normal match events involving non-displayable order types. (Note: There is a separate message for NASDAQ Option auction events.) */
typedef struct {
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t timestamp[6];        /* bytes 2 to 7 */
  uint8_t buy_sell_indicator;  /* byte 8 */
  uint8_t option_id[4];        /* bytes 9 to 12 */
  uint8_t cross_number[4];     /* bytes 13 to 16 */
  uint8_t match_number[4];     /* bytes 17 to 20 */
  uint8_t price_long[4];       /* bytes 21 to 24 */
  uint8_t volume_long[4];      /* bytes 25 to 28 */
} OptionsTradeMessagesNonAuction;

/* any Options Trade Messages Non Auction at all: every byte one the checker chooses */
static void any_options_trade_messages_non_auction(OptionsTradeMessagesNonAuction *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = arbitrary(); }
}

/* Options Trade Messages Non Auction to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_options_trade_messages_non_auction(const OptionsTradeMessagesNonAuction *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_long[i]; }

  return at;
}

/* Options Trade Messages Non Auction off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_options_trade_messages_non_auction(OptionsTradeMessagesNonAuction *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = wire[at++]; }

  return at;
}

/* what was read of Options Trade Messages Non Auction is what was written, byte for byte */
static void equal_options_trade_messages_non_auction(const OptionsTradeMessagesNonAuction *read, const OptionsTradeMessagesNonAuction *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_number[i] == written->cross_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_long[i] == written->volume_long[i]); }
}

/* Options Trade Messages Non Auction: written and read back, then read and written back */
static void check_options_trade_messages_non_auction(void) {
  OptionsTradeMessagesNonAuction sent;
  OptionsTradeMessagesNonAuction got;
  uint8_t wire[29];
  uint8_t again[29];

  any_options_trade_messages_non_auction(&sent);
  assert(encode_options_trade_messages_non_auction(&sent, wire, 0) == 29);
  assert(decode_options_trade_messages_non_auction(&got, wire, 0) == 29);
  equal_options_trade_messages_non_auction(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_options_trade_messages_non_auction(&got, wire, 0) == 29);
  assert(encode_options_trade_messages_non_auction(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Cross Trade Message: 29 bytes ----------------------------------- */

/* This message will also be used to report all executions within a price improvement (PRISM) auction. */
typedef struct {
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t timestamp[6];        /* bytes 2 to 7 */
  uint8_t option_id[4];        /* bytes 8 to 11 */
  uint8_t cross_number[4];     /* bytes 12 to 15 */
  uint8_t match_number[4];     /* bytes 16 to 19 */
  uint8_t cross_type;          /* byte 20 */
  uint8_t price_long[4];       /* bytes 21 to 24 */
  uint8_t volume_long[4];      /* bytes 25 to 28 */
} OptionsCrossTradeMessage;

/* any Options Cross Trade Message at all: every byte one the checker chooses */
static void any_options_cross_trade_message(OptionsCrossTradeMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  record->cross_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = arbitrary(); }
}

/* Options Cross Trade Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_options_cross_trade_message(const OptionsCrossTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->cross_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_long[i]; }

  return at;
}

/* Options Cross Trade Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_options_cross_trade_message(OptionsCrossTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  record->cross_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_long[i] = wire[at++]; }

  return at;
}

/* what was read of Options Cross Trade Message is what was written, byte for byte */
static void equal_options_cross_trade_message(const OptionsCrossTradeMessage *read, const OptionsCrossTradeMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_number[i] == written->cross_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->cross_type == written->cross_type);
  for (size_t i = 0; i < 4; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_long[i] == written->volume_long[i]); }
}

/* Options Cross Trade Message: written and read back, then read and written back */
static void check_options_cross_trade_message(void) {
  OptionsCrossTradeMessage sent;
  OptionsCrossTradeMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_options_cross_trade_message(&sent);
  assert(encode_options_cross_trade_message(&sent, wire, 0) == 29);
  assert(decode_options_cross_trade_message(&got, wire, 0) == 29);
  equal_options_cross_trade_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_options_cross_trade_message(&got, wire, 0) == 29);
  assert(encode_options_cross_trade_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broken Trade Order Executed Message: 16 bytes --------------------------- */

/* The Broken Trade Message is sent whenever an execution on NASDAQ is broken. An execution may be broken if it is found to be “clearly erroneous” pursuant to NASDAQ’s Clearly Erroneous Policy. A trade break is final; once a trade is broken, it cannot be reinstated. */
typedef struct {
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t timestamp[6];        /* bytes 2 to 7 */
  uint8_t cross_number[4];     /* bytes 8 to 11 */
  uint8_t match_number[4];     /* bytes 12 to 15 */
} BrokenTradeOrderExecutedMessage;

/* any Broken Trade Order Executed Message at all: every byte one the checker chooses */
static void any_broken_trade_order_executed_message(BrokenTradeOrderExecutedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
}

/* Broken Trade Order Executed Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_order_executed_message(const BrokenTradeOrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Broken Trade Order Executed Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_order_executed_message(BrokenTradeOrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Broken Trade Order Executed Message is what was written, byte for byte */
static void equal_broken_trade_order_executed_message(const BrokenTradeOrderExecutedMessage *read, const BrokenTradeOrderExecutedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_number[i] == written->cross_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Broken Trade Order Executed Message: written and read back, then read and written back */
static void check_broken_trade_order_executed_message(void) {
  BrokenTradeOrderExecutedMessage sent;
  BrokenTradeOrderExecutedMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_broken_trade_order_executed_message(&sent);
  assert(encode_broken_trade_order_executed_message(&sent, wire, 0) == 16);
  assert(decode_broken_trade_order_executed_message(&got, wire, 0) == 16);
  equal_broken_trade_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_broken_trade_order_executed_message(&got, wire, 0) == 16);
  assert(encode_broken_trade_order_executed_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Noii Message: 34 bytes -------------------------------------------------- */

/* For the NASDAQ Opening Auction, NASDAQ will begin the dissemination of NOII messages for a put or a call option five minutes prior to the start of opening process event and two minutes prior to the halt resumption (reopening) process event. */
typedef struct {
  uint8_t tracking_number[2];       /* bytes 0 to 1 */
  uint8_t timestamp[6];             /* bytes 2 to 7 */
  uint8_t auction_id[4];            /* bytes 8 to 11 */
  uint8_t auction_type;             /* byte 12 */
  uint8_t paired_contracts[4];      /* bytes 13 to 16 */
  uint8_t imbalance_direction;      /* byte 17 */
  uint8_t option_id[4];             /* bytes 18 to 21 */
  uint8_t imbalance_price[4];       /* bytes 22 to 25 */
  uint8_t imbalance_volume[4];      /* bytes 26 to 29 */
  uint8_t customer_firm_indicator;  /* byte 30 */
  uint8_t reserved_3[3];            /* bytes 31 to 33 */
} NoiiMessage;

/* any Noii Message at all: every byte one the checker chooses */
static void any_noii_message(NoiiMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->paired_contracts[i] = arbitrary(); }
  record->imbalance_direction = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->imbalance_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->imbalance_volume[i] = arbitrary(); }
  record->customer_firm_indicator = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Noii Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_noii_message(const NoiiMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->paired_contracts[i]; }
  wire[at++] = record->imbalance_direction;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->imbalance_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->imbalance_volume[i]; }
  wire[at++] = record->customer_firm_indicator;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Noii Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_noii_message(NoiiMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->paired_contracts[i] = wire[at++]; }
  record->imbalance_direction = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->option_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->imbalance_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->imbalance_volume[i] = wire[at++]; }
  record->customer_firm_indicator = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Noii Message is what was written, byte for byte */
static void equal_noii_message(const NoiiMessage *read, const NoiiMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 4; i++) { assert(read->paired_contracts[i] == written->paired_contracts[i]); }
  assert(read->imbalance_direction == written->imbalance_direction);
  for (size_t i = 0; i < 4; i++) { assert(read->option_id[i] == written->option_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->imbalance_price[i] == written->imbalance_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->imbalance_volume[i] == written->imbalance_volume[i]); }
  assert(read->customer_firm_indicator == written->customer_firm_indicator);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Noii Message: written and read back, then read and written back */
static void check_noii_message(void) {
  NoiiMessage sent;
  NoiiMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_noii_message(&sent);
  assert(encode_noii_message(&sent, wire, 0) == 34);
  assert(decode_noii_message(&got, wire, 0) == 34);
  equal_noii_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_noii_message(&got, wire, 0) == 34);
  assert(encode_noii_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_system_event_message();
  check_options_directory_message();
  check_trading_action_message();
  check_security_open_message();
  check_add_order_message_short_message_form();
  check_add_order_message_long_form_message();
  check_add_quote_message_short_form_message();
  check_add_quote_message_long_form_message();
  check_single_side_executed_message();
  check_single_side_executed_with_price_message();
  check_order_cancel_message();
  check_single_side_replace_message_short_form();
  check_single_side_replace_message_long_form();
  check_single_side_delete_message();
  check_single_side_change_message();
  check_quote_replace_message_short_form();
  check_quote_replace_message_long_form();
  check_quote_delete_message();
  check_options_trade_messages_non_auction();
  check_options_cross_trade_message();
  check_broken_trade_order_executed_message();
  check_noii_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
