#include <string.h>
#include <stdio.h>
#include <ncarg/hlu/App.h>
#include <ncarg/hlu/NcgmWorkstation.h>
#include <ncarg/hlu/PSWorkstation.h>
#include <ncarg/hlu/XWorkstation.h>
#include "wrapper.h"

extern NGCALLF(tdttri,tdttri)(float *,float *,float*,int *,int *, float *,
                              float *,float *,int *,int *,int *,float *, 
                              float *,float *,float *,float *,float *);

extern NGCALLF(tditri,tditri)(float *,int *,float *,int *, float *,int *,
                              float *,int *,int *,float *,float *,int *,
			      int *, int *);

extern NGCALLF(tdstri,TDSTRI)(float *,int *,float *,int *,float *,int *,
			      float *,int *,int *,int *);

extern NGCALLF(tdez1d,TDEZ1D)(int *,float *,float *,float*,int *,float *,
                              float *,float *,float *,float *,int *);

NhlErrorTypes tdinit_W( void )
{
/*
 * Input variables
 */
  float *mid, *orig, *third, *otep;

/*
 * Retrieve parameters.
 *
 * Note that any of the pointer parameters can be set to NULL,
 * which implies you don't care about its value.
 */
  mid = (float*)NclGetArgValue(
          0,
          4,
          NULL,
          NULL,
          NULL,
          NULL,
          NULL,
          2);

  orig = (float*)NclGetArgValue(
          1,
          4,
          NULL,
          NULL,
          NULL,
          NULL,
          NULL,
          2);

  third = (float*)NclGetArgValue(
          2,
          4,
          NULL,
          NULL,
          NULL,
          NULL,
          NULL,
          2);

  otep = (float*)NclGetArgValue(
          3,
          4,
          NULL,
          NULL,
          NULL,
          NULL,
          NULL,
          2);

  c_tdinit(mid[0],mid[1],mid[2],orig[0],orig[1],orig[2],
           third[0],third[1],third[2],*otep);

  return(NhlNOERROR);
}


NhlErrorTypes tdpara_W( void )
{
/*
 * Input variables
 */
  float *a00, *v10, *v01;

/*
 * Retrieve parameters.
 *
 * Note that any of the pointer parameters can be set to NULL,
 * which implies you don't care about its value.
 */
  a00 = (float*)NclGetArgValue(
          0,
          3,
          NULL,
          NULL,
          NULL,
          NULL,
          NULL,
          2);

  v10 = (float*)NclGetArgValue(
          1,
          3,
          NULL,
          NULL,
          NULL,
          NULL,
          NULL,
          2);

  v01 = (float*)NclGetArgValue(
          2,
          3,
          NULL,
          NULL,
          NULL,
          NULL,
          NULL,
          2);

  c_tdpara(a00[0],a00[1],a00[2],v10[0],v10[1],v10[2],v01[0],v01[1],v01[2]);

  return(NhlNOERROR);
}


NhlErrorTypes tdclrs_W( void )
{
/*
 *  Definte a variable to store the HLU object identifier.
 */
  NclHLUObj tmp_hlu_obj;

  int *nwid, *ibow, *iofc, *iolc, *ilmt;
  float *shde, *shdr;
  int gkswid, grlist, nid;

/*
 * Retrieve parameters.
 *
 * Note any of the pointer parameters can be set to NULL, which
 * implies you don't care about its value. In this example
 * the type parameter is set to NULL because the function
 * is later registered to only accept floating point numbers.
 */
  nwid =    (int*)NclGetArgValue(0,7,NULL,NULL,NULL,NULL,NULL,2);
  ibow =    (int*)NclGetArgValue(1,7,NULL,NULL,NULL,NULL,NULL,2);
  shde =  (float*)NclGetArgValue(2,7,NULL,NULL,NULL,NULL,NULL,2);
  shdr =  (float*)NclGetArgValue(3,7,NULL,NULL,NULL,NULL,NULL,2);
  iofc =    (int*)NclGetArgValue(4,7,NULL,NULL,NULL,NULL,NULL,2);
  iolc =    (int*)NclGetArgValue(5,7,NULL,NULL,NULL,NULL,NULL,2);
  ilmt =    (int*)NclGetArgValue(6,7,NULL,NULL,NULL,NULL,NULL,2);

/*
 *  Determine the NCL identifier for the graphic object in nid.
 */
  tmp_hlu_obj = (NclHLUObj) _NclGetObj(*nwid);
  nid = tmp_hlu_obj->hlu.hlu_id;
/*
 * Retrieve the GKS workstation id from the workstation object.
 */
  grlist = NhlRLCreate(NhlGETRL);
  NhlRLClear(grlist);
  NhlRLGetInteger(grlist,NhlNwkGksWorkId,&gkswid);
  NhlGetValues(nid,grlist);

  gactivate_ws (gkswid);
  c_tdclrs(gkswid, *ibow, *shde, *shdr, *iofc, *iolc, *ilmt);
  gdeactivate_ws (gkswid);

  return(NhlNOERROR);
}


NhlErrorTypes tdgetp_W(void)
{
/*
 *  Get values for tdpack parameters.
 */
  char  *arg1;
  int   numpi, numpf, i;
  string *pvalue, *qvalue;

/*
 *  List the integer and float parameter names.  To add new ones,
 *  all that needs to be done is add the names to this list.
 */
  char *params_i[] = {"cs1", "cs2", "fov", "hnd", "ifc1", "ifc2", 
                      "ifc3", "ifc4", "ilc1", "ilc2", "iltd",
                      "lsu", "lsv", "lsw", "set", "shd", "ste", 
                      "CS1", "CS2", "FOV", "HND", "IFC1", "IFC2", 
                      "IFC3", "IFC4", "ILC1", "ILC2", "ILTD",
                      "LSU", "LSV", "LSW", "SET", "SHD", "STE", 
  };
  char *params_f[] = {"cs1", "cs2", "fov", "lsu", "lsv", "lsw", 
                      "vpb", "vpl", "vpr", "vpt", "ustp", "vstp", "wstp"
                      "CS1", "CS2", "FOV", "LSU", "LSV", "LSW", 
                      "VPB", "VPL", "VPR", "VPT", "USTP", "VSTP", "WSTP"
  };
/*
 * Input array variable
 */
  string *pname;
  int ndims_pname, dsizes_pname[NCL_MAX_DIMENSIONS];
  float *fval;
  int *ival;
  int ret_size = 1; 

/*
 * Retrieve argument #1
 */
  pname = (string *) NclGetArgValue(
          0,
          1,
          &ndims_pname,
          dsizes_pname,
          NULL,
          NULL,
          NULL,
          2);

  arg1 = NrmQuarkToString(*pname);

/*
 *  Check to see if the parameter name is valid.
 */
  numpi = sizeof(params_i)/sizeof(void *);
  numpf = sizeof(params_f)/sizeof(void *);
  for (i = 0; i < numpi; i++) {
    if (!strncmp(arg1, params_i[i], strlen(params_i[i]))) {
      goto OK_NAME;
    }
  }
  for (i = 0; i < numpf; i++) {
    if (!strncmp(arg1, params_f[i], strlen(params_f[i]))) {
      goto OK_NAME;
    }
  }
  NhlPError(NhlFATAL, NhlEUNKNOWN, "tdgetp: unrecognized parameter name");
  return(NhlFATAL);

/*
 *  Process the parameter if it has an integer value.
 */
OK_NAME:  for (i = 0; i < numpi; i++) {
    if (!strncmp(arg1, params_i[i], strlen(params_i[i]))) {
      ival = (int *) calloc(1,sizeof(int));
      c_tdgeti(arg1, ival);
      return(NclReturnValue( (void *) ival, 1, &ret_size, NULL, NCL_int, 0));
    }
  }

/*
 *  Process the parameter if it has a float value.
 */
  for (i = 0; i < numpf; i++) {
    if (!strncmp(arg1, params_f[i], strlen(params_f[i]))) {
      fval = (float *) calloc(1,sizeof(float));
      c_tdgetr(arg1, fval);
      return(NclReturnValue((void *) fval, 1, &ret_size, NULL, NCL_float, 0));
    }
  }

  NhlPError(NhlFATAL, NhlEUNKNOWN, "tdgetp: impossible to get this message");
  return(NhlFATAL);
}

