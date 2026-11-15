// nasdaq/utp/snapshot/Nasdaq_Utp_Snapshot_v3_0_Server.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Snapshot
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
 *   - a run filling what frames it
 *   - the dispatch that chooses a message by its type
 *   - a field present only on a condition
 *   - a length prefix framing what follows
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

/* ---- Server Tcp Packet Header: 3 bytes --------------------------------------- */

/* Packet header of a packet sent by the server */
typedef struct {
  uint8_t packet_length[2];    /* bytes 0 to 1 */
  uint8_t server_packet_type;  /* byte 2 */
} ServerTcpPacketHeader;

/* any Server Tcp Packet Header at all: every byte one the checker chooses */
static void any_server_tcp_packet_header(ServerTcpPacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  record->server_packet_type = arbitrary();
}

/* Server Tcp Packet Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_server_tcp_packet_header(const ServerTcpPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  wire[at++] = record->server_packet_type;

  return at;
}

/* Server Tcp Packet Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_server_tcp_packet_header(ServerTcpPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  record->server_packet_type = wire[at++];

  return at;
}

/* what was read of Server Tcp Packet Header is what was written, byte for byte */
static void equal_server_tcp_packet_header(const ServerTcpPacketHeader *read, const ServerTcpPacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  assert(read->server_packet_type == written->server_packet_type);
}

/* Server Tcp Packet Header: written and read back, then read and written back */
static void check_server_tcp_packet_header(void) {
  ServerTcpPacketHeader sent;
  ServerTcpPacketHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_server_tcp_packet_header(&sent);
  assert(encode_server_tcp_packet_header(&sent, wire, 0) == 3);
  assert(decode_server_tcp_packet_header(&got, wire, 0) == 3);
  equal_server_tcp_packet_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_server_tcp_packet_header(&got, wire, 0) == 3);
  assert(encode_server_tcp_packet_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 2 bytes ------------------------------------------------- */

/* UTP Snap-Shot message header — fixed Version + Message Category prefix */
typedef struct {
  uint8_t version;           /* byte 0 */
  uint8_t message_category;  /* byte 1 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->version = arbitrary();
  record->message_category = arbitrary();
}

/* Message Header to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->version;
  wire[at++] = record->message_category;

  return at;
}

/* Message Header off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->version = wire[at++];
  record->message_category = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->version == written->version);
  assert(read->message_category == written->message_category);
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

/* ---- Issue Symbol Directory Message: 87 bytes -------------------------------- */

/* Issue Symbol Directory Message providing reference data for NASDAQ-listed securities. To be retired in Q1 2027 in favor of the Enhanced Issue Symbol Directory Message (Type F). */
typedef struct {
  uint8_t market_center_originator;        /* byte 0 */
  uint8_t sub_market_center_id;            /* byte 1 */
  uint8_t sip_timestamp[8];                /* bytes 2 to 9 */
  uint8_t timestamp_1[8];                  /* bytes 10 to 17 */
  uint8_t participant_token[8];            /* bytes 18 to 25 */
  uint8_t symbol[11];                      /* bytes 26 to 36 */
  uint8_t old_symbol[11];                  /* bytes 37 to 47 */
  uint8_t issue_name[30];                  /* bytes 48 to 77 */
  uint8_t issue_type;                      /* byte 78 */
  uint8_t issue_subtype[2];                /* bytes 79 to 80 */
  uint8_t market_tier;                     /* byte 81 */
  uint8_t authenticity;                    /* byte 82 */
  uint8_t short_sale_threshold_indicator;  /* byte 83 */
  uint8_t round_lot_size[2];               /* bytes 84 to 85 */
  uint8_t financial_status_indicator;      /* byte 86 */
} IssueSymbolDirectoryMessage;

/* any Issue Symbol Directory Message at all: every byte one the checker chooses */
static void any_issue_symbol_directory_message(IssueSymbolDirectoryMessage *record) {
  record->market_center_originator = arbitrary();
  record->sub_market_center_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->old_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->issue_name[i] = arbitrary(); }
  record->issue_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->issue_subtype[i] = arbitrary(); }
  record->market_tier = arbitrary();
  record->authenticity = arbitrary();
  record->short_sale_threshold_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->round_lot_size[i] = arbitrary(); }
  record->financial_status_indicator = arbitrary();
}

/* Issue Symbol Directory Message to the wire: 87 bytes from at, returning where the next byte goes */
static size_t encode_issue_symbol_directory_message(const IssueSymbolDirectoryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_originator;
  wire[at++] = record->sub_market_center_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->old_symbol[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->issue_name[i]; }
  wire[at++] = record->issue_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->issue_subtype[i]; }
  wire[at++] = record->market_tier;
  wire[at++] = record->authenticity;
  wire[at++] = record->short_sale_threshold_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->round_lot_size[i]; }
  wire[at++] = record->financial_status_indicator;

  return at;
}

/* Issue Symbol Directory Message off the wire: 87 bytes from at, returning where the next byte lies */
static size_t decode_issue_symbol_directory_message(IssueSymbolDirectoryMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_originator = wire[at++];
  record->sub_market_center_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->old_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->issue_name[i] = wire[at++]; }
  record->issue_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->issue_subtype[i] = wire[at++]; }
  record->market_tier = wire[at++];
  record->authenticity = wire[at++];
  record->short_sale_threshold_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->round_lot_size[i] = wire[at++]; }
  record->financial_status_indicator = wire[at++];

  return at;
}

/* what was read of Issue Symbol Directory Message is what was written, byte for byte */
static void equal_issue_symbol_directory_message(const IssueSymbolDirectoryMessage *read, const IssueSymbolDirectoryMessage *written) {
  assert(read->market_center_originator == written->market_center_originator);
  assert(read->sub_market_center_id == written->sub_market_center_id);
  for (size_t i = 0; i < 8; i++) { assert(read->sip_timestamp[i] == written->sip_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_token[i] == written->participant_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->old_symbol[i] == written->old_symbol[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->issue_name[i] == written->issue_name[i]); }
  assert(read->issue_type == written->issue_type);
  for (size_t i = 0; i < 2; i++) { assert(read->issue_subtype[i] == written->issue_subtype[i]); }
  assert(read->market_tier == written->market_tier);
  assert(read->authenticity == written->authenticity);
  assert(read->short_sale_threshold_indicator == written->short_sale_threshold_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->round_lot_size[i] == written->round_lot_size[i]); }
  assert(read->financial_status_indicator == written->financial_status_indicator);
}

