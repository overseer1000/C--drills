#include "std_lib_facilities.h"

int main()
{
   String first_name;
   
 //1
  cout << "Enter the name of the person you want to write to  ";
  cin >> first_name;
  
//2
  cout << "Dear " << first_name <<",\n";
  cout << "     Hope you doing well bro, call me soon .\n";

//3
  String  friend_name;
  cin >> friend_name;
  cout << "have you seen " <<  friend_name << " lately ?\n";

//4 
 
 char friend_sex = '0';
 cout << " What's the sex of your friend (m/f) ?\n";
 cin >> friend_sex;

 if (friend_sex == 'm')
 cout << "If you see " << friend_name << " please tell him to call me.\n";
 if (friend_sex == 'f')
 cout << "If you see " << friend_name << " please tell her to call me.\n";

//5
cout << "How old is " << first_name << "?\n";
int age;
cin >> age;

if (age <=0 || age>=110 )
simple_error("Your'e kidding !");

cout << "I heard you just turned " << age << " years old\n";

//6
if (age < 12 ) cout << "Next year you would be " << age+1.;
if (age == 17) cout << "Next year you would be able to vote\n";
if (age >= 70) cout << "I hope you are enjoying  retirement\n";

//7
cout << "Yours sincerely, \n\n";

cout << "Tonte";


  

return 0;
}

 
