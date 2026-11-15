// nasdaq/nomoptions/quoting/NomOptions_Quoting_v9_0_Client.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Specialized Quote Interface
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

/* ---- Client Packet Header: 3 bytes ------------------------------------------- */

/* Packet header of a packet sent by the client */
typedef struct {
  uint8_t packet_length[2];    /* bytes 0 to 1 */
  uint8_t client_packet_type;  /* byte 2 */
} ClientPacketHeader;

/* any Client Packet Header at all: every byte one the checker chooses */
static void any_client_packet_header(ClientPacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  record->client_packet_type = arbitrary();
}

/* Client Packet Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_client_packet_header(const ClientPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  wire[at++] = record->client_packet_type;

  return at;
}

/* Client Packet Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_client_packet_header(ClientPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  record->client_packet_type = wire[at++];

  return at;
}

/* what was read of Client Packet Header is what was written, byte for byte */
static void equal_client_packet_header(const ClientPacketHeader *read, const ClientPacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  assert(read->client_packet_type == written->client_packet_type);
}

/* Client Packet Header: written and read back, then read and written back */
static void check_client_packet_header(void) {
  ClientPacketHeader sent;
  ClientPacketHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_client_packet_header(&sent);
  assert(encode_client_packet_header(&sent, wire, 0) == 3);
  assert(decode_client_packet_header(&got, wire, 0) == 3);
  equal_client_packet_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_client_packet_header(&got, wire, 0) == 3);
  assert(encode_client_packet_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request Packet: 51 bytes ------------------------------------------ */

/* The SoupBinTCP client must send a Login Request Packet immediately upon establishing a new TCP/IP socket connection to the server */
typedef struct {
  uint8_t username[6];                    /* bytes 0 to 5 */
  uint8_t password[10];                   /* bytes 6 to 15 */
  uint8_t requested_session[10];          /* bytes 16 to 25 */
  uint8_t requested_sequence_number[20];  /* bytes 26 to 45 */
  uint8_t heartbeat_timeout[5];           /* bytes 46 to 50 */
} LoginRequestPacket;

/* any Login Request Packet at all: every byte one the checker chooses */
static void any_login_request_packet(LoginRequestPacket *record) {
  for (size_t i = 0; i < 6; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->requested_session[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->requested_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->heartbeat_timeout[i] = arbitrary(); }
}

/* Login Request Packet to the wire: 51 bytes from at, returning where the next byte goes */
static size_t encode_login_request_packet(const LoginRequestPacket *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->requested_session[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->requested_sequence_number[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->heartbeat_timeout[i]; }

  return at;
}

/* Login Request Packet off the wire: 51 bytes from at, returning where the next byte lies */
static size_t decode_login_request_packet(LoginRequestPacket *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->requested_session[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->requested_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->heartbeat_timeout[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request Packet is what was written, byte for byte */
static void equal_login_request_packet(const LoginRequestPacket *read, const LoginRequestPacket *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->requested_session[i] == written->requested_session[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->requested_sequence_number[i] == written->requested_sequence_number[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->heartbeat_timeout[i] == written->heartbeat_timeout[i]); }
}

/* Login Request Packet: written and read back, then read and written back */
static void check_login_request_packet(void) {
  LoginRequestPacket sent;
  LoginRequestPacket got;
  uint8_t wire[51];
  uint8_t again[51];

  any_login_request_packet(&sent);
  assert(encode_login_request_packet(&sent, wire, 0) == 51);
  assert(decode_login_request_packet(&got, wire, 0) == 51);
  equal_login_request_packet(&got, &sent);

  for (size_t i = 0; i < 51; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request_packet(&got, wire, 0) == 51);
  assert(encode_login_request_packet(&got, again, 0) == 51);
  for (size_t i = 0; i < 51; i++) { assert(again[i] == wire[i]); }
}

/* ---- Notification Subscription Request Message: 36 bytes --------------------- */

/* Modifies the set of optional notification types delivered on the current session. */
typedef struct {
  uint8_t badge[4];          /* bytes 0 to 3 */
  uint8_t message_id[8];     /* bytes 4 to 11 */
  uint8_t subscription[24];  /* bytes 12 to 35 */
} NotificationSubscriptionRequestMessage;

/* any Notification Subscription Request Message at all: every byte one the checker chooses */
static void any_notification_subscription_request_message(NotificationSubscriptionRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 24; i++) { record->subscription[i] = arbitrary(); }
}

/* Notification Subscription Request Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_notification_subscription_request_message(const NotificationSubscriptionRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 24; i++) { wire[at++] = record->subscription[i]; }

  return at;
}

/* Notification Subscription Request Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_notification_subscription_request_message(NotificationSubscriptionRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 24; i++) { record->subscription[i] = wire[at++]; }

  return at;
}

/* what was read of Notification Subscription Request Message is what was written, byte for byte */
static void equal_notification_subscription_request_message(const NotificationSubscriptionRequestMessage *read, const NotificationSubscriptionRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 24; i++) { assert(read->subscription[i] == written->subscription[i]); }
}

/* Notification Subscription Request Message: written and read back, then read and written back */
static void check_notification_subscription_request_message(void) {
  NotificationSubscriptionRequestMessage sent;
  NotificationSubscriptionRequestMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_notification_subscription_request_message(&sent);
  assert(encode_notification_subscription_request_message(&sent, wire, 0) == 36);
  assert(decode_notification_subscription_request_message(&got, wire, 0) == 36);
  equal_notification_subscription_request_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_notification_subscription_request_message(&got, wire, 0) == 36);
  assert(encode_notification_subscription_request_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mm Parameter Definition Request Message: 74 bytes ----------------------- */

/* Sets the Rapid Fire/Curtailment parameters (CumQty, Percentage, Delta, Vega and Interval) per underlying and instrument type. Rejected if the badge is configured for ActiveQP. */
typedef struct {
  uint8_t badge[4];         /* bytes 0 to 3 */
  uint8_t message_id[8];    /* bytes 4 to 11 */
  uint8_t instrument_type;  /* byte 12 */
  uint8_t underlying[13];   /* bytes 13 to 25 */
  uint8_t interval[2];      /* bytes 26 to 27 */
  uint8_t percentage[2];    /* bytes 28 to 29 */
  uint8_t cum_qty[4];       /* bytes 30 to 33 */
  uint8_t delta[4];         /* bytes 34 to 37 */
  uint8_t vega[4];          /* bytes 38 to 41 */
  uint8_t reserved_32[32];  /* bytes 42 to 73 */
} MmParameterDefinitionRequestMessage;

/* any Mm Parameter Definition Request Message at all: every byte one the checker chooses */
static void any_mm_parameter_definition_request_message(MmParameterDefinitionRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->underlying[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->interval[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->percentage[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->vega[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->reserved_32[i] = arbitrary(); }
}

/* Mm Parameter Definition Request Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_mm_parameter_definition_request_message(const MmParameterDefinitionRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->interval[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->percentage[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->vega[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->reserved_32[i]; }

  return at;
}

/* Mm Parameter Definition Request Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_mm_parameter_definition_request_message(MmParameterDefinitionRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->underlying[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->interval[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->percentage[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->vega[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->reserved_32[i] = wire[at++]; }

  return at;
}

/* what was read of Mm Parameter Definition Request Message is what was written, byte for byte */
static void equal_mm_parameter_definition_request_message(const MmParameterDefinitionRequestMessage *read, const MmParameterDefinitionRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 13; i++) { assert(read->underlying[i] == written->underlying[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->interval[i] == written->interval[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->percentage[i] == written->percentage[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->delta[i] == written->delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->vega[i] == written->vega[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->reserved_32[i] == written->reserved_32[i]); }
}

/* Mm Parameter Definition Request Message: written and read back, then read and written back */
static void check_mm_parameter_definition_request_message(void) {
  MmParameterDefinitionRequestMessage sent;
  MmParameterDefinitionRequestMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_mm_parameter_definition_request_message(&sent);
  assert(encode_mm_parameter_definition_request_message(&sent, wire, 0) == 74);
  assert(decode_mm_parameter_definition_request_message(&got, wire, 0) == 74);
  equal_mm_parameter_definition_request_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_mm_parameter_definition_request_message(&got, wire, 0) == 74);
  assert(encode_mm_parameter_definition_request_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Active Qp Self Replenishment Set Limit Message: 29 bytes ---------------- */

/* ActiveQP/Self-Replenishment Set Limit Message: sets the contract limit for self-replenishment purge. */
typedef struct {
  uint8_t badge[4];               /* bytes 0 to 3 */
  uint8_t message_id[8];          /* bytes 4 to 11 */
  uint8_t underlying_symbol[13];  /* bytes 12 to 24 */
  uint8_t set_value[4];           /* bytes 25 to 28 */
} ActiveQpSelfReplenishmentSetLimitMessage;

/* any Active Qp Self Replenishment Set Limit Message at all: every byte one the checker chooses */
static void any_active_qp_self_replenishment_set_limit_message(ActiveQpSelfReplenishmentSetLimitMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->set_value[i] = arbitrary(); }
}

/* Active Qp Self Replenishment Set Limit Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_active_qp_self_replenishment_set_limit_message(const ActiveQpSelfReplenishmentSetLimitMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->set_value[i]; }

  return at;
}

/* Active Qp Self Replenishment Set Limit Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_active_qp_self_replenishment_set_limit_message(ActiveQpSelfReplenishmentSetLimitMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->set_value[i] = wire[at++]; }

  return at;
}

/* what was read of Active Qp Self Replenishment Set Limit Message is what was written, byte for byte */
static void equal_active_qp_self_replenishment_set_limit_message(const ActiveQpSelfReplenishmentSetLimitMessage *read, const ActiveQpSelfReplenishmentSetLimitMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->set_value[i] == written->set_value[i]); }
}

/* Active Qp Self Replenishment Set Limit Message: written and read back, then read and written back */
static void check_active_qp_self_replenishment_set_limit_message(void) {
  ActiveQpSelfReplenishmentSetLimitMessage sent;
  ActiveQpSelfReplenishmentSetLimitMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_active_qp_self_replenishment_set_limit_message(&sent);
  assert(encode_active_qp_self_replenishment_set_limit_message(&sent, wire, 0) == 29);
  assert(decode_active_qp_self_replenishment_set_limit_message(&got, wire, 0) == 29);
  equal_active_qp_self_replenishment_set_limit_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_active_qp_self_replenishment_set_limit_message(&got, wire, 0) == 29);
  assert(encode_active_qp_self_replenishment_set_limit_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Rapid Fire Config Request Message: 25 bytes ----------------------------- */

/* Rapid Fire/Curtailment Config Request. Supported on Phlx, NOM and NTX; replaced by the MM Parameter Definition messages. */
typedef struct {
  uint8_t badge[4];               /* bytes 0 to 3 */
  uint8_t underlying_symbol[13];  /* bytes 4 to 16 */
  uint8_t percentage[2];          /* bytes 17 to 18 */
  uint8_t interval[2];            /* bytes 19 to 20 */
  uint8_t cum_qty[4];             /* bytes 21 to 24 */
} RapidFireConfigRequestMessage;

/* any Rapid Fire Config Request Message at all: every byte one the checker chooses */
static void any_rapid_fire_config_request_message(RapidFireConfigRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->percentage[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->interval[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
}

/* Rapid Fire Config Request Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_rapid_fire_config_request_message(const RapidFireConfigRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->percentage[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->interval[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }

  return at;
}

/* Rapid Fire Config Request Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_rapid_fire_config_request_message(RapidFireConfigRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->percentage[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->interval[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }

  return at;
}

/* what was read of Rapid Fire Config Request Message is what was written, byte for byte */
static void equal_rapid_fire_config_request_message(const RapidFireConfigRequestMessage *read, const RapidFireConfigRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->percentage[i] == written->percentage[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->interval[i] == written->interval[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
}

/* Rapid Fire Config Request Message: written and read back, then read and written back */
static void check_rapid_fire_config_request_message(void) {
  RapidFireConfigRequestMessage sent;
  RapidFireConfigRequestMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_rapid_fire_config_request_message(&sent);
  assert(encode_rapid_fire_config_request_message(&sent, wire, 0) == 25);
  assert(decode_rapid_fire_config_request_message(&got, wire, 0) == 25);
  equal_rapid_fire_config_request_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_rapid_fire_config_request_message(&got, wire, 0) == 25);
  assert(encode_rapid_fire_config_request_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Purge Request Message: 34 bytes ------------------------------ */

/* Underlying Purge Message including SentTimestamp: pulls all quotes for all options contracts of the specified underlying and inhibits new quotes until reentry. */
typedef struct {
  uint8_t badge[4];               /* bytes 0 to 3 */
  uint8_t message_id[8];          /* bytes 4 to 11 */
  uint8_t sent_timestamp[8];      /* bytes 12 to 19 */
  uint8_t underlying_symbol[13];  /* bytes 20 to 32 */
  uint8_t instrument_type;        /* byte 33 */
} UnderlyingPurgeRequestMessage;

/* any Underlying Purge Request Message at all: every byte one the checker chooses */
static void any_underlying_purge_request_message(UnderlyingPurgeRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sent_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
}

/* Underlying Purge Request Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_underlying_purge_request_message(const UnderlyingPurgeRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sent_timestamp[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->instrument_type;

  return at;
}

/* Underlying Purge Request Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_underlying_purge_request_message(UnderlyingPurgeRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sent_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];

  return at;
}

/* what was read of Underlying Purge Request Message is what was written, byte for byte */
static void equal_underlying_purge_request_message(const UnderlyingPurgeRequestMessage *read, const UnderlyingPurgeRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sent_timestamp[i] == written->sent_timestamp[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
}

/* Underlying Purge Request Message: written and read back, then read and written back */
static void check_underlying_purge_request_message(void) {
  UnderlyingPurgeRequestMessage sent;
  UnderlyingPurgeRequestMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_underlying_purge_request_message(&sent);
  assert(encode_underlying_purge_request_message(&sent, wire, 0) == 34);
  assert(decode_underlying_purge_request_message(&got, wire, 0) == 34);
  equal_underlying_purge_request_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_purge_request_message(&got, wire, 0) == 34);
  assert(encode_underlying_purge_request_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Reentry Request Message: 26 bytes -------------------------------- */

/* Market Reentry Message: resets risk protection previously triggered by a Rapid Fire/Curtailment event or a user Purge request. */
typedef struct {
  uint8_t badge[4];               /* bytes 0 to 3 */
  uint8_t message_id[8];          /* bytes 4 to 11 */
  uint8_t underlying_symbol[13];  /* bytes 12 to 24 */
  uint8_t instrument_type;        /* byte 25 */
} MarketReentryRequestMessage;

/* any Market Reentry Request Message at all: every byte one the checker chooses */
static void any_market_reentry_request_message(MarketReentryRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
}

/* Market Reentry Request Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_market_reentry_request_message(const MarketReentryRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->instrument_type;

  return at;
}

/* Market Reentry Request Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_market_reentry_request_message(MarketReentryRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];

  return at;
}

/* what was read of Market Reentry Request Message is what was written, byte for byte */
static void equal_market_reentry_request_message(const MarketReentryRequestMessage *read, const MarketReentryRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
}

/* Market Reentry Request Message: written and read back, then read and written back */
static void check_market_reentry_request_message(void) {
  MarketReentryRequestMessage sent;
  MarketReentryRequestMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_market_reentry_request_message(&sent);
  assert(encode_market_reentry_request_message(&sent, wire, 0) == 26);
  assert(decode_market_reentry_request_message(&got, wire, 0) == 26);
  equal_market_reentry_request_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_market_reentry_request_message(&got, wire, 0) == 26);
  assert(encode_market_reentry_request_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Active Qp Self Replenishment Request Reentry Message: 29 bytes ---------- */

/* ActiveQP/Self-Replenishment Request/Reentry Message: partial replenishment (removes a number of contracts from the Active QP counter) or full replenishment/reentry (value 0). */
typedef struct {
  uint8_t badge[4];                /* bytes 0 to 3 */
  uint8_t message_id[8];           /* bytes 4 to 11 */
  uint8_t underlying_symbol[13];   /* bytes 12 to 24 */
  uint8_t replenishment_value[4];  /* bytes 25 to 28 */
} ActiveQpSelfReplenishmentRequestReentryMessage;

/* any Active Qp Self Replenishment Request Reentry Message at all: every byte one the checker chooses */
static void any_active_qp_self_replenishment_request_reentry_message(ActiveQpSelfReplenishmentRequestReentryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->replenishment_value[i] = arbitrary(); }
}

/* Active Qp Self Replenishment Request Reentry Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_active_qp_self_replenishment_request_reentry_message(const ActiveQpSelfReplenishmentRequestReentryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->replenishment_value[i]; }

  return at;
}

/* Active Qp Self Replenishment Request Reentry Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_active_qp_self_replenishment_request_reentry_message(ActiveQpSelfReplenishmentRequestReentryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->replenishment_value[i] = wire[at++]; }

  return at;
}

/* what was read of Active Qp Self Replenishment Request Reentry Message is what was written, byte for byte */
static void equal_active_qp_self_replenishment_request_reentry_message(const ActiveQpSelfReplenishmentRequestReentryMessage *read, const ActiveQpSelfReplenishmentRequestReentryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->replenishment_value[i] == written->replenishment_value[i]); }
}

/* Active Qp Self Replenishment Request Reentry Message: written and read back, then read and written back */
static void check_active_qp_self_replenishment_request_reentry_message(void) {
  ActiveQpSelfReplenishmentRequestReentryMessage sent;
  ActiveQpSelfReplenishmentRequestReentryMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_active_qp_self_replenishment_request_reentry_message(&sent);
  assert(encode_active_qp_self_replenishment_request_reentry_message(&sent, wire, 0) == 29);
  assert(decode_active_qp_self_replenishment_request_reentry_message(&got, wire, 0) == 29);
  equal_active_qp_self_replenishment_request_reentry_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_active_qp_self_replenishment_request_reentry_message(&got, wire, 0) == 29);
  assert(encode_active_qp_self_replenishment_request_reentry_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Msar Request Message: 30 bytes ----------------------------------- */

/* SQF Market Sweep and Auction Response (MSAR) request for a simple instrument. A size of zero cancels a prior auction response for the same instrument/price/side. */
typedef struct {
  uint8_t badge[4];          /* bytes 0 to 3 */
  uint8_t message_id[8];     /* bytes 4 to 11 */
  uint8_t instrument_id[4];  /* bytes 12 to 15 */
  uint8_t msar_type;         /* byte 16 */
  uint8_t auction_id[4];     /* bytes 17 to 20 */
  uint8_t price[4];          /* bytes 21 to 24 */
  uint8_t side;              /* byte 25 */
  uint8_t contracts[4];      /* bytes 26 to 29 */
} SimpleMsarRequestMessage;

/* any Simple Msar Request Message at all: every byte one the checker chooses */
static void any_simple_msar_request_message(SimpleMsarRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->msar_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
}

/* Simple Msar Request Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_simple_msar_request_message(const SimpleMsarRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->msar_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }

  return at;
}

/* Simple Msar Request Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_simple_msar_request_message(SimpleMsarRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->msar_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Msar Request Message is what was written, byte for byte */
static void equal_simple_msar_request_message(const SimpleMsarRequestMessage *read, const SimpleMsarRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->msar_type == written->msar_type);
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
}

/* Simple Msar Request Message: written and read back, then read and written back */
static void check_simple_msar_request_message(void) {
  SimpleMsarRequestMessage sent;
  SimpleMsarRequestMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_simple_msar_request_message(&sent);
  assert(encode_simple_msar_request_message(&sent, wire, 0) == 30);
  assert(decode_simple_msar_request_message(&got, wire, 0) == 30);
  equal_simple_msar_request_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_msar_request_message(&got, wire, 0) == 30);
  assert(encode_simple_msar_request_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Msar Request Message: 36 bytes ---------------------------------- */

/* MSAR request for a complex instrument. Price cannot be negative; the Debit/Credit indicator gives the sign. */
typedef struct {
  uint8_t badge[4];          /* bytes 0 to 3 */
  uint8_t message_id[8];     /* bytes 4 to 11 */
  uint8_t instrument_id[4];  /* bytes 12 to 15 */
  uint8_t msar_type;         /* byte 16 */
  uint8_t auction_id[4];     /* bytes 17 to 20 */
  uint8_t price[4];          /* bytes 21 to 24 */
  uint8_t side;              /* byte 25 */
  uint8_t debit_credit;      /* byte 26 */
  uint8_t contracts[4];      /* bytes 27 to 30 */
  uint8_t price_protection;  /* byte 31 */
  uint8_t reserved_4[4];     /* bytes 32 to 35 */
} ComplexMsarRequestMessage;

/* any Complex Msar Request Message at all: every byte one the checker chooses */
static void any_complex_msar_request_message(ComplexMsarRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->msar_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->side = arbitrary();
  record->debit_credit = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
  record->price_protection = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Complex Msar Request Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_complex_msar_request_message(const ComplexMsarRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->badge[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->msar_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->side;
  wire[at++] = record->debit_credit;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }
  wire[at++] = record->price_protection;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Complex Msar Request Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_complex_msar_request_message(ComplexMsarRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->badge[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->msar_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->side = wire[at++];
  record->debit_credit = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }
  record->price_protection = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Msar Request Message is what was written, byte for byte */
static void equal_complex_msar_request_message(const ComplexMsarRequestMessage *read, const ComplexMsarRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->badge[i] == written->badge[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_id[i] == written->message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->msar_type == written->msar_type);
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->side == written->side);
  assert(read->debit_credit == written->debit_credit);
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
  assert(read->price_protection == written->price_protection);
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Complex Msar Request Message: written and read back, then read and written back */
static void check_complex_msar_request_message(void) {
  ComplexMsarRequestMessage sent;
  ComplexMsarRequestMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_complex_msar_request_message(&sent);
  assert(encode_complex_msar_request_message(&sent, wire, 0) == 36);
  assert(decode_complex_msar_request_message(&got, wire, 0) == 36);
  equal_complex_msar_request_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_msar_request_message(&got, wire, 0) == 36);
  assert(encode_complex_msar_request_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_client_packet_header();
  check_login_request_packet();
  check_notification_subscription_request_message();
  check_mm_parameter_definition_request_message();
  check_active_qp_self_replenishment_set_limit_message();
  check_rapid_fire_config_request_message();
  check_underlying_purge_request_message();
  check_market_reentry_request_message();
  check_active_qp_self_replenishment_request_reentry_message();
  check_simple_msar_request_message();
  check_complex_msar_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
