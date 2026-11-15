// lme/lmeselect/tradestatistics/LmeSelect_TradeStatistics_v4_18.c
/*
 * The London Metal Exchange LMEsource TradeStatistics
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

/* LMEsource packet header, giving the packet size, the number of messages it carries, the sequence number of the first of them and the time the packet was sent */
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

/* ---- Message Header: 4 bytes ------------------------------------------------- */

/* LMEsource message header, giving the size of the message and its type */
typedef struct {
  uint8_t msg_size[2];  /* bytes 0 to 1 */
  uint8_t msg_type[2];  /* bytes 2 to 3 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->msg_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->msg_type[i] = arbitrary(); }
}

/* Message Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_type[i]; }

  return at;
}

/* Message Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->msg_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->msg_type[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->msg_size[i] == written->msg_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->msg_type[i] == written->msg_type[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 4);
  assert(decode_message_header(&got, wire, 0) == 4);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 4);
  assert(encode_message_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Reset Message: 4 bytes ----------------------------------------- */

/* Sent on each multicast channel at start of day, and intraday in case of a disaster recovery. The client must ignore the sequence number of the Sequence Reset message itself and set the next expected sequence number to NewSeqNo, clear all cached data for all instruments and subscribe to the refresh channels to receive the current state of the market. */
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

/* ---- Trade Statistics Intraday Message: 42 bytes ----------------------------- */

/* Contains trade information for completed trades, provided on a snapshot basis. Off book trades resulting from Cross Order execution are not used in the calculation. */
typedef struct {
  uint8_t trading_venue[2];           /* bytes 0 to 1 */
  uint8_t time_of_event[8];           /* bytes 2 to 9 */
  uint8_t tradable_instrument_id[8];  /* bytes 10 to 17 */
  uint8_t open_price[8];              /* bytes 18 to 25 */
  uint8_t trade_high[8];              /* bytes 26 to 33 */
  uint8_t trade_low[8];               /* bytes 34 to 41 */
} TradeStatisticsIntradayMessage;

/* any Trade Statistics Intraday Message at all: every byte one the checker chooses */
static void any_trade_statistics_intraday_message(TradeStatisticsIntradayMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_of_event[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_low[i] = arbitrary(); }
}

/* Trade Statistics Intraday Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_trade_statistics_intraday_message(const TradeStatisticsIntradayMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_of_event[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tradable_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_low[i]; }

  return at;
}

/* Trade Statistics Intraday Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_trade_statistics_intraday_message(TradeStatisticsIntradayMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_of_event[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_low[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Statistics Intraday Message is what was written, byte for byte */
static void equal_trade_statistics_intraday_message(const TradeStatisticsIntradayMessage *read, const TradeStatisticsIntradayMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->trading_venue[i] == written->trading_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_of_event[i] == written->time_of_event[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tradable_instrument_id[i] == written->tradable_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_price[i] == written->open_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_high[i] == written->trade_high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_low[i] == written->trade_low[i]); }
}

/* Trade Statistics Intraday Message: written and read back, then read and written back */
static void check_trade_statistics_intraday_message(void) {
  TradeStatisticsIntradayMessage sent;
  TradeStatisticsIntradayMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_trade_statistics_intraday_message(&sent);
  assert(encode_trade_statistics_intraday_message(&sent, wire, 0) == 42);
  assert(decode_trade_statistics_intraday_message(&got, wire, 0) == 42);
  equal_trade_statistics_intraday_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_statistics_intraday_message(&got, wire, 0) == 42);
  assert(encode_trade_statistics_intraday_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_sequence_reset_message();
  check_trade_statistics_intraday_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