/* Issue Symbol Directory Message: written and read back, then read and written back */
static void check_issue_symbol_directory_message(void) {
  IssueSymbolDirectoryMessage sent;
  IssueSymbolDirectoryMessage got;
  uint8_t wire[87];
  uint8_t again[87];

  any_issue_symbol_directory_message(&sent);
  assert(encode_issue_symbol_directory_message(&sent, wire, 0) == 87);
  assert(decode_issue_symbol_directory_message(&got, wire, 0) == 87);
  equal_issue_symbol_directory_message(&got, &sent);

  for (size_t i = 0; i < 87; i++) { wire[i] = arbitrary(); }
  assert(decode_issue_symbol_directory_message(&got, wire, 0) == 87);
  assert(encode_issue_symbol_directory_message(&got, again, 0) == 87);
  for (size_t i = 0; i < 87; i++) { assert(again[i] == wire[i]); }
}

/* ---- Enhanced Issue Symbol Directory Message: 114 bytes ---------------------- */

/* Enhanced Issue Symbol Directory Message — introduced in v3.0 alongside the existing Issue Symbol Directory Message (Type B) to support the SEC MPI Tick Rule (Nov 2026) and Extended Operational Hours (Dec 6, 2026). Adds ETP/IPO/MPI/Trading-State/Halt-Reason/Reg-SHO fields and two RESERVED prior-close prices. */
typedef struct {
  uint8_t market_center_originator;                          /* byte 0 */
  uint8_t sub_market_center_id;                              /* byte 1 */
  uint8_t sip_timestamp[8];                                  /* bytes 2 to 9 */
  uint8_t timestamp_1[8];                                    /* bytes 10 to 17 */
  uint8_t participant_token[8];                              /* bytes 18 to 25 */
  uint8_t symbol[11];                                        /* bytes 26 to 36 */
  uint8_t old_symbol[11];                                    /* bytes 37 to 47 */
  uint8_t issue_name[30];                                    /* bytes 48 to 77 */
  uint8_t issue_type;                                        /* byte 78 */
  uint8_t issue_subtype[2];                                  /* bytes 79 to 80 */
  uint8_t market_tier;                                       /* byte 81 */
  uint8_t authenticity;                                      /* byte 82 */
  uint8_t short_sale_threshold_indicator;                    /* byte 83 */
  uint8_t round_lot_size[2];                                 /* bytes 84 to 85 */
  uint8_t financial_status_indicator;                        /* byte 86 */
  uint8_t etp_indicator;                                     /* byte 87 */
  uint8_t new_issue_indicator;                               /* byte 88 */
  uint8_t mpi_tick;                                          /* byte 89 */
  uint8_t trading_state;                                     /* byte 90 */
  uint8_t halt_reason[6];                                    /* bytes 91 to 96 */
  uint8_t reg_sho_action;                                    /* byte 97 */
  uint8_t consolidated_prior_day_close_price[8];             /* bytes 98 to 105 */
  uint8_t listing_market_official_prior_day_close_price[8];  /* bytes 106 to 113 */
} EnhancedIssueSymbolDirectoryMessage;

/* any Enhanced Issue Symbol Directory Message at all: every byte one the checker chooses */
static void any_enhanced_issue_symbol_directory_message(EnhancedIssueSymbolDirectoryMessage *record) {
  record->market_center_originator = arbitrary();
  record->sub_market_center_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->old_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->issue_name[i] = arbitrary(); }
  record->issue_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->issue_subtype[i] = arbitrary(); }
  record->market_tier = arbitrary();
  record->authenticity = arbitrary();
  record->short_sale_threshold_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->round_lot_size[i] = arbitrary(); }
  record->financial_status_indicator = arbitrary();
  record->etp_indicator = arbitrary();
  record->new_issue_indicator = arbitrary();
  record->mpi_tick = arbitrary();
  record->trading_state = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->halt_reason[i] = arbitrary(); }
  record->reg_sho_action = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->consolidated_prior_day_close_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->listing_market_official_prior_day_close_price[i] = arbitrary(); }
}

/* Enhanced Issue Symbol Directory Message to the wire: 114 bytes from at, returning where the next byte goes */
static size_t encode_enhanced_issue_symbol_directory_message(const EnhancedIssueSymbolDirectoryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_originator;
  wire[at++] = record->sub_market_center_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->old_symbol[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->issue_name[i]; }
  wire[at++] = record->issue_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->issue_subtype[i]; }
  wire[at++] = record->market_tier;
  wire[at++] = record->authenticity;
  wire[at++] = record->short_sale_threshold_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->round_lot_size[i]; }
  wire[at++] = record->financial_status_indicator;
  wire[at++] = record->etp_indicator;
  wire[at++] = record->new_issue_indicator;
  wire[at++] = record->mpi_tick;
  wire[at++] = record->trading_state;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->halt_reason[i]; }
  wire[at++] = record->reg_sho_action;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_prior_day_close_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->listing_market_official_prior_day_close_price[i]; }

  return at;
}

/* Enhanced Issue Symbol Directory Message off the wire: 114 bytes from at, returning where the next byte lies */
static size_t decode_enhanced_issue_symbol_directory_message(EnhancedIssueSymbolDirectoryMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_originator = wire[at++];
  record->sub_market_center_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->old_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->issue_name[i] = wire[at++]; }
  record->issue_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->issue_subtype[i] = wire[at++]; }
  record->market_tier = wire[at++];
  record->authenticity = wire[at++];
  record->short_sale_threshold_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->round_lot_size[i] = wire[at++]; }
  record->financial_status_indicator = wire[at++];
  record->etp_indicator = wire[at++];
  record->new_issue_indicator = wire[at++];
  record->mpi_tick = wire[at++];
  record->trading_state = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->halt_reason[i] = wire[at++]; }
  record->reg_sho_action = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->consolidated_prior_day_close_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->listing_market_official_prior_day_close_price[i] = wire[at++]; }

  return at;
}

