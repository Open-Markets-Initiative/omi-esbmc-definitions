// gpw/wse/pricesandtrades/Wse_PricesAndTrades_v6_8.c
/*
 * Giełda Papierów Wartościowych w Warszawie Warsaw Stock Exchange Prices and Trades
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
 *   - a field filling what is left of what holds it
 *   - a run filling what frames it
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

/* All messages are preceded by a common packet header format, which section 1.1 states for every Market Information message */
typedef struct {
  uint8_t packet_length[2];           /* bytes 0 to 1 */
  uint8_t packet_type[2];             /* bytes 2 to 3 */
  uint8_t packet_sequence_number[4];  /* bytes 4 to 7 */
  uint8_t send_time[4];               /* bytes 8 to 11 */
  uint8_t service_id[2];              /* bytes 12 to 13 */
  uint8_t delivery_flag;              /* byte 14 */
  uint8_t number_msg_entries;         /* byte 15 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->packet_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->packet_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->send_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->service_id[i] = arbitrary(); }
  record->delivery_flag = arbitrary();
  record->number_msg_entries = arbitrary();
}

/* Packet Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->packet_sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->send_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->service_id[i]; }
  wire[at++] = record->delivery_flag;
  wire[at++] = record->number_msg_entries;

  return at;
}

/* Packet Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->packet_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->packet_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->send_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->service_id[i] = wire[at++]; }
  record->delivery_flag = wire[at++];
  record->number_msg_entries = wire[at++];

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->packet_type[i] == written->packet_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->packet_sequence_number[i] == written->packet_sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->send_time[i] == written->send_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->service_id[i] == written->service_id[i]); }
  assert(read->delivery_flag == written->delivery_flag);
  assert(read->number_msg_entries == written->number_msg_entries);
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

typedef struct {
  uint8_t message_size[2];  /* bytes 0 to 1 */
  uint8_t message_type[2];  /* bytes 2 to 3 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = arbitrary(); }
}

/* Message Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_type[i]; }

  return at;
}

/* Message Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_size[i] == written->message_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_type[i] == written->message_type[i]); }
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

/* ---- Trade Full Information Message: 272 bytes ------------------------------- */

/* Trade full information message is sent each time a trade or a cancellation of a trade has occurred */
typedef struct {
  uint8_t symbol_index[4];                    /* bytes 0 to 3 */
  uint8_t source_time[4];                     /* bytes 4 to 7 */
  uint8_t trade_id_number[4];                 /* bytes 8 to 11 */
  uint8_t venue_of_execution[4];              /* bytes 12 to 15 */
  uint8_t source_seq_num[4];                  /* bytes 16 to 19 */
  uint8_t price_notation[4];                  /* bytes 20 to 23 */
  uint8_t transaction_to_be_cleared[4];       /* bytes 24 to 27 */
  uint8_t cumulative_quantity[4];             /* bytes 28 to 31 */
  uint8_t highest_price[4];                   /* bytes 32 to 35 */
  uint8_t lowest_price[4];                    /* bytes 36 to 39 */
  uint8_t variation_last_price[4];            /* bytes 40 to 43 */
  uint8_t system_id[4];                       /* bytes 44 to 47 */
  uint8_t source_time_micro_secs[2];          /* bytes 48 to 49 */
  uint8_t price_currency[3];                  /* bytes 50 to 52 */
  uint8_t last_trade_indicator;               /* byte 53 */
  uint8_t type_of_trade;                      /* byte 54 */
  uint8_t trade_origin;                       /* byte 55 */
  uint8_t tick_direction;                     /* byte 56 */
  uint8_t opening_trade_indicator;            /* byte 57 */
  uint8_t variation_scale_code;               /* byte 58 */
  uint8_t price_scale_code;                   /* byte 59 */
  uint8_t trading_date_time[27];              /* bytes 60 to 86 */
  uint8_t publication_date_time[27];          /* bytes 87 to 113 */
  uint8_t instrument_id_code_type[4];         /* bytes 114 to 117 */
  uint8_t instrument_id_code[12];             /* bytes 118 to 129 */
  uint8_t price_ascii_ch_20[20];              /* bytes 130 to 149 */
  uint8_t quantity[20];                       /* bytes 150 to 169 */
  uint8_t notional_amount[20];                /* bytes 170 to 189 */
  uint8_t notional_currency[3];               /* bytes 190 to 192 */
  uint8_t reserved_1;                         /* byte 193 */
  uint8_t transaction_id_code[52];            /* bytes 194 to 245 */
  uint8_t mmt_market_mechanism;               /* byte 246 */
  uint8_t mmt_trading_mode;                   /* byte 247 */
  uint8_t mmt_algorithmic_indicator[4];       /* bytes 248 to 251 */
  uint8_t mmt_modification_indicator[4];      /* bytes 252 to 255 */
  uint8_t mmt_negotiation_indicator[4];       /* bytes 256 to 259 */
  uint8_t mmt_special_dividend_indicator[4];  /* bytes 260 to 263 */
  uint8_t mmt_contribution_to_price[4];       /* bytes 264 to 267 */
  uint8_t mmt_benchmark_indicator[4];         /* bytes 268 to 271 */
} TradeFullInformationMessage;

/* any Trade Full Information Message at all: every byte one the checker chooses */
static void any_trade_full_information_message(TradeFullInformationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->transaction_to_be_cleared[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cumulative_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->highest_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lowest_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->variation_last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->price_currency[i] = arbitrary(); }
  record->last_trade_indicator = arbitrary();
  record->type_of_trade = arbitrary();
  record->trade_origin = arbitrary();
  record->tick_direction = arbitrary();
  record->opening_trade_indicator = arbitrary();
  record->variation_scale_code = arbitrary();
  record->price_scale_code = arbitrary();
  for (size_t i = 0; i < 27; i++) { record->trading_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 27; i++) { record->publication_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id_code_type[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->instrument_id_code[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->price_ascii_ch_20[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->notional_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 52; i++) { record->transaction_id_code[i] = arbitrary(); }
  record->mmt_market_mechanism = arbitrary();
  record->mmt_trading_mode = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->mmt_algorithmic_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_modification_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_negotiation_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_special_dividend_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_contribution_to_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_benchmark_indicator[i] = arbitrary(); }
}

/* Trade Full Information Message to the wire: 272 bytes from at, returning where the next byte goes */
static size_t encode_trade_full_information_message(const TradeFullInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue_of_execution[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_notation[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_to_be_cleared[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cumulative_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->highest_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lowest_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->variation_last_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->price_currency[i]; }
  wire[at++] = record->last_trade_indicator;
  wire[at++] = record->type_of_trade;
  wire[at++] = record->trade_origin;
  wire[at++] = record->tick_direction;
  wire[at++] = record->opening_trade_indicator;
  wire[at++] = record->variation_scale_code;
  wire[at++] = record->price_scale_code;
  for (size_t i = 0; i < 27; i++) { wire[at++] = record->trading_date_time[i]; }
  for (size_t i = 0; i < 27; i++) { wire[at++] = record->publication_date_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id_code_type[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->instrument_id_code[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->price_ascii_ch_20[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->notional_amount[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->notional_currency[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->transaction_id_code[i]; }
  wire[at++] = record->mmt_market_mechanism;
  wire[at++] = record->mmt_trading_mode;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_algorithmic_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_modification_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_negotiation_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_special_dividend_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_contribution_to_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_benchmark_indicator[i]; }

  return at;
}

/* Trade Full Information Message off the wire: 272 bytes from at, returning where the next byte lies */
static size_t decode_trade_full_information_message(TradeFullInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->transaction_to_be_cleared[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cumulative_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->highest_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lowest_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->variation_last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->price_currency[i] = wire[at++]; }
  record->last_trade_indicator = wire[at++];
  record->type_of_trade = wire[at++];
  record->trade_origin = wire[at++];
  record->tick_direction = wire[at++];
  record->opening_trade_indicator = wire[at++];
  record->variation_scale_code = wire[at++];
  record->price_scale_code = wire[at++];
  for (size_t i = 0; i < 27; i++) { record->trading_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 27; i++) { record->publication_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id_code_type[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->instrument_id_code[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->price_ascii_ch_20[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->notional_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 52; i++) { record->transaction_id_code[i] = wire[at++]; }
  record->mmt_market_mechanism = wire[at++];
  record->mmt_trading_mode = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->mmt_algorithmic_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_modification_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_negotiation_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_special_dividend_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_contribution_to_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_benchmark_indicator[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Full Information Message is what was written, byte for byte */
static void equal_trade_full_information_message(const TradeFullInformationMessage *read, const TradeFullInformationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id_number[i] == written->trade_id_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->venue_of_execution[i] == written->venue_of_execution[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_notation[i] == written->price_notation[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_to_be_cleared[i] == written->transaction_to_be_cleared[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cumulative_quantity[i] == written->cumulative_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->highest_price[i] == written->highest_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lowest_price[i] == written->lowest_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->variation_last_price[i] == written->variation_last_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->price_currency[i] == written->price_currency[i]); }
  assert(read->last_trade_indicator == written->last_trade_indicator);
  assert(read->type_of_trade == written->type_of_trade);
  assert(read->trade_origin == written->trade_origin);
  assert(read->tick_direction == written->tick_direction);
  assert(read->opening_trade_indicator == written->opening_trade_indicator);
  assert(read->variation_scale_code == written->variation_scale_code);
  assert(read->price_scale_code == written->price_scale_code);
  for (size_t i = 0; i < 27; i++) { assert(read->trading_date_time[i] == written->trading_date_time[i]); }
  for (size_t i = 0; i < 27; i++) { assert(read->publication_date_time[i] == written->publication_date_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id_code_type[i] == written->instrument_id_code_type[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->instrument_id_code[i] == written->instrument_id_code[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->price_ascii_ch_20[i] == written->price_ascii_ch_20[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->notional_amount[i] == written->notional_amount[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->notional_currency[i] == written->notional_currency[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 52; i++) { assert(read->transaction_id_code[i] == written->transaction_id_code[i]); }
  assert(read->mmt_market_mechanism == written->mmt_market_mechanism);
  assert(read->mmt_trading_mode == written->mmt_trading_mode);
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_algorithmic_indicator[i] == written->mmt_algorithmic_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_modification_indicator[i] == written->mmt_modification_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_negotiation_indicator[i] == written->mmt_negotiation_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_special_dividend_indicator[i] == written->mmt_special_dividend_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_contribution_to_price[i] == written->mmt_contribution_to_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_benchmark_indicator[i] == written->mmt_benchmark_indicator[i]); }
}

/* Trade Full Information Message: written and read back, then read and written back */
static void check_trade_full_information_message(void) {
  TradeFullInformationMessage sent;
  TradeFullInformationMessage got;
  uint8_t wire[272];
  uint8_t again[272];

  any_trade_full_information_message(&sent);
  assert(encode_trade_full_information_message(&sent, wire, 0) == 272);
  assert(decode_trade_full_information_message(&got, wire, 0) == 272);
  equal_trade_full_information_message(&got, &sent);

  for (size_t i = 0; i < 272; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_full_information_message(&got, wire, 0) == 272);
  assert(encode_trade_full_information_message(&got, again, 0) == 272);
  for (size_t i = 0; i < 272; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Update Message: 40 bytes ------------------------------------------ */

/* The Price update message contains a bid price or an ask price in case of alternative indicative price (AIP), or the modification of the last reference price on a given instrument */
typedef struct {
  uint8_t symbol_index[4];            /* bytes 0 to 3 */
  uint8_t source_time[4];             /* bytes 4 to 7 */
  uint8_t source_seq_num[4];          /* bytes 8 to 11 */
  uint8_t price_binary_int_4[4];      /* bytes 12 to 15 */
  uint8_t highest_price[4];           /* bytes 16 to 19 */
  uint8_t lowest_price[4];            /* bytes 20 to 23 */
  uint8_t variation_last_price[4];    /* bytes 24 to 27 */
  uint8_t system_id[4];               /* bytes 28 to 31 */
  uint8_t source_time_micro_secs[2];  /* bytes 32 to 33 */
  uint8_t type_of_price[2];           /* bytes 34 to 35 */
  uint8_t reserved_2[2];              /* bytes 36 to 37 */
  uint8_t price_scale_code;           /* byte 38 */
  uint8_t variation_scale_code;       /* byte 39 */
} PriceUpdateMessage;

/* any Price Update Message at all: every byte one the checker chooses */
static void any_price_update_message(PriceUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_binary_int_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->highest_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lowest_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->variation_last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->type_of_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->price_scale_code = arbitrary();
  record->variation_scale_code = arbitrary();
}

/* Price Update Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_price_update_message(const PriceUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_binary_int_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->highest_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lowest_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->variation_last_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->type_of_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->price_scale_code;
  wire[at++] = record->variation_scale_code;

  return at;
}

/* Price Update Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_price_update_message(PriceUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_binary_int_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->highest_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lowest_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->variation_last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->type_of_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->price_scale_code = wire[at++];
  record->variation_scale_code = wire[at++];

  return at;
}

/* what was read of Price Update Message is what was written, byte for byte */
static void equal_price_update_message(const PriceUpdateMessage *read, const PriceUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_binary_int_4[i] == written->price_binary_int_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->highest_price[i] == written->highest_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lowest_price[i] == written->lowest_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->variation_last_price[i] == written->variation_last_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->type_of_price[i] == written->type_of_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->variation_scale_code == written->variation_scale_code);
}

/* Price Update Message: written and read back, then read and written back */
static void check_price_update_message(void) {
  PriceUpdateMessage sent;
  PriceUpdateMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_price_update_message(&sent);
  assert(encode_price_update_message(&sent, wire, 0) == 40);
  assert(decode_price_update_message(&got, wire, 0) == 40);
  equal_price_update_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_price_update_message(&got, wire, 0) == 40);
  assert(encode_price_update_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Publication Message: 284 bytes ------------------------------------ */

/* A trade publication message is sent by the reporting system whenever a trade is reported */
typedef struct {
  uint8_t symbol_index[4];                    /* bytes 0 to 3 */
  uint8_t source_time[4];                     /* bytes 4 to 7 */
  uint8_t source_seq_num[4];                  /* bytes 8 to 11 */
  uint8_t venue_of_execution[4];              /* bytes 12 to 15 */
  uint8_t instrument_id_code_type[4];         /* bytes 16 to 19 */
  uint8_t price_multiplier[4];                /* bytes 20 to 23 */
  uint8_t system_id[4];                       /* bytes 24 to 27 */
  uint8_t source_time_micro_secs[2];          /* bytes 28 to 29 */
  uint8_t trading_date_time[27];              /* bytes 30 to 56 */
  uint8_t price_currency[3];                  /* bytes 57 to 59 */
  uint8_t instrument_id_code[12];             /* bytes 60 to 71 */
  uint8_t publication_date_time[27];          /* bytes 72 to 98 */
  uint8_t notional_currency[3];               /* bytes 99 to 101 */
  uint8_t tcs_trade_id[16];                   /* bytes 102 to 117 */
  uint8_t price_notation[4];                  /* bytes 118 to 121 */
  uint8_t reserved_1;                         /* byte 122 */
  uint8_t transaction_to_be_cleared[4];       /* bytes 123 to 126 */
  uint8_t mmt_benchmark_indicator[4];         /* bytes 127 to 130 */
  uint8_t mmt_contribution_to_price[4];       /* bytes 131 to 134 */
  uint8_t multiplier_scale_code;              /* byte 135 */
  uint8_t price_ascii_ch_20[20];              /* bytes 136 to 155 */
  uint8_t quantity[20];                       /* bytes 156 to 175 */
  uint8_t notional_amount[20];                /* bytes 176 to 195 */
  uint8_t transaction_id_code[52];            /* bytes 196 to 247 */
  uint8_t mmt_market_mechanism;               /* byte 248 */
  uint8_t mmt_trading_mode;                   /* byte 249 */
  uint8_t mmt_special_dividend_indicator[4];  /* bytes 250 to 253 */
  uint8_t mmt_negotiation_indicator[4];       /* bytes 254 to 257 */
  uint8_t mmt_agency_cross_indicator[4];      /* bytes 258 to 261 */
  uint8_t mmt_transaction_category[4];        /* bytes 262 to 265 */
  uint8_t mmt_modification_indicator[4];      /* bytes 266 to 269 */
  uint8_t mmt_duplicative_indicator[4];       /* bytes 270 to 273 */
  uint8_t mmt_publication_mode[4];            /* bytes 274 to 277 */
  uint8_t mmt_algorithmic_indicator[4];       /* bytes 278 to 281 */
  uint8_t reserved_2[2];                      /* bytes 282 to 283 */
} TradePublicationMessage;

/* any Trade Publication Message at all: every byte one the checker chooses */
static void any_trade_publication_message(TradePublicationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id_code_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_multiplier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 27; i++) { record->trading_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->price_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->instrument_id_code[i] = arbitrary(); }
  for (size_t i = 0; i < 27; i++) { record->publication_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->tcs_trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_to_be_cleared[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_benchmark_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_contribution_to_price[i] = arbitrary(); }
  record->multiplier_scale_code = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->price_ascii_ch_20[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->notional_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 52; i++) { record->transaction_id_code[i] = arbitrary(); }
  record->mmt_market_mechanism = arbitrary();
  record->mmt_trading_mode = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->mmt_special_dividend_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_negotiation_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_agency_cross_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_transaction_category[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_modification_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_duplicative_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_publication_mode[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_algorithmic_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Trade Publication Message to the wire: 284 bytes from at, returning where the next byte goes */
static size_t encode_trade_publication_message(const TradePublicationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue_of_execution[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id_code_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_multiplier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 27; i++) { wire[at++] = record->trading_date_time[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->price_currency[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->instrument_id_code[i]; }
  for (size_t i = 0; i < 27; i++) { wire[at++] = record->publication_date_time[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->notional_currency[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->tcs_trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_notation[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_to_be_cleared[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_benchmark_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_contribution_to_price[i]; }
  wire[at++] = record->multiplier_scale_code;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->price_ascii_ch_20[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->notional_amount[i]; }
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->transaction_id_code[i]; }
  wire[at++] = record->mmt_market_mechanism;
  wire[at++] = record->mmt_trading_mode;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_special_dividend_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_negotiation_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_agency_cross_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_transaction_category[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_modification_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_duplicative_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_publication_mode[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_algorithmic_indicator[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Trade Publication Message off the wire: 284 bytes from at, returning where the next byte lies */
static size_t decode_trade_publication_message(TradePublicationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id_code_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_multiplier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 27; i++) { record->trading_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->price_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->instrument_id_code[i] = wire[at++]; }
  for (size_t i = 0; i < 27; i++) { record->publication_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->tcs_trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_to_be_cleared[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_benchmark_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_contribution_to_price[i] = wire[at++]; }
  record->multiplier_scale_code = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->price_ascii_ch_20[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->notional_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 52; i++) { record->transaction_id_code[i] = wire[at++]; }
  record->mmt_market_mechanism = wire[at++];
  record->mmt_trading_mode = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->mmt_special_dividend_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_negotiation_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_agency_cross_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_transaction_category[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_modification_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_duplicative_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_publication_mode[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_algorithmic_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Publication Message is what was written, byte for byte */
static void equal_trade_publication_message(const TradePublicationMessage *read, const TradePublicationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->venue_of_execution[i] == written->venue_of_execution[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id_code_type[i] == written->instrument_id_code_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_multiplier[i] == written->price_multiplier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 27; i++) { assert(read->trading_date_time[i] == written->trading_date_time[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->price_currency[i] == written->price_currency[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->instrument_id_code[i] == written->instrument_id_code[i]); }
  for (size_t i = 0; i < 27; i++) { assert(read->publication_date_time[i] == written->publication_date_time[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->notional_currency[i] == written->notional_currency[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->tcs_trade_id[i] == written->tcs_trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_notation[i] == written->price_notation[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_to_be_cleared[i] == written->transaction_to_be_cleared[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_benchmark_indicator[i] == written->mmt_benchmark_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_contribution_to_price[i] == written->mmt_contribution_to_price[i]); }
  assert(read->multiplier_scale_code == written->multiplier_scale_code);
  for (size_t i = 0; i < 20; i++) { assert(read->price_ascii_ch_20[i] == written->price_ascii_ch_20[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->notional_amount[i] == written->notional_amount[i]); }
  for (size_t i = 0; i < 52; i++) { assert(read->transaction_id_code[i] == written->transaction_id_code[i]); }
  assert(read->mmt_market_mechanism == written->mmt_market_mechanism);
  assert(read->mmt_trading_mode == written->mmt_trading_mode);
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_special_dividend_indicator[i] == written->mmt_special_dividend_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_negotiation_indicator[i] == written->mmt_negotiation_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_agency_cross_indicator[i] == written->mmt_agency_cross_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_transaction_category[i] == written->mmt_transaction_category[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_modification_indicator[i] == written->mmt_modification_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_duplicative_indicator[i] == written->mmt_duplicative_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_publication_mode[i] == written->mmt_publication_mode[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_algorithmic_indicator[i] == written->mmt_algorithmic_indicator[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Trade Publication Message: written and read back, then read and written back */
static void check_trade_publication_message(void) {
  TradePublicationMessage sent;
  TradePublicationMessage got;
  uint8_t wire[284];
  uint8_t again[284];

  any_trade_publication_message(&sent);
  assert(encode_trade_publication_message(&sent, wire, 0) == 284);
  assert(decode_trade_publication_message(&got, wire, 0) == 284);
  equal_trade_publication_message(&got, &sent);

  for (size_t i = 0; i < 284; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_publication_message(&got, wire, 0) == 284);
  assert(encode_trade_publication_message(&got, again, 0) == 284);
  for (size_t i = 0; i < 284; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Summary Message: 48 bytes --------------------------------------- */

/* An Auction Summary message summarizes an instrument's opening or auction trades */
typedef struct {
  uint8_t symbol_index[4];             /* bytes 0 to 3 */
  uint8_t source_time[4];              /* bytes 4 to 7 */
  uint8_t source_seq_num[4];           /* bytes 8 to 11 */
  uint8_t first_price[4];              /* bytes 12 to 15 */
  uint8_t last_price[4];               /* bytes 16 to 19 */
  uint8_t highest_price[4];            /* bytes 20 to 23 */
  uint8_t lowest_price[4];             /* bytes 24 to 27 */
  uint8_t cumulative_quantity[4];      /* bytes 28 to 31 */
  uint8_t variation[4];                /* bytes 32 to 35 */
  uint8_t system_id[4];                /* bytes 36 to 39 */
  uint8_t source_time_micro_secs[2];   /* bytes 40 to 41 */
  uint8_t type_of_last_price[2];       /* bytes 42 to 43 */
  uint8_t tick_direction;              /* byte 44 */
  uint8_t instrument_valuation_price;  /* byte 45 */
  uint8_t price_scale_code;            /* byte 46 */
  uint8_t variation_scale_code;        /* byte 47 */
} AuctionSummaryMessage;

/* any Auction Summary Message at all: every byte one the checker chooses */
static void any_auction_summary_message(AuctionSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->first_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->highest_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lowest_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cumulative_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->variation[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->type_of_last_price[i] = arbitrary(); }
  record->tick_direction = arbitrary();
  record->instrument_valuation_price = arbitrary();
  record->price_scale_code = arbitrary();
  record->variation_scale_code = arbitrary();
}

/* Auction Summary Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_auction_summary_message(const AuctionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->highest_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lowest_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cumulative_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->variation[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->type_of_last_price[i]; }
  wire[at++] = record->tick_direction;
  wire[at++] = record->instrument_valuation_price;
  wire[at++] = record->price_scale_code;
  wire[at++] = record->variation_scale_code;

  return at;
}

/* Auction Summary Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_auction_summary_message(AuctionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->first_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->highest_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lowest_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cumulative_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->variation[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->type_of_last_price[i] = wire[at++]; }
  record->tick_direction = wire[at++];
  record->instrument_valuation_price = wire[at++];
  record->price_scale_code = wire[at++];
  record->variation_scale_code = wire[at++];

  return at;
}

/* what was read of Auction Summary Message is what was written, byte for byte */
static void equal_auction_summary_message(const AuctionSummaryMessage *read, const AuctionSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->first_price[i] == written->first_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->highest_price[i] == written->highest_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lowest_price[i] == written->lowest_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cumulative_quantity[i] == written->cumulative_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->variation[i] == written->variation[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->type_of_last_price[i] == written->type_of_last_price[i]); }
  assert(read->tick_direction == written->tick_direction);
  assert(read->instrument_valuation_price == written->instrument_valuation_price);
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->variation_scale_code == written->variation_scale_code);
}

/* Auction Summary Message: written and read back, then read and written back */
static void check_auction_summary_message(void) {
  AuctionSummaryMessage sent;
  AuctionSummaryMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_auction_summary_message(&sent);
  assert(encode_auction_summary_message(&sent, wire, 0) == 48);
  assert(decode_auction_summary_message(&got, wire, 0) == 48);
  equal_auction_summary_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_summary_message(&got, wire, 0) == 48);
  assert(encode_auction_summary_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Vwap Closing Price Message: 52 bytes ------------------------------------ */

/* This message contains the Volume-Weighted Average Price for an instrument, along with few statistical information related to the cumulated traded value and volume */
typedef struct {
  uint8_t symbol_index[4];            /* bytes 0 to 3 */
  uint8_t source_time[4];             /* bytes 4 to 7 */
  uint8_t source_seq_num[4];          /* bytes 8 to 11 */
  uint8_t sending_indicator[2];       /* bytes 12 to 13 */
  uint8_t closing_price_rule[2];      /* bytes 14 to 15 */
  uint8_t closing_price[4];           /* bytes 16 to 19 */
  uint8_t adjusted_closing_price[4];  /* bytes 20 to 23 */
  uint8_t nb_trades[4];               /* bytes 24 to 27 */
  uint8_t amount_traded[8];           /* bytes 28 to 35 */
  uint8_t qty_shares[4];              /* bytes 36 to 39 */
  uint8_t system_id[4];               /* bytes 40 to 43 */
  uint8_t source_time_micro_secs[2];  /* bytes 44 to 45 */
  uint8_t scale_code;                 /* byte 46 */
  uint8_t reserved_5[5];              /* bytes 47 to 51 */
} VwapClosingPriceMessage;

/* any Vwap Closing Price Message at all: every byte one the checker chooses */
static void any_vwap_closing_price_message(VwapClosingPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->sending_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->closing_price_rule[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->adjusted_closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nb_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->amount_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->qty_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  record->scale_code = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->reserved_5[i] = arbitrary(); }
}

/* Vwap Closing Price Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_vwap_closing_price_message(const VwapClosingPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sending_indicator[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->closing_price_rule[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->closing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->adjusted_closing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nb_trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->amount_traded[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->qty_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  wire[at++] = record->scale_code;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->reserved_5[i]; }

  return at;
}

/* Vwap Closing Price Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_vwap_closing_price_message(VwapClosingPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->sending_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->closing_price_rule[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->adjusted_closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nb_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->amount_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->qty_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  record->scale_code = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->reserved_5[i] = wire[at++]; }

  return at;
}

/* what was read of Vwap Closing Price Message is what was written, byte for byte */
static void equal_vwap_closing_price_message(const VwapClosingPriceMessage *read, const VwapClosingPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->sending_indicator[i] == written->sending_indicator[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->closing_price_rule[i] == written->closing_price_rule[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->adjusted_closing_price[i] == written->adjusted_closing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nb_trades[i] == written->nb_trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->amount_traded[i] == written->amount_traded[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->qty_shares[i] == written->qty_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  assert(read->scale_code == written->scale_code);
  for (size_t i = 0; i < 5; i++) { assert(read->reserved_5[i] == written->reserved_5[i]); }
}

/* Vwap Closing Price Message: written and read back, then read and written back */
static void check_vwap_closing_price_message(void) {
  VwapClosingPriceMessage sent;
  VwapClosingPriceMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_vwap_closing_price_message(&sent);
  assert(encode_vwap_closing_price_message(&sent, wire, 0) == 52);
  assert(decode_vwap_closing_price_message(&got, wire, 0) == 52);
  equal_vwap_closing_price_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_vwap_closing_price_message(&got, wire, 0) == 52);
  assert(encode_vwap_closing_price_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_trade_full_information_message();
  check_price_update_message();
  check_trade_publication_message();
  check_auction_summary_message();
  check_vwap_closing_price_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
