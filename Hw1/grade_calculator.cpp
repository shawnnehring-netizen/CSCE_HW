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
    double exam;
    double hw;
    double lw;
    double final_exam;
    double reading;
    double engagement;
    char final_letter_grade;
    int exam_num = 0;
    int hw_num = 0;
    int lw_num = 0;
    int reading_num = 0;
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
            exam += score;
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
            lw += score;
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
    double mid_exam = 0;
    // TODO(student): compute component averages and assign to the above variables
    mid_exam = exam / exam_num;
    exam_average = final_exam * .4 + mid_exam * .6;
    hw_average = hw / hw_num;
    lw_average = lw / lw_num;
    reading = reading / reading_num * 100;
    // TODO(student): compute weighted total of components
    double weighted_total = 0.2 * hw_average + 0.1 * lw_average + exam_average * .5+ reading * 0.05 + engagement * 0.05;

    // TODO(student): compute final letter grade
    cout << "here" << (weighted_total >= 60.0) << endl;
    if (weighted_total >= 90.0){
        final_letter_grade = 'A';
    }else if (weighted_total >= 80.0){
        final_letter_grade = 'B';
    }else if (weighted_total >= 70.0){
        final_letter_grade = 'C';
    }else if (weighted_total >= 60.0){
        final_letter_grade = 'D';
    }else if (weighted_total >= 0.0){
        final_letter_grade = 'F';
    }
    cout << "here" << final_letter_grade << endl;
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
