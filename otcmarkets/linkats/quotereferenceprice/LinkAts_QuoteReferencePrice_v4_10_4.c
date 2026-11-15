// otcmarkets/linkats/quotereferenceprice/LinkAts_QuoteReferencePrice_v4_10_4.c
/*
 * OTC Markets Group
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
 *   - a field read in bits
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

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* Otc Udp Message Header */
typedef struct {
  uint8_t message_size[2];  /* bytes 0 to 1 */
  uint8_t message_type;     /* byte 2 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_size[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_size[i] == written->message_size[i]); }
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 3);
  assert(decode_message_header(&got, wire, 0) == 3);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 3);
  assert(encode_message_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Spin Message: 17 bytes ----------------------------------------- */

/* This message appears on all quote channels and indicates the beginning of a spin message cycle. */
typedef struct {
  uint8_t channel_seq_num[4];        /* bytes 0 to 3 */
  uint8_t spin_type;                 /* byte 4 */
  uint8_t spin_start_time_milli[8];  /* bytes 5 to 12 */
  uint8_t spin_last_seq_num[4];      /* bytes 13 to 16 */
} StartOfSpinMessage;

/* any Start Of Spin Message at all: every byte one the checker chooses */
static void any_start_of_spin_message(StartOfSpinMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->channel_seq_num[i] = arbitrary(); }
  record->spin_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->spin_start_time_milli[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->spin_last_seq_num[i] = arbitrary(); }
}

/* Start Of Spin Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_start_of_spin_message(const StartOfSpinMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->channel_seq_num[i]; }
  wire[at++] = record->spin_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->spin_start_time_milli[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->spin_last_seq_num[i]; }

  return at;
}

/* Start Of Spin Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_start_of_spin_message(StartOfSpinMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->channel_seq_num[i] = wire[at++]; }
  record->spin_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->spin_start_time_milli[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->spin_last_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Start Of Spin Message is what was written, byte for byte */
static void equal_start_of_spin_message(const StartOfSpinMessage *read, const StartOfSpinMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->channel_seq_num[i] == written->channel_seq_num[i]); }
  assert(read->spin_type == written->spin_type);
  for (size_t i = 0; i < 8; i++) { assert(read->spin_start_time_milli[i] == written->spin_start_time_milli[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->spin_last_seq_num[i] == written->spin_last_seq_num[i]); }
}

