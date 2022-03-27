delete Person from Person inner join Person as t
on Person.email = t.email and Person.id > t.id
