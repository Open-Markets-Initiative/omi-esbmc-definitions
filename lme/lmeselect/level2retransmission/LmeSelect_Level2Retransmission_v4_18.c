// lme/lmeselect/level2retransmission/LmeSelect_Level2Retransmission_v4_18.c
/*
 * The London Metal Exchange LMEsource Level2 Retransmission
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

/* ---- Market State Contract Message: 42 bytes --------------------------------- */

/* Indicates the trading state of instruments at the contract level, for example Copper Futures or Aluminium Options. The ContractCode field is common across the Market State - Contract, Outright Definition and Strategy Definition messages and links the contract state to individual tradable instruments. */
typedef struct {
  uint8_t trading_venue[2];         /* bytes 0 to 1 */
  uint8_t time_of_event[8];         /* bytes 2 to 9 */
  uint8_t contract_code[12];        /* bytes 10 to 21 */
  uint8_t trading_state;            /* byte 22 */
  uint8_t start_time[8];            /* bytes 23 to 30 */
  uint8_t end_time[8];              /* bytes 31 to 38 */
  uint8_t trading_state_condition;  /* byte 39 */
  uint8_t filler_string_2[2];       /* bytes 40 to 41 */
} MarketStateContractMessage;

/* any Market State Contract Message at all: every byte one the checker chooses */
static void any_market_state_contract_message(MarketStateContractMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_of_event[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->contract_code[i] = arbitrary(); }
  record->trading_state = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->start_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_time[i] = arbitrary(); }
  record->trading_state_condition = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->filler_string_2[i] = arbitrary(); }
}

/* Market State Contract Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_market_state_contract_message(const MarketStateContractMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_of_event[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->contract_code[i]; }
  wire[at++] = record->trading_state;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->start_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_time[i]; }
  wire[at++] = record->trading_state_condition;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_string_2[i]; }

  return at;
}

/* Market State Contract Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_market_state_contract_message(MarketStateContractMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_of_event[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->contract_code[i] = wire[at++]; }
  record->trading_state = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->start_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_time[i] = wire[at++]; }
  record->trading_state_condition = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->filler_string_2[i] = wire[at++]; }

  return at;
}

/* what was read of Market State Contract Message is what was written, byte for byte */
static void equal_market_state_contract_message(const MarketStateContractMessage *read, const MarketStateContractMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->trading_venue[i] == written->trading_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_of_event[i] == written->time_of_event[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->contract_code[i] == written->contract_code[i]); }
  assert(read->trading_state == written->trading_state);
  for (size_t i = 0; i < 8; i++) { assert(read->start_time[i] == written->start_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_time[i] == written->end_time[i]); }
  assert(read->trading_state_condition == written->trading_state_condition);
  for (size_t i = 0; i < 2; i++) { assert(read->filler_string_2[i] == written->filler_string_2[i]); }
}

/* Market State Contract Message: written and read back, then read and written back */
static void check_market_state_contract_message(void) {
  MarketStateContractMessage sent;
  MarketStateContractMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_market_state_contract_message(&sent);
  assert(encode_market_state_contract_message(&sent, wire, 0) == 42);
  assert(decode_market_state_contract_message(&got, wire, 0) == 42);
  equal_market_state_contract_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_market_state_contract_message(&got, wire, 0) == 42);
  assert(encode_market_state_contract_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market State Instrument Message: 40 bytes ------------------------------- */

/* Indicates the trading state of an individual tradable instrument. Sent when the instrument state differs from that at contract level, for example when TOM goes into Post Trade before the contract. */
typedef struct {
  uint8_t trading_venue[2];           /* bytes 0 to 1 */
  uint8_t time_of_event[8];           /* bytes 2 to 9 */
  uint8_t tradable_instrument_id[8];  /* bytes 10 to 17 */
  uint8_t timetable_control_type;     /* byte 18 */
  uint8_t trading_state;              /* byte 19 */
  uint8_t start_time[8];              /* bytes 20 to 27 */
  uint8_t end_time[8];                /* bytes 28 to 35 */
  uint8_t trading_state_condition;    /* byte 36 */
  uint8_t filler_string_3[3];         /* bytes 37 to 39 */
} MarketStateInstrumentMessage;

/* any Market State Instrument Message at all: every byte one the checker chooses */
static void any_market_state_instrument_message(MarketStateInstrumentMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_of_event[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = arbitrary(); }
  record->timetable_control_type = arbitrary();
  record->trading_state = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->start_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_time[i] = arbitrary(); }
  record->trading_state_condition = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_string_3[i] = arbitrary(); }
}

