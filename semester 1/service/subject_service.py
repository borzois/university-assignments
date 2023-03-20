from domain.entities import Subject
from domain.validators import SubjectValidator
from repository.repo import MemorySubjectRepo
from repository.file_repo import FileSubjectRepo
import unittest

class SubjectService:
    def __init__(self, repo, validator):
        """Initializes the subject service

        Args:
            repo (object): Subject repository 
            validator (object): Subject validator
        """
        self.__repo = repo
        self.__validator = validator

    def add_subject(self, id, name, professor):
        """Adds a new subject to the repository

        Args:
            id (int): Subject id
            name (string): Subject name
            professor (string): Name of professor

        Returns:
            object: The added subject
        """
        new_subject = Subject(id, name, professor)
        self.__validator.validate(new_subject)
        self.__repo.store(new_subject)
        return new_subject

    def remove_subject(self, id, name, professor):
        """Removes a subject

        Args:
            id (int): Subject id
            name (string): Subject name
            professor (string): Name of professor

        Returns:
            object: The added subject
        """
        deleted_subject = Subject(id, name, professor)
        self.__repo.remove(deleted_subject)
        return deleted_subject

    def modify_subject(self, id, name, professor, new_id, new_name, new_professor):
        """Modifies a subject

        Args:
            id (int): Subject id
            name (string): Subject name
            professor (string): Name of professor
            new_id (int): Modified id
            new_name (string): Modified name
            new_professor (string): Modified professor name

        Returns:
            objects: The old subject and the new subject
        """
        modified_subject = Subject(id, name, professor)
        new_subject = Subject(new_id, new_name, new_professor)
        self.__repo.modify(modified_subject, new_subject)
        return modified_subject, new_subject

    def get_all(self):
        """Returns the list of all subjects

        Returns:
            list: List of subjects
        """
        return self.__repo.get_all()

    def search(self, id):
        """Returns subject by id

        Args:
            id (int): id

        Returns:
            object: subject
        """
        return self.__repo.search(id)

class SubjectTestCase(unittest.TestCase):
    def setUp(self):
        self.test_repo = MemorySubjectRepo()
        self.test_validator = SubjectValidator()
        self.test_service = SubjectService(self.test_repo, self.test_validator)
        self.subject = self.test_service.add_subject(48, "H", "Abc")

    def test_add(self):
        self.assertTrue(self.subject.get_id() == 48)
        self.assertTrue(self.subject.get_name() == "H")
        self.assertTrue(self.subject.get_professor() == "Abc")

    def test_remove(self):
        self.test_service.remove_subject(48, "H", "Abc")
        self.assertTrue(len(self.test_service.get_all()) == 0)

    def test_modify(self):
        self.subject, self.subject = self.test_service.modify_subject(48, "H", "Abc", 49, "G", "Def")
        self.assertTrue(self.subject.get_id() == 49)
        self.assertTrue(self.subject.get_name() == "G")

if __name__ == "__main__":
    unittest.main()