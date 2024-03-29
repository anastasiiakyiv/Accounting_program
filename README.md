# Програма для автоматизації обліку роботи басейна.

**Завдання**: написати програму для автоматизації обліку роботу басейна.
У басейна є 3 плавальні доріжки. На кожній з доріжок в окремий момент часу може
працювати тільки один тренер з певною групою. Кількість осіб в групі обмежена. 
Для простоти припустимо числом 10.
Потрібно розробити програму, яка б дозволяла формувати розклад роботи тренера.
Припустимо, що заклад працює з 9:00 до 21:00 за київським часом, кожного дня, крім неділі. 
Але окремий тренер може працювати якусь певну кількість годин і днів з цього часу. 
Потім його може змінити інший тренер. Потрібно створити список тренерів з
прізвищами, номерами телефонів, ставками погодинної оплати і розкладом занять. 

В розкладі занять має бути вказано номер доріжки, час проведення занять і група. 
Має бути можливість формування зведеного розкладу по всіх доріжках, тренерах, групах.
Має бути можливість створення і вилучення нових груп і додавання й вилучення
дітей, які займаються плаванням. В кожного учасника групи має бути ім’я, ім’я одного
з батьків, контактний номер телефона, обсяг проплачених коштів і прив’язка до
певного списку занять. Потрібно розробити можливість пошуку учасника за
контактним номером телефона і вивід на екран розкладу занять на тиждень для нього.

Для виконання завдання можете використовувати будь-які структури даних. 
Але результати треба буде зберігати у файл до наступного запуска програми.

У вас мають бути наступні класи і об’єкти:
1) Доріжки мають номер і список занять.
2) Заняття характеризується часом, номером доріжки, тренером і групою.
3) Тренер має прізвище, номер телефону, погодинна ставка і пов’язаний із списком
занять.
4) Група має номер і список учнів, пов’язана із заняттями.
5) Учень має прізвище, прізвище, ім’я одного з батьків, контактний номер телефона і
кількість проплачених занять.

**Реалізація**: програма містить чотири опції у головному меню:
1) `a/ Print the schedule for all the tracks, instructors and groups.` - Опція виведення на екран загального розкладу всіх доріжок, інструкторів та груп.
```
15 Jan 2024 17:37:05 | ===== Generalized weekly schedule. ==================
-----------------------------------------------------------------------------
| Time           | Lane number   | Instructor         | Group number        |
-----------------------------------------------------------------------------
  Monday                                                                    |
-----------------------------------------------------------------------------
| 09:00-09:45    | 1             | Yakhno             | 1                   |
| 10:15-11:00    | 1             | Yakhno             | 1                   |
| 10:15-11:00    | 2             | Dovzhanskyi        | 3                   |
| 11:30-12:15    | 1             | Yakhno             | 4                   |
| 11:30-12:15    | 2             | Dovzhanskyi        | 3                   |
```
2) `b/ Print the schedule for the particular track or group.` - Опція виведення на екран розкладу для вибраної доріжки або групи.
```
15 Jan 2024 17:37:09 | ===== Weekly schedule for group 1. ===================
-----------------------------------------------------------------------------
Day             |Time           |Lane Number         |Instructor            |
-----------------------------------------------------------------------------
Monday          |09:00-09:45    |1                   |Yakhno                |
Monday          |10:15-11:00    |1                   |Yakhno                |
Wednesday       |10:15-11:00    |1                   |Panchyshyn            |
Wednesday       |11:30-12:15    |1                   |Panchyshyn            |
Friday          |12:45-13:30    |3                   |Kinash                |
```
3) `c/ Print the schedule for the particular instructor or student.` - Опція виведення на екран розкладу для інструктора чи студента.
```
15 Jan 2024 17:37:21 | ==== Weekly schedule for student with phone "+38(078)3556676".
-----------------------------------------------------------------------------
Day             |Time            |Lane           |Group      |Instructor    |
-----------------------------------------------------------------------------
Tuesday         |16:30-17:15     |3              |2          |Krutiy        |
Tuesday         |17:45-18:30     |3              |2          |Krutiy        |
Thursday        |16:30-17:15     |3              |2          |Krutiy        |
Thursday        |17:45-18:30     |3              |2          |Krutiy        |
Saturday        |11:30-12:15     |2              |2          |Shira         |
Saturday        |12:45-13:30     |2              |2          |Shira         |
```

