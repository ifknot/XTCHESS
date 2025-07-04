/**
 *  @brief
 *  @details   ~
 *  @url http://www.techhelpmanual.com/27-dos__bios___extensions_service_index.html
 */
//#include <assert.h>
#include <stdint.h>

#include "bios_video_services_constants.h"
#include "bios_video_services.h"

/**
* @brief INT 10,0 - Set Video Mode
* AH = 00
* AL = video_mode_t
* @see bios_video_services_constants.h enum type
*/
void bios_set_video_mode(uint8_t mode) {
	__asm {
		.8086
		pushf                                ; preserve what int BIOS functions may not
        push    ds                           ; due to unreliable behaviour

		mov		al, mode
		mov		ah, BIOS_SET_VIDEO_MODE
		int		BIOS_VIDEO_SERVICES

		pop 	ds
		popf
	}
}

/**
 * @brief INT 10,1 - Set Cursor Type
 *  AH = 01
 *	CH = cursor starting scan line (cursor top) (low order 5 bits)
 *	CL = cursor ending scan line (cursor bottom) (low order 5 bits)
 * @note - use CX = 2000h to disable cursor
 *  - cursor scan lines are zero based
 *	- cursor size can also be set via the 6845 CRT controller
 *	- cursor size can be determined using the CRTC,  INT 10,3  or the
 *	  BIOS Data Area bytes 40:60 (ending scan line) and 40:61 (starting
 *	  scan line)
 *	- the following is a list of the cursor scan lines associated with
 *	  most common adapters;  screen sizes over 40 lines may differ
 *	  depending on adapters.
 *
 *		Line	 Starting     Ending	  Character
 *	Video	Count	 Scan Line    Scan Line   Point Size
 *
 *	CGA	 25	    06		 07	      08
 *	MDA	 25	    0B		 0C	      0E
 *	EGA	 25	    06		 07	      0E
 *	EGA	 43	  04/06 	 07	      08
 *	VGA	 25	    0D		 0E	      10
 *	VGA	 40	    08		 09	      0A
 *	VGA	 50	    06		 07	      08
 */
void bios_set_cursor_type(uint8_t start_scan_line, uint8_t end_scan_line) {
    __asm {
        .8086
        pushf                                ; preserve what int BIOS functions may not
        push    ds                           ; due to unreliable behaviour

        mov		ch, start_scan_line
        mov     cl, end_scan_line
        mov		ah, BIOS_SET_CURSOR_TYPE
        int		BIOS_VIDEO_SERVICES

        pop 	ds
        popf
	}
}

/**
 * @brief INT 10,2 - Set Cursor Position
 *  AH = 02
 *	BH = page number (0 for graphics modes)
 *	DH = row
 *	DL = column
 *  - positions relative to 0,0 origin
 *	- 80x25 uses coordinates 0,0 to 24,79;	40x25 uses 0,0 to 24,39
 */
void bios_set_cursor_position(uint8_t x, uint8_t y, uint8_t video_page) {
    __asm {
        .8086
        pushf                                ; preserve what int BIOS functions may not
        push    ds                           ; due to unreliable behaviour

        mov		bh, video_page
        mov     dh, y
        mov     dl, x
        mov		ah, BIOS_SET_CURSOR_POSITION
        int		BIOS_VIDEO_SERVICES

        pop 	ds
        popf
	}
}

/**
 * @brief INT 10,3 - Read Cursor Position and Size
 * 	AH = 03
 *	BH = video page
 *	on return:
 *	CH = cursor starting scan line (low order 5 bits)
 *	CL = cursor ending scan line (low order 5 bits)
 *	DH = row
 *	DL = column
 */
void bios_get_cursor_position_and_size(bios_cursor_state_t* state, uint8_t video_page) {
    __asm {
        .8086
        pushf                                ; preserve what int BIOS functions may not
        push    ds                           ; due to unreliable behaviour

		mov     bh, video_page
        mov		ah, BIOS_READ_CURSOR_POSITION_SIZE
        int		BIOS_VIDEO_SERVICES
        les	di, state
		mov	es:[di], ch				; start_scanline
		mov	es:[di + 1], cl			; end_scanline
		mov	es:[di + 2], dh			; row
		mov	es:[di + 3], dl			; column

        pop 	ds
        popf
	}
}

