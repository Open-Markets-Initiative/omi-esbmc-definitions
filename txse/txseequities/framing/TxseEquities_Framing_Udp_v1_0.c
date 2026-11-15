// txse/txseequities/framing/TxseEquities_Framing_Udp_v1_0.c
/*
 * Texas Stock Exchange
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

/* ---- Udp Header: 19 bytes ---------------------------------------------------- */

/* Rake Udp packet header */
typedef struct {
  uint8_t session[8];        /* bytes 0 to 7 */
  uint8_t sequence[8];       /* bytes 8 to 15 */
  uint8_t message_count[2];  /* bytes 16 to 17 */
  uint8_t packet_type;       /* byte 18 */
} UdpHeader;

/* any Udp Header at all: every byte one the checker chooses */
static void any_udp_header(UdpHeader *record) {
  for (size_t i = 0; i < 8; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = arbitrary(); }
  record->packet_type = arbitrary();
}

/* Udp Header to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_udp_header(const UdpHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_count[i]; }
  wire[at++] = record->packet_type;

  return at;
}

/* Udp Header off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_udp_header(UdpHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = wire[at++]; }
  record->packet_type = wire[at++];

  return at;
}

/* what was read of Udp Header is what was written, byte for byte */
static void equal_udp_header(const UdpHeader *read, const UdpHeader *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence[i] == written->sequence[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_count[i] == written->message_count[i]); }
  assert(read->packet_type == written->packet_type);
}

/* Udp Header: written and read back, then read and written back */
static void check_udp_header(void) {
  UdpHeader sent;
  UdpHeader got;
  uint8_t wire[19];
  uint8_t again[19];

  any_udp_header(&sent);
  assert(encode_udp_header(&sent, wire, 0) == 19);
  assert(decode_udp_header(&got, wire, 0) == 19);
  equal_udp_header(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_udp_header(&got, wire, 0) == 19);
  assert(encode_udp_header(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_udp_header();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
