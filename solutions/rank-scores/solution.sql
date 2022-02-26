select t1.score, count(*) as 'rank'
from Scores as t1
left join (select distinct score from Scores) as t2
on t2.score >= t1.score
group by t1.score, t1.id
order by t1.score desc
