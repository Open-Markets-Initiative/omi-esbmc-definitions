// hkex/hkexsecurities/standard/HkexSecurities_Standard_v1_45.c
/*
 * Hong Kong Exchanges and Clearing Orion Market Data Cash Standard
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

/* ---- Packet Header: 16 bytes ------------------------------------------------- */

/* Omd packet header (no payload compression; byte 3 is Filler) */
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

/* ---- Msg Header: 4 bytes ----------------------------------------------------- */

/* Omd message header */
typedef struct {
  uint8_t msg_size[2];  /* bytes 0 to 1 */
  uint8_t msg_type[2];  /* bytes 2 to 3 */
} MsgHeader;

/* any Msg Header at all: every byte one the checker chooses */
static void any_msg_header(MsgHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->msg_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->msg_type[i] = arbitrary(); }
}

/* Msg Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_msg_header(const MsgHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_type[i]; }

  return at;
}

/* Msg Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_msg_header(MsgHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->msg_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->msg_type[i] = wire[at++]; }

  return at;
}

/* what was read of Msg Header is what was written, byte for byte */
static void equal_msg_header(const MsgHeader *read, const MsgHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->msg_size[i] == written->msg_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->msg_type[i] == written->msg_type[i]); }
}

/* Msg Header: written and read back, then read and written back */
static void check_msg_header(void) {
  MsgHeader sent;
  MsgHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_msg_header(&sent);
  assert(encode_msg_header(&sent, wire, 0) == 4);
  assert(decode_msg_header(&got, wire, 0) == 4);
  equal_msg_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_msg_header(&got, wire, 0) == 4);
  assert(encode_msg_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Closing Price Message: 12 bytes ----------------------------------------- */

/* The Closing Price message is generated near the end of the business day for each security. If the closing price is not available, ClosingPrice is set to 0. NumberOfTrades is not populated for SS (OMD Securities Standard) clients. */
typedef struct {
  uint8_t security_code[4];     /* bytes 0 to 3 */
  uint8_t closing_price[4];     /* bytes 4 to 7 */
  uint8_t number_of_trades[4];  /* bytes 8 to 11 */
} ClosingPriceMessage;

/* any Closing Price Message at all: every byte one the checker chooses */
static void any_closing_price_message(ClosingPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_trades[i] = arbitrary(); }
}

/* Closing Price Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_closing_price_message(const ClosingPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->closing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_trades[i]; }

  return at;
}

/* Closing Price Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_closing_price_message(ClosingPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_trades[i] = wire[at++]; }

  return at;
}

/* what was read of Closing Price Message is what was written, byte for byte */
static void equal_closing_price_message(const ClosingPriceMessage *read, const ClosingPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_trades[i] == written->number_of_trades[i]); }
}

/* Closing Price Message: written and read back, then read and written back */
static void check_closing_price_message(void) {
  ClosingPriceMessage sent;
  ClosingPriceMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_closing_price_message(&sent);
  assert(encode_closing_price_message(&sent, wire, 0) == 12);
  assert(decode_closing_price_message(&got, wire, 0) == 12);
  equal_closing_price_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_closing_price_message(&got, wire, 0) == 12);
  assert(encode_closing_price_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Reset Message: 4 bytes ----------------------------------------- */

/* The Sequence Reset message is sent on each multicast channel at start of day. It may also be sent when there is a need for the rectification of stock reference data before market open. */
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

/* ---- Disaster Recovery Signal Message: 4 bytes ------------------------------- */

/* The Disaster Recovery (DR) Signal message is sent on a dedicated multicast channel whenever a site failover scenario is triggered. */
typedef struct {
  uint8_t dr_status[4];  /* bytes 0 to 3 */
} DisasterRecoverySignalMessage;

/* any Disaster Recovery Signal Message at all: every byte one the checker chooses */
static void any_disaster_recovery_signal_message(DisasterRecoverySignalMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->dr_status[i] = arbitrary(); }
}

/* Disaster Recovery Signal Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_disaster_recovery_signal_message(const DisasterRecoverySignalMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->dr_status[i]; }

  return at;
}

/* Disaster Recovery Signal Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_disaster_recovery_signal_message(DisasterRecoverySignalMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->dr_status[i] = wire[at++]; }

  return at;
}

/* what was read of Disaster Recovery Signal Message is what was written, byte for byte */
static void equal_disaster_recovery_signal_message(const DisasterRecoverySignalMessage *read, const DisasterRecoverySignalMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->dr_status[i] == written->dr_status[i]); }
}

