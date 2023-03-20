from service.student_service import StudentService
from service.subject_service import SubjectService

class Menu:
    def main_menu(self):
        print("===========================")
        print("1. Manage lists")
        print("2. Search")
        print("3. Assign grades")
        print("4. Stats\n")
        print("(S)ave/(L)oad")
        print("===========================")

    def manager_menu(self):
        print("===========================")
        print("1. Manage students")
        print("2. Manage subjects")
        print("===========================")

    def manager_menu_2(self):
        print("===========================")
        print("1. Add..")
        print("2. Remove..")
        print("3. Modify..")
        print("4. Get all")
        print("9. Generate")
        print("===========================")

    def search_menu(self):
        print("===========================")
        print("1. Search students")
        print("2. Search subjects")
        print("===========================")

    def stat_menu(self):
        print("===========================")
        print("1. Students sorted alphabetically")
        print("2. Students sorted by grade")
        print("3. Top 20% of students")
        print("4. First 3 subjects by number of grades")
        print("===========================")

class Console:
    def __init__(self, student_service, subject_service, grade_service, menu):
        self.__student_service = student_service
        self.__subject_service = subject_service
        self.__grade_service = grade_service
        self.__menu = menu

    def __load_from_file(self):
        """Loads from file
        """
        self.__student_service.load()
        self.__subject_service.load()

    def __save_to_file(self):
        """Saves to file
        """
        self.__student_service.save()
        self.__subject_service.save()

    def __add_student(self):
        """
        Adds a new student from input
        """
        try:
            id = int(input("Student id: "))
        except ValueError:
            print("ID must be a number")
            return
        name = input("Name: ")

        try:
            added_student = self.__student_service.add_student(id, name)
            print("Student " + str(added_student.get_id()) + " added successfully")
        except ValueError as e:
            print(e)

    def __remove_student(self):
        """
        Removes a student 
        """
        id = int(input("Student id: "))
        try:
            removed_student = self.__student_service.remove_student(id, "")
            print("Student " + str(removed_student.get_id()) + " removed successfully")
        except ValueError as e:
            print(e)

    def __modify_student(self):
        """
        Modifies a student 
        """
        id = int(input("Student id: "))
        new_id = int(input("New id: "))
        new_name = input("New name: ")

        try:
            modified_student, new_student = self.__student_service.modify_r(id, "", new_id, new_name)
            print("Student " + str(modified_student.get_id()) + " is now " + str(new_student.get_id()) + ":" + new_student.get_name())
        except ValueError as e:
            print(e)

    def __add_subject(self):
        """
        Adds a new subject from input
        """
        try:
            id = int(input("Subject id: "))
        except ValueError:
            print("ID must be a number")
            return
        name = input("Name: ")
        professor = input("Professor: ")

        try:
            added_subject = self.__subject_service.add_subject(id, name, professor)
            print("Subject " + str(added_subject.get_id()) + " added successfully")
        except ValueError as e:
            print(e)

    def __remove_subject(self):
        """
        Removes a subject 
        """
        id = int(input("Subject id: "))
        try:
            removed_subject = self.__subject_service.remove_subject(id, "", "")
            print("Subject " + str(removed_subject.get_id()) + " removed successfully")
        except ValueError as e:
            print(e)

    def __modify_subject(self):
        """
        Modifies a subject
        """
        id = int(input("Subject id: "))
        new_id = int(input("New id: "))
        new_name = input("New name: ")
        new_professor = input("New professor: ")

        try:
            modified_subject, new_subject = self.__subject_service.modify_subject(id, "", "", new_id, new_name, new_professor)
            print("Subject " + str(modified_subject.get_id()) + " is now " + str(new_subject.get_id()) + ":" + new_subject.get_name() + " - " + new_subject.get_professor())
        except ValueError as e:
            print(e)


    def __get_all(self, service):
        """Prints list of students/subjects

        Args:
            service (object): Specifies which list to print
        """
        list = service.get_all()
        if service == self.__student_service:
            for st in list:
                print(str(st.get_id())+ ":" + st.get_name())
        else:
            for sub in list:
                print(str(sub.get_id())+ ":" + sub.get_name() + " - " + sub.get_professor())

    def __search_student(self):
        """Prints student with given id
        """
        id = int(input("Student id: "))
        try:
            student = self.__student_service.search_r(id)
            print(str(student.get_id()) + " : " + student.get_name())
        except ValueError as e:
            print(e)

    def __search_subject(self):
        """Prints subject with given id
        """
        id = int(input("Subject id: "))
        try:
            subject = self.__subject_service.search(id)
            print(str(subject.get_id()) + " : " + subject.get_name() + " - " + subject.get_professor())
        except ValueError as e:
            print(e)

    def __assign_grade(self):
        """Assigns grade
        """
        try:
            student_id = int(input("Student id: "))
            subject_id = int(input("Subject id: "))
            grade = int(input("Grade: "))
            self.__grade_service.assign(student_id, subject_id, grade)
        except ValueError as e:
            print(e)

    def __get_all_grades(self):
        """Prints list of grades
        """
        list = self.__grade_service.get_all()
        for el in list:
            print(str(el.get_st_id()) + ":" + el.get_st_name() + " - " + str(el.get_sub_id()) + ":" + el.get_sub_name() + " - " + str(el.get_grade()))

    def __generate_students(self):
        """Generates students
        """
        try:
            num = int(input("Number of students to generate: "))
            self.__student_service.generate(num)
        except ValueError as e:
            print(e)

    def __sort_by_name(self):
        """Sorts students by name
        """
        try:
            subject_id = int(input("Subject id: "))
            list = self.__grade_service.sort_by_name(subject_id)
            for el in list:
                print(str(el.get_st_id()) + ":" + el.get_st_name() + " - " + str(el.get_sub_id()) + ":" + el.get_sub_name() + " - " + str(el.get_grade()))
        except ValueError as e:
            print(e);

    def __sort_by_grade(self):
        """Sorts students by grade
        """
        try:
            subject_id = int(input("Subject id: "))
            list = self.__grade_service.sort_by_grade(subject_id)
            for el in list:
                print(str(el.get_st_id()) + ":" + el.get_st_name() + " - " + str(el.get_sub_id()) + ":" + el.get_sub_name() + " - " + str(el.get_grade()))
        except ValueError as e:
            print(e);

    def __get_top_students(self, percentage):
        """Gets the top [percentage]% of students

        Args:
            percentage (int): percentage of students to display
        """
        list = self.__grade_service.student_average_grade()
        for i in range(0, int(len(list) * percentage / 100)):
            student = self.__student_service.search(list[i][0])
            print(student.get_name() + " : " + str(list[i][1]))

    def __get_subjects_with_most_grades(self):
        """Gets the first 3 subjects ordered by number of grades
        """
        list = self.__grade_service.sort_subjects_by_grade_no()
        if len(list) >= 3:
            for i in range(3):
                subject = self.__subject_service.search(list[i][0])
                print(subject.get_name() + " : " + str(list[i][1]) + " grades")
        else:
            for i in range(len(list)):
                subject = self.__subject_service.search(list[i][0])
                print(subject.get_name() + " : " + str(list[i][1]) + " grades")

    def ui(self):
        while True:
            self.__menu.main_menu()
            option1 = input("Choose an option: ")
            if option1 == "1": 
                self.__menu.manager_menu()
                option2 = input("Choose an option: ")
                if option2 == "1":
                    self.__menu.manager_menu_2()
                    option3 = input("Choose an option: ")
                    if option3 == "1":
                        self.__add_student()
                    if option3 == "2":
                        self.__remove_student()
                    if option3 == "3":
                        self.__modify_student()
                    if option3 == "4":
                        self.__get_all(self.__student_service)
                    if option3 == "9":
                        self.__generate_students()
                if option2 == "2":
                    self.__menu.manager_menu_2()
                    option3 = input("Choose an option: ")
                    if option3 == "1":
                        self.__add_subject()
                    if option3 == "2":
                        self.__remove_subject()
                    if option3 == "3":
                        self.__modify_subject()
                    if option3 == "4":
                        self.__get_all(self.__subject_service)
            if option1 == "2":
                self.__menu.search_menu()
                option2 = input("Choose an option: ")
                if option2 == "1":
                    self.__search_student()
                if option2 == "2":
                    self.__search_subject()
            if option1 == "3":
                self.__assign_grade()
            if option1 == "4":
                self.__menu.stat_menu()
                option2 = input("Choose an option: ")
                if option2 == "1":
                    self.__sort_by_name()
                if option2 == "2":
                    self.__sort_by_grade()
                if option2 == "3":
                    self.__get_top_students(50)
                if option2 == "4":
                    self.__get_subjects_with_most_grades()
            if option1 == "9":
                self.__get_all_grades()
            if option1 == "L":
                self.__load_from_file()
            if option1 == "S":
                self.__save_to_file()
