// lme/lmeselect/referencedata/LmeSelect_ReferenceData_v4_18.c
/*
 * The London Metal Exchange LMEsource ReferenceData
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

/* ---- Contract Definition Message: 134 bytes ---------------------------------- */

/* Published for a new contract prior to its first trading date, to enable participants to configure risk management parameters before the contract becomes tradable. */
typedef struct {
  uint8_t trading_venue[2];              /* bytes 0 to 1 */
  uint8_t contract_code[12];             /* bytes 2 to 13 */
  uint8_t name[64];                      /* bytes 14 to 77 */
  uint8_t contract_type;                 /* byte 78 */
  uint8_t product_code[2];               /* bytes 79 to 80 */
  uint8_t underlying_type;               /* byte 81 */
  uint8_t underlying_contract_code[12];  /* bytes 82 to 93 */
  uint8_t trading_currency[3];           /* bytes 94 to 96 */
  uint8_t settlement_type;               /* byte 97 */
  uint8_t settlement_pricing_method;     /* byte 98 */
  uint8_t exercise_style;                /* byte 99 */
  uint8_t lot_unit[20];                  /* bytes 100 to 119 */
  uint8_t lot_size[8];                   /* bytes 120 to 127 */
  uint8_t lot_size_type;                 /* byte 128 */
  uint8_t contract_price_type;           /* byte 129 */
  uint8_t first_trading_date[4];         /* bytes 130 to 133 */
} ContractDefinitionMessage;

/* any Contract Definition Message at all: every byte one the checker chooses */
static void any_contract_definition_message(ContractDefinitionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->contract_code[i] = arbitrary(); }
  for (size_t i = 0; i < 64; i++) { record->name[i] = arbitrary(); }
  record->contract_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->product_code[i] = arbitrary(); }
  record->underlying_type = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->underlying_contract_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = arbitrary(); }
  record->settlement_type = arbitrary();
  record->settlement_pricing_method = arbitrary();
  record->exercise_style = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->lot_unit[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lot_size[i] = arbitrary(); }
  record->lot_size_type = arbitrary();
  record->contract_price_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->first_trading_date[i] = arbitrary(); }
}

/* Contract Definition Message to the wire: 134 bytes from at, returning where the next byte goes */
static size_t encode_contract_definition_message(const ContractDefinitionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_venue[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->contract_code[i]; }
  for (size_t i = 0; i < 64; i++) { wire[at++] = record->name[i]; }
  wire[at++] = record->contract_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->product_code[i]; }
  wire[at++] = record->underlying_type;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_contract_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_currency[i]; }
  wire[at++] = record->settlement_type;
  wire[at++] = record->settlement_pricing_method;
  wire[at++] = record->exercise_style;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->lot_unit[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lot_size[i]; }
  wire[at++] = record->lot_size_type;
  wire[at++] = record->contract_price_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_trading_date[i]; }

  return at;
}

/* Contract Definition Message off the wire: 134 bytes from at, returning where the next byte lies */
static size_t decode_contract_definition_message(ContractDefinitionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->contract_code[i] = wire[at++]; }
  for (size_t i = 0; i < 64; i++) { record->name[i] = wire[at++]; }
  record->contract_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->product_code[i] = wire[at++]; }
  record->underlying_type = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->underlying_contract_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = wire[at++]; }
  record->settlement_type = wire[at++];
  record->settlement_pricing_method = wire[at++];
  record->exercise_style = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->lot_unit[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lot_size[i] = wire[at++]; }
  record->lot_size_type = wire[at++];
  record->contract_price_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->first_trading_date[i] = wire[at++]; }

  return at;
}

