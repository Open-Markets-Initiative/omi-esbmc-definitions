// iex/iexequities/deep/IexEquities_Deep_v1_6.c
/*
 * Investors Exchange Deep
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
 *   - a length prefix framing what follows
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

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* Snap message header */
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

/* ---- Snapshot Request Message: 56 bytes -------------------------------------- */

/* The Snapshot Request message is sent from the client to the Deep Snap server to authenticate and request a Snapshot Response */
typedef struct {
  uint8_t authentication_token[40];    /* bytes 0 to 39 */
  uint8_t channel_id[4];               /* bytes 40 to 43 */
  uint8_t session_id[4];               /* bytes 44 to 47 */
  uint8_t minimum_sequence_number[8];  /* bytes 48 to 55 */
} SnapshotRequestMessage;

/* any Snapshot Request Message at all: every byte one the checker chooses */
static void any_snapshot_request_message(SnapshotRequestMessage *record) {
  for (size_t i = 0; i < 40; i++) { record->authentication_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->channel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_sequence_number[i] = arbitrary(); }
}

/* Snapshot Request Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_request_message(const SnapshotRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->authentication_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->channel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_sequence_number[i]; }

  return at;
}

/* Snapshot Request Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_request_message(SnapshotRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 40; i++) { record->authentication_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->channel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Snapshot Request Message is what was written, byte for byte */
static void equal_snapshot_request_message(const SnapshotRequestMessage *read, const SnapshotRequestMessage *written) {
  for (size_t i = 0; i < 40; i++) { assert(read->authentication_token[i] == written->authentication_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->channel_id[i] == written->channel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_sequence_number[i] == written->minimum_sequence_number[i]); }
}

/* Snapshot Request Message: written and read back, then read and written back */
static void check_snapshot_request_message(void) {
  SnapshotRequestMessage sent;
  SnapshotRequestMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_snapshot_request_message(&sent);
  assert(encode_snapshot_request_message(&sent, wire, 0) == 56);
  assert(decode_snapshot_request_message(&got, wire, 0) == 56);
  equal_snapshot_request_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_request_message(&got, wire, 0) == 56);
  assert(encode_snapshot_request_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Error Response Message: 1 byte ------------------------------------------ */

/* Sent by the Deep Snap server to the client when a Snapshot Request is rejected */
typedef struct {
  uint8_t reject_reason_code;  /* byte 0 */
} ErrorResponseMessage;

/* any Error Response Message at all: every byte one the checker chooses */
static void any_error_response_message(ErrorResponseMessage *record) {
  record->reject_reason_code = arbitrary();
}

/* Error Response Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_error_response_message(const ErrorResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reject_reason_code;

  return at;
}

/* Error Response Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_error_response_message(ErrorResponseMessage *record, const uint8_t *wire, size_t at) {
  record->reject_reason_code = wire[at++];

  return at;
}

/* what was read of Error Response Message is what was written, byte for byte */
static void equal_error_response_message(const ErrorResponseMessage *read, const ErrorResponseMessage *written) {
  assert(read->reject_reason_code == written->reject_reason_code);
}

/* Error Response Message: written and read back, then read and written back */
static void check_error_response_message(void) {
  ErrorResponseMessage sent;
  ErrorResponseMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_error_response_message(&sent);
  assert(encode_error_response_message(&sent, wire, 0) == 1);
  assert(decode_error_response_message(&got, wire, 0) == 1);
  equal_error_response_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_error_response_message(&got, wire, 0) == 1);
  assert(encode_error_response_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot Start Message: 8 bytes ----------------------------------------- */

/* First message of a Snapshot Response sent from the Deep Snap server when a Snapshot Request is successful */
typedef struct {
  uint8_t snapshot_length[8];  /* bytes 0 to 7 */
} SnapshotStartMessage;

/* any Snapshot Start Message at all: every byte one the checker chooses */
static void any_snapshot_start_message(SnapshotStartMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->snapshot_length[i] = arbitrary(); }
}

/* Snapshot Start Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_start_message(const SnapshotStartMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->snapshot_length[i]; }

  return at;
}

/* Snapshot Start Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_start_message(SnapshotStartMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->snapshot_length[i] = wire[at++]; }

  return at;
}

/* what was read of Snapshot Start Message is what was written, byte for byte */
static void equal_snapshot_start_message(const SnapshotStartMessage *read, const SnapshotStartMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->snapshot_length[i] == written->snapshot_length[i]); }
}

