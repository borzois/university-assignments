from domain.entities import Student, Subject
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
        line = f.readline().strip()
        student_list = []
        while line != "":
            split_line = line.split(";")
            student = Student(int(split_line[0]), split_line[1])
            student_list.append(student)
            line = f.readline().strip()
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
            student_string = str(student.get_id()) + ";" + student.get_name() + ";\n"
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
        line = f.readline().strip()
        subject_list = []
        while line != "":
            split_line = line.split(";")
            subject = Subject(int(split_line[0]), split_line[1], split_line[2])
            subject_list.append(subject)
            line = f.readline().strip()
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
            subject_string = str(subject.get_id()) + ";" + subject.get_name() + ";" + subject.get_professor() + ";\n"
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

class RepoTestCase(unittest.TestCase):
    def setUp(self):
        self.test_repo = FileStudentRepo()
        self.test_list = self.test_repo.get_all()
    
    def test_load(self):
        self.assertTrue(len(self.test_list) != 0)

if __name__ == "__main__":
    unittest.main()