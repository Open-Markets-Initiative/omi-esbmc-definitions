// nse/nseix/recovery/NseIx_Recovery_v1_4_Tcp.c
/*
 * National Stock Exchange of India Ltd Mtbt Tick Data Recovery
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
 *   - the dispatch that chooses a message by its type
 *   - a Composite rule
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

/* ---- Stream Header: 8 bytes -------------------------------------------------- */

/* STREAM_HEADER */
typedef struct {
  uint8_t message_length[2];   /* bytes 0 to 1 */
  uint8_t stream_id[2];        /* bytes 2 to 3 */
  uint8_t sequence_number[4];  /* bytes 4 to 7 */
} StreamHeader;

/* any Stream Header at all: every byte one the checker chooses */
static void any_stream_header(StreamHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Stream Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_stream_header(const StreamHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stream_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Stream Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_stream_header(StreamHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Stream Header is what was written, byte for byte */
static void equal_stream_header(const StreamHeader *read, const StreamHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->stream_id[i] == written->stream_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Stream Header: written and read back, then read and written back */
static void check_stream_header(void) {
  StreamHeader sent;
  StreamHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_stream_header(&sent);
  assert(encode_stream_header(&sent, wire, 0) == 8);
  assert(decode_stream_header(&got, wire, 0) == 8);
  equal_stream_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_stream_header(&got, wire, 0) == 8);
  assert(encode_stream_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Status Message: 18 bytes ----------------------------------------- */

/* Sent whenever the status of the market is changed to preopen, preopen-end, open, closed, preclose and preclose-end, for both T and T+1 sessions (section 6.5). */
typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t instrument[6];    /* bytes 8 to 13 */
  uint8_t status[2];        /* bytes 14 to 15 */
  uint8_t session_indc[2];  /* bytes 16 to 17 */
} MarketStatusMessage;

/* any Market Status Message at all: every byte one the checker chooses */
static void any_market_status_message(MarketStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->status[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_indc[i] = arbitrary(); }
}

/* Market Status Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_market_status_message(const MarketStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->status[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_indc[i]; }

  return at;
}

/* Market Status Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_market_status_message(MarketStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->status[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_indc[i] = wire[at++]; }

  return at;
}

/* what was read of Market Status Message is what was written, byte for byte */
static void equal_market_status_message(const MarketStatusMessage *read, const MarketStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->status[i] == written->status[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_indc[i] == written->session_indc[i]); }
}

/* Market Status Message: written and read back, then read and written back */
static void check_market_status_message(void) {
  MarketStatusMessage sent;
  MarketStatusMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_market_status_message(&sent);
  assert(encode_market_status_message(&sent, wire, 0) == 18);
  assert(decode_market_status_message(&got, wire, 0) == 18);
  equal_market_status_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_market_status_message(&got, wire, 0) == 18);
  assert(encode_market_status_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indicative Price And Quantity Message: 21 bytes ------------------------- */

/* Indicative equilibrium price and quantity, sent for contracts with pre-open and pre-close sessions, only between the preopen or preclose and the preopen end or preclose end statuses, when the indicative price and quantity are determined or updated during order collection (section 6.6). */
typedef struct {
  uint8_t timestamp[8];            /* bytes 0 to 7 */
  uint8_t token[4];                /* bytes 8 to 11 */
  uint8_t identifier;              /* byte 12 */
  uint8_t indicative_price[4];     /* bytes 13 to 16 */
  uint8_t indicative_quantity[4];  /* bytes 17 to 20 */
} IndicativePriceAndQuantityMessage;

/* any Indicative Price And Quantity Message at all: every byte one the checker chooses */
static void any_indicative_price_and_quantity_message(IndicativePriceAndQuantityMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->token[i] = arbitrary(); }
  record->identifier = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->indicative_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->indicative_quantity[i] = arbitrary(); }
}

/* Indicative Price And Quantity Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_indicative_price_and_quantity_message(const IndicativePriceAndQuantityMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->token[i]; }
  wire[at++] = record->identifier;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->indicative_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->indicative_quantity[i]; }

  return at;
}

/* Indicative Price And Quantity Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_indicative_price_and_quantity_message(IndicativePriceAndQuantityMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->token[i] = wire[at++]; }
  record->identifier = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->indicative_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->indicative_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Indicative Price And Quantity Message is what was written, byte for byte */
static void equal_indicative_price_and_quantity_message(const IndicativePriceAndQuantityMessage *read, const IndicativePriceAndQuantityMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->token[i] == written->token[i]); }
  assert(read->identifier == written->identifier);
  for (size_t i = 0; i < 4; i++) { assert(read->indicative_price[i] == written->indicative_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->indicative_quantity[i] == written->indicative_quantity[i]); }
}

