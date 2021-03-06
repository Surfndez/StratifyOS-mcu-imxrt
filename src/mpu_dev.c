/* Copyright 2011-2016 Tyler Gilbert; 
 * This file is part of Stratify OS.
 *
 * Stratify OS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Stratify OS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Stratify OS.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

#include <stdbool.h>
#include "cortexm/mpu.h"

//not used
int mpu_dev_init(){
	int err;


	err = mpu_enable_region(
				1,
				(void*)0x40000000,  //APB/AHB Peripherals
				0x60000000 - 0x40000000,
				MPU_ACCESS_PRW_UR,
				MPU_MEMORY_PERIPHERALS,
				false
				);

	if ( err < 0 ){
		return err;
	}


	/* make SEMC (i.e. external SDRAM, etc.) shared */
	err = mpu_enable_region(
				4,
				(void*)0x80000000,  //SEMC
				0x90000000 - 0x80000000, //NOTE: only 256MB of 1.5GB space is opened
				MPU_ACCESS_PRW_URW,
				MPU_MEMORY_PERIPHERALS,
				false
				);

	if ( err < 0 ){
		return err;
	}


	return 0;
}