/* what was read of Contract Definition Message is what was written, byte for byte */
static void equal_contract_definition_message(const ContractDefinitionMessage *read, const ContractDefinitionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->trading_venue[i] == written->trading_venue[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->contract_code[i] == written->contract_code[i]); }
  for (size_t i = 0; i < 64; i++) { assert(read->name[i] == written->name[i]); }
  assert(read->contract_type == written->contract_type);
  for (size_t i = 0; i < 2; i++) { assert(read->product_code[i] == written->product_code[i]); }
  assert(read->underlying_type == written->underlying_type);
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_contract_code[i] == written->underlying_contract_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trading_currency[i] == written->trading_currency[i]); }
  assert(read->settlement_type == written->settlement_type);
  assert(read->settlement_pricing_method == written->settlement_pricing_method);
  assert(read->exercise_style == written->exercise_style);
  for (size_t i = 0; i < 20; i++) { assert(read->lot_unit[i] == written->lot_unit[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lot_size[i] == written->lot_size[i]); }
  assert(read->lot_size_type == written->lot_size_type);
  assert(read->contract_price_type == written->contract_price_type);
  for (size_t i = 0; i < 4; i++) { assert(read->first_trading_date[i] == written->first_trading_date[i]); }
}

/* Contract Definition Message: written and read back, then read and written back */
static void check_contract_definition_message(void) {
  ContractDefinitionMessage sent;
  ContractDefinitionMessage got;
  uint8_t wire[134];
  uint8_t again[134];

  any_contract_definition_message(&sent);
  assert(encode_contract_definition_message(&sent, wire, 0) == 134);
  assert(decode_contract_definition_message(&got, wire, 0) == 134);
  equal_contract_definition_message(&got, &sent);

  for (size_t i = 0; i < 134; i++) { wire[i] = arbitrary(); }
  assert(decode_contract_definition_message(&got, wire, 0) == 134);
  assert(encode_contract_definition_message(&got, again, 0) == 134);
  for (size_t i = 0; i < 134; i++) { assert(again[i] == wire[i]); }
}

/* ---- Outright Definition Message: 121 bytes ---------------------------------- */

/* Describes individual outright tradable instruments available from LMEsource. */
typedef struct {
  uint8_t trading_venue[2];                  /* bytes 0 to 1 */
  uint8_t tradable_instrument_id[8];         /* bytes 2 to 9 */
  uint8_t merged_tradable_instrument_id[8];  /* bytes 10 to 17 */
  uint8_t linked_tradable_instrument_id[8];  /* bytes 18 to 25 */
  uint8_t product_code[2];                   /* bytes 26 to 27 */
  uint8_t contract_type;                     /* byte 28 */
  uint8_t trading_currency[3];               /* bytes 29 to 31 */
  uint8_t contract_code[12];                 /* bytes 32 to 43 */
  uint8_t expiry_date[4];                    /* bytes 44 to 47 */
  uint8_t prompt_type;                       /* byte 48 */
  uint8_t strike_price[8];                   /* bytes 49 to 56 */
  uint8_t option_type;                       /* byte 57 */
  uint8_t exercise_style;                    /* byte 58 */
  uint8_t prompt_date_label[6];              /* bytes 59 to 64 */
  uint8_t price_code[2];                     /* bytes 65 to 66 */
  uint8_t isin[12];                          /* bytes 67 to 78 */
  uint8_t cfi_code[6];                       /* bytes 79 to 84 */
  uint8_t market_code[4];                    /* bytes 85 to 88 */
  uint8_t market_segment_code[12];           /* bytes 89 to 100 */
  uint8_t tick_size_id[4];                   /* bytes 101 to 104 */
  uint8_t lot_size[8];                       /* bytes 105 to 112 */
  uint8_t lot_size_type;                     /* byte 113 */
  uint8_t last_trading_date[4];              /* bytes 114 to 117 */
  uint8_t settlement_type;                   /* byte 118 */
  uint8_t settlement_pricing_method;         /* byte 119 */
  uint8_t underlying_type;                   /* byte 120 */
} OutrightDefinitionMessage;

/* any Outright Definition Message at all: every byte one the checker chooses */
static void any_outright_definition_message(OutrightDefinitionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->merged_tradable_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->linked_tradable_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->product_code[i] = arbitrary(); }
  record->contract_type = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->contract_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = arbitrary(); }
  record->prompt_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->option_type = arbitrary();
  record->exercise_style = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->prompt_date_label[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->market_segment_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tick_size_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lot_size[i] = arbitrary(); }
  record->lot_size_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_trading_date[i] = arbitrary(); }
  record->settlement_type = arbitrary();
  record->settlement_pricing_method = arbitrary();
  record->underlying_type = arbitrary();
}

