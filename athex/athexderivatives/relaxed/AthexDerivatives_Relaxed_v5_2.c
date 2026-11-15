// athex/athexderivatives/relaxed/AthexDerivatives_Relaxed_v5_2.c
/*
 * Athens Exchange Group Athens Exchange Derivatives Market Relaxed Channel
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

/* ---- Message Header: 35 bytes ------------------------------------------------ */

/* Thirty five character header succeeding the Soh character of every message packet */
typedef struct {
  uint8_t vendor_identifier[2];        /* bytes 0 to 1 */
  uint8_t message_category;            /* byte 2 */
  uint8_t message_subcategory;         /* byte 3 */
  uint8_t venue_i_d[4];                /* bytes 4 to 7 */
  uint8_t message_sequence_number[7];  /* bytes 8 to 14 */
  uint8_t publication_timestamp[20];   /* bytes 15 to 34 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->vendor_identifier[i] = arbitrary(); }
  record->message_category = arbitrary();
  record->message_subcategory = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->venue_i_d[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->publication_timestamp[i] = arbitrary(); }
}

/* Message Header to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->vendor_identifier[i]; }
  wire[at++] = record->message_category;
  wire[at++] = record->message_subcategory;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue_i_d[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->publication_timestamp[i]; }

  return at;
}

/* Message Header off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->vendor_identifier[i] = wire[at++]; }
  record->message_category = wire[at++];
  record->message_subcategory = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->venue_i_d[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->publication_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->vendor_identifier[i] == written->vendor_identifier[i]); }
  assert(read->message_category == written->message_category);
  assert(read->message_subcategory == written->message_subcategory);
  for (size_t i = 0; i < 4; i++) { assert(read->venue_i_d[i] == written->venue_i_d[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->publication_timestamp[i] == written->publication_timestamp[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[35];
  uint8_t again[35];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 35);
  assert(decode_message_header(&got, wire, 0) == 35);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 35);
  assert(encode_message_header(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Apa Post Trade Message: 699 bytes --------------------------------------- */

/* Transmitted whenever a trade is reported to the Ids subsystem, for the Athex Apa post trade transparency service required by Mifid II */
typedef struct {
  uint8_t report_status[4];                                  /* bytes 0 to 3 */
  uint8_t trading_date_and_time[20];                         /* bytes 4 to 23 */
  uint8_t trade_id_indicator;                                /* byte 24 */
  uint8_t trade_id[52];                                      /* bytes 25 to 76 */
  uint8_t venue[4];                                          /* bytes 77 to 80 */
  uint8_t transaction_to_be_cleared;                         /* byte 81 */
  uint8_t price_notation[4];                                 /* bytes 82 to 85 */
  uint8_t price[18];                                         /* bytes 86 to 103 */
  uint8_t price_currency[3];                                 /* bytes 104 to 106 */
  uint8_t quantity[18];                                      /* bytes 107 to 124 */
  uint8_t quantity_currency[3];                              /* bytes 125 to 127 */
  uint8_t notation_of_the_quantity_in_measurement_unit[25];  /* bytes 128 to 152 */
  uint8_t quantity_in_measurement_unit[18];                  /* bytes 153 to 170 */
  uint8_t notional_amount[18];                               /* bytes 171 to 188 */
  uint8_t notional_currency[3];                              /* bytes 189 to 191 */
  uint8_t instrument_id_type[4];                             /* bytes 192 to 195 */
  uint8_t instrument_id[12];                                 /* bytes 196 to 207 */
  uint8_t instrument_full_name[350];                         /* bytes 208 to 557 */
  uint8_t instrument_classification[6];                      /* bytes 558 to 563 */
  uint8_t price_multiplier[18];                              /* bytes 564 to 581 */
  uint8_t underlying_instrument_code[12];                    /* bytes 582 to 593 */
  uint8_t underlying_index_name[25];                         /* bytes 594 to 618 */
  uint8_t term_of_the_underlying_index[7];                   /* bytes 619 to 625 */
  uint8_t option_type[4];                                    /* bytes 626 to 629 */
  uint8_t strike_price[18];                                  /* bytes 630 to 647 */
  uint8_t strike_price_currency[3];                          /* bytes 648 to 650 */
  uint8_t strike_price_notation[4];                          /* bytes 651 to 654 */
  uint8_t option_exercise_style[4];                          /* bytes 655 to 658 */
  uint8_t maturity_date[8];                                  /* bytes 659 to 666 */
  uint8_t expiry_date[8];                                    /* bytes 667 to 674 */
  uint8_t delivery_type[4];                                  /* bytes 675 to 678 */
  uint8_t type_emission_allowance[4];                        /* bytes 679 to 682 */
  uint8_t otc_post_trade_indicator[4];                       /* bytes 683 to 686 */
  uint8_t deferral_indicator;                                /* byte 687 */
  uint8_t lmtf;                                              /* byte 688 */
  uint8_t fulf;                                              /* byte 689 */
  uint8_t datf;                                              /* byte 690 */
  uint8_t fula;                                              /* byte 691 */
  uint8_t volo;                                              /* byte 692 */
  uint8_t fulv;                                              /* byte 693 */
  uint8_t fwaf;                                              /* byte 694 */
  uint8_t fulj;                                              /* byte 695 */
  uint8_t idaf;                                              /* byte 696 */
  uint8_t volw;                                              /* byte 697 */
  uint8_t coaf;                                              /* byte 698 */
} ApaPostTradeMessage;

/* any Apa Post Trade Message at all: every byte one the checker chooses */
static void any_apa_post_trade_message(ApaPostTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->report_status[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->trading_date_and_time[i] = arbitrary(); }
  record->trade_id_indicator = arbitrary();
  for (size_t i = 0; i < 52; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->venue[i] = arbitrary(); }
  record->transaction_to_be_cleared = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->price_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->quantity_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->notation_of_the_quantity_in_measurement_unit[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->quantity_in_measurement_unit[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->notional_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id_type[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 350; i++) { record->instrument_full_name[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->instrument_classification[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->price_multiplier[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->underlying_instrument_code[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->underlying_index_name[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->term_of_the_underlying_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_type[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->strike_price_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price_notation[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_exercise_style[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expiry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->delivery_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->type_emission_allowance[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->otc_post_trade_indicator[i] = arbitrary(); }
  record->deferral_indicator = arbitrary();
  record->lmtf = arbitrary();
  record->fulf = arbitrary();
  record->datf = arbitrary();
  record->fula = arbitrary();
  record->volo = arbitrary();
  record->fulv = arbitrary();
  record->fwaf = arbitrary();
  record->fulj = arbitrary();
  record->idaf = arbitrary();
  record->volw = arbitrary();
  record->coaf = arbitrary();
}

/* Apa Post Trade Message to the wire: 699 bytes from at, returning where the next byte goes */
static size_t encode_apa_post_trade_message(const ApaPostTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->report_status[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->trading_date_and_time[i]; }
  wire[at++] = record->trade_id_indicator;
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue[i]; }
  wire[at++] = record->transaction_to_be_cleared;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_notation[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->price_currency[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->quantity_currency[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->notation_of_the_quantity_in_measurement_unit[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->quantity_in_measurement_unit[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->notional_amount[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->notional_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id_type[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 350; i++) { wire[at++] = record->instrument_full_name[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->instrument_classification[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->price_multiplier[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_instrument_code[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->underlying_index_name[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->term_of_the_underlying_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_type[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->strike_price_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price_notation[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_exercise_style[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expiry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delivery_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->type_emission_allowance[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->otc_post_trade_indicator[i]; }
  wire[at++] = record->deferral_indicator;
  wire[at++] = record->lmtf;
  wire[at++] = record->fulf;
  wire[at++] = record->datf;
  wire[at++] = record->fula;
  wire[at++] = record->volo;
  wire[at++] = record->fulv;
  wire[at++] = record->fwaf;
  wire[at++] = record->fulj;
  wire[at++] = record->idaf;
  wire[at++] = record->volw;
  wire[at++] = record->coaf;

  return at;
}

/* Apa Post Trade Message off the wire: 699 bytes from at, returning where the next byte lies */
static size_t decode_apa_post_trade_message(ApaPostTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->report_status[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->trading_date_and_time[i] = wire[at++]; }
  record->trade_id_indicator = wire[at++];
  for (size_t i = 0; i < 52; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->venue[i] = wire[at++]; }
  record->transaction_to_be_cleared = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->price_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->quantity_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->notation_of_the_quantity_in_measurement_unit[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->quantity_in_measurement_unit[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->notional_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id_type[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 350; i++) { record->instrument_full_name[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->instrument_classification[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->price_multiplier[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->underlying_instrument_code[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->underlying_index_name[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->term_of_the_underlying_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_type[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->strike_price_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price_notation[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_exercise_style[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expiry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->delivery_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->type_emission_allowance[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->otc_post_trade_indicator[i] = wire[at++]; }
  record->deferral_indicator = wire[at++];
  record->lmtf = wire[at++];
  record->fulf = wire[at++];
  record->datf = wire[at++];
  record->fula = wire[at++];
  record->volo = wire[at++];
  record->fulv = wire[at++];
  record->fwaf = wire[at++];
  record->fulj = wire[at++];
  record->idaf = wire[at++];
  record->volw = wire[at++];
  record->coaf = wire[at++];

  return at;
}

/* what was read of Apa Post Trade Message is what was written, byte for byte */
static void equal_apa_post_trade_message(const ApaPostTradeMessage *read, const ApaPostTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->report_status[i] == written->report_status[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->trading_date_and_time[i] == written->trading_date_and_time[i]); }
  assert(read->trade_id_indicator == written->trade_id_indicator);
  for (size_t i = 0; i < 52; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->venue[i] == written->venue[i]); }
  assert(read->transaction_to_be_cleared == written->transaction_to_be_cleared);
  for (size_t i = 0; i < 4; i++) { assert(read->price_notation[i] == written->price_notation[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->price_currency[i] == written->price_currency[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->quantity_currency[i] == written->quantity_currency[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->notation_of_the_quantity_in_measurement_unit[i] == written->notation_of_the_quantity_in_measurement_unit[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->quantity_in_measurement_unit[i] == written->quantity_in_measurement_unit[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->notional_amount[i] == written->notional_amount[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->notional_currency[i] == written->notional_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id_type[i] == written->instrument_id_type[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 350; i++) { assert(read->instrument_full_name[i] == written->instrument_full_name[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->instrument_classification[i] == written->instrument_classification[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->price_multiplier[i] == written->price_multiplier[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_instrument_code[i] == written->underlying_instrument_code[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->underlying_index_name[i] == written->underlying_index_name[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->term_of_the_underlying_index[i] == written->term_of_the_underlying_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_type[i] == written->option_type[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->strike_price_currency[i] == written->strike_price_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price_notation[i] == written->strike_price_notation[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_exercise_style[i] == written->option_exercise_style[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expiry_date[i] == written->expiry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->delivery_type[i] == written->delivery_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->type_emission_allowance[i] == written->type_emission_allowance[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->otc_post_trade_indicator[i] == written->otc_post_trade_indicator[i]); }
  assert(read->deferral_indicator == written->deferral_indicator);
  assert(read->lmtf == written->lmtf);
  assert(read->fulf == written->fulf);
  assert(read->datf == written->datf);
  assert(read->fula == written->fula);
  assert(read->volo == written->volo);
  assert(read->fulv == written->fulv);
  assert(read->fwaf == written->fwaf);
  assert(read->fulj == written->fulj);
  assert(read->idaf == written->idaf);
  assert(read->volw == written->volw);
  assert(read->coaf == written->coaf);
}

/* Apa Post Trade Message: written and read back, then read and written back */
static void check_apa_post_trade_message(void) {
  ApaPostTradeMessage sent;
  ApaPostTradeMessage got;
  uint8_t wire[699];
  uint8_t again[699];

  any_apa_post_trade_message(&sent);
  assert(encode_apa_post_trade_message(&sent, wire, 0) == 699);
  assert(decode_apa_post_trade_message(&got, wire, 0) == 699);
  equal_apa_post_trade_message(&got, &sent);

  for (size_t i = 0; i < 699; i++) { wire[i] = arbitrary(); }
  assert(decode_apa_post_trade_message(&got, wire, 0) == 699);
  assert(encode_apa_post_trade_message(&got, again, 0) == 699);
  for (size_t i = 0; i < 699; i++) { assert(again[i] == wire[i]); }
}

/* ---- Apa Pre Trade Message: 699 bytes ---------------------------------------- */

/* Transmitted whenever a quote is reported to the Ids subsystem by the Athex Apa service, for the Athex Apa pre trade transparency service */
typedef struct {
  uint8_t report_status[4];                                  /* bytes 0 to 3 */
  uint8_t quote_type;                                        /* byte 4 */
  uint8_t quote_id[52];                                      /* bytes 5 to 56 */
  uint8_t event_time[20];                                    /* bytes 57 to 76 */
  uint8_t quote_liquidity;                                   /* byte 77 */
  uint8_t venue_mic[4];                                      /* bytes 78 to 81 */
  uint8_t submitting_entity_identification_code[20];         /* bytes 82 to 101 */
  uint8_t price_notation[4];                                 /* bytes 102 to 105 */
  uint8_t price[18];                                         /* bytes 106 to 123 */
  uint8_t price_currency[3];                                 /* bytes 124 to 126 */
  uint8_t quantity[18];                                      /* bytes 127 to 144 */
  uint8_t quantity_currency[3];                              /* bytes 145 to 147 */
  uint8_t notation_of_the_quantity_in_measurement_unit[25];  /* bytes 148 to 172 */
  uint8_t quantity_in_measurement_unit[18];                  /* bytes 173 to 190 */
  uint8_t notional_amount[18];                               /* bytes 191 to 208 */
  uint8_t notional_currency[3];                              /* bytes 209 to 211 */
  uint8_t instrument_id_type[4];                             /* bytes 212 to 215 */
  uint8_t instrument_id[12];                                 /* bytes 216 to 227 */
  uint8_t instrument_full_name[350];                         /* bytes 228 to 577 */
  uint8_t instrument_classification[6];                      /* bytes 578 to 583 */
  uint8_t price_multiplier[18];                              /* bytes 584 to 601 */
  uint8_t underlying_instrument_code[12];                    /* bytes 602 to 613 */
  uint8_t underlying_index_name[25];                         /* bytes 614 to 638 */
  uint8_t term_of_the_underlying_index[7];                   /* bytes 639 to 645 */
  uint8_t option_type[4];                                    /* bytes 646 to 649 */
  uint8_t strike_price[18];                                  /* bytes 650 to 667 */
  uint8_t strike_price_currency[3];                          /* bytes 668 to 670 */
  uint8_t strike_price_notation[4];                          /* bytes 671 to 674 */
  uint8_t option_exercise_style[4];                          /* bytes 675 to 678 */
  uint8_t maturity_date[8];                                  /* bytes 679 to 686 */
  uint8_t expiry_date[8];                                    /* bytes 687 to 694 */
  uint8_t delivery_type[4];                                  /* bytes 695 to 698 */
} ApaPreTradeMessage;

/* any Apa Pre Trade Message at all: every byte one the checker chooses */
static void any_apa_pre_trade_message(ApaPreTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->report_status[i] = arbitrary(); }
  record->quote_type = arbitrary();
  for (size_t i = 0; i < 52; i++) { record->quote_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->event_time[i] = arbitrary(); }
  record->quote_liquidity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->venue_mic[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->submitting_entity_identification_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->price_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->quantity_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->notation_of_the_quantity_in_measurement_unit[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->quantity_in_measurement_unit[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->notional_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id_type[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 350; i++) { record->instrument_full_name[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->instrument_classification[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->price_multiplier[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->underlying_instrument_code[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->underlying_index_name[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->term_of_the_underlying_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_type[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->strike_price_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price_notation[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_exercise_style[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expiry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->delivery_type[i] = arbitrary(); }
}

/* Apa Pre Trade Message to the wire: 699 bytes from at, returning where the next byte goes */
static size_t encode_apa_pre_trade_message(const ApaPreTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->report_status[i]; }
  wire[at++] = record->quote_type;
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->quote_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->event_time[i]; }
  wire[at++] = record->quote_liquidity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue_mic[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->submitting_entity_identification_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_notation[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->price_currency[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->quantity_currency[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->notation_of_the_quantity_in_measurement_unit[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->quantity_in_measurement_unit[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->notional_amount[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->notional_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id_type[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 350; i++) { wire[at++] = record->instrument_full_name[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->instrument_classification[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->price_multiplier[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_instrument_code[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->underlying_index_name[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->term_of_the_underlying_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_type[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->strike_price_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price_notation[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_exercise_style[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expiry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delivery_type[i]; }

  return at;
}

/* Apa Pre Trade Message off the wire: 699 bytes from at, returning where the next byte lies */
static size_t decode_apa_pre_trade_message(ApaPreTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->report_status[i] = wire[at++]; }
  record->quote_type = wire[at++];
  for (size_t i = 0; i < 52; i++) { record->quote_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->event_time[i] = wire[at++]; }
  record->quote_liquidity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->venue_mic[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->submitting_entity_identification_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->price_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->quantity_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->notation_of_the_quantity_in_measurement_unit[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->quantity_in_measurement_unit[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->notional_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id_type[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 350; i++) { record->instrument_full_name[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->instrument_classification[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->price_multiplier[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->underlying_instrument_code[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->underlying_index_name[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->term_of_the_underlying_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_type[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->strike_price_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price_notation[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_exercise_style[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expiry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->delivery_type[i] = wire[at++]; }

  return at;
}

/* what was read of Apa Pre Trade Message is what was written, byte for byte */
static void equal_apa_pre_trade_message(const ApaPreTradeMessage *read, const ApaPreTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->report_status[i] == written->report_status[i]); }
  assert(read->quote_type == written->quote_type);
  for (size_t i = 0; i < 52; i++) { assert(read->quote_id[i] == written->quote_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->event_time[i] == written->event_time[i]); }
  assert(read->quote_liquidity == written->quote_liquidity);
  for (size_t i = 0; i < 4; i++) { assert(read->venue_mic[i] == written->venue_mic[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->submitting_entity_identification_code[i] == written->submitting_entity_identification_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_notation[i] == written->price_notation[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->price_currency[i] == written->price_currency[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->quantity_currency[i] == written->quantity_currency[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->notation_of_the_quantity_in_measurement_unit[i] == written->notation_of_the_quantity_in_measurement_unit[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->quantity_in_measurement_unit[i] == written->quantity_in_measurement_unit[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->notional_amount[i] == written->notional_amount[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->notional_currency[i] == written->notional_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id_type[i] == written->instrument_id_type[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 350; i++) { assert(read->instrument_full_name[i] == written->instrument_full_name[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->instrument_classification[i] == written->instrument_classification[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->price_multiplier[i] == written->price_multiplier[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_instrument_code[i] == written->underlying_instrument_code[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->underlying_index_name[i] == written->underlying_index_name[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->term_of_the_underlying_index[i] == written->term_of_the_underlying_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_type[i] == written->option_type[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->strike_price_currency[i] == written->strike_price_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price_notation[i] == written->strike_price_notation[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_exercise_style[i] == written->option_exercise_style[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expiry_date[i] == written->expiry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->delivery_type[i] == written->delivery_type[i]); }
}

/* Apa Pre Trade Message: written and read back, then read and written back */
static void check_apa_pre_trade_message(void) {
  ApaPreTradeMessage sent;
  ApaPreTradeMessage got;
  uint8_t wire[699];
  uint8_t again[699];

  any_apa_pre_trade_message(&sent);
  assert(encode_apa_pre_trade_message(&sent, wire, 0) == 699);
  assert(decode_apa_pre_trade_message(&got, wire, 0) == 699);
  equal_apa_pre_trade_message(&got, &sent);

  for (size_t i = 0; i < 699; i++) { wire[i] = arbitrary(); }
  assert(decode_apa_pre_trade_message(&got, wire, 0) == 699);
  assert(encode_apa_pre_trade_message(&got, again, 0) == 699);
  for (size_t i = 0; i < 699; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_apa_post_trade_message();
  check_apa_pre_trade_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
