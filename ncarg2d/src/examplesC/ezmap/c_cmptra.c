/*
 * $Id: c_cmptra.c,v 1.1 1994-05-13 14:26:25 haley Exp $
 */

#include <stdio.h>

#include <ncarg/ncargC.h>
#include <ncarg/gks.h>

main()
{
    float plim1[2], plim2[2], plim3[2], plim4[2];
/*
 * Open GKS, Turn Clipping off
 */
	c_opngks(); 
/*
 * INVOKE DEMO DRIVER
 */
    plim1[0] = 22.;
    plim2[0] = -120.;
    plim3[0] = 47.;
    plim4[0] = -65.;
	cmptra("OR",35.,-105.,0.,"PO","CO",plim1,plim2,plim3,plim4);
/*
 *     DEACTIVATE AND CLOSE WORKSTATION, CLOSE GKS.
 */
	c_clsgks();
}

cmptra(proj, plat, plon, rota, outln, jlim, plim1, plim2, plim3, plim4)
char proj[3], outln[3], jlim[3];
float plim1[2], plim2[2], plim3[2], plim4[2];
float plat, plon, rota;
{
    float x, y;
/*
 * CMPTRA demonstrates marking points on a map
 *
 * Draw Continental, political outlines 
 */
	c_mapstc ("OU - OUTLINE DATASET SELECTOR",outln);
/*
 * Set up projection
 */
	c_maproj (proj,plat,plon,rota);
/*
 * If it"s a satellite projection, choose a satellite distance
 */
	if ( !strcmp(proj, "SV") ) c_mapstr ("SA - SATELLITE DISTANCE",5.);
/*
 * Set limits of map
 */
	c_mapset (jlim,plim1,plim2,plim3,plim4);
/*
 * Turn off Grid lines
 */
	c_mapstr ("GR",0.);
/*
 * Draw map
 */
	c_mapdrw();
/*
 * Draw a star over Boulder Colorado
 */
	c_maptra(40.,-105.15,&x,&y);
	if ( x != 1.e12) c_points (&x, &y, 1, -3, 0);
/*
 * Draw the state of Colorado in
 */
	c_mapit (37.,-109.,0);
	c_mapit (41.,-109.,1);
	c_mapit (41.,-102.,1);
	c_mapit (37.,-102.,1);
	c_mapit (37.,-109.,1);
	c_mapiq();
/*
 * Advance the frame.
 */
	c_frame();
/*
 * Done.
 */
	return;
}
