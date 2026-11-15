// hkex/hkexsecurities/index/HkexSecurities_Index_v1_44.c
/*
 * Hong Kong Exchanges and Clearing Orion Market Data Cash Index
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

/* ---- Packet Header: 16 bytes ------------------------------------------------- */

/* Omd packet header (no payload compression; byte 3 is Filler) */
typedef struct {
  uint8_t pkt_size[2];   /* bytes 0 to 1 */
  uint8_t msg_count;     /* byte 2 */
  uint8_t filler;        /* byte 3 */
  uint8_t seq_num[4];    /* bytes 4 to 7 */
  uint8_t send_time[8];  /* bytes 8 to 15 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->pkt_size[i] = arbitrary(); }
  record->msg_count = arbitrary();
  record->filler = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = arbitrary(); }
}

/* Packet Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->pkt_size[i]; }
  wire[at++] = record->msg_count;
  wire[at++] = record->filler;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->send_time[i]; }

  return at;
}

/* Packet Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->pkt_size[i] = wire[at++]; }
  record->msg_count = wire[at++];
  record->filler = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->pkt_size[i] == written->pkt_size[i]); }
  assert(read->msg_count == written->msg_count);
  assert(read->filler == written->filler);
  for (size_t i = 0; i < 4; i++) { assert(read->seq_num[i] == written->seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->send_time[i] == written->send_time[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[16];
  uint8_t again[16];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 16);
  assert(decode_packet_header(&got, wire, 0) == 16);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 16);
  assert(encode_packet_header(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Msg Header: 4 bytes ----------------------------------------------------- */

/* Omd message header */
typedef struct {
  uint8_t msg_size[2];  /* bytes 0 to 1 */
  uint8_t msg_type[2];  /* bytes 2 to 3 */
} MsgHeader;

/* any Msg Header at all: every byte one the checker chooses */
static void any_msg_header(MsgHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->msg_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->msg_type[i] = arbitrary(); }
}

/* Msg Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_msg_header(const MsgHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_type[i]; }

  return at;
}

/* Msg Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_msg_header(MsgHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->msg_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->msg_type[i] = wire[at++]; }

  return at;
}

/* what was read of Msg Header is what was written, byte for byte */
static void equal_msg_header(const MsgHeader *read, const MsgHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->msg_size[i] == written->msg_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->msg_type[i] == written->msg_type[i]); }
}

/* Msg Header: written and read back, then read and written back */
static void check_msg_header(void) {
  MsgHeader sent;
  MsgHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_msg_header(&sent);
  assert(encode_msg_header(&sent, wire, 0) == 4);
  assert(decode_msg_header(&got, wire, 0) == 4);
  equal_msg_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_msg_header(&got, wire, 0) == 4);
  assert(encode_msg_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Reset Message: 4 bytes ----------------------------------------- */

/* The Sequence Reset message is sent on each multicast channel at start of day. It may also be sent when there is a need for the rectification of stock reference data before market open. */
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

/* ---- Disaster Recovery Signal Message: 4 bytes ------------------------------- */

/* The Disaster Recovery (DR) Signal message is sent on a dedicated multicast channel whenever a site failover scenario is triggered. */
typedef struct {
  uint8_t dr_status[4];  /* bytes 0 to 3 */
} DisasterRecoverySignalMessage;

/* any Disaster Recovery Signal Message at all: every byte one the checker chooses */
static void any_disaster_recovery_signal_message(DisasterRecoverySignalMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->dr_status[i] = arbitrary(); }
}

/* Disaster Recovery Signal Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_disaster_recovery_signal_message(const DisasterRecoverySignalMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->dr_status[i]; }

  return at;
}

/* Disaster Recovery Signal Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_disaster_recovery_signal_message(DisasterRecoverySignalMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->dr_status[i] = wire[at++]; }

  return at;
}

/* what was read of Disaster Recovery Signal Message is what was written, byte for byte */
static void equal_disaster_recovery_signal_message(const DisasterRecoverySignalMessage *read, const DisasterRecoverySignalMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->dr_status[i] == written->dr_status[i]); }
}

/* Disaster Recovery Signal Message: written and read back, then read and written back */
static void check_disaster_recovery_signal_message(void) {
  DisasterRecoverySignalMessage sent;
  DisasterRecoverySignalMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_disaster_recovery_signal_message(&sent);
  assert(encode_disaster_recovery_signal_message(&sent, wire, 0) == 4);
  assert(decode_disaster_recovery_signal_message(&got, wire, 0) == 4);
  equal_disaster_recovery_signal_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_disaster_recovery_signal_message(&got, wire, 0) == 4);
  assert(encode_disaster_recovery_signal_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Definition Message: 16 bytes -------------------------------------- */

/* The Index Definition message contains the static referential data for the given index and is generated at the start of the business day. May be re-disseminated during trading hours. */
typedef struct {
  uint8_t index_code[11];    /* bytes 0 to 10 */
  uint8_t index_source;      /* byte 11 */
  uint8_t currency_code[3];  /* bytes 12 to 14 */
  uint8_t filler_1;          /* byte 15 */
} IndexDefinitionMessage;

/* any Index Definition Message at all: every byte one the checker chooses */
static void any_index_definition_message(IndexDefinitionMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->index_code[i] = arbitrary(); }
  record->index_source = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = arbitrary(); }
  record->filler_1 = arbitrary();
}

