// void calculation (int i){
//   //cout << "Function 1" << "\n";
//   //cout << i << "\n";
// };

#include <iostream>
using namespace std;

void errorMessage (string funcName, double tempK, double preskPa, int it, int jp,int  Ntemp, int Npres ){
  cout << " ERROR in function: " <<  funcName << endl; 
  cout << "   Double-chech the range of temperature (between 278.15 and 313.15) and " ;
  cout << "   pressure (between 1550 and 1750)" << endl ;
  cout << "   Currently: tempK = " << tempK << " and " << "preskPa = " << preskPa ;
  cout << "   that gives it = " << it << " and " << "jp = " << jp << ","<<endl	;
  cout << "   which should be less than Ntemp = " << Ntemp << " and " << "Npres = " << Npres	;
  cout << ", respectively." << endl;
};


double convert_Celsius_to_Kelvin (double t_celsius) {
  #include	"fit-header.h"
  double t_kel ;
  t_kel = t_celsius + tk_ref; 
  return t_kel ;
};


void calculate_tk_it_jp (double tempK, double preskPa, double* t_kel, int* it, int* jp)
{
#include	"fit-header.h"
  *t_kel	=   t_cel0 + tk_ref; 
  *it		=  (tempK   - *t_kel)	/ del_t_kel   ;
  *jp		=  (preskPa - p_kPa0) 	/ del_p_kPa   ;
};

double  mass_density_H2O (double tempK, double preskPa ) {
  #include	"fit-header.h"
  double	rho_m[Ntemp][Npres] ;
  #include	"density_H2O.h"
  int		it, jp ;
  double	dtk, dpkPa, coeff[4], rho_m_intp ;

  calculate_tk_it_jp (tempK, preskPa, &t_kel0, &it, &jp) ;
  
  if (it < Ntemp &&  jp < Npres) {
    dtk		= tempK		- del_t_kel * float(it) - t_kel0 ;  
    dpkPa	= preskPa	- del_p_kPa * float(jp) - p_kPa0  ;
    coeff[0]	=  rho_m[it][jp]					;
    coeff[1]	= (rho_m[it+1][jp] - rho_m[it][jp] ) / del_t_kel	;
    coeff[2]	= (rho_m[it][jp+1] - rho_m[it][jp] ) / del_p_kPa	;
    coeff[3]	= rho_m[it+1][jp+1] +  rho_m[it][jp] - rho_m[it+1][jp] - rho_m[it][jp+1] ;
    coeff[3]	= coeff[3] / (del_t_kel * del_p_kPa) ;
    rho_m_intp	= coeff[0] + coeff[1] * dtk + coeff[2] * dpkPa + coeff[3] * dtk * dpkPa  ;
    //cout << " rho_m_near = " << rho_m[it][jp] << endl;;
    return rho_m_intp;
  } 
  else{
    errorMessage (__func__, tempK, preskPa, it,  jp,  Ntemp,  Npres ) ;
    return -9001 ;
  } 
};


double  mass_density_R32 (double tempK, double preskPa ) {
  #include	"fit-header.h"
  double	rho_m[Ntemp][Npres] ;
  #include	"density_R32.h"
  int		it, jp ;
  double	dtk, dpkPa, coeff[4], rho_m_intp ;

  calculate_tk_it_jp (tempK, preskPa, &t_kel0, &it, &jp) ;
  
  if (it < Ntemp &&  jp < Npres) {
    dtk		= tempK		- del_t_kel * float(it) - t_kel0 ;  
    dpkPa	= preskPa	- del_p_kPa * float(jp) - p_kPa0  ;
    coeff[0]	=  rho_m[it][jp]					;
    coeff[1]	= (rho_m[it+1][jp] - rho_m[it][jp] ) / del_t_kel	;
    coeff[2]	= (rho_m[it][jp+1] - rho_m[it][jp] ) / del_p_kPa	;
    coeff[3]	= rho_m[it+1][jp+1] +  rho_m[it][jp] - rho_m[it+1][jp] - rho_m[it][jp+1] ;
    coeff[3]	= coeff[3] / (del_t_kel * del_p_kPa) ;
    rho_m_intp	= coeff[0] + coeff[1] * dtk + coeff[2] * dpkPa + coeff[3] * dtk * dpkPa  ;
    //cout << " rho_m_near = " << rho_m[it][jp] << endl;
    return rho_m_intp;
  } 
  else{
    errorMessage (__func__, tempK, preskPa, it,  jp,  Ntemp,  Npres ) ;
    return -9002 ;
  } 
};
  
