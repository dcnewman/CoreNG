// ASF 3.27.0

/**
 * \file
 *
 * \brief SPI master common service for SAM.
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
 /**
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef _SPI_MASTER_H_
#define _SPI_MASTER_H_

#include "compiler.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

//! Default Configuration of SPI Master Delay BCS
#ifndef CONFIG_SPI_MASTER_DELAY_BCS
#define CONFIG_SPI_MASTER_DELAY_BCS          0
#endif

//! Default Configuration of SPI Master Bits per Transfer Definition
#ifndef CONFIG_SPI_MASTER_BITS_PER_TRANSFER
#define CONFIG_SPI_MASTER_BITS_PER_TRANSFER  SPI_CSR_BITS_8_BIT
#endif

//! Default Configuration of SPI Master Delay BCT
#ifndef CONFIG_SPI_MASTER_DELAY_BCT
#define CONFIG_SPI_MASTER_DELAY_BCT          0
#endif

//! Default Configuration of SPI Master Delay BS
#ifndef CONFIG_SPI_MASTER_DELAY_BS
#define CONFIG_SPI_MASTER_DELAY_BS           0
#endif

//! Default Configuration of SPI Master Dummy Field
#ifndef CONFIG_SPI_MASTER_DUMMY
#define CONFIG_SPI_MASTER_DUMMY              0xFF
#endif
//! @}

#if defined(USE_SAM3X_DMAC)
#include "dmac.h"
#include "pmc.h"
#endif

/**
 * \brief Clock phase.
 */
#define SPI_CPHA  (1 << 0)

/**
 * \brief Clock polarity.
 */
#define SPI_CPOL  (1 << 1)

/**
 * \brief SPI mode 0.
 */
#define SPI_MODE_0  0
/**
 * \brief SPI mode 1.
 */
#define SPI_MODE_1  (SPI_CPHA)
/**
 * \brief SPI mode 2.
 */
#define SPI_MODE_2  (SPI_CPOL)
/**
 * \brief SPI mode 3.
 */
#define SPI_MODE_3  (SPI_CPOL | SPI_CPHA)

#ifndef SPI_TYPE_DEFS
#define SPI_TYPE_DEFS
//! SPI Flags Definition
typedef uint8_t spi_flags_t;

//! Board SPI Select Id Definition
typedef uint32_t board_spi_select_id_t;
#endif

//! \brief Polled SPI device definition.
struct spi_device {
	//! Board specific select id
	board_spi_select_id_t id;
	uint8_t cs;
	uint8_t bits;
};

void spi_set_peripheral_chip_select_value(Spi *p_spi, uint32_t ul_value);
void spi_set_delay_between_chip_select(Spi *p_spi, uint32_t ul_delay);
void spi_set_baudrate_div(Spi *p_spi, uint32_t ul_pcs_ch,
						  uint8_t uc_baudrate_divider);
void spi_set_transfer_delay(Spi *p_spi, uint32_t ul_pcs_ch,
							uint8_t uc_dlybs, uint8_t uc_dlybct);


/** \brief Initialize the SPI in master mode.
 *
 * \param p_spi Base address of the SPI instance.
 *
 */
extern void spi_master_init(Spi *p_spi, int ul_cs_pin, int ul_npcs_pin);

/**
 * \brief Set up an SPI device.
 *
 * The returned device descriptor structure must be passed to the driver
 * whenever that device should be used as current slave device.
 *
 * \param p_spi     Base address of the SPI instance.
 * \param device    Pointer to SPI device struct that should be initialized.
 * \param flags     SPI configuration flags. Common flags for all
 *                  implementations are the SPI modes SPI_MODE_0 ...
 *                  SPI_MODE_3.
 * \param baud_rate Baud rate for communication with slave device in Hz.
 * \param sel_id    Board specific select id.
 */
extern void spi_master_setup_device(Spi *p_spi, const struct spi_device *device,
		spi_flags_t flags, uint32_t baud_rate, board_spi_select_id_t sel_id);

/**
 * \brief Select the given device on the SPI bus.
 *
 * Set device specific setting and call board chip select.
 *
 * \param p_spi  Base address of the SPI instance.
 * \param device SPI device.
 *
 */
extern void spi_select_device(Spi *p_spi, const struct spi_device *device);

/**
 * \brief Deselect the given device on the SPI bus.
 *
 * Call board chip deselect.
 *
 * \param p_spi  Base address of the SPI instance.
 * \param device SPI device.
 *
 * \pre SPI device must be selected with spi_select_device() first.
 */
extern void spi_deselect_device(Spi *p_spi, const struct spi_device *device);

/**
 * \brief Send a sequence of bytes to an SPI device.
 *
 * Received bytes on the SPI bus are discarded.
 *
 * \param p_spi     Base address of the SPI instance.
 * \param data      Data buffer to write.
 * \param len       Length of data to be written.
 *
 * \pre SPI device must be selected with spi_select_device() first.
 */
