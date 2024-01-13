// 	std::cout << BLUE << "25 METER POOL SCHEDULE\n\n" << RESET;
// 	std::cout << RED << "FOR YOUTH DEVELOPMENT " << RESET << "Empowering young people to reach their full potential\n";
// 	std::cout << RED << "FOR HEALTHY LIVING " << RESET << "Improving individual and community well-being\n";
// 	std::cout << RED << "FOR SOCIAL RESPONSIBILITY " << RESET << "Providing support and inspiring action in our communities\n\n";
// 	std::cout << "Choose one of the following options:\n";
// 	std::cout << "1. " << std::endl;
// 	std::cout << "2. " << std::endl;
// 	std::cout << "3. " << std::endl;
// 	std::cout << "4. " << std::endl;
// 	std::cout << "5. Exit" << std::endl;
// }


/* Мета: написати програму для автоматизації обліку роботу басейна. У басейна є 3 плавальні доріжки. На кожній з доріжок в окремий момент часу може працювати тільки один тренер з певною групою. Кількість осіб в групі обмежена. Для простоти припустимо числом 10. Потрібно розробити програму, яка б дозволяла формувати розклад роботи тренера. Припустимо, що заклад працює з 9:00 до 21:00 за київським часом, кожного дня, крім неділі. Але окремий тренер може працювати якусь певну кількість годин і днів з цього часу. Потім його може змінити інший тренер. Потрібно створити список тренерів з прізвищами, номерами телефонів, ставками погодинної оплати і розкладом занять.

В розкладі занять має бути вказано номер доріжки, час проведення занять і група. Має бути можливість формування зведеного розкладу по всіх доріжках, тренерах, групах. Має бути можливість створення і вилучення нових груп і додавання й вилучення дітей, які займаються плаванням. В кожного учасника групи має бути ім’я, ім’я одного з батьків, контактний номер телефона, обсяг проплачених коштів і прив’язка до певного списку занять. Потрібно розробити можливість пошуку учасника за контактним номером телефона і вивід на екран розкладу занять на тиждень для нього.

Для виконання завдання можете використовувати будь-які структури даних. Але результати треба буде зберігати у файл до наступного запуска програми.

У вас мають бути наступні класи і об’єкти:
1. Доріжки мають номер і список занять.
2. Заняття характеризується часом, номером доріжки, тренером і групою.
3. Тренер має прізвище, номер телефону, погодинна ставка і пов’язаний із списком занять.
4. Група має номер і список учнів, пов’язана із заняттями.
5. Учень має прізвище, прізвище, ім’я одного з батьків, контактний номер телефона і кількість проплачених занять. */

// General libraries
//#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <windows.h>
#include <conio.h>
#include <string>
#include <iomanip>
#include <sstream>

// Specific libs
#include "Lane.h"
#include "Instructor.h"
#include "Group.h"

using namespace std;

#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define PURPLE  "\033[35m"
#define RED     "\033[31m"

std::string textToSave;
std::stringstream buffer;
std::vector<std::shared_ptr<Lane>> allLanes;
std::vector<std::shared_ptr<Group>> allGroups;
std::vector<std::shared_ptr<Instructor>> allInstructors;

// Tool Function 1 | 
string timestamp(bool format) {
  // This block of code is used to get the current system timestamp into "timestamp".
  struct tm time;
  __time32_t aclock;
  char timestamp[32];
  _time32( &aclock );                 // Get time in seconds.
  _localtime32_s( &time, &aclock );   // Convert time to struct tm form.
  // The next line makes the timestamp in the format "18 Sep 2023 15:14:32".
  if (format) { strftime(timestamp, sizeof(timestamp), " %d %b %Y %H:%M:%S | ", &time); return string(timestamp); }
  // The next line makes the timestamp in the format "2024_11_01__17_11_07".
  strftime(timestamp, sizeof(timestamp), "%Y_%d_%m__%H_%M_%S", &time);
  return string(timestamp);
}

// Tool Function 2 | Save the console output, even the program closed or stopped abruptly.
void save_file() {
  ofstream myfile;                                            // Create the file object.
  myfile.open("schedule_search_history."+timestamp(0)+".txt");
  myfile << string(8, '/') << timestamp(1) << "Pool schedule search history " << string(8, '\\') << endl;
  myfile << textToSave;
  myfile.close();
}

using PrintScheduleFunction = void (*)(const WeeklySchedule&); // Using a function pointer

void printWeeklySchedule(const WeeklySchedule& schedule) // This printWeeklySchedule function uses the printSchedule function to output the weekly schedule
{
    printSchedule(schedule);
}

