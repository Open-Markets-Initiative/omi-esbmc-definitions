// bmv/bmvmarketdata/product37/BmvMarketData_Product37_v1_1.c
/*
 * Bolsa Mexicana de Valores Bmv Market Data Product 37
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

/* ---- Message Header: 4 bytes ------------------------------------------------- */

/* Message length and message type */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t message_type[2];    /* bytes 2 to 3 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = arbitrary(); }
}

/* Message Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_type[i]; }

  return at;
}

/* Message Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
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

/* ---- Order Adition Message: 35 bytes ----------------------------------------- */

/* When the order is accepted by the BMV central system, this message is disseminated to the relevant media. */
typedef struct {
  uint8_t id_instrument[4];  /* bytes 0 to 3 */
  uint8_t date_and_hour[8];  /* bytes 4 to 11 */
  uint8_t folio[4];          /* bytes 12 to 15 */
  uint8_t direction;         /* byte 16 */
  uint8_t volume[4];         /* bytes 17 to 20 */
  uint8_t price[8];          /* bytes 21 to 28 */
  uint8_t participant[5];    /* bytes 29 to 33 */
  uint8_t operation_type;    /* byte 34 */
} OrderAditionMessage;

/* any Order Adition Message at all: every byte one the checker chooses */
static void any_order_adition_message(OrderAditionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->id_instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_and_hour[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->folio[i] = arbitrary(); }
  record->direction = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->participant[i] = arbitrary(); }
  record->operation_type = arbitrary();
}

/* Order Adition Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_order_adition_message(const OrderAditionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->id_instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_and_hour[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->folio[i]; }
  wire[at++] = record->direction;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->participant[i]; }
  wire[at++] = record->operation_type;

  return at;
}

/* Order Adition Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_order_adition_message(OrderAditionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->id_instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_and_hour[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->folio[i] = wire[at++]; }
  record->direction = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->participant[i] = wire[at++]; }
  record->operation_type = wire[at++];

  return at;
}

/* what was read of Order Adition Message is what was written, byte for byte */
static void equal_order_adition_message(const OrderAditionMessage *read, const OrderAditionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->id_instrument[i] == written->id_instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_and_hour[i] == written->date_and_hour[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->folio[i] == written->folio[i]); }
  assert(read->direction == written->direction);
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->participant[i] == written->participant[i]); }
  assert(read->operation_type == written->operation_type);
}

/* Order Adition Message: written and read back, then read and written back */
static void check_order_adition_message(void) {
  OrderAditionMessage sent;
  OrderAditionMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_order_adition_message(&sent);
  assert(encode_order_adition_message(&sent, wire, 0) == 35);
  assert(decode_order_adition_message(&got, wire, 0) == 35);
  equal_order_adition_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_order_adition_message(&got, wire, 0) == 35);
  assert(encode_order_adition_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Of Orders Message: 33 bytes ----------------------------------- */

/* The message is disseminated as soon as there is a match in the BMV's electronic system. */
typedef struct {
  uint8_t id_instrument[4];    /* bytes 0 to 3 */
  uint8_t date[8];             /* bytes 4 to 11 */
  uint8_t folio[4];            /* bytes 12 to 15 */
  uint8_t volume[4];           /* bytes 16 to 19 */
  uint8_t trade_number[4];     /* bytes 20 to 23 */
  uint8_t execution_price[8];  /* bytes 24 to 31 */
  uint8_t operation_type;      /* byte 32 */
} ExecutionOfOrdersMessage;

/* any Execution Of Orders Message at all: every byte one the checker chooses */
static void any_execution_of_orders_message(ExecutionOfOrdersMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->id_instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->folio[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_price[i] = arbitrary(); }
  record->operation_type = arbitrary();
}

/* Execution Of Orders Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_execution_of_orders_message(const ExecutionOfOrdersMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->id_instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->folio[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_price[i]; }
  wire[at++] = record->operation_type;

  return at;
}

/* Execution Of Orders Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_execution_of_orders_message(ExecutionOfOrdersMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->id_instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->folio[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_price[i] = wire[at++]; }
  record->operation_type = wire[at++];

  return at;
}

/* what was read of Execution Of Orders Message is what was written, byte for byte */
static void equal_execution_of_orders_message(const ExecutionOfOrdersMessage *read, const ExecutionOfOrdersMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->id_instrument[i] == written->id_instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->folio[i] == written->folio[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
  assert(read->operation_type == written->operation_type);
}

/* Execution Of Orders Message: written and read back, then read and written back */
static void check_execution_of_orders_message(void) {
  ExecutionOfOrdersMessage sent;
  ExecutionOfOrdersMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_execution_of_orders_message(&sent);
  assert(encode_execution_of_orders_message(&sent, wire, 0) == 33);
  assert(decode_execution_of_orders_message(&got, wire, 0) == 33);
  equal_execution_of_orders_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_of_orders_message(&got, wire, 0) == 33);
  assert(encode_execution_of_orders_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancellation Message: 17 bytes ------------------------------------ */

/* This message indicates the fully elimination of an order in the trading floor */
typedef struct {
  uint8_t id_instrument[4];  /* bytes 0 to 3 */
  uint8_t date[8];           /* bytes 4 to 11 */
  uint8_t folio[4];          /* bytes 12 to 15 */
  uint8_t operation_type;    /* byte 16 */
} OrderCancellationMessage;

/* any Order Cancellation Message at all: every byte one the checker chooses */
static void any_order_cancellation_message(OrderCancellationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->id_instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->folio[i] = arbitrary(); }
  record->operation_type = arbitrary();
}

/* Order Cancellation Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_order_cancellation_message(const OrderCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->id_instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->folio[i]; }
  wire[at++] = record->operation_type;

  return at;
}

/* Order Cancellation Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_order_cancellation_message(OrderCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->id_instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->folio[i] = wire[at++]; }
  record->operation_type = wire[at++];

  return at;
}

/* what was read of Order Cancellation Message is what was written, byte for byte */
static void equal_order_cancellation_message(const OrderCancellationMessage *read, const OrderCancellationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->id_instrument[i] == written->id_instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->folio[i] == written->folio[i]); }
  assert(read->operation_type == written->operation_type);
}

