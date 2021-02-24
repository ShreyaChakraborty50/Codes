#include <iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

int main (){
int processesNumber, resourcesNumber,resourcesInstances[250],maxi[250][250],allocation[250][250],need[250][250],available[250],executed[250];
int i,j;
FILE *InputFile;
	InputFile = fopen("input.txt", "r");
fscanf(InputFile, "%d", &processesNumber);
fscanf(InputFile, "%d", &resourcesNumber);
for(int i=0 ; i<resourcesNumber; i++)
	{
			fscanf(InputFile, "%d", &resourcesInstances[i]);

	}
char help[250];
for(i=0 ; i<processesNumber; i++)
	{
	    for(j=0 ; j<resourcesNumber; j++)
		{
			fscanf(InputFile, "%d", &maxi[i][j]);

		}
	}

for(int i=0 ; i<processesNumber; i++)
	{
	    for(j=0 ; j<resourcesNumber; j++)
		{
			fscanf(InputFile, "%d", &allocation[i][j]);
		}

	}
fclose(InputFile);


	for(i=0 ; i<processesNumber; i++)
	{
		for(j=0 ; j<resourcesNumber; j++)
		{
			need[i][j] = maxi[i][j] - allocation[i][j];
		}
	}

int sum;
	// available vector calculation
	for(j=0; j<resourcesNumber; j++)
	{
		sum = 0;
		for(i=0; i<processesNumber ; i++)
		{
			sum += allocation[i][j];
		}
		available[j] = resourcesInstances[j] - sum;
	}


int f[processesNumber], ans[processesNumber], ind = 0,k;
    for (k = 0; k < processesNumber; k++)
    {
        f[k] = 0;
    }


    int y = 0;
    for (k = 0; k <  processesNumber; k++)
    {
        for (i = 0; i < processesNumber; i++)
        {
            if (f[i] == 0)
            {

                int flag = 0;
                for (j = 0; j < resourcesNumber; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    ans[ind++] = i;
                    cout<<""<<i<<endl;
                    for (y = 0; y < resourcesNumber; y++)
                        available[y] += allocation[i][y];
                    f[i] = 1;
                }
            }
        }

    }






cout << "Following is the SAFE Sequence" << endl;
    for (i = 0; i < processesNumber - 1; i++)
        cout << " P" << ans[i] << " ->";
    cout << " P" << ans[processesNumber - 1] <<endl;

    return (0);









}
