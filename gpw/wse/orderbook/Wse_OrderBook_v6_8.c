// gpw/wse/orderbook/Wse_OrderBook_v6_8.c
/*
 * Giełda Papierów Wartościowych w Warszawie Warsaw Stock Exchange Order Book
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

/* ---- Order Update Market Sheet Message: 60 bytes ----------------------------- */

/* The Order update message generated by the trading engine UTP indicates the creation or modification of a line in the "market sheet" (a.k.a */
typedef struct {
  uint8_t symbol_index[4];               /* bytes 0 to 3 */
  uint8_t source_time[4];                /* bytes 4 to 7 */
  uint8_t source_seq_num[4];             /* bytes 8 to 11 */
  uint8_t price[4];                      /* bytes 12 to 15 */
  uint8_t aggregated_volume[4];          /* bytes 16 to 19 */
  uint8_t volume[4];                     /* bytes 20 to 23 */
  uint8_t link_id[4];                    /* bytes 24 to 27 */
  uint8_t order_id[4];                   /* bytes 28 to 31 */
  uint8_t system_id[4];                  /* bytes 32 to 35 */
  uint8_t source_time_micro_secs[2];     /* bytes 36 to 37 */
  uint8_t number_orders[2];              /* bytes 38 to 39 */
  uint8_t side;                          /* byte 40 */
  uint8_t order_type;                    /* byte 41 */
  uint8_t action_type;                   /* byte 42 */
  uint8_t price_scale_code;              /* byte 43 */
  uint8_t order_date[4];                 /* bytes 44 to 47 */
  uint8_t order_priority_date[4];        /* bytes 48 to 51 */
  uint8_t order_priority_time[4];        /* bytes 52 to 55 */
  uint8_t order_priority_micro_secs[2];  /* bytes 56 to 57 */
  uint8_t order_origin;                  /* byte 58 */
  uint8_t reserved_1;                    /* byte 59 */
} OrderUpdateMarketSheetMessage;

/* any Order Update Market Sheet Message at all: every byte one the checker chooses */
static void any_order_update_market_sheet_message(OrderUpdateMarketSheetMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->aggregated_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->link_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_orders[i] = arbitrary(); }
  record->side = arbitrary();
  record->order_type = arbitrary();
  record->action_type = arbitrary();
  record->price_scale_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_priority_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_priority_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->order_priority_micro_secs[i] = arbitrary(); }
  record->order_origin = arbitrary();
  record->reserved_1 = arbitrary();
}

/* Order Update Market Sheet Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_order_update_market_sheet_message(const OrderUpdateMarketSheetMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->aggregated_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->link_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_orders[i]; }
  wire[at++] = record->side;
  wire[at++] = record->order_type;
  wire[at++] = record->action_type;
  wire[at++] = record->price_scale_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_priority_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_priority_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->order_priority_micro_secs[i]; }
  wire[at++] = record->order_origin;
  wire[at++] = record->reserved_1;

  return at;
}

/* Order Update Market Sheet Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_order_update_market_sheet_message(OrderUpdateMarketSheetMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->aggregated_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->link_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_orders[i] = wire[at++]; }
  record->side = wire[at++];
  record->order_type = wire[at++];
  record->action_type = wire[at++];
  record->price_scale_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_priority_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_priority_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->order_priority_micro_secs[i] = wire[at++]; }
  record->order_origin = wire[at++];
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Order Update Market Sheet Message is what was written, byte for byte */
static void equal_order_update_market_sheet_message(const OrderUpdateMarketSheetMessage *read, const OrderUpdateMarketSheetMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->aggregated_volume[i] == written->aggregated_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->link_id[i] == written->link_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_orders[i] == written->number_orders[i]); }
  assert(read->side == written->side);
  assert(read->order_type == written->order_type);
  assert(read->action_type == written->action_type);
  assert(read->price_scale_code == written->price_scale_code);
  for (size_t i = 0; i < 4; i++) { assert(read->order_date[i] == written->order_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_priority_date[i] == written->order_priority_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_priority_time[i] == written->order_priority_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->order_priority_micro_secs[i] == written->order_priority_micro_secs[i]); }
  assert(read->order_origin == written->order_origin);
  assert(read->reserved_1 == written->reserved_1);
}

/* Order Update Market Sheet Message: written and read back, then read and written back */
static void check_order_update_market_sheet_message(void) {
  OrderUpdateMarketSheetMessage sent;
  OrderUpdateMarketSheetMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_order_update_market_sheet_message(&sent);
  assert(encode_order_update_market_sheet_message(&sent, wire, 0) == 60);
  assert(decode_order_update_market_sheet_message(&got, wire, 0) == 60);
  equal_order_update_market_sheet_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_order_update_market_sheet_message(&got, wire, 0) == 60);
  assert(encode_order_update_market_sheet_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Book Retransmission Delimiter Message: 12 bytes ------------------- */

/* The Orderbook retransmission delimiter message is set to clean then update the market sheet with the orders from previous days still remaining in the order book */
typedef struct {
  uint8_t source_time[4];            /* bytes 0 to 3 */
  uint8_t source_seq_num[4];         /* bytes 4 to 7 */
  uint8_t application_id[2];         /* bytes 8 to 9 */
  uint8_t instance_num;              /* byte 10 */
  uint8_t retransmission_indicator;  /* byte 11 */
} OrderBookRetransmissionDelimiterMessage;

/* any Order Book Retransmission Delimiter Message at all: every byte one the checker chooses */
static void any_order_book_retransmission_delimiter_message(OrderBookRetransmissionDelimiterMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->application_id[i] = arbitrary(); }
  record->instance_num = arbitrary();
  record->retransmission_indicator = arbitrary();
}

/* Order Book Retransmission Delimiter Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_order_book_retransmission_delimiter_message(const OrderBookRetransmissionDelimiterMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->application_id[i]; }
  wire[at++] = record->instance_num;
  wire[at++] = record->retransmission_indicator;

  return at;
}

/* Order Book Retransmission Delimiter Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_order_book_retransmission_delimiter_message(OrderBookRetransmissionDelimiterMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->application_id[i] = wire[at++]; }
  record->instance_num = wire[at++];
  record->retransmission_indicator = wire[at++];

  return at;
}

/* what was read of Order Book Retransmission Delimiter Message is what was written, byte for byte */
static void equal_order_book_retransmission_delimiter_message(const OrderBookRetransmissionDelimiterMessage *read, const OrderBookRetransmissionDelimiterMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->application_id[i] == written->application_id[i]); }
  assert(read->instance_num == written->instance_num);
  assert(read->retransmission_indicator == written->retransmission_indicator);
}

/* Order Book Retransmission Delimiter Message: written and read back, then read and written back */
static void check_order_book_retransmission_delimiter_message(void) {
  OrderBookRetransmissionDelimiterMessage sent;
  OrderBookRetransmissionDelimiterMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_order_book_retransmission_delimiter_message(&sent);
  assert(encode_order_book_retransmission_delimiter_message(&sent, wire, 0) == 12);
  assert(decode_order_book_retransmission_delimiter_message(&got, wire, 0) == 12);
  equal_order_book_retransmission_delimiter_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_retransmission_delimiter_message(&got, wire, 0) == 12);
  assert(encode_order_book_retransmission_delimiter_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_order_update_market_sheet_message();
  check_order_book_retransmission_delimiter_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