/**
* @brief INT 10,8 - Read Character and Attribute at Cursor Position
*	AH = 08
*	BH = display page
*	on return:
*	AH = attribute of character
*	AL = character at cursor position
* @note 1. attribute only valid in text modes
* @note 2. video mode 4 (300x200 4 color) on the EGA, MCGA and VGA this function works only on page zero
*/
uint16_t bios_read_character_and_attribute_at_cursor(uint8_t video_page) {
	uint16_t char_attr_pair;
	__asm {
        .8086
        pushf                                ; preserve what int BIOS functions may not
        push    ds                           ; due to unreliable behaviour

        mov		ah, BIOS_READ_CHARACTER_AND_ATTRIBUTE_AT_CURSOR
        int		BIOS_VIDEO_SERVICES
		mov 	char_attr_pair, ax

        pop 	ds
        popf
	}
	return char_attr_pair;
}

/**
* @brief INT 10,9 - Write Character and Attribute at Cursor Position
* 	AH = 09
*	AL = ASCII character to write
*	BH = display page  (or mode 13h, background pixel value)
*	BL = character attribute (text) foreground color (graphics)
*	CX = count of characters to write (CX >= 1)
*	@note 1. does *not* move the cursor
*	@note 2. in graphics mode (except mode 13h), if BL bit 7=1 then value of BL is XOR'ed with the background color
*/
void bios_write_character_and_attribute_at_cursor(char chr, char attr, uint16_t count, uint8_t video_page) {
	__asm {
        .8086
        pushf                                ; preserve what int BIOS functions may not
        push    ds                           ; due to unreliable behaviour

		mov 	al, chr
		mov 	bh, video_page
		mov		bl, attr
		mov 	cx, count
        mov		ah, BIOS_WRITE_CHARACTER_AND_ATTRIBUTE_AT_CURSOR
        int		BIOS_VIDEO_SERVICES

        pop 	ds
        popf
	}
}

/**
* @brief INT 10,A - Write Character Only at Current Cursor Position
*	AH = 0A
*	AL = ASCII character to write
*	BH = display page  (or mode 13h, background pixel value)
*	BL = foreground color (graphics mode only)
*	CX = count of characters to write (CX >= 1)
*   @note 1. does *not* move the cursor
*   @note 2. inherits the attribute at the cursor position
*	@note 3. colour ignored in text modes
*/
void bios_write_character_at_cursor(char chr, uint8_t foreground_colour, uint16_t count, uint8_t video_page) {
	__asm {
        .8086
        pushf                                ; preserve what int BIOS functions may not
        push    ds                           ; due to unreliable behaviour

		mov 	al, chr
		mov 	bh, video_page
		mov		bl, foreground_colour
		mov 	cx, count
        mov		ah, BIOS_WRITE_CHARACTER_AT_CURRENT_CURSOR
        int		BIOS_VIDEO_SERVICES

        pop 	ds
        popf
	}
}

/**
* @brief INT 10,E - Write Text in Teletype Mode
*	AH = 0E
*	AL = ASCII character to write
*	BH = page number (text modes)
*	BL = foreground pixel color (graphics modes)
*	@note 1. cursor advances after write *unless* it is a control code
*	@note 2. characters BEL (7), BS (8), LF (A), and CR (D) are treated as control codes
*	@note 3. for some older BIOS (10/19/81), the BH register must point to the currently displayed page
*/
void bios_write_text_teletype_mode(char chr, uint8_t foreground_colour, uint8_t video_page) {
	__asm {
        .8086
        pushf                                ; preserve what int BIOS functions may not
        push    ds                           ; due to unreliable behaviour

		mov 	al, chr
		mov 	bh, video_page
		mov		bl, foreground_colour
        mov		ah, BIOS_WRITE_TEXT_IN_TELETYPE_MODE
        int		BIOS_VIDEO_SERVICES

        pop 	ds
        popf
	}
}