/* Outright Definition Message to the wire: 121 bytes from at, returning where the next byte goes */
static size_t encode_outright_definition_message(const OutrightDefinitionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tradable_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->merged_tradable_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->linked_tradable_instrument_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->product_code[i]; }
  wire[at++] = record->contract_type;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_currency[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->contract_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expiry_date[i]; }
  wire[at++] = record->prompt_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->option_type;
  wire[at++] = record->exercise_style;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->prompt_date_label[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cfi_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->market_segment_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tick_size_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lot_size[i]; }
  wire[at++] = record->lot_size_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trading_date[i]; }
  wire[at++] = record->settlement_type;
  wire[at++] = record->settlement_pricing_method;
  wire[at++] = record->underlying_type;

  return at;
}

/* Outright Definition Message off the wire: 121 bytes from at, returning where the next byte lies */
static size_t decode_outright_definition_message(OutrightDefinitionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->merged_tradable_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->linked_tradable_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->product_code[i] = wire[at++]; }
  record->contract_type = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->contract_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = wire[at++]; }
  record->prompt_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->option_type = wire[at++];
  record->exercise_style = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->prompt_date_label[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->market_segment_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tick_size_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lot_size[i] = wire[at++]; }
  record->lot_size_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->last_trading_date[i] = wire[at++]; }
  record->settlement_type = wire[at++];
  record->settlement_pricing_method = wire[at++];
  record->underlying_type = wire[at++];

  return at;
}

/* what was read of Outright Definition Message is what was written, byte for byte */
static void equal_outright_definition_message(const OutrightDefinitionMessage *read, const OutrightDefinitionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->trading_venue[i] == written->trading_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tradable_instrument_id[i] == written->tradable_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->merged_tradable_instrument_id[i] == written->merged_tradable_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->linked_tradable_instrument_id[i] == written->linked_tradable_instrument_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->product_code[i] == written->product_code[i]); }
  assert(read->contract_type == written->contract_type);
  for (size_t i = 0; i < 3; i++) { assert(read->trading_currency[i] == written->trading_currency[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->contract_code[i] == written->contract_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expiry_date[i] == written->expiry_date[i]); }
  assert(read->prompt_type == written->prompt_type);
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->option_type == written->option_type);
  assert(read->exercise_style == written->exercise_style);
  for (size_t i = 0; i < 6; i++) { assert(read->prompt_date_label[i] == written->prompt_date_label[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_code[i] == written->price_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cfi_code[i] == written->cfi_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_code[i] == written->market_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->market_segment_code[i] == written->market_segment_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tick_size_id[i] == written->tick_size_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lot_size[i] == written->lot_size[i]); }
  assert(read->lot_size_type == written->lot_size_type);
  for (size_t i = 0; i < 4; i++) { assert(read->last_trading_date[i] == written->last_trading_date[i]); }
  assert(read->settlement_type == written->settlement_type);
  assert(read->settlement_pricing_method == written->settlement_pricing_method);
  assert(read->underlying_type == written->underlying_type);
}

