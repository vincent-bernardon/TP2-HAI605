#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  int som;
  if (argc != 6)
  {
    printf("Usage: ImageIn.pgm ImageOut.pgm dilatation(0==true 1==false) largeur hauteur\n");
    exit (1) ;
  }

  sscanf (argv[1],"%s",cNomImgLue) ;
  sscanf (argv[2],"%s",cNomImgEcrite);

  OCTET *ImgIn, *ImgOut;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille);

  int dilatation = atoi(argv[3]);
int largeur = atoi(argv[4]);
int hauteur = atoi(argv[5]);

int largeurOffset = largeur % 2 == 0 ? largeur / 2 - 1 : largeur / 2;
int hauteurOffset = hauteur % 2 == 0 ? hauteur / 2 - 1 : hauteur / 2;
  int min;

  for (int i=0; i < nH; i++) 
  {
    for (int j=0; j < nW; j++)
    {
      if(dilatation==0){
        min = 255;
        for (int di=-hauteurOffset; di <=hauteurOffset + (hauteur % 2 == 0 ? 1 : 0); di++) 
        {
          for (int dj=-largeurOffset; dj <=largeurOffset + (largeur % 2 == 0 ? 1 : 0); dj++)
          {
            if ((i + di) >= 0 && (i + di) < nW && (j + dj) >= 0 && (j + dj) < nH) { // si on est dans notre borne
              if (ImgIn[(i + di) * nW + (j + dj)] < min) { //dilatation
                min = ImgIn[(i + di) * nW + (j + dj)];
              }
            }
          }
        }
      }else{
        min = 0;
        for (int di=-hauteurOffset; di <=hauteurOffset + (hauteur % 2 == 0 ? 1 : 0); di++) 
        {
          for (int dj=-largeurOffset; dj <=largeurOffset + (largeur % 2 == 0 ? 1 : 0); dj++)
          {
            if ((i + di) >= 0 && (i + di) < nW && (j + dj) >= 0 && (j + dj) < nH) { // si on est dans notre borne
              if (ImgIn[(i + di) * nW + (j + dj)] < min) { //erosion
                min = ImgIn[(i + di) * nW + (j + dj)];
              }
            }
          }
        }
      }
  
      ImgOut[i*nW+j]=min;
    } 
  }
 
  ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
  free(ImgIn);
  free(ImgOut);

  return 1;
}