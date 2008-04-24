C
C $Id: mdqtra.f,v 1.1 2008-04-18 04:09:20 kennison Exp $
C
C                Copyright (C)  2000
C        University Corporation for Atmospheric Research
C                All Rights Reserved
C
C This file is free software; you can redistribute it and/or modify
C it under the terms of the GNU General Public License as published
C by the Free Software Foundation; either version 2 of the License, or
C (at your option) any later version.
C
C This software is distributed in the hope that it will be useful, but
C WITHOUT ANY WARRANTY; without even the implied warranty of
C MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
C General Public License for more details.
C
C You should have received a copy of the GNU General Public License
C along with this software; if not, write to the Free Software
C Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
C USA.
C
      SUBROUTINE MDQTRA (RLAT,RLON,UVAL,VVAL)
C
        DOUBLE PRECISION RLAT,RLON,UVAL,VVAL
C
C Declare a special common block, containing only those variables that
C MDQINI needs to set to make MDQTRA, MDQTRI, and MDQTRN carry out the
C transformation in effect at the time MDQINI was called.
C
        COMMON /MAQCMN/  ALFA,COSO,COSR,DCSA,DCSB,DSNA,DSNB,DTOR,DTRH,
     +                   OOPI,PHOC,  PI,PIOT,ROTA,RTDD,RTOD,SALT,SINO,
     +                   SINR,SRSS,SSMO,TOPI,UCNM,UMNM,UMXM,UOFF,URNM,
     +                   VCNM,VMNM,VMXM,VOFF,VRNM,UTPA,IPRF,IPRJ,IROD,
     +                   ELPM
        DOUBLE PRECISION ALFA,COSO,COSR,DCSA,DCSB,DSNA,DSNB,DTOR,DTRH,
     +                   OOPI,PHOC,  PI,PIOT,ROTA,RTDD,RTOD,SALT,SINO,
     +                   SINR,SRSS,SSMO,TOPI,UCNM,UMNM,UMXM,UOFF,URNM,
     +                   VCNM,VMNM,VMXM,VOFF,VRNM,UTPA(15)
C
        INTEGER IPRF,IPRJ,IROD
C
        LOGICAL ELPM
C
        SAVE   /MAQCMN/
C
C Check for an uncleared prior error.
C
        IF (ICFELL('MDQTRA - UNCLEARED PRIOR ERROR',1).NE.0) RETURN
C
C The call to MDQTRA is simply passed on to MDQTRN, but the values
C returned are checked to see if the point lies outside the perimeter;
C if so, the value 1.D12 is substituted for UVAL.
C
        CALL MDQTRN (RLAT,RLON,UVAL,VVAL)
        IF (ICFELL('MDQTRA',2).NE.0) RETURN
C
        IF (ELPM) THEN
          IF (((UVAL-UCNM)/URNM)**2+
     +        ((VVAL-VCNM)/VRNM)**2.GT.1.000002D0) THEN
            UVAL=1.D12
            VVAL=1.D12
          END IF
        ELSE
          IF (UVAL.LT.UMNM.OR.UVAL.GT.UMXM.OR.
     +        VVAL.LT.VMNM.OR.VVAL.GT.VMXM) THEN
            UVAL=1.D12
            VVAL=1.D12
          END IF
        END IF
C
        RETURN
C
      END