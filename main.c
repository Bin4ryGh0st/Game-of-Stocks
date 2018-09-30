#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

COORD coord;
int i,j,k,c,z,tempi;
char tempc,tempstr[50],tempnewfile[50],tempnewfile1[50];
FILE *fptr;
FILE *fptr2;
FILE *fptr3;
FILE *ftemp;

struct details
{
    char name[50];
    char phno[12];
    char email[100];
    char pas[50];
    char pan[10];
    int balance;
}det,temps;

typedef struct
{
    char c_name[50];
    int price;
}company;

company comp;
company tempco;

struct verify
{
    char pas[50];
    char email[100];
    char name[50];
}ver;

typedef struct
{
    char coname[50];
    char status[50];
    int buyingPrice;

    struct stocknode *link;
}stocknode;

char tempstatus[50],tempconame[50];
int tempbuyingPrice;

int n=0;
stocknode *stockhead = NULL;
stocknode *stocktemp1 = NULL;
stocknode *stocktemp2 = NULL;
stocknode *stocktemp3 = NULL;

void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}*/

void logo(int x, int y)
{
    gotoxy(x,y);
    printf("  ___      ___      ___   ");
    gotoxy(x,y+1);
    printf("//   \\\\  //   \\\\  //      ");
    gotoxy(x,y+2);
    printf("|| __    ||   ||  \\\\___   ");
    gotoxy(x,y+3);
    printf("||   ||  ||   ||      \\\\  ");
    gotoxy(x,y+4);
    printf("\\\\___// .\\\\___// . ___// .");
}

int makeGeneralBox(int xc,int yc,int lx,int ly,int dt)
{
    for(i=0;i<lx+1;i++)
    {
        gotoxy(xc+i,yc);
        if(i==0 || i==lx)
            printf("+");
        else
            printf("-");

        gotoxy(xc+lx-i,yc+ly);
        if(i==0 || i==lx)
            printf("+");
        else
            printf("-");
        delay(dt);
    }
    for(i=0;i<ly;i++)
    {
        gotoxy(xc,yc+ly-i);
        if(i==0)
            printf("+");
        else
            printf("|");
        gotoxy(xc+lx,yc+1+i);
        if(i==ly-1)
            printf("+");
        else
            printf("|");
        delay(dt);
    }
}

void cls(int x)
{
    system("cls");
    makeGeneralBox(1,0,117,29,0);
    if(x==1)
    {
        logo(92,24);
    }
}

void nStockList(int size)
{
    n=size;
    if(size>=1)
    {
        stockhead = (stocknode*)malloc(sizeof(stocknode));
        stocktemp1=stockhead;
        for(i=0;i<size-1;i++)
        {
            stocktemp1->link = (stocknode*)malloc(sizeof(stocknode));
            stocktemp1 = stocktemp1->link;
        }
        stocktemp1->link = NULL;
    }
    else
    {
        stockhead=NULL;
        printf("\nEnter Size greater than zero");
    }
}

int addInStockList(int p)
{
    if(p==1)
    {
        stocktemp1=stockhead;
        stockhead=(stocknode*)malloc(sizeof(stocknode));
        stocktemp2=stockhead;
        stocktemp2->link=stocktemp1;
        n=n+1;
    }
    else if(p>1 && p<=n+1)
    {
        stocktemp1=stockhead;
        for(i=0;i<p-2;i++)
        {
            stocktemp1 = stocktemp1->link;
        }
        stocktemp2=stocktemp1->link;
        stocktemp1->link=(stocknode*)malloc(sizeof(stocknode));
        stocktemp1=stocktemp1->link;
        stocktemp1->link=stocktemp2;
        n=n+1;
    }
    else
        printf("INSERT VALUE IN RANGE(aLL)");
    stocktemp1 = NULL;
    stocktemp2 = NULL;
}

int printCurrentList()
{
    printf("\n");
    stocktemp1=stockhead;
    gotoxy(8,4);
    printf("S.no. Company");
    gotoxy(23,4);
    printf("Buying Price");
    gotoxy(8,5);
    printf("----------------------------");
    c=1;
    while(stocktemp1!= NULL)
    {
        gotoxy(10,5+c);
        printf("%d.  %s",c,stocktemp1->coname);
        gotoxy(27,5+c);
        printf("%d",stocktemp1->buyingPrice);
        stocktemp1=stocktemp1->link;
        c++;
    }
}