NhlErrorTypes tdgtrs_W( void )
{
/*
 * Input variables
 */
  int *irst, *ifc1, *ifc2, *ifc3, *ifc4, *ilc1, *ilc2, *iltd;
  float *ustp, *vstp, *wstp;

/*
 * Retrieve parameters.
 *
 * Note that any of the pointer parameters can be set to NULL,
 * which implies you don't care about its value.
 */
  irst =   (int*)NclGetArgValue( 0,11,NULL,NULL,NULL,NULL,NULL,2);
  ifc1 =   (int*)NclGetArgValue( 1,11,NULL,NULL,NULL,NULL,NULL,2);
  ifc2 =   (int*)NclGetArgValue( 2,11,NULL,NULL,NULL,NULL,NULL,2);
  ifc3 =   (int*)NclGetArgValue( 3,11,NULL,NULL,NULL,NULL,NULL,2);
  ifc4 =   (int*)NclGetArgValue( 4,11,NULL,NULL,NULL,NULL,NULL,2);
  ilc1 =   (int*)NclGetArgValue( 5,11,NULL,NULL,NULL,NULL,NULL,2);
  ilc2 =   (int*)NclGetArgValue( 6,11,NULL,NULL,NULL,NULL,NULL,2);
  iltd =   (int*)NclGetArgValue( 7,11,NULL,NULL,NULL,NULL,NULL,2);
  ustp = (float*)NclGetArgValue( 8,11,NULL,NULL,NULL,NULL,NULL,2);
  vstp = (float*)NclGetArgValue( 9,11,NULL,NULL,NULL,NULL,NULL,2);
  wstp = (float*)NclGetArgValue(10,11,NULL,NULL,NULL,NULL,NULL,2);

  c_tdgtrs(*irst,ifc1,ifc2,ifc3,ifc4,ilc1,ilc2,iltd,ustp,vstp,vstp);

  return(NhlNOERROR);
}


/*
 * The tdsetp_W code is based on Fred Clare's wmsetp_W code.
 */

NhlErrorTypes tdsetp_W(void)
{
  char  *arg1;
  int   numpi, numpf, i, j;

/*
 *  List the integer and float parameter names.  To add new ones,
 *  all that needs to be done is add the names to this list.
 */
  char *params_i[] = {"cs1", "cs2", "fov", "hnd", "ifc1", "ifc2", 
                      "ifc3", "ifc4", "ilc1", "ilc2", "iltd",
                      "lsu", "lsv", "lsw", "set", "shd", "ste", 
                      "CS1", "CS2", "FOV", "HND", "IFC1", "IFC2", 
                      "IFC3", "IFC4", "ILC1", "ILC2", "ILTD",
                      "LSU", "LSV", "LSW", "SET", "SHD", "STE", 
  };
  char *params_f[] = {"cs1", "cs2", "fov", "lsu", "lsv", "lsw", 
                      "vpb", "vpl", "vpr", "vpt", "ustp", "vstp", "wstp"
                      "CS1", "CS2", "FOV", "LSU", "LSV", "LSW", 
                      "VPB", "VPL", "VPR", "VPT", "USTP", "VSTP", "WSTP"
  };
/*
 * Input array variables
 */
  string *pname;
  int ndims_pname, dsizes_pname[NCL_MAX_DIMENSIONS];
  void *pvalue;
  int ndims_pvalue, dsizes_pvalue[NCL_MAX_DIMENSIONS];
  NclBasicDataTypes type_pvalue;

/*
 * Retrieve argument #1
 */
  pname = (string *) NclGetArgValue(
          0,
          2,
          &ndims_pname,
          dsizes_pname,
          NULL,
          NULL,
          NULL,
          2);

  arg1 = NrmQuarkToString(*pname);
 
/*
 *  Check to see if the parameter name is valid.
 */
  numpi = sizeof(params_i)/sizeof(void *);
  numpf = sizeof(params_f)/sizeof(void *);
  for (i = 0; i < numpi; i++) {
    if (!strncmp(arg1, params_i[i], strlen(params_i[i]))) {
      goto OK_NAME;
    }
  }
  for (i = 0; i < numpf; i++) {
    if (!strncmp(arg1, params_f[i], strlen(params_f[i]))) {
      goto OK_NAME;
    }
  }
  NhlPError(NhlFATAL, NhlEUNKNOWN, "tdsetp: unrecognized parameter name");
  return(NhlFATAL);

/*
 * Retrieve argument #2
 */
OK_NAME: pvalue = (void *) NclGetArgValue(
           1,
           2,
           &ndims_pvalue,
           dsizes_pvalue,
           NULL,
           NULL,
           &type_pvalue,
           2);

/*
 *  Process the parameter if it has an integer value.
 */
  if (type_pvalue == NCL_int) {
    for (i = 0; i < numpi; i++) {
      if (!strncmp(arg1, params_i[i], strlen(params_i[i]))) {
        j = *((int *) pvalue);
        c_tdseti(arg1, j);
        return(NhlNOERROR);
      }
    }
    NhlPError(NhlFATAL, NhlEUNKNOWN, "tdsetp: The specified value for the parameter has an invalid type");
    return(NhlFATAL);
  }
  else if (type_pvalue == NCL_float || type_pvalue == NCL_double) {

/*
 *  Process the parameter if it has a float value or double value.
 */
    for (i = 0; i < numpf; i++) {
      if (!strncmp(arg1, params_f[i], strlen(params_f[i]))) {
        if (type_pvalue == NCL_float) {
          c_tdsetr(arg1, *((float *) pvalue));
          return(NhlNOERROR);
        }
        else if (type_pvalue == NCL_double) {
          c_tdsetr(arg1, (float) *((double *) pvalue));
          return(NhlNOERROR);
        }
      }
    }
    NhlPError(NhlFATAL, NhlEUNKNOWN, "tdsetp: The specified value for the parameter has an invalid type");
    return(NhlFATAL);
  }
  else {
    NhlPError(NhlFATAL, NhlEUNKNOWN, "tdsetp: The specified value for the "
              "parameter has an incorrect type");
    return(NhlFATAL);
  }
}



/*
 * The pcsetp_W code is based on Fred Clare's wmsetp_W code.
 */