/* what was read of Enhanced Issue Symbol Directory Message is what was written, byte for byte */
static void equal_enhanced_issue_symbol_directory_message(const EnhancedIssueSymbolDirectoryMessage *read, const EnhancedIssueSymbolDirectoryMessage *written) {
  assert(read->market_center_originator == written->market_center_originator);
  assert(read->sub_market_center_id == written->sub_market_center_id);
  for (size_t i = 0; i < 8; i++) { assert(read->sip_timestamp[i] == written->sip_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_token[i] == written->participant_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->old_symbol[i] == written->old_symbol[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->issue_name[i] == written->issue_name[i]); }
  assert(read->issue_type == written->issue_type);
  for (size_t i = 0; i < 2; i++) { assert(read->issue_subtype[i] == written->issue_subtype[i]); }
  assert(read->market_tier == written->market_tier);
  assert(read->authenticity == written->authenticity);
  assert(read->short_sale_threshold_indicator == written->short_sale_threshold_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->round_lot_size[i] == written->round_lot_size[i]); }
  assert(read->financial_status_indicator == written->financial_status_indicator);
  assert(read->etp_indicator == written->etp_indicator);
  assert(read->new_issue_indicator == written->new_issue_indicator);
  assert(read->mpi_tick == written->mpi_tick);
  assert(read->trading_state == written->trading_state);
  for (size_t i = 0; i < 6; i++) { assert(read->halt_reason[i] == written->halt_reason[i]); }
  assert(read->reg_sho_action == written->reg_sho_action);
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_prior_day_close_price[i] == written->consolidated_prior_day_close_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->listing_market_official_prior_day_close_price[i] == written->listing_market_official_prior_day_close_price[i]); }
}

