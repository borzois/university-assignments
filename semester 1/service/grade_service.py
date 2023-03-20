from domain.entities import Student, Subject, Grade
from domain.validators import StudentValidator, SubjectValidator, GradeValidator
from repository.repo import MemoryStudentRepo, MemorySubjectRepo, MemoryGradeRepo
import unittest


class GradeService:
    def __init__(self, grade_repo, student_repo, subject_repo, validator):
        """Initializes the grade service

        Args:
            grade_repo (object): Grade repository
            student_repo (object): Student repository
            subject_repo (object): Subject repository
        """
        self.__grade_repo = grade_repo
        self.__student_repo = student_repo
        self.__subject_repo = subject_repo
        self.__validator = validator

    def assign(self, student_id, subject_id, grade):
        """Assigns grade to a student for a given subject

        Args:
            student_id (int): Student id
            subject_id (int): Subject id
            grade (int): Grade
        """
        try:
            new_student = self.__student_repo.search(student_id)
            new_subject = self.__subject_repo.search(subject_id)
            new_grade = Grade(new_student, new_subject, grade)
            self.__validator.validate(new_grade)
            self.__grade_repo.assign(new_grade)
        except ValueError as e:
            print(e)

    def get_all(self):
        """Returns list of grades

        Returns:
            list: List of grades
        """
        return self.__grade_repo.get_all()

    def sort_by_name(self, subject_id):
        """Sorts students by name

        Args:
            subject_id (int): ID of the subject

        Returns:
            list: sorted list
        """
        grades = self.__grade_repo.get_all()
        subject_grades = []
        for grade in grades:
            if grade.get_sub_id() == subject_id:
                subject_grades.append(grade)
        new_subject_grades = self.new_sorted(subject_grades, key = lambda grade : grade.get_st_name(), mode="b")
        return new_subject_grades

    def sort_by_grade(self, subject_id):
        """Sorts students by grade

        Args:
            subject_id (int): ID of the subject

        Returns:
            list: sorted list
        """
        grades = self.__grade_repo.get_all()
        subject_grades = []
        for grade in grades:
            if grade.get_sub_id() == subject_id:
                subject_grades.append(grade)
        new_subject_grades = self.new_sorted(subject_grades, reverse = True, mode="b", cmp = self.new_cmp)
        return new_subject_grades

    def student_average_grade(self):
        """Gets the average grade for all students

        Returns:
            list: List of student id's and average grades ([student_id, average])
        """
        grades = self.__grade_repo.get_all()
        average_grades = [] # [student_id, sum, count]
        for grade in grades: # for each grade
            exists = False
            for average in average_grades: 
                if grade.get_st_id() == average[0]: # check if the student exists in the average list
                    average[1] += grade.get_grade()  # if true, add the new grade and count it
                    average[2] += 1
                    exists = True
            if exists == False:
                new_average = [grade.get_st_id(), grade.get_grade(), 1] # if not, initialize the student's average
                average_grades.append(new_average)
        for grade in average_grades:
            grade[1] = grade[1] / grade[2] # calculate the average for each student
        new_average_grades = self.new_sorted(average_grades, key = lambda grade : grade[1], reverse = True, mode="s")
        return new_average_grades

    def sort_subjects_by_grade_no(self):
        """Sorts subjects by number of grades

        Returns:
            list: List of subject ids and number of grades
        """
        grades = self.__grade_repo.get_all()
        counter = [] 
        for grade in grades: 
            exists = False
            for subject in counter: 
                if grade.get_sub_id() == subject[0]:
                    subject[1] += 1
                    exists = True
            if exists == False:
                new_subject = [grade.get_sub_id(), 1] 
                counter.append(new_subject)
        new_counter = self.new_sorted(counter, key = lambda grade : grade[1], reverse = True, mode="s")
        return new_counter

    def default_cmp(x, y, key):
        """Default compare function

        Args:
            x (int): x
            y (int): y
            key (function): key function to use for comparison

        Returns:
            int: 1 if the first number is greater, -1 if the first number is less than the second, 0 otherwise
        """
        if key(x) > key(y): 
            return 1
        elif key(x) < key(y): 
            return -1
        else: 
            return 0

    def new_cmp(self, grade1, grade2, key):
        """new comparison function

        Args:
            grade1 (object): grade object
            grade2 (object): grade object
            key (function): key function

        Returns:
            int: same as the default compare
        """
        grade1_key = key(grade1) # egale daca key = lambda x : x, altfel functia
        grade2_key = key(grade2)
        
        if grade1_key.get_grade() > grade2_key.get_grade():
            return 1
        elif grade1_key.get_grade() < grade2_key.get_grade():
            return -1
        else:
            if grade1_key.get_st_name() < grade2_key.get_st_name():
                return 1
            elif grade1_key.get_st_name() > grade2_key.get_st_name():
                return -1
            else:
                return 0

    def new_sorted(self, list, key = lambda x : x, reverse = False, mode = 's', cmp = default_cmp):
        """New sorted function, using bubble sort and shell sort

        Args:
            list (list): List of elements to sort
            key (function, optional): Key function to use in comparison. Defaults to lambdax:x.
            reverse (bool, optional): Whether to reverse the sorting order. Defaults to False.
            mode (str, optional): Used to choose the algorithm - (s)hell/(b)ubble. Defaults to 's'.
            cmp (function, optional): Comparison function to use. Defaults to default_cmp.

        Returns:
            list: Sorted list
        """
        if mode == "b":
            sorted = False
            while not sorted:
                sorted = True
                for i in range(len(list)-1):
                    if cmp(list[i+1], list[i], key) < 0:
                        sorted = False
                        list[i], list[i+1] = list[i+1], list[i]
        elif mode == "s":
            gaps = [57, 23, 10, 4, 1]
            for gap in gaps:
                if gap <= len(list)/2:
                    i = 0
                    j = gap
                    while j < len(list):
                        if cmp(list[i], list[j], key) == 1:
                            list[i], list[j] = list[j], list[i]
                        i += 1
                        j += 1

                        k = i
                        while k - gap >= 0:
                            if cmp(list[k-gap], list[k], key) == 1:
                                list[k], list[k-gap] = list[k-gap], list[k]
                            k -= 1

        if reverse == True:
            reversed_list = []
            for i in range(len(list)):
                reversed_list.append(list[-i-1])
            return reversed_list
        return list


