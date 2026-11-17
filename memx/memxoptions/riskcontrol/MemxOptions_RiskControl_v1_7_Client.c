// memx/memxoptions/riskcontrol/MemxOptions_RiskControl_v1_7_Client.c
/*
 * The Members Exchange Risk Control
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
 *   - a Reassemble rule
 *   - the dispatch that chooses a message by its type
 *   - a block whose stated length holds more than its fields
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

/* ---- Common Header: 3 bytes -------------------------------------------------- */

/* Tcp Common Header */
typedef struct {
  uint8_t message_type;       /* byte 0 */
  uint8_t message_length[2];  /* bytes 1 to 2 */
} CommonHeader;

/* any Common Header at all: every byte one the checker chooses */
static void any_common_header(CommonHeader *record) {
  record->message_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
}

/* Common Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_common_header(const CommonHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }

  return at;
}

/* Common Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_common_header(CommonHeader *record, const uint8_t *wire, size_t at) {
  record->message_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }

  return at;
}

/* what was read of Common Header is what was written, byte for byte */
static void equal_common_header(const CommonHeader *read, const CommonHeader *written) {
  assert(read->message_type == written->message_type);
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
}

/* Common Header: written and read back, then read and written back */
static void check_common_header(void) {
  CommonHeader sent;
  CommonHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_common_header(&sent);
  assert(encode_common_header(&sent, wire, 0) == 3);
  assert(decode_common_header(&got, wire, 0) == 3);
  equal_common_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_common_header(&got, wire, 0) == 3);
  assert(encode_common_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request Message: 2 bytes ------------------------------------------ */

/* Memx Tcp Login message */
typedef struct {
  uint8_t token_type;  /* byte 0 */
  uint8_t token;       /* byte 1 */
} LoginRequestMessage;

/* any Login Request Message at all: every byte one the checker chooses */
static void any_login_request_message(LoginRequestMessage *record) {
  record->token_type = arbitrary();
  record->token = arbitrary();
}

/* Login Request Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_login_request_message(const LoginRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->token_type;
  wire[at++] = record->token;

  return at;
}

/* Login Request Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_login_request_message(LoginRequestMessage *record, const uint8_t *wire, size_t at) {
  record->token_type = wire[at++];
  record->token = wire[at++];

  return at;
}

/* what was read of Login Request Message is what was written, byte for byte */
static void equal_login_request_message(const LoginRequestMessage *read, const LoginRequestMessage *written) {
  assert(read->token_type == written->token_type);
  assert(read->token == written->token);
}

/* Login Request Message: written and read back, then read and written back */
static void check_login_request_message(void) {
  LoginRequestMessage sent;
  LoginRequestMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_login_request_message(&sent);
  assert(encode_login_request_message(&sent, wire, 0) == 2);
  assert(decode_login_request_message(&got, wire, 0) == 2);
  equal_login_request_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request_message(&got, wire, 0) == 2);
  assert(encode_login_request_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay Request Message: 20 bytes ---------------------------------------- */

/* Memx Tcp Replay Request message */
typedef struct {
  uint8_t session_id[8];            /* bytes 0 to 7 */
  uint8_t next_sequence_number[8];  /* bytes 8 to 15 */
  uint8_t count[4];                 /* bytes 16 to 19 */
} ReplayRequestMessage;

/* any Replay Request Message at all: every byte one the checker chooses */
static void any_replay_request_message(ReplayRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count[i] = arbitrary(); }
}

/* Replay Request Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_replay_request_message(const ReplayRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count[i]; }

  return at;
}

/* Replay Request Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_replay_request_message(ReplayRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count[i] = wire[at++]; }

  return at;
}

/* what was read of Replay Request Message is what was written, byte for byte */
static void equal_replay_request_message(const ReplayRequestMessage *read, const ReplayRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->next_sequence_number[i] == written->next_sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->count[i] == written->count[i]); }
}

/* Replay Request Message: written and read back, then read and written back */
static void check_replay_request_message(void) {
  ReplayRequestMessage sent;
  ReplayRequestMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_replay_request_message(&sent);
  assert(encode_replay_request_message(&sent, wire, 0) == 20);
  assert(decode_replay_request_message(&got, wire, 0) == 20);
  equal_replay_request_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_request_message(&got, wire, 0) == 20);
  assert(encode_replay_request_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay All Request Message: 8 bytes ------------------------------------- */

/* Memx Tcp Replay All Request message */
typedef struct {
  uint8_t session_id[8];  /* bytes 0 to 7 */
} ReplayAllRequestMessage;

/* any Replay All Request Message at all: every byte one the checker chooses */
static void any_replay_all_request_message(ReplayAllRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = arbitrary(); }
}

/* Replay All Request Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_replay_all_request_message(const ReplayAllRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_id[i]; }

  return at;
}

/* Replay All Request Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_replay_all_request_message(ReplayAllRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = wire[at++]; }

  return at;
}

/* what was read of Replay All Request Message is what was written, byte for byte */
static void equal_replay_all_request_message(const ReplayAllRequestMessage *read, const ReplayAllRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->session_id[i] == written->session_id[i]); }
}

/* Replay All Request Message: written and read back, then read and written back */
static void check_replay_all_request_message(void) {
  ReplayAllRequestMessage sent;
  ReplayAllRequestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_replay_all_request_message(&sent);
  assert(encode_replay_all_request_message(&sent, wire, 0) == 8);
  assert(decode_replay_all_request_message(&got, wire, 0) == 8);
  equal_replay_all_request_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_all_request_message(&got, wire, 0) == 8);
  assert(encode_replay_all_request_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stream Request Message: 16 bytes ---------------------------------------- */

/* Memx Tcp Stream Request message */
typedef struct {
  uint8_t session_id[8];            /* bytes 0 to 7 */
  uint8_t next_sequence_number[8];  /* bytes 8 to 15 */
} StreamRequestMessage;

/* any Stream Request Message at all: every byte one the checker chooses */
static void any_stream_request_message(StreamRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = arbitrary(); }
}

/* Stream Request Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_stream_request_message(const StreamRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_sequence_number[i]; }

  return at;
}

/* Stream Request Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_stream_request_message(StreamRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Stream Request Message is what was written, byte for byte */
static void equal_stream_request_message(const StreamRequestMessage *read, const StreamRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->next_sequence_number[i] == written->next_sequence_number[i]); }
}

/* Stream Request Message: written and read back, then read and written back */
static void check_stream_request_message(void) {
  StreamRequestMessage sent;
  StreamRequestMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_stream_request_message(&sent);
  assert(encode_stream_request_message(&sent, wire, 0) == 16);
  assert(decode_stream_request_message(&got, wire, 0) == 16);
  equal_stream_request_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_stream_request_message(&got, wire, 0) == 16);
  assert(encode_stream_request_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sbe Header: 6 bytes ----------------------------------------------------- */

/* Sbe Header */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id;      /* byte 2 */
  uint8_t schema_id;        /* byte 3 */
  uint8_t version[2];       /* bytes 4 to 5 */
} SbeHeader;

