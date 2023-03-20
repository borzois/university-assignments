import unittest

class Student:
    def __init__(self, id, name):
        """Initializes the Student object

        Args:
            id (int): Student id
            name (string): Student name
        """
        self._id = id
        self._name = name

    def get_id(self):
        return self._id

    def get_name(self):
        return self._name

    def set_id(self, val):
        self._id = val

    def set_name(self, val):
        self._name = val

    def __str__(self):
        return str(self._id) + ":" + self._name

class Subject:
    def __init__(self, id, name, professor):
        """Initializes the Subject object

        Args:
            id (int): Subject id
            name (string): Subject name
            professor (string): Name of professor
        """
        self._id = id
        self._name = name
        self._professor = professor

    def get_id(self):
        return self._id

    def get_name(self):
        return self._name

    def get_professor(self):
        return self._professor

    def set_id(self, val):
        self._id = val

    def set_name(self, val):
        self._name = val

    def set_professor(self, val):
        self._professor = val

    def __str__(self):
        return str(self._id) + ":" + self._name + ", " + self._professor

class Grade:
    def __init__(self, student, subject, grade):
        self.__student_id = student.get_id()
        self.__student_name = student.get_name()
        self.__subject_id = subject.get_id()
        self.__subject_name = subject.get_name()
        self.__grade = grade

    def get_grade(self):
        return self.__grade

    def get_st_id(self):
        return self.__student_id

    def get_st_name(self):
        return self.__student_name

    def get_sub_id(self):
        return self.__subject_id

    def get_sub_name(self):
        return self.__subject_name

class EntityTestCase(unittest.TestCase):
    def setUp(self):
        self.student1 = Student(64, "H")
        self.subject1 = Subject(64, "H", "G")
    
    def test_create_student(self):
        self.assertTrue(self.student1.get_id() == 64)
        self.assertTrue(self.student1.get_name()) == "H"

    def test_create_subject(self):
        self.assertTrue(self.subject1.get_id() == 64)
        self.assertTrue(self.subject1.get_name()) == "H"
        self.assertTrue(self.subject1.get_professor() == "G")

    def test_create_grade(self):
        self.grade1 = Grade(self.student1, self.subject1, 6)
        self.assertTrue(self.grade1.get_grade() == 6)
        self.assertTrue(self.grade1.get_st_id() == 64)
        self.assertTrue(self.grade1.get_st_name() == "H")
        self.assertTrue(self.grade1.get_sub_id() == 64)
        self.assertTrue(self.grade1.get_sub_name() == "H")

if __name__ == "__main__":
    unittest.main()