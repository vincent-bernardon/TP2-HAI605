// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLueS[250], cNomImgLueD[250],cNomImgEcrite[250];
 int nH, nW, nTaille;
 int som;
 if (argc != 4)
 {
 printf("Usage: ImageS.pgm ImageD.pgm ImageOut.pgm \n");
 exit (1) ;
 }

 sscanf (argv[1],"%s",cNomImgLueS) ;
 sscanf (argv[2],"%s",cNomImgLueD);
 sscanf (argv[3],"%s",cNomImgEcrite);


 OCTET *ImgInS, *ImgInD, *ImgOut;

 lire_nb_lignes_colonnes_image_pgm(cNomImgLueS, &nH, &nW);
 nTaille = nH * nW;

 allocation_tableau(ImgInS, OCTET, nTaille);
 lire_image_pgm(cNomImgLueS, ImgInS, nH * nW);
    allocation_tableau(ImgInD, OCTET, nTaille);
 lire_image_pgm(cNomImgLueD, ImgInD, nH * nW);
 allocation_tableau(ImgOut, OCTET, nTaille);


 for (int i=0; i < nH; i++)
 {
 for (int j=0; j < nW; j++)
 {
    if(ImgInD[i*nW+j]==255 && ImgInS[i*nW+j]==255){
        ImgOut[i*nW+j]=255;
    }else if(ImgInD[i*nW+j]==0 && ImgInS[i*nW+j]==0){
        ImgOut[i*nW+j]=255;
    }else{
        ImgOut[i*nW+j]=0;
    }
 }
 }
 
 
 
 ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
 free(ImgInS);
 free(ImgInD);
 free(ImgOut);

   return 1;
}