void stockSellingConfirmation()
{
    switch(_getch())
    {
    case 's':
    case 'S':
        makeGeneralBox(75,6,33,8,0);
        gotoxy(79,8);
        printf("Enter S.no of the Company");
        gotoxy(77,9);
        printf("  or 'q' key to exit Lobby    ");
        gotoxy(90,10);
        printf("...");
        gotoxy(91,12);
        switch(tempc=_getch())
        {
        case 'q':
        case 'Q':
            loggedIn();
            break;
        default:
            if(((int)tempc-(int)'0')>c-1)
            {
                cls(1);
                gotoxy(48,5);
                printf("SELLING FAILED!!");
                _getch();
                loggedIn();
                break;
            }
            else
            {
                cls(1);
                gotoxy(52,5);
                printf("SUCCESS!!");
                _getch();
            }
        }

    default :
        loggedIn();
        break;
    }
}

void currentStockStatus()
{
    FILE *fptr;
    strcpy(tempnewfile,"Indi\\");
    strcat(tempnewfile,ver.name);
    strcat(tempnewfile,".txt");
    fptr=fopen(tempnewfile,"r");
    nStockList(1);
    stocktemp3=stockhead;
    stocktemp2=stockhead;
    while(fscanf(fptr,"%s %s %d\n",tempstatus,tempconame,&tempbuyingPrice)>=1)
    {
        if((strcmp(tempstatus,"B")==0)||(strcmp(tempstatus,"b")==0))
        {
            strcpy(stocktemp3->status,tempstatus);
            strcpy(stocktemp3->coname,tempconame);
            stocktemp3->buyingPrice=tempbuyingPrice;
            addInStockList(n+1);
            stocktemp2=stocktemp3;
            stocktemp3=stocktemp3->link;
        }
        else
        {
            continue;
        }
    }
    if(n==1)
    {
        stockhead=NULL;
        printf("NO STOCKS ARE AVAILABLE");
    }
    stocktemp2->link=NULL;
    stocktemp3->link=NULL;
    printCurrentList();
    fclose(fptr);
    makeGeneralBox(75,6,33,8,0);
    gotoxy(84,8);
    printf("Enter S to Sell");
    gotoxy(77,9);
    printf("or any other key to exit Lobby");
    gotoxy(90,10);
    printf("...");
    gotoxy(91,12);
    stockSellingConfirmation();
}

void printTitle()
{
    gotoxy(52,8);
    printf("Welcome to the ");
    makeGeneralBox(40,10,40,2,10);
    gotoxy(50,11);
    printf("The");
    delay(500);
    printf(" Game");
    delay(500);
    printf(" Of");
    delay(500);
    printf(" Stocks!!");
}

void countDown()
{
    cls(0);
    logo(47,9);
    gotoxy(45,15);
    printf("_____________________________");
    gotoxy(50,16);
    printf("The Game Of Stocks !!");
    gotoxy(45,17);
    printf("_____________________________");
    gotoxy(45,20);
    printf("Game will start in 5 seconds...");
    for(i=4;i>=0;i--)
    {
        gotoxy(64,20);
        delay(1000);
        printf("%d",i);
    }
}

void credits()
{
    gotoxy(45,15);
    delay(500);
    printf("DEVELOPED BY:-");
    gotoxy(45,16);
    delay(500);
    printf("(BATCH : B8)");
    gotoxy(45,17);
    delay(500);
    printf("Kaushal Bhansali (17103299)");
    gotoxy(45,18);
    delay(500);
    printf("Gyan Ranjan      (17103306)");
    gotoxy(45,19);
    delay(500);
    printf("Pradhuman Gupta  (17103301)");
    gotoxy(45,20);
    delay(500);
    printf("Ankit Bathla     (17103302)");
}

