// hkex/sse/chinaconnect/Sse_ChinaConnect_v1_4.c
/*
 * Hong Kong Exchanges and Clearing Orion Market Data China Connect
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

/* The Sequence Reset message is sent on each multicast channel at start of day. The client must ignore the sequence number of the Sequence Reset message itself, and set the next expected sequence number to NewSeqNo. On receipt clients must clear all cached data for all eligible instruments traded in SSE and SZSE and then subscribe to the refresh channels. */
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

/* The Disaster Recovery (DR) Signal message is sent on a dedicated multicast channel whenever site failover is triggered. */
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

/* ---- Market Definition Message: 36 bytes ------------------------------------- */

/* The Market Definition message is generated at the start of the business day for each market (SSE or SZSE). Market Definition messages for different markets are sent via different channels. */
typedef struct {
  uint8_t market_code[4];           /* bytes 0 to 3 */
  uint8_t market_name[25];          /* bytes 4 to 28 */
  uint8_t currency_code[3];         /* bytes 29 to 31 */
  uint8_t number_of_securities[4];  /* bytes 32 to 35 */
} MarketDefinitionMessage;

/* any Market Definition Message at all: every byte one the checker chooses */
static void any_market_definition_message(MarketDefinitionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->market_name[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_securities[i] = arbitrary(); }
}

/* Market Definition Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_market_definition_message(const MarketDefinitionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_code[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->market_name[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_securities[i]; }

  return at;
}

/* Market Definition Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_market_definition_message(MarketDefinitionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->market_name[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_securities[i] = wire[at++]; }

  return at;
}

/* what was read of Market Definition Message is what was written, byte for byte */
static void equal_market_definition_message(const MarketDefinitionMessage *read, const MarketDefinitionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_code[i] == written->market_code[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->market_name[i] == written->market_name[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency_code[i] == written->currency_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_securities[i] == written->number_of_securities[i]); }
}

/* Market Definition Message: written and read back, then read and written back */
static void check_market_definition_message(void) {
  MarketDefinitionMessage sent;
  MarketDefinitionMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_market_definition_message(&sent);
  assert(encode_market_definition_message(&sent, wire, 0) == 36);
  assert(decode_market_definition_message(&got, wire, 0) == 36);
  equal_market_definition_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_market_definition_message(&got, wire, 0) == 36);
  assert(encode_market_definition_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Complete Message: 4 bytes --------------------------------------- */

/* This message is published to mark the end of a refresh. */
typedef struct {
  uint8_t last_seq_num[4];  /* bytes 0 to 3 */
} RefreshCompleteMessage;

/* any Refresh Complete Message at all: every byte one the checker chooses */
static void any_refresh_complete_message(RefreshCompleteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->last_seq_num[i] = arbitrary(); }
}

/* Refresh Complete Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_refresh_complete_message(const RefreshCompleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_seq_num[i]; }

  return at;
}

/* Refresh Complete Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_refresh_complete_message(RefreshCompleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Refresh Complete Message is what was written, byte for byte */
static void equal_refresh_complete_message(const RefreshCompleteMessage *read, const RefreshCompleteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_seq_num[i] == written->last_seq_num[i]); }
}

