// jpx/osederivatives/rewind/OseDerivatives_Rewind_v2_2.c
/*
 * Japan Exchange Group Rewind
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

/* ---- Rewind Request Packet: 20 bytes ----------------------------------------- */

/* Sent by the Itch user to the Itch server to request resend of lost multicast data */
typedef struct {
  uint8_t session[10];                 /* bytes 0 to 9 */
  uint8_t sequence_number[8];          /* bytes 10 to 17 */
  uint8_t requested_message_count[2];  /* bytes 18 to 19 */
} RewindRequestPacket;

/* any Rewind Request Packet at all: every byte one the checker chooses */
static void any_rewind_request_packet(RewindRequestPacket *record) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->requested_message_count[i] = arbitrary(); }
}

/* Rewind Request Packet to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_rewind_request_packet(const RewindRequestPacket *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->requested_message_count[i]; }

  return at;
}

/* Rewind Request Packet off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_rewind_request_packet(RewindRequestPacket *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->requested_message_count[i] = wire[at++]; }

  return at;
}

/* what was read of Rewind Request Packet is what was written, byte for byte */
static void equal_rewind_request_packet(const RewindRequestPacket *read, const RewindRequestPacket *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->requested_message_count[i] == written->requested_message_count[i]); }
}

/* Rewind Request Packet: written and read back, then read and written back */
static void check_rewind_request_packet(void) {
  RewindRequestPacket sent;
  RewindRequestPacket got;
  uint8_t wire[20];
  uint8_t again[20];

  any_rewind_request_packet(&sent);
  assert(encode_rewind_request_packet(&sent, wire, 0) == 20);
  assert(decode_rewind_request_packet(&got, wire, 0) == 20);
  equal_rewind_request_packet(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_rewind_request_packet(&got, wire, 0) == 20);
  assert(encode_rewind_request_packet(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_rewind_request_packet();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
