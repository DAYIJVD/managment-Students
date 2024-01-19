#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
using namespace std;
//--->variable
string nameStudent;
//---->functions
void manageMent();
void Panel_Student(string user);
void Login_Student();
void Panel_Teacher();
void Login_Teacher();

//--->classes
class Person
{
public:
  string username;
  string password;
  string Fname;
  string Lname;
};
class User : public Person
{
public:
  bool checkUser(std::string &searchString)
  {
    std::ifstream file("db/User.txt");
    std::string line;
    while (std::getline(file, line))
    {
      if (line.find(searchString) != std::string::npos)
      {
        return true;
      }
    }
    return false;
  }
  void addUser()
  {
    std::ifstream file("db/User.txt");
    std::string line;
    while (std::getline(file, line))
    {
      int L = line.find(":");
      username = line.substr(2, L - 2);
    }
    int username_i = stoi(username) + 1;
    std::cout << "Your username: " << username_i << endl;
    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "Enter Fname: ";
    std::cin >> Fname;
    std::cout << "Enter Lname: ";
    std::cin >> Lname;
    std::ofstream file_("db/User.txt", std::ios::app);
    file_ << "S"
          << " " << username_i << ":" << password << " " << Fname << "_" << Lname << std::endl;
    file_.close();
    std::cout << "Your registration was successful" << std::endl;
    getch();
    system("cls");
    manageMent();
  }
};
class Lessons
{
public:
  string newLesson;
  string Lesson;
  void listLessons()
  {
    system("cls");
    std::ifstream file_x("db/Lessons.txt");
    std::string line;
    int i = 1;
    while (std::getline(file_x, line))
    {
      int P = line.find(":");
      string K = line.substr(0, P);
      cout << i << '.' << K << endl;
      i++;
    }
  }
};
class Student : public Person, public User, public Lessons
{
public:
  void listLessons_Student(string user)
  {
    system("cls");
    std::ifstream file_xP("db/User.txt");
    std::string lineO;
    while (std::getline(file_xP, lineO))
    {
      if (lineO.substr(0, 8) == user)
      {
        std::cout << user << std::endl;
        std::cout << lineO.substr(20) << std::endl;
      }
    }
    std::ifstream file_x("db/Lessons.txt");
    std::string line;
    int i = 1;
    while (std::getline(file_x, line))
    {
      int P = line.find(":");
      string K = line.substr(0, P);
      std::ifstream file_xL("db/Lessons/" + K + ".txt");
      std::string lineX;
      while (std::getline(file_xL, lineX))
      {
        string X = lineX.substr(0, 8);
        if (X == user)
        {
          string XL = lineX.substr(9);
          std::cout << i << "." << K << " " << XL << std::endl;
          i++;
        }
      }
    }
    getch();
    system("cls");
    Panel_Student(user);
  }
  void registerLesson(string user)
  {
    system("cls");
    listLessons();
    std::cout << "Type the name of the lesson:" << std::endl;
    cin >> Lesson;
    std::ifstream file_x("db/Lessons.txt");
    std::string line;
    bool H = false;
    while (std::getline(file_x, line))
    {
      int P = line.find(":");
      string K = line.substr(0, P);
      if (K == Lesson)
      {
        H = true;
      }
    }
    bool S = false;
    if (H)
    {
      std::ifstream file_xlp("db/Lessons/" + Lesson + ".txt");
      std::string lineP;
      while (std::getline(file_xlp, lineP))
      {
        string M = lineP.substr(0, 8);
        if (M == user)
        {
          S = true;
        }
      }
    }
    else
    {
      std::cout << "correctly name" << std::endl;
      getch();
      system("cls");
      Panel_Student(user);
    }
    if (!S)
    {
      std::ofstream file_xs("db/Lessons/" + Lesson + ".txt", std::ios::app);
      file_xs << user << " -- " << std::endl;
      file_xs.close();
      std::cout << "Successfull Register." << std::endl;
      getch();
      system("cls");
      Panel_Student(user);
    }
    else
    {
      std::cout << "You have already registered" << std::endl;
      getch();
      system("cls");
      Panel_Student(user);
    }
  }
};
class Teacher : public Person, public User, public Lessons
{
public:
  void createLesson()
  {
    listLessons();
    std::cout << "---Type back to return---" << std::endl;
    std::cout << "enter a new lesson :" << std::endl;
    std::cin >> newLesson;
    if (newLesson == "back")
    {
      system("cls");
      Panel_Teacher();
    }
    else
    {
      std::ofstream file_xs("db/Lessons/" + newLesson + ".txt", std::ios::app);
      file_xs << newLesson << ":" << std::endl;
      file_xs.close();
      std::ofstream file_("db/Lessons.txt", std::ios::app);
      file_ << newLesson << ":" << std::endl;
      file_.close();
      std::cout << "Your registration was successful" << std::endl;
      getch();
      system("cls");
      Panel_Teacher();
    }
  }
  void changeS(string *answer, bool *N)
  {
    if (*N)
    {
      string A, B, C;
      std::cout << "Enter a username student for set grade:" << std::endl;
      cin >> A;
      std::cout << "enter a old grade:" << std::endl;
      cin >> C;
      std::cout << "enter a new grade:" << std::endl;
      cin >> B;
      std::string filename = "db/Lessons/" + *answer + ".txt";
      std::string search = A + " " + C;
      std::string replace = A + " " + B;
      std::ifstream inputFile(filename);
      std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
      inputFile.close();
      size_t pos = fileContent.find(search);
      while (pos != std::string::npos)
      {
        fileContent.replace(pos, search.length(), replace);
        pos = fileContent.find(search, pos + replace.length());
      }
      std::ofstream outputFile(filename);
      outputFile << fileContent;
      outputFile.close();
      registeredSList(*answer);
    }
    else
    {
      std::cout << "invalid lesson." << std::endl;
      getch();
      system("cls");
      registeredSList(*answer);
    }
  };
  void SetS(string *answer, bool *N)
  {
    if (*N)
    {
      string A, B;
      std::cout << "Enter a username student for set grade:" << std::endl;
      cin >> A;
      std::cout << "enter a grade:" << std::endl;
      cin >> B;
      std::string filename = "db/Lessons/" + *answer + ".txt";
      std::string search = A + " --";
      std::string replace = A + " " + B;
      std::ifstream inputFile(filename);
      std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
      inputFile.close();
      size_t pos = fileContent.find(search);
      while (pos != std::string::npos)
      {
        fileContent.replace(pos, search.length(), replace);
        pos = fileContent.find(search, pos + replace.length());
      }
      std::ofstream outputFile(filename);
      outputFile << fileContent;
      outputFile.close();
      registeredSList(*answer);
    }
    else
    {
      std::cout << "invalid lesson." << std::endl;
      getch();
      system("cls");
      registeredSList(*answer);
    }
  };
  void registeredSList(string answer)
  {
    listLessons();
    int Choice;
    bool N = false;
    std::cout << "-----type a back for back----- " << std::endl;
    if (!answer.length())
    {
      std::cout << "Type a lesson for students list and set grades :" << std::endl;
      cin >> answer;
    }
    if (answer == "back")
    {
      system("cls");
      Panel_Teacher();
      return;
    }
    std::ifstream file_xP("db/Lessons.txt");
    std::string line;
    while (std::getline(file_xP, line))
    {
      int P = line.find(":");
      string K = line.substr(0, P);
      if (K == answer)
      {
        system("cls");
        N = true;
        std::ifstream file_x("db/Lessons/" + answer + ".txt");
        std::string linee;
        while (std::getline(file_x, linee))
        {
          std::cout << linee.substr(0, 20) << std::endl;
        }
      }
    }

    std::cout << "----------------------" << std::endl;
    std::cout << "1"
              << ".enter a set grade:" << std::endl;
    std::cout << "2"
              << ".a change grade:" << std::endl;
    std::cout << "3"
              << ".Exit" << std::endl;
    cin >> Choice;
    switch (Choice)
    {
    case 1:
      SetS(&answer, &N);
      break;
    case 2:
      changeS(&answer, &N);
      break;
    case 3:
      system("cls");
      registeredSList("");
    default:
      break;
    }
  }
  void listS()
  {
    system("cls");
    std::ifstream file("db/User.txt");
    std::string line;
    int i = 1;
    while (std::getline(file, line))
    {
      if (line[0] == 'S')
      {
        string K = line.substr(19);
        string S = line.substr(2, 8);
        cout << i << '.' << K << " " << S << endl;
        i++;
      }
    }
    std::cout << "Enter to return ..." << std::endl;
    getch();
    system("cls");
    Panel_Teacher();
  }
};