void ui()
{
    system("color a");
    makeGeneralBox(1,0,117,29,10);
    countDown();
    system("color A");
    delay(200);
    system("color C");
    delay(200);
    system("color A");
    delay(200);
    system("color C");
    delay(200);
    system("color A");
    delay(200);
    cls(0);
    makeGeneralBox(30,6,60,15,20);
    printTitle();
    delay(500);
    makeGeneralBox(40,14,40,7,0);
    credits();
    logo(49,22);
    delay(2000);
    cls(1);
}

int signUpAsIndi()
{
    strcpy(tempnewfile,"Indi\\");
    gotoxy(55,3);
    printf("SIGN UP");
    fflush(stdin);
    gotoxy(20,5);
    printf("Name:");
    makeGeneralBox(18,6,60,2,0);
    gotoxy(20,7);
    gets(det.name);
    strcat(tempnewfile,det.name);
    fflush(stdin);
    gotoxy(20,9);
    printf("Email:");
    makeGeneralBox(18,10,60,2,0);
    gotoxy(20,11);
    gets(det.email);
    fflush(stdin);
    gotoxy(20,13);
    printf("Password:");
    makeGeneralBox(18,14,60,2,0);
    gotoxy(20,15);
    i=0;
    while((int)(tempc=_getch())!=13)
    {
        if((int)tempc!=8)
        {
            gotoxy(20+i,15);
            printf("*");
            det.pas[i]=tempc;
            i=i+1;
        }
        else if(i>0)
        {
            i=i-1;
            gotoxy(20+i,15);
            printf(" ");
            gotoxy(20+i,15);
        }
    }
    det.pas[i]='\0';
    fflush(stdin);
    gotoxy(20,17);
    printf("Phone no.:");
    makeGeneralBox(18,18,60,2,0);
    gotoxy(20,19);
    gets(det.phno);
    fflush(stdin);
    gotoxy(20,21);
    printf("Pan no.:");
    makeGeneralBox(18,22,60,2,0);
    gotoxy(20,23);
    gets(det.pan);
    fflush(stdin);
    strcpy(tempnewfile1,tempnewfile);
    strcat(tempnewfile1,"bal.txt");
    strcat(tempnewfile,".txt");
    fptr3=fopen(tempnewfile,"w");
    fclose(fptr3);
    fptr3=fopen(tempnewfile1,"w");
    fprintf(fptr3,"%d\n",10000);
    fclose(fptr3);


}

int logIn()
{
    gotoxy(57,3);
    printf("LOG IN");
    fflush(stdin);
    gotoxy(37,11);
    printf("Email:");
    makeGeneralBox(35,12,50,2,0);
    gotoxy(37,13);
    gets(temps.email);
    fflush(stdin);
    gotoxy(37,15);
    printf("Password:");
    makeGeneralBox(35,16,50,2,0);
    gotoxy(37,17);
    i=0;
    while((int)(tempc=_getch())!=13)
    {
        if((int)tempc!=8)
        {
            gotoxy(37+i,17);
            printf("*");
            temps.pas[i]=tempc;
            i=i+1;
        }
        else if(i>0)
        {
            i=i-1;
            gotoxy(37+i,17);
            printf(" ");
            gotoxy(37+i,17);
        }
    }
    temps.pas[i]='\0';
    fflush(stdin);
    ftemp=fopen("Records\\pass.txt","r");
    while(fscanf(ftemp,"%s %s %s",ver.email,ver.pas,ver.name)>=1)
    {
        if(strcmp(ver.email,temps.email)==0)
        {
            if((strcmp(ver.pas,temps.pas)==0))
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }
    }
    fclose(ftemp);
    return 2;
}

