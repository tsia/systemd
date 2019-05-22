/* SPDX-License-Identifier: LGPL-2.1+ */

#include <linux/if_link.h>

#include "netdev/ipoib.h"
#include "string-table.h"

static const char* const ipoib_mode_table[_NETDEV_IPOIB_MODE_MAX] = {
        [NETDEV_IPOIB_MODE_DATAGRAM]  = "datagram",
        [NETDEV_IPOIB_MODE_CONNECTED] = "connected",
};

DEFINE_PRIVATE_STRING_TABLE_LOOKUP_FROM_STRING(ipoib_mode, IPoIBMode);
DEFINE_CONFIG_PARSE_ENUM(config_parse_ipoib_mode, ipoib_mode, IPoIBMode, "Failed to parse ipoib mode");

static int netdev_ipoib_fill_message_create(NetDev *netdev, Link *link, sd_netlink_message *m) {
        IPoIB *v;
        int r;

        assert(netdev);
        assert(m);

        v = IPOIB(netdev);

        assert(v);

        if (v->mode >= 0) {
                r = sd_netlink_message_append_u16(m, IFLA_IPOIB_MODE, v->mode);
                if (r < 0)
                        return log_error_errno(r, "Failed to append IFLA_IPOIB_MODE attribute: %m");
        }

        if (v->umcast >= 0) {
                r = sd_netlink_message_append_u16(m, IFLA_IPOIB_UMCAST, v->umcast);
                if (r < 0)
                        return log_error_errno(r, "Failed to append IFLA_IPOIB_UMCAST attribute: %m");
        }

        if (v->pkey > 0) {
                r = sd_netlink_message_append_u16(m, IFLA_IPOIB_PKEY, v->pkey);
                if (r < 0)
                        return log_error_errno(r, "Failed to append IFLA_IPOIB_PKEY attribute: %m");
        }

        return 0;
}

const NetDevVTable ipoib_vtable = {
        .object_size = sizeof(IPoIB),
        .sections = "Match\0NetDev\0IPoIB\0",
        .fill_message_create = netdev_ipoib_fill_message_create,
        .create_type = NETDEV_CREATE_INDEPENDENT,
};
