// nasdaq/mrxoptions/spreadtradefeed/MrxOptions_SpreadTradeFeed_v2_1_Server.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) MRX Options Spread Trade Feed
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
 *   - a length prefix framing what follows
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

/* ---- Server Packet Header: 3 bytes ------------------------------------------- */

/* Packet header of a packet sent by the server */
typedef struct {
  uint8_t packet_length[2];    /* bytes 0 to 1 */
  uint8_t server_packet_type;  /* byte 2 */
} ServerPacketHeader;

/* any Server Packet Header at all: every byte one the checker chooses */
static void any_server_packet_header(ServerPacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  record->server_packet_type = arbitrary();
}

/* Server Packet Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_server_packet_header(const ServerPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  wire[at++] = record->server_packet_type;

  return at;
}

/* Server Packet Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_server_packet_header(ServerPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  record->server_packet_type = wire[at++];

  return at;
}

/* what was read of Server Packet Header is what was written, byte for byte */
static void equal_server_packet_header(const ServerPacketHeader *read, const ServerPacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  assert(read->server_packet_type == written->server_packet_type);
}

/* Server Packet Header: written and read back, then read and written back */
static void check_server_packet_header(void) {
  ServerPacketHeader sent;
  ServerPacketHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_server_packet_header(&sent);
  assert(encode_server_packet_header(&sent, wire, 0) == 3);
  assert(decode_server_packet_header(&got, wire, 0) == 3);
  equal_server_packet_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_server_packet_header(&got, wire, 0) == 3);
  assert(encode_server_packet_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Accepted Packet: 30 bytes ----------------------------------------- */

/* The SoupBinTCP server sends a Login Accepted Packet in response to receiving a valid Login Request from the client */
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

/* The SoupBinTCP server sends this packet in response to an invalid Login Request Packet from the client */
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

/* ---- System Event Message: 11 bytes ------------------------------------------ */

/* The system event message type is used to signal a market or data feed handler event. */
typedef struct {
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t timestamp[8];        /* bytes 2 to 9 */
  uint8_t event_code;          /* byte 10 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->event_code == written->event_code);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 11);
  assert(decode_system_event_message(&got, wire, 0) == 11);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 11);
  assert(encode_system_event_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strategy Trading Action Message: 15 bytes ------------------------------- */

/* The options system uses this administrative message to indicate the current trading status of an index or equity option within the options market. */
typedef struct {
  uint8_t tracking_number[2];     /* bytes 0 to 1 */
  uint8_t timestamp[8];           /* bytes 2 to 9 */
  uint8_t strategy_id[4];         /* bytes 10 to 13 */
  uint8_t current_trading_state;  /* byte 14 */
} StrategyTradingActionMessage;

/* any Strategy Trading Action Message at all: every byte one the checker chooses */
static void any_strategy_trading_action_message(StrategyTradingActionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  record->current_trading_state = arbitrary();
}

/* Strategy Trading Action Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_strategy_trading_action_message(const StrategyTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  wire[at++] = record->current_trading_state;

  return at;
}

/* Strategy Trading Action Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_strategy_trading_action_message(StrategyTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  record->current_trading_state = wire[at++];

  return at;
}

/* what was read of Strategy Trading Action Message is what was written, byte for byte */
static void equal_strategy_trading_action_message(const StrategyTradingActionMessage *read, const StrategyTradingActionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  assert(read->current_trading_state == written->current_trading_state);
}

/* Strategy Trading Action Message: written and read back, then read and written back */
static void check_strategy_trading_action_message(void) {
  StrategyTradingActionMessage sent;
  StrategyTradingActionMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_strategy_trading_action_message(&sent);
  assert(encode_strategy_trading_action_message(&sent, wire, 0) == 15);
  assert(decode_strategy_trading_action_message(&got, wire, 0) == 15);
  equal_strategy_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_strategy_trading_action_message(&got, wire, 0) == 15);
  assert(encode_strategy_trading_action_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Strategy Trade Report: 43 bytes --------------------------------- */

/* The Complex Strategy Trade Report message is used to publish real-time trade information for complex strategies. */
typedef struct {
  uint8_t tracking_number[2];  /* bytes 0 to 1 */
  uint8_t timestamp[8];        /* bytes 2 to 9 */
  uint8_t strategy_id[4];      /* bytes 10 to 13 */
  uint8_t cross_id[4];         /* bytes 14 to 17 */
  uint8_t trade_condition;     /* byte 18 */
  uint8_t price[4];            /* bytes 19 to 22 */
  uint8_t volume[4];           /* bytes 23 to 26 */
  uint8_t reserved_16[16];     /* bytes 27 to 42 */
} ComplexStrategyTradeReport;

/* any Complex Strategy Trade Report at all: every byte one the checker chooses */
static void any_complex_strategy_trade_report(ComplexStrategyTradeReport *record) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  record->trade_condition = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Complex Strategy Trade Report to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_complex_strategy_trade_report(const ComplexStrategyTradeReport *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  wire[at++] = record->trade_condition;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Complex Strategy Trade Report off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_complex_strategy_trade_report(ComplexStrategyTradeReport *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->tracking_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  record->trade_condition = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Strategy Trade Report is what was written, byte for byte */
static void equal_complex_strategy_trade_report(const ComplexStrategyTradeReport *read, const ComplexStrategyTradeReport *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_number[i] == written->tracking_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  assert(read->trade_condition == written->trade_condition);
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Complex Strategy Trade Report: written and read back, then read and written back */
static void check_complex_strategy_trade_report(void) {
  ComplexStrategyTradeReport sent;
  ComplexStrategyTradeReport got;
  uint8_t wire[43];
  uint8_t again[43];

  any_complex_strategy_trade_report(&sent);
  assert(encode_complex_strategy_trade_report(&sent, wire, 0) == 43);
  assert(decode_complex_strategy_trade_report(&got, wire, 0) == 43);
  equal_complex_strategy_trade_report(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_strategy_trade_report(&got, wire, 0) == 43);
  assert(encode_complex_strategy_trade_report(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Replay Sequence Message: 20 bytes -------------------------------- */

/* The End of replay Sequence message reflects the sequence number at the time replay of existing messages is complete. */
typedef struct {
  uint8_t end_of_replay_sequence_number[20];  /* bytes 0 to 19 */
} EndOfReplaySequenceMessage;

/* any End Of Replay Sequence Message at all: every byte one the checker chooses */
static void any_end_of_replay_sequence_message(EndOfReplaySequenceMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->end_of_replay_sequence_number[i] = arbitrary(); }
}

/* End Of Replay Sequence Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_end_of_replay_sequence_message(const EndOfReplaySequenceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->end_of_replay_sequence_number[i]; }

  return at;
}

/* End Of Replay Sequence Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_end_of_replay_sequence_message(EndOfReplaySequenceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->end_of_replay_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Replay Sequence Message is what was written, byte for byte */
static void equal_end_of_replay_sequence_message(const EndOfReplaySequenceMessage *read, const EndOfReplaySequenceMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->end_of_replay_sequence_number[i] == written->end_of_replay_sequence_number[i]); }
}

/* End Of Replay Sequence Message: written and read back, then read and written back */
static void check_end_of_replay_sequence_message(void) {
  EndOfReplaySequenceMessage sent;
  EndOfReplaySequenceMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_end_of_replay_sequence_message(&sent);
  assert(encode_end_of_replay_sequence_message(&sent, wire, 0) == 20);
  assert(decode_end_of_replay_sequence_message(&got, wire, 0) == 20);
  equal_end_of_replay_sequence_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_replay_sequence_message(&got, wire, 0) == 20);
  assert(encode_end_of_replay_sequence_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_system_event_message();
  check_strategy_trading_action_message();
  check_complex_strategy_trade_report();
  check_end_of_replay_sequence_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