/* Enhanced Issue Symbol Directory Message: written and read back, then read and written back */
static void check_enhanced_issue_symbol_directory_message(void) {
  EnhancedIssueSymbolDirectoryMessage sent;
  EnhancedIssueSymbolDirectoryMessage got;
  uint8_t wire[114];
  uint8_t again[114];

  any_enhanced_issue_symbol_directory_message(&sent);
  assert(encode_enhanced_issue_symbol_directory_message(&sent, wire, 0) == 114);
  assert(decode_enhanced_issue_symbol_directory_message(&got, wire, 0) == 114);
  equal_enhanced_issue_symbol_directory_message(&got, &sent);

  for (size_t i = 0; i < 114; i++) { wire[i] = arbitrary(); }
  assert(decode_enhanced_issue_symbol_directory_message(&got, wire, 0) == 114);
  assert(encode_enhanced_issue_symbol_directory_message(&got, again, 0) == 114);
  for (size_t i = 0; i < 114; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reg Sho Short Sale Price Test Restricted Indicator Message: 38 bytes ---- */

/* Reg SHO Restriction Indicator Message indicating the Rule 201 status for NASDAQ-listed securities. Snap-Shot sends a full spin of all active securities reflecting the current Reg SHO Action. */
typedef struct {
  uint8_t market_center_originator;  /* byte 0 */
  uint8_t sub_market_center_id;      /* byte 1 */
  uint8_t sip_timestamp[8];          /* bytes 2 to 9 */
  uint8_t timestamp_1[8];            /* bytes 10 to 17 */
  uint8_t participant_token[8];      /* bytes 18 to 25 */
  uint8_t symbol[11];                /* bytes 26 to 36 */
  uint8_t reg_sho_action;            /* byte 37 */
} RegShoShortSalePriceTestRestrictedIndicatorMessage;

/* any Reg Sho Short Sale Price Test Restricted Indicator Message at all: every byte one the checker chooses */
static void any_reg_sho_short_sale_price_test_restricted_indicator_message(RegShoShortSalePriceTestRestrictedIndicatorMessage *record) {
  record->market_center_originator = arbitrary();
  record->sub_market_center_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = arbitrary(); }
  record->reg_sho_action = arbitrary();
}

/* Reg Sho Short Sale Price Test Restricted Indicator Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_reg_sho_short_sale_price_test_restricted_indicator_message(const RegShoShortSalePriceTestRestrictedIndicatorMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_originator;
  wire[at++] = record->sub_market_center_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->reg_sho_action;

  return at;
}

/* Reg Sho Short Sale Price Test Restricted Indicator Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_reg_sho_short_sale_price_test_restricted_indicator_message(RegShoShortSalePriceTestRestrictedIndicatorMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_originator = wire[at++];
  record->sub_market_center_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = wire[at++]; }
  record->reg_sho_action = wire[at++];

  return at;
}

/* what was read of Reg Sho Short Sale Price Test Restricted Indicator Message is what was written, byte for byte */
static void equal_reg_sho_short_sale_price_test_restricted_indicator_message(const RegShoShortSalePriceTestRestrictedIndicatorMessage *read, const RegShoShortSalePriceTestRestrictedIndicatorMessage *written) {
  assert(read->market_center_originator == written->market_center_originator);
  assert(read->sub_market_center_id == written->sub_market_center_id);
  for (size_t i = 0; i < 8; i++) { assert(read->sip_timestamp[i] == written->sip_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_token[i] == written->participant_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->reg_sho_action == written->reg_sho_action);
}

/* Reg Sho Short Sale Price Test Restricted Indicator Message: written and read back, then read and written back */
static void check_reg_sho_short_sale_price_test_restricted_indicator_message(void) {
  RegShoShortSalePriceTestRestrictedIndicatorMessage sent;
  RegShoShortSalePriceTestRestrictedIndicatorMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_reg_sho_short_sale_price_test_restricted_indicator_message(&sent);
  assert(encode_reg_sho_short_sale_price_test_restricted_indicator_message(&sent, wire, 0) == 38);
  assert(decode_reg_sho_short_sale_price_test_restricted_indicator_message(&got, wire, 0) == 38);
  equal_reg_sho_short_sale_price_test_restricted_indicator_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_reg_sho_short_sale_price_test_restricted_indicator_message(&got, wire, 0) == 38);
  assert(encode_reg_sho_short_sale_price_test_restricted_indicator_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cross Sro Trading Action Message: 56 bytes ------------------------------ */

/* Cross SRO Trading Action message. In Snap-Shot, sent only for NASDAQ-listed issues currently halted, in a Quote Resumption, or in a LULD pause. Absence implies the issue is eligible for normal quoting and trading. */
typedef struct {
  uint8_t market_center_originator;           /* byte 0 */
  uint8_t sub_market_center_id;               /* byte 1 */
  uint8_t sip_timestamp[8];                   /* bytes 2 to 9 */
  uint8_t timestamp_1[8];                     /* bytes 10 to 17 */
  uint8_t participant_token[8];               /* bytes 18 to 25 */
  uint8_t symbol[11];                         /* bytes 26 to 36 */
  uint8_t trading_action_code;                /* byte 37 */
  uint8_t trading_action_sequence_number[4];  /* bytes 38 to 41 */
  uint8_t action_time[8];                     /* bytes 42 to 49 */
  uint8_t reason_for_the_trading_action[6];   /* bytes 50 to 55 */
} CrossSroTradingActionMessage;

/* any Cross Sro Trading Action Message at all: every byte one the checker chooses */
static void any_cross_sro_trading_action_message(CrossSroTradingActionMessage *record) {
  record->market_center_originator = arbitrary();
  record->sub_market_center_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = arbitrary(); }
  record->trading_action_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trading_action_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->action_time[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reason_for_the_trading_action[i] = arbitrary(); }
}

/* Cross Sro Trading Action Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_cross_sro_trading_action_message(const CrossSroTradingActionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_originator;
  wire[at++] = record->sub_market_center_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->trading_action_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_action_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->action_time[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reason_for_the_trading_action[i]; }

  return at;
}

/* Cross Sro Trading Action Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_cross_sro_trading_action_message(CrossSroTradingActionMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_originator = wire[at++];
  record->sub_market_center_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = wire[at++]; }
  record->trading_action_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trading_action_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->action_time[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reason_for_the_trading_action[i] = wire[at++]; }

  return at;
}

/* what was read of Cross Sro Trading Action Message is what was written, byte for byte */
static void equal_cross_sro_trading_action_message(const CrossSroTradingActionMessage *read, const CrossSroTradingActionMessage *written) {
  assert(read->market_center_originator == written->market_center_originator);
  assert(read->sub_market_center_id == written->sub_market_center_id);
  for (size_t i = 0; i < 8; i++) { assert(read->sip_timestamp[i] == written->sip_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_token[i] == written->participant_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->trading_action_code == written->trading_action_code);
  for (size_t i = 0; i < 4; i++) { assert(read->trading_action_sequence_number[i] == written->trading_action_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->action_time[i] == written->action_time[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reason_for_the_trading_action[i] == written->reason_for_the_trading_action[i]); }
}

/* Cross Sro Trading Action Message: written and read back, then read and written back */
static void check_cross_sro_trading_action_message(void) {
  CrossSroTradingActionMessage sent;
  CrossSroTradingActionMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_cross_sro_trading_action_message(&sent);
  assert(encode_cross_sro_trading_action_message(&sent, wire, 0) == 56);
  assert(decode_cross_sro_trading_action_message(&got, wire, 0) == 56);
  equal_cross_sro_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_cross_sro_trading_action_message(&got, wire, 0) == 56);
  assert(encode_cross_sro_trading_action_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Center Trading Action Message: 47 bytes -------------------------- */

/* Market Center Trading Action message — sent when a UTP participant invokes or releases a market center-specific trading halt for a NASDAQ-listed security. Other participants may continue to quote and trade. */
typedef struct {
  uint8_t market_center_originator;  /* byte 0 */
  uint8_t sub_market_center_id;      /* byte 1 */
  uint8_t sip_timestamp[8];          /* bytes 2 to 9 */
  uint8_t timestamp_1[8];            /* bytes 10 to 17 */
  uint8_t participant_token[8];      /* bytes 18 to 25 */
  uint8_t symbol[11];                /* bytes 26 to 36 */
  uint8_t trading_action_code;       /* byte 37 */
  uint8_t action_time[8];            /* bytes 38 to 45 */
  uint8_t market_center_identifier;  /* byte 46 */
} MarketCenterTradingActionMessage;

/* any Market Center Trading Action Message at all: every byte one the checker chooses */
static void any_market_center_trading_action_message(MarketCenterTradingActionMessage *record) {
  record->market_center_originator = arbitrary();
  record->sub_market_center_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = arbitrary(); }
  record->trading_action_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->action_time[i] = arbitrary(); }
  record->market_center_identifier = arbitrary();
}

/* Market Center Trading Action Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_market_center_trading_action_message(const MarketCenterTradingActionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_originator;
  wire[at++] = record->sub_market_center_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->trading_action_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->action_time[i]; }
  wire[at++] = record->market_center_identifier;

  return at;
}

/* Market Center Trading Action Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_market_center_trading_action_message(MarketCenterTradingActionMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_originator = wire[at++];
  record->sub_market_center_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = wire[at++]; }
  record->trading_action_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->action_time[i] = wire[at++]; }
  record->market_center_identifier = wire[at++];

  return at;
}

/* what was read of Market Center Trading Action Message is what was written, byte for byte */
static void equal_market_center_trading_action_message(const MarketCenterTradingActionMessage *read, const MarketCenterTradingActionMessage *written) {
  assert(read->market_center_originator == written->market_center_originator);
  assert(read->sub_market_center_id == written->sub_market_center_id);
  for (size_t i = 0; i < 8; i++) { assert(read->sip_timestamp[i] == written->sip_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_token[i] == written->participant_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->trading_action_code == written->trading_action_code);
  for (size_t i = 0; i < 8; i++) { assert(read->action_time[i] == written->action_time[i]); }
  assert(read->market_center_identifier == written->market_center_identifier);
}

/* Market Center Trading Action Message: written and read back, then read and written back */
static void check_market_center_trading_action_message(void) {
  MarketCenterTradingActionMessage sent;
  MarketCenterTradingActionMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_market_center_trading_action_message(&sent);
  assert(encode_market_center_trading_action_message(&sent, wire, 0) == 47);
  assert(decode_market_center_trading_action_message(&got, wire, 0) == 47);
  equal_market_center_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_market_center_trading_action_message(&got, wire, 0) == 47);
  assert(encode_market_center_trading_action_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Wide Circuit Breaker Decline Level Message: 50 bytes ------------- */

/* MWCB Decline Message. Communicates the daily MWCB breach points (Levels 1/2/3) set based on the prior day's closing value of the S&P 500 index. May be re-sent if levels are reset due to erroneous activity; participants should use the most recently disseminated values. */
typedef struct {
  uint8_t market_center_originator;  /* byte 0 */
  uint8_t sub_market_center_id;      /* byte 1 */
  uint8_t sip_timestamp[8];          /* bytes 2 to 9 */
  uint8_t timestamp_1[8];            /* bytes 10 to 17 */
  uint8_t participant_token[8];      /* bytes 18 to 25 */
  uint8_t mwcb_level_1[8];           /* bytes 26 to 33 */
  uint8_t mwcb_level_2[8];           /* bytes 34 to 41 */
  uint8_t mwcb_level_3[8];           /* bytes 42 to 49 */
} MarketWideCircuitBreakerDeclineLevelMessage;

/* any Market Wide Circuit Breaker Decline Level Message at all: every byte one the checker chooses */
static void any_market_wide_circuit_breaker_decline_level_message(MarketWideCircuitBreakerDeclineLevelMessage *record) {
  record->market_center_originator = arbitrary();
  record->sub_market_center_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_3[i] = arbitrary(); }
}

/* Market Wide Circuit Breaker Decline Level Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_market_wide_circuit_breaker_decline_level_message(const MarketWideCircuitBreakerDeclineLevelMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_originator;
  wire[at++] = record->sub_market_center_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mwcb_level_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mwcb_level_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mwcb_level_3[i]; }

  return at;
}

/* Market Wide Circuit Breaker Decline Level Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_market_wide_circuit_breaker_decline_level_message(MarketWideCircuitBreakerDeclineLevelMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_originator = wire[at++];
  record->sub_market_center_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_3[i] = wire[at++]; }

  return at;
}

/* what was read of Market Wide Circuit Breaker Decline Level Message is what was written, byte for byte */
static void equal_market_wide_circuit_breaker_decline_level_message(const MarketWideCircuitBreakerDeclineLevelMessage *read, const MarketWideCircuitBreakerDeclineLevelMessage *written) {
  assert(read->market_center_originator == written->market_center_originator);
  assert(read->sub_market_center_id == written->sub_market_center_id);
  for (size_t i = 0; i < 8; i++) { assert(read->sip_timestamp[i] == written->sip_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_token[i] == written->participant_token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mwcb_level_1[i] == written->mwcb_level_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mwcb_level_2[i] == written->mwcb_level_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mwcb_level_3[i] == written->mwcb_level_3[i]); }
}

/* Market Wide Circuit Breaker Decline Level Message: written and read back, then read and written back */
static void check_market_wide_circuit_breaker_decline_level_message(void) {
  MarketWideCircuitBreakerDeclineLevelMessage sent;
  MarketWideCircuitBreakerDeclineLevelMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_market_wide_circuit_breaker_decline_level_message(&sent);
  assert(encode_market_wide_circuit_breaker_decline_level_message(&sent, wire, 0) == 50);
  assert(decode_market_wide_circuit_breaker_decline_level_message(&got, wire, 0) == 50);
  equal_market_wide_circuit_breaker_decline_level_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_market_wide_circuit_breaker_decline_level_message(&got, wire, 0) == 50);
  assert(encode_market_wide_circuit_breaker_decline_level_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Limit Up Limit Down Price Band Message: 62 bytes ------------------------ */

/* Limit Up – Limit Down Price Band Message. Reflects the current LULD band for LULD-eligible securities. Designed to prevent trades outside specified Upper and Lower Limit Price Bands. */
typedef struct {
  uint8_t market_center_originator;           /* byte 0 */
  uint8_t sub_market_center_id;               /* byte 1 */
  uint8_t sip_timestamp[8];                   /* bytes 2 to 9 */
  uint8_t timestamp_1[8];                     /* bytes 10 to 17 */
  uint8_t participant_token[8];               /* bytes 18 to 25 */
  uint8_t symbol[11];                         /* bytes 26 to 36 */
  uint8_t luld_price_band_indicator;          /* byte 37 */
  uint8_t luld_price_band_effective_time[8];  /* bytes 38 to 45 */
  uint8_t limit_down_price[8];                /* bytes 46 to 53 */
  uint8_t limit_up_price[8];                  /* bytes 54 to 61 */
} LimitUpLimitDownPriceBandMessage;

/* any Limit Up Limit Down Price Band Message at all: every byte one the checker chooses */
static void any_limit_up_limit_down_price_band_message(LimitUpLimitDownPriceBandMessage *record) {
  record->market_center_originator = arbitrary();
  record->sub_market_center_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = arbitrary(); }
  record->luld_price_band_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->luld_price_band_effective_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->limit_down_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->limit_up_price[i] = arbitrary(); }
}

/* Limit Up Limit Down Price Band Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_limit_up_limit_down_price_band_message(const LimitUpLimitDownPriceBandMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_originator;
  wire[at++] = record->sub_market_center_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->luld_price_band_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->luld_price_band_effective_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->limit_down_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->limit_up_price[i]; }

  return at;
}

/* Limit Up Limit Down Price Band Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_limit_up_limit_down_price_band_message(LimitUpLimitDownPriceBandMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_originator = wire[at++];
  record->sub_market_center_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = wire[at++]; }
  record->luld_price_band_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->luld_price_band_effective_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->limit_down_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->limit_up_price[i] = wire[at++]; }

  return at;
}

/* what was read of Limit Up Limit Down Price Band Message is what was written, byte for byte */
static void equal_limit_up_limit_down_price_band_message(const LimitUpLimitDownPriceBandMessage *read, const LimitUpLimitDownPriceBandMessage *written) {
  assert(read->market_center_originator == written->market_center_originator);
  assert(read->sub_market_center_id == written->sub_market_center_id);
  for (size_t i = 0; i < 8; i++) { assert(read->sip_timestamp[i] == written->sip_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_token[i] == written->participant_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->luld_price_band_indicator == written->luld_price_band_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->luld_price_band_effective_time[i] == written->luld_price_band_effective_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->limit_down_price[i] == written->limit_down_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->limit_up_price[i] == written->limit_up_price[i]); }
}

/* Limit Up Limit Down Price Band Message: written and read back, then read and written back */
static void check_limit_up_limit_down_price_band_message(void) {
  LimitUpLimitDownPriceBandMessage sent;
  LimitUpLimitDownPriceBandMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_limit_up_limit_down_price_band_message(&sent);
  assert(encode_limit_up_limit_down_price_band_message(&sent, wire, 0) == 62);
  assert(decode_limit_up_limit_down_price_band_message(&got, wire, 0) == 62);
  equal_limit_up_limit_down_price_band_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_limit_up_limit_down_price_band_message(&got, wire, 0) == 62);
  assert(encode_limit_up_limit_down_price_band_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Collar Message: 66 bytes ---------------------------------------- */

/* Auction Collar Message published by primary markets using an automated reopening after a LULD Trading Pause. Snap-Shot sends only the most recent Auction Collar message per security. */
typedef struct {
  uint8_t market_center_originator;           /* byte 0 */
  uint8_t sub_market_center_id;               /* byte 1 */
  uint8_t sip_timestamp[8];                   /* bytes 2 to 9 */
  uint8_t timestamp_1[8];                     /* bytes 10 to 17 */
  uint8_t participant_token[8];               /* bytes 18 to 25 */
  uint8_t symbol[11];                         /* bytes 26 to 36 */
  uint8_t trading_action_sequence_number[4];  /* bytes 37 to 40 */
  uint8_t collar_reference_price[8];          /* bytes 41 to 48 */
  uint8_t collar_up_price[8];                 /* bytes 49 to 56 */
  uint8_t collar_down_price[8];               /* bytes 57 to 64 */
  uint8_t collar_extension_indicator;         /* byte 65 */
} AuctionCollarMessage;

/* any Auction Collar Message at all: every byte one the checker chooses */
static void any_auction_collar_message(AuctionCollarMessage *record) {
  record->market_center_originator = arbitrary();
  record->sub_market_center_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_action_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->collar_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->collar_up_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->collar_down_price[i] = arbitrary(); }
  record->collar_extension_indicator = arbitrary();
}

/* Auction Collar Message to the wire: 66 bytes from at, returning where the next byte goes */
static size_t encode_auction_collar_message(const AuctionCollarMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_originator;
  wire[at++] = record->sub_market_center_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_token[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_action_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->collar_reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->collar_up_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->collar_down_price[i]; }
  wire[at++] = record->collar_extension_indicator;

  return at;
}

/* Auction Collar Message off the wire: 66 bytes from at, returning where the next byte lies */
static size_t decode_auction_collar_message(AuctionCollarMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_originator = wire[at++];
  record->sub_market_center_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_action_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->collar_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->collar_up_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->collar_down_price[i] = wire[at++]; }
  record->collar_extension_indicator = wire[at++];

  return at;
}

/* what was read of Auction Collar Message is what was written, byte for byte */
static void equal_auction_collar_message(const AuctionCollarMessage *read, const AuctionCollarMessage *written) {
  assert(read->market_center_originator == written->market_center_originator);
  assert(read->sub_market_center_id == written->sub_market_center_id);
  for (size_t i = 0; i < 8; i++) { assert(read->sip_timestamp[i] == written->sip_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_token[i] == written->participant_token[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_action_sequence_number[i] == written->trading_action_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->collar_reference_price[i] == written->collar_reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->collar_up_price[i] == written->collar_up_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->collar_down_price[i] == written->collar_down_price[i]); }
  assert(read->collar_extension_indicator == written->collar_extension_indicator);
}

/* Auction Collar Message: written and read back, then read and written back */
static void check_auction_collar_message(void) {
  AuctionCollarMessage sent;
  AuctionCollarMessage got;
  uint8_t wire[66];
  uint8_t again[66];

  any_auction_collar_message(&sent);
  assert(encode_auction_collar_message(&sent, wire, 0) == 66);
  assert(decode_auction_collar_message(&got, wire, 0) == 66);
  equal_auction_collar_message(&got, &sent);

  for (size_t i = 0; i < 66; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_collar_message(&got, wire, 0) == 66);
  assert(encode_auction_collar_message(&got, again, 0) == 66);
  for (size_t i = 0; i < 66; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot Sequence Message: 34 bytes ------------------------------------- */

/* Snapshot Sequence Number Message. Reflects the UTP Data Service sequence number at the time the UTP Snap-Shot spin was requested. To stay current, firms should process real-time UTP Data Service messages beginning with the next sequence number after this value. */
typedef struct {
  uint8_t market_center_originator;  /* byte 0 */
  uint8_t sub_market_center_id;      /* byte 1 */
  uint8_t sip_timestamp[8];          /* bytes 2 to 9 */
  uint8_t timestamp_1[8];            /* bytes 10 to 17 */
  uint8_t participant_token[8];      /* bytes 18 to 25 */
  uint8_t sequence_number[8];        /* bytes 26 to 33 */
} SnapshotSequenceMessage;

/* any Snapshot Sequence Message at all: every byte one the checker chooses */
static void any_snapshot_sequence_message(SnapshotSequenceMessage *record) {
  record->market_center_originator = arbitrary();
  record->sub_market_center_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Snapshot Sequence Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_sequence_message(const SnapshotSequenceMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_originator;
  wire[at++] = record->sub_market_center_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Snapshot Sequence Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_sequence_message(SnapshotSequenceMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_originator = wire[at++];
  record->sub_market_center_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Snapshot Sequence Message is what was written, byte for byte */
static void equal_snapshot_sequence_message(const SnapshotSequenceMessage *read, const SnapshotSequenceMessage *written) {
  assert(read->market_center_originator == written->market_center_originator);
  assert(read->sub_market_center_id == written->sub_market_center_id);
  for (size_t i = 0; i < 8; i++) { assert(read->sip_timestamp[i] == written->sip_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_token[i] == written->participant_token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Snapshot Sequence Message: written and read back, then read and written back */
static void check_snapshot_sequence_message(void) {
  SnapshotSequenceMessage sent;
  SnapshotSequenceMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_snapshot_sequence_message(&sent);
  assert(encode_snapshot_sequence_message(&sent, wire, 0) == 34);
  assert(decode_snapshot_sequence_message(&got, wire, 0) == 34);
  equal_snapshot_sequence_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_sequence_message(&got, wire, 0) == 34);
  assert(encode_snapshot_sequence_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Day Message: 26 bytes ------------------------------------------ */

/* Start of Day Control Message. Each day, signals that all subsequent data transmitted will be real-time updates. Prior to 03:58 the data feed handler may be broadcasting heartbeats. */
typedef struct {
  uint8_t market_center_originator;  /* byte 0 */
  uint8_t sub_market_center_id;      /* byte 1 */
  uint8_t sip_timestamp[8];          /* bytes 2 to 9 */
  uint8_t timestamp_1[8];            /* bytes 10 to 17 */
  uint8_t participant_token[8];      /* bytes 18 to 25 */
} StartOfDayMessage;

/* any Start Of Day Message at all: every byte one the checker chooses */
static void any_start_of_day_message(StartOfDayMessage *record) {
  record->market_center_originator = arbitrary();
  record->sub_market_center_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = arbitrary(); }
}

/* Start Of Day Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_start_of_day_message(const StartOfDayMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_originator;
  wire[at++] = record->sub_market_center_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_token[i]; }

  return at;
}

/* Start Of Day Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_start_of_day_message(StartOfDayMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_originator = wire[at++];
  record->sub_market_center_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = wire[at++]; }

  return at;
}

/* what was read of Start Of Day Message is what was written, byte for byte */
static void equal_start_of_day_message(const StartOfDayMessage *read, const StartOfDayMessage *written) {
  assert(read->market_center_originator == written->market_center_originator);
  assert(read->sub_market_center_id == written->sub_market_center_id);
  for (size_t i = 0; i < 8; i++) { assert(read->sip_timestamp[i] == written->sip_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_token[i] == written->participant_token[i]); }
}

/* Start Of Day Message: written and read back, then read and written back */
static void check_start_of_day_message(void) {
  StartOfDayMessage sent;
  StartOfDayMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_start_of_day_message(&sent);
  assert(encode_start_of_day_message(&sent, wire, 0) == 26);
  assert(decode_start_of_day_message(&got, wire, 0) == 26);
  equal_start_of_day_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_day_message(&got, wire, 0) == 26);
  assert(encode_start_of_day_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Session Open Message: 26 bytes ----------------------------------- */

/* Market Session Open Control Message. Signifies the opening of market systems for the Normal Market Session. Each UTP participant may choose to provide its own Market Session Open control message. */
typedef struct {
  uint8_t market_center_originator;  /* byte 0 */
  uint8_t sub_market_center_id;      /* byte 1 */
  uint8_t sip_timestamp[8];          /* bytes 2 to 9 */
  uint8_t timestamp_1[8];            /* bytes 10 to 17 */
  uint8_t participant_token[8];      /* bytes 18 to 25 */
} MarketSessionOpenMessage;

/* any Market Session Open Message at all: every byte one the checker chooses */
static void any_market_session_open_message(MarketSessionOpenMessage *record) {
  record->market_center_originator = arbitrary();
  record->sub_market_center_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = arbitrary(); }
}

/* Market Session Open Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_market_session_open_message(const MarketSessionOpenMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_originator;
  wire[at++] = record->sub_market_center_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_token[i]; }

  return at;
}

/* Market Session Open Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_market_session_open_message(MarketSessionOpenMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_originator = wire[at++];
  record->sub_market_center_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = wire[at++]; }

  return at;
}

/* what was read of Market Session Open Message is what was written, byte for byte */
static void equal_market_session_open_message(const MarketSessionOpenMessage *read, const MarketSessionOpenMessage *written) {
  assert(read->market_center_originator == written->market_center_originator);
  assert(read->sub_market_center_id == written->sub_market_center_id);
  for (size_t i = 0; i < 8; i++) { assert(read->sip_timestamp[i] == written->sip_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_token[i] == written->participant_token[i]); }
}

/* Market Session Open Message: written and read back, then read and written back */
static void check_market_session_open_message(void) {
  MarketSessionOpenMessage sent;
  MarketSessionOpenMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_market_session_open_message(&sent);
  assert(encode_market_session_open_message(&sent, wire, 0) == 26);
  assert(decode_market_session_open_message(&got, wire, 0) == 26);
  equal_market_session_open_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_market_session_open_message(&got, wire, 0) == 26);
  assert(encode_market_session_open_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Session Close Message: 26 bytes ---------------------------------- */

/* Market Session Close Control Message. Signals the closing of market systems for the Normal Market Session. */
typedef struct {
  uint8_t market_center_originator;  /* byte 0 */
  uint8_t sub_market_center_id;      /* byte 1 */
  uint8_t sip_timestamp[8];          /* bytes 2 to 9 */
  uint8_t timestamp_1[8];            /* bytes 10 to 17 */
  uint8_t participant_token[8];      /* bytes 18 to 25 */
} MarketSessionCloseMessage;

/* any Market Session Close Message at all: every byte one the checker chooses */
static void any_market_session_close_message(MarketSessionCloseMessage *record) {
  record->market_center_originator = arbitrary();
  record->sub_market_center_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = arbitrary(); }
}

/* Market Session Close Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_market_session_close_message(const MarketSessionCloseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_originator;
  wire[at++] = record->sub_market_center_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_token[i]; }

  return at;
}

/* Market Session Close Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_market_session_close_message(MarketSessionCloseMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_originator = wire[at++];
  record->sub_market_center_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = wire[at++]; }

  return at;
}

/* what was read of Market Session Close Message is what was written, byte for byte */
static void equal_market_session_close_message(const MarketSessionCloseMessage *read, const MarketSessionCloseMessage *written) {
  assert(read->market_center_originator == written->market_center_originator);
  assert(read->sub_market_center_id == written->sub_market_center_id);
  for (size_t i = 0; i < 8; i++) { assert(read->sip_timestamp[i] == written->sip_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_token[i] == written->participant_token[i]); }
}

/* Market Session Close Message: written and read back, then read and written back */
static void check_market_session_close_message(void) {
  MarketSessionCloseMessage sent;
  MarketSessionCloseMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_market_session_close_message(&sent);
  assert(encode_market_session_close_message(&sent, wire, 0) == 26);
  assert(decode_market_session_close_message(&got, wire, 0) == 26);
  equal_market_session_close_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_market_session_close_message(&got, wire, 0) == 26);
  assert(encode_market_session_close_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Day Message: 26 bytes -------------------------------------------- */

/* End of Day Control Message. Signals the end of active message dissemination for the UTP SIP operational cycle. */
typedef struct {
  uint8_t market_center_originator;  /* byte 0 */
  uint8_t sub_market_center_id;      /* byte 1 */
  uint8_t sip_timestamp[8];          /* bytes 2 to 9 */
  uint8_t timestamp_1[8];            /* bytes 10 to 17 */
  uint8_t participant_token[8];      /* bytes 18 to 25 */
} EndOfDayMessage;

/* any End Of Day Message at all: every byte one the checker chooses */
static void any_end_of_day_message(EndOfDayMessage *record) {
  record->market_center_originator = arbitrary();
  record->sub_market_center_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = arbitrary(); }
}

/* End Of Day Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_end_of_day_message(const EndOfDayMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_originator;
  wire[at++] = record->sub_market_center_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_token[i]; }

  return at;
}

/* End Of Day Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_end_of_day_message(EndOfDayMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_originator = wire[at++];
  record->sub_market_center_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Day Message is what was written, byte for byte */
static void equal_end_of_day_message(const EndOfDayMessage *read, const EndOfDayMessage *written) {
  assert(read->market_center_originator == written->market_center_originator);
  assert(read->sub_market_center_id == written->sub_market_center_id);
  for (size_t i = 0; i < 8; i++) { assert(read->sip_timestamp[i] == written->sip_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_token[i] == written->participant_token[i]); }
}

/* End Of Day Message: written and read back, then read and written back */
static void check_end_of_day_message(void) {
  EndOfDayMessage sent;
  EndOfDayMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_end_of_day_message(&sent);
  assert(encode_end_of_day_message(&sent, wire, 0) == 26);
  assert(decode_end_of_day_message(&got, wire, 0) == 26);
  equal_end_of_day_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_day_message(&got, wire, 0) == 26);
  assert(encode_end_of_day_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Transmissions Message: 26 bytes ---------------------------------- */

/* End of Transmissions Control Message. Last production message of the day; signals no further transmissions through the UTP SIP line. */
typedef struct {
  uint8_t market_center_originator;  /* byte 0 */
  uint8_t sub_market_center_id;      /* byte 1 */
  uint8_t sip_timestamp[8];          /* bytes 2 to 9 */
  uint8_t timestamp_1[8];            /* bytes 10 to 17 */
  uint8_t participant_token[8];      /* bytes 18 to 25 */
} EndOfTransmissionsMessage;

/* any End Of Transmissions Message at all: every byte one the checker chooses */
static void any_end_of_transmissions_message(EndOfTransmissionsMessage *record) {
  record->market_center_originator = arbitrary();
  record->sub_market_center_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = arbitrary(); }
}

/* End Of Transmissions Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_end_of_transmissions_message(const EndOfTransmissionsMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center_originator;
  wire[at++] = record->sub_market_center_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sip_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_token[i]; }

  return at;
}

/* End Of Transmissions Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_end_of_transmissions_message(EndOfTransmissionsMessage *record, const uint8_t *wire, size_t at) {
  record->market_center_originator = wire[at++];
  record->sub_market_center_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sip_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_token[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Transmissions Message is what was written, byte for byte */
static void equal_end_of_transmissions_message(const EndOfTransmissionsMessage *read, const EndOfTransmissionsMessage *written) {
  assert(read->market_center_originator == written->market_center_originator);
  assert(read->sub_market_center_id == written->sub_market_center_id);
  for (size_t i = 0; i < 8; i++) { assert(read->sip_timestamp[i] == written->sip_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_1[i] == written->timestamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_token[i] == written->participant_token[i]); }
}

/* End Of Transmissions Message: written and read back, then read and written back */
static void check_end_of_transmissions_message(void) {
  EndOfTransmissionsMessage sent;
  EndOfTransmissionsMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_end_of_transmissions_message(&sent);
  assert(encode_end_of_transmissions_message(&sent, wire, 0) == 26);
  assert(decode_end_of_transmissions_message(&got, wire, 0) == 26);
  equal_end_of_transmissions_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_transmissions_message(&got, wire, 0) == 26);
  assert(encode_end_of_transmissions_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Accepted Packet: 30 bytes ----------------------------------------- */

/* SoupBinTCP Login Accepted Packet */
typedef struct {
  uint8_t accepted_session[10];          /* bytes 0 to 9 */
  uint8_t accepted_sequence_number[20];  /* bytes 10 to 29 */
} LoginAcceptedPacket;

/* any Login Accepted Packet at all: every byte one the checker chooses */
static void any_login_accepted_packet(LoginAcceptedPacket *record) {
  for (size_t i = 0; i < 10; i++) { record->accepted_session[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->accepted_sequence_number[i] = arbitrary(); }
}

/* Login Accepted Packet to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_login_accepted_packet(const LoginAcceptedPacket *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->accepted_session[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->accepted_sequence_number[i]; }

  return at;
}

/* Login Accepted Packet off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_login_accepted_packet(LoginAcceptedPacket *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->accepted_session[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->accepted_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Accepted Packet is what was written, byte for byte */
static void equal_login_accepted_packet(const LoginAcceptedPacket *read, const LoginAcceptedPacket *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->accepted_session[i] == written->accepted_session[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->accepted_sequence_number[i] == written->accepted_sequence_number[i]); }
}

/* Login Accepted Packet: written and read back, then read and written back */
static void check_login_accepted_packet(void) {
  LoginAcceptedPacket sent;
  LoginAcceptedPacket got;
  uint8_t wire[30];
  uint8_t again[30];

  any_login_accepted_packet(&sent);
  assert(encode_login_accepted_packet(&sent, wire, 0) == 30);
  assert(decode_login_accepted_packet(&got, wire, 0) == 30);
  equal_login_accepted_packet(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_login_accepted_packet(&got, wire, 0) == 30);
  assert(encode_login_accepted_packet(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Rejected Packet: 1 byte ------------------------------------------- */

/* SoupBinTCP Login Rejected Packet */
typedef struct {
  uint8_t reject_reason_code;  /* byte 0 */
} LoginRejectedPacket;

/* any Login Rejected Packet at all: every byte one the checker chooses */
static void any_login_rejected_packet(LoginRejectedPacket *record) {
  record->reject_reason_code = arbitrary();
}

/* Login Rejected Packet to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_login_rejected_packet(const LoginRejectedPacket *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reject_reason_code;

  return at;
}

/* Login Rejected Packet off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_login_rejected_packet(LoginRejectedPacket *record, const uint8_t *wire, size_t at) {
  record->reject_reason_code = wire[at++];

  return at;
}

/* what was read of Login Rejected Packet is what was written, byte for byte */
static void equal_login_rejected_packet(const LoginRejectedPacket *read, const LoginRejectedPacket *written) {
  assert(read->reject_reason_code == written->reject_reason_code);
}

/* Login Rejected Packet: written and read back, then read and written back */
static void check_login_rejected_packet(void) {
  LoginRejectedPacket sent;
  LoginRejectedPacket got;
  uint8_t wire[1];
  uint8_t again[1];

  any_login_rejected_packet(&sent);
  assert(encode_login_rejected_packet(&sent, wire, 0) == 1);
  assert(decode_login_rejected_packet(&got, wire, 0) == 1);
  equal_login_rejected_packet(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_login_rejected_packet(&got, wire, 0) == 1);
  assert(encode_login_rejected_packet(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_tcp_packet_header();
  check_message_header();
  check_issue_symbol_directory_message();
  check_enhanced_issue_symbol_directory_message();
  check_reg_sho_short_sale_price_test_restricted_indicator_message();
  check_cross_sro_trading_action_message();
  check_market_center_trading_action_message();
  check_market_wide_circuit_breaker_decline_level_message();
  check_limit_up_limit_down_price_band_message();
  check_auction_collar_message();
  check_snapshot_sequence_message();
  check_start_of_day_message();
  check_market_session_open_message();
  check_market_session_close_message();
  check_end_of_day_message();
  check_end_of_transmissions_message();
  check_login_accepted_packet();
  check_login_rejected_packet();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
