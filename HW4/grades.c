#include "grades.h"
#include <stdlib.h>
#include <stdio.h>
#include "linked-list.h"
#include <string.h>

#define FAIL -1
#define SUCCESS 0
#define MAX_GRADE 100

typedef struct grades {
	struct list *students_list;
}grades;

typedef struct student {
    char  *student_name;
	int    student_id;
	struct list *courses;
}student;

typedef struct course {
	char *course_name;
	int  student_grade;
}course;

static int element_clone_student_t(void *element, void **output);
static int element_clone_course_t(void *element, void **output);
static void element_destroy_student_t(void *element);
static void element_destroy_course_t(void *element);
static struct iterator *find_id(struct grades *grades, int id);
static int find_course(student *student, const char *course_name);
static student* invalid_check_fetch_student(grades* grades,int id);
static void print_student_data(grades *grades,student *temp_student);


struct grades *grades_init() {
	grades *grades_p = (grades*)malloc(sizeof(grades));
	if (grades_p == NULL) {
		free(grades_p);
		return NULL;
	}
	grades_p->students_list = list_init(element_clone_student_t,element_destroy_student_t);
	if (grades_p->students_list == NULL) {
		free(grades_p);
		return NULL;
	}
	return grades_p;
}

void grades_destroy(grades *grades) {
	list_destroy(grades->students_list);
	free(grades);
}

int grades_add_student(grades *grades, const char *name, int id) {
	if ((find_id(grades, id) != NULL) || (grades == NULL)) {
		return FAIL;
	}
	student *new_student = (student*)malloc(sizeof(student));
	if (new_student == NULL) {
		return FAIL;
	}
	new_student->student_name =(char*)malloc(sizeof(char) * (strlen(name)+1));
	if ((new_student->student_name) == NULL) {
		free(new_student);
		return FAIL;
	}
	strcpy(new_student->student_name, name);
	new_student->student_id = id;
	new_student->courses = list_init(element_clone_course_t,element_destroy_course_t);
	if ((new_student->courses)== NULL) {
		free(new_student->student_name);
		free(new_student);
	}
	if (list_push_back(grades->students_list, new_student) != SUCCESS) {
		free(new_student->student_name);
		list_destroy(new_student->courses);
		free(new_student);
		return FAIL;
	}
	//list_destroy(new_student->courses);
	//free(new_student->student_name);
	//free(new_student);
	return SUCCESS;
	}

	int grades_add_grade(grades *grades, const char *name,
		                 int id, int grade) {
        student *temp_student = invalid_check_fetch_student(grades, id);
		if (temp_student == NULL) {
			return FAIL;
		}
		if((find_course(temp_student, name) != FAIL) ||
		              (grade < 0) || (grade > MAX_GRADE)) {
			return FAIL;
		}
		course *new_course = (course*)malloc(sizeof(course));
		if (new_course == NULL) {
			return FAIL;
		}
		new_course->course_name =(char*)malloc(sizeof(char) *(strlen(name)+1));
		if ((new_course->course_name) == NULL) {
			free(new_course);
			return FAIL;
		}
		strcpy(new_course->course_name, name);
		new_course->student_grade = grade;
		if (list_push_back(temp_student->courses, new_course) != SUCCESS) {
			free(new_course->course_name);
			free(new_course);
			return FAIL;
		}
		free(new_course->course_name);
		free(new_course);
		return SUCCESS;
}

	float grades_calc_avg(grades *grades, int id, char **out) {
		student* temp_student = invalid_check_fetch_student(grades, id);
		if (temp_student == NULL) {
			out = NULL;
			return FAIL;
		}

		if (temp_student->courses == NULL) {
			return 0;
		}
		int grade_counter = 0, courses_counter = 0;
		float average = 0;
		struct iterator *current = list_begin(temp_student->courses);
		course *temp_course;
		while (current) {
			temp_course = list_get(current);
			grade_counter += temp_course->student_grade;
			courses_counter++;
			current = list_next(current);
		}
		if(courses_counter > 0){
		average = (float)grade_counter / (float)courses_counter;
        }
		//need to put the student's name in out 
		char *str = (char*)malloc(sizeof(char) *
		                          strlen((temp_student->student_name) + 1));
		if (str == NULL) {
			return FAIL;
		}
		strcpy(str, temp_student->student_name);
		*out = str;
		return average;
		}