NhlErrorTypes pcsetp_W(void)
{
  char  *arg1;
  int   numpi, numpf, i, j;

/*
 *  List the integer and float parameter names.  To add new ones,
 *  all that needs to be done is add the names to this list.
 */
  char *params_i[] = {"fn","of","FN","OF"};
  char *params_f[] = {"ol","oc","OL","OC"};
/*
 * Input array variables
 */
  string *pname;
  int ndims_pname, dsizes_pname[NCL_MAX_DIMENSIONS];
  void *pvalue;
  int ndims_pvalue, dsizes_pvalue[NCL_MAX_DIMENSIONS];
  NclBasicDataTypes type_pvalue;

/*
 * Retrieve argument #1
 */
  pname = (string *) NclGetArgValue(
          0,
          2,
          &ndims_pname,
          dsizes_pname,
          NULL,
          NULL,
          NULL,
          2);

  arg1 = NrmQuarkToString(*pname);
 
/*
 *  Check to see if the parameter name is valid.
 */
  numpi = sizeof(params_i)/sizeof(void *);
  numpf = sizeof(params_f)/sizeof(void *);
  for (i = 0; i < numpi; i++) {
    if (!strncmp(arg1, params_i[i], strlen(params_i[i]))) {
      goto OK_NAME;
    }
  }
  for (i = 0; i < numpf; i++) {
    if (!strncmp(arg1, params_f[i], strlen(params_f[i]))) {
      goto OK_NAME;
    }
  }
  NhlPError(NhlFATAL, NhlEUNKNOWN, "pcsetp: unrecognized parameter name");
  return(NhlFATAL);

/*
 * Retrieve argument #2
 */
OK_NAME: pvalue = (void *) NclGetArgValue(
           1,
           2,
           &ndims_pvalue,
           dsizes_pvalue,
           NULL,
           NULL,
           &type_pvalue,
           2);

/*
 *  Process the parameter if it has an integer value.
 */
  if (type_pvalue == NCL_int) {
    for (i = 0; i < numpi; i++) {
      if (!strncmp(arg1, params_i[i], strlen(params_i[i]))) {
        j = *((int *) pvalue);
        c_pcseti(arg1, j);
        return(NhlNOERROR);
      }
    }
    NhlPError(NhlFATAL, NhlEUNKNOWN, "pcsetp: The specified value for the parameter has an invalid type");
    return(NhlFATAL);
  }
  else if (type_pvalue == NCL_float || type_pvalue == NCL_double) {

/*
 *  Process the parameter if it has a float value or double value.
 */
    for (i = 0; i < numpf; i++) {
      if (!strncmp(arg1, params_f[i], strlen(params_f[i]))) {
        if (type_pvalue == NCL_float) {
          c_pcsetr(arg1, *((float *) pvalue));
          return(NhlNOERROR);
        }
        else if (type_pvalue == NCL_double) {
          c_pcsetr(arg1, (float) *((double *) pvalue));
          return(NhlNOERROR);
        }
      }
    }
    NhlPError(NhlFATAL, NhlEUNKNOWN, "pcsetp: The specified value for the parameter has an invalid type");
    return(NhlFATAL);
  }
  else {
    NhlPError(NhlFATAL, NhlEUNKNOWN, "pcsetp: The specified value for the "
              "parameter has an incorrect type");
    return(NhlFATAL);
  }
}



NhlErrorTypes tdstrs_W( void )
{
/*
 * Input variables
 */
  int *irst, *ifc1, *ifc2, *ifc3, *ifc4, *ilc1, *ilc2, *iltd;
  float *ustp, *vstp, *wstp;

/*
 * Retrieve parameters.
 *
 * Note that any of the pointer parameters can be set to NULL,
 * which implies you don't care about its value.
 */
  irst =   (int*)NclGetArgValue( 0,11,NULL,NULL,NULL,NULL,NULL,2);
  ifc1 =   (int*)NclGetArgValue( 1,11,NULL,NULL,NULL,NULL,NULL,2);
  ifc2 =   (int*)NclGetArgValue( 2,11,NULL,NULL,NULL,NULL,NULL,2);
  ifc3 =   (int*)NclGetArgValue( 3,11,NULL,NULL,NULL,NULL,NULL,2);
  ifc4 =   (int*)NclGetArgValue( 4,11,NULL,NULL,NULL,NULL,NULL,2);
  ilc1 =   (int*)NclGetArgValue( 5,11,NULL,NULL,NULL,NULL,NULL,2);
  ilc2 =   (int*)NclGetArgValue( 6,11,NULL,NULL,NULL,NULL,NULL,2);
  iltd =   (int*)NclGetArgValue( 7,11,NULL,NULL,NULL,NULL,NULL,2);
  ustp = (float*)NclGetArgValue( 8,11,NULL,NULL,NULL,NULL,NULL,2);
  vstp = (float*)NclGetArgValue( 9,11,NULL,NULL,NULL,NULL,NULL,2);
  wstp = (float*)NclGetArgValue(10,11,NULL,NULL,NULL,NULL,NULL,2);

  c_tdstrs(*irst,*ifc1,*ifc2,*ifc3,*ifc4,*ilc1,*ilc2,*iltd,
           *ustp,*vstp,*vstp);

  return(NhlNOERROR);
}


NhlErrorTypes tdprpt_W( void )
{
  float *uvw, xy[2];
  int dsizes_xy[1];

/*
 * Retrieve parameter.
 */
  uvw = (float*)NclGetArgValue(0,1,NULL,NULL,NULL,NULL,NULL,2);

  c_tdprpt(uvw[0], uvw[1], uvw[2], &xy[0], &xy[1]);
  
  dsizes_xy[0] = 2;
  return(NclReturnValue( (void *) xy, 1, dsizes_xy, NULL, NCL_float, 0));
}


NhlErrorTypes tdprpa_W( void )
{
  float *xy_in, xy_out[2];
  int dsizes_xy[1];

/*
 * Retrieve parameter.
 */
  xy_in = (float*)NclGetArgValue(0,1,NULL,NULL,NULL,NULL,NULL,2);

  c_tdprpa(xy_in[0], xy_in[1], &xy_out[0], &xy_out[1]);
  
  dsizes_xy[0] = 2;
  return(NclReturnValue( (void *) xy_out, 1, dsizes_xy, NULL, NCL_float, 0));
}


NhlErrorTypes tdprpi_W( void )
{
  float *xy_in, xy_out[2];
  int dsizes_xy[1];

/*
 * Retrieve parameter.
 */
  xy_in = (float*)NclGetArgValue(0,1,NULL,NULL,NULL,NULL,NULL,2);

  c_tdprpi(xy_in[0], xy_in[1], &xy_out[0], &xy_out[1]);
  
  dsizes_xy[0] = 2;
  return(NclReturnValue( (void *) xy_out, 1, dsizes_xy, NULL, NCL_float, 0));
}


NhlErrorTypes tdline_W( void )
{
  int *nwid;
  float *uvw1, *uvw2;
/*
 * Variables for retrieving workstation information.
 */
  int grlist, gkswid, nid;
  NclHLUObj tmp_hlu_obj;

/*
 * Retrieve parameters.
 */
  nwid =   (int*)NclGetArgValue(0,3,NULL,NULL,NULL,NULL,NULL,2);
  uvw1 = (float*)NclGetArgValue(1,3,NULL,NULL,NULL,NULL,NULL,2);
  uvw2 = (float*)NclGetArgValue(2,3,NULL,NULL,NULL,NULL,NULL,2);

/*
 *  Determine the NCL identifier for the graphic object in nid.
 */
  tmp_hlu_obj = (NclHLUObj) _NclGetObj(*nwid);
  nid         = tmp_hlu_obj->hlu.hlu_id;

/*
 * Retrieve the GKS workstation id from the workstation object.
 */
  grlist = NhlRLCreate(NhlGETRL);
  NhlRLClear(grlist);
  NhlRLGetInteger(grlist, NhlNwkGksWorkId, &gkswid);
  NhlGetValues(nid, grlist);
 
/*
 * The following section activates the workstation, calls the 
 * c_tdline function, and then deactivates the workstation.
 */
  gactivate_ws (gkswid);
  c_tdline(uvw1[0], uvw1[1], uvw1[2], uvw2[0], uvw2[1], uvw2[2]);
  gdeactivate_ws (gkswid);

  return(NhlNOERROR);
}


