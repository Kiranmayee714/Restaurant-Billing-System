#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct Item{
  char Item[30];
  float price;
  int Quantity;
};
struct orders {
 char customer[50];
 char date[50]; //change 'date ' to 'date' here
int numOfItems;
struct Item itm[50];
};

// Function to generate bills
void generateBillHeader(char name[50],char date[30]){
  printf("\n\n");
  printf("\t   AKR Restaurant");
  printf("\n\t  -----------------");
  printf("\nDate:%s",date); // This should be date not name as per your original code
  printf("\nInvoice To: %s",name);
  printf("\n");
  printf("----------------------------");
  printf("\n");
  printf("Items\t\t");
  printf("Quantity\t");
  printf("Total\t\t");
  printf("\n----------------------------");
  printf("\n\n");
}

void generateBillBody(char Item[30],int Quantity,float price){
  printf("%s\t\t",Item);
  printf("%d\t\t",Quantity);
  printf("%.2f\t\t",Quantity * price);
  printf("\n");
}

void generateBillFooter(float total){
  printf("\n");
  float dis=0.1*total;
  float netTotal=total-dis;
  float cgst=0.09*netTotal,grandTotal=netTotal + 2*cgst;
  printf("--------------------------------\n");
  printf("sub total\t\t\t%.2f",total);
  printf("\ndiscount @10%s\t\t\t%.2f","%",dis);
  printf("\n\t\t\t\t--------");
  printf("\nNet Total\t\t\t%.2f",netTotal);
  printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
  printf("\n--------------------------------");
  printf("\nGrand Total\t\t\t%.2f",grandTotal);
  printf("\n--------------------------------");
}

int main(){
  int opt,n;
  struct orders ord;
  struct orders order;
  char saveBill = 'y';
  char contFlag='y';
  char name[50];
  FILE *fp;

  //dasboard

     while(contFlag=='y'){
       float total=0.0;
       int invoiceFound=0;
    printf("\n\t============== AKR Restaurant==============\n");
     printf("\n\nPlease select your prefered operation");
    printf("\n\n1.Generate Invoice");
    printf("\n2.Show all Invoice");
printf("\n3.Search Invoice");
    printf("\n4.Exit");

  printf("\n\nYour choice:\t");
     scanf("%d",&opt);
     fgetc(stdin);

       switch(opt){
   case 1 :
     {

     system ("clear");
     printf("\nPlease enter the name of the customer:\t");
     fgets(ord.customer,50,stdin);
     ord.customer[strlen(ord.customer)-1]=0;
     strcpy(ord.date,__DATE__);
         printf("\nPlease enter the number of Items:\t");
       scanf("%d",&n);
       ord.numOfItems=n;

         for(int i=0;i<n;i++){
           fgetc(stdin);
           printf("\n\n");
           printf("Please enter the Item name %d:\t",i+1);
           fgets(ord.itm[i].Item,20,stdin);
           ord.itm[i].Item[strlen(ord.itm[i].Item)-1]=0;
           printf("Please enter the Quantity:\t");
           scanf("%d",&ord.itm[i].Quantity);
           printf("Please enter the unit price:\t");
           scanf("%f",&ord.itm[i].price);
           total +=ord.itm[i].Quantity*ord.itm[i].price;
         }
         generateBillHeader(ord.customer,ord.date);
         for(int i=0;i<ord.numOfItems;i++){
           generateBillBody(ord.itm[i].Item,ord.itm[i].Quantity,ord.itm[i].price);

         }
         generateBillFooter(total);
         printf("\nDo you want to save the invoice[y/n]:\t");
         scanf("%s",&saveBill);
         if(saveBill=='y')
           fp=fopen("RestaurantBill.dat","a+");
         fwrite(&ord,sizeof(struct orders),1,fp);
         if(fwrite !=0)
           printf("\nSuccessfully Saved");
          else

           printf("\nError in saving");
         fclose(fp);
     break;}

       case 2:
         {
           system("clear");
           fp=fopen("RestaurantBill.dat","r");
           printf("\n********Your previous Invoice******\n");
           while(fread(&order,sizeof(struct orders),1,fp)){
             float tot=0;

             generateBillHeader(order.customer,order.date);
             for(int i=0;i<order.numOfItems;i++){
               generateBillBody(order.itm[i].Item,order.itm[i].Quantity,order.itm[i].price);
               tot+=order.itm[i].Quantity*order.itm[i].price;

             }
             generateBillFooter(tot);
           }
           fclose(fp);
           break;

         }
         case 3:{
           printf("\nEnter the name of the customer:\t");
          // fgetc(stdin);
           fgets(name,50,stdin);
           name[strlen(name)-1]=0;
           system("clear");
            fp=fopen("RestaurantBill.dat","r");
            printf("\t********Invoice of %s******\n",name);
            while(fread(&order,sizeof(struct orders),1,fp)){
              float tot=0;

            if(!strcmp(order.customer,name)){
              generateBillHeader(order.customer,order.date);
              for(int i=0;i<order.numOfItems;i++){
                generateBillBody(order.itm[i].Item,order.itm[i].Quantity,order.itm[i].price);
                tot+=order.itm[i].Quantity*order.itm[i].price;

              }
              generateBillFooter(tot);
              invoiceFound = 1;

            }
              if(!invoiceFound){
                printf("sorry the invoice for %s doesnot exits",name);
              }

            }
            fclose(fp);
            break;}

           case 4:{
             printf("\n\t\t See You Again :)\n\n");
             exit(0);
             break;}

             default:{
             printf("sorry invalid option");
             break;
           }

                printf("\nDo u want to perform the another operation?[y/n]:\t");
       scanf("%s",&contFlag);

         }

     }
     printf("\n\n");
     return 0;}

