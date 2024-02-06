#include <stdio.h>
#include "image_ppm.h"

void applyMorphologicalOperation(OCTET* ImgIn, OCTET* ImgOut, int nH, int nW, int dilatation) {
    int min;
    for (int i=0; i < nH; i++) 
    {
        for (int j=0; j < nW; j++)
        {
            if(dilatation==0){
                min = 255;
                for (int di=-1; di <=1; di++) 
                {
                    for (int dj=-1; dj <=1; dj++)
                    {
                        if ((i + di) >= 0 && (i + di) < nH && (j + dj) >= 0 && (j + dj) < nW) { // si on est dans notre borne
                            if (ImgIn[(i + di) * nW + (j + dj)] < min) { //dilatation
                                min = ImgIn[(i + di) * nW + (j + dj)];
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
                            if (ImgIn[(i + di) * nW + (j + dj)] > min) { //erosion
                                min = ImgIn[(i + di) * nW + (j + dj)];
                            }
                        }
                    }
                }
            }
            ImgOut[i*nW+j] = min;
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

 lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
 nTaille = nH * nW;

 allocation_tableau(ImgIn, OCTET, nTaille);
 lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
 allocation_tableau(ImgOut, OCTET, nTaille);
 allocation_tableau(ImgOutM, OCTET, nTaille);


 
 applyMorphologicalOperation(ImgIn, ImgOutM, nH, nW, 0);//dilatation
 applyMorphologicalOperation(ImgOutM, ImgOut, nH, nW, 1);//erosion


ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
 free(ImgIn);
 free(ImgOut);
 free(ImgOutM);

return 1;
}