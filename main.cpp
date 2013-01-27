#include <stdio.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
 
const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
 
int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP *background = NULL;
   ALLEGRO_BITMAP *background2 = NULL;
   ALLEGRO_BITMAP *penguin = NULL;
   ALLEGRO_BITMAP *speed[60];
   ALLEGRO_SAMPLE *bgm=NULL;
   float background_offset = 0;
   int current_image = 0;
   bool key[4] = { false, false, false, false };
   bool redraw = true;
   bool doexit = false;
   volatile int ticks = 0;  //Use this to count how many frames has passed since game started
 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   if(!al_init_image_addon()) {
      fprintf(stderr, "failed to initialize al_init_image_addon!\n");
      return -1;
   }

   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   }
 
      if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
      return -1;
   }
 
   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
      return -1;
   }
 
   if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
   }

   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
 
   bgm = al_load_sample( "resources/audio/bgm.wav" );
 
   if (!bgm){
      printf( "BGM not loaded!\n" ); 
	  al_destroy_timer(timer);
      return -1;
   }

   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
	  al_destroy_sample(bgm);
      al_destroy_timer(timer);
      return -1;
   }

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

   penguin = al_load_bitmap("resources/images/penguin.png");
   if(!penguin) {
      fprintf(stderr, "failed to create penguin bitmap!\n");
	  al_destroy_bitmap(background2);
	  al_destroy_bitmap(background);
      al_destroy_display(display);
	  al_destroy_sample(bgm);
      al_destroy_timer(timer);
      return -1;
   }

   //Get dimentions of penguin image and set initial position
   const int penguin_w = al_get_bitmap_width(penguin);
   const int penguin_h = al_get_bitmap_height(penguin);
   float penguin_x = SCREEN_W / 20.0;
   float penguin_y = SCREEN_H / 2.0 - penguin_h / 2.0;

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
		   al_destroy_bitmap(penguin);
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
	  al_destroy_bitmap(penguin);
	  al_destroy_bitmap(background2);
	  al_destroy_bitmap(background);
      al_destroy_display(display);
	  al_destroy_sample(bgm);
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
         if(key[KEY_UP] && penguin_y >= 8.0) {
            penguin_y -= 8.0;
         }
 
         if(key[KEY_DOWN] && penguin_y <= SCREEN_H - penguin_h - 6.0) {
            penguin_y += 8.0;
         }
 
         if(key[KEY_LEFT] && penguin_x >= 8.0) {
            penguin_x -= 6.0;
         }
 
         if(key[KEY_RIGHT] && penguin_x <= SCREEN_W - penguin_w - 6.0) {
            penguin_x += 6.0;
         }
 
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
			 //Check penguin x position and scroll screen accordingly
			 if(penguin_x < (SCREEN_W * 1/4)){
				background_offset -= 20.0;
			 }
			 else if(penguin_x < (SCREEN_W * 2/4)){
				background_offset -= 22.0;
			 }
			 else if(penguin_x < (SCREEN_W * 3/4)){
				background_offset -= 24.0;
			 }
			 else{
				background_offset -= 26.0;
			 }
		 
			 if(background_offset < -(bg_w / 2) +1){
				 background_offset += (bg_w / 2);
			 }

			 al_draw_bitmap(background,background_offset,0,0);
			 al_draw_bitmap(penguin,penguin_x,penguin_y,0);
			 }
		 //Switch to sky background
		 else{
			background_offset -= 60.0;
			if(background_offset < -(bg2_w / 2) +1){
				background_offset += (bg2_w / 2);
			}
			al_draw_bitmap(background2,background_offset,0,0);
			al_draw_bitmap(penguin,penguin_x,penguin_y,0);
			al_draw_bitmap(speed[current_image],0,0,0);
			current_image = (current_image + 1 ) % 60;     //increment 1 frame in speed line animation
		 }
 
         al_flip_display();
      }
   }
   
   //free memory when closing game 
   for (i = 0; i <  60; i++){
	   al_destroy_bitmap(speed[i]);
   }
   al_destroy_sample(bgm);
   al_destroy_bitmap(background2);
   al_destroy_bitmap(background);
   al_destroy_bitmap(penguin);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);

   return 0;
}