int form()
{
    makeGeneralBox(28,12,25,2,0);
    gotoxy(32,13);
    printf("Enter 1 to LOG IN");
    makeGeneralBox(28,15,25,2,0);
    gotoxy(32,16);
    printf("Enter 2 to SIGN UP");
    makeGeneralBox(65,12,25,5,0);
    gotoxy(67,13);
    printf("Enter Your Choice Here:");
    gotoxy(77,15);
    switch((int)_getch()-(int)'0')
    {
    case 1:
        cls(1);
        switch(logIn())
        {
        case 1:
            cls(1);
            gotoxy(57,11);
            break;
        case 2:
            cls(1);
            gotoxy(40,9);
            printf("Incorrect Credentials Please Try Again!!");
            system("color c");
            form();
            system("color a");
            break;
        default:
            cls(1);
            gotoxy(55,15);
            printf("Wrong Input");
            delay(1000);
            exit(1);
        }
        break;
    case 2:
        cls(1);
        fptr=fopen("Records\\data.txt","a");
        fptr2=fopen("Records\\pass.txt","a");
        signUpAsIndi();
        fprintf(fptr,"%s %s %s %s %s\n",det.name,det.pas,det.email,det.phno,det.pan);
        fprintf(fptr2,"%s %s %s\n",det.email,det.pas,det.name);
        fclose(fptr2);
        fclose(fptr);
        cls(1);
        gotoxy(45,9);
        printf("Please, Press 1 to Proceed...");
        form();
        break;
    case 3:
            cls(1);
            gotoxy(50,15);
            printf("STOCK MARKET NEVER SLEEPS!!");
            delay(2000);
            gotoxy(25,20);
            exit(1);
    default:
        cls(1);
        gotoxy(55,15);
        printf("Wrong Input");
        delay(1000);
        exit(1);
    }
    return 0;
}

int rankOfCompanies()
{
    fptr=fopen("Records\\companies.txt","r");
    tempi=1;
    while((tempc=getc(fptr))!=EOF)
    {
        if(tempc=='\n')
        {
            tempi=tempi+1;
        }
    }
    company tempcomp[tempi-1];
    fclose(fptr);
    fptr=fopen("Records\\companies.txt","r");
    j=0;
    while((j<=tempi-2)&&(fscanf(fptr,"%s %d",tempcomp[j].c_name,&tempcomp[j].price)!=EOF))
    {
        j++;
    }
    fclose(fptr);

    fptr=fopen("Records\\companies.txt","w");
    for(i=0;i<=tempi-2;i++)
    {
        if(rand()%2==0 && tempcomp[i].price>=30)
            fprintf(fptr,"%s %d\n",tempcomp[i].c_name,(tempcomp[i].price-(rand()%6)));
        else
            fprintf(fptr,"%s %d\n",tempcomp[i].c_name,(tempcomp[i].price+(rand()%6)));
    }
    fclose(fptr);
    fptr=fopen("Records\\companies.txt","r");
    j=0;
    while((j<=tempi-2)&&(fscanf(fptr,"%s %d",tempcomp[j].c_name,&tempcomp[j].price)!=EOF))
    {
        j++;
    }
    fclose(fptr);

    for(i=0;i<=tempi-2;i++)
    {
        for(j=0;j<=tempi-i-3;j++)
        {
            if(tempcomp[j+1].price>=tempcomp[j].price)
            {
                tempcomp[j+1].price=tempcomp[j+1].price+tempcomp[j].price;
                tempcomp[j].price=tempcomp[j+1].price-tempcomp[j].price;
                tempcomp[j+1].price=tempcomp[j+1].price-tempcomp[j].price;
                strcpy(tempstr,tempcomp[j].c_name);
                strcpy(tempcomp[j].c_name,tempcomp[j+1].c_name);
                strcpy(tempcomp[j+1].c_name,tempstr);
            }
        }
    }
    fptr=fopen("Records\\companies.txt","w");
    for(i=0;i<=tempi-2;i++)
    {
        fprintf(fptr,"%s %d\n",tempcomp[i].c_name,tempcomp[i].price);
    }
    fclose(fptr);
    return tempi;
}

void mainPage()
{
    form();
    loggedIn();
}

void rankTable()
{
    fptr=fopen("Records\\companies.txt","r");
        gotoxy(8,2);
        printf("Rank   Company    Buying Price   Selling Price");
        gotoxy(8,3);
        printf("----------------------------------------------");
        c=1;
        while(fscanf(fptr,"%s %d",comp.c_name,&comp.price)>1)
        {
            gotoxy(9,3+c);
            printf("%d.",(c+1)/2);
            gotoxy(15,3+c);
            printf("%s",comp.c_name);
            gotoxy(30,3+c);
            printf("$%d",comp.price);
            gotoxy(45,3+c);
            printf("$%d",(comp.price * 98)/100);
            c++;
            gotoxy(8,3+c);
            printf("----------------------------------------------");
            c++;
        }
        fclose(fptr);
}

