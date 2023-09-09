#ifndef __CONFIG_M8B_ONECLOUD_H__
#define __CONFIG_M8B_ONECLOUD_H__



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                 UART Sectoion
// =============================================================================
#define CONFIG_CONS_INDEX	(2)
// =============================================================================



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 ACS: DDR controller and system PLLs settings
// =============================================================================
#define CONFIG_ACS
#ifdef CONFIG_ACS
	// Pass memory size from spl to uboot
	#define CONFIG_DDR_SIZE_IND_ADDR	(0xD9000000)
#endif
// =============================================================================



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                 Security boot
// =============================================================================
#define CONFIG_AML_DISABLE_CRYPTO_UBOOT

// #define CONFIG_SECURITYKEY
// #define CONFIG_SECU_BOOT
// =============================================================================



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                             UCL data compression
// =============================================================================
#define CONFIG_UCL				1
#define CONFIG_SELF_COMPRESS
// =============================================================================



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                     Store
// =============================================================================
#define CONFIG_STORE_COMPATIBLE

#define CONFIG_SDIO_B		1
#define PORT_B_CARD_TYPE	(CARD_TYPE_SD)

#define CONFIG_SDIO_C		1
#define PORT_C_CARD_TYPE	(CARD_TYPE_MMC)
// =============================================================================



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                     eFuse
// =============================================================================
#define CONFIG_EFUSE			1
// #define CONFIG_MACHID_CHECK
// =============================================================================



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                 Video output
// =============================================================================
#define CONFIG_VIDEO_AML
#define CONFIG_VIDEO_AMLTVOUT
#define CONFIG_AML_HDMI_TX		1
#define CONFIG_OSD_SCALE_ENABLE
#define COLOR_BIT				24
#define CONFIG_AML_FONT

#if(COLOR_BIT == 16)
	#define LCD_BPP				(LCD_COLOR16)
#elif(COLOR_BIT == 24)
	#define LCD_BPP				(LCD_COLOR24)
#else
	#error "unsupported COLOR_BIT"
#endif

#define CONFIG_CMD_BMP
#define CONFIG_CMD_LOGO
// =============================================================================



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                   Commands
// =============================================================================
#define CONFIG_SYS_LONGHELP
#define CONFIG_AUTO_COMPLETE

#define CONFIG_CMD_AUTOSCRIPT
// #define CONFIG_CMD_BOOTD

#ifdef CONFIG_STORE_COMPATIBLE
	#define CONFIG_NEXT_NAND	// `store` sub-system
	#define CONFIG_CMD_IMGREAD
#endif
#define CONFIG_CMD_IMGPACK

#define CONFIG_CMD_CPU_TEMP

#define CONFIG_CMD_REBOOT
// =============================================================================



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                    Network
// =============================================================================
#define CONFIG_CMD_NET
#ifdef CONFIG_CMD_NET
	#define CONFIG_AML_ETHERNET
	#define CONFIG_NET_MULTI
	#define CONFIG_CMD_PING
	#define CONFIG_CMD_DHCP
	#define CONFIG_CMD_RARP
#endif
// =============================================================================



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                      USB
// =============================================================================
#define CONFIG_CMD_USB
#ifdef CONFIG_CMD_USB
	#define CONFIG_USB_DWC_OTG_HCD
	#define CONFIG_USB_DWC_OTG_294
	#define CONFIG_USB_STORAGE
#endif
// =============================================================================



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                   USB Burn
// =============================================================================
#ifdef CONFIG_STORE_COMPATIBLE
	#define CONFIG_AML_V2_USBTOOL
	#ifdef CONFIG_AML_V2_USBTOOL
		#define CONFIG_SHA1
	#endif
#endif
// =============================================================================



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                          FDT: Flattened Device Tree
// =============================================================================
#define CONFIG_OF_LIBFDT
// =============================================================================



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                     bootm
// =============================================================================
#define CONFIG_AML_GATE_INIT
#define CONFIG_SYS_BOOTMAPSZ	(PHYS_MEMORY_SIZE)	// Initial Memory map for Linux
#define CONFIG_ANDROID_IMG
// =============================================================================



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                             Environment variables
// =============================================================================
#define CONFIG_PREBOOT				"run prepare_video; run check_usbburn; print 'Waiting for autoboot...'"
#define CONFIG_BOOTDELAY			3
#define CONFIG_BOOTCOMMAND			"print 'Autobooting...'; run boot_emmc_armbian; print 'Failed to boot'; "
#define CONFIG_HOSTNAME				"onecloud"
#define CONFIG_ETHADDR				00:15:18:01:81:31
#define CONFIG_IPADDR				192.168.1.150
#define CONFIG_GATEWAYIP			192.168.1.254
#define CONFIG_NETMASK				255.255.255.0
#define CONFIG_SERVERIP				192.168.1.100
#define CONFIG_BOOTFILE				"uImage"
#if (COLOR_BIT == 16)
	#define ENV_VIDEO_COLOR \
		"display_color_format_index=16\0" \
		"display_bpp=16\0" \
		"display_color_fg=0xffff\0" \
		"display_color_bg=0\0"
