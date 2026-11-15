// cixats/rerequest/CixAts_CixAspen_Rerequest_v1_1.c
/*
 * CIX Trading Inc. CIX Udp Rerequest
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

/* ---- Rerequest Header: 20 bytes ---------------------------------------------- */

/* Aspen Udp rerequest header */
typedef struct {
  uint8_t market_day_identifier[9];  /* bytes 0 to 8 */
  uint8_t feed_identifier;           /* byte 9 */
  uint8_t sequence[8];               /* bytes 10 to 17 */
  uint8_t count[2];                  /* bytes 18 to 19 */
} RerequestHeader;

/* any Rerequest Header at all: every byte one the checker chooses */
static void any_rerequest_header(RerequestHeader *record) {
  for (size_t i = 0; i < 9; i++) { record->market_day_identifier[i] = arbitrary(); }
  record->feed_identifier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->count[i] = arbitrary(); }
}

/* Rerequest Header to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_rerequest_header(const RerequestHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->market_day_identifier[i]; }
  wire[at++] = record->feed_identifier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->count[i]; }

  return at;
}

/* Rerequest Header off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_rerequest_header(RerequestHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->market_day_identifier[i] = wire[at++]; }
  record->feed_identifier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->count[i] = wire[at++]; }

  return at;
}

/* what was read of Rerequest Header is what was written, byte for byte */
static void equal_rerequest_header(const RerequestHeader *read, const RerequestHeader *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->market_day_identifier[i] == written->market_day_identifier[i]); }
  assert(read->feed_identifier == written->feed_identifier);
  for (size_t i = 0; i < 8; i++) { assert(read->sequence[i] == written->sequence[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->count[i] == written->count[i]); }
}

/* Rerequest Header: written and read back, then read and written back */
static void check_rerequest_header(void) {
  RerequestHeader sent;
  RerequestHeader got;
  uint8_t wire[20];
  uint8_t again[20];

  any_rerequest_header(&sent);
  assert(encode_rerequest_header(&sent, wire, 0) == 20);
  assert(decode_rerequest_header(&got, wire, 0) == 20);
  equal_rerequest_header(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_rerequest_header(&got, wire, 0) == 20);
  assert(encode_rerequest_header(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Packet: 20 bytes -------------------------------------------------------- */

/* Aspen Udp Rerequest Packet */
typedef struct {
  RerequestHeader rerequest_header;  /* bytes 0 to 19 */
} Packet;

/* any Packet at all: every byte one the checker chooses */
static void any_packet(Packet *record) {
  any_rerequest_header(&record->rerequest_header);
}

/* Packet to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_packet(const Packet *record, uint8_t *wire, size_t at) {
  at = encode_rerequest_header(&record->rerequest_header, wire, at);

  return at;
}

/* Packet off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_packet(Packet *record, const uint8_t *wire, size_t at) {
  at = decode_rerequest_header(&record->rerequest_header, wire, at);

  return at;
}

/* what was read of Packet is what was written, byte for byte */
static void equal_packet(const Packet *read, const Packet *written) {
  equal_rerequest_header(&read->rerequest_header, &written->rerequest_header);
}

/* Packet: written and read back, then read and written back */
static void check_packet(void) {
  Packet sent;
  Packet got;
  uint8_t wire[20];
  uint8_t again[20];

  any_packet(&sent);
  assert(encode_packet(&sent, wire, 0) == 20);
  assert(decode_packet(&got, wire, 0) == 20);
  equal_packet(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_packet(&got, wire, 0) == 20);
  assert(encode_packet(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_rerequest_header();
  check_packet();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
