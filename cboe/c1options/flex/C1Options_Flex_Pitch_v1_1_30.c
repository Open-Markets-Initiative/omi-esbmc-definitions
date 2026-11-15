// cboe/c1options/flex/C1Options_Flex_Pitch_v1_1_30.c
/*
 * Chicago Board Options Exchange Flex
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
 *   - a run filling what frames it
 *   - a field read in bits
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

/* ---- Packet Header: 8 bytes -------------------------------------------------- */

typedef struct {
  uint8_t length[2];      /* bytes 0 to 1 */
  uint8_t message_count;  /* byte 2 */
  uint8_t unit;           /* byte 3 */
  uint8_t sequence[4];    /* bytes 4 to 7 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  record->message_count = arbitrary();
  record->unit = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
}

/* Packet Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  wire[at++] = record->message_count;
  wire[at++] = record->unit;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }

  return at;
}

/* Packet Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  record->message_count = wire[at++];
  record->unit = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  assert(read->message_count == written->message_count);
  assert(read->unit == written->unit);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 8);
  assert(decode_packet_header(&got, wire, 0) == 8);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 8);
  assert(encode_packet_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 2 bytes ------------------------------------------------- */

typedef struct {
  uint8_t message_length;  /* byte 0 */
  uint8_t message_type;    /* byte 1 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->message_length = arbitrary();
  record->message_type = arbitrary();
}

/* Message Header to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_length;
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->message_length = wire[at++];
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->message_length == written->message_length);
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

/* ---- Time Reference Message: 16 bytes ---------------------------------------- */

/* The Time Reference message is used to provide a midnight reference point for recipients of the feed. */
typedef struct {
  uint8_t midnight_reference[4];  /* bytes 0 to 3 */
  uint8_t time[4];                /* bytes 4 to 7 */
  uint8_t time_offset[4];         /* bytes 8 to 11 */
  uint8_t trade_date[4];          /* bytes 12 to 15 */
} TimeReferenceMessage;

/* any Time Reference Message at all: every byte one the checker chooses */
static void any_time_reference_message(TimeReferenceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->midnight_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = arbitrary(); }
}

/* Time Reference Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_time_reference_message(const TimeReferenceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->midnight_reference[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_date[i]; }

  return at;
}

/* Time Reference Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_time_reference_message(TimeReferenceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->midnight_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = wire[at++]; }

  return at;
}

/* what was read of Time Reference Message is what was written, byte for byte */
static void equal_time_reference_message(const TimeReferenceMessage *read, const TimeReferenceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->midnight_reference[i] == written->midnight_reference[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
}

/* Time Reference Message: written and read back, then read and written back */
static void check_time_reference_message(void) {
  TimeReferenceMessage sent;
  TimeReferenceMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_time_reference_message(&sent);
  assert(encode_time_reference_message(&sent, wire, 0) == 16);
  assert(decode_time_reference_message(&got, wire, 0) == 16);
  equal_time_reference_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_time_reference_message(&got, wire, 0) == 16);
  assert(encode_time_reference_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Time Message: 8 bytes --------------------------------------------------- */

/* A Time message is immediately generated and sent when there is a FLEX event for a given clock second. */
typedef struct {
  uint8_t time[4];        /* bytes 0 to 3 */
  uint8_t epoch_time[4];  /* bytes 4 to 7 */
} TimeMessage;

/* any Time Message at all: every byte one the checker chooses */
static void any_time_message(TimeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->epoch_time[i] = arbitrary(); }
}

/* Time Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_time_message(const TimeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->epoch_time[i]; }

  return at;
}

/* Time Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_time_message(TimeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->epoch_time[i] = wire[at++]; }

  return at;
}

/* what was read of Time Message is what was written, byte for byte */
static void equal_time_message(const TimeMessage *read, const TimeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->epoch_time[i] == written->epoch_time[i]); }
}

/* Time Message: written and read back, then read and written back */
static void check_time_message(void) {
  TimeMessage sent;
  TimeMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_time_message(&sent);
  assert(encode_time_message(&sent, wire, 0) == 8);
  assert(decode_time_message(&got, wire, 0) == 8);
  equal_time_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_time_message(&got, wire, 0) == 8);
  assert(encode_time_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Notification Message: 45 bytes ---------------------------------- */

/* Auction Notification messages are used to disseminate order details of a FLEX Auction. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t flex_instrument_id[6];  /* bytes 4 to 9 */
  uint8_t auction_id[8];          /* bytes 10 to 17 */
  uint8_t auction_type;           /* byte 18 */
  uint8_t side;                   /* byte 19 */
  uint8_t signed_price_long[8];   /* bytes 20 to 27 */
  uint8_t quantity_long[4];       /* bytes 28 to 31 */
  uint8_t customer_indicator;     /* byte 32 */
  uint8_t participant_id[4];      /* bytes 33 to 36 */
  uint8_t auction_end_offset[4];  /* bytes 37 to 40 */
  uint8_t client_id[4];           /* bytes 41 to 44 */
} AuctionNotificationMessage;

/* any Auction Notification Message at all: every byte one the checker chooses */
static void any_auction_notification_message(AuctionNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->flex_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = arbitrary(); }
  record->auction_type = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  record->customer_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_end_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
}

/* Auction Notification Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_auction_notification_message(const AuctionNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->flex_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_id[i]; }
  wire[at++] = record->auction_type;
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->signed_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  wire[at++] = record->customer_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_end_offset[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }

  return at;
}

/* Auction Notification Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_auction_notification_message(AuctionNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->flex_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = wire[at++]; }
  record->auction_type = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  record->customer_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_end_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Notification Message is what was written, byte for byte */
static void equal_auction_notification_message(const AuctionNotificationMessage *read, const AuctionNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->flex_instrument_id[i] == written->flex_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  assert(read->auction_type == written->auction_type);
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->signed_price_long[i] == written->signed_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  assert(read->customer_indicator == written->customer_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_id[i] == written->participant_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_end_offset[i] == written->auction_end_offset[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
}

/* Auction Notification Message: written and read back, then read and written back */
static void check_auction_notification_message(void) {
  AuctionNotificationMessage sent;
  AuctionNotificationMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_auction_notification_message(&sent);
  assert(encode_auction_notification_message(&sent, wire, 0) == 45);
  assert(decode_auction_notification_message(&got, wire, 0) == 45);
  equal_auction_notification_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_notification_message(&got, wire, 0) == 45);
  assert(encode_auction_notification_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Cancel Message: 12 bytes ---------------------------------------- */

/* Auction Cancel messages are used to disseminate the cancellation of an earlier Auction Notification message. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
  uint8_t auction_id[8];   /* bytes 4 to 11 */
} AuctionCancelMessage;

/* any Auction Cancel Message at all: every byte one the checker chooses */
static void any_auction_cancel_message(AuctionCancelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = arbitrary(); }
}

/* Auction Cancel Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_auction_cancel_message(const AuctionCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_id[i]; }

  return at;
}

/* Auction Cancel Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_auction_cancel_message(AuctionCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Cancel Message is what was written, byte for byte */
static void equal_auction_cancel_message(const AuctionCancelMessage *read, const AuctionCancelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
}

/* Auction Cancel Message: written and read back, then read and written back */
static void check_auction_cancel_message(void) {
  AuctionCancelMessage sent;
  AuctionCancelMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_auction_cancel_message(&sent);
  assert(encode_auction_cancel_message(&sent, wire, 0) == 12);
  assert(decode_auction_cancel_message(&got, wire, 0) == 12);
  equal_auction_cancel_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_cancel_message(&got, wire, 0) == 12);
  assert(encode_auction_cancel_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Trade Message: 32 bytes ----------------------------------------- */

/* Auction Trade messages are used to disseminate executions resulting from an auction. */
typedef struct {
  uint8_t time_offset[4];        /* bytes 0 to 3 */
  uint8_t auction_id[8];         /* bytes 4 to 11 */
  uint8_t execution_id[8];       /* bytes 12 to 19 */
  uint8_t signed_price_long[8];  /* bytes 20 to 27 */
  uint8_t quantity_long[4];      /* bytes 28 to 31 */
} AuctionTradeMessage;

/* any Auction Trade Message at all: every byte one the checker chooses */
static void any_auction_trade_message(AuctionTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
}

/* Auction Trade Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_auction_trade_message(const AuctionTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->signed_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }

  return at;
}

/* Auction Trade Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_auction_trade_message(AuctionTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Trade Message is what was written, byte for byte */
static void equal_auction_trade_message(const AuctionTradeMessage *read, const AuctionTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->signed_price_long[i] == written->signed_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
}

/* Auction Trade Message: written and read back, then read and written back */
static void check_auction_trade_message(void) {
  AuctionTradeMessage sent;
  AuctionTradeMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_auction_trade_message(&sent);
  assert(encode_auction_trade_message(&sent, wire, 0) == 32);
  assert(decode_auction_trade_message(&got, wire, 0) == 32);
  equal_auction_trade_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_trade_message(&got, wire, 0) == 32);
  assert(encode_auction_trade_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Long Message: 40 bytes -------------------------------------------- */

/* The Trade message provides information about executions of FLEX orders on the Cboe Options trading floor. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t order_id[8];            /* bytes 4 to 11 */
  uint8_t side_indicator;         /* byte 12 */
  uint8_t quantity_long[4];       /* bytes 13 to 16 */
  uint8_t flex_instrument_id[6];  /* bytes 17 to 22 */
  uint8_t signed_price_long[8];   /* bytes 23 to 30 */
  uint8_t execution_id[8];        /* bytes 31 to 38 */
  uint8_t trade_condition;        /* byte 39 */
} TradeLongMessage;

/* any Trade Long Message at all: every byte one the checker chooses */
static void any_trade_long_message(TradeLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->flex_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Trade Long Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_trade_long_message(const TradeLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->flex_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->signed_price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Trade Long Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_trade_long_message(TradeLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->flex_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Trade Long Message is what was written, byte for byte */
static void equal_trade_long_message(const TradeLongMessage *read, const TradeLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->flex_instrument_id[i] == written->flex_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->signed_price_long[i] == written->signed_price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Trade Long Message: written and read back, then read and written back */
static void check_trade_long_message(void) {
  TradeLongMessage sent;
  TradeLongMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_trade_long_message(&sent);
  assert(encode_trade_long_message(&sent, wire, 0) == 40);
  assert(decode_trade_long_message(&got, wire, 0) == 40);
  equal_trade_long_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_long_message(&got, wire, 0) == 40);
  assert(encode_trade_long_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Short Message: 32 bytes ------------------------------------------- */

/* The Trade (short) message provides information about executions of FLEX orders on the Cboe Options trading floor. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t order_id[8];            /* bytes 4 to 11 */
  uint8_t side_indicator;         /* byte 12 */
  uint8_t quantity_short[2];      /* bytes 13 to 14 */
  uint8_t flex_instrument_id[6];  /* bytes 15 to 20 */
  uint8_t signed_price_short[2];  /* bytes 21 to 22 */
  uint8_t execution_id[8];        /* bytes 23 to 30 */
  uint8_t trade_condition;        /* byte 31 */
} TradeShortMessage;

/* any Trade Short Message at all: every byte one the checker chooses */
static void any_trade_short_message(TradeShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->flex_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->signed_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Trade Short Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_trade_short_message(const TradeShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quantity_short[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->flex_instrument_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->signed_price_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Trade Short Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_trade_short_message(TradeShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->flex_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->signed_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Trade Short Message is what was written, byte for byte */
static void equal_trade_short_message(const TradeShortMessage *read, const TradeShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->quantity_short[i] == written->quantity_short[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->flex_instrument_id[i] == written->flex_instrument_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->signed_price_short[i] == written->signed_price_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Trade Short Message: written and read back, then read and written back */
static void check_trade_short_message(void) {
  TradeShortMessage sent;
  TradeShortMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_trade_short_message(&sent);
  assert(encode_trade_short_message(&sent, wire, 0) == 32);
  assert(decode_trade_short_message(&got, wire, 0) == 32);
  equal_trade_short_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_short_message(&got, wire, 0) == 32);
  assert(encode_trade_short_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dac Trade Message: 58 bytes --------------------------------------------- */

/* The DAC Trade message provides information about executions of Delta Adjusted at Close (DAC) FLEX orders on the Cboe Options trading floor. */
typedef struct {
  uint8_t time_offset[4];          /* bytes 0 to 3 */
  uint8_t order_id[8];             /* bytes 4 to 11 */
  uint8_t side_indicator;          /* byte 12 */
  uint8_t quantity_long[4];        /* bytes 13 to 16 */
  uint8_t flex_instrument_id[6];   /* bytes 17 to 22 */
  uint8_t signed_price_long[8];    /* bytes 23 to 30 */
  uint8_t execution_id[8];         /* bytes 31 to 38 */
  uint8_t trade_condition;         /* byte 39 */
  uint8_t dac_reference_price[8];  /* bytes 40 to 47 */
  uint8_t dac_closing_price[8];    /* bytes 48 to 55 */
  uint8_t dac_delta_value[2];      /* bytes 56 to 57 */
} DacTradeMessage;

/* any Dac Trade Message at all: every byte one the checker chooses */
static void any_dac_trade_message(DacTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->flex_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  record->trade_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->dac_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->dac_closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->dac_delta_value[i] = arbitrary(); }
}

/* Dac Trade Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_dac_trade_message(const DacTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->flex_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->signed_price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->trade_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->dac_reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->dac_closing_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->dac_delta_value[i]; }

  return at;
}

/* Dac Trade Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_dac_trade_message(DacTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->flex_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  record->trade_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->dac_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->dac_closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->dac_delta_value[i] = wire[at++]; }

  return at;
}

/* what was read of Dac Trade Message is what was written, byte for byte */
static void equal_dac_trade_message(const DacTradeMessage *read, const DacTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->flex_instrument_id[i] == written->flex_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->signed_price_long[i] == written->signed_price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->trade_condition == written->trade_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->dac_reference_price[i] == written->dac_reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->dac_closing_price[i] == written->dac_closing_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->dac_delta_value[i] == written->dac_delta_value[i]); }
}

/* Dac Trade Message: written and read back, then read and written back */
static void check_dac_trade_message(void) {
  DacTradeMessage sent;
  DacTradeMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_dac_trade_message(&sent);
  assert(encode_dac_trade_message(&sent, wire, 0) == 58);
  assert(decode_dac_trade_message(&got, wire, 0) == 58);
  equal_dac_trade_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_dac_trade_message(&got, wire, 0) == 58);
  assert(encode_dac_trade_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Break Message: 12 bytes ------------------------------------------- */

/* The Trade Break message is sent whenever a FLEX options execution on Cboe is broken. */
typedef struct {
  uint8_t time_offset[4];   /* bytes 0 to 3 */
  uint8_t execution_id[8];  /* bytes 4 to 11 */
} TradeBreakMessage;

/* any Trade Break Message at all: every byte one the checker chooses */
static void any_trade_break_message(TradeBreakMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
}

/* Trade Break Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_trade_break_message(const TradeBreakMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Trade Break Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_trade_break_message(TradeBreakMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Break Message is what was written, byte for byte */
static void equal_trade_break_message(const TradeBreakMessage *read, const TradeBreakMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Trade Break Message: written and read back, then read and written back */
static void check_trade_break_message(void) {
  TradeBreakMessage sent;
  TradeBreakMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_trade_break_message(&sent);
  assert(encode_trade_break_message(&sent, wire, 0) == 12);
  assert(decode_trade_break_message(&got, wire, 0) == 12);
  equal_trade_break_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_break_message(&got, wire, 0) == 12);
  assert(encode_trade_break_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Mapping Message: 36 bytes ---------------------------------------- */

/* A Symbol Mapping message is used to map the 6 character multicast feed symbol field to an OSI symbol and Underlying. */
typedef struct {
  uint8_t feed_symbol[6];    /* bytes 0 to 5 */
  uint8_t osi_symbol[21];    /* bytes 6 to 26 */
  uint8_t symbol_condition;  /* byte 27 */
  uint8_t underlying[8];     /* bytes 28 to 35 */
} SymbolMappingMessage;

/* any Symbol Mapping Message at all: every byte one the checker chooses */
static void any_symbol_mapping_message(SymbolMappingMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->feed_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 21; i++) { record->osi_symbol[i] = arbitrary(); }
  record->symbol_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->underlying[i] = arbitrary(); }
}

/* Symbol Mapping Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_symbol_mapping_message(const SymbolMappingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->feed_symbol[i]; }
  for (size_t i = 0; i < 21; i++) { wire[at++] = record->osi_symbol[i]; }
  wire[at++] = record->symbol_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying[i]; }

  return at;
}

/* Symbol Mapping Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_symbol_mapping_message(SymbolMappingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->feed_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 21; i++) { record->osi_symbol[i] = wire[at++]; }
  record->symbol_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->underlying[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Mapping Message is what was written, byte for byte */
static void equal_symbol_mapping_message(const SymbolMappingMessage *read, const SymbolMappingMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->feed_symbol[i] == written->feed_symbol[i]); }
  for (size_t i = 0; i < 21; i++) { assert(read->osi_symbol[i] == written->osi_symbol[i]); }
  assert(read->symbol_condition == written->symbol_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->underlying[i] == written->underlying[i]); }
}

/* Symbol Mapping Message: written and read back, then read and written back */
static void check_symbol_mapping_message(void) {
  SymbolMappingMessage sent;
  SymbolMappingMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_symbol_mapping_message(&sent);
  assert(encode_symbol_mapping_message(&sent, wire, 0) == 36);
  assert(decode_symbol_mapping_message(&got, wire, 0) == 36);
  equal_symbol_mapping_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_mapping_message(&got, wire, 0) == 36);
  assert(encode_symbol_mapping_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 16 bytes ---------------------------------------- */

/* The Trading Status message is used to indicate the current trading status of a FLEX options instrument. */
typedef struct {
  uint8_t time_offset[4];      /* bytes 0 to 3 */
  uint8_t symbol[6];           /* bytes 4 to 9 */
  uint8_t reserved_2[2];       /* bytes 10 to 11 */
  uint8_t trading_status;      /* byte 12 */
  uint8_t reserved_1;          /* byte 13 */
  uint8_t gth_trading_status;  /* byte 14 */
  uint8_t second_reserved_1;   /* byte 15 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->reserved_1 = arbitrary();
  record->gth_trading_status = arbitrary();
  record->second_reserved_1 = arbitrary();
}

/* Trading Status Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->trading_status;
  wire[at++] = record->reserved_1;
  wire[at++] = record->gth_trading_status;
  wire[at++] = record->second_reserved_1;

  return at;
}

/* Trading Status Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->trading_status = wire[at++];
  record->reserved_1 = wire[at++];
  record->gth_trading_status = wire[at++];
  record->second_reserved_1 = wire[at++];

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->trading_status == written->trading_status);
  assert(read->reserved_1 == written->reserved_1);
  assert(read->gth_trading_status == written->gth_trading_status);
  assert(read->second_reserved_1 == written->second_reserved_1);
}

/* Trading Status Message: written and read back, then read and written back */
static void check_trading_status_message(void) {
  TradingStatusMessage sent;
  TradingStatusMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_trading_status_message(&sent);
  assert(encode_trading_status_message(&sent, wire, 0) == 16);
  assert(decode_trading_status_message(&got, wire, 0) == 16);
  equal_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_message(&got, wire, 0) == 16);
  assert(encode_trading_status_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Session Message: 4 bytes ----------------------------------------- */

/* The End of Session message is sent for each unit when the unit shuts down. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} EndOfSessionMessage;

/* any End Of Session Message at all: every byte one the checker chooses */
static void any_end_of_session_message(EndOfSessionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* End Of Session Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_end_of_session_message(const EndOfSessionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* End Of Session Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_end_of_session_message(EndOfSessionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Session Message is what was written, byte for byte */
static void equal_end_of_session_message(const EndOfSessionMessage *read, const EndOfSessionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* End Of Session Message: written and read back, then read and written back */
static void check_end_of_session_message(void) {
  EndOfSessionMessage sent;
  EndOfSessionMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_end_of_session_message(&sent);
  assert(encode_end_of_session_message(&sent, wire, 0) == 4);
  assert(decode_end_of_session_message(&got, wire, 0) == 4);
  equal_end_of_session_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_session_message(&got, wire, 0) == 4);
  assert(encode_end_of_session_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_time_reference_message();
  check_time_message();
  check_auction_notification_message();
  check_auction_cancel_message();
  check_auction_trade_message();
  check_trade_long_message();
  check_trade_short_message();
  check_dac_trade_message();
  check_trade_break_message();
  check_symbol_mapping_message();
  check_trading_status_message();
  check_end_of_session_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