/* Outright Definition Message: written and read back, then read and written back */
static void check_outright_definition_message(void) {
  OutrightDefinitionMessage sent;
  OutrightDefinitionMessage got;
  uint8_t wire[121];
  uint8_t again[121];

  any_outright_definition_message(&sent);
  assert(encode_outright_definition_message(&sent, wire, 0) == 121);
  assert(decode_outright_definition_message(&got, wire, 0) == 121);
  equal_outright_definition_message(&got, &sent);

  for (size_t i = 0; i < 121; i++) { wire[i] = arbitrary(); }
  assert(decode_outright_definition_message(&got, wire, 0) == 121);
  assert(encode_outright_definition_message(&got, again, 0) == 121);
  for (size_t i = 0; i < 121; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Limits Message: 32 bytes ------------------------------------------ */

/* Describes the upper and lower price limits for an outright tradable instrument. Where Daily Price Limits are enabled for a contract they are published for electronic tradable instruments, and the same limits also apply to non-electronic tradable instruments. */
typedef struct {
  uint8_t tradable_instrument_id[8];  /* bytes 0 to 7 */
  uint8_t upper_price_limit[8];       /* bytes 8 to 15 */
  uint8_t lower_price_limit[8];       /* bytes 16 to 23 */
  uint8_t transaction_time[8];        /* bytes 24 to 31 */
} PriceLimitsMessage;

/* any Price Limits Message at all: every byte one the checker chooses */
static void any_price_limits_message(PriceLimitsMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->upper_price_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lower_price_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
}

/* Price Limits Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_price_limits_message(const PriceLimitsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tradable_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->upper_price_limit[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_price_limit[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }

  return at;
}

/* Price Limits Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_price_limits_message(PriceLimitsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->upper_price_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lower_price_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }

  return at;
}

/* what was read of Price Limits Message is what was written, byte for byte */
static void equal_price_limits_message(const PriceLimitsMessage *read, const PriceLimitsMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->tradable_instrument_id[i] == written->tradable_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->upper_price_limit[i] == written->upper_price_limit[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lower_price_limit[i] == written->lower_price_limit[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
}

/* Price Limits Message: written and read back, then read and written back */
static void check_price_limits_message(void) {
  PriceLimitsMessage sent;
  PriceLimitsMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_price_limits_message(&sent);
  assert(encode_price_limits_message(&sent, wire, 0) == 32);
  assert(decode_price_limits_message(&got, wire, 0) == 32);
  equal_price_limits_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_price_limits_message(&got, wire, 0) == 32);
  assert(encode_price_limits_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Statistics End Of Day Message: 50 bytes --------------------------- */

/* Generated when the market moves to the Post-Trade session for instruments that have traded. LMEsource publishes the LMEselect Opening and Closing Prices, LMEselect Trading High and LMEselect Trading Low for all contracts that have traded during the day. Off book trades resulting from Cross Order execution are not used in the calculation. */
typedef struct {
  uint8_t trading_venue[2];           /* bytes 0 to 1 */
  uint8_t time_of_event[8];           /* bytes 2 to 9 */
  uint8_t tradable_instrument_id[8];  /* bytes 10 to 17 */
  uint8_t open_price[8];              /* bytes 18 to 25 */
  uint8_t trade_high[8];              /* bytes 26 to 33 */
  uint8_t trade_low[8];               /* bytes 34 to 41 */
  uint8_t closing_price[8];           /* bytes 42 to 49 */
} TradeStatisticsEndOfDayMessage;

/* any Trade Statistics End Of Day Message at all: every byte one the checker chooses */
static void any_trade_statistics_end_of_day_message(TradeStatisticsEndOfDayMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_of_event[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = arbitrary(); }
}

/* Trade Statistics End Of Day Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_trade_statistics_end_of_day_message(const TradeStatisticsEndOfDayMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_of_event[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tradable_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price[i]; }

  return at;
}

/* Trade Statistics End Of Day Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_trade_statistics_end_of_day_message(TradeStatisticsEndOfDayMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->trading_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_of_event[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tradable_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Statistics End Of Day Message is what was written, byte for byte */
static void equal_trade_statistics_end_of_day_message(const TradeStatisticsEndOfDayMessage *read, const TradeStatisticsEndOfDayMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->trading_venue[i] == written->trading_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_of_event[i] == written->time_of_event[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tradable_instrument_id[i] == written->tradable_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_price[i] == written->open_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_high[i] == written->trade_high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_low[i] == written->trade_low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
}

/* Trade Statistics End Of Day Message: written and read back, then read and written back */
static void check_trade_statistics_end_of_day_message(void) {
  TradeStatisticsEndOfDayMessage sent;
  TradeStatisticsEndOfDayMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_trade_statistics_end_of_day_message(&sent);
  assert(encode_trade_statistics_end_of_day_message(&sent, wire, 0) == 50);
  assert(decode_trade_statistics_end_of_day_message(&got, wire, 0) == 50);
  equal_trade_statistics_end_of_day_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_statistics_end_of_day_message(&got, wire, 0) == 50);
  assert(encode_trade_statistics_end_of_day_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_sequence_reset_message();
  check_contract_definition_message();
  check_outright_definition_message();
  check_price_limits_message();
  check_trade_statistics_end_of_day_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
