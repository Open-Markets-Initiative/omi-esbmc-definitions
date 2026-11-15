// b3/b3derivatives/binaryumdf/B3Derivatives_BinaryUmdf_v2_1.c
/*
 * Brasil, Bolsa, Balcão Binary Unified Market Data Feed
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
 *   - a field read in bits
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

/* ---- Packet Header: 16 bytes ------------------------------------------------- */

/* B3 Mdp Packet Header */
typedef struct {
  uint8_t channel_id;           /* byte 0 */
  uint8_t packet_reserved;      /* byte 1 */
  uint8_t sequence_version[2];  /* bytes 2 to 3 */
  uint8_t sequence_number[4];   /* bytes 4 to 7 */
  uint8_t sending_time[8];      /* bytes 8 to 15 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  record->channel_id = arbitrary();
  record->packet_reserved = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->sequence_version[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
}

/* Packet Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->channel_id;
  wire[at++] = record->packet_reserved;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sequence_version[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }

  return at;
}

/* Packet Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  record->channel_id = wire[at++];
  record->packet_reserved = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->sequence_version[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  assert(read->channel_id == written->channel_id);
  assert(read->packet_reserved == written->packet_reserved);
  for (size_t i = 0; i < 2; i++) { assert(read->sequence_version[i] == written->sequence_version[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
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

/* ---- Framing Header: 4 bytes ------------------------------------------------- */

/* B3 Sbe framing header */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t encoding_type[2];   /* bytes 2 to 3 */
} FramingHeader;

/* any Framing Header at all: every byte one the checker chooses */
static void any_framing_header(FramingHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->encoding_type[i] = arbitrary(); }
}

/* Framing Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_framing_header(const FramingHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->encoding_type[i]; }

  return at;
}

/* Framing Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_framing_header(FramingHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->encoding_type[i] = wire[at++]; }

  return at;
}

/* what was read of Framing Header is what was written, byte for byte */
static void equal_framing_header(const FramingHeader *read, const FramingHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->encoding_type[i] == written->encoding_type[i]); }
}

/* Framing Header: written and read back, then read and written back */
static void check_framing_header(void) {
  FramingHeader sent;
  FramingHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_framing_header(&sent);
  assert(encode_framing_header(&sent, wire, 0) == 4);
  assert(decode_framing_header(&got, wire, 0) == 4);
  equal_framing_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_framing_header(&got, wire, 0) == 4);
  assert(encode_framing_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 8 bytes ------------------------------------------------- */

/* B3 Sbe message header — message identifiers and length of message root */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id[2];   /* bytes 2 to 3 */
  uint8_t schema_id[2];     /* bytes 4 to 5 */
  uint8_t version[2];       /* bytes 6 to 7 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Message Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->schema_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Message Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->schema_id[i] == written->schema_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 8);
  assert(decode_message_header(&got, wire, 0) == 8);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 8);
  assert(encode_message_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Message: 4 bytes ----------------------------------------------- */

/* Sequence_2Message */
typedef struct {
  uint8_t next_seq_no[4];  /* bytes 0 to 3 */
} SequenceMessage;

/* any Sequence Message at all: every byte one the checker chooses */
static void any_sequence_message(SequenceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->next_seq_no[i] = arbitrary(); }
}

/* Sequence Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_sequence_message(const SequenceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_seq_no[i]; }

  return at;
}

/* Sequence Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_sequence_message(SequenceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->next_seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Sequence Message is what was written, byte for byte */
static void equal_sequence_message(const SequenceMessage *read, const SequenceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->next_seq_no[i] == written->next_seq_no[i]); }
}

