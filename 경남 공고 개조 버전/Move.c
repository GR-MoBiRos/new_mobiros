/***************************************************************************************
MOVE.C 
                                                         update : 2023. 1. 9. Park JunYong
***************************************************************************************/
#include "Interface.h"

vuc tc=0, vcam_en=1, vcam_n=0, vcam_cnt=0, vcam_buff[140]={0, }, vcam_data[10][5], vcam[10][5];
int stand=0, tsize, aup, adn, acc, cset[7]={0, }, cnt[7]={0, }, xs, xb, ys, yb;
vdb totc=0, enx, eny, ena, enx2, eny2, lzig, lhd, wzig, whd, vb[3]={0, }, vg[3]={0, }, vm[3]={0, }, vf[3][51];

ISR(TIMER1_OVF_vect){ //************���� �ҽ� ����
     TCNT1H=0xFF; TCNT1L=0x70;
     totc++;
     if(tc>0) tc--;
     gen();
     if(stand&&SWIN){
          ee2(50); while(SWIN);
          while(!sw_in()); ee3(50);
     }
}

void sss(int n){acc=n; ifor for(int k=0; k<acc; k++) vf[i][k]=0;}
void count(int n, int set){cnt[n]+=(!cset[n]&&set); cset[n]=set;}
db gra(int min, int x, int xm){rr x>min? (db)(xm-x)/(xm-min): 1;}
void sen(void){ifor WC(i, DFH); enx=eny=ena=enx2=eny2=0;}
void gen(void){
     long k, n[3]={0, }; db d, z, x, y, x2, y2;

     ifor{
          WC(i, RDRP);
          for(k=0; k<4; k++){
               while(MOTOR_CMD(i)&0x01);
               n[i]|=MOTOR_DATA(i);
               if(k!=3) n[i]<<=8;
          }
     }
     x2=(n[0]-n[2])/2.0f/ENX;
     y2=(n[1]-(n[0]+n[1]+n[2])/3.0f)/ENY;
     ena=-(n[0]+n[1]+n[2])/3.0f/ENA;
     x=x2-enx2; y=y2-eny2;
     d=atan2(y, x)+ena*PI/180; z=sqrt(x*x+y*y);
     enx+=z*cos(d); eny+=z*sin(d);
     enx2=x2; eny2=y2;
}

void size(int_xyav){

     db mt=1, t[3]={x, y, a/10.0F};

     ifor if(fabs(t[i])>mt) mt=fabs(t[i]);
     for(i=0; i<3; i++){vb[i]=vg[i]; vm[i]=v*t[i]/mt;}
     tsize=v>0? mt*100/v+aup+0.5: 0;
}

void speed(int n){
     db sum[3]={0, };

     ifor{ 
          for(int k=acc-1; k>0; k--) sum[i]+=(vf[i][k]=vf[i][k-1]);
          vf[i][0]=vm[i];
          if(!aup&&n<tsize-adn) vg[i]=(sum[i]+vm[i])/acc;
          else vg[i]=n>tsize-adn? vm[i]*(tsize-n)/adn: n>aup? vm[i]: (vm[i]-vb[i])*n/aup+vb[i];
     }
}

int xxs(int mode){ //mode-FLL �Ǵ� FLR ��� ����, mode=0 ������, mode=1 �����
     int ir=ir_in();

     //if(!ir) rr LOST;
     if((ir&1)&&(ir&16)) rr FL;
     if(mode){if(ir&1) rr FLL; if(ir&16) rr FLR;}
     if(ir==1) rr 4;
     if(ir==3) rr 3;
     if(ir==2) rr 2;
     if(ir==6) rr 1;
     if(ir==12) rr -1;
     if(ir==8) rr -2;
     if(ir==24) rr -3;
     if(ir==16) rr -4;
     rr 0;
}

int xxc(int dir){
     int i, k, ir=ir_in(); db ey=eny2, g=1, n=1;

     i=k=dir? dir: (ir>7)? -1: 1;
    //if(!ir){if(psd[3]>90) i=k=-1; else if(psd[8]>90) i=k=1;}
     while(!(ir&4)){
          ir=ir_in();
          if(!dir&&i==k&&!ir&&fabs(eny2-ey)>100){n=1; k=-k;}
          if(fabs(eny2-ey)>300) rr -1;
          if(++n<160) g=n/160.0f;
          if(ir&4) g=0.2;
          mgo(0, 120*k*g, 0);
     }
     mee();
     rr 0;
}