//--->Teacher
void Login_Teacher()
{
  User Te;
  std::cout << "Enter username: ";
  std::cin >> Te.username;
  std::cout << "Enter password: ";
  std::cin >> Te.password;
  string uss = "T " + Te.username + ":" + Te.password;
  if (Te.checkUser(uss))
  {
    std::cout << "Login successful!" << std::endl;
    getch();
    system("cls");
    Panel_Teacher();
  }
  else
  {
    std::cout << "Invalid username or password." << std::endl;
    std::cout << "Enter to return ..." << std::endl;
    getch();
    system("cls");
    manageMent();
  }
}
void Panel_Teacher()
{
  Teacher Te;
  int choice;
  cout << "1.Create a new lesson" << endl;
  cout << "2.Enter students' grades" << endl;
  cout << "3.List of registered students" << endl;
  cout << "4.Exit." << endl;
  cout << "Your Choice:";
  std::cin >> choice;
  switch (choice)
  {
  case 1:
    Te.createLesson();
    break;
  case 2:
    Te.registeredSList("");
    break;
  case 3:
    Te.listS();
    break;
  case 4:
    system("cls");
    manageMent();
    break;
  default:
    cout << "Invalid Your Choice!" << endl;
    getch();
    system("cls");
    Panel_Teacher();
    break;
  }
};

