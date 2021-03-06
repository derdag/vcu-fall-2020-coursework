#include <rpc/rpc.h>
#include "avg.h"
#include <stdio.h>
#include <stdlib.h>

static double sum_avg;
static double median_val;

// compare helper function for qsort
int compare(const void *x, const void *y)
{
	return (*(double *)x - *(double *)y);
}

double *average_1(input_data *input, CLIENT *client)
{
	double *dp = input->input_data.input_data_val;
	int n = input->input_data.input_data_len;
	double arr[n];
	u_int i;

	for (i = 1; i <= n; i++)
	{
		arr[i] = *dp;
		dp++;
	}

	qsort(arr, n, sizeof(arr[0]), compare);

	if (n % 2 == 1) // if there is an odd number of elements, take the middle one
	{
		median_val = arr[(n + 1) / 2];
	}
	else // if there is an even number, take median of middle two numbers
	{
		median_val = (arr[(n + 1) / 2] + arr[(n + 1) / 2 + 1]) / 2;
	}

	return (&median_val);
}

double *average_1_svc(input_data *input, struct svc_req *svc)
{
	CLIENT *client;
	return (average_1(input, client));
}
