// nasdaq/nordicequities/lastsale/NordicEquities_LastSale_v1_2_9.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Nordic Equity Last Sale
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
 *   - the dispatch that chooses a message by its type
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

/* ---- Packet Header: 20 bytes ------------------------------------------------- */

/* Itch Mold Udp 64 Packet Header */
typedef struct {
  uint8_t session[10];         /* bytes 0 to 9 */
  uint8_t sequence_number[8];  /* bytes 10 to 17 */
  uint8_t message_count[2];    /* bytes 18 to 19 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = arbitrary(); }
}

/* Packet Header to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_count[i]; }

  return at;
}

/* Packet Header off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_count[i] == written->message_count[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[20];
  uint8_t again[20];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 20);
  assert(decode_packet_header(&got, wire, 0) == 20);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 20);
  assert(encode_packet_header(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* Mold Udp 64 Message Header */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t message_type;       /* byte 2 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
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

/* ---- Adjusted Closing Price Message: 22 bytes -------------------------------- */

/* Adjusted closing price disseminated for all active symbols at the start of each trading day */
typedef struct {
  uint8_t timestamp[8];               /* bytes 0 to 7 */
  uint8_t tracking_number[2];         /* bytes 8 to 9 */
  uint8_t order_book[4];              /* bytes 10 to 13 */
  uint8_t adjusted_closing_price[8];  /* bytes 14 to 21 */
} AdjustedClosingPriceMessage;

/* any Adjusted Closing Price Message at all: every byte one the checker chooses */
static void any_adjusted_closing_price_message(AdjustedClosingPriceMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->adjusted_closing_price[i] = arbitrary(); }
}

/* Adjusted Closing Price Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_adjusted_closing_price_message(const AdjustedClosingPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->adjusted_closing_price[i]; }

  return at;
}

/* Adjusted Closing Price Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_adjusted_closing_price_message(AdjustedClosingPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->adjusted_closing_price[i] = wire[at++]; }

  return at;
}

/* what was read of Adjusted Closing Price Message is what was written, byte for byte */
static void equal_adjusted_closing_price_message(const AdjustedClosingPriceMessage *read, const AdjustedClosingPriceMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book[i] == written->order_book[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->adjusted_closing_price[i] == written->adjusted_closing_price[i]); }
}

