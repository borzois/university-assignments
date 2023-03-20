from domain.entities import Student, Subject, Grade
import unittest

class FileStudentRepo:
    def __init__(self):
        """Initializes the repository
        """
        self.__filename = "python/assignment_7-9/files/students.txt"
        self.__students = []
    
    def __fload(self):
        """Loads a student list from file

        Returns:
            list: student list
        """
        try:
            f = open(self.__filename, "r")
        except IOError:
            print ("Could not open file")
            return []
        student_id = f.readline().strip()
        student_list = []
        while student_id != "":
            student_name = f.readline().strip()
            student = Student(int(student_id), student_name)
            student_list.append(student)
            student_id = f.readline().strip()
        f.close()
        return student_list

    def __fstore(self, student_list):
        """Stores the current list from memory into the file

        Args:
            student_list (list): student list
        """
        try:
            f = open(self.__filename, "w")
        except IOError:
            print ("Could not open file")
        for student in student_list:
            student_string = str(student.get_id()) + "\n" + student.get_name() + "\n"
            f.write(student_string)

    def store(self, student):
        """Stores an object in the repository

        Args:
            student (object): Student object

        Raises:
            ValueError: Error
        """
        self.__students = self.__fload()
        for st in self.__students:
            if st.get_id() == student.get_id():
                raise ValueError("A student with the same id already exists")
        else:
            self.__students.append(student)
            self.__fstore(self.__students)

    def remove(self, student):
        """Removes an object from the repository

        Args:
            student (object): Student object
        """
        self.__students = self.__fload()
        modified_list = []
        for st in self.__students:
            if st.get_id() != student.get_id():
                modified_list.append(st)
        self.__students = modified_list
        self.__fstore(self.__students)

    def modify(self, student, new_student):
        """Modifies an object

        Args:
            student (object): Student object
            new_student (object): New student object
        """
        self.__students = self.__fload()
        modified_list = []
        for st in self.__students:
            if st.get_id() != student.get_id():
                modified_list.append(st)
            else:
                modified_list.append(new_student)
        self.__students = modified_list
        self.__fstore(self.__students)

    '''
    def store_modify_recursive(self, students, student, new_student, i):
        """Passes the arguments to the recursive function and stores the returned list

        Args:
            students (list): Student list
            student (object): Student object
            new_student (object): New student object
            i (int): Length of student list
        """
        new_list = self.modify_recursive(students, student, new_student, i)
        self.__fstore(new_list)

    def modify_recursive(self, students, student, new_student, i):
        """Modifies an object

        Args:
            student (object): Student object
            new_student (object): New student object
            students: student list
            i: length of student list
        """
        if i == 0:
            print("h")
            return []
            
        elif students[i-1].get_id() == student.get_id():
            return self.modify_recursive(students, student, new_student, i-1).append(new_student)
        print(i)
        return self.modify_recursive(students, student, new_student, i-1).append(students[i-1])
    '''

    def modify_recursive(self, students, student, new_student, i, new_list):
        """Modifies an object

        Args:
            student (object): Student object
            new_student (object): New student object
            students: student list
            i: length of student list
        """
        if i == 0:
            new_list = []
            return new_list
        elif students[i-1].get_id() == student.get_id():
            new_list.append(new_student)
        else:
            new_list.append(students[i-1])
        self.modify_recursive(students, student, new_student, i-1, new_list)
        if len(new_list) == len(students):
            self.__fstore(reversed(new_list))
    
    def get_all(self):
        """Returns the list of students

        Returns:
            list: List of students
        """
        self.__students = self.__fload()
        return self.__students

    def search(self, id):
        """Returns a student by id

        Args:
            id (int): Student id

        Returns:
            st (object): Student object
        """

        self.__students = self.__fload()
        for st in self.__students:
            if st.get_id() == id:
                return st
        raise ValueError("There is no student with id " + str(id))

    def search_recursive(self, students, id, i):
        """Returns a student by id

        Args:
            students (list): Student list
            id (int): Student id
            i (int): Length of list

        Returns:
            object: Student object
        """
        if students[i-1].get_id() == id:
            return students[i-1]
        if i == 1:
            raise ValueError("Student not found")
        return self.search_recursive(students, id, i - 1)
            
