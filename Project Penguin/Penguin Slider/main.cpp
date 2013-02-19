
#include "initgame.h"
#include "menu.h"
#include "score.h"
using namespace std;


 
int main(int argc, char **argv)
{   

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
    mainmenu();
	//initgame();


   return 0;
}