/* any Sbe Header at all: every byte one the checker chooses */
static void any_sbe_header(SbeHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  record->template_id = arbitrary();
  record->schema_id = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Sbe Header to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_sbe_header(const SbeHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  wire[at++] = record->template_id;
  wire[at++] = record->schema_id;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Sbe Header off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_sbe_header(SbeHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  record->template_id = wire[at++];
  record->schema_id = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Sbe Header is what was written, byte for byte */
static void equal_sbe_header(const SbeHeader *read, const SbeHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  assert(read->template_id == written->template_id);
  assert(read->schema_id == written->schema_id);
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Sbe Header: written and read back, then read and written back */
static void check_sbe_header(void) {
  SbeHeader sent;
  SbeHeader got;
  uint8_t wire[6];
  uint8_t again[6];

  any_sbe_header(&sent);
  assert(encode_sbe_header(&sent, wire, 0) == 6);
  assert(decode_sbe_header(&got, wire, 0) == 6);
  equal_sbe_header(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_sbe_header(&got, wire, 0) == 6);
  assert(encode_sbe_header(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Risk Settings Query Message: 20 bytes ----------------------------------- */

/* RiskSettingsQueryMessage */
typedef struct {
  uint8_t cl_ord_id[20];  /* bytes 0 to 19 */
} RiskSettingsQueryMessage;

/* any Risk Settings Query Message at all: every byte one the checker chooses */
static void any_risk_settings_query_message(RiskSettingsQueryMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
}

/* Risk Settings Query Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_risk_settings_query_message(const RiskSettingsQueryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }

  return at;
}

/* Risk Settings Query Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_risk_settings_query_message(RiskSettingsQueryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }

  return at;
}

/* what was read of Risk Settings Query Message is what was written, byte for byte */
static void equal_risk_settings_query_message(const RiskSettingsQueryMessage *read, const RiskSettingsQueryMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
}

/* Risk Settings Query Message: written and read back, then read and written back */
static void check_risk_settings_query_message(void) {
  RiskSettingsQueryMessage sent;
  RiskSettingsQueryMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_risk_settings_query_message(&sent);
  assert(encode_risk_settings_query_message(&sent, wire, 0) == 20);
  assert(decode_risk_settings_query_message(&got, wire, 0) == 20);
  equal_risk_settings_query_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_risk_settings_query_message(&got, wire, 0) == 20);
  assert(encode_risk_settings_query_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Active Risk Threshold Change Request Message: 34 bytes ------------------ */

/* ActiveRiskThresholdChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];  /* bytes 20 to 25 */
  uint8_t efid_optional[4];       /* bytes 26 to 29 */
  uint8_t threshold_quantity[4];  /* bytes 30 to 33 */
} ActiveRiskThresholdChangeRequestMessage;

/* any Active Risk Threshold Change Request Message at all: every byte one the checker chooses */
static void any_active_risk_threshold_change_request_message(ActiveRiskThresholdChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->threshold_quantity[i] = arbitrary(); }
}

/* Active Risk Threshold Change Request Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_active_risk_threshold_change_request_message(const ActiveRiskThresholdChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->threshold_quantity[i]; }

  return at;
}

/* Active Risk Threshold Change Request Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_active_risk_threshold_change_request_message(ActiveRiskThresholdChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->threshold_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Active Risk Threshold Change Request Message is what was written, byte for byte */
static void equal_active_risk_threshold_change_request_message(const ActiveRiskThresholdChangeRequestMessage *read, const ActiveRiskThresholdChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->threshold_quantity[i] == written->threshold_quantity[i]); }
}

/* Active Risk Threshold Change Request Message: written and read back, then read and written back */
static void check_active_risk_threshold_change_request_message(void) {
  ActiveRiskThresholdChangeRequestMessage sent;
  ActiveRiskThresholdChangeRequestMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_active_risk_threshold_change_request_message(&sent);
  assert(encode_active_risk_threshold_change_request_message(&sent, wire, 0) == 34);
  assert(decode_active_risk_threshold_change_request_message(&got, wire, 0) == 34);
  equal_active_risk_threshold_change_request_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_active_risk_threshold_change_request_message(&got, wire, 0) == 34);
  assert(encode_active_risk_threshold_change_request_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Active Risk Acknowledgement Request Message: 34 bytes ------------------- */

/* ActiveRiskAcknowledgementRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];  /* bytes 0 to 19 */
  uint8_t underlier[6];   /* bytes 20 to 25 */
  uint8_t efid[4];        /* bytes 26 to 29 */
  uint8_t quantity[4];    /* bytes 30 to 33 */
} ActiveRiskAcknowledgementRequestMessage;

/* any Active Risk Acknowledgement Request Message at all: every byte one the checker chooses */
static void any_active_risk_acknowledgement_request_message(ActiveRiskAcknowledgementRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
}

/* Active Risk Acknowledgement Request Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_active_risk_acknowledgement_request_message(const ActiveRiskAcknowledgementRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Active Risk Acknowledgement Request Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_active_risk_acknowledgement_request_message(ActiveRiskAcknowledgementRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Active Risk Acknowledgement Request Message is what was written, byte for byte */
static void equal_active_risk_acknowledgement_request_message(const ActiveRiskAcknowledgementRequestMessage *read, const ActiveRiskAcknowledgementRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier[i] == written->underlier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid[i] == written->efid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Active Risk Acknowledgement Request Message: written and read back, then read and written back */
static void check_active_risk_acknowledgement_request_message(void) {
  ActiveRiskAcknowledgementRequestMessage sent;
  ActiveRiskAcknowledgementRequestMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_active_risk_acknowledgement_request_message(&sent);
  assert(encode_active_risk_acknowledgement_request_message(&sent, wire, 0) == 34);
  assert(decode_active_risk_acknowledgement_request_message(&got, wire, 0) == 34);
  equal_active_risk_acknowledgement_request_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_active_risk_acknowledgement_request_message(&got, wire, 0) == 34);
  assert(encode_active_risk_acknowledgement_request_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Volume Threshold Change Request Message: 44 bytes -------------------- */

/* CPVolumeThresholdChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];               /* bytes 0 to 19 */
  uint8_t underlier_optional[6];       /* bytes 20 to 25 */
  uint8_t efid_optional[4];            /* bytes 26 to 29 */
  uint8_t risk_group_id[2];            /* bytes 30 to 31 */
  uint8_t volume[8];                   /* bytes 32 to 39 */
  uint8_t period_in_milli_seconds[4];  /* bytes 40 to 43 */
} CpVolumeThresholdChangeRequestMessage;

/* any Cp Volume Threshold Change Request Message at all: every byte one the checker chooses */
static void any_cp_volume_threshold_change_request_message(CpVolumeThresholdChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = arbitrary(); }
}

/* Cp Volume Threshold Change Request Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_cp_volume_threshold_change_request_message(const CpVolumeThresholdChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->period_in_milli_seconds[i]; }

  return at;
}

/* Cp Volume Threshold Change Request Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_cp_volume_threshold_change_request_message(CpVolumeThresholdChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Volume Threshold Change Request Message is what was written, byte for byte */
static void equal_cp_volume_threshold_change_request_message(const CpVolumeThresholdChangeRequestMessage *read, const CpVolumeThresholdChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->period_in_milli_seconds[i] == written->period_in_milli_seconds[i]); }
}

/* Cp Volume Threshold Change Request Message: written and read back, then read and written back */
static void check_cp_volume_threshold_change_request_message(void) {
  CpVolumeThresholdChangeRequestMessage sent;
  CpVolumeThresholdChangeRequestMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_cp_volume_threshold_change_request_message(&sent);
  assert(encode_cp_volume_threshold_change_request_message(&sent, wire, 0) == 44);
  assert(decode_cp_volume_threshold_change_request_message(&got, wire, 0) == 44);
  equal_cp_volume_threshold_change_request_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_volume_threshold_change_request_message(&got, wire, 0) == 44);
  assert(encode_cp_volume_threshold_change_request_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Executed Notional Threshold Change Request Message: 44 bytes --------- */

/* CPExecutedNotionalThresholdChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];               /* bytes 0 to 19 */
  uint8_t underlier_optional[6];       /* bytes 20 to 25 */
  uint8_t efid_optional[4];            /* bytes 26 to 29 */
  uint8_t risk_group_id[2];            /* bytes 30 to 31 */
  uint8_t price_in_dollars[8];         /* bytes 32 to 39 */
  uint8_t period_in_milli_seconds[4];  /* bytes 40 to 43 */
} CpExecutedNotionalThresholdChangeRequestMessage;

/* any Cp Executed Notional Threshold Change Request Message at all: every byte one the checker chooses */
static void any_cp_executed_notional_threshold_change_request_message(CpExecutedNotionalThresholdChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = arbitrary(); }
}

/* Cp Executed Notional Threshold Change Request Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_cp_executed_notional_threshold_change_request_message(const CpExecutedNotionalThresholdChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_in_dollars[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->period_in_milli_seconds[i]; }

  return at;
}

/* Cp Executed Notional Threshold Change Request Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_cp_executed_notional_threshold_change_request_message(CpExecutedNotionalThresholdChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Executed Notional Threshold Change Request Message is what was written, byte for byte */
static void equal_cp_executed_notional_threshold_change_request_message(const CpExecutedNotionalThresholdChangeRequestMessage *read, const CpExecutedNotionalThresholdChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_in_dollars[i] == written->price_in_dollars[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->period_in_milli_seconds[i] == written->period_in_milli_seconds[i]); }
}

