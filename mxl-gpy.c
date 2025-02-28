// SPDX-License-Identifier: GPL-2.0+
#include <phy.h>
#include <linux/bitfield.h>

/* PHY ID */
#define PHY_ID_GPY211C		0x67C9DE10


static int gpy211_probe(struct phy_device *phydev)
{
	phydev->flags |= PHY_FLAG_BROKEN_RESET;
	return 0;
}

static int gpy211_config(struct phy_device *phydev)
{
	phy_write_mmd(phydev, MDIO_MMD_VEND1, 8, 0xa4fa);
	debug("\n\n\n\n GPY211 CONFIGURATO \n\n\n\n");
	return 0;
}

static int gpy211_startup(struct phy_device *phydev)
{
	int ret;

	ret = genphy_update_link(phydev);
	if (ret)
		return ret;

	phydev->speed = SPEED_1000;
	phydev->duplex = DUPLEX_FULL;

	return 0;
}



U_BOOT_PHY_DRIVER(mxl_gpy) = {
	.name = "MaxLinear/Intel GPY211C 10/100/1000/2500Mbps Ethernet",
	.uid = PHY_ID_GPY211C,
	.mask = 0xffffff00,
	.features = PHY_GBIT_FEATURES,
	.probe = &gpy211_probe,
	.config = &gpy211_config,
	.startup = &gpy211_startup,
	.shutdown = &genphy_shutdown,
};