#include <xc.h>
#include "buttons.h"


#define PUL_ROJO 0 // RA0
#define PUL_VERDE 1 // RA1
#define PUL_AZUL 2 // RB2
#define PUL_AMARILLO 3 // RB3
#define PUL_START 5 // RB5


void initButtons(){
    ANSELA &= ~((1 << PUL_ROJO)|(1 << PUL_VERDE));
    ANSELB &= ~((1 << PUL_AZUL)|(1 << PUL_AMARILLO));

    TRISA |= ((1 << PUL_ROJO)|(1 << PUL_VERDE));
    TRISB |= ((1 << PUL_AZUL)|(1 << PUL_AMARILLO));

}

int act_rojo, act_verde, act_azul, act_amarillo, act_start;
int ant_rojo = 1;
int ant_verde = 1;
int ant_azul = 1;
int ant_amarillo = 1;
int ant_start = 1;


// Dentro del while o ejecución del juego, se debe llamar a ButtonsPressed() y guardarla en button

button_t ButtonsPressed(){
    // Devolverá el tipo de botón según se detecte:

    act_rojo = (PORTA >> PUL_ROJO) & 1; 
    act_verde = (PORTA >> PUL_VERDE) & 1; 
    act_azul = (PORTB >> PUL_AZUL) & 1; 
    act_amarillo = (PORTB >> PUL_AMARILLO) & 1;
    act_start = (PORTB >> PUL_START) & 1;

    if (act_start < ant_start){
        return BUTTON_START;
    }
    if (act_rojo < ant_rojo){
        return BUTTON_RED;
    }
    if (act_verde < ant_verde){
        return BUTTON_GREEN;
    }
    if (act_azul < ant_azul){
        return BUTTON_BLUE;
    }
    if (act_amarillo < ant_amarillo){
        return BUTTON_YELLOW;
    }

    // Actualizo estados

    ant_rojo = act_rojo; 
    ant_verde = act_verde;
    ant_azul = act_azul;
    ant_amarillo = act_amarillo;

    return BUTTON_NONE; // En caso de no pulsarse ningún botón

    
}