class GradeTestCase(unittest.TestCase):
    def setUp(self):
        self.test_gr = MemoryGradeRepo()
        self.test_str = MemoryStudentRepo()
        self.test_sr = MemorySubjectRepo()
        self.test_validator = GradeValidator()
        self.test_service = GradeService(self.test_gr, self.test_str, self.test_sr, self.test_validator)

    def test_new_sort(self):
        test_list = [25, 33, 27, 4, 7, 14, 11, 57, 46, 49, 54, 26, 42, 41, 13, 40, 59, 5, 45, 55, 37, 31, 23, 36, 18]
        sorted_list = self.test_service.new_sorted(test_list, reverse=True, mode='b')
        print(sorted_list)
    
    def test_sort_subjects(self):
        self.test_student = Student(11, "H")
        self.test_student2 = Student(15, "J")
        self.test_subject = Subject(12, "GH", "I")
        self.test_subject2 = Subject(13, "FP", "G")
        self.test_str.store(self.test_student)
        self.test_str.store(self.test_student2)
        self.test_sr.store(self.test_subject)
        self.test_sr.store(self.test_subject2)

        self.test_service.assign(11, 12, 8)
        self.test_service.assign(11, 13, 9)
        self.test_service.assign(15, 12, 10)
        self.ordered = self.test_service.sort_subjects_by_grade_no()
        self.assertTrue(self.ordered[0][0] == 12)

    def test_average(self):
        self.test_student = Student(11, "H")
        self.test_subject = Subject(12, "GH", "I")
        self.test_subject2 = Subject(13, "FP", "G")
        self.test_str.store(self.test_student)
        self.test_sr.store(self.test_subject)
        self.test_sr.store(self.test_subject2)

        self.test_service.assign(11, 12, 8)
        self.test_service.assign(11, 13, 9)
        self.averages = self.test_service.student_average_grade()
        self.assertTrue(self.averages[0][1] == 8.5)

    def test_assign(self):
        self.test_student = Student(11, "H")
        self.test_subject = Subject(13, "FP", "G")
        self.test_str.store(self.test_student)
        self.test_sr.store(self.test_subject)

        self.test_service.assign(11, 13, 10)
        assert(len(self.test_service.get_all()) == 1)

    def test_sort_by_name(self):
        self.test_student = Student(11, "J")
        self.test_student2 = Student(12, "G")
        self.test_subject = Subject(13, "FP", "G")
        self.test_str.store(self.test_student)
        self.test_str.store(self.test_student2)
        self.test_sr.store(self.test_subject)

        self.test_service.assign(11, 13, 7)
        self.test_service.assign(12, 13, 9)

        self.sorted = self.test_service.sort_by_name(13)
        self.assertTrue(self.sorted[0].get_st_name() == "G")

    def test_sort_by_grade(self):
        self.test_student = Student(11, "H")
        self.test_student2 = Student(12, "G")
        self.test_subject = Subject(13, "FP", "G")
        self.test_str.store(self.test_student)
        self.test_str.store(self.test_student2)
        self.test_sr.store(self.test_subject)

        self.test_service.assign(11, 13, 7)
        self.test_service.assign(12, 13, 9)

        self.sorted = self.test_service.sort_by_grade(13)
        self.assertTrue(self.sorted[0].get_grade() == 9)

        self.test_service.assign(11, 13, 9)
        self.test_service.assign(12, 13, 9)

        self.sorted = self.test_service.sort_by_grade(13)
        self.assertTrue(self.sorted[0].get_st_name() == "G")

        self.test_service.assign(11, 13, 8)

        self.sorted = self.test_service.sort_by_grade(13)
        self.assertTrue(self.sorted[0].get_st_name() == "G") 

if __name__ == "__main__":
    unittest.main()
