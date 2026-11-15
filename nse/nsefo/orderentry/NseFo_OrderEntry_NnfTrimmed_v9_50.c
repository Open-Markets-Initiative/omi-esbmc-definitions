// nse/nsefo/orderentry/NseFo_OrderEntry_NnfTrimmed_v9_50.c
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

/* ---- Contract Desc Tr: 26 bytes ---------------------------------------------- */

/* CONTRACT_DESC_TR */
typedef struct {
  uint8_t instrument_name[6];  /* bytes 0 to 5 */
  uint8_t symbol[10];          /* bytes 6 to 15 */
  uint8_t expiry_date[4];      /* bytes 16 to 19 */
  uint8_t strike_price[4];     /* bytes 20 to 23 */
  uint8_t option_type[2];      /* bytes 24 to 25 */
} ContractDescTr;

/* any Contract Desc Tr at all: every byte one the checker chooses */
static void any_contract_desc_tr(ContractDescTr *record) {
  for (size_t i = 0; i < 6; i++) { record->instrument_name[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->option_type[i] = arbitrary(); }
}

/* Contract Desc Tr to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_contract_desc_tr(const ContractDescTr *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->instrument_name[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expiry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->option_type[i]; }

  return at;
}

/* Contract Desc Tr off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_contract_desc_tr(ContractDescTr *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->instrument_name[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->option_type[i] = wire[at++]; }

  return at;
}

/* what was read of Contract Desc Tr is what was written, byte for byte */
static void equal_contract_desc_tr(const ContractDescTr *read, const ContractDescTr *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->instrument_name[i] == written->instrument_name[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expiry_date[i] == written->expiry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->option_type[i] == written->option_type[i]); }
}

/* Contract Desc Tr: written and read back, then read and written back */
static void check_contract_desc_tr(void) {
  ContractDescTr sent;
  ContractDescTr got;
  uint8_t wire[26];
  uint8_t again[26];

  any_contract_desc_tr(&sent);
  assert(encode_contract_desc_tr(&sent, wire, 0) == 26);
  assert(decode_contract_desc_tr(&got, wire, 0) == 26);
  equal_contract_desc_tr(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_contract_desc_tr(&got, wire, 0) == 26);
  assert(encode_contract_desc_tr(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quick Acknowledgement Message: 20 bytes --------------------------------- */

/* Immediate acknowledgement that an order related request reached the exchange */
typedef struct {
  uint8_t trader_id[4];       /* bytes 0 to 3 */
  uint8_t time_stamp[8];      /* bytes 4 to 11 */
  uint8_t reference[4];       /* bytes 12 to 15 */
  uint8_t error_code[2];      /* bytes 16 to 17 */
  uint8_t message_length[2];  /* bytes 18 to 19 */
} QuickAcknowledgementMessage;

/* any Quick Acknowledgement Message at all: every byte one the checker chooses */
static void any_quick_acknowledgement_message(QuickAcknowledgementMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
}

/* Quick Acknowledgement Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_quick_acknowledgement_message(const QuickAcknowledgementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }

  return at;
}

/* Quick Acknowledgement Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_quick_acknowledgement_message(QuickAcknowledgementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_stamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }

  return at;
}

/* what was read of Quick Acknowledgement Message is what was written, byte for byte */
static void equal_quick_acknowledgement_message(const QuickAcknowledgementMessage *read, const QuickAcknowledgementMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference[i] == written->reference[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->error_code[i] == written->error_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
}

/* Quick Acknowledgement Message: written and read back, then read and written back */
static void check_quick_acknowledgement_message(void) {
  QuickAcknowledgementMessage sent;
  QuickAcknowledgementMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_quick_acknowledgement_message(&sent);
  assert(encode_quick_acknowledgement_message(&sent, wire, 0) == 20);
  assert(decode_quick_acknowledgement_message(&got, wire, 0) == 20);
  equal_quick_acknowledgement_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_quick_acknowledgement_message(&got, wire, 0) == 20);
  assert(encode_quick_acknowledgement_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_contract_desc_tr();
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