int grades_print_student(grades *grades, int id) {
	student* temp_student = invalid_check_fetch_student(grades, id);
	if (temp_student == NULL) {
		return FAIL;
	}
	print_student_data(grades,temp_student);
	return SUCCESS;
}

int grades_print_all(grades *grades) {
	if (grades == NULL) {
		return FAIL;
	}
	struct iterator *current_student = list_begin(grades->students_list);
	student *temp_student = list_get(current_student);
	if ((temp_student == NULL) && (list_size(grades->students_list) > 0)){
		return FAIL;
	}
	while (current_student) {
	print_student_data(grades, temp_student);
	current_student = list_next(current_student);
	temp_student = list_get(current_student);
		if(temp_student == NULL){
			break;
		}
	}
	return SUCCESS;
}


static int element_clone_student_t(void *element, void **output) {
	if (element == NULL) {
		return FAIL;
	}
	student *original = (student*)element;
	student *clone = (student*)malloc(sizeof(student));
	if (clone == NULL) {
		return FAIL;
	}
	clone->student_name = (char*)malloc(sizeof(char) * strlen(original->student_name) + 1);
	if (clone->student_name == NULL) {
		free((char*)clone->student_name);
		free(clone);
		return FAIL;
	}
	strcpy(clone->student_name, original->student_name);
	clone->student_id = original->student_id;
	clone->courses = original->courses;
	*output = clone;
	return SUCCESS;
}

static int element_clone_course_t(void *element, void **output) {
	if (element == NULL) {
		return FAIL;
	}
	course *clone = (course*)malloc(sizeof(course));
	course *original = (course*)element;
	if (clone == NULL) {
		return FAIL;
	}
	clone->course_name = (char*)malloc(sizeof(char)* (strlen(original->course_name) + 1));
	if (clone->course_name == NULL) {
		free(clone);
		return FAIL;
	}
	strcpy(clone->course_name, original->course_name);
	clone->student_grade = original->student_grade;
	*output = clone;
	return SUCCESS;
}


static void element_destroy_student_t(void *element) {
	list_destroy(((student*)element) -> courses);
	free(((char*)(((student*)(element))->student_name)));
	free((student*)element);
	return;
}

static void element_destroy_course_t(void* element) {
	free(((course*)element)->course_name);
	free((course*)element);
	return;
}

static struct iterator *find_id(grades* grades, int id) {
	struct iterator *current = list_begin(grades->students_list);
	student *temp_student;
	while (current) {
		temp_student = list_get(current);
		if (temp_student->student_id == id) {
			return current;
		}
		else {
			current = list_next(current);
		}
	}
	return NULL;
}

static int find_course(student *student, const char *course_name) {
	struct iterator *current = list_begin(student->courses);
	course *temp_course;
	while (current) {
		temp_course = list_get(current);
		if (strcmp(temp_course->course_name,course_name) == SUCCESS) {
			return SUCCESS;
		}
		else {
			current = list_next(current);
		}
	}
	return FAIL;
}

static student* invalid_check_fetch_student(grades *grades,int id) {
	if (grades == NULL) {
		return NULL;
	}
	struct iterator* current_student = find_id(grades, id);
	student* temp_student;
	temp_student = list_get(current_student);
	if (temp_student == NULL) {
		return NULL;
	}
	return temp_student;
}
static void print_student_data(grades *grades,student *temp_student){
	struct iterator *current = list_begin(temp_student->courses);
	course *temp_course;
	printf("%s %d:", temp_student->student_name, temp_student->student_id);
	while (current) {
		temp_course = list_get(current);
		if(list_next(current) != NULL){
		printf(" %s %d,", temp_course->course_name, temp_course->student_grade);
	    }
	    else {
	    printf(" %s %d", temp_course->course_name, temp_course->student_grade);	
	    }
		current = list_next(current);
	}
	printf("\n");
	return;
}