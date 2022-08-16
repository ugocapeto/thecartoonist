#include "header.h"

void thecartoonist_main(
 char *imageFile,
 char *imageFile2
)

{

 FImage *sourceLab2;
 PImage *PsourceRGB;

 input = new PImage(imageFile);

 sourceRGB = new FImage(input);

 sourceLab = convert_srgb2Lab(sourceRGB);

 fprintf(stdout,"Computing the tangent flow vector field ...\n");

 tfm = tangentFlow(sourceRGB, tensor_sigma);

 fprintf(stdout,"Computing the tangent flow vector field ... done.\n");

 fprintf(stdout,"Visualizing the tangent flow vector field ...\n");

 FImage *lic = lineIntegralConvolution(tfm, 10.f);
 PImage *Plic = lic->toPImage();
 Plic->write((char *)"tangent_flow.png");

 fprintf(stdout,"Visualizing the tangent flow vector field ... done.\n");

 // perform 1 iteration of Separated OABF

 fprintf(stdout,"Applying the bilateral filter ...\n");

 sourceLab2 = orientationAlignedBilateralFilter(sourceLab, tfm, sigma_d, sigma_r, n_e);
 delete sourceLab;
 sourceLab = new FImage(sourceLab2);
 sourceRGB = convert_Lab2srgb(sourceLab);
 PsourceRGB = sourceRGB->toPImage();
 //PsourceRGB->write((char *)"oabf.png");
 PsourceRGB->write((char *)"abstracted_image_after_oabf.png");

 fprintf(stdout,"Applying the bilateral filter ... done.\n");

 // detect the edges using Separated FODG

 fprintf(stdout,"Detecting the edges ...\n");

 FImage *edges = fdog(sourceLab, tfm, fdog_n, fdog_sigma_e, fdog_tau, fdog_sigma_m, fdog_phi);
 PImage *Pedges = edges->toPImage();
 //Pedges->write((char *)"edges.png");
 Pedges->write((char *)"edges_image.png");

 fprintf(stdout,"Detecting the edges ... done.\n");

 // perform the remaining iterations of Separated OABF

 fprintf(stdout,"Applying the bilateral filter ...\n");

 sourceLab2 = orientationAlignedBilateralFilter(sourceLab, tfm, sigma_d, sigma_r, n_a-n_e);
 delete sourceLab;
 sourceLab = new FImage(sourceLab2);
 sourceRGB = convert_Lab2srgb(sourceLab);
 PsourceRGB = sourceRGB->toPImage();
 //PsourceRGB->write((char *)"oabf.png");
 PsourceRGB->write((char *)"abstracted_image_after_oabf2.png");

 fprintf(stdout,"Applying the bilateral filter ... done.\n");

 // quantize the luminance

 fprintf(stdout,"Quantizing ...\n");

 FImage *qu = quantize(sourceLab, quant_levels, phi_q);
 FImage *rgb = convert_Lab2srgb(qu);
 PImage *Prgb = rgb->toPImage();
 //Prgb->write((char *)"rgb.png");
 Prgb->write((char *)"abstracted_image_after_quantize.png");

 fprintf(stdout,"Quantizing ... done.\n");

 // blend the quantized image with the edges

 fprintf(stdout,"Superimposing the edges onto the quantized image ...\n");

 float v[3];
 v[0] = 0.f;
 v[1] = 0.f;
 v[2] = 0.f;
 FImage *blend = blendImages(rgb, edges, v);
 PImage *Pblend = blend->toPImage();
 //Pblend->write((char *)"blend.png");
 Pblend->write(imageFile2);

 fprintf(stdout,"Superimposing the edges onto the quantized image ... done.\n");

}