/* Disaster Recovery Signal Message: written and read back, then read and written back */
static void check_disaster_recovery_signal_message(void) {
  DisasterRecoverySignalMessage sent;
  DisasterRecoverySignalMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_disaster_recovery_signal_message(&sent);
  assert(encode_disaster_recovery_signal_message(&sent, wire, 0) == 4);
  assert(decode_disaster_recovery_signal_message(&got, wire, 0) == 4);
  equal_disaster_recovery_signal_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_disaster_recovery_signal_message(&got, wire, 0) == 4);
  assert(encode_disaster_recovery_signal_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indicative Equilibrium Price Message: 16 bytes -------------------------- */

/* The Indicative Equilibrium Price (IEP) message is generated whenever there is change of the IEP or Indicative Equilibrium Volume (IEV) during Pre-Opening Session (POS) or Closing Auction Session (CAS). The IEP is 0 when IEP does not exist. */
typedef struct {
  uint8_t security_code[4];       /* bytes 0 to 3 */
  uint8_t price[4];               /* bytes 4 to 7 */
  uint8_t aggregate_quantity[8];  /* bytes 8 to 15 */
} IndicativeEquilibriumPriceMessage;

/* any Indicative Equilibrium Price Message at all: every byte one the checker chooses */
static void any_indicative_equilibrium_price_message(IndicativeEquilibriumPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->aggregate_quantity[i] = arbitrary(); }
}

/* Indicative Equilibrium Price Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_indicative_equilibrium_price_message(const IndicativeEquilibriumPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->aggregate_quantity[i]; }

  return at;
}

/* Indicative Equilibrium Price Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_indicative_equilibrium_price_message(IndicativeEquilibriumPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->aggregate_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Indicative Equilibrium Price Message is what was written, byte for byte */
static void equal_indicative_equilibrium_price_message(const IndicativeEquilibriumPriceMessage *read, const IndicativeEquilibriumPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->aggregate_quantity[i] == written->aggregate_quantity[i]); }
}

/* Indicative Equilibrium Price Message: written and read back, then read and written back */
static void check_indicative_equilibrium_price_message(void) {
  IndicativeEquilibriumPriceMessage sent;
  IndicativeEquilibriumPriceMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_indicative_equilibrium_price_message(&sent);
  assert(encode_indicative_equilibrium_price_message(&sent, wire, 0) == 16);
  assert(decode_indicative_equilibrium_price_message(&got, wire, 0) == 16);
  equal_indicative_equilibrium_price_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_indicative_equilibrium_price_message(&got, wire, 0) == 16);
  assert(encode_indicative_equilibrium_price_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Nominal Price Message: 8 bytes ------------------------------------------ */

/* The Nominal message may be generated when an order is added, deleted or modified in a book or when trade or trade cancel is performed. Before the first Nominal Price message, the nominal price should be the same as the previous closing price provided in Security Definition (11). */
typedef struct {
  uint8_t security_code[4];  /* bytes 0 to 3 */
  uint8_t nominal_price[4];  /* bytes 4 to 7 */
} NominalPriceMessage;

/* any Nominal Price Message at all: every byte one the checker chooses */
static void any_nominal_price_message(NominalPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nominal_price[i] = arbitrary(); }
}

/* Nominal Price Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_nominal_price_message(const NominalPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nominal_price[i]; }

  return at;
}

/* Nominal Price Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_nominal_price_message(NominalPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nominal_price[i] = wire[at++]; }

  return at;
}

/* what was read of Nominal Price Message is what was written, byte for byte */
static void equal_nominal_price_message(const NominalPriceMessage *read, const NominalPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nominal_price[i] == written->nominal_price[i]); }
}