NhlErrorTypes tdlnpa_W( void )
{
  int *nwid;
  float *uvw1, *uvw2;
/*
 * Variables for retrieving workstation information.
 */
  int grlist, gkswid, nid;
  NclHLUObj tmp_hlu_obj;

/*
 * Retrieve parameters.
 */
  nwid =   (int*)NclGetArgValue(0,3,NULL,NULL,NULL,NULL,NULL,2);
  uvw1 = (float*)NclGetArgValue(1,3,NULL,NULL,NULL,NULL,NULL,2);
  uvw2 = (float*)NclGetArgValue(2,3,NULL,NULL,NULL,NULL,NULL,2);

/*
 *  Determine the NCL identifier for the graphic object in nid.
 */
  tmp_hlu_obj = (NclHLUObj) _NclGetObj(*nwid);
  nid         = tmp_hlu_obj->hlu.hlu_id;

/*
 * Retrieve the GKS workstation id from the workstation object.
 */
  grlist = NhlRLCreate(NhlGETRL);
  NhlRLClear(grlist);
  NhlRLGetInteger(grlist, NhlNwkGksWorkId, &gkswid);
  NhlGetValues(nid, grlist);
 
/*
 * The following section activates the workstation, calls the 
 * c_tdlnpa function, and then deactivates the workstation.
 */
  gactivate_ws (gkswid);
  c_tdlnpa(uvw1[0], uvw1[1], uvw2[0], uvw2[1]);
  gdeactivate_ws (gkswid);

  return(NhlNOERROR);
}


NhlErrorTypes tdgrds_W( void )
{
  int *nwid, *igrt, *ihid;
  float *uvwmin, *uvwmax, *uvwstp;
/*
 * Variables for retrieving workstation information.
 */
  int grlist, gkswid, nid;
  NclHLUObj tmp_hlu_obj;

/*
 * Retrieve parameters.
 */
  nwid   =   (int*)NclGetArgValue(0,6,NULL,NULL,NULL,NULL,NULL,2);
  uvwmin = (float*)NclGetArgValue(1,6,NULL,NULL,NULL,NULL,NULL,2);
  uvwmax = (float*)NclGetArgValue(2,6,NULL,NULL,NULL,NULL,NULL,2);
  uvwstp = (float*)NclGetArgValue(3,6,NULL,NULL,NULL,NULL,NULL,2);
  igrt   =   (int*)NclGetArgValue(4,6,NULL,NULL,NULL,NULL,NULL,2);
  ihid   =   (int*)NclGetArgValue(5,6,NULL,NULL,NULL,NULL,NULL,2);

/*
 *  Determine the NCL identifier for the graphic object in nid.
 */
  tmp_hlu_obj = (NclHLUObj) _NclGetObj(*nwid);
  nid         = tmp_hlu_obj->hlu.hlu_id;

/*
 * Retrieve the GKS workstation id from the workstation object.
 */
  grlist = NhlRLCreate(NhlGETRL);
  NhlRLClear(grlist);
  NhlRLGetInteger(grlist, NhlNwkGksWorkId, &gkswid);
  NhlGetValues(nid, grlist);
 
/*
 * The following section activates the workstation, calls the 
 * c_tdgrds function, and then deactivates the workstation.
 */
  gactivate_ws (gkswid);
  c_tdgrds(uvwmin[0], uvwmin[1], uvwmin[2], uvwmax[0], uvwmax[1], uvwmax[2],
           uvwstp[0], uvwstp[1], uvwstp[2], *igrt, *ihid);
  gdeactivate_ws (gkswid);

  return(NhlNOERROR);
}


NhlErrorTypes tdgrid_W( void )
{
  int *nwid, *noxs, *noys, *igrd;
  float *xbeg, *xstp, *ybeg, *ystp;
/*
 * Variables for retrieving workstation information.
 */
  int grlist, gkswid, nid;
  NclHLUObj tmp_hlu_obj;

/*
 * Retrieve parameters.
 */
  nwid =   (int*)NclGetArgValue(0,8,NULL,NULL,NULL,NULL,NULL,2);
  xbeg = (float*)NclGetArgValue(1,8,NULL,NULL,NULL,NULL,NULL,2);
  xstp = (float*)NclGetArgValue(2,8,NULL,NULL,NULL,NULL,NULL,2);
  noxs =   (int*)NclGetArgValue(3,8,NULL,NULL,NULL,NULL,NULL,2);
  ybeg = (float*)NclGetArgValue(4,8,NULL,NULL,NULL,NULL,NULL,2);
  ystp = (float*)NclGetArgValue(5,8,NULL,NULL,NULL,NULL,NULL,2);
  noys =   (int*)NclGetArgValue(6,8,NULL,NULL,NULL,NULL,NULL,2);
  igrd =   (int*)NclGetArgValue(7,8,NULL,NULL,NULL,NULL,NULL,2);

/*
 *  Determine the NCL identifier for the graphic object in nid.
 */
  tmp_hlu_obj = (NclHLUObj) _NclGetObj(*nwid);
  nid         = tmp_hlu_obj->hlu.hlu_id;

/*
 * Retrieve the GKS workstation id from the workstation object.
 */
  grlist = NhlRLCreate(NhlGETRL);
  NhlRLClear(grlist);
  NhlRLGetInteger(grlist, NhlNwkGksWorkId, &gkswid);
  NhlGetValues(nid, grlist);
 
/*
 * The following section activates the workstation, calls the 
 * c_tdgrid function, and then deactivates the workstation.
 */
  gactivate_ws (gkswid);
  c_tdgrid(*xbeg, *xstp, *noxs, *ybeg, *ystp, *noys, *igrd);
  gdeactivate_ws (gkswid);

  return(NhlNOERROR);
}


NhlErrorTypes tdlbls_W( void )
{
  int *nwid, *ipck;
  float *uvwmn, *uvwmx;
  string *uvwn, *uvwi;
  char *cuvwn0, *cuvwi0, *cuvwn1, *cuvwi1, *cuvwn2, *cuvwi2;
/*
 * Variables for retrieving workstation information.
 */
  int grlist, gkswid, nid;
  NclHLUObj tmp_hlu_obj;

/*
 * Retrieve parameters.
 */
  nwid  =    (int*)NclGetArgValue(0,6,NULL,NULL,NULL,NULL,NULL,2);
  uvwmn =  (float*)NclGetArgValue(1,6,NULL,NULL,NULL,NULL,NULL,2);
  uvwmx =  (float*)NclGetArgValue(2,6,NULL,NULL,NULL,NULL,NULL,2);
  uvwn  = (string*)NclGetArgValue(3,6,NULL,NULL,NULL,NULL,NULL,2);
  uvwi  = (string*)NclGetArgValue(4,6,NULL,NULL,NULL,NULL,NULL,2);
  ipck  =    (int*)NclGetArgValue(5,6,NULL,NULL,NULL,NULL,NULL,2);

  cuvwn0 = NrmQuarkToString(uvwn[0]);
  cuvwi0 = NrmQuarkToString(uvwi[0]);
  cuvwn1 = NrmQuarkToString(uvwn[1]);
  cuvwi1 = NrmQuarkToString(uvwi[1]);
  cuvwn2 = NrmQuarkToString(uvwn[2]);
  cuvwi2 = NrmQuarkToString(uvwi[2]);
/*
 *  Determine the NCL identifier for the graphic object in nid.
 */
  tmp_hlu_obj = (NclHLUObj) _NclGetObj(*nwid);
  nid         = tmp_hlu_obj->hlu.hlu_id;

/*
 * Retrieve the GKS workstation id from the workstation object.
 */
  grlist = NhlRLCreate(NhlGETRL);
  NhlRLClear(grlist);
  NhlRLGetInteger(grlist, NhlNwkGksWorkId, &gkswid);
  NhlGetValues(nid, grlist);
 
/*
 * The following section activates the workstation, calls the 
 * c_tdlbls function, and then deactivates the workstation.
 */
  gactivate_ws (gkswid);
  c_tdlbls(uvwmn[0], uvwmn[1], uvwmn[2], uvwmx[0], uvwmx[1], uvwmx[2],
           cuvwn0, cuvwn1, cuvwn2, cuvwi0, cuvwi1, cuvwi2, *ipck);
  gdeactivate_ws (gkswid);

  return(NhlNOERROR);
}


