;-----------------------------------------------------------------
;  NCL User Guide Example:   NUG_wind_mag.ncl
;
;  KMF 30.10.14
;-----------------------------------------------------------------

undef("file_ERROR")
procedure file_ERROR(name)
begin
   print("")
   print("You don't have the necessary data for this script. You can download it from:​")
   print("")
   print("http://www.ncl.ucar.edu/Document/Manuals/NCL_User_Guide/Data/"+name)
   print("")
   print("or use the wget command:")
   print("")
   print("wget http://www.ncl.ucar.edu/Document/Manuals/NCL_User_Guide/Data/"+name)
   print("")
   exit
end

  
;======================================
;== define the function wind_mag(u,v)
;======================================
undef("wind_mag")
function wind_mag(u,v)
local ma
begin
  ma = u
  ma@long_name = "wind magnitude"
  ma@standard_name = "magnitude_of_wind_velocity"
  if(isatt(ma,"cell_methods")) then
    delete(ma@cell_methods)
  end if
  if(isatt(ma,"original_name")) then
    delete(ma@original_name)
  end if
  ma = sqrt(u^2 + v^2)
  return(ma)
end
;=========================================================================
;==   MAIN script
;=========================================================================
; These load commands are not required in NCL versions 6.2.0 and later.
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_code.ncl"
load "$NCARG_ROOT/lib/ncarg/nclscripts/csm/gsn_csm.ncl"

begin

  diri = "$NCARG_ROOT/lib/ncarg/data/nug/"
  fil1 = "uas_rectilinear_grid_2D.nc"
  fil2 = "vas_rectilinear_grid_2D.nc"


  if (.not. fileexists(diri+fil1)) then
     file_ERROR(fil1)
  end if
  if (.not. fileexists(diri+fil2)) then
     file_ERROR(fil2)
  end if
  
  f1 = addfile(diri+fil1,"r")
  f2 = addfile(diri+fil2,"r")
  u  = f1->uas(0,:,:)
  v  = f2->vas(0,:,:)

  wks  =  gsn_open_wks("png","plot_wind_mag")

  res                   =  True
  res@gsnAddCyclic      =  True
  res@tiMainString      = "NCL Doc Example: Function wind_mag()"
  res@tiMainFontHeightF =  0.02
 
  mag             = wind_mag(u,v)
  mag&lat@units  = "degrees_north"
  mag&lon@units  = "degrees_east"

  printVarSummary(mag)

  ;-- draw the contour map

  plot = gsn_csm_contour_map(wks,mag,res)

  print("--------------------------------------")

;------------------------------------------------------------------
;-- if you won't copy ma=u within the function wind_mag, there are
;-- no dimension attributes at all. The user has to define the named
;-- dimensions and attributes by himself.
;------------------------------------------------------------------
  show_flag = 0
  if(show_flag.eq.1) then
    mm               = sqrt(u^2+v^2)
    mm!0             = "lat"
    mm!1             = "lon"
    mm&lat           = u&lat
    mm&lon           = u&lon
    mm&lat@units     = "degrees_north"
    mm&lon@units     = "degrees_east"
    mm@standard_name = "magnitude_of_wind_velocity"
    mm@long_name     = "magnitude (sqrt(u^2+v^2)"
    mm@units         = "m s-1"
    printVarSummary(mm)

    plot = gsn_csm_contour_map(wks,mm,res)
  end if

end
