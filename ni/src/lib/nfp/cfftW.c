#include <stdio.h>
#include <math.h>
#include "wrapper.h"

extern void NGCALLF(cfftfdriver,CFFTFDRIVER)(int*,double*,double*,double*,
                                             double*,int*);

NhlErrorTypes cfftf_W( void )
{
/*
 * Input array variables
 */
  void *x;
  int *opt;
  int size_x, ndims_x, dsizes_x[NCL_MAX_DIMENSIONS];
  NclBasicDataTypes type_x;
  NclScalar missing_x, missing_dx, missing_rx;
  int has_missing_x;
  double *tmp_x;
/*
 * Output array variables
 */
  void *cf;
  int ndims_cf, *dsizes_cf;
  double *tmp_cfa, *tmp_cfb;
  NclBasicDataTypes type_cf;
  NclTypeClass type_cf_class;
  NclScalar missing_cf;
/*
 * Attribute variables
 */
  void *frq;
  double *tmp_frq, fmsg = -999.;
  int *N;
  int att_id;
  int dsizes[1];
  NclMultiDValData att_md, return_md;
  NclVar tmp_var;
  NclStackEntry return_data;
/*
 * various
 */
  double *work;
  int i, j, npts, npts2, nwrk, index_x, index_cfb;
  int found_missing, any_missing, size_leftmost, size_cf;
/*
 * Retrieve parameters
 *
 * Note any of the pointer parameters can be set to NULL, which
 * implies you don't care about its value.
 */
  x = (void*)NclGetArgValue(
           0,
           2,
           &ndims_x, 
           dsizes_x,
           &missing_x,
           &has_missing_x,
           &type_x,
           2);

  opt = (int*)NclGetArgValue(
           1,
           2,
           NULL,
           NULL,
           NULL,
           NULL,
           NULL,
           2);
/*
 * Calculate number of leftmost elements and dimension sizes of output
 */
  ndims_cf     = ndims_x + 1;
  dsizes_cf = (int *)malloc(ndims_cf*sizeof(int));
  dsizes_cf[0] = 2;
  size_leftmost = 1;
  for( i = 0; i < ndims_x-1; i++ ) {
    size_leftmost *= dsizes_x[i];
    dsizes_cf[i+1] = dsizes_x[i];
  }
  dsizes_cf[ndims_x] = npts = dsizes_x[ndims_x-1];

/* Calculate size of output array. */
  npts2   = 2*npts;
  size_x  = size_leftmost * npts;
  size_cf = 2 * size_x;

/*
 * Coerce missing values.
 */
  coerce_missing(type_x,has_missing_x,&missing_x,&missing_dx,&missing_rx);
/*
 * Create space for temporary input array if necessary.
 */
  if(type_x != NCL_double) {
    tmp_x = (double*)calloc(npts,sizeof(double));
    if(tmp_x == NULL) {
      NhlPError(NhlFATAL,NhlEUNKNOWN,"cfftf: Unable to allocate memory for coercing input array to double precision");
      return(NhlFATAL);
    }
  }
/*
 * Allocate space for other arrays.
 */
  nwrk     = (4*npts) + 25;
  tmp_frq  = (double*)calloc(npts,sizeof(double));
  tmp_cfa  = (double*)calloc(npts,sizeof(double));
  tmp_cfb  = (double*)calloc(npts,sizeof(double));
  work     = (double*)calloc(nwrk,sizeof(double));
  N        = (void*)calloc(1,sizeof(int));
  if ( tmp_frq == NULL || tmp_cfa == NULL || tmp_cfb == NULL || \
       work == NULL || N == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"cfftf: Cannot allocate memory for temporary arrays" );
    return(NhlFATAL);
  }
  if(type_x == NCL_double) {
    cf   = (void*)calloc(size_cf,sizeof(double));
    frq  = (void*)calloc(size_x,sizeof(double));
    type_cf = NCL_double;
    if(has_missing_x) missing_cf = missing_dx;
  }
  else {
    cf   = (void*)calloc(size_cf,sizeof(float));
    frq  = (void*)calloc(size_x,sizeof(float));
    type_cf = NCL_float;
    if(has_missing_x) missing_cf = missing_rx;
  }
  if ( cf == NULL || frq == NULL) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"cfftf: Cannot allocate memory for output arrays" );
    return(NhlFATAL);
  }

