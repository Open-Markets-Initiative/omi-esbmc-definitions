// box/boxoptions/solamulticast/BoxOptions_SolaMulticast_v1_9.c
/*
 * Box Options Market Sola Multicast
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
 *   - a Composite rule
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

/* ---- Message Header: 11 bytes ------------------------------------------------ */

/* Hsvf Udp Market Data Packet Header */
typedef struct {
  uint8_t sequence_number[9];  /* bytes 0 to 8 */
  uint8_t message_type[2];     /* bytes 9 to 10 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 9; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = arbitrary(); }
}

/* Message Header to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_type[i]; }

  return at;
}

/* Message Header off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_type[i] == written->message_type[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[11];
  uint8_t again[11];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 11);
  assert(decode_message_header(&got, wire, 0) == 11);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 11);
  assert(encode_message_header(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Transmission Message: 7 bytes ------------------------------------ */

/* This message will be sent to indicate that the day's transmission is complete */
typedef struct {
  uint8_t exchange_id;  /* byte 0 */
  uint8_t time[6];      /* bytes 1 to 6 */
} EndOfTransmissionMessage;

/* any End Of Transmission Message at all: every byte one the checker chooses */
static void any_end_of_transmission_message(EndOfTransmissionMessage *record) {
  record->exchange_id = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
}

/* End Of Transmission Message to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_end_of_transmission_message(const EndOfTransmissionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->exchange_id;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }

  return at;
}

/* End Of Transmission Message off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_end_of_transmission_message(EndOfTransmissionMessage *record, const uint8_t *wire, size_t at) {
  record->exchange_id = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Transmission Message is what was written, byte for byte */
static void equal_end_of_transmission_message(const EndOfTransmissionMessage *read, const EndOfTransmissionMessage *written) {
  assert(read->exchange_id == written->exchange_id);
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
}

/* End Of Transmission Message: written and read back, then read and written back */
static void check_end_of_transmission_message(void) {
  EndOfTransmissionMessage sent;
  EndOfTransmissionMessage got;
  uint8_t wire[7];
  uint8_t again[7];

  any_end_of_transmission_message(&sent);
  assert(encode_end_of_transmission_message(&sent, wire, 0) == 7);
  assert(decode_end_of_transmission_message(&got, wire, 0) == 7);
  equal_end_of_transmission_message(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_transmission_message(&got, wire, 0) == 7);
  assert(encode_end_of_transmission_message(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Circuit Assurance Message: 6 bytes -------------------------------------- */

/* This message is sent out if no messages are sent by BOX for more than one second after the broadcast has started */
typedef struct {
  uint8_t time[6];  /* bytes 0 to 5 */
} CircuitAssuranceMessage;

/* any Circuit Assurance Message at all: every byte one the checker chooses */
static void any_circuit_assurance_message(CircuitAssuranceMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
}

/* Circuit Assurance Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_circuit_assurance_message(const CircuitAssuranceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }

  return at;
}

/* Circuit Assurance Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_circuit_assurance_message(CircuitAssuranceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }

  return at;
}

/* what was read of Circuit Assurance Message is what was written, byte for byte */
static void equal_circuit_assurance_message(const CircuitAssuranceMessage *read, const CircuitAssuranceMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
}

/* Circuit Assurance Message: written and read back, then read and written back */
static void check_circuit_assurance_message(void) {
  CircuitAssuranceMessage sent;
  CircuitAssuranceMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_circuit_assurance_message(&sent);
  assert(encode_circuit_assurance_message(&sent, wire, 0) == 6);
  assert(decode_circuit_assurance_message(&got, wire, 0) == 6);
  equal_circuit_assurance_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_circuit_assurance_message(&got, wire, 0) == 6);
  assert(encode_circuit_assurance_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Timestamp Message: 9 bytes --------------------------------------- */

/* This message is sent out every second and contains the time stamp when it was originally transmitted by the trading engine */
typedef struct {
  uint8_t trading_engine_timestamp[9];  /* bytes 0 to 8 */
} SystemTimestampMessage;

/* any System Timestamp Message at all: every byte one the checker chooses */
static void any_system_timestamp_message(SystemTimestampMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->trading_engine_timestamp[i] = arbitrary(); }
}

/* System Timestamp Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_system_timestamp_message(const SystemTimestampMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->trading_engine_timestamp[i]; }

  return at;
}

/* System Timestamp Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_system_timestamp_message(SystemTimestampMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->trading_engine_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of System Timestamp Message is what was written, byte for byte */
static void equal_system_timestamp_message(const SystemTimestampMessage *read, const SystemTimestampMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->trading_engine_timestamp[i] == written->trading_engine_timestamp[i]); }
}

/* System Timestamp Message: written and read back, then read and written back */
static void check_system_timestamp_message(void) {
  SystemTimestampMessage sent;
  SystemTimestampMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_system_timestamp_message(&sent);
  assert(encode_system_timestamp_message(&sent, wire, 0) == 9);
  assert(decode_system_timestamp_message(&got, wire, 0) == 9);
  equal_system_timestamp_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_system_timestamp_message(&got, wire, 0) == 9);
  assert(encode_system_timestamp_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Description: 20 bytes ---------------------------------------- */

typedef struct {
  uint8_t root_symbol[6];                   /* bytes 0 to 5 */
  uint8_t expiry_month_code;                /* byte 6 */
  uint8_t filler_1;                         /* byte 7 */
  uint8_t strike_price[7];                  /* bytes 8 to 14 */
  uint8_t strike_price_fraction_indicator;  /* byte 15 */
  uint8_t expiry_year[2];                   /* bytes 16 to 17 */
  uint8_t expiry_day[2];                    /* bytes 18 to 19 */
} InstrumentDescription;

/* any Instrument Description at all: every byte one the checker chooses */
static void any_instrument_description(InstrumentDescription *record) {
  for (size_t i = 0; i < 6; i++) { record->root_symbol[i] = arbitrary(); }
  record->expiry_month_code = arbitrary();
  record->filler_1 = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->strike_price[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->expiry_year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expiry_day[i] = arbitrary(); }
}

/* Instrument Description to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_instrument_description(const InstrumentDescription *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->root_symbol[i]; }
  wire[at++] = record->expiry_month_code;
  wire[at++] = record->filler_1;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->strike_price_fraction_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiry_year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiry_day[i]; }

  return at;
}

/* Instrument Description off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_instrument_description(InstrumentDescription *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->root_symbol[i] = wire[at++]; }
  record->expiry_month_code = wire[at++];
  record->filler_1 = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->strike_price[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->expiry_year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expiry_day[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Description is what was written, byte for byte */
static void equal_instrument_description(const InstrumentDescription *read, const InstrumentDescription *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->root_symbol[i] == written->root_symbol[i]); }
  assert(read->expiry_month_code == written->expiry_month_code);
  assert(read->filler_1 == written->filler_1);
  for (size_t i = 0; i < 7; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->expiry_year[i] == written->expiry_year[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expiry_day[i] == written->expiry_day[i]); }
}

/* Instrument Description: written and read back, then read and written back */
static void check_instrument_description(void) {
  InstrumentDescription sent;
  InstrumentDescription got;
  uint8_t wire[20];
  uint8_t again[20];

  any_instrument_description(&sent);
  assert(encode_instrument_description(&sent, wire, 0) == 20);
  assert(decode_instrument_description(&got, wire, 0) == 20);
  equal_instrument_description(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_description(&got, wire, 0) == 20);
  assert(encode_instrument_description(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Opening Time Message: 14 bytes ------------------------------------ */

/* Group Opening Time */
typedef struct {
  uint8_t exchange_id;        /* byte 0 */
  uint8_t root_symbol[6];     /* bytes 1 to 6 */
  uint8_t group_status;       /* byte 7 */
  uint8_t scheduled_time[6];  /* bytes 8 to 13 */
} GroupOpeningTimeMessage;

/* any Group Opening Time Message at all: every byte one the checker chooses */
static void any_group_opening_time_message(GroupOpeningTimeMessage *record) {
  record->exchange_id = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->root_symbol[i] = arbitrary(); }
  record->group_status = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->scheduled_time[i] = arbitrary(); }
}

/* Group Opening Time Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_group_opening_time_message(const GroupOpeningTimeMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->exchange_id;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->root_symbol[i]; }
  wire[at++] = record->group_status;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->scheduled_time[i]; }

  return at;
}

/* Group Opening Time Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_group_opening_time_message(GroupOpeningTimeMessage *record, const uint8_t *wire, size_t at) {
  record->exchange_id = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->root_symbol[i] = wire[at++]; }
  record->group_status = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->scheduled_time[i] = wire[at++]; }

  return at;
}

/* what was read of Group Opening Time Message is what was written, byte for byte */
static void equal_group_opening_time_message(const GroupOpeningTimeMessage *read, const GroupOpeningTimeMessage *written) {
  assert(read->exchange_id == written->exchange_id);
  for (size_t i = 0; i < 6; i++) { assert(read->root_symbol[i] == written->root_symbol[i]); }
  assert(read->group_status == written->group_status);
  for (size_t i = 0; i < 6; i++) { assert(read->scheduled_time[i] == written->scheduled_time[i]); }
}

/* Group Opening Time Message: written and read back, then read and written back */
static void check_group_opening_time_message(void) {
  GroupOpeningTimeMessage sent;
  GroupOpeningTimeMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_group_opening_time_message(&sent);
  assert(encode_group_opening_time_message(&sent, wire, 0) == 14);
  assert(decode_group_opening_time_message(&got, wire, 0) == 14);
  equal_group_opening_time_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_group_opening_time_message(&got, wire, 0) == 14);
  assert(encode_group_opening_time_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Status Message: 8 bytes ------------------------------------------- */

/* This message will be sent when a group of trading instruments enters a new status */
typedef struct {
  uint8_t exchange_id;     /* byte 0 */
  uint8_t root_symbol[6];  /* bytes 1 to 6 */
  uint8_t group_status;    /* byte 7 */
} GroupStatusMessage;

/* any Group Status Message at all: every byte one the checker chooses */
static void any_group_status_message(GroupStatusMessage *record) {
  record->exchange_id = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->root_symbol[i] = arbitrary(); }
  record->group_status = arbitrary();
}

/* Group Status Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_group_status_message(const GroupStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->exchange_id;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->root_symbol[i]; }
  wire[at++] = record->group_status;

  return at;
}

/* Group Status Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_group_status_message(GroupStatusMessage *record, const uint8_t *wire, size_t at) {
  record->exchange_id = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->root_symbol[i] = wire[at++]; }
  record->group_status = wire[at++];

  return at;
}

/* what was read of Group Status Message is what was written, byte for byte */
static void equal_group_status_message(const GroupStatusMessage *read, const GroupStatusMessage *written) {
  assert(read->exchange_id == written->exchange_id);
  for (size_t i = 0; i < 6; i++) { assert(read->root_symbol[i] == written->root_symbol[i]); }
  assert(read->group_status == written->group_status);
}

/* Group Status Message: written and read back, then read and written back */
static void check_group_status_message(void) {
  GroupStatusMessage sent;
  GroupStatusMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_group_status_message(&sent);
  assert(encode_group_status_message(&sent, wire, 0) == 8);
  assert(decode_group_status_message(&got, wire, 0) == 8);
  equal_group_status_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_group_status_message(&got, wire, 0) == 8);
  assert(encode_group_status_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strategies Group Status Message: 4 bytes -------------------------------- */

/* This message will be sent when a group of complex trading instruments enters a new status */
typedef struct {
  uint8_t exchange_id;                               /* byte 0 */
  uint8_t group_of_the_complex_order_instrument[2];  /* bytes 1 to 2 */
  uint8_t group_status;                              /* byte 3 */
} StrategiesGroupStatusMessage;

/* any Strategies Group Status Message at all: every byte one the checker chooses */
static void any_strategies_group_status_message(StrategiesGroupStatusMessage *record) {
  record->exchange_id = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->group_of_the_complex_order_instrument[i] = arbitrary(); }
  record->group_status = arbitrary();
}

/* Strategies Group Status Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_strategies_group_status_message(const StrategiesGroupStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->exchange_id;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group_of_the_complex_order_instrument[i]; }
  wire[at++] = record->group_status;

  return at;
}

/* Strategies Group Status Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_strategies_group_status_message(StrategiesGroupStatusMessage *record, const uint8_t *wire, size_t at) {
  record->exchange_id = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->group_of_the_complex_order_instrument[i] = wire[at++]; }
  record->group_status = wire[at++];

  return at;
}

/* what was read of Strategies Group Status Message is what was written, byte for byte */
static void equal_strategies_group_status_message(const StrategiesGroupStatusMessage *read, const StrategiesGroupStatusMessage *written) {
  assert(read->exchange_id == written->exchange_id);
  for (size_t i = 0; i < 2; i++) { assert(read->group_of_the_complex_order_instrument[i] == written->group_of_the_complex_order_instrument[i]); }
  assert(read->group_status == written->group_status);
}

/* Strategies Group Status Message: written and read back, then read and written back */
static void check_strategies_group_status_message(void) {
  StrategiesGroupStatusMessage sent;
  StrategiesGroupStatusMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_strategies_group_status_message(&sent);
  assert(encode_strategies_group_status_message(&sent, wire, 0) == 4);
  assert(decode_strategies_group_status_message(&got, wire, 0) == 4);
  equal_strategies_group_status_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_strategies_group_status_message(&got, wire, 0) == 4);
  assert(encode_strategies_group_status_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Flow Indicator: 2 bytes ------------------------------------------ */

typedef struct {
  uint8_t type_of_instrument;  /* byte 0 */
  uint8_t type_of_underlying;  /* byte 1 */
} MarketFlowIndicator;

/* any Market Flow Indicator at all: every byte one the checker chooses */
static void any_market_flow_indicator(MarketFlowIndicator *record) {
  record->type_of_instrument = arbitrary();
  record->type_of_underlying = arbitrary();
}

/* Market Flow Indicator to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_market_flow_indicator(const MarketFlowIndicator *record, uint8_t *wire, size_t at) {
  wire[at++] = record->type_of_instrument;
  wire[at++] = record->type_of_underlying;

  return at;
}

/* Market Flow Indicator off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_market_flow_indicator(MarketFlowIndicator *record, const uint8_t *wire, size_t at) {
  record->type_of_instrument = wire[at++];
  record->type_of_underlying = wire[at++];

  return at;
}

/* what was read of Market Flow Indicator is what was written, byte for byte */
static void equal_market_flow_indicator(const MarketFlowIndicator *read, const MarketFlowIndicator *written) {
  assert(read->type_of_instrument == written->type_of_instrument);
  assert(read->type_of_underlying == written->type_of_underlying);
}

/* Market Flow Indicator: written and read back, then read and written back */
static void check_market_flow_indicator(void) {
  MarketFlowIndicator sent;
  MarketFlowIndicator got;
  uint8_t wire[2];
  uint8_t again[2];

  any_market_flow_indicator(&sent);
  assert(encode_market_flow_indicator(&sent, wire, 0) == 2);
  assert(decode_market_flow_indicator(&got, wire, 0) == 2);
  equal_market_flow_indicator(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_market_flow_indicator(&got, wire, 0) == 2);
  assert(encode_market_flow_indicator(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Option Marker: 2 bytes -------------------------------------------------- */

typedef struct {
  uint8_t type_of_market;   /* byte 0 */
  uint8_t type_of_options;  /* byte 1 */
} OptionMarker;

/* any Option Marker at all: every byte one the checker chooses */
static void any_option_marker(OptionMarker *record) {
  record->type_of_market = arbitrary();
  record->type_of_options = arbitrary();
}

/* Option Marker to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_option_marker(const OptionMarker *record, uint8_t *wire, size_t at) {
  wire[at++] = record->type_of_market;
  wire[at++] = record->type_of_options;

  return at;
}

/* Option Marker off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_option_marker(OptionMarker *record, const uint8_t *wire, size_t at) {
  record->type_of_market = wire[at++];
  record->type_of_options = wire[at++];

  return at;
}

/* what was read of Option Marker is what was written, byte for byte */
static void equal_option_marker(const OptionMarker *read, const OptionMarker *written) {
  assert(read->type_of_market == written->type_of_market);
  assert(read->type_of_options == written->type_of_options);
}

/* Option Marker: written and read back, then read and written back */
static void check_option_marker(void) {
  OptionMarker sent;
  OptionMarker got;
  uint8_t wire[2];
  uint8_t again[2];

  any_option_marker(&sent);
  assert(encode_option_marker(&sent, wire, 0) == 2);
  assert(decode_option_marker(&got, wire, 0) == 2);
  equal_option_marker(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_option_marker(&got, wire, 0) == 2);
  assert(encode_option_marker(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Option Instrument Keys Message: 108 bytes ------------------------------- */

/* Option Instrument Keys */
typedef struct {
  uint8_t exchange_id;                                 /* byte 0 */
  InstrumentDescription instrument_description;        /* bytes 1 to 20 */
  uint8_t strike_price_currency[3];                    /* bytes 21 to 23 */
  uint8_t maximum_number_of_contracts_per_order[6];    /* bytes 24 to 29 */
  uint8_t minimum_number_of_contracts_per_order[6];    /* bytes 30 to 35 */
  uint8_t maximum_threshold_price[6];                  /* bytes 36 to 41 */
  uint8_t maximum_threshold_price_fraction_indicator;  /* byte 42 */
  uint8_t minimum_threshold_price[6];                  /* bytes 43 to 48 */
  uint8_t minimum_threshold_price_fraction_indicator;  /* byte 49 */
  uint8_t tick_increment[6];                           /* bytes 50 to 55 */
  uint8_t tick_increment_fraction_indicator;           /* byte 56 */
  uint8_t option_type;                                 /* byte 57 */
  MarketFlowIndicator market_flow_indicator;           /* bytes 58 to 59 */
  uint8_t group_instrument[2];                         /* bytes 60 to 61 */
  uint8_t instrument[4];                               /* bytes 62 to 65 */
  uint8_t instrument_external_code[30];                /* bytes 66 to 95 */
  OptionMarker option_marker;                          /* bytes 96 to 97 */
  uint8_t underlying_symbol_root[10];                  /* bytes 98 to 107 */
} OptionInstrumentKeysMessage;

/* any Option Instrument Keys Message at all: every byte one the checker chooses */
static void any_option_instrument_keys_message(OptionInstrumentKeysMessage *record) {
  record->exchange_id = arbitrary();
  any_instrument_description(&record->instrument_description);
  for (size_t i = 0; i < 3; i++) { record->strike_price_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->maximum_number_of_contracts_per_order[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->minimum_number_of_contracts_per_order[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->maximum_threshold_price[i] = arbitrary(); }
  record->maximum_threshold_price_fraction_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->minimum_threshold_price[i] = arbitrary(); }
  record->minimum_threshold_price_fraction_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->tick_increment[i] = arbitrary(); }
  record->tick_increment_fraction_indicator = arbitrary();
  record->option_type = arbitrary();
  any_market_flow_indicator(&record->market_flow_indicator);
  for (size_t i = 0; i < 2; i++) { record->group_instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->instrument_external_code[i] = arbitrary(); }
  any_option_marker(&record->option_marker);
  for (size_t i = 0; i < 10; i++) { record->underlying_symbol_root[i] = arbitrary(); }
}

/* Option Instrument Keys Message to the wire: 108 bytes from at, returning where the next byte goes */
static size_t encode_option_instrument_keys_message(const OptionInstrumentKeysMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->exchange_id;
  at = encode_instrument_description(&record->instrument_description, wire, at);
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->strike_price_currency[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->maximum_number_of_contracts_per_order[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->minimum_number_of_contracts_per_order[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->maximum_threshold_price[i]; }
  wire[at++] = record->maximum_threshold_price_fraction_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->minimum_threshold_price[i]; }
  wire[at++] = record->minimum_threshold_price_fraction_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->tick_increment[i]; }
  wire[at++] = record->tick_increment_fraction_indicator;
  wire[at++] = record->option_type;
  at = encode_market_flow_indicator(&record->market_flow_indicator, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group_instrument[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->instrument_external_code[i]; }
  at = encode_option_marker(&record->option_marker, wire, at);
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->underlying_symbol_root[i]; }

  return at;
}

/* Option Instrument Keys Message off the wire: 108 bytes from at, returning where the next byte lies */
static size_t decode_option_instrument_keys_message(OptionInstrumentKeysMessage *record, const uint8_t *wire, size_t at) {
  record->exchange_id = wire[at++];
  at = decode_instrument_description(&record->instrument_description, wire, at);
  for (size_t i = 0; i < 3; i++) { record->strike_price_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->maximum_number_of_contracts_per_order[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->minimum_number_of_contracts_per_order[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->maximum_threshold_price[i] = wire[at++]; }
  record->maximum_threshold_price_fraction_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->minimum_threshold_price[i] = wire[at++]; }
  record->minimum_threshold_price_fraction_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->tick_increment[i] = wire[at++]; }
  record->tick_increment_fraction_indicator = wire[at++];
  record->option_type = wire[at++];
  at = decode_market_flow_indicator(&record->market_flow_indicator, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group_instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->instrument_external_code[i] = wire[at++]; }
  at = decode_option_marker(&record->option_marker, wire, at);
  for (size_t i = 0; i < 10; i++) { record->underlying_symbol_root[i] = wire[at++]; }

  return at;
}

/* what was read of Option Instrument Keys Message is what was written, byte for byte */
static void equal_option_instrument_keys_message(const OptionInstrumentKeysMessage *read, const OptionInstrumentKeysMessage *written) {
  assert(read->exchange_id == written->exchange_id);
  equal_instrument_description(&read->instrument_description, &written->instrument_description);
  for (size_t i = 0; i < 3; i++) { assert(read->strike_price_currency[i] == written->strike_price_currency[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->maximum_number_of_contracts_per_order[i] == written->maximum_number_of_contracts_per_order[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->minimum_number_of_contracts_per_order[i] == written->minimum_number_of_contracts_per_order[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->maximum_threshold_price[i] == written->maximum_threshold_price[i]); }
  assert(read->maximum_threshold_price_fraction_indicator == written->maximum_threshold_price_fraction_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->minimum_threshold_price[i] == written->minimum_threshold_price[i]); }
  assert(read->minimum_threshold_price_fraction_indicator == written->minimum_threshold_price_fraction_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->tick_increment[i] == written->tick_increment[i]); }
  assert(read->tick_increment_fraction_indicator == written->tick_increment_fraction_indicator);
  assert(read->option_type == written->option_type);
  equal_market_flow_indicator(&read->market_flow_indicator, &written->market_flow_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->group_instrument[i] == written->group_instrument[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->instrument_external_code[i] == written->instrument_external_code[i]); }
  equal_option_marker(&read->option_marker, &written->option_marker);
  for (size_t i = 0; i < 10; i++) { assert(read->underlying_symbol_root[i] == written->underlying_symbol_root[i]); }
}

/* Option Instrument Keys Message: written and read back, then read and written back */
static void check_option_instrument_keys_message(void) {
  OptionInstrumentKeysMessage sent;
  OptionInstrumentKeysMessage got;
  uint8_t wire[108];
  uint8_t again[108];

  any_option_instrument_keys_message(&sent);
  assert(encode_option_instrument_keys_message(&sent, wire, 0) == 108);
  assert(decode_option_instrument_keys_message(&got, wire, 0) == 108);
  equal_option_instrument_keys_message(&got, &sent);

  for (size_t i = 0; i < 108; i++) { wire[i] = arbitrary(); }
  assert(decode_option_instrument_keys_message(&got, wire, 0) == 108);
  assert(encode_option_instrument_keys_message(&got, again, 0) == 108);
  for (size_t i = 0; i < 108; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bulletins Message: 82 bytes --------------------------------------------- */

/* When a Trading instrument has been halted by BOX, a Bulletin Message explaining the reason for the halt will be transmitted. */
typedef struct {
  uint8_t filler_1;               /* byte 0 */
  uint8_t bulletin_type;          /* byte 1 */
  uint8_t bulletin_contents[79];  /* bytes 2 to 80 */
  uint8_t continue_marker;        /* byte 81 */
} BulletinsMessage;

/* any Bulletins Message at all: every byte one the checker chooses */
static void any_bulletins_message(BulletinsMessage *record) {
  record->filler_1 = arbitrary();
  record->bulletin_type = arbitrary();
  for (size_t i = 0; i < 79; i++) { record->bulletin_contents[i] = arbitrary(); }
  record->continue_marker = arbitrary();
}

/* Bulletins Message to the wire: 82 bytes from at, returning where the next byte goes */
static size_t encode_bulletins_message(const BulletinsMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->filler_1;
  wire[at++] = record->bulletin_type;
  for (size_t i = 0; i < 79; i++) { wire[at++] = record->bulletin_contents[i]; }
  wire[at++] = record->continue_marker;

  return at;
}

/* Bulletins Message off the wire: 82 bytes from at, returning where the next byte lies */
static size_t decode_bulletins_message(BulletinsMessage *record, const uint8_t *wire, size_t at) {
  record->filler_1 = wire[at++];
  record->bulletin_type = wire[at++];
  for (size_t i = 0; i < 79; i++) { record->bulletin_contents[i] = wire[at++]; }
  record->continue_marker = wire[at++];

  return at;
}

/* what was read of Bulletins Message is what was written, byte for byte */
static void equal_bulletins_message(const BulletinsMessage *read, const BulletinsMessage *written) {
  assert(read->filler_1 == written->filler_1);
  assert(read->bulletin_type == written->bulletin_type);
  for (size_t i = 0; i < 79; i++) { assert(read->bulletin_contents[i] == written->bulletin_contents[i]); }
  assert(read->continue_marker == written->continue_marker);
}

/* Bulletins Message: written and read back, then read and written back */
static void check_bulletins_message(void) {
  BulletinsMessage sent;
  BulletinsMessage got;
  uint8_t wire[82];
  uint8_t again[82];

  any_bulletins_message(&sent);
  assert(encode_bulletins_message(&sent, wire, 0) == 82);
  assert(decode_bulletins_message(&got, wire, 0) == 82);
  equal_bulletins_message(&got, &sent);

  for (size_t i = 0; i < 82; i++) { wire[i] = arbitrary(); }
  assert(decode_bulletins_message(&got, wire, 0) == 82);
  assert(encode_bulletins_message(&got, again, 0) == 82);
  for (size_t i = 0; i < 82; i++) { assert(again[i] == wire[i]); }
}

/* ---- Beginning Of Options Summary Message: 1 byte ---------------------------- */

/* This message indicates that the beginning and the end of day option summaries */
typedef struct {
  uint8_t exchange_id;  /* byte 0 */
} BeginningOfOptionsSummaryMessage;

/* any Beginning Of Options Summary Message at all: every byte one the checker chooses */
static void any_beginning_of_options_summary_message(BeginningOfOptionsSummaryMessage *record) {
  record->exchange_id = arbitrary();
}

/* Beginning Of Options Summary Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_beginning_of_options_summary_message(const BeginningOfOptionsSummaryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->exchange_id;

  return at;
}

/* Beginning Of Options Summary Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_beginning_of_options_summary_message(BeginningOfOptionsSummaryMessage *record, const uint8_t *wire, size_t at) {
  record->exchange_id = wire[at++];

  return at;
}

/* what was read of Beginning Of Options Summary Message is what was written, byte for byte */
static void equal_beginning_of_options_summary_message(const BeginningOfOptionsSummaryMessage *read, const BeginningOfOptionsSummaryMessage *written) {
  assert(read->exchange_id == written->exchange_id);
}

/* Beginning Of Options Summary Message: written and read back, then read and written back */
static void check_beginning_of_options_summary_message(void) {
  BeginningOfOptionsSummaryMessage sent;
  BeginningOfOptionsSummaryMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_beginning_of_options_summary_message(&sent);
  assert(encode_beginning_of_options_summary_message(&sent, wire, 0) == 1);
  assert(decode_beginning_of_options_summary_message(&got, wire, 0) == 1);
  equal_beginning_of_options_summary_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_beginning_of_options_summary_message(&got, wire, 0) == 1);
  assert(encode_beginning_of_options_summary_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Beginning Of Complex Order Summary Message: 1 byte ---------------------- */

/* This message indicates that the beginning and the end of day Complex Order summaries */
typedef struct {
  uint8_t exchange_id;  /* byte 0 */
} BeginningOfComplexOrderSummaryMessage;

/* any Beginning Of Complex Order Summary Message at all: every byte one the checker chooses */
static void any_beginning_of_complex_order_summary_message(BeginningOfComplexOrderSummaryMessage *record) {
  record->exchange_id = arbitrary();
}

/* Beginning Of Complex Order Summary Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_beginning_of_complex_order_summary_message(const BeginningOfComplexOrderSummaryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->exchange_id;

  return at;
}

/* Beginning Of Complex Order Summary Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_beginning_of_complex_order_summary_message(BeginningOfComplexOrderSummaryMessage *record, const uint8_t *wire, size_t at) {
  record->exchange_id = wire[at++];

  return at;
}

/* what was read of Beginning Of Complex Order Summary Message is what was written, byte for byte */
static void equal_beginning_of_complex_order_summary_message(const BeginningOfComplexOrderSummaryMessage *read, const BeginningOfComplexOrderSummaryMessage *written) {
  assert(read->exchange_id == written->exchange_id);
}

/* Beginning Of Complex Order Summary Message: written and read back, then read and written back */
static void check_beginning_of_complex_order_summary_message(void) {
  BeginningOfComplexOrderSummaryMessage sent;
  BeginningOfComplexOrderSummaryMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_beginning_of_complex_order_summary_message(&sent);
  assert(encode_beginning_of_complex_order_summary_message(&sent, wire, 0) == 1);
  assert(decode_beginning_of_complex_order_summary_message(&got, wire, 0) == 1);
  equal_beginning_of_complex_order_summary_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_beginning_of_complex_order_summary_message(&got, wire, 0) == 1);
  assert(encode_beginning_of_complex_order_summary_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Sales Message: 7 bytes ------------------------------------------- */

/* This message is sent when there is no more trading activity to be transmitted */
typedef struct {
  uint8_t reserved;  /* byte 0 */
  uint8_t time[6];   /* bytes 1 to 6 */
} EndOfSalesMessage;

/* any End Of Sales Message at all: every byte one the checker chooses */
static void any_end_of_sales_message(EndOfSalesMessage *record) {
  record->reserved = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
}

/* End Of Sales Message to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_end_of_sales_message(const EndOfSalesMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reserved;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }

  return at;
}

/* End Of Sales Message off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_end_of_sales_message(EndOfSalesMessage *record, const uint8_t *wire, size_t at) {
  record->reserved = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Sales Message is what was written, byte for byte */
static void equal_end_of_sales_message(const EndOfSalesMessage *read, const EndOfSalesMessage *written) {
  assert(read->reserved == written->reserved);
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
}

/* End Of Sales Message: written and read back, then read and written back */
static void check_end_of_sales_message(void) {
  EndOfSalesMessage sent;
  EndOfSalesMessage got;
  uint8_t wire[7];
  uint8_t again[7];

  any_end_of_sales_message(&sent);
  assert(encode_end_of_sales_message(&sent, wire, 0) == 7);
  assert(decode_end_of_sales_message(&got, wire, 0) == 7);
  equal_end_of_sales_message(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_sales_message(&got, wire, 0) == 7);
  assert(encode_end_of_sales_message(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Option Improvement Process Beginning Message: 73 bytes ------------------ */

/* Start of Option Improvement Process */
typedef struct {
  uint8_t exchange_id;                                /* byte 0 */
  InstrumentDescription instrument_description;       /* bytes 1 to 20 */
  uint8_t improvement_phase_sequential_number[6];     /* bytes 21 to 26 */
  uint8_t initial_order_price[6];                     /* bytes 27 to 32 */
  uint8_t initial_order_price_fraction_indicator;     /* byte 33 */
  uint8_t initial_order_quantity[8];                  /* bytes 34 to 41 */
  uint8_t initial_order_side;                         /* byte 42 */
  uint8_t improvement_phase_expiry_time[8];           /* bytes 43 to 50 */
  uint8_t improvement_process_expiry_duration[4];     /* bytes 51 to 54 */
  uint8_t minimum_quantity_for_improvement_order[8];  /* bytes 55 to 62 */
  uint8_t percentage_assured_to_initial_order[8];     /* bytes 63 to 70 */
  uint8_t auction_type;                               /* byte 71 */
  uint8_t filler_1;                                   /* byte 72 */
} OptionImprovementProcessBeginningMessage;

/* any Option Improvement Process Beginning Message at all: every byte one the checker chooses */
static void any_option_improvement_process_beginning_message(OptionImprovementProcessBeginningMessage *record) {
  record->exchange_id = arbitrary();
  any_instrument_description(&record->instrument_description);
  for (size_t i = 0; i < 6; i++) { record->improvement_phase_sequential_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->initial_order_price[i] = arbitrary(); }
  record->initial_order_price_fraction_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->initial_order_quantity[i] = arbitrary(); }
  record->initial_order_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->improvement_phase_expiry_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->improvement_process_expiry_duration[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_quantity_for_improvement_order[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->percentage_assured_to_initial_order[i] = arbitrary(); }
  record->auction_type = arbitrary();
  record->filler_1 = arbitrary();
}

/* Option Improvement Process Beginning Message to the wire: 73 bytes from at, returning where the next byte goes */
static size_t encode_option_improvement_process_beginning_message(const OptionImprovementProcessBeginningMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->exchange_id;
  at = encode_instrument_description(&record->instrument_description, wire, at);
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->improvement_phase_sequential_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->initial_order_price[i]; }
  wire[at++] = record->initial_order_price_fraction_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->initial_order_quantity[i]; }
  wire[at++] = record->initial_order_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->improvement_phase_expiry_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->improvement_process_expiry_duration[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_quantity_for_improvement_order[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->percentage_assured_to_initial_order[i]; }
  wire[at++] = record->auction_type;
  wire[at++] = record->filler_1;

  return at;
}

/* Option Improvement Process Beginning Message off the wire: 73 bytes from at, returning where the next byte lies */
static size_t decode_option_improvement_process_beginning_message(OptionImprovementProcessBeginningMessage *record, const uint8_t *wire, size_t at) {
  record->exchange_id = wire[at++];
  at = decode_instrument_description(&record->instrument_description, wire, at);
  for (size_t i = 0; i < 6; i++) { record->improvement_phase_sequential_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->initial_order_price[i] = wire[at++]; }
  record->initial_order_price_fraction_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->initial_order_quantity[i] = wire[at++]; }
  record->initial_order_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->improvement_phase_expiry_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->improvement_process_expiry_duration[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_quantity_for_improvement_order[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->percentage_assured_to_initial_order[i] = wire[at++]; }
  record->auction_type = wire[at++];
  record->filler_1 = wire[at++];

  return at;
}

/* what was read of Option Improvement Process Beginning Message is what was written, byte for byte */
static void equal_option_improvement_process_beginning_message(const OptionImprovementProcessBeginningMessage *read, const OptionImprovementProcessBeginningMessage *written) {
  assert(read->exchange_id == written->exchange_id);
  equal_instrument_description(&read->instrument_description, &written->instrument_description);
  for (size_t i = 0; i < 6; i++) { assert(read->improvement_phase_sequential_number[i] == written->improvement_phase_sequential_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->initial_order_price[i] == written->initial_order_price[i]); }
  assert(read->initial_order_price_fraction_indicator == written->initial_order_price_fraction_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->initial_order_quantity[i] == written->initial_order_quantity[i]); }
  assert(read->initial_order_side == written->initial_order_side);
  for (size_t i = 0; i < 8; i++) { assert(read->improvement_phase_expiry_time[i] == written->improvement_phase_expiry_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->improvement_process_expiry_duration[i] == written->improvement_process_expiry_duration[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_quantity_for_improvement_order[i] == written->minimum_quantity_for_improvement_order[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->percentage_assured_to_initial_order[i] == written->percentage_assured_to_initial_order[i]); }
  assert(read->auction_type == written->auction_type);
  assert(read->filler_1 == written->filler_1);
}

/* Option Improvement Process Beginning Message: written and read back, then read and written back */
static void check_option_improvement_process_beginning_message(void) {
  OptionImprovementProcessBeginningMessage sent;
  OptionImprovementProcessBeginningMessage got;
  uint8_t wire[73];
  uint8_t again[73];

  any_option_improvement_process_beginning_message(&sent);
  assert(encode_option_improvement_process_beginning_message(&sent, wire, 0) == 73);
  assert(decode_option_improvement_process_beginning_message(&got, wire, 0) == 73);
  equal_option_improvement_process_beginning_message(&got, &sent);

  for (size_t i = 0; i < 73; i++) { wire[i] = arbitrary(); }
  assert(decode_option_improvement_process_beginning_message(&got, wire, 0) == 73);
  assert(encode_option_improvement_process_beginning_message(&got, again, 0) == 73);
  for (size_t i = 0; i < 73; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Order Improvement Process Beginning Message Message: 83 bytes ---- */

/* Complex Order Improvement Process Beginning Message */
typedef struct {
  uint8_t exchange_id;                                /* byte 0 */
  uint8_t complex_order_instrument_symbol[30];        /* bytes 1 to 30 */
  uint8_t improvement_phase_sequential_number[6];     /* bytes 31 to 36 */
  uint8_t initial_order_price_sign;                   /* byte 37 */
  uint8_t initial_order_price[6];                     /* bytes 38 to 43 */
  uint8_t initial_order_price_fraction_indicator;     /* byte 44 */
  uint8_t initial_order_quantity[8];                  /* bytes 45 to 52 */
  uint8_t initial_order_side;                         /* byte 53 */
  uint8_t improvement_phase_expiry_time[8];           /* bytes 54 to 61 */
  uint8_t improvement_process_expiry_duration[4];     /* bytes 62 to 65 */
  uint8_t minimum_quantity_for_improvement_order[8];  /* bytes 66 to 73 */
  uint8_t percentage_assured_to_initial_order[8];     /* bytes 74 to 81 */
  uint8_t auction_type;                               /* byte 82 */
} ComplexOrderImprovementProcessBeginningMessageMessage;

/* any Complex Order Improvement Process Beginning Message Message at all: every byte one the checker chooses */
static void any_complex_order_improvement_process_beginning_message_message(ComplexOrderImprovementProcessBeginningMessageMessage *record) {
  record->exchange_id = arbitrary();
  for (size_t i = 0; i < 30; i++) { record->complex_order_instrument_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->improvement_phase_sequential_number[i] = arbitrary(); }
  record->initial_order_price_sign = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->initial_order_price[i] = arbitrary(); }
  record->initial_order_price_fraction_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->initial_order_quantity[i] = arbitrary(); }
  record->initial_order_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->improvement_phase_expiry_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->improvement_process_expiry_duration[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_quantity_for_improvement_order[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->percentage_assured_to_initial_order[i] = arbitrary(); }
  record->auction_type = arbitrary();
}

/* Complex Order Improvement Process Beginning Message Message to the wire: 83 bytes from at, returning where the next byte goes */
static size_t encode_complex_order_improvement_process_beginning_message_message(const ComplexOrderImprovementProcessBeginningMessageMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->exchange_id;
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->complex_order_instrument_symbol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->improvement_phase_sequential_number[i]; }
  wire[at++] = record->initial_order_price_sign;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->initial_order_price[i]; }
  wire[at++] = record->initial_order_price_fraction_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->initial_order_quantity[i]; }
  wire[at++] = record->initial_order_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->improvement_phase_expiry_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->improvement_process_expiry_duration[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_quantity_for_improvement_order[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->percentage_assured_to_initial_order[i]; }
  wire[at++] = record->auction_type;

  return at;
}

/* Complex Order Improvement Process Beginning Message Message off the wire: 83 bytes from at, returning where the next byte lies */
static size_t decode_complex_order_improvement_process_beginning_message_message(ComplexOrderImprovementProcessBeginningMessageMessage *record, const uint8_t *wire, size_t at) {
  record->exchange_id = wire[at++];
  for (size_t i = 0; i < 30; i++) { record->complex_order_instrument_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->improvement_phase_sequential_number[i] = wire[at++]; }
  record->initial_order_price_sign = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->initial_order_price[i] = wire[at++]; }
  record->initial_order_price_fraction_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->initial_order_quantity[i] = wire[at++]; }
  record->initial_order_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->improvement_phase_expiry_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->improvement_process_expiry_duration[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_quantity_for_improvement_order[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->percentage_assured_to_initial_order[i] = wire[at++]; }
  record->auction_type = wire[at++];

  return at;
}

/* what was read of Complex Order Improvement Process Beginning Message Message is what was written, byte for byte */
static void equal_complex_order_improvement_process_beginning_message_message(const ComplexOrderImprovementProcessBeginningMessageMessage *read, const ComplexOrderImprovementProcessBeginningMessageMessage *written) {
  assert(read->exchange_id == written->exchange_id);
  for (size_t i = 0; i < 30; i++) { assert(read->complex_order_instrument_symbol[i] == written->complex_order_instrument_symbol[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->improvement_phase_sequential_number[i] == written->improvement_phase_sequential_number[i]); }
  assert(read->initial_order_price_sign == written->initial_order_price_sign);
  for (size_t i = 0; i < 6; i++) { assert(read->initial_order_price[i] == written->initial_order_price[i]); }
  assert(read->initial_order_price_fraction_indicator == written->initial_order_price_fraction_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->initial_order_quantity[i] == written->initial_order_quantity[i]); }
  assert(read->initial_order_side == written->initial_order_side);
  for (size_t i = 0; i < 8; i++) { assert(read->improvement_phase_expiry_time[i] == written->improvement_phase_expiry_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->improvement_process_expiry_duration[i] == written->improvement_process_expiry_duration[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_quantity_for_improvement_order[i] == written->minimum_quantity_for_improvement_order[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->percentage_assured_to_initial_order[i] == written->percentage_assured_to_initial_order[i]); }
  assert(read->auction_type == written->auction_type);
}

/* Complex Order Improvement Process Beginning Message Message: written and read back, then read and written back */
static void check_complex_order_improvement_process_beginning_message_message(void) {
  ComplexOrderImprovementProcessBeginningMessageMessage sent;
  ComplexOrderImprovementProcessBeginningMessageMessage got;
  uint8_t wire[83];
  uint8_t again[83];

  any_complex_order_improvement_process_beginning_message_message(&sent);
  assert(encode_complex_order_improvement_process_beginning_message_message(&sent, wire, 0) == 83);
  assert(decode_complex_order_improvement_process_beginning_message_message(&got, wire, 0) == 83);
  equal_complex_order_improvement_process_beginning_message_message(&got, &sent);

  for (size_t i = 0; i < 83; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_order_improvement_process_beginning_message_message(&got, wire, 0) == 83);
  assert(encode_complex_order_improvement_process_beginning_message_message(&got, again, 0) == 83);
  for (size_t i = 0; i < 83; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Sheet Initial And Improvement Order Message: 69 bytes ------------ */

/* Market Sheet Initial and Improvement Order */
typedef struct {
  uint8_t exchange_id;                             /* byte 0 */
  InstrumentDescription instrument_description;    /* bytes 1 to 20 */
  uint8_t order_side;                              /* byte 21 */
  uint8_t type_of_order;                           /* byte 22 */
  uint8_t limit_entered_for_an_order[6];           /* bytes 23 to 28 */
  uint8_t limit_fraction_indicator;                /* byte 29 */
  uint8_t order_quantity[8];                       /* bytes 30 to 37 */
  uint8_t order_sequence_number[6];                /* bytes 38 to 43 */
  uint8_t improvement_phase_sequential_number[6];  /* bytes 44 to 49 */
  uint8_t type_of_clearing_account;                /* byte 50 */
  uint8_t filler_1;                                /* byte 51 */
  uint8_t end_of_the_exposition[8];                /* bytes 52 to 59 */
  uint8_t auction_type;                            /* byte 60 */
  uint8_t firm_id[4];                              /* bytes 61 to 64 */
  uint8_t cmta[4];                                 /* bytes 65 to 68 */
} MarketSheetInitialAndImprovementOrderMessage;

/* any Market Sheet Initial And Improvement Order Message at all: every byte one the checker chooses */
static void any_market_sheet_initial_and_improvement_order_message(MarketSheetInitialAndImprovementOrderMessage *record) {
  record->exchange_id = arbitrary();
  any_instrument_description(&record->instrument_description);
  record->order_side = arbitrary();
  record->type_of_order = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->limit_entered_for_an_order[i] = arbitrary(); }
  record->limit_fraction_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->order_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->improvement_phase_sequential_number[i] = arbitrary(); }
  record->type_of_clearing_account = arbitrary();
  record->filler_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->end_of_the_exposition[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cmta[i] = arbitrary(); }
}

/* Market Sheet Initial And Improvement Order Message to the wire: 69 bytes from at, returning where the next byte goes */
static size_t encode_market_sheet_initial_and_improvement_order_message(const MarketSheetInitialAndImprovementOrderMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->exchange_id;
  at = encode_instrument_description(&record->instrument_description, wire, at);
  wire[at++] = record->order_side;
  wire[at++] = record->type_of_order;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->limit_entered_for_an_order[i]; }
  wire[at++] = record->limit_fraction_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_quantity[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->order_sequence_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->improvement_phase_sequential_number[i]; }
  wire[at++] = record->type_of_clearing_account;
  wire[at++] = record->filler_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_of_the_exposition[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta[i]; }

  return at;
}

/* Market Sheet Initial And Improvement Order Message off the wire: 69 bytes from at, returning where the next byte lies */
static size_t decode_market_sheet_initial_and_improvement_order_message(MarketSheetInitialAndImprovementOrderMessage *record, const uint8_t *wire, size_t at) {
  record->exchange_id = wire[at++];
  at = decode_instrument_description(&record->instrument_description, wire, at);
  record->order_side = wire[at++];
  record->type_of_order = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->limit_entered_for_an_order[i] = wire[at++]; }
  record->limit_fraction_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->order_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->improvement_phase_sequential_number[i] = wire[at++]; }
  record->type_of_clearing_account = wire[at++];
  record->filler_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->end_of_the_exposition[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cmta[i] = wire[at++]; }

  return at;
}

/* what was read of Market Sheet Initial And Improvement Order Message is what was written, byte for byte */
static void equal_market_sheet_initial_and_improvement_order_message(const MarketSheetInitialAndImprovementOrderMessage *read, const MarketSheetInitialAndImprovementOrderMessage *written) {
  assert(read->exchange_id == written->exchange_id);
  equal_instrument_description(&read->instrument_description, &written->instrument_description);
  assert(read->order_side == written->order_side);
  assert(read->type_of_order == written->type_of_order);
  for (size_t i = 0; i < 6; i++) { assert(read->limit_entered_for_an_order[i] == written->limit_entered_for_an_order[i]); }
  assert(read->limit_fraction_indicator == written->limit_fraction_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->order_quantity[i] == written->order_quantity[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->order_sequence_number[i] == written->order_sequence_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->improvement_phase_sequential_number[i] == written->improvement_phase_sequential_number[i]); }
  assert(read->type_of_clearing_account == written->type_of_clearing_account);
  assert(read->filler_1 == written->filler_1);
  for (size_t i = 0; i < 8; i++) { assert(read->end_of_the_exposition[i] == written->end_of_the_exposition[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cmta[i] == written->cmta[i]); }
}

/* Market Sheet Initial And Improvement Order Message: written and read back, then read and written back */
static void check_market_sheet_initial_and_improvement_order_message(void) {
  MarketSheetInitialAndImprovementOrderMessage sent;
  MarketSheetInitialAndImprovementOrderMessage got;
  uint8_t wire[69];
  uint8_t again[69];

  any_market_sheet_initial_and_improvement_order_message(&sent);
  assert(encode_market_sheet_initial_and_improvement_order_message(&sent, wire, 0) == 69);
  assert(decode_market_sheet_initial_and_improvement_order_message(&got, wire, 0) == 69);
  equal_market_sheet_initial_and_improvement_order_message(&got, &sent);

  for (size_t i = 0; i < 69; i++) { wire[i] = arbitrary(); }
  assert(decode_market_sheet_initial_and_improvement_order_message(&got, wire, 0) == 69);
  assert(encode_market_sheet_initial_and_improvement_order_message(&got, again, 0) == 69);
  for (size_t i = 0; i < 69; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Order Market Sheet Initial And Improvement Order Message: 80 bytes ---- */

/* Market Sheet Initial and Improvement Order (Complex Order) / Exposed Order (Complex Order) */
typedef struct {
  uint8_t exchange_id;                             /* byte 0 */
  uint8_t complex_order_instrument_symbol[30];     /* bytes 1 to 30 */
  uint8_t order_side;                              /* byte 31 */
  uint8_t type_of_order;                           /* byte 32 */
  uint8_t limit_entered_for_an_order_sign;         /* byte 33 */
  uint8_t limit_entered_for_an_order[6];           /* bytes 34 to 39 */
  uint8_t limit_fraction_indicator;                /* byte 40 */
  uint8_t order_quantity[8];                       /* bytes 41 to 48 */
  uint8_t order_sequence_number[6];                /* bytes 49 to 54 */
  uint8_t improvement_phase_sequential_number[6];  /* bytes 55 to 60 */
  uint8_t type_of_clearing_account;                /* byte 61 */
  uint8_t filler_1;                                /* byte 62 */
  uint8_t end_of_the_exposition[8];                /* bytes 63 to 70 */
  uint8_t auction_type;                            /* byte 71 */
  uint8_t firm_id[4];                              /* bytes 72 to 75 */
  uint8_t cmta[4];                                 /* bytes 76 to 79 */
} ComplexOrderMarketSheetInitialAndImprovementOrderMessage;

/* any Complex Order Market Sheet Initial And Improvement Order Message at all: every byte one the checker chooses */
static void any_complex_order_market_sheet_initial_and_improvement_order_message(ComplexOrderMarketSheetInitialAndImprovementOrderMessage *record) {
  record->exchange_id = arbitrary();
  for (size_t i = 0; i < 30; i++) { record->complex_order_instrument_symbol[i] = arbitrary(); }
  record->order_side = arbitrary();
  record->type_of_order = arbitrary();
  record->limit_entered_for_an_order_sign = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->limit_entered_for_an_order[i] = arbitrary(); }
  record->limit_fraction_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->order_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->improvement_phase_sequential_number[i] = arbitrary(); }
  record->type_of_clearing_account = arbitrary();
  record->filler_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->end_of_the_exposition[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cmta[i] = arbitrary(); }
}

/* Complex Order Market Sheet Initial And Improvement Order Message to the wire: 80 bytes from at, returning where the next byte goes */
static size_t encode_complex_order_market_sheet_initial_and_improvement_order_message(const ComplexOrderMarketSheetInitialAndImprovementOrderMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->exchange_id;
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->complex_order_instrument_symbol[i]; }
  wire[at++] = record->order_side;
  wire[at++] = record->type_of_order;
  wire[at++] = record->limit_entered_for_an_order_sign;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->limit_entered_for_an_order[i]; }
  wire[at++] = record->limit_fraction_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_quantity[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->order_sequence_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->improvement_phase_sequential_number[i]; }
  wire[at++] = record->type_of_clearing_account;
  wire[at++] = record->filler_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_of_the_exposition[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta[i]; }

  return at;
}

/* Complex Order Market Sheet Initial And Improvement Order Message off the wire: 80 bytes from at, returning where the next byte lies */
static size_t decode_complex_order_market_sheet_initial_and_improvement_order_message(ComplexOrderMarketSheetInitialAndImprovementOrderMessage *record, const uint8_t *wire, size_t at) {
  record->exchange_id = wire[at++];
  for (size_t i = 0; i < 30; i++) { record->complex_order_instrument_symbol[i] = wire[at++]; }
  record->order_side = wire[at++];
  record->type_of_order = wire[at++];
  record->limit_entered_for_an_order_sign = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->limit_entered_for_an_order[i] = wire[at++]; }
  record->limit_fraction_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->order_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->improvement_phase_sequential_number[i] = wire[at++]; }
  record->type_of_clearing_account = wire[at++];
  record->filler_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->end_of_the_exposition[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cmta[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Order Market Sheet Initial And Improvement Order Message is what was written, byte for byte */
static void equal_complex_order_market_sheet_initial_and_improvement_order_message(const ComplexOrderMarketSheetInitialAndImprovementOrderMessage *read, const ComplexOrderMarketSheetInitialAndImprovementOrderMessage *written) {
  assert(read->exchange_id == written->exchange_id);
  for (size_t i = 0; i < 30; i++) { assert(read->complex_order_instrument_symbol[i] == written->complex_order_instrument_symbol[i]); }
  assert(read->order_side == written->order_side);
  assert(read->type_of_order == written->type_of_order);
  assert(read->limit_entered_for_an_order_sign == written->limit_entered_for_an_order_sign);
  for (size_t i = 0; i < 6; i++) { assert(read->limit_entered_for_an_order[i] == written->limit_entered_for_an_order[i]); }
  assert(read->limit_fraction_indicator == written->limit_fraction_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->order_quantity[i] == written->order_quantity[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->order_sequence_number[i] == written->order_sequence_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->improvement_phase_sequential_number[i] == written->improvement_phase_sequential_number[i]); }
  assert(read->type_of_clearing_account == written->type_of_clearing_account);
  assert(read->filler_1 == written->filler_1);
  for (size_t i = 0; i < 8; i++) { assert(read->end_of_the_exposition[i] == written->end_of_the_exposition[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cmta[i] == written->cmta[i]); }
}

/* Complex Order Market Sheet Initial And Improvement Order Message: written and read back, then read and written back */
static void check_complex_order_market_sheet_initial_and_improvement_order_message(void) {
  ComplexOrderMarketSheetInitialAndImprovementOrderMessage sent;
  ComplexOrderMarketSheetInitialAndImprovementOrderMessage got;
  uint8_t wire[80];
  uint8_t again[80];

  any_complex_order_market_sheet_initial_and_improvement_order_message(&sent);
  assert(encode_complex_order_market_sheet_initial_and_improvement_order_message(&sent, wire, 0) == 80);
  assert(decode_complex_order_market_sheet_initial_and_improvement_order_message(&got, wire, 0) == 80);
  equal_complex_order_market_sheet_initial_and_improvement_order_message(&got, &sent);

  for (size_t i = 0; i < 80; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_order_market_sheet_initial_and_improvement_order_message(&got, wire, 0) == 80);
  assert(encode_complex_order_market_sheet_initial_and_improvement_order_message(&got, again, 0) == 80);
  for (size_t i = 0; i < 80; i++) { assert(again[i] == wire[i]); }
}

/* ---- Initial And Improvement Order Message: 36 bytes ------------------------- */

/* Initial and Improvement Order (Options) / Exposed Order */
typedef struct {
  uint8_t exchange_id;                             /* byte 0 */
  InstrumentDescription instrument_description;    /* bytes 1 to 20 */
  uint8_t deletion_type;                           /* byte 21 */
  uint8_t order_sequence_number[6];                /* bytes 22 to 27 */
  uint8_t improvement_order_side;                  /* byte 28 */
  uint8_t improvement_phase_sequential_number[6];  /* bytes 29 to 34 */
  uint8_t auction_type;                            /* byte 35 */
} InitialAndImprovementOrderMessage;

/* any Initial And Improvement Order Message at all: every byte one the checker chooses */
static void any_initial_and_improvement_order_message(InitialAndImprovementOrderMessage *record) {
  record->exchange_id = arbitrary();
  any_instrument_description(&record->instrument_description);
  record->deletion_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->order_sequence_number[i] = arbitrary(); }
  record->improvement_order_side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->improvement_phase_sequential_number[i] = arbitrary(); }
  record->auction_type = arbitrary();
}

/* Initial And Improvement Order Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_initial_and_improvement_order_message(const InitialAndImprovementOrderMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->exchange_id;
  at = encode_instrument_description(&record->instrument_description, wire, at);
  wire[at++] = record->deletion_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->order_sequence_number[i]; }
  wire[at++] = record->improvement_order_side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->improvement_phase_sequential_number[i]; }
  wire[at++] = record->auction_type;

  return at;
}

/* Initial And Improvement Order Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_initial_and_improvement_order_message(InitialAndImprovementOrderMessage *record, const uint8_t *wire, size_t at) {
  record->exchange_id = wire[at++];
  at = decode_instrument_description(&record->instrument_description, wire, at);
  record->deletion_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->order_sequence_number[i] = wire[at++]; }
  record->improvement_order_side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->improvement_phase_sequential_number[i] = wire[at++]; }
  record->auction_type = wire[at++];

  return at;
}

/* what was read of Initial And Improvement Order Message is what was written, byte for byte */
static void equal_initial_and_improvement_order_message(const InitialAndImprovementOrderMessage *read, const InitialAndImprovementOrderMessage *written) {
  assert(read->exchange_id == written->exchange_id);
  equal_instrument_description(&read->instrument_description, &written->instrument_description);
  assert(read->deletion_type == written->deletion_type);
  for (size_t i = 0; i < 6; i++) { assert(read->order_sequence_number[i] == written->order_sequence_number[i]); }
  assert(read->improvement_order_side == written->improvement_order_side);
  for (size_t i = 0; i < 6; i++) { assert(read->improvement_phase_sequential_number[i] == written->improvement_phase_sequential_number[i]); }
  assert(read->auction_type == written->auction_type);
}

/* Initial And Improvement Order Message: written and read back, then read and written back */
static void check_initial_and_improvement_order_message(void) {
  InitialAndImprovementOrderMessage sent;
  InitialAndImprovementOrderMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_initial_and_improvement_order_message(&sent);
  assert(encode_initial_and_improvement_order_message(&sent, wire, 0) == 36);
  assert(decode_initial_and_improvement_order_message(&got, wire, 0) == 36);
  equal_initial_and_improvement_order_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_initial_and_improvement_order_message(&got, wire, 0) == 36);
  assert(encode_initial_and_improvement_order_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Order Initial And Improvement Order Message: 46 bytes ----------- */

/* Initial and Improvement Order (Complex Order) / Exposed Order (Complex Order) */
typedef struct {
  uint8_t exchange_id;                             /* byte 0 */
  uint8_t complex_order_instrument_symbol[30];     /* bytes 1 to 30 */
  uint8_t deletion_type;                           /* byte 31 */
  uint8_t order_sequence_number[6];                /* bytes 32 to 37 */
  uint8_t order_side;                              /* byte 38 */
  uint8_t improvement_phase_sequential_number[6];  /* bytes 39 to 44 */
  uint8_t auction_type;                            /* byte 45 */
} ComplexOrderInitialAndImprovementOrderMessage;

/* any Complex Order Initial And Improvement Order Message at all: every byte one the checker chooses */
static void any_complex_order_initial_and_improvement_order_message(ComplexOrderInitialAndImprovementOrderMessage *record) {
  record->exchange_id = arbitrary();
  for (size_t i = 0; i < 30; i++) { record->complex_order_instrument_symbol[i] = arbitrary(); }
  record->deletion_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->order_sequence_number[i] = arbitrary(); }
  record->order_side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->improvement_phase_sequential_number[i] = arbitrary(); }
  record->auction_type = arbitrary();
}

/* Complex Order Initial And Improvement Order Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_complex_order_initial_and_improvement_order_message(const ComplexOrderInitialAndImprovementOrderMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->exchange_id;
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->complex_order_instrument_symbol[i]; }
  wire[at++] = record->deletion_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->order_sequence_number[i]; }
  wire[at++] = record->order_side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->improvement_phase_sequential_number[i]; }
  wire[at++] = record->auction_type;

  return at;
}

/* Complex Order Initial And Improvement Order Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_complex_order_initial_and_improvement_order_message(ComplexOrderInitialAndImprovementOrderMessage *record, const uint8_t *wire, size_t at) {
  record->exchange_id = wire[at++];
  for (size_t i = 0; i < 30; i++) { record->complex_order_instrument_symbol[i] = wire[at++]; }
  record->deletion_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->order_sequence_number[i] = wire[at++]; }
  record->order_side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->improvement_phase_sequential_number[i] = wire[at++]; }
  record->auction_type = wire[at++];

  return at;
}

/* what was read of Complex Order Initial And Improvement Order Message is what was written, byte for byte */
static void equal_complex_order_initial_and_improvement_order_message(const ComplexOrderInitialAndImprovementOrderMessage *read, const ComplexOrderInitialAndImprovementOrderMessage *written) {
  assert(read->exchange_id == written->exchange_id);
  for (size_t i = 0; i < 30; i++) { assert(read->complex_order_instrument_symbol[i] == written->complex_order_instrument_symbol[i]); }
  assert(read->deletion_type == written->deletion_type);
  for (size_t i = 0; i < 6; i++) { assert(read->order_sequence_number[i] == written->order_sequence_number[i]); }
  assert(read->order_side == written->order_side);
  for (size_t i = 0; i < 6; i++) { assert(read->improvement_phase_sequential_number[i] == written->improvement_phase_sequential_number[i]); }
  assert(read->auction_type == written->auction_type);
}

/* Complex Order Initial And Improvement Order Message: written and read back, then read and written back */
static void check_complex_order_initial_and_improvement_order_message(void) {
  ComplexOrderInitialAndImprovementOrderMessage sent;
  ComplexOrderInitialAndImprovementOrderMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_complex_order_initial_and_improvement_order_message(&sent);
  assert(encode_complex_order_initial_and_improvement_order_message(&sent, wire, 0) == 46);
  assert(decode_complex_order_initial_and_improvement_order_message(&got, wire, 0) == 46);
  equal_complex_order_initial_and_improvement_order_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_order_initial_and_improvement_order_message(&got, wire, 0) == 46);
  assert(encode_complex_order_initial_and_improvement_order_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_end_of_transmission_message();
  check_circuit_assurance_message();
  check_system_timestamp_message();
  check_instrument_description();
  check_group_opening_time_message();
  check_group_status_message();
  check_strategies_group_status_message();
  check_market_flow_indicator();
  check_option_marker();
  check_option_instrument_keys_message();
  check_bulletins_message();
  check_beginning_of_options_summary_message();
  check_beginning_of_complex_order_summary_message();
  check_end_of_sales_message();
  check_option_improvement_process_beginning_message();
  check_complex_order_improvement_process_beginning_message_message();
  check_market_sheet_initial_and_improvement_order_message();
  check_complex_order_market_sheet_initial_and_improvement_order_message();
  check_initial_and_improvement_order_message();
  check_complex_order_initial_and_improvement_order_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
