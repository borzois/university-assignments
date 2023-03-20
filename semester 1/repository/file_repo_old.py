from domain.entities import Student, Subject

class FileStudentRepo:
    def __init__(self):
        """Initializes the repository
        """
        self.__filename = "python/assignment_7-9/files/students.txt"
    
    def load(self):
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

    def store(self, student_list):
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

class FileSubjectRepo:
    def __init__(self):
        """Initializes the repository
        """
        self.__filename = "python/assignment_7-9/files/subjects.txt"
    
    def load(self):
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

    def store(self, subject_list):
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

def test_load_student():
    test_repo = FileStudentRepo()
    test_list = test_repo.load()
    assert(len(test_list) != 0)

def test_load_subject():
    test_repo = FileSubjectRepo()
    test_list = test_repo.load()
    assert(len(test_list) != 0)

test_load_student()
test_load_subject()
