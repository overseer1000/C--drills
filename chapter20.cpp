#include "std_lib_facilities.h"

ostream& print_array(ostream& os, int* a, int n)
{
    for (int i = 0; i < n; i++)
        os << a[i] << " ";
    os << endl;
    return os;
}

ostream& print_vector(ostream& os, vector<int>& v)
{
    for (int i = 0; i < v.size(); i++)
        os << v[i] << " ";
    os << endl;
    return os;
}

ostream& print_list(ostream& os, list<int>& l)
{
    list<int>::iterator it;
    for (it = l.begin(); it!=l.end(); it++)
        os << *it <<" ";
    os << endl;
    return os;
}

ostream& increase_list(ostream& os, list<int>& l, int n)
{
    list<int>::iterator it;
    for (it = l.begin(); it!=l.end(); it++)
        os << *it + n <<" ";
    os << endl;
    return os;
} 

/*Q6. Write a simple copy() operation：
            template<typename Iter1, typename Iter2>
                //requires Input_iterator<Iter1>() && Output_iterator<Iter2>() 
            Iter2 copy(Iter1 f1, Iter1 e1, Iter2 f2);
    that copies [f1,e1) to [f2,f2+(e1–f1)) and returns f2+(e1–f1) just like the standard library copy function. 
    Note that if f1==e1 the sequence is empty, so that there is nothing to copy.*/

template<typename Iter1, typename Iter2> // requires Input_iterator<Iter1>() && Output_iterator<Iter2>()
Iter2 copy(Iter1 f1, Iter1 e1, Iter2 f2)  
{
    if(f1 != e1)
        for (Iter1 p = f1; p != e1; p++)
        {
            *f2 = *p;
            f2++;
        }
    return f2;
}

int main()
{  //Remember to test after each step.

//Q1. Define an array of ints with the ten elements { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }.
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    print_array(cout, a,10);

//Q2. Define a vector<int> with those ten elements.
    vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    print_vector(cout, v);

//Q3. Define a list<int> with those ten elements.
    list<int> l = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    print_list(cout, l);

//Q4. Define a second array, vector, and list, each initialized as a copy of the first array, vector, and list, respectively.
    int a1[10];
    for (int i = 0; i < 10; i++)
        a1[i] = a[i];

    vector<int> v1 = v;
    list <int> l1 = l;

    print_array(cout,a1,10);    
    print_vector(cout, v1);
    print_list(cout, l1);  

/* Q5. Increase the value of each element in the array by 2; increase the value of each element in the vector by 3; 
   increase the value of each element in the list by 5.*/
    for (int i = 0; i < 10; i++)
        a[i] = a[i] + 2;
    print_array(cout, a,10);

    for (int i = 0; i < 10; i++)
        v[i] = v[i] + 3;
    print_vector(cout, v);

    increase_list(cout, l, 5);

//Q7. Use your copy() to copy the array into the vector and to copy the list into the array.
    list<int> lis_a(a,a+10);
    std::copy(lis_a.begin(), lis_a.end(), v.begin());
    std::copy(l.begin(), l.end(), lis_a.begin());
    print_vector(cout, v);
    print_array(cout, a,10);

/*Q8. Use the standard library find() to see if the vector contains the value 3 and print out its position if it does; 
      use find() to see if the list contains the value 27 and print out its position if it does. 
      The “position” of the first element is 0, the position of the second element is 1, etc.
      Note that if find() returns the end of the sequence, the value wasn’t found.*/
    vector<int>::iterator it1;
    it1 = find(v.begin(), v.end(), 3);
    if (it1 != v.end())
        cout << "The position is: " << distance(v.begin(), it1) << endl;
    else
        cout << "It can not be find" << endl;

    list<int>::iterator it2;
    it2 = find(l.begin(), l.end(), 27);
    if (it2 != l.end())
        cout << "The position is:" << distance(l.begin(), it2) << endl;
    else
        cout <<"It can not be find" << endl;

    return 0;
}