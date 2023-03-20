from domain.validators import StudentValidator, SubjectValidator, GradeValidator
from ui.console import Console, Menu
from repository.repo import MemoryStudentRepo, MemorySubjectRepo, MemoryGradeRepo
#from repository.file_repo import FileStudentRepo, FileSubjectRepo
from repository.file_repo_lab import FileStudentRepo, FileSubjectRepo, FileGradeRepo
from service.student_service import StudentService
from service.subject_service import SubjectService
from service.grade_service import GradeService

student_repo = MemoryStudentRepo()
subject_repo = MemorySubjectRepo()
grade_repo = MemoryGradeRepo()

file_student_repo = FileStudentRepo()
file_subject_repo = FileSubjectRepo()
file_grade_repo = FileGradeRepo()

student_validator = StudentValidator()
subject_validator = SubjectValidator()
grade_validator = GradeValidator()

student_service = StudentService(file_student_repo, student_validator)
subject_service = SubjectService(file_subject_repo, subject_validator)
grade_service = GradeService(file_grade_repo, file_student_repo, file_subject_repo, grade_validator)

menu = Menu()

console = Console(student_service, subject_service, grade_service, menu)
console.ui()