4) `d/ Create/modify group. Add/remove student to/from the group.` - Опція внесення змін до груп студентів.

Клавіша `TAB` повертає користувача до попереднього меню.
Клавіша `ESC` закриває програму.

Програма містить головний файл **Main.cpp** та заголовкові файли, що містять основні класи: **Lesson.h, Group.h, Instructor.h, Lane.h та Student.h**.

Файл **Lesson.h** містить наступні функції виведення розкладу:
1) Функція **printSchedule** виводить розклад у форматі таблиці. 
* Спочатку виводиться заголовок з використанням функції `timestamp` та розділюючих ліній.
* Далі виводяться заголовки стовпців для часу, номеру доріжки, інструктора та номеру групи.
* Потім виводяться дані для кожного дня розкладу, включаючи час, номер доріжки, ім'я інструктора та номер групи для кожного уроку у цьому дні.
2) Функція **printScheduleForGroupOrLane** призначена для виведення часткового тижневого розкладу для певної групи або доріжки (в залежності від опції).
* Функція спочатку визначає, чи вказано правильну опцію (`g` або `l`).
* Формується заголовок розкладу, де вказується опція, номер групи чи доріжки та розділюючі лінії.
* Для кожного дня у тижні та для кожного уроку у цьому дні функція перевіряє, чи відповідає номер групи чи доріжки (`groupOrLaneNumber`) номеру групи чи доріжки у розкладі. Якщо умова виконується, виводяться дані про урок (день, час, номер доріжки або групи, ім'я інструктора).
3) Функція **printScheduleForPerson** призначена для виведення часткового тижневого розкладу для конкретної особи (студента або інструктора).
* Функція перевіряє, чи вказано правильну опцію (`s` або `i`).
* Формується заголовок розкладу в залежності від опції та ідентифікатора.
* Для кожного дня у тижні та для кожного уроку у цьому дні функція перевіряє, чи відповідає ідентифікатор (телефонний номер чи прізвище) особі, за якою проводиться пошук. Якщо умова виконується, виводяться дані про урок (день, час, номер доріжки, номер групи та ім'я інструктора).

Об'єкти створюються в головній функції **main**. Вона також містить головний цикл взаємодії з користувачем у текстовому інтерфейсі за допомогою клавіш на клавіатурі.
* Визначається змінна `qt` для зберігання значення клавіші, яку натискав користувач, та змінна `inOption`, яка вказує, чи користувач вже вибрав опцію.
* Функція `_kbhit()` перевіряє, чи була натиснута клавіша на клавіатурі.
* Функція `_getch()` отримує код ASCII клавіші, яку ввів користувач.
* Конструкція switch обробляє різні значення `qt`.

Функція **timestamp** генерує часові мітки у форматі дати та часу та повертає відформатований рядок. Вона приймає параметр format, який вказує, у якому форматі потрібно повертати час.

Функція **save_file** призначена для збереження вмісту консолі (включаючи виведений текст) у файл. Вона відкриває файл з унікальною назвою та записує вміст змінної `textToSave` у цей файл. Важливо, що запис у файл відбувається тільки після (в момент) виходу з програми.

Функція **printMsg** використовується для виведення повідомлень на консоль та/або запису їх у змінну `buffer`.

Функція **manageGroups** служить для управління групами та студентами, надаючи можливість додавати студентів до груп. Важливо те, що після будь-якої із змін у складі груп (додавання нового студента, модифікація інформації про студента, додавання нової групи) буде створений backup складу групи (тобто опції d - 1). Таким чином зміни завжди будуть відслідковуватися. 
