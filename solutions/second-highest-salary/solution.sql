select max(Employee.salary) as SecondHighestSalary from Employee
where Employee.salary < (select max(Employee.salary) from Employee)
