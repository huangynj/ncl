C
C	$Id: gqfaci.f,v 1.5 2008-07-27 00:20:59 haley Exp $
C                                                                      
C                Copyright (C)  2000
C        University Corporation for Atmospheric Research
C                All Rights Reserved
C
C The use of this Software is governed by a License Agreement.
C
      SUBROUTINE GQFACI(ERRIND,COLI)
C
C  INQUIRE FILL AREA COLOUR INDEX
C
      include 'gkscom.h'
C
      INTEGER ERRIND,COLI
C
C  Check if GKS is in the proper state.
C
      CALL GZCKST(8,-1,ERRIND)
      IF (ERRIND.EQ.0) THEN
       COLI = CFACI
      ELSE
       COLI = -1
      ENDIF
C
      RETURN
      END