/* Sequence Message: written and read back, then read and written back */
static void check_sequence_message(void) {
  SequenceMessage sent;
  SequenceMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_sequence_message(&sent);
  assert(encode_sequence_message(&sent, wire, 0) == 4);
  assert(decode_sequence_message(&got, wire, 0) == 4);
  equal_sequence_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence_message(&got, wire, 0) == 4);
  assert(encode_sequence_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maturity Month Year: 5 bytes -------------------------------------------- */

/* SecurityDefinition_12Message */
typedef struct {
  uint8_t year[2];  /* bytes 0 to 1 */
  uint8_t month;    /* byte 2 */
  uint8_t day;      /* byte 3 */
  uint8_t week;     /* byte 4 */
} MaturityMonthYear;

/* any Maturity Month Year at all: every byte one the checker chooses */
static void any_maturity_month_year(MaturityMonthYear *record) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = arbitrary(); }
  record->month = arbitrary();
  record->day = arbitrary();
  record->week = arbitrary();
}

/* Maturity Month Year to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_maturity_month_year(const MaturityMonthYear *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->year[i]; }
  wire[at++] = record->month;
  wire[at++] = record->day;
  wire[at++] = record->week;

  return at;
}

/* Maturity Month Year off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_maturity_month_year(MaturityMonthYear *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = wire[at++]; }
  record->month = wire[at++];
  record->day = wire[at++];
  record->week = wire[at++];

  return at;
}

/* what was read of Maturity Month Year is what was written, byte for byte */
static void equal_maturity_month_year(const MaturityMonthYear *read, const MaturityMonthYear *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->year[i] == written->year[i]); }
  assert(read->month == written->month);
  assert(read->day == written->day);
  assert(read->week == written->week);
}

/* Maturity Month Year: written and read back, then read and written back */
static void check_maturity_month_year(void) {
  MaturityMonthYear sent;
  MaturityMonthYear got;
  uint8_t wire[5];
  uint8_t again[5];

  any_maturity_month_year(&sent);
  assert(encode_maturity_month_year(&sent, wire, 0) == 5);
  assert(decode_maturity_month_year(&got, wire, 0) == 5);
  equal_maturity_month_year(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_maturity_month_year(&got, wire, 0) == 5);
  assert(encode_maturity_month_year(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Contract Settl Month: 5 bytes ------------------------------------------- */

/* SecurityDefinition_12Message */
typedef struct {
  uint8_t year[2];  /* bytes 0 to 1 */
  uint8_t month;    /* byte 2 */
  uint8_t day;      /* byte 3 */
  uint8_t week;     /* byte 4 */
} ContractSettlMonth;

/* any Contract Settl Month at all: every byte one the checker chooses */
static void any_contract_settl_month(ContractSettlMonth *record) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = arbitrary(); }
  record->month = arbitrary();
  record->day = arbitrary();
  record->week = arbitrary();
}

/* Contract Settl Month to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_contract_settl_month(const ContractSettlMonth *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->year[i]; }
  wire[at++] = record->month;
  wire[at++] = record->day;
  wire[at++] = record->week;

  return at;
}

/* Contract Settl Month off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_contract_settl_month(ContractSettlMonth *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = wire[at++]; }
  record->month = wire[at++];
  record->day = wire[at++];
  record->week = wire[at++];

  return at;
}

/* what was read of Contract Settl Month is what was written, byte for byte */
static void equal_contract_settl_month(const ContractSettlMonth *read, const ContractSettlMonth *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->year[i] == written->year[i]); }
  assert(read->month == written->month);
  assert(read->day == written->day);
  assert(read->week == written->week);
}

