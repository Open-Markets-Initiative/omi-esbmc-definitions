// tmx/tsx/indexfeed/Tsx_IndexFeed_v1_19.c
/*
 * TMX Group Index Feed
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

/* ---- Message Header: 22 bytes ------------------------------------------------ */

/* Twenty two byte ascii header carried on every Qrtmd message */
typedef struct {
  uint8_t message_length[4];          /* bytes 0 to 3 */
  uint8_t sequence_number[9];         /* bytes 4 to 12 */
  uint8_t service_identifier[3];      /* bytes 13 to 15 */
  uint8_t retransmission_identifier;  /* byte 16 */
  uint8_t continuation_identifier;    /* byte 17 */
  uint8_t message_type[2];            /* bytes 18 to 19 */
  uint8_t exchange_identifier[2];     /* bytes 20 to 21 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->service_identifier[i] = arbitrary(); }
  record->retransmission_identifier = arbitrary();
  record->continuation_identifier = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->exchange_identifier[i] = arbitrary(); }
}

/* Message Header to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->service_identifier[i]; }
  wire[at++] = record->retransmission_identifier;
  wire[at++] = record->continuation_identifier;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->exchange_identifier[i]; }

  return at;
}

/* Message Header off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->service_identifier[i] = wire[at++]; }
  record->retransmission_identifier = wire[at++];
  record->continuation_identifier = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->exchange_identifier[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->service_identifier[i] == written->service_identifier[i]); }
  assert(read->retransmission_identifier == written->retransmission_identifier);
  assert(read->continuation_identifier == written->continuation_identifier);
  for (size_t i = 0; i < 2; i++) { assert(read->message_type[i] == written->message_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->exchange_identifier[i] == written->exchange_identifier[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[22];
  uint8_t again[22];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 22);
  assert(decode_message_header(&got, wire, 0) == 22);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 22);
  assert(encode_message_header(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- S And P Tsx Official Index Level Message: 122 bytes --------------------- */

/* Level of an index as of the time of the calculation. */
typedef struct {
  uint8_t time[6];                   /* bytes 0 to 5 */
  uint8_t index_id[4];               /* bytes 6 to 9 */
  uint8_t last_level[8];             /* bytes 10 to 17 */
  uint8_t net_change[7];             /* bytes 18 to 24 */
  uint8_t volume[11];                /* bytes 25 to 35 */
  uint8_t value[12];                 /* bytes 36 to 47 */
  uint8_t open_level[8];             /* bytes 48 to 55 */
  uint8_t settlement_value[8];       /* bytes 56 to 63 */
  uint8_t special_opening_quote[8];  /* bytes 64 to 71 */
  uint8_t percent_trading[7];        /* bytes 72 to 78 */
  uint8_t high_level[8];             /* bytes 79 to 86 */
  uint8_t low_level[8];              /* bytes 87 to 94 */
  uint8_t pe[7];                     /* bytes 95 to 101 */
  uint8_t yield[5];                  /* bytes 102 to 106 */
  uint8_t markers;                   /* byte 107 */
  uint8_t bid_price[7];              /* bytes 108 to 114 */
  uint8_t ask_price[7];              /* bytes 115 to 121 */
} SAndPTsxOfficialIndexLevelMessage;

/* any S And P Tsx Official Index Level Message at all: every byte one the checker chooses */
static void any_s_and_p_tsx_official_index_level_message(SAndPTsxOfficialIndexLevelMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_level[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->net_change[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_level[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->special_opening_quote[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->percent_trading[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_level[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_level[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->pe[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->yield[i] = arbitrary(); }
  record->markers = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->ask_price[i] = arbitrary(); }
}

/* S And P Tsx Official Index Level Message to the wire: 122 bytes from at, returning where the next byte goes */
static size_t encode_s_and_p_tsx_official_index_level_message(const SAndPTsxOfficialIndexLevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_level[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->net_change[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_level[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->special_opening_quote[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->percent_trading[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_level[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_level[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->pe[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->yield[i]; }
  wire[at++] = record->markers;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->ask_price[i]; }

  return at;
}

/* S And P Tsx Official Index Level Message off the wire: 122 bytes from at, returning where the next byte lies */
static size_t decode_s_and_p_tsx_official_index_level_message(SAndPTsxOfficialIndexLevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_level[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->net_change[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_level[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->special_opening_quote[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->percent_trading[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_level[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_level[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->pe[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->yield[i] = wire[at++]; }
  record->markers = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->ask_price[i] = wire[at++]; }

  return at;
}

/* what was read of S And P Tsx Official Index Level Message is what was written, byte for byte */
static void equal_s_and_p_tsx_official_index_level_message(const SAndPTsxOfficialIndexLevelMessage *read, const SAndPTsxOfficialIndexLevelMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_level[i] == written->last_level[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->net_change[i] == written->net_change[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->value[i] == written->value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_level[i] == written->open_level[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_value[i] == written->settlement_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->special_opening_quote[i] == written->special_opening_quote[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->percent_trading[i] == written->percent_trading[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_level[i] == written->high_level[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_level[i] == written->low_level[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->pe[i] == written->pe[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->yield[i] == written->yield[i]); }
  assert(read->markers == written->markers);
  for (size_t i = 0; i < 7; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->ask_price[i] == written->ask_price[i]); }
}

/* S And P Tsx Official Index Level Message: written and read back, then read and written back */
static void check_s_and_p_tsx_official_index_level_message(void) {
  SAndPTsxOfficialIndexLevelMessage sent;
  SAndPTsxOfficialIndexLevelMessage got;
  uint8_t wire[122];
  uint8_t again[122];

  any_s_and_p_tsx_official_index_level_message(&sent);
  assert(encode_s_and_p_tsx_official_index_level_message(&sent, wire, 0) == 122);
  assert(decode_s_and_p_tsx_official_index_level_message(&got, wire, 0) == 122);
  equal_s_and_p_tsx_official_index_level_message(&got, &sent);

  for (size_t i = 0; i < 122; i++) { wire[i] = arbitrary(); }
  assert(decode_s_and_p_tsx_official_index_level_message(&got, wire, 0) == 122);
  assert(encode_s_and_p_tsx_official_index_level_message(&got, again, 0) == 122);
  for (size_t i = 0; i < 122; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_s_and_p_tsx_official_index_level_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
