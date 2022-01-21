#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int scanRecords(char total_input[],char *firstname[],char* lastname[],double meetingtime [] );
void printRecords(char total_output[],char *firstname[], char *lastname[],double meetingtime [], double givenDuration, int numberOfLine);
void insertionSort(char *firstname[], char *lastname[],double meetingtime [],int numberOfLines);

int main(int arg1, char *arg2[]) //char *argi[],char* argo[],int minDuration,char*disp[]
{
    int scan_status;
    double meetingtime[500];//in terms of minutes
    int numberOfLines=0;
    char *firstname[500];
    char *surname[500];

    numberOfLines= scanRecords(arg2[1],firstname,surname,meetingtime);
    if(arg2[4]!= NULL)
    {
        if(strcmp(arg2[4],"sorted")==0)
        {
            insertionSort(firstname,surname,meetingtime,numberOfLines);
        }
    }

    printRecords(arg2[2],firstname,surname,meetingtime,atof(arg2[3]),numberOfLines);
    return 0;
}

int scanRecords(char total_input[30],char *firstname[],char *surname[],double meetingtime[])
{
    char newLine[500];
    char name[500];
    char firname[500];
    char lastname[500];
    //char copy [700];
    char passedtime[700];
    char garbage[600];
    char * firstpart_delimeter;
    char * splittedtext;
    char * inputstatus;
    double zoomtime;
    int scancounter=0;
    FILE* inputfile = fopen(total_input,"r");
    fgets(garbage,500,inputfile); // get first line as a garbage.
    for(inputstatus=fgets(newLine,700,inputfile); inputstatus!=0 ; inputstatus=fgets(newLine,700,inputfile))
    {
        printf("dosya okunuyor");

        splittedtext= strtok(newLine,",");
        strcpy(name,splittedtext);// Copy the hole Text Before the Comma","
        while(splittedtext!=NULL)
        {
            strcpy(passedtime,splittedtext);
            splittedtext= strtok(NULL,",");

            if(splittedtext==NULL)
            {
                zoomtime = atof(passedtime);
            }
        }
        zoomtime = atof(passedtime);
        firstpart_delimeter= strtok(name," "); // first string in the name part.

        strcpy(firname,firstpart_delimeter); // first name; if we have 1 name and 1 surname;
        firstpart_delimeter= strtok(NULL," ");

        strcpy(lastname,firstpart_delimeter);
        // now check if we have more text we should modify predetermined name and surname.
        firstpart_delimeter= strtok(NULL," ");
        if(firstpart_delimeter!=NULL)
        {
            strcat(firname," ");
            strcat(firname,lastname);
            strcpy(lastname,firstpart_delimeter);
        }

        int found=0;
        for(int j=0; j<scancounter; j++)
        {
            if(strcasecmp(firstname+scancounter,firname)==0 && strcasecmp(surname+scancounter,lastname)==0)
            {
                meetingtime[scancounter]+= zoomtime;
                found=1;
            }
        }
        if(found==0)
        {
            strcpy(firstname+scancounter,firname);
            firstname[scancounter]=firname;
            printf("%s",firstname[scancounter]);
            strcpy(surname+scancounter,lastname);
            surname[scancounter]=lastname;
            printf("%s",surname[scancounter] );
            meetingtime[scancounter]=zoomtime;
            scancounter++;
        }
    }
    fclose(inputfile);
    printf("%d",scancounter);
    return scancounter;
}
void printRecords(char total_output[],char *firstname[], char *lastname[],double meetingtime[],double givenDuration, int numberOfLines)
{
    printf("print records ici");
    FILE* outputfile = fopen(total_output,"w");
    for(int a=1; a< numberOfLines; a++)
    {
        if(meetingtime[a]>=givenDuration)
        {
            fprintf(outputfile,"%s %s %2.lf \n",lastname[a],firstname[a],meetingtime[a]); //meetingtime[a]
        }

    }
    fclose(outputfile);

}
void insertionSort(char *firstname[], char *lastname[],double meetingtime[],int numberOfLines)
{
    char *tempfirstname;
    char * templastname;
    double  tempd;
    for(int i=numberOfLines; i>0; i--)
    {
        for(int j=i; j<numberOfLines; j++)
        {
            if(strcasecmp(lastname[j],lastname[j-1])<=-1)
            {
                tempfirstname= lastname[j];
                firstname[j]=firstname[j-1];
                firstname[j-1]=tempfirstname;
                //////
                templastname=lastname[j];
                lastname[j]=lastname[j-1];
                lastname[j-1]=templastname;
                //////
                tempd= meetingtime[j];
                meetingtime[j]=meetingtime[j-1];
                meetingtime[j-1]=tempd;

            }
            else if(strcasecmp(lastname[j],lastname[j-1])== 0 && strcasecmp(firstname[j],firstname[j-1])<= -1 )
            {
                tempfirstname= lastname[j];
                firstname[j]=firstname[j-1];
                firstname[j-1]=tempfirstname;
                //////
                templastname=lastname[j];
                lastname[j]=lastname[j-1];
                lastname[j-1]=templastname;
                //////
                tempd= meetingtime[j];
                meetingtime[j]=meetingtime[j-1];
                meetingtime[j-1]=tempd;


            }

        }
    }

}