/* Start Of Spin Message: written and read back, then read and written back */
static void check_start_of_spin_message(void) {
  StartOfSpinMessage sent;
  StartOfSpinMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_start_of_spin_message(&sent);
  assert(encode_start_of_spin_message(&sent, wire, 0) == 17);
  assert(decode_start_of_spin_message(&got, wire, 0) == 17);
  equal_start_of_spin_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_spin_message(&got, wire, 0) == 17);
  assert(encode_start_of_spin_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Spin Message: 21 bytes ------------------------------------------- */

/* This message appears on all quote channels and indicates the end of a spin message cycle. */
typedef struct {
  uint8_t channel_seq_num[4];      /* bytes 0 to 3 */
  uint8_t spin_type;               /* byte 4 */
  uint8_t spin_msg_ct[4];          /* bytes 5 to 8 */
  uint8_t spin_end_time_milli[8];  /* bytes 9 to 16 */
  uint8_t spin_last_seq_num[4];    /* bytes 17 to 20 */
} EndOfSpinMessage;

/* any End Of Spin Message at all: every byte one the checker chooses */
static void any_end_of_spin_message(EndOfSpinMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->channel_seq_num[i] = arbitrary(); }
  record->spin_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->spin_msg_ct[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->spin_end_time_milli[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->spin_last_seq_num[i] = arbitrary(); }
}

/* End Of Spin Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_end_of_spin_message(const EndOfSpinMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->channel_seq_num[i]; }
  wire[at++] = record->spin_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->spin_msg_ct[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->spin_end_time_milli[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->spin_last_seq_num[i]; }

  return at;
}

/* End Of Spin Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_end_of_spin_message(EndOfSpinMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->channel_seq_num[i] = wire[at++]; }
  record->spin_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->spin_msg_ct[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->spin_end_time_milli[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->spin_last_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Spin Message is what was written, byte for byte */
static void equal_end_of_spin_message(const EndOfSpinMessage *read, const EndOfSpinMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->channel_seq_num[i] == written->channel_seq_num[i]); }
  assert(read->spin_type == written->spin_type);
  for (size_t i = 0; i < 4; i++) { assert(read->spin_msg_ct[i] == written->spin_msg_ct[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->spin_end_time_milli[i] == written->spin_end_time_milli[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->spin_last_seq_num[i] == written->spin_last_seq_num[i]); }
}

/* End Of Spin Message: written and read back, then read and written back */
static void check_end_of_spin_message(void) {
  EndOfSpinMessage sent;
  EndOfSpinMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_end_of_spin_message(&sent);
  assert(encode_end_of_spin_message(&sent, wire, 0) == 21);
  assert(decode_end_of_spin_message(&got, wire, 0) == 21);
  equal_end_of_spin_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_spin_message(&got, wire, 0) == 21);
  assert(encode_end_of_spin_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Open Message: 20 bytes ------------------------------------------- */

/* This message is sent out at 6 AM on all channels. The message can also be sent mid-day if a technical outage caused a temporary closure of the market. */
typedef struct {
  uint8_t channel_seq_num[4];  /* bytes 0 to 3 */
  uint8_t market_open[8];      /* bytes 4 to 11 */
  uint8_t market_close[8];     /* bytes 12 to 19 */
} MarketOpenMessage;

/* any Market Open Message at all: every byte one the checker chooses */
static void any_market_open_message(MarketOpenMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->channel_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->market_open[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->market_close[i] = arbitrary(); }
}

/* Market Open Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_market_open_message(const MarketOpenMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->channel_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_open[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_close[i]; }

  return at;
}

/* Market Open Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_market_open_message(MarketOpenMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->channel_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->market_open[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->market_close[i] = wire[at++]; }

  return at;
}

/* what was read of Market Open Message is what was written, byte for byte */
static void equal_market_open_message(const MarketOpenMessage *read, const MarketOpenMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->channel_seq_num[i] == written->channel_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->market_open[i] == written->market_open[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->market_close[i] == written->market_close[i]); }
}

/* Market Open Message: written and read back, then read and written back */
static void check_market_open_message(void) {
  MarketOpenMessage sent;
  MarketOpenMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_market_open_message(&sent);
  assert(encode_market_open_message(&sent, wire, 0) == 20);
  assert(decode_market_open_message(&got, wire, 0) == 20);
  equal_market_open_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_market_open_message(&got, wire, 0) == 20);
  assert(encode_market_open_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Close Message: 16 bytes ------------------------------------------ */

/* This message is sent out at 5 PM on all channels. The message can also be sent mid-day if a technical outage causes a temporary closure of the market. */
typedef struct {
  uint8_t channel_seq_num[4];          /* bytes 0 to 3 */
  uint8_t market_close_time_milli[8];  /* bytes 4 to 11 */
  uint8_t market_msg_ct[4];            /* bytes 12 to 15 */
} MarketCloseMessage;

/* any Market Close Message at all: every byte one the checker chooses */
static void any_market_close_message(MarketCloseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->channel_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->market_close_time_milli[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_msg_ct[i] = arbitrary(); }
}

/* Market Close Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_market_close_message(const MarketCloseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->channel_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_close_time_milli[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_msg_ct[i]; }

  return at;
}

/* Market Close Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_market_close_message(MarketCloseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->channel_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->market_close_time_milli[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_msg_ct[i] = wire[at++]; }

  return at;
}

/* what was read of Market Close Message is what was written, byte for byte */
static void equal_market_close_message(const MarketCloseMessage *read, const MarketCloseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->channel_seq_num[i] == written->channel_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->market_close_time_milli[i] == written->market_close_time_milli[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_msg_ct[i] == written->market_msg_ct[i]); }
}

/* Market Close Message: written and read back, then read and written back */
static void check_market_close_message(void) {
  MarketCloseMessage sent;
  MarketCloseMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_market_close_message(&sent);
  assert(encode_market_close_message(&sent, wire, 0) == 16);
  assert(decode_market_close_message(&got, wire, 0) == 16);
  equal_market_close_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_market_close_message(&got, wire, 0) == 16);
  assert(encode_market_close_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_start_of_spin_message();
  check_end_of_spin_message();
  check_market_open_message();
  check_market_close_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
