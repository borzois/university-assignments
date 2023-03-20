from domain.entities import Student, Subject
import unittest

class MemoryStudentRepo:
    def __init__(self):
        """Initializes the repository
        """
        self.__students = []
    
    def store(self, student):
        """Stores an object in the repository

        Args:
            student (object): Student object

        Raises:
            ValueError: Error
        """
        for st in self.__students:
            if st.get_id() == student.get_id():
                raise ValueError("A student with the same id already exists")
        else:
            self.__students.append(student)

    def remove(self, student):
        """Removes an object from the repository

        Args:
            student (object): Student object
        """
        modified_list = []
        for st in self.__students:
            if st.get_id() != student.get_id():
                modified_list.append(st)
        self.__students = modified_list

    def modify(self, student, new_student):
        """Modifies an object

        Args:
            student (object): Student object
            new_student (object): New student object
        """
        modified_list = []
        for st in self.__students:
            if st.get_id() != student.get_id():
                modified_list.append(st)
            else:
                modified_list.append(new_student)
        self.__students = modified_list

    def get_all(self):
        """Returns the list of students

        Returns:
            list: List of students
        """
        return self.__students

    def search(self, id):
        """Returns a student by id

        Args:
            id (int): Student id

        Returns:
            st (object): Student object
        """
        for st in self.__students:
            if st.get_id() == id:
                return st
        raise ValueError("There is no student with id " + str(id))

class MemorySubjectRepo:
    def __init__(self):
        """Initializes the repository
        """
        self.__subjects = []
    
    def store(self, subject):
        """Stores an object in the repository

        Args:
            subject (object): Subject object

        Raises:
            ValueError: Error
        """
        for sub in self.__subjects:
            if sub.get_id() == subject.get_id():
                raise ValueError("A subject with the same id already exists")
        else:
            self.__subjects.append(subject)

    def remove(self, subject):
        """Removes an object from the repository

        Args:
            subject (object): Subject object
        """
        modified_list = []
        for sub in self.__subjects:
            if sub.get_id() != subject.get_id():
                modified_list.append(sub)
        self.__subjects = modified_list

    def modify(self, subject, new_subject):
        """Modifies an object

        Args:
            subject (object): Subject object
            new_subject (object): New subject object
        """
        modified_list = []
        for sub in self.__subjects:
            if sub.get_id() != subject.get_id():
                modified_list.append(sub)
            else:
                modified_list.append(new_subject)
        self.__subjects = modified_list
        
    def get_all(self):
        """Returns the list of subjects

        Returns:
            list: List of subjects
        """
        return self.__subjects

    def search(self, id):
        """Returns a subject by id

        Args:
            id (int): Subject id

        Returns:
            st (object): Subject object
        """
        for sub in self.__subjects:
            if sub.get_id() == id:
                return sub
        raise ValueError("There is no subject with id " + str(id))

class MemoryGradeRepo:
    def __init__(self):
        """Initializes the grade repository
        """
        self.__grades = []

    def assign(self, grade):
        """Adds a grade to the repo

        Args:
            grade (object): Grade object
        """
        self.__grades.append(grade)

    def get_all(self):
        """Returns the list of grades

        Returns:
            list: List of grades
        """
        return self.__grades

class RepoTestCase(unittest.TestCase):
    def test_student_store(self):
        self.test_repo = MemoryStudentRepo()
        self.test_student = Student(16, "T")

        self.assertTrue(len(self.test_repo.get_all()) == 0)
        self.test_repo.store(self.test_student)
        self.assertTrue(len(self.test_repo.get_all()) == 1)

    def test_student_modify(self):
        self.test_repo = MemoryStudentRepo()
        self.test_student = Student(16, "T")
        self.test_repo.store(self.test_student)
        self.new_student = Student(17, "U")
        self.test_repo.modify(self.test_student, self.new_student)
        self.assertTrue(self.test_repo.get_all()[0].get_id() == 17)
        self.assertTrue(self.test_repo.get_all()[0].get_name() == "U")

    def test_student_remove(self):
        self.test_repo = MemoryStudentRepo()
        self.test_student = Student(16, "T")
        self.test_repo.store(self.test_student)
        self.test_repo.remove(self.test_student)
        self.assertTrue(len(self.test_repo.get_all()) == 0)

    def test_subject_store(self):
        self.test_repo = MemorySubjectRepo()
        self.test_subject = Subject(16, "Compsci", "H")

        self.assertTrue(len(self.test_repo.get_all()) == 0)
        self.test_repo.store(self.test_subject)
        self.assertTrue(len(self.test_repo.get_all()) == 1)

    def test_subject_modify(self):
        self.test_repo = MemorySubjectRepo()
        self.test_subject = Subject(16, "Compsci", "H")
        self.test_repo.store(self.test_subject)
        self.new_subject = Subject(17, "U", "Q")
        self.test_repo.modify(self.test_subject, self.new_subject)
        self.assertTrue(self.test_repo.get_all()[0].get_id() == 17)
        self.assertTrue(self.test_repo.get_all()[0].get_name() == "U")
        self.assertTrue(self.test_repo.get_all()[0].get_professor() == "Q")

    def test_subject_remove(self):
        self.test_repo = MemorySubjectRepo()
        self.test_subject = Subject(16, "Compsci", "H")
        self.test_repo.store(self.test_subject)
        self.test_repo.remove(self.test_subject)
        self.assertTrue(len(self.test_repo.get_all()) == 0)

    def test_search_student(self):
        self.test_repo = MemoryStudentRepo()
        self.test_student = Student(16, "T")
        self.test_repo.store(self.test_student)
        self.assertTrue(self.test_repo.search(16).get_name() == "T")

    def test_search_subject(self):
        self.test_repo = MemorySubjectRepo()
        self.test_subject = Subject(16, "T", "H")
        self.test_repo.store(self.test_subject)
        self.assertTrue(self.test_repo.search(16).get_name() == "T")

if __name__ == "__main__":
    unittest.main()