class FileSubjectRepo:
    def __init__(self):
        """Initializes the repository
        """
        self.__filename = "python/assignment_7-9/files/subjects.txt"
        self.__subjects = []
    
    def __fload(self):
        """Loads a subject list from file

        Returns:
            list: subject list
        """
        try:
            f = open(self.__filename, "r")
        except IOError:
            print ("Could not open file")
            return []
        subject_id = f.readline().strip()
        subject_list = []
        while subject_id != "":
            subject_name = f.readline().strip()
            subject_professor = f.readline().strip()
            subject = Subject(int(subject_id), subject_name, subject_professor)
            subject_list.append(subject)
            subject_id = f.readline().strip()
        f.close()
        return subject_list

    def __fstore(self, subject_list):
        """Stores the current list from memory into the file

        Args:
            subject_list (list): subject list
        """
        try:
            f = open(self.__filename, "w")
        except IOError:
            print ("Could not open file")
        for subject in subject_list:
            subject_string = str(subject.get_id()) + "\n" + subject.get_name() + "\n" + subject.get_professor() + "\n"
            f.write(subject_string)

    def store(self, subject):
        """Stores an object in the repository

        Args:
            subject (object): Subject object

        Raises:
            ValueError: Error
        """
        self.__subjects = self.__fload()
        for sub in self.__subjects:
            if sub.get_id() == subject.get_id():
                raise ValueError("A subject with the same id already exists")
        else:
            self.__subjects.append(subject)
            self.__fstore(self.__subjects)

    def remove(self, subject):
        """Removes an object from the repository

        Args:
            subject (object): Subject object
        """
        self.__subjects = self.__fload()
        modified_list = []
        for sub in self.__subjects:
            if sub.get_id() != subject.get_id():
                modified_list.append(sub)
        self.__subjects = modified_list
        self.__fstore(self.__subjects)

    def modify(self, subject, new_subject):
        """Modifies an object

        Args:
            subject (object): Subject object
            new_subject (object): New subject object
        """
        self.__subjects = self.__fload()
        modified_list = []
        for sub in self.__subjects:
            if sub.get_id() != subject.get_id():
                modified_list.append(sub)
            else:
                modified_list.append(new_subject)
        self.__subjects = modified_list
        self.__fstore(self.__subjects)
        
    def get_all(self):
        """Returns the list of subjects

        Returns:
            list: List of subjects
        """
        self.__subjects = self.__fload()
        return self.__subjects

    def search(self, id):
        """Returns a subject by id

        Args:
            id (int): Subject id

        Returns:
            st (object): Subject object
        """
        self.__subjects = self.__fload()
        for sub in self.__subjects:
            if sub.get_id() == id:
                return sub
        raise ValueError("There is no subject with id " + str(id))

class FileGradeRepo:
    def __init__(self):
        """Initializes the grade repository
        """
        self.__grades = []
        self.__filename = "python/assignment_7-9/files/grades.txt"

    def __fload(self):
        """Loads a grade list from file

        Returns:
            list: grade list
        """
        try:
            f = open(self.__filename, "r")
        except IOError:
            print ("Could not open file")
            return []
        student_id = f.readline().strip()
        grade_list = []
        while student_id != "":
            student_name = f.readline().strip()
            subject_id = f.readline().strip()
            subject_name = f.readline().strip()
            grade = f.readline().strip()
            student = Student(int(student_id), student_name)
            subject = Subject(int(subject_id), subject_name, "prof")
            grade = Grade(student, subject, int(grade))
            grade_list.append(grade)
            student_id = f.readline().strip()
        f.close()
        return grade_list

    def __fstore(self, grade_list):
        """Stores the current list from memory into the file

        Args:
            student_list (list): grade list
        """
        try:
            f = open(self.__filename, "w")
        except IOError:
            print ("Could not open file")
        for grade in grade_list:
            student_string = str(grade.get_st_id()) + "\n" + grade.get_st_name() + "\n" + str(grade.get_sub_id()) + "\n" + grade.get_sub_name() + "\n" + str(grade.get_grade()) + "\n"
            f.write(student_string)


    def assign(self, grade):
        """Adds a grade to the repo

        Args:
            grade (object): Grade object
        """
        self.__grades = self.__fload()
        self.__grades.append(grade)
        self.__fstore(self.__grades)

    def get_all(self):
        """Returns the list of grades

        Returns:
            list: List of grades
        """
        self.__grades = self.__fload()
        return self.__grades

class RepoTestCase(unittest.TestCase):
    def setUp(self):
        self.test_repo = FileStudentRepo()
        self.test_list = self.test_repo.get_all()
    
    def test_load(self):
        self.assertTrue(len(self.test_list) != 0)

if __name__ == "__main__":
    unittest.main()