/* Cp Executed Notional Threshold Change Request Message: written and read back, then read and written back */
static void check_cp_executed_notional_threshold_change_request_message(void) {
  CpExecutedNotionalThresholdChangeRequestMessage sent;
  CpExecutedNotionalThresholdChangeRequestMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_cp_executed_notional_threshold_change_request_message(&sent);
  assert(encode_cp_executed_notional_threshold_change_request_message(&sent, wire, 0) == 44);
  assert(decode_cp_executed_notional_threshold_change_request_message(&got, wire, 0) == 44);
  equal_cp_executed_notional_threshold_change_request_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_executed_notional_threshold_change_request_message(&got, wire, 0) == 44);
  assert(encode_cp_executed_notional_threshold_change_request_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Total Executions Threshold Change Request Message: 40 bytes ---------- */

/* CPTotalExecutionsThresholdChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];               /* bytes 0 to 19 */
  uint8_t underlier_optional[6];       /* bytes 20 to 25 */
  uint8_t efid_optional[4];            /* bytes 26 to 29 */
  uint8_t risk_group_id[2];            /* bytes 30 to 31 */
  uint8_t total_executions[4];         /* bytes 32 to 35 */
  uint8_t period_in_milli_seconds[4];  /* bytes 36 to 39 */
} CpTotalExecutionsThresholdChangeRequestMessage;

/* any Cp Total Executions Threshold Change Request Message at all: every byte one the checker chooses */
static void any_cp_total_executions_threshold_change_request_message(CpTotalExecutionsThresholdChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_executions[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = arbitrary(); }
}

/* Cp Total Executions Threshold Change Request Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_cp_total_executions_threshold_change_request_message(const CpTotalExecutionsThresholdChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_executions[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->period_in_milli_seconds[i]; }

  return at;
}

/* Cp Total Executions Threshold Change Request Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_cp_total_executions_threshold_change_request_message(CpTotalExecutionsThresholdChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_executions[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Total Executions Threshold Change Request Message is what was written, byte for byte */
static void equal_cp_total_executions_threshold_change_request_message(const CpTotalExecutionsThresholdChangeRequestMessage *read, const CpTotalExecutionsThresholdChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_executions[i] == written->total_executions[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->period_in_milli_seconds[i] == written->period_in_milli_seconds[i]); }
}

/* Cp Total Executions Threshold Change Request Message: written and read back, then read and written back */
static void check_cp_total_executions_threshold_change_request_message(void) {
  CpTotalExecutionsThresholdChangeRequestMessage sent;
  CpTotalExecutionsThresholdChangeRequestMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_cp_total_executions_threshold_change_request_message(&sent);
  assert(encode_cp_total_executions_threshold_change_request_message(&sent, wire, 0) == 40);
  assert(decode_cp_total_executions_threshold_change_request_message(&got, wire, 0) == 40);
  equal_cp_total_executions_threshold_change_request_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_total_executions_threshold_change_request_message(&got, wire, 0) == 40);
  assert(encode_cp_total_executions_threshold_change_request_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Percent Outstanding Contracts Threshold Change Request Message: 38 bytes ---- */

/* CPPercentOutstandingContractsThresholdChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];               /* bytes 0 to 19 */
  uint8_t underlier_optional[6];       /* bytes 20 to 25 */
  uint8_t efid_optional[4];            /* bytes 26 to 29 */
  uint8_t percent[4];                  /* bytes 30 to 33 */
  uint8_t period_in_milli_seconds[4];  /* bytes 34 to 37 */
} CpPercentOutstandingContractsThresholdChangeRequestMessage;

/* any Cp Percent Outstanding Contracts Threshold Change Request Message at all: every byte one the checker chooses */
static void any_cp_percent_outstanding_contracts_threshold_change_request_message(CpPercentOutstandingContractsThresholdChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->percent[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = arbitrary(); }
}

/* Cp Percent Outstanding Contracts Threshold Change Request Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_cp_percent_outstanding_contracts_threshold_change_request_message(const CpPercentOutstandingContractsThresholdChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->percent[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->period_in_milli_seconds[i]; }

  return at;
}

/* Cp Percent Outstanding Contracts Threshold Change Request Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_cp_percent_outstanding_contracts_threshold_change_request_message(CpPercentOutstandingContractsThresholdChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->percent[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Percent Outstanding Contracts Threshold Change Request Message is what was written, byte for byte */
static void equal_cp_percent_outstanding_contracts_threshold_change_request_message(const CpPercentOutstandingContractsThresholdChangeRequestMessage *read, const CpPercentOutstandingContractsThresholdChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->percent[i] == written->percent[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->period_in_milli_seconds[i] == written->period_in_milli_seconds[i]); }
}

/* Cp Percent Outstanding Contracts Threshold Change Request Message: written and read back, then read and written back */
static void check_cp_percent_outstanding_contracts_threshold_change_request_message(void) {
  CpPercentOutstandingContractsThresholdChangeRequestMessage sent;
  CpPercentOutstandingContractsThresholdChangeRequestMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_cp_percent_outstanding_contracts_threshold_change_request_message(&sent);
  assert(encode_cp_percent_outstanding_contracts_threshold_change_request_message(&sent, wire, 0) == 38);
  assert(decode_cp_percent_outstanding_contracts_threshold_change_request_message(&got, wire, 0) == 38);
  equal_cp_percent_outstanding_contracts_threshold_change_request_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_percent_outstanding_contracts_threshold_change_request_message(&got, wire, 0) == 38);
  assert(encode_cp_percent_outstanding_contracts_threshold_change_request_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Breach Count Threshold Change Request Message: 40 bytes -------------- */

/* CPBreachCountThresholdChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];               /* bytes 0 to 19 */
  uint8_t underlier_optional[6];       /* bytes 20 to 25 */
  uint8_t efid_optional[4];            /* bytes 26 to 29 */
  uint8_t risk_group_id[2];            /* bytes 30 to 31 */
  uint8_t count[4];                    /* bytes 32 to 35 */
  uint8_t period_in_milli_seconds[4];  /* bytes 36 to 39 */
} CpBreachCountThresholdChangeRequestMessage;

/* any Cp Breach Count Threshold Change Request Message at all: every byte one the checker chooses */
static void any_cp_breach_count_threshold_change_request_message(CpBreachCountThresholdChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = arbitrary(); }
}