/**
* @brief INT 10,F - Get Video State
* AH = 0F
*
* on return:
* AH = number of screen columns
* AL = mode currently set (see VIDEO MODES)
* BH = current display page
*
* @note - video modes greater than 13h on EGA, MCGA and VGA indicate
* INT 10,0 was called with the high bit of the mode (AL) set
* to 1, meaning the display does not need cleared
* @note - function returns byte value at 40:49;  On EGA, MCGA and
* VGA bit 7 of register AL is determined by bit 7 of BIOS Data
* Area byte 40:87.   This bit is usually set by INT 10,0
* with bit 7 of the requested mode (in AL) set to 1
*/
void bios_get_video_state(bios_video_state_t* state) {
	__asm {
		.8086
		pushf
		push 	ds

		mov	ah, BIOS_GET_CURRENT_VIDEO_STATE
		int	BIOS_VIDEO_SERVICES
		les	di, state
		mov	es:[di], ah				; number of screen columns
		mov	es:[di + 1], al			; video mode
		mov	es:[di + 2], bh			; display page

		pop 	ds
		popf
	}
}



/**
* @brief	INT 10,12 - Video Subsystem Configuration (EGA/VGA)
* -----------------------------------------------------------------------------------------------------
*			Sub-function: Return Video Configuration Information
* -----------------------------------------------------------------------------------------------------
* @details
* AH = 12h
* BL = 10  return video configuration information
*
* on return:
* BH = 0 if color mode in effect
*    = 1 if mono mode in effect
* BL = 0 if 64k EGA memory
*    = 1 if 128k EGA memory
*    = 2 if 192k EGA memory
*    = 3 if 256k EGA memory
* CH = feature bits
* CL = switch settings
*
* Info: This obtains miscellaneous information about the EGA switch
*       settings and the current values of the "feature bits" as read
*       through those rarely-used RCA connectors on some EGA cards.
*
*  @note If upon return from this call, BL>4, then must be running on a CGA or MDA (not an EGA or VGA).
*/
uint8_t bios_return_video_configuration_information(bios_video_subsystem_config_t* config) {
	uint8_t e = 0;
	__asm {
		.8086
		pushf
		push 	ds

		mov		ah, BIOS_VIDEO_SUBSYSTEM_CONFIGURATION
		mov		bl, 10h						; return video configuration information
		int		BIOS_VIDEO_SERVICES
		mov		e, al
		les		di, config
		mov		es:[di], bh					; color_mode(0 = colour, 1 = mono)
		mov		es:[di + 1], bl				; EGA memory BL(0 = 64k, 2 = 128k, 2 = 192k, 3 = 256k)
		mov		es:[di + 2], ch				; feature_bits(values of those RCA connectors)
		mov		es:[di + 3], cl				; switch_settings

		pop 	ds
		popf
	}
	return e;
}