#elif (COLOR_BIT == 24)
	#define ENV_VIDEO_COLOR \
		"display_color_format_index=24\0" \
		"display_bpp=24\0" \
		"display_color_fg=0xffffff\0" \
		"display_color_bg=0\0"
#else
	#error "unsupported COLOR_BIT"
#endif
#define CONFIG_EXTRA_ENV_SETTINGS \
	"outputmode=1080p\0" \
	"video_dev=tvout\0" \
	"display_width=1920\0" \
	"display_height=1080\0" \
	"display_layer=osd2\0" \
	ENV_VIDEO_COLOR \
	"fb_addr=0x15100000\0" \
	"fb_width=1280\0" \
	"fb_height=720\0" \
	"loadaddr_logo=0x13000000\0" \
	"prepare_video=" \
		"video open; " \
		"video clear; " \
		"video dev open ${outputmode}; " \
		"imgread pic resource bootup ${loadaddr_logo}; " \
		"bmp display ${bootup_offset}; " \
		"bmp scale; " \
		"set_fontsize 24; " \
		"setenv print_color 0xFFFFFF; " \
		"print 'U-Boot'; " \
		"\0" \
	\
	"check_usbburn=" \
		"print -n 'Checking USBBurn...'; " \
		"update 1000; " \
		"print 'Fail'; " \
		"\0" \
	\
	"loadaddr=0x12000000\0" \
	"boot_emmc_armbian=" \
		"print -n 'Try to boot from eMMC...'; " \
		"mmc rescan 1; " \
		"setenv bootdev 'mmc 1'; " \
		"fatload ${bootdev} ${loadaddr} boot.scr && autoscr ${loadaddr}; " \
		"print 'Fail'; " \
		"\0" \
	""
// =============================================================================



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                        Environment variables Storages
// =============================================================================
#define CONFIG_ENV_SIZE						(64*1024)
#define CONFIG_CMD_SAVEENV
#define CONFIG_ENV_OVERWRITE

#ifndef CONFIG_STORE_COMPATIBLE
	#define CONFIG_ENV_IS_IN_MMC
	#define CONFIG_SYS_MMC_ENV_DEV			(1)
	#define CONFIG_ENV_OFFSET				(0x800000)
#endif
// =============================================================================



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                      CPU
// =============================================================================
// CPU clock (unit: MHz)
// #define M8_CPU_CLK		(600)
#define M8_CPU_CLK			(792)
// #define M8_CPU_CLK		(996)
// #define M8_CPU_CLK		(1200)
#define CONFIG_SYS_CPU_CLK	(M8_CPU_CLK)

// Enable L1 cache
// to speed up uboot decompression
#define CONFIG_AML_SPL_L1_CACHE_ON	1

// Disable L2 cache
#define CONFIG_L2_OFF
// =============================================================================



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                      DDR
// =============================================================================
// Memory size
#define PHYS_MEMORY_START		(0x00000000)
#define PHYS_MEMORY_SIZE		(0x40000000)
#define CONFIG_DDR3_ROW_SIZE	(3)
#define CONFIG_DDR3_COL_SIZE	(2)
#define CONFIG_DDR_ROW_BITS		(15)

// Auto detect memory
#ifdef CONFIG_ACS
	#define CONFIG_DDR_MODE_AUTO_DETECT		// Auto detect DDR bus-width
	#define CONFIG_DDR_SIZE_AUTO_DETECT		// Auto detect DDR size
#endif

// Dump ddr info
#define CONFIG_DUMP_DDR_INFO

// DDR test
#define CONFIG_ENABLE_MEM_DEVICE_TEST
#define CONFIG_SYS_MEMTEST_START		0x10000000	// 256MB
#define CONFIG_SYS_MEMTEST_END			0x18000000	// 384MB

// DDR clock: 408~804MHz with fixed step 12MHz
// #define CFG_DDR_CLK		(636)
#define CFG_DDR_CLK			(696)
// #define CFG_DDR_CLK		(768)
// #define CFG_DDR_CLK		(792)
#define CFG_DDR_MODE		(CFG_DDR_32BIT)

// DDR features
// #define CONFIG_GATEACDDRCLK_DISABLE				// Disable DDR clock gating
// #define CONFIG_DDR_LOW_POWER_DISABLE				// Disable DDR low power feature
#define CONFIG_NO_DDR_PUB_VT_CHECK					// Not check the VT done flag when DDR PUB training
// #define CONFIG_PUB_WLWDRDRGLVTWDRDBVT_DISABLE	// Disable DDR PUB WL/WD/RD/RG-LVT, WD/RD-BVT
#define CONFIG_ENABLE_WRITE_LEVELING
// =============================================================================



#endif // __CONFIG_M8B_ONECLOUD_H__