NhlErrorTypes tdlbla_W( void )
{
  int *nwid, *iaxs;
  float *xat, *yat, *angd;
  string *ilbl, *nlbl;
  char *cilbl, *cnlbl;
/*
 * Variables for retrieving workstation information.
 */
  int grlist, gkswid, nid;
  NclHLUObj tmp_hlu_obj;

/*
 * Retrieve parameters.
 */
  nwid =    (int*)NclGetArgValue(0,7,NULL,NULL,NULL,NULL,NULL,2);
  iaxs =    (int*)NclGetArgValue(1,7,NULL,NULL,NULL,NULL,NULL,2);
  ilbl = (string*)NclGetArgValue(2,7,NULL,NULL,NULL,NULL,NULL,2);
  nlbl = (string*)NclGetArgValue(3,7,NULL,NULL,NULL,NULL,NULL,2);
  xat  =  (float*)NclGetArgValue(4,7,NULL,NULL,NULL,NULL,NULL,2);
  yat  =  (float*)NclGetArgValue(5,7,NULL,NULL,NULL,NULL,NULL,2);
  angd =  (float*)NclGetArgValue(6,7,NULL,NULL,NULL,NULL,NULL,2);

  cilbl = NrmQuarkToString(*ilbl);
  cnlbl = NrmQuarkToString(*nlbl);

/*
 *  Determine the NCL identifier for the graphic object in nid.
 */
  tmp_hlu_obj = (NclHLUObj) _NclGetObj(*nwid);
  nid         = tmp_hlu_obj->hlu.hlu_id;

/*
 * Retrieve the GKS workstation id from the workstation object.
 */
  grlist = NhlRLCreate(NhlGETRL);
  NhlRLClear(grlist);
  NhlRLGetInteger(grlist, NhlNwkGksWorkId, &gkswid);
  NhlGetValues(nid, grlist);
 
/*
 * The following section activates the workstation, calls the 
 * c_tdlbla function, and then deactivates the workstation.
 */
  gactivate_ws (gkswid);
  c_tdlbla(*iaxs, cilbl, cnlbl, xat[0], xat[1], yat[0], yat[1], *angd);
  gdeactivate_ws (gkswid);

  return(NhlNOERROR);
}


NhlErrorTypes tdplch_W( void )
{
  int *nwid, *iaxs;
  float *xpos, *ypos, *size, *angd, *cntr;
  string *chrs;
  char *cchrs;
/*
 * Variables for retrieving workstation information.
 */
  int grlist, gkswid, nid;
  NclHLUObj tmp_hlu_obj;

/*
 * Retrieve parameters.
 */
  nwid =    (int*)NclGetArgValue(0,7,NULL,NULL,NULL,NULL,NULL,2);
  xpos =  (float*)NclGetArgValue(1,7,NULL,NULL,NULL,NULL,NULL,2);
  ypos =  (float*)NclGetArgValue(2,7,NULL,NULL,NULL,NULL,NULL,2);
  chrs = (string*)NclGetArgValue(3,7,NULL,NULL,NULL,NULL,NULL,2);
  size =  (float*)NclGetArgValue(4,7,NULL,NULL,NULL,NULL,NULL,2);
  angd =  (float*)NclGetArgValue(6,7,NULL,NULL,NULL,NULL,NULL,2);
  cntr =  (float*)NclGetArgValue(6,7,NULL,NULL,NULL,NULL,NULL,2);

  cchrs = NrmQuarkToString(*chrs);

/*
 *  Determine the NCL identifier for the graphic object in nid.
 */
  tmp_hlu_obj = (NclHLUObj) _NclGetObj(*nwid);
  nid         = tmp_hlu_obj->hlu.hlu_id;

/*
 * Retrieve the GKS workstation id from the workstation object.
 */
  grlist = NhlRLCreate(NhlGETRL);
  NhlRLClear(grlist);
  NhlRLGetInteger(grlist, NhlNwkGksWorkId, &gkswid);
  NhlGetValues(nid, grlist);
 
/*
 * The following section activates the workstation, calls the 
 * c_tdplch function, and then deactivates the workstation.
 */
  gactivate_ws (gkswid);
  c_tdplch(*xpos, *ypos, cchrs, *size, *angd, *cntr);
  gdeactivate_ws (gkswid);

  return(NhlNOERROR);
}


NhlErrorTypes tddtri_W( void )
{
  int *nwid, *ntri, *itwk, mtri, dsizes_rtri[2];
  float *rtri;
/*
 * Variables for retrieving workstation information.
 */
  int grlist, gkswid, nid;
  NclHLUObj tmp_hlu_obj;

/*
 * Retrieve parameters.
 */
  nwid =   (int*)NclGetArgValue(0,4,NULL,NULL,NULL,NULL,NULL,2);
  rtri = (float*)NclGetArgValue(1,4,NULL,dsizes_rtri,NULL,NULL,NULL,2);
  ntri =   (int*)NclGetArgValue(2,4,NULL,NULL,NULL,NULL,NULL,2);
  itwk =   (int*)NclGetArgValue(3,4,NULL,NULL,NULL,NULL,NULL,2);

  mtri = dsizes_rtri[0];
  if(dsizes_rtri[1] != 10) {
    NhlPError(NhlFATAL, NhlEUNKNOWN, "tddtri: the second dimension of ntri must be 10");
    return(NhlFATAL);
  }
/*
 *  Determine the NCL identifier for the graphic object in nid.
 */
  tmp_hlu_obj = (NclHLUObj) _NclGetObj(*nwid);
  nid         = tmp_hlu_obj->hlu.hlu_id;

/*
 * Retrieve the GKS workstation id from the workstation object.
 */
  grlist = NhlRLCreate(NhlGETRL);
  NhlRLClear(grlist);
  NhlRLGetInteger(grlist, NhlNwkGksWorkId, &gkswid);
  NhlGetValues(nid, grlist);
 
/*
 * The following section activates the workstation, calls the 
 * c_tddtri function, and then deactivates the workstation.
 */
  gactivate_ws (gkswid);
  c_tddtri(rtri, mtri, ntri, itwk);
  gdeactivate_ws (gkswid);

  return(NhlNOERROR);
}


