// cboe/cfefutures/oofmulticasttop/CfeFutures_OofMulticastTop_Pitch_v1_0_8.c
/*
 * Chicago Board Options Exchange OOF Multicast Top
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
 *   - a run filling what frames it
 *   - a run counted by a field
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

/* ---- Packet Header: 8 bytes -------------------------------------------------- */

typedef struct {
  uint8_t length[2];      /* bytes 0 to 1 */
  uint8_t message_count;  /* byte 2 */
  uint8_t unit;           /* byte 3 */
  uint8_t sequence[4];    /* bytes 4 to 7 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  record->message_count = arbitrary();
  record->unit = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
}

/* Packet Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  wire[at++] = record->message_count;
  wire[at++] = record->unit;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }

  return at;
}

/* Packet Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  record->message_count = wire[at++];
  record->unit = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  assert(read->message_count == written->message_count);
  assert(read->unit == written->unit);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 8);
  assert(decode_packet_header(&got, wire, 0) == 8);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 8);
  assert(encode_packet_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 2 bytes ------------------------------------------------- */

typedef struct {
  uint8_t message_length;  /* byte 0 */
  uint8_t message_type;    /* byte 1 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->message_length = arbitrary();
  record->message_type = arbitrary();
}

/* Message Header to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_length;
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->message_length = wire[at++];
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->message_length == written->message_length);
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

/* ---- Time Reference Message: 16 bytes ---------------------------------------- */

/* The Time Reference message is used to provide a midnight reference point for recipients of the feed. It is sent whenever the system starts up and when the system crosses a midnight boundary. All subsequent Time messages for the same unit will the use the last Midnight Reference until another Time Reference message is received for that unit. The Time Reference message includes the Trade Date, so most other sequenced messages will not include that information. Time Reference messages will be included in a spin response. */
typedef struct {
  uint8_t midnight_reference[4];  /* bytes 0 to 3 */
  uint8_t time_reference[4];      /* bytes 4 to 7 */
  uint8_t time_offset[4];         /* bytes 8 to 11 */
  uint8_t trade_date[4];          /* bytes 12 to 15 */
} TimeReferenceMessage;

/* any Time Reference Message at all: every byte one the checker chooses */
static void any_time_reference_message(TimeReferenceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->midnight_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = arbitrary(); }
}

/* Time Reference Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_time_reference_message(const TimeReferenceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->midnight_reference[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_reference[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_date[i]; }

  return at;
}

/* Time Reference Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_time_reference_message(TimeReferenceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->midnight_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = wire[at++]; }

  return at;
}

/* what was read of Time Reference Message is what was written, byte for byte */
static void equal_time_reference_message(const TimeReferenceMessage *read, const TimeReferenceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->midnight_reference[i] == written->midnight_reference[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time_reference[i] == written->time_reference[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
}

/* Time Reference Message: written and read back, then read and written back */
static void check_time_reference_message(void) {
  TimeReferenceMessage sent;
  TimeReferenceMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_time_reference_message(&sent);
  assert(encode_time_reference_message(&sent, wire, 0) == 16);
  assert(decode_time_reference_message(&got, wire, 0) == 16);
  equal_time_reference_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_time_reference_message(&got, wire, 0) == 16);
  assert(encode_time_reference_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Time Message: 8 bytes --------------------------------------------------- */

/* A Time message is immediately generated and sent when there is a TOP event for a given clock second. If there is no new sequenced TOP event for a given clock second, then no Time message is sent for that second. All subsequent Time Offset fields for the same unit will use the new Time value as the base until another Time message is received for the same unit. The Time field is the number of seconds relative to midnight Central Time, which is provided in the Time Reference message. The Time message also includes the Epoch Time field, which is the current time represented as the number of whole seconds since the Epoch (Midnight January 1, 1970). */
typedef struct {
  uint8_t time_reference[4];  /* bytes 0 to 3 */
  uint8_t epoch_time[4];      /* bytes 4 to 7 */
} TimeMessage;

/* any Time Message at all: every byte one the checker chooses */
static void any_time_message(TimeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->epoch_time[i] = arbitrary(); }
}

/* Time Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_time_message(const TimeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_reference[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->epoch_time[i]; }

  return at;
}

/* Time Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_time_message(TimeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->epoch_time[i] = wire[at++]; }

  return at;
}

/* what was read of Time Message is what was written, byte for byte */
static void equal_time_message(const TimeMessage *read, const TimeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_reference[i] == written->time_reference[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->epoch_time[i] == written->epoch_time[i]); }
}

/* Time Message: written and read back, then read and written back */
static void check_time_message(void) {
  TimeMessage sent;
  TimeMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_time_message(&sent);
  assert(encode_time_message(&sent, wire, 0) == 8);
  assert(decode_time_message(&got, wire, 0) == 8);
  equal_time_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_time_message(&got, wire, 0) == 8);
  assert(encode_time_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Unit Clear Message: 4 bytes --------------------------------------------- */

/* The Unit Clear message instructs feed recipients to clear all market snapshots for the CFE book in the unit specified in the Sequenced Unit Header message header. It would be distributed in rare recovery events such as a data center fail-over. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} UnitClearMessage;

/* any Unit Clear Message at all: every byte one the checker chooses */
static void any_unit_clear_message(UnitClearMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* Unit Clear Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_unit_clear_message(const UnitClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* Unit Clear Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_unit_clear_message(UnitClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of Unit Clear Message is what was written, byte for byte */
static void equal_unit_clear_message(const UnitClearMessage *read, const UnitClearMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* Unit Clear Message: written and read back, then read and written back */
static void check_unit_clear_message(void) {
  UnitClearMessage sent;
  UnitClearMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_unit_clear_message(&sent);
  assert(encode_unit_clear_message(&sent, wire, 0) == 4);
  assert(decode_unit_clear_message(&got, wire, 0) == 4);
  equal_unit_clear_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_unit_clear_message(&got, wire, 0) == 4);
  assert(encode_unit_clear_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Oof Symbol Mapping Message: 58 bytes ------------------------------------ */

/* An OOF Symbol Mapping message is used to map the 6 character multicast feed symbol field and options on futures name to the option contract and future underlying. The option contract is comprised of the strike price, put/call flag, options expiration date, and future underlying. The future underlying is comprised of the futures product and futures expiration date, which map to a futures symbol. This message can be sent either as a sequenced message or as an unsequenced message. It is sent as a sequenced message at system startup upon the beginning of a trading session or if an instrument is created or modified during a trading day. A new sequenced message may also be sent for a symbol that does not visibly change any attribute. A continuous loop of unsequenced symbol mapping messages (sequence = 0) is sent throughout the day at variable rates as bandwidth allows. The Time Offset field should be ignored on unsequenced messages. OOF Symbol Mapping messages are included in a spin response and will be disseminated before Complex Instrument Definition Expanded messages. */
typedef struct {
  uint8_t time_offset[4];               /* bytes 0 to 3 */
  uint8_t feed_symbol[6];               /* bytes 4 to 9 */
  uint8_t futures_product[8];           /* bytes 10 to 17 */
  uint8_t futures_expiration[4];        /* bytes 18 to 21 */
  uint8_t futures_symbol[6];            /* bytes 22 to 27 */
  uint8_t strike_price[8];              /* bytes 28 to 35 */
  uint8_t call_put_indicator;           /* byte 36 */
  uint8_t options_expiration[4];        /* bytes 37 to 40 */
  uint8_t options_on_futures_name[16];  /* bytes 41 to 56 */
  uint8_t symbol_condition;             /* byte 57 */
} OofSymbolMappingMessage;

/* any Oof Symbol Mapping Message at all: every byte one the checker chooses */
static void any_oof_symbol_mapping_message(OofSymbolMappingMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->feed_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->futures_product[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->futures_expiration[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->futures_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->call_put_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->options_expiration[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->options_on_futures_name[i] = arbitrary(); }
  record->symbol_condition = arbitrary();
}

/* Oof Symbol Mapping Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_oof_symbol_mapping_message(const OofSymbolMappingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->feed_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->futures_product[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->futures_expiration[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->futures_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->call_put_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->options_expiration[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->options_on_futures_name[i]; }
  wire[at++] = record->symbol_condition;

  return at;
}

/* Oof Symbol Mapping Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_oof_symbol_mapping_message(OofSymbolMappingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->feed_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->futures_product[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->futures_expiration[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->futures_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->call_put_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->options_expiration[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->options_on_futures_name[i] = wire[at++]; }
  record->symbol_condition = wire[at++];

  return at;
}

/* what was read of Oof Symbol Mapping Message is what was written, byte for byte */
static void equal_oof_symbol_mapping_message(const OofSymbolMappingMessage *read, const OofSymbolMappingMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->feed_symbol[i] == written->feed_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->futures_product[i] == written->futures_product[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->futures_expiration[i] == written->futures_expiration[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->futures_symbol[i] == written->futures_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->call_put_indicator == written->call_put_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->options_expiration[i] == written->options_expiration[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->options_on_futures_name[i] == written->options_on_futures_name[i]); }
  assert(read->symbol_condition == written->symbol_condition);
}

/* Oof Symbol Mapping Message: written and read back, then read and written back */
static void check_oof_symbol_mapping_message(void) {
  OofSymbolMappingMessage sent;
  OofSymbolMappingMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_oof_symbol_mapping_message(&sent);
  assert(encode_oof_symbol_mapping_message(&sent, wire, 0) == 58);
  assert(decode_oof_symbol_mapping_message(&got, wire, 0) == 58);
  equal_oof_symbol_mapping_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_oof_symbol_mapping_message(&got, wire, 0) == 58);
  assert(encode_oof_symbol_mapping_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 16 bytes ---------------------------------------- */

/* The Trading Status message is used to indicate the current trading status of a symbol. A Trading Status message will be sent for all symbols as they transition through various trading states. If a Trading Status message has not been received for a symbol, then the Trading Status for the symbol should be assumed to be H = Halted. The following summarizes the Trading Status values for options in the CFE system: H = Halted state. This state is used for Supervisory Halts initiated by the Trade Desk. Orders are not being accepted in this state. Q = Queuing state. This state is used when orders are being accepted for queuing. The Queuing state is used during the pre-open for all symbols. It is also used for spread instruments that may not be tradeable due to Threshold Width. T = Trading state. This state is used when the symbol is available for trading. CFE will send a Trading Status of Q once orders can be accepted for queuing in preparation for the open. At or after the opening time, CFE will send a Trading Status of T as symbols are opened for trading. Once trading is done for the day CFE will send a Trading Status of H indicating the symbol is Halted. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
  uint8_t symbol[6];       /* bytes 4 to 9 */
  uint8_t reserved_2[2];   /* bytes 10 to 11 */
  uint8_t trading_status;  /* byte 12 */
  uint8_t reserved_3[3];   /* bytes 13 to 15 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->trading_status = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Trading Status Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->trading_status;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Trading Status Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->trading_status = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->trading_status == written->trading_status);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Trading Status Message: written and read back, then read and written back */
static void check_trading_status_message(void) {
  TradingStatusMessage sent;
  TradingStatusMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_trading_status_message(&sent);
  assert(encode_trading_status_message(&sent, wire, 0) == 16);
  assert(decode_trading_status_message(&got, wire, 0) == 16);
  equal_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_message(&got, wire, 0) == 16);
  assert(encode_trading_status_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Update Short Message: 15 bytes ------------------------------ */

/* Single Side Update messages provide an updated price and size for a single side of a Symbol. The side is denoted by the Side field. One Single Side Update message may reflect one or more updates to the inside book that were processed at the same time, but will only be done so in a way that can be arbitrated between A/B feeds. Single Side Update messages come in two variants: Single Side Update (Long) message and Single Side Update (Short) message. The Single Side Update (Short) message is used whenever possible, but the Single Side Update (Long) message is used whenever the Price cannot be represented by a Binary Short Price or the Quantity cannot be represented by an unsigned 16-bit integer. */
typedef struct {
  uint8_t time_offset[4];     /* bytes 0 to 3 */
  uint8_t symbol[6];          /* bytes 4 to 9 */
  uint8_t side;               /* byte 10 */
  uint8_t price_short[2];     /* bytes 11 to 12 */
  uint8_t quantity_short[2];  /* bytes 13 to 14 */
} SingleSideUpdateShortMessage;

/* any Single Side Update Short Message at all: every byte one the checker chooses */
static void any_single_side_update_short_message(SingleSideUpdateShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = arbitrary(); }
}

/* Single Side Update Short Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_single_side_update_short_message(const SingleSideUpdateShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quantity_short[i]; }

  return at;
}

/* Single Side Update Short Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_single_side_update_short_message(SingleSideUpdateShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Update Short Message is what was written, byte for byte */
static void equal_single_side_update_short_message(const SingleSideUpdateShortMessage *read, const SingleSideUpdateShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 2; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->quantity_short[i] == written->quantity_short[i]); }
}

/* Single Side Update Short Message: written and read back, then read and written back */
static void check_single_side_update_short_message(void) {
  SingleSideUpdateShortMessage sent;
  SingleSideUpdateShortMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_single_side_update_short_message(&sent);
  assert(encode_single_side_update_short_message(&sent, wire, 0) == 15);
  assert(decode_single_side_update_short_message(&got, wire, 0) == 15);
  equal_single_side_update_short_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_update_short_message(&got, wire, 0) == 15);
  assert(encode_single_side_update_short_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Update Long Message: 23 bytes ------------------------------- */

/* Single Side Update messages provide an updated price and size for a single side of a Symbol. The side is denoted by the Side field. One Single Side Update message may reflect one or more updates to the inside book that were processed at the same time, but will only be done so in a way that can be arbitrated between A/B feeds. Single Side Update messages come in two variants: Single Side Update (Long) message and Single Side Update (Short) message. The Single Side Update (Short) message is used whenever possible, but the Single Side Update (Long) message is used whenever the Price cannot be represented by a Binary Short Price or the Quantity cannot be represented by an unsigned 16-bit integer. */
typedef struct {
  uint8_t time_offset[4];    /* bytes 0 to 3 */
  uint8_t symbol[6];         /* bytes 4 to 9 */
  uint8_t side;              /* byte 10 */
  uint8_t price_long[8];     /* bytes 11 to 18 */
  uint8_t quantity_long[4];  /* bytes 19 to 22 */
} SingleSideUpdateLongMessage;

/* any Single Side Update Long Message at all: every byte one the checker chooses */
static void any_single_side_update_long_message(SingleSideUpdateLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
}

/* Single Side Update Long Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_single_side_update_long_message(const SingleSideUpdateLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }

  return at;
}

/* Single Side Update Long Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_single_side_update_long_message(SingleSideUpdateLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Update Long Message is what was written, byte for byte */
static void equal_single_side_update_long_message(const SingleSideUpdateLongMessage *read, const SingleSideUpdateLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
}

/* Single Side Update Long Message: written and read back, then read and written back */
static void check_single_side_update_long_message(void) {
  SingleSideUpdateLongMessage sent;
  SingleSideUpdateLongMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_single_side_update_long_message(&sent);
  assert(encode_single_side_update_long_message(&sent, wire, 0) == 23);
  assert(decode_single_side_update_long_message(&got, wire, 0) == 23);
  equal_single_side_update_long_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_update_long_message(&got, wire, 0) == 23);
  assert(encode_single_side_update_long_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Two Side Update Short Message: 18 bytes --------------------------------- */

/* Two Side Update messages provide an updated price and size for both sides of a Symbol. One Two Side Update message may reflect one or more updates to the inside book that were processed at the same time, but will only be done so in a way that can be arbitrated between A/B feeds. Two Side Update messages come in two variants: Two Side Update (Long) message and Two Side Update (Short) message. The Two Side Update (Short) message is used whenever possible, but the Two Side Update (Long) message is used whenever the Price cannot be represented by a Binary Short Price or the Quantity cannot be represented by an unsigned 16-bit integer. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t symbol[6];              /* bytes 4 to 9 */
  uint8_t bid_price_short[2];     /* bytes 10 to 11 */
  uint8_t bid_quantity_short[2];  /* bytes 12 to 13 */
  uint8_t ask_price_short[2];     /* bytes 14 to 15 */
  uint8_t ask_quantity_short[2];  /* bytes 16 to 17 */
} TwoSideUpdateShortMessage;

/* any Two Side Update Short Message at all: every byte one the checker chooses */
static void any_two_side_update_short_message(TwoSideUpdateShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_quantity_short[i] = arbitrary(); }
}

/* Two Side Update Short Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_two_side_update_short_message(const TwoSideUpdateShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_quantity_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_quantity_short[i]; }

  return at;
}

/* Two Side Update Short Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_two_side_update_short_message(TwoSideUpdateShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_quantity_short[i] = wire[at++]; }

  return at;
}

/* what was read of Two Side Update Short Message is what was written, byte for byte */
static void equal_two_side_update_short_message(const TwoSideUpdateShortMessage *read, const TwoSideUpdateShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_price_short[i] == written->bid_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_quantity_short[i] == written->bid_quantity_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_price_short[i] == written->ask_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_quantity_short[i] == written->ask_quantity_short[i]); }
}

/* Two Side Update Short Message: written and read back, then read and written back */
static void check_two_side_update_short_message(void) {
  TwoSideUpdateShortMessage sent;
  TwoSideUpdateShortMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_two_side_update_short_message(&sent);
  assert(encode_two_side_update_short_message(&sent, wire, 0) == 18);
  assert(decode_two_side_update_short_message(&got, wire, 0) == 18);
  equal_two_side_update_short_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_two_side_update_short_message(&got, wire, 0) == 18);
  assert(encode_two_side_update_short_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Two Side Update Long Message: 34 bytes ---------------------------------- */

/* Two Side Update messages provide an updated price and size for both sides of a Symbol. One Two Side Update message may reflect one or more updates to the inside book that were processed at the same time, but will only be done so in a way that can be arbitrated between A/B feeds. Two Side Update messages come in two variants: Two Side Update (Long) message and Two Side Update (Short) message. The Two Side Update (Short) message is used whenever possible, but the Two Side Update (Long) message is used whenever the Price cannot be represented by a Binary Short Price or the Quantity cannot be represented by an unsigned 16-bit integer. */
typedef struct {
  uint8_t time_offset[4];        /* bytes 0 to 3 */
  uint8_t symbol[6];             /* bytes 4 to 9 */
  uint8_t bid_price_long[8];     /* bytes 10 to 17 */
  uint8_t bid_quantity_long[4];  /* bytes 18 to 21 */
  uint8_t ask_price_long[8];     /* bytes 22 to 29 */
  uint8_t ask_quantity_long[4];  /* bytes 30 to 33 */
} TwoSideUpdateLongMessage;

/* any Two Side Update Long Message at all: every byte one the checker chooses */
static void any_two_side_update_long_message(TwoSideUpdateLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_quantity_long[i] = arbitrary(); }
}

/* Two Side Update Long Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_two_side_update_long_message(const TwoSideUpdateLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_quantity_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_quantity_long[i]; }

  return at;
}

/* Two Side Update Long Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_two_side_update_long_message(TwoSideUpdateLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Two Side Update Long Message is what was written, byte for byte */
static void equal_two_side_update_long_message(const TwoSideUpdateLongMessage *read, const TwoSideUpdateLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_price_long[i] == written->bid_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_quantity_long[i] == written->bid_quantity_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_price_long[i] == written->ask_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_quantity_long[i] == written->ask_quantity_long[i]); }
}

/* Two Side Update Long Message: written and read back, then read and written back */
static void check_two_side_update_long_message(void) {
  TwoSideUpdateLongMessage sent;
  TwoSideUpdateLongMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_two_side_update_long_message(&sent);
  assert(encode_two_side_update_long_message(&sent, wire, 0) == 34);
  assert(decode_two_side_update_long_message(&got, wire, 0) == 34);
  equal_two_side_update_long_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_two_side_update_long_message(&got, wire, 0) == 34);
  assert(encode_two_side_update_long_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Top Trade Message: 35 bytes --------------------------------------------- */

/* The TOP Trade message provides information about executions of orders on the CFE book. TOP Trade messages are necessary to calculate CFE execution-based data. TOP Trade messages do not alter the book. One or more Single Side Update or Two Side Update messages will follow a TOP Trade message to reflect the updated book (for example, an aggressive order may take out one or more price levels and establish a new level on the opposite side). Any order may be executed in parts. A complete view of all CFE executions can be built from all TOP Trade messages. The TOP Trade message sends the trade price, trade quantity, execution id, and trade condition of a trade as well as the cumulative volume for the business day. A TOP Trade message will be sent for each execution, but not every TOP Trade message indicates a trade. The Trade Condition value of X (Trade Break) is sent whenever an execution on CFE is broken. Trade breaks are rare and only affect applications that rely upon CFE execution-based data. Trade breaks will contain the Symbol, Quantity, Price, and Execution Id of the original trade. The Total Volume field will be reduced by the number of shares reported in the Quantity field. */
typedef struct {
  uint8_t time_offset[4];    /* bytes 0 to 3 */
  uint8_t symbol[6];         /* bytes 4 to 9 */
  uint8_t quantity_long[4];  /* bytes 10 to 13 */
  uint8_t price_long[8];     /* bytes 14 to 21 */
  uint8_t execution_id[8];   /* bytes 22 to 29 */
  uint8_t total_volume[4];   /* bytes 30 to 33 */
  uint8_t trade_condition;   /* byte 34 */
} TopTradeMessage;

/* any Top Trade Message at all: every byte one the checker chooses */
static void any_top_trade_message(TopTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Top Trade Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_top_trade_message(const TopTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_volume[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Top Trade Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_top_trade_message(TopTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Top Trade Message is what was written, byte for byte */
static void equal_top_trade_message(const TopTradeMessage *read, const TopTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Top Trade Message: written and read back, then read and written back */
static void check_top_trade_message(void) {
  TopTradeMessage sent;
  TopTradeMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_top_trade_message(&sent);
  assert(encode_top_trade_message(&sent, wire, 0) == 35);
  assert(decode_top_trade_message(&got, wire, 0) == 35);
  equal_top_trade_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_top_trade_message(&got, wire, 0) == 35);
  assert(encode_top_trade_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Message: 23 bytes -------------------------------------------- */

/* Settlement messages are used to provide information concerning indicative, approved, or corrected daily and final settlement prices for CFE products. An indicative daily settlement price (Issue = I) is calculated by the system and sent immediately after an instrument closes trading but before the settlement price is approved. An approved settlement price (Issue = S) is sent once the CFE Trade Desk approves a settlement price for an instrument. If there is an error in the approved settlement price, then it may be re-issued (Issue = R). Settlement messages will be included in a spin response. */
typedef struct {
  uint8_t time_offset[4];       /* bytes 0 to 3 */
  uint8_t symbol[6];            /* bytes 4 to 9 */
  uint8_t trade_date[4];        /* bytes 10 to 13 */
  uint8_t settlement_price[8];  /* bytes 14 to 21 */
  uint8_t issue;                /* byte 22 */
} SettlementMessage;

/* any Settlement Message at all: every byte one the checker chooses */
static void any_settlement_message(SettlementMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = arbitrary(); }
  record->issue = arbitrary();
}

/* Settlement Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_settlement_message(const SettlementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price[i]; }
  wire[at++] = record->issue;

  return at;
}

/* Settlement Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_settlement_message(SettlementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = wire[at++]; }
  record->issue = wire[at++];

  return at;
}

/* what was read of Settlement Message is what was written, byte for byte */
static void equal_settlement_message(const SettlementMessage *read, const SettlementMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
  assert(read->issue == written->issue);
}

/* Settlement Message: written and read back, then read and written back */
static void check_settlement_message(void) {
  SettlementMessage sent;
  SettlementMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_settlement_message(&sent);
  assert(encode_settlement_message(&sent, wire, 0) == 23);
  assert(decode_settlement_message(&got, wire, 0) == 23);
  equal_settlement_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_message(&got, wire, 0) == 23);
  assert(encode_settlement_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Session Message: 4 bytes ----------------------------------------- */

/* The End of Session message is sent for each unit when the unit shuts down. No more sequenced messages will be delivered for this unit, but heartbeats from the unit may be received. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} EndOfSessionMessage;

/* any End Of Session Message at all: every byte one the checker chooses */
static void any_end_of_session_message(EndOfSessionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* End Of Session Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_end_of_session_message(const EndOfSessionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* End Of Session Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_end_of_session_message(EndOfSessionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Session Message is what was written, byte for byte */
static void equal_end_of_session_message(const EndOfSessionMessage *read, const EndOfSessionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* End Of Session Message: written and read back, then read and written back */
static void check_end_of_session_message(void) {
  EndOfSessionMessage sent;
  EndOfSessionMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_end_of_session_message(&sent);
  assert(encode_end_of_session_message(&sent, wire, 0) == 4);
  assert(decode_end_of_session_message(&got, wire, 0) == 4);
  equal_end_of_session_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_session_message(&got, wire, 0) == 4);
  assert(encode_end_of_session_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_time_reference_message();
  check_time_message();
  check_unit_clear_message();
  check_oof_symbol_mapping_message();
  check_trading_status_message();
  check_single_side_update_short_message();
  check_single_side_update_long_message();
  check_two_side_update_short_message();
  check_two_side_update_long_message();
  check_top_trade_message();
  check_settlement_message();
  check_end_of_session_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