/* Index Definition Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_index_definition_message(const IndexDefinitionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->index_code[i]; }
  wire[at++] = record->index_source;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency_code[i]; }
  wire[at++] = record->filler_1;

  return at;
}

/* Index Definition Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_index_definition_message(IndexDefinitionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->index_code[i] = wire[at++]; }
  record->index_source = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = wire[at++]; }
  record->filler_1 = wire[at++];

  return at;
}

/* what was read of Index Definition Message is what was written, byte for byte */
static void equal_index_definition_message(const IndexDefinitionMessage *read, const IndexDefinitionMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->index_code[i] == written->index_code[i]); }
  assert(read->index_source == written->index_source);
  for (size_t i = 0; i < 3; i++) { assert(read->currency_code[i] == written->currency_code[i]); }
  assert(read->filler_1 == written->filler_1);
}

/* Index Definition Message: written and read back, then read and written back */
static void check_index_definition_message(void) {
  IndexDefinitionMessage sent;
  IndexDefinitionMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_index_definition_message(&sent);
  assert(encode_index_definition_message(&sent, wire, 0) == 16);
  assert(decode_index_definition_message(&got, wire, 0) == 16);
  equal_index_definition_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_index_definition_message(&got, wire, 0) == 16);
  assert(encode_index_definition_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Data Message: 108 bytes ------------------------------------------- */

/* The Index Data message contains all the real-time data for a given index. Fields may be populated with null values to indicate when an update is not provided. */
typedef struct {
  uint8_t index_code[11];           /* bytes 0 to 10 */
  uint8_t index_status;             /* byte 11 */
  uint8_t index_time[8];            /* bytes 12 to 19 */
  uint8_t index_value[8];           /* bytes 20 to 27 */
  uint8_t net_chg_prev_day[8];      /* bytes 28 to 35 */
  uint8_t high_value[8];            /* bytes 36 to 43 */
  uint8_t low_value[8];             /* bytes 44 to 51 */
  uint8_t eas_value[8];             /* bytes 52 to 59 */
  uint8_t index_turnover[8];        /* bytes 60 to 67 */
  uint8_t opening_value[8];         /* bytes 68 to 75 */
  uint8_t closing_value[8];         /* bytes 76 to 83 */
  uint8_t previous_ses_close[8];    /* bytes 84 to 91 */
  uint8_t index_volume[8];          /* bytes 92 to 99 */
  uint8_t net_chg_prev_day_pct[4];  /* bytes 100 to 103 */
  uint8_t exception;                /* byte 104 */
  uint8_t filler_3[3];              /* bytes 105 to 107 */
} IndexDataMessage;

/* any Index Data Message at all: every byte one the checker chooses */
static void any_index_data_message(IndexDataMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->index_code[i] = arbitrary(); }
  record->index_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->index_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->net_chg_prev_day[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->eas_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_turnover[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_ses_close[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->net_chg_prev_day_pct[i] = arbitrary(); }
  record->exception = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = arbitrary(); }
}

/* Index Data Message to the wire: 108 bytes from at, returning where the next byte goes */
static size_t encode_index_data_message(const IndexDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->index_code[i]; }
  wire[at++] = record->index_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->net_chg_prev_day[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->eas_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_turnover[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_ses_close[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->net_chg_prev_day_pct[i]; }
  wire[at++] = record->exception;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_3[i]; }

  return at;
}

/* Index Data Message off the wire: 108 bytes from at, returning where the next byte lies */
static size_t decode_index_data_message(IndexDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->index_code[i] = wire[at++]; }
  record->index_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->index_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->net_chg_prev_day[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->eas_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_turnover[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_ses_close[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->net_chg_prev_day_pct[i] = wire[at++]; }
  record->exception = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = wire[at++]; }

  return at;
}

/* what was read of Index Data Message is what was written, byte for byte */
static void equal_index_data_message(const IndexDataMessage *read, const IndexDataMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->index_code[i] == written->index_code[i]); }
  assert(read->index_status == written->index_status);
  for (size_t i = 0; i < 8; i++) { assert(read->index_time[i] == written->index_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_value[i] == written->index_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->net_chg_prev_day[i] == written->net_chg_prev_day[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_value[i] == written->high_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_value[i] == written->low_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->eas_value[i] == written->eas_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_turnover[i] == written->index_turnover[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_value[i] == written->opening_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_value[i] == written->closing_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_ses_close[i] == written->previous_ses_close[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_volume[i] == written->index_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->net_chg_prev_day_pct[i] == written->net_chg_prev_day_pct[i]); }
  assert(read->exception == written->exception);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
}

/* Index Data Message: written and read back, then read and written back */
static void check_index_data_message(void) {
  IndexDataMessage sent;
  IndexDataMessage got;
  uint8_t wire[108];
  uint8_t again[108];

  any_index_data_message(&sent);
  assert(encode_index_data_message(&sent, wire, 0) == 108);
  assert(decode_index_data_message(&got, wire, 0) == 108);
  equal_index_data_message(&got, &sent);

  for (size_t i = 0; i < 108; i++) { wire[i] = arbitrary(); }
  assert(decode_index_data_message(&got, wire, 0) == 108);
  assert(encode_index_data_message(&got, again, 0) == 108);
  for (size_t i = 0; i < 108; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_msg_header();
  check_sequence_reset_message();
  check_disaster_recovery_signal_message();
  check_index_definition_message();
  check_index_data_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
