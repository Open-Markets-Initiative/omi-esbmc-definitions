// moex/spectra/optinforeplay/Spectra_OptInfoReplay_v6_0_0.c
/*
 * Moscow Exchange SIMBA Spectra Options Instrument Replay
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
 *   - a field read in bits
 *   - a run filling what frames it
 *   - a block whose stated length holds more than its fields
 *   - a run counted by a field
 *   - a field present only on a condition
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

/* ---- Sbe Header: 8 bytes ----------------------------------------------------- */

/* Root block length, message template id, message schema id and schema version */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id[2];   /* bytes 2 to 3 */
  uint8_t schema_id[2];     /* bytes 4 to 5 */
  uint8_t version[2];       /* bytes 6 to 7 */
} SbeHeader;

/* any Sbe Header at all: every byte one the checker chooses */
static void any_sbe_header(SbeHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Sbe Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_sbe_header(const SbeHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->schema_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Sbe Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_sbe_header(SbeHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Sbe Header is what was written, byte for byte */
static void equal_sbe_header(const SbeHeader *read, const SbeHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->schema_id[i] == written->schema_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Sbe Header: written and read back, then read and written back */
static void check_sbe_header(void) {
  SbeHeader sent;
  SbeHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_sbe_header(&sent);
  assert(encode_sbe_header(&sent, wire, 0) == 8);
  assert(decode_sbe_header(&got, wire, 0) == 8);
  equal_sbe_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_sbe_header(&got, wire, 0) == 8);
  assert(encode_sbe_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Reset Message: 4 bytes ----------------------------------------- */

/* SequenceResetMessage */
typedef struct {
  uint8_t new_seq_no[4];  /* bytes 0 to 3 */
} SequenceResetMessage;

/* any Sequence Reset Message at all: every byte one the checker chooses */
static void any_sequence_reset_message(SequenceResetMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->new_seq_no[i] = arbitrary(); }
}

/* Sequence Reset Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_sequence_reset_message(const SequenceResetMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_seq_no[i]; }

  return at;
}

/* Sequence Reset Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_sequence_reset_message(SequenceResetMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->new_seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Sequence Reset Message is what was written, byte for byte */
static void equal_sequence_reset_message(const SequenceResetMessage *read, const SequenceResetMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->new_seq_no[i] == written->new_seq_no[i]); }
}

/* Sequence Reset Message: written and read back, then read and written back */
static void check_sequence_reset_message(void) {
  SequenceResetMessage sent;
  SequenceResetMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_sequence_reset_message(&sent);
  assert(encode_sequence_reset_message(&sent, wire, 0) == 4);
  assert(decode_sequence_reset_message(&got, wire, 0) == 4);
  equal_sequence_reset_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence_reset_message(&got, wire, 0) == 4);
  assert(encode_sequence_reset_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Size: 3 bytes ----------------------------------------------------- */

/* groupSize */
typedef struct {
  uint8_t block_length[2];      /* bytes 0 to 1 */
  uint8_t num_in_group_uint_8;  /* byte 2 */
} GroupSize;

/* any Group Size at all: every byte one the checker chooses */
static void any_group_size(GroupSize *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  record->num_in_group_uint_8 = arbitrary();
}

/* Group Size to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_group_size(const GroupSize *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  wire[at++] = record->num_in_group_uint_8;

  return at;
}

/* Group Size off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_group_size(GroupSize *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  record->num_in_group_uint_8 = wire[at++];

  return at;
}

/* what was read of Group Size is what was written, byte for byte */
static void equal_group_size(const GroupSize *read, const GroupSize *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  assert(read->num_in_group_uint_8 == written->num_in_group_uint_8);
}

/* Group Size: written and read back, then read and written back */
static void check_group_size(void) {
  GroupSize sent;
  GroupSize got;
  uint8_t wire[3];
  uint8_t again[3];

  any_group_size(&sent);
  assert(encode_group_size(&sent, wire, 0) == 3);
  assert(decode_group_size(&got, wire, 0) == 3);
  equal_group_size(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_group_size(&got, wire, 0) == 3);
  assert(encode_group_size(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Session Status Message: 48 bytes -------------------------------- */

/* TradingSessionStatusMessage */
typedef struct {
  uint8_t trad_ses_open_time[8];                                /* bytes 0 to 7 */
  uint8_t trad_ses_close_time[8];                               /* bytes 8 to 15 */
  uint8_t trad_ses_interm_clearing_start_time[8];               /* bytes 16 to 23 */
  uint8_t trad_ses_interm_clearing_end_time[8];                 /* bytes 24 to 31 */
  uint8_t trading_session_id;                                   /* byte 32 */
  uint8_t exchange_trading_session_id_int_32_null_optional[4];  /* bytes 33 to 36 */
  uint8_t trad_ses_status;                                      /* byte 37 */
  uint8_t market_segment_id;                                    /* byte 38 */
  uint8_t trad_ses_event;                                       /* byte 39 */
  uint8_t trade_period_id[8];                                   /* bytes 40 to 47 */
} TradingSessionStatusMessage;

/* any Trading Session Status Message at all: every byte one the checker chooses */
static void any_trading_session_status_message(TradingSessionStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->trad_ses_open_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trad_ses_close_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trad_ses_interm_clearing_start_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trad_ses_interm_clearing_end_time[i] = arbitrary(); }
  record->trading_session_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->exchange_trading_session_id_int_32_null_optional[i] = arbitrary(); }
  record->trad_ses_status = arbitrary();
  record->market_segment_id = arbitrary();
  record->trad_ses_event = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trade_period_id[i] = arbitrary(); }
}

/* Trading Session Status Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_trading_session_status_message(const TradingSessionStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trad_ses_open_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trad_ses_close_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trad_ses_interm_clearing_start_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trad_ses_interm_clearing_end_time[i]; }
  wire[at++] = record->trading_session_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_trading_session_id_int_32_null_optional[i]; }
  wire[at++] = record->trad_ses_status;
  wire[at++] = record->market_segment_id;
  wire[at++] = record->trad_ses_event;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_period_id[i]; }

  return at;
}

/* Trading Session Status Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_trading_session_status_message(TradingSessionStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->trad_ses_open_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trad_ses_close_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trad_ses_interm_clearing_start_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trad_ses_interm_clearing_end_time[i] = wire[at++]; }
  record->trading_session_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->exchange_trading_session_id_int_32_null_optional[i] = wire[at++]; }
  record->trad_ses_status = wire[at++];
  record->market_segment_id = wire[at++];
  record->trad_ses_event = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trade_period_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Session Status Message is what was written, byte for byte */
static void equal_trading_session_status_message(const TradingSessionStatusMessage *read, const TradingSessionStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->trad_ses_open_time[i] == written->trad_ses_open_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trad_ses_close_time[i] == written->trad_ses_close_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trad_ses_interm_clearing_start_time[i] == written->trad_ses_interm_clearing_start_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trad_ses_interm_clearing_end_time[i] == written->trad_ses_interm_clearing_end_time[i]); }
  assert(read->trading_session_id == written->trading_session_id);
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_trading_session_id_int_32_null_optional[i] == written->exchange_trading_session_id_int_32_null_optional[i]); }
  assert(read->trad_ses_status == written->trad_ses_status);
  assert(read->market_segment_id == written->market_segment_id);
  assert(read->trad_ses_event == written->trad_ses_event);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_period_id[i] == written->trade_period_id[i]); }
}