/*
 * Call the f77 version of 'cfftfdriver' with the full argument list.
 */
  index_x   = 0;
  index_cfb = size_x;
  any_missing = 0;
  for(i = 0; i < size_leftmost; i++) {
    if(type_x != NCL_double) { 
      coerce_subset_input_double(x,tmp_x,index_x,type_x,npts,0,NULL,NULL);
    }
    else {
      tmp_x = &((double*)x)[index_x];
    }
/*
 * Check for missing values in x.  If any, then coerce that section of
 * the output to missing.
 */
    found_missing = contains_missing(tmp_x,npts,has_missing_x,
                                     missing_dx.doubleval);
    if(found_missing) {
      any_missing++;
      set_subset_output_missing(cf,index_x,type_cf,npts,
                                missing_dx.doubleval);
      set_subset_output_missing(cf,index_cfb,type_cf,npts,
                                missing_dx.doubleval);
    }
    else {
      NGCALLF(cfftfdriver,CFFTFDRIVER)(&npts,tmp_x,tmp_cfa,tmp_cfb,work,&nwrk);
/*
 * Copy results back into cf.
 */
      coerce_output_float_or_double(cf,tmp_cfa,type_cf,npts,index_x);
      coerce_output_float_or_double(cf,tmp_cfb,type_cf,npts,index_cfb);
    }
    index_x   += npts;
    index_cfb += npts;
  }

/*
 * Free up memory.
 */
  if(type_x != NCL_double) free(tmp_x);
  free(work);
  free(tmp_cfa);
  free(tmp_cfb);
/*
 * Set up variable to return.
 */
  type_cf_class = (NclTypeClass)_NclNameToTypeClass(NrmStringToQuark(_NclBasicDataTypeToName(type_cf)));

/*
 * Set up return values.
 */
  if(any_missing) {
    NhlPError(NhlWARNING,NhlEUNKNOWN,"cfftf: %d input arrays contained missing values. No calculations performed on these arrays.",any_missing);

    return_md = _NclCreateVal(
                              NULL,
                              NULL,
                              Ncl_MultiDValData,
                              0,
                              cf,
                              &missing_cf,
                              ndims_cf,
                              dsizes_cf,
                              TEMPORARY,
                              NULL,
                              (NclObjClass)type_cf_class
                              );
  }
  else {
    return_md = _NclCreateVal(
                              NULL,
                              NULL,
                              Ncl_MultiDValData,
                              0,
                              cf,
                              NULL,
                              ndims_cf,
                              dsizes_cf,
                              TEMPORARY,
                              NULL,
                              (NclObjClass)type_cf_class
                              );
  }
/*
 * Attributes "frq" and "npts".
 */
  att_id = _NclAttCreate(NULL,NULL,Ncl_Att,0,NULL);

/* Calculate frequences */
  NGCALLF(frqcfft,FRQCFFT)(&npts,&fmsg,tmp_frq);
  coerce_output_float_or_double(frq,tmp_frq,type_cf,npts,0);
  free(tmp_frq);

  dsizes[0] = npts;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         frq,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         (NclObjClass)type_cf_class
                         );
  _NclAddAtt(
             att_id,
             "frq",
             att_md,
             NULL
             );


  (*(int*)N) = npts;
  dsizes[0] = 1;
  att_md = _NclCreateVal(
                         NULL,
                         NULL,
                         Ncl_MultiDValData,
                         0,
                         N,
                         NULL,
                         1,
                         dsizes,
                         TEMPORARY,
                         NULL,
                         (NclObjClass)nclTypeintClass
                         );
  _NclAddAtt(
             att_id,
             "npts",
             att_md,
             NULL
             );

/*
 * Set up variable to hold return array and attributes.
 */
  tmp_var = _NclVarCreate(
                          NULL,
                          NULL,
                          Ncl_Var,
                          0,
                          NULL,
                          return_md,
                          NULL,
                          att_id,
                          NULL,
                          RETURNVAR,
                          NULL,
                          TEMPORARY
                          );
/*
 * Return output grid and attributes to NCL.
 */
  return_data.kind = NclStk_VAR;
  return_data.u.data_var = tmp_var;
  _NclPlaceReturn(return_data);
  return(NhlNOERROR);
}


