#include <stdio.h>
#include "sdl_wrapper.h"
#include "ogl.h"
#include "font.h"
#include "config.h"
#include "category.h"
#include "platform.h"
#include "bg.h"
#include "menu.h"
#include "submenu.h"
#include "hint.h"
#include "game_sel.h"
#include "sound.h"
#include "event.h"
#include "setup.h"
#include "focus.h"
#include "snap.h"
#include "location.h"
#include "video.h"

static int supress_wait = 0;

void supress( void ) {
	supress_wait = config_get()->iface.frame_rate / 5;
}

void clean_up( void ) {
	sound_free();
	game_list_free();
	submenu_free();
	platform_free(); 
	menu_free();
	hint_free();
	font_free();
	bg_free();
	location_free();
	event_free();
	snap_free();
	video_free();
	sdl_free();
}

void bail( void ) {
	/* Exit "gracefully" */
	clean_up();
	exit( -1 );
}

int main( int argc, char *arvg[] ) {
	int quit = 0;
	int config_status = 0;
	int event;

#ifdef __WIN32__
	freopen( "cabrio.out", "w", stdout );
	freopen( "cabrio.err", "w", stderr );
#endif

	config_status = config_open( NULL );
	if( config_status == -1 )
		return -1;

	if( sdl_init() != 0 )
		bail();

	if( ogl_init() != 0 )
		bail();
	
	/* Clear the screen as soon as we can. This avoids graphics
	 * glitches which can occur with some SDL implementations. */
	ogl_clear();
	sdl_swap();

	if( event_init() != 0 )
		bail();

	if( font_init() != 0 )
		bail();

	setup(); 

}

