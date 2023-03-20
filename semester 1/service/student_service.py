from domain.entities import Student
from domain.validators import StudentValidator
from repository.repo import MemoryStudentRepo
from repository.file_repo_lab import FileStudentRepo
import random, string, unittest

class StudentService:
    def __init__(self, repo, validator):
        """Initializes the student service

        Args:
            repo (object): Student repository 
            validator (object): Student validator
        """
        self.__repo = repo
        self.__validator = validator

    def add_student(self, id, name):
        """Adds a new student to the repository

        Args:
            id (int): Student id
            name (string): Student name

        Returns:
            object: The added student
        """
        new_student = Student(id, name)
        self.__validator.validate(new_student)
        self.__repo.store(new_student)
        return new_student

    def remove_student(self, id, name):
        """Removes a student

        Args:
            id (int): Student id
            name (string): Student name

        Returns:
            object: The added student
        """
        deleted_student = Student(id, name)
        self.__repo.remove(deleted_student)
        return deleted_student

    def modify_student(self, id, name, new_id, new_name):
        """Modifies a student

        Args:
            id (int): Student id
            name (string): Student name
            new_id (int): Modified id
            new_name (string): Modified name

        Returns:
            objects: The old student and the new student
        """
        modified_student = Student(id, name)
        new_student = Student(new_id, new_name)
        self.__repo.modify(modified_student, new_student)
        return modified_student, new_student

    def modify_r(self, id, name, new_id, new_name):
        """Modifies a student

        Args:
            id (int): Student id
            name (string): Student name
            new_id (int): Modified id
            new_name (string): Modified name

        Returns:
            objects: The old student and the new student
        """
        modified_student = Student(id, name)
        new_student = Student(new_id, new_name)
        student_list = self.__repo.get_all()
        new_list = []
        self.__repo.modify_recursive(student_list, modified_student, new_student, len(student_list), new_list)
        return modified_student, new_student

    def get_all(self):
        """Returns the list of all students

        Returns:
            list: List of students
        """
        return self.__repo.get_all()

    def search(self, id):
        """Returns subject by id

        Args:
            id (int): id

        Returns:
            object: student
        """
        return self.__repo.search(id)

    def search_r(self, id):
        """Returns subject by id

        Args:
            id (int): id

        Returns:
            object: student
        """
        student_list = self.__repo.get_all()
        return self.__repo.search_recursive(student_list, id, len(student_list))

    def generate(self, num):
        """Generates students

        Args:
            num (int): number of students to generate
        """
        for i in range(num):
            letters = string.ascii_lowercase
            name = "".join(random.choice(letters) for j in range(6))
            generated_student = Student(i, name.capitalize())
            self.__validator.validate(generated_student)
            self.__repo.store(generated_student)

class StudentTestCase(unittest.TestCase):
    def setUp(self):
        self.test_repo = MemoryStudentRepo()
        self.test_validator = StudentValidator()
        self.test_service = StudentService(self.test_repo, self.test_validator)
        self.added_student = self.test_service.add_student(48, "H")

    def test_add(self):
        self.assertTrue(self.added_student.get_id() == 48)
        self.assertTrue(self.added_student.get_name() == "H")

    def test_remove(self):
        self.test_service.remove_student(48, "H")
        self.assertTrue(len(self.test_service.get_all()) == 0)

    def test_modify(self):
        self.added_student, self.new_student = self.test_service.modify_student(48, "H", 49, "G")
        self.assertTrue(self.new_student.get_id() == 49)
        self.assertTrue(self.new_student.get_name() == "G")

    def test_get_all(self):
        self.test_service.generate(16)
        self.assertTrue(len(self.test_service.get_all()) == 17)

if __name__ == "__main__":
    unittest.main()