/* Nominal Price Message: written and read back, then read and written back */
static void check_nominal_price_message(void) {
  NominalPriceMessage sent;
  NominalPriceMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_nominal_price_message(&sent);
  assert(encode_nominal_price_message(&sent, wire, 0) == 8);
  assert(decode_nominal_price_message(&got, wire, 0) == 8);
  equal_nominal_price_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_nominal_price_message(&got, wire, 0) == 8);
  assert(encode_nominal_price_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Imbalance Message: 16 bytes --------------------------------------- */

/* The Order Imbalance message provides order imbalance information at the Indicative Equilibrium Price (IEP) during the Pre-Opening Session (POS) and Closing Auction Session (CAS). */
typedef struct {
  uint8_t security_code[4];             /* bytes 0 to 3 */
  uint8_t order_imbalance_direction;    /* byte 4 */
  uint8_t filler_1;                     /* byte 5 */
  uint8_t order_imbalance_quantity[8];  /* bytes 6 to 13 */
  uint8_t filler_2[2];                  /* bytes 14 to 15 */
} OrderImbalanceMessage;

/* any Order Imbalance Message at all: every byte one the checker chooses */
static void any_order_imbalance_message(OrderImbalanceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  record->order_imbalance_direction = arbitrary();
  record->filler_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_imbalance_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
}

/* Order Imbalance Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_order_imbalance_message(const OrderImbalanceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  wire[at++] = record->order_imbalance_direction;
  wire[at++] = record->filler_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_imbalance_quantity[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }

  return at;
}

/* Order Imbalance Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_order_imbalance_message(OrderImbalanceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  record->order_imbalance_direction = wire[at++];
  record->filler_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_imbalance_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }

  return at;
}

/* what was read of Order Imbalance Message is what was written, byte for byte */
static void equal_order_imbalance_message(const OrderImbalanceMessage *read, const OrderImbalanceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  assert(read->order_imbalance_direction == written->order_imbalance_direction);
  assert(read->filler_1 == written->filler_1);
  for (size_t i = 0; i < 8; i++) { assert(read->order_imbalance_quantity[i] == written->order_imbalance_quantity[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
}

/* Order Imbalance Message: written and read back, then read and written back */
static void check_order_imbalance_message(void) {
  OrderImbalanceMessage sent;
  OrderImbalanceMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_order_imbalance_message(&sent);
  assert(encode_order_imbalance_message(&sent, wire, 0) == 16);
  assert(decode_order_imbalance_message(&got, wire, 0) == 16);
  equal_order_imbalance_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_order_imbalance_message(&got, wire, 0) == 16);
  assert(encode_order_imbalance_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Definition Message: 36 bytes ------------------------------------- */

/* The Market Definition message is generated at the start of the business day for each market segment. */
typedef struct {
  uint8_t market_code[4];           /* bytes 0 to 3 */
  uint8_t market_name[25];          /* bytes 4 to 28 */
  uint8_t currency_code[3];         /* bytes 29 to 31 */
  uint8_t number_of_securities[4];  /* bytes 32 to 35 */
} MarketDefinitionMessage;

/* any Market Definition Message at all: every byte one the checker chooses */
static void any_market_definition_message(MarketDefinitionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->market_name[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_securities[i] = arbitrary(); }
}

/* Market Definition Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_market_definition_message(const MarketDefinitionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_code[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->market_name[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_securities[i]; }

  return at;
}

/* Market Definition Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_market_definition_message(MarketDefinitionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->market_name[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_securities[i] = wire[at++]; }

  return at;
}

/* what was read of Market Definition Message is what was written, byte for byte */
static void equal_market_definition_message(const MarketDefinitionMessage *read, const MarketDefinitionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_code[i] == written->market_code[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->market_name[i] == written->market_name[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency_code[i] == written->currency_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_securities[i] == written->number_of_securities[i]); }
}

/* Market Definition Message: written and read back, then read and written back */
static void check_market_definition_message(void) {
  MarketDefinitionMessage sent;
  MarketDefinitionMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_market_definition_message(&sent);
  assert(encode_market_definition_message(&sent, wire, 0) == 36);
  assert(decode_market_definition_message(&got, wire, 0) == 36);
  equal_market_definition_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_market_definition_message(&got, wire, 0) == 36);
  assert(encode_market_definition_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Face Value Composite: 9 bytes ------------------------------------------- */

/* Bond face value scaled at runtime by DecimalsInFaceValue. 0 mantissa means Not available. */
typedef struct {
  uint8_t face_value[8];           /* bytes 0 to 7 */
  uint8_t decimals_in_face_value;  /* byte 8 */
} FaceValueComposite;

/* any Face Value Composite at all: every byte one the checker chooses */
static void any_face_value_composite(FaceValueComposite *record) {
  for (size_t i = 0; i < 8; i++) { record->face_value[i] = arbitrary(); }
  record->decimals_in_face_value = arbitrary();
}

/* Face Value Composite to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_face_value_composite(const FaceValueComposite *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->face_value[i]; }
  wire[at++] = record->decimals_in_face_value;

  return at;
}

/* Face Value Composite off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_face_value_composite(FaceValueComposite *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->face_value[i] = wire[at++]; }
  record->decimals_in_face_value = wire[at++];

  return at;
}

/* what was read of Face Value Composite is what was written, byte for byte */
static void equal_face_value_composite(const FaceValueComposite *read, const FaceValueComposite *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->face_value[i] == written->face_value[i]); }
  assert(read->decimals_in_face_value == written->decimals_in_face_value);
}

/* Face Value Composite: written and read back, then read and written back */
static void check_face_value_composite(void) {
  FaceValueComposite sent;
  FaceValueComposite got;
  uint8_t wire[9];
  uint8_t again[9];

  any_face_value_composite(&sent);
  assert(encode_face_value_composite(&sent, wire, 0) == 9);
  assert(decode_face_value_composite(&got, wire, 0) == 9);
  equal_face_value_composite(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_face_value_composite(&got, wire, 0) == 9);
  assert(encode_face_value_composite(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Call Price Composite: 5 bytes ------------------------------------------- */

/* CBBC call price scaled at runtime by DecimalsInCallPrice. 0 mantissa means Not available. */
typedef struct {
  uint8_t call_price[4];           /* bytes 0 to 3 */
  uint8_t decimals_in_call_price;  /* byte 4 */
} CallPriceComposite;

/* any Call Price Composite at all: every byte one the checker chooses */
static void any_call_price_composite(CallPriceComposite *record) {
  for (size_t i = 0; i < 4; i++) { record->call_price[i] = arbitrary(); }
  record->decimals_in_call_price = arbitrary();
}

/* Call Price Composite to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_call_price_composite(const CallPriceComposite *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->call_price[i]; }
  wire[at++] = record->decimals_in_call_price;

  return at;
}

/* Call Price Composite off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_call_price_composite(CallPriceComposite *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->call_price[i] = wire[at++]; }
  record->decimals_in_call_price = wire[at++];

  return at;
}

/* what was read of Call Price Composite is what was written, byte for byte */
static void equal_call_price_composite(const CallPriceComposite *read, const CallPriceComposite *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->call_price[i] == written->call_price[i]); }
  assert(read->decimals_in_call_price == written->decimals_in_call_price);
}

/* Call Price Composite: written and read back, then read and written back */
static void check_call_price_composite(void) {
  CallPriceComposite sent;
  CallPriceComposite got;
  uint8_t wire[5];
  uint8_t again[5];

  any_call_price_composite(&sent);
  assert(encode_call_price_composite(&sent, wire, 0) == 5);
  assert(decode_call_price_composite(&got, wire, 0) == 5);
  equal_call_price_composite(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_call_price_composite(&got, wire, 0) == 5);
  assert(encode_call_price_composite(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Entitlement Composite: 5 bytes ------------------------------------------ */

/* Warrant entitlement scaled at runtime by DecimalsInEntitlement. 0 mantissa means Not available. */
typedef struct {
  uint8_t entitlement[4];           /* bytes 0 to 3 */
  uint8_t decimals_in_entitlement;  /* byte 4 */
} EntitlementComposite;

/* any Entitlement Composite at all: every byte one the checker chooses */
static void any_entitlement_composite(EntitlementComposite *record) {
  for (size_t i = 0; i < 4; i++) { record->entitlement[i] = arbitrary(); }
  record->decimals_in_entitlement = arbitrary();
}

/* Entitlement Composite to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_entitlement_composite(const EntitlementComposite *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entitlement[i]; }
  wire[at++] = record->decimals_in_entitlement;

  return at;
}

/* Entitlement Composite off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_entitlement_composite(EntitlementComposite *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->entitlement[i] = wire[at++]; }
  record->decimals_in_entitlement = wire[at++];

  return at;
}

/* what was read of Entitlement Composite is what was written, byte for byte */
static void equal_entitlement_composite(const EntitlementComposite *read, const EntitlementComposite *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->entitlement[i] == written->entitlement[i]); }
  assert(read->decimals_in_entitlement == written->decimals_in_entitlement);
}

/* Entitlement Composite: written and read back, then read and written back */
static void check_entitlement_composite(void) {
  EntitlementComposite sent;
  EntitlementComposite got;
  uint8_t wire[5];
  uint8_t again[5];

  any_entitlement_composite(&sent);
  assert(encode_entitlement_composite(&sent, wire, 0) == 5);
  assert(decode_entitlement_composite(&got, wire, 0) == 5);
  equal_entitlement_composite(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_entitlement_composite(&got, wire, 0) == 5);
  assert(encode_entitlement_composite(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Currency Rate Message: 12 bytes ----------------------------------------- */

/* The Currency Rate message provides the foreign exchange conversion rates between various foreign currencies and the Hong Kong dollar. */
typedef struct {
  uint8_t currency_code[3];    /* bytes 0 to 2 */
  uint8_t filler_1;            /* byte 3 */
  uint8_t currency_factor[2];  /* bytes 4 to 5 */
  uint8_t filler_2[2];         /* bytes 6 to 7 */
  uint8_t currency_rate[4];    /* bytes 8 to 11 */
} CurrencyRateMessage;

/* any Currency Rate Message at all: every byte one the checker chooses */
static void any_currency_rate_message(CurrencyRateMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = arbitrary(); }
  record->filler_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->currency_factor[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->currency_rate[i] = arbitrary(); }
}

/* Currency Rate Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_currency_rate_message(const CurrencyRateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency_code[i]; }
  wire[at++] = record->filler_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->currency_factor[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->currency_rate[i]; }

  return at;
}

/* Currency Rate Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_currency_rate_message(CurrencyRateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = wire[at++]; }
  record->filler_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->currency_factor[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->currency_rate[i] = wire[at++]; }

  return at;
}

/* what was read of Currency Rate Message is what was written, byte for byte */
static void equal_currency_rate_message(const CurrencyRateMessage *read, const CurrencyRateMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->currency_code[i] == written->currency_code[i]); }
  assert(read->filler_1 == written->filler_1);
  for (size_t i = 0; i < 2; i++) { assert(read->currency_factor[i] == written->currency_factor[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->currency_rate[i] == written->currency_rate[i]); }
}

/* Currency Rate Message: written and read back, then read and written back */
static void check_currency_rate_message(void) {
  CurrencyRateMessage sent;
  CurrencyRateMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_currency_rate_message(&sent);
  assert(encode_currency_rate_message(&sent, wire, 0) == 12);
  assert(decode_currency_rate_message(&got, wire, 0) == 12);
  equal_currency_rate_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_currency_rate_message(&got, wire, 0) == 12);
  assert(encode_currency_rate_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reference Price Message: 16 bytes --------------------------------------- */

/* Reference price, lower and upper price limits for order input during an applicable auction session (POS or CAS). Sent again when there is any change. */
typedef struct {
  uint8_t security_code[4];    /* bytes 0 to 3 */
  uint8_t reference_price[4];  /* bytes 4 to 7 */
  uint8_t lower_price[4];      /* bytes 8 to 11 */
  uint8_t upper_price[4];      /* bytes 12 to 15 */
} ReferencePriceMessage;

/* any Reference Price Message at all: every byte one the checker chooses */
static void any_reference_price_message(ReferencePriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lower_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->upper_price[i] = arbitrary(); }
}

/* Reference Price Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_reference_price_message(const ReferencePriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lower_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->upper_price[i]; }

  return at;
}

/* Reference Price Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_reference_price_message(ReferencePriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lower_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->upper_price[i] = wire[at++]; }

  return at;
}

/* what was read of Reference Price Message is what was written, byte for byte */
static void equal_reference_price_message(const ReferencePriceMessage *read, const ReferencePriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lower_price[i] == written->lower_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->upper_price[i] == written->upper_price[i]); }
}

/* Reference Price Message: written and read back, then read and written back */
static void check_reference_price_message(void) {
  ReferencePriceMessage sent;
  ReferencePriceMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_reference_price_message(&sent);
  assert(encode_reference_price_message(&sent, wire, 0) == 16);
  assert(decode_reference_price_message(&got, wire, 0) == 16);
  equal_reference_price_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_reference_price_message(&got, wire, 0) == 16);
  assert(encode_reference_price_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Complete Message: 4 bytes --------------------------------------- */

/* This message is published to mark the end of a refresh. */
typedef struct {
  uint8_t last_seq_num[4];  /* bytes 0 to 3 */
} RefreshCompleteMessage;

/* any Refresh Complete Message at all: every byte one the checker chooses */
static void any_refresh_complete_message(RefreshCompleteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->last_seq_num[i] = arbitrary(); }
}

/* Refresh Complete Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_refresh_complete_message(const RefreshCompleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_seq_num[i]; }

  return at;
}

/* Refresh Complete Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_refresh_complete_message(RefreshCompleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Refresh Complete Message is what was written, byte for byte */
static void equal_refresh_complete_message(const RefreshCompleteMessage *read, const RefreshCompleteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_seq_num[i] == written->last_seq_num[i]); }
}

/* Refresh Complete Message: written and read back, then read and written back */
static void check_refresh_complete_message(void) {
  RefreshCompleteMessage sent;
  RefreshCompleteMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_refresh_complete_message(&sent);
  assert(encode_refresh_complete_message(&sent, wire, 0) == 4);
  assert(decode_refresh_complete_message(&got, wire, 0) == 4);
  equal_refresh_complete_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_complete_message(&got, wire, 0) == 4);
  assert(encode_refresh_complete_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Statistics Message: 48 bytes -------------------------------------------- */

/* The Statistics message provides statistics including volume-weighted average price and turnover. Generated (excluding overseas trades) once after CTS/auction match, manual trade, odd lot trade, or trade cancel. VWAP is not populated for SS (OMD Securities Standard) clients. */
typedef struct {
  uint8_t security_code[4];             /* bytes 0 to 3 */
  uint8_t shares_traded[8];             /* bytes 4 to 11 */
  uint8_t turnover[8];                  /* bytes 12 to 19 */
  uint8_t high_price[4];                /* bytes 20 to 23 */
  uint8_t low_price[4];                 /* bytes 24 to 27 */
  uint8_t last_price[4];                /* bytes 28 to 31 */
  uint8_t vwap[4];                      /* bytes 32 to 35 */
  uint8_t short_sell_shares_traded[4];  /* bytes 36 to 39 */
  uint8_t short_sell_turnover[8];       /* bytes 40 to 47 */
} StatisticsMessage;

/* any Statistics Message at all: every byte one the checker chooses */
static void any_statistics_message(StatisticsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->shares_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_shares_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->short_sell_turnover[i] = arbitrary(); }
}

/* Statistics Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_statistics_message(const StatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->shares_traded[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->vwap[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_shares_traded[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->short_sell_turnover[i]; }

  return at;
}

/* Statistics Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_statistics_message(StatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->shares_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_shares_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->short_sell_turnover[i] = wire[at++]; }

  return at;
}

/* what was read of Statistics Message is what was written, byte for byte */
static void equal_statistics_message(const StatisticsMessage *read, const StatisticsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->shares_traded[i] == written->shares_traded[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover[i] == written->turnover[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->vwap[i] == written->vwap[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_shares_traded[i] == written->short_sell_shares_traded[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->short_sell_turnover[i] == written->short_sell_turnover[i]); }
}

/* Statistics Message: written and read back, then read and written back */
static void check_statistics_message(void) {
  StatisticsMessage sent;
  StatisticsMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_statistics_message(&sent);
  assert(encode_statistics_message(&sent, wire, 0) == 48);
  assert(decode_statistics_message(&got, wire, 0) == 48);
  equal_statistics_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_statistics_message(&got, wire, 0) == 48);
  assert(encode_statistics_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Turnover Message: 16 bytes --------------------------------------- */

/* The Market Turnover message contains the total turnover (excluding overseas trades) for all securities on a given market segment for a given trading currency. When CurrencyCode is blank, the turnover represents the total for all trading currencies, expressed in HKD. Updates disseminated around every 2 seconds during trading hours. */
typedef struct {
  uint8_t market_code[4];    /* bytes 0 to 3 */
  uint8_t currency_code[3];  /* bytes 4 to 6 */
  uint8_t filler_1;          /* byte 7 */
  uint8_t turnover[8];       /* bytes 8 to 15 */
} MarketTurnoverMessage;

/* any Market Turnover Message at all: every byte one the checker chooses */
static void any_market_turnover_message(MarketTurnoverMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = arbitrary(); }
  record->filler_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = arbitrary(); }
}

/* Market Turnover Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_market_turnover_message(const MarketTurnoverMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency_code[i]; }
  wire[at++] = record->filler_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover[i]; }

  return at;
}

/* Market Turnover Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_market_turnover_message(MarketTurnoverMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = wire[at++]; }
  record->filler_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = wire[at++]; }

  return at;
}

/* what was read of Market Turnover Message is what was written, byte for byte */
static void equal_market_turnover_message(const MarketTurnoverMessage *read, const MarketTurnoverMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_code[i] == written->market_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency_code[i] == written->currency_code[i]); }
  assert(read->filler_1 == written->filler_1);
  for (size_t i = 0; i < 8; i++) { assert(read->turnover[i] == written->turnover[i]); }
}

/* Market Turnover Message: written and read back, then read and written back */
static void check_market_turnover_message(void) {
  MarketTurnoverMessage sent;
  MarketTurnoverMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_market_turnover_message(&sent);
  assert(encode_market_turnover_message(&sent, wire, 0) == 16);
  assert(decode_market_turnover_message(&got, wire, 0) == 16);
  equal_market_turnover_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_market_turnover_message(&got, wire, 0) == 16);
  assert(encode_market_turnover_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Yield Message: 8 bytes -------------------------------------------------- */

/* The Yield message is generated for bond securities when their yield percentage changes. */
typedef struct {
  uint8_t security_code[4];  /* bytes 0 to 3 */
  uint8_t yield[4];          /* bytes 4 to 7 */
} YieldMessage;

/* any Yield Message at all: every byte one the checker chooses */
static void any_yield_message(YieldMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->yield[i] = arbitrary(); }
}

/* Yield Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_yield_message(const YieldMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->yield[i]; }

  return at;
}

/* Yield Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_yield_message(YieldMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->yield[i] = wire[at++]; }

  return at;
}

/* what was read of Yield Message is what was written, byte for byte */
static void equal_yield_message(const YieldMessage *read, const YieldMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->yield[i] == written->yield[i]); }
}