/* Refresh Complete Message: written and read back, then read and written back */
static void check_refresh_complete_message(void) {
  RefreshCompleteMessage sent;
  RefreshCompleteMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_refresh_complete_message(&sent);
  assert(encode_refresh_complete_message(&sent, wire, 0) == 4);
  assert(decode_refresh_complete_message(&got, wire, 0) == 4);
  equal_refresh_complete_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_complete_message(&got, wire, 0) == 4);
  assert(encode_refresh_complete_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Definition Message: 216 bytes ---------------------------------- */

/* The Security Definition message contains all the reference data for a security. Security Definition messages for different markets (SSE and SZSE) are sent via different channels. */
typedef struct {
  uint8_t security_code[4];           /* bytes 0 to 3 */
  uint8_t market_code[4];             /* bytes 4 to 7 */
  uint8_t isin_code[12];              /* bytes 8 to 19 */
  uint8_t instrument_type[4];         /* bytes 20 to 23 */
  uint8_t filler_2[2];                /* bytes 24 to 25 */
  uint8_t security_short_name[40];    /* bytes 26 to 65 */
  uint8_t currency_code[3];           /* bytes 66 to 68 */
  uint8_t filler_60[60];              /* bytes 69 to 128 */
  uint8_t security_name_gb[60];       /* bytes 129 to 188 */
  uint8_t lot_size[4];                /* bytes 189 to 192 */
  uint8_t previous_closing_price[4];  /* bytes 193 to 196 */
  uint8_t filler_1;                   /* byte 197 */
  uint8_t shortsell_flag;             /* byte 198 */
  uint8_t filler_6[6];                /* bytes 199 to 204 */
  uint8_t listing_date[4];            /* bytes 205 to 208 */
  uint8_t filler_7[7];                /* bytes 209 to 215 */
} SecurityDefinitionMessage;

/* any Security Definition Message at all: every byte one the checker chooses */
static void any_security_definition_message(SecurityDefinitionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->security_short_name[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = arbitrary(); }
  for (size_t i = 0; i < 60; i++) { record->filler_60[i] = arbitrary(); }
  for (size_t i = 0; i < 60; i++) { record->security_name_gb[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->previous_closing_price[i] = arbitrary(); }
  record->filler_1 = arbitrary();
  record->shortsell_flag = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->listing_date[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->filler_7[i] = arbitrary(); }
}

/* Security Definition Message to the wire: 216 bytes from at, returning where the next byte goes */
static size_t encode_security_definition_message(const SecurityDefinitionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->security_short_name[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency_code[i]; }
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->filler_60[i]; }
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->security_name_gb[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lot_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_closing_price[i]; }
  wire[at++] = record->filler_1;
  wire[at++] = record->shortsell_flag;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->filler_6[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->listing_date[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->filler_7[i]; }

  return at;
}

/* Security Definition Message off the wire: 216 bytes from at, returning where the next byte lies */
static size_t decode_security_definition_message(SecurityDefinitionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->security_short_name[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = wire[at++]; }
  for (size_t i = 0; i < 60; i++) { record->filler_60[i] = wire[at++]; }
  for (size_t i = 0; i < 60; i++) { record->security_name_gb[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->previous_closing_price[i] = wire[at++]; }
  record->filler_1 = wire[at++];
  record->shortsell_flag = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->listing_date[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->filler_7[i] = wire[at++]; }

  return at;
}

/* what was read of Security Definition Message is what was written, byte for byte */
static void equal_security_definition_message(const SecurityDefinitionMessage *read, const SecurityDefinitionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_code[i] == written->market_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_type[i] == written->instrument_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->security_short_name[i] == written->security_short_name[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency_code[i] == written->currency_code[i]); }
  for (size_t i = 0; i < 60; i++) { assert(read->filler_60[i] == written->filler_60[i]); }
  for (size_t i = 0; i < 60; i++) { assert(read->security_name_gb[i] == written->security_name_gb[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lot_size[i] == written->lot_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->previous_closing_price[i] == written->previous_closing_price[i]); }
  assert(read->filler_1 == written->filler_1);
  assert(read->shortsell_flag == written->shortsell_flag);
  for (size_t i = 0; i < 6; i++) { assert(read->filler_6[i] == written->filler_6[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->listing_date[i] == written->listing_date[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->filler_7[i] == written->filler_7[i]); }
}

/* Security Definition Message: written and read back, then read and written back */
static void check_security_definition_message(void) {
  SecurityDefinitionMessage sent;
  SecurityDefinitionMessage got;
  uint8_t wire[216];
  uint8_t again[216];

  any_security_definition_message(&sent);
  assert(encode_security_definition_message(&sent, wire, 0) == 216);
  assert(decode_security_definition_message(&got, wire, 0) == 216);
  equal_security_definition_message(&got, &sent);

  for (size_t i = 0; i < 216; i++) { wire[i] = arbitrary(); }
  assert(decode_security_definition_message(&got, wire, 0) == 216);
  assert(encode_security_definition_message(&got, again, 0) == 216);
  for (size_t i = 0; i < 216; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Status Message: 16 bytes --------------------------------------- */

/* The Security Status message is generated at the start of the business day if the security is halted, and whenever a security state or trading phase changes. Security Status messages for different markets (SSE and SZSE) are sent via different channels. */
typedef struct {
  uint8_t security_code[4];         /* bytes 0 to 3 */
  uint8_t security_trading_status;  /* byte 4 */
  uint8_t filler_3[3];              /* bytes 5 to 7 */
  uint8_t trading_phase_code[8];    /* bytes 8 to 15 */
} SecurityStatusMessage;

/* any Security Status Message at all: every byte one the checker chooses */
static void any_security_status_message(SecurityStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  record->security_trading_status = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_phase_code[i] = arbitrary(); }
}

/* Security Status Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_security_status_message(const SecurityStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  wire[at++] = record->security_trading_status;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_3[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_phase_code[i]; }

  return at;
}

/* Security Status Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_security_status_message(SecurityStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  record->security_trading_status = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_phase_code[i] = wire[at++]; }

  return at;
}

/* what was read of Security Status Message is what was written, byte for byte */
static void equal_security_status_message(const SecurityStatusMessage *read, const SecurityStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  assert(read->security_trading_status == written->security_trading_status);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_phase_code[i] == written->trading_phase_code[i]); }
}

/* Security Status Message: written and read back, then read and written back */
static void check_security_status_message(void) {
  SecurityStatusMessage sent;
  SecurityStatusMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_security_status_message(&sent);
  assert(encode_security_status_message(&sent, wire, 0) == 16);
  assert(decode_security_status_message(&got, wire, 0) == 16);
  equal_security_status_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_security_status_message(&got, wire, 0) == 16);
  assert(encode_security_status_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Statistics Message: 48 bytes -------------------------------------------- */

/* The Statistics message provides statistics including turnover. Statistics messages for different markets (SSE and SZSE) are sent via different channels. */
typedef struct {
  uint8_t security_code[4];  /* bytes 0 to 3 */
  uint8_t shares_traded[8];  /* bytes 4 to 11 */
  uint8_t turnover[8];       /* bytes 12 to 19 */
  uint8_t high_price[4];     /* bytes 20 to 23 */
  uint8_t low_price[4];      /* bytes 24 to 27 */
  uint8_t last_price[4];     /* bytes 28 to 31 */
  uint8_t opening_price[4];  /* bytes 32 to 35 */
  uint8_t filler_12[12];     /* bytes 36 to 47 */
} StatisticsMessage;

/* any Statistics Message at all: every byte one the checker chooses */
static void any_statistics_message(StatisticsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->shares_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->filler_12[i] = arbitrary(); }
}

/* Statistics Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_statistics_message(const StatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->shares_traded[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->filler_12[i]; }

  return at;
}

/* Statistics Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_statistics_message(StatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->shares_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->filler_12[i] = wire[at++]; }

  return at;
}

/* what was read of Statistics Message is what was written, byte for byte */
static void equal_statistics_message(const StatisticsMessage *read, const StatisticsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->shares_traded[i] == written->shares_traded[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover[i] == written->turnover[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->filler_12[i] == written->filler_12[i]); }
}

/* Statistics Message: written and read back, then read and written back */
static void check_statistics_message(void) {
  StatisticsMessage sent;
  StatisticsMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_statistics_message(&sent);
  assert(encode_statistics_message(&sent, wire, 0) == 48);
  assert(decode_statistics_message(&got, wire, 0) == 48);
  equal_statistics_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_statistics_message(&got, wire, 0) == 48);
  assert(encode_statistics_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Top Of Book Message: 36 bytes ------------------------------------------- */

/* The Top Of Book (TOB) message is generated when the top price level has been modified. TOB messages for different markets (SSE and SZSE) are sent via different channels. */
typedef struct {
  uint8_t security_code[4];           /* bytes 0 to 3 */
  uint8_t aggregate_bid_quantity[8];  /* bytes 4 to 11 */
  uint8_t aggregate_ask_quantity[8];  /* bytes 12 to 19 */
  uint8_t bid_price[4];               /* bytes 20 to 23 */
  uint8_t ask_price[4];               /* bytes 24 to 27 */
  uint8_t filler_8[8];                /* bytes 28 to 35 */
} TopOfBookMessage;

/* any Top Of Book Message at all: every byte one the checker chooses */
static void any_top_of_book_message(TopOfBookMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->aggregate_bid_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->aggregate_ask_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->filler_8[i] = arbitrary(); }
}

/* Top Of Book Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_top_of_book_message(const TopOfBookMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->aggregate_bid_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->aggregate_ask_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->filler_8[i]; }

  return at;
}

/* Top Of Book Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_top_of_book_message(TopOfBookMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->aggregate_bid_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->aggregate_ask_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->filler_8[i] = wire[at++]; }

  return at;
}

/* what was read of Top Of Book Message is what was written, byte for byte */
static void equal_top_of_book_message(const TopOfBookMessage *read, const TopOfBookMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->aggregate_bid_quantity[i] == written->aggregate_bid_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->aggregate_ask_quantity[i] == written->aggregate_ask_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_price[i] == written->ask_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->filler_8[i] == written->filler_8[i]); }
}

/* Top Of Book Message: written and read back, then read and written back */
static void check_top_of_book_message(void) {
  TopOfBookMessage sent;
  TopOfBookMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_top_of_book_message(&sent);
  assert(encode_top_of_book_message(&sent, wire, 0) == 36);
  assert(decode_top_of_book_message(&got, wire, 0) == 36);
  equal_top_of_book_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_top_of_book_message(&got, wire, 0) == 36);
  assert(encode_top_of_book_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_msg_header();
  check_sequence_reset_message();
  check_disaster_recovery_signal_message();
  check_market_definition_message();
  check_refresh_complete_message();
  check_security_definition_message();
  check_security_status_message();
  check_statistics_message();
  check_top_of_book_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
