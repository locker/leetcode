select distinct t1.email as Email
from Person as t1
join Person as t2
on t1.email = t2.email and t1.id != t2.id