PrintScheduleFunction printScheduleFunction = printWeeklySchedule;

// Tool Function 3 | Prints (or writes right into file) specific message based on the passed "_window".
void printMsg(int _window, string _text = "", int _w2 = -1) {  // 
  SetConsoleOutputCP(1251);
  SetConsoleCP(1251);

  switch (_window) {
  case 0: 
    printMsg(16, " Pool Schedule Accounting Application ");
    printMsg(17, "a");  printMsg(18, "Print the generalized schedule across all the tracks, instructors and groups."); 
    printMsg(17, "b");  printMsg(18, "Print the schedule for the particular track or group."); 
    printMsg(17, "c");  printMsg(18, "Find and print the schedule for the particular instructor or student."); 
    printMsg(17, "d");  printMsg(18, "Create/modify group. Add/remove student to/from the group."); break;
  case 4: 
    printMsg(16, " Groups and students management ");
    printMsg(17, "1");  printMsg(18, "Print list of all the students and groups."); 
    printMsg(17, "2");  printMsg(18, "Add the student and assign it to the group."); 
    printMsg(17, "3");  printMsg(18, "Remove the student from the group."); break;
  // case 7: printMsg(17, "3");  printMsg(18, "."); 
  case 12: 
    textToSave.append(buffer.str()); cout << buffer.str(); buffer.str(""); break;
  case 13: 
    cout << buffer.str(); buffer.str(""); break;
  case 14: 
    buffer << endl << string(110, '-') << endl << timestamp(1) << "A problem occured in the program :\n" << _text << endl << string(110, '-'); 
    textToSave.append(buffer.str()); buffer.str(""); break;
  case 15: 
    buffer << endl << timestamp(1) << string(6, '=') << setw(50) << left << _text << string(30, '=') << endl << string(110, '-') << endl; 
    textToSave.append(buffer.str()); buffer.str("");
    buffer << endl << string(30, '=') << setw(50) << left << _text << string(30, '=') << endl << string(110, '-') << endl; break;
  case 16: cout << string(30, '=') << setw(40) << left << _text << string(30, '=') << endl; break;
  case 17: cout << string(100, '-') << endl << setw(2) << left << "|" << setw(4) << _text; break;
  case 18: cout << setw(2) << left << "|" << setw(90) << _text << setw(2) << right << "|" << endl; break;
  case 19: cout << "\nYou have pressed the key \"" << _text <<"\". There is no such option in this menu. Please try again.\n\n"; break;
  case 20: 
    printMsg(17, "TAB"); printMsg(18, "Back to the previous menu."); 
    printMsg(17, "ESC"); printMsg(18, "Exit the program."); cout << string(100, '-'); break;
  default: break;
  } if (_w2 != -1) printMsg(_w2);
}

template <typename T0, typename T1, typename T2, typename T3, typename T4>
void print_row(std::stringstream& os, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, bool last)
{
  if (last) {
    os << "*" << string(21, '-') << "*" << string(20, '-') << "*" 
    << string(20, '-') << "*" << string(21, '-') << "*" << string(23, '-') << "*" << endl; return; 
  } os << "." << string(21, '-') << "|" << string(20, '-') << "|" << string(20, '-') << "|" 
    << string(21, '-')     << "|" << string(23, '-') << "." << endl << setw(2) << left 
    << "|" << std::setw(8) << " " << std::setw(12) << t0 
    << "|" << std::setw(6) << " " << std::setw(14) << t1 
    << "|" << std::setw(5) << " " << std::setw(15) << t2
    << "|" << std::setw(3) << " " << std::setw(18) << t3 
    << "|" << std::setw(9) << " " << std::setw(13) << t4 << setw(2) << right << "|" << "\n";
}

// Tool Function 4
void printSchedule(bool generalized, bool particularTrack, bool particularGroup, bool particularPerson) {
  system("CLS");

  if (generalized) printMsg(15, " Printing the generalized schedule. ");
  
  if (particularTrack) printMsg(15, " Printing the schedule for the particular track. ");

  if (particularGroup) printMsg(15, " Printing the schedule for the particular group. ");

  if (particularPerson) printMsg(15, " Printing the schedule for the particular person. ");
  printMsg(13);
}

