select
    Department.name as Department,
    Employee.name as Employee,
    TopSalaries.salary as Salary
from Employee
join (select t1.departmentId, t1.salary
      from Employee as t1 left join Employee as t2
      on t1.departmentId = t2.departmentId and t1.salary < t2.salary
      group by t1.departmentId, t1.salary
      having count(distinct t2.salary) < 3) as TopSalaries
on (Employee.departmentId = TopSalaries.departmentId and
    Employee.salary = TopSalaries.salary)
join Department
on Department.id = Employee.departmentId
