/************************************************************************************************************/
/*                                                                                                          */
/*                                                Move.h                                                    */
/*                                                                                                          */
/*                                                                                       2023. 1. 9.        */
/************************************************************************************************************/
#ifndef __MOVE_H
#define __MOVE_H

enum{LOST=10, FL, FLL, FLR, FM, FW, FC};
#define PI M_PI
#define int_xv int x, int v
#define int_sp int sn, int p
#define int_xyav int x, int y, int a, int v
#define ENX 165.4f
#define ENY	191.1f
#define ENA	415.0f
#define vx	vg[0]
#define vy	vg[1]
#define va	vg[2]
#define deg	(ena-ea)*PI/180
#define ssa(x, y)	aup=(x), adn=(y)
#define ssx(x, y)	lzig=(x), lhd=(y)
#define ssw(x, y)	wzig=(x), whd=(y)
#define ssc(x1, x2, y1, y2)	xs=(x1), xb=(x2), ys=(y1), yb=(y2)
#define time	while(tc); tc=1
#define sign(x)	((x)<0? -1: 1)
#define fmx(x, y)	(fabs(x)>(y)? (y)*sign(x): (x))
#define ifor	int i; for(i=0; i<3; i++)
#define ffor	int i; db g, z, ea; g=1; z=0; ea=ena; size(x, y, a, v); tc=1; for(i=1; i<tsize; i++)
#define ffor2	int i; db d, g, z, ea; g=1; d=atan2(y, x)+ag*PI/1800; if(a) a+=ag; ea=ena; size(x, y, a, v); z=sqrt(vm[0]*vm[0]+vm[1]*vm[1]); tc=1; for(i=1; i<tsize; i++)
#define sf	s=s? s*100.0f/v+aup/2.0f: 0
#define sfor	sf; ffor
#define sfor2	sf; ffor2
#define fgo(x, y, a)	speed(i); time; mgo(vx=x, vy=y, va=a)
#define fgo2	vm[0]=z*cos(d-deg); vm[1]=z*sin(d-deg); fgo(vx*g, vy*g, va*g)
#define pstop 	{if(abs(psd[sn]-p)<5){mee(); rr FW;} g=(sn==3||sn==8)? 20: 50; g=gra(g, psd[sn], p);}
#define plost	{if(!(i%5)&&i>s+10000.0f/v+aup&&abs(zig)<5) safety=1; if(safety&&abs(zig)>20) zig=hd=0;}

void sss(int n);
void count(int n, int set);
db gra(int min, int x, int xm);
void sen(void);
void gen(void);
void size(int_xyav);
void speed(int n);
int xxs(int mode);
int xxc(int dir);

int xxf(int n);
void aa(int_xyav);
void TQ(int_xyav);
void dd(int a, int v, int_sp);
void CC(int nx, int sx, int ny, int sy, db ratio);
void CC2(int nx, int sx, int ny, int sy, db ratio);
void CC3(int nx, int sx, int ny, int sy, db ratio);
void ee(int n);
void ee2(int n);
void ee3(int n);
void TD(int_xyav, int ag);
void TD2(int_xyav, int ag);
int fx(int_xyav, int ag, int sn, int s);
int fw(int_xyav, int ag, int_sp, int s);
int xx(int_xv, int_sp, int dir, int no, int mode);
int pb(int x, int a, int v, int rn, int range, int_sp, int s);
int pb2(int x, int a, int v, int rn, int range, int_sp, int s);
int wp(int x, int a, int v, int rn, int range, int rn2, int range2, int_sp, int s);
int yw(int y, int a, int v, int rn, int range, db ratio, int_sp, int s);
int gm(int mode);
int gm2(int mode, int c);
int CD(int mode, int cn, int_xyav, int cx, int cy, int tx, int s);

void non_Holonomic(float Fx, float Fy, float Fw);
void HolonomicW(float f_agl, float f_speed, float fw_speed);

#endif      // __MOVE_H