int buyStock()
{
    switch(_getch())
    {
    case 'B':
    case 'b':
        cls(1);
        fptr3=fopen("Records\\companies.txt","r");
        rankTable();
        makeGeneralBox(75,6,33,8,0);
        gotoxy(79,8);
        printf("Enter name of the Company");
        gotoxy(78,9);
        printf("or 'quit' key to exit Lobby");
        gotoxy(90,10);
        printf("...");
        gotoxy(88,12);
        fflush(stdin);
        gets(tempstr);
        fflush(stdin);
        if(strcmp(tempstr,"quit")!=0)
        {
            strcpy(tempnewfile,"Indi\\");
            strcat(tempnewfile,ver.name);
            strcpy(tempnewfile1,tempnewfile);
            strcat(tempnewfile1,"bal.txt");
            strcat(tempnewfile,".txt");
            fptr2=fopen(tempnewfile,"a");
            fptr=fopen(tempnewfile1,"r");
            fscanf(fptr,"%d",&k);
            fclose(fptr);
            fptr=fopen(tempnewfile1,"w");
            while(fscanf(fptr3,"%s %d",tempco.c_name,&tempco.price)>=1)
            {
                if(strcmp(tempstr,tempco.c_name)==0 && k>=tempco.price)
                {
                    fprintf(fptr2,"B %s %d\n",tempco.c_name,tempco.price);
                    k=k-tempco.price;
                    fprintf(fptr,"%d",k);
                    cls(1);
                    gotoxy(45,5);
                    printf("STOCK BOUGHT SUCCESSFULLY!");
                    fclose(fptr);
                    fclose(fptr2);
                    fclose(fptr3);
                    _getch();
                    loggedIn();
                }
                else
                    continue;
            }
            fprintf(fptr,"%d\n",k);
            cls(1);
            gotoxy(50,5);
            printf("BUYING FAILED!");
            fclose(fptr);
            fclose(fptr2);
            fclose(fptr3);
            _getch();
            loggedIn();
        }
        else
        {
            loggedIn();
        }
        fclose(fptr3);
        cls(1);
        break;
    default :
        loggedIn();
        exit(1);
    }
    return 0;
}

int loggedIn()
{
    cls(1);
    makeGeneralBox(28,9,25,3,0);
    gotoxy(35,10);
    printf("Enter 1 for ");
    gotoxy(31,11);
    printf("CURRENT MARKET STATUS");
    makeGeneralBox(28,13,25,3,0);
    gotoxy(35,14);
    printf("Enter 2 to ");
    gotoxy(30,15);
    printf("Visit Your Own Profile");
    makeGeneralBox(28,17,25,3,0);
    gotoxy(35,18);
    printf("Enter 3 for ");
    gotoxy(37,19);
    printf("LOGOUT");
    makeGeneralBox(65,12,25,5,0);
    gotoxy(67,13);
    printf("Enter Your Choice Here:");
    gotoxy(55,4);
    printf("WELCOME %s!",ver.name);
    gotoxy(77,15);
    switch((int)_getch()-(int)'0')
    {
    case 1:
        cls(1);
        rankOfCompanies();
        rankTable();
        makeGeneralBox(75,6,33,8,0);
        gotoxy(84,8);
        printf("Enter B to Buy");
        gotoxy(77,9);
        printf("or any other key to exit Lobby");
        gotoxy(90,10);
        printf("...");
        gotoxy(91,12);
        buyStock();
        break;
    case 2:
        cls(1);
        currentStockStatus();
        break;
    case 3:
        cls(1);
        mainPage();
        break;
    default:
        cls(1);
        gotoxy(55,15);
        printf("Wrong Input");
        delay(1000);
        exit(1);
    }
    return 0;
}

int main()
{
    ui();
    mainPage();
}