double  specific_heat_H2O (double tempK, double preskPa ) {
  #include	"fit-header.h"
  double	cp_m[Ntemp][Npres] ;
  #include	"specific_heat_H2O.h"
  int		it, jp ;
  double	dtk, dpkPa, coeff[4], cp_m_intp ;

  calculate_tk_it_jp (tempK, preskPa, &t_kel0, &it, &jp) ;
  
  if (it < Ntemp &&  jp < Npres) {
    dtk		= tempK		- del_t_kel * float(it) - t_kel0 ;  
    dpkPa	= preskPa	- del_p_kPa * float(jp) - p_kPa0  ;
    coeff[0]	=  cp_m[it][jp]					;
    coeff[1]	= (cp_m[it+1][jp] - cp_m[it][jp] ) / del_t_kel	;
    coeff[2]	= (cp_m[it][jp+1] - cp_m[it][jp] ) / del_p_kPa	;
    coeff[3]	= cp_m[it+1][jp+1] +  cp_m[it][jp] - cp_m[it+1][jp] - cp_m[it][jp+1] ;
    coeff[3]	= coeff[3] / (del_t_kel * del_p_kPa) ;
    cp_m_intp	= coeff[0] + coeff[1] * dtk + coeff[2] * dpkPa + coeff[3] * dtk * dpkPa  ;
    //cout << " cp_m_near = " << cp_m[it][jp] << endl;
    return cp_m_intp;
  } 
  else{
    errorMessage (__func__, tempK, preskPa, it,  jp,  Ntemp,  Npres ) ;
    return -9003 ;
    
  } 
};


double  specific_heat_R32 (double tempK, double preskPa ) {
  #include	"fit-header.h"
  double	cp_m[Ntemp][Npres] ;
  #include	"specific_heat_R32.h"
  int		it, jp ;
  double	dtk, dpkPa, coeff[4], cp_m_intp ;

  calculate_tk_it_jp (tempK, preskPa, &t_kel0, &it, &jp) ;
  
  if (it < Ntemp &&  jp < Npres) {
    dtk		= tempK		- del_t_kel * float(it) - t_kel0 ;  
    dpkPa	= preskPa	- del_p_kPa * float(jp) - p_kPa0  ;
    coeff[0]	=  cp_m[it][jp]					;
    coeff[1]	= (cp_m[it+1][jp] - cp_m[it][jp] ) / del_t_kel	;
    coeff[2]	= (cp_m[it][jp+1] - cp_m[it][jp] ) / del_p_kPa	;
    coeff[3]	= cp_m[it+1][jp+1] +  cp_m[it][jp] - cp_m[it+1][jp] - cp_m[it][jp+1] ;
    coeff[3]	= coeff[3] / (del_t_kel * del_p_kPa) ;
    cp_m_intp	= coeff[0] + coeff[1] * dtk + coeff[2] * dpkPa + coeff[3] * dtk * dpkPa  ;
    //cout << " cp_m_near = " << cp_m[it][jp] << endl;
    return cp_m_intp;
  } 
  else{
    errorMessage (__func__, tempK, preskPa, it,  jp,  Ntemp,  Npres ) ;
    return -9004 ;
  } 
};
  

double  viscosity_H2O (double tempK, double preskPa ) {
  #include	"fit-header.h"
  double	visco[Ntemp][Npres] ;
  #include	"viscosity_H2O.h"
  int		it, jp ;
  double	dtk, dpkPa, coeff[4], visco_intp ;

  calculate_tk_it_jp (tempK, preskPa, &t_kel0, &it, &jp) ;
  
  if (it < Ntemp &&  jp < Npres) {
    dtk		= tempK		- del_t_kel * float(it) - t_kel0 ;  
    dpkPa	= preskPa	- del_p_kPa * float(jp) - p_kPa0  ;
    coeff[0]	=  visco[it][jp]					;
    coeff[1]	= (visco[it+1][jp] - visco[it][jp] ) / del_t_kel	;
    coeff[2]	= (visco[it][jp+1] - visco[it][jp] ) / del_p_kPa	;
    coeff[3]	= visco[it+1][jp+1] +  visco[it][jp] - visco[it+1][jp] - visco[it][jp+1] ;
    coeff[3]	= coeff[3] / (del_t_kel * del_p_kPa) ;
    visco_intp	= coeff[0] + coeff[1] * dtk + coeff[2] * dpkPa + coeff[3] * dtk * dpkPa  ;
    //cout << " visco_near = " << visco[it][jp] << endl;
    return visco_intp;
  } 
  else{
    errorMessage (__func__, tempK, preskPa, it,  jp,  Ntemp,  Npres ) ;
    return -9005 ;
    //cout << " Double-chech the range of temperature (between 278.15 and 313.15) and " ;
    //cout << " pressure (between 1550 and 1750)" << endl ;
    //cout << " Currently: tempK = " << tempK << " and " << "preskPa = " << preskPa ;
    //cout << " that gives it = " << it << " and " << "jp = " << jp << ","<<endl	;
    //cout << " which should be less than Ntemp = " << Ntemp << " and " << "Npres = " << Npres	;
    //cout << ", respectively." << endl;
  } 
};
  
