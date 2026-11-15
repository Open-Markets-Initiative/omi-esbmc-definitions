// jpx/tseequities/marketbyorder/TseEquities_MarketByOrder_v1_3_Udp.c
/*
 * Japan Exchange Group Market By Order
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

/* ---- Packet Header: 26 bytes ------------------------------------------------- */

/* Jpx Flex 26 byte packet header */
typedef struct {
  uint8_t multicast_group_number;    /* byte 0 */
  uint8_t number_of_system_reboots;  /* byte 1 */
  uint8_t sequence_number[4];        /* bytes 2 to 5 */
  uint8_t issue_code[12];            /* bytes 6 to 17 */
  uint8_t update_number[4];          /* bytes 18 to 21 */
  uint8_t packet_number;             /* byte 22 */
  uint8_t total_number_of_packets;   /* byte 23 */
  uint8_t utility_flag;              /* byte 24 */
  uint8_t message_count;             /* byte 25 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  record->multicast_group_number = arbitrary();
  record->number_of_system_reboots = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->issue_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->update_number[i] = arbitrary(); }
  record->packet_number = arbitrary();
  record->total_number_of_packets = arbitrary();
  record->utility_flag = arbitrary();
  record->message_count = arbitrary();
}

/* Packet Header to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->multicast_group_number;
  wire[at++] = record->number_of_system_reboots;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->issue_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->update_number[i]; }
  wire[at++] = record->packet_number;
  wire[at++] = record->total_number_of_packets;
  wire[at++] = record->utility_flag;
  wire[at++] = record->message_count;

  return at;
}

/* Packet Header off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  record->multicast_group_number = wire[at++];
  record->number_of_system_reboots = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->issue_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->update_number[i] = wire[at++]; }
  record->packet_number = wire[at++];
  record->total_number_of_packets = wire[at++];
  record->utility_flag = wire[at++];
  record->message_count = wire[at++];

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  assert(read->multicast_group_number == written->multicast_group_number);
  assert(read->number_of_system_reboots == written->number_of_system_reboots);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->issue_code[i] == written->issue_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->update_number[i] == written->update_number[i]); }
  assert(read->packet_number == written->packet_number);
  assert(read->total_number_of_packets == written->total_number_of_packets);
  assert(read->utility_flag == written->utility_flag);
  assert(read->message_count == written->message_count);
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[26];
  uint8_t again[26];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 26);
  assert(decode_packet_header(&got, wire, 0) == 26);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 26);
  assert(encode_packet_header(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 2 bytes ------------------------------------------------- */

/* Jpx Flex tag header carrying length prefix and message type discriminator */
typedef struct {
  uint8_t tag_length;    /* byte 0 */
  uint8_t message_type;  /* byte 1 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->tag_length = arbitrary();
  record->message_type = arbitrary();
}

/* Message Header to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->tag_length;
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->tag_length = wire[at++];
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->tag_length == written->tag_length);
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[2];
  uint8_t again[2];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 2);
  assert(decode_message_header(&got, wire, 0) == 2);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 2);
  assert(encode_message_header(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Seconds Timestamp Message: 4 bytes -------------------------------------- */

/* Provides information about the time of processing on the Trading Server to the nearest second. Always delivered at the time the information is generated, except for Reset and Communication Control. Only one tag is delivered per process and stored at the top of the first packet. */
typedef struct {
  uint8_t time_seconds[4];  /* bytes 0 to 3 */
} SecondsTimestampMessage;

/* any Seconds Timestamp Message at all: every byte one the checker chooses */
static void any_seconds_timestamp_message(SecondsTimestampMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_seconds[i] = arbitrary(); }
}

/* Seconds Timestamp Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_seconds_timestamp_message(const SecondsTimestampMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_seconds[i]; }

  return at;
}

/* Seconds Timestamp Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_seconds_timestamp_message(SecondsTimestampMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Seconds Timestamp Message is what was written, byte for byte */
static void equal_seconds_timestamp_message(const SecondsTimestampMessage *read, const SecondsTimestampMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_seconds[i] == written->time_seconds[i]); }
}