/* Market State Instrument Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_market_state_instrument_message(const MarketStateInstrumentMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_of_event[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tradable_instrument_id[i]; }
  wire[at++] = record->timetable_control_type;
  wire[at++] = record->trading_state;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->start_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_time[i]; }
  wire[at++] = record->trading_state_condition;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_string_3[i]; }

  return at;
}

/* Market State Instrument Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_market_state_instrument_message(MarketStateInstrumentMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_of_event[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = wire[at++]; }
  record->timetable_control_type = wire[at++];
  record->trading_state = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->start_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_time[i] = wire[at++]; }
  record->trading_state_condition = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_string_3[i] = wire[at++]; }

  return at;
}

/* what was read of Market State Instrument Message is what was written, byte for byte */
static void equal_market_state_instrument_message(const MarketStateInstrumentMessage *read, const MarketStateInstrumentMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->trading_venue[i] == written->trading_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_of_event[i] == written->time_of_event[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tradable_instrument_id[i] == written->tradable_instrument_id[i]); }
  assert(read->timetable_control_type == written->timetable_control_type);
  assert(read->trading_state == written->trading_state);
  for (size_t i = 0; i < 8; i++) { assert(read->start_time[i] == written->start_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_time[i] == written->end_time[i]); }
  assert(read->trading_state_condition == written->trading_state_condition);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_string_3[i] == written->filler_string_3[i]); }
}

/* Market State Instrument Message: written and read back, then read and written back */
static void check_market_state_instrument_message(void) {
  MarketStateInstrumentMessage sent;
  MarketStateInstrumentMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_market_state_instrument_message(&sent);
  assert(encode_market_state_instrument_message(&sent, wire, 0) == 40);
  assert(decode_market_state_instrument_message(&got, wire, 0) == 40);
  equal_market_state_instrument_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_market_state_instrument_message(&got, wire, 0) == 40);
  assert(encode_market_state_instrument_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indicative Opening Price Message: 40 bytes ------------------------------ */

/* Carries the price at which a tradable instrument would open, computed by the uncrossing algorithm during Pre-Open. If there are no crossed prices no IOP is calculated or disseminated; where the book is not crossed but has both a bid and an offer, a mid price is calculated and published instead. At the transition from Pre-Open to Open an IOP message is published for every tradable instrument with both prices null and the volume zero, to indicate the prices are no longer valid. */
typedef struct {
  uint8_t trading_venue[2];                 /* bytes 0 to 1 */
  uint8_t time_of_event[8];                 /* bytes 2 to 9 */
  uint8_t tradable_instrument_id[8];        /* bytes 10 to 17 */
  uint8_t indicative_opening_price[8];      /* bytes 18 to 25 */
  uint8_t indicative_opening_volume[4];     /* bytes 26 to 29 */
  uint8_t indicative_opening_mid_price[8];  /* bytes 30 to 37 */
  uint8_t filler_string_2[2];               /* bytes 38 to 39 */
} IndicativeOpeningPriceMessage;

/* any Indicative Opening Price Message at all: every byte one the checker chooses */
static void any_indicative_opening_price_message(IndicativeOpeningPriceMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_of_event[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->indicative_opening_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_opening_mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_string_2[i] = arbitrary(); }
}

/* Indicative Opening Price Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_indicative_opening_price_message(const IndicativeOpeningPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_of_event[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tradable_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_opening_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->indicative_opening_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_opening_mid_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_string_2[i]; }

  return at;
}

/* Indicative Opening Price Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_indicative_opening_price_message(IndicativeOpeningPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_of_event[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->indicative_opening_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_opening_mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_string_2[i] = wire[at++]; }

  return at;
}

/* what was read of Indicative Opening Price Message is what was written, byte for byte */
static void equal_indicative_opening_price_message(const IndicativeOpeningPriceMessage *read, const IndicativeOpeningPriceMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->trading_venue[i] == written->trading_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_of_event[i] == written->time_of_event[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tradable_instrument_id[i] == written->tradable_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_opening_price[i] == written->indicative_opening_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->indicative_opening_volume[i] == written->indicative_opening_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_opening_mid_price[i] == written->indicative_opening_mid_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_string_2[i] == written->filler_string_2[i]); }
}