double  viscosity_R32 (double tempK, double preskPa ) {
  #include	"fit-header.h"
  double	visco[Ntemp][Npres] ;
  #include	"viscosity_R32.h"
  int		it, jp ;
  double	dtk, dpkPa, coeff[4], visco_intp ;

  calculate_tk_it_jp (tempK, preskPa, &t_kel0, &it, &jp) ;
  
  if (it < Ntemp &&  jp < Npres) {
    dtk		= tempK		- del_t_kel * float(it) - t_kel0 ;  
    dpkPa	= preskPa	- del_p_kPa * float(jp) - p_kPa0  ;
    coeff[0]	=  visco[it][jp]					;
    coeff[1]	= (visco[it+1][jp] - visco[it][jp] ) / del_t_kel	;
    coeff[2]	= (visco[it][jp+1] - visco[it][jp] ) / del_p_kPa	;
    coeff[3]	= visco[it+1][jp+1] +  visco[it][jp] - visco[it+1][jp] - visco[it][jp+1] ;
    coeff[3]	= coeff[3] / (del_t_kel * del_p_kPa) ;
    visco_intp	= coeff[0] + coeff[1] * dtk + coeff[2] * dpkPa + coeff[3] * dtk * dpkPa  ;
    //cout << " visco_near = " << visco[it][jp] << endl;
    return visco_intp;
  } 
  else{
    errorMessage (__func__, tempK, preskPa, it,  jp,  Ntemp,  Npres ) ;
    return -9006 ;
  } 
};
  

double  thermalCond_H2O (double tempK, double preskPa ) {
  #include	"fit-header.h"
  double	kappa[Ntemp][Npres] ;
  #include	"thermal_conductivity_H2O.h"
  int		it, jp ;
  double	dtk, dpkPa, coeff[4], kappa_intp ;

  calculate_tk_it_jp (tempK, preskPa, &t_kel0, &it, &jp) ;
  
  if (it < Ntemp &&  jp < Npres) {
    dtk		= tempK		- del_t_kel * float(it) - t_kel0 ;  
    dpkPa	= preskPa	- del_p_kPa * float(jp) - p_kPa0  ;
    coeff[0]	=  kappa[it][jp]					;
    coeff[1]	= (kappa[it+1][jp] - kappa[it][jp] ) / del_t_kel	;
    coeff[2]	= (kappa[it][jp+1] - kappa[it][jp] ) / del_p_kPa	;
    coeff[3]	= kappa[it+1][jp+1] +  kappa[it][jp] - kappa[it+1][jp] - kappa[it][jp+1] ;
    coeff[3]	= coeff[3] / (del_t_kel * del_p_kPa) ;
    kappa_intp	= coeff[0] + coeff[1] * dtk + coeff[2] * dpkPa + coeff[3] * dtk * dpkPa  ;
    //cout << " kappa_near = " << kappa[it][jp] << endl;
    return kappa_intp;
  } 
  else{
    errorMessage (__func__, tempK, preskPa, it,  jp,  Ntemp,  Npres ) ;
    return -9007 ;
  } 
};
  


  

double  thermalCond_R32 (double tempK, double preskPa ) {
  #include	"fit-header.h"
  double	kappa[Ntemp][Npres] ;
  #include	"thermal_conductivity_R32.h"
  int		it, jp ;
  double	dtk, dpkPa, coeff[4], kappa_intp ;

  calculate_tk_it_jp (tempK, preskPa, &t_kel0, &it, &jp) ;
  
  if (it < Ntemp &&  jp < Npres) {
    dtk		= tempK		- del_t_kel * float(it) - t_kel0 ;  
    dpkPa	= preskPa	- del_p_kPa * float(jp) - p_kPa0  ;
    coeff[0]	=  kappa[it][jp]					;
    coeff[1]	= (kappa[it+1][jp] - kappa[it][jp] ) / del_t_kel	;
    coeff[2]	= (kappa[it][jp+1] - kappa[it][jp] ) / del_p_kPa	;
    coeff[3]	= kappa[it+1][jp+1] +  kappa[it][jp] - kappa[it+1][jp] - kappa[it][jp+1] ;
    coeff[3]	= coeff[3] / (del_t_kel * del_p_kPa) ;
    kappa_intp	= coeff[0] + coeff[1] * dtk + coeff[2] * dpkPa + coeff[3] * dtk * dpkPa  ;
    //cout << " kappa_near = " << kappa[it][jp] << endl;
    return kappa_intp;
  } 
  else{
    errorMessage (__func__, tempK, preskPa, it,  jp,  Ntemp,  Npres ) ;
    return -9008 ;
  } 
};
  


