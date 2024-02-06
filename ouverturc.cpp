#include <stdio.h>
#include "image_ppm.h"

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

void applyColorMorphologicalOperation(OCTET* ImgIn, OCTET* ImgOut, int nH, int nW, int dilatation) {
    int minR, minV, minB;
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
}

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

 OCTET *ImgIn, *ImgOutM, *ImgOut;

 lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
 nTaille = nH * nW;
 int nTaille3= nTaille*3;

 allocation_tableau(ImgIn, OCTET, nTaille3);
 lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
 allocation_tableau(ImgOut, OCTET, nTaille3);
 allocation_tableau(ImgOutM, OCTET, nTaille3);


 applyColorMorphologicalOperation(ImgIn, ImgOutM, nH, nW, 1);//erosion
 applyColorMorphologicalOperation(ImgOutM, ImgOut, nH, nW, 0);//dilatation


ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
 free(ImgIn);
 free(ImgOut);
 free(ImgOutM);

return 1;
}