// nyse/nysebonds/quote/NyseBonds_Quote_v1_2_a.c
/*
 * New York Stock Exchange Quote
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

/* ---- Message Header: 16 bytes ------------------------------------------------ */

/* Nyse Pdp common message header */
typedef struct {
  uint8_t msg_size[2];       /* bytes 0 to 1 */
  uint8_t msg_type[2];       /* bytes 2 to 3 */
  uint8_t msg_seq_num[4];    /* bytes 4 to 7 */
  uint8_t send_time[4];      /* bytes 8 to 11 */
  uint8_t product_id;        /* byte 12 */
  uint8_t retrans_flag;      /* byte 13 */
  uint8_t num_body_entries;  /* byte 14 */
  uint8_t filler;            /* byte 15 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->msg_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->msg_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->send_time[i] = arbitrary(); }
  record->product_id = arbitrary();
  record->retrans_flag = arbitrary();
  record->num_body_entries = arbitrary();
  record->filler = arbitrary();
}

/* Message Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->send_time[i]; }
  wire[at++] = record->product_id;
  wire[at++] = record->retrans_flag;
  wire[at++] = record->num_body_entries;
  wire[at++] = record->filler;

  return at;
}

/* Message Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->msg_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->msg_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->send_time[i] = wire[at++]; }
  record->product_id = wire[at++];
  record->retrans_flag = wire[at++];
  record->num_body_entries = wire[at++];
  record->filler = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->msg_size[i] == written->msg_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->msg_type[i] == written->msg_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->send_time[i] == written->send_time[i]); }
  assert(read->product_id == written->product_id);
  assert(read->retrans_flag == written->retrans_flag);
  assert(read->num_body_entries == written->num_body_entries);
  assert(read->filler == written->filler);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[16];
  uint8_t again[16];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 16);
  assert(decode_message_header(&got, wire, 0) == 16);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 16);
  assert(encode_message_header(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Number Reset Message: 4 bytes ---------------------------------- */

/* Sent to reset the sequence number at start of day and in response to failures. The message carries its own valid sequence number in the header. */
typedef struct {
  uint8_t next_seq_number[4];  /* bytes 0 to 3 */
} SequenceNumberResetMessage;

/* any Sequence Number Reset Message at all: every byte one the checker chooses */
static void any_sequence_number_reset_message(SequenceNumberResetMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->next_seq_number[i] = arbitrary(); }
}

/* Sequence Number Reset Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_sequence_number_reset_message(const SequenceNumberResetMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_seq_number[i]; }

  return at;
}

/* Sequence Number Reset Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_sequence_number_reset_message(SequenceNumberResetMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->next_seq_number[i] = wire[at++]; }

  return at;
}

/* what was read of Sequence Number Reset Message is what was written, byte for byte */
static void equal_sequence_number_reset_message(const SequenceNumberResetMessage *read, const SequenceNumberResetMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->next_seq_number[i] == written->next_seq_number[i]); }
}

/* Sequence Number Reset Message: written and read back, then read and written back */
static void check_sequence_number_reset_message(void) {
  SequenceNumberResetMessage sent;
  SequenceNumberResetMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_sequence_number_reset_message(&sent);
  assert(encode_sequence_number_reset_message(&sent, wire, 0) == 4);
  assert(decode_sequence_number_reset_message(&got, wire, 0) == 4);
  equal_sequence_number_reset_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence_number_reset_message(&got, wire, 0) == 4);
  assert(encode_sequence_number_reset_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Unavailable Message: 8 bytes ------------------------------------ */

/* Sent when the requested messages cannot be retransmitted. */
typedef struct {
  uint8_t begin_seq_num[4];  /* bytes 0 to 3 */
  uint8_t end_seq_num[4];    /* bytes 4 to 7 */
} MessageUnavailableMessage;

/* any Message Unavailable Message at all: every byte one the checker chooses */
static void any_message_unavailable_message(MessageUnavailableMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = arbitrary(); }
}

/* Message Unavailable Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_message_unavailable_message(const MessageUnavailableMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->begin_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_seq_num[i]; }

  return at;
}

/* Message Unavailable Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_message_unavailable_message(MessageUnavailableMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Message Unavailable Message is what was written, byte for byte */
static void equal_message_unavailable_message(const MessageUnavailableMessage *read, const MessageUnavailableMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->begin_seq_num[i] == written->begin_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_seq_num[i] == written->end_seq_num[i]); }
}