/* Snapshot Start Message: written and read back, then read and written back */
static void check_snapshot_start_message(void) {
  SnapshotStartMessage sent;
  SnapshotStartMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_snapshot_start_message(&sent);
  assert(encode_snapshot_start_message(&sent, wire, 0) == 8);
  assert(decode_snapshot_start_message(&got, wire, 0) == 8);
  equal_snapshot_start_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_start_message(&got, wire, 0) == 8);
  assert(encode_snapshot_start_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Iextp Header: 40 bytes -------------------------------------------------- */

/* IexTp header of the wrapped feed message */
typedef struct {
  uint8_t version;                           /* byte 0 */
  uint8_t reserved;                          /* byte 1 */
  uint8_t message_protocol_id[2];            /* bytes 2 to 3 */
  uint8_t channel_id[4];                     /* bytes 4 to 7 */
  uint8_t session_id[4];                     /* bytes 8 to 11 */
  uint8_t payload_length[2];                 /* bytes 12 to 13 */
  uint8_t message_count[2];                  /* bytes 14 to 15 */
  uint8_t stream_offset[8];                  /* bytes 16 to 23 */
  uint8_t first_message_sequence_number[8];  /* bytes 24 to 31 */
  uint8_t send_time[8];                      /* bytes 32 to 39 */
} IextpHeader;

/* any Iextp Header at all: every byte one the checker chooses */
static void any_iextp_header(IextpHeader *record) {
  record->version = arbitrary();
  record->reserved = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->message_protocol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->channel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->payload_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stream_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->first_message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = arbitrary(); }
}

/* Iextp Header to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_iextp_header(const IextpHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->version;
  wire[at++] = record->reserved;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_protocol_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->channel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->payload_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stream_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->first_message_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->send_time[i]; }

  return at;
}

/* Iextp Header off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_iextp_header(IextpHeader *record, const uint8_t *wire, size_t at) {
  record->version = wire[at++];
  record->reserved = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->message_protocol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->channel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->payload_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stream_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->first_message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = wire[at++]; }

  return at;
}

/* what was read of Iextp Header is what was written, byte for byte */
static void equal_iextp_header(const IextpHeader *read, const IextpHeader *written) {
  assert(read->version == written->version);
  assert(read->reserved == written->reserved);
  for (size_t i = 0; i < 2; i++) { assert(read->message_protocol_id[i] == written->message_protocol_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->channel_id[i] == written->channel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->payload_length[i] == written->payload_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_count[i] == written->message_count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stream_offset[i] == written->stream_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->first_message_sequence_number[i] == written->first_message_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->send_time[i] == written->send_time[i]); }
}