NhlErrorTypes tdstri_W( void )
{
  float *u, *v, *w, *rtri;
  int *idim, *jdim, *ntri, mtri, *irst;
  int dsizes_w[2], dsizes_rtri[2];
/*
 * Retrieve parameters.
 */
  u    = (float*)NclGetArgValue(0,8,NULL,NULL,NULL,NULL,NULL,2);
  idim =   (int*)NclGetArgValue(1,8,NULL,NULL,NULL,NULL,NULL,2);
  v    = (float*)NclGetArgValue(2,8,NULL,NULL,NULL,NULL,NULL,2);
  jdim =   (int*)NclGetArgValue(3,8,NULL,NULL,NULL,NULL,NULL,2);
  w    = (float*)NclGetArgValue(4,8,NULL,dsizes_w,NULL,NULL,NULL,2);
  rtri = (float*)NclGetArgValue(5,8,NULL,dsizes_rtri,NULL,NULL,NULL,2);
  ntri =   (int*)NclGetArgValue(6,8,NULL,NULL,NULL,NULL,NULL,2);
  irst =   (int*)NclGetArgValue(7,8,NULL,NULL,NULL,NULL,NULL,2);

  mtri = dsizes_rtri[0];
  if(dsizes_rtri[1] != 10) {
    NhlPError(NhlFATAL, NhlEUNKNOWN, "tdstri: the second dimension of rtri must be 10");
    return(NhlFATAL);
  }

  if(dsizes_w[0] < *jdim || dsizes_w[1] < *idim) {
    NhlPError(NhlFATAL, NhlEUNKNOWN, "tdstri: the dimensions of w must greater than or equal to nv x nu");
    return(NhlFATAL);
  }

  NGCALLF(tdstri,TDSTRI)(u, idim, v, jdim, w, &dsizes_w[1], rtri, &mtri, ntri,
			 irst);

  if(*ntri == mtri) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"tdstri: triangle list overflow");
    return(NhlFATAL);
  }

  return(NhlNOERROR);
}


NhlErrorTypes tditri_W( void )
{
  float *u, *v, *w, *f, *fiso, *rtri;
  int *idim, *jdim, *kdim, *ntri, mtri, *irst;
  int dsizes_f[3], dsizes_rtri[2];
/*
 * Retrieve parameters.
 */
  u    = (float*)NclGetArgValue( 0,11,NULL,NULL,NULL,NULL,NULL,2);
  idim =   (int*)NclGetArgValue( 1,11,NULL,NULL,NULL,NULL,NULL,2);
  v    = (float*)NclGetArgValue( 2,11,NULL,NULL,NULL,NULL,NULL,2);
  jdim =   (int*)NclGetArgValue( 3,11,NULL,NULL,NULL,NULL,NULL,2);
  w    = (float*)NclGetArgValue( 4,11,NULL,NULL,NULL,NULL,NULL,2);
  kdim =   (int*)NclGetArgValue( 5,11,NULL,NULL,NULL,NULL,NULL,2);
  f    = (float*)NclGetArgValue( 6,11,NULL,dsizes_f,NULL,NULL,NULL,2);
  fiso = (float*)NclGetArgValue( 7,11,NULL,NULL,NULL,NULL,NULL,2);
  rtri = (float*)NclGetArgValue( 8,11,NULL,dsizes_rtri,NULL,NULL,NULL,2);
  ntri =   (int*)NclGetArgValue( 9,11,NULL,NULL,NULL,NULL,NULL,2);
  irst =   (int*)NclGetArgValue(10,11,NULL,NULL,NULL,NULL,NULL,2);

  mtri = dsizes_rtri[0];
  if(dsizes_rtri[1] != 10) {
    NhlPError(NhlFATAL, NhlEUNKNOWN, "tditri: the second dimension of ntri must be 10");
    return(NhlFATAL);
  }

  if(dsizes_f[0] < *kdim || dsizes_f[1] < *jdim || dsizes_f[2] < *idim) {
    NhlPError(NhlFATAL, NhlEUNKNOWN, "tditri: the dimensions of f must be greater than or equal to nw x nv x nu");
    return(NhlFATAL);
  }

  NGCALLF(tditri,TDITRI)(u,idim,v,jdim,w,kdim,f,&dsizes_f[2],&dsizes_f[1],
			 fiso,rtri,&mtri,ntri,irst);

  if(*ntri == mtri) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"tditri: triangle list overflow");
    return(NhlFATAL);
  }

  return(NhlNOERROR);
}


NhlErrorTypes tdmtri_W( void )
{
  float *u, *v, *w, *s, *rtri;
  float *umin, *vmin, *wmin, *umax, *vmax, *wmax;
  int *imrk, *ntri, mtri, *irst;
  int dsizes_rtri[2];
/*
 * Retrieve parameters.
 */
  imrk =   (int*)NclGetArgValue( 0,14,NULL,NULL,NULL,NULL,NULL,2);
  u    = (float*)NclGetArgValue( 1,14,NULL,NULL,NULL,NULL,NULL,2);
  v    = (float*)NclGetArgValue( 2,14,NULL,NULL,NULL,NULL,NULL,2);
  w    = (float*)NclGetArgValue( 3,14,NULL,NULL,NULL,NULL,NULL,2);
  s    = (float*)NclGetArgValue( 4,14,NULL,NULL,NULL,NULL,NULL,2);
  rtri = (float*)NclGetArgValue( 5,14,NULL,dsizes_rtri,NULL,NULL,NULL,2);
  ntri =   (int*)NclGetArgValue( 6,14,NULL,NULL,NULL,NULL,NULL,2);
  irst =   (int*)NclGetArgValue( 7,14,NULL,NULL,NULL,NULL,NULL,2);
  umin = (float*)NclGetArgValue( 8,14,NULL,NULL,NULL,NULL,NULL,2);
  vmin = (float*)NclGetArgValue( 9,14,NULL,NULL,NULL,NULL,NULL,2);
  wmin = (float*)NclGetArgValue(10,14,NULL,NULL,NULL,NULL,NULL,2);
  umax = (float*)NclGetArgValue(11,14,NULL,NULL,NULL,NULL,NULL,2);
  vmax = (float*)NclGetArgValue(12,14,NULL,NULL,NULL,NULL,NULL,2);
  wmax = (float*)NclGetArgValue(13,14,NULL,NULL,NULL,NULL,NULL,2);

  mtri = dsizes_rtri[0];
  if(dsizes_rtri[1] != 10) {
    NhlPError(NhlFATAL, NhlEUNKNOWN, "tdmtri: the second dimension of ntri must be 10");
    return(NhlFATAL);
  }

  c_tdmtri(*imrk, *u, *v, *w, *s, rtri, mtri, ntri, *irst, 
           *umin, *vmin, *wmin, *umax, *vmax, *wmax);

  if(*ntri == mtri) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"tdmtri: triangle list overflow");
    return(NhlFATAL);
  }

  return(NhlNOERROR);
}


NhlErrorTypes tdttri_W( void )
{
  float *ucra, *vcra, *wcra, *umin, *vmin, *wmin, *umax, *vmax, *wmax;
  float *rmrk, *smrk, *rtri;
  int *imrk, *ntri, *irst, mtri, ncra;
  int dsizes_rtri[2], dsizes_ucra[1], dsizes_vcra[1], dsizes_wcra[1];
/*
 * Retrieve parameters.
 */
  ucra = (float*)NclGetArgValue( 0,15,NULL,dsizes_ucra,NULL,NULL,NULL,2);
  vcra = (float*)NclGetArgValue( 1,15,NULL,dsizes_vcra,NULL,NULL,NULL,2);
  wcra = (float*)NclGetArgValue( 2,15,NULL,dsizes_wcra,NULL,NULL,NULL,2);

  imrk =   (int*)NclGetArgValue( 3,15,NULL,NULL,NULL,NULL,NULL,2);
  rmrk = (float*)NclGetArgValue( 4,15,NULL,NULL,NULL,NULL,NULL,2);
  smrk = (float*)NclGetArgValue( 5,15,NULL,NULL,NULL,NULL,NULL,2);

  rtri = (float*)NclGetArgValue( 6,15,NULL,dsizes_rtri,NULL,NULL,NULL,2);
  ntri =   (int*)NclGetArgValue( 7,15,NULL,NULL,NULL,NULL,NULL,2);
  irst =   (int*)NclGetArgValue( 8,15,NULL,NULL,NULL,NULL,NULL,2);

  umin = (float*)NclGetArgValue( 9,15,NULL,NULL,NULL,NULL,NULL,2);
  vmin = (float*)NclGetArgValue(10,15,NULL,NULL,NULL,NULL,NULL,2);
  wmin = (float*)NclGetArgValue(11,15,NULL,NULL,NULL,NULL,NULL,2);
  umax = (float*)NclGetArgValue(12,15,NULL,NULL,NULL,NULL,NULL,2);
  vmax = (float*)NclGetArgValue(13,15,NULL,NULL,NULL,NULL,NULL,2);
  wmax = (float*)NclGetArgValue(14,15,NULL,NULL,NULL,NULL,NULL,2);

  mtri = dsizes_rtri[0];
  if(dsizes_rtri[1] != 10) {
    NhlPError(NhlFATAL, NhlEUNKNOWN, "tdttri: the second dimension of ntri must be 10");
    return(NhlFATAL);
  }

  ncra = dsizes_ucra[0];
  if(dsizes_vcra[0] != ncra || dsizes_wcra[0] != ncra) {
    NhlPError(NhlFATAL, NhlEUNKNOWN, "tdttri: ucra, vcra, and wcra must all be the same length");
    return(NhlFATAL);
  }

  NGCALLF(tdttri,TDTTRI)(ucra, vcra, wcra, &ncra, imrk, rmrk, smrk, rtri, 
                         &mtri, ntri, irst, 
                         umin, vmin, wmin, umax, vmax, wmax);

  if(*ntri == mtri) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"tdttri: triangle list overflow");
    return(NhlFATAL);
  }

  return(NhlNOERROR);
}


