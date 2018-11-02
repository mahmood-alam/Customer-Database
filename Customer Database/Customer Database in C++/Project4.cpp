/* 
 * EE312 Simple CRM Project
 *
 * Mahmood Alam
 * EE 312
 * October 9
 */

#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;

/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */
String bottles;
String diapers;
String rattles;

int botNum=0;
int diapNum=0;
int ratNum=0;

void inventory(String item, int num){
    if (StringIsEqualTo(&item, &bottles)) {
        botNum += num;
    } else if (StringIsEqualTo(&item, &diapers)) {
        diapNum += num;
    } else {
        ratNum += num;
    }
}

void sorry(String item, int num, int returnIndex){
    if (StringIsEqualTo(&item, &bottles)) {
        if(botNum>=num){
            botNum -= num;
            customers[returnIndex].bottles += num;
        } else{
            printf("Sorry ");
            StringPrint(&customers[returnIndex].name);
            printf(" , we only have %d Bottles\n", botNum);
        }
    } else if (StringIsEqualTo(&item, &diapers)) {
        if(diapNum>=num){
            diapNum -= num;
            customers[returnIndex].diapers += num;
        } else{
            printf("Sorry ");
            StringPrint(&customers[returnIndex].name);
            printf(" , we only have %d Diapers\n", diapNum);
        }
    } else {
        if(ratNum>=num){
            ratNum -= num;
            customers[returnIndex].rattles += num;
        } else{
            printf("Sorry ");
            StringPrint(&customers[returnIndex].name);
            printf(" , we only have %d Rattles\n", ratNum);
        }
    }
}

void resetVariables(){
    botNum=0;
    diapNum=0;
    ratNum=0;
}

void resetStruct(){
    int i=0;
    while(i<num_customers){
        StringDestroy(&customers[i].name);
        customers[i].bottles=0;
        customers[i].diapers=0;
        customers[i].rattles=0;
        i++;
    }
}

void response(int botMax, int ratMax, int diapMax, int botDex, int diapDex, int ratDex){
    if(botMax>0){
        StringPrint(&customers[botDex].name);
        printf(" has purchased the most Bottles (%d)\n", botMax);
    }
    else{
        printf("no one has purchased any Bottles\n");
    }
    if(diapMax>0){
        StringPrint(&customers[diapDex].name);
        printf(" has purchased the most Diapers (%d)\n", diapMax);
    }
    else{
        printf("no one has purchased any Diapers\n");
    }
    if(ratMax>0){
        StringPrint(&customers[ratDex].name);
        printf(" has purchased the most Rattles (%d)", ratMax);
    }
    else{
        printf("no one has purchased any Rattles");
    }
}

/* clear the inventory and reset the customer database to empty */
void reset(void) {
	/* your code here */
    resetVariables();
    resetStruct();
    num_customers=0;
}

void processSummarize() {
    printf("There are %d Bottles, %d Diapers and %d Rattles in inventory\n", botNum, diapNum, ratNum);
    printf("we have had a total of %d different customers\n", num_customers);
    int botMax=0;
    int diapMax=0;
    int ratMax=0;
    int botDex=0;
    int diapDex=0;
    int ratDex=0;
    int i=0;
    while(i<num_customers){
        if(botMax<customers[i].bottles){
            botMax = customers[i].bottles;
            botDex=i;
        }
        if(diapMax<customers[i].diapers){
            diapMax = customers[i].diapers;
            diapDex=i;
        }
        if(ratMax<customers[i].rattles){
            ratMax = customers[i].rattles;
            ratDex=i;
        }
        i++;
    }
    response(botMax, ratMax, diapMax, botDex, diapDex, ratDex);
}

void processPurchase() {
    bool happy=0;
    String check;
    readString(&check);
    int returnIndex=0;
    int i=0;
    while(i<num_customers){
        if (StringIsEqualTo(&check, &customers[i].name)){
            happy=true;
            returnIndex=i;
            break;
        }
        i++;
    }

    if(happy){
        bottles = StringCreate("Bottles");
        rattles = StringCreate("Rattles");
        diapers = StringCreate("Diapers");
        String item;
        readString(&item);
        int num;
        readNum(&num);
        sorry(item, num, returnIndex);
        StringDestroy(&item);
    }

    else if(num_customers<MAX_CUSTOMERS & !happy){
        num_customers++;

        customers[num_customers-1].name = check;

        String item;
        readString(&item);

        int num;
        readNum(&num);

        bottles = StringCreate("Bottles");
        diapers = StringCreate("Diapers");
        rattles = StringCreate("Rattles");

        if (StringIsEqualTo(&item, &bottles)) {
            if(botNum>=num){
                botNum -= num;
                customers[num_customers-1].bottles += num;
            } else{
                printf("Sorry ");
                StringPrint(&customers[num_customers-1].name);
                printf(" , we only have %d Bottles\n", botNum);
                StringDestroy(&customers[num_customers-1].name);
                num_customers--;
            }
        } else if (StringIsEqualTo(&item, &diapers)) {
            if(diapNum>=num){
                diapNum -= num;
                customers[num_customers-1].diapers += num;
            } else{
                printf("Sorry ");
                StringPrint(&customers[num_customers-1].name);
                printf(" , we only have %d Diapers\n", diapNum);
                StringDestroy(&customers[num_customers-1].name);
                num_customers--;
            }
        } else {
            if(ratNum>=num){
                ratNum -= num;
                customers[num_customers-1].rattles += num;
            } else{
                printf("Sorry ");
                StringPrint(&customers[num_customers-1].name);
                printf(" , we only have %d Rattles\n", ratNum);
                StringDestroy(&customers[num_customers-1].name);
                num_customers--;
            }
        }

        StringDestroy(&item);
    }

}

void processInventory() {
    bottles = StringCreate("Bottles");
    diapers = StringCreate("Diapers");
    rattles = StringCreate("Rattles");
    String item;
    readString(&item);
    int num;
    readNum(&num);
    inventory(item, num);
    StringDestroy(&item);
}
