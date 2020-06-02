#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSELON 1e-16

int WorkWithFile(const char* a, const char* b);
int changes(double *arr, int h, int w);

#endif

int WorkWithFile(const char* a, const char* b) {
   FILE *fp;
   FILE *fo;
   int h, w, new_w;
   int i = 0, j = 0;
   double* arr;
   fp = fopen(a, "r");
   fo = fopen(b, "w");
   if (!fp || !fo) {
      printf("Cannot open file\n");
      return -1;
   }
   if (fscanf(fp, "%d %d", &h, &w) != 2) {
      printf("smth in %s went wrong!\n", "a.txt");
      fclose(fp);
      fclose(fo);
      return -1;
   }
   if (h <= 0 || w <= 0) {
      printf("Error! Cannot allocate memory...\n");
      fclose(fp);
      fclose(fo);
      return -1;
   }

   arr = (double*)malloc(h * w * sizeof(double));
   for(i = 0; i < h; i++) {
      for (j = 0; j < w; j++) {
         if (fscanf(fp, "%lf", &arr [i * w + j]) != 1) {
            printf("Cannot read data from file %s!\n", "a.txt");
            free(arr);
            fclose(fp);
            fclose(fo);
            return -1;
         }
      }
   }
   printf("We have:\n");
   for (int k = 0; k < h; k++) {
      for (int g = 0; g < w; g++) {
          printf("%lf ", arr[k * w + g]);
      }
      printf("\n");
   }
   new_w = changes(arr, h, w);
   printf("The answer is...:\n");
   for (int l = 0; l < h; l++) {
      for (int d = 0; d < new_w; d++) {
          printf("%lf ", arr[l * w + d]);
          fprintf(fo,"%lf ", arr[l * w + d]);
      }
      printf("\n");
      fprintf(fo, "\n");
   }
   free(arr);
   fclose(fp);
   fclose(fo);
   return 0;
}

int changes(double *arr, int m, int n)
{
	int i, j, k, new_n = n, flag = 0;
	double sum = 0, sr;
	printf ("m = %d\n", m);
	for (j = 0; j < new_n; j++) {
		sum = 0;
		for (i = 0; i < m; i++) {
			sum += arr[i*n+j];
		}
		sr = sum/m;
		printf ("sum = %lf\n", sr);
		for (i = 0; i < m; i++) {
			if (fabs(arr[i*n+j] - sr) < EPSELON) {
				flag = 1;
				break;
			}
		}
		if (flag) {
			for (k = j; k < new_n-1; k++) {
				for (i = 0; i < m; i++) {
					arr[i*n+k] = arr[i*n+k+1];
				}
			}
			new_n--;
			j--;
			flag = 0;
		}
	}
	return new_n;
}


int main(void) {
   WorkWithFile("a.txt", "b.txt");
   return 0;
}