/**
* @brief INT 10,12 - Video Subsystem Configuration (EGA/VGA)
* -----------------------------------------------------------------------------------------------------
* @note Other than Sub-function: Return Video Configuration Information the other subfunctions have a
* uniform interface
* -----------------------------------------------------------------------------------------------------
* BL = 20  select alternate print screen routine
*
* Info: This redirects the INT 05H (print screen) vector to a handler within the EGA/VGA ROM-BIOS.
*
* On older PCs, XTs, and ATs, the default ROM-BIOS print-screen handler stops printing after 25 lines.
* The EGA/VGA handler correctly prints the number of lines specified in the byte at 0040:0084 in the BIOS Data Area.
*
* @note Most EGAs and VGAs set this automatically.
* However, it is good practice to use this fn whenever change the number of video lines that are displayed in text mode.
* -----------------------------------------------------------------------------------------------------
* BL = 30  select scan lines for alphanumeric modes
*    AL = 0  200 scan lines
*       = 1  350 scan lines
*       = 2  400 scan lines
*
* on return: AL = 12 if a VGA is active
*
* Info: This updates bits 0-3 in the EgaMiscInfo2Rec (at 0040:0088) and bits 4 and 7 of the VgaFlagsRec (at 0040:0089).
* Then, on the next INT 10H 00H call to switch to a text mode, the specified resolution will be in effect.
* -----------------------------------------------------------------------------------------------------
* @note Compatibility: VGA
* BL = 31  select default palette loading
*    AL = 0 enable default palette loading
*       = 1 disable default palette loading
*
* on return: AL = 12 if a valid value was passed in AL
*
* Info: This changes how the BIOS handles the color palette on subsequent calls to INT 10H 00H (set video mode).
* It updates bit 3 of the VgaFlagsRec (at 0040:0089).
*
* @note When automatic palette loading is enabled (the default setting), the BIOS reprograms the ATC
* with the default palette values each time the video mode is reset.
* User can modify the VgaSavePtr2Rec to setup own palette to be used the default.
*
* @note When disabled, the current palette setting are left in place on mode changes.
* -----------------------------------------------------------------------------------------------------
* @note Compatibility: VGA
* BL = 32  CPU access to video RAM
*    AL = 0  enable CPU access to video RAM and I/O ports
*       = 1  disable CPU access to video RAM and I/O ports
*
* on return: AL = 12h if a valid value was passed in AL
*
* Info: You can use this to suppress CPU access to video RAM and I/O ports on VGA-compatible displays.  It updates bit 0 of the
* VgaFlagsRec (at 0040:0089).
* -----------------------------------------------------------------------------------------------------
* * @note Compatibility: VGA
* BL = 33  Gray scale summing
*    AL = 0  enable gray scale summing
*       = 2  disable gray scale summing
*
* on return: AL = 12 if a valid value was passed in AL
*
* Info: This updates bit 1 of the VgaFlagsRec (at 0040:0089).
* On the next mode reset (via INT 10H 00H), if that bit is set, then the BIOS will automatically
* reprogram the palette to display only shades of gray
* -----------------------------------------------------------------------------------------------------
* BL = 34  cursor emulation
*    AL = 0  enable cursor emulation
*       = 1  disable cursor emulation
*
* on return: AL = 12
* -----------------------------------------------------------------------------------------------------
* BL = 35  PS/2 video display switching
*    AL = 0 initial adapter video off
*       = 1 initial planar video on
*       = 2 switch active video off
*       = 3 switch inactive video on
*    ES:DX pointer to 128 byte save area (when AL = 0, 2 or 3)
*
* on return: AL = 12  if a valid value was passed in AL
*
* Info: ON PS/2 systems, this provides a means to switch between the built-in VGA (on the motherboard)
* and another, incompatible display system.(!)
* -----------------------------------------------------------------------------------------------------
* BL = 36  video refresh control
*    AL = 0 enable refresh
*       = 1 disable refresh
*
* on return: AL = 12 if a valid value was passed in AL
* Info: This modifies bit 5 of the VGA's Sequencer Clocking Mode Register.
* Can draw complex graphics faster while refresh is disabled (it avoids some enforced wait states).
* @note Be sure to re-enable refresh when finished updating video memory.
* -----------------------------------------------------------------------------------------------------
*/
uint8_t bios_helper_video_subsytem_configuration(uint8_t request, uint8_t setting) {
	uint8_t e = 0;
	__asm {
		.8086
		pushf
		push 	ds

		mov		ah, BIOS_VIDEO_SUBSYSTEM_CONFIGURATION
		mov		bl, request
		mov		al, setting
		int		BIOS_VIDEO_SERVICES
		mov		e, al

		pop 	ds
		popf
	}
	return e;
}

/**
* @brief INT 10,12 - Video Subsystem Configuration (EGA/VGA)
*/
uint8_t bios_video_subsystem_configuration(uint8_t request, uint8_t setting, bios_video_subsystem_config_t* config) {
	switch (request) {
	case BIOS_RETURN_VIDEO_CONFIGURATION_INFORMATION:	// the odd one out of the sub-functions
		return bios_return_video_configuration_information(config);
	case BIOS_SELECT_ALTERNATE_PRINT_SCREEN_ROUTINE:
	case BIOS_SELECT_SCAN_LINES_FOR_ALPHANUMERIC_MODES:
	case BIOS_SELECT_DEFAULT_PALETTE_LOADING:
	case BIOS_CPU_ACCESS_TO_VIDEO_RAM:
	case BIOS_GRAY_SCALE_SUMMING:
	case BIOS_CURSOR_EMULATION:
	case BIOS_PS2_VIDEO_DISPLAY_SWITCHING:
	case BIOS_VIDEO_REFRESH_CONTROL:
		return bios_helper_video_subsytem_configuration(request, setting);
	default:
		return 0;
		break;
	}
}
