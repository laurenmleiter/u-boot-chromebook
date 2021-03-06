/*
 * (C) Copyright 2002-2010
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef	__ASM_GBL_DATA_H
#define __ASM_GBL_DATA_H

#ifdef CONFIG_SYS_GENERIC_BOARD
/* Use the generic board which requires a unified global_data */
#include <asm-generic/global_data.h>
#else
/*
 * The following data structure is placed in some memory wich is
 * available very early after boot (like DPRAM on MPC8xx/MPC82xx, or
 * some locked parts of the data cache) to allow for a minimum set of
 * global variables during system initialization (until we have set
 * up the memory controller so that we can use RAM).
 *
 * Keep it *SMALL* and remember to set GENERATED_GBL_DATA_SIZE > sizeof(gd_t)
 */

#ifndef __ASSEMBLY__

#include <asm/u-boot.h>

typedef	struct global_data {
	bd_t		*bd;
	unsigned long	flags;
	unsigned long	baudrate;
	unsigned long	have_console;	/* serial_init() was called */
#ifdef CONFIG_PRE_CONSOLE_BUFFER
	unsigned long	precon_buf_idx;	/* Pre-Console buffer index */
#endif
	unsigned long	reloc_off;	/* Relocation Offset */
	unsigned long	load_off;	/* Load Offset */
	unsigned long	env_addr;	/* Address  of Environment struct */
	unsigned long	env_valid;	/* Checksum of Environment valid? */
	unsigned long	cpu_clk;	/* CPU clock in Hz!		*/
	unsigned long	bus_clk;
	unsigned long	relocaddr;	/* Start address of U-Boot in RAM */
	unsigned long	start_addr_sp;	/* start_addr_stackpointer */
	phys_size_t	ram_size;	/* RAM size */
	unsigned long	reset_status;	/* reset status register at boot */
	const void	*fdt_blob;	/* Our device tree, NULL if none */
	void		**jt;		/* jump table */
	char		env_buf[32];	/* buffer for getenv() before reloc. */
} gd_t;

extern gd_t *gd;

#endif

/*
 * Global Data Flags
 */
#define	GD_FLG_RELOC		0x00001	/* Code was relocated to RAM		*/
#define	GD_FLG_DEVINIT		0x00002	/* Devices have been initialized	*/
#define	GD_FLG_SILENT		0x00004	/* Silent mode				*/
#define	GD_FLG_POSTFAIL		0x00008	/* Critical POST test failed		*/
#define	GD_FLG_POSTSTOP		0x00010	/* POST seqeunce aborted		*/
#define	GD_FLG_LOGINIT		0x00020	/* Log Buffer has been initialized	*/
#define GD_FLG_DISABLE_CONSOLE	0x00040	/* Disable console (in & out)		*/
#define GD_FLG_ENV_READY	0x00080	/* Environment imported into hash table	*/
#define GD_FLG_COLD_BOOT	0x00100	/* Cold Boot */
#define GD_FLG_WARM_BOOT	0x00200	/* Warm Boot */

#endif /* nCONFIG_SYS_GENERIC_BOARD */

#if 0

#define DECLARE_GLOBAL_DATA_PTR
#else
#define XTRN_DECLARE_GLOBAL_DATA_PTR    extern
#define DECLARE_GLOBAL_DATA_PTR     XTRN_DECLARE_GLOBAL_DATA_PTR \
gd_t *gd
#endif

#endif /* __ASM_GBL_DATA_H */