/* Iextp Header: written and read back, then read and written back */
static void check_iextp_header(void) {
  IextpHeader sent;
  IextpHeader got;
  uint8_t wire[40];
  uint8_t again[40];

  any_iextp_header(&sent);
  assert(encode_iextp_header(&sent, wire, 0) == 40);
  assert(decode_iextp_header(&got, wire, 0) == 40);
  equal_iextp_header(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_iextp_header(&got, wire, 0) == 40);
  assert(encode_iextp_header(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 9 bytes ------------------------------------------- */

/* The System Event Message is used to indicate events that apply to the market or the data feed. */
typedef struct {
  uint8_t system_event;  /* byte 0 */
  uint8_t timestamp[8];  /* bytes 1 to 8 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  record->system_event = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* System Event Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->system_event;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* System Event Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  record->system_event = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  assert(read->system_event == written->system_event);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
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

/* ---- Trading Status Message: 21 bytes ---------------------------------------- */

/* The Trading Status Message is used to indicate the current trading status of a security. */
typedef struct {
  uint8_t trading_status;  /* byte 0 */
  uint8_t timestamp[8];    /* bytes 1 to 8 */
  uint8_t symbol[8];       /* bytes 9 to 16 */
  uint8_t reason[4];       /* bytes 17 to 20 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  record->trading_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reason[i] = arbitrary(); }
}

/* Trading Status Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Trading Status Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  record->trading_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  assert(read->trading_status == written->trading_status);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reason[i] == written->reason[i]); }
}

/* Trading Status Message: written and read back, then read and written back */
static void check_trading_status_message(void) {
  TradingStatusMessage sent;
  TradingStatusMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_trading_status_message(&sent);
  assert(encode_trading_status_message(&sent, wire, 0) == 21);
  assert(decode_trading_status_message(&got, wire, 0) == 21);
  equal_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_message(&got, wire, 0) == 21);
  assert(encode_trading_status_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retail Liquidity Indicator Message: 17 bytes ---------------------------- */

/* broadcasts a real-time Retail Liquidity Indicator Message each time there is an update to IEX's eligible retail liquidity interest during the trading day */
typedef struct {
  uint8_t retail_liquidity_indicator;  /* byte 0 */
  uint8_t timestamp[8];                /* bytes 1 to 8 */
  uint8_t symbol[8];                   /* bytes 9 to 16 */
} RetailLiquidityIndicatorMessage;

/* any Retail Liquidity Indicator Message at all: every byte one the checker chooses */
static void any_retail_liquidity_indicator_message(RetailLiquidityIndicatorMessage *record) {
  record->retail_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
}

/* Retail Liquidity Indicator Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_retail_liquidity_indicator_message(const RetailLiquidityIndicatorMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->retail_liquidity_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }

  return at;
}

/* Retail Liquidity Indicator Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_retail_liquidity_indicator_message(RetailLiquidityIndicatorMessage *record, const uint8_t *wire, size_t at) {
  record->retail_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Retail Liquidity Indicator Message is what was written, byte for byte */
static void equal_retail_liquidity_indicator_message(const RetailLiquidityIndicatorMessage *read, const RetailLiquidityIndicatorMessage *written) {
  assert(read->retail_liquidity_indicator == written->retail_liquidity_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
}

/* Retail Liquidity Indicator Message: written and read back, then read and written back */
static void check_retail_liquidity_indicator_message(void) {
  RetailLiquidityIndicatorMessage sent;
  RetailLiquidityIndicatorMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_retail_liquidity_indicator_message(&sent);
  assert(encode_retail_liquidity_indicator_message(&sent, wire, 0) == 17);
  assert(decode_retail_liquidity_indicator_message(&got, wire, 0) == 17);
  equal_retail_liquidity_indicator_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_retail_liquidity_indicator_message(&got, wire, 0) == 17);
  assert(encode_retail_liquidity_indicator_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Operational Halt Status Message: 17 bytes ------------------------------- */

/* The Exchange may suspend trading of one or more securities on IEX for operational reasons and indicates such operational halt using the Operational Halt Status Message. */
typedef struct {
  uint8_t operational_halt_status;  /* byte 0 */
  uint8_t timestamp[8];             /* bytes 1 to 8 */
  uint8_t symbol[8];                /* bytes 9 to 16 */
} OperationalHaltStatusMessage;

/* any Operational Halt Status Message at all: every byte one the checker chooses */
static void any_operational_halt_status_message(OperationalHaltStatusMessage *record) {
  record->operational_halt_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
}

/* Operational Halt Status Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_operational_halt_status_message(const OperationalHaltStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->operational_halt_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }

  return at;
}

/* Operational Halt Status Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_operational_halt_status_message(OperationalHaltStatusMessage *record, const uint8_t *wire, size_t at) {
  record->operational_halt_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Operational Halt Status Message is what was written, byte for byte */
static void equal_operational_halt_status_message(const OperationalHaltStatusMessage *read, const OperationalHaltStatusMessage *written) {
  assert(read->operational_halt_status == written->operational_halt_status);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
}

/* Operational Halt Status Message: written and read back, then read and written back */
static void check_operational_halt_status_message(void) {
  OperationalHaltStatusMessage sent;
  OperationalHaltStatusMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_operational_halt_status_message(&sent);
  assert(encode_operational_halt_status_message(&sent, wire, 0) == 17);
  assert(decode_operational_halt_status_message(&got, wire, 0) == 17);
  equal_operational_halt_status_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_operational_halt_status_message(&got, wire, 0) == 17);
  assert(encode_operational_halt_status_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Sale Price Test Status Message: 18 bytes -------------------------- */

/* The Short Sale Price Test Message is used to indicate when a short sale price test restriction is in effect for a security. */
typedef struct {
  uint8_t short_sale_price_test_status;  /* byte 0 */
  uint8_t timestamp[8];                  /* bytes 1 to 8 */
  uint8_t symbol[8];                     /* bytes 9 to 16 */
  uint8_t detail;                        /* byte 17 */
} ShortSalePriceTestStatusMessage;

/* any Short Sale Price Test Status Message at all: every byte one the checker chooses */
static void any_short_sale_price_test_status_message(ShortSalePriceTestStatusMessage *record) {
  record->short_sale_price_test_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->detail = arbitrary();
}

/* Short Sale Price Test Status Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_short_sale_price_test_status_message(const ShortSalePriceTestStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->short_sale_price_test_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->detail;

  return at;
}

/* Short Sale Price Test Status Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_short_sale_price_test_status_message(ShortSalePriceTestStatusMessage *record, const uint8_t *wire, size_t at) {
  record->short_sale_price_test_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->detail = wire[at++];

  return at;
}

/* what was read of Short Sale Price Test Status Message is what was written, byte for byte */
static void equal_short_sale_price_test_status_message(const ShortSalePriceTestStatusMessage *read, const ShortSalePriceTestStatusMessage *written) {
  assert(read->short_sale_price_test_status == written->short_sale_price_test_status);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->detail == written->detail);
}

/* Short Sale Price Test Status Message: written and read back, then read and written back */
static void check_short_sale_price_test_status_message(void) {
  ShortSalePriceTestStatusMessage sent;
  ShortSalePriceTestStatusMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_short_sale_price_test_status_message(&sent);
  assert(encode_short_sale_price_test_status_message(&sent, wire, 0) == 18);
  assert(decode_short_sale_price_test_status_message(&got, wire, 0) == 18);
  equal_short_sale_price_test_status_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_short_sale_price_test_status_message(&got, wire, 0) == 18);
  assert(encode_short_sale_price_test_status_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Event Message: 17 bytes ---------------------------------------- */

/* The Security Event Message is used to indicate events that apply to a security */
typedef struct {
  uint8_t security_event;  /* byte 0 */
  uint8_t timestamp[8];    /* bytes 1 to 8 */
  uint8_t symbol[8];       /* bytes 9 to 16 */
} SecurityEventMessage;

/* any Security Event Message at all: every byte one the checker chooses */
static void any_security_event_message(SecurityEventMessage *record) {
  record->security_event = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
}

/* Security Event Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_security_event_message(const SecurityEventMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->security_event;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }

  return at;
}

/* Security Event Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_security_event_message(SecurityEventMessage *record, const uint8_t *wire, size_t at) {
  record->security_event = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Security Event Message is what was written, byte for byte */
static void equal_security_event_message(const SecurityEventMessage *read, const SecurityEventMessage *written) {
  assert(read->security_event == written->security_event);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
}

/* Security Event Message: written and read back, then read and written back */
static void check_security_event_message(void) {
  SecurityEventMessage sent;
  SecurityEventMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_security_event_message(&sent);
  assert(encode_security_event_message(&sent, wire, 0) == 17);
  assert(decode_security_event_message(&got, wire, 0) == 17);
  equal_security_event_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_security_event_message(&got, wire, 0) == 17);
  assert(encode_security_event_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Level Buy Update Message: 29 bytes -------------------------------- */

/* Deep broadcasts a real-time Price Level Update Message each time a displayed price level on IEX is updated during the trading day */
typedef struct {
  uint8_t event_flags;   /* byte 0 */
  uint8_t timestamp[8];  /* bytes 1 to 8 */
  uint8_t symbol[8];     /* bytes 9 to 16 */
  uint8_t size[4];       /* bytes 17 to 20 */
  uint8_t price[8];      /* bytes 21 to 28 */
} PriceLevelBuyUpdateMessage;

/* any Price Level Buy Update Message at all: every byte one the checker chooses */
static void any_price_level_buy_update_message(PriceLevelBuyUpdateMessage *record) {
  record->event_flags = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Price Level Buy Update Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_price_level_buy_update_message(const PriceLevelBuyUpdateMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->event_flags;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Price Level Buy Update Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_price_level_buy_update_message(PriceLevelBuyUpdateMessage *record, const uint8_t *wire, size_t at) {
  record->event_flags = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Price Level Buy Update Message is what was written, byte for byte */
static void equal_price_level_buy_update_message(const PriceLevelBuyUpdateMessage *read, const PriceLevelBuyUpdateMessage *written) {
  assert(read->event_flags == written->event_flags);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Price Level Buy Update Message: written and read back, then read and written back */
static void check_price_level_buy_update_message(void) {
  PriceLevelBuyUpdateMessage sent;
  PriceLevelBuyUpdateMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_price_level_buy_update_message(&sent);
  assert(encode_price_level_buy_update_message(&sent, wire, 0) == 29);
  assert(decode_price_level_buy_update_message(&got, wire, 0) == 29);
  equal_price_level_buy_update_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_price_level_buy_update_message(&got, wire, 0) == 29);
  assert(encode_price_level_buy_update_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Level Sell Update Message: 29 bytes ------------------------------- */

/* Deep broadcasts a real-time Price Level Update Message each time a displayed price level on IEX is updated during the trading day */
typedef struct {
  uint8_t event_flags;   /* byte 0 */
  uint8_t timestamp[8];  /* bytes 1 to 8 */
  uint8_t symbol[8];     /* bytes 9 to 16 */
  uint8_t size[4];       /* bytes 17 to 20 */
  uint8_t price[8];      /* bytes 21 to 28 */
} PriceLevelSellUpdateMessage;

/* any Price Level Sell Update Message at all: every byte one the checker chooses */
static void any_price_level_sell_update_message(PriceLevelSellUpdateMessage *record) {
  record->event_flags = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Price Level Sell Update Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_price_level_sell_update_message(const PriceLevelSellUpdateMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->event_flags;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Price Level Sell Update Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_price_level_sell_update_message(PriceLevelSellUpdateMessage *record, const uint8_t *wire, size_t at) {
  record->event_flags = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Price Level Sell Update Message is what was written, byte for byte */
static void equal_price_level_sell_update_message(const PriceLevelSellUpdateMessage *read, const PriceLevelSellUpdateMessage *written) {
  assert(read->event_flags == written->event_flags);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Price Level Sell Update Message: written and read back, then read and written back */
static void check_price_level_sell_update_message(void) {
  PriceLevelSellUpdateMessage sent;
  PriceLevelSellUpdateMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_price_level_sell_update_message(&sent);
  assert(encode_price_level_sell_update_message(&sent, wire, 0) == 29);
  assert(decode_price_level_sell_update_message(&got, wire, 0) == 29);
  equal_price_level_sell_update_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_price_level_sell_update_message(&got, wire, 0) == 29);
  assert(encode_price_level_sell_update_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Official Price Message: 25 bytes ---------------------------------------- */

/* Official Price Messages are sent for each IEX-listed security to indicate the IEX Official Opening Price and IEX Official Closing Price. */
typedef struct {
  uint8_t price_type;         /* byte 0 */
  uint8_t timestamp[8];       /* bytes 1 to 8 */
  uint8_t symbol[8];          /* bytes 9 to 16 */
  uint8_t official_price[8];  /* bytes 17 to 24 */
} OfficialPriceMessage;

/* any Official Price Message at all: every byte one the checker chooses */
static void any_official_price_message(OfficialPriceMessage *record) {
  record->price_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->official_price[i] = arbitrary(); }
}

/* Official Price Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_official_price_message(const OfficialPriceMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->price_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->official_price[i]; }

  return at;
}

/* Official Price Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_official_price_message(OfficialPriceMessage *record, const uint8_t *wire, size_t at) {
  record->price_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->official_price[i] = wire[at++]; }

  return at;
}

/* what was read of Official Price Message is what was written, byte for byte */
static void equal_official_price_message(const OfficialPriceMessage *read, const OfficialPriceMessage *written) {
  assert(read->price_type == written->price_type);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->official_price[i] == written->official_price[i]); }
}

/* Official Price Message: written and read back, then read and written back */
static void check_official_price_message(void) {
  OfficialPriceMessage sent;
  OfficialPriceMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_official_price_message(&sent);
  assert(encode_official_price_message(&sent, wire, 0) == 25);
  assert(decode_official_price_message(&got, wire, 0) == 25);
  equal_official_price_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_official_price_message(&got, wire, 0) == 25);
  assert(encode_official_price_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Information Message: 79 bytes ----------------------------------- */

/* Broadcasts an Auction Information Message every one second between the Lock-in Time and the auction match for Opening and Closing Auctions, and during the Display Only Period for IPO, Halt, and Volatility Auctions. */
typedef struct {
  uint8_t auction_type;                    /* byte 0 */
  uint8_t timestamp[8];                    /* bytes 1 to 8 */
  uint8_t symbol[8];                       /* bytes 9 to 16 */
  uint8_t paired_shares[4];                /* bytes 17 to 20 */
  uint8_t reference_price[8];              /* bytes 21 to 28 */
  uint8_t indicative_clearing_price[8];    /* bytes 29 to 36 */
  uint8_t imbalance_shares[4];             /* bytes 37 to 40 */
  uint8_t imbalance_side;                  /* byte 41 */
  uint8_t extension_number;                /* byte 42 */
  uint8_t scheduled_auction_time[4];       /* bytes 43 to 46 */
  uint8_t auction_book_clearing_price[8];  /* bytes 47 to 54 */
  uint8_t collar_reference_price[8];       /* bytes 55 to 62 */
  uint8_t lower_auction_collar[8];         /* bytes 63 to 70 */
  uint8_t upper_auction_collar[8];         /* bytes 71 to 78 */
} AuctionInformationMessage;

/* any Auction Information Message at all: every byte one the checker chooses */
static void any_auction_information_message(AuctionInformationMessage *record) {
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->paired_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_clearing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->imbalance_shares[i] = arbitrary(); }
  record->imbalance_side = arbitrary();
  record->extension_number = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->scheduled_auction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_book_clearing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->collar_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lower_auction_collar[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->upper_auction_collar[i] = arbitrary(); }
}

/* Auction Information Message to the wire: 79 bytes from at, returning where the next byte goes */
static size_t encode_auction_information_message(const AuctionInformationMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->paired_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_clearing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->imbalance_shares[i]; }
  wire[at++] = record->imbalance_side;
  wire[at++] = record->extension_number;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->scheduled_auction_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_book_clearing_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->collar_reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_auction_collar[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->upper_auction_collar[i]; }

  return at;
}

/* Auction Information Message off the wire: 79 bytes from at, returning where the next byte lies */
static size_t decode_auction_information_message(AuctionInformationMessage *record, const uint8_t *wire, size_t at) {
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->paired_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_clearing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->imbalance_shares[i] = wire[at++]; }
  record->imbalance_side = wire[at++];
  record->extension_number = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->scheduled_auction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_book_clearing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->collar_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lower_auction_collar[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->upper_auction_collar[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Information Message is what was written, byte for byte */
static void equal_auction_information_message(const AuctionInformationMessage *read, const AuctionInformationMessage *written) {
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->paired_shares[i] == written->paired_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_clearing_price[i] == written->indicative_clearing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->imbalance_shares[i] == written->imbalance_shares[i]); }
  assert(read->imbalance_side == written->imbalance_side);
  assert(read->extension_number == written->extension_number);
  for (size_t i = 0; i < 4; i++) { assert(read->scheduled_auction_time[i] == written->scheduled_auction_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_book_clearing_price[i] == written->auction_book_clearing_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->collar_reference_price[i] == written->collar_reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lower_auction_collar[i] == written->lower_auction_collar[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->upper_auction_collar[i] == written->upper_auction_collar[i]); }
}

/* Auction Information Message: written and read back, then read and written back */
static void check_auction_information_message(void) {
  AuctionInformationMessage sent;
  AuctionInformationMessage got;
  uint8_t wire[79];
  uint8_t again[79];

  any_auction_information_message(&sent);
  assert(encode_auction_information_message(&sent, wire, 0) == 79);
  assert(decode_auction_information_message(&got, wire, 0) == 79);
  equal_auction_information_message(&got, &sent);

  for (size_t i = 0; i < 79; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_information_message(&got, wire, 0) == 79);
  assert(encode_auction_information_message(&got, again, 0) == 79);
  for (size_t i = 0; i < 79; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot End Message: 8 bytes ------------------------------------------- */

/* Final message of a Snapshot Response, carries the sequence number at which the snapshot was created */
typedef struct {
  uint8_t snapshot_sequence_number[8];  /* bytes 0 to 7 */
} SnapshotEndMessage;

/* any Snapshot End Message at all: every byte one the checker chooses */
static void any_snapshot_end_message(SnapshotEndMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->snapshot_sequence_number[i] = arbitrary(); }
}

/* Snapshot End Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_end_message(const SnapshotEndMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->snapshot_sequence_number[i]; }

  return at;
}

/* Snapshot End Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_end_message(SnapshotEndMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->snapshot_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Snapshot End Message is what was written, byte for byte */
static void equal_snapshot_end_message(const SnapshotEndMessage *read, const SnapshotEndMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->snapshot_sequence_number[i] == written->snapshot_sequence_number[i]); }
}

/* Snapshot End Message: written and read back, then read and written back */
static void check_snapshot_end_message(void) {
  SnapshotEndMessage sent;
  SnapshotEndMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_snapshot_end_message(&sent);
  assert(encode_snapshot_end_message(&sent, wire, 0) == 8);
  assert(decode_snapshot_end_message(&got, wire, 0) == 8);
  equal_snapshot_end_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_end_message(&got, wire, 0) == 8);
  assert(encode_snapshot_end_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_snapshot_request_message();
  check_error_response_message();
  check_snapshot_start_message();
  check_iextp_header();
  check_system_event_message();
  check_trading_status_message();
  check_retail_liquidity_indicator_message();
  check_operational_halt_status_message();
  check_short_sale_price_test_status_message();
  check_security_event_message();
  check_price_level_buy_update_message();
  check_price_level_sell_update_message();
  check_official_price_message();
  check_auction_information_message();
  check_snapshot_end_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
