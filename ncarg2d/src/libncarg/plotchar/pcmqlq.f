C
C $Id: pcmqlq.f,v 1.3 1992-11-18 02:14:05 kennison Exp $
C
C
C ---------------------------------------------------------------------
C
      SUBROUTINE PCMQLQ (XSUB,YSUB,CHRS,SIZE,ANGD,CNTR)
C
C When lower-quality characters have been selected by the user, this
C routine is called by PLCHHQ to write out the substrings, using one
C of the routines PLCHMQ or PLCHLQ.  The user may substitute his own
C version of this routine to call some other character-drawer.
C
C The arguments are identical to those of PLCHHQ.
C
      CHARACTER*(*) CHRS
C
C COMMON block declarations.
C
      COMMON /PCPRMS/ ADDS,CONS,DSTB,DSTL,DSTR,DSTT,HPIC(3),ICEN,IOUC,
     +                IOUF,IPCC,
     +                IQUF,ISHC,ISHF,ITEF,JCOD,NFCC,NODF,SHDX,SHDY,
     +                SIZA,SSIC,SSPR,SUBS,VPIC(3),WPIC(3),XBEG,XCEN,
     +                XEND,XMUL(3),YBEG,YCEN,YEND,YMUL(3)
      SAVE   /PCPRMS/
C
C Call the appropriate routine.
C
      IF (IQUF.EQ.1) THEN
        CALL PLCHMQ (XSUB,YSUB,CHRS,SIZE,ANGD,CNTR)
      ELSE
        CALL PLCHLQ (XSUB,YSUB,CHRS,SIZE,ANGD,CNTR)
      END IF
C
C Done.
C
      RETURN
C
      END