/* Yield Message: written and read back, then read and written back */
static void check_yield_message(void) {
  YieldMessage sent;
  YieldMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_yield_message(&sent);
  assert(encode_yield_message(&sent, wire, 0) == 8);
  assert(decode_yield_message(&got, wire, 0) == 8);
  equal_yield_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_yield_message(&got, wire, 0) == 8);
  assert(encode_yield_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Session Status Message: 28 bytes -------------------------------- */

/* The Trading Session Status provides information on the status of a market segment. It is sent whenever there is change of trading session. This message may be sent on a separate multicast channel from order and trade data and therefore may not be synchronized. */
typedef struct {
  uint8_t market_code[4];            /* bytes 0 to 3 */
  uint8_t filler_1;                  /* byte 4 */
  uint8_t trading_session_sub_id;    /* byte 5 */
  uint8_t trading_ses_status;        /* byte 6 */
  uint8_t trading_ses_control_flag;  /* byte 7 */
  uint8_t filler_4[4];               /* bytes 8 to 11 */
  uint8_t start_date_time[8];        /* bytes 12 to 19 */
  uint8_t end_date_time[8];          /* bytes 20 to 27 */
} TradingSessionStatusMessage;

/* any Trading Session Status Message at all: every byte one the checker chooses */
static void any_trading_session_status_message(TradingSessionStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = arbitrary(); }
  record->filler_1 = arbitrary();
  record->trading_session_sub_id = arbitrary();
  record->trading_ses_status = arbitrary();
  record->trading_ses_control_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->start_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_date_time[i] = arbitrary(); }
}

