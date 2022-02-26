select t1.name as Employee
from Employee as t1
join Employee as t2
on t1.managerId = t2.id and t1.salary > t2.salary
