from domain.entities import Student, Subject, Grade
import unittest

class StudentValidator:
    def validate(self, student):
        """Validates a student object

        Args:
            student (object): Student

        Raises:
            ValueError: Error
        """
        errors = []
        name = student.get_name()
        if type(student.get_id()) != int:
            errors.append("ID must be a number")
        if len(name) == 0:
            errors.append("Name can not be empty")
        if name.isalpha() == False and len(name) > 0:
            errors.append("Name can not contain numbers")
        if len(errors) > 0:
            error_string = ' '.join(errors)
            raise ValueError(error_string)

class SubjectValidator:
    def validate(self, subject):
        """Validates a subject object

        Args:
            subject (object): Subject

        Raises:
            ValueError: Error
        """
        errors = []
        name = subject.get_name()
        professor = subject.get_professor()
        if type(subject.get_id()) != int:
            errors.append("ID must be a number")
        if len(name) == 0 or len(professor) == 0:
            errors.append("Name can not be empty")
        if professor.isalpha() == False and len(name) > 0:
            errors.append("Name can not contain numbers")
        if len(errors) > 0:
            error_string = ' '.join(errors)
            raise ValueError(error_string)

class GradeValidator:
    def validate(self, grade):
        """Validates a grade object

        Args:
            grade (object): Grade object
        """
        errors = []
        st_id = grade.get_st_id()
        sub_id = grade.get_sub_id()
        grade = grade.get_grade()

        if st_id == "" or sub_id == "":
            errors.append("ID can not be empty")
        if grade > 10 or grade < 1:
            errors.append("Grade must be between 1 and 10")
        if len(errors) > 0:
            error_string = ' '.join(errors)
            raise ValueError(error_string)

class ValidatorTestCase(unittest.TestCase):
    def test_grade_validator(self):
        self.test_validator = GradeValidator()
        self.test_student = Student(12, "Abc")
        self.test_subject = Subject(14, "Cde", "Fgh")
        self.test_grade = Grade(self.test_student, self.test_subject, 8)
        self.test_validator.validate(self.test_grade)

    def test_student_validator(self):
        self.test_validator = StudentValidator()
        self.test_student = Student(128, "Sergiu")
        self.test_validator.validate(self.test_student)

        self.test_student = Student("12b", "Sergiu")
        self.assertRaises(ValueError, self.test_validator.validate(self.test_student))
            
        self.test_student = Student(12, "Sergiu 12")
        self.assertRaises(ValueError, self.test_validator.validate(self.test_student))

    def test_subject_validator(self):
        self.test_validator = SubjectValidator()
        self.test_subject = Subject(128, "Mathematical analysis", "Abcdef")
        self.test_validator.validate(self.test_subject)

        self.test_subject = Subject("12b", "Mathematical analysis", "Abcdef")
        self.assertRaises(ValueError, self.test_validator.validate(self.test_subject))

        self.test_subject = Subject(128, "Mathematical analysis", "Abcdef 12")
        self.assertRaises(ValueError, self.test_validator.validate(self.test_subject))

        self.test_subject = Subject(128, "Ms", "Abcdef")
        self.assertRaises(ValueError, self.test_validator.validate(self.test_subject))