/* Trading Session Status Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_trading_session_status_message(const TradingSessionStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_code[i]; }
  wire[at++] = record->filler_1;
  wire[at++] = record->trading_session_sub_id;
  wire[at++] = record->trading_ses_status;
  wire[at++] = record->trading_ses_control_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->start_date_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_date_time[i]; }

  return at;
}

/* Trading Session Status Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_trading_session_status_message(TradingSessionStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = wire[at++]; }
  record->filler_1 = wire[at++];
  record->trading_session_sub_id = wire[at++];
  record->trading_ses_status = wire[at++];
  record->trading_ses_control_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->start_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_date_time[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Session Status Message is what was written, byte for byte */
static void equal_trading_session_status_message(const TradingSessionStatusMessage *read, const TradingSessionStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_code[i] == written->market_code[i]); }
  assert(read->filler_1 == written->filler_1);
  assert(read->trading_session_sub_id == written->trading_session_sub_id);
  assert(read->trading_ses_status == written->trading_ses_status);
  assert(read->trading_ses_control_flag == written->trading_ses_control_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->start_date_time[i] == written->start_date_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_date_time[i] == written->end_date_time[i]); }
}

/* Trading Session Status Message: written and read back, then read and written back */
static void check_trading_session_status_message(void) {
  TradingSessionStatusMessage sent;
  TradingSessionStatusMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_trading_session_status_message(&sent);
  assert(encode_trading_session_status_message(&sent, wire, 0) == 28);
  assert(decode_trading_session_status_message(&got, wire, 0) == 28);
  equal_trading_session_status_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_session_status_message(&got, wire, 0) == 28);
  assert(encode_trading_session_status_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Status Message: 8 bytes ---------------------------------------- */

/* The Security Status message is generated at the start of the business day if the security is not available for trading, and whenever a security state changes. */
typedef struct {
  uint8_t security_code[4];      /* bytes 0 to 3 */
  uint8_t suspension_indicator;  /* byte 4 */
  uint8_t filler_3[3];           /* bytes 5 to 7 */
} SecurityStatusMessage;

/* any Security Status Message at all: every byte one the checker chooses */
static void any_security_status_message(SecurityStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  record->suspension_indicator = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = arbitrary(); }
}

