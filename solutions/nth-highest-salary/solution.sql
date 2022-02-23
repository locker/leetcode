CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  DECLARE M INT;
  SET M = N - 1;
  RETURN (
      SELECT DISTINCT Employee.salary
      FROM Employee
      ORDER BY Employee.salary DESC
      LIMIT 1 OFFSET M
  );
END