/* Cp Breach Count Threshold Change Request Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_cp_breach_count_threshold_change_request_message(const CpBreachCountThresholdChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->period_in_milli_seconds[i]; }

  return at;
}

/* Cp Breach Count Threshold Change Request Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_cp_breach_count_threshold_change_request_message(CpBreachCountThresholdChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Breach Count Threshold Change Request Message is what was written, byte for byte */
static void equal_cp_breach_count_threshold_change_request_message(const CpBreachCountThresholdChangeRequestMessage *read, const CpBreachCountThresholdChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->count[i] == written->count[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->period_in_milli_seconds[i] == written->period_in_milli_seconds[i]); }
}

/* Cp Breach Count Threshold Change Request Message: written and read back, then read and written back */
static void check_cp_breach_count_threshold_change_request_message(void) {
  CpBreachCountThresholdChangeRequestMessage sent;
  CpBreachCountThresholdChangeRequestMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_cp_breach_count_threshold_change_request_message(&sent);
  assert(encode_cp_breach_count_threshold_change_request_message(&sent, wire, 0) == 40);
  assert(decode_cp_breach_count_threshold_change_request_message(&got, wire, 0) == 40);
  equal_cp_breach_count_threshold_change_request_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_breach_count_threshold_change_request_message(&got, wire, 0) == 40);
  assert(encode_cp_breach_count_threshold_change_request_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Manual Cp Breach Trigger Request Message: 33 bytes ---------------------- */

/* ManualCPBreachTriggerRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];  /* bytes 20 to 25 */
  uint8_t efid_optional[4];       /* bytes 26 to 29 */
  uint8_t risk_group_id[2];       /* bytes 30 to 31 */
  uint8_t send_cancels;           /* byte 32 */
} ManualCpBreachTriggerRequestMessage;

/* any Manual Cp Breach Trigger Request Message at all: every byte one the checker chooses */
static void any_manual_cp_breach_trigger_request_message(ManualCpBreachTriggerRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  record->send_cancels = arbitrary();
}

/* Manual Cp Breach Trigger Request Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_manual_cp_breach_trigger_request_message(const ManualCpBreachTriggerRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  wire[at++] = record->send_cancels;

  return at;
}

/* Manual Cp Breach Trigger Request Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_manual_cp_breach_trigger_request_message(ManualCpBreachTriggerRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  record->send_cancels = wire[at++];

  return at;
}

/* what was read of Manual Cp Breach Trigger Request Message is what was written, byte for byte */
static void equal_manual_cp_breach_trigger_request_message(const ManualCpBreachTriggerRequestMessage *read, const ManualCpBreachTriggerRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  assert(read->send_cancels == written->send_cancels);
}

/* Manual Cp Breach Trigger Request Message: written and read back, then read and written back */
static void check_manual_cp_breach_trigger_request_message(void) {
  ManualCpBreachTriggerRequestMessage sent;
  ManualCpBreachTriggerRequestMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_manual_cp_breach_trigger_request_message(&sent);
  assert(encode_manual_cp_breach_trigger_request_message(&sent, wire, 0) == 33);
  assert(decode_manual_cp_breach_trigger_request_message(&got, wire, 0) == 33);
  equal_manual_cp_breach_trigger_request_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_manual_cp_breach_trigger_request_message(&got, wire, 0) == 33);
  assert(encode_manual_cp_breach_trigger_request_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Clear Breach Request Message: 28 bytes ------------------------------- */

/* CPClearBreachRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];  /* bytes 0 to 19 */
  uint8_t breach_id[8];   /* bytes 20 to 27 */
} CpClearBreachRequestMessage;

/* any Cp Clear Breach Request Message at all: every byte one the checker chooses */
static void any_cp_clear_breach_request_message(CpClearBreachRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->breach_id[i] = arbitrary(); }
}

/* Cp Clear Breach Request Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_cp_clear_breach_request_message(const CpClearBreachRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->breach_id[i]; }

  return at;
}

/* Cp Clear Breach Request Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_cp_clear_breach_request_message(CpClearBreachRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->breach_id[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Clear Breach Request Message is what was written, byte for byte */
static void equal_cp_clear_breach_request_message(const CpClearBreachRequestMessage *read, const CpClearBreachRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->breach_id[i] == written->breach_id[i]); }
}

/* Cp Clear Breach Request Message: written and read back, then read and written back */
static void check_cp_clear_breach_request_message(void) {
  CpClearBreachRequestMessage sent;
  CpClearBreachRequestMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_cp_clear_breach_request_message(&sent);
  assert(encode_cp_clear_breach_request_message(&sent, wire, 0) == 28);
  assert(decode_cp_clear_breach_request_message(&got, wire, 0) == 28);
  equal_cp_clear_breach_request_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_clear_breach_request_message(&got, wire, 0) == 28);
  assert(encode_cp_clear_breach_request_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Order Allow Iso Orders Change Request Message: 33 bytes ---------- */

/* SingleOrderAllowISOOrdersChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];  /* bytes 20 to 25 */
  uint8_t efid_optional[4];       /* bytes 26 to 29 */
  uint8_t risk_group_id[2];       /* bytes 30 to 31 */
  uint8_t allow_iso_orders;       /* byte 32 */
} SingleOrderAllowIsoOrdersChangeRequestMessage;

/* any Single Order Allow Iso Orders Change Request Message at all: every byte one the checker chooses */
static void any_single_order_allow_iso_orders_change_request_message(SingleOrderAllowIsoOrdersChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  record->allow_iso_orders = arbitrary();
}

/* Single Order Allow Iso Orders Change Request Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_single_order_allow_iso_orders_change_request_message(const SingleOrderAllowIsoOrdersChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  wire[at++] = record->allow_iso_orders;

  return at;
}

/* Single Order Allow Iso Orders Change Request Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_single_order_allow_iso_orders_change_request_message(SingleOrderAllowIsoOrdersChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  record->allow_iso_orders = wire[at++];

  return at;
}

/* what was read of Single Order Allow Iso Orders Change Request Message is what was written, byte for byte */
static void equal_single_order_allow_iso_orders_change_request_message(const SingleOrderAllowIsoOrdersChangeRequestMessage *read, const SingleOrderAllowIsoOrdersChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  assert(read->allow_iso_orders == written->allow_iso_orders);
}

/* Single Order Allow Iso Orders Change Request Message: written and read back, then read and written back */
static void check_single_order_allow_iso_orders_change_request_message(void) {
  SingleOrderAllowIsoOrdersChangeRequestMessage sent;
  SingleOrderAllowIsoOrdersChangeRequestMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_single_order_allow_iso_orders_change_request_message(&sent);
  assert(encode_single_order_allow_iso_orders_change_request_message(&sent, wire, 0) == 33);
  assert(decode_single_order_allow_iso_orders_change_request_message(&got, wire, 0) == 33);
  equal_single_order_allow_iso_orders_change_request_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_single_order_allow_iso_orders_change_request_message(&got, wire, 0) == 33);
  assert(encode_single_order_allow_iso_orders_change_request_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Order Allow Orders In Crossed Market Change Request Message: 33 bytes ---- */

/* SingleOrderAllowOrdersInCrossedMarketChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];  /* bytes 20 to 25 */
  uint8_t efid_optional[4];       /* bytes 26 to 29 */
  uint8_t risk_group_id[2];       /* bytes 30 to 31 */
  uint8_t allow_orders;           /* byte 32 */
} SingleOrderAllowOrdersInCrossedMarketChangeRequestMessage;

/* any Single Order Allow Orders In Crossed Market Change Request Message at all: every byte one the checker chooses */
static void any_single_order_allow_orders_in_crossed_market_change_request_message(SingleOrderAllowOrdersInCrossedMarketChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  record->allow_orders = arbitrary();
}

