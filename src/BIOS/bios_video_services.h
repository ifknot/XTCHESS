/**
 *  @brief     INT 10 - Video BIOS Services
 *  @note	   Warning: Some BIOS implementations have a bug that causes register
 *			   BP to be destroyed.   It is advisable to save BP before a call to
 *		       Video BIOS routines on these systems.
 */
#ifndef BIOS_VIDEO_SERVICES_H
#define	BIOS_VIDEO_SERVICES_H

#include "bios_video_services_constants.h"
#include "bios_video_services_types.h"

// INT 10,0 - Set video mode
void bios_set_video_mode(uint8_t mode);

// INT 10,1 - Set cursor type
void bios_set_cursor_type(uint8_t start_scan_line, uint8_t end_scan_line);

// INT 10,2 - Set cursor position
void bios_set_cursor_position(uint8_t x, uint8_t y, uint8_t video_page);

// INT 10,3 - Read cursor position and size
void bios_get_cursor_position_and_size(bios_cursor_state_t* state, uint8_t video_page);

// INT 10,4 - Read light pen
// INT 10,5 - Select active display page
// INT 10,6 - Scroll active page up
// INT 10,7 - Scroll active page down

// INT 10,8 - Read character and attribute at cursor
uint16_t bios_read_character_and_attribute_at_cursor(uint8_t video_page);

// INT 10,9 - Write character and attribute at cursor
void bios_write_character_and_attribute_at_cursor(char chr, char attr, uint16_t count, uint8_t video_page);

// INT 10,A - Write character at current cursor
void bios_write_character_at_cursor(char chr, uint8_t foreground_colour, uint16_t count, uint8_t video_page);

// INT 10,B - Set color palette
// INT 10,C - Write graphics pixel at coordinate
// INT 10,D - Read graphics pixel at coordinate

// INT 10,E - Write text in teletype mode
void bios_write_text_teletype_mode(char chr, uint8_t foreground_colour, uint8_t video_page);

// INT 10,F - Get current video state
void bios_get_video_state(bios_video_state_t* state);

// INT 10,10 - Set/get palette registers (EGA/VGA)
// INT 10,11 - Character generator routine (EGA/VGA)

// INT 10,12 - Video subsystem configuration (EGA/VGA)
uint8_t bios_video_subsystem_configuration(uint8_t request, uint8_t setting, bios_video_subsystem_config_t* config);

	//INT 10,12 - broken down into its sub-functions
	uint8_t bios_return_video_configuration_information(bios_video_subsystem_config_t* config);
	//bios_select_alternate_print_screen_routine
	//bios_select_scan_lines_for_alphanumeric_modes
	//bios_select_default_palette_loading
	//uint8_t bios_cpu_access_to_video_ram(uint8_t enable);
	//bios_gray_scale_summing
	//bios_cursor_emulation
	//bios_ps2_video_display_switching
	//bios_video_refresh_control
	uint8_t bios_helper_video_subsytem_configuration(uint8_t request, uint8_t setting);

// INT 10,13 - Write string (BIOS after 1/10/86)
// INT 10,14 - Load LCD char font (convertible)
// INT 10,15 - Return physical display parms (convertible)
// INT 10,1A - Video Display Combination (VGA)
// INT 10,1B - Video BIOS Functionality/State Information (MCGA/VGA)
// INT 10,1C - Save/Restore Video State  (VGA only)
// INT 10,FE - Get DESQView/TopView Virtual Screen Regen Buffer
// INT 10,FF - Update DESQView/TopView Virtual Screen Regen Buffer

#endif