int xxf(int n){ //n : ������ ���� ��
     int ir=ir_in();

     count(1, ir&1); count(2, ir&2); count(3, ir&4); count(4, ir&8); count(5, ir&16);
     if(n&&(cnt[1]+cnt[2]+cnt[3]+cnt[4]+cnt[5])>n) rr FL;
     rr 0;
}
// #define fgo(x, y, a)	speed(i); time; mgo(vx=x, vy=y, va=a)
// #define fgo2	vm[0]=z*cos(d-deg); vm[1]=z*sin(d-deg); fgo(vx*g, vy*g, va*g)
void aa(int_xyav){
	 y=-y;
     a*=-10;
     ffor{
          fgo(vx, vy, va);
     }
}
void TD(int_xyav, int ag){
     y=-y;
     a*=-10;ag*=-10;
     ffor2{
          fgo2;
     }
}
void TD2(int_xyav, int ag){
     int ir=ir_in();
     y=-y;
     a*=-10;ag*=-10;
     cnt[1]=0;
     ffor2{
          if(abs(x)>abs(y)) count(1, (ir&6)==6||(ir&12)==12); else count(1, ir&4);
          fgo2;
     }
}
void tq(int_xyav){
     y=-y;
     a*=-10;
     db r=fabs(a*PI/1800);
     aa(x*r, y*r, a, v);
}

void dd(int a, int v, int_sp){
     int x=0, y=0;

     ffor{
          z=i<30? i*1.2f/30: 1.2;
          fgo(z*v*cos(deg), -z*v*sin(deg), va);
     }
     if(sn) fw(0, -2000*sign(a), 0, fabs(vy), 0, sn, p, 0); else ee(p);
}

void CC(int nx, int sx, int ny, int sy, db ratio){
     int n=1, n1=9, n2=7; db z0, z1, z2, dx=3, dy=3, da=0.3, g=1;

     if(ny<6){dy=-3; da=-0.5; n1=2; n2=4;}
     if(nx&4){da=1.0; n1=6; n2=5;}
     do{
          if(++n<500) g=n/500.0f;
          if((psd[nx]-sx)<10) g=1;
          z0=sx? (psd[nx]-sx)*dx*g: 0;
          if((psd[ny]-sy)<10) g=1;
          z1=sy? (psd[ny]-sy)*dy*g: 0;
          z2=ratio? (psd[n1]-psd[n2]*ratio)*da: 0;
          if(fabs(z2)>10) z0=z1=0;
          z0=fmx(z0, 100); z1=fmx(z1, 100);
          mgo(z0, z1, z2);
     } while(fabs(z0/dx)>5*g||fabs(z1/dy)>5*g||fabs(z2/da)>3);
     mee();
}

void CC2(int nx, int sx, int ny, int sy, db ratio){
     int n=1, n1=8, n2=7; db z0, z1, z2, dx=3, dy=3, da=0.3, g=1;
     
     if(ny<6) dy=-3, da=-0.5, n1=3, n2=4;
     if(nx&4) da=1.0, n1=7, n2=4;
     do{
          if(++n<500) g=n/500.0f;
          if((psd[nx]-sx)<10) g=1;
          z0=sx? (psd[nx]-sx)*dx*g: 0;
          if((psd[ny]-sy)<10) g=1;
          z1=sy? (psd[ny]-sy)*dy*g: 0;
          z2=ratio? (psd[n1]-psd[n2]*ratio)*da: 0;
          if(fabs(z2)>10) z0=z1=0;
          z0=fmx(z0, 100); z1=fmx(z1, 100);
          mgo(z0, z1, z2);
     } while(fabs(z0/dx)>5*g||fabs(z1/dy)>5*g||fabs(z2/da)>3);
     mee();
}

void CC3(int nx, int sx, int ny, int sy, db ratio){
     int n=1, n1=8, n2=9; db z0, z1, z2, dx=3, dy=3, da=-0.3, g=1;
     
     if(ny<6) dy=-3, da=0.5, n1=3, n2=2; 
     if(nx&4) da=1.0, n1=6, n2=5;
     do{
          if(++n<500) g=n/500.0f;
          if((psd[nx]-sx)<10) g=1;
          z0=sx? (psd[nx]-sx)*dx*g: 0;
          if((psd[ny]-sy)<10) g=1;
          z1=sy? (psd[ny]-sy)*dy*g: 0;
          z2=ratio? (psd[n1]-psd[n2]*ratio)*da: 0;
          if(fabs(z2)>10) z0=z1=0;
          z0=fmx(z0, 100); z1=fmx(z1, 100);
          mgo(z0, z1, z2);
     } while(fabs(z0/dx)>5*g||fabs(z1/dy)>5*g||fabs(z2/da)>3);
     mee();
}

void ee(int n){
     db g;

     for(int i=n; i>=0; i--){
          g=(db)i/n;
          time; mgo(vx*g, vy*g, va*g);
     }
     mee();
}

