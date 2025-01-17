#include "st7789_240_135.h"

static const struct st7789_config lcd_config = {
    .spi      = spi1,
    .gpio_din = 11,
    .gpio_clk = 10,
    .gpio_cs  = 9,
    .gpio_dc  = 8,
    .gpio_rst = 12,
    .gpio_bl  = 13,
};

void st7789_240_135_initScreen(void) {
    // width and height only come into play for fills so let's just pass the memory size instead of LCD size
    st7789_init(&lcd_config, MEMORY_WIDTH, MEMORY_HEIGHT);
    st7789_fill(0x0000);
}

void st7789_240_135_handleFrameStart(uint8_t frame) {
    nearestNeighborHandleFrameStart();
}

void st7789_240_135_blit(uint16_t *downsampled_line, int scanline) {
    // st7789_fill(scanline % 2 == 0 ? 0x0000 : 0xffff);
    st7789_set_cursor((MEMORY_WIDTH - LCD_WIDTH) / 2 + SCREEN_WIDTH_OFFSET, (MEMORY_HEIGHT - LCD_HEIGHT) / 2 + (scanline));
    st7789_write(downsampled_line, DOWNSAMPLED_WIDTH*sizeof(uint16_t)); ///???
    
    // for debugging
    // for (uint16_t x = 0; x < DOWNSAMPLED_WIDTH; x++) {
        // st7789_put(downsampled_line[x]); 
    // }
}

void st7789_240_135_handleScanline(uint16_t *line, int scanline) {
    nearestNeighborHandleDownsampling(line, scanline, st7789_240_135_blit);
}