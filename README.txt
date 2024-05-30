Learn Words App is a simple and convenient application
for the Linux users who want to learn english/swedish words.
This app mimics old word cards, which people usually use
when they learn a foreign language.
One thing what make this app convenient is a fact,
that user is allowed to add(fill) application's vocabulary
with words he/she needs, instead of using inline vocabulary
with words what they actually don't need.
This release consists of only two tables in data base:
english and swedish vocabularies.

HOW TO WORK WITH IT.
In the folder "build-Learn_Words_App_0_0_1-Release" 
run Learn_Words_App_0_0_1 and you will see the main window
of the app. On the rigth you may see sidebar with icons
what represent features:

Start -> simply starts the lesson (english vocabulary by default).
The lesson widget appears and user is available to start
learning words. Widget prompts to fill an edit line with
the right answer and press button "Next" via mouse or
simply use "CTRL+ENTER" from the keyboard. There are three
additional buttons:
"Stats" -> shows to user current statistics;
"Restart" -> restarts lesson;
"Finish" -> closes the app;
When the lesson is over it means that user passed all words(tasks)
and overall stats will show up.

Finish -> does nothing, just closes the app.

Stats -> shows stats from the previous lessons.
With graphical views it's easy to understand progress/regress.
User is alowed to check daily stats, last week/month stats.
Moreover, option "Overall stats" displays linear chart
using all saved stats data to show overall results.

Change mode -> changing language for the learning session.
Instead of learning english user can switch mode to the 
swedish and work with it as he/she does it with english vocabulary.

Add word -> Attention! This is the first feature user has to apply.
Because the vocabularies are empty, user must add words into it
by himself/herself. It is very easy, just select what database 
you are gonna to fill and add words using edit lines and pressing
button "Add". In the right buttom corner app shows total amount of words
in the data base, separately english and swedish.

Delete word -> as you could guessed, this tool deletes words.
It works directly as "Add word", but it deletes instead of adding.
User can switch deleting modes depending of his/her goals.

Set word -> if user added some word with an error or unwanted symbol
and he/she desires to correct it, "Set word" is the saviour.
It works in the familliar way as the previous features. Widget has a
user friendly interface and it doesn't need a deep explanation here.

For this application I use C++, QT6 and SQLite3.

This release marked as 0.0.1.
It means that I will upgrade it time to time.
If you have any questions you can send me an email using
this adress: sautenkoandrey@gmail.com