/* Trading Session Status Message: written and read back, then read and written back */
static void check_trading_session_status_message(void) {
  TradingSessionStatusMessage sent;
  TradingSessionStatusMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_trading_session_status_message(&sent);
  assert(encode_trading_session_status_message(&sent, wire, 0) == 48);
  assert(decode_trading_session_status_message(&got, wire, 0) == 48);
  equal_trading_session_status_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_session_status_message(&got, wire, 0) == 48);
  assert(encode_trading_session_status_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Group Status Message: 38 bytes --------------------------------- */

/* SecurityGroupStatusMessage */
typedef struct {
  uint8_t security_group_id[8];          /* bytes 0 to 7 */
  uint8_t halt_type;                     /* byte 8 */
  uint8_t trade_mode_mask[4];            /* bytes 9 to 12 */
  uint8_t group_mask_optional[8];        /* bytes 13 to 20 */
  uint8_t section_id_optional[4];        /* bytes 21 to 24 */
  uint8_t base_contract_id_optional[4];  /* bytes 25 to 28 */
  uint8_t security_trading_status;       /* byte 29 */
  uint8_t status_change_time[8];         /* bytes 30 to 37 */
} SecurityGroupStatusMessage;

/* any Security Group Status Message at all: every byte one the checker chooses */
static void any_security_group_status_message(SecurityGroupStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->security_group_id[i] = arbitrary(); }
  record->halt_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trade_mode_mask[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->group_mask_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->section_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->base_contract_id_optional[i] = arbitrary(); }
  record->security_trading_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->status_change_time[i] = arbitrary(); }
}

/* Security Group Status Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_security_group_status_message(const SecurityGroupStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_group_id[i]; }
  wire[at++] = record->halt_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_mode_mask[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->group_mask_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->section_id_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->base_contract_id_optional[i]; }
  wire[at++] = record->security_trading_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->status_change_time[i]; }

  return at;
}

/* Security Group Status Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_security_group_status_message(SecurityGroupStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->security_group_id[i] = wire[at++]; }
  record->halt_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trade_mode_mask[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->group_mask_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->section_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->base_contract_id_optional[i] = wire[at++]; }
  record->security_trading_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->status_change_time[i] = wire[at++]; }

  return at;
}

/* what was read of Security Group Status Message is what was written, byte for byte */
static void equal_security_group_status_message(const SecurityGroupStatusMessage *read, const SecurityGroupStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->security_group_id[i] == written->security_group_id[i]); }
  assert(read->halt_type == written->halt_type);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_mode_mask[i] == written->trade_mode_mask[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->group_mask_optional[i] == written->group_mask_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->section_id_optional[i] == written->section_id_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->base_contract_id_optional[i] == written->base_contract_id_optional[i]); }
  assert(read->security_trading_status == written->security_trading_status);
  for (size_t i = 0; i < 8; i++) { assert(read->status_change_time[i] == written->status_change_time[i]); }
}

/* Security Group Status Message: written and read back, then read and written back */
static void check_security_group_status_message(void) {
  SecurityGroupStatusMessage sent;
  SecurityGroupStatusMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_security_group_status_message(&sent);
  assert(encode_security_group_status_message(&sent, wire, 0) == 38);
  assert(decode_security_group_status_message(&got, wire, 0) == 38);
  equal_security_group_status_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_security_group_status_message(&got, wire, 0) == 38);
  assert(encode_security_group_status_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_sbe_header();
  check_sequence_reset_message();
  check_group_size();
  check_trading_session_status_message();
  check_security_group_status_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
