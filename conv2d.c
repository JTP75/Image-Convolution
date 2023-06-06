#pragma once

#include <stdint.h>

// 3x3 kernel
#define KERNEL_SIZE 3

uint8_t *convolve_base(uint8_t *mat, size_t r_mat, size_t c_mat, int8_t *kernel) {
    
    uint8_t* result = (uint8_t*)calloc(r_mat*c_mat, sizeof(uint8_t));
    uint8_t* line_buffer = (uint8_t*)calloc((KERNEL_SIZE-1)*(c_mat-KERNEL_SIZE), sizeof(uint8_t));
    uint8_t* kernel_buffer = (uint8_t*)calloc(KERNEL_SIZE*KERNEL_SIZE, sizeof(int8_t));
    int16_t rslt;

	for (size_t i = 0; i < r_mat*c_mat; ++i) {

        // rotate buffers
		for (size_t rk=0; rk<KERNEL_SIZE; rk++) {
			for (size_t ck=0; ck<KERNEL_SIZE-1; ck++) {
				kernel_buffer[rk*KERNEL_SIZE+ck] = kernel_buffer[rk*KERNEL_SIZE+ck+1];
			}
			if (rk < KERNEL_SIZE-1) {
				kernel_buffer[rk*KERNEL_SIZE+KERNEL_SIZE-1] = line_buffer[rk*(KERNEL_SIZE-1)];
				for (size_t cl=0; cl<c_mat-KERNEL_SIZE-1; cl++) {
					line_buffer[rk*(KERNEL_SIZE-1)+cl] = line_buffer[rk*(KERNEL_SIZE-1)+cl+1];
				}
				line_buffer[rk*(KERNEL_SIZE-1)+c_mat-KERNEL_SIZE-1] = kernel_buffer[(rk+1)*KERNEL_SIZE];
			}
		}
		kernel_buffer[KERNEL_SIZE*KERNEL_SIZE-1] = mat[i];

        // compute convolution
		rslt = 0;
		for (int k=0; k<KERNEL_SIZE*KERNEL_SIZE; k++) {
			rslt += kernel_buffer[k] * kernel[k];
		}
        // filter result
		rslt=rslt>>4;
		if (rslt<0)
			rslt = 0;
		else if (rslt>0xFF)
			rslt=0xFF;
		result[i] = (uint8_t)rslt;

	}

    free(line_buffer);
    free(kernel_buffer);

    return result;
}