/* Seconds Timestamp Message: written and read back, then read and written back */
static void check_seconds_timestamp_message(void) {
  SecondsTimestampMessage sent;
  SecondsTimestampMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_seconds_timestamp_message(&sent);
  assert(encode_seconds_timestamp_message(&sent, wire, 0) == 4);
  assert(decode_seconds_timestamp_message(&got, wire, 0) == 4);
  equal_seconds_timestamp_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_seconds_timestamp_message(&got, wire, 0) == 4);
  assert(encode_seconds_timestamp_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 17 bytes ---------------------------------------- */

/* Provides information about the status of trading on a per-issue basis. Delivered when there is a change in the tag. */
typedef struct {
  uint8_t time_microseconds[4];  /* bytes 0 to 3 */
  uint8_t market_status;         /* byte 4 */
  uint8_t status_flag[2];        /* bytes 5 to 6 */
  uint8_t short_selling_status;  /* byte 7 */
  uint8_t pricing_method;        /* byte 8 */
  uint8_t book_center_price[8];  /* bytes 9 to 16 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_microseconds[i] = arbitrary(); }
  record->market_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->status_flag[i] = arbitrary(); }
  record->short_selling_status = arbitrary();
  record->pricing_method = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->book_center_price[i] = arbitrary(); }
}

/* Trading Status Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_microseconds[i]; }
  wire[at++] = record->market_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->status_flag[i]; }
  wire[at++] = record->short_selling_status;
  wire[at++] = record->pricing_method;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_center_price[i]; }

  return at;
}

/* Trading Status Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_microseconds[i] = wire[at++]; }
  record->market_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->status_flag[i] = wire[at++]; }
  record->short_selling_status = wire[at++];
  record->pricing_method = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->book_center_price[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_microseconds[i] == written->time_microseconds[i]); }
  assert(read->market_status == written->market_status);
  for (size_t i = 0; i < 2; i++) { assert(read->status_flag[i] == written->status_flag[i]); }
  assert(read->short_selling_status == written->short_selling_status);
  assert(read->pricing_method == written->pricing_method);
  for (size_t i = 0; i < 8; i++) { assert(read->book_center_price[i] == written->book_center_price[i]); }
}

/* Trading Status Message: written and read back, then read and written back */
static void check_trading_status_message(void) {
  TradingStatusMessage sent;
  TradingStatusMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_trading_status_message(&sent);
  assert(encode_trading_status_message(&sent, wire, 0) == 17);
  assert(decode_trading_status_message(&got, wire, 0) == 17);
  equal_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_message(&got, wire, 0) == 17);
  assert(encode_trading_status_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Summary Message: 54 bytes ------------------------------------- */

/* Provides summary information about execution. Delivered when an execution occurs. */
typedef struct {
  uint8_t time_microseconds[4];    /* bytes 0 to 3 */
  uint8_t triggered_side;          /* byte 4 */
  uint8_t total_volume[6];         /* bytes 5 to 10 */
  uint8_t total_invalidation[6];   /* bytes 11 to 16 */
  uint8_t last_price[8];           /* bytes 17 to 24 */
  uint8_t match_id[4];             /* bytes 25 to 28 */
  uint8_t best_offer[8];           /* bytes 29 to 36 */
  uint8_t best_bid[8];             /* bytes 37 to 44 */
  uint8_t price_direction;         /* byte 45 */
  uint8_t stq_reference_price[8];  /* bytes 46 to 53 */
} ExecutionSummaryMessage;

/* any Execution Summary Message at all: every byte one the checker chooses */
static void any_execution_summary_message(ExecutionSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_microseconds[i] = arbitrary(); }
  record->triggered_side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_invalidation[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_offer[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_bid[i] = arbitrary(); }
  record->price_direction = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->stq_reference_price[i] = arbitrary(); }
}

/* Execution Summary Message to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_execution_summary_message(const ExecutionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_microseconds[i]; }
  wire[at++] = record->triggered_side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_volume[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_invalidation[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_offer[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_bid[i]; }
  wire[at++] = record->price_direction;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stq_reference_price[i]; }

  return at;
}

/* Execution Summary Message off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_execution_summary_message(ExecutionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_microseconds[i] = wire[at++]; }
  record->triggered_side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_invalidation[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_offer[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_bid[i] = wire[at++]; }
  record->price_direction = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->stq_reference_price[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Summary Message is what was written, byte for byte */
static void equal_execution_summary_message(const ExecutionSummaryMessage *read, const ExecutionSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_microseconds[i] == written->time_microseconds[i]); }
  assert(read->triggered_side == written->triggered_side);
  for (size_t i = 0; i < 6; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_invalidation[i] == written->total_invalidation[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_offer[i] == written->best_offer[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_bid[i] == written->best_bid[i]); }
  assert(read->price_direction == written->price_direction);
  for (size_t i = 0; i < 8; i++) { assert(read->stq_reference_price[i] == written->stq_reference_price[i]); }
}

/* Execution Summary Message: written and read back, then read and written back */
static void check_execution_summary_message(void) {
  ExecutionSummaryMessage sent;
  ExecutionSummaryMessage got;
  uint8_t wire[54];
  uint8_t again[54];

  any_execution_summary_message(&sent);
  assert(encode_execution_summary_message(&sent, wire, 0) == 54);
  assert(decode_execution_summary_message(&got, wire, 0) == 54);
  equal_execution_summary_message(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_summary_message(&got, wire, 0) == 54);
  assert(encode_execution_summary_message(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message: 25 bytes --------------------------------------------- */

/* Provides information about book registration. Delivered when a new order or modification order is registered. */
typedef struct {
  uint8_t time_microseconds[4];  /* bytes 0 to 3 */
  uint8_t order_id[4];           /* bytes 4 to 7 */
  uint8_t side;                  /* byte 8 */
  uint8_t quantity[6];           /* bytes 9 to 14 */
  uint8_t price[8];              /* bytes 15 to 22 */
  uint8_t order_condition;       /* byte 23 */
  uint8_t modification_flag;     /* byte 24 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_microseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->order_condition = arbitrary();
  record->modification_flag = arbitrary();
}

/* Add Order Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_microseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->order_condition;
  wire[at++] = record->modification_flag;

  return at;
}

/* Add Order Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_microseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->order_condition = wire[at++];
  record->modification_flag = wire[at++];

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_microseconds[i] == written->time_microseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->order_condition == written->order_condition);
  assert(read->modification_flag == written->modification_flag);
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 25);
  assert(decode_add_order_message(&got, wire, 0) == 25);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 25);
  assert(encode_add_order_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 19 bytes ---------------------------------------- */

/* Provides information about registered orders in case of Zaraba execution. Delivered when an execution occurs in Zaraba. */
typedef struct {
  uint8_t time_microseconds[4];  /* bytes 0 to 3 */
  uint8_t order_id[4];           /* bytes 4 to 7 */
  uint8_t side;                  /* byte 8 */
  uint8_t volume[6];             /* bytes 9 to 14 */
  uint8_t match_id[4];           /* bytes 15 to 18 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_microseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_microseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_id[i]; }

  return at;
}

/* Order Executed Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_microseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_microseconds[i] == written->time_microseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_id[i] == written->match_id[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 19);
  assert(decode_order_executed_message(&got, wire, 0) == 19);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 19);
  assert(encode_order_executed_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed With Price Message: 28 bytes ----------------------------- */

/* Provides information about registered orders in case of Itayose execution. Delivered when an execution occurs by the Itayose method or while an SQ or STQ is displayed. */
typedef struct {
  uint8_t time_microseconds[4];    /* bytes 0 to 3 */
  uint8_t order_id[4];             /* bytes 4 to 7 */
  uint8_t side;                    /* byte 8 */
  uint8_t volume[6];               /* bytes 9 to 14 */
  uint8_t match_id[4];             /* bytes 15 to 18 */
  uint8_t execution_price[8];      /* bytes 19 to 26 */
  uint8_t adopted_pricing_method;  /* byte 27 */
} OrderExecutedWithPriceMessage;

/* any Order Executed With Price Message at all: every byte one the checker chooses */
static void any_order_executed_with_price_message(OrderExecutedWithPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_microseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_price[i] = arbitrary(); }
  record->adopted_pricing_method = arbitrary();
}

/* Order Executed With Price Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_with_price_message(const OrderExecutedWithPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_microseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_price[i]; }
  wire[at++] = record->adopted_pricing_method;

  return at;
}

/* Order Executed With Price Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_with_price_message(OrderExecutedWithPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_microseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_price[i] = wire[at++]; }
  record->adopted_pricing_method = wire[at++];

  return at;
}

/* what was read of Order Executed With Price Message is what was written, byte for byte */
static void equal_order_executed_with_price_message(const OrderExecutedWithPriceMessage *read, const OrderExecutedWithPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_microseconds[i] == written->time_microseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
  assert(read->adopted_pricing_method == written->adopted_pricing_method);
}

/* Order Executed With Price Message: written and read back, then read and written back */
static void check_order_executed_with_price_message(void) {
  OrderExecutedWithPriceMessage sent;
  OrderExecutedWithPriceMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_order_executed_with_price_message(&sent);
  assert(encode_order_executed_with_price_message(&sent, wire, 0) == 28);
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 28);
  equal_order_executed_with_price_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 28);
  assert(encode_order_executed_with_price_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Delete Message: 10 bytes ------------------------------------------ */

/* Provides information about order deletion from the order book. Delivered when an order is deleted via a cancel order or a modification order or when a registered order expires. */
typedef struct {
  uint8_t time_microseconds[4];      /* bytes 0 to 3 */
  uint8_t order_id[4];               /* bytes 4 to 7 */
  uint8_t side;                      /* byte 8 */
  uint8_t delete_modification_flag;  /* byte 9 */
} OrderDeleteMessage;

/* any Order Delete Message at all: every byte one the checker chooses */
static void any_order_delete_message(OrderDeleteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_microseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  record->delete_modification_flag = arbitrary();
}

/* Order Delete Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_order_delete_message(const OrderDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_microseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  wire[at++] = record->delete_modification_flag;

  return at;
}

/* Order Delete Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_order_delete_message(OrderDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_microseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  record->delete_modification_flag = wire[at++];

  return at;
}

/* what was read of Order Delete Message is what was written, byte for byte */
static void equal_order_delete_message(const OrderDeleteMessage *read, const OrderDeleteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_microseconds[i] == written->time_microseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  assert(read->delete_modification_flag == written->delete_modification_flag);
}

/* Order Delete Message: written and read back, then read and written back */
static void check_order_delete_message(void) {
  OrderDeleteMessage sent;
  OrderDeleteMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_order_delete_message(&sent);
  assert(encode_order_delete_message(&sent, wire, 0) == 10);
  assert(decode_order_delete_message(&got, wire, 0) == 10);
  equal_order_delete_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_order_delete_message(&got, wire, 0) == 10);
  assert(encode_order_delete_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reset Message: 1 byte --------------------------------------------------- */

/* A tag requesting the resetting (i.e. cancellation) of all distributed information. When the user receives this tag, the user must clear all valid A tags. */
typedef struct {
  uint8_t reset_start_end_flag;  /* byte 0 */
} ResetMessage;

/* any Reset Message at all: every byte one the checker chooses */
static void any_reset_message(ResetMessage *record) {
  record->reset_start_end_flag = arbitrary();
}

/* Reset Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_reset_message(const ResetMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reset_start_end_flag;

  return at;
}

/* Reset Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_reset_message(ResetMessage *record, const uint8_t *wire, size_t at) {
  record->reset_start_end_flag = wire[at++];

  return at;
}

/* what was read of Reset Message is what was written, byte for byte */
static void equal_reset_message(const ResetMessage *read, const ResetMessage *written) {
  assert(read->reset_start_end_flag == written->reset_start_end_flag);
}

/* Reset Message: written and read back, then read and written back */
static void check_reset_message(void) {
  ResetMessage sent;
  ResetMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_reset_message(&sent);
  assert(encode_reset_message(&sent, wire, 0) == 1);
  assert(decode_reset_message(&got, wire, 0) == 1);
  equal_reset_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_reset_message(&got, wire, 0) == 1);
  assert(encode_reset_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Communication Control Message: 2 bytes ---------------------------------- */

/* Provides information about communication control. Delivered when communication starts and ends, and in between at minute intervals. */
typedef struct {
  uint8_t test_mode_flag;                /* byte 0 */
  uint8_t communication_start_end_flag;  /* byte 1 */
} CommunicationControlMessage;

/* any Communication Control Message at all: every byte one the checker chooses */
static void any_communication_control_message(CommunicationControlMessage *record) {
  record->test_mode_flag = arbitrary();
  record->communication_start_end_flag = arbitrary();
}

/* Communication Control Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_communication_control_message(const CommunicationControlMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->test_mode_flag;
  wire[at++] = record->communication_start_end_flag;

  return at;
}

/* Communication Control Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_communication_control_message(CommunicationControlMessage *record, const uint8_t *wire, size_t at) {
  record->test_mode_flag = wire[at++];
  record->communication_start_end_flag = wire[at++];

  return at;
}

/* what was read of Communication Control Message is what was written, byte for byte */
static void equal_communication_control_message(const CommunicationControlMessage *read, const CommunicationControlMessage *written) {
  assert(read->test_mode_flag == written->test_mode_flag);
  assert(read->communication_start_end_flag == written->communication_start_end_flag);
}

/* Communication Control Message: written and read back, then read and written back */
static void check_communication_control_message(void) {
  CommunicationControlMessage sent;
  CommunicationControlMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_communication_control_message(&sent);
  assert(encode_communication_control_message(&sent, wire, 0) == 2);
  assert(decode_communication_control_message(&got, wire, 0) == 2);
  equal_communication_control_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_communication_control_message(&got, wire, 0) == 2);
  assert(encode_communication_control_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_seconds_timestamp_message();
  check_trading_status_message();
  check_execution_summary_message();
  check_add_order_message();
  check_order_executed_message();
  check_order_executed_with_price_message();
  check_order_delete_message();
  check_reset_message();
  check_communication_control_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
