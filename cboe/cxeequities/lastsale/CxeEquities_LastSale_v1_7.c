// cboe/cxeequities/lastsale/CxeEquities_LastSale_v1_7.c
/*
 * Chicago Board Options Exchange Last Sale
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
 *   - a field filling what is left of what holds it
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

/* ---- Debug Packet: 1 byte ---------------------------------------------------- */

/* Debug packets are intended to provide human readable text that may aid in debugging problems. */
typedef struct {
  uint8_t text;  /* byte 0 */
} DebugPacket;

/* any Debug Packet at all: every byte one the checker chooses */
static void any_debug_packet(DebugPacket *record) {
  record->text = arbitrary();
}

/* Debug Packet to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_debug_packet(const DebugPacket *record, uint8_t *wire, size_t at) {
  wire[at++] = record->text;

  return at;
}

/* Debug Packet off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_debug_packet(DebugPacket *record, const uint8_t *wire, size_t at) {
  record->text = wire[at++];

  return at;
}

/* what was read of Debug Packet is what was written, byte for byte */
static void equal_debug_packet(const DebugPacket *read, const DebugPacket *written) {
  assert(read->text == written->text);
}

/* Debug Packet: written and read back, then read and written back */
static void check_debug_packet(void) {
  DebugPacket sent;
  DebugPacket got;
  uint8_t wire[1];
  uint8_t again[1];

  any_debug_packet(&sent);
  assert(encode_debug_packet(&sent, wire, 0) == 1);
  assert(decode_debug_packet(&got, wire, 0) == 1);
  equal_debug_packet(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_debug_packet(&got, wire, 0) == 1);
  assert(encode_debug_packet(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Accepted Packet: 20 bytes ----------------------------------------- */

/* The Soup 2.0 server sends a Login Accepted Packet in response to receiving a valid Login Request  from the client. */
typedef struct {
  uint8_t session[10];          /* bytes 0 to 9 */
  uint8_t sequence_number[10];  /* bytes 10 to 19 */
} LoginAcceptedPacket;

/* any Login Accepted Packet at all: every byte one the checker chooses */
static void any_login_accepted_packet(LoginAcceptedPacket *record) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Login Accepted Packet to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_login_accepted_packet(const LoginAcceptedPacket *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Login Accepted Packet off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_login_accepted_packet(LoginAcceptedPacket *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Accepted Packet is what was written, byte for byte */
static void equal_login_accepted_packet(const LoginAcceptedPacket *read, const LoginAcceptedPacket *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Login Accepted Packet: written and read back, then read and written back */
static void check_login_accepted_packet(void) {
  LoginAcceptedPacket sent;
  LoginAcceptedPacket got;
  uint8_t wire[20];
  uint8_t again[20];

  any_login_accepted_packet(&sent);
  assert(encode_login_accepted_packet(&sent, wire, 0) == 20);
  assert(decode_login_accepted_packet(&got, wire, 0) == 20);
  equal_login_accepted_packet(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_login_accepted_packet(&got, wire, 0) == 20);
  assert(encode_login_accepted_packet(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Rejected Packet: 1 byte ------------------------------------------- */

/* The Soup 2.0 server sends this packet in response to an invalid Login Request Packet from the client. */
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

/* ---- Sequenced Message Header: 9 bytes --------------------------------------- */

/* Sequenced Message Header */
typedef struct {
  uint8_t timestamp[8];            /* bytes 0 to 7 */
  uint8_t sequenced_message_type;  /* byte 8 */
} SequencedMessageHeader;

/* any Sequenced Message Header at all: every byte one the checker chooses */
static void any_sequenced_message_header(SequencedMessageHeader *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->sequenced_message_type = arbitrary();
}

/* Sequenced Message Header to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_sequenced_message_header(const SequencedMessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->sequenced_message_type;

  return at;
}

/* Sequenced Message Header off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_sequenced_message_header(SequencedMessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->sequenced_message_type = wire[at++];

  return at;
}

/* what was read of Sequenced Message Header is what was written, byte for byte */
static void equal_sequenced_message_header(const SequencedMessageHeader *read, const SequencedMessageHeader *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->sequenced_message_type == written->sequenced_message_type);
}

/* Sequenced Message Header: written and read back, then read and written back */
static void check_sequenced_message_header(void) {
  SequencedMessageHeader sent;
  SequencedMessageHeader got;
  uint8_t wire[9];
  uint8_t again[9];

  any_sequenced_message_header(&sent);
  assert(encode_sequenced_message_header(&sent, wire, 0) == 9);
  assert(decode_sequenced_message_header(&got, wire, 0) == 9);
  equal_sequenced_message_header(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_sequenced_message_header(&got, wire, 0) == 9);
  assert(encode_sequenced_message_header(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Sale Europe Message: 157 bytes ------------------------------------- */

/* Last Sale Europe Messages are sent when an order on a Cboe order book is executed in whole or in part, or when a reported trade is submitted to Cboe */
typedef struct {
  uint8_t trading_date_time[27];             /* bytes 0 to 26 */
  uint8_t symbol[12];                        /* bytes 27 to 38 */
  uint8_t price[18];                         /* bytes 39 to 56 */
  uint8_t price_currency[3];                 /* bytes 57 to 59 */
  uint8_t executed_shares[12];               /* bytes 60 to 71 */
  uint8_t execution_venue[4];                /* bytes 72 to 75 */
  uint8_t publication_date_time[27];         /* bytes 76 to 102 */
  uint8_t trade_id[12];                      /* bytes 103 to 114 */
  uint8_t transaction_category[4];           /* bytes 115 to 118 */
  uint8_t negotiation_flag[4];               /* bytes 119 to 122 */
  uint8_t agency_cross_trade[4];             /* bytes 123 to 126 */
  uint8_t modification_indicator[4];         /* bytes 127 to 130 */
  uint8_t benchmark_reference_indicator[4];  /* bytes 131 to 134 */
  uint8_t special_dividend[4];               /* bytes 135 to 138 */
  uint8_t price_discovery_process[4];        /* bytes 139 to 142 */
  uint8_t algorithmic_indicator[4];          /* bytes 143 to 146 */
  uint8_t post_trade_deferral_reason[4];     /* bytes 147 to 150 */
  uint8_t duplicative_indicator[4];          /* bytes 151 to 154 */
  uint8_t jurisdiction[2];                   /* bytes 155 to 156 */
} LastSaleEuropeMessage;

/* any Last Sale Europe Message at all: every byte one the checker chooses */
static void any_last_sale_europe_message(LastSaleEuropeMessage *record) {
  for (size_t i = 0; i < 27; i++) { record->trading_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->price_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->executed_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 27; i++) { record->publication_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->transaction_category[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->negotiation_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->agency_cross_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->modification_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->benchmark_reference_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->special_dividend[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_discovery_process[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->algorithmic_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->post_trade_deferral_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->duplicative_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->jurisdiction[i] = arbitrary(); }
}

/* Last Sale Europe Message to the wire: 157 bytes from at, returning where the next byte goes */
static size_t encode_last_sale_europe_message(const LastSaleEuropeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 27; i++) { wire[at++] = record->trading_date_time[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->price_currency[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->executed_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_venue[i]; }
  for (size_t i = 0; i < 27; i++) { wire[at++] = record->publication_date_time[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_category[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->negotiation_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->agency_cross_trade[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->modification_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->benchmark_reference_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->special_dividend[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_discovery_process[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->algorithmic_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->post_trade_deferral_reason[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->duplicative_indicator[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->jurisdiction[i]; }

  return at;
}

/* Last Sale Europe Message off the wire: 157 bytes from at, returning where the next byte lies */
static size_t decode_last_sale_europe_message(LastSaleEuropeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 27; i++) { record->trading_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->price_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->executed_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 27; i++) { record->publication_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->transaction_category[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->negotiation_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->agency_cross_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->modification_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->benchmark_reference_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->special_dividend[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_discovery_process[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->algorithmic_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->post_trade_deferral_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->duplicative_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->jurisdiction[i] = wire[at++]; }

  return at;
}

/* what was read of Last Sale Europe Message is what was written, byte for byte */
static void equal_last_sale_europe_message(const LastSaleEuropeMessage *read, const LastSaleEuropeMessage *written) {
  for (size_t i = 0; i < 27; i++) { assert(read->trading_date_time[i] == written->trading_date_time[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->price_currency[i] == written->price_currency[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->executed_shares[i] == written->executed_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_venue[i] == written->execution_venue[i]); }
  for (size_t i = 0; i < 27; i++) { assert(read->publication_date_time[i] == written->publication_date_time[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_category[i] == written->transaction_category[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->negotiation_flag[i] == written->negotiation_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->agency_cross_trade[i] == written->agency_cross_trade[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->modification_indicator[i] == written->modification_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->benchmark_reference_indicator[i] == written->benchmark_reference_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->special_dividend[i] == written->special_dividend[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_discovery_process[i] == written->price_discovery_process[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->algorithmic_indicator[i] == written->algorithmic_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->post_trade_deferral_reason[i] == written->post_trade_deferral_reason[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->duplicative_indicator[i] == written->duplicative_indicator[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->jurisdiction[i] == written->jurisdiction[i]); }
}

/* Last Sale Europe Message: written and read back, then read and written back */
static void check_last_sale_europe_message(void) {
  LastSaleEuropeMessage sent;
  LastSaleEuropeMessage got;
  uint8_t wire[157];
  uint8_t again[157];

  any_last_sale_europe_message(&sent);
  assert(encode_last_sale_europe_message(&sent, wire, 0) == 157);
  assert(decode_last_sale_europe_message(&got, wire, 0) == 157);
  equal_last_sale_europe_message(&got, &sent);

  for (size_t i = 0; i < 157; i++) { wire[i] = arbitrary(); }
  assert(decode_last_sale_europe_message(&got, wire, 0) == 157);
  assert(encode_last_sale_europe_message(&got, again, 0) == 157);
  for (size_t i = 0; i < 157; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Sale Europe Message New: 234 bytes --------------------------------- */

/* Last Sale Europe Messages are sent when an order on a Cboe order book is executed in whole or in part, or when a reported trade is submitted to Cboe */
typedef struct {
  uint8_t trading_date_time[27];               /* bytes 0 to 26 */
  uint8_t symbol[12];                          /* bytes 27 to 38 */
  uint8_t price[18];                           /* bytes 39 to 56 */
  uint8_t price_notation[4];                   /* bytes 57 to 60 */
  uint8_t price_currency[3];                   /* bytes 61 to 63 */
  uint8_t executed_shares[12];                 /* bytes 64 to 75 */
  uint8_t notional_amount[18];                 /* bytes 76 to 93 */
  uint8_t notional_currency[3];                /* bytes 94 to 96 */
  uint8_t execution_venue[4];                  /* bytes 97 to 100 */
  uint8_t third_country_trading_venue[4];      /* bytes 101 to 104 */
  uint8_t publication_date_time[27];           /* bytes 105 to 131 */
  uint8_t trade_id[12];                        /* bytes 132 to 143 */
  uint8_t market_mechanism[4];                 /* bytes 144 to 147 */
  uint8_t trading_mode[4];                     /* bytes 148 to 151 */
  uint8_t transaction_category[4];             /* bytes 152 to 155 */
  uint8_t negotiation_flag[4];                 /* bytes 156 to 159 */
  uint8_t agency_cross_trade[4];               /* bytes 160 to 163 */
  uint8_t modification_indicator[4];           /* bytes 164 to 167 */
  uint8_t benchmark_indicator[4];              /* bytes 168 to 171 */
  uint8_t special_dividend[4];                 /* bytes 172 to 175 */
  uint8_t off_book_automated[4];               /* bytes 176 to 179 */
  uint8_t price_discovery_process[4];          /* bytes 180 to 183 */
  uint8_t algorithmic_indicator[4];            /* bytes 184 to 187 */
  uint8_t pre_trade_transparency_waiver[4];    /* bytes 188 to 191 */
  uint8_t portfolio_flag[4];                   /* bytes 192 to 195 */
  uint8_t contingent_flag[4];                  /* bytes 196 to 199 */
  uint8_t give_up_flag[4];                     /* bytes 200 to 203 */
  uint8_t post_trade_deferral_reason[4];       /* bytes 204 to 207 */
  uint8_t deferral_or_enrichment_type[4];      /* bytes 208 to 211 */
  uint8_t deferral_illiquid_instrument[4];     /* bytes 212 to 215 */
  uint8_t deferral_size_specific[4];           /* bytes 216 to 219 */
  uint8_t duplicative_within_jurisdiction[4];  /* bytes 220 to 223 */
  uint8_t duplicative_across_jurisdiction[4];  /* bytes 224 to 227 */
  uint8_t intra_group_indicator[4];            /* bytes 228 to 231 */
  uint8_t jurisdiction[2];                     /* bytes 232 to 233 */
} LastSaleEuropeMessageNew;

/* any Last Sale Europe Message New at all: every byte one the checker chooses */
static void any_last_sale_europe_message_new(LastSaleEuropeMessageNew *record) {
  for (size_t i = 0; i < 27; i++) { record->trading_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->price_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->executed_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->notional_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->third_country_trading_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 27; i++) { record->publication_date_time[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_mechanism[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_mode[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->transaction_category[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->negotiation_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->agency_cross_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->modification_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->benchmark_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->special_dividend[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->off_book_automated[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_discovery_process[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->algorithmic_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pre_trade_transparency_waiver[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->portfolio_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contingent_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->give_up_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->post_trade_deferral_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->deferral_or_enrichment_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->deferral_illiquid_instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->deferral_size_specific[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->duplicative_within_jurisdiction[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->duplicative_across_jurisdiction[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->intra_group_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->jurisdiction[i] = arbitrary(); }
}

/* Last Sale Europe Message New to the wire: 234 bytes from at, returning where the next byte goes */
static size_t encode_last_sale_europe_message_new(const LastSaleEuropeMessageNew *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 27; i++) { wire[at++] = record->trading_date_time[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_notation[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->price_currency[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->executed_shares[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->notional_amount[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->notional_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_venue[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->third_country_trading_venue[i]; }
  for (size_t i = 0; i < 27; i++) { wire[at++] = record->publication_date_time[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_mechanism[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_mode[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_category[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->negotiation_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->agency_cross_trade[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->modification_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->benchmark_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->special_dividend[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->off_book_automated[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_discovery_process[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->algorithmic_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pre_trade_transparency_waiver[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->portfolio_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contingent_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_up_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->post_trade_deferral_reason[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->deferral_or_enrichment_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->deferral_illiquid_instrument[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->deferral_size_specific[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->duplicative_within_jurisdiction[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->duplicative_across_jurisdiction[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->intra_group_indicator[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->jurisdiction[i]; }

  return at;
}

/* Last Sale Europe Message New off the wire: 234 bytes from at, returning where the next byte lies */
static size_t decode_last_sale_europe_message_new(LastSaleEuropeMessageNew *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 27; i++) { record->trading_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->price_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->executed_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->notional_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->third_country_trading_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 27; i++) { record->publication_date_time[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_mechanism[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_mode[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->transaction_category[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->negotiation_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->agency_cross_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->modification_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->benchmark_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->special_dividend[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->off_book_automated[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_discovery_process[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->algorithmic_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pre_trade_transparency_waiver[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->portfolio_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contingent_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->give_up_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->post_trade_deferral_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->deferral_or_enrichment_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->deferral_illiquid_instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->deferral_size_specific[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->duplicative_within_jurisdiction[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->duplicative_across_jurisdiction[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->intra_group_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->jurisdiction[i] = wire[at++]; }

  return at;
}

/* what was read of Last Sale Europe Message New is what was written, byte for byte */
static void equal_last_sale_europe_message_new(const LastSaleEuropeMessageNew *read, const LastSaleEuropeMessageNew *written) {
  for (size_t i = 0; i < 27; i++) { assert(read->trading_date_time[i] == written->trading_date_time[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_notation[i] == written->price_notation[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->price_currency[i] == written->price_currency[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->executed_shares[i] == written->executed_shares[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->notional_amount[i] == written->notional_amount[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->notional_currency[i] == written->notional_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_venue[i] == written->execution_venue[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->third_country_trading_venue[i] == written->third_country_trading_venue[i]); }
  for (size_t i = 0; i < 27; i++) { assert(read->publication_date_time[i] == written->publication_date_time[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_mechanism[i] == written->market_mechanism[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_mode[i] == written->trading_mode[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_category[i] == written->transaction_category[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->negotiation_flag[i] == written->negotiation_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->agency_cross_trade[i] == written->agency_cross_trade[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->modification_indicator[i] == written->modification_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->benchmark_indicator[i] == written->benchmark_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->special_dividend[i] == written->special_dividend[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->off_book_automated[i] == written->off_book_automated[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_discovery_process[i] == written->price_discovery_process[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->algorithmic_indicator[i] == written->algorithmic_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pre_trade_transparency_waiver[i] == written->pre_trade_transparency_waiver[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->portfolio_flag[i] == written->portfolio_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contingent_flag[i] == written->contingent_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->give_up_flag[i] == written->give_up_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->post_trade_deferral_reason[i] == written->post_trade_deferral_reason[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->deferral_or_enrichment_type[i] == written->deferral_or_enrichment_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->deferral_illiquid_instrument[i] == written->deferral_illiquid_instrument[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->deferral_size_specific[i] == written->deferral_size_specific[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->duplicative_within_jurisdiction[i] == written->duplicative_within_jurisdiction[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->duplicative_across_jurisdiction[i] == written->duplicative_across_jurisdiction[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->intra_group_indicator[i] == written->intra_group_indicator[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->jurisdiction[i] == written->jurisdiction[i]); }
}

/* Last Sale Europe Message New: written and read back, then read and written back */
static void check_last_sale_europe_message_new(void) {
  LastSaleEuropeMessageNew sent;
  LastSaleEuropeMessageNew got;
  uint8_t wire[234];
  uint8_t again[234];

  any_last_sale_europe_message_new(&sent);
  assert(encode_last_sale_europe_message_new(&sent, wire, 0) == 234);
  assert(decode_last_sale_europe_message_new(&got, wire, 0) == 234);
  equal_last_sale_europe_message_new(&got, &sent);

  for (size_t i = 0; i < 234; i++) { wire[i] = arbitrary(); }
  assert(decode_last_sale_europe_message_new(&got, wire, 0) == 234);
  assert(encode_last_sale_europe_message_new(&got, again, 0) == 234);
  for (size_t i = 0; i < 234; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request Packet: 36 bytes ------------------------------------------ */

/* The Soup 2.0 client must send a Login Request Packet immediately upon establishing a new TCP/IP socket connection to the server. */
typedef struct {
  uint8_t username[6];                    /* bytes 0 to 5 */
  uint8_t password[10];                   /* bytes 6 to 15 */
  uint8_t requested_session[10];          /* bytes 16 to 25 */
  uint8_t requested_sequence_number[10];  /* bytes 26 to 35 */
} LoginRequestPacket;

/* any Login Request Packet at all: every byte one the checker chooses */
static void any_login_request_packet(LoginRequestPacket *record) {
  for (size_t i = 0; i < 6; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->requested_session[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->requested_sequence_number[i] = arbitrary(); }
}

/* Login Request Packet to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_login_request_packet(const LoginRequestPacket *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->requested_session[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->requested_sequence_number[i]; }

  return at;
}

/* Login Request Packet off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_login_request_packet(LoginRequestPacket *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->requested_session[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->requested_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request Packet is what was written, byte for byte */
static void equal_login_request_packet(const LoginRequestPacket *read, const LoginRequestPacket *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->requested_session[i] == written->requested_session[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->requested_sequence_number[i] == written->requested_sequence_number[i]); }
}

/* Login Request Packet: written and read back, then read and written back */
static void check_login_request_packet(void) {
  LoginRequestPacket sent;
  LoginRequestPacket got;
  uint8_t wire[36];
  uint8_t again[36];

  any_login_request_packet(&sent);
  assert(encode_login_request_packet(&sent, wire, 0) == 36);
  assert(decode_login_request_packet(&got, wire, 0) == 36);
  equal_login_request_packet(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request_packet(&got, wire, 0) == 36);
  assert(encode_login_request_packet(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_debug_packet();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_sequenced_message_header();
  check_last_sale_europe_message();
  check_last_sale_europe_message_new();
  check_login_request_packet();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