/* Security Status Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_security_status_message(const SecurityStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  wire[at++] = record->suspension_indicator;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_3[i]; }

  return at;
}

/* Security Status Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_security_status_message(SecurityStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  record->suspension_indicator = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = wire[at++]; }

  return at;
}

/* what was read of Security Status Message is what was written, byte for byte */
static void equal_security_status_message(const SecurityStatusMessage *read, const SecurityStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  assert(read->suspension_indicator == written->suspension_indicator);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
}

/* Security Status Message: written and read back, then read and written back */
static void check_security_status_message(void) {
  SecurityStatusMessage sent;
  SecurityStatusMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_security_status_message(&sent);
  assert(encode_security_status_message(&sent, wire, 0) == 8);
  assert(decode_security_status_message(&got, wire, 0) == 8);
  equal_security_status_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_security_status_message(&got, wire, 0) == 8);
  assert(encode_security_status_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Ticker Message: 32 bytes ------------------------------------------ */

/* The Trade Ticker is an aggregation of several trades into one message, combining quantities of subsequent trades made on a given instrument at a given fixed price. */
typedef struct {
  uint8_t security_code[4];       /* bytes 0 to 3 */
  uint8_t ticker_id[4];           /* bytes 4 to 7 */
  uint8_t price[4];               /* bytes 8 to 11 */
  uint8_t aggregate_quantity[8];  /* bytes 12 to 19 */
  uint8_t trade_time[8];          /* bytes 20 to 27 */
  uint8_t trd_type[2];            /* bytes 28 to 29 */
  uint8_t trd_cancel_flag;        /* byte 30 */
  uint8_t filler_1;               /* byte 31 */
} TradeTickerMessage;

/* any Trade Ticker Message at all: every byte one the checker chooses */
static void any_trade_ticker_message(TradeTickerMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ticker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->aggregate_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  record->trd_cancel_flag = arbitrary();
  record->filler_1 = arbitrary();
}

/* Trade Ticker Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_trade_ticker_message(const TradeTickerMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ticker_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->aggregate_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  wire[at++] = record->trd_cancel_flag;
  wire[at++] = record->filler_1;

  return at;
}

/* Trade Ticker Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_trade_ticker_message(TradeTickerMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ticker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->aggregate_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  record->trd_cancel_flag = wire[at++];
  record->filler_1 = wire[at++];

  return at;
}

/* what was read of Trade Ticker Message is what was written, byte for byte */
static void equal_trade_ticker_message(const TradeTickerMessage *read, const TradeTickerMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ticker_id[i] == written->ticker_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->aggregate_quantity[i] == written->aggregate_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_time[i] == written->trade_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  assert(read->trd_cancel_flag == written->trd_cancel_flag);
  assert(read->filler_1 == written->filler_1);
}

/* Trade Ticker Message: written and read back, then read and written back */
static void check_trade_ticker_message(void) {
  TradeTickerMessage sent;
  TradeTickerMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_trade_ticker_message(&sent);
  assert(encode_trade_ticker_message(&sent, wire, 0) == 32);
  assert(decode_trade_ticker_message(&got, wire, 0) == 32);
  equal_trade_ticker_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_ticker_message(&got, wire, 0) == 32);
  assert(encode_trade_ticker_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Vcm Trigger Message: 32 bytes ------------------------------------------- */

/* The VCM Trigger message is generated whenever a cooling off period is triggered by Volatility Control Mechanism (VCM). */
typedef struct {
  uint8_t security_code[4];           /* bytes 0 to 3 */
  uint8_t cooling_off_start_time[8];  /* bytes 4 to 11 */
  uint8_t cooling_off_end_time[8];    /* bytes 12 to 19 */
  uint8_t vcm_reference_price[4];     /* bytes 20 to 23 */
  uint8_t vcm_lower_price[4];         /* bytes 24 to 27 */
  uint8_t vcm_upper_price[4];         /* bytes 28 to 31 */
} VcmTriggerMessage;

/* any Vcm Trigger Message at all: every byte one the checker chooses */
static void any_vcm_trigger_message(VcmTriggerMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cooling_off_start_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cooling_off_end_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->vcm_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->vcm_lower_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->vcm_upper_price[i] = arbitrary(); }
}

/* Vcm Trigger Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_vcm_trigger_message(const VcmTriggerMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cooling_off_start_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cooling_off_end_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->vcm_reference_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->vcm_lower_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->vcm_upper_price[i]; }

  return at;
}

/* Vcm Trigger Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_vcm_trigger_message(VcmTriggerMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cooling_off_start_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cooling_off_end_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->vcm_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->vcm_lower_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->vcm_upper_price[i] = wire[at++]; }

  return at;
}

/* what was read of Vcm Trigger Message is what was written, byte for byte */
static void equal_vcm_trigger_message(const VcmTriggerMessage *read, const VcmTriggerMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cooling_off_start_time[i] == written->cooling_off_start_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cooling_off_end_time[i] == written->cooling_off_end_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->vcm_reference_price[i] == written->vcm_reference_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->vcm_lower_price[i] == written->vcm_lower_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->vcm_upper_price[i] == written->vcm_upper_price[i]); }
}

/* Vcm Trigger Message: written and read back, then read and written back */
static void check_vcm_trigger_message(void) {
  VcmTriggerMessage sent;
  VcmTriggerMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_vcm_trigger_message(&sent);
  assert(encode_vcm_trigger_message(&sent, wire, 0) == 32);
  assert(decode_vcm_trigger_message(&got, wire, 0) == 32);
  equal_vcm_trigger_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_vcm_trigger_message(&got, wire, 0) == 32);
  assert(encode_vcm_trigger_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_msg_header();
  check_closing_price_message();
  check_sequence_reset_message();
  check_disaster_recovery_signal_message();
  check_indicative_equilibrium_price_message();
  check_nominal_price_message();
  check_order_imbalance_message();
  check_market_definition_message();
  check_face_value_composite();
  check_call_price_composite();
  check_entitlement_composite();
  check_currency_rate_message();
  check_reference_price_message();
  check_refresh_complete_message();
  check_statistics_message();
  check_market_turnover_message();
  check_yield_message();
  check_trading_session_status_message();
  check_security_status_message();
  check_trade_ticker_message();
  check_vcm_trigger_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
