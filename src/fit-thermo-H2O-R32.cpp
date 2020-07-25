#include <iostream>
#include <math.h>
#include <string>
#include "fit-header.h"
using namespace std;
double	convert_Celsius_to_Kelvin (double t_celsius) ;
void    calculate_tk_it_jp (double tempK, double preskPa, double* t_kel, int* it, int* jp) ;

double	mass_density_H2O (double tempK, double preskPa) ; 
double  mass_density_R32 (double tempK, double preskPa) ;
double  specific_heat_H2O (double tempK, double preskPa) ;
double  specific_heat_R32 (double tempK, double preskPa) ;
double  viscosity_H2O	(double tempK, double preskPa) ;
double  viscosity_R32	(double tempK, double preskPa) ;
double  thermalCond_H2O (double tempK, double preskPa) ;
double  thermalCond_R32 (double tempK, double preskPa) ;

int main(int argc, char *argv[])
{
  
  double x=3.14159;
  double rho_m_interp ;
  double t_kel_prob, p_kPa_prob;
  double rho_m_H2O, cp_m_H2O, visco_H2O, kappa_H2O ;
  double rho_m_R32, cp_m_R32, visco_R32, kappa_R32 ;
  double rho_m_test, cp_m_test, visco_test, kappa_test ;
  double t_kel[Ntemp]		, p_kPa[Npres]		;
  // double rho_m[Ntemp][Npres]	, cp_m[Ntemp][Npres]	;
  // double eta_Pas[Ntemp][Npres]	, kappa[Ntemp][Npres]	;
  
  t_kel0 =  t_cel0 + 273.1500 ;
  
  cout << " Ntemp = " << Ntemp << endl;
  cout << " Npres = " << Npres << endl;

  for (int itemp = 0; itemp < Ntemp; ++itemp) {
    t_kel[itemp]  = t_kel0 +  del_t_kel * double(itemp);
    // cout << "temperature ["<< itemp <<"] = " <<t_kel[itemp] << endl;
  }

  for (int jpres = 0; jpres < Npres; ++jpres) {
    p_kPa[jpres]  = p_kPa0 +  del_p_kPa * double(jpres);
    // cout << "pressure ["<< jpres <<"] (kPa) = " << p_kPa[jpres] << endl;
  }

  t_kel_prob	= 300.12345	;
  p_kPa_prob	= 1603.25 	;
  
  rho_m_H2O	= mass_density_H2O	(t_kel_prob, p_kPa_prob);
  rho_m_R32	= mass_density_R32	(t_kel_prob, p_kPa_prob);
  cp_m_H2O	= specific_heat_H2O	(t_kel_prob, p_kPa_prob);
  cp_m_R32	= specific_heat_R32	(t_kel_prob, p_kPa_prob);
  visco_H2O	= viscosity_H2O		(t_kel_prob, p_kPa_prob);
  visco_R32	= viscosity_R32		(t_kel_prob, p_kPa_prob);
  kappa_H2O	= thermalCond_H2O 	(t_kel_prob, p_kPa_prob);
  kappa_R32	= thermalCond_R32 	(t_kel_prob, p_kPa_prob);

  cout << endl ;
  cout << " t_kel_prob = " << t_kel_prob << endl ;
  cout << " p_kPa_prob = " << p_kPa_prob << endl ;
  cout << " rho_m_H2O = " << rho_m_H2O << ": rho_m_R32 = " << rho_m_R32 << endl ;
  cout << " cp_m_H2O  = " << cp_m_H2O  << ": cp_m_R32  = " << cp_m_R32  << endl ;
  cout << " visco_H2O = " << visco_H2O << ": visco_R32 = " << visco_R32 << endl ;
  cout << " kappa_H2O = " << kappa_H2O << ": kappa_R32 = " << kappa_R32 << endl ;
  cout << endl ;

  return 0;
}
