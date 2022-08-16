#include "header.h"

// params
// tensor
float tensor_sigma;
// orientation aligned bilateral filter
int n_e;
int n_a;
float sigma_d;
float sigma_r;
// flow based differences of Gaussian
int fdog_n;
float fdog_sigma_e;
float fdog_tau;
float fdog_sigma_m;
float fdog_phi;
// quantization
float phi_q;
int quant_levels;

// variables
PImage *input;
FImage *tfm;
FImage *sourceRGB;
FImage *sourceLab;

int main(
 int argc,
 char* argv[]
)

{

 char filename[256];
 char filename_input_rgb_image[256];
 char filename_output_rgb_image[256];
 FILE *fp;

 /*
 Let's read in the input file
 */

 fp= fopen("thecartoonist_input.txt","r");
 if ( fp == NULL ) {
    fprintf(stdout,"thecartoonist_input.txt not found!\n");
    return 1;
 }

 /*
 Get filename for input rgb image
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"input rgb image = %s\n",filename);

 strcpy(filename_input_rgb_image,filename);

 // params
 // tensor

 fscanf(fp,"%g",&tensor_sigma);

 fprintf(stdout,"tensor_sigma = %g\n",tensor_sigma);

 // orientation aligned bilateral filter

 fscanf(fp,"%d",&n_e);

 fprintf(stdout,"n_e = %d\n",n_e);

 fscanf(fp,"%d",&n_a);

 fprintf(stdout,"n_a = %d\n",n_a);

 fscanf(fp,"%g",&sigma_d);

 fprintf(stdout,"sigma_d = %g\n",sigma_d);

 fscanf(fp,"%g",&sigma_r);

 fprintf(stdout,"sigma_r = %g\n",sigma_r);

 // flow based differences of Gaussian

 fscanf(fp,"%d",&fdog_n);

 fprintf(stdout,"fdog_n = %d\n",fdog_n);

 fscanf(fp,"%g",&fdog_sigma_e);

 fprintf(stdout,"fdog_sigma_e = %g\n",fdog_sigma_e);

 fscanf(fp,"%g",&fdog_tau);

 fprintf(stdout,"fdog_tau = %g\n",fdog_tau);

 fscanf(fp,"%g",&fdog_sigma_m);

 fprintf(stdout,"fdog_sigma_m = %g\n",fdog_sigma_m);

 fscanf(fp,"%g",&fdog_phi);

 fprintf(stdout,"fdog_phi = %g\n",fdog_phi);

 // quantization

 fscanf(fp,"%g",&phi_q);

 fprintf(stdout,"phi_q = %g\n",phi_q);

 fscanf(fp,"%d",&quant_levels);
 
 fprintf(stdout,"quant_levels = %d\n",quant_levels);

 /*
 Get filename for output rgb image
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"output rgb image = %s\n",filename);

 strcpy(filename_output_rgb_image,filename);

 /*
 We are done reading the input file
 */

 fclose(fp);

 /*
 Check the input
 */

 if ( !(n_a >= n_e) ) {
   fprintf(stdout,"n_a must be greater than or equal to n_e!\n");
   //force abnormal process termination
   abort();
 }

 thecartoonist_main(
  filename_input_rgb_image,
  filename_output_rgb_image
 );

 return 0;

}