/* Message Unavailable Message: written and read back, then read and written back */
static void check_message_unavailable_message(void) {
  MessageUnavailableMessage sent;
  MessageUnavailableMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_message_unavailable_message(&sent);
  assert(encode_message_unavailable_message(&sent, wire, 0) == 8);
  assert(decode_message_unavailable_message(&got, wire, 0) == 8);
  equal_message_unavailable_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_message_unavailable_message(&got, wire, 0) == 8);
  assert(encode_message_unavailable_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Quote Message: 72 bytes ----------------------------------------- */

/* Sent in response to a Refresh Quote Request, and automatically when there are intraday symbol additions. The same body as a Quote message with the symbol and Cusip appended. */
typedef struct {
  uint8_t symbol_index[4];         /* bytes 0 to 3 */
  uint8_t source_time[4];          /* bytes 4 to 7 */
  uint8_t quote_link_id[4];        /* bytes 8 to 11 */
  uint8_t ask_price_numerator[4];  /* bytes 12 to 15 */
  uint8_t ask_size[4];             /* bytes 16 to 19 */
  uint8_t bid_price_numerator[4];  /* bytes 20 to 23 */
  uint8_t bid_size[4];             /* bytes 24 to 27 */
  uint8_t price_scale_code;        /* byte 28 */
  uint8_t exchange_id;             /* byte 29 */
  uint8_t security_type;           /* byte 30 */
  uint8_t quote_condition;         /* byte 31 */
  uint8_t flat_pricing;            /* byte 32 */
  uint8_t trading_action;          /* byte 33 */
  uint8_t filler_ascii_2[2];       /* bytes 34 to 35 */
  uint8_t symbol[22];              /* bytes 36 to 57 */
  uint8_t cusip[14];               /* bytes 58 to 71 */
} RefreshQuoteMessage;

/* any Refresh Quote Message at all: every byte one the checker chooses */
static void any_refresh_quote_message(RefreshQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quote_link_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_price_numerator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_price_numerator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = arbitrary(); }
  record->price_scale_code = arbitrary();
  record->exchange_id = arbitrary();
  record->security_type = arbitrary();
  record->quote_condition = arbitrary();
  record->flat_pricing = arbitrary();
  record->trading_action = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->filler_ascii_2[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->cusip[i] = arbitrary(); }
}

/* Refresh Quote Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_refresh_quote_message(const RefreshQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quote_link_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_price_numerator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price_numerator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size[i]; }
  wire[at++] = record->price_scale_code;
  wire[at++] = record->exchange_id;
  wire[at++] = record->security_type;
  wire[at++] = record->quote_condition;
  wire[at++] = record->flat_pricing;
  wire[at++] = record->trading_action;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_ascii_2[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->cusip[i]; }

  return at;
}

/* Refresh Quote Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_refresh_quote_message(RefreshQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quote_link_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_price_numerator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_price_numerator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = wire[at++]; }
  record->price_scale_code = wire[at++];
  record->exchange_id = wire[at++];
  record->security_type = wire[at++];
  record->quote_condition = wire[at++];
  record->flat_pricing = wire[at++];
  record->trading_action = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->filler_ascii_2[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->cusip[i] = wire[at++]; }

  return at;
}

/* what was read of Refresh Quote Message is what was written, byte for byte */
static void equal_refresh_quote_message(const RefreshQuoteMessage *read, const RefreshQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quote_link_id[i] == written->quote_link_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_price_numerator[i] == written->ask_price_numerator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size[i] == written->ask_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price_numerator[i] == written->bid_price_numerator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size[i] == written->bid_size[i]); }
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->exchange_id == written->exchange_id);
  assert(read->security_type == written->security_type);
  assert(read->quote_condition == written->quote_condition);
  assert(read->flat_pricing == written->flat_pricing);
  assert(read->trading_action == written->trading_action);
  for (size_t i = 0; i < 2; i++) { assert(read->filler_ascii_2[i] == written->filler_ascii_2[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->cusip[i] == written->cusip[i]); }
}

/* Refresh Quote Message: written and read back, then read and written back */
static void check_refresh_quote_message(void) {
  RefreshQuoteMessage sent;
  RefreshQuoteMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_refresh_quote_message(&sent);
  assert(encode_refresh_quote_message(&sent, wire, 0) == 72);
  assert(decode_refresh_quote_message(&got, wire, 0) == 72);
  equal_refresh_quote_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_quote_message(&got, wire, 0) == 72);
  assert(encode_refresh_quote_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Index Mapping Message: 44 bytes ---------------------------------- */

/* Maps a symbol index to its bond symbol and Cusip. */
typedef struct {
  uint8_t symbol_index[4];    /* bytes 0 to 3 */
  uint8_t symbol[22];         /* bytes 4 to 25 */
  uint8_t cusip[14];          /* bytes 26 to 39 */
  uint8_t filler_ascii_4[4];  /* bytes 40 to 43 */
} SymbolIndexMappingMessage;

/* any Symbol Index Mapping Message at all: every byte one the checker chooses */
static void any_symbol_index_mapping_message(SymbolIndexMappingMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->cusip[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_ascii_4[i] = arbitrary(); }
}

/* Symbol Index Mapping Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_symbol_index_mapping_message(const SymbolIndexMappingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->cusip[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_ascii_4[i]; }

  return at;
}

/* Symbol Index Mapping Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_symbol_index_mapping_message(SymbolIndexMappingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->cusip[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_ascii_4[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Index Mapping Message is what was written, byte for byte */
static void equal_symbol_index_mapping_message(const SymbolIndexMappingMessage *read, const SymbolIndexMappingMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->cusip[i] == written->cusip[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_ascii_4[i] == written->filler_ascii_4[i]); }
}