//--->Student
void Login_Student()
{
  User St;
  std::string username, password;
  std::cout << "Enter username: ";
  std::cin >> St.username;
  std::cout << "Enter password: ";
  std::cin >> St.password;
  string us = "S " + St.username + ":" + St.password;
  if (St.checkUser(us))
  {
    std::cout << "Login successful!" << std::endl;
    getch();
    system("cls");
    Panel_Student(St.username);
  }
  else
  {
    std::cout << "Invalid username or password." << std::endl;
    std::cout << "Enter to return ..." << std::endl;
    getch();
    system("cls");
    manageMent();
  }
}
void Panel_Student(string user)
{
  std::ifstream file_x("db/User.txt");
  std::string line;
  while (std::getline(file_x, line))
  {
    if (line.substr(2, 8) == user)
    {
      std::cout << user << std::endl;
      nameStudent = line.substr(20);
      std::cout << nameStudent << std::endl;
    }
  }
  Student st;
  int choice;
  std::cout << "1.register in lessons." << std::endl;
  std::cout << "2.List of lessons" << std::endl;
  std::cout << "3.Exit" << std::endl;
  std::cout << "Your Choice:" << std::endl;
  std::cin >> choice;
  switch (choice)
  {
  case 1:
    st.registerLesson(user);
    break;
  case 2:
    st.listLessons_Student(user);
    break;
  case 3:
    system("cls");
    manageMent();
    break;
  default:
    cout << "Invalid Your Choice!" << endl;
    getch();
    system("cls");
    Panel_Student(user);
    break;
  }
};
//--->main program
int main()
{
  std::cout << "          -----Welcome to University TheDN-----" << std::endl;
  std::cout << "          ------------Click To Enter-----------" << std::endl;
  getch();
  system("cls");
  manageMent();
}
//--->managment
void manageMent()
{
  int choice;
  cout << "1.Student Login" << endl;
  cout << "2.Teacher Login " << endl;
  cout << "3.Student SignUp " << endl;
  User newUser;
  cout << "Your Choice:";
  std::cin >> choice;
  switch (choice)
  {
  case 1:
    Login_Student();
    break;
  case 2:
    Login_Teacher();
    break;
  case 3:
    newUser.addUser();
    break;
  default:
    cout << "Invalid Your Choice!" << endl;
    getch();
    system("cls");
    manageMent();
    break;
  }
}