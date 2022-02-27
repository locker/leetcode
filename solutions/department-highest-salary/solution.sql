select
    Department.name as Department,
    Employee.name as Employee,
    DepartmentMaxSalary.salary as Salary
from Employee
join (select Employee.departmentId, max(Employee.salary) as salary
      from Employee group by Employee.departmentId) as DepartmentMaxSalary
on (Employee.departmentId = DepartmentMaxSalary.departmentId and
    Employee.salary = DepartmentMaxSalary.salary)
join Department
on Employee.departmentId = Department.id