/* Single Order Allow Orders In Crossed Market Change Request Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_single_order_allow_orders_in_crossed_market_change_request_message(const SingleOrderAllowOrdersInCrossedMarketChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  wire[at++] = record->allow_orders;

  return at;
}

/* Single Order Allow Orders In Crossed Market Change Request Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_single_order_allow_orders_in_crossed_market_change_request_message(SingleOrderAllowOrdersInCrossedMarketChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  record->allow_orders = wire[at++];

  return at;
}

/* what was read of Single Order Allow Orders In Crossed Market Change Request Message is what was written, byte for byte */
static void equal_single_order_allow_orders_in_crossed_market_change_request_message(const SingleOrderAllowOrdersInCrossedMarketChangeRequestMessage *read, const SingleOrderAllowOrdersInCrossedMarketChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  assert(read->allow_orders == written->allow_orders);
}

/* Single Order Allow Orders In Crossed Market Change Request Message: written and read back, then read and written back */
static void check_single_order_allow_orders_in_crossed_market_change_request_message(void) {
  SingleOrderAllowOrdersInCrossedMarketChangeRequestMessage sent;
  SingleOrderAllowOrdersInCrossedMarketChangeRequestMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_single_order_allow_orders_in_crossed_market_change_request_message(&sent);
  assert(encode_single_order_allow_orders_in_crossed_market_change_request_message(&sent, wire, 0) == 33);
  assert(decode_single_order_allow_orders_in_crossed_market_change_request_message(&got, wire, 0) == 33);
  equal_single_order_allow_orders_in_crossed_market_change_request_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_single_order_allow_orders_in_crossed_market_change_request_message(&got, wire, 0) == 33);
  assert(encode_single_order_allow_orders_in_crossed_market_change_request_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Order Max Notional Change Request Message: 40 bytes -------------- */

/* SingleOrderMaxNotionalChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];               /* bytes 0 to 19 */
  uint8_t underlier_optional[6];       /* bytes 20 to 25 */
  uint8_t efid_optional[4];            /* bytes 26 to 29 */
  uint8_t risk_group_id[2];            /* bytes 30 to 31 */
  uint8_t max_notional_in_dollars[8];  /* bytes 32 to 39 */
} SingleOrderMaxNotionalChangeRequestMessage;

/* any Single Order Max Notional Change Request Message at all: every byte one the checker chooses */
static void any_single_order_max_notional_change_request_message(SingleOrderMaxNotionalChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_notional_in_dollars[i] = arbitrary(); }
}

/* Single Order Max Notional Change Request Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_single_order_max_notional_change_request_message(const SingleOrderMaxNotionalChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_notional_in_dollars[i]; }

  return at;
}

/* Single Order Max Notional Change Request Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_single_order_max_notional_change_request_message(SingleOrderMaxNotionalChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_notional_in_dollars[i] = wire[at++]; }

  return at;
}

/* what was read of Single Order Max Notional Change Request Message is what was written, byte for byte */
static void equal_single_order_max_notional_change_request_message(const SingleOrderMaxNotionalChangeRequestMessage *read, const SingleOrderMaxNotionalChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_notional_in_dollars[i] == written->max_notional_in_dollars[i]); }
}

/* Single Order Max Notional Change Request Message: written and read back, then read and written back */
static void check_single_order_max_notional_change_request_message(void) {
  SingleOrderMaxNotionalChangeRequestMessage sent;
  SingleOrderMaxNotionalChangeRequestMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_single_order_max_notional_change_request_message(&sent);
  assert(encode_single_order_max_notional_change_request_message(&sent, wire, 0) == 40);
  assert(decode_single_order_max_notional_change_request_message(&got, wire, 0) == 40);
  equal_single_order_max_notional_change_request_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_single_order_max_notional_change_request_message(&got, wire, 0) == 40);
  assert(encode_single_order_max_notional_change_request_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Order Max Contracts Change Request Message: 36 bytes ------------- */

/* SingleOrderMaxContractsChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];  /* bytes 20 to 25 */
  uint8_t efid_optional[4];       /* bytes 26 to 29 */
  uint8_t risk_group_id[2];       /* bytes 30 to 31 */
  uint8_t max_contracts[4];       /* bytes 32 to 35 */
} SingleOrderMaxContractsChangeRequestMessage;

/* any Single Order Max Contracts Change Request Message at all: every byte one the checker chooses */
static void any_single_order_max_contracts_change_request_message(SingleOrderMaxContractsChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_contracts[i] = arbitrary(); }
}

/* Single Order Max Contracts Change Request Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_single_order_max_contracts_change_request_message(const SingleOrderMaxContractsChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_contracts[i]; }

  return at;
}

/* Single Order Max Contracts Change Request Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_single_order_max_contracts_change_request_message(SingleOrderMaxContractsChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_contracts[i] = wire[at++]; }

  return at;
}

/* what was read of Single Order Max Contracts Change Request Message is what was written, byte for byte */
static void equal_single_order_max_contracts_change_request_message(const SingleOrderMaxContractsChangeRequestMessage *read, const SingleOrderMaxContractsChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_contracts[i] == written->max_contracts[i]); }
}

/* Single Order Max Contracts Change Request Message: written and read back, then read and written back */
static void check_single_order_max_contracts_change_request_message(void) {
  SingleOrderMaxContractsChangeRequestMessage sent;
  SingleOrderMaxContractsChangeRequestMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_single_order_max_contracts_change_request_message(&sent);
  assert(encode_single_order_max_contracts_change_request_message(&sent, wire, 0) == 36);
  assert(decode_single_order_max_contracts_change_request_message(&got, wire, 0) == 36);
  equal_single_order_max_contracts_change_request_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_single_order_max_contracts_change_request_message(&got, wire, 0) == 36);
  assert(encode_single_order_max_contracts_change_request_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Order Allow Market Orders Change Request Message: 33 bytes ------- */

/* SingleOrderAllowMarketOrdersChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];  /* bytes 20 to 25 */
  uint8_t efid_optional[4];       /* bytes 26 to 29 */
  uint8_t risk_group_id[2];       /* bytes 30 to 31 */
  uint8_t allow_market_orders;    /* byte 32 */
} SingleOrderAllowMarketOrdersChangeRequestMessage;

/* any Single Order Allow Market Orders Change Request Message at all: every byte one the checker chooses */
static void any_single_order_allow_market_orders_change_request_message(SingleOrderAllowMarketOrdersChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  record->allow_market_orders = arbitrary();
}

/* Single Order Allow Market Orders Change Request Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_single_order_allow_market_orders_change_request_message(const SingleOrderAllowMarketOrdersChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  wire[at++] = record->allow_market_orders;

  return at;
}

/* Single Order Allow Market Orders Change Request Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_single_order_allow_market_orders_change_request_message(SingleOrderAllowMarketOrdersChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  record->allow_market_orders = wire[at++];

  return at;
}

/* what was read of Single Order Allow Market Orders Change Request Message is what was written, byte for byte */
static void equal_single_order_allow_market_orders_change_request_message(const SingleOrderAllowMarketOrdersChangeRequestMessage *read, const SingleOrderAllowMarketOrdersChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  assert(read->allow_market_orders == written->allow_market_orders);
}

/* Single Order Allow Market Orders Change Request Message: written and read back, then read and written back */
static void check_single_order_allow_market_orders_change_request_message(void) {
  SingleOrderAllowMarketOrdersChangeRequestMessage sent;
  SingleOrderAllowMarketOrdersChangeRequestMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_single_order_allow_market_orders_change_request_message(&sent);
  assert(encode_single_order_allow_market_orders_change_request_message(&sent, wire, 0) == 33);
  assert(decode_single_order_allow_market_orders_change_request_message(&got, wire, 0) == 33);
  equal_single_order_allow_market_orders_change_request_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_single_order_allow_market_orders_change_request_message(&got, wire, 0) == 33);
  assert(encode_single_order_allow_market_orders_change_request_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Order Restricted Underlier Change Request Message: 33 bytes ------ */

/* SingleOrderRestrictedUnderlierChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];     /* bytes 0 to 19 */
  uint8_t underlier[6];      /* bytes 20 to 25 */
  uint8_t efid_optional[4];  /* bytes 26 to 29 */
  uint8_t risk_group_id[2];  /* bytes 30 to 31 */
  uint8_t restricted;        /* byte 32 */
} SingleOrderRestrictedUnderlierChangeRequestMessage;