/* Order Cancellation Message: written and read back, then read and written back */
static void check_order_cancellation_message(void) {
  OrderCancellationMessage sent;
  OrderCancellationMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_order_cancellation_message(&sent);
  assert(encode_order_cancellation_message(&sent, wire, 0) == 17);
  assert(decode_order_cancellation_message(&got, wire, 0) == 17);
  equal_order_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancellation_message(&got, wire, 0) == 17);
  assert(encode_order_cancellation_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Change Message: 42 bytes ------------------------------------------ */

/* Message sent when the order modifies any of its data, the system assigns it a new priority in the electronic book, the order to be replaced is identified with the original Instrument, Date, and Folio, and the new priority assignment in the electronic book appears in the New Date and Folio fields. */
typedef struct {
  uint8_t id_instrument[4];   /* bytes 0 to 3 */
  uint8_t original_date[8];   /* bytes 4 to 11 */
  uint8_t original_folio[4];  /* bytes 12 to 15 */
  uint8_t new_date[8];        /* bytes 16 to 23 */
  uint8_t new_folio[4];       /* bytes 24 to 27 */
  uint8_t direction;          /* byte 28 */
  uint8_t volume[4];          /* bytes 29 to 32 */
  uint8_t price[8];           /* bytes 33 to 40 */
  uint8_t operation_type;     /* byte 41 */
} OrderChangeMessage;

/* any Order Change Message at all: every byte one the checker chooses */
static void any_order_change_message(OrderChangeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->id_instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_folio[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->new_folio[i] = arbitrary(); }
  record->direction = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->operation_type = arbitrary();
}

/* Order Change Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_order_change_message(const OrderChangeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->id_instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_folio[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_folio[i]; }
  wire[at++] = record->direction;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->operation_type;

  return at;
}

/* Order Change Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_order_change_message(OrderChangeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->id_instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_folio[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->new_folio[i] = wire[at++]; }
  record->direction = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->operation_type = wire[at++];

  return at;
}

/* what was read of Order Change Message is what was written, byte for byte */
static void equal_order_change_message(const OrderChangeMessage *read, const OrderChangeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->id_instrument[i] == written->id_instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_date[i] == written->original_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_folio[i] == written->original_folio[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_date[i] == written->new_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->new_folio[i] == written->new_folio[i]); }
  assert(read->direction == written->direction);
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->operation_type == written->operation_type);
}

/* Order Change Message: written and read back, then read and written back */
static void check_order_change_message(void) {
  OrderChangeMessage sent;
  OrderChangeMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_order_change_message(&sent);
  assert(encode_order_change_message(&sent, wire, 0) == 42);
  assert(decode_order_change_message(&got, wire, 0) == 42);
  equal_order_change_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_order_change_message(&got, wire, 0) == 42);
  assert(encode_order_change_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_i_n_t_r_a_multicast_header();
  check_message_header();
  check_order_adition_message();
  check_execution_of_orders_message();
  check_order_cancellation_message();
  check_order_change_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
