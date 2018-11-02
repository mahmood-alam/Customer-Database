/*
 * Name:
 * EID:
 * Project 7, CRM part 2
 * EE 312, Spring 2017
 */

#include <stdio.h>
#include "String.h"
#include "Customer.h"
#include "CustomerDB.h"

void readString(String&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;
int custnum = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
    database.clear();
    num_bottles = 0;
    num_rattles = 0;
    num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(String word) {
    if (word == "Bottles") {
        return &num_bottles;
    } else if (word == "Diapers") {
        return &num_diapers;
    } else if (word == "Rattles") {
        return &num_rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(String word, Customer& cust) {
    if (word == "Bottles") {
        return &cust.bottles;
    } else if (word == "Diapers") {
        return &cust.diapers;
    } else if (word == "Rattles") {
        return &cust.rattles;
    }

    /* NOT REACHED */
    return 0;
}


/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 *
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(String type) {
    Customer* result = 0;
    int max = 0;
    for (int k = 0; k < database.size(); k += 1) {
        Customer& cust = database[k];
        int *p = selectInventItem(type, cust);
        if (*p > max) {
            max = *p;
            result = &cust;
        }
    }

    return result;
}

void processPurchase() {
    String boi;
    String grill;
    int num = 0;
    readString(boi);
    readString(grill);
    readNum(num);
    if (database.isMember(boi)){
        if (grill == "Bottles"){
            //readNum(num);
            if (num_bottles >= num) {
                num_bottles -= num;
                database[boi].bottles+=num;
            }
            else{
                printf("Sorry ");
                printf("%s",database[boi].name.c_str());
                printf(", we only have %d Bottles\n", num_bottles);
            }
        }
        else if (grill == "Diapers"){
            // readNum(num);
            if (num_diapers >= num) {
                num_diapers -= num;
                database[boi].diapers+=num;
            }
            else{
                printf("Sorry ");
                printf("%s",database[boi].name.c_str());
                printf(", we only have %d Diapers\n", num_diapers);
            }

        }
        else if (grill == "Rattles"){
            // readNum(num);
            if (num_rattles >= num) {
                num_rattles -= num;
                database[boi].rattles+=num;
            }
            else{
                printf("Sorry ");
                printf("%s",database[boi].name.c_str());
                printf(", we only have %d Rattles\n", num_rattles);
            }
        }
    }else{
        // Customer cust(boi);
        //database.length++;
        if (grill == "Bottles"){
            //readNum(num);
            if (num_bottles >= num) {
                num_bottles -= num;
                database[boi].bottles+=num;
            }
            else{
                printf("Sorry ");
                printf("%s", name.c_str());
                printf(", we only have %d Bottles\n", num_bottles);

            }
        }
        else if (grill == "Diapers"){
            //readNum(num);
            if (num_diapers >= num) {
                num_diapers -= num;
                database[boi].diapers+=num;
            }
            else{
                printf("Sorry ");
                printf("%s", name.c_str());
                printf(", we only have %d Diapers\n", num_diapers);

            }
        }
        else if (grill == "Rattles"){
            //readNum(num);
            if (num_rattles >= num) {
                num_rattles -= num;
                database[boi].rattles+=num;
            }
            else{
                printf("Sorry ");
                printf("%s", name.c_str());
                printf(", we only have %d Rattles\n", num_rattles);

            }
        }
        //database[boi].name = boi;
        custnum++;

    }

}

void processSummarize() {
    printf("There are %d Bottles, %d Diapers and %d Rattles in inventory\n", num_bottles, num_diapers, num_rattles);
    printf("we have had a total of %d different customers\n", database.size());
    int bmax=0,dmax=0,rmax = 0;
    int b=0,d=0,r=0;
    for(int i=0;i<database.size();i++){
        if(database[i].bottles > b){
            b = database[i].bottles;
            bmax = i;
        }
    }
    for(int i=0;i<database.size();i++){
        if(database[i].diapers > d){
            d = database[i].diapers;
            dmax = i;
        }
    }
    for(int i=0;i<database.size();i++){
        if(database[i].rattles > r){
            r = database[i].rattles;
            rmax++;
        }
    }


    if(b>0){
        printf("%s has purchased the most Bottles (%d)\n", database[bmax].name.c_str(), b);
    } else{
        printf("no one has purchased any Bottles\n");
    }
    if(d>0){
        printf("%s",database[dmax].name.c_str());
        printf(" has purchased the most Diapers (%d)\n", d);
    } else{
        printf("no one has purchased any Diapers\n");
    }
    if(r>0){
        printf("%s",database[rmax].name.c_str());
        printf(" has purchased the most Rattles (%d)\n", r);
    } else{
        printf("no one has purchased any Rattles\n");
    }
}

void processInventory() {
    String boi;
    int num;
    readString(boi);
    if (boi == "Bottles"){
        readNum(num);
        num_bottles += num;
    }
    if (boi == "Diapers"){
        readNum(num);
        num_diapers += num;
    }
    if (boi == "Rattles"){
        readNum(num);
        num_rattles += num;
    }

}