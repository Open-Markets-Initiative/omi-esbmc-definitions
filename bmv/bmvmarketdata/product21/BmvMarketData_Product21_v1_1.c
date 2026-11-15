// bmv/bmvmarketdata/product21/BmvMarketData_Product21_v1_1.c
/*
 * Bolsa Mexicana de Valores Bmv Market Data Product 21
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

/* ---- INTRA Multicast Header: 17 bytes ---------------------------------------- */

/* BMV INTRA Multicast Header */
typedef struct {
  uint8_t length[2];           /* bytes 0 to 1 */
  uint8_t total_messages;      /* byte 2 */
  uint8_t market_data_group;   /* byte 3 */
  uint8_t session;             /* byte 4 */
  uint8_t sequence_number[4];  /* bytes 5 to 8 */
  uint8_t datetime[8];         /* bytes 9 to 16 */
} INTRAMulticastHeader;

/* any INTRA Multicast Header at all: every byte one the checker chooses */
static void any_i_n_t_r_a_multicast_header(INTRAMulticastHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  record->total_messages = arbitrary();
  record->market_data_group = arbitrary();
  record->session = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->datetime[i] = arbitrary(); }
}

/* INTRA Multicast Header to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_i_n_t_r_a_multicast_header(const INTRAMulticastHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  wire[at++] = record->total_messages;
  wire[at++] = record->market_data_group;
  wire[at++] = record->session;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->datetime[i]; }

  return at;
}

/* INTRA Multicast Header off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_i_n_t_r_a_multicast_header(INTRAMulticastHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  record->total_messages = wire[at++];
  record->market_data_group = wire[at++];
  record->session = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->datetime[i] = wire[at++]; }

  return at;
}

/* what was read of INTRA Multicast Header is what was written, byte for byte */
static void equal_i_n_t_r_a_multicast_header(const INTRAMulticastHeader *read, const INTRAMulticastHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  assert(read->total_messages == written->total_messages);
  assert(read->market_data_group == written->market_data_group);
  assert(read->session == written->session);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->datetime[i] == written->datetime[i]); }
}

/* INTRA Multicast Header: written and read back, then read and written back */
static void check_i_n_t_r_a_multicast_header(void) {
  INTRAMulticastHeader sent;
  INTRAMulticastHeader got;
  uint8_t wire[17];
  uint8_t again[17];

  any_i_n_t_r_a_multicast_header(&sent);
  assert(encode_i_n_t_r_a_multicast_header(&sent, wire, 0) == 17);
  assert(decode_i_n_t_r_a_multicast_header(&got, wire, 0) == 17);
  equal_i_n_t_r_a_multicast_header(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_i_n_t_r_a_multicast_header(&got, wire, 0) == 17);
  assert(encode_i_n_t_r_a_multicast_header(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* Message length and message type */
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

/* ---- Events System Message: 22 bytes ----------------------------------------- */

/* The system of events message is used to inform that an event has occurred, which needs to be of public domain. */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t event_code;            /* byte 4 */
  uint8_t market;                /* byte 5 */
  uint8_t sending_time[8];       /* bytes 6 to 13 */
  uint8_t ending_time[8];        /* bytes 14 to 21 */
} EventsSystemMessage;

/* any Events System Message at all: every byte one the checker chooses */
static void any_events_system_message(EventsSystemMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  record->event_code = arbitrary();
  record->market = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ending_time[i] = arbitrary(); }
}

/* Events System Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_events_system_message(const EventsSystemMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  wire[at++] = record->event_code;
  wire[at++] = record->market;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ending_time[i]; }

  return at;
}

/* Events System Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_events_system_message(EventsSystemMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  record->event_code = wire[at++];
  record->market = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Events System Message is what was written, byte for byte */
static void equal_events_system_message(const EventsSystemMessage *read, const EventsSystemMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  assert(read->event_code == written->event_code);
  assert(read->market == written->market);
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ending_time[i] == written->ending_time[i]); }
}

