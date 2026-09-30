# Student Grade Calculator (C++)

This is a C++ program I wrote to manage and calculate final grades for a group of students. 

It basically saves you from doing the math manually and prints everything neatly organized in a console table. The project is designed to be modular to keep things clean and apply Object-Oriented Programming practices, like the Rule of Three.

## What it does

- Flexible input: You can either type the student data manually in the console or, to save time, load a file and let the program read everything at once.

- Grade calculation: It calculates the final score based on the homework (HW) and the final exam using the following formula: 
  `Final Points = 0.4 * (Average of HW / Median of HW) + 0.6 * Exam`
  You can choose whether the program should use the average or the median of the homework grades for the calculation.

- Sorting and formatting: Once it processes all the data, it sorts the students alphabetically by their first and last names, and outputs a clean, formatted table with the results.

## Text file structure

If you test the file reading option, make sure to place your .txt file inside a files/ folder next to the code. 

The program automatically ignores the first line (the header) and assumes that the last number in each row is the exam grade, while all the previous numbers are the homework grades. It should look something like this:

Name        Surname    HW1   HW2   HW3   HW4   HW5   Exam
Ana         Garcia       8     9    10     6    10      9
Carlos      Lopez        7    10     8     5     4      6
