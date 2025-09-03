// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO(student)

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin"
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double reading,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO(student)

    // TODO(student): declare and initialize variables
    double exam = 0;
    double hw;
    double lw;
    double final_exam;
    double reading;
    double engagement = 15;
    char final_letter_grade;
    int exam_num = 0;
    int hw_num = 0;
    int lw_num = 0;
    int reading_num = 0;
    double exam1 = 0;
    double exam2 = 0;
    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam") {
            // TODO(student): process midterm exam score
            if (exam_num == 0){
                exam = score;
            }
            else if (exam_num == 1){
                exam1 = score;
            }
            else if (exam_num == 2){
                exam2 = score;
            }
            exam_num += 1;

        } else if (category == "final-exam") {
            // TODO(student): process final exam score
            final_exam = score;
        } else if (category == "hw") {
            // TODO(student): process hw score
            hw += score;
            hw_num += 1;
        } else if (category == "lw") {
            // TODO(student): process lw score
            if (score >= 50){
                lw += 100;}
            else{
                lw += 0;
            }
            lw_num += 1;
        } else if (category == "reading") {
            // TODO(student): process reading score
            reading += score;
            reading_num += 1;
        } else if (category == "engagement") {
            // TODO(student): process engagement score
            engagement += score;
        } else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

    double hw_average = 0;
    double lw_average = 0;
    double exam_average = 0;
    double all_exam = 0;
    // TODO(student): compute component averages and assign to the above variables
    if (exam >= exam1 && exam2 >= exam1){
        all_exam = exam + exam2;
    }
    else if (exam1 >= exam && exam2 >= exam){
        all_exam = exam1 + exam2;
    }
    else if (exam >= exam2 && exam1 >= exam2){
        all_exam = exam + exam1;
    }
    exam_average = final_exam * .4 + (all_exam / 2) * .6;
    //
    if (hw != 0){
        hw_average = hw / hw_num;
        if (hw_average > 100){
            hw_average = 100;
        }
    //
    }
    if (lw != 0){
        lw_average = lw / lw_num;
    }
    else {
        lw_average = lw;
    }
    //
    if (reading !=0){
        reading = reading / reading_num * 100;
        if (100 <= reading && reading >= 85){
        reading = 100;
        }
        else{
        reading += 15;
    }}
    else if (reading == 0) {
        reading = 15;
    }
    //
    if (100 < engagement && engagement >= 85){
        engagement = 100;
    }
    // TODO(student): compute weighted total of components
    double weighted_total = 0.2 * hw_average + 0.1 * lw_average + exam_average * .6+ reading * 0.05 + engagement * 0.05;

    // TODO(student): compute final letter grade
    if (weighted_total >= 89.5){
        final_letter_grade = 'A';
    }else if (weighted_total >= 79.5){
        final_letter_grade = 'B';
    }else if (weighted_total >= 69.5){
        final_letter_grade = 'C';
    }else if (weighted_total >= 59.5){
        final_letter_grade = 'D';
    }else{
        final_letter_grade = 'F';
    }
    // Do not modify print_results since this will not help
    print_results(
        exam_average, hw_average, lw_average, reading, engagement,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them
// Even minor changes might cause you to fail test cases for the wrong reasons

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | reading | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double reading,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "        exam average: " << exam_average << endl;
    cout << "          hw average: " << hw_average << endl;
    cout << "          lw average: " << lw_average << endl;
    cout << "     reading average: " << reading << endl;
    cout << "  engagement average: " << engagement << endl;
    cout << "  -------------------" << endl;

    cout << "      weighted total: " << weighted_total << endl;

    cout << "  final letter grade: " << final_letter_grade << endl;
}