NhlErrorTypes tdctri_W( void )
{
  float *rtri, *rcut;
  int *ntri, *iaxs, mtri, dsizes_rtri[2];

/*
 * Retrieve parameters.
 */
  rtri = (float*)NclGetArgValue(0,4,NULL,dsizes_rtri,NULL,NULL,NULL,2);
  ntri =   (int*)NclGetArgValue(1,4,NULL,NULL,NULL,NULL,NULL,2);
  iaxs =   (int*)NclGetArgValue(2,4,NULL,NULL,NULL,NULL,NULL,2);
  rcut = (float*)NclGetArgValue(3,4,NULL,NULL,NULL,NULL,NULL,2);

  mtri = dsizes_rtri[0];
  if(dsizes_rtri[1] != 10) {
    NhlPError(NhlFATAL, NhlEUNKNOWN, "tdctri: the second dimension of ntri must be 10");
    return(NhlFATAL);
  }
  c_tdctri(rtri, mtri, ntri, *iaxs, *rcut);

  if(*ntri == mtri) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"tdctri: triangle list overflow");
    return(NhlFATAL);
  }

  return(NhlNOERROR);
}


NhlErrorTypes tdotri_W( void )
{
  int *ntri, mtri, *iord, dsizes_rtri[2];
  float *rtri;
/*
 * Work arrays.
 */
  float *rtwk;
  int *itwk;
/*
 * Retrieve parameters.
 */
  rtri = (float*)NclGetArgValue(0,5,NULL,dsizes_rtri,NULL,NULL,NULL,2);
  ntri =   (int*)NclGetArgValue(1,5,NULL,NULL,NULL,NULL,NULL,2);
  rtwk = (float*)NclGetArgValue(2,5,NULL,NULL,NULL,NULL,NULL,2);
  itwk =   (int*)NclGetArgValue(3,5,NULL,NULL,NULL,NULL,NULL,2);
  iord =   (int*)NclGetArgValue(4,5,NULL,NULL,NULL,NULL,NULL,2);

  mtri = dsizes_rtri[0];
  if(dsizes_rtri[1] != 10) {
    NhlPError(NhlFATAL, NhlEUNKNOWN, "tdotri: the second dimension of ntri must be 10");
    return(NhlFATAL);
  }

  c_tdotri(rtri, mtri, ntri, rtwk, itwk, *iord);

  if(*ntri == mtri) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"tdotri: triangle list overflow");
    return(NhlFATAL);
  }

  return(NhlNOERROR);
}


NhlErrorTypes tdsort_W( void )
{
  float *rwrk;
  int *iwrk, *iord, nwrk;
  int dsizes_rwrk[1], dsizes_iwrk[1];
/*
 * Retrieve parameters.
 */
  rwrk = (float*)NclGetArgValue(0,3,NULL,dsizes_rwrk,NULL,NULL,NULL,2);
  iord =   (int*)NclGetArgValue(1,3,NULL,NULL,NULL,NULL,NULL,2);
  iwrk =   (int*)NclGetArgValue(2,3,NULL,dsizes_iwrk,NULL,NULL,NULL,2);
  nwrk = dsizes_rwrk[0];

  if(dsizes_iwrk[0] != nwrk) {
    NhlPError(NhlFATAL, NhlEUNKNOWN, "tdsort: the two work arrays, rwrk and iwrk must be the same length");
    return(NhlFATAL);
  }

  c_tdsort(rwrk, nwrk, *iord, iwrk);

  return(NhlNOERROR);
}


NhlErrorTypes tdez2d_W( void )
{
  float *x, *y, *z, *zp;
  int dsizes_x[NCL_MAX_DIMENSIONS];
  int dsizes_y[NCL_MAX_DIMENSIONS];
  int dsizes_z[NCL_MAX_DIMENSIONS];
  float *rmult, *theta, *phi;
  int *style, *nwid;
  int i, j;
/*
 * Variables for retrieving workstation information.
 */
  int grlist, gkswid, nid;
  NclHLUObj tmp_hlu_obj;
/*
 * Retrieve parameters.
 *
 * Note any of the pointer parameters can be set to NULL, which
 * implies you don't care about its value. In this example
 * the type parameter is set to NULL because the function
 * is later registered to only accept floating point numbers.
 */
  nwid   = (int*)NclGetArgValue(0,8,NULL,NULL,NULL,NULL,NULL,2);
  x      = (float*)NclGetArgValue(1,8, NULL, dsizes_x, NULL,NULL,NULL,2);
  y      = (float*)NclGetArgValue(2,8, NULL, dsizes_y, NULL,NULL,NULL,2);
  z      = (float*)NclGetArgValue(3,8, NULL, dsizes_z, NULL,NULL,NULL,2);
  rmult  = (float*)NclGetArgValue(4,8,NULL,NULL,NULL,NULL,NULL,2);
  theta  = (float*)NclGetArgValue(5,8,NULL,NULL,NULL,NULL,NULL,2);
  phi    = (float*)NclGetArgValue(6,8,NULL,NULL,NULL,NULL,NULL,2);
  style  = (int*)NclGetArgValue(7,8,NULL,NULL,NULL,NULL,NULL,2);

/*
 * Check input sizes.
 */
  if( (dsizes_x[0] == dsizes_z[0]) && (dsizes_y[0] == dsizes_z[1]) ) {
/*
 * Reverse the order of the dimensions.
 */
    zp = (float *) calloc(dsizes_x[0] * dsizes_y[0],sizeof(float));
    for (i = 0; i < dsizes_x[0]; i++) {
      for (j = 0; j < dsizes_y[0]; j++) { 
        zp[j*dsizes_x[0] + i] = z[i*dsizes_y[0] + j];
      }
    }
/*
 *  Determine the NCL identifier for the graphic object in nid.
 */
    tmp_hlu_obj = (NclHLUObj) _NclGetObj(*nwid);
    nid         = tmp_hlu_obj->hlu.hlu_id;
/*
 * Retrieve the GKS workstation id from the workstation object.
 */
    grlist = NhlRLCreate(NhlGETRL);
    NhlRLClear(grlist);
    NhlRLGetInteger(grlist,NhlNwkGksWorkId,&gkswid);
    NhlGetValues(nid,grlist);
 
/*
 * The following section activates the workstation, calls the 
 * c_tdez2d function, and then deactivates the workstation.
 */
    gactivate_ws (gkswid);
    c_tdez2d(dsizes_x[0],dsizes_y[0],x,y,zp,*rmult,*theta,*phi,*style);
    gdeactivate_ws (gkswid);
    free(zp);
  }
  else { 
    NhlPError(NhlFATAL,NhlEUNKNOWN,"tdez2d: the dimension sizes of z must be the dimension of x by the dimension of y");
    return(NhlFATAL);
  }

  return(NhlNOERROR);
  
}


