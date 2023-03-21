#include"AdptArray.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * \brief This is Adaptive array struct
 *  This structure is used as an array with a changeable size 
 */

struct AdptArray_{
    PElement* array;                /*!< array pointer */
    int size;                       /*!< size of the array*/
    DEL_FUNC delFunct;              /*!< pointer to delete function*/
    COPY_FUNC copyFunct;            /*!< pointer to copy function*/
    PRINT_FUNC printFunct;          /*!< pointer to printing function*/
}AdptArray;
/**
 * \brief Create a Adpt Array object
 *        like Constructor for AdptArray_
 * 
 * \param copyFunc  pointer to copy function
 * \param delFunc   pointer to delete function
 * \param printFunc pointer to printing function
 * \return PAdptArray pointer to the sturct
 */
PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc,PRINT_FUNC printFunc){
    PAdptArray pAdptArray = (PAdptArray ) malloc(sizeof(AdptArray));
    if(!pAdptArray){
        printf("Memory Creation Failed\n");
        exit(1); // error creating AdptArray
    }
    pAdptArray->array=NULL;
    pAdptArray->size=0;
    pAdptArray->delFunct=delFunc;
    pAdptArray->copyFunct=copyFunc;
    pAdptArray->printFunct=printFunc;
    return pAdptArray;
}
/**
 * \brief freeing memory of AdptArray , array , copied-structs (PElements)
 * 
 * \param pAdptArray 
 */
void DeleteAdptArray(PAdptArray pAdptArray){
    int size=pAdptArray->size;
    for (size_t i = 0; i < size; i++)
    {
        PElement p = pAdptArray->array[i];
        if(p){
            pAdptArray->delFunct(p);
        }
    }
    free(pAdptArray->array);
    free(pAdptArray);
}
/**
 * \brief inserting PElement into the array at id
 *        allocating memory for the array if size<id
 *        else size>id adding PElement to the array at the appropriate index
 * \param pAdptArray pointer to AdptArray
 * \param id         index 
 * \param pElement   the structure that inserted into the array
 * \return Result    enum FAIL=0 ,SUCCESS=1
 */
Result SetAdptArrayAt(PAdptArray pAdptArray, int id, PElement pElement){
    int size=pAdptArray->size;
    Result result=FAIL;
    if(id<0){
        return result;
    }
    if(size==0){
        int newSize= id+1;
        pAdptArray->array = (PElement) calloc(newSize,sizeof(PElement));
        if(!(pAdptArray->array)){
            printf("Memory Creation Failed\n");
            exit (1);
            }
        pAdptArray->size=newSize;
    }else{
        if(size<=id){
            int newSize = id+1;
            PElement *tempArray=pAdptArray->array;
            pAdptArray->array=(PElement) calloc(newSize,sizeof(PElement));
            if(!(pAdptArray->array)){
                printf("Memory Creation Failed\n");
                exit (1);
                }
            for (int i = 0; i < pAdptArray->size; i++)
            {
                pAdptArray->array[i]=tempArray[i];
            }
            pAdptArray->size=newSize;
            free(tempArray);
        }
    }
    PElement pCopy=pAdptArray->copyFunct(pElement);
    pAdptArray->array[id]=pCopy;
    result = SUCCESS;
    return result;
}
/**
 * \brief return the pointer to PElement 
 *        if empty "cell" return NULL
 * 
 * \param pAdptArray pointer to Adaptive array
 * \param id integer index 
 * \return PElement pointer to PElement
 */
PElement GetAdptArrayAt(PAdptArray pAdptArray, int id){
    int size=pAdptArray->size;
    if(size==0 || size<id){
        return NULL;
    }else{
        PElement pOrg = pAdptArray->array[id];
        if(pOrg!=NULL){
            PElement pCopy = pAdptArray->copyFunct(pOrg);
            return pCopy;
        }else return NULL;
    }
}
/**
 * \brief size of the array
 *        if wrong return -1;
 * \param pAdptArray pointer to the AdptArray
 * \return int integer representing the size
 */
int GetAdptArraySize(PAdptArray pAdptArray){
    if((pAdptArray->size!=0) &&  (pAdptArray->array==NULL)){return -1;}
    return  pAdptArray->size;
}
/**
 * \brief printing all elements in the array
 * 
 * \param pAdptArray pointer to AdptArray
 */
void PrintDB(PAdptArray pAdptArray){
    int size=pAdptArray->size;
    for (int i = 0; i < size; i++)
    {
        PElement p = pAdptArray->array[i];
        if(p!=NULL){
            pAdptArray->printFunct(p);
        }
    }
}