void ee2(int n){ //stand ���� �� ����
     db g;

     for(int i=n; i>=0; i--){
          g=(db)i/n;
          mgo(vx*g, vy*g, va*g); _delay_ms(10);
     }
}

void ee3(int n){ //stand ���� �� ����
     db g;

     for(int i=0; i<n; i++){
          g=(db)i/n;
          mgo(vx*g, vy*g, va*g); _delay_ms(10);
     }
}



int fx(int_xyav, int ag, int sn, int s){ //sn : ������ ���� ��
     int ir;

     cnt[1]=cnt[2]=cnt[3]=cnt[4]=cnt[5]=0;
     sfor2{
          if(i>s){ir=xxf(sn); if(ir) rr ir;}
          fgo2;
     }
     rr 0;
}

int fw(int_xyav, int ag, int_sp, int s){
     sfor2{
          if(i>s){
               if(sn&&p>0) pstop;
               if(sn&&psd[sn]<-p) rr LOST;
          }
          fgo2;
     }
     rr 0;
}

int xx(int_xv, int_sp, int dir, int no, int mode){ //no : ������ ���� ����, mode : FLL/FLR ��� ����, ���(1), ����(0)
     int y=0, a=0, br=0, j=0, n=0, ir;

     if(x<0) ssx(20, 3); else ssx(5, 5);
     if(aup>0&&xxc(dir)<0) rr -1;
     ffor{
          ir=xxs(mode);
          if(++j>4800.0f/v&&ir>=FL) j=0, n++; //���� ������ �ּ� 5cm�̻��̾�� ��
          if(n==no) rr ir;
          if(sn) pstop;
          if(ir>=LOST) ir=br; else br=ir;
          fgo(vx*g, ir*lzig, ir*lhd*sign(x)); vy=va=0;
     }
     rr 0;
}

int  pb(int x, int a, int v, int rn, int range, int_sp, int s){ //p : ��ݼ� ������ 1, �ݼ� ������ 2, �Ѵ� ������ 4
     int y=0, dir, ir; db zig=0, hd=0, safety=0;

     if(rn==5||rn==6) a=-a;
     dir=sign(rn-6);
     if(!a&&x<0) ssw(0.5, 0.2); else ssw(1, 0.5);
     if(!s&&a&&x<0&&aup>0) aa(0, 0, -a*dir, 40);
     sfor{
          if(i>s){
               if(sn&&p>0) pstop;
               if(sn&&psd[sn]<-p) rr LOST;
               ir=xxf(p); if(!sn&&ir) rr ir;
               zig=hd=psd[rn]-range;
               if(p<0) plost;
          }
          speed(i); vx*=g;
          vy=vx*sin(a*PI/1800)*dir; if(x>0) vy=-vy;
          vx=vx*cos(a*PI/1800);
          time; mgo(vx, vy+dir*zig*wzig, dir*hd*whd*sign(x)); if(!a) vy=va=0;
     }
     rr 0;
}

int pb2(int x, int a, int v, int rn, int range, int_sp, int s){ //p : ��ݼ� ������ 1, �ݼ� ������ 2, �Ѵ� ������ 4
     int y=0, dir, ir; db zig=0, hd=0, safety=0;

     if(rn==5||rn==6) a=-a;
     dir=sign(rn-6);
     if(!a&&x<0) ssw(0.5, 0.2); else ssw(1, 0.5);
     if(!s&&a&&x<0&&aup>0) aa(0, 0, -a*dir, 40);
     cnt[1]=0;
     sfor{
          if(i>s){
               ir=ir_in();
               count(1, (ir&6)==6||(ir&12)==12);
               if(sn&&p>0) pstop;
               if(sn&&psd[sn]<-p) rr LOST;
               zig=hd=psd[rn]-range;
               if(p<0) plost;
          }
          speed(i); vx*=g;
          vy=vx*sin(a*PI/1800)*dir; if(x>0) vy=-vy;
          vx=vx*cos(a*PI/1800);
          time; mgo(vx, vy+dir*zig*wzig, dir*hd*whd*sign(x)); if(!a) vy=va=0;
     }
     rr 0;
}