// Tool Function 5 | If "tui" (terminal-user-interface) is false, then add/remove the student non-interactively.
void manageGroups(bool _tui, shared_ptr<Student> _student=nullptr, bool _add=true, bool _random=true, int _groupNum=0) {
  if (!_tui) {
    if (!_student) { 
      printMsg(14, "The \"_student\" object was passed with \"nullptr\" value to the \"" + string(__func__) + "\" function."); return;
    }

    bool assigned = false;
    for (auto group : allGroups) {
      if (group.get()->getAllStudents().size() == 10) continue;
      else if (!_random) {
        if (group.get()->getNumber() == _groupNum) { group.get()->addStudentToGroup(_student); assigned = true; break; } 
        else continue;
      } group.get()->addStudentToGroup(_student); assigned = true; break;
    }
    if (!assigned) 
      _random ? printMsg(14, "Unfortunately, all the groups are full.") : printMsg(14, "Unfortunately, the group \""+to_string(_groupNum) + "\"is full");

    // // For Debugging.
    // for (auto group : allGroups) {
    //   std::cout << "MANAGE GRPS | INLOOP2 | group.get()->getNumber() = " << group.get()->getNumber() << std::endl;
    //   for (auto _student : group.get()->getAllStudents()) {
    //     std::cout << "MANAGE GRPS | INLOOP2 | _student.get()->getLastName() = " << _student.get()->getLastName() << std::endl;
    //   }
    // }
    return;
  }

  char qt; 
  bool run = true, inOption = false;
  system("CLS");
  printMsg(4, "", 20); 
  while (run) {
    if (_kbhit()) {
      system("CLS");
      qt = _getch();
      switch (qt) {
        case(9):                       // decimal 9 - "TAB" as char (ASCII) | Go back to the previous menu.
          if (inOption) { inOption=false; printMsg(4, "", 20); } 
          else return; break; 
        case(27): std::exit(0); break; // decimal 27 - "ESCAPE" as char (ASCII) | Exit Program.

        case(49):                      // decimal 49 - "1" as char (ASCII) | Print all students,all groups.
          if (inOption) printMsg(19, string(1, qt), 20); 
          else {  
            printMsg(15, " Printing all students from all the groups "); buffer.str("");
            print_row(buffer, "group id" ,"last name", "parent name", "phone number", "paid lessons", 0);
            for (auto _group : allGroups) 
            { auto _groupp = _group.get();
              for (auto _student : _groupp->getAllStudents()) 
              { auto _studentt = _student.get();
                print_row(buffer, _groupp->getNumber(), _studentt->getLastName(), _studentt->getParentName(), 
                _studentt->getPhoneNumber(), _studentt->getPaidLessons(), 0);
              }
            } print_row(buffer, 0, "", "", 0, 0, 1);
            // .---------------------|--------------------|--------------------|---------------------|-----------------------.
            // |         group id    |      last name     |     parent name    |   phone number      |         paid lessons  |
            // .---------------------|--------------------|--------------------|---------------------|-----------------------.
            // |         1           |      Arseniuk      |     Nihoslav       |   +38(542)2578432   |         7             |
            // .---------------------|--------------------|--------------------|---------------------|-----------------------.
            // |         1           |      Pastukh       |     Pershyk        |   +38(472)7682276   |         6             |

            printMsg(12);
            inOption = true; 
          } break; 

        case(50):                      // decimal 50 - "2" as char (ASCII) | Print all students,all groups.
          if (inOption) printMsg(19, string(1, qt), 20); 
          else {
            printMsg(15, " Enter the details for the new student: ", 13);
            inOption = true;
          } break;
        
        default: 
          printMsg(19, string(1, qt), 20); 
          break;
      }
    }
  }

  return;
}