NhlErrorTypes tdez3d_W( void )
{
  float *x, *y, *z, *u, *value, *up;
  int dsizes_x[NCL_MAX_DIMENSIONS];
  int dsizes_y[NCL_MAX_DIMENSIONS];
  int dsizes_z[NCL_MAX_DIMENSIONS];
  int dsizes_u[NCL_MAX_DIMENSIONS];
  float *rmult, *theta, *phi;
  int *nwid, *style;
/*
 * Variables for retrieving workstation information.
 */
  int grlist, gkswid, nid;
  NclHLUObj tmp_hlu_obj;

  int i, j, k;
/*
 * Retrieve parameters.
 *
 * Note any of the pointer parameters can be set to NULL, which
 * implies you don't care about its value. In this example
 * the type parameter is set to NULL because the function
 * is later registered to only accept floating point numbers.
 */
  nwid  =  (int*)NclGetArgValue(0,10,NULL,NULL,NULL,NULL,NULL,2);
  x     =  (float*)NclGetArgValue(1,10, NULL, dsizes_x, NULL,NULL,NULL,2);
  y     =  (float*)NclGetArgValue(2,10, NULL, dsizes_y, NULL,NULL,NULL,2);
  z     =  (float*)NclGetArgValue(3,10, NULL, dsizes_z, NULL,NULL,NULL,2);
  u     =  (float*)NclGetArgValue(4,10, NULL, dsizes_u, NULL,NULL,NULL,2);
  value = (float*)NclGetArgValue(5,10,NULL,NULL,NULL,NULL,NULL,2);
  rmult = (float*)NclGetArgValue(6,10,NULL,NULL,NULL,NULL,NULL,2);
  theta = (float*)NclGetArgValue(7,10,NULL,NULL,NULL,NULL,NULL,2);
  phi   = (float*)NclGetArgValue(8,10,NULL,NULL,NULL,NULL,NULL,2);
  style = (int*)NclGetArgValue(9,10,NULL,NULL,NULL,NULL,NULL,2);

/*
 * Check input sizes.
 */
  if( (dsizes_x[0] == dsizes_u[0]) && (dsizes_y[0] == dsizes_u[1]) && 
      (dsizes_z[0] == dsizes_u[2]) ) {
/*
 * Reverse the order of the dimensions.
 */
    up = (float *) calloc(dsizes_x[0]*dsizes_y[0]*dsizes_z[0],sizeof(float));
    for (i = 0; i < dsizes_x[0]; i++) {
      for (j = 0; j < dsizes_y[0]; j++) { 
        for (k = 0; k < dsizes_z[0]; k++) { 
          up[dsizes_x[0]*dsizes_y[0]*k + j*dsizes_x[0] + i] = 
            u[i*dsizes_z[0]*dsizes_y[0] + dsizes_z[0]*j + k];
        }
      }
    }

/*
 *  Determine the NCL identifier for the graphic object in nid.
 */
    tmp_hlu_obj = (NclHLUObj) _NclGetObj(*nwid);
    nid         = tmp_hlu_obj->hlu.hlu_id;
 
/*
 * Retrieve the GKS workstation id from the workstation object.
 */
    grlist = NhlRLCreate(NhlGETRL);
    NhlRLClear(grlist);
    NhlRLGetInteger(grlist,NhlNwkGksWorkId,&gkswid);
    NhlGetValues(nid,grlist);

/*
 * The following section activates the workstation, calls the 
 * c_tdez3d function, and then deactivates the workstation.
 */
    gactivate_ws (gkswid);
    c_tdez3d(dsizes_x[0],dsizes_y[0],dsizes_z[0],x,y,z,up,*value,
             *rmult,*theta,*phi,*style);
    gdeactivate_ws (gkswid);
    free(up);
  }
  else {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"tdez3d: the dimension sizes of u must be the dimension of x by the dimension of y by the dimension of z");
    return(NhlFATAL);
  }
  return(NhlNOERROR);
  
}


NhlErrorTypes tdez1d_W( void )
{
  int *nwid, *imrk, *style;
  float *x, *y, *z, *rmrk, *smrk, *rmult, *theta, *phi;
  int dsizes_x[1], dsizes_y[1], dsizes_z[1];
/*
 * Variables for retrieving workstation information.
 */
  int grlist, gkswid, nid;
  NclHLUObj tmp_hlu_obj;
/*
 * Retrieve parameters.
 *
 * Note any of the pointer parameters can be set to NULL, which
 * implies you don't care about its value. In this example
 * the type parameter is set to NULL because the function
 * is later registered to only accept floating point numbers.
 */
  nwid   =   (int*)NclGetArgValue( 0,11,NULL,NULL,NULL,NULL,NULL,2);
  x      = (float*)NclGetArgValue( 1,11,NULL,dsizes_x,NULL,NULL,NULL,2);
  y      = (float*)NclGetArgValue( 2,11,NULL,dsizes_y,NULL,NULL,NULL,2);
  z      = (float*)NclGetArgValue( 3,11,NULL,dsizes_z,NULL,NULL,NULL,2);
  imrk   =   (int*)NclGetArgValue( 4,11,NULL,NULL,NULL,NULL,NULL,2);
  rmrk   = (float*)NclGetArgValue( 5,11,NULL,NULL,NULL,NULL,NULL,2);
  smrk   = (float*)NclGetArgValue( 6,11,NULL,NULL,NULL,NULL,NULL,2);
  rmult  = (float*)NclGetArgValue( 7,11,NULL,NULL,NULL,NULL,NULL,2);
  theta  = (float*)NclGetArgValue( 8,11,NULL,NULL,NULL,NULL,NULL,2);
  phi    = (float*)NclGetArgValue( 9,11,NULL,NULL,NULL,NULL,NULL,2);
  style  =   (int*)NclGetArgValue(10,11,NULL,NULL,NULL,NULL,NULL,2);
/*
 * Check the input sizes.
 */
  if( dsizes_x[0] != dsizes_y[0] || dsizes_x[0] != dsizes_z[0] ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"tdez1d: the length of the x, y, and z arrays must be the same");
    return(NhlFATAL);
  }
/*
 *  Determine the NCL identifier for the graphic object in nid.
 */
  tmp_hlu_obj = (NclHLUObj) _NclGetObj(*nwid);
  nid         = tmp_hlu_obj->hlu.hlu_id;
/*
 * Retrieve the GKS workstation id from the workstation object.
 */
  grlist = NhlRLCreate(NhlGETRL);
  NhlRLClear(grlist);
  NhlRLGetInteger(grlist,NhlNwkGksWorkId,&gkswid);
  NhlGetValues(nid,grlist);
 
/*
 * The following section activates the workstation, calls the 
 * tdez1d function, and then deactivates the workstation.
 */
  gactivate_ws (gkswid);
  NGCALLF(tdez1d,TDEZ1D)(&dsizes_x[0],x,y,z,imrk,rmrk,smrk,rmult,theta,phi,
                         style);
  gdeactivate_ws (gkswid);

  return(NhlNOERROR);
}