/* Indicative Price And Quantity Message: written and read back, then read and written back */
static void check_indicative_price_and_quantity_message(void) {
  IndicativePriceAndQuantityMessage sent;
  IndicativePriceAndQuantityMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_indicative_price_and_quantity_message(&sent);
  assert(encode_indicative_price_and_quantity_message(&sent, wire, 0) == 21);
  assert(decode_indicative_price_and_quantity_message(&got, wire, 0) == 21);
  equal_indicative_price_and_quantity_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_indicative_price_and_quantity_message(&got, wire, 0) == 21);
  assert(encode_indicative_price_and_quantity_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heartbeat Message: 4 bytes ---------------------------------------------- */

/* Sent when there is no data available for a few seconds; the sequence number field in the Stream Header will have the value 0 (zero) (section 9). */
typedef struct {
  uint8_t last_sequence_no[4];  /* bytes 0 to 3 */
} HeartbeatMessage;

/* any Heartbeat Message at all: every byte one the checker chooses */
static void any_heartbeat_message(HeartbeatMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->last_sequence_no[i] = arbitrary(); }
}

/* Heartbeat Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat_message(const HeartbeatMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_sequence_no[i]; }

  return at;
}

/* Heartbeat Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat_message(HeartbeatMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_sequence_no[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat Message is what was written, byte for byte */
static void equal_heartbeat_message(const HeartbeatMessage *read, const HeartbeatMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_sequence_no[i] == written->last_sequence_no[i]); }
}

/* Heartbeat Message: written and read back, then read and written back */
static void check_heartbeat_message(void) {
  HeartbeatMessage sent;
  HeartbeatMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_heartbeat_message(&sent);
  assert(encode_heartbeat_message(&sent, wire, 0) == 4);
  assert(decode_heartbeat_message(&got, wire, 0) == 4);
  equal_heartbeat_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_heartbeat_message(&got, wire, 0) == 4);
  assert(encode_heartbeat_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Data Recovery Response Message: 1 byte ----------------------------- */

/* First message sent by the Recovery Server, indicating whether the request was processed successfully; the Stream Header's sequence number is zero. */
typedef struct {
  uint8_t request_status;  /* byte 0 */
} TickDataRecoveryResponseMessage;

/* any Tick Data Recovery Response Message at all: every byte one the checker chooses */
static void any_tick_data_recovery_response_message(TickDataRecoveryResponseMessage *record) {
  record->request_status = arbitrary();
}

/* Tick Data Recovery Response Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_tick_data_recovery_response_message(const TickDataRecoveryResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->request_status;

  return at;
}

/* Tick Data Recovery Response Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_tick_data_recovery_response_message(TickDataRecoveryResponseMessage *record, const uint8_t *wire, size_t at) {
  record->request_status = wire[at++];

  return at;
}

/* what was read of Tick Data Recovery Response Message is what was written, byte for byte */
static void equal_tick_data_recovery_response_message(const TickDataRecoveryResponseMessage *read, const TickDataRecoveryResponseMessage *written) {
  assert(read->request_status == written->request_status);
}

/* Tick Data Recovery Response Message: written and read back, then read and written back */
static void check_tick_data_recovery_response_message(void) {
  TickDataRecoveryResponseMessage sent;
  TickDataRecoveryResponseMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_tick_data_recovery_response_message(&sent);
  assert(encode_tick_data_recovery_response_message(&sent, wire, 0) == 1);
  assert(decode_tick_data_recovery_response_message(&got, wire, 0) == 1);
  equal_tick_data_recovery_response_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_data_recovery_response_message(&got, wire, 0) == 1);
  assert(encode_tick_data_recovery_response_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_stream_header();
  check_market_status_message();
  check_indicative_price_and_quantity_message();
  check_heartbeat_message();
  check_tick_data_recovery_response_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
