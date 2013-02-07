#include "initgame.h"
#include "obstacle.h"
#include "penguin.h"
#include "enemy.h"
#include "bullet.h"
#include <time.h>
#include <stdlib.h>


int random_number( const int min, const int max )
{

    int range = max - min;
    return rand() % range + min;

}


int initgame(){
	obstacle box;
	obstacle death;
	
	const float FPS = 60;
	
	enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
	};
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP *background = NULL;
   ALLEGRO_BITMAP *background2 = NULL;
   ALLEGRO_BITMAP *fox = NULL;
   ALLEGRO_BITMAP *speed[60];
   ALLEGRO_SAMPLE *bgm = NULL;
   ALLEGRO_SAMPLE *death_sound = NULL;
   ALLEGRO_MONITOR_INFO info;
   float background_offset = 0;
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
      return -1;
   }
   al_reserve_samples(10);
   bgm = al_load_sample( "resources/audio/bgm.wav" );
   death_sound = al_load_sample("resources/audio/BSZ_Pause_Close.wav");
 
   if (!bgm){
      printf( "BGM not loaded!\n" ); 
	  al_destroy_timer(timer);
      return -1;
   }
   al_get_monitor_info(0, &info);
	int w = info.x2 - info.x1; /* Assume this is 1366 */
	int h = info.y2 - info.y1; /* Assume this is 768 */
   display = al_create_display(w, h);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
	  al_destroy_sample(bgm);
      al_destroy_timer(timer);
      return -1;
   }

	penguin p;
	Enemy enm;
	Bullet tama;

   background = al_load_bitmap("resources/images/background.jpg");
   if(!background) {
      fprintf(stderr, "failed to create background bitmap!\n");
      al_destroy_display(display);
	  al_destroy_sample(bgm);
      al_destroy_timer(timer);
      return -1;
   }

   const int bg_w = al_get_bitmap_width(background);

   background2 = al_load_bitmap("resources/images/background2.jpg");
   if(!background) {
      fprintf(stderr, "failed to create background bitmap!\n");
	  al_destroy_bitmap(background);
      al_destroy_display(display);
	  al_destroy_sample(bgm);
      al_destroy_timer(timer);
      return -1;
   }

   const int bg2_w = al_get_bitmap_width(background2);

  if(!p.bitmap) {
      fprintf(stderr, "failed to create penguin bitmap!\n");
	  al_destroy_bitmap(background2);
	  al_destroy_bitmap(background);
      al_destroy_display(display);
	  al_destroy_sample(bgm);
      al_destroy_timer(timer);
      return -1;
   }


   fox = al_load_bitmap("resources/images/fox.png");
   if(!fox) {
      fprintf(stderr, "failed to create death bitmap!\n");
	  al_destroy_bitmap(background2);
	  al_destroy_bitmap(background);
      al_destroy_display(display);
	  al_destroy_sample(bgm);
      al_destroy_timer(timer);
      return -1;
   }


   death.width = al_get_bitmap_width(fox) - 10;
   death.height = al_get_bitmap_height(fox)- 10;
   death.x0 = 0;
   death.y0 = 0;

   //load all images for speed line animation
   scorekeeper s;
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
		   al_destroy_bitmap(p.bitmap);
		   al_destroy_bitmap(background2);
		   al_destroy_bitmap(background);
           al_destroy_display(display);
	       al_destroy_sample(bgm);
           al_destroy_timer(timer);
		   return -1;
	   }
   }



   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
	  for (i = 0; i <  60; i++){
		  al_destroy_bitmap(speed[i]);
	  }
	  al_destroy_bitmap(p.bitmap);
	  al_destroy_bitmap(background2);
	  al_destroy_bitmap(background);
      al_destroy_display(display);
	  al_destroy_sample(bgm);
	  al_destroy_sample(death_sound);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_register_event_source(event_queue, al_get_keyboard_event_source());
 
   al_draw_bitmap(background,0,0,0);

   al_flip_display();
 
   al_start_timer(timer);
 
   /* Loop the sample until the display closes. */
   al_play_sample(bgm, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

   while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
	  //Check which keys are being held down and adjust the penguin's x and y positions each frame

      if(ev.type == ALLEGRO_EVENT_TIMER) {
		 if (ticks%60 == 0)
		 {
			s.incrementscore();		
		 }
         if(key[KEY_UP] && p.penguin_y >= 8.0) {
            p.penguin_y -= 8.0;
			box.y0 = p.penguin_y;
			box.width = p.penguin_w;
		    box.height = p.penguin_h;
		
         }
 
         if(key[KEY_DOWN] && p.penguin_y <= h - p.penguin_h - 6.0) {
            p.penguin_y += 8.0;
			box.y0 = p.penguin_y;
			box.width = p.penguin_w;
		    box.height = p.penguin_h;
		
         }
 
         if(key[KEY_LEFT] && p.penguin_x >= 8.0) {
            p.penguin_x -= 6.0;
			box.x0 = p.penguin_x;
			box.width = p.penguin_w;
		    box.height = p.penguin_h;
		
         }
 
         if(key[KEY_RIGHT] && p.penguin_x <= w - p.penguin_w - 6.0) {
            p.penguin_x += 6.0;
			box.x0 = p.penguin_x;
			box.width = p.penguin_w;
			box.height = p.penguin_h;

         }

		if(box.bounding_box_collision(box.x0,box.y0,box.width,box.height,death.x0,death.y0,death.width,death.height) == 1){			
			 if (!death_sound){
					printf( "Death sound not loaded!\n" ); 
					al_destroy_timer(timer);
					return -1;
			 }

			 al_play_sample(death_sound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		}
		
		 enm.enemy_act();
         redraw = true;
		 ticks++;
      }
	  

	  //break out of loop if window is closed
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
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
		 
		 //Use underwater background before frame 5240
		 if(ticks < 5240){
			 if(s.getscore() > 2500){
				 death.x0 -= 8;
			 }
			 else
				 death.x0 -= 4;
			 	   //death.x0 -= 4;
				   if(death.x0 < -100)
					{
						death.x0 = w+100;
						death.y0 = random_number(20,h-10);
					}

			 //TODO: Check to see score and then make the screen scroll faster if the score is at a certain amount. Same for the sky background.
				background_offset -= 20.0;
			 
			 if(background_offset < -(bg_w / 2) +1){
				 background_offset += (bg_w / 2);
			 }

			 al_draw_bitmap(background,background_offset,0,0);
			 al_draw_bitmap(p.bitmap,p.penguin_x,p.penguin_y,0);
			 al_draw_bitmap(fox,(float)(death.x0),(float)(death.y0),0);
			 al_draw_bitmap(tama.bitmap,tama.x0,tama.y0,0);
			 if(enm.flag == 1){
				al_draw_bitmap(enm.bitmap,enm.x0,enm.y0,0);
			 }
			 al_draw_textf(font24,al_map_rgb(255,255,255),w - 100, 10, 0, "%i", s.score);
			 }
		 //Switch to sky background
		 else{
			background_offset -= 60.0;
			if(background_offset < -(bg2_w / 2) +1){
				background_offset += (bg2_w / 2);
			}
			al_draw_bitmap(background2,background_offset,0,0);
			al_draw_bitmap(p.bitmap,p.penguin_x,p.penguin_y,0);
			al_draw_bitmap(speed[current_image],0,0,0);
			al_draw_textf(font24,al_map_rgb(255,255,255),w - 100, 10, 0, "%i", s.score);
			current_image = (current_image + 1 ) % 60;     //increment 1 frame in speed line animation
		 }
 
         al_flip_display();
		 //al_clear_to_color(al_map_rgb(0,0,0));
      }
   }


   
   //free memory when closing game 
   for (i = 0; i <  60; i++){
	   al_destroy_bitmap(speed[i]);
   }
   al_destroy_sample(bgm);
   al_destroy_bitmap(background2);
   al_destroy_bitmap(background);
   al_destroy_bitmap(p.bitmap);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);

   return 0;

}