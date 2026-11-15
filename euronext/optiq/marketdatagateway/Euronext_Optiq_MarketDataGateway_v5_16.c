// euronext/optiq/marketdatagateway/Euronext_Optiq_MarketDataGateway_v5_16.c
/*
 * Euronext Market Data Gateway
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
 *   - a field read in bits
 *   - a Conversion rule
 *   - a block whose stated length holds more than its fields
 *   - a run counted by a field
 *   - a Empty element
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

/* ---- Message Header: 8 bytes ------------------------------------------------- */

/* Optiq Sbe message header — message identifiers and length of message root */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id[2];   /* bytes 2 to 3 */
  uint8_t schema_id[2];     /* bytes 4 to 5 */
  uint8_t version[2];       /* bytes 6 to 7 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Message Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->schema_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Message Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->schema_id[i] == written->schema_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 8);
  assert(decode_message_header(&got, wire, 0) == 8);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 8);
  assert(encode_message_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Day Message: 10 bytes ------------------------------------------ */

/* StartOfDayMessage */
typedef struct {
  uint8_t md_seq_num[8];           /* bytes 0 to 7 */
  uint8_t session_trading_day[2];  /* bytes 8 to 9 */
} StartOfDayMessage;

/* any Start Of Day Message at all: every byte one the checker chooses */
static void any_start_of_day_message(StartOfDayMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_trading_day[i] = arbitrary(); }
}

/* Start Of Day Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_start_of_day_message(const StartOfDayMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->md_seq_num[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_trading_day[i]; }

  return at;
}

/* Start Of Day Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_start_of_day_message(StartOfDayMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_trading_day[i] = wire[at++]; }

  return at;
}

/* what was read of Start Of Day Message is what was written, byte for byte */
static void equal_start_of_day_message(const StartOfDayMessage *read, const StartOfDayMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->md_seq_num[i] == written->md_seq_num[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_trading_day[i] == written->session_trading_day[i]); }
}

/* Start Of Day Message: written and read back, then read and written back */
static void check_start_of_day_message(void) {
  StartOfDayMessage sent;
  StartOfDayMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_start_of_day_message(&sent);
  assert(encode_start_of_day_message(&sent, wire, 0) == 10);
  assert(decode_start_of_day_message(&got, wire, 0) == 10);
  equal_start_of_day_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_day_message(&got, wire, 0) == 10);
  assert(encode_start_of_day_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Day Message: 10 bytes -------------------------------------------- */

/* EndOfDayMessage */
typedef struct {
  uint8_t md_seq_num[8];           /* bytes 0 to 7 */
  uint8_t session_trading_day[2];  /* bytes 8 to 9 */
} EndOfDayMessage;

/* any End Of Day Message at all: every byte one the checker chooses */
static void any_end_of_day_message(EndOfDayMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_trading_day[i] = arbitrary(); }
}

/* End Of Day Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_end_of_day_message(const EndOfDayMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->md_seq_num[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_trading_day[i]; }

  return at;
}

/* End Of Day Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_end_of_day_message(EndOfDayMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_trading_day[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Day Message is what was written, byte for byte */
static void equal_end_of_day_message(const EndOfDayMessage *read, const EndOfDayMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->md_seq_num[i] == written->md_seq_num[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_trading_day[i] == written->session_trading_day[i]); }
}

/* End Of Day Message: written and read back, then read and written back */
static void check_end_of_day_message(void) {
  EndOfDayMessage sent;
  EndOfDayMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_end_of_day_message(&sent);
  assert(encode_end_of_day_message(&sent, wire, 0) == 10);
  assert(decode_end_of_day_message(&got, wire, 0) == 10);
  equal_end_of_day_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_day_message(&got, wire, 0) == 10);
  assert(encode_end_of_day_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Health Status Message: 16 bytes ----------------------------------------- */

/* HealthStatusMessage */
typedef struct {
  uint8_t md_seq_num[8];  /* bytes 0 to 7 */
  uint8_t event_time[8];  /* bytes 8 to 15 */
} HealthStatusMessage;

/* any Health Status Message at all: every byte one the checker chooses */
static void any_health_status_message(HealthStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_time[i] = arbitrary(); }
}

/* Health Status Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_health_status_message(const HealthStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->md_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_time[i]; }

  return at;
}

/* Health Status Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_health_status_message(HealthStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_time[i] = wire[at++]; }

  return at;
}

/* what was read of Health Status Message is what was written, byte for byte */
static void equal_health_status_message(const HealthStatusMessage *read, const HealthStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->md_seq_num[i] == written->md_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_time[i] == written->event_time[i]); }
}

/* Health Status Message: written and read back, then read and written back */
static void check_health_status_message(void) {
  HealthStatusMessage sent;
  HealthStatusMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_health_status_message(&sent);
  assert(encode_health_status_message(&sent, wire, 0) == 16);
  assert(decode_health_status_message(&got, wire, 0) == 16);
  equal_health_status_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_health_status_message(&got, wire, 0) == 16);
  assert(encode_health_status_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Technical Notification Message: 30 bytes -------------------------------- */

/* TechnicalNotificationMessage */
typedef struct {
  uint8_t md_seq_num_optional[8];        /* bytes 0 to 7 */
  uint8_t technical_notification_type;   /* byte 8 */
  uint8_t rebroadcast_indicator;         /* byte 9 */
  uint8_t retransmission_start_time[8];  /* bytes 10 to 17 */
  uint8_t retransmission_end_time[8];    /* bytes 18 to 25 */
  uint8_t symbol_index_optional[4];      /* bytes 26 to 29 */
} TechnicalNotificationMessage;

/* any Technical Notification Message at all: every byte one the checker chooses */
static void any_technical_notification_message(TechnicalNotificationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num_optional[i] = arbitrary(); }
  record->technical_notification_type = arbitrary();
  record->rebroadcast_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->retransmission_start_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->retransmission_end_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index_optional[i] = arbitrary(); }
}

/* Technical Notification Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_technical_notification_message(const TechnicalNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->md_seq_num_optional[i]; }
  wire[at++] = record->technical_notification_type;
  wire[at++] = record->rebroadcast_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->retransmission_start_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->retransmission_end_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index_optional[i]; }

  return at;
}

/* Technical Notification Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_technical_notification_message(TechnicalNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num_optional[i] = wire[at++]; }
  record->technical_notification_type = wire[at++];
  record->rebroadcast_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->retransmission_start_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->retransmission_end_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Technical Notification Message is what was written, byte for byte */
static void equal_technical_notification_message(const TechnicalNotificationMessage *read, const TechnicalNotificationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->md_seq_num_optional[i] == written->md_seq_num_optional[i]); }
  assert(read->technical_notification_type == written->technical_notification_type);
  assert(read->rebroadcast_indicator == written->rebroadcast_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->retransmission_start_time[i] == written->retransmission_start_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->retransmission_end_time[i] == written->retransmission_end_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index_optional[i] == written->symbol_index_optional[i]); }
}

