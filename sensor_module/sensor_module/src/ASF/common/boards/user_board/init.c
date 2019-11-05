/**
 * \file
 *
 * \brief User board initialization template
 *
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

static void basic_io_test_init(void)
{
	// Initiera io-portar.
	DDRA = 0x00; // Alla pinnar på A är input.
	__asm__ __volatile__ ("nop");
}

void board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	basic_io_test_init();
}