/* Indicative Opening Price Message: written and read back, then read and written back */
static void check_indicative_opening_price_message(void) {
  IndicativeOpeningPriceMessage sent;
  IndicativeOpeningPriceMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_indicative_opening_price_message(&sent);
  assert(encode_indicative_opening_price_message(&sent, wire, 0) == 40);
  assert(decode_indicative_opening_price_message(&got, wire, 0) == 40);
  equal_indicative_opening_price_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_indicative_opening_price_message(&got, wire, 0) == 40);
  assert(encode_indicative_opening_price_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Request Message: 26 bytes ----------------------------------------- */

/* Generated when a request for quote is accepted by the Matching Engine. */
typedef struct {
  uint8_t trading_venue[2];           /* bytes 0 to 1 */
  uint8_t time_of_event[8];           /* bytes 2 to 9 */
  uint8_t tradable_instrument_id[8];  /* bytes 10 to 17 */
  uint8_t quote_request_type;         /* byte 18 */
  uint8_t buy_sell;                   /* byte 19 */
  uint8_t volume[4];                  /* bytes 20 to 23 */
  uint8_t filler_string_2[2];         /* bytes 24 to 25 */
} QuoteRequestMessage;

/* any Quote Request Message at all: every byte one the checker chooses */
static void any_quote_request_message(QuoteRequestMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_of_event[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = arbitrary(); }
  record->quote_request_type = arbitrary();
  record->buy_sell = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_string_2[i] = arbitrary(); }
}

/* Quote Request Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_quote_request_message(const QuoteRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_of_event[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tradable_instrument_id[i]; }
  wire[at++] = record->quote_request_type;
  wire[at++] = record->buy_sell;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_string_2[i]; }

  return at;
}

/* Quote Request Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_quote_request_message(QuoteRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_of_event[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = wire[at++]; }
  record->quote_request_type = wire[at++];
  record->buy_sell = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_string_2[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Request Message is what was written, byte for byte */
static void equal_quote_request_message(const QuoteRequestMessage *read, const QuoteRequestMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->trading_venue[i] == written->trading_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_of_event[i] == written->time_of_event[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tradable_instrument_id[i] == written->tradable_instrument_id[i]); }
  assert(read->quote_request_type == written->quote_request_type);
  assert(read->buy_sell == written->buy_sell);
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_string_2[i] == written->filler_string_2[i]); }
}

/* Quote Request Message: written and read back, then read and written back */
static void check_quote_request_message(void) {
  QuoteRequestMessage sent;
  QuoteRequestMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_quote_request_message(&sent);
  assert(encode_quote_request_message(&sent, wire, 0) == 26);
  assert(decode_quote_request_message(&got, wire, 0) == 26);
  equal_quote_request_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_request_message(&got, wire, 0) == 26);
  assert(encode_quote_request_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Book Clear Message: 18 bytes -------------------------------------- */

/* Generated when the order book is required to be cleared, for example after the transition between certain market states, or when an instrument's Trading State Condition is Trade Halt. Following an Order Book Clear, if an instrument is subsequently open for trading any resting orders are sent as Top Of Book, Aggregate Order Book or Order Add messages to allow clients to rebuild the order book. It is not published when an instrument enters or leaves Trade Pause. */
typedef struct {
  uint8_t trading_venue[2];           /* bytes 0 to 1 */
  uint8_t time_of_event[8];           /* bytes 2 to 9 */
  uint8_t tradable_instrument_id[8];  /* bytes 10 to 17 */
} OrderBookClearMessage;

/* any Order Book Clear Message at all: every byte one the checker chooses */
static void any_order_book_clear_message(OrderBookClearMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_of_event[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = arbitrary(); }
}

/* Order Book Clear Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_order_book_clear_message(const OrderBookClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_of_event[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tradable_instrument_id[i]; }

  return at;
}

/* Order Book Clear Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_order_book_clear_message(OrderBookClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_of_event[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Book Clear Message is what was written, byte for byte */
static void equal_order_book_clear_message(const OrderBookClearMessage *read, const OrderBookClearMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->trading_venue[i] == written->trading_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_of_event[i] == written->time_of_event[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tradable_instrument_id[i] == written->tradable_instrument_id[i]); }
}