/* Technical Notification Message: written and read back, then read and written back */
static void check_technical_notification_message(void) {
  TechnicalNotificationMessage sent;
  TechnicalNotificationMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_technical_notification_message(&sent);
  assert(encode_technical_notification_message(&sent, wire, 0) == 30);
  assert(decode_technical_notification_message(&got, wire, 0) == 30);
  equal_technical_notification_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_technical_notification_message(&got, wire, 0) == 30);
  assert(encode_technical_notification_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Size Encoding: 2 bytes -------------------------------------------- */

/* groupSizeEncoding */
typedef struct {
  uint8_t block_length_short;  /* byte 0 */
  uint8_t num_in_group;        /* byte 1 */
} GroupSizeEncoding;

/* any Group Size Encoding at all: every byte one the checker chooses */
static void any_group_size_encoding(GroupSizeEncoding *record) {
  record->block_length_short = arbitrary();
  record->num_in_group = arbitrary();
}

/* Group Size Encoding to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_group_size_encoding(const GroupSizeEncoding *record, uint8_t *wire, size_t at) {
  wire[at++] = record->block_length_short;
  wire[at++] = record->num_in_group;

  return at;
}

/* Group Size Encoding off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_group_size_encoding(GroupSizeEncoding *record, const uint8_t *wire, size_t at) {
  record->block_length_short = wire[at++];
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Group Size Encoding is what was written, byte for byte */
static void equal_group_size_encoding(const GroupSizeEncoding *read, const GroupSizeEncoding *written) {
  assert(read->block_length_short == written->block_length_short);
  assert(read->num_in_group == written->num_in_group);
}

/* Group Size Encoding: written and read back, then read and written back */
static void check_group_size_encoding(void) {
  GroupSizeEncoding sent;
  GroupSizeEncoding got;
  uint8_t wire[2];
  uint8_t again[2];

  any_group_size_encoding(&sent);
  assert(encode_group_size_encoding(&sent, wire, 0) == 2);
  assert(decode_group_size_encoding(&got, wire, 0) == 2);
  equal_group_size_encoding(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_group_size_encoding(&got, wire, 0) == 2);
  assert(encode_group_size_encoding(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Real Time Index Message: 50 bytes --------------------------------------- */

/* RealTimeIndexMessage */
typedef struct {
  uint8_t md_seq_num[8];               /* bytes 0 to 7 */
  uint8_t rebroadcast_indicator;       /* byte 8 */
  uint8_t emm;                         /* byte 9 */
  uint8_t event_time[8];               /* bytes 10 to 17 */
  uint8_t symbol_index[4];             /* bytes 18 to 21 */
  uint8_t index_level[8];              /* bytes 22 to 29 */
  uint8_t pctg_of_capitalization[8];   /* bytes 30 to 37 */
  uint8_t prct_varfrom_prev_close[8];  /* bytes 38 to 45 */
  uint8_t num_traded_instruments[2];   /* bytes 46 to 47 */
  uint8_t index_level_type;            /* byte 48 */
  uint8_t index_price_code;            /* byte 49 */
} RealTimeIndexMessage;

/* any Real Time Index Message at all: every byte one the checker chooses */
static void any_real_time_index_message(RealTimeIndexMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num[i] = arbitrary(); }
  record->rebroadcast_indicator = arbitrary();
  record->emm = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->event_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_level[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->pctg_of_capitalization[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->prct_varfrom_prev_close[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->num_traded_instruments[i] = arbitrary(); }
  record->index_level_type = arbitrary();
  record->index_price_code = arbitrary();
}

/* Real Time Index Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_real_time_index_message(const RealTimeIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->md_seq_num[i]; }
  wire[at++] = record->rebroadcast_indicator;
  wire[at++] = record->emm;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_level[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pctg_of_capitalization[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->prct_varfrom_prev_close[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->num_traded_instruments[i]; }
  wire[at++] = record->index_level_type;
  wire[at++] = record->index_price_code;

  return at;
}

/* Real Time Index Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_real_time_index_message(RealTimeIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num[i] = wire[at++]; }
  record->rebroadcast_indicator = wire[at++];
  record->emm = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->event_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_level[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->pctg_of_capitalization[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->prct_varfrom_prev_close[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->num_traded_instruments[i] = wire[at++]; }
  record->index_level_type = wire[at++];
  record->index_price_code = wire[at++];

  return at;
}

/* what was read of Real Time Index Message is what was written, byte for byte */
static void equal_real_time_index_message(const RealTimeIndexMessage *read, const RealTimeIndexMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->md_seq_num[i] == written->md_seq_num[i]); }
  assert(read->rebroadcast_indicator == written->rebroadcast_indicator);
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 8; i++) { assert(read->event_time[i] == written->event_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_level[i] == written->index_level[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->pctg_of_capitalization[i] == written->pctg_of_capitalization[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->prct_varfrom_prev_close[i] == written->prct_varfrom_prev_close[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->num_traded_instruments[i] == written->num_traded_instruments[i]); }
  assert(read->index_level_type == written->index_level_type);
  assert(read->index_price_code == written->index_price_code);
}

/* Real Time Index Message: written and read back, then read and written back */
static void check_real_time_index_message(void) {
  RealTimeIndexMessage sent;
  RealTimeIndexMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_real_time_index_message(&sent);
  assert(encode_real_time_index_message(&sent, wire, 0) == 50);
  assert(decode_real_time_index_message(&got, wire, 0) == 50);
  equal_real_time_index_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_real_time_index_message(&got, wire, 0) == 50);
  assert(encode_real_time_index_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Summary Message: 126 bytes ---------------------------------------- */

/* IndexSummaryMessage */
typedef struct {
  uint8_t md_seq_num[8];                 /* bytes 0 to 7 */
  uint8_t rebroadcast_indicator;         /* byte 8 */
  uint8_t emm;                           /* byte 9 */
  uint8_t event_time[8];                 /* bytes 10 to 17 */
  uint8_t symbol_index[4];               /* bytes 18 to 21 */
  uint8_t opening_level[8];              /* bytes 22 to 29 */
  uint8_t opening_time[8];               /* bytes 30 to 37 */
  uint8_t confirmed_reference_level[8];  /* bytes 38 to 45 */
  uint8_t confirmed_reference_time[8];   /* bytes 46 to 53 */
  uint8_t closing_reference_level[8];    /* bytes 54 to 61 */
  uint8_t closing_reference_time[8];     /* bytes 62 to 69 */
  uint8_t prct_varfrom_prev_close[8];    /* bytes 70 to 77 */
  uint8_t high_level[8];                 /* bytes 78 to 85 */
  uint8_t high_time[8];                  /* bytes 86 to 93 */
  uint8_t low_level[8];                  /* bytes 94 to 101 */
  uint8_t low_time[8];                   /* bytes 102 to 109 */
  uint8_t liquidation_level[8];          /* bytes 110 to 117 */
  uint8_t liquidation_time[8];           /* bytes 118 to 125 */
} IndexSummaryMessage;

/* any Index Summary Message at all: every byte one the checker chooses */
static void any_index_summary_message(IndexSummaryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num[i] = arbitrary(); }
  record->rebroadcast_indicator = arbitrary();
  record->emm = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->event_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_level[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->confirmed_reference_level[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->confirmed_reference_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_reference_level[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_reference_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->prct_varfrom_prev_close[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_level[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_level[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->liquidation_level[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->liquidation_time[i] = arbitrary(); }
}

/* Index Summary Message to the wire: 126 bytes from at, returning where the next byte goes */
static size_t encode_index_summary_message(const IndexSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->md_seq_num[i]; }
  wire[at++] = record->rebroadcast_indicator;
  wire[at++] = record->emm;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_level[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->confirmed_reference_level[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->confirmed_reference_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_reference_level[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_reference_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->prct_varfrom_prev_close[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_level[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_level[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->liquidation_level[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->liquidation_time[i]; }

  return at;
}

/* Index Summary Message off the wire: 126 bytes from at, returning where the next byte lies */
static size_t decode_index_summary_message(IndexSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num[i] = wire[at++]; }
  record->rebroadcast_indicator = wire[at++];
  record->emm = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->event_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_level[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->confirmed_reference_level[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->confirmed_reference_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_reference_level[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_reference_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->prct_varfrom_prev_close[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_level[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_level[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->liquidation_level[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->liquidation_time[i] = wire[at++]; }

  return at;
}

/* what was read of Index Summary Message is what was written, byte for byte */
static void equal_index_summary_message(const IndexSummaryMessage *read, const IndexSummaryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->md_seq_num[i] == written->md_seq_num[i]); }
  assert(read->rebroadcast_indicator == written->rebroadcast_indicator);
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 8; i++) { assert(read->event_time[i] == written->event_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_level[i] == written->opening_level[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_time[i] == written->opening_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->confirmed_reference_level[i] == written->confirmed_reference_level[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->confirmed_reference_time[i] == written->confirmed_reference_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_reference_level[i] == written->closing_reference_level[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_reference_time[i] == written->closing_reference_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->prct_varfrom_prev_close[i] == written->prct_varfrom_prev_close[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_level[i] == written->high_level[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_time[i] == written->high_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_level[i] == written->low_level[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_time[i] == written->low_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->liquidation_level[i] == written->liquidation_level[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->liquidation_time[i] == written->liquidation_time[i]); }
}

/* Index Summary Message: written and read back, then read and written back */
static void check_index_summary_message(void) {
  IndexSummaryMessage sent;
  IndexSummaryMessage got;
  uint8_t wire[126];
  uint8_t again[126];

  any_index_summary_message(&sent);
  assert(encode_index_summary_message(&sent, wire, 0) == 126);
  assert(decode_index_summary_message(&got, wire, 0) == 126);
  equal_index_summary_message(&got, &sent);

  for (size_t i = 0; i < 126; i++) { wire[i] = arbitrary(); }
  assert(decode_index_summary_message(&got, wire, 0) == 126);
  assert(encode_index_summary_message(&got, again, 0) == 126);
  for (size_t i = 0; i < 126; i++) { assert(again[i] == wire[i]); }
}

/* ---- Apa Quotes Message: 105 bytes ------------------------------------------- */

/* APAQuotesMessage */
typedef struct {
  uint8_t md_seq_num_optional[8];       /* bytes 0 to 7 */
  uint8_t rebroadcast_indicator;        /* byte 8 */
  uint8_t mifid_instrument_id_type[4];  /* bytes 9 to 12 */
  uint8_t mifid_instrument_id[12];      /* bytes 13 to 24 */
  uint8_t mic[4];                       /* bytes 25 to 28 */
  uint8_t currency[3];                  /* bytes 29 to 31 */
  uint8_t lei_code[20];                 /* bytes 32 to 51 */
  uint8_t event_time[8];                /* bytes 52 to 59 */
  uint8_t quote_update_type;            /* byte 60 */
  uint8_t mifid_price[20];              /* bytes 61 to 80 */
  uint8_t mifid_quantity[20];           /* bytes 81 to 100 */
  uint8_t apa_origin[4];                /* bytes 101 to 104 */
} ApaQuotesMessage;

/* any Apa Quotes Message at all: every byte one the checker chooses */
static void any_apa_quotes_message(ApaQuotesMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num_optional[i] = arbitrary(); }
  record->rebroadcast_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->mifid_instrument_id_type[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->mifid_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->lei_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_time[i] = arbitrary(); }
  record->quote_update_type = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->mifid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mifid_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->apa_origin[i] = arbitrary(); }
}

/* Apa Quotes Message to the wire: 105 bytes from at, returning where the next byte goes */
static size_t encode_apa_quotes_message(const ApaQuotesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->md_seq_num_optional[i]; }
  wire[at++] = record->rebroadcast_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mifid_instrument_id_type[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->mifid_instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mic[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->lei_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_time[i]; }
  wire[at++] = record->quote_update_type;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mifid_price[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mifid_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->apa_origin[i]; }

  return at;
}

/* Apa Quotes Message off the wire: 105 bytes from at, returning where the next byte lies */
static size_t decode_apa_quotes_message(ApaQuotesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num_optional[i] = wire[at++]; }
  record->rebroadcast_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->mifid_instrument_id_type[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->mifid_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->lei_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_time[i] = wire[at++]; }
  record->quote_update_type = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->mifid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mifid_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->apa_origin[i] = wire[at++]; }

  return at;
}

/* what was read of Apa Quotes Message is what was written, byte for byte */
static void equal_apa_quotes_message(const ApaQuotesMessage *read, const ApaQuotesMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->md_seq_num_optional[i] == written->md_seq_num_optional[i]); }
  assert(read->rebroadcast_indicator == written->rebroadcast_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->mifid_instrument_id_type[i] == written->mifid_instrument_id_type[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->mifid_instrument_id[i] == written->mifid_instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mic[i] == written->mic[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->lei_code[i] == written->lei_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_time[i] == written->event_time[i]); }
  assert(read->quote_update_type == written->quote_update_type);
  for (size_t i = 0; i < 20; i++) { assert(read->mifid_price[i] == written->mifid_price[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mifid_quantity[i] == written->mifid_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->apa_origin[i] == written->apa_origin[i]); }
}

/* Apa Quotes Message: written and read back, then read and written back */
static void check_apa_quotes_message(void) {
  ApaQuotesMessage sent;
  ApaQuotesMessage got;
  uint8_t wire[105];
  uint8_t again[105];

  any_apa_quotes_message(&sent);
  assert(encode_apa_quotes_message(&sent, wire, 0) == 105);
  assert(decode_apa_quotes_message(&got, wire, 0) == 105);
  equal_apa_quotes_message(&got, &sent);

  for (size_t i = 0; i < 105; i++) { wire[i] = arbitrary(); }
  assert(decode_apa_quotes_message(&got, wire, 0) == 105);
  assert(encode_apa_quotes_message(&got, again, 0) == 105);
  for (size_t i = 0; i < 105; i++) { assert(again[i] == wire[i]); }
}

/* ---- Apa Standing Data Message: 217 bytes ------------------------------------ */

/* APAStandingDataMessage */
typedef struct {
  uint8_t md_seq_num_optional[8];       /* bytes 0 to 7 */
  uint8_t rebroadcast_indicator;        /* byte 8 */
  uint8_t mifid_instrument_id_type[4];  /* bytes 9 to 12 */
  uint8_t mifid_instrument_id[12];      /* bytes 13 to 24 */
  uint8_t full_instrument_name[102];    /* bytes 25 to 126 */
  uint8_t cfi_optional[6];              /* bytes 127 to 132 */
  uint8_t notional_currency[3];         /* bytes 133 to 135 */
  uint8_t second_notional_currency[3];  /* bytes 136 to 138 */
  uint8_t price_multiplier[4];          /* bytes 139 to 142 */
  uint8_t price_multiplier_decimals;    /* byte 143 */
  uint8_t underlying_isin_code[12];     /* bytes 144 to 155 */
  uint8_t underlying_index_name[25];    /* bytes 156 to 180 */
  uint8_t underlying_index_term[8];     /* bytes 181 to 188 */
  uint8_t option_type;                  /* byte 189 */
  uint8_t strike_price[8];              /* bytes 190 to 197 */
  uint8_t strike_price_decimals;        /* byte 198 */
  uint8_t exer_style;                   /* byte 199 */
  uint8_t maturity_date_optional[8];    /* bytes 200 to 207 */
  uint8_t expiry_date[8];               /* bytes 208 to 215 */
  uint8_t settlement_method;            /* byte 216 */
} ApaStandingDataMessage;

/* any Apa Standing Data Message at all: every byte one the checker chooses */
static void any_apa_standing_data_message(ApaStandingDataMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num_optional[i] = arbitrary(); }
  record->rebroadcast_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->mifid_instrument_id_type[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->mifid_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 102; i++) { record->full_instrument_name[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cfi_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->second_notional_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_multiplier[i] = arbitrary(); }
  record->price_multiplier_decimals = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->underlying_isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->underlying_index_name[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->underlying_index_term[i] = arbitrary(); }
  record->option_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->strike_price_decimals = arbitrary();
  record->exer_style = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->maturity_date_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expiry_date[i] = arbitrary(); }
  record->settlement_method = arbitrary();
}

/* Apa Standing Data Message to the wire: 217 bytes from at, returning where the next byte goes */
static size_t encode_apa_standing_data_message(const ApaStandingDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->md_seq_num_optional[i]; }
  wire[at++] = record->rebroadcast_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mifid_instrument_id_type[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->mifid_instrument_id[i]; }
  for (size_t i = 0; i < 102; i++) { wire[at++] = record->full_instrument_name[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cfi_optional[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->notional_currency[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->second_notional_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_multiplier[i]; }
  wire[at++] = record->price_multiplier_decimals;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_isin_code[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->underlying_index_name[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying_index_term[i]; }
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->strike_price_decimals;
  wire[at++] = record->exer_style;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_date_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expiry_date[i]; }
  wire[at++] = record->settlement_method;

  return at;
}

/* Apa Standing Data Message off the wire: 217 bytes from at, returning where the next byte lies */
static size_t decode_apa_standing_data_message(ApaStandingDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num_optional[i] = wire[at++]; }
  record->rebroadcast_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->mifid_instrument_id_type[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->mifid_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 102; i++) { record->full_instrument_name[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cfi_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->second_notional_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_multiplier[i] = wire[at++]; }
  record->price_multiplier_decimals = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->underlying_isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->underlying_index_name[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->underlying_index_term[i] = wire[at++]; }
  record->option_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->strike_price_decimals = wire[at++];
  record->exer_style = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->maturity_date_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expiry_date[i] = wire[at++]; }
  record->settlement_method = wire[at++];

  return at;
}

/* what was read of Apa Standing Data Message is what was written, byte for byte */
static void equal_apa_standing_data_message(const ApaStandingDataMessage *read, const ApaStandingDataMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->md_seq_num_optional[i] == written->md_seq_num_optional[i]); }
  assert(read->rebroadcast_indicator == written->rebroadcast_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->mifid_instrument_id_type[i] == written->mifid_instrument_id_type[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->mifid_instrument_id[i] == written->mifid_instrument_id[i]); }
  for (size_t i = 0; i < 102; i++) { assert(read->full_instrument_name[i] == written->full_instrument_name[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cfi_optional[i] == written->cfi_optional[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->notional_currency[i] == written->notional_currency[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->second_notional_currency[i] == written->second_notional_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_multiplier[i] == written->price_multiplier[i]); }
  assert(read->price_multiplier_decimals == written->price_multiplier_decimals);
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_isin_code[i] == written->underlying_isin_code[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->underlying_index_name[i] == written->underlying_index_name[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->underlying_index_term[i] == written->underlying_index_term[i]); }
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->strike_price_decimals == written->strike_price_decimals);
  assert(read->exer_style == written->exer_style);
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_date_optional[i] == written->maturity_date_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expiry_date[i] == written->expiry_date[i]); }
  assert(read->settlement_method == written->settlement_method);
}

/* Apa Standing Data Message: written and read back, then read and written back */
static void check_apa_standing_data_message(void) {
  ApaStandingDataMessage sent;
  ApaStandingDataMessage got;
  uint8_t wire[217];
  uint8_t again[217];

  any_apa_standing_data_message(&sent);
  assert(encode_apa_standing_data_message(&sent, wire, 0) == 217);
  assert(decode_apa_standing_data_message(&got, wire, 0) == 217);
  equal_apa_standing_data_message(&got, &sent);

  for (size_t i = 0; i < 217; i++) { wire[i] = arbitrary(); }
  assert(decode_apa_standing_data_message(&got, wire, 0) == 217);
  assert(encode_apa_standing_data_message(&got, again, 0) == 217);
  for (size_t i = 0; i < 217; i++) { assert(again[i] == wire[i]); }
}

/* ---- Apa Full Trade Information Message: 405 bytes --------------------------- */

/* APAFullTradeInformationMessage */
typedef struct {
  uint8_t md_seq_num[8];                               /* bytes 0 to 7 */
  uint8_t rebroadcast_indicator;                       /* byte 8 */
  uint8_t emm;                                         /* byte 9 */
  uint8_t event_time[8];                               /* bytes 10 to 17 */
  uint8_t trading_date_time[27];                       /* bytes 18 to 44 */
  uint8_t publication_date_time[27];                   /* bytes 45 to 71 */
  uint8_t trade_type;                                  /* byte 72 */
  uint8_t mifid_instrument_id_type_optional[4];        /* bytes 73 to 76 */
  uint8_t mifid_instrument_id_optional[12];            /* bytes 77 to 88 */
  uint8_t mifid_transaction_id[52];                    /* bytes 89 to 140 */
  uint8_t mifid_price_optional[20];                    /* bytes 141 to 160 */
  uint8_t mifid_quantity[20];                          /* bytes 161 to 180 */
  uint8_t mifid_price_notation[4];                     /* bytes 181 to 184 */
  uint8_t mifid_currency[3];                           /* bytes 185 to 187 */
  uint8_t mifid_qty_in_msrmt_unit_notation[25];        /* bytes 188 to 212 */
  uint8_t mifid_quantity_measurement_unit[20];         /* bytes 213 to 232 */
  uint8_t mifid_notional_amount[20];                   /* bytes 233 to 252 */
  uint8_t notional_currency[3];                        /* bytes 253 to 255 */
  uint8_t mifid_clearing_flag[5];                      /* bytes 256 to 260 */
  uint8_t efficient_mmt_market_mechanism;              /* byte 261 */
  uint8_t efficient_mmt_trading_mode;                  /* byte 262 */
  uint8_t efficient_mmt_transaction_category;          /* byte 263 */
  uint8_t efficient_mmt_negotiation_indicator;         /* byte 264 */
  uint8_t efficient_mmt_agency_cross_trade_indicator;  /* byte 265 */
  uint8_t efficient_mmt_modification_indicator;        /* byte 266 */
  uint8_t efficient_mmt_benchmark_indicator;           /* byte 267 */
  uint8_t efficient_mmt_special_dividend_indicator;    /* byte 268 */
  uint8_t efficient_mmt_off_book_automated_indicator;  /* byte 269 */
  uint8_t efficient_mmt_contributionto_price;          /* byte 270 */
  uint8_t efficient_mmt_algorithmic_indicator;         /* byte 271 */
  uint8_t efficient_mmt_publication_mode;              /* byte 272 */
  uint8_t efficient_mmt_post_trade_deferral;           /* byte 273 */
  uint8_t efficient_mmt_duplicative_indicator;         /* byte 274 */
  uint8_t trade_reference[30];                         /* bytes 275 to 304 */
  uint8_t original_report_timestamp[8];                /* bytes 305 to 312 */
  uint8_t price_multiplier[4];                         /* bytes 313 to 316 */
  uint8_t price_multiplier_decimals;                   /* byte 317 */
  uint8_t venue[11];                                   /* bytes 318 to 328 */
  uint8_t mifid_emission_allowance_type[4];            /* bytes 329 to 332 */
  uint8_t long_trade_reference[52];                    /* bytes 333 to 384 */
  uint8_t apa_origin[4];                               /* bytes 385 to 388 */
  uint8_t trade_unique_identifier[16];                 /* bytes 389 to 404 */
} ApaFullTradeInformationMessage;

/* any Apa Full Trade Information Message at all: every byte one the checker chooses */
static void any_apa_full_trade_information_message(ApaFullTradeInformationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num[i] = arbitrary(); }
  record->rebroadcast_indicator = arbitrary();
  record->emm = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->event_time[i] = arbitrary(); }
  for (size_t i = 0; i < 27; i++) { record->trading_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 27; i++) { record->publication_date_time[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->mifid_instrument_id_type_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->mifid_instrument_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 52; i++) { record->mifid_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mifid_price_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mifid_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mifid_price_notation[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->mifid_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->mifid_qty_in_msrmt_unit_notation[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mifid_quantity_measurement_unit[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mifid_notional_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->mifid_clearing_flag[i] = arbitrary(); }
  record->efficient_mmt_market_mechanism = arbitrary();
  record->efficient_mmt_trading_mode = arbitrary();
  record->efficient_mmt_transaction_category = arbitrary();
  record->efficient_mmt_negotiation_indicator = arbitrary();
  record->efficient_mmt_agency_cross_trade_indicator = arbitrary();
  record->efficient_mmt_modification_indicator = arbitrary();
  record->efficient_mmt_benchmark_indicator = arbitrary();
  record->efficient_mmt_special_dividend_indicator = arbitrary();
  record->efficient_mmt_off_book_automated_indicator = arbitrary();
  record->efficient_mmt_contributionto_price = arbitrary();
  record->efficient_mmt_algorithmic_indicator = arbitrary();
  record->efficient_mmt_publication_mode = arbitrary();
  record->efficient_mmt_post_trade_deferral = arbitrary();
  record->efficient_mmt_duplicative_indicator = arbitrary();
  for (size_t i = 0; i < 30; i++) { record->trade_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_report_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_multiplier[i] = arbitrary(); }
  record->price_multiplier_decimals = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->venue[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mifid_emission_allowance_type[i] = arbitrary(); }
  for (size_t i = 0; i < 52; i++) { record->long_trade_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->apa_origin[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->trade_unique_identifier[i] = arbitrary(); }
}

/* Apa Full Trade Information Message to the wire: 405 bytes from at, returning where the next byte goes */
static size_t encode_apa_full_trade_information_message(const ApaFullTradeInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->md_seq_num[i]; }
  wire[at++] = record->rebroadcast_indicator;
  wire[at++] = record->emm;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_time[i]; }
  for (size_t i = 0; i < 27; i++) { wire[at++] = record->trading_date_time[i]; }
  for (size_t i = 0; i < 27; i++) { wire[at++] = record->publication_date_time[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mifid_instrument_id_type_optional[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->mifid_instrument_id_optional[i]; }
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->mifid_transaction_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mifid_price_optional[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mifid_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mifid_price_notation[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->mifid_currency[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->mifid_qty_in_msrmt_unit_notation[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mifid_quantity_measurement_unit[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mifid_notional_amount[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->notional_currency[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->mifid_clearing_flag[i]; }
  wire[at++] = record->efficient_mmt_market_mechanism;
  wire[at++] = record->efficient_mmt_trading_mode;
  wire[at++] = record->efficient_mmt_transaction_category;
  wire[at++] = record->efficient_mmt_negotiation_indicator;
  wire[at++] = record->efficient_mmt_agency_cross_trade_indicator;
  wire[at++] = record->efficient_mmt_modification_indicator;
  wire[at++] = record->efficient_mmt_benchmark_indicator;
  wire[at++] = record->efficient_mmt_special_dividend_indicator;
  wire[at++] = record->efficient_mmt_off_book_automated_indicator;
  wire[at++] = record->efficient_mmt_contributionto_price;
  wire[at++] = record->efficient_mmt_algorithmic_indicator;
  wire[at++] = record->efficient_mmt_publication_mode;
  wire[at++] = record->efficient_mmt_post_trade_deferral;
  wire[at++] = record->efficient_mmt_duplicative_indicator;
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->trade_reference[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_report_timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_multiplier[i]; }
  wire[at++] = record->price_multiplier_decimals;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->venue[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mifid_emission_allowance_type[i]; }
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->long_trade_reference[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->apa_origin[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->trade_unique_identifier[i]; }

  return at;
}

/* Apa Full Trade Information Message off the wire: 405 bytes from at, returning where the next byte lies */
static size_t decode_apa_full_trade_information_message(ApaFullTradeInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num[i] = wire[at++]; }
  record->rebroadcast_indicator = wire[at++];
  record->emm = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->event_time[i] = wire[at++]; }
  for (size_t i = 0; i < 27; i++) { record->trading_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 27; i++) { record->publication_date_time[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->mifid_instrument_id_type_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->mifid_instrument_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 52; i++) { record->mifid_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mifid_price_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mifid_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mifid_price_notation[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->mifid_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->mifid_qty_in_msrmt_unit_notation[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mifid_quantity_measurement_unit[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mifid_notional_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->mifid_clearing_flag[i] = wire[at++]; }
  record->efficient_mmt_market_mechanism = wire[at++];
  record->efficient_mmt_trading_mode = wire[at++];
  record->efficient_mmt_transaction_category = wire[at++];
  record->efficient_mmt_negotiation_indicator = wire[at++];
  record->efficient_mmt_agency_cross_trade_indicator = wire[at++];
  record->efficient_mmt_modification_indicator = wire[at++];
  record->efficient_mmt_benchmark_indicator = wire[at++];
  record->efficient_mmt_special_dividend_indicator = wire[at++];
  record->efficient_mmt_off_book_automated_indicator = wire[at++];
  record->efficient_mmt_contributionto_price = wire[at++];
  record->efficient_mmt_algorithmic_indicator = wire[at++];
  record->efficient_mmt_publication_mode = wire[at++];
  record->efficient_mmt_post_trade_deferral = wire[at++];
  record->efficient_mmt_duplicative_indicator = wire[at++];
  for (size_t i = 0; i < 30; i++) { record->trade_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_report_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_multiplier[i] = wire[at++]; }
  record->price_multiplier_decimals = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->venue[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mifid_emission_allowance_type[i] = wire[at++]; }
  for (size_t i = 0; i < 52; i++) { record->long_trade_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->apa_origin[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->trade_unique_identifier[i] = wire[at++]; }

  return at;
}

/* what was read of Apa Full Trade Information Message is what was written, byte for byte */
static void equal_apa_full_trade_information_message(const ApaFullTradeInformationMessage *read, const ApaFullTradeInformationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->md_seq_num[i] == written->md_seq_num[i]); }
  assert(read->rebroadcast_indicator == written->rebroadcast_indicator);
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 8; i++) { assert(read->event_time[i] == written->event_time[i]); }
  for (size_t i = 0; i < 27; i++) { assert(read->trading_date_time[i] == written->trading_date_time[i]); }
  for (size_t i = 0; i < 27; i++) { assert(read->publication_date_time[i] == written->publication_date_time[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->mifid_instrument_id_type_optional[i] == written->mifid_instrument_id_type_optional[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->mifid_instrument_id_optional[i] == written->mifid_instrument_id_optional[i]); }
  for (size_t i = 0; i < 52; i++) { assert(read->mifid_transaction_id[i] == written->mifid_transaction_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mifid_price_optional[i] == written->mifid_price_optional[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mifid_quantity[i] == written->mifid_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mifid_price_notation[i] == written->mifid_price_notation[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->mifid_currency[i] == written->mifid_currency[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->mifid_qty_in_msrmt_unit_notation[i] == written->mifid_qty_in_msrmt_unit_notation[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mifid_quantity_measurement_unit[i] == written->mifid_quantity_measurement_unit[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mifid_notional_amount[i] == written->mifid_notional_amount[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->notional_currency[i] == written->notional_currency[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->mifid_clearing_flag[i] == written->mifid_clearing_flag[i]); }
  assert(read->efficient_mmt_market_mechanism == written->efficient_mmt_market_mechanism);
  assert(read->efficient_mmt_trading_mode == written->efficient_mmt_trading_mode);
  assert(read->efficient_mmt_transaction_category == written->efficient_mmt_transaction_category);
  assert(read->efficient_mmt_negotiation_indicator == written->efficient_mmt_negotiation_indicator);
  assert(read->efficient_mmt_agency_cross_trade_indicator == written->efficient_mmt_agency_cross_trade_indicator);
  assert(read->efficient_mmt_modification_indicator == written->efficient_mmt_modification_indicator);
  assert(read->efficient_mmt_benchmark_indicator == written->efficient_mmt_benchmark_indicator);
  assert(read->efficient_mmt_special_dividend_indicator == written->efficient_mmt_special_dividend_indicator);
  assert(read->efficient_mmt_off_book_automated_indicator == written->efficient_mmt_off_book_automated_indicator);
  assert(read->efficient_mmt_contributionto_price == written->efficient_mmt_contributionto_price);
  assert(read->efficient_mmt_algorithmic_indicator == written->efficient_mmt_algorithmic_indicator);
  assert(read->efficient_mmt_publication_mode == written->efficient_mmt_publication_mode);
  assert(read->efficient_mmt_post_trade_deferral == written->efficient_mmt_post_trade_deferral);
  assert(read->efficient_mmt_duplicative_indicator == written->efficient_mmt_duplicative_indicator);
  for (size_t i = 0; i < 30; i++) { assert(read->trade_reference[i] == written->trade_reference[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_report_timestamp[i] == written->original_report_timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_multiplier[i] == written->price_multiplier[i]); }
  assert(read->price_multiplier_decimals == written->price_multiplier_decimals);
  for (size_t i = 0; i < 11; i++) { assert(read->venue[i] == written->venue[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mifid_emission_allowance_type[i] == written->mifid_emission_allowance_type[i]); }
  for (size_t i = 0; i < 52; i++) { assert(read->long_trade_reference[i] == written->long_trade_reference[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->apa_origin[i] == written->apa_origin[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->trade_unique_identifier[i] == written->trade_unique_identifier[i]); }
}

/* Apa Full Trade Information Message: written and read back, then read and written back */
static void check_apa_full_trade_information_message(void) {
  ApaFullTradeInformationMessage sent;
  ApaFullTradeInformationMessage got;
  uint8_t wire[405];
  uint8_t again[405];

  any_apa_full_trade_information_message(&sent);
  assert(encode_apa_full_trade_information_message(&sent, wire, 0) == 405);
  assert(decode_apa_full_trade_information_message(&got, wire, 0) == 405);
  equal_apa_full_trade_information_message(&got, &sent);

  for (size_t i = 0; i < 405; i++) { wire[i] = arbitrary(); }
  assert(decode_apa_full_trade_information_message(&got, wire, 0) == 405);
  assert(encode_apa_full_trade_information_message(&got, again, 0) == 405);
  for (size_t i = 0; i < 405; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bf Trade Message: 148 bytes --------------------------------------------- */

/* BFTradeMessage */
typedef struct {
  uint8_t md_seq_num_optional[8];               /* bytes 0 to 7 */
  uint8_t rebroadcast_indicator;                /* byte 8 */
  uint8_t symbol_index[4];                      /* bytes 9 to 12 */
  uint8_t mifid_transaction_id[52];             /* bytes 13 to 64 */
  uint8_t event_time[8];                        /* bytes 65 to 72 */
  uint8_t bid_offer_date_time[8];               /* bytes 73 to 80 */
  uint8_t mmt_modification_indicator[4];        /* bytes 81 to 84 */
  uint8_t price[8];                             /* bytes 85 to 92 */
  uint8_t bid_price[8];                         /* bytes 93 to 100 */
  uint8_t offer_price[8];                       /* bytes 101 to 108 */
  uint8_t quantity[8];                          /* bytes 109 to 116 */
  uint8_t mmt_agency_cross_trade_indicator[4];  /* bytes 117 to 120 */
  uint8_t mmt_benchmark_indicator[4];           /* bytes 121 to 124 */
  uint8_t mmt_special_dividend_indicator[4];    /* bytes 125 to 128 */
  uint8_t mmt_trading_mode;                     /* byte 129 */
  uint8_t mifid_price_notation[4];              /* bytes 130 to 133 */
  uint8_t quantity_notation[3];                 /* bytes 134 to 136 */
  uint8_t notional_amount_traded[8];            /* bytes 137 to 144 */
  uint8_t trading_currency_optional[3];         /* bytes 145 to 147 */
} BfTradeMessage;

/* any Bf Trade Message at all: every byte one the checker chooses */
static void any_bf_trade_message(BfTradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num_optional[i] = arbitrary(); }
  record->rebroadcast_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 52; i++) { record->mifid_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_offer_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_modification_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->offer_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_agency_cross_trade_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_benchmark_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_special_dividend_indicator[i] = arbitrary(); }
  record->mmt_trading_mode = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->mifid_price_notation[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->quantity_notation[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->notional_amount_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trading_currency_optional[i] = arbitrary(); }
}

/* Bf Trade Message to the wire: 148 bytes from at, returning where the next byte goes */
static size_t encode_bf_trade_message(const BfTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->md_seq_num_optional[i]; }
  wire[at++] = record->rebroadcast_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->mifid_transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_offer_date_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_modification_indicator[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->offer_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_agency_cross_trade_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_benchmark_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_special_dividend_indicator[i]; }
  wire[at++] = record->mmt_trading_mode;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mifid_price_notation[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->quantity_notation[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notional_amount_traded[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_currency_optional[i]; }

  return at;
}

/* Bf Trade Message off the wire: 148 bytes from at, returning where the next byte lies */
static size_t decode_bf_trade_message(BfTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num_optional[i] = wire[at++]; }
  record->rebroadcast_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 52; i++) { record->mifid_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_offer_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_modification_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->offer_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_agency_cross_trade_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_benchmark_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_special_dividend_indicator[i] = wire[at++]; }
  record->mmt_trading_mode = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->mifid_price_notation[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->quantity_notation[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->notional_amount_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trading_currency_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Bf Trade Message is what was written, byte for byte */
static void equal_bf_trade_message(const BfTradeMessage *read, const BfTradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->md_seq_num_optional[i] == written->md_seq_num_optional[i]); }
  assert(read->rebroadcast_indicator == written->rebroadcast_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 52; i++) { assert(read->mifid_transaction_id[i] == written->mifid_transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_time[i] == written->event_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_offer_date_time[i] == written->bid_offer_date_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_modification_indicator[i] == written->mmt_modification_indicator[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->offer_price[i] == written->offer_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_agency_cross_trade_indicator[i] == written->mmt_agency_cross_trade_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_benchmark_indicator[i] == written->mmt_benchmark_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_special_dividend_indicator[i] == written->mmt_special_dividend_indicator[i]); }
  assert(read->mmt_trading_mode == written->mmt_trading_mode);
  for (size_t i = 0; i < 4; i++) { assert(read->mifid_price_notation[i] == written->mifid_price_notation[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->quantity_notation[i] == written->quantity_notation[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->notional_amount_traded[i] == written->notional_amount_traded[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trading_currency_optional[i] == written->trading_currency_optional[i]); }
}

/* Bf Trade Message: written and read back, then read and written back */
static void check_bf_trade_message(void) {
  BfTradeMessage sent;
  BfTradeMessage got;
  uint8_t wire[148];
  uint8_t again[148];

  any_bf_trade_message(&sent);
  assert(encode_bf_trade_message(&sent, wire, 0) == 148);
  assert(decode_bf_trade_message(&got, wire, 0) == 148);
  equal_bf_trade_message(&got, &sent);

  for (size_t i = 0; i < 148; i++) { wire[i] = arbitrary(); }
  assert(decode_bf_trade_message(&got, wire, 0) == 148);
  assert(encode_bf_trade_message(&got, again, 0) == 148);
  for (size_t i = 0; i < 148; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bfnav Message: 109 bytes ------------------------------------------------ */

/* BFNAVMessage */
typedef struct {
  uint8_t md_seq_num_optional[8];         /* bytes 0 to 7 */
  uint8_t rebroadcast_indicator;          /* byte 8 */
  uint8_t symbol_index[4];                /* bytes 9 to 12 */
  uint8_t bid_offer_date_time[8];         /* bytes 13 to 20 */
  uint8_t mifid_transaction_id[52];       /* bytes 21 to 72 */
  uint8_t mmt_modification_indicator[4];  /* bytes 73 to 76 */
  uint8_t nav_price[8];                   /* bytes 77 to 84 */
  uint8_t event_time_optional[8];         /* bytes 85 to 92 */
  uint8_t nav_bid_price[8];               /* bytes 93 to 100 */
  uint8_t nav_offer_price[8];             /* bytes 101 to 108 */
} BfnavMessage;

/* any Bfnav Message at all: every byte one the checker chooses */
static void any_bfnav_message(BfnavMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num_optional[i] = arbitrary(); }
  record->rebroadcast_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_offer_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 52; i++) { record->mifid_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mmt_modification_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nav_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_time_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nav_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nav_offer_price[i] = arbitrary(); }
}

/* Bfnav Message to the wire: 109 bytes from at, returning where the next byte goes */
static size_t encode_bfnav_message(const BfnavMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->md_seq_num_optional[i]; }
  wire[at++] = record->rebroadcast_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_offer_date_time[i]; }
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->mifid_transaction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmt_modification_indicator[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nav_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_time_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nav_bid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nav_offer_price[i]; }

  return at;
}

/* Bfnav Message off the wire: 109 bytes from at, returning where the next byte lies */
static size_t decode_bfnav_message(BfnavMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num_optional[i] = wire[at++]; }
  record->rebroadcast_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_offer_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 52; i++) { record->mifid_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mmt_modification_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nav_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_time_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nav_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nav_offer_price[i] = wire[at++]; }

  return at;
}

/* what was read of Bfnav Message is what was written, byte for byte */
static void equal_bfnav_message(const BfnavMessage *read, const BfnavMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->md_seq_num_optional[i] == written->md_seq_num_optional[i]); }
  assert(read->rebroadcast_indicator == written->rebroadcast_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_offer_date_time[i] == written->bid_offer_date_time[i]); }
  for (size_t i = 0; i < 52; i++) { assert(read->mifid_transaction_id[i] == written->mifid_transaction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mmt_modification_indicator[i] == written->mmt_modification_indicator[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nav_price[i] == written->nav_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_time_optional[i] == written->event_time_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nav_bid_price[i] == written->nav_bid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nav_offer_price[i] == written->nav_offer_price[i]); }
}

/* Bfnav Message: written and read back, then read and written back */
static void check_bfnav_message(void) {
  BfnavMessage sent;
  BfnavMessage got;
  uint8_t wire[109];
  uint8_t again[109];

  any_bfnav_message(&sent);
  assert(encode_bfnav_message(&sent, wire, 0) == 109);
  assert(decode_bfnav_message(&got, wire, 0) == 109);
  equal_bfnav_message(&got, &sent);

  for (size_t i = 0; i < 109; i++) { wire[i] = arbitrary(); }
  assert(decode_bfnav_message(&got, wire, 0) == 109);
  assert(encode_bfnav_message(&got, again, 0) == 109);
  for (size_t i = 0; i < 109; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bf Instrument Suspension Message: 22 bytes ------------------------------ */

/* BFInstrumentSuspensionMessage */
typedef struct {
  uint8_t md_seq_num_optional[8];  /* bytes 0 to 7 */
  uint8_t rebroadcast_indicator;   /* byte 8 */
  uint8_t symbol_index[4];         /* bytes 9 to 12 */
  uint8_t event_time[8];           /* bytes 13 to 20 */
  uint8_t security_condition;      /* byte 21 */
} BfInstrumentSuspensionMessage;

/* any Bf Instrument Suspension Message at all: every byte one the checker chooses */
static void any_bf_instrument_suspension_message(BfInstrumentSuspensionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num_optional[i] = arbitrary(); }
  record->rebroadcast_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_time[i] = arbitrary(); }
  record->security_condition = arbitrary();
}

/* Bf Instrument Suspension Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_bf_instrument_suspension_message(const BfInstrumentSuspensionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->md_seq_num_optional[i]; }
  wire[at++] = record->rebroadcast_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_time[i]; }
  wire[at++] = record->security_condition;

  return at;
}

/* Bf Instrument Suspension Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_bf_instrument_suspension_message(BfInstrumentSuspensionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->md_seq_num_optional[i] = wire[at++]; }
  record->rebroadcast_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_time[i] = wire[at++]; }
  record->security_condition = wire[at++];

  return at;
}

/* what was read of Bf Instrument Suspension Message is what was written, byte for byte */
static void equal_bf_instrument_suspension_message(const BfInstrumentSuspensionMessage *read, const BfInstrumentSuspensionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->md_seq_num_optional[i] == written->md_seq_num_optional[i]); }
  assert(read->rebroadcast_indicator == written->rebroadcast_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_time[i] == written->event_time[i]); }
  assert(read->security_condition == written->security_condition);
}

/* Bf Instrument Suspension Message: written and read back, then read and written back */
static void check_bf_instrument_suspension_message(void) {
  BfInstrumentSuspensionMessage sent;
  BfInstrumentSuspensionMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_bf_instrument_suspension_message(&sent);
  assert(encode_bf_instrument_suspension_message(&sent, wire, 0) == 22);
  assert(decode_bf_instrument_suspension_message(&got, wire, 0) == 22);
  equal_bf_instrument_suspension_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_bf_instrument_suspension_message(&got, wire, 0) == 22);
  assert(encode_bf_instrument_suspension_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Snapshot Message: 16 bytes ------------------------------------- */

/* StartOfSnapshotMessage */
typedef struct {
  uint8_t last_md_seq_num[8];  /* bytes 0 to 7 */
  uint8_t snapshot_time[8];    /* bytes 8 to 15 */
} StartOfSnapshotMessage;

/* any Start Of Snapshot Message at all: every byte one the checker chooses */
static void any_start_of_snapshot_message(StartOfSnapshotMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->last_md_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->snapshot_time[i] = arbitrary(); }
}

/* Start Of Snapshot Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_start_of_snapshot_message(const StartOfSnapshotMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_md_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->snapshot_time[i]; }

  return at;
}

/* Start Of Snapshot Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_start_of_snapshot_message(StartOfSnapshotMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->last_md_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->snapshot_time[i] = wire[at++]; }

  return at;
}

/* what was read of Start Of Snapshot Message is what was written, byte for byte */
static void equal_start_of_snapshot_message(const StartOfSnapshotMessage *read, const StartOfSnapshotMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->last_md_seq_num[i] == written->last_md_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->snapshot_time[i] == written->snapshot_time[i]); }
}

/* Start Of Snapshot Message: written and read back, then read and written back */
static void check_start_of_snapshot_message(void) {
  StartOfSnapshotMessage sent;
  StartOfSnapshotMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_start_of_snapshot_message(&sent);
  assert(encode_start_of_snapshot_message(&sent, wire, 0) == 16);
  assert(decode_start_of_snapshot_message(&got, wire, 0) == 16);
  equal_start_of_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_snapshot_message(&got, wire, 0) == 16);
  assert(encode_start_of_snapshot_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Snapshot Message: 16 bytes --------------------------------------- */

/* EndOfSnapshotMessage */
typedef struct {
  uint8_t last_md_seq_num[8];  /* bytes 0 to 7 */
  uint8_t snapshot_time[8];    /* bytes 8 to 15 */
} EndOfSnapshotMessage;

/* any End Of Snapshot Message at all: every byte one the checker chooses */
static void any_end_of_snapshot_message(EndOfSnapshotMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->last_md_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->snapshot_time[i] = arbitrary(); }
}

/* End Of Snapshot Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_end_of_snapshot_message(const EndOfSnapshotMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_md_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->snapshot_time[i]; }

  return at;
}

/* End Of Snapshot Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_end_of_snapshot_message(EndOfSnapshotMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->last_md_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->snapshot_time[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Snapshot Message is what was written, byte for byte */
static void equal_end_of_snapshot_message(const EndOfSnapshotMessage *read, const EndOfSnapshotMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->last_md_seq_num[i] == written->last_md_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->snapshot_time[i] == written->snapshot_time[i]); }
}

/* End Of Snapshot Message: written and read back, then read and written back */
static void check_end_of_snapshot_message(void) {
  EndOfSnapshotMessage sent;
  EndOfSnapshotMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_end_of_snapshot_message(&sent);
  assert(encode_end_of_snapshot_message(&sent, wire, 0) == 16);
  assert(decode_end_of_snapshot_message(&got, wire, 0) == 16);
  equal_end_of_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_snapshot_message(&got, wire, 0) == 16);
  assert(encode_end_of_snapshot_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_start_of_day_message();
  check_end_of_day_message();
  check_health_status_message();
  check_technical_notification_message();
  check_group_size_encoding();
  check_real_time_index_message();
  check_index_summary_message();
  check_apa_quotes_message();
  check_apa_standing_data_message();
  check_apa_full_trade_information_message();
  check_bf_trade_message();
  check_bfnav_message();
  check_bf_instrument_suspension_message();
  check_start_of_snapshot_message();
  check_end_of_snapshot_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
