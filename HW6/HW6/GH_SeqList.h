/*
 *File:GH_SeqList_h
 *Version:1.0
 *-------------------------------------------
 *Usage:a simple data structure,it can store some elems
 *Remark:using template
 */

#ifndef _GH_SeqList_h
#define _GH_SeqList_h

#include<iostream>
using namespace std;

template <class ElemType> 
class SeqList
{
	private:
		ElemType *elem;    // Array to store the data of each element.
		int length;       // Existing element number in the list, also the length of list.
		int MaxSize;     // Maximum size of the array elem. 
	
	public:
		SeqList(int InitSize);   // Constructor.
		~SeqList();       // Destructor.
		
		void Clear();       // Clear all the elements in the sequence list.
		bool IsEmpty();     // Return TRUE if the list is empty, otherwise return FALSE.
		int Length();       // Return the length of the list.
		ElemType Get(int i) const;	// Return the value of the ith element.
		int Find(ElemType e) const;  // Return element order if its value is equal to e, return 0 if no such element exists.
		int Insert(int i, ElemType e);  // Insert a new element with the value e in the ith position.	
										// Alter the former ith element to the (i+1)th one. 
										// Return 1 if inserting is successful, otherwise return 0. 
		ElemType Delete(int i);		  // Delete the ith element and return its value.
};

#endif