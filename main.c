#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef  struct
{
    char name[50];
    char surname[50];
    double attendenceduration;
} student;
int scanStudent(char inputFile[], student studentsp[]);
int loadStudents(student students[],double duration, int numOfStudents,char firstname[],char lastname[]);
void writeStudentsOnFile(char outputFile[],  student students[],double givenDuration, int numOfStudents);
void insertionSort(student students[],int numberOfLines);

int main(int arg1, char *arg2[]) //char *argi[],char* argo[],int minDuration,char*disp[]
{
    int scan_status;
    student students[500];
    int numOfStudents=0;
    numOfStudents= scanStudent(arg2[1],students);
    if(arg2[4]!= NULL)
    {
        if(strcmp(arg2[4],"sorted")==0)
        {
            insertionSort(students,numOfStudents);
        }
    }
    writeStudentsOnFile(arg2[2],students,atof(arg2[3]),numOfStudents);
    return 0;
}
int scanStudent(char inputFile[], student studentsp[])
{
    char newLine[500];
    char name[500];
    char firname[500];
    char yeniname[500];
    char namecpy [200];
    int found =0;
    char passedtime[700];
    char garbage[600];
    char * firstpart_delimeter;
    char * splittedtext;
    char * inputstatus;
    double zoomtime;
    int scancounter=0;
    FILE* students_record = fopen(inputFile,"r");
    fgets(garbage,500,students_record);

    while(fscanf(students_record,"%[^\n] ",newLine)!=EOF)
    {
        char * firstpart_delimeter2;
        char lastname[500];
        char othername[500];
        char surname[500];
        int spacecounter=0;
        splittedtext= strtok(newLine,","); //
        strcpy(name,splittedtext);

        while(splittedtext!=NULL)
        {
            strcpy(passedtime,splittedtext);
            splittedtext= strtok(NULL,",");
        }
        zoomtime = atof(passedtime);

        /**splitting name*/
        strcpy(namecpy,name);
        firstpart_delimeter= strtok(name," ");
        while(firstpart_delimeter!=NULL)
        {
            strcpy(lastname,firstpart_delimeter);
            firstpart_delimeter=strtok(NULL," ");
            spacecounter++;
        }
        strcpy(surname,lastname);
        firstpart_delimeter2=strtok(namecpy," ");
        strcpy(firname,firstpart_delimeter2);

        for(int i=0; i< spacecounter-2; i++)
        {
            if(i==0)
            {
                firstpart_delimeter2=strtok(NULL," ");
                strcpy(othername,firstpart_delimeter2);
                found=1;
                strcat(firname," ");
                strcat(firname,othername);
            }
            else
            {
                strcat(firname," ");
                firstpart_delimeter2= strtok(NULL," ");
                strcpy(yeniname,firstpart_delimeter2);
                strcat(firname,yeniname);
            }
        }
        scancounter=loadStudents(studentsp,zoomtime,scancounter,firname,surname);//lastname
    }
    fclose(students_record);
    return scancounter;
}

int loadStudents(student students[],double duration, int numOfStudents,char firstname[],char lastname[])
{
    int isFound=0;
    for(int i=0; i<numOfStudents; i++)
    {
        if(strcasecmp(students[i].name,firstname)==0 && strcasecmp(students[i].surname,lastname)==0)
        {
            students[i].attendenceduration += duration;
            isFound=1;
        }
    }
    if(isFound==0)
    {
        strcpy(students[numOfStudents].name,firstname);
        strcpy(students[numOfStudents].surname,lastname);
        students[numOfStudents].attendenceduration=duration;
        numOfStudents++;
    }
    return numOfStudents;
}
void writeStudentsOnFile(char outputFile[], student students [], double givenDuration, int numOfStudents) // pointerla yap
{
    FILE *student_record_output = fopen(outputFile,"w");
    for(int j=0; j<numOfStudents; j++)
    {
        if(students[j].attendenceduration >= givenDuration)
        {
            fprintf(student_record_output,"%s %s %.2lf\n",students[j].surname,students[j].name,students[j].attendenceduration);
            printf( "%s %s %.2lf\n",students[j].surname,students[j].name,students[j].attendenceduration);
        }
    }
    fclose(student_record_output);
}

void insertionSort(student students[],int numberOfLines)
{
    char *tempfirstname;
    char * templastname;
    double  tempd;
    student temporary;
    for(int i=0; i<numberOfLines; i++)
    {
        for(int j=i+1; j<numberOfLines; j++)
        {
            if(strcasecmp(students[i].surname,students[j].surname)>0)
            {
                temporary= students[i];
                students[i]= students[j];
                students[j]=temporary;
            }
            else if(strcasecmp(students[i].surname,students[j].surname)== 0 && strcasecmp(students[i].name,students[j].name)>0)

            {
                temporary= students[i];
                students[i]= students[j];
                students[j]=temporary;
            }
        }
    }
}