//�ҿ������� ���� ����ϴ� ��� ���, ������ rn�� 2�� ���, rn2�� 9�� ���
int wp(int x, int a, int v, int rn, int range, int rn2, int range2, int_sp, int s){
     int y=0, dir, ir; db zig=0, hd=0;

     if(rn==5||rn==6) a=-a;
     dir=sign(rn-6);
     if(!s&&a&&x<0&&aup>0) aa(0, 0, -a*dir, 40);

     sfor{
          if(i>s){
               if(sn&&p>0) pstop;
               if(sn&&psd[sn]<-p) rr LOST;
               ir=xxf(p); if(!sn&&ir) rr ir;
               dir=sign(rn-6); a=abs(a);
               if(rn==5||rn==6) a=-a;
               if(psd[rn]>range-30) zig=hd=psd[rn]-range;
               else if(psd[rn2]>range2-10){zig=hd=psd[rn2]-range2; dir=sign(rn2-6); a=-a;}
               else zig=hd=0;
          }
          speed(i); vx*=g;
          vy=vx*sin(a*PI/1800)*dir; if(x>0) vy=-vy;
          vx=vx*cos(a*PI/1800);
          time; mgo(vx, vy+dir*zig*wzig, dir*hd*whd*sign(x));
     }
     rr 0;
}

int yw(int y, int a, int v, int rn, int range, db ratio, int_sp, int s){
     int x=0, dir=1, n1=6, n2=5, ir;  db zig=0, hd=0, safety=0;

     sfor{
          if(i>s){
               if(sn&&p>0) pstop;
               if(sn&&psd[sn]<-p) rr LOST;
               ir=xxf(p); if(!sn&&ir) rr ir;
               hd=psd[n1]-psd[n2]*ratio;
               if(abs(hd)<5) zig=psd[rn]-range;
               if(p<0) plost;
          }
          speed(i); vy*=g;
          vx=vy*sin(a*PI/1800);
          vy=vy*cos(a*PI/1800);
          time; mgo(vx+dir*zig*wzig, vy, hd*whd);
     }
     rr 0;
}

int gm(int mode){
    vuc i=0;

    vcam_n=0; memset(vcam, 0, sizeof(vcam));
    while(!vcam_n){_delay_ms(1); if(++i>200) break;} //���ᵿ�۽� �����ϰ�, _delay_ms(200);
    rr gm2(mode, 0);
}

int gm2(int mode, int c){ //1-��������, 2-��������, 3-�ָ�������, 4-����������
     vuc i, j, n=0, buff[5], *vp, *vp2, *dp, m=mode<3? 1: 2; //����, y��ǥ, x��ǥ, yũ��, xũ��

     vp=&vcam[1][0]; dp=&vcam_data[1][0];
     for(i=1; i<vcam_n+1; ++i){
          if(((c&&*dp==c)||!c)&&*(dp+1)>=ys&&*(dp+1)<=yb&&*(dp+2)>=xs&&*(dp+2)<=xb){
               n++;
               *vp=*dp; vp++; dp++; //����
               *vp=*dp; vp++; dp++; //y��ǥ
               *vp=*dp; vp++; dp++; //x��ǥ
               *vp=*dp; vp++; dp++; //yũ��
               *vp=*dp; vp++; dp++; //xũ��
          }
          else dp+=5;
     }
     for(i=1; i<n; ++i) for(j=i+1; j<n+1; ++j){
          if(((mode%2)&&vcam[i][m]>vcam[j][m])||(!(mode%2)&&vcam[i][m]<vcam[j][m])){
               vp=&vcam[i][0]; vp2=&vcam[j][0]; dp=&buff[0];
               *dp=*vp; *vp=*vp2; *vp2=*dp; dp++; vp++; vp2++; //����
               *dp=*vp; *vp=*vp2; *vp2=*dp; dp++; vp++; vp2++; //y��ǥ
               *dp=*vp; *vp=*vp2; *vp2=*dp; dp++; vp++; vp2++; //x��ǥ
               *dp=*vp; *vp=*vp2; *vp2=*dp; dp++; vp++; vp2++; //yũ��
               *dp=*vp; *vp=*vp2; *vp2=*dp; dp++; vp++; vp2++; //xũ��
          }
     }
     rr n;
}
int CD(int mode, int cn, int_xyav, int cx, int cy, int tx, int s){
     vuc x1=0, y1=0; int up=aup, dn=adn; db g1=1, g2=1;

     sfor{
          gm2(mode, 0);
          x1=x? vcam[cn][2]: cx; y1=y||a? vcam[cn][1]: cy;
          if(i>s&&y1){
               if(abs(x1-cx)<5&&abs(y1-cy)<3){
                    if(tx) ssa(30, 30), aa(tx, 0, 0, 200), ssa(up, dn);
                    rr FC;
               }
               z=fmx((cy-y1)/1.8f, 80);
               g1=gra(cx-v/10, x1, cx); g2=y>0? (db)(cy-y1)/cy: y1? (db)(y1-cy)/cy: 1;
          }
          fgo(fmx(vx*g1, 120), fmx(vy*g2, 120), z*va); va=0;
     }
     rr 0;
}