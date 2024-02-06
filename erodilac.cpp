// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
using namespace std;

int choix(int dilatation, OCTET *ImgIn, int i, int j, int nW, int nH, int offset){
  int min;
  if(dilatation==0){
    min = 255;
    for (int di=-1; di <=1; di++) 
    {
      for (int dj=-1; dj <=1; dj++)
      {
        if ((i + di) >= 0 && (i + di) < nH && (j + dj) >= 0 && (j + dj) < nW) { // si on est dans notre borne
          if (ImgIn[((i + di) * nW + (j + dj)) * 3 + offset] < min) { //dilatation
            min = ImgIn[((i + di) * nW + (j + dj)) * 3 + offset];
          }
        }
      }
    }
  }else{
    min = 0;
    for (int di=-1; di <=1; di++) 
    {
      for (int dj=-1; dj <=1; dj++)
      {
        if ((i + di) >= 0 && (i + di) < nH && (j + dj) >= 0 && (j + dj) < nW) { // si on est dans notre borne
          if (ImgIn[((i + di) * nW + (j + dj)) * 3 + offset] > min) { //erosion
            min = ImgIn[((i + di) * nW + (j + dj)) * 3 + offset];
          }
        }
      }
    }
  }
  return min;
}

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
 int nH, nW, nTaille;
 int som;
 if (argc != 4)
 {
 printf("Usage: ImageIn.ppm ImageOut.ppm dilatation(0==true 1==false)\n");
 exit (1) ;
 }

 sscanf (argv[1],"%s",cNomImgLue) ;
 sscanf (argv[2],"%s",cNomImgEcrite);


 OCTET *ImgIn, *ImgOut;

 lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
 nTaille = nH * nW;
 int nTaille3 = nTaille*3;

 allocation_tableau(ImgIn, OCTET, nTaille3);
 lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
 allocation_tableau(ImgOut, OCTET, nTaille3);

int dilatation = atoi(argv[3]);
int minR;
int minV;
int minB;
int tempi, tempj;

for (int i=0; i < nH; i++)
{
  for (int j=0; j < nW; j++)
  {
    //on recupere le min de chaque couleur
    minR = choix(dilatation,ImgIn,i,j,nW,nH,0);
    minV = choix(dilatation,ImgIn,i,j,nW,nH,1);
    minB = choix(dilatation,ImgIn,i,j,nW,nH,2);
    //on met le min dans l'image de sortie
    ImgOut[(i * nW + j) * 3] = minR;
    ImgOut[(i * nW + j) * 3 + 1] = minV;
    ImgOut[(i * nW + j) * 3 + 2] = minB;
  }
}
  
  //Sauvegarde
 ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
 free(ImgIn);
 free(ImgOut);

   return 1;
}