/* Contract Settl Month: written and read back, then read and written back */
static void check_contract_settl_month(void) {
  ContractSettlMonth sent;
  ContractSettlMonth got;
  uint8_t wire[5];
  uint8_t again[5];

  any_contract_settl_month(&sent);
  assert(encode_contract_settl_month(&sent, wire, 0) == 5);
  assert(decode_contract_settl_month(&got, wire, 0) == 5);
  equal_contract_settl_month(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_contract_settl_month(&got, wire, 0) == 5);
  assert(encode_contract_settl_month(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Size Encoding: 3 bytes -------------------------------------------- */

/* GroupSizeEncoding */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t num_in_group;     /* byte 2 */
} GroupSizeEncoding;

/* any Group Size Encoding at all: every byte one the checker chooses */
static void any_group_size_encoding(GroupSizeEncoding *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  record->num_in_group = arbitrary();
}

/* Group Size Encoding to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_group_size_encoding(const GroupSizeEncoding *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  wire[at++] = record->num_in_group;

  return at;
}

/* Group Size Encoding off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_group_size_encoding(GroupSizeEncoding *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Group Size Encoding is what was written, byte for byte */
static void equal_group_size_encoding(const GroupSizeEncoding *read, const GroupSizeEncoding *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  assert(read->num_in_group == written->num_in_group);
}

/* Group Size Encoding: written and read back, then read and written back */
static void check_group_size_encoding(void) {
  GroupSizeEncoding sent;
  GroupSizeEncoding got;
  uint8_t wire[3];
  uint8_t again[3];

  any_group_size_encoding(&sent);
  assert(encode_group_size_encoding(&sent, wire, 0) == 3);
  assert(decode_group_size_encoding(&got, wire, 0) == 3);
  equal_group_size_encoding(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_group_size_encoding(&got, wire, 0) == 3);
  assert(encode_group_size_encoding(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot Full Refresh Header 30 Message: 34 bytes ----------------------- */

/* SnapshotFullRefresh_Header_30Message */
typedef struct {
  uint8_t security_id[8];                 /* bytes 0 to 7 */
  uint8_t last_msg_seq_num_processed[4];  /* bytes 8 to 11 */
  uint8_t tot_num_reports[4];             /* bytes 12 to 15 */
  uint8_t tot_num_bids[4];                /* bytes 16 to 19 */
  uint8_t tot_num_offers[4];              /* bytes 20 to 23 */
  uint8_t tot_num_stats[2];               /* bytes 24 to 25 */
  uint8_t offset_26_padding_2[2];         /* bytes 26 to 27 */
  uint8_t last_rpt_seq[4];                /* bytes 28 to 31 */
  uint8_t last_sequence_version[2];       /* bytes 32 to 33 */
} SnapshotFullRefreshHeader30Message;

/* any Snapshot Full Refresh Header 30 Message at all: every byte one the checker chooses */
static void any_snapshot_full_refresh_header30_message(SnapshotFullRefreshHeader30Message *record) {
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_msg_seq_num_processed[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tot_num_reports[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tot_num_bids[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tot_num_offers[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tot_num_stats[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->offset_26_padding_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_rpt_seq[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->last_sequence_version[i] = arbitrary(); }
}

/* Snapshot Full Refresh Header 30 Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_full_refresh_header30_message(const SnapshotFullRefreshHeader30Message *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_msg_seq_num_processed[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tot_num_reports[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tot_num_bids[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tot_num_offers[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tot_num_stats[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->offset_26_padding_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_rpt_seq[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->last_sequence_version[i]; }

  return at;
}

/* Snapshot Full Refresh Header 30 Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_full_refresh_header30_message(SnapshotFullRefreshHeader30Message *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_msg_seq_num_processed[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tot_num_reports[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tot_num_bids[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tot_num_offers[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tot_num_stats[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->offset_26_padding_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_rpt_seq[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->last_sequence_version[i] = wire[at++]; }

  return at;
}

/* what was read of Snapshot Full Refresh Header 30 Message is what was written, byte for byte */
static void equal_snapshot_full_refresh_header30_message(const SnapshotFullRefreshHeader30Message *read, const SnapshotFullRefreshHeader30Message *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_msg_seq_num_processed[i] == written->last_msg_seq_num_processed[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tot_num_reports[i] == written->tot_num_reports[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tot_num_bids[i] == written->tot_num_bids[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tot_num_offers[i] == written->tot_num_offers[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tot_num_stats[i] == written->tot_num_stats[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->offset_26_padding_2[i] == written->offset_26_padding_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_rpt_seq[i] == written->last_rpt_seq[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->last_sequence_version[i] == written->last_sequence_version[i]); }
}

/* Snapshot Full Refresh Header 30 Message: written and read back, then read and written back */
static void check_snapshot_full_refresh_header30_message(void) {
  SnapshotFullRefreshHeader30Message sent;
  SnapshotFullRefreshHeader30Message got;
  uint8_t wire[34];
  uint8_t again[34];

  any_snapshot_full_refresh_header30_message(&sent);
  assert(encode_snapshot_full_refresh_header30_message(&sent, wire, 0) == 34);
  assert(decode_snapshot_full_refresh_header30_message(&got, wire, 0) == 34);
  equal_snapshot_full_refresh_header30_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_full_refresh_header30_message(&got, wire, 0) == 34);
  assert(encode_snapshot_full_refresh_header30_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Summary 55 Message: 64 bytes ---------------------------------- */

/* ExecutionSummary_55Message */
typedef struct {
  uint8_t security_id[8];         /* bytes 0 to 7 */
  uint8_t offset_8_padding_2[2];  /* bytes 8 to 9 */
  uint8_t aggressor_side;         /* byte 10 */
  uint8_t offset_11_padding_1;    /* byte 11 */
  uint8_t last_px[8];             /* bytes 12 to 19 */
  uint8_t fill_qty[8];            /* bytes 20 to 27 */
  uint8_t traded_hidden_qty[8];   /* bytes 28 to 35 */
  uint8_t cxl_qty[8];             /* bytes 36 to 43 */
  uint8_t aggressor_time[8];      /* bytes 44 to 51 */
  uint8_t rpt_seq[4];             /* bytes 52 to 55 */
  uint8_t transact_time[8];       /* bytes 56 to 63 */
} ExecutionSummary55Message;

/* any Execution Summary 55 Message at all: every byte one the checker chooses */
static void any_execution_summary55_message(ExecutionSummary55Message *record) {
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->offset_8_padding_2[i] = arbitrary(); }
  record->aggressor_side = arbitrary();
  record->offset_11_padding_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fill_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->traded_hidden_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cxl_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->aggressor_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->rpt_seq[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Execution Summary 55 Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_execution_summary55_message(const ExecutionSummary55Message *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->offset_8_padding_2[i]; }
  wire[at++] = record->aggressor_side;
  wire[at++] = record->offset_11_padding_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fill_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->traded_hidden_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cxl_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->aggressor_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->rpt_seq[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Execution Summary 55 Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_execution_summary55_message(ExecutionSummary55Message *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->offset_8_padding_2[i] = wire[at++]; }
  record->aggressor_side = wire[at++];
  record->offset_11_padding_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fill_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->traded_hidden_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cxl_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->aggressor_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->rpt_seq[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Summary 55 Message is what was written, byte for byte */
static void equal_execution_summary55_message(const ExecutionSummary55Message *read, const ExecutionSummary55Message *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->offset_8_padding_2[i] == written->offset_8_padding_2[i]); }
  assert(read->aggressor_side == written->aggressor_side);
  assert(read->offset_11_padding_1 == written->offset_11_padding_1);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fill_qty[i] == written->fill_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->traded_hidden_qty[i] == written->traded_hidden_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cxl_qty[i] == written->cxl_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->aggressor_time[i] == written->aggressor_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->rpt_seq[i] == written->rpt_seq[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Execution Summary 55 Message: written and read back, then read and written back */
static void check_execution_summary55_message(void) {
  ExecutionSummary55Message sent;
  ExecutionSummary55Message got;
  uint8_t wire[64];
  uint8_t again[64];

  any_execution_summary55_message(&sent);
  assert(encode_execution_summary55_message(&sent, wire, 0) == 64);
  assert(decode_execution_summary55_message(&got, wire, 0) == 64);
  equal_execution_summary55_message(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_summary55_message(&got, wire, 0) == 64);
  assert(encode_execution_summary55_message(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_framing_header();
  check_message_header();
  check_sequence_message();
  check_maturity_month_year();
  check_contract_settl_month();
  check_group_size_encoding();
  check_snapshot_full_refresh_header30_message();
  check_execution_summary55_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
