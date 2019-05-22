/* SPDX-License-Identifier: LGPL-2.1+ */
#pragma once

typedef struct IPoIB IPoIB;

#include "netdev/netdev.h"

typedef enum {
        NETDEV_IPOIB_MODE_DATAGRAM  = IPOIB_MODE_DATAGRAM,
        NETDEV_IPOIB_MODE_CONNECTED = IPOIB_MODE_CONNECTED,
        _NETDEV_IPOIB_MODE_MAX,
        _NETDEV_IPOIB_MODE_INVALID  = -1
} IPoIBMode;

struct IPoIB {
        NetDev meta;

        IPoIBMode mode;
        int umcast;
        uint16_t pkey;
};

DEFINE_NETDEV_CAST(IPOIB, IPoIB);

extern const NetDevVTable ipoib_vtable;

CONFIG_PARSER_PROTOTYPE(config_parse_ipoib_mode);
