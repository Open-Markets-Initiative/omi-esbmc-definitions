// sse/ssesecurities/mdgw/SseSecurities_Mdgw_v0_63.c
/*
 * Shanghai Stock Exchange Market Data Gateway
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

/* ---- Standard Header: 24 bytes ----------------------------------------------- */

typedef struct {
  uint8_t msg_type[4];      /* bytes 0 to 3 */
  uint8_t sending_time[8];  /* bytes 4 to 11 */
  uint8_t msg_seq_num[8];   /* bytes 12 to 19 */
  uint8_t body_length[4];   /* bytes 20 to 23 */
} StandardHeader;

/* any Standard Header at all: every byte one the checker chooses */
static void any_standard_header(StandardHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->body_length[i] = arbitrary(); }
}

/* Standard Header to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_standard_header(const StandardHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->body_length[i]; }

  return at;
}

/* Standard Header off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_standard_header(StandardHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->body_length[i] = wire[at++]; }

  return at;
}

/* what was read of Standard Header is what was written, byte for byte */
static void equal_standard_header(const StandardHeader *read, const StandardHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_type[i] == written->msg_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->body_length[i] == written->body_length[i]); }
}

/* Standard Header: written and read back, then read and written back */
static void check_standard_header(void) {
  StandardHeader sent;
  StandardHeader got;
  uint8_t wire[24];
  uint8_t again[24];

  any_standard_header(&sent);
  assert(encode_standard_header(&sent, wire, 0) == 24);
  assert(decode_standard_header(&got, wire, 0) == 24);
  equal_standard_header(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_standard_header(&got, wire, 0) == 24);
  assert(encode_standard_header(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Message: 74 bytes ------------------------------------------------- */

/* The client must send this message first when starting a market data session. */
typedef struct {
  uint8_t sender_comp_i_d[32];  /* bytes 0 to 31 */
  uint8_t target_comp_i_d[32];  /* bytes 32 to 63 */
  uint8_t heart_bt_int[2];      /* bytes 64 to 65 */
  uint8_t appl_ver_i_d[8];      /* bytes 66 to 73 */
} LogonMessage;

/* any Logon Message at all: every byte one the checker chooses */
static void any_logon_message(LogonMessage *record) {
  for (size_t i = 0; i < 32; i++) { record->sender_comp_i_d[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->target_comp_i_d[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->heart_bt_int[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_ver_i_d[i] = arbitrary(); }
}

/* Logon Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_logon_message(const LogonMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->sender_comp_i_d[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->target_comp_i_d[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->heart_bt_int[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_ver_i_d[i]; }

  return at;
}

/* Logon Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_logon_message(LogonMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 32; i++) { record->sender_comp_i_d[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->target_comp_i_d[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->heart_bt_int[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_ver_i_d[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Message is what was written, byte for byte */
static void equal_logon_message(const LogonMessage *read, const LogonMessage *written) {
  for (size_t i = 0; i < 32; i++) { assert(read->sender_comp_i_d[i] == written->sender_comp_i_d[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->target_comp_i_d[i] == written->target_comp_i_d[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->heart_bt_int[i] == written->heart_bt_int[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_ver_i_d[i] == written->appl_ver_i_d[i]); }
}

/* Logon Message: written and read back, then read and written back */
static void check_logon_message(void) {
  LogonMessage sent;
  LogonMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_logon_message(&sent);
  assert(encode_logon_message(&sent, wire, 0) == 74);
  assert(decode_logon_message(&got, wire, 0) == 74);
  equal_logon_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_message(&got, wire, 0) == 74);
  assert(encode_logon_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Message: 260 bytes ----------------------------------------------- */

/* The logout message starts or confirms the end of a market data session. A disconnection without an exchange of logout messages is treated as an abnormal disconnection. After sending a logout message, neither side of the connection should send any further message. */
typedef struct {
  uint8_t session_status[4];  /* bytes 0 to 3 */
  uint8_t text[256];          /* bytes 4 to 259 */
} LogoutMessage;

/* any Logout Message at all: every byte one the checker chooses */
static void any_logout_message(LogoutMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_status[i] = arbitrary(); }
  for (size_t i = 0; i < 256; i++) { record->text[i] = arbitrary(); }
}

/* Logout Message to the wire: 260 bytes from at, returning where the next byte goes */
static size_t encode_logout_message(const LogoutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_status[i]; }
  for (size_t i = 0; i < 256; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Logout Message off the wire: 260 bytes from at, returning where the next byte lies */
static size_t decode_logout_message(LogoutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_status[i] = wire[at++]; }
  for (size_t i = 0; i < 256; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Logout Message is what was written, byte for byte */
static void equal_logout_message(const LogoutMessage *read, const LogoutMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_status[i] == written->session_status[i]); }
  for (size_t i = 0; i < 256; i++) { assert(read->text[i] == written->text[i]); }
}

/* Logout Message: written and read back, then read and written back */
static void check_logout_message(void) {
  LogoutMessage sent;
  LogoutMessage got;
  uint8_t wire[260];
  uint8_t again[260];

  any_logout_message(&sent);
  assert(encode_logout_message(&sent, wire, 0) == 260);
  assert(decode_logout_message(&got, wire, 0) == 260);
  equal_logout_message(&got, &sent);

  for (size_t i = 0; i < 260; i++) { wire[i] = arbitrary(); }
  assert(decode_logout_message(&got, wire, 0) == 260);
  assert(encode_logout_message(&got, again, 0) == 260);
  for (size_t i = 0; i < 260; i++) { assert(again[i] == wire[i]); }
}

/* ---- Channel Heartbeat: 12 bytes --------------------------------------------- */

/* Tick-by-tick market data supports sending a heartbeat every 3 seconds during idle periods of data sending. If data sending stays busy, the channel heartbeat interval can exceed 3s. */
typedef struct {
  uint8_t channel_heartbeat_security_type;   /* byte 0 */
  uint8_t channel_heartbeat_channel_n_o[2];  /* bytes 1 to 2 */
  uint8_t appl_last_seq_num[8];              /* bytes 3 to 10 */
  uint8_t end_of_channel;                    /* byte 11 */
} ChannelHeartbeat;

/* any Channel Heartbeat at all: every byte one the checker chooses */
static void any_channel_heartbeat(ChannelHeartbeat *record) {
  record->channel_heartbeat_security_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->channel_heartbeat_channel_n_o[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_last_seq_num[i] = arbitrary(); }
  record->end_of_channel = arbitrary();
}

/* Channel Heartbeat to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_channel_heartbeat(const ChannelHeartbeat *record, uint8_t *wire, size_t at) {
  wire[at++] = record->channel_heartbeat_security_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_heartbeat_channel_n_o[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_last_seq_num[i]; }
  wire[at++] = record->end_of_channel;

  return at;
}

/* Channel Heartbeat off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_channel_heartbeat(ChannelHeartbeat *record, const uint8_t *wire, size_t at) {
  record->channel_heartbeat_security_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->channel_heartbeat_channel_n_o[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_last_seq_num[i] = wire[at++]; }
  record->end_of_channel = wire[at++];

  return at;
}

/* what was read of Channel Heartbeat is what was written, byte for byte */
static void equal_channel_heartbeat(const ChannelHeartbeat *read, const ChannelHeartbeat *written) {
  assert(read->channel_heartbeat_security_type == written->channel_heartbeat_security_type);
  for (size_t i = 0; i < 2; i++) { assert(read->channel_heartbeat_channel_n_o[i] == written->channel_heartbeat_channel_n_o[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_last_seq_num[i] == written->appl_last_seq_num[i]); }
  assert(read->end_of_channel == written->end_of_channel);
}

/* Channel Heartbeat: written and read back, then read and written back */
static void check_channel_heartbeat(void) {
  ChannelHeartbeat sent;
  ChannelHeartbeat got;
  uint8_t wire[12];
  uint8_t again[12];

  any_channel_heartbeat(&sent);
  assert(encode_channel_heartbeat(&sent, wire, 0) == 12);
  assert(decode_channel_heartbeat(&got, wire, 0) == 12);
  equal_channel_heartbeat(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_channel_heartbeat(&got, wire, 0) == 12);
  assert(encode_channel_heartbeat(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Message: 52 bytes ---------------------------------------- */

/* The retransmission message is used to request market data on a channel that supports retransmission. For application messages that can be retransmitted (all types of tick-by-tick market data messages), if application messages are missing, the user can send a retransmission message upstream, which represents a retransmission request. The upstream handles retransmission requests in a "request–reply" manner: it returns the data to be retransmitted according to the start and end sequence numbers specified in the retransmission message, and after the retransmission is complete it returns a retransmission message reporting that the retransmission is complete; if the retransmission fails, it returns a retransmission message reporting that the retransmission failed. The upstream system supports retransmission of only one message gap at a time; when the upstream receives multiple retransmission requests, it returns a retransmission failure for the other request messages. For tick-by-tick market data, the channel code and the message record number can be used to determine whether messages have been lost. When the message record number received is <= the largest message record number already received on this channel, the message has already been received and should be ignored. When the message record number received is > the largest message record number already received +1 (for example, the largest message record number received is 100 and the new message record number is 102), messages have been lost, and the lost data should be recovered by sending a retransmission request. */
typedef struct {
  uint8_t retransmission_message_channel_n_o[2];  /* bytes 0 to 1 */
  uint8_t resend_type;                            /* byte 2 */
  uint8_t appl_beg_seq_num[8];                    /* bytes 3 to 10 */
  uint8_t appl_end_seq_num[8];                    /* bytes 11 to 18 */
  uint8_t resend_status;                          /* byte 19 */
  uint8_t reject_text[32];                        /* bytes 20 to 51 */
} RetransmissionMessage;

/* any Retransmission Message at all: every byte one the checker chooses */
static void any_retransmission_message(RetransmissionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->retransmission_message_channel_n_o[i] = arbitrary(); }
  record->resend_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->appl_beg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_end_seq_num[i] = arbitrary(); }
  record->resend_status = arbitrary();
  for (size_t i = 0; i < 32; i++) { record->reject_text[i] = arbitrary(); }
}

/* Retransmission Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_message(const RetransmissionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->retransmission_message_channel_n_o[i]; }
  wire[at++] = record->resend_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_beg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_end_seq_num[i]; }
  wire[at++] = record->resend_status;
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->reject_text[i]; }

  return at;
}

/* Retransmission Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_message(RetransmissionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->retransmission_message_channel_n_o[i] = wire[at++]; }
  record->resend_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->appl_beg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_end_seq_num[i] = wire[at++]; }
  record->resend_status = wire[at++];
  for (size_t i = 0; i < 32; i++) { record->reject_text[i] = wire[at++]; }

  return at;
}

/* what was read of Retransmission Message is what was written, byte for byte */
static void equal_retransmission_message(const RetransmissionMessage *read, const RetransmissionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->retransmission_message_channel_n_o[i] == written->retransmission_message_channel_n_o[i]); }
  assert(read->resend_type == written->resend_type);
  for (size_t i = 0; i < 8; i++) { assert(read->appl_beg_seq_num[i] == written->appl_beg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_end_seq_num[i] == written->appl_end_seq_num[i]); }
  assert(read->resend_status == written->resend_status);
  for (size_t i = 0; i < 32; i++) { assert(read->reject_text[i] == written->reject_text[i]); }
}

/* Retransmission Message: written and read back, then read and written back */
static void check_retransmission_message(void) {
  RetransmissionMessage sent;
  RetransmissionMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_retransmission_message(&sent);
  assert(encode_retransmission_message(&sent, wire, 0) == 52);
  assert(decode_retransmission_message(&got, wire, 0) == 52);
  equal_retransmission_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_message(&got, wire, 0) == 52);
  assert(encode_retransmission_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Status Message: 14 bytes ----------------------------------------- */

/* The market status message is used by the exchange to publish information such as the market status and the number of products. It is published periodically and when the market status changes. */
typedef struct {
  uint8_t market_status_message_security_type;  /* byte 0 */
  uint8_t trad_ses_mode;                        /* byte 1 */
  uint8_t trading_session_i_d[8];               /* bytes 2 to 9 */
  uint8_t tot_no_related_sym[4];                /* bytes 10 to 13 */
} MarketStatusMessage;

/* any Market Status Message at all: every byte one the checker chooses */
static void any_market_status_message(MarketStatusMessage *record) {
  record->market_status_message_security_type = arbitrary();
  record->trad_ses_mode = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trading_session_i_d[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tot_no_related_sym[i] = arbitrary(); }
}

/* Market Status Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_market_status_message(const MarketStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_status_message_security_type;
  wire[at++] = record->trad_ses_mode;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_session_i_d[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tot_no_related_sym[i]; }

  return at;
}

/* Market Status Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_market_status_message(MarketStatusMessage *record, const uint8_t *wire, size_t at) {
  record->market_status_message_security_type = wire[at++];
  record->trad_ses_mode = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trading_session_i_d[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tot_no_related_sym[i] = wire[at++]; }

  return at;
}

/* what was read of Market Status Message is what was written, byte for byte */
static void equal_market_status_message(const MarketStatusMessage *read, const MarketStatusMessage *written) {
  assert(read->market_status_message_security_type == written->market_status_message_security_type);
  assert(read->trad_ses_mode == written->trad_ses_mode);
  for (size_t i = 0; i < 8; i++) { assert(read->trading_session_i_d[i] == written->trading_session_i_d[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tot_no_related_sym[i] == written->tot_no_related_sym[i]); }
}

/* Market Status Message: written and read back, then read and written back */
static void check_market_status_message(void) {
  MarketStatusMessage sent;
  MarketStatusMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_market_status_message(&sent);
  assert(encode_market_status_message(&sent, wire, 0) == 14);
  assert(decode_market_status_message(&got, wire, 0) == 14);
  equal_market_status_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_market_status_message(&got, wire, 0) == 14);
  assert(encode_market_status_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick-by-Tick Order Market Data Extension Fields: 139 bytes -------------- */

typedef struct {
  uint8_t side;                                                                   /* byte 0 */
  uint8_t quote_i_d[18];                                                          /* bytes 1 to 18 */
  uint8_t member_i_d[12];                                                         /* bytes 19 to 30 */
  uint8_t trader_code[12];                                                        /* bytes 31 to 42 */
  uint8_t full_amount_trade;                                                      /* byte 43 */
  uint8_t settl_type;                                                             /* byte 44 */
  uint8_t contract_multiplier[4];                                                 /* bytes 45 to 48 */
  uint8_t expiration_days[2];                                                     /* bytes 49 to 50 */
  uint8_t tick_by_tick_order_market_data_extension_fields_total_value_traded[8];  /* bytes 51 to 58 */
  uint8_t basket_i_d[16];                                                         /* bytes 59 to 74 */
  uint8_t investor_name[32];                                                      /* bytes 75 to 106 */
  uint8_t bid_trans_type;                                                         /* byte 107 */
  uint8_t bid_exec_inst_type;                                                     /* byte 108 */
  uint8_t expire_date[4];                                                         /* bytes 109 to 112 */
  uint8_t secondary_order_i_d[18];                                                /* bytes 113 to 130 */
  uint8_t min_qty[8];                                                             /* bytes 131 to 138 */
} Tick_by_TickOrderMarketDataExtensionFields;

/* any Tick-by-Tick Order Market Data Extension Fields at all: every byte one the checker chooses */
static void any_tick_by_tick_order_market_data_extension_fields(Tick_by_TickOrderMarketDataExtensionFields *record) {
  record->side = arbitrary();
  for (size_t i = 0; i < 18; i++) { record->quote_i_d[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->member_i_d[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->trader_code[i] = arbitrary(); }
  record->full_amount_trade = arbitrary();
  record->settl_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->contract_multiplier[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tick_by_tick_order_market_data_extension_fields_total_value_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->basket_i_d[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->investor_name[i] = arbitrary(); }
  record->bid_trans_type = arbitrary();
  record->bid_exec_inst_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->secondary_order_i_d[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_qty[i] = arbitrary(); }
}

/* Tick-by-Tick Order Market Data Extension Fields to the wire: 139 bytes from at, returning where the next byte goes */
static size_t encode_tick_by_tick_order_market_data_extension_fields(const Tick_by_TickOrderMarketDataExtensionFields *record, uint8_t *wire, size_t at) {
  wire[at++] = record->side;
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->quote_i_d[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->member_i_d[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trader_code[i]; }
  wire[at++] = record->full_amount_trade;
  wire[at++] = record->settl_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_multiplier[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiration_days[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick_by_tick_order_market_data_extension_fields_total_value_traded[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->basket_i_d[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->investor_name[i]; }
  wire[at++] = record->bid_trans_type;
  wire[at++] = record->bid_exec_inst_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expire_date[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->secondary_order_i_d[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_qty[i]; }

  return at;
}

/* Tick-by-Tick Order Market Data Extension Fields off the wire: 139 bytes from at, returning where the next byte lies */
static size_t decode_tick_by_tick_order_market_data_extension_fields(Tick_by_TickOrderMarketDataExtensionFields *record, const uint8_t *wire, size_t at) {
  record->side = wire[at++];
  for (size_t i = 0; i < 18; i++) { record->quote_i_d[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->member_i_d[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->trader_code[i] = wire[at++]; }
  record->full_amount_trade = wire[at++];
  record->settl_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->contract_multiplier[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tick_by_tick_order_market_data_extension_fields_total_value_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->basket_i_d[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->investor_name[i] = wire[at++]; }
  record->bid_trans_type = wire[at++];
  record->bid_exec_inst_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->secondary_order_i_d[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_qty[i] = wire[at++]; }

  return at;
}

/* what was read of Tick-by-Tick Order Market Data Extension Fields is what was written, byte for byte */
static void equal_tick_by_tick_order_market_data_extension_fields(const Tick_by_TickOrderMarketDataExtensionFields *read, const Tick_by_TickOrderMarketDataExtensionFields *written) {
  assert(read->side == written->side);
  for (size_t i = 0; i < 18; i++) { assert(read->quote_i_d[i] == written->quote_i_d[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->member_i_d[i] == written->member_i_d[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->trader_code[i] == written->trader_code[i]); }
  assert(read->full_amount_trade == written->full_amount_trade);
  assert(read->settl_type == written->settl_type);
  for (size_t i = 0; i < 4; i++) { assert(read->contract_multiplier[i] == written->contract_multiplier[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expiration_days[i] == written->expiration_days[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tick_by_tick_order_market_data_extension_fields_total_value_traded[i] == written->tick_by_tick_order_market_data_extension_fields_total_value_traded[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->basket_i_d[i] == written->basket_i_d[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->investor_name[i] == written->investor_name[i]); }
  assert(read->bid_trans_type == written->bid_trans_type);
  assert(read->bid_exec_inst_type == written->bid_exec_inst_type);
  for (size_t i = 0; i < 4; i++) { assert(read->expire_date[i] == written->expire_date[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->secondary_order_i_d[i] == written->secondary_order_i_d[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
}

/* Tick-by-Tick Order Market Data Extension Fields: written and read back, then read and written back */
static void check_tick_by_tick_order_market_data_extension_fields(void) {
  Tick_by_TickOrderMarketDataExtensionFields sent;
  Tick_by_TickOrderMarketDataExtensionFields got;
  uint8_t wire[139];
  uint8_t again[139];

  any_tick_by_tick_order_market_data_extension_fields(&sent);
  assert(encode_tick_by_tick_order_market_data_extension_fields(&sent, wire, 0) == 139);
  assert(decode_tick_by_tick_order_market_data_extension_fields(&got, wire, 0) == 139);
  equal_tick_by_tick_order_market_data_extension_fields(&got, &sent);

  for (size_t i = 0; i < 139; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_by_tick_order_market_data_extension_fields(&got, wire, 0) == 139);
  assert(encode_tick_by_tick_order_market_data_extension_fields(&got, again, 0) == 139);
  for (size_t i = 0; i < 139; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick-by-Tick Trade Market Data Extension Fields: 53 bytes --------------- */

typedef struct {
  uint8_t bid_appl_seq_num[18];                                                   /* bytes 0 to 17 */
  uint8_t offer_appl_seq_num[18];                                                 /* bytes 18 to 35 */
  uint8_t tick_by_tick_trade_market_data_extension_fields_total_value_traded[8];  /* bytes 36 to 43 */
  uint8_t trade_method;                                                           /* byte 44 */
  uint8_t margin_price[8];                                                        /* bytes 45 to 52 */
} Tick_by_TickTradeMarketDataExtensionFields;

/* any Tick-by-Tick Trade Market Data Extension Fields at all: every byte one the checker chooses */
static void any_tick_by_tick_trade_market_data_extension_fields(Tick_by_TickTradeMarketDataExtensionFields *record) {
  for (size_t i = 0; i < 18; i++) { record->bid_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->offer_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tick_by_tick_trade_market_data_extension_fields_total_value_traded[i] = arbitrary(); }
  record->trade_method = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->margin_price[i] = arbitrary(); }
}

/* Tick-by-Tick Trade Market Data Extension Fields to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_tick_by_tick_trade_market_data_extension_fields(const Tick_by_TickTradeMarketDataExtensionFields *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->bid_appl_seq_num[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->offer_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick_by_tick_trade_market_data_extension_fields_total_value_traded[i]; }
  wire[at++] = record->trade_method;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->margin_price[i]; }

  return at;
}

/* Tick-by-Tick Trade Market Data Extension Fields off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_tick_by_tick_trade_market_data_extension_fields(Tick_by_TickTradeMarketDataExtensionFields *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 18; i++) { record->bid_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->offer_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tick_by_tick_trade_market_data_extension_fields_total_value_traded[i] = wire[at++]; }
  record->trade_method = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->margin_price[i] = wire[at++]; }

  return at;
}

/* what was read of Tick-by-Tick Trade Market Data Extension Fields is what was written, byte for byte */
static void equal_tick_by_tick_trade_market_data_extension_fields(const Tick_by_TickTradeMarketDataExtensionFields *read, const Tick_by_TickTradeMarketDataExtensionFields *written) {
  for (size_t i = 0; i < 18; i++) { assert(read->bid_appl_seq_num[i] == written->bid_appl_seq_num[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->offer_appl_seq_num[i] == written->offer_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tick_by_tick_trade_market_data_extension_fields_total_value_traded[i] == written->tick_by_tick_trade_market_data_extension_fields_total_value_traded[i]); }
  assert(read->trade_method == written->trade_method);
  for (size_t i = 0; i < 8; i++) { assert(read->margin_price[i] == written->margin_price[i]); }
}

/* Tick-by-Tick Trade Market Data Extension Fields: written and read back, then read and written back */
static void check_tick_by_tick_trade_market_data_extension_fields(void) {
  Tick_by_TickTradeMarketDataExtensionFields sent;
  Tick_by_TickTradeMarketDataExtensionFields got;
  uint8_t wire[53];
  uint8_t again[53];

  any_tick_by_tick_trade_market_data_extension_fields(&sent);
  assert(encode_tick_by_tick_trade_market_data_extension_fields(&sent, wire, 0) == 53);
  assert(decode_tick_by_tick_trade_market_data_extension_fields(&got, wire, 0) == 53);
  equal_tick_by_tick_trade_market_data_extension_fields(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_by_tick_trade_market_data_extension_fields(&got, wire, 0) == 53);
  assert(encode_tick_by_tick_trade_market_data_extension_fields(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- Standard Trailer: 4 bytes ----------------------------------------------- */

/* The checksum is calculated from the start of the message header (header included) to the end of the message body. See Appendix 1 "Calculating the checksum" for sample code. */
typedef struct {
  uint8_t check_sum[4];  /* bytes 0 to 3 */
} StandardTrailer;

/* any Standard Trailer at all: every byte one the checker chooses */
static void any_standard_trailer(StandardTrailer *record) {
  for (size_t i = 0; i < 4; i++) { record->check_sum[i] = arbitrary(); }
}

/* Standard Trailer to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_standard_trailer(const StandardTrailer *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->check_sum[i]; }

  return at;
}

/* Standard Trailer off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_standard_trailer(StandardTrailer *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->check_sum[i] = wire[at++]; }

  return at;
}

/* what was read of Standard Trailer is what was written, byte for byte */
static void equal_standard_trailer(const StandardTrailer *read, const StandardTrailer *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->check_sum[i] == written->check_sum[i]); }
}

/* Standard Trailer: written and read back, then read and written back */
static void check_standard_trailer(void) {
  StandardTrailer sent;
  StandardTrailer got;
  uint8_t wire[4];
  uint8_t again[4];

  any_standard_trailer(&sent);
  assert(encode_standard_trailer(&sent, wire, 0) == 4);
  assert(decode_standard_trailer(&got, wire, 0) == 4);
  equal_standard_trailer(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_standard_trailer(&got, wire, 0) == 4);
  assert(encode_standard_trailer(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_standard_header();
  check_logon_message();
  check_logout_message();
  check_channel_heartbeat();
  check_retransmission_message();
  check_market_status_message();
  check_tick_by_tick_order_market_data_extension_fields();
  check_tick_by_tick_trade_market_data_extension_fields();
  check_standard_trailer();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
