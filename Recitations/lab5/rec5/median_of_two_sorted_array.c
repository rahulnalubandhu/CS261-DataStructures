#include <stdio.h>
#include <stdlib.h>
int max(int nums1, int nums2);
int min(int nums1, int nums2);
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
	//FIXME:
	
	int indexMin  = 0, indexMax  = nums1Size, i, j, median;
	// sorting
	while (indexMin <= indexMax)
	{
		i = (indexMin + indexMax) / 2;
		j = ((nums1Size + nums2Size + 1) / 2) - i;
		if (i < nums1Size && j > 0 && nums2[j - 1] > nums1[i])
		indexMin = i + 1;
		else if (i > 0 && j < nums2Size && nums2[j] < nums1[i - 1])
		indexMax = i - 1;
		else
		{
			if (i == 0)
			median = nums2[j - 1];
			else if (j == 0)
			median = nums1[i - 1];
			else
			median = max(nums1[i - 1], nums2[j - 1]);
			break;
		}
	}
	// Olong(nums1Size + nums2Size)
	if ((nums1Size + nums2Size) % 2 == 1) //is length
	return (double)median; 
	if (i == nums1Size)
	return (median+nums2[j]) / 2.0;
	if (j == nums2Size)
	return (median + nums1[i]) / 2.0;
	return (median + min(nums1[i], nums2[j])) / 2.0;
}
int max(int nums1, int nums2)
{
	if(nums1>nums2){
		return nums1;}
		else {
		return nums2;
		}
}
int min(int nums1, int nums2)
{
	if(nums1<nums2){
		return nums1;}
		else {
		return nums2;
		}
}
int main(int argc, char **argv)
{
	int a1[] = {1};
	int a2[] = {2};
	
	int n1 = sizeof(a1)/sizeof(a1[0]);
	int n2 = sizeof(a2)/sizeof(a2[0]);

	printf("Median is 1.5 = %f\n", findMedianSortedArrays(a1, n1, a2, n2));

	int a3[] = {1, 12, 15, 26, 38};
	int a4[] = {2, 13, 17, 30, 45, 50};
	
	n1 = sizeof(a3)/sizeof(a3[0]);
	n2 = sizeof(a4)/sizeof(a4[0]);

	printf("Median is 17 = %f\n", findMedianSortedArrays(a3, n1, a4, n2));

	int a5[] = {1, 12, 15, 26, 38};
	int a6[] = {2, 13, 17, 30, 45 };
	
	n1 = sizeof(a5)/sizeof(a5[0]);
	n2 = sizeof(a6)/sizeof(a6[0]);

	printf("Median is 16 = %f\n", findMedianSortedArrays(a5, n1, a6, n2));

	int a7[] = {1, 2, 5, 6, 8 };
	int a8[] = {13, 17, 30, 45, 50};
	
	n1 = sizeof(a7)/sizeof(a7[0]);
	n2 = sizeof(a8)/sizeof(a8[0]);

	printf("Median is 10.5 = %f\n", findMedianSortedArrays(a7, n1, a8, n2));

	int a9[] = {1, 2, 5, 6, 8, 9, 10 };
	int a10[] = {13, 17, 30, 45, 50};
	
	n1 = sizeof(a9)/sizeof(a9[0]);
	n2 = sizeof(a10)/sizeof(a10[0]);

	printf("Median is 9.5 = %f\n", findMedianSortedArrays(a9, n1, a10, n2));

	int a11[] = {1, 2, 5, 6, 8, 9 };
	int a12[] = {13, 17, 30, 45, 50};
	
	n1 = sizeof(a11)/sizeof(a11[0]);
	n2 = sizeof(a12)/sizeof(a12[0]);

	printf("Median is 9 = %f\n", findMedianSortedArrays(a11, n1, a12, n2));

	int a13[] = {1, 2, 5, 6, 8 };
	int a14[] = {11, 13, 17, 30, 45, 50};
	
	n1 = sizeof(a13)/sizeof(a13[0]);
	n2 = sizeof(a14)/sizeof(a14[0]);

	printf("Median is 11 = %f\n", findMedianSortedArrays(a13, n1, a14, n2));


	return 0;
}
