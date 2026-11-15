// nse/nsecm/orderentry/NseCm_OrderEntry_NnfTrimmed_v6_6.c
/*
 * National Stock Exchange of India Ltd Order Entry
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
 *   - a Composite rule
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

/* ---- Sec Info: 12 bytes ------------------------------------------------------ */

/* SEC_INFO */
typedef struct {
  uint8_t symbol[10];  /* bytes 0 to 9 */
  uint8_t series[2];   /* bytes 10 to 11 */
} SecInfo;

/* any Sec Info at all: every byte one the checker chooses */
static void any_sec_info(SecInfo *record) {
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->series[i] = arbitrary(); }
}

/* Sec Info to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_sec_info(const SecInfo *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->series[i]; }

  return at;
}

/* Sec Info off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_sec_info(SecInfo *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->series[i] = wire[at++]; }

  return at;
}

/* what was read of Sec Info is what was written, byte for byte */
static void equal_sec_info(const SecInfo *read, const SecInfo *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->series[i] == written->series[i]); }
}

/* Sec Info: written and read back, then read and written back */
static void check_sec_info(void) {
  SecInfo sent;
  SecInfo got;
  uint8_t wire[12];
  uint8_t again[12];

  any_sec_info(&sent);
  assert(encode_sec_info(&sent, wire, 0) == 12);
  assert(decode_sec_info(&got, wire, 0) == 12);
  equal_sec_info(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_sec_info(&got, wire, 0) == 12);
  assert(encode_sec_info(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quick Acknowledgement Message: 22 bytes --------------------------------- */

/* Immediate acknowledgement of a trimmed order entry, modification or cancellation request, answered on the separate port of the gateway router server */
typedef struct {
  uint8_t transaction_code[2];  /* bytes 0 to 1 */
  uint8_t trader_id[4];         /* bytes 2 to 5 */
  uint8_t timestamp[8];         /* bytes 6 to 13 */
  uint8_t reference[4];         /* bytes 14 to 17 */
  uint8_t error_code[2];        /* bytes 18 to 19 */
  uint8_t message_length[2];    /* bytes 20 to 21 */
} QuickAcknowledgementMessage;

/* any Quick Acknowledgement Message at all: every byte one the checker chooses */
static void any_quick_acknowledgement_message(QuickAcknowledgementMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->transaction_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
}

/* Quick Acknowledgement Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_quick_acknowledgement_message(const QuickAcknowledgementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->transaction_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }

  return at;
}

/* Quick Acknowledgement Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_quick_acknowledgement_message(QuickAcknowledgementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->transaction_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }

  return at;
}

/* what was read of Quick Acknowledgement Message is what was written, byte for byte */
static void equal_quick_acknowledgement_message(const QuickAcknowledgementMessage *read, const QuickAcknowledgementMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->transaction_code[i] == written->transaction_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference[i] == written->reference[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->error_code[i] == written->error_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
}

/* Quick Acknowledgement Message: written and read back, then read and written back */
static void check_quick_acknowledgement_message(void) {
  QuickAcknowledgementMessage sent;
  QuickAcknowledgementMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_quick_acknowledgement_message(&sent);
  assert(encode_quick_acknowledgement_message(&sent, wire, 0) == 22);
  assert(decode_quick_acknowledgement_message(&got, wire, 0) == 22);
  equal_quick_acknowledgement_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_quick_acknowledgement_message(&got, wire, 0) == 22);
  assert(encode_quick_acknowledgement_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_sec_info();
  check_quick_acknowledgement_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