/* Order Book Clear Message: written and read back, then read and written back */
static void check_order_book_clear_message(void) {
  OrderBookClearMessage sent;
  OrderBookClearMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_order_book_clear_message(&sent);
  assert(encode_order_book_clear_message(&sent, wire, 0) == 18);
  assert(decode_order_book_clear_message(&got, wire, 0) == 18);
  equal_order_book_clear_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_clear_message(&got, wire, 0) == 18);
  assert(encode_order_book_clear_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cross Request Message: 40 bytes ----------------------------------------- */

/* Generated when a cross request is created on LMEselect. */
typedef struct {
  uint8_t trading_venue[2];           /* bytes 0 to 1 */
  uint8_t time_of_event[8];           /* bytes 2 to 9 */
  uint8_t tradable_instrument_id[8];  /* bytes 10 to 17 */
  uint8_t cross_id[8];                /* bytes 18 to 25 */
  uint8_t volume[4];                  /* bytes 26 to 29 */
  uint8_t expire_time[8];             /* bytes 30 to 37 */
  uint8_t filler_string_2[2];         /* bytes 38 to 39 */
} CrossRequestMessage;

/* any Cross Request Message at all: every byte one the checker chooses */
static void any_cross_request_message(CrossRequestMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_of_event[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_string_2[i] = arbitrary(); }
}

/* Cross Request Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_cross_request_message(const CrossRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_of_event[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tradable_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expire_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_string_2[i]; }

  return at;
}

/* Cross Request Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_cross_request_message(CrossRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_of_event[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_string_2[i] = wire[at++]; }

  return at;
}

/* what was read of Cross Request Message is what was written, byte for byte */
static void equal_cross_request_message(const CrossRequestMessage *read, const CrossRequestMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->trading_venue[i] == written->trading_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_of_event[i] == written->time_of_event[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tradable_instrument_id[i] == written->tradable_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_string_2[i] == written->filler_string_2[i]); }
}

/* Cross Request Message: written and read back, then read and written back */
static void check_cross_request_message(void) {
  CrossRequestMessage sent;
  CrossRequestMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_cross_request_message(&sent);
  assert(encode_cross_request_message(&sent, wire, 0) == 40);
  assert(decode_cross_request_message(&got, wire, 0) == 40);
  equal_cross_request_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_cross_request_message(&got, wire, 0) == 40);
  assert(encode_cross_request_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Message: 12 bytes ------------------------------------------------- */

/* Enables client authentication. Not required for multicast channels and only used for retransmission requests. The client sends a Logon containing a username, to which LMEsource responds with a Logon Response. */
typedef struct {
  uint8_t username[12];  /* bytes 0 to 11 */
} LogonMessage;

/* any Logon Message at all: every byte one the checker chooses */
static void any_logon_message(LogonMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->username[i] = arbitrary(); }
}

/* Logon Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_logon_message(const LogonMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->username[i]; }

  return at;
}

/* Logon Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_logon_message(LogonMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->username[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Message is what was written, byte for byte */
static void equal_logon_message(const LogonMessage *read, const LogonMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->username[i] == written->username[i]); }
}

/* Logon Message: written and read back, then read and written back */
static void check_logon_message(void) {
  LogonMessage sent;
  LogonMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_logon_message(&sent);
  assert(encode_logon_message(&sent, wire, 0) == 12);
  assert(decode_logon_message(&got, wire, 0) == 12);
  equal_logon_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_message(&got, wire, 0) == 12);
  assert(encode_logon_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Response Message: 4 bytes ----------------------------------------- */

/* Response to a Logon, carrying the status of the session. */
typedef struct {
  uint8_t session_status;      /* byte 0 */
  uint8_t filler_string_3[3];  /* bytes 1 to 3 */
} LogonResponseMessage;

/* any Logon Response Message at all: every byte one the checker chooses */
static void any_logon_response_message(LogonResponseMessage *record) {
  record->session_status = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_string_3[i] = arbitrary(); }
}

/* Logon Response Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_logon_response_message(const LogonResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->session_status;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_string_3[i]; }

  return at;
}

/* Logon Response Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_logon_response_message(LogonResponseMessage *record, const uint8_t *wire, size_t at) {
  record->session_status = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_string_3[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Response Message is what was written, byte for byte */
static void equal_logon_response_message(const LogonResponseMessage *read, const LogonResponseMessage *written) {
  assert(read->session_status == written->session_status);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_string_3[i] == written->filler_string_3[i]); }
}

