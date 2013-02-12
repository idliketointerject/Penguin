#include "menu.h"

void mainmenu() {

	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_BITMAP *menu_background; 
	ALLEGRO_BITMAP *start;
	ALLEGRO_BITMAP *click_pen;
	ALLEGRO_BITMAP *options;
	ALLEGRO_BITMAP *leaderboard;
	ALLEGRO_BITMAP *exit;
	ALLEGRO_BITMAP *speed[60];
	ALLEGRO_SAMPLE *menu_bgm;
	ALLEGRO_MONITOR_INFO info;

	const float FPS = 60;
	
	enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
	};

   float menu_background_offset = 0;
   int current_image = 0;
   bool key[4] = { false, false, false, false };
   bool redraw = true;
   bool doexit = false;
   volatile int ticks = 0;  //Use this to count how many frames has passed since game started

   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_FONT *font24 = al_load_font("escape.ttf",24,0);

   
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return;
   }
   al_reserve_samples(10);
   menu_bgm = al_load_sample( "resources/audio/menu_bgm.wav" );
 
   if (!menu_bgm){
      printf( "menu_bgm not loaded!\n" ); 
	  al_destroy_timer(timer);
      return;
   }


   al_get_monitor_info(0, &info);
	int w = info.x2 - info.x1; /* Assume this is 1366 */
	int h = info.y2 - info.y1; /* Assume this is 768 */
   display = al_create_display(w, h);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
	  al_destroy_sample(menu_bgm);
      al_destroy_timer(timer);
      return;
   }

   menu_background = al_load_bitmap("resources/images/menuscr.jpg");
   if(!menu_background) {
      fprintf(stderr, "failed to create menu_background bitmap!\n");
      al_destroy_display(display);
	  al_destroy_sample(menu_bgm);
      al_destroy_timer(timer);
      return;
   }

   start = al_load_bitmap("resources/images/start.png");
   if(!menu_background) {
      fprintf(stderr, "failed to create menu_background bitmap!\n");
      al_destroy_display(display);
	  al_destroy_sample(menu_bgm);
      al_destroy_timer(timer);
      return;
   }

   options = al_load_bitmap("resources/images/options.png");
   if(!options) {
      fprintf(stderr, "failed to create options bitmap!\n");
      al_destroy_display(display);
	  al_destroy_sample(menu_bgm);
      al_destroy_timer(timer);
      return;
   }

   leaderboard = al_load_bitmap("resources/images/leaderboard.png");
   if(!leaderboard) {
      fprintf(stderr, "failed to create leaderboard bitmap!\n");
      al_destroy_display(display);
	  al_destroy_sample(menu_bgm);
      al_destroy_timer(timer);
      return;
   }

   exit = al_load_bitmap("resources/images/exit.png");
   if(!exit) {
      fprintf(stderr, "failed to create exit bitmap!\n");
      al_destroy_display(display);
	  al_destroy_sample(menu_bgm);
      al_destroy_timer(timer);
      return;
   }


    click_pen = al_load_bitmap("resources/images/menu_pen.jpg");
	if(!click_pen) {
      fprintf(stderr, "failed to create click_pen bitmap!\n");
      al_destroy_display(display);
	  al_destroy_sample(menu_bgm);
      al_destroy_timer(timer);
      return;
   }

   const int bg_w = al_get_bitmap_width(menu_background);


   //load all images for speed line animation
   
   int i;
   char path[80];
   for(i=0; i<60; i++) {
	   sprintf(path, "resources/images/speed_%05d.png", i);
	   speed[i] = NULL;
	   speed[i] = al_load_bitmap(path);
	  
	   if(speed[i] == NULL) {
		   printf("Error loading image");
		   for (i = 0; i <  60; i++){
			   al_destroy_bitmap(speed[i]);
		   }
		   al_destroy_bitmap(menu_background);
           al_destroy_display(display);
	       al_destroy_sample(menu_bgm);
           al_destroy_timer(timer);
		   return;
	   }
   }



   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
	  for (i = 0; i <  60; i++){
		  al_destroy_bitmap(speed[i]);
	  }
	  al_destroy_bitmap(menu_background);
      al_destroy_display(display);
	  al_destroy_sample(menu_bgm);
      al_destroy_timer(timer);
      return;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_register_event_source(event_queue, al_get_keyboard_event_source());
 
   al_draw_bitmap(menu_background,0,0,0);
   al_draw_bitmap(click_pen,SCREEN_W/2,SCREEN_H/2,0);
   al_draw_bitmap(start,SCREEN_W/2+400,SCREEN_H/2+90,0);
   al_draw_bitmap(leaderboard,SCREEN_W/2+400,SCREEN_H/2+180,0);
   al_draw_bitmap(options,SCREEN_W/2+400,SCREEN_H/2+260,0);
   al_draw_bitmap(exit,SCREEN_W/2+400,SCREEN_H/2+350,0);

   al_flip_display();
 
   al_start_timer(timer);
 
   /* Loop the sample until the display closes. */
   al_play_sample(menu_bgm, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

   while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 

	  //break out of loop if window is closed
      if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
	  //Change key[#] to true when key is held down
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = true;
               break;
 
            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = true;
               break;
 
            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = true;
               break;
 
            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = true;
               break;
         }
      }
	  //Change key[#] to false when key is released
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = false;
               break;
 
            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = false;
               break;
 
            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = false;
               break;
 
            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = false;
               break;
 
            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;
         }
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
         al_flip_display();
      }
   }


 
return;
}
