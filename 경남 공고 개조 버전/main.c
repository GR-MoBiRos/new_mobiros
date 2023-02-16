/************************************************************************************************************/
/*                                                                                                          */
/*                                              MobileRobot.c                                               */
/*                                                                                                          */
/*                                                                                       2023. 1. 9.        */
/************************************************************************************************************/
#include "Interface.h"

#define _break break;
#define ARM		mee(); bz(100, 0); stand=0; while(!sw_in()); stand=1
#define PASS  		if(GN){ARM;};
#define PASS2           if(GN){gest(++GN); PASS; 

#define pause stand=0; while(!sw_in()){StopMotion(9);} stand=1

#define	C24		CC(0, 0, 2, 170, 170.0f/165)
#define C97		CC(0, 0, 9, 130, 130.0f/200)
#define C34		CC2(0, 0, 3, 210, 210.0f/70)
#define C87		CC2(0, 0, 8, 210, 210.0f/90)
#define C47(s, p)		CC2(4, 120, s, p, 80.0f/95)
#define C56(s, p)		CC(5, 210, s, p, 195.0f/210)
#define C32		CC3(0,0,3,225,225.0f/105)
#define C89		CC3(0, 0, 8, 225, 225.0f/90)

#define SO               sss(50); ssa(0, 0)
#define SF               ssa(50, 50)
#define GG(x)            if(GN==x) goto

#define lds(r, c)          lcd_display_str(r, c, str)
#define clear             lcd_clear_screen()

#define ET 	        ee(280.0f*88/(vx)+0.5)
#define sp	        sprintf

int GN;
char str[31];

void C(int p){ 
	C56(p, p==2? 170: p==9? 135: p==3? 100: p==8? 110: 0);
	if(p==4 || p==7) CC(0, 0, p, p==4? 160: 210, 0);
}
void ps(int p){ CC(0, 0, p, p==2? 170: p==9? 135: p==4? 75: p==7? 95: p==5? 120: 150, 0); }
void ps2(int p){ CC(0, 0, p, p==2? 130: p==9? 115: p==4? 180: p==7? 200: p==5? 115: 145, 0); }
void ss(int x, int y, int a){ SO; aa(x, y, 0, 350); SF; aa(0, 0, a, abs(a)>=900? 170: 120); mee(); }
void we(int v, int p){pb(3000, 0, v, p, p==2? 170: 135, p, p==2? -140: -105, 0); }

void step(int cnn);
void sw_pro(void);
void test(void){

    if(GN<0){
        sp(str, "ENX] %4d", (int)enx); lds(0, 0);
        sp(str, "ENY] %4d", (int)-eny); lds(1, 0);
        sp(str, "ENA] %4d", (int)-ena); lds(2, 0);
	lcd(0,0,"enx %04d", (int)enx);
	lcd(0,0,"eny %04d", (int)-eny);
	lcd(0,0,"ena %04d", (int)-ena);
    }
    else if(GN>0){
	 gm(1);
        for(int i=1; i<=vcam_n; i++){
		
		lcd(i-1,11,"%d>%03d %03d",vcam[i][0],vcam[i][2], vcam[i][1]);
	}
    }
    else{
        lcd(0,0,"%03d %03d %03d", psd[2], psd[9], psd[1]);
        lcd(1,0, "%03d %03d", psd[3], psd[8]);
        lcd(2,0,"%03d %03d", psd[4], psd[7]);
        lcd(3,0,"%03d %03d", psd[5], psd[6]);
        _delay_ms(100);
    }
}

void gest(int n){
    sp(str, "[%2d]", n); lds(3, 15);
}

int main(void){
    Interface_init(); Motor_init(); mee(); Camera_init();
    putchar1(18); vcam_n=0; memset(vcam_data, 0, sizeof(vcam_data));
    _delay_ms(300);

    ssa(50, 50);
    ssx(5, 5); 
    ssw(1, 0.5);
    ssc(0, 180, 0, 240);
    sss(50);
    sen();      

    GN=0;
    while(1){
        stand=0;
        switch(sw_in()){
            case SW3: stand=1; led_off(LED); step(GN);mee(); bz(200, 0);led_on(LED); break;
            case SW1: gest(GN+=1); break;
            case SW2: gest(GN-=1); break;
            case SWB: mee(); while(SWIN) test(); clear; break;

            default : gest(GN);
        }
    }
}
void step(int cnn){
	clear;
    switch(cnn){
        case 0:
			TD(450,450,90,400,0);
        _break
        case 1:
			C47(0,0);
        _break

        case 2:
			aa(500,0,90,500);
        _break
    }

}
