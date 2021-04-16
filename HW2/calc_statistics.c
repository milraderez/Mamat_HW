#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

int median_find(int* grade_histogram, int student_count);

int main(int argc, char* argv[]) {
	FILE *fd_course, *fd_grade;
	int grade_histogram[101] = { 0 }, garbage = 0;
	int new_student = 0 , student_count = 0, grade_sum = 0;
	int max_grade = 0, min_grade = 101, pass_count = 0;
	bool still_have_students = true;
	fd_course = fopen("course_statistics.txt", "w");
	fd_grade = fopen("grades.txt", "r");
	// skips the first line of headlines
	fscanf(fd_grade, "%*[^\n]\n"); 
	// garbage is meant to read the ID column
	while (still_have_students == true) {
		if (fscanf(fd_grade, "%d %d", &garbage, &new_student) == EOF) {
			still_have_students = false;
		}
		if (still_have_students == false || new_student > 100 ||
			                                                new_student < 1) {
			continue;
		}

		grade_histogram[new_student]++;
		student_count++;
		grade_sum += new_student;

		if (new_student > max_grade) {
			max_grade = new_student;
		}
		else if (new_student < min_grade) {
			min_grade = new_student;
		}
		if (new_student >= 55) {
			pass_count++;
		}
	}
	//creating a copy to avoid median_find from changing the histogram 
	int histogram_copy[101] = { 0 };
	for (int i = 0; i < 101; i++) {
		histogram_copy[i] = grade_histogram[i];
	}

	float grade_average = ((float)grade_sum / (float)student_count);
	float pass_percentage = ((float)pass_count / (float)student_count) * 100;
	int median = median_find(histogram_copy, student_count);

	//passing all the data to grades.txt
	fprintf(fd_course, "num of students = %d\n"
		"avg = %.3f\n"
		"the median is - %d\n"
		"max grade = %d, min grade = %d\n"
		"pass rate = %.2f%%\n",
		student_count, grade_average, median, max_grade, min_grade,
		pass_percentage);
	for (int i = 1; i < 101; i++) {
        //every first number of a row, to not print extra space
		if (i % 10 == 1) {
			fprintf(fd_course, "%d", grade_histogram[i]);
		}
		else {
			fprintf(fd_course, " %d", grade_histogram[i]);
			//every last number of a row, to keep the histogram shape
			if (i % 10 == 0 && i < 100) {
				fprintf(fd_course, "\n");
			}
		}
	}
	fclose(fd_course);
	fclose(fd_grade);
	return 0;
}

//@brief orders all the students in one ordered array in return the median
//@param grade_histogram contains all the students grades in the file
//@param student_count number of students in current file
//@note student_count is assumed to be smaller than int
int median_find(int* grade_histogram, int student_count) {
	int *all_students = malloc(sizeof(int) * student_count);
	int next_free_location = 0;
	for (int i = 1; i < 101; i++) {
		while (grade_histogram[i] > 0) {
			all_students[next_free_location] = i;
			next_free_location++;
			grade_histogram[i]--;
		}
	}
	//median formula
	return all_students[ (student_count + 1) / 2 ];
}