/* any Single Order Restricted Underlier Change Request Message at all: every byte one the checker chooses */
static void any_single_order_restricted_underlier_change_request_message(SingleOrderRestrictedUnderlierChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  record->restricted = arbitrary();
}

/* Single Order Restricted Underlier Change Request Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_single_order_restricted_underlier_change_request_message(const SingleOrderRestrictedUnderlierChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  wire[at++] = record->restricted;

  return at;
}

/* Single Order Restricted Underlier Change Request Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_single_order_restricted_underlier_change_request_message(SingleOrderRestrictedUnderlierChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  record->restricted = wire[at++];

  return at;
}

/* what was read of Single Order Restricted Underlier Change Request Message is what was written, byte for byte */
static void equal_single_order_restricted_underlier_change_request_message(const SingleOrderRestrictedUnderlierChangeRequestMessage *read, const SingleOrderRestrictedUnderlierChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier[i] == written->underlier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  assert(read->restricted == written->restricted);
}

/* Single Order Restricted Underlier Change Request Message: written and read back, then read and written back */
static void check_single_order_restricted_underlier_change_request_message(void) {
  SingleOrderRestrictedUnderlierChangeRequestMessage sent;
  SingleOrderRestrictedUnderlierChangeRequestMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_single_order_restricted_underlier_change_request_message(&sent);
  assert(encode_single_order_restricted_underlier_change_request_message(&sent, wire, 0) == 33);
  assert(decode_single_order_restricted_underlier_change_request_message(&got, wire, 0) == 33);
  equal_single_order_restricted_underlier_change_request_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_single_order_restricted_underlier_change_request_message(&got, wire, 0) == 33);
  assert(encode_single_order_restricted_underlier_change_request_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Gross Notional Threshold Change Request Message: 40 bytes ------------ */

/* CPGrossNotionalThresholdChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];  /* bytes 20 to 25 */
  uint8_t efid_optional[4];       /* bytes 26 to 29 */
  uint8_t risk_group_id[2];       /* bytes 30 to 31 */
  uint8_t price_in_dollars[8];    /* bytes 32 to 39 */
} CpGrossNotionalThresholdChangeRequestMessage;

/* any Cp Gross Notional Threshold Change Request Message at all: every byte one the checker chooses */
static void any_cp_gross_notional_threshold_change_request_message(CpGrossNotionalThresholdChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = arbitrary(); }
}

/* Cp Gross Notional Threshold Change Request Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_cp_gross_notional_threshold_change_request_message(const CpGrossNotionalThresholdChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_in_dollars[i]; }

  return at;
}

/* Cp Gross Notional Threshold Change Request Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_cp_gross_notional_threshold_change_request_message(CpGrossNotionalThresholdChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Gross Notional Threshold Change Request Message is what was written, byte for byte */
static void equal_cp_gross_notional_threshold_change_request_message(const CpGrossNotionalThresholdChangeRequestMessage *read, const CpGrossNotionalThresholdChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_in_dollars[i] == written->price_in_dollars[i]); }
}

/* Cp Gross Notional Threshold Change Request Message: written and read back, then read and written back */
static void check_cp_gross_notional_threshold_change_request_message(void) {
  CpGrossNotionalThresholdChangeRequestMessage sent;
  CpGrossNotionalThresholdChangeRequestMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_cp_gross_notional_threshold_change_request_message(&sent);
  assert(encode_cp_gross_notional_threshold_change_request_message(&sent, wire, 0) == 40);
  assert(decode_cp_gross_notional_threshold_change_request_message(&got, wire, 0) == 40);
  equal_cp_gross_notional_threshold_change_request_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_gross_notional_threshold_change_request_message(&got, wire, 0) == 40);
  assert(encode_cp_gross_notional_threshold_change_request_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Market Order Gross Notional Threshold Change Request Message: 40 bytes ---- */

/* CPMarketOrderGrossNotionalThresholdChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];  /* bytes 20 to 25 */
  uint8_t efid_optional[4];       /* bytes 26 to 29 */
  uint8_t risk_group_id[2];       /* bytes 30 to 31 */
  uint8_t price_in_dollars[8];    /* bytes 32 to 39 */
} CpMarketOrderGrossNotionalThresholdChangeRequestMessage;

/* any Cp Market Order Gross Notional Threshold Change Request Message at all: every byte one the checker chooses */
static void any_cp_market_order_gross_notional_threshold_change_request_message(CpMarketOrderGrossNotionalThresholdChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = arbitrary(); }
}

/* Cp Market Order Gross Notional Threshold Change Request Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_cp_market_order_gross_notional_threshold_change_request_message(const CpMarketOrderGrossNotionalThresholdChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_in_dollars[i]; }

  return at;
}

/* Cp Market Order Gross Notional Threshold Change Request Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_cp_market_order_gross_notional_threshold_change_request_message(CpMarketOrderGrossNotionalThresholdChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Market Order Gross Notional Threshold Change Request Message is what was written, byte for byte */
static void equal_cp_market_order_gross_notional_threshold_change_request_message(const CpMarketOrderGrossNotionalThresholdChangeRequestMessage *read, const CpMarketOrderGrossNotionalThresholdChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_in_dollars[i] == written->price_in_dollars[i]); }
}

/* Cp Market Order Gross Notional Threshold Change Request Message: written and read back, then read and written back */
static void check_cp_market_order_gross_notional_threshold_change_request_message(void) {
  CpMarketOrderGrossNotionalThresholdChangeRequestMessage sent;
  CpMarketOrderGrossNotionalThresholdChangeRequestMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_cp_market_order_gross_notional_threshold_change_request_message(&sent);
  assert(encode_cp_market_order_gross_notional_threshold_change_request_message(&sent, wire, 0) == 40);
  assert(decode_cp_market_order_gross_notional_threshold_change_request_message(&got, wire, 0) == 40);
  equal_cp_market_order_gross_notional_threshold_change_request_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_market_order_gross_notional_threshold_change_request_message(&got, wire, 0) == 40);
  assert(encode_cp_market_order_gross_notional_threshold_change_request_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Net Notional Threshold Change Request Message: 40 bytes -------------- */

/* CPNetNotionalThresholdChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];  /* bytes 20 to 25 */
  uint8_t efid_optional[4];       /* bytes 26 to 29 */
  uint8_t risk_group_id[2];       /* bytes 30 to 31 */
  uint8_t price_in_dollars[8];    /* bytes 32 to 39 */
} CpNetNotionalThresholdChangeRequestMessage;

/* any Cp Net Notional Threshold Change Request Message at all: every byte one the checker chooses */
static void any_cp_net_notional_threshold_change_request_message(CpNetNotionalThresholdChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = arbitrary(); }
}

/* Cp Net Notional Threshold Change Request Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_cp_net_notional_threshold_change_request_message(const CpNetNotionalThresholdChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_in_dollars[i]; }

  return at;
}

/* Cp Net Notional Threshold Change Request Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_cp_net_notional_threshold_change_request_message(CpNetNotionalThresholdChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Net Notional Threshold Change Request Message is what was written, byte for byte */
static void equal_cp_net_notional_threshold_change_request_message(const CpNetNotionalThresholdChangeRequestMessage *read, const CpNetNotionalThresholdChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_in_dollars[i] == written->price_in_dollars[i]); }
}

