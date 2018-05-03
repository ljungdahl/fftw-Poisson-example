/// This program performs a 3d real-to-complex in place FFT,
/// and then solves the Poisson equation in Fourierspace and then backtransforms.

#include <cmath>
#include <iostream>
#include <fftw3.h>

typedef double Real;
typedef int Int;

#define SIZE 8
#define NXX SIZE
#define NYY SIZE
#define NZZ SIZE


Int main()
{
  	Real Pi = M_PI;
	
	/// Grid size
	Int Nx=NXX,Ny=NYY,Nz=NZZ,Nzh=(Nz/2+1);


	/// Declare FFTW things.
	fftw_complex *mem;
	fftw_complex *out;
	Real *in;
	mem = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * Nx * Ny * Nzh);
	out = mem;
	in = mem[0];

	fftw_plan fwrd = fftw_plan_dft_r2c_3d(Nx,Ny,Nz,in,out,FFTW_MEASURE);
	fftw_plan bwrd = fftw_plan_dft_c2r_3d(Nx,Ny,Nz,out,in,FFTW_MEASURE);
	
	Real L0=0.0;
	Real L1=2*Pi;
	Real xlen = (L1-L0);

	/* TODO
	/// Setup grid and initialise
	
	/// Parameters
	*/
        
        fftw_execute(fwrd);

        Int II,JJ;
        Real k1,k2,k3;
        for (Int i=0;i<Nx;i++)
        {
                if (2*i<Nx)
                        II = i;
                else
                        II = Nx-i;
                k1 = 2*Pi*II/xlen;
                
                for (Int j=0;j<Ny;j++)
                {
                        if (2*j<Ny)
                                JJ = j;
                        else
                                JJ = Ny-j;
                        k2 = 2*Pi*JJ/xlen;
                        
                        for (Int k=0;k<Nzh;k++)
                        {
                                k3 = 2*Pi*k/xlen;
                                Real fac = -1.0*(pow(k1,2)+pow(k2,2)+pow(k3,2));
                                if (fabs(fac) < 1e-14)
                                {
                                        out[k+Nzh*(j+Ny*i)][0] = 0.0;
                                        out[k+Nzh*(j+Ny*i)][1] = 0.0;
                                }
                                else
                                {
                                        out[k+Nzh*(j+Ny*i)][0] /= fac;
                                        out[k+Nzh*(j+Ny*i)][1] /= fac;
                                }
                                
                        }
                }
        }
        
        fftw_execute(bwrd);
        

	return 0;
}