/* Events System Message: written and read back, then read and written back */
static void check_events_system_message(void) {
  EventsSystemMessage sent;
  EventsSystemMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_events_system_message(&sent);
  assert(encode_events_system_message(&sent, wire, 0) == 22);
  assert(decode_events_system_message(&got, wire, 0) == 22);
  equal_events_system_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_events_system_message(&got, wire, 0) == 22);
  assert(encode_events_system_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dollar Buy Sell Message: 38 bytes --------------------------------------- */

/* Dollar Buy/Sell */
typedef struct {
  uint8_t posture_date[8];  /* bytes 0 to 7 */
  uint8_t currency[5];      /* bytes 8 to 12 */
  uint8_t dollar_side;      /* byte 13 */
  uint8_t buy[8];           /* bytes 14 to 21 */
  uint8_t sell[8];          /* bytes 22 to 29 */
  uint8_t last_deal[8];     /* bytes 30 to 37 */
} DollarBuySellMessage;

/* any Dollar Buy Sell Message at all: every byte one the checker chooses */
static void any_dollar_buy_sell_message(DollarBuySellMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->posture_date[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->currency[i] = arbitrary(); }
  record->dollar_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->buy[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_deal[i] = arbitrary(); }
}

/* Dollar Buy Sell Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_dollar_buy_sell_message(const DollarBuySellMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->posture_date[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->dollar_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_deal[i]; }

  return at;
}

/* Dollar Buy Sell Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_dollar_buy_sell_message(DollarBuySellMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->posture_date[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->currency[i] = wire[at++]; }
  record->dollar_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->buy[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_deal[i] = wire[at++]; }

  return at;
}

/* what was read of Dollar Buy Sell Message is what was written, byte for byte */
static void equal_dollar_buy_sell_message(const DollarBuySellMessage *read, const DollarBuySellMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->posture_date[i] == written->posture_date[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->dollar_side == written->dollar_side);
  for (size_t i = 0; i < 8; i++) { assert(read->buy[i] == written->buy[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell[i] == written->sell[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_deal[i] == written->last_deal[i]); }
}

/* Dollar Buy Sell Message: written and read back, then read and written back */
static void check_dollar_buy_sell_message(void) {
  DollarBuySellMessage sent;
  DollarBuySellMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_dollar_buy_sell_message(&sent);
  assert(encode_dollar_buy_sell_message(&sent, wire, 0) == 38);
  assert(decode_dollar_buy_sell_message(&got, wire, 0) == 38);
  equal_dollar_buy_sell_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_dollar_buy_sell_message(&got, wire, 0) == 38);
  assert(encode_dollar_buy_sell_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Sales Balances Per Instrument Message: 44 bytes ------------------- */

/* Short sales balances per instrument */
typedef struct {
  uint8_t instrument_number[4];  /* bytes 0 to 3 */
  uint8_t date[8];               /* bytes 4 to 11 */
  uint8_t previous_balance[8];   /* bytes 12 to 19 */
  uint8_t amount_traded[8];      /* bytes 20 to 27 */
  uint8_t buybacks[8];           /* bytes 28 to 35 */
  uint8_t current_balance[8];    /* bytes 36 to 43 */
} ShortSalesBalancesPerInstrumentMessage;

/* any Short Sales Balances Per Instrument Message at all: every byte one the checker chooses */
static void any_short_sales_balances_per_instrument_message(ShortSalesBalancesPerInstrumentMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_balance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->amount_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buybacks[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->current_balance[i] = arbitrary(); }
}

/* Short Sales Balances Per Instrument Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_short_sales_balances_per_instrument_message(const ShortSalesBalancesPerInstrumentMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_balance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->amount_traded[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buybacks[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->current_balance[i]; }

  return at;
}

/* Short Sales Balances Per Instrument Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_short_sales_balances_per_instrument_message(ShortSalesBalancesPerInstrumentMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_balance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->amount_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buybacks[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->current_balance[i] = wire[at++]; }

  return at;
}

/* what was read of Short Sales Balances Per Instrument Message is what was written, byte for byte */
static void equal_short_sales_balances_per_instrument_message(const ShortSalesBalancesPerInstrumentMessage *read, const ShortSalesBalancesPerInstrumentMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_number[i] == written->instrument_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_balance[i] == written->previous_balance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->amount_traded[i] == written->amount_traded[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buybacks[i] == written->buybacks[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->current_balance[i] == written->current_balance[i]); }
}

/* Short Sales Balances Per Instrument Message: written and read back, then read and written back */
static void check_short_sales_balances_per_instrument_message(void) {
  ShortSalesBalancesPerInstrumentMessage sent;
  ShortSalesBalancesPerInstrumentMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_short_sales_balances_per_instrument_message(&sent);
  assert(encode_short_sales_balances_per_instrument_message(&sent, wire, 0) == 44);
  assert(decode_short_sales_balances_per_instrument_message(&got, wire, 0) == 44);
  equal_short_sales_balances_per_instrument_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_short_sales_balances_per_instrument_message(&got, wire, 0) == 44);
  assert(encode_short_sales_balances_per_instrument_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Capital Market Multiples Message: 130 bytes ----------------------------- */

/* Capital Market Multiples */
typedef struct {
  uint8_t instrument_id[4];       /* bytes 0 to 3 */
  uint8_t multiple_type;          /* byte 4 */
  uint8_t registry_number;        /* byte 5 */
  uint8_t sector;                 /* byte 6 */
  uint8_t subsector;              /* byte 7 */
  uint8_t business_line;          /* byte 8 */
  uint8_t sub_line;               /* byte 9 */
  uint8_t pflepa_multiple[8];     /* bytes 10 to 17 */
  uint8_t pfepa_multiple[8];      /* bytes 18 to 25 */
  uint8_t ve_uaiida_multiple[8];  /* bytes 26 to 33 */
  uint8_t p_u[8];                 /* bytes 34 to 41 */
  uint8_t p_vl[8];                /* bytes 42 to 49 */
  uint8_t f_1_p_unoc[8];          /* bytes 50 to 57 */
  uint8_t f_2_p_unoc[8];          /* bytes 58 to 65 */
  uint8_t f_1_p_ue[8];            /* bytes 66 to 73 */
  uint8_t f_2_p_ue[8];            /* bytes 74 to 81 */
  uint8_t f_1_ve_uaiida[8];       /* bytes 82 to 89 */
  uint8_t f_2_ve_uaiida[8];       /* bytes 90 to 97 */
  uint8_t f_1_p_u[8];             /* bytes 98 to 105 */
  uint8_t f_2_p_u[8];             /* bytes 106 to 113 */
  uint8_t f_1_p_vl[8];            /* bytes 114 to 121 */
  uint8_t f_2_p_vl[8];            /* bytes 122 to 129 */
} CapitalMarketMultiplesMessage;

/* any Capital Market Multiples Message at all: every byte one the checker chooses */
static void any_capital_market_multiples_message(CapitalMarketMultiplesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->multiple_type = arbitrary();
  record->registry_number = arbitrary();
  record->sector = arbitrary();
  record->subsector = arbitrary();
  record->business_line = arbitrary();
  record->sub_line = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->pflepa_multiple[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->pfepa_multiple[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ve_uaiida_multiple[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->p_u[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->p_vl[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_1_p_unoc[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_2_p_unoc[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_1_p_ue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_2_p_ue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_1_ve_uaiida[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_2_ve_uaiida[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_1_p_u[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_2_p_u[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_1_p_vl[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->f_2_p_vl[i] = arbitrary(); }
}

/* Capital Market Multiples Message to the wire: 130 bytes from at, returning where the next byte goes */
static size_t encode_capital_market_multiples_message(const CapitalMarketMultiplesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->multiple_type;
  wire[at++] = record->registry_number;
  wire[at++] = record->sector;
  wire[at++] = record->subsector;
  wire[at++] = record->business_line;
  wire[at++] = record->sub_line;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pflepa_multiple[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pfepa_multiple[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ve_uaiida_multiple[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->p_u[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->p_vl[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_1_p_unoc[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_2_p_unoc[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_1_p_ue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_2_p_ue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_1_ve_uaiida[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_2_ve_uaiida[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_1_p_u[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_2_p_u[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_1_p_vl[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->f_2_p_vl[i]; }

  return at;
}

/* Capital Market Multiples Message off the wire: 130 bytes from at, returning where the next byte lies */
static size_t decode_capital_market_multiples_message(CapitalMarketMultiplesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->multiple_type = wire[at++];
  record->registry_number = wire[at++];
  record->sector = wire[at++];
  record->subsector = wire[at++];
  record->business_line = wire[at++];
  record->sub_line = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->pflepa_multiple[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->pfepa_multiple[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ve_uaiida_multiple[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->p_u[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->p_vl[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_1_p_unoc[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_2_p_unoc[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_1_p_ue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_2_p_ue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_1_ve_uaiida[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_2_ve_uaiida[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_1_p_u[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_2_p_u[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_1_p_vl[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->f_2_p_vl[i] = wire[at++]; }

  return at;
}

/* what was read of Capital Market Multiples Message is what was written, byte for byte */
static void equal_capital_market_multiples_message(const CapitalMarketMultiplesMessage *read, const CapitalMarketMultiplesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->multiple_type == written->multiple_type);
  assert(read->registry_number == written->registry_number);
  assert(read->sector == written->sector);
  assert(read->subsector == written->subsector);
  assert(read->business_line == written->business_line);
  assert(read->sub_line == written->sub_line);
  for (size_t i = 0; i < 8; i++) { assert(read->pflepa_multiple[i] == written->pflepa_multiple[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->pfepa_multiple[i] == written->pfepa_multiple[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ve_uaiida_multiple[i] == written->ve_uaiida_multiple[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->p_u[i] == written->p_u[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->p_vl[i] == written->p_vl[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_1_p_unoc[i] == written->f_1_p_unoc[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_2_p_unoc[i] == written->f_2_p_unoc[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_1_p_ue[i] == written->f_1_p_ue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_2_p_ue[i] == written->f_2_p_ue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_1_ve_uaiida[i] == written->f_1_ve_uaiida[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_2_ve_uaiida[i] == written->f_2_ve_uaiida[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_1_p_u[i] == written->f_1_p_u[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_2_p_u[i] == written->f_2_p_u[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_1_p_vl[i] == written->f_1_p_vl[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->f_2_p_vl[i] == written->f_2_p_vl[i]); }
}

/* Capital Market Multiples Message: written and read back, then read and written back */
static void check_capital_market_multiples_message(void) {
  CapitalMarketMultiplesMessage sent;
  CapitalMarketMultiplesMessage got;
  uint8_t wire[130];
  uint8_t again[130];

  any_capital_market_multiples_message(&sent);
  assert(encode_capital_market_multiples_message(&sent, wire, 0) == 130);
  assert(decode_capital_market_multiples_message(&got, wire, 0) == 130);
  equal_capital_market_multiples_message(&got, &sent);

  for (size_t i = 0; i < 130; i++) { wire[i] = arbitrary(); }
  assert(decode_capital_market_multiples_message(&got, wire, 0) == 130);
  assert(encode_capital_market_multiples_message(&got, again, 0) == 130);
  for (size_t i = 0; i < 130; i++) { assert(again[i] == wire[i]); }
}

/* ---- Benchmark Message: 149 bytes -------------------------------------------- */

/* Benchmark */
typedef struct {
  uint8_t benchmark_name[40];                      /* bytes 0 to 39 */
  uint8_t benchmark_date[8];                       /* bytes 40 to 47 */
  uint8_t outstanding[8];                          /* bytes 48 to 55 */
  uint8_t integer_amount[8];                       /* bytes 56 to 63 */
  uint8_t decimal_amount[4];                       /* bytes 64 to 67 */
  uint8_t indices[8];                              /* bytes 68 to 75 */
  uint8_t indices_24[8];                           /* bytes 76 to 83 */
  uint8_t rebalance;                               /* byte 84 */
  uint8_t daily_performance[8];                    /* bytes 85 to 92 */
  uint8_t annual_performance[8];                   /* bytes 93 to 100 */
  uint8_t monthly_performance[8];                  /* bytes 101 to 108 */
  uint8_t last_12_months_performance[8];           /* bytes 109 to 116 */
  uint8_t v24_hours_daily_performance[8];          /* bytes 117 to 124 */
  uint8_t v24_hours_annual_performance[8];         /* bytes 125 to 132 */
  uint8_t v24_hours_monthly_performance[8];        /* bytes 133 to 140 */
  uint8_t last_12_months_24_hours_performance[8];  /* bytes 141 to 148 */
} BenchmarkMessage;

/* any Benchmark Message at all: every byte one the checker chooses */
static void any_benchmark_message(BenchmarkMessage *record) {
  for (size_t i = 0; i < 40; i++) { record->benchmark_name[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->benchmark_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->outstanding[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->integer_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->decimal_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indices[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indices_24[i] = arbitrary(); }
  record->rebalance = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->daily_performance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->annual_performance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->monthly_performance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_12_months_performance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->v24_hours_daily_performance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->v24_hours_annual_performance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->v24_hours_monthly_performance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_12_months_24_hours_performance[i] = arbitrary(); }
}

/* Benchmark Message to the wire: 149 bytes from at, returning where the next byte goes */
static size_t encode_benchmark_message(const BenchmarkMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->benchmark_name[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->benchmark_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->outstanding[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->integer_amount[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decimal_amount[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indices[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indices_24[i]; }
  wire[at++] = record->rebalance;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->daily_performance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->annual_performance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->monthly_performance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_12_months_performance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->v24_hours_daily_performance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->v24_hours_annual_performance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->v24_hours_monthly_performance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_12_months_24_hours_performance[i]; }

  return at;
}

/* Benchmark Message off the wire: 149 bytes from at, returning where the next byte lies */
static size_t decode_benchmark_message(BenchmarkMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 40; i++) { record->benchmark_name[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->benchmark_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->outstanding[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->integer_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->decimal_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indices[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indices_24[i] = wire[at++]; }
  record->rebalance = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->daily_performance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->annual_performance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->monthly_performance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_12_months_performance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->v24_hours_daily_performance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->v24_hours_annual_performance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->v24_hours_monthly_performance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_12_months_24_hours_performance[i] = wire[at++]; }

  return at;
}

/* what was read of Benchmark Message is what was written, byte for byte */
static void equal_benchmark_message(const BenchmarkMessage *read, const BenchmarkMessage *written) {
  for (size_t i = 0; i < 40; i++) { assert(read->benchmark_name[i] == written->benchmark_name[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->benchmark_date[i] == written->benchmark_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->outstanding[i] == written->outstanding[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->integer_amount[i] == written->integer_amount[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->decimal_amount[i] == written->decimal_amount[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indices[i] == written->indices[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indices_24[i] == written->indices_24[i]); }
  assert(read->rebalance == written->rebalance);
  for (size_t i = 0; i < 8; i++) { assert(read->daily_performance[i] == written->daily_performance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->annual_performance[i] == written->annual_performance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->monthly_performance[i] == written->monthly_performance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_12_months_performance[i] == written->last_12_months_performance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->v24_hours_daily_performance[i] == written->v24_hours_daily_performance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->v24_hours_annual_performance[i] == written->v24_hours_annual_performance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->v24_hours_monthly_performance[i] == written->v24_hours_monthly_performance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_12_months_24_hours_performance[i] == written->last_12_months_24_hours_performance[i]); }
}

/* Benchmark Message: written and read back, then read and written back */
static void check_benchmark_message(void) {
  BenchmarkMessage sent;
  BenchmarkMessage got;
  uint8_t wire[149];
  uint8_t again[149];

  any_benchmark_message(&sent);
  assert(encode_benchmark_message(&sent, wire, 0) == 149);
  assert(decode_benchmark_message(&got, wire, 0) == 149);
  equal_benchmark_message(&got, &sent);

  for (size_t i = 0; i < 149; i++) { wire[i] = arbitrary(); }
  assert(decode_benchmark_message(&got, wire, 0) == 149);
  assert(encode_benchmark_message(&got, again, 0) == 149);
  for (size_t i = 0; i < 149; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_i_n_t_r_a_multicast_header();
  check_message_header();
  check_events_system_message();
  check_dollar_buy_sell_message();
  check_short_sales_balances_per_instrument_message();
  check_capital_market_multiples_message();
  check_benchmark_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