/* Symbol Index Mapping Message: written and read back, then read and written back */
static void check_symbol_index_mapping_message(void) {
  SymbolIndexMappingMessage sent;
  SymbolIndexMappingMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_symbol_index_mapping_message(&sent);
  assert(encode_symbol_index_mapping_message(&sent, wire, 0) == 44);
  assert(decode_symbol_index_mapping_message(&got, wire, 0) == 44);
  equal_symbol_index_mapping_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_index_mapping_message(&got, wire, 0) == 44);
  assert(encode_symbol_index_mapping_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Message: 36 bytes ------------------------------------------------- */

/* The L1 top of book quote for a bond. */
typedef struct {
  uint8_t symbol_index[4];         /* bytes 0 to 3 */
  uint8_t source_time[4];          /* bytes 4 to 7 */
  uint8_t quote_link_id[4];        /* bytes 8 to 11 */
  uint8_t ask_price_numerator[4];  /* bytes 12 to 15 */
  uint8_t ask_size[4];             /* bytes 16 to 19 */
  uint8_t bid_price_numerator[4];  /* bytes 20 to 23 */
  uint8_t bid_size[4];             /* bytes 24 to 27 */
  uint8_t price_scale_code;        /* byte 28 */
  uint8_t exchange_id;             /* byte 29 */
  uint8_t security_type;           /* byte 30 */
  uint8_t quote_condition;         /* byte 31 */
  uint8_t flat_pricing;            /* byte 32 */
  uint8_t trading_action;          /* byte 33 */
  uint8_t filler_ascii_2[2];       /* bytes 34 to 35 */
} QuoteMessage;

/* any Quote Message at all: every byte one the checker chooses */
static void any_quote_message(QuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quote_link_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_price_numerator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_price_numerator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = arbitrary(); }
  record->price_scale_code = arbitrary();
  record->exchange_id = arbitrary();
  record->security_type = arbitrary();
  record->quote_condition = arbitrary();
  record->flat_pricing = arbitrary();
  record->trading_action = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->filler_ascii_2[i] = arbitrary(); }
}

/* Quote Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_quote_message(const QuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quote_link_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_price_numerator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price_numerator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size[i]; }
  wire[at++] = record->price_scale_code;
  wire[at++] = record->exchange_id;
  wire[at++] = record->security_type;
  wire[at++] = record->quote_condition;
  wire[at++] = record->flat_pricing;
  wire[at++] = record->trading_action;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_ascii_2[i]; }

  return at;
}

/* Quote Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_quote_message(QuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quote_link_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_price_numerator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_price_numerator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = wire[at++]; }
  record->price_scale_code = wire[at++];
  record->exchange_id = wire[at++];
  record->security_type = wire[at++];
  record->quote_condition = wire[at++];
  record->flat_pricing = wire[at++];
  record->trading_action = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->filler_ascii_2[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Message is what was written, byte for byte */
static void equal_quote_message(const QuoteMessage *read, const QuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quote_link_id[i] == written->quote_link_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_price_numerator[i] == written->ask_price_numerator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size[i] == written->ask_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price_numerator[i] == written->bid_price_numerator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size[i] == written->bid_size[i]); }
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->exchange_id == written->exchange_id);
  assert(read->security_type == written->security_type);
  assert(read->quote_condition == written->quote_condition);
  assert(read->flat_pricing == written->flat_pricing);
  assert(read->trading_action == written->trading_action);
  for (size_t i = 0; i < 2; i++) { assert(read->filler_ascii_2[i] == written->filler_ascii_2[i]); }
}

/* Quote Message: written and read back, then read and written back */
static void check_quote_message(void) {
  QuoteMessage sent;
  QuoteMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_quote_message(&sent);
  assert(encode_quote_message(&sent, wire, 0) == 36);
  assert(decode_quote_message(&got, wire, 0) == 36);
  equal_quote_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_message(&got, wire, 0) == 36);
  assert(encode_quote_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_sequence_number_reset_message();
  check_message_unavailable_message();
  check_refresh_quote_message();
  check_symbol_index_mapping_message();
  check_quote_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
