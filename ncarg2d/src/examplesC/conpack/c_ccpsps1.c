/*
 * $Id: c_ccpsps1.c,v 1.4 1994-08-23 22:50:20 haley Exp $
 */

#include <stdio.h>

#include <ncarg/ncargC.h>
#include <ncarg/gks.h>

#define K    9
#define N    7
#define LRWK    1000
#define LIWK    1000
#define LZDT    2000

#define WSTYPE SED_WSTYPE
#define WKID   1

main()
{
    float z[N][K], zdat[LZDT], rwrk[LRWK];
    int j;
    int iwrk[LIWK];
    extern void getdat(), mark();

    getdat (z);
/*
 * Open GKS
 */
	gopen_gks ("stdout",0);
	gopen_ws (WKID, NULL, WSTYPE);
	gactivate_ws(WKID);
/*
 * Initialize Conpack
 */
    c_cpsps1((float *)z,K,K,N,rwrk,LRWK,iwrk,LIWK,zdat,LZDT);
/*
 * Draw perimeter
 */
    c_cpback(zdat, rwrk, iwrk);
/*
 * Use a different line attribute on every line drawn
 * Draw Contours
 */
    c_cpcldr(zdat,rwrk,iwrk);
/*
 * Mark data points
 */
    mark ();
/*
 * Close frame and close GKS
 */
    c_frame();
	gdeactivate_ws(WKID);
	gclose_ws(WKID);
	gclose_gks();
}

void getdat (z)
float *z;
{
    int i, j, l;

    l = 0;
    for( j = 1; j <= N; j++ ) {
        for( i = 1; i <= K; i++ ) {
            z[l++] = 10.e-5*(-16.*(float)(i*i*j) + 34.*(float)(i*j*j) - (float)(6*i) + 93.);
        }
    }
    return;
}

void mark()
{
    int i, j, idum5;
    float x[1], y[1];
    float dum1, dum2, dum3, dum4, xmin, xmax, ymin, ymax;
    int idum;

    c_getset(&dum1,&dum2,&dum3,&dum4,&xmin,&xmax,&ymin,&ymax,&idum5);
    gset_marker_size(.5);

    for( i = 1; i <= K; i++ ) {
        for( j = 1; j <= N; j++ ) {
            x[0] = (float)(i-1)*(xmax-xmin)/(float)(K-1)+xmin;
            y[0] = (float)(j-1)*(ymax-ymin)/(float)(N-1)+ymin;
            c_points (x, y, 1, -4, 0);
        }
    }
    return;
}