/* Cp Net Notional Threshold Change Request Message: written and read back, then read and written back */
static void check_cp_net_notional_threshold_change_request_message(void) {
  CpNetNotionalThresholdChangeRequestMessage sent;
  CpNetNotionalThresholdChangeRequestMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_cp_net_notional_threshold_change_request_message(&sent);
  assert(encode_cp_net_notional_threshold_change_request_message(&sent, wire, 0) == 40);
  assert(decode_cp_net_notional_threshold_change_request_message(&got, wire, 0) == 40);
  equal_cp_net_notional_threshold_change_request_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_net_notional_threshold_change_request_message(&got, wire, 0) == 40);
  assert(encode_cp_net_notional_threshold_change_request_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Market Order Net Notional Threshold Change Request Message: 40 bytes ---- */

/* CPMarketOrderNetNotionalThresholdChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];  /* bytes 20 to 25 */
  uint8_t efid_optional[4];       /* bytes 26 to 29 */
  uint8_t risk_group_id[2];       /* bytes 30 to 31 */
  uint8_t price_in_dollars[8];    /* bytes 32 to 39 */
} CpMarketOrderNetNotionalThresholdChangeRequestMessage;

/* any Cp Market Order Net Notional Threshold Change Request Message at all: every byte one the checker chooses */
static void any_cp_market_order_net_notional_threshold_change_request_message(CpMarketOrderNetNotionalThresholdChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = arbitrary(); }
}

/* Cp Market Order Net Notional Threshold Change Request Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_cp_market_order_net_notional_threshold_change_request_message(const CpMarketOrderNetNotionalThresholdChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_in_dollars[i]; }

  return at;
}

/* Cp Market Order Net Notional Threshold Change Request Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_cp_market_order_net_notional_threshold_change_request_message(CpMarketOrderNetNotionalThresholdChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Market Order Net Notional Threshold Change Request Message is what was written, byte for byte */
static void equal_cp_market_order_net_notional_threshold_change_request_message(const CpMarketOrderNetNotionalThresholdChangeRequestMessage *read, const CpMarketOrderNetNotionalThresholdChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_in_dollars[i] == written->price_in_dollars[i]); }
}

/* Cp Market Order Net Notional Threshold Change Request Message: written and read back, then read and written back */
static void check_cp_market_order_net_notional_threshold_change_request_message(void) {
  CpMarketOrderNetNotionalThresholdChangeRequestMessage sent;
  CpMarketOrderNetNotionalThresholdChangeRequestMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_cp_market_order_net_notional_threshold_change_request_message(&sent);
  assert(encode_cp_market_order_net_notional_threshold_change_request_message(&sent, wire, 0) == 40);
  assert(decode_cp_market_order_net_notional_threshold_change_request_message(&got, wire, 0) == 40);
  equal_cp_market_order_net_notional_threshold_change_request_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_market_order_net_notional_threshold_change_request_message(&got, wire, 0) == 40);
  assert(encode_cp_market_order_net_notional_threshold_change_request_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Duplicate Order Threshold Change Request Message: 41 bytes ----------- */

/* CPDuplicateOrderThresholdChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];                          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];                  /* bytes 20 to 25 */
  uint8_t efid_optional[4];                       /* bytes 26 to 29 */
  uint8_t risk_group_id[2];                       /* bytes 30 to 31 */
  uint8_t max_dup_orders[4];                      /* bytes 32 to 35 */
  uint8_t use_order_price_in_dup_check_optional;  /* byte 36 */
  uint8_t period_in_milli_seconds[4];             /* bytes 37 to 40 */
} CpDuplicateOrderThresholdChangeRequestMessage;

/* any Cp Duplicate Order Threshold Change Request Message at all: every byte one the checker chooses */
static void any_cp_duplicate_order_threshold_change_request_message(CpDuplicateOrderThresholdChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_dup_orders[i] = arbitrary(); }
  record->use_order_price_in_dup_check_optional = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = arbitrary(); }
}

/* Cp Duplicate Order Threshold Change Request Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_cp_duplicate_order_threshold_change_request_message(const CpDuplicateOrderThresholdChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_dup_orders[i]; }
  wire[at++] = record->use_order_price_in_dup_check_optional;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->period_in_milli_seconds[i]; }

  return at;
}

/* Cp Duplicate Order Threshold Change Request Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_cp_duplicate_order_threshold_change_request_message(CpDuplicateOrderThresholdChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_dup_orders[i] = wire[at++]; }
  record->use_order_price_in_dup_check_optional = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Duplicate Order Threshold Change Request Message is what was written, byte for byte */
static void equal_cp_duplicate_order_threshold_change_request_message(const CpDuplicateOrderThresholdChangeRequestMessage *read, const CpDuplicateOrderThresholdChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_dup_orders[i] == written->max_dup_orders[i]); }
  assert(read->use_order_price_in_dup_check_optional == written->use_order_price_in_dup_check_optional);
  for (size_t i = 0; i < 4; i++) { assert(read->period_in_milli_seconds[i] == written->period_in_milli_seconds[i]); }
}

/* Cp Duplicate Order Threshold Change Request Message: written and read back, then read and written back */
static void check_cp_duplicate_order_threshold_change_request_message(void) {
  CpDuplicateOrderThresholdChangeRequestMessage sent;
  CpDuplicateOrderThresholdChangeRequestMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_cp_duplicate_order_threshold_change_request_message(&sent);
  assert(encode_cp_duplicate_order_threshold_change_request_message(&sent, wire, 0) == 41);
  assert(decode_cp_duplicate_order_threshold_change_request_message(&got, wire, 0) == 41);
  equal_cp_duplicate_order_threshold_change_request_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_duplicate_order_threshold_change_request_message(&got, wire, 0) == 41);
  assert(encode_cp_duplicate_order_threshold_change_request_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Order Rate Threshold Change Request Message: 40 bytes ---------------- */

/* CPOrderRateThresholdChangeRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];               /* bytes 0 to 19 */
  uint8_t underlier_optional[6];       /* bytes 20 to 25 */
  uint8_t efid_optional[4];            /* bytes 26 to 29 */
  uint8_t risk_group_id[2];            /* bytes 30 to 31 */
  uint8_t max_order_msgs[4];           /* bytes 32 to 35 */
  uint8_t period_in_milli_seconds[4];  /* bytes 36 to 39 */
} CpOrderRateThresholdChangeRequestMessage;

/* any Cp Order Rate Threshold Change Request Message at all: every byte one the checker chooses */
static void any_cp_order_rate_threshold_change_request_message(CpOrderRateThresholdChangeRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_order_msgs[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = arbitrary(); }
}

/* Cp Order Rate Threshold Change Request Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_cp_order_rate_threshold_change_request_message(const CpOrderRateThresholdChangeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_order_msgs[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->period_in_milli_seconds[i]; }

  return at;
}

/* Cp Order Rate Threshold Change Request Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_cp_order_rate_threshold_change_request_message(CpOrderRateThresholdChangeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_order_msgs[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Order Rate Threshold Change Request Message is what was written, byte for byte */
static void equal_cp_order_rate_threshold_change_request_message(const CpOrderRateThresholdChangeRequestMessage *read, const CpOrderRateThresholdChangeRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_order_msgs[i] == written->max_order_msgs[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->period_in_milli_seconds[i] == written->period_in_milli_seconds[i]); }
}

