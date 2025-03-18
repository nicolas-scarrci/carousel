#include "carousel.h"
#include "utf8.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(0,1,0);

#ifndef CAROUSEL_MAX
#define CAROUSEL_MAX 25
#endif
int carousel = -1;
int carousel_index = 0;

bool process_record_carousel(uint16_t keycode, keyrecord_t *record) {
    if(carousel >= 0 && carousel < CAROUSEL_MAX){
        int dir = 0;
        if(keycode == CSL_L && record->event.pressed){
            dir = -1; 
        }
        else if(keycode == CSL_R && record->event.pressed){
            dir = +1;
        }
        if(dir != 0){
            int32_t code = -1;
            while(code == -1){
                carousel_index+=dir; 
                if(carousel_index < 0){ 
                    carousel_index = 0;
                    while(carousels[carousel].options[carousel_index]!= '\0'){
                        carousel_index++;
                    }
                    carousel_index--;
                } 
                if(carousels[carousel].options[carousel_index] == '\0'){
                    carousel_index = 0;
                }

                decode_utf8(&carousels[carousel].options[carousel_index],&code);
            }  
            
            tap_code16(KC_BSPC);
            //send_char(48+carousel_index);
            char c = carousels[carousel].options[carousel_index];
            // char s[10];
            // sprintf(s,"%li",code);
            // send_string(s);
            if((char)(int)code == c){
                // send_char('B');
                send_char(c);
            }
            else{
                // send_char('U');
                register_unicode(code);
            }


            return false;
        }
    }
    if(record->event.pressed){
        for(int a = 0; a < CAROUSEL_MAX; a++){
            if(carousels[a].keycode == keycode){
                carousel = a;
                carousel_index = 0;
                return true;
            } 
        }
        carousel = -1;
    }
    return true;
}