extern spi_status_t spi_write_packet(Spi *p_spi, const uint8_t *data, size_t len);

/** \brief Get one data to a SPI peripheral.
 *
 * \param p_spi Base address of the SPI instance.
 * \return The data byte
 *
 */
static inline spi_status_t spi_get_timeout(Spi *p_spi, uint8_t *b)
{
	// wait for transmit register empty
	uint32_t timeout = SPI_TIMEOUT;
	while (!spi_is_tx_ready(p_spi)) {
		if (--timeout == 0) {
			return SPI_ERROR_TIMEOUT;
		}
	}

	// write dummy byte with address and end transmission flag
	p_spi->SPI_TDR = 0x000000FF | SPI_TDR_LASTXFER;

	// wait for receive register 
	timeout = SPI_TIMEOUT;
	while (!spi_is_rx_ready(p_spi)) {
		if (--timeout == 0) {
			return SPI_ERROR_TIMEOUT;
		}
	}

	// get byte from receive register
	*b = (uint8_t)p_spi->SPI_RDR;

	return SPI_OK;

	// return (p_spi->SPI_RDR & SPI_RDR_RD_Msk);
}

/** \brief Receive one byte from an SPI device.
 *
 * \param p_spi     Base address of the SPI instance.
 * \param data      Data to read.
 *
 */
#define spi_read_single(p,d) spi_get_timeout(p,d)
//static inline spi_status_t spi_read_single(Spi *p_spi, uint8_t *data)
//{
//	return spi_get(p_spi, data);
//}

/**
 * \brief Receive a sequence of bytes from an SPI device.
 *
 * All bytes sent out on SPI bus are sent as value 0xff.
 *
 * \param p_spi     Base address of the SPI instance.
 * \param data      Data buffer to read.
 * \param len       Length of data to be read.
 *
 * \pre SPI device must be selected with spi_select_device() first.
 */
extern spi_status_t spi_read_packet(Spi *p_spi, uint8_t *data, size_t len);

/**
 * \brief Put one data to a SPI peripheral.
 *
 * \param p_spi Base address of the SPI instance.
 * \param data The data byte to be loaded
 *
 */
static inline spi_status_t spi_put_timeout(Spi *p_spi, uint8_t data)
{
	// p_spi->SPI_TDR = SPI_TDR_TD(data);

	// wait for transmit register empty
	uint32_t timeout = SPI_TIMEOUT;
	while (!spi_is_tx_ready(p_spi)) {
		if (!timeout--)
		{
			return SPI_ERROR_TIMEOUT;
		}
	}

	// write byte with address and end transmission flag
 	p_spi->SPI_TDR = (uint32_t)data | SPI_TDR_LASTXFER;

	// wait for receive register 
	timeout = SPI_TIMEOUT;
	while (!spi_is_rx_ready(p_spi)) {
		if (--timeout == 0) {
			return SPI_ERROR_TIMEOUT;
		}
	}

	// clear status
	p_spi->SPI_RDR;

	return SPI_OK;
}


/** \brief Write one byte to an SPI device.
 *
 * \param p_spi     Base address of the SPI instance.
 * \param data      Data to write.
 *
 */
#define spi_write_single(p,d) spi_put_timeout(p,d)
//static inline status_code_t spi_write_single(Spi *p_spi, uint8_t data)
//{
//        return spi_put(p_spi, (uint16_t)data);
//}

#if defined(USE_SAM3X_DMAC)

#define SPI_TX_IDX 1 // DMAC HW interface id for SPI TX (Table 22-2. DMA Controller)
#define SPI_RX_IDX 2 // DMAC HW interface id for SPI RX (Table 22-2. DMA Controller)

void spi_start_transmit_dma(Dmac *p_dmac, Spi *p_spi, uint32_t ul_num,
							const void *src, uint32_t nb_bytes);

void spi_start_receive_dma(Dmac *p_dmac, Spi *p_spi, uint32_t ul_num,
						   const void *dest, uint32_t nb_bytes);

static inline uint32_t spi_get_peripheral_chip_select_value(Spi *p_spi)
{
	// return 3 & ((p_spi->SPI_MR & SPI_MR_PCS_Msk) >> SPI_MR_PCS_Pos);
	return 3 & (p_spi->SPI_MR >> SPI_MR_PCS_Pos);
}

static inline uint32_t spi_get_clock_divisor(Spi *p_spi)
{
	uint32_t ul_pcs_ch = spi_get_peripheral_chip_select_value(p_spi);
	if (ul_pcs_ch > 3) return 255;
	return (p_spi->SPI_CSR[ul_pcs_ch] & SPI_CSR_SCBR_Msk) >> SPI_CSR_SCBR_Pos;
}

#endif

#ifdef __cplusplus
}
#endif

#endif // _SPI_MASTER_H_
