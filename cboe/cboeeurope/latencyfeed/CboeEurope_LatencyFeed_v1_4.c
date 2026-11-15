// cboe/cboeeurope/latencyfeed/CboeEurope_LatencyFeed_v1_4.c
/*
 * Chicago Board Options Exchange Multicast Latency Feed
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

/* ---- Packet Header: 8 bytes -------------------------------------------------- */

typedef struct {
  uint8_t length[2];      /* bytes 0 to 1 */
  uint8_t message_count;  /* byte 2 */
  uint8_t unit;           /* byte 3 */
  uint8_t sequence[4];    /* bytes 4 to 7 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  record->message_count = arbitrary();
  record->unit = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
}

/* Packet Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  wire[at++] = record->message_count;
  wire[at++] = record->unit;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }

  return at;
}

/* Packet Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  record->message_count = wire[at++];
  record->unit = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  assert(read->message_count == written->message_count);
  assert(read->unit == written->unit);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 8);
  assert(decode_packet_header(&got, wire, 0) == 8);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 8);
  assert(encode_packet_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 2 bytes ------------------------------------------------- */

typedef struct {
  uint8_t message_length;  /* byte 0 */
  uint8_t message_type;    /* byte 1 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->message_length = arbitrary();
  record->message_type = arbitrary();
}

/* Message Header to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_length;
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->message_length = wire[at++];
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->message_length == written->message_length);
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[2];
  uint8_t again[2];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 2);
  assert(decode_message_header(&got, wire, 0) == 2);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 2);
  assert(encode_message_header(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Latency Stat Message: 110 bytes ----------------------------------------- */

/* A Latency Stat Message demonstrates performance for a specific Matching Engine unit for a specific timeframe */
typedef struct {
  uint8_t measurement_type;          /* byte 0 */
  uint8_t matching_unit;             /* byte 1 */
  uint8_t begin_time[4];             /* bytes 2 to 5 */
  uint8_t end_time[4];               /* bytes 6 to 9 */
  uint8_t count[4];                  /* bytes 10 to 13 */
  uint8_t minimum[8];                /* bytes 14 to 21 */
  uint8_t maximum[8];                /* bytes 22 to 29 */
  uint8_t average[8];                /* bytes 30 to 37 */
  uint8_t standard_deviation[8];     /* bytes 38 to 45 */
  uint8_t mode[8];                   /* bytes 46 to 53 */
  uint8_t percentile_99_point_9[8];  /* bytes 54 to 61 */
  uint8_t percentile_99[8];          /* bytes 62 to 69 */
  uint8_t percentile_95[8];          /* bytes 70 to 77 */
  uint8_t percentile_90[8];          /* bytes 78 to 85 */
  uint8_t percentile_75[8];          /* bytes 86 to 93 */
  uint8_t percentile_50[8];          /* bytes 94 to 101 */
  uint8_t percentile_25[8];          /* bytes 102 to 109 */
} LatencyStatMessage;

/* any Latency Stat Message at all: every byte one the checker chooses */
static void any_latency_stat_message(LatencyStatMessage *record) {
  record->measurement_type = arbitrary();
  record->matching_unit = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->begin_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maximum[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->average[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->standard_deviation[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mode[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->percentile_99_point_9[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->percentile_99[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->percentile_95[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->percentile_90[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->percentile_75[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->percentile_50[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->percentile_25[i] = arbitrary(); }
}

/* Latency Stat Message to the wire: 110 bytes from at, returning where the next byte goes */
static size_t encode_latency_stat_message(const LatencyStatMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->measurement_type;
  wire[at++] = record->matching_unit;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->begin_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maximum[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->average[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->standard_deviation[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mode[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->percentile_99_point_9[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->percentile_99[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->percentile_95[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->percentile_90[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->percentile_75[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->percentile_50[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->percentile_25[i]; }

  return at;
}

/* Latency Stat Message off the wire: 110 bytes from at, returning where the next byte lies */
static size_t decode_latency_stat_message(LatencyStatMessage *record, const uint8_t *wire, size_t at) {
  record->measurement_type = wire[at++];
  record->matching_unit = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->begin_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maximum[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->average[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->standard_deviation[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mode[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->percentile_99_point_9[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->percentile_99[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->percentile_95[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->percentile_90[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->percentile_75[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->percentile_50[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->percentile_25[i] = wire[at++]; }

  return at;
}

/* what was read of Latency Stat Message is what was written, byte for byte */
static void equal_latency_stat_message(const LatencyStatMessage *read, const LatencyStatMessage *written) {
  assert(read->measurement_type == written->measurement_type);
  assert(read->matching_unit == written->matching_unit);
  for (size_t i = 0; i < 4; i++) { assert(read->begin_time[i] == written->begin_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_time[i] == written->end_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->count[i] == written->count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum[i] == written->minimum[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maximum[i] == written->maximum[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->average[i] == written->average[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->standard_deviation[i] == written->standard_deviation[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mode[i] == written->mode[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->percentile_99_point_9[i] == written->percentile_99_point_9[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->percentile_99[i] == written->percentile_99[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->percentile_95[i] == written->percentile_95[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->percentile_90[i] == written->percentile_90[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->percentile_75[i] == written->percentile_75[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->percentile_50[i] == written->percentile_50[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->percentile_25[i] == written->percentile_25[i]); }
}

/* Latency Stat Message: written and read back, then read and written back */
static void check_latency_stat_message(void) {
  LatencyStatMessage sent;
  LatencyStatMessage got;
  uint8_t wire[110];
  uint8_t again[110];

  any_latency_stat_message(&sent);
  assert(encode_latency_stat_message(&sent, wire, 0) == 110);
  assert(decode_latency_stat_message(&got, wire, 0) == 110);
  equal_latency_stat_message(&got, &sent);

  for (size_t i = 0; i < 110; i++) { wire[i] = arbitrary(); }
  assert(decode_latency_stat_message(&got, wire, 0) == 110);
  assert(encode_latency_stat_message(&got, again, 0) == 110);
  for (size_t i = 0; i < 110; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_latency_stat_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