/* Adjusted Closing Price Message: written and read back, then read and written back */
static void check_adjusted_closing_price_message(void) {
  AdjustedClosingPriceMessage sent;
  AdjustedClosingPriceMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_adjusted_closing_price_message(&sent);
  assert(encode_adjusted_closing_price_message(&sent, wire, 0) == 22);
  assert(decode_adjusted_closing_price_message(&got, wire, 0) == 22);
  equal_adjusted_closing_price_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_adjusted_closing_price_message(&got, wire, 0) == 22);
  assert(encode_adjusted_closing_price_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- On Exchange Trade Message: 92 bytes ------------------------------------- */

/* Relays on exchange trade transactions executed or deferred to the current business day */
typedef struct {
  uint8_t timestamp[8];                     /* bytes 0 to 7 */
  uint8_t tracking_number[2];               /* bytes 8 to 9 */
  uint8_t order_book[4];                    /* bytes 10 to 13 */
  uint8_t execution_date[4];                /* bytes 14 to 17 */
  uint8_t execution_time[8];                /* bytes 18 to 25 */
  uint8_t agreement_date[4];                /* bytes 26 to 29 */
  uint8_t agreement_time[8];                /* bytes 30 to 37 */
  uint8_t price_on_exchange[8];             /* bytes 38 to 45 */
  uint8_t quantity[8];                      /* bytes 46 to 53 */
  uint8_t venue_of_execution[4];            /* bytes 54 to 57 */
  uint8_t transaction_identifier_code[10];  /* bytes 58 to 67 */
  uint8_t mmt_trade_flags[14];              /* bytes 68 to 81 */
  uint8_t trade_type;                       /* byte 82 */
  uint8_t mpid_buyer[4];                    /* bytes 83 to 86 */
  uint8_t mpid_seller[4];                   /* bytes 87 to 90 */
  uint8_t transaction_to_be_cleared;        /* byte 91 */
} OnExchangeTradeMessage;

/* any On Exchange Trade Message at all: every byte one the checker chooses */
static void any_on_exchange_trade_message(OnExchangeTradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->agreement_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->agreement_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_on_exchange[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->transaction_identifier_code[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->mmt_trade_flags[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->mpid_buyer[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid_seller[i] = arbitrary(); }
  record->transaction_to_be_cleared = arbitrary();
}

/* On Exchange Trade Message to the wire: 92 bytes from at, returning where the next byte goes */
static size_t encode_on_exchange_trade_message(const OnExchangeTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->agreement_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->agreement_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_on_exchange[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue_of_execution[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->transaction_identifier_code[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->mmt_trade_flags[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid_buyer[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid_seller[i]; }
  wire[at++] = record->transaction_to_be_cleared;

  return at;
}

/* On Exchange Trade Message off the wire: 92 bytes from at, returning where the next byte lies */
static size_t decode_on_exchange_trade_message(OnExchangeTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->agreement_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->agreement_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_on_exchange[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->transaction_identifier_code[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->mmt_trade_flags[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->mpid_buyer[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid_seller[i] = wire[at++]; }
  record->transaction_to_be_cleared = wire[at++];

  return at;
}

/* what was read of On Exchange Trade Message is what was written, byte for byte */
static void equal_on_exchange_trade_message(const OnExchangeTradeMessage *read, const OnExchangeTradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book[i] == written->order_book[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_date[i] == written->execution_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_time[i] == written->execution_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->agreement_date[i] == written->agreement_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->agreement_time[i] == written->agreement_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_on_exchange[i] == written->price_on_exchange[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->venue_of_execution[i] == written->venue_of_execution[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->transaction_identifier_code[i] == written->transaction_identifier_code[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->mmt_trade_flags[i] == written->mmt_trade_flags[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->mpid_buyer[i] == written->mpid_buyer[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid_seller[i] == written->mpid_seller[i]); }
  assert(read->transaction_to_be_cleared == written->transaction_to_be_cleared);
}

/* On Exchange Trade Message: written and read back, then read and written back */
static void check_on_exchange_trade_message(void) {
  OnExchangeTradeMessage sent;
  OnExchangeTradeMessage got;
  uint8_t wire[92];
  uint8_t again[92];

  any_on_exchange_trade_message(&sent);
  assert(encode_on_exchange_trade_message(&sent, wire, 0) == 92);
  assert(decode_on_exchange_trade_message(&got, wire, 0) == 92);
  equal_on_exchange_trade_message(&got, &sent);

  for (size_t i = 0; i < 92; i++) { wire[i] = arbitrary(); }
  assert(decode_on_exchange_trade_message(&got, wire, 0) == 92);
  assert(encode_on_exchange_trade_message(&got, again, 0) == 92);
  for (size_t i = 0; i < 92; i++) { assert(again[i] == wire[i]); }
}

/* ---- Otc Trade Message: 147 bytes -------------------------------------------- */

/* Relays over the counter and systematic internaliser trade transactions */
typedef struct {
  uint8_t timestamp[8];                                      /* bytes 0 to 7 */
  uint8_t tracking_number[2];                                /* bytes 8 to 9 */
  uint8_t instrument_identification_code_type[4];            /* bytes 10 to 13 */
  uint8_t instrument_identification_code[12];                /* bytes 14 to 25 */
  uint8_t agreement_date[4];                                 /* bytes 26 to 29 */
  uint8_t agreement_time[8];                                 /* bytes 30 to 37 */
  uint8_t price_otc[8];                                      /* bytes 38 to 45 */
  uint8_t price_fraction;                                    /* byte 46 */
  uint8_t price_notation[4];                                 /* bytes 47 to 50 */
  uint8_t price_currency[3];                                 /* bytes 51 to 53 */
  uint8_t quantity[8];                                       /* bytes 54 to 61 */
  uint8_t quantity_fraction;                                 /* byte 62 */
  uint8_t notation_of_the_quantity_in_measurement_unit[25];  /* bytes 63 to 87 */
  uint8_t quantity_in_measurement_unit[8];                   /* bytes 88 to 95 */
  uint8_t quantity_in_measurement_unit_fraction;             /* byte 96 */
  uint8_t venue_of_execution[4];                             /* bytes 97 to 100 */
  uint8_t notional_amount[8];                                /* bytes 101 to 108 */
  uint8_t notional_amount_fraction;                          /* byte 109 */
  uint8_t notional_currency[3];                              /* bytes 110 to 112 */
  uint8_t type[4];                                           /* bytes 113 to 116 */
  uint8_t transaction_identifier_code[10];                   /* bytes 117 to 126 */
  uint8_t mmt_trade_flags[14];                               /* bytes 127 to 140 */
  uint8_t transaction_to_be_cleared;                         /* byte 141 */
  uint8_t trade_type;                                        /* byte 142 */
  uint8_t third_country_trading_venue_of_execution[4];       /* bytes 143 to 146 */
} OtcTradeMessage;

/* any Otc Trade Message at all: every byte one the checker chooses */
static void any_otc_trade_message(OtcTradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_identification_code_type[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->instrument_identification_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->agreement_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->agreement_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_otc[i] = arbitrary(); }
  record->price_fraction = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->price_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  record->quantity_fraction = arbitrary();
  for (size_t i = 0; i < 25; i++) { record->notation_of_the_quantity_in_measurement_unit[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_in_measurement_unit[i] = arbitrary(); }
  record->quantity_in_measurement_unit_fraction = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->notional_amount[i] = arbitrary(); }
  record->notional_amount_fraction = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->type[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->transaction_identifier_code[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->mmt_trade_flags[i] = arbitrary(); }
  record->transaction_to_be_cleared = arbitrary();
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->third_country_trading_venue_of_execution[i] = arbitrary(); }
}

/* Otc Trade Message to the wire: 147 bytes from at, returning where the next byte goes */
static size_t encode_otc_trade_message(const OtcTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_identification_code_type[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->instrument_identification_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->agreement_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->agreement_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_otc[i]; }
  wire[at++] = record->price_fraction;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_notation[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->price_currency[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->quantity_fraction;
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->notation_of_the_quantity_in_measurement_unit[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_in_measurement_unit[i]; }
  wire[at++] = record->quantity_in_measurement_unit_fraction;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue_of_execution[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notional_amount[i]; }
  wire[at++] = record->notional_amount_fraction;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->notional_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->type[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->transaction_identifier_code[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->mmt_trade_flags[i]; }
  wire[at++] = record->transaction_to_be_cleared;
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->third_country_trading_venue_of_execution[i]; }

  return at;
}

/* Otc Trade Message off the wire: 147 bytes from at, returning where the next byte lies */
static size_t decode_otc_trade_message(OtcTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_identification_code_type[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->instrument_identification_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->agreement_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->agreement_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_otc[i] = wire[at++]; }
  record->price_fraction = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->price_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  record->quantity_fraction = wire[at++];
  for (size_t i = 0; i < 25; i++) { record->notation_of_the_quantity_in_measurement_unit[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_in_measurement_unit[i] = wire[at++]; }
  record->quantity_in_measurement_unit_fraction = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->notional_amount[i] = wire[at++]; }
  record->notional_amount_fraction = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->type[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->transaction_identifier_code[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->mmt_trade_flags[i] = wire[at++]; }
  record->transaction_to_be_cleared = wire[at++];
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->third_country_trading_venue_of_execution[i] = wire[at++]; }

  return at;
}

/* what was read of Otc Trade Message is what was written, byte for byte */
static void equal_otc_trade_message(const OtcTradeMessage *read, const OtcTradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_identification_code_type[i] == written->instrument_identification_code_type[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->instrument_identification_code[i] == written->instrument_identification_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->agreement_date[i] == written->agreement_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->agreement_time[i] == written->agreement_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_otc[i] == written->price_otc[i]); }
  assert(read->price_fraction == written->price_fraction);
  for (size_t i = 0; i < 4; i++) { assert(read->price_notation[i] == written->price_notation[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->price_currency[i] == written->price_currency[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->quantity_fraction == written->quantity_fraction);
  for (size_t i = 0; i < 25; i++) { assert(read->notation_of_the_quantity_in_measurement_unit[i] == written->notation_of_the_quantity_in_measurement_unit[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_in_measurement_unit[i] == written->quantity_in_measurement_unit[i]); }
  assert(read->quantity_in_measurement_unit_fraction == written->quantity_in_measurement_unit_fraction);
  for (size_t i = 0; i < 4; i++) { assert(read->venue_of_execution[i] == written->venue_of_execution[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->notional_amount[i] == written->notional_amount[i]); }
  assert(read->notional_amount_fraction == written->notional_amount_fraction);
  for (size_t i = 0; i < 3; i++) { assert(read->notional_currency[i] == written->notional_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->type[i] == written->type[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->transaction_identifier_code[i] == written->transaction_identifier_code[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->mmt_trade_flags[i] == written->mmt_trade_flags[i]); }
  assert(read->transaction_to_be_cleared == written->transaction_to_be_cleared);
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->third_country_trading_venue_of_execution[i] == written->third_country_trading_venue_of_execution[i]); }
}

/* Otc Trade Message: written and read back, then read and written back */
static void check_otc_trade_message(void) {
  OtcTradeMessage sent;
  OtcTradeMessage got;
  uint8_t wire[147];
  uint8_t again[147];

  any_otc_trade_message(&sent);
  assert(encode_otc_trade_message(&sent, wire, 0) == 147);
  assert(decode_otc_trade_message(&got, wire, 0) == 147);
  equal_otc_trade_message(&got, &sent);

  for (size_t i = 0; i < 147; i++) { wire[i] = arbitrary(); }
  assert(decode_otc_trade_message(&got, wire, 0) == 147);
  assert(encode_otc_trade_message(&got, again, 0) == 147);
  for (size_t i = 0; i < 147; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_adjusted_closing_price_message();
  check_on_exchange_trade_message();
  check_otc_trade_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