/* Logon Response Message: written and read back, then read and written back */
static void check_logon_response_message(void) {
  LogonResponseMessage sent;
  LogonResponseMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_logon_response_message(&sent);
  assert(encode_logon_response_message(&sent, wire, 0) == 4);
  assert(decode_logon_response_message(&got, wire, 0) == 4);
  equal_logon_response_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_response_message(&got, wire, 0) == 4);
  assert(encode_logon_response_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Request Message: 12 bytes -------------------------------- */

/* Requests the retransmission of a range of messages on a multicast channel. */
typedef struct {
  uint8_t channel_id[2];       /* bytes 0 to 1 */
  uint8_t filler_string_2[2];  /* bytes 2 to 3 */
  uint8_t begin_seq_num[4];    /* bytes 4 to 7 */
  uint8_t end_seq_num[4];      /* bytes 8 to 11 */
} RetransmissionRequestMessage;

/* any Retransmission Request Message at all: every byte one the checker chooses */
static void any_retransmission_request_message(RetransmissionRequestMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_string_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = arbitrary(); }
}

/* Retransmission Request Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_request_message(const RetransmissionRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_string_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->begin_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_seq_num[i]; }

  return at;
}

/* Retransmission Request Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_request_message(RetransmissionRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_string_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Retransmission Request Message is what was written, byte for byte */
static void equal_retransmission_request_message(const RetransmissionRequestMessage *read, const RetransmissionRequestMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_id[i] == written->channel_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_string_2[i] == written->filler_string_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->begin_seq_num[i] == written->begin_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_seq_num[i] == written->end_seq_num[i]); }
}

/* Retransmission Request Message: written and read back, then read and written back */
static void check_retransmission_request_message(void) {
  RetransmissionRequestMessage sent;
  RetransmissionRequestMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_retransmission_request_message(&sent);
  assert(encode_retransmission_request_message(&sent, wire, 0) == 12);
  assert(decode_retransmission_request_message(&got, wire, 0) == 12);
  equal_retransmission_request_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_request_message(&got, wire, 0) == 12);
  assert(encode_retransmission_request_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Response Message: 12 bytes ------------------------------- */

/* Response to a Retransmission Request, carrying the status of the request and the sequence range being resent. */
typedef struct {
  uint8_t channel_id[2];     /* bytes 0 to 1 */
  uint8_t retrans_status;    /* byte 2 */
  uint8_t filler_string_1;   /* byte 3 */
  uint8_t begin_seq_num[4];  /* bytes 4 to 7 */
  uint8_t end_seq_num[4];    /* bytes 8 to 11 */
} RetransmissionResponseMessage;

/* any Retransmission Response Message at all: every byte one the checker chooses */
static void any_retransmission_response_message(RetransmissionResponseMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_id[i] = arbitrary(); }
  record->retrans_status = arbitrary();
  record->filler_string_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = arbitrary(); }
}

/* Retransmission Response Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_response_message(const RetransmissionResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_id[i]; }
  wire[at++] = record->retrans_status;
  wire[at++] = record->filler_string_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->begin_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_seq_num[i]; }

  return at;
}

/* Retransmission Response Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_response_message(RetransmissionResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_id[i] = wire[at++]; }
  record->retrans_status = wire[at++];
  record->filler_string_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Retransmission Response Message is what was written, byte for byte */
static void equal_retransmission_response_message(const RetransmissionResponseMessage *read, const RetransmissionResponseMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_id[i] == written->channel_id[i]); }
  assert(read->retrans_status == written->retrans_status);
  assert(read->filler_string_1 == written->filler_string_1);
  for (size_t i = 0; i < 4; i++) { assert(read->begin_seq_num[i] == written->begin_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_seq_num[i] == written->end_seq_num[i]); }
}

/* Retransmission Response Message: written and read back, then read and written back */
static void check_retransmission_response_message(void) {
  RetransmissionResponseMessage sent;
  RetransmissionResponseMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_retransmission_response_message(&sent);
  assert(encode_retransmission_response_message(&sent, wire, 0) == 12);
  assert(decode_retransmission_response_message(&got, wire, 0) == 12);
  equal_retransmission_response_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_response_message(&got, wire, 0) == 12);
  assert(encode_retransmission_response_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_sequence_reset_message();
  check_market_state_contract_message();
  check_market_state_instrument_message();
  check_indicative_opening_price_message();
  check_quote_request_message();
  check_order_book_clear_message();
  check_cross_request_message();
  check_logon_message();
  check_logon_response_message();
  check_retransmission_request_message();
  check_retransmission_response_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