/* Cp Order Rate Threshold Change Request Message: written and read back, then read and written back */
static void check_cp_order_rate_threshold_change_request_message(void) {
  CpOrderRateThresholdChangeRequestMessage sent;
  CpOrderRateThresholdChangeRequestMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_cp_order_rate_threshold_change_request_message(&sent);
  assert(encode_cp_order_rate_threshold_change_request_message(&sent, wire, 0) == 40);
  assert(decode_cp_order_rate_threshold_change_request_message(&got, wire, 0) == 40);
  equal_cp_order_rate_threshold_change_request_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_order_rate_threshold_change_request_message(&got, wire, 0) == 40);
  assert(encode_cp_order_rate_threshold_change_request_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Clear All Breaches Request Message: 20 bytes ------------------------- */

/* CPClearAllBreachesRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];  /* bytes 0 to 19 */
} CpClearAllBreachesRequestMessage;

/* any Cp Clear All Breaches Request Message at all: every byte one the checker chooses */
static void any_cp_clear_all_breaches_request_message(CpClearAllBreachesRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
}

/* Cp Clear All Breaches Request Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_cp_clear_all_breaches_request_message(const CpClearAllBreachesRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }

  return at;
}

/* Cp Clear All Breaches Request Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_cp_clear_all_breaches_request_message(CpClearAllBreachesRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Clear All Breaches Request Message is what was written, byte for byte */
static void equal_cp_clear_all_breaches_request_message(const CpClearAllBreachesRequestMessage *read, const CpClearAllBreachesRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
}

/* Cp Clear All Breaches Request Message: written and read back, then read and written back */
static void check_cp_clear_all_breaches_request_message(void) {
  CpClearAllBreachesRequestMessage sent;
  CpClearAllBreachesRequestMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_cp_clear_all_breaches_request_message(&sent);
  assert(encode_cp_clear_all_breaches_request_message(&sent, wire, 0) == 20);
  assert(decode_cp_clear_all_breaches_request_message(&got, wire, 0) == 20);
  equal_cp_clear_all_breaches_request_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_clear_all_breaches_request_message(&got, wire, 0) == 20);
  assert(encode_cp_clear_all_breaches_request_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Clear All Breaches By Efid Or Underlier Request Message: 30 bytes ---- */

/* CPClearAllBreachesByEFIDOrUnderlierRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];  /* bytes 20 to 25 */
  uint8_t efid_optional[4];       /* bytes 26 to 29 */
} CpClearAllBreachesByEfidOrUnderlierRequestMessage;

/* any Cp Clear All Breaches By Efid Or Underlier Request Message at all: every byte one the checker chooses */
static void any_cp_clear_all_breaches_by_efid_or_underlier_request_message(CpClearAllBreachesByEfidOrUnderlierRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
}

/* Cp Clear All Breaches By Efid Or Underlier Request Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_cp_clear_all_breaches_by_efid_or_underlier_request_message(const CpClearAllBreachesByEfidOrUnderlierRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }

  return at;
}

/* Cp Clear All Breaches By Efid Or Underlier Request Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_cp_clear_all_breaches_by_efid_or_underlier_request_message(CpClearAllBreachesByEfidOrUnderlierRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Clear All Breaches By Efid Or Underlier Request Message is what was written, byte for byte */
static void equal_cp_clear_all_breaches_by_efid_or_underlier_request_message(const CpClearAllBreachesByEfidOrUnderlierRequestMessage *read, const CpClearAllBreachesByEfidOrUnderlierRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
}

/* Cp Clear All Breaches By Efid Or Underlier Request Message: written and read back, then read and written back */
static void check_cp_clear_all_breaches_by_efid_or_underlier_request_message(void) {
  CpClearAllBreachesByEfidOrUnderlierRequestMessage sent;
  CpClearAllBreachesByEfidOrUnderlierRequestMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_cp_clear_all_breaches_by_efid_or_underlier_request_message(&sent);
  assert(encode_cp_clear_all_breaches_by_efid_or_underlier_request_message(&sent, wire, 0) == 30);
  assert(decode_cp_clear_all_breaches_by_efid_or_underlier_request_message(&got, wire, 0) == 30);
  equal_cp_clear_all_breaches_by_efid_or_underlier_request_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_clear_all_breaches_by_efid_or_underlier_request_message(&got, wire, 0) == 30);
  assert(encode_cp_clear_all_breaches_by_efid_or_underlier_request_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Active Risk Acknowledge All Request Message: 30 bytes ------------------- */

/* ActiveRiskAcknowledgeAllRequestMessage */
typedef struct {
  uint8_t cl_ord_id[20];  /* bytes 0 to 19 */
  uint8_t underlier[6];   /* bytes 20 to 25 */
  uint8_t efid[4];        /* bytes 26 to 29 */
} ActiveRiskAcknowledgeAllRequestMessage;

/* any Active Risk Acknowledge All Request Message at all: every byte one the checker chooses */
static void any_active_risk_acknowledge_all_request_message(ActiveRiskAcknowledgeAllRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid[i] = arbitrary(); }
}

/* Active Risk Acknowledge All Request Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_active_risk_acknowledge_all_request_message(const ActiveRiskAcknowledgeAllRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid[i]; }

  return at;
}

/* Active Risk Acknowledge All Request Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_active_risk_acknowledge_all_request_message(ActiveRiskAcknowledgeAllRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid[i] = wire[at++]; }

  return at;
}

/* what was read of Active Risk Acknowledge All Request Message is what was written, byte for byte */
static void equal_active_risk_acknowledge_all_request_message(const ActiveRiskAcknowledgeAllRequestMessage *read, const ActiveRiskAcknowledgeAllRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier[i] == written->underlier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid[i] == written->efid[i]); }
}

/* Active Risk Acknowledge All Request Message: written and read back, then read and written back */
static void check_active_risk_acknowledge_all_request_message(void) {
  ActiveRiskAcknowledgeAllRequestMessage sent;
  ActiveRiskAcknowledgeAllRequestMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_active_risk_acknowledge_all_request_message(&sent);
  assert(encode_active_risk_acknowledge_all_request_message(&sent, wire, 0) == 30);
  assert(decode_active_risk_acknowledge_all_request_message(&got, wire, 0) == 30);
  equal_active_risk_acknowledge_all_request_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_active_risk_acknowledge_all_request_message(&got, wire, 0) == 30);
  assert(encode_active_risk_acknowledge_all_request_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_common_header();
  check_login_request_message();
  check_replay_request_message();
  check_replay_all_request_message();
  check_stream_request_message();
  check_sbe_header();
  check_risk_settings_query_message();
  check_active_risk_threshold_change_request_message();
  check_active_risk_acknowledgement_request_message();
  check_cp_volume_threshold_change_request_message();
  check_cp_executed_notional_threshold_change_request_message();
  check_cp_total_executions_threshold_change_request_message();
  check_cp_percent_outstanding_contracts_threshold_change_request_message();
  check_cp_breach_count_threshold_change_request_message();
  check_manual_cp_breach_trigger_request_message();
  check_cp_clear_breach_request_message();
  check_single_order_allow_iso_orders_change_request_message();
  check_single_order_allow_orders_in_crossed_market_change_request_message();
  check_single_order_max_notional_change_request_message();
  check_single_order_max_contracts_change_request_message();
  check_single_order_allow_market_orders_change_request_message();
  check_single_order_restricted_underlier_change_request_message();
  check_cp_gross_notional_threshold_change_request_message();
  check_cp_market_order_gross_notional_threshold_change_request_message();
  check_cp_net_notional_threshold_change_request_message();
  check_cp_market_order_net_notional_threshold_change_request_message();
  check_cp_duplicate_order_threshold_change_request_message();
  check_cp_order_rate_threshold_change_request_message();
  check_cp_clear_all_breaches_request_message();
  check_cp_clear_all_breaches_by_efid_or_underlier_request_message();
  check_active_risk_acknowledge_all_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