int main() {
  std::atexit(save_file);
  SetConsoleOutputCP(1251);
  SetConsoleCP(1251);
  
  // Generating the 3 "Lane" objects and 4 "Group" objects.
  for (int i=1; i<=3; i++) {  
    allLanes.push_back(std::make_shared<Lane>(i));                      // Create "Lane" objects.
    allGroups.push_back(std::make_shared<Group>(i));                    // Create "Group" objects.
  } allGroups.push_back(std::make_shared<Group>(4));

  // Generating the 8 "Instructor" objects.
  unique_ptr<string>::pointer tmp1 = new string[5]{"Krutiy","Stetsyk","Yakhno","Dovzhanskyi","Shira"};
  unique_ptr<string>::pointer tmp2 = new string[5]{"+38(063)8651819","+38(096)5631589","+38(095)7834967","+38(067)6145363","+38(063)3255133"}, tmp3;
  unique_ptr<double>::pointer tmp4 = new double[5]{300.0,300.0,350.0,300.0,350.0}; unique_ptr<int>::pointer tmp5;
  for (int i=0; i<=4; i++) allInstructors.push_back(std::make_shared<Instructor>(tmp1[i], tmp2[i], tmp4[i]));
  allInstructors.push_back(std::make_shared<Instructor>("Kolchak", "+38(067)1345840", 300.0));
  allInstructors.push_back(std::make_shared<Instructor>("Panchyshyn", "+38(067)7462681", 300.0));
  allInstructors.push_back(std::make_shared<Instructor>("Kinash", "+38(099)4884404", 400.0));

  // Generating the 5 "Student" objects. Assigning them all to the "Group" with the "number" field = 3.
  tmp1 = new string[5]{"Tichenko","Chujkevych","Pidoplichko","Ovrah","Hrynishak"}, tmp3 = new string[5]{"Sharl","Ustym","Emil","Jonas","Fedir"};
  tmp2 = new string[5]{"+38(730)7621483","+380(884)8890726","+380(248)8717477","+380(668)4952298","+380(404)2303088"}; tmp5 = new int[5]{4,10,9,8,3};
  for (int i=0; i<=4; i++) manageGroups(0, std::make_shared<Student>(tmp1[i],tmp3[i],tmp2[i], tmp5[i]),1,0,3);

  // For ref: void manageGroups(bool _tui, shared_ptr<Student> _student=nullptr, bool _add=true, bool _random=true, int _groupNum=0)

  // Generating another 5 "Student" objects. Assigning them to the groups, randomly.
  tmp1 = new string[5]{"Arseniuk","Pastukh","Nechytailo","Polozhii","Holovinskyi"}, tmp3 = new string[5]{"Nihoslav","Pershyk","Chestyslav","Velet","Klym"};
  tmp2 = new string[5]{"+38(542)2578432","+38(472)7682276","+38(827)3367671","+38(352)3966987","+38(797)4122186"}; tmp5 = new int[5]{7,6,6,5,7};
  for (int i=0; i<=4; i++) manageGroups(0, std::make_shared<Student>(tmp1[i],tmp3[i],tmp2[i], tmp5[i]),1,1);

  manageGroups(0, std::make_shared<Student>("Turkevych","Avrelii","+380(118)7284874", 4),1,0,1);
  manageGroups(0, std::make_shared<Student>("Kompanec","Lyubodar ","+380(783)5566764", 2),1,0,1);

  manageGroups(0, nullptr,1,0,1); // Generating the "Student" object as "nullptr" and passing it to this same function.

  WeeklySchedule weeklySchedule; // Creating a schedule

  weeklySchedule.days.push_back({ "Monday", {{"10:00-10:45", 1, "Instructor1", 1}, {"11:00-11:45", 1, "Instructor2", 1}} });
  weeklySchedule.days.push_back({ "Wednesday", {{"10:00-10:45", 1, "Instructor2", 1}} });
  weeklySchedule.days.push_back({ "Friday", {{"10:00-10:45", 1, "Instructor3", 1}} });

  // // For debugging:
  // for (auto group : allGroups) {
  //     std::cout << "MAIN | INLOOP1 | group.get()->getNumber() = " << group.get()->getNumber() << std::endl;
  //     for (auto _student : group.get()->getAllStudents()) {
  //       std::cout << "MAIN | INLOOP1 | _student.get()->getLastName() = " << _student.get()->getLastName() << std::endl;
  //   }
  // }

  char qt; 
  bool run = true, inOption = false;

  // system("CLS");
  printMsg(0, "", 20); 
  while (run) {
    if (_kbhit()) {
      system("CLS");
      qt = _getch();
      switch (qt) {  // decimal 9 - "TAB" as char (ASCII) | Go back to the main menu.
        case(9): printMsg(0, "", 20); inOption = false; break; 
        case(27): return 0; break; // decimal 27 - "ESCAPE" as char (ASCII) | Exit Program.
        case(97):                  // decimal 97 - "a" as char (ASCII) | Print generalized schedule.
          if (inOption) printMsg(19, string(1, qt), 20); 
          else { printSchedule(1,0,0,0); printMsg(20); inOption = true; } break; 
        case(98): // decimal 98 - "b" as char (ASCII) | Print the schedule for the particular track or group. 
          if (inOption) printMsg(19, string(1, qt), 20); 
          else { printSchedule(0,1,1,0); inOption = true; } break; 
        case(99): // decimal 99 - "c" as char (ASCII) | Print the schedule for the particular instructor or student.
          if (inOption) printMsg(19, string(1, qt), 20);
          else { printSchedule(0, 0, 0, 1); inOption = true; } break; 
        case(100): // decimal 100 - "d" as char (ASCII) | Modify/create groups. Add/remove students to/from the group.
          if (inOption) printMsg(19, string(1, qt), 20); 
          else { manageGroups(1); printMsg(0, "", 20); }
          break;
        default: 
          printMsg(19, string(1, qt), 20); 
          break;
      }
    }
  } run = true;
  return 0;
}
