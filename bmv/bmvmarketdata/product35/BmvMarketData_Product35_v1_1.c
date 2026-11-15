// bmv/bmvmarketdata/product35/BmvMarketData_Product35_v1_1.c
/*
 * Bolsa Mexicana de Valores Bmv Market Data Product 35
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

/* ---- Indices Components Message: 57 bytes ------------------------------------ */

/* Indices components obtained during the day. */
typedef struct {
  uint8_t date[8];            /* bytes 0 to 7 */
  uint8_t component[2];       /* bytes 8 to 9 */
  uint8_t sector;             /* byte 10 */
  uint8_t type;               /* byte 11 */
  uint8_t issuer[7];          /* bytes 12 to 18 */
  uint8_t series[6];          /* bytes 19 to 24 */
  uint8_t indices_stocks[8];  /* bytes 25 to 32 */
  uint8_t last_price[8];      /* bytes 33 to 40 */
  uint8_t closing_price[8];   /* bytes 41 to 48 */
  uint8_t influence[8];       /* bytes 49 to 56 */
} IndicesComponentsMessage;

/* any Indices Components Message at all: every byte one the checker chooses */
static void any_indices_components_message(IndicesComponentsMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->component[i] = arbitrary(); }
  record->sector = arbitrary();
  record->type = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->series[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indices_stocks[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->influence[i] = arbitrary(); }
}

/* Indices Components Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_indices_components_message(const IndicesComponentsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->component[i]; }
  wire[at++] = record->sector;
  wire[at++] = record->type;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->issuer[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->series[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indices_stocks[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->influence[i]; }

  return at;
}

/* Indices Components Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_indices_components_message(IndicesComponentsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->component[i] = wire[at++]; }
  record->sector = wire[at++];
  record->type = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->series[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indices_stocks[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->influence[i] = wire[at++]; }

  return at;
}

/* what was read of Indices Components Message is what was written, byte for byte */
static void equal_indices_components_message(const IndicesComponentsMessage *read, const IndicesComponentsMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->component[i] == written->component[i]); }
  assert(read->sector == written->sector);
  assert(read->type == written->type);
  for (size_t i = 0; i < 7; i++) { assert(read->issuer[i] == written->issuer[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->series[i] == written->series[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indices_stocks[i] == written->indices_stocks[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->influence[i] == written->influence[i]); }
}

/* Indices Components Message: written and read back, then read and written back */
static void check_indices_components_message(void) {
  IndicesComponentsMessage sent;
  IndicesComponentsMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_indices_components_message(&sent);
  assert(encode_indices_components_message(&sent, wire, 0) == 57);
  assert(decode_indices_components_message(&got, wire, 0) == 57);
  equal_indices_components_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_indices_components_message(&got, wire, 0) == 57);
  assert(encode_indices_components_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_i_n_t_r_a_multicast_header();
  check_message_header();
  check_events_system_message();
  check_indices_components_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
