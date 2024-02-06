
#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
char cNomImgLue[250], cNomImgEcrite[250];
 int nH, nW, nTaille;
 int som;
 if (argc != 3)
 {
 printf("Usage: ImageIn.pgm ImageOut.pgm \n");
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


 int valeur_pixel_actuel;
// la strat de l'érosion c'est de regarder tout les voisins du pixel (8) et de les mettre à la valeur du pixel actuel
 for (int i=0; i < nH; i++) // ça va dilater la couleur
 {
 for (int j=0; j < nW; j++)
 {
 
 // valeur_pixel_actuel = ImgIn[i * nW + j]; 
 if(i>=0 && i<nH && j>=0 && j<nW){
    if (ImgIn[i*nW+j] == 255) { // si pixel est noir on modifie ces voisinns si besoin

 if (ImgIn[(i-1)*nW+(j-1)] == 0) { //case haut gauche
 ImgOut[i*nW+j] = 0;
 }

 else if (ImgIn[i*nW+(j-1)] == 0) { // case gauche
 ImgOut[i*nW+j] = 0;
 }

 else if (ImgIn[(i+1)*nW+(j-1)] == 0) { // case bas gauche
 ImgOut[i*nW+j] = 0;
 }

 else if (ImgIn[(i-1)*nW+j] == 0) { //case du haut
 ImgOut[i*nW+j] = 0;
 }

 else if (ImgIn[(i+1)*nW+j] == 0) { // case du bas
 ImgOut[i*nW+j] = 0;
 }

 else if (ImgIn[(i-1)*nW+(j+1)] == 0) { // case du haut droite
 ImgOut[i*nW+j] = 0;
 }

 else if (ImgIn[i*nW+(j+1)] == 0) { // case droite
 ImgOut[i*nW+j] = 0;
 }

 else if (ImgIn[(i+1)*nW+(j+1)] == 0) { // case bas droite
 ImgOut[i*nW+j] = 0;
 }
 else {
 ImgOut[i*nW+j] = ImgIn[i*nW+j];
 }
 }else {
 ImgOut[i*nW+j] = ImgIn[i*nW+j];
 }
 }
 } 
 }
 ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
 free(ImgIn);
 free(ImgOut);
